/*************************************************************************
 * readtpl.h - header of readtpl.c [part of AVInfo 1.x]
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
#ifndef _H_READTPL_H
#define _H_READTPL_H

#include "config.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"


typedef struct{
	char* text; /*template content*/
	char* name; /*name of template*/
	int allocated; /*space, allocated for 'text'*/
	int used; /*space, used for 'text'*/
	int textlinesize; /*maximal line length for text line (while parsing template)*/
}template_item_t;

typedef struct{
	int templ_n; /*number of templates*/
	template_item_t* content;
}template_t;

#define TEMPLATE_VERSION 1

#ifndef LINE_MAX
	#define MAX_TEMPLATE_LINE_SIZE 2048
#endif
#ifdef LINE_MAX
	#define MAX_TEMPLATE_LINE_SIZE LINE_MAX
#endif

#define DEFAULT_TEMPLATE_SIZE 4*MAX_TEMPLATE_LINE_SIZE
#define MAX_TEMPLATE_SIZE 1024*1024

template_t* ReadTemplate(const char* TemplateFileName, const char* TemplateName);
void DeleteTemplte(template_t* tpl);
#endif
