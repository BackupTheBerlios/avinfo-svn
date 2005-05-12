/*************************************************************************
 * ass.h Script language defenition [part of AVInfo 1.x]
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

#ifndef _H_ASS_H
#define _H_ASS_H

enum{ MODE_NORMAL=0, MODE_EXPRESSION=1, MODE_VAR=2, MODE_COMMAND=3};
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ver.h"
#include "common.h"
#include "var.h"
#include "print.h"

int yyparse(void*);
var_t Op( var_t var1, var_t var2, int op_type );

typedef struct{
	char* line; /*pointer to line for parse*/
	int c;
	int flag; /* EoL or zero at the end*/ /*TODO!*/
	int active;
	int mode;
	vlist_t* list;
	linecache *l; /*handle for output*/
}lexerctl_t;
#define ACTIVE (((lexerctl_t*)lexer_ctl)->active)
#define MODE (((lexerctl_t*)lexer_ctl)->mode)
#define  BUFFER_SIZE 256
#endif
