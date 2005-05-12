/*************************************************************************
 * text.c Subtitle (text files) support [part of AVInfo 1.x]
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
#include "text.h"

extern int textparse (vlist_t* list, FILE* file, int flags ){
/*** This module just detect language of subtitle file (only eng/rus check)
	 v0.1 beta. Ideas acepting and will be taking with pleasure*/
#define MAX_READ_TRY 128
	char buffer[1024];
	char* pointer;
	int GT_128=1;/*non ASCII chars count*/
	int bin=1;
	int total=1;
	int try_count=0;
	IncStreamCounter(list,'t');
	do{
		if(try_count>MAX_READ_TRY) break;
		if(!fread(buffer,1023,1,file)) break;
		try_count++;
		buffer[1023]=0;
		pointer=buffer;
		while(*pointer){
			if(*pointer>128) GT_128++;
			if(*pointer>128 && *pointer <32 && *pointer!='\x09' && *pointer!='\x0D' && *pointer!='\x0A') bin++;
			total++;
			pointer++;
		}
	}while(!feof(file));
	GT_128++;
	total++;
	if(bin>5){
		SetStringVar(list,"t1.lang", "binary");
	}
	else{
		if(total/GT_128<5){
			SetStringVar(list,"t1.lang","non-eng");
		}
		else{
			SetStringVar(list,"t1.lang","eng");
		}
	}
	return 1;
}
