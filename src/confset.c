/*************************************************************************
 * confset.c configuration and CMD line reading [part of AVInfo 1.x]
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
#include "confset.h"

const char* help_title=
	AVINFO_SIGNATURE" "
	AVINFO_VERSION" "
	AVINFO_VERSIONNAME"\n";

const char* help_head=
	"Usage: avinfo [FILENAME] ... [OPTION]\nGenerate report about audio video file(s)\n\n";

const char* help_foot="\t" AVINFO_URL "\n\tbulid: " __DATE__" "__TIME__
	", (" AVINFO_BUILDNAME")\n\t(c) George Shuklin, gs@shounen.ru\n\n";

const constants_t consts[]={
	{"m1000",PRINT_MODE_M1000},
	{"m1024",PRINT_MODE_M1024},
	{"hex",PRINT_MODE_HEX},
	{"fcc",PRINT_MODE_FCC},
	{"ct",PRINT_MODE_COMPACT_TIME},
	{"sn",PRINT_MODE_SHORT_NAME},
	{"time",PRINT_MODE_TIME},
	{"cn", PRINT_MODE_CODEC_NAME},
	{"maxlist",77},
	{"sotona",0x29A},
	{"DIV3",FOURCC_DIV3},
	{"XVID",FOURCC_XVID},
	{"DIVX",FOURCC_DIVX},
	{"DX50",FOURCC_DX50}
};

const optd_t parameter[]={
	{	"include",		0,		0,					VT_unknown,	""	}, /*special value*/
	{	"reccurent",	'r',	OPTION_reccurent,	VT_number,	"Do reccurent scan of directory"	},
	{	"cache-ro",		'R',	OPTION_cache_ro, 	VT_number,	"ReadOnly access to cache file"		},
	{	"cache-erase",	'E',	OPTION_cache_er, 	VT_number,	"Recreate new cache file (old will be erased)"	},
	{	"no-cache",		'n',	OPTION_no_cache, 	VT_number,	"Do not use cache file"	},
	{	"no-scan",		'N',	OPTION_no_scan, 	VT_number,	"Do not scan (only use a cache)"	},
	{	"delete",		'D',	OPTION_delete, 		VT_number,	"Remove specified files from cache"	},
	{	"backup",		'B',	OPTION_backup, 		VT_number,	"Create backup copy of cache"		},
	{	"max-line",		'm',	OPTION_maxline, 	VT_number,	"redefine maximal line length"		},
	{	"silent",		's',	OPTION_silent, 		VT_number,	"do not print any on screen"		},
	{	"wait",			'w',	OPTION_wait, 		VT_number,	"pause between scan operation (ms)"	},
	{	"sort",			's',	OPTION_sort, 		VT_number,	"sort output by filename"			},
	{	"crc-verify",	'V',	OPTION_crc, 		VT_number,	"check CRC32 (if filename contain CRC) (SLOW!)"	},
	{	"list",			'l',	OPTION_list, 		VT_string,	"use a filelist (use '-' as a stdin)"	},
	{	"config",		'c',	OPTION_config, 		VT_string,	"use a different config file"	},
	{	"template-file",'T',	OPTION_template_file, VT_string,"use a different template file"	},
	{	"cache-file",	'C',	OPTION_cache_file,	VT_string,	"use a different cache-file"	},
	{	"output",		'o',	OPTION_output, 		VT_string,	"write otput to specified file"	},
	{	"process",		'p',	OPTION_process, 	VT_string,	"mask for file selection"		},
	{	"template",		't',	OPTION_template_name, VT_string,"template name"					},
	{	"force-ext",	'f',	OPTION_force_ext, 	VT_string,	"thread all file as specified type (buggly)"	},
	{	"ignore-ext",	'i',	OPTION_ignore_ext,	VT_string,	"ignore specified extension (separated by ';')"	},
	{	"group",		'g',	OPTION_group,		VT_string,	"use grouping"	},
	{	"modify-var",	'M',	OPTION_modify_var,	VT_string,	"set variable for template parser"	},
	{	"date-range",	'd',	OPTION_date_range,	VT_string,	"set date range (YYYY.MM.DD-YYYY.MM.DD)"	},
	{	"help",			'h',	OPTION_help,		VT_unknown, "diplay help message"	},
	{	"built-in",		'b',	OPTION_usebuiltin,	VT_number,	"use built in template if external template file not found"	},
	{	"version",		'v',	OPTION_version,		VT_unknown, "application vesion"	},
	{	"title",		0,		OPTION_title,		VT_string,	"set up title (for html templates)"	},
	{	"report-unknown",0,		OPTION_reportUnknown,VT_unknown,	"report about files with unknown format"},
	{	"filename",		0,		OPTION_filename,	VT_string,	""}
};


