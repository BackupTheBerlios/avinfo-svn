/*************************************************************************
 * ifo.c - DVD's *.ifo reading code [part of AVInfo 1.x]
 * * format information taked from http://dvd.sf.net/ (domou arigatou)
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

 /* use a tabulation size 4 spaces for normal editig*/

 /*note: this is a test version, due lack of information about DVD*/

#include "ifo.h"

const char VTS_SIGNATURE[12]="DVDVIDEO-VTS";
const unsigned short int X_table[4][2]={ {720,720}, {704,704}, {352,352}, {352,352} };
const unsigned short int Y_table[4][2]={ {480,576}, {480,576}, {480,576}, {240,288} };
const unsigned int Codec_table[8]={ FCC_AC3, 0, FCC_MPG1, FCC_MPG2, FCC_LPCM, 0, FCC_DTS, 0};

int ifoparse(vlist_t*list,FILE* file, int s){ /*supported only a vts_xx_0.ifo, video_ts.ifo is not needed for AVInfo*/
    char buffer[0x316];
	unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE];
	unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE];
	unsigned int type=0;
	unsigned int a_c=0;
	unsigned int s_c=0;
	unsigned int audio_streams=0;
	unsigned int subtitle_streams=0;
	char *lang;
	memset(video,0,sizeof(video));
	memset(audio,0,sizeof(audio));
	if(!fread(buffer,0x316,1,file)) return 0; /*if we can not read at least 790 bytes we can not recognize IFO file information*/
    if(memcmp(buffer,VTS_SIGNATURE,sizeof(VTS_SIGNATURE))) return 0; /*non VTS IFO or not the IFO*/
/*video (always 1 stream)*/    
    video[0][V_exist]=1;
	switch(buffer[0x200]&0xC){
		case 0:
			video[0][V_cc]=FCC_MPG1;
			break;
		case 0x40:
			video[0][V_cc]=FCC_MPG2;
			break;
	}
	type=(buffer[0x200]&0x10)>>4;
	SetStringVar(list,"v1.type",type?"PAL":"NTSC");
	switch(buffer[0x200]&0xC){
		case 0: 
			video[0][V_aspectX]=4;
			video[0][V_aspectY]=3;
			break;
		case 0xC:
			video[0][V_aspectX]=16;
			video[0][V_aspectY]=9;
			break;	
	}
	if(buffer[0x201]&0x20) return 0; /*should not be a 1*/
	video[0][V_x]=X_table[(buffer[0x201]&0x18)>>3][type];
	video[0][V_y]=Y_table[(buffer[0x201]&0x18)>>3][type];


/*audio (max 8 streams)*/
	audio_streams=buffer[0x203];
	if(audio_streams>8) audio_streams=8;
	for(a_c=0;a_c<audio_streams;a_c++){
/*		base=104+a_c*8;*/
		audio[a_c][A_exist]=1;
		audio[a_c][A_cc]=Codec_table[(buffer[0x204+a_c*8]&0xE0)>>5];
		if(!(buffer[0x205+a_c*8]&0x30)) audio[a_c][A_freq]=48000;
		lang=malloc(3);
		audio[a_c][A_ch]=(buffer[0x20B+a_c*7]&0x70)>>4;
		lang[0]=buffer[0x206+a_c*8];
		lang[1]=buffer[0x207+a_c*8];
		lang[2]=0;
		SetIdxStringVar(list,"a%d.lang",a_c+1,lang);
		/*todo chanels*/		
	}


/*subtitle (max 32 streams, but AVInfo supports only first 9) */
	subtitle_streams=buffer[0x254];
	if(subtitle_streams>9) subtitle_streams=9;
	SetNumericVar(list,"stream.t",subtitle_streams);
	for(s_c=0;s_c<subtitle_streams;s_c++){
		lang=malloc(3);
		lang[0]=buffer[0x258+s_c*6];
		lang[1]=buffer[0x257+s_c*6];
		lang[2]=0;
		SetIdxStringVar(list,"t%d.lang",s_c+1,lang);
	}
	AddAudioVideo(list,video,audio);
	return 1;
}
