/*************************************************************************
 * riff.c AVI headers reading code [part of AVInfo 1.x]
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
 *     patch by Cyrille Lefevre in description reading (2005-05-27, 1.0a16)
 *
 *************************************************************************/
#include "riff.h"
#include "memleak.h"
#define MAX_ALLOWED_AVI_HEADER_SIZE 131072
#define SAFE_PAD 128
#define FRAME_SIZE 65536 /*for index*/
 
#define b2DW(value,buffer,offset) value=buffer[offset]+(buffer[offset+1]<<8)+(buffer[offset+2]<<16)+(buffer[offset+3]<<24);
#define b2DWv(buffer,offset) buffer[offset]+(buffer[offset+1]<<8)+(buffer[offset+2]<<16)+(buffer[offset+3]<<24)
#define b2Wv(buffer,offset) buffer[offset]+(buffer[offset+1]<<8)
#define b2DWi(value,buffer,offset) {value=buffer[offset++];value+=buffer[offset++]<<8;value+=buffer[offset++]<<16;value+=buffer[offset++]<<24;}
#define INSb(value,buffer,offset) {value=((value>>8)+((buffer[offset++])<<24));}


const char* patterns[]={
"LIST\0\0\0\0hdrl",
"LIST\0\0\0\0INFO",
"LIST\0\0\0\0movi",
"idx1\0\0\0\0\0\0\0\0"
};

const char* avi_signature="RIFF\0\0\0\0AVI ";