vlist_t* CreateConstantList(){
	int c;
	time_t gtime=time(NULL);
	vlist_t* retval;
	struct tm* vtime;
	assert((int)gtime!=-1);
	assert(retval=CreateVList(NULL));
	for (c=0;c<sizeof(consts)/sizeof(constants_t);c++)
		SetNumericVar(retval,consts[c].name,consts[c].value);
	SetStringVar(retval,"app.name",AVINFO_SIGNATURE);
	SetStringVar(retval,"app.ver", AVINFO_VERSION" "AVINFO_VERSIONNAME);
	SetStringVar(retval,"app.build",AVINFO_BUILDNAME);
	SetStringVar(retval,"app.url",AVINFO_URL);

	vtime=localtime(&gtime);
	SetNumericVar(retval,"run.utime",gtime);
	SetNumericVar(retval,"run.year",vtime->tm_year+1900);
	SetNumericVar(retval,"run.mon",vtime->tm_mon+1);
	SetNumericVar(retval,"run.day",vtime->tm_mday);
	SetNumericVar(retval,"run.hour",vtime->tm_hour);
	SetNumericVar(retval,"run.min",vtime->tm_min);
	SetNumericVar(retval,"run.sec",vtime->tm_sec);
	SetNumericVar(retval,"run.wday",vtime->tm_wday);
	SetNumericVar(retval,"run.yday",vtime->tm_yday);
	return retval;
}

char* GetEnvVar(const char* varname){ 
	char* retval;
	char* clearname=malloc(strlen(varname)+1);
	int c,cc;
	assert(clearname);
	cc=0;
	c=0;
	while(varname[c]&&varname[c]!='%') c++;
	c++;
	while(varname[c]&&varname[c]!='%'){
		clearname[cc++]=varname[c++];
	}
	clearname[cc]=0;
	retval=getenv(clearname);
	return retval?retval:""; 
	free(clearname);
} 


char* CropQuotation(const char* line){
	char* retval;
	int c;
	if(line[0]!='"') return strdup(line);
	assert(retval=malloc(strlen(line)));
	for(c=1;line[c];c++){
		if(line[c]!='"') retval[c-1]=line[c];
		else break;
	}
	retval[c-1]=0;
	return retval;
}


char* CopyStringValue(char* line){
	char* retval;
	switch(line[0]){
		case '%': 
			retval=strdup(GetEnvVar(line));
			break;
		case '"':
			retval=CropQuotation(line);
			break;
		default: retval=strdup(line);
	}
	return retval;
}


int CopyIntValue(char* line){
	char* work_line;
	int retval;
	if(line[0]=='%'){
		work_line=GetEnvVar(line);
	}else work_line=line;
	retval=atoi(work_line); /*TODO hex, octal, binary, boolean (Y/N, yes/no)*/
	return retval;
}

void AddIgnoreList(config_t* conf,char* string){
	/*convert string to list of values, value are separated by ';'(without or with spaces)
	  result places at conf->ignore_ext_num (numer of values) and conf->ignore_ext_list*/
	int c;
	int base=0;
	int size=0;
	for(c=0;string[c];c++){
		if(string[c]==';'){
			if(c-base<2) continue; /*ignore ';;', etc*/
			conf->ignore_ext_num++;
			assert(conf->ignore_ext_list=realloc(conf->ignore_ext_list,conf->ignore_ext_num));
			size=base-c;
			assert(conf->ignore_ext_list[conf->ignore_ext_num-1]=malloc(base-c+1));
			memcpy(conf->ignore_ext_list[conf->ignore_ext_num-1],string+base,base-c);
			conf->ignore_ext_list[conf->ignore_ext_num-1][base-c]=0;
			base=c+1;
		}
	}
}

