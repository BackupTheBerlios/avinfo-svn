/*************************************************************************
 * codec.c codec names support [part of AVInfo 1.x]
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

#include "codec.h"

#ifdef CODEC_C_SIZE

typedef struct{
	FOURCC code;
	const char* name;
}codec_data;

const codec_data codecs[]={
	{85, "mp3"},
	{FCC_DIVX, "DivX"},
	{FCC_DIV3, "DivX3"},
	{FCC_XVID, "XviD"},
	{FCC_OGG, "Vorbis"},
	{FCC_DX50, "DivX5"},
	{FCC_MPG1, "MPEG1"},
	{FCC_MPG2, "MPEG2"}
};

const char* fcctoa (const FOURCC fcc){
/*convert from FourCC to ASCIIZ string
flag values:
0 - video
1 - audio
*/
	int c;
	static char buffer[5];
	for(c=0;c<sizeof(codecs)/sizeof(codec_data);c++){
		if(fcc==codecs[c].code) return codecs[c].name;
	}
	buffer[0]=fcc&0x000000FF;
	buffer[1]=(fcc&0x0000FF00)>>8;
	buffer[2]=(fcc&0x00FF0000)>>16;
	buffer[3]=(fcc&0xFF000000)>>24;
	buffer[4]=0;
	return buffer;
}
#endif
