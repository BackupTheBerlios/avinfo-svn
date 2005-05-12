/*************************************************************************
 * common.c Implementation of some common-using function [part of AVInfo 1.x]
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
 #include "common.h"

int CHARS_PRINT=0;
int MAX_CHARS;

char *ITOA(int value, char *string,int radix){
	if(radix==16)
		sprintf(string,"%x",value);
	else
		sprintf(string,"%d",value);
	return string;
}

char* strjoin(const char* line1, const char* line2){
	int l1=strlen(line1);
	int l2=strlen(line2);
	char* retval=malloc(l1+l2+1);
	assert(retval);
	memcpy(retval,line1,l1);
	memcpy(retval+l1,line2,l2);
	retval[l1+l2]=0;
	return retval;
}

int advmemcmp(const char* base, const char* pattern, const int number){
/* 
	@description: Function compare a base and pattern lines with no more then 'number' bytes.
	some like memcmp, but using 0 in pattern as a mask "anybyte"*/
	int c;
	for(c=0;c<number;c++){
		if(!pattern[c]) continue;
		if(pattern[c]!=base[c]) return base[c]-pattern[c];
	}
	return 0; /*ok*/
}

int sscmp(const char* base, const char* pattern){
/* return 0 if pattern is begin of base and non 0 in other case*/
	int c=0;
	while(base[c]==pattern[c]&&pattern[c])
		c++;
	return pattern[c];
}


void lowcase(char* line){
	char* temp;
	for(temp=line;*temp;temp++){
		*temp=tolower(*temp);
	}
}


int maskstrcmp(char* line,char* pattern){
	/**
		case insensetive comparation of two strings, 
		accept mask in pattern: 
			# - isdigit(), 
			$ - isalpha(), 
			? - any sign (except 0)
		return: 0 - string comparation successful, notzero - not.
	**/
	int c=0;
	while(pattern[c]){
		switch(pattern[c]){
			case '#':
				if(isdigit(line[c])) break; /*ok*/
				return 1; /*not*/
			case '$':
				if(isalpha(line[c])) break; /*ok*/
				return 1;  /*not*/
			case '?':
				if(line[c]) break; /*ok*/
				return 1;  /*not*/
			default:
				if(toupper(line[c])==toupper(pattern[c])) break;  /*ok*/
				return 1; /*not*/
		}
		c++;
	}
	return line[c];
}

char* mkstr (char* buffer, int pos, int size){
	char *retval=malloc(size+1);
	if(retval){
		memcpy(retval,buffer+pos,size);
		retval[size]=0;
	}
	return retval;
}

void inline CropCRLF(char* buf){
	int linesize=strlen(buf);
	if(linesize) if(buf[linesize-1]==0xD||buf[linesize-1]==0xA) buf[linesize-1]=0;
	if(linesize>1) if(buf[linesize-2]==0xD||buf[linesize-2]==0xA) buf[linesize-2]=0;
}

char* SkipSpaces(char* line){
	char* p;
	for(p=line;*p;p++)
		if(*p!=' '&&*p!='\t') break;
	return p;
}
