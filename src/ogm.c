/*************************************************************************
 * ogm.c - OGG media reading code [part of AVInfo 1.x]
 * format information from 
 * http://xiph.org/ and http://tobias.everwicked.com/
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
#include "ogm.h"

#define DEFAULT_PARSE_BLOCK 32768

#define CharsToInt32(table,offset)  (table[offset]+(table[offset+1]<<8)+(table[offset+2]<<16)+(table[offset+3]<<24))
#define CharsToInt64H(table,offset) (CharsToInt32(table,offset+4))
#define CharsToInt64L(table,offset) (CharsToInt32(table,offset))

#define EoS_FLAG 0x4

typedef struct{
	char* name;
	char* value;
}comment_t;

comment_t CommentSplit(char*CommentVector, int CommentSize){
    comment_t ret_val;
    int c;
    ret_val.name=NULL;
	if(CommentSize>1){
		for(c=1;c<CommentSize-1;c++){ /* char '=' in fist and last position useless, ignore*/
			if(CommentVector[c] == '='){
				ret_val.name=malloc(c+1);
				memcpy(ret_val.name,CommentVector,c);
				ret_val.name[c]=0;
				ret_val.value=malloc(CommentSize-c+1);
				memcpy(ret_val.value,CommentVector+c+1,CommentSize-c-1);
				ret_val.value[CommentSize-c-1]=0;
			}
		}
	
	}
	if(!ret_val.name){
		ret_val.name=calloc(1,1);
		ret_val.value=calloc(1,1);
	}
	return ret_val;
}

typedef struct{
	char type; /* 'a' for audio, 'v' for video, 0 for 'no stream'*/
	char header; /*1 of header parsed*/
	char desc; /*1 of description parsed*/
	int num; /*number of stream (in audio|video|text array)*/
}str_data;

const char OggS_signature[5]={0x4f, 0x67, 0x67, 0x53, 0};

const char stream_signatures[4][8]={
	{'v', 'i', 'd', 'e', 'o',  0,  0,  0},
	{'v', 'o', 'r', 'b', 'i', 's', 0,  0},
	{'a', 'u', 'd', 'i', 'o',  0,  0,  0},
	{'t', 'e', 'x', 't',  0,   0,  0,  0}
};

