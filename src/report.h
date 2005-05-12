/*************************************************************************
 * report.h header for report.c [part of AVInfo 1.x]
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
#ifndef _H_REPORT_H
#define _H_REPORT_H
#include "config.h"
#include <time.h>
#include "var.h"
#include "print.h"
#include "ass.h"
#include "filecach.h"
#include "confset.h"
#include "statisti.h"
vlist_t* GatherStatistic(fcache_t* fcache, config_t *cfg);
#endif
