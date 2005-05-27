#ifndef _H_SCAN_H
#define _H_SCAN_H
#include "config.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
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
	int mode;
	FILE* filelisthandle;
	DIR* dirhandle;
}filelist_t;

typedef int (*modulefunc) (vlist_t* list, FILE* file, int flags ); 

typedef struct{
	char* mask; /*mask of supported files*/
	int ver;
	modulefunc func;
}module_t;

fcache_t* scan(config_t* cfg);

enum{
	FL_ERROR=0,
	FL_STDIN,
	FL_FILE,
	FL_DIR
};/*name for filelist modes*/

#endif
