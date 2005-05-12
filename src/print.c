/*************************************************************************
 * print.c - line caching and printing code [part of AVInfo 1.x]
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

#include "print.h"

#define DEFAULT_LINE_BUFFER_SIZE 4096
#define MAX_TAB_SUPPORT 64
#define MAX(a,b) a>b?a:b
#define SPACE ' '
#define MAX_ALLOWED_CACHED_LINE_SIZE   1048576

linecache* InitLineCache(FILE* handler, int max_size, int cropflag){
/*create a record for cache*/
    linecache *retval=malloc(sizeof(linecache));
	assert(retval);
	retval->handler=handler;
	assert(retval->line=malloc(MAX(DEFAULT_LINE_BUFFER_SIZE,max_size)));
	retval->allocated=MAX(DEFAULT_LINE_BUFFER_SIZE,max_size);
	retval->line[0]=0;
	retval->max_size=max_size;
	retval->last_pos=0;
	retval->cropflag=cropflag;
	return retval;
}

int ExpandTab(linecache* l){
/*convert tabs in cached line to 'justify' aligniment line.*/
	int tab[MAX_TAB_SUPPORT];
	int tab_c=0;
	int p;
	int pn=0;
	int pad_size;
	int last_pad_size;
	char *templine=0;
	int c;
	if(!l) return 0;
	if(!l->line) return 0;
	if(!l->last_pos) return 1;/*nothing to do*/
	if(!l->max_size) return 1;/*nothing to do*/
	if(l->max_size < l->last_pos ) {return 0;/*oops*/}
	memset(tab,0,sizeof(tab));
	for(p=0;p<l->last_pos;p++)	if(l->line[p]=='\t') tab[tab_c++]=p;
	if(!tab_c) return 1; /*nothing to do*/
	pad_size=(l->max_size-l->last_pos+tab_c)/tab_c;
	last_pad_size= l->max_size - l->last_pos + tab_c - pad_size*(tab_c-1);
	templine=malloc(l->max_size);
	if(!templine)return 0;/*big ooooops*/

	if(tab[0]) memcpy(templine,l->line,tab[0]);
	pn=tab[0];
	memset(templine+pn,SPACE,tab_c>1?pad_size:last_pad_size);
	pn+=tab_c>1?pad_size:last_pad_size;

	for(c=1;c<tab_c;c++){
		memcpy(templine+pn,l->line+tab[c-1]+1,tab[c]-tab[c-1]-1);
		pn+=tab[c]-tab[c-1]-1;
		memset(templine+pn,SPACE,c<tab_c-1?pad_size:last_pad_size);
		pn+=c<tab_c-1?pad_size:last_pad_size;
	}
	if(tab[tab_c-1]<l->last_pos){
		memcpy(templine+pn,l->line+tab[tab_c-1]+1,l->last_pos-tab[tab_c-1]-1);
		pn+=l->last_pos-tab[tab_c-1]-1;
	}
	templine[pn]=0;
	free(l->line);
	l->line=templine;
	l->last_pos=pn;
	return 2; /*ok, replacement finished*/
}

void ClearNonprintable(char* line, char replace){
/*replace all nonprintable character in line with 'replate' char, replace should not be a zero*/
	int c;
	for(c=0;line[c];c++) 
		if((line[c]<32)&&line[c]!='\n'&&line[c]!='\r'&&line[c]!='\t') line[c]=replace; /*is \r requed for *nix?*/
}

int FlushLineCache(linecache* l){
/*print unprinted in cache, reset line*/
    int errorcode=0;
    if(!l) return 0;
    if(!l->handler||!l->line)return 0;
	if(!ExpandTab(l)) return 0;
	l->line[l->last_pos]=0;
	ClearNonprintable(l->line,' ');
	errorcode=fprintf(l->handler,"%s",l->line);
	if(errorcode){
		l->last_pos=0;
		l->line[0]=0;
	}
	return errorcode;/*ok*/
}

int CloseLineCache(linecache* l){
/*print unprinted, delete cache*/
    int errorcode=1;
	errorcode=FlushLineCache(l);
	free(l->line);
	free(l);
	return errorcode;
}

int AddStringToLineCache(linecache *l, const char* line){
	int p;
	signed int begin=0;
	signed int end=0;
	int alloc_request;
	int len=strlen(line);
	if(!len)return 0;
	for(p=0;p<len;p++){
		if(line[p]=='\n'){
			begin=end;/*prev.end -> curr.begin*/
			end=p+1;
			if(l->last_pos+end-begin<l->max_size ||!l->max_size||line[begin]=='\n'){

				if(end-begin+l->last_pos>=l->allocated){/*buffer incresize*/
					alloc_request=(end-begin+l->last_pos)/DEFAULT_LINE_BUFFER_SIZE+1;
					if(alloc_request>MAX_ALLOWED_CACHED_LINE_SIZE/DEFAULT_LINE_BUFFER_SIZE) return 0;
					l->line=realloc(l->line,alloc_request*DEFAULT_LINE_BUFFER_SIZE);
					if(!l->line)return 0;
				}

				memcpy(l->line+l->last_pos,line+begin,end-begin);
				l->line[l->last_pos+end-begin]=0;
				l->last_pos+=end-begin;
				FlushLineCache(l);
			}
			else{/*TODO warp*/}
		}
	}
	if(end!=len){
		if(l->last_pos+len-end<l->max_size ||!l->max_size||line[len-1]=='\n'){
			memcpy(l->line+l->last_pos,line+end,len-end);
			l->line[l->last_pos+len-end]=0;
			l->last_pos+=len-end;
		}
	}
	return 1;
}

