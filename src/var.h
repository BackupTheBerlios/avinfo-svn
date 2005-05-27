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

	���楯�� ���:

		�� ��६���� �࠭���� � ���ᨢ� � ��६���� ࠧ��஬,
		�� ��६���� �।�⠢���� �� ᥡ� ��������� ��ப�
		� �᫠.

		���� ������ ���, � �� �� ���� �࠭���� NULL




���᮪ �-権 � ⨯��:


vlist_t - 㪠��⥫� �� ᯨ᮪. ������� ���� �� ���譨� �-権 � ��
������ �������� ᠬ����⥫쭮. �㭪�樨 ᠬ����⥫쭮 ��ࠡ��뢠�� ᮤ�ন��� ᯨ᪠.

typedef struct var{
	int number;	//�᫮
	char* string; //��ப�
}var_t; - ��६����� ᬥ蠭���� ⨯�. �᫨ string �� ���⮩, � number ᮤ�ন� ����� ��ப�.

vlist_t* CreateVList(vlist_t* PrevList);

	@desc: ������� ���� ᯨ᮪, �ਫ�����뢠�� � ���� �।��騩
	@param: PrevList - �।��騩 ᯨ᮪ (�㤥� ����������� � r/o), ����� ���� ࠢ�� NULL (��� �।. ᯨ᪠)
	@return: 㪠��⥫� �� ����ᮧ����� ᯨ᮪ ��६�����. ������ �᢮��������� DeleteVList();
	@memleak: use DeleteVList after use.

void DeleteVList(vlist_t* list);

	@desc: ������ ᯨ᮪ � �� ��६���� � ��. �ਫ��������� ᯨ᪨ �� �ண���.
	@param: ���᮪ ��� 㤠�����. ��।���� 㪠��⥫� �ᮡ�������� � ����� �ᯮ�짮������ �� ������
	@return: none
	@memleak: none

int SetVar(vlist_t* list,const char* name,const int nvalue, const char* svalue);

	@desc: �������� ����� ��६����� � 㪠����� ᯨ᮪. � ��砥 ����⢮����� ��६����� � ⠪�� ��
		������ �������. �᫨ ��६����� ������� � �ਫ���������� ᯨ᪥, ��� "��⥭����" ����ᮧ������
		��६����� � ᯨ᪥ (��� �-権 GetVar*), ��६����� � �ਫ���������� ᯨ᪥ �� �ண�����. �᫨
		� �����塞�� ��६����� �뫮 ��ப���� ���祭��, ��� free'���.
	@param:
			name - ��易⥫쭮 �������� ��ப�. ��ப� ���������, ⠪ �� ����� ������᭮ �ᯮ�짮���� 
			��ப� ��� ⨯� (��⨪�, ��������). �� ������ ���� NULL.
			nvalue - �᫮��� ���祭�� ��६�����. �᫨ svalue ���㫥���, nvalue ������ ᮤ�ঠ�� ����� ��ப�.
			svalue - ��ப���� ���祭�� ��६�����. ����� ���� NULL. ��ப� ���������.
	@return: 1 - success, 0 - error.
	@memleak: use DeleteVList


var_t GetROVar(vlist_t* list, const char* name);
		
	@desc: �����頥� ���祭�� ��६����� � 㪠����� ������. 
	@param:
			name - ��� ��६�����. �� ������ ���� NULL.
	@return: ���祭�� ��६�����. �᫨ ��६����� ᮤ�ন� ��ப�, � �㤥� �����饭� �� ����� ��ப�,
			� 㪠��⥫� �� ��ப� � ᯨ᪥ ��६����� (��ப��� ��ࠬ��� �� ᫥��� free'��� �� �� ����� �᫮����).
			����� �������� NULL ����� ��ப� (!)
	@memleak: no

int SetStringVar(vlist_t* list,const char* name,const char* svalue);
	@desc: �������� (��� �������) ��६����� � 㪠����� ������.
		  ��ப�, ��।����� � �-�� ���������.
	@param: 
			name - ��� ��६�����, (�� ������ ���� NULL)
			svalue - ��ப� (�� ������ ���� NULL)
	@return: 1 - success, 0 - error.
	@memleak: use DeleteVList

var_t GetVar(vlist_t* list, const char* name);
	@desc: �����頥� ����� ��६����� (��ப� ������� �� �뢠�� NULL).
	@param: name - ��� ��६�����, (�� ������ ���� NULL)
	@return: ����� ��ப� (��᫥ �ᯮ�짮����� ᫥��� free(var_t.string)),
			����� ��ப� ���������� ��� dup("");
	@memleak: user MUST free (var_t.string);

const char* GetROStringVar(list,name);
	@desc: return a r/o string variable, if no varible or non-numeric value, return "";
	@param name - variable name
	@return string variable or pointer to zero-length string.
	@memleak: NO! do not free returned string


int SetIdxVar(vlist_t *list,const char* name, const int param, const int nvalue, const char* svalue);
	@desc: ᮧ���� (�������) ��६����� �� 㪠������� 蠡���� � ��ࠬ����.
	@param:
			name - 蠡��� �����. ������ ᮤ�ঠ�� ���� ����� %d (%x)
			param - �᫮, �ᯮ����饥�� ����� %d � name. �� �� ������⥫��� ���祭��� ��������� �� ��।�����, 
			nvalue, svalue - ᮮ⢥����� ���ᠭ�� SetVar.
	@return: 1 - success, 0 error.
	@warning: �祭� ���⢨⥫쭠 � �訡��� � name.
	@memleak: use DeleteVList

var_t GetIdxROVar(vlist_t* list, const char* name, const int param);
	@desc: �����頥� ���祭�� ��६����� � 㪠����� 蠡�����/��ࠬ��஬
	@param:
			name - 蠡��� �����. ������ ᮤ�ঠ�� ���� ����� %d (%x)
			param - �᫮, �ᯮ����饥�� ����� %d � name. �� �� ������⥫��� ���祭��� ��������� �� ��।�����, 
	@return: �������� ��६�����. �᫨ ��६����� �� �������, �����頥� {0,""} (var.string!=NULL)
	@warning: �祭� ���⢨⥫쭠 � �訡��� � name.	
	@memleak: do not free var.string!

void IncStreamCounter( vlist_t* list, int T );
	@desc: 㢥��稢��� ��६����� ���� stream.X �� �������, X ᮮ⢥����� �㪢�, ��।����� � T.
	@param:	T - ASCII ��� �㪢� (v - video, a - audio, t - text, d - description)
	@memleak:no

void AddAudioVideo(vlist_t* list, unsigned int video[MAX_STREAMS][VIDEO_INFO_SIZE], unsigned int audio[MAX_STREAMS][AUDIO_INFO_SIZE]);

	@desc: ������� ��६���� 㪠������ ⨯�� � �������� �� 㪠����묨 ���祭�ﬨ.
	@param: video - ���ᨢ ���ᠭ�� �����. ������⢮ ��ப - MAX_STREAMS
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
			audio - ���ᨢ ���ᠭ�� �㤨�. ������⢮ ��ப - MAX_STREAMS
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
