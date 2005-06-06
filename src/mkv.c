/*************************************************************************
 * mkv.c - Matroska reading code [part of AVInfo 1.x]
 * data format from 
 * http://matroska.org/
 *
 * Copyright (c) 2004 George Shuklin
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
#include "mkv.h"
#include "memleak.h"
#define BUFFER_SIZE 0x4000
#define MAX_STRING_SIZE 1024

int VINTparse(const char* buffer, const int start, const int end, int64 *result,const int flag){
/*конвертирует из VINT (по указанному смещению) в int64, возвращает размер (сдвиг), flag=0 - elementID, 1 - size*/
    unsigned const char mask[8]={0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
    unsigned const char imask[8]={0x7F,0x3F,0x1F,0xF,0x7,0x3,0x1,00};
	int VINT_WIDTH;	
	int c;
	if(end-start<2) {return 0; /*ops*/}
	VINT_WIDTH=0;
    for(c=0;c<8;c++) 
    	if( !(buffer[start]&mask[c]) ) VINT_WIDTH++; 
    	else break;
    if(VINT_WIDTH>=8 || VINT_WIDTH+start+1>=end) {return 0;}
	*result=0;
    for(c=0;c<VINT_WIDTH;c++)
    	*result+=buffer[start+VINT_WIDTH-c]<<(c*8);
    if(flag)
    	 *result+=(buffer[start]&imask[VINT_WIDTH])<<(VINT_WIDTH*8);
    else *result+=(buffer[start])<<(VINT_WIDTH*8);
	return VINT_WIDTH+1;
}

int ElementRead(const char* buffer, const int start, const int end, unsigned int* ID, int64* size){
	int64 tempID;
	int64 tempsize;
	int ID_offset,size_offset;
	ID_offset=VINTparse(buffer,start,end,&tempID,0);
	if(!ID_offset) return 0;
	size_offset=VINTparse(buffer,start+ID_offset,end,&tempsize,1);
	if(!size_offset) return 0;
	*ID=(int)tempID; /*id must be <4 and must to feet in uint*/
	*size=tempsize;
	return ID_offset+size_offset;
}

int64  GetInt(const char* buffer,const int start, const int size){
/*return a int [8-64], from buffer, Big Endian*/
	int64 result=0;
	int c;
	for(c=1;c<=size;c++){
		result+=buffer[start+c-1]<<(8*(size-c));
	}
	return result;
}

float GetFloat(const char* buffer, const int start, const int size){
	float result=0;
	char tmp[4];
	if(size==sizeof(float)) {
		tmp[0]=buffer[start+3];
		tmp[1]=buffer[start+2];
		tmp[2]=buffer[start+1];
		tmp[3]=buffer[start];
		result=*((float*)(tmp));
	}
	return result;
}

const unsigned int MKV_Parse_list[]={/*Elements, containing requed information (sub-elements), see enum in mkv.h for values*/
	MKVID_Segment,
	MKVID_Info,
	MKVID_Video,
	MKVID_Audio,
	MKVID_TrackEntry,
	MKVID_Tracks
};

const char stream_type_letters[]="?vat";/*[0]-no, [1]-video,[2]-audio,[3]-text*/

int mkvparse(vlist_t *list,FILE* file, int s){

	char* buffer=malloc(BUFFER_SIZE+128);
	unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE]; 
	unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE];
	char* lang[MAX_STREAMS][4];/*1 - video, 2 - audio, 3 - text, 0 unused*/
	char* codec[MAX_STREAMS][4];/*1 - video, 2 - audio, 3 - text, 0 unused*/
	int p; /*pointer in buffer*/
	int c,c2; /*counter in some loops*/
	int readed_bytes;
	unsigned int eID; /*element ID*/
	int64 eSize; /*Size of element content*/
   	int offs;
	char* title=NULL;
	int64 timescale=1000000;
	float Duration=0;
	char* tstr1, *tstr2; /*temp strings*/
	int64 DefaultDuration=0;
	int TrackType=0;
	int pvt_look_flag=0;
	int curr_c=-1;
	int a_c=-1;
	int v_c=-1;
	int t_c=-1;
	int value=0;

	if(!buffer) return 0;
	memset(video,0,sizeof(video));
	memset(audio,0,sizeof(audio));
	memset(lang,0,sizeof(lang));
	memset(codec,0,sizeof(codec));

	readed_bytes=fread(buffer,1,BUFFER_SIZE,file); /*todo buffer_size,1 ? */
	if(!readed_bytes){free(buffer);return 0;}
	p=0;
	while(buffer[p]!=MKVID_FILE_BEGIN){
		p++;
		if(p>=readed_bytes){
			free(buffer);
			return 0;
		}
	}; /*skip text while EBML begin*/

