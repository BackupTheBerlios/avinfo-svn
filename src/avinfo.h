/*************************************************************************
 * avinfo.h basic defenition for AVInfo [part of AVInfo 1.x]
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
#ifndef _H_AVINFO_H
#define _H_AVINFO_H


#define MAX_STREAMS 9

#include "config.h"
#include "ver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "var.h"
#include "common.h"
#include "print.h"
#include "confset.h"
#include "filecach.h"
#include "scan.h"
#include "report.h"
#include "wintypes.h"
#include "riff.h"
#include "mpeg.h"
#include "text.h"
#include "ifo.h"
#include "ogm.h"
#include "mkv.h"
#include "codec.h"
#include "ass.h"



#ifndef MAX_PATH 
	#define MAX_PATH 32767
#endif

#endif
