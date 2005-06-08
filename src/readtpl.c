/*************************************************************************
 * readtpl.c - template reading [part of AVInfo 1.x]
 *
 * Copyright (c) 2005 George Shuklin
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
#include "readtpl.h"
#include "memleak.h"
template_t* InitTemplate(const int namec, const char* namev[]){
	template_t* retval=NULL;
	int c;
	assert(retval=malloc(sizeof(template_t)));
	assert(retval->content=malloc(sizeof(template_item_t)*namec));
	for(c=0;c<namec;c++){
		assert(retval->content[c].text=malloc(DEFAULT_TEMPLATE_SIZE));
		retval->content[c].text[0]=0;
		retval->content[c].allocated=DEFAULT_TEMPLATE_SIZE;
		retval->content[c].used=0;
		retval->content[c].textlinesize=0;
		assert(retval->content[c].name=strdup(namev[c]));
	}
	retval->templ_n=namec;
	return retval;
}


int SearchTemplateHeader(FILE* f, const char* name){
/**
	@description:	Read file f, search template header
	@return: number of line, where template starts (line with template header), or 0 if nothing found
**/
#define ALT_SEARCH_SIGN "[template"
	int lc=0;
	char buf[MAX_TEMPLATE_LINE_SIZE];	
	char* p;
	char pattern[MAX_TEMPLATE_LINE_SIZE];	
	if(name) snprintf(pattern,MAX_TEMPLATE_SIZE,"[template name=%s ver=%d]",name,TEMPLATE_VERSION);
	while(fgets(buf,MAX_TEMPLATE_LINE_SIZE,f)){
		lc++;
		p=SkipSpaces(buf);
		CropCRLF(p);
		if(!*p||*p=='#') continue;
		if(name) if(!strcmp(p,pattern)) {
			return lc;
		}
		if(!name) if(!memcmp(p,ALT_SEARCH_SIGN,strlen(ALT_SEARCH_SIGN))) return lc;
	}
	return -1;
}



int ReadTemplate2(FILE *f,template_t* t, int lc){
	int tpl_curr=1;/*by default we reading a body text if other do not specified by [head]/[foot]*/
	char buf[MAX_TEMPLATE_LINE_SIZE];
	char *p,*p2;
	int temp;
	int c;
	int param;
	int fflag;
	int status=0;
	while(fgets(buf,MAX_TEMPLATE_LINE_SIZE,f)){
		status=1;
		lc++;
		p=SkipSpaces(buf);
		if(!*p||*p=='#') continue;
		if(*p=='['){
			fflag=0;
			for(c=0;c<t->templ_n;c++){
		       	temp=strlen(t->content[c].name);
				if(!memcmp(p+1,t->content[c].name,temp)){
					fflag=1;
					p2=SkipSpaces(p+temp+1);
					if(*p2=='='){
						p2=SkipSpaces(p2+1);
						param=atoi(p2);
					}else param=0;
					tpl_curr=c;
					t->content[c].textlinesize=param;
				}
			}
			if(!fflag) break;
		}else{
			if(tpl_curr==-1) continue;
			temp=strlen(p);
			while(temp+t->content[tpl_curr].used>=t->content[tpl_curr].allocated){/*TODO*/}
			memcpy(t->content[tpl_curr].text+t->content[tpl_curr].used,p,temp);
			t->content[tpl_curr].used+=temp;
		}
	}
	return status;
}

template_t* ReadTemplate(const char* TemplateFileName, const char* TemplateName){
/*
	@description:	Read template file (by TemplateFileName), search template specified by TemplateName
	@parameter:		TemplateFileName - name of file with templates.
					TemplateName - name of template
	@return:		
	*/
	FILE* f;
	template_t* retval;
	int lc;
	const char* template_parts_names[]={"head","body","foot"};
	#define template_parts_names_number (sizeof(template_parts_names)/sizeof(*template_parts_names))
	f=fopen(TemplateFileName,"r");
	if(!f) {
		printf ("* unable to open template file %s\n",TemplateFileName);
		return NULL;
	}
	lc=SearchTemplateHeader(f,TemplateName);
	if(lc==-1) {
		printf("template %s not found in %s\n",TemplateName, TemplateFileName);
		return NULL;
	}
	retval=InitTemplate(template_parts_names_number,template_parts_names);
	if(!ReadTemplate2(f,retval,lc)) {
		retval=NULL; /*bad, redo, memory leak*/
	}
	return retval;
}


void DeleteTemplate(template_t* tpl){
	int c;
	if(tpl){
		for(c=0;c<tpl->templ_n;c++){
			if(tpl->content[c].text) free(tpl->content[c].text);
			if(tpl->content[c].name) free(tpl->content[c].name);
		}
		free(tpl->content);
		free(tpl);
	}
}
