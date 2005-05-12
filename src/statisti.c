/*************************************************************************
 * statisti.c Gathering statistic [part of AVInfo 1.x]
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
#include "statisti.h"


typedef struct{
	char* searchName;
	char* resultName;
}minmax_t;

minmax_t minmax[]={
	{"v#.x","x"},
	{"v#.y","y"},
	{"v#.fpsH","fps"},
	{"v#.bps","vidbps"},
	{"a#.freq","freq"},
	{"a#.bps","audbps"},
	{"stream.v","vidstream"},
	{"stream.a","audstream"},
	{"stream.t","textstream"},
	{"stream.d","descstream"}
};
#define MINMAXC (sizeof(minmax)/sizeof(minmax[0]))


vlist_t* GatherStatistic(fcache_t* fcache, config_t *cfg){
	/**
		collecting data:
			minimal and maximal values of resolution, bitrate, fps, sound freq.
			summ of length of movies.
			total size of files
			maximal length of filename
			maximal number of video, audio, text and description streams
			number of errors variable (number of error, while scan)
			
			TODO: list of used codecs, languages...
	**/
	vlist_t* retval=CreateVList(cfg->base);
	int minv[MINMAXC];
	int maxv[MINMAXC];
	int currentMin=0;
	int currentMax=0;
	int fileCounter=0;
	int fileCommonSize=0; /*we are calculating in 10KB, e.g. max 20Tb... Bug, I know about it, but untill full support for int64, keep this ***TODO*** */
	int fileCommonLength=0; /*in sec, 31bit let us to keep about  1634 years (1^31sec) of movies. I'm hope it's enough*/
	int minFileNameLen=0;
	int maxFileNameLen=0;
	int tempLen;
	#define GathStatBUFFSIZE 128
	char buffer[GathStatBUFFSIZE];
	int c,i;
	memset(maxv,0,MINMAXC*sizeof(int));
	memset(minv,0,MINMAXC*sizeof(int));
	assert(retval);
	*buffer=0;
	for(c=0;c<fcache->used_records;c++){  /*gathering statistic*/
		for(i=0;i<MINMAXC;i++){ /* min & max values for file*/
			GetMinMaxVarValueByMaskName(fcache->record[c].var_list,minmax[i].searchName,&currentMin,&currentMax);
			if(currentMin!=0&&(currentMin<minv[i]||!minv[i])) minv[i]=currentMin;
			if(currentMax>maxv[i])maxv[i]=currentMax;
		}
		fileCounter++;
		fileCommonSize+=(GetNumericVar(fcache->record[c].var_list,"size")/1024); /* in Kb (!!!) TODO */
		tempLen=GetNumericVar(fcache->record[c].var_list,"v1.l");
		if(!tempLen) tempLen=GetNumericVar(fcache->record[c].var_list,"a1.l");
		fileCommonLength+=tempLen;
		tempLen=strlen(GetStringVar(fcache->record[c].var_list,"name"));
		if(tempLen>maxFileNameLen) maxFileNameLen=tempLen;
		if(!minFileNameLen||minFileNameLen>tempLen) minFileNameLen=tempLen;		
	}
	/*setup stat.* hierarchy*/
	for(i=0;i<MINMAXC;i++){
		snprintf(buffer,GathStatBUFFSIZE-1,"stat.min.%s",minmax[i].resultName);
		SetNumericVar(retval,buffer,minv[i]);
		snprintf(buffer,GathStatBUFFSIZE-1,"stat.max.%s",minmax[i].resultName);	
		SetNumericVar(retval,buffer,maxv[i]);		
	}
	SetNumericVar(retval,"stat.total.files",fileCounter);
	SetNumericVar(retval,"stat.total.size",fileCommonSize/1024);/*kb->Mb*/
	SetNumericVar(retval,"stat.total.length",fileCommonLength);
	SetNumericVar(retval,"stat.max.name",maxFileNameLen);
	SetNumericVar(retval,"stat.min.name",minFileNameLen);
	if(cfg->title) SetStringVar(retval,"title",cfg->title);
	return retval;
}
