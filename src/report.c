/*************************************************************************
 * report.c Generating reports & statistic [part of AVInfo 1.x]
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
#include "report.h"
#include "memleak.h"

void ParseTemplate(FILE* output, char* template, int linelength, vlist_t* list){
	lexerctl_t  lexerctl;
	lexerctl.l=InitLineCache(output,linelength,1);
	lexerctl.line=template;	
	lexerctl.c=0;
	lexerctl.flag=0;
	lexerctl.active=1;
	lexerctl.mode=0;
	lexerctl.list=list;
	yyparse( &lexerctl );
	CloseLineCache(lexerctl.l);
}

void report(fcache_t* fcache, FILE* output, config_t* cfg){
	
	int c;
	vlist_t* FileStatistic=GatherStatistic(fcache,cfg);
	cfg->reportbegin=time(NULL);
	SetNumericVar(FileStatistic,"run.scan.time",cfg->reportbegin - cfg->scanbegin);
	if(!cfg->falltobuiltintemplate){ /*print head*/
		ParseTemplate(output,cfg->template->content[0].text,cfg->template->content[0].textlinesize,FileStatistic);
	}
	for (c=0;c<fcache->used_records;c++){/*print body for each entry*/
		if(!cfg->falltobuiltintemplate) {
			AddList(fcache->record[c].var_list,FileStatistic);
			SetNumericVar(fcache->record[c].var_list,"counter",c);
			ParseTemplate(output,cfg->template->content[1].text, cfg->template->content[1].textlinesize,fcache->record[c].var_list);
		}
	    else 
			PrintVList(output,fcache->record[c].var_list);
	}
	cfg->timeend=time(NULL);
	if(!cfg->falltobuiltintemplate){	/*print foot*/
		SetNumericVar(FileStatistic,"run.report.time",cfg->timeend-cfg->reportbegin);
		ParseTemplate(output,cfg->template->content[2].text,cfg->template->content[2].textlinesize,FileStatistic);
	}
	if(FileStatistic) DeleteVList(FileStatistic);
}

