/*************************************************************************
 * riff.h header file for riff.c [part of AVInfo 1.x]
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
#ifndef _H_AVI_H
#define _H_AVI_H
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ver.h"
#include "common.h"
#include "var.h"
#include "codec.h"

#define AVI_FPS_NUMBERS 100
/*100 for 2 digits, 1000 for 3, etc*/

#define AVI_MAX_STREAMS 9
enum{
	FOURCC_RIFF=0x46464952,
	FOURCC_AVI =0x20495641,
	FOURCC_LIST=0x5453494C,
	FOURCC_hdrl=0x6C726468,
	FOURCC_avih=0x68697661,
	FOURCC_strl=0x6C727473,
	FOURCC_strh=0x68727473,
	FOURCC_strf=0x66727473,
	FOURCC_STRD=0x64727473,
	FOURCC_vids=0x73646976,
	FOURCC_auds=0x73647561,
	FOURCC_INFO=0x4F464E49,
	FOURCC_idx1=0x31786469,
	FOURCC_movi=0x69766F6D,
	FOURCC_JUNK=0x4B4E554A,
	FOURCC_PAD =0x20444150,
	FOURCC_fmt =0x20746D66,  /*for WAVE files*/
	FOURCC_data=0x61746164,  /*for WAVE files*/
	FOURCC_WAVE=0x45564157	 /*for WAVE files*/
};



extern int riffparse(vlist_t* list, FILE* file, int s);
#define AVIIF_KEYFRAME	0x00000010L /*avi idx1 keyframe flag*/
#define AVIIF_LIST	0x00000001L

#endif