void ModifyVar(config_t* conf,char* svalue){
	char varname[PATH_MAX];
	char varvalue[PATH_MAX];
	int c;
	int nc=0;
	int vc=0;
	int mode=0;
	int slen=strlen(svalue);
	int vartype=0;	 /*0 - number 1 - string*/
	for(c=0;c<slen;c++){
		if(mode){
			varvalue[vc++]=svalue[c];
		}else{
			if(svalue[c]=='='||svalue[c]==':') {
				varname[nc]=0;
				mode=1;
				continue;
			}
			varname[nc++]=svalue[c];
		}
	}
	varvalue[vc]=0;
	if(*varname){
		for(c=0;c<vc;c++) 
			if(!isdigit(varvalue[c])) 
				vartype=1;
		if(vartype){
			SetStringVar(conf->base,varname,varvalue);
		}else{
			SetNumericVar(conf->base,varname,atoi(varvalue));
		}
	}
}

void ParseDateRange(config_t* conf,char* svalue){
	/*TODO*/
}


void FillAfterOption(char* from, char* to){
	char* p=from;
	while(*p){
		if(*p=='='||*p==':') if (p[1]) {
			strcpy(to,p+1);
			return;
		}
		p++;
	}
	strcpy(to,"");
}

int GetOption(char* line, char* retval,const optd_t* OptList, const int OptListSize){
	int c;
	if(*line=='-'){
		if(line[1]=='-'){ /*long option*/
			for(c=0;c<OptListSize;c++){
				if(!sscmp(line+2,OptList[c].name)) {
					FillAfterOption(line+3,retval);
					return c;
				}
			}
			printf("* unknown option: %s\n",line);
			return OPTION_unknown;
		}else{ /*short option*/
				for(c=0;c<OptListSize;c++){
					if(line[1]==OptList[c].ShortCMD){
						FillAfterOption(line+2,retval);
						return c;
					}
				}
			}
		printf("* unknown option: %s\n",line);
		return OPTION_unknown;
	}
	strcpy(retval,line);
	return OPTION_filename;
}

optv_t* ReadCommandLine(int argc, char* argv[], optv_t* retopt, const optd_t* OptList, const int OptListSize){
	int c;
	int option;
	char value[MAX_PATH];
	for(c=1;c<argc;c++){
		option=GetOption(argv[c], value, OptList,OptListSize);
		if(OptList[option].type==VT_string){
			/*string*/
			retopt[option].found=1;
			retopt[option].string_value=CopyStringValue(value);
		}
		if(OptList[option].type==VT_number){
			/*number*/
			retopt[option].found=1;
			retopt[option].number_value=CopyIntValue(value);
		}
		if(OptList[option].type==VT_unknown){
			retopt[option].found=1;
			retopt[option].number_value=1;
		}
	}
	return retopt;
}

int GetSection(char**retval, const char* line){
	int c=0;
	while(line[c]&&line[c]!='='&&line[c]!='#'){
		(*retval)[c]=line[c];
		c++;
	} 
	(*retval)[c]=0;
	return c ;
}	

void CropEndSpaces(char* line){
	int c;
	for(c=strlen(line);c>=0;c--){
		if(line[c]!=' '&&line[c]!='\t'&&line[c]) break;
		line[c]=0;
	}
}

int SplitLine(char** name, char** value, char*line){
	/*@return: 0 - ok, 1 - no content, 2 - no value*/
	char* p;
	int temp;
	p=SkipSpaces(line);
	temp=GetSection(name,p);
	if(!temp) return 1;
	CropEndSpaces(*name);
	temp=GetSection(value,SkipSpaces(p+temp+1));
	if(!temp) return 2;
	CropEndSpaces(*value);
	return 0;
}


int FindOptionNumber(const char* OptName, const optd_t* OptList, const int OptListSize){
	/*return No of option or -1 if no such option*/
	int c;
	for(c=0;c<OptListSize;c++){
		if(!strcmp(OptName,OptList[c].name)) return c;
	}
	return -1;
}


#define COMMENT_CHAR '#'
#define MAX_CONFIG_LINE_SIZE MAX_PATH*2
int ReadConf(const char* ConfigName, const optd_t* OptList, const int OptListSize, optv_t* conf, const int AllowChange){

	char *buf;
	char *name;
	char *value;
	FILE* f;
	int Option;
	int linec;
	char* templine;
	f=fopen(ConfigName,"r");
	if(!f){
		if(ConfigName) fprintf(stderr,"* unable to open configure file %s\n",ConfigName);
		return -1;
	}
	linec=0;
	buf=malloc(MAX_CONFIG_LINE_SIZE);
	name=malloc(MAX_CONFIG_LINE_SIZE);
	value=malloc(MAX_CONFIG_LINE_SIZE);
	assert(buf&&name&&value);
	while((fgets(buf,MAX_CONFIG_LINE_SIZE,f))){
		linec++;
		CropCRLF(buf);
		switch(SplitLine(&name,&value,buf)){
			case 1: continue;
			case 2: fprintf(stderr,"* incorrect line #%d of %s: %s\n",linec,ConfigName,buf);
					continue;
		}
		Option=FindOptionNumber(name,OptList,OptListSize);
		if(Option==-1){/*unknown option*/
			fprintf(stderr,"* unknown option at line #%d of %s: %s\n",linec,ConfigName,name);
			continue;
		}
		if(Option==0){
			templine=CopyStringValue(value);
			if(!strcmp(templine,ConfigName)){
				fprintf(stderr,"* recurrent include at line #%d of %s\n",linec,ConfigName);
			}else{
				if(!ReadConf(templine,OptList,OptListSize,conf,AllowChange)) fprintf(stderr, "* error in include file %s from line #%d of %s\n",value,linec,ConfigName);
			}
			free(templine);
			continue;
		}
		if((conf[Option].found&&AllowChange)||!conf[Option].found){
			if(parameter[Option].type==1){	/*String*/
				if(conf[Option].found) free(conf[Option].string_value);
				conf[Option].string_value=CopyStringValue(value);
				conf[Option].found=1;
			}
			if(parameter[Option].type==2){/*Number*/
				conf[Option].number_value=CopyIntValue(value);
				conf[Option].found=1;
			}
		}
	}
	fclose(f);
	free(buf);
	free(name);
	free(value);
	return 0;
}


void PrintOptionList(const optd_t* optd, const int OptListSize){
	int c;
	for(c=0;c<OptListSize;c++){
		if(optd[c].ShortCMD) printf("-%c",optd[c].ShortCMD);else printf("  ");
		if(*(optd[c].name)&&optd[c].ShortCMD)printf(", ");else printf ("  ");
		if(*(optd[c].name)) printf("--%-12s ",optd[c].name); else printf ("             ");
		if(*(optd[c].description)) printf("%s\n",optd[c].description); else printf (" (no description)\n");
	}
	printf("\n");
}

void PrintHelpMessage(const optd_t* optd, const int OptListSize){
	printf(help_title);
	printf(help_head);
	PrintOptionList(optd,OptListSize);
	printf(help_foot);
}



const char* SystemMandatoryConfig=CFG_SYSTEM_MANDATORY_CONFIG;
const char* SystemDefaultConfig=CFG_SYSTEM_DEFAULT_CONFIG;
const char* UserDefaultConfig=CFG_USER_DEFAULT_CONFIG;
const char* SystemDefaultTemplate=CFG_SYSTEM_DEFAULT_TEMPLATE;
const char* DefaultTemplateName=CFG_DEFAULT_TEMPLATE_NAME;


