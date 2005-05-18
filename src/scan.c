/*************************************************************************
 * scan.c File Scaning Module [part of AVInfo 1.x]
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

#include "scan.h"

void RemoveQuotas(char* line){
	int lineLen=strlen(line);
	if(lineLen>1){
		if(*line=='"'&&line[lineLen-1]=='"'){
			memmove(line,line+1,lineLen+1);
			line[lineLen-2]=0;
		}
	}
}


filelist_t* InitFilelist(const char* filelistname){
	FILE* q=stdin;
	filelist_t* retval=NULL;
	int mode=-1;
	if(*filelistname=='-'){
		if(filelistname[1]==0){
			q=stdin;
			mode=1;
		}
	}else {
			q=fopen(filelistname,"r");
			mode=0;
	}
	if(q){
		assert(retval=malloc(sizeof(filelist_t)));
		retval->filelistname=strdup(filelistname);
		retval->filelisthandle=q;
		retval->mode=mode;
	}
	return retval;
}

char* GetNext(filelist_t* filelist){
	char* retval=NULL;
	if(filelist->mode<2&&filelist->filelisthandle){ /*use text filelist (file or stdin)*/
		retval=malloc(MAX_PATH+3);
		if(fgets(retval,MAX_PATH+2,filelist->filelisthandle)){
			CropCRLF(retval);
			if(*retval=='"') RemoveQuotas(retval); /*for windows compability, qutas around filename will be removed*/
		}else{
			free(retval);
			retval=NULL;
		}
	}
	return retval;
}

void CloseFilelist(filelist_t* filelist){
	if(filelist->mode<1) fclose(filelist->filelisthandle);
	free(filelist);
}



int voidparse(vlist_t*list,FILE* f, int flags){
/*used for unsupported files, no data, always success*/
	return 1;
}


const module_t modules[]={
	{	"avi\0",							1,	&riffparse	},
	{	"mpg\0mpeg\0m2v\0m1v\0vob\0",		1,	&mpegparse	},
	{	"smi\0ssa\0srt\0sub\0sami\0s2k\0",	1,	&textparse	},
	{	"mp3\0mp2\0",						1,	&mp3parse	},
	{	"mkv\0",							1,	&mkvparse	},
	{	"rm\0asf\0wmv\0",					1,	&voidparse	},/*currently unsupported*/
	{	"ifo\0",							1,	&ifoparse	},
	{	"ogg\0ogm\0",						1,	&ogmparse	}
};


const char* GetExt(const char* filename){
/*return pointer fo extension in filename, 
return empty line if no extension or filename==NULL, 
requed a valid or NULL filename*/
	int c;
	if(filename){
		for(c=strlen(filename);c>=0;c--){
			if(filename[c]=='.')
				return filename+c+1; /*return pointer to ext. in filename*/
			if(filename[c]=='\\'||filename[c]=='/'||filename[c]==':')	/* '\\' and ':' req. for windows paths*/
				break;
		}
	}
	return ""; /*no ext found*/
}

modulefunc GetModule(const char* pattern){
	/*check pattern within mask in 'modules' global var*/
	int c;
	int mc=0;
	for( c = 0; c < ( sizeof( modules )/sizeof( modules[0] ) ); c++ ) {
		mc=0;
		while( modules[c].mask[ mc ] ){
			if( ! strcasecmp( modules[c].mask + mc, pattern ) ) return modules[c].func;
			mc += strlen( modules[c].mask ) + 1;
		}
	}
	return NULL;
}


modulefunc SelectModule(const char *filename, const config_t* cfg){
/*return module corresponding to filename extension or NULL if no module found
  use a cfg->force_ext and cfg->ignore_ext_list as overrides */

/* TODO add an autodetect*/

	const char* ext;
	int c;
	if(cfg->force_ext) return GetModule(cfg->force_ext);
	ext=GetExt(filename);
	for(c=0;c<cfg->ignore_ext_num;c++)
		if(! strcasecmp(ext,cfg->ignore_ext_list[c])) return NULL;
	return GetModule(ext);
}


void PrepareName(vlist_t* list,const char* in){
/*function split name, path and extension*/
	int c;
	int ext_found=0;
	int name=1;
	c=strlen(in);
	SetStringVar(list,"in",in);
	while(c&&name){
		if(in[c]=='.'&&!ext_found&&name){ /*extenshion found*/
			SetStringVar(list,"ext",in+c+1);
			ext_found=1;	
		}
		if((in[c]=='/'||in[c]==':'||in[c]=='\\')&&name){
			name=0;
			SetStringVar(list,"name",in+c+1);
			break;
		}
		c--;
	}
	if(name)SetStringVar(list,"name",in);
	if(!ext_found) SetStringVar(list,"ext","");
}



FILE* PrepareFile(const char* filename, vlist_t* list, config_t* cfg){
	FILE* retval;
	char buffer[80];
	PrepareName(list,filename);	
	retval=fopen(filename,"rb");
	if(retval){
		fseek(retval,0,SEEK_END); /*TODO: do not use a fseek to get a size, use a stat()*/
		SetNumericVar(list,"size",(int)ftell(retval)); /*TODO size_t!=int!*/
		fseek(retval,cfg->offset,SEEK_SET);
	}
	else{
			snprintf(buffer,80,"unable open file (error #%d)",errno);
			SetStringVar(list,"error", "unable to open file");
	}
	return retval;
}

vlist_t* ScanFile(const char* filename, config_t* cfg){
	modulefunc module=SelectModule(filename,cfg);
	vlist_t* retval=NULL;	
	FILE* handle;
	if(module||cfg->reportUnknown){
		assert(retval=CreateVList(NULL));
	}
	if(module){
		handle=PrepareFile(filename,retval,cfg);
		if(handle){
			if(!module(retval,handle,cfg->flags))  /*	*SCAN*		*/
				SetStringVar(retval,"error","format unrecognized");
			fclose(handle);
		}
	}else{
		if(cfg->reportUnknown){
			PrepareName(retval,filename);
			SetStringVar(retval,"error", "unknown format");
		}
	}
	return retval;
}


fcache_t* scan(config_t* cfg){
/*main scan function*/
	fcache_t* fcache=InitFileCache(); /*replace to Load (TODO)*/
	vlist_t* filedesc;
	filelist_t* filelist;
	char* filename;
	cfg->scanbegin=time(NULL);
	if(fcache){
		if(cfg->filelist){ /*filelist*/
			filelist=InitFilelist(cfg->filelist);
			if(!filelist){
				ClearCache(fcache);
				fprintf(stderr," * unable to open filelist\n");
				return NULL;
			}
			while((filename=GetNext(filelist))){
				filedesc=ScanFile(filename,cfg);
				if(filedesc)  AddRecord(fcache,filename,filedesc);
				if(cfg->wait) sleep(10);
				free(filename);
			}
			CloseFilelist(filelist);
		}
		else{ /* single file or directory*/
			filedesc=ScanFile(cfg->filename,cfg);
			if(filedesc) AddRecord(fcache,cfg->filename,filedesc);
		}
	}
	return fcache;
}
