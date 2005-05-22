#ifndef _H_SCAN_H
#define _H_SCAN_H
#include "config.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "var.h"
#include "confset.h"
#include "filecach.h"
#include "wintypes.h"
#include "riff.h"
#include "mpeg.h"
#include "text.h"
#include "ifo.h"
#include "ogm.h"
#include "mkv.h"
#include "codec.h"

typedef struct{ 
	char* filelistname; 
	int mode;/*for future use*/
	FILE* filelisthandle;
}filelist_t;

typedef int (*modulefunc) (vlist_t* list, FILE* file, int flags ); 

typedef struct{
	char* mask; /*mask of supported files*/
	int ver;
	modulefunc func;
}module_t;

fcache_t* scan(config_t* cfg);

#endif