static char* GetStartDir(char* appPath){
	int l=strlen(appPath);
	char* retval;
	while(l && (appPath[l]!='/'&&appPath[l]!='\\')) l--;  /*note: appPath[l]!='\\' - for Windows compability*/
	if(!l) return strdup("");
	assert(retval=malloc(l+1));
	memcpy(retval,appPath,l+1);
	retval[l+1]=0;
	return retval;
}

static int isAbsolutePath(const char* line){
	/** return 1 if line is absolute path and return 0 if relative*/
	if(*line=='/'||*line=='\\') return 1; /* '\\' - for Windows*/
	if(strlen(line)>3){ 
		if(isalpha(line[0])&&line[1]==':'&&(line[2]=='/'||line[2]=='\\')) return 1;  /*for Windows, paths, looks like: C:\util\avinfo, d:/run, etc */
	}
	return 0;
}


config_t* Configure(int argc, char* argv[]){
	#define EL_NUM sizeof(parameter)/sizeof(*parameter)
	char* startDir=GetStartDir(argv[0]);
	char* ConfigPath;
	config_t * cfg;
	optv_t* optv;
	assert(cfg=calloc(sizeof(config_t),1));
	assert(optv=calloc(sizeof(optv_t),EL_NUM));

	if(*SystemDefaultConfig) {
		if(isAbsolutePath(SystemDefaultConfig)) ConfigPath=strdup(SystemDefaultConfig);
			else ConfigPath=strjoin(startDir,SystemDefaultConfig); /* N.B. If SystemConfig is not absolute path, it will thread as a relative path starts from avinfo home dir (not a pwd!)*/
		ReadConf(ConfigPath,parameter,EL_NUM,optv,1);
		free(ConfigPath);
	}
	if (argc>1) 
		ReadCommandLine(argc,argv,optv,parameter,EL_NUM);

	ApplyOption(cfg,parameter,optv,EL_NUM);

	if(cfg->noerrorclose) exit(0); /*help, version, etc - We are already print message, just silent shut up (and down)*/

	if(cfg->userconfig) {
		ReadConf(cfg->userconfig,parameter,EL_NUM,optv,1); 
	}
	else{
		if(*UserDefaultConfig) {
		if(isAbsolutePath(UserDefaultConfig)) ConfigPath=strdup(UserDefaultConfig);
			else ConfigPath=strjoin(startDir,UserDefaultConfig); /* N.B. If cfg->userconfig is not absolute path, it will thread as a relative path starts from avinfo home dir (not a pwd!)*/
			ReadConf(ConfigPath,parameter,EL_NUM,optv,1);
			free(ConfigPath);
		}
	}
	if(*SystemMandatoryConfig) {
			if(isAbsolutePath(SystemMandatoryConfig)) ConfigPath=strdup(SystemMandatoryConfig);
				else ConfigPath=strjoin(startDir,SystemDefaultConfig); /* N.B. If cfg->userconfig is not absolute path, it will thread as a relative path starts from avinfo home dir (not a pwd!)*/
				ReadConf(ConfigPath,parameter,EL_NUM,optv,1);
				free(ConfigPath);
		}
	if(cfg->userconfig||*UserDefaultConfig||*SystemMandatoryConfig)	
		ApplyOption(cfg,parameter,optv,EL_NUM);

	if(!cfg->templatefile){
			if(isAbsolutePath(SystemDefaultTemplate)) ConfigPath=strdup(SystemDefaultTemplate);
				else ConfigPath=strjoin(startDir,SystemDefaultTemplate);
	}else{
			if(isAbsolutePath(cfg->templatefile)) ConfigPath=strdup(cfg->templatefile);
			else ConfigPath=strjoin(startDir,cfg->templatefile);
	}
	if(!cfg->templatename) cfg->templatename=strdup(DefaultTemplateName);
	cfg->template=ReadTemplate(ConfigPath,cfg->templatename);
	free(ConfigPath);
	free(startDir);
	if(!cfg->template){
		/*TODO add BuiltIn*/
		cfg->falltobuiltintemplate=1;
		printf("Switch to builtin template\n");
	}
	assert(cfg->base=CreateConstantList());
	if(!cfg->filename&&!cfg->filelist){
		printf("no filename of filelist, try avinfo --help\n");
		/*todo add CloseConfigure*/
		return 0;
	}
	return cfg;
	#undef EL_NUM
}



