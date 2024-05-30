//
// UPDTLANG.H
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// Purpose: 
// Header file for UpdateLang.cpp
//

#ifndef _UPDTLANG

// Constants
#define MAX_LOADSTRING  200
#define BUFFER_SIZE     200
#define MAX_NAME        100
#define LARGEBUFFER     1000

// GDI defines for RTL mirroring standard windows 
#ifndef LAYOUT_RTL

#define LAYOUT_RTL                         0x00000001 // Right to left
#define LAYOUT_BTT                         0x00000002 // Bottom to top, not currently used
#define LAYOUT_VBH                         0x00000004 // Vertical before horizontal
#define LAYOUT_ORIENTATIONMASK             (LAYOUT_RTL | LAYOUT_BTT | LAYOUT_VBH)
#define LAYOUT_BITMAPORIENTATIONPRESERVED  0x00000008

#endif /* #ifndef LAYOUT_RTL */

// USER defines for RTL mirroring standard windows
#ifndef WS_EX_LAYOUTRTL

#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#define WS_EX_LAYOUTRTL         0x00400000L  // Right to left mirroring

#endif /* #ifndef WS_EX_LAYOUTRTL */

// Structure to store language/locale state
typedef struct tagLangState {
    UINT        InputCodePage ;
    BOOL        IsRTLLayout   ;
    LANGID      UILang        ;
    HMENU       hMenu         ;
    HMODULE     hMResource    ;
    HACCEL      hAccelTable   ;
} LANGSTATE, *PLANGSTATE ;

#ifndef MIN
#define MIN(_aa, _bb) ((_aa) < (_bb) ? (_aa) : (_bb))
#endif

// Functions provided in this module
BOOL    InitUILang(HINSTANCE hInstance , PLANGSTATE pLState) ;
BOOL    UpdateUILang(HINSTANCE , LANGID, PLANGSTATE)         ;
UINT    LangToCodePage(IN LANGID wLangID)                  ;
BOOL    FindResourceDirectory (HINSTANCE , LPWSTR )        ;
HMODULE GetResourceModule     (HINSTANCE , LCID   )        ;
int     RcMessageBox (HWND , PLANGSTATE, int nMessageID, int nOptions, ...) ;

#define FALLBACK_UI_LANG MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)
#define ILLEGAL_LANGID 0xFFFF

#define _UPDTLANG
#endif /* _UPDTLANG */