/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */

#if !defined(_DEBUG_API_)
#define _DEBUG_API_
#include <tchar.h>
#include <crtdbg.h>
#include <malloc.h>
#if defined(__cplusplus)
extern "C" {
#endif 



#define CHAR_CONVERSION static int _convert = 0
LPSTR WINAPI UniCode2Ansi(LPSTR lpa, LPCWSTR lpw, int nChars);
LPWSTR WINAPI Ansi2Unicode(LPWSTR lpw, LPCSTR lpa, int nChars);

#define A2W(lpa) (\
	((LPCSTR)lpa == NULL) ? NULL : (\
	_convert = (lstrlenA(lpa)+1),\
	Ansi2Unicode((LPWSTR) _alloca(_convert*2), lpa, _convert)))

#define W2A(lpw) (\
	((LPCWSTR)lpw == NULL) ? NULL : (\
		_convert = (lstrlenW(lpw)+1),\
		UniCode2Ansi((LPSTR) _alloca(_convert), lpw, _convert)))


#if defined(_DEBUG)
void _cdecl DebugTrace(LPCTSTR lpszFormat, ...);
#define DEBUGTRACE		DebugTrace
#define CHECKPOINTER(p) if (!(p)) return E_POINTER
#define RELEASEINTERFACE(p) do {(p)->Release(); (p) = NULL;} while(0)
#else  // !_DEBUG
__inline void DebugTrace(){}
//#define DEBUGTRACE            1 ? (void)0 : DebugTrace
#define DEBUGTRACE            1 ? (void)0 : (void)0
#define CHECKPOINTER(p) (void)0
#define RELEASEINTERFACE(p) (p)->Release()
#endif //_DEBUG
#if defined(__cplusplus)
}
#endif
#endif //_DEBUG_API_