int riffparse(vlist_t* list, FILE* file, int s){
	char scan[12];
	unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE];
	unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE];
	char *buffer=NULL;
	unsigned int pos;
	char error_status=1; /*critical error flag*/
	int c;
	unsigned int size;
	unsigned int movi_size=0;
	unsigned int fcc=0;
	unsigned int a_c=0;
	unsigned int v_c=0;
	unsigned int type=0;
	unsigned int scale=0;
	unsigned int rate=0;
	unsigned int length=0;
	unsigned int cont=1;
	double fps=0;


	unsigned int frame_size=0;
	unsigned int readed_bytes=0;
	unsigned int temp=0;
	unsigned int bps[MAX_STREAMS][3];
	unsigned int common_data=0;
	unsigned int entr=0;/*todel!*/

	char *desc_name=NULL;
	char* desc_value=NULL;
	unsigned int desc_size=0;
	unsigned int d_c=0;

	memset(video,0,sizeof(video));
	memset(audio,0,sizeof(audio));
	memset(bps,0,sizeof(bps));

	if(!fread(scan,12,1,file)) return 0;
	if(advmemcmp(scan, avi_signature,12)) return 0; /*non avi file*/
	while(cont){

		if(!fread(scan,12,1,file)){cont=0;continue;}
		b2DW(size,scan,4);
		if(size<4) size=4;
		for(c=0;c<4;c++) 
			if(!advmemcmp(scan,patterns[c],12)) break;
		switch(c){
			case 0:				/*header reading*/
				if(size>MAX_ALLOWED_AVI_HEADER_SIZE) return 0; /*header too big*/
				assert(buffer=malloc(size+SAFE_PAD-4));
				memset(buffer+size-4,SAFE_PAD-4,0);
				if(!fread(buffer,size-4,1,file)) 
					goto riff_loop_end;
				pos=76;
				b2DWi(fcc,buffer,pos);
				while(pos<size){
					switch(fcc) {
						case FCC_strh:
							b2DW(type,buffer,pos+4);
							b2DW(scale,buffer,pos+24);
							b2DW(rate,buffer,pos+28);
							b2DW(length,buffer,pos+36);
							fps=(double)rate/(double)(scale?scale:0x7FFFFFFF); /*change 7f...f to 0?*/
							length=(int)(length/fps);
							pos+=60;
							fcc=0;
							break;
						case FCC_strf:
							switch(type){
								case FCC_vids:
									error_status=0;
									video[v_c][V_x]=b2DWv(buffer,pos+8);
									video[v_c][V_y]=b2DWv(buffer,pos+12);
									video[v_c][V_cc]=b2DWv(buffer,pos+20);
									video[v_c][V_fpsH]=(int)fps;
									video[v_c][V_fpsL]=(int)(((double)fps-(int)fps)*100);
									video[v_c][V_l]=length;
									video[v_c][V_exist]=1;
									pos+=40;
									v_c++;
									if(v_c>=MAX_STREAMS)v_c=MAX_STREAMS-1;
									break;
								case FCC_auds:
									audio[a_c][A_cc]=b2Wv(buffer,pos+4);
									audio[a_c][A_ch]=b2Wv(buffer,pos+6);
									audio[a_c][A_freq]=b2DWv(buffer,pos+8);
									audio[a_c][A_bits]=b2Wv(buffer,pos+18);
									audio[a_c][A_exist]=1;
									audio[a_c][A_l]=length;
									pos+=22;
									error_status=0;
									a_c++;
									if(a_c>=MAX_STREAMS)a_c=MAX_STREAMS-1;
									break;
							}
							fcc=0;
							break;
					}
					INSb(fcc,buffer,pos);
				}
				if(buffer) free(buffer);
				buffer=NULL;
				continue;
			case 1:	/*INFO reading*/
				if(size>MAX_ALLOWED_AVI_HEADER_SIZE){
					fseek(file,size-4,SEEK_CUR);
					continue;
				}
				if(size<16) continue;
				buffer=malloc(size);
				if(!buffer) continue;
				if(!fread(buffer,size-4,1,file))
					{if(buffer)free(buffer);buffer=NULL;continue;}
				pos=0;
				while(pos<size){
					if(!buffer[pos] || buffer[pos] != 'I'){ /*search for desc. begin*/
						pos++;
						continue;
					}
					b2DW(desc_size,buffer,pos+4);
					if(desc_size>size-pos) desc_size=size-pos-1;
					desc_value=malloc(desc_size+1);
					desc_name=malloc(5);
					if(!desc_value||!desc_name) break;
					memcpy(desc_value,buffer+pos+8,desc_size);
					memcpy(desc_name,buffer+pos,4);
					desc_name[4]=0;
					desc_value[desc_size]=0;
					if(strcmp(desc_name,"ISFT")){/*skip 'Software' entry */
						d_c++;
						SetIdxStringVar(list,"d1%d.name",d_c,desc_name);
						SetIdxStringVar(list,"d1%d.value",d_c,desc_value);
					}
					pos+=8+desc_size;
					free(desc_name);
					free(desc_value);
				}
				if(d_c){
					SetNumericVar(list,"d1.num",d_c);
					SetNumericVar(list,"stream.d",1);
				}
				if(buffer)free(buffer);
				buffer=NULL;
				continue;
			case 2:				/*movi skip*/
				movi_size=size;
				break;
			case 3:			/*idx1 processing*/
				if(size<FRAME_SIZE) frame_size=size; else frame_size=FRAME_SIZE;
				buffer=malloc(frame_size);
				if(!buffer) return !error_status; /*if we do not read index this do not mean an error ... we can success in some cases*/
				pos=0;
				memcpy(buffer,scan+8,4);
				if(!fread(buffer+4,frame_size-4,1,file)) readed_bytes=size; /*just skip bps calculation*/
				while(readed_bytes+pos<((s&0x2)?size:131072)){
					if(pos+16>frame_size){
						readed_bytes+=pos;
						if(size-readed_bytes-pos<frame_size&&size-readed_bytes-pos) frame_size=size-readed_bytes-pos;
						temp=fread(buffer,1,frame_size,file);
						if(temp!=frame_size) break; /*broken index*/
						pos=0;
						continue;
					}
					temp=buffer[pos+1]-'0';
					if(buffer[pos]!='0'||temp>'9') {pos+=16;continue; /*skip invalid*/}
					if(buffer[pos+2]=='d'||buffer[pos+2]=='w'){
						bps[temp][0]=buffer[pos+2];
						bps[temp][1]++;
						bps[temp][2]+=b2DWv(buffer,pos+12);
					}
					if(!(buffer[pos+4]&0x1)||!(buffer[pos+5]&0x1)) common_data+=b2DWv(buffer,pos+12)+8; /*summ data ,'rec' list, non timing frames ignoring, */
					entr++;
					pos+=16;
				}
				a_c=0;
				v_c=0;

				for(temp=0;temp<MAX_STREAMS;temp++){
					switch(bps[temp][0]){
						case 'd':
							video[v_c][V_bps]=(int)((double)bps[temp][2]*(double)movi_size/(double)common_data)/(video[v_c][V_l]?video[v_c][V_l]:0xFFFFFFFF)*8; /*UNSAFE! REDO!!!!*/
							v_c++;
							break;
						case 'w':
							audio[a_c][A_bps]=(int)((double)bps[temp][2]*(double)movi_size/(double)common_data)/(audio[a_c][A_l]?audio[a_c][A_l]:0xFFFFFFFF)*8;
							a_c++;
							break;
					}
				}
				cont=0;
				break;
				if(buffer) free(buffer);
				buffer=NULL;
			case 4: 
		}
		if(ftell(file)&0x1){/* note - if entry not aligied to word, try again, (offset+1), needs for some soft, like AviUtl.*/
			fseek(file,-3,SEEK_CUR);
		}
        else fseek(file,size-4,SEEK_CUR);
	}
	riff_loop_end:
	if(buffer) free(buffer);
	buffer=NULL;
	if(error_status) return 0;
	AddAudioVideo(list,video, audio);
	return 1;
}
