/*************************************************************************
 * print.h - header of print.c [part of AVInfo 1.x]
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

#ifndef _H_PRINT_H
#define _H_PRINT_H
#include "config.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "common.h"
#include "var.h"
#include "codec.h"
typedef struct{
	int allocated; /*size of allocated buffer for line*/
	char* line; /*cached line*/
	int last_pos; /*last printed position*/
	int max_size; /*max allowed string length*/
	FILE* handler; /*handler for output. may be file, strerr, strout, etc*/
	int cropflag;/*if cropflag=1, overflow will be croped, else, current line will be printed and line begin to filling from begin*/
}linecache;

const char* print_mode(const var_t var, const int mode);

linecache* InitLineCache(FILE* handler, int max_size, int cropflag);

int ExpandTab(linecache* l);

int FlushLineCache(linecache* l);

int CloseLineCache(linecache* l);

int AddStringToLineCache(linecache *l, const char* line);

int PrintVarToLineCache(linecache*l, const int mode_prn,const var_t var);


#endif