int in_crc_check(char* from, char* to){
	char* p=from;
	if(from>to) return 0; /*hmm..*/
	while(p<=to){
		if(!(
				(*p>='a'&&*p<='f')
				||
				(*p>='A'&&*p<='F')
				||
				(*p>='0'&&*p<='9')
			))
				return 0;
		p++;
	}
	return 1; /*crc!*/
}

char* name_clean(char* line){
	int l=strlen(line);
	char* buffer=malloc(l+9);
	char *p=buffer;
	int c;
	memcpy(buffer,line,l+1);
	buffer[l+7]=0;
	while(*p){
		if(
			(*p=='['&&*(p+9)==']')
			||
			(*p=='('&&*(p+9)==')')
		) {
				if (in_crc_check(p+1,p+8)) memset(p,'_',10);
			}
	if(
		((*p=='_'||*p==' ')&&(p[9]==')'||p[9]==']'))
		||
		((*p=='('||*p=='[')&&(p[9]=='_'||p[9]==' '))
		) if(in_crc_check(p+1,p+8)) memset(p+1,'_',8);
		if(*p==' '&&p!=buffer) *p='_';
		p++;
	}
	c=0;
	for(p=buffer;*p;p++){
		if(*p=='_'&&p[1]=='_') continue;
		if(*p=='_'&&p[1]=='.'&&p!=buffer) continue;
		if(*p==']'&&(p[1]=='_'||p[1]==' ')){
			line[c++]=*p;
			p++;
			continue;
		}
		if(*p=='_'&&p[1]=='-'&&p[2]=='_'){p++;continue;}
		if(*p=='_'&&p!=buffer) line[c]=' ';
		else line[c]=*p;
		c++;
	}
	line[c]=0;
	free(buffer);
	return line;
}


const char* print_mode(const var_t var, const int mode_prn){
	static char buffer[257]; /*TODO REMOVE STATIC!*/
	int mod=1024;
	int div=1;
	int nH,nL;
	int h,m,s;
	int ct_flag=0;
	char *tmp_p;
	int E=0; /*end char, can be 'K','M','G'*/
	*buffer=0;/*luchshe perebded, chem nedobled (c)*/
	if (*var.string){
		if(mode_prn==PRINT_MODE_SHORT_NAME) {
				return name_clean(var.string);/*short_name(buffer,var.string)*/;
		}
		return var.string;
	}
	switch(mode_prn){ /*numeric processing*/
		case PRINT_MODE_NORMAL:
			if(var.number) sprintf(buffer,"%d",var.number);
			return buffer;
		case PRINT_MODE_M1000:
			mod=1000;
			/*passthrow*/
		case PRINT_MODE_M1024:
			if(var.number>=mod*mod*mod) {
				div=mod*mod*mod;
				E='G';
			}else
			if(var.number>=mod*mod){
				div=mod*mod;
				E='M';
			}else
			if(var.number>mod){
				div=mod;
				E='K';
			}
			nH=(int)var.number/(int)div;
			nL=(var.number-nH*div)/(div<=mod?mod:div/mod*100);
			if(!(nL%10)) nL=nL/10;
			if(nH>20||!nL)sprintf(buffer,"%d%c",nH,(char)E);
			else sprintf(buffer,"%d.%d%c",nH,nL,(char)E);
			return buffer;
		case PRINT_MODE_HEX:
			sprintf(buffer,"%x",var.number);
			return buffer;
		case PRINT_MODE_FCC:
			buffer[0]=var.number&0x000000FF;
			buffer[1]=(var.number&0x0000FF00)>>8;
			buffer[2]=(var.number&0x00FF0000)>>16;
			buffer[3]=(var.number&0xFF000000)>>24;
			buffer[4]=0;
			return buffer;
		case PRINT_MODE_COMPACT_TIME:
		    ct_flag=1;
			/*passthrow*/
		case PRINT_MODE_TIME:
			h=var.number/3600;
			m=(var.number%3600)/60;
			s=var.number-h*3600-m*60;
			if(!ct_flag) sprintf(buffer,"%02d:%02d:%02d",h,m,s);
			else{
				tmp_p=buffer;
				if(h) tmp_p+=sprintf(tmp_p,"%dh",h);
				if(h<10&&m) tmp_p+=sprintf(tmp_p,"%dm",m);
				if(!h&&m<10&&s) sprintf(tmp_p,"%ds",s);
			}
			return buffer;
		case PRINT_MODE_CODEC_NAME:
			return fcctoa(var.number);
			break;
		default: sprintf(buffer,"%d",var.number);
	}
	return buffer;
}


int PrintVarToLineCache(linecache*l, int mode_prn,var_t var){
	const char* tmp_buff;
	tmp_buff=print_mode(var,mode_prn);
	AddStringToLineCache(l,tmp_buff);
	return 1;
}

