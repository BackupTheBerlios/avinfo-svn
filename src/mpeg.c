/*************************************************************************
 * mpeg.c MPEG 1/2 headers reading code [part of AVInfo 1.x]
 *
 * Copyright (c) 2003 George Shuklin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *   
 * You should have received a copy of the GNU General Public License along
 * with this program (see the file COPYING); if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
 * MA  02111-1307  USA  or visit http://www.gnu.org/copyleft/gpl.html
 *
 *************************************************************************/
#define _POSIX_C_SOURCE 200112L

#include "mpeg.h"
#include "memleak.h"
#define MAX_READING_BYTES 32768
#define MAX_TRYS 16
#define MPEG_ISO_11172_END_CODE 0x000001B9
#define MPEG_PACK_HEADER 0x000001BA
#define MPEG_SYSTEM_HEADER 0x000001BB
#define MPEG_PICTURE_SEQUENCE 0x00001B3
#define MAX_STREAMS 9

#undef MPEG_DEBUG


const unsigned char mp3_bitrate_table[16][8]={ /*in 8k units*/
	/*                       MP3   MP2				*/
	/*v2l3  v2l2  v2l1  v2l? v1l3! v1l2  v1l1  */
	{ 0,    0,    0,    0,    0,    0,    0,    0 },
	{ 0,    1,   4,   4,    0,   4,   4,   4 },
	{ 0,    2,  6,   6,    0,   5,   6,   8 },
	{ 0,    3,  7,   12,    0,   6,   7,   12 },
	{ 0,    4,  8,  16,    0,   7,   8,  16 },
	{ 0,    8,  10,  20,    0,   8,   10,  20 },
	{ 0,    10,  12,  24,    0,   10,   12,  24 },
	{ 0,    7, 14,  28,    0,   12,  14,  28},
	{ 0,    8, 16,  32,    0,   14, 16,  32},
	{ 0,    16,20,  36,    0,   16, 20,  36},
	{ 0,    20,24,  40,    0,   20, 24,  40},
	{ 0,    14,28,  44,    0,   24, 28,  44},
	{ 0,    16,32,  48,    0,   28, 32,  48},
	{ 0,    32,40,  52,    0,   32, 40,  52},
	{ 0,    40,52,  56,    0,   40, 48,  56},
	{ 0,    0,  0,   0,  0,    0, 0,    0 }
};
unsigned short int mp3_freq_table[4][2]={
	{22050,44100},
	{24000,48000},
	{16000,32000},
	{0,    0}
};

const char fps_table[16][2]={ /*{0,0} means error or unknown value*/
		{0,0},{23,98},{24,0},{25,0},	
		{29,97},{30,0},{50,0},{59,94},
		{60,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0}
	};

const char aspect_table[16][2]={ /*format: Y:X*/
		{0,0},{1,1},{3,4},{16,9},
		{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0}
	};

typedef struct{
int exist;
int x;
int y;
int fps;
int aspect;
int bitrate;
}vids_t;

typedef struct{
int exist;
int bitrate;
int freq;
int ch;
}auds_t;

int GetMP3FrameData(int scan,int *bitrate, int *freq, int *ch){
			int mpeg_mp3_ver=(scan&0xE0000)>>17;
			int fr=mp3_freq_table[(scan&0xC00)>>10][mpeg_mp3_ver>>2];
			int btr=mp3_bitrate_table[(scan&0xF000)>>12][mpeg_mp3_ver]*8000;
			if(!fr||!btr) {return 0;}
			*ch=((scan&0xC0)==0xC0?1:2);
			*bitrate=btr;
			*freq=fr;
			return 144*btr/fr+((scan&0x200)?1:0)-4;
}

