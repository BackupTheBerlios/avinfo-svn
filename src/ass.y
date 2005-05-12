/*************************************************************************
 * ass.y AVInfo Simple Script parser engie [part of AVInfo 1.x]
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
%{

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

%}

//%expect 1

%pure_parser

%expect 1 /* else block*/

%union{
	int 	letter;
	var_t 	var;
	int 	mode;
	struct{
		int position;
		int flag;
	} state;
	char* 	var_name;
}

%token	<var>		E_ATOM
%token	<state>		'{' WHILE DO IF SET ELSE
%token	<var_name>	VAR_PART
%type	<var>		exp 
%type	<var_name>	var
%type	<state>		do while
%type <var>		oper
%token 	PRINT  EXIT


%left 	'&' '^' '|' OR AND
%left 	'='
%left 	NE 
%left 	'>' '<' GE LE
%left 	SHIFT_LEFT SHIFT_RIGHT
%left 	'+' '-'
%left 	PP MM 
%left	'*' '/' '%'
%right	'!'
%left 	'(' ')'


%%


begin: |{}
		all {};

all: oper {}
	|
	all oper{}
	;

oper:   SET {MODE=MODE_VAR;} 
			var '=' exp ';' {
				if(ACTIVE) SetVar(ctl->list,$3,$5.number, $5.string ); 
				free($5.string);
				free($3);
				MODE=MODE_NORMAL;
			}
		|
		if {}
		|
		do ';' {}
		|
		while {}
		|	
		PRINT	 {	MODE=MODE_VAR;}	print_string ';' {MODE=MODE_NORMAL;}
		|
		'{' all '}' {}
		|
		EXIT ';' {if(ACTIVE) YYACCEPT;}
		;

print_string: print_var{}
			|
			print_string ',' print_var {}
			;
print_var:   exp  {
				if (ACTIVE) PrintVarToLineCache(ctl->l,PRINT_MODE_NORMAL,$1);
				free($1.string);
			}
			|
			exp ':' exp {
				if(ACTIVE){
					PrintVarToLineCache(ctl->l,$1.number,$3);
				}
				free($1.string);
				free($3.string);
			};



if: IF {MODE=MODE_VAR; }  '(' exp ')'
		 {$1.flag=ACTIVE; ACTIVE=ACTIVE&&$4.number;MODE=MODE_NORMAL;free($4.string);} 
		oper {ACTIVE=$1.flag;} else_part;

else_part: {}/*no else*/
			|
			ELSE {ACTIVE=ACTIVE&!$<var>-4.number;} 
			oper {ACTIVE=$<state>-7.flag;};


do: DO {} 
	 oper WHILE {MODE=MODE_VAR;}  '(' exp ')'
	{MODE=MODE_NORMAL;if($7.number) pos=$1.position;free($7.string);};


while: WHILE {MODE=MODE_VAR;$1.flag=ACTIVE;}
		 '(' exp ')'
		{MODE=MODE_NORMAL; ACTIVE=ACTIVE&&$4.number;free($4.string);} 
		oper 
		{if (ACTIVE)  {pos=$1.position;}  else {ACTIVE=$1.flag; };}
		;


var: VAR_PART {$$=$1;}
	| 
	var VAR_PART {$$=malloc(strlen($1)+strlen($2)+1);strcpy($$,$1);strcat($$,$2);free($1);free($2);}
	|
	var '[' exp ']' {$$=malloc(strlen($1)+10); sprintf($$,"%s%d",$1,$3.number);free($3.string);free($1);};


exp: 		E_ATOM{$$=$1;}| 
			var { 
				$$=GetVar(ctl->list,$1);
				free($1);

			}|
			PP var{/*TODO!!! fix memory leak*/
					$$=GetVar(ctl->list,$2);
					$$.number++;
					if(ACTIVE) SetVar(ctl->list,$2,$$.number, $$.string);
					free($2);
			}|
			var PP{
					$$=GetVar(ctl->list,$1);
					if(ACTIVE) SetVar(ctl->list,$1,$$.number+1, $$.string);
					free($1);
			}|

			MM var{
					$$=GetVar(ctl->list,$2);
					$$.number--;
					if(ACTIVE) SetVar(ctl->list,$2,$$.number, $$.string);
					free($2);
			}|
			var MM{
					$$=GetVar(ctl->list,$1);
					$$.number--;
					if(ACTIVE) SetVar(ctl->list,$1,$$.number-1, $$.string);
					free($1);
			}|
			'-' exp {$$=$2;if(!*$$.string) $$.number=-$$.number;}|
			'(' exp ')' {$$=$2;}|
			'!' exp {$$=$2;if(!*$$.string) $$.number=!$$.number;}|
			exp '*' exp {$$=Op($1,$3,'*');}|
			exp '/' exp {$$=Op($1,$3,'/');}|
			exp '+' exp {$$=Op($1,$3,'+');}|
			exp '-' exp {$$=Op($1,$3,'-');}|
			exp NE exp  {$$=Op($1,$3,NE);}|
			exp '=' exp {$$=Op($1,$3,'=');}|
			exp '&' exp {$$=Op($1,$3,'&');}|
			exp AND exp {$$=Op($1,$3,AND);}|
			exp '|' exp {$$=Op($1,$3,'|');}|
			exp OR exp  {$$=Op($1,$3,OR);}|
			exp '<' exp {$$=Op($1,$3,'<');}|
			exp '>' exp {$$=Op($1,$3,'>');}|
			exp GE exp  {$$=Op($1,$3,GE);}|
			exp LE exp	{$$=Op($1,$3,LE);}|
			exp SHIFT_LEFT exp {$$=Op($1,$3,SHIFT_LEFT);}|
			exp SHIFT_RIGHT exp {$$=Op($1,$3,SHIFT_LEFT);};

%%

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

 
