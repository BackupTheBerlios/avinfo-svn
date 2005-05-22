/*************************************************************************
 * common.h header file for common.c [part of AVInfo 1.x]
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
#ifndef _H_COMMON_H
#define _H_COMMON_H
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char* min_view (const int number);
char *ITOA(int value, char *string,int radix);
int advmemcmp(const char* base,const char* pattern, const int number);
void lowcase(char* line);
enum{
	PRINT_MODE_NORMAL=0,
	PRINT_MODE_M1000=1,
	PRINT_MODE_M1024=2,
	PRINT_MODE_HEX=3,
	PRINT_MODE_FCC=4,
	PRINT_MODE_COMPACT_TIME=5,
	PRINT_MODE_TIME=6,
	PRINT_MODE_CODEC_NAME=7,
	PRINT_MODE_SHORT_NAME=8
};

extern int MAX_CHARS;
extern int CHARS_PRINT;
extern char* mkstr (char* buffer, int pos, int size);
#define STRICMP(a,b) strcasecmp(a,b)

void inline CropCRLF(char* buf);
char* SkipSpaces(char* line);
int sscmp(const char* base, const char* pattern);
int maskstrcmp(char* line,char* pattern);
char* strjoin(const char* line1, const char* line2);
#endif

