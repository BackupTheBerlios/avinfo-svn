/*************************************************************************
 * codec.h header file for codec.c [part of AVInfo 1.x]
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
#ifndef _H_CODEC_H
#define _H_CODEC_H
#include "config.h"
#include "wintypes.h"

#define CODEC_C_SIZE 1
/* use CODEC_C_SIZE to set a number of avaible (build-in) codecs name.
possible values:
(not defined) - do not use a codec detection
1 basic set of codec (DivX/XVID/vp6/mp3, etc)
2 MAX BASE SIZE (full content of http://fourcc.org/ codecs table)
*/

#ifndef CODEC_C_SIZE
	#define fcctoa(a) ""
#endif

#ifdef CODEC_C_SIZE
	extern const char* fcctoa (const FOURCC fcc);
#endif

#define FCC_MPG1 0x3147504D
#define FCC_MPG2 0x3247504D
#define FCC_AC3  0x20334341
#define FCC_DTS  0x20535444
#define FCC_LPCM	0x4C4D4350
#define FCC_OGG	0x2047474F

enum{/*TODO!!!*/
	FCC_DIV3=861292868,
	FCC_DIVX=1482049860,
	FCC_XVID=1145656920,
	FCC_DX50=808802372
};
#endif
