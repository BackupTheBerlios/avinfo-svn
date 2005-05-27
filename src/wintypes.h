/* no copyrights :-P*/
#ifndef _H_WINTYPES_H
#define _H_WINTYPES_H

#ifdef WINDOWS
	#include <windows.h>
#endif
#ifndef WINDOWS
	typedef 	unsigned int 		DWORD;
	typedef 	DWORD 				FOURCC;
	typedef 	unsigned short int 	WORD;
	typedef 	signed int 			LONG;
#endif

#endif
