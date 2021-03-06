/*************************************************************************
 * avinfo.c module selection and startup code [part of AVInfo 1.x]
 *
 * Copyright (c) 2003-2005 George Shuklin
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
#include "avinfo.h"
#include "memleak.h"

int main( int argc, char* argv[] ){
    config_t *cfg;
	fcache_t *fcache;
	FILE* output;

	cfg=Configure(argc,argv);
	if(!cfg) return -1; /*if no filename or filelist*/
	fcache=scan(cfg);
	if(!fcache) return 1;

	if(cfg->outputfilename){
		if(cfg->outputfilename[0]=='-'&&cfg->outputfilename[1]==0) output=stdout;
		else{
			output=fopen(cfg->outputfilename,cfg->appendFlag?"a":"w");
			if(!output){
				fprintf(stderr,"error opening output file %s\n",cfg->outputfilename);
				return 1;
			}
		
		}
	}else output=stdout;
	report(fcache,output,cfg);
	CloseFileCache(fcache);
	CloseConfig(cfg);
	if(output!=stdout) fclose(output);
	return 0;
}
