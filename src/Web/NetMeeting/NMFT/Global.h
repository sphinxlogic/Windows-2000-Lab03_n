//****************************************************************************
//  Module:     NMFT.EXE
//  File:       GLOBAL.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H


//-------------------------------------------------------
// Useful macros

#define ClearBytes(lpv, cb)		ZeroMemory((LPVOID) (lpv), (cb))
#define ClearStruct(lpv)		ZeroMemory((LPVOID) (lpv), sizeof(*(lpv)))
#define InitStruct(lpv)        {ClearStruct(lpv); (* (LPDWORD) lpv) = sizeof(*(lpv));}
#define CopyStruct(pDest, pSrc)  CopyMemory(pDest, pSrc, sizeof(*(pDest)))

#define SetEmptySz(sz)			( *(sz) = _T('\0') )
#define FEmptySz(sz)            (((sz) == NULL) || (*(sz) == _T('\0')))

#define ARRAY_ELEMENTS(rg)      (sizeof(rg) / sizeof(rg[0]))
#define CCHMAX(sz)              (sizeof(sz) / sizeof(TCHAR))




#ifdef DEBUG
VOID FAR PASCAL AssertProc(LPTSTR lpszMsg, LPTSTR lpszAssert, LPTSTR lpszFile, UINT line);

#define DEBASSERT(exp,szMsg)  \
	if (!(exp))                                                      \
	{                                                                \
		static char _szAssert[] = #exp ;   \
		static char _szMsg[]    = szMsg;   \
		AssertProc(_szMsg,_szAssert,__FILE__,__LINE__); \
	}

#define ASSERT(f)       DEBASSERT(f, "(" #f ")")
#define AssertSz(f,sz)  DEBASSERT(f, sz)
#define NotReached()    DEBASSERT(FALSE, "NotReached declaration was reached!")
#else
#define ASSERT(f)
#define AssertSz(f, sz)
#define NotReached()
#endif



//****************************************************************************
//
// Global Function Prototypes.
//
//****************************************************************************

// from msg.cpp
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID CmdClose(void);

// from util.cpp
BOOL FGetFileName(LPTSTR szFileName);
BOOL FFileExists(LPCTSTR szFile);
LPVOID LpvAlloc(int cb);
LPTSTR PszAlloc(int cch);
VOID FreePlpv(LPVOID plpv);
LPCTSTR StrChr(LPCTSTR pcsz, TCHAR ch);


//****************************************************************************
//
// Global variables.
//
//****************************************************************************

extern HINSTANCE ghInst;          // The current instance handle
extern HWND   ghwndMain;          // Main Window
extern const GUID g_guidApp;      // Our NmFt Guid
extern TCHAR  g_szFile[MAX_PATH]; //
extern BOOL   g_fQuiet;           // if TRUE, no progress dialog

#endif /* GLOBAL_H */
