/*************************************************************************
 * filecach.c file caching module [part of AVInfo 1.x]
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

#include "filecach.h"
#include "memleak.h"


char* CopyStripName(const char* name){
	int c;
	for(c=strlen(name);c>=0;c--)
		if(name[c]=='\\'||name[c]=='/'){
			break;
		}
	return strdup(name+c+1);
}


int CacheCheck (const fcache_t *c, const char* filename){

	char* tempname;
	struct stat s;
	int i;

	assert(tempname=CopyStripName(filename));
	if(!stat(filename,&s)){
		free(tempname); 
		return -2;/*fail to get stats info*/
	}
	for(i=0;i<c->used_records;i++){	
		if(c->record[i].filesize==s.st_size){
			if(!strcmp(c->record[i].filename,tempname)){
				c->record[i].flag_found++;
				free(tempname);
				return i;
			}
		}
	}
	return -1;

}

int AddRecord(fcache_t* c, const char* name, vlist_t *l){

	/* @desc: Add a new record at the end of records array
	   @param: c - pointer to cache, l - variable list
	   @return: <0 - error, >=0 - order number of record
	*/

	int i;
	struct stat s;
	assert(c!=NULL);
	while(c->used_records>=c->allocated_records){
		assert(c->record=realloc(c->record,c->allocated_records*2*sizeof(fcache_entry_t)));
		c->allocated_records*=2;
	}
	i=c->used_records;
	c->record[i].filename=CopyStripName(name);
	c->record[i].flag_found=1;
	c->record[i].flag_newfile=1;
	c->record[i].filesize=s.st_size;
	c->record[i].filemtime=s.st_mtime;
	c->record[i].atime=time(NULL);
	c->record[i].flag_delete=0;
	c->record[i].var_list=l;
	c->used_records++;
	return i;
}

inline vlist_t*  GetRecord(const fcache_t* c, const int number){
    return c->record[number].var_list;
}

#define DEFAULT_FCACHE_RECORDS 1024

fcache_t* InitFileCache(void){
/*dump mode - create cache in memory*/
	fcache_t* retval;
	assert(retval=malloc(sizeof(fcache_t)));
	assert(retval->record=malloc(sizeof(fcache_entry_t)*DEFAULT_FCACHE_RECORDS));
	retval->allocated_records=DEFAULT_FCACHE_RECORDS;
	retval->used_records=0;
	retval->fCacheHandle=NULL; /*do not used yet*/
	retval->fCacheName=NULL;
	return retval;
}

int LoadCache(fcache_t* fache, const char* filename, config_t *cfg){
	/*@return value: 0 - ok, -1 - error opening, 1 - unknown format*/
	FILE* f;
	f=fopen(filename,"rb");
	if(!f) return -1;
	return 0;
}

void CloseFileCache(fcache_t* fcache){
	int c;
	for(c=0;c<fcache->used_records;c++){
		DeleteVList(fcache->record[c].var_list);
		free(fcache->record[c].filename);
	}
	free(fcache->record);
	if(fcache->fCacheName) free(fcache->fCacheName);
	if(fcache->fCacheHandle) fclose(fcache->fCacheHandle);
	free(fcache);
}
