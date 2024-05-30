//
//  GenTextOut.h
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// Purpose: 
// Headerfile for GenTextOut.cpp
//

#ifndef _GENTEXTOUT

#include <usp10.h>

// typedefs of Uniscribe function pointers
typedef HRESULT (WINAPI *PFNSCRIPTSTRINGANALYSE) (  
        HDC            ,
        const void *   ,
        int            ,
        int            ,
        int            ,
        DWORD          ,
        int            ,
        SCRIPT_CONTROL *,
        SCRIPT_STATE * ,
        const int *    ,
        SCRIPT_TABDEF *,
        const BYTE *   ,
        SCRIPT_STRING_ANALYSIS * ) ;

typedef HRESULT (WINAPI *PFNSCRIPTSTRINGOUT)(  
        SCRIPT_STRING_ANALYSIS ,
        int                    ,
        int                    ,
        UINT                   ,
        const RECT *           ,
        int                    ,
        int                    ,
        BOOL) ;

typedef HRESULT (WINAPI *PFNSCRIPTSTRINGFREE) (SCRIPT_STRING_ANALYSIS * ) ; 

typedef BOOL  (WINAPI *PFNGENERICTEXTOUT)(HDC, int, int, UINT, CONST RECT *,LPCWSTR, UINT, CONST INT *) ;

#define _GENTEXTOUT
#endif