int mpegparse ( vlist_t* list,FILE* file, int flags ){

#define GETC(a) do {if(pos<readed_bytes) a=buffer[pos++]; else break;} while(0)
#define _GETDW(a) if(pos<readed_bytes-4) {a=buffer[pos++]<<24;a+=buffer[pos++]<<16;a+=buffer[pos++]<<8;a+=buffer[pos++];} 
#define GETDW(a) {if(pos<readed_bytes-4) {a=buffer[pos++]<<24;a+=buffer[pos++]<<16;a+=buffer[pos++]<<8;a+=buffer[pos++];} else break;};
#define GETW(a) do {if(pos<readed_bytes-2){ a=buffer[pos++]<<8;a+=buffer[pos++];}else break;} while(0)
#define SKIPtemp(a) do{pos+=a;}while(0)
#define SKIPC() do{pos++;}while(0)
#define INSCtemp(a) do {if(pos<readed_bytes);a=(a<<8)+(buffer[pos++]);} while(0)

#define SKIP(a) pos+=a;
#define INSC(a) {if(pos<readed_bytes-1) {a=(a<<8)+buffer[pos++];} else break;};

	unsigned char *buffer=malloc(MAX_READING_BYTES);
	int pos=0;
	int found_a=0;
	int found_v=0;
	int try=0;
	int readed_bytes=0;
	unsigned int sync=MPEG_ISO_11172_END_CODE;
	int c;
	int size=0;
	int size2=0;
	int temp=0;
	int common_bitrate=0;
	unsigned int vids_n=0;
	unsigned int auds_n=0;
	vids_t vids[MAX_STREAMS];
	auds_t auds[MAX_STREAMS];
/*	int mp3_mpeg_layer_ver=0;*/
	int mpeg2=0;
	for (c=0;c<MAX_STREAMS;c++){ vids[c].exist=0; auds[c].exist=0;}
	while(try<MAX_TRYS&&!(found_a&&found_v)){
		readed_bytes=fread(buffer,1,MAX_READING_BYTES,file);
		try++;
		pos=0;
		if(!readed_bytes) break;/*no data to parse*/
		_GETDW(sync);
		while(pos<readed_bytes){
#ifdef MPEG_DEBUG
printf ("Get a %x DWORD at %x\n",sync,pos-4);
#endif
			if(sync==MPEG_ISO_11172_END_CODE){
#ifdef MPEG_DEBUG
printf ("got a EoF at 0x%x\n",pos-4);
#endif
				break;
			}
			if(sync==MPEG_PACK_HEADER){/*skip pack header*/
#ifdef MPEG_DEBUG
printf ("got a PACK_HEADER at 0x%x\n",pos-4);
#endif
				GETC(temp);
				if((temp&0xF0)==0x20) mpeg2=0;
				if((temp&0xC0)==0x40) mpeg2=1;
				if(mpeg2){
					SKIP(8);
					GETC(size);
					SKIP(size&3);
				}else SKIP(6);
				GETDW(sync);
				continue;
			}
			if(sync==MPEG_SYSTEM_HEADER){
#ifdef MPEG_DEBUG
printf ("got a SYSTEM_HEADER at 0x%x\n",pos-4);
#endif
				GETW(size);
				if(size>0) SKIP(size);
				GETDW(sync);
				continue;
			}
			if ((sync&0xFFFFFC0)==0x0001C0){/* audio or video PES header*/
#ifdef MPEG_DEBUG
printf ("got a a/v header at 0x%x, 0x%x\n",pos-4,sync);
#endif
				GETW(size); /*PES packet length*/
				if(!mpeg2){
					size2=0;
					do{ GETC(temp); size2++;}while (temp==0xFF);
					if((temp&0xC0)==0x40) {SKIP(1);GETC(temp);size2+=2;}
					if(temp&0x20) SKIP(4);size2+=4;
					if(temp&0x10) SKIP(5);size2+=5;
				}else{/*if mpeg2*/
					SKIP(2);		
					GETC(size2); 
					SKIP(size2);
					size2+=3;
				}
				GETDW(temp); 
				if(sync&0x20){ /*video*/
					vids_n=sync&0xF;
#ifdef MPEG_DEBUG
printf("found video #%d, signature=0x%x\n",sync&0xF,temp);
#endif
					found_v=1;
					if(vids_n>MAX_STREAMS) {free(buffer);return 0;}
					if( temp==MPEG_PICTURE_SEQUENCE){
						if(pos>MAX_READING_BYTES-12) break;
						vids[vids_n].exist=1;
						vids[vids_n].exist=1;
						vids[vids_n].x=(buffer[pos++]<<4);
						vids[vids_n].y=((buffer[pos++]&0xF)<<8);
						vids[vids_n].y+=(buffer[pos++]);
						vids[vids_n].aspect=(buffer[pos]&0xF0)>>4;
						vids[vids_n].fps=(buffer[pos++]&0x0F);
						vids[vids_n].bitrate=(buffer[pos++]<<10);
						vids[vids_n].bitrate+=(buffer[pos++]<<2);
						vids[vids_n].bitrate+=(buffer[pos++]&0xC0);
						vids[vids_n].bitrate*=400;
						common_bitrate+=vids[vids_n].bitrate;
					}
				}else {
					auds_n=sync&0x1F;
#ifdef MPEG_DEBUG
printf("found audio #%d\n",sync&0x1F);
#endif
					found_a=1;
					if(auds_n>MAX_STREAMS) {break;}
					if((temp&0xFFF00000)==0xFFF00000){
						if(GetMP3FrameData(temp,&auds[auds_n].bitrate,&auds[auds_n].freq,&auds[auds_n].ch)){
							auds[auds_n].exist=1;
							common_bitrate+=auds[auds_n].bitrate;
						}
					}
				}
				if(size-size2-4>0) SKIP(size-size2-4);
				GETDW(sync);
				continue;
			}
			if((sync&0xFFFFFF00)==0x100){		/*skip all others header*/
				GETW(size);
				if(size>0) SKIP(size);		
				GETDW(sync);
				continue;
			}
			INSC(sync);
		}
	}
	size=GetNumericVar(list,"size");
	temp=(int)((double)size*8/(double)(common_bitrate?common_bitrate:0xFFFFFFFF));
	for(c=0;c<MAX_STREAMS;c++){
		if(auds[c].exist){ /*TODO replace with AddAudioVideo*/
			IncStreamCounter(list,'a');
			SetIdxNumericVar(list,"a%d.freq",c+1,auds[c].freq);
			SetIdxNumericVar(list,"a%d.bps",c+1,auds[c].bitrate);
			SetIdxNumericVar(list,"a%d.ch",c+1,auds[c].ch);
			SetIdxNumericVar(list,"a%d.l",c+1,temp);
		}
		if(vids[c].exist){
			IncStreamCounter(list,'v');
			SetIdxNumericVar(list,"v%d.x",c+1,vids[c].x);
			SetIdxNumericVar(list,"v%d.y",c+1,vids[c].y);
			SetIdxNumericVar(list,"v%d.bps",c+1,vids[c].bitrate);
			SetIdxNumericVar(list,"v%d.fpsH",c+1,fps_table[vids[c].fps][0]);
			SetIdxNumericVar(list,"v%d.fpsL",c+1,fps_table[vids[c].fps][1]);
			SetIdxNumericVar(list,"v%d.aspectY",c+1,aspect_table[vids[c].aspect][0]);
			SetIdxNumericVar(list,"v%d.aspectX",c+1,aspect_table[vids[c].aspect][1]);
			SetIdxNumericVar(list,"v%d.l",c+1,temp);
			SetIdxNumericVar(list,"v%d.cc",c+1,mpeg2?0x3247504D:0x3147504D);
		}
	}
	free(buffer);
	return 1;
}
void GetId3v1(vlist_t* list,FILE* file){
	char buffer[129];
	fseek(file,-128,SEEK_END);
	if(ftell(file)<400) return;
	if(!fread(buffer,128,1,file)) return;
	if(buffer[0]!='T'||buffer[1]!='A'||buffer[2]!='G') return;
	buffer[128]=0;
	IncStreamCounter(list,'d');
	SetStringVar(list,"d11.name","title");	
	SetStringVar(list,"d11.value",buffer+3);
	SetStringVar(list,"d12.name","artist");
	SetStringVar(list,"d12.value",buffer+33);
	SetStringVar(list,"d13.name","album");
	SetStringVar(list,"d13.value",buffer+63);
	buffer[97]=0;
	SetStringVar(list,"d14.name","year");
	SetStringVar(list,"d14.value",buffer+93);
	SetNumericVar(list,"d1.num",4);
}

