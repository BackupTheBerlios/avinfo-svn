/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 22 "ass.y"


#include "ass.h"
#include "ass.tab.h"
#define YYERROR_VERBOSE

#define 		YYLEX_PARAM 	lexer_ctl
#define 		YYPARSE_PARAM 	lexer_ctl
#define 		line 			(((lexerctl_t*)lexer_ctl)->line)
#define 		pos 			(((lexerctl_t*)lexer_ctl)->c)
#define ctl ((lexerctl_t*)lexer_ctl)

int yyerror( const char *s );
int yylex (YYSTYPE *lval, void* lexer_ctl);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 45 "ass.y"
typedef union YYSTYPE {
	int 	letter;
	var_t 	var;
	int 	mode;
	struct{
		int position;
		int flag;
	} state;
	char* 	var_name;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 144 "ass.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 156 "ass.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   312

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  23
/* YYNRULES -- Number of rules. */
#define YYNRULES  60
/* YYNRULES -- Number of states. */
#define YYNSTATES  111

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,     2,     2,    32,    13,     2,
      34,    35,    30,    26,    38,    27,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    36,
      21,    18,    20,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,    14,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     4,    15,    37,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     5,
       6,     7,     8,     9,    10,    11,    12,    16,    17,    19,
      22,    23,    24,    25,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     4,     5,     8,    10,    13,    14,    21,
      23,    26,    28,    29,    34,    38,    41,    43,    47,    49,
      53,    54,    55,    56,    66,    67,    68,    72,    73,    74,
      83,    84,    85,    93,    95,    98,   103,   105,   107,   110,
     113,   116,   119,   122,   126,   129,   133,   137,   141,   145,
     149,   153,   157,   161,   165,   169,   173,   177,   181,   185,
     189
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      43,     0,    -1,    -1,    -1,    44,    45,    -1,    46,    -1,
      45,    46,    -1,    -1,     8,    47,    63,    18,    64,    36,
      -1,    51,    -1,    57,    36,    -1,    60,    -1,    -1,    11,
      48,    49,    36,    -1,     4,    45,    37,    -1,    12,    36,
      -1,    50,    -1,    49,    38,    50,    -1,    64,    -1,    64,
      39,    64,    -1,    -1,    -1,    -1,     7,    52,    34,    64,
      35,    53,    46,    54,    55,    -1,    -1,    -1,     9,    56,
      46,    -1,    -1,    -1,     6,    58,    46,     5,    59,    34,
      64,    35,    -1,    -1,    -1,     5,    61,    34,    64,    35,
      62,    46,    -1,    10,    -1,    63,    10,    -1,    63,    40,
      64,    41,    -1,     3,    -1,    63,    -1,    29,    63,    -1,
      63,    29,    -1,    28,    63,    -1,    63,    28,    -1,    27,
      64,    -1,    34,    64,    35,    -1,    33,    64,    -1,    64,
      30,    64,    -1,    64,    31,    64,    -1,    64,    26,    64,
      -1,    64,    27,    64,    -1,    64,    19,    64,    -1,    64,
      18,    64,    -1,    64,    13,    64,    -1,    64,    16,    64,
      -1,    64,    15,    64,    -1,    64,    17,    64,    -1,    64,
      21,    64,    -1,    64,    20,    64,    -1,    64,    23,    64,
      -1,    64,    22,    64,    -1,    64,    25,    64,    -1,    64,
      24,    64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    81,    81,    81,    81,    84,    86,    89,    89,    97,
      99,   101,   103,   103,   105,   107,   110,   112,   114,   119,
     129,   130,   131,   129,   133,   135,   135,   139,   140,   139,
     144,   146,   144,   152,   154,   156,   159,   160,   165,   171,
     177,   183,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "E_ATOM", "'{'", "WHILE", "DO", "IF",
  "SET", "ELSE", "VAR_PART", "PRINT", "EXIT", "'&'", "'^'", "'|'", "AND",
  "OR", "'='", "NE", "'>'", "'<'", "LE", "GE", "SHIFT_RIGHT", "SHIFT_LEFT",
  "'+'", "'-'", "MM", "PP", "'*'", "'/'", "'%'", "'!'", "'('", "')'",
  "';'", "'}'", "','", "':'", "'['", "']'", "$accept", "begin", "@1",
  "all", "oper", "@2", "@3", "print_string", "print_var", "if", "@4", "@5",
  "@6", "else_part", "@7", "do", "@8", "@9", "while", "@10", "@11", "var",
  "exp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   123,   259,   260,   261,   262,   263,
     264,   265,   266,    38,    94,   124,   267,   268,    61,   269,
      62,    60,   270,   271,   272,   273,    43,    45,   274,   275,
      42,    47,    37,    33,    40,    41,    59,   125,    44,    58,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    42,    43,    44,    43,    45,    45,    47,    46,    46,
      46,    46,    48,    46,    46,    46,    49,    49,    50,    50,
      52,    53,    54,    51,    55,    56,    55,    58,    59,    57,
      61,    62,    60,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,     2,     1,     2,     0,     6,     1,
       2,     1,     0,     4,     3,     2,     1,     3,     1,     3,
       0,     0,     0,     9,     0,     0,     3,     0,     0,     8,
       0,     0,     7,     1,     2,     4,     1,     1,     2,     2,
       2,     2,     2,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     0,     1,     0,    30,    27,    20,     7,    12,
       0,     4,     5,     9,     0,    11,     0,     0,     0,     0,
       0,     0,    15,     6,    10,    14,     0,     0,     0,    33,
       0,    36,     0,     0,     0,     0,     0,     0,    16,    37,
      18,     0,    28,     0,    34,     0,     0,    42,    40,    38,
      44,     0,    13,     0,    41,    39,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    21,     0,     0,    43,    17,
      51,    53,    52,    54,    50,    49,    56,    55,    58,    57,
      60,    59,    47,    48,    45,    46,    19,     0,     0,     0,
       8,    35,    32,     0,    22,    29,    24,    25,    23,     0,
      26
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     2,    11,    12,    20,    21,    37,    38,    13,
      19,    99,   106,   108,   109,    14,    18,    74,    15,    17,
      97,    39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -27
static const short int yypact[] =
{
       3,     6,    55,   -27,    55,   -27,   -27,   -27,   -27,   -27,
     -26,    55,   -27,   -27,    18,   -27,    12,    -5,    55,    30,
      60,    48,   -27,   -27,   -27,   -27,    48,    66,    48,   -27,
      -9,   -27,    48,    60,    60,    48,    48,    -8,   -27,    40,
     111,   158,   -27,   179,   -27,    48,    48,   -16,    15,    15,
     -27,   200,   -27,    48,   -27,   -27,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,   -27,    31,   -27,   136,    84,   -27,   -27,
     256,   256,   256,   256,   269,   281,    65,    65,    65,    65,
      26,    26,   -16,   -16,   -27,   -27,   242,    55,    48,    55,
     -27,   -27,   -27,   221,   -27,   -27,    63,   -27,   -27,    55,
     -27
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -27,   -27,   -27,    69,   -11,   -27,   -27,   -27,    25,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,    -7,   -24
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yysigned_char yytable[] =
{
      23,    44,    41,    -2,    43,    23,     3,    27,    47,    45,
      22,    50,    51,    30,    70,    71,     4,     5,     6,     7,
       8,    76,    77,     9,    10,    44,    48,    49,    52,    26,
      53,    46,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    25,
      44,    31,    68,    69,    24,    46,    70,    71,    29,     4,
       5,     6,     7,     8,    28,    98,     9,    10,    54,    55,
      29,    42,   107,    16,   103,    32,    33,    34,    79,     0,
      46,    35,    36,     0,     0,     0,   102,     0,   104,    66,
      67,    68,    69,     0,     0,    70,    71,    56,   110,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,     0,    70,    71,     0,     0,     0,     0,
       0,     0,     0,     0,    56,   101,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
       0,    70,    71,     0,     0,     0,     0,     0,     0,    56,
      72,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     0,     0,    70,    71,     0,     0,
       0,    56,   100,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     0,     0,    70,    71,
       0,     0,    56,    73,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,     0,     0,    70,
      71,     0,     0,    56,    75,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     0,     0,
      70,    71,     0,     0,    56,    78,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
       0,    70,    71,     0,     0,    56,   105,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,     0,    70,    71,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     0,     0,    70,    71,    61,    62,
      63,    64,    65,    66,    67,    68,    69,     0,     0,    70,
      71,    62,    63,    64,    65,    66,    67,    68,    69,     0,
       0,    70,    71
};

static const yysigned_char yycheck[] =
{
      11,    10,    26,     0,    28,    16,     0,    18,    32,    18,
      36,    35,    36,    20,    30,    31,     4,     5,     6,     7,
       8,    45,    46,    11,    12,    10,    33,    34,    36,    34,
      38,    40,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    37,
      10,     3,    26,    27,    36,    40,    30,    31,    10,     4,
       5,     6,     7,     8,    34,    34,    11,    12,    28,    29,
      10,     5,     9,     4,    98,    27,    28,    29,    53,    -1,
      40,    33,    34,    -1,    -1,    -1,    97,    -1,    99,    24,
      25,    26,    27,    -1,    -1,    30,    31,    13,   109,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    13,    41,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    13,
      39,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    -1,    -1,
      -1,    13,    36,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    31,
      -1,    -1,    13,    35,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    -1,    -1,    13,    35,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    -1,    -1,    13,    35,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    -1,    -1,    13,    35,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    -1,    30,    31,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    -1,    -1,    30,
      31,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    43,    44,     0,     4,     5,     6,     7,     8,    11,
      12,    45,    46,    51,    57,    60,    45,    61,    58,    52,
      47,    48,    36,    46,    36,    37,    34,    46,    34,    10,
      63,     3,    27,    28,    29,    33,    34,    49,    50,    63,
      64,    64,     5,    64,    10,    18,    40,    64,    63,    63,
      64,    64,    36,    38,    28,    29,    13,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      30,    31,    39,    35,    59,    35,    64,    64,    35,    50,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    62,    34,    53,
      36,    41,    46,    64,    46,    35,    54,     9,    55,    56,
      46
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 81 "ass.y"
    {;}
    break;

  case 4:
#line 82 "ass.y"
    {;}
    break;

  case 5:
#line 84 "ass.y"
    {;}
    break;

  case 6:
#line 86 "ass.y"
    {;}
    break;

  case 7:
#line 89 "ass.y"
    {MODE=MODE_VAR;;}
    break;

  case 8:
#line 90 "ass.y"
    {
				if(ACTIVE) SetVar(ctl->list,yyvsp[-3].var_name,yyvsp[-1].var.number, yyvsp[-1].var.string ); 
				free(yyvsp[-1].var.string);
				free(yyvsp[-3].var_name);
				MODE=MODE_NORMAL;
			;}
    break;

  case 9:
#line 97 "ass.y"
    {;}
    break;

  case 10:
#line 99 "ass.y"
    {;}
    break;

  case 11:
#line 101 "ass.y"
    {;}
    break;

  case 12:
#line 103 "ass.y"
    {	MODE=MODE_VAR;;}
    break;

  case 13:
#line 103 "ass.y"
    {MODE=MODE_NORMAL;;}
    break;

  case 14:
#line 105 "ass.y"
    {;}
    break;

  case 15:
#line 107 "ass.y"
    {if(ACTIVE) YYACCEPT;;}
    break;

  case 16:
#line 110 "ass.y"
    {;}
    break;

  case 17:
#line 112 "ass.y"
    {;}
    break;

  case 18:
#line 114 "ass.y"
    {
				if (ACTIVE) PrintVarToLineCache(ctl->l,PRINT_MODE_NORMAL,yyvsp[0].var);
				free(yyvsp[0].var.string);
			;}
    break;

  case 19:
#line 119 "ass.y"
    {
				if(ACTIVE){
					PrintVarToLineCache(ctl->l,yyvsp[-2].var.number,yyvsp[0].var);
				}
				free(yyvsp[-2].var.string);
				free(yyvsp[0].var.string);
			;}
    break;

  case 20:
#line 129 "ass.y"
    {MODE=MODE_VAR; ;}
    break;

  case 21:
#line 130 "ass.y"
    {yyvsp[-4].state.flag=ACTIVE; ACTIVE=ACTIVE&&yyvsp[-1].var.number;MODE=MODE_NORMAL;free(yyvsp[-1].var.string);;}
    break;

  case 22:
#line 131 "ass.y"
    {ACTIVE=yyvsp[-6].state.flag;;}
    break;

  case 24:
#line 133 "ass.y"
    {;}
    break;

  case 25:
#line 135 "ass.y"
    {ACTIVE=ACTIVE&!yyvsp[-5].var.number;;}
    break;

  case 26:
#line 136 "ass.y"
    {ACTIVE=yyvsp[-10].state.flag;;}
    break;

  case 27:
#line 139 "ass.y"
    {;}
    break;

  case 28:
#line 140 "ass.y"
    {MODE=MODE_VAR;;}
    break;

  case 29:
#line 141 "ass.y"
    {MODE=MODE_NORMAL;if(yyvsp[-1].var.number) pos=yyvsp[-7].state.position;free(yyvsp[-1].var.string);;}
    break;

  case 30:
#line 144 "ass.y"
    {MODE=MODE_VAR;yyvsp[0].state.flag=ACTIVE;;}
    break;

  case 31:
#line 146 "ass.y"
    {MODE=MODE_NORMAL; ACTIVE=ACTIVE&&yyvsp[-1].var.number;free(yyvsp[-1].var.string);;}
    break;

  case 32:
#line 148 "ass.y"
    {if (ACTIVE)  {pos=yyvsp[-6].state.position;}  else {ACTIVE=yyvsp[-6].state.flag; };;}
    break;

  case 33:
#line 152 "ass.y"
    {yyval.var_name=yyvsp[0].var_name;;}
    break;

  case 34:
#line 154 "ass.y"
    {yyval.var_name=malloc(strlen(yyvsp[-1].var_name)+strlen(yyvsp[0].var_name)+1);strcpy(yyval.var_name,yyvsp[-1].var_name);strcat(yyval.var_name,yyvsp[0].var_name);free(yyvsp[-1].var_name);free(yyvsp[0].var_name);;}
    break;

  case 35:
#line 156 "ass.y"
    {yyval.var_name=malloc(strlen(yyvsp[-3].var_name)+10); sprintf(yyval.var_name,"%s%d",yyvsp[-3].var_name,yyvsp[-1].var.number);free(yyvsp[-1].var.string);free(yyvsp[-3].var_name);;}
    break;

  case 36:
#line 159 "ass.y"
    {yyval.var=yyvsp[0].var;;}
    break;

  case 37:
#line 160 "ass.y"
    { 
				yyval.var=GetVar(ctl->list,yyvsp[0].var_name);
				free(yyvsp[0].var_name);

			;}
    break;

  case 38:
#line 165 "ass.y"
    {/*TODO!!! fix memory leak*/
					yyval.var=GetVar(ctl->list,yyvsp[0].var_name);
					yyval.var.number++;
					if(ACTIVE) SetVar(ctl->list,yyvsp[0].var_name,yyval.var.number, yyval.var.string);
					free(yyvsp[0].var_name);
			;}
    break;

  case 39:
#line 171 "ass.y"
    {
					yyval.var=GetVar(ctl->list,yyvsp[-1].var_name);
					if(ACTIVE) SetVar(ctl->list,yyvsp[-1].var_name,yyval.var.number+1, yyval.var.string);
					free(yyvsp[-1].var_name);
			;}
    break;

  case 40:
#line 177 "ass.y"
    {
					yyval.var=GetVar(ctl->list,yyvsp[0].var_name);
					yyval.var.number--;
					if(ACTIVE) SetVar(ctl->list,yyvsp[0].var_name,yyval.var.number, yyval.var.string);
					free(yyvsp[0].var_name);
			;}
    break;

  case 41:
#line 183 "ass.y"
    {
					yyval.var=GetVar(ctl->list,yyvsp[-1].var_name);
					yyval.var.number--;
					if(ACTIVE) SetVar(ctl->list,yyvsp[-1].var_name,yyval.var.number-1, yyval.var.string);
					free(yyvsp[-1].var_name);
			;}
    break;

  case 42:
#line 189 "ass.y"
    {yyval.var=yyvsp[0].var;if(!*yyval.var.string) yyval.var.number=-yyval.var.number;;}
    break;

  case 43:
#line 190 "ass.y"
    {yyval.var=yyvsp[-1].var;;}
    break;

  case 44:
#line 191 "ass.y"
    {yyval.var=yyvsp[0].var;if(!*yyval.var.string) yyval.var.number=!yyval.var.number;;}
    break;

  case 45:
#line 192 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'*');;}
    break;

  case 46:
#line 193 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'/');;}
    break;

  case 47:
#line 194 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'+');;}
    break;

  case 48:
#line 195 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'-');;}
    break;

  case 49:
#line 196 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,NE);;}
    break;

  case 50:
#line 197 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'=');;}
    break;

  case 51:
#line 198 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'&');;}
    break;

  case 52:
#line 199 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,AND);;}
    break;

  case 53:
#line 200 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'|');;}
    break;

  case 54:
#line 201 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,OR);;}
    break;

  case 55:
#line 202 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'<');;}
    break;

  case 56:
#line 203 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,'>');;}
    break;

  case 57:
#line 204 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,GE);;}
    break;

  case 58:
#line 205 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,LE);;}
    break;

  case 59:
#line 206 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,SHIFT_LEFT);;}
    break;

  case 60:
#line 207 "ass.y"
    {yyval.var=Op(yyvsp[-2].var,yyvsp[0].var,SHIFT_LEFT);;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1501 "ass.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 209 "ass.y"


var_t Op(var_t var1, var_t var2, int op_type){
	var_t res;
	res.string=NULL;
	res.number=0;
	switch(op_type){
		case '+': if(*var1.string && *var2.string){
					res.string=malloc(var1.number+var2.number+1);
					strcpy(res.string,var1.string);
					strcpy(res.string+var1.number,var2.string);
				} 
				else res.number=var1.number+var2.number;
				break;
		case '-': res.number=var1.number-var2.number;
				break;
		case '*': res.number=var1.number*var2.number;
				break;
		case '/':res.number=var2.number?var1.number/var2.number:1;
				break;
		case NE :if(*var1.string&&*var2.string) res.number= strcasecmp(var1.string,var2.string);
					else res.number=(var1.number!=var2.number);
				break;
		case '=':if(*var1.string && *var2.string)res.number=! strcasecmp(var1.string,var2.string);
					else res.number=(var1.number==var2.number);
				break;
		case '&':res.number=var1.number&var2.number;
				break;
		case AND:res.number=var1.number&&var2.number;
				break;
		case '|':res.number=var1.number|var2.number;
				break;
		case OR :res.number=var1.number||var2.number;
				break;
		case '<':res.number=(var1.number<var2.number);
				break;
		case '>':res.number=(var1.number>var2.number);
				break;
		case GE :res.number=var1.number>=var2.number;
				break;
		case LE :res.number=var1.number<=var2.number;
				break;
		case SHIFT_LEFT:res.number=var1.number<<var2.number;
				break;
		case SHIFT_RIGHT:res.number=var1.number>>var2.number;
				break;
		default: res.number=1;
	}
	if(!res.string) res.string=strdup("");
	free(var1.string);
	free(var2.string);
	return res;
}

int yyerror (const char *s) /* вызывается yyparse в случае ошибки */
{
	printf ("\n* error in template: %s\n",s);
	return 1;
}

int isoperator(const char ch1, const char ch2){
	const int ops[]={
				'>','>',SHIFT_RIGHT,
				'<','<',SHIFT_LEFT, 
				'>','=',GE,
				'+', '+', PP,
				'-','-',MM,
				'<','=',LE,
				'!','=',NE,
				'|', '|', OR,
				'&', '&', AND
			}; 
	const char op[]={
			'+', '-', '=', '*', '/', '!', '>', '<',
			'&', '|', '(', ')', '[', ']', ';', '}', '{', ',', ':', ';'
			 }; /*chars to be returned as is - special (reserved) symbols*/
	int cnt=0;
	for(cnt=0;cnt<sizeof(ops)/sizeof(int);cnt+=3)
		if(ch1==ops[cnt]&&ch2==ops[cnt+1])	return ops[cnt+2];			
	for(cnt=0;cnt<sizeof(op)/sizeof(char);cnt++)
		if(ch1==op[cnt]) return ch1;
	return 0;
}

int iskeyword(char* string){
	const char* ops[]={ "if", "while", "do", "print", "set", "exit", "else"};
	const int codes[]={  IF,   WHILE,   DO,   PRINT, SET, EXIT, ELSE};
	char* pointer;
	char buffer[BUFFER_SIZE];
	int buff_p=0;
	int c;
	for(pointer=string;(isalpha(*pointer));pointer++) buffer[buff_p++]=*pointer;
	buffer[buff_p]=0;
	for(c=0;c<sizeof(ops)/sizeof(char*);c++){
		if(!strcmp(ops[c],buffer)) 	{
				return codes[c];
		}
	}
	return 0;
}

#define skip_digit(a,b) {while(isdigit(a[(b)])) (b)++;}
#define skip_alpha(a,b) {while(isalpha(a[(b)])) (b)++;}

int yylex (YYSTYPE *yylval, void* lexer_ctl){
	char *buffer=NULL;
	char *string=NULL;
	char *string_pointer;
	int buffer_pos;
	int tmp_char;
	while(line[pos]==' '||line[pos]=='\t'||line[pos]=='\n') pos++;
	if(!line[pos]) return 0;
	if( (tmp_char=isoperator(line[pos],line[pos+1])) ) {
		if(tmp_char!=line[pos])pos++;/* >>, >=, !=, ==, etc */
		pos++;
		return tmp_char;
	}
	if(MODE==MODE_VAR){
		if(line[pos]=='"'){
			pos++;
			string=malloc(strlen(line+pos)+1);
			string_pointer=string;
			while(line[pos]!='"'&&line[pos]){
				if(line[pos]=='\\'){
					pos++;
					switch(line[pos]){
						case 0: return 0; /*eol*/
						case 's': *string=' ';
								break;
						case 'n': *string='\n';
								break;
						case 't': *string='\t';
								break;
						case 'x':
								pos++;
								*string=atoi(line+pos);
								skip_digit(line,pos);
								pos--;
						default: 
							*string=line[pos];
					}
				}  else *string=line[pos];
                string++;
				pos++;
			};

			if(line[pos]=='"') pos++;
			*string=0; /*eol*/
			yylval->var.string=string_pointer;
			yylval->var.number=strlen(yylval->var.string);
			return E_ATOM;

		}
		if(isdigit(line[pos])){
			yylval->var.number=atoi(line+pos);
			yylval->var.string=strdup("");
			skip_digit(line,pos);
			return E_ATOM;
		}
		if(isalpha(line[pos])||line[pos]=='.'||line[pos]=='?'){
			buffer=malloc(strlen(line+pos));
			buffer_pos=0;
			while(isalpha(line[pos])||isdigit(line[pos])||line[pos]=='.'||line[pos]=='?')
			buffer[buffer_pos++]=line[pos++];
			buffer[buffer_pos]=0;
			yylval->var_name=buffer;
			return VAR_PART;
		}
		printf ("internal error\n");
	}
	/*ELSE, MODE=MODE_NORMAL*/
	yylval->state.position=pos;
	tmp_char=iskeyword(line+pos);
	if(tmp_char){
		skip_alpha(line,pos);
		return tmp_char;
	};
	return 1; /*error*/
}

 

