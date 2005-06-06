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
#ifndef _H_CONFSET_H
#define _H_CONFSET_H
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include "ver.h"
#include "common.h"
#include "var.h"
#include "codec.h"
#include "readtpl.h"

#define COMMENT_CHAR '#'
#ifndef MAX_PATH
	#define MAX_PATH 1024
#endif
#define MAX_CONFIG_LINE_SIZE MAX_PATH*2

enum{
VT_unknown=0,
VT_string=1,
VT_number=2
}; /*option type*/


enum{
	OPTION_unknown,
	OPTION_reccurent=1,
	OPTION_cache_ro,
	OPTION_cache_er,
	OPTION_no_cache,
	OPTION_no_scan,
	OPTION_delete,
	OPTION_backup,
	OPTION_maxline,
	OPTION_silent,
	OPTION_wait,
	OPTION_sort,
	OPTION_list,
	OPTION_config,
	OPTION_template_file,
	OPTION_cache_file,
	OPTION_output,
	OPTION_append,
	OPTION_process,
	OPTION_template_name,
	OPTION_force_ext,
	OPTION_ignore_ext,
	OPTION_group,
	OPTION_modify_var,
	OPTION_date_range,
	OPTION_usebuiltin,
	OPTION_help,
	OPTION_version,
	OPTION_title,
	OPTION_reportUnknown,
	OPTION_offset,
	OPTION_verbose,
	OPTION_filename
};

typedef struct {
	char* force_ext;
	int ignore_ext_num;
	char** ignore_ext_list;
	char* filelist;
	char* filename;
	char* fcachename;
	char* userconfig;
	char* systemconfig;
	int flags;
	int linelength;
	char* templatefile;
	char* templatename;
	vlist_t* base;
	template_t* template;
	char* outputfilename;
	char* process;
	char* title;
	int reccurent;
	int cache_ro;
	int cache_er;
	int no_cache;
	int no_scan;
	int delete;
	int backup;
	int forcemaxline;
	int silent;
	int wait;
	int sort;
	int checkcrc;
	int falltobuiltintemplate; 
	int usebuiltin;
	int noerrorclose; /*if ==1, just shut up and terminate (if --help, we do not need to do anything except help message)*/
	int reportUnknown;
	int offset; /*scaning offset in file*/
	int appendFlag; /*open output file for append instead overwrite*/
	int verbose; /*print filename to stderr while scaning*/
	time_t scanbegin;
	time_t reportbegin;
	time_t timeend;
}config_t;

typedef struct{
	char* name;
	int value;
}constants_t;


extern config_t config;
extern void ImportConstants(vlist_t *list);
extern int SetConfig(vlist_t* list, int argc, char* argv[]);
extern int NamePrepare(vlist_t* list,const char* in);
extern char* GetOptFromFile(const char* filename);
extern config_t* Configure(int argc, char* argv[]);

typedef struct{
	char* name;
	char ShortCMD;
	int OptID;
	int type; /*VT_string/VT_number/VT_unknown*/
	char* description; /*for builtin help*/
}optd_t;

typedef struct{/*filling while scanned*/
	int found;
	char* string_value; /*filling while scaning.*/
	int number_value; /*filling while scaning*/
}optv_t;

int ReadConf(const char* ConfigName, const optd_t* OptList, const int OptListSize, optv_t* conf, const int AllowChange);
extern optv_t* ReadCommandLine(int argc, char* argv[], optv_t* retopt, const optd_t* OptList, const int OptListSize);
int ApplyOption(config_t* conf, const optd_t*optd, optv_t* in, const int OptListSize);
void ClearOpt(optv_t* optv);
void CloseConfig(config_t *cfg);
#endif
