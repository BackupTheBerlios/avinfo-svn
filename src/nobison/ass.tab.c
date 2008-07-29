/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

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




/* Copy the first part of user declarations.  */
#line 22 "ass.y"


#include "ass.h"
#include "ass.tab.h"
#include "memleak.h"
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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 187 of yacc.c.  */
#line 165 "ass.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 178 "ass.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   312

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNRULES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,     8,    10,    13,    14,    21,
      23,    26,    28,    29,    34,    38,    41,    43,    47,    49,
      53,    54,    55,    56,    66,    67,    68,    72,    73,    74,
      83,    84,    85,    93,    95,    98,   103,   105,   107,   110,
     113,   116,   119,   122,   126,   129,   133,   137,   141,   145,
     149,   153,   157,   161,   165,   169,   173,   177,   181,   185,
     189
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
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
static const yytype_uint8 yyrline[] =
{
       0,    82,    82,    82,    82,    85,    87,    90,    90,    98,
     100,   102,   104,   104,   106,   108,   111,   113,   115,   120,
     130,   131,   132,   130,   134,   136,   136,   140,   141,   140,
     145,   147,   145,   153,   155,   157,   160,   161,   166,   172,
     178,   184,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
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
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   123,   259,   260,   261,   262,   263,
     264,   265,   266,    38,    94,   124,   267,   268,    61,   269,
      62,    60,   270,   271,   272,   273,    43,    45,   274,   275,
      42,    47,    37,    33,    40,    41,    59,   125,    44,    58,
      91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
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
static const yytype_uint8 yyr2[] =
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
static const yytype_uint8 yydefact[] =
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

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    11,    12,    20,    21,    37,    38,    13,
      19,    99,   106,   108,   109,    14,    18,    74,    15,    17,
      97,    39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -27
static const yytype_int16 yypact[] =
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
static const yytype_int8 yypgoto[] =
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
static const yytype_int8 yytable[] =
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

static const yytype_int8 yycheck[] =
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
static const yytype_uint8 yystos[] =
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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
#line 82 "ass.y"
    {;}
    break;

  case 4:
#line 83 "ass.y"
    {;}
    break;

  case 5:
#line 85 "ass.y"
    {;}
    break;

  case 6:
#line 87 "ass.y"
    {;}
    break;

  case 7:
#line 90 "ass.y"
    {MODE=MODE_VAR;;}
    break;

  case 8:
#line 91 "ass.y"
    {
				if(ACTIVE) SetVar(ctl->list,(yyvsp[(3) - (6)].var_name),(yyvsp[(5) - (6)].var).number, (yyvsp[(5) - (6)].var).string ); 
				free((yyvsp[(5) - (6)].var).string);
				free((yyvsp[(3) - (6)].var_name));
				MODE=MODE_NORMAL;
			;}
    break;

  case 9:
#line 98 "ass.y"
    {;}
    break;

  case 10:
#line 100 "ass.y"
    {;}
    break;

  case 11:
#line 102 "ass.y"
    {;}
    break;

  case 12:
#line 104 "ass.y"
    {	MODE=MODE_VAR;;}
    break;

  case 13:
#line 104 "ass.y"
    {MODE=MODE_NORMAL;;}
    break;

  case 14:
#line 106 "ass.y"
    {;}
    break;

  case 15:
#line 108 "ass.y"
    {if(ACTIVE) YYACCEPT;;}
    break;

  case 16:
#line 111 "ass.y"
    {;}
    break;

  case 17:
#line 113 "ass.y"
    {;}
    break;

  case 18:
#line 115 "ass.y"
    {
				if (ACTIVE) PrintVarToLineCache(ctl->l,PRINT_MODE_NORMAL,(yyvsp[(1) - (1)].var));
				free((yyvsp[(1) - (1)].var).string);
			;}
    break;

  case 19:
#line 120 "ass.y"
    {
				if(ACTIVE){
					PrintVarToLineCache(ctl->l,(yyvsp[(1) - (3)].var).number,(yyvsp[(3) - (3)].var));
				}
				free((yyvsp[(1) - (3)].var).string);
				free((yyvsp[(3) - (3)].var).string);
			;}
    break;

  case 20:
#line 130 "ass.y"
    {MODE=MODE_VAR; ;}
    break;

  case 21:
#line 131 "ass.y"
    {(yyvsp[(1) - (5)].state).flag=ACTIVE; ACTIVE=ACTIVE&&(yyvsp[(4) - (5)].var).number;MODE=MODE_NORMAL;free((yyvsp[(4) - (5)].var).string);;}
    break;

  case 22:
#line 132 "ass.y"
    {ACTIVE=(yyvsp[(1) - (7)].state).flag;;}
    break;

  case 24:
#line 134 "ass.y"
    {;}
    break;

  case 25:
#line 136 "ass.y"
    {ACTIVE=ACTIVE&!(yyvsp[(-4) - (1)].var).number;;}
    break;

  case 26:
#line 137 "ass.y"
    {ACTIVE=(yyvsp[(-7) - (3)].state).flag;;}
    break;

  case 27:
#line 140 "ass.y"
    {;}
    break;

  case 28:
#line 141 "ass.y"
    {MODE=MODE_VAR;;}
    break;

  case 29:
#line 142 "ass.y"
    {MODE=MODE_NORMAL;if((yyvsp[(7) - (8)].var).number) pos=(yyvsp[(1) - (8)].state).position;free((yyvsp[(7) - (8)].var).string);;}
    break;

  case 30:
#line 145 "ass.y"
    {MODE=MODE_VAR;(yyvsp[(1) - (1)].state).flag=ACTIVE;;}
    break;

  case 31:
#line 147 "ass.y"
    {MODE=MODE_NORMAL; ACTIVE=ACTIVE&&(yyvsp[(4) - (5)].var).number;free((yyvsp[(4) - (5)].var).string);;}
    break;

  case 32:
#line 149 "ass.y"
    {if (ACTIVE)  {pos=(yyvsp[(1) - (7)].state).position;}  else {ACTIVE=(yyvsp[(1) - (7)].state).flag; };;}
    break;

  case 33:
#line 153 "ass.y"
    {(yyval.var_name)=(yyvsp[(1) - (1)].var_name);;}
    break;

  case 34:
#line 155 "ass.y"
    {(yyval.var_name)=malloc(strlen((yyvsp[(1) - (2)].var_name))+strlen((yyvsp[(2) - (2)].var_name))+1);strcpy((yyval.var_name),(yyvsp[(1) - (2)].var_name));strcat((yyval.var_name),(yyvsp[(2) - (2)].var_name));free((yyvsp[(1) - (2)].var_name));free((yyvsp[(2) - (2)].var_name));;}
    break;

  case 35:
#line 157 "ass.y"
    {(yyval.var_name)=malloc(strlen((yyvsp[(1) - (4)].var_name))+10); sprintf((yyval.var_name),"%s%d",(yyvsp[(1) - (4)].var_name),(yyvsp[(3) - (4)].var).number);free((yyvsp[(3) - (4)].var).string);free((yyvsp[(1) - (4)].var_name));;}
    break;

  case 36:
#line 160 "ass.y"
    {(yyval.var)=(yyvsp[(1) - (1)].var);;}
    break;

  case 37:
#line 161 "ass.y"
    { 
				(yyval.var)=GetVar(ctl->list,(yyvsp[(1) - (1)].var_name));
				free((yyvsp[(1) - (1)].var_name)); /*$1 - name*/

			;}
    break;

  case 38:
#line 166 "ass.y"
    {/*TODO!!! fix memory leak*/
					(yyval.var)=GetVar(ctl->list,(yyvsp[(2) - (2)].var_name));
					(yyval.var).number++;
					if(ACTIVE) SetVar(ctl->list,(yyvsp[(2) - (2)].var_name),(yyval.var).number, (yyval.var).string);
					free((yyvsp[(2) - (2)].var_name));
			;}
    break;

  case 39:
#line 172 "ass.y"
    {
					(yyval.var)=GetVar(ctl->list,(yyvsp[(1) - (2)].var_name));
					if(ACTIVE) SetVar(ctl->list,(yyvsp[(1) - (2)].var_name),(yyval.var).number+1, (yyval.var).string);
					free((yyvsp[(1) - (2)].var_name));
			;}
    break;

  case 40:
#line 178 "ass.y"
    {
					(yyval.var)=GetVar(ctl->list,(yyvsp[(2) - (2)].var_name));
					(yyval.var).number--;
					if(ACTIVE) SetVar(ctl->list,(yyvsp[(2) - (2)].var_name),(yyval.var).number, (yyval.var).string);
					free((yyvsp[(2) - (2)].var_name));
			;}
    break;

  case 41:
#line 184 "ass.y"
    {
					(yyval.var)=GetVar(ctl->list,(yyvsp[(1) - (2)].var_name));
					(yyval.var).number--;
					if(ACTIVE) SetVar(ctl->list,(yyvsp[(1) - (2)].var_name),(yyval.var).number-1, (yyval.var).string);
					free((yyvsp[(1) - (2)].var_name));
			;}
    break;

  case 42:
#line 190 "ass.y"
    {(yyval.var)=(yyvsp[(2) - (2)].var);if(!*(yyval.var).string) (yyval.var).number=-(yyval.var).number;;}
    break;

  case 43:
#line 191 "ass.y"
    {(yyval.var)=(yyvsp[(2) - (3)].var);;}
    break;

  case 44:
#line 192 "ass.y"
    {(yyval.var)=(yyvsp[(2) - (2)].var);if(!*(yyval.var).string) (yyval.var).number=!(yyval.var).number;;}
    break;

  case 45:
#line 193 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'*');;}
    break;

  case 46:
#line 194 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'/');;}
    break;

  case 47:
#line 195 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'+');;}
    break;

  case 48:
#line 196 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'-');;}
    break;

  case 49:
#line 197 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),NE);;}
    break;

  case 50:
#line 198 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'=');;}
    break;

  case 51:
#line 199 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'&');;}
    break;

  case 52:
#line 200 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),AND);;}
    break;

  case 53:
#line 201 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'|');;}
    break;

  case 54:
#line 202 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),OR);;}
    break;

  case 55:
#line 203 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'<');;}
    break;

  case 56:
#line 204 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),'>');;}
    break;

  case 57:
#line 205 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),GE);;}
    break;

  case 58:
#line 206 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),LE);;}
    break;

  case 59:
#line 207 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),SHIFT_LEFT);;}
    break;

  case 60:
#line 208 "ass.y"
    {(yyval.var)=Op((yyvsp[(1) - (3)].var),(yyvsp[(3) - (3)].var),SHIFT_LEFT);;}
    break;


/* Line 1267 of yacc.c.  */
#line 1833 "ass.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 210 "ass.y"


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

 