/*main loop*/	
	do{
		offs=ElementRead(buffer,p,readed_bytes,&eID,&eSize);
        p+=offs;
		if(!offs||p>=readed_bytes) break;
		for(c=0;c<sizeof(MKV_Parse_list)/sizeof(*MKV_Parse_list);c++)
			if(MKV_Parse_list[c]==eID) {
				break;
		    }
		if(c<sizeof(MKV_Parse_list)/sizeof(*MKV_Parse_list)) continue;
		if(p+eSize>readed_bytes) break; /*TODO - add (if requied) suckup from file to buffer*/
		if(eSize==4||eSize==8||eSize==1||eSize==2)
			value=(int)GetInt(buffer,p,eSize);
		switch(eID){
			case MKVID_TrackType: /*detect a stream type (video/audio/text)*/
				TrackType=value;
				pvt_look_flag=0;
				switch(TrackType){
					case MKV_Track_video: 
						v_c++;
						if(v_c>MAX_STREAMS) v_c=MAX_STREAMS;
						video[v_c][V_exist]=1;
						video[v_c][V_l]=(int)(Duration/1e+9*(float)timescale);
						curr_c=v_c;
						break;
					case MKV_Track_audio: 
					    a_c++;
					    if(a_c>MAX_STREAMS) a_c=MAX_STREAMS;
					    audio[a_c][A_exist]=1;
						audio[a_c][A_l]=(int)(Duration/1e+9*(float)timescale);
						curr_c=a_c;
					    break;
					case MKV_Track_subtitle_orig: 
					    t_c++;
					    TrackType=MKV_Track_subtitle; /*for normal use in lang array*/
					    if(t_c>MAX_STREAMS) t_c=MAX_STREAMS;
					    curr_c=t_c;
						break;
				}
				break;
			case MKVID_DefaultDuration: /*fps detection*/
				if(TrackType==MKV_Track_video&&v_c>=0){
						DefaultDuration=value;
						if(DefaultDuration>100){
							video[v_c][V_fpsH]=1000000000/DefaultDuration; /*DD in nano sec. fps=1s/DD*/
							video[v_c][V_fpsL]=1000000000/(DefaultDuration/100)-100*video[v_c][V_fpsH];
						}
				}
				break;
			case MKVID_Language: /*stream language*/
				if(curr_c>=0&&TrackType<4&&eSize<MAX_STRING_SIZE)
					if(lang[curr_c][TrackType]) free(lang[curr_c][TrackType]);
					lang[curr_c][TrackType]=mkstr(buffer,p,eSize);
				break;
			case MKVID_CodecName:/*passtrough*/
			case MKVID_CodecID: /*codec detection (if V_MS/VFW/FOURCC - set a fourcc code, else fill a vcodecs value)*/				
				if(curr_c>=0&&TrackType<4&&eSize<MAX_STRING_SIZE){
					if(codec[curr_c][TrackType]) free(codec[curr_c][TrackType]);
					codec[curr_c][TrackType]=mkstr(buffer,p,eSize);
					if(!strcmp(codec[curr_c][TrackType],"V_MS/VFW/FOURCC")) pvt_look_flag=1;
				}
				break;
			case MKVID_CodecPrivate:
				if(pvt_look_flag&&v_c>=0&&eSize>=24){ /*CodecPrivate contains a BITMAPINFOHEADER structure due CodecID==V_MS/VFW/FOURCC*/
					pvt_look_flag=0;
					video[v_c][V_cc]=(buffer[p+16]<<24)+(buffer[p+17]<<16)+(buffer[p+18]<<8)+buffer[p+19];
					if(codec[v_c][MKV_Track_video]){
						free(codec[v_c][MKV_Track_video]);
						codec[v_c][MKV_Track_video]=NULL;
					}
				}
				break; 
			case MKVID_PixelWidth: /*pasthough*/ /*bug with aspect differ from 1:1*/
			case MKVID_DisplayWidth:
				if(v_c>=0)video[v_c][V_x]=value;
				break;
			case MKVID_PixelHeight: /*pasthough*/
			case MKVID_DisplayHeight:
				if(v_c>=0)video[v_c][V_y]=value;
				break;
			case MKVID_TimeCodeScale: 
				timescale=GetInt(buffer,p,eSize);
				break;
			case MKVID_Duration: 
				Duration=GetFloat(buffer,p,eSize);
				break;
			case MKVID_Channels:
				if(a_c>=0)audio[a_c][A_ch]=value;
				break;
			case MKVID_BitDepth:
				if(a_c>=0)audio[a_c][A_bits]=value;
				break;
			case MKVID_OutputSamplingFrequency: /*pasthough*/
			case MKVID_SamplingFrequency:
				if(a_c>=0) audio[a_c][A_freq]=(int)GetFloat(buffer,p,eSize);
				break;
			case MKVID_Title: 	
				if(eSize>MAX_STRING_SIZE) break;
				title=mkstr(buffer,p,eSize);
				SetNumericVar(list,"stream.d",1);
				SetNumericVar(list,"d1.num",1);
				SetStringVar(list,"d11.name","Title");
				SetStringVar(list,"d11.value",title);
				free(title);
				break;
/*TODO			case MKVID_Tags:*/ 
		}
		p+=eSize;/*skip unknown or uninteresting*/
	}while(1);
	AddAudioVideo(list,video,audio);
	tstr1=strdup("d?.lang");
	tstr2=strdup("d?.cc");
	if(tstr1&&tstr2){
		for(c=0;c<MAX_STREAMS;c++){
			for(c2=0;c2<4;c2++){
				tstr1[0]=stream_type_letters[c2];
				tstr1[1]=c+'0'+1;
				tstr2[1]=tstr1[1];
				tstr2[0]=tstr1[0];
				if(lang[c][c2]){
					SetStringVar(list,tstr1,lang[c][c2]);
					free(lang[c][c2]);
				}
				if(codec[c][c2]){
					SetStringVar(list,tstr2,codec[c][c2]);
					free(codec[c][c2]);
				}
			}
		}
		SetNumericVar(list,"stream.t",t_c+1);
		free(tstr1);
		free(tstr2);
	}
	if(buffer) free(buffer);
	return 1;
}
