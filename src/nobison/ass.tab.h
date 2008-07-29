/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     E_ATOM = 258,
     WHILE = 259,
     DO = 260,
     IF = 261,
     SET = 262,
     ELSE = 263,
     VAR_PART = 264,
     PRINT = 265,
     EXIT = 266,
     AND = 267,
     OR = 268,
     NE = 269,
     LE = 270,
     GE = 271,
     SHIFT_RIGHT = 272,
     SHIFT_LEFT = 273,
     MM = 274,
     PP = 275
   };
#endif
/* Tokens.  */
#define E_ATOM 258
#define WHILE 259
#define DO 260
#define IF 261
#define SET 262
#define ELSE 263
#define VAR_PART 264
#define PRINT 265
#define EXIT 266
#define AND 267
#define OR 268
#define NE 269
#define LE 270
#define GE 271
#define SHIFT_RIGHT 272
#define SHIFT_LEFT 273
#define MM 274
#define PP 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 46 "ass.y"
{
	int 	letter;
	var_t 	var;
	int 	mode;
	struct{
		int position;
		int flag;
	} state;
	char* 	var_name;
}
/* Line 1489 of yacc.c.  */
#line 100 "ass.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