int mp3parse (vlist_t*list,FILE* file , int flags){
	unsigned char* buffer=malloc(MAX_READING_BYTES);
	int pos=0;
	int readed_bytes=0;
	int scan=0;
	int temp=0;
	int bitrate=0;
	int freq=0;
	int frames=0;
	int current_bitrate=0;
	int vbr_flag=0;
	int ch;
	int size;
	readed_bytes=fread(buffer,1,MAX_READING_BYTES,file);
	if(!readed_bytes) {free(buffer);return 0;}
	while(pos<readed_bytes){
		GETDW(scan);
		while((scan&0xFFF00000)!=0xFFF00000) INSC(scan); /*search for instance*/
		if ((scan&0xFFF00000)==0xFFF00000){
			temp=GetMP3FrameData(scan,&current_bitrate,&freq,&ch);
			if(temp<=0) continue;
			frames++;
			bitrate+=current_bitrate;
			if(current_bitrate*frames!=bitrate) vbr_flag=1;
			SKIP(temp);
		}
	}
	if(!frames){free(buffer);return 0;}
	IncStreamCounter(list,'a');
	SetNumericVar(list,"a1.freq",freq);
	SetNumericVar(list,"a1.bps",bitrate/frames);
	if(vbr_flag) SetNumericVar(list,"a1.vbr",1);
	SetNumericVar(list,"a1.ch",ch);
	size=GetNumericVar(list,"size");
	if(size&&bitrate) SetNumericVar(list,"a1.l",size/(bitrate/frames/8));
	/*if*/
	if(buffer) free(buffer);
	if(!flags)GetId3v1(list,file); /*TODO!!!*/
	return 1;
}

