/*************************************************************************
 * var.h Operations with variables in script language [part of AVInfo 1.x]
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

/*new API*/


/**russian 866 codepage

	Концепция АПИ:

		Все переменные хранятся в массиве с переменным размером,
		все переменные представляют из себя комбинацию строки
		и числа.

		ЕСЛИ СТРОКИ НЕТ, то на её месте хранится NULL




Список ф-ций и типов:


vlist_t - указатель на список. Структура скрыта от внешних ф-ций и не
должна меняться самостоятельно. Функиции самостоятельно обрабатывают содержимое списка.

typedef struct var{
	int number;	//число
	char* string; //строка
}var_t; - переменная смешанного типа. Если string не пустой, то number содержит длину строки.

vlist_t* CreateVList(vlist_t* PrevList);

	@desc: Создаёт новый список, прилинковывает к нему предыдущий
	@param: PrevList - предыдущий список (будет подлинкован в r/o), может быть равен NULL (нет пред. списка)
	@return: указатель на новосозданный список переменных. Должен освобождаться DeleteVList();
	@memleak: use DeleteVList after use.

void DeleteVList(vlist_t* list);

	@desc: Удаляет список и все переменные в нём. Прилинкованные списки не трогает.
	@param: Список для удаления. Переданный указатель особождается и более использоваться не должен
	@return: none
	@memleak: none

int SetVar(vlist_t* list,const char* name,const int nvalue, const char* svalue);

	@desc: Добавляет новую переменную в указанный список. В случае существования переменной с таким же
		именем заменяет. Если переменная существует в прилинкованном списке, она "затеняется" новосозданной
		переменной в списке (для ф-ций GetVar*), переменная в прилинкованном списке не трогается. Если
		у заменяемой переменной было строковое значение, оно free'тися.
	@param:
			name - обязательно валидная строка. Строка копируется, так что можно безопасно использовать 
			строки любого типа (статику, динамику). Не должно быть NULL.
			nvalue - числовое значение переменной. Если svalue ненулевое, nvalue должно содержать длину строки.
			svalue - строковое значение переменной. Может быть NULL. Строка копируется.
	@return: 1 - success, 0 - error.
	@memleak: use DeleteVList


var_t GetROVar(vlist_t* list, const char* name);
		
	@desc: Возвращает значение переменной с указанным именем. 
	@param:
			name - имя переменной. Не должно быть NULL.
	@return: значение переменной. Если переменная содержит строку, то будет возвращена не копия строки,
			а указатель на строку в списке переменных (строковый параметр не следует free'ить ни при каких условиях).
			Может возвращать NULL вместо строки (!)
	@memleak: no

int SetStringVar(vlist_t* list,const char* name,const char* svalue);
	@desc: добавляет (или изменяет) переменную с указанным именем.
		  Строка, переданная в ф-цию копируется.
	@param: 
			name - имя переменной, (не должно быть NULL)
			svalue - строка (не должно быть NULL)
	@return: 1 - success, 0 - error.
	@memleak: use DeleteVList

var_t GetVar(vlist_t* list, const char* name);
	@desc: возвращает копию переменной (строка никогда не бывает NULL).
	@param: name - имя переменной, (не должно быть NULL)
	@return: Копию строки (после использования следует free(var_t.string)),
			пустые строки возвращаются как dup("");
	@memleak: user MUST free (var_t.string);

const char* GetROStringVar(list,name);
	@desc: return a r/o string variable, if no varible or non-numeric value, return "";
	@param name - variable name
	@return string variable or pointer to zero-length string.
	@memleak: NO! do not free returned string


int SetIdxVar(vlist_t *list,const char* name, const int param, const int nvalue, const char* svalue);
	@desc: создаёт (заменяет) переменную по указанному шаблону и параметру.
	@param:
			name - шаблон имени. ДОЛЖЕН содержать ОДИН элемент %d (%x)
			param - число, использующееся вместо %d в name. При не положительных значениях поведение не определено, 
			nvalue, svalue - соответствует описанию SetVar.
	@return: 1 - success, 0 error.
	@warning: очень чувствительна к ошибкам в name.
	@memleak: use DeleteVList

var_t GetIdxROVar(vlist_t* list, const char* name, const int param);
	@desc: Возвращает значение переменной с указанным шаблоном/параметром
	@param:
			name - шаблон имени. ДОЛЖЕН содержать ОДИН элемент %d (%x)
			param - число, использующееся вместо %d в name. При не положительных значениях поведение не определено, 
	@return: Найденую переменную. Если переменная не найдена, возвращает {0,""} (var.string!=NULL)
	@warning: очень чувствительна к ошибкам в name.	
	@memleak: do not free var.string!

void IncStreamCounter( vlist_t* list, int T );
	@desc: увеличивает переменную вида stream.X на единицу, X соответствует букве, переданной в T.
	@param:	T - ASCII код буквы (v - video, a - audio, t - text, d - description)
	@memleak:no

void AddAudioVideo(vlist_t* list, unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE], unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE]);

	@desc: Создаёт переменные указанных типов и заполняет их указанными значениями.
	@param: video - массив описаний видео. Количество строк - MAX_STREAMS
				const char *vids_names[VIDEO_INFO_SIZE]={
					"v!.l",
					"v!.x",
					"v!.y",
					"v!.bits",
					"v!.cc",
					"v!.fpsH",
					"v!.fpsL",
					"v!.bps",
					"v!.bspadd",
					"v!.aspectX",
					"v!.aspectY"
				}
			audio - массив описаний аудио. Количество строк - MAX_STREAMS
				const char *auds_names[AUDIO_INFO_SIZE]={
					"a!.l",
					"a!.bits",
					"a!.cc",
					"a!.bps",
					"a!.bspadd",
					"a!.ch",
					"a!.freq"
	@memleak: no
};


*/