int ogmparse(vlist_t* list,FILE* file, int s){
	char *buffer=malloc(DEFAULT_PARSE_BLOCK*4);
	unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE]; /*temporal storage for found data*/
	unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE];
	int a_c=0; /*counter for found audio streams (include vorbis)*/
	int v_c=0; /*video counter*/
	int t_c=0;
	int d_c=0;
    int readed_bytes=0;
	int base=0; /*offset of current page in buffer*/
	int baseD=0; /*offset of data of current page in buffer*/
	int page_data_size=0;/*size of data of current page*/
	int comm_num;/*number of comments*/
	int comment_base; /*offset of comments block*/
    int comment_offset;/*offset of current comment (pointer to 4bytes field size)*/
    int comment_size;/*size of current comment*/

    char tempbuff[255];/*temp. buffer for string op.*/
    comment_t comment;/*keep converted from vector to string current comment*/
	int c;
	unsigned int common_audio_data_size=0; /*using for video bitrate calc.*/

	str_data streams[61];
	unsigned int curr_stream_num=0;
	int cont=1;
	unsigned int absolute_granue_position=0; /*used for stream length calculation*/
	
	if(!buffer) return 0;

	memset(video,0,sizeof(video));
	memset(audio,0,sizeof(audio));
	memset(streams,0,sizeof(streams));

	/*header scan*/
	readed_bytes=fread(buffer,1,DEFAULT_PARSE_BLOCK,file);
	if(readed_bytes<0x1B) {free(buffer);return 0;}
	while( cont && base+0x1B<readed_bytes){
   		if(memcmp(buffer+base,OggS_signature,5)) {base++;continue;}
		if(!buffer[base+0x1A]){buffer+=0x1B;continue;}/*skip empty page*/
		page_data_size=0;
		for(c=0;c<buffer[base+0x1A];c++) page_data_size+=buffer[base+0x1B+c];
		if(base+0x1B+page_data_size>=readed_bytes) break;
		baseD=base+0x1B+buffer[base+0x1A];
		curr_stream_num=CharsToInt32(buffer,base+0xE);
		if(curr_stream_num>63) curr_stream_num=60;
		switch(buffer[baseD]){
			case 1: /*header*/
			    if(page_data_size<8) break;
				for(c=0;c<4;c++) if (!memcmp(buffer+baseD+1,stream_signatures[c],8)) break; /*c: 0-video, 1 - vorbis, 2, - audio, 3 - text*/
				if(c>=4) break; /*unknown pack*/
				switch(c){ 
					case 0:/*video*/
						if(page_data_size<0x35) break; /*too small to be a video header*/
						streams[curr_stream_num].type='v';
						streams[curr_stream_num].num=v_c;
						video[v_c][V_exist]=1;
						video[v_c][V_cc]=CharsToInt32(buffer,baseD+0x9);
						video[v_c][V_fpsH]=10000000/CharsToInt32(buffer,baseD+0x11);
						video[v_c][V_fpsL]=1000000000/CharsToInt32(buffer,baseD+0x11)-video[v_c][V_fpsH]*100;
						video[v_c][V_bits]=CharsToInt32(buffer,baseD+0x29);
						video[v_c][V_x]=CharsToInt32(buffer,baseD+0x2D);
						video[v_c][V_y]=CharsToInt32(buffer,baseD+0x31);
						v_c++;
						break;
					case 1:/*vorbis*/
					    if(page_data_size<0x18) break; /*too small to be a vorbis header*/
						streams[curr_stream_num].type='a';
						streams[curr_stream_num].num=a_c;
						audio[a_c][A_exist]=1;
						audio[a_c][A_ch]=(unsigned int)buffer[baseD+0xB];
						audio[a_c][A_freq]=CharsToInt32(buffer,baseD+0xC);
						audio[a_c][A_bps]=CharsToInt32(buffer,baseD+0x14);
						if((signed int)audio[a_c][A_bps]<0) audio[a_c][A_bps]=0; /*to prevent bps=-1*/
						audio[a_c][A_cc]=CharsToInt32("OGG ",0);
						a_c++;
						break;
					case 2:/*audio*/
						/*not supported -TODO in next version*/
						break;
					case 3:/*text*/
						streams[curr_stream_num].type='t';
						streams[curr_stream_num].num=t_c;
						t_c++;
						break;
				}
				break;
			case 3: /*comment header*/
			    if (page_data_size<6) break; /*too small for any puporses*/
				if(memcmp(baseD+buffer+1,"vorbis",6)) break; /*non vorbis comments not supported*/
				comment_base=baseD+CharsToInt32(buffer,baseD+0x7)+11;/*skip vendor record*/
				if(comment_base+4>readed_bytes) break; /*oops*/
				comm_num=CharsToInt32(buffer,comment_base);
				if(!comm_num) break; /*if no real comments - skip*/
				comment_base+=4;/*move to real comments begin*/
				comment_offset=0;
				for(c=0;c<comm_num;c++){
					comment_size=CharsToInt32(buffer,comment_base+comment_offset);
				    if (comment_base+comment_size+comment_offset>readed_bytes) break;
					comment=CommentSplit(buffer+comment_base+comment_offset+4,comment_size);
					comment_offset+=4+comment_size;
					if(!strcmp((char*)comment.name,"LANGUAGE")){ /*process a LANGUAGE comment, make a long name short (e.g. JAPANESE -> jap)*/
						if(strlen((char*)comment.value)>3){
							comment.value[3]=0;
							lowcase(comment.value);
							sprintf((char*)tempbuff,"%c%d.lang",streams[curr_stream_num].type,streams[curr_stream_num].num+1);
							SetStringVar(list,tempbuff,comment.value);
							free(comment.name);
							free(comment.value);
							continue;
						}
					}
					if(strlen((char*)comment.name)>=7){/*ignore stupid descriptions from ogm navigation*/
					   	if(!memcmp(comment.name,"CHAPTER",7)) continue;
					   	if(!memcmp(comment.name,"LWING_GAIN",10)) continue;
					}
					d_c++;
					SetIdxStringVar(list,"d1%d.name",d_c,comment.name);
					SetIdxStringVar(list,"d1%d.value",d_c,comment.value);
					free(comment.name);
					free(comment.value);
				}
       			break;
		}
		base+=page_data_size+0x1B+buffer[base+0x1A];
	}
	if(!a_c&&!v_c&&!t_c) {free(buffer);return 0;} /*if nothing found - not count*/


	/*tail scan (for stream (a/v) length calculation)*/
	fseek(file,-DEFAULT_PARSE_BLOCK*3,SEEK_END); /*go to file end, get last 32k*3 block */
	readed_bytes=fread(buffer,1,DEFAULT_PARSE_BLOCK*3,file);
	if(readed_bytes<0x1B) goto skip;
	base=0;
	while( cont && base+0x1B<readed_bytes){
		if(memcmp(buffer+base,OggS_signature,5)){base++;continue;}/*seach nearest OggS signature*/
		if(!buffer[base+0x1A]){buffer+=0x1B;continue;}
		page_data_size=0;
		for(c=0;c<buffer[base+0x1A];c++) page_data_size+=buffer[base+0x1B+c];
		if(base+0x1B+page_data_size>readed_bytes) break;
		curr_stream_num=CharsToInt32(buffer,base+0xE);
		if(curr_stream_num>63) curr_stream_num=60;
		absolute_granue_position=CharsToInt32(buffer,base+0x6);
		if(buffer[base+0x5]&EoS_FLAG){ /*if current page is the LAST page in stream, a_g_p contain common number of frames/samples for stream*/
			switch(streams[curr_stream_num].type){
				case 'a':
					if(audio[streams[curr_stream_num].num][A_freq])audio[streams[curr_stream_num].num][A_l]=absolute_granue_position/audio[streams[curr_stream_num].num][A_freq];
					break;
				case 'v':
					if(video[streams[curr_stream_num].num][V_fpsH])video[streams[curr_stream_num].num][V_l]=absolute_granue_position*100/(video[streams[curr_stream_num].num][V_fpsH]*100+video[streams[curr_stream_num].num][V_fpsL]);
					break;
			}
		}
		base+=page_data_size+0x1B+buffer[base+0x1A];
	}


			/*experimental segment: try to fast calculate a video bitrate:
				video_bps=(filesize-summ(audio_bitrate[stream_num]*audio_length[stream_num])/video_length
				works only if single video stream and defined avg.bitrates for all audio streams.
			*/
			if(v_c>1||!video[0][V_l]) goto skip;
			for(c=0;c<a_c;c++){
				if(!audio[c][A_bps]||!audio[c][A_l]) goto skip;
				common_audio_data_size+=audio[c][A_bps]*audio[c][A_l]/8;
			}
			fseek(file,0,SEEK_END); /*redo?*/
			video[0][V_bps]=(ftell(file)-common_audio_data_size)/video[0][V_l]*8;


	skip:  /*label for terminating process of scan. Sorry, goto IMHO is the best in this case*/
	AddAudioVideo(list,video,audio);
	SetNumericVar(list,"stream.t",t_c);
	if(d_c){
		SetNumericVar(list,"stream.d",1);
		SetNumericVar(list,"d1.num",d_c);
	}
	free(buffer);
	return 1;
}
