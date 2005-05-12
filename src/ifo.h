#ifndef _H_IFO_H
#define _H_IFO_H
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ver.h"
#include "common.h"
#include "var.h"
#include "codec.h"
extern int ifoparse(vlist_t*list,FILE* file, int s);
#endif