#ifndef _H_VAR_H
#define _H_VAR_H
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "common.h"

typedef struct var{
	int number;
	char* string;
}var_t;

typedef struct vlist_item{
	int number;
	char* string;
	char* name;	/*string name*/
}vlist_item_t;

typedef struct vlist{
	vlist_item_t* data; /*data[512]*/
	int first_free;/*first_free_el*/
	int allocated;
	struct vlist* Next;
}vlist_t;

enum video_enum{
	V_l,
	V_x,
	V_y,
	V_bits,
	V_cc,
	V_fpsH,
	V_fpsL,
	V_bps,
	V_vbr_flag,
	V_aspectX,
	V_aspectY,
	V_exist
}video_enum;

#define VIDEO_INFO_SIZE (V_exist+1)

enum{
	A_l,
	A_bits,
	A_cc,
	A_bps,
	A_vbr_flag,
	A_ch,
	A_freq,
	A_exist
}audio_enum;


#define AUDIO_INFO_SIZE (A_exist+1)
#define MAX_STREAMS 9

#define VARLIST_SIZE 512 /*~10k per array*/


vlist_t* CreateVList(vlist_t* PrevList);
void DeleteVList(vlist_t* list);
int SetVar(vlist_t* list,const char* name,const int nvalue, const char* svalue);
var_t GetROVar(vlist_t* list, const char* name);
var_t GetVar(vlist_t* list, const char* name);
int SetIdxVar(vlist_t *list,const char* name, const int param, const int nvalue, const char* svalue);
var_t GetIdxROVar(vlist_t* list, const char* name, const int param);
void IncStreamCounter( vlist_t* list, int T );
void AddAudioVideo(vlist_t* list, unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE], unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE]);
int SetStringVar(vlist_t* list,const char* name,const char* svalue);
char* GetROStringVar(vlist_t* list,const char* name);
#define SetNumericVar(list,name,nvalue) SetVar(list,name,nvalue,NULL)
#define GetNumericVar(list,name) GetROVar(list,name).number
#define GetStringVar(list,name) strdup(GetROVar(list,name).string)
#define SetIdxNumericVar(list,name,param,nvalue) SetIdxVar(list,name,param,nvalue,NULL)
#define SetIdxStringVar(list,name,param,svalue) SetIdxVar(list,name,param,strlen(svalue),svalue)
#define GetIdxNumericVar(list,name,param) GetIdxROVar(list,name,param).numeric
#define GetIdxROStringVar(list,name,param) GetIdxROVar(list,name,param).string
#define GetIdxStringVar(list,name,param) strdup(GetIdxROVar(list,name,param).string)

void PrintVList(FILE* out,vlist_t* list);
void GetMinMaxVarValueByMaskName(vlist_t* list, char* mask, int *min, int *max);
void AddList(vlist_t* to, vlist_t* newlist);
void ViewAllLists(vlist_t* start);
void AddDate(vlist_t* list, char* prefix,time_t UnixTime);
#endif