int ApplyOption(config_t* conf, const optd_t*optd, optv_t* in, const int OptListSize){
	/* convert option list (from command line or config file) to internal config_t structure*/
	/*return 0 if all OK, return 1 if error*/
	int c;
	for(c=0;c<OptListSize;c++){
		if(!in[c].found) continue;
		switch(optd[c].OptID){
			case OPTION_reccurent: 
				conf->reccurent=in[c].number_value;
				break;
			case OPTION_cache_ro:
				conf->cache_ro=in[c].number_value;
				break;
			case OPTION_cache_er:
				conf->cache_er=in[c].number_value;
				break;
			case OPTION_no_cache:
				conf->no_cache=in[c].number_value;
				break;
			case OPTION_no_scan:
				conf->no_scan=in[c].number_value;
				break;
			case OPTION_delete:
				conf->delete=in[c].number_value;
				break;
			case OPTION_backup:
				conf->backup=in[c].number_value;
				break;
			case OPTION_maxline:
				conf->linelength=in[c].number_value;/*override a template values for head/body/foot*/
				break;
			case OPTION_silent:
				conf->silent=in[c].number_value;
				break;
			case OPTION_wait:
				conf->wait=in[c].number_value;
				break;
			case OPTION_sort:
				conf->sort=in[c].number_value;
				break;
			case OPTION_crc:
				conf->checkcrc=in[c].number_value;
				break;
			/*path option*/
			case OPTION_list:
				if(conf->filelist) free(conf->filelist);
				conf->filelist=strdup(in[c].string_value);
				break;
			case OPTION_config:
				if(conf->userconfig) free(conf->userconfig);
				conf->userconfig=strdup(in[c].string_value);
				break;
			case OPTION_template_file:
				if(conf->templatefile) free(conf->templatefile);
				conf->templatefile=strdup(in[c].string_value);
				break;
			case OPTION_cache_file:
				if(conf->fcachename) free(conf->fcachename);
				conf->fcachename=strdup(in[c].string_value);
				break;
			case OPTION_output:
				if(conf->outputfilename) free(conf->outputfilename);
				conf->outputfilename=strdup(in[c].string_value);
				break;
			/*string option*/
			case OPTION_process:
				if(conf->process) free(conf->process);
				conf->process=strdup(in[c].string_value);
				break;
			case OPTION_template_name:
				if(conf->templatename) free(conf->templatename);
				conf->templatename=strdup(in[c].string_value);
				break;
			case OPTION_force_ext:
				if(conf->force_ext) free(conf->force_ext);
				conf->force_ext=strdup(in[c].string_value);
				break;
			/*special*/
			case OPTION_ignore_ext:
				AddIgnoreList(conf,in[c].string_value); 
				break;
			case OPTION_group:
				fprintf(stderr,"* grouping yet not supported\n");
				break;
			case OPTION_modify_var:
				ModifyVar(conf,in[c].string_value);
				break;
			case OPTION_date_range:
				ParseDateRange(conf,in[c].string_value); /*TODO*/
			/*filename/path*/
				break;
			case OPTION_filename:
				if(conf->filename) free(conf->filename);
				conf->filename=strdup(in[c].string_value);
				break;
			case OPTION_usebuiltin:
				conf->usebuiltin=in[c].number_value;
				break;
			case OPTION_version:
				conf->noerrorclose=1;
				printf("%s",help_title);
				printf("%s",help_foot);
				break;
			case OPTION_title:
				conf->title=strdup(in[c].string_value);
				break;
			case OPTION_reportUnknown:
				conf->reportUnknown=in[c].number_value;
				break;
			case OPTION_help:
				conf->noerrorclose=1;
				PrintHelpMessage(optd,OptListSize);
				break;

		}
	}
	return 0;
}
