/*************************************************************************
 * mkv.h - header for mkv.c [part of AVInfo 1.x]
 *
 * Copyright (c) 2004 George Shuklin
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

#ifndef _H_MKV_H
#define _H_MKV_H

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codec.h"
#include "var.h"
#include "common.h"

typedef long long int64;
extern int mkvparse(vlist_t*list,FILE* file, int s);

enum{
MKV_Track_video=1,
MKV_Track_audio=2,
MKV_Track_subtitle=3,
MKV_Track_subtitle_orig=0x11
};
enum{
MKVID_OutputSamplingFrequency=0x78B5,
MKVID_FILE_BEGIN=0x1A,
MKVID_EBML=0x1A45DFA3,
MKVID_Segment=0x18538067,
MKVID_Info=0x1549A966,
MKVID_Tracks=0x1654AE6B,
MKVID_TrackEntry=0xAE,
MKVID_TrackType=0x83,
MKVID_DefaultDuration=0x23E383,
MKVID_Language=0x22B59C,
MKVID_CodecID=0x86,
MKVID_CodecPrivate=0x63A2,
MKVID_PixelWidth=0xB0,
MKVID_PixelHeight=0xBA,
MKVID_TimeCodeScale=0x2AD7B1,
MKVID_Duration=0x4489,
MKVID_Channels=0x9F,
MKVID_BitDepth=0x6264,
MKVID_SamplingFrequency=0xB5,
MKVID_Title=0x7BA9,
MKVID_Tags=0x1254C367,
MKVID_SeekHead=0x114D9B74,
MKVID_Video=0xE0,
MKVID_Audio=0xE1,
MKVID_CodecName=0x258688,
MKVID_DisplayHeight=0x54BA,
MKVID_DisplayWidth=0x54B0
};

#endif
