/*************************************************************************
 * filecach.h header for filecach.c [part of AVInfo 1.x]
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
#ifndef _H_FILECACH_H
#define _H_FILECACH_H

#include "config.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "var.h"
#include "time.h"
#include "common.h"
#include "confset.h"

typedef struct{
	char* filename; /*name of file (without path)*/
	off_t  filesize; /*int64 is OK?*/
	time_t filemtime; /*modification time*/
	time_t atime; /*if record adds a first time filling by current date, else used value from cachefile*/
	int flag_newfile;/*file has been added*/
	int flag_found; /*file has been found (counter for cach dups and records about deleted files)*/
	int flag_delete;/*do not save to cache - setup by external function by user command line switches */
	vlist_t *var_list; /*description of file in vlist_t format (see var.c for detail)*/
}fcache_entry_t;

typedef struct{
	char* fCacheName; /*file name of the cache*/
	FILE* fCacheHandle;/*cache handle, lock while working by fopen(..,"a");*/
	int allocated_records; /*number of RECORDS (NOT A BYTES!)*/
	int used_records;/*used records number, must be <allocated_records*/
	fcache_entry_t *record; /*fcache content, record[allocated_records*/
}fcache_t;

/** External API **/
fcache_t* ReadFileCache(const char* fCacheName, const int flags);
fcache_t* InitFileCache(void);
int SaveFileCache(fcache_t* fcache);
int CacheCheck (const fcache_t *c, const char* filename);
int AddRecord(fcache_t* c,const char* name, vlist_t *l);
inline vlist_t* GetRecord(const fcache_t* c, const int number);

void CloseFileCache(fcache_t* fcache);

/** Internal Function (invisible outsize module) **/

char* CopyStripName(const char* name);

#endif
