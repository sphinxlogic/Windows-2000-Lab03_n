//
// GenTextOut.cpp
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// Purpose:
// Implements a generic Text Out function, pfnGenericTextOut. It uses Uniscribe if 
// available, or ExtTextOut otherwise. Use pfnGenericTextOut exactly like ExtTextOut.
//

/* 
   You can use pfnGenericTextOut in a Win32 application by  
   including the following lines near the top of the C source file:

#include "GenTextOut.h"
extern PFNGENERICTEXTOUT pfnGenericTextOut ;
*/

#include <windows.h>
#include "gentextout.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Initialization function
BOOL WINAPI GenTextOutInit(HDC hdc, int x, int y, UINT fuOptions, CONST RECT *lprc,
                      LPCWSTR lpString, UINT cbCount, const int *lpdx) ;

PFNGENERICTEXTOUT pfnGenericTextOut = GenTextOutInit ; // Set to initialization function

HRESULT WINAPI ScriptStringInit(  // Initialization routine for Uniscribe functions
    HDC             ,
    const void *    ,
    int             ,
    int             ,
    int             ,
    DWORD           ,
    int             ,
    SCRIPT_CONTROL *,
    SCRIPT_STATE *  ,
    const int *     ,
    SCRIPT_TABDEF * ,
    const BYTE *    ,
    SCRIPT_STRING_ANALYSIS *) ;

// Function pointers that are set to the corresponding Uniscribe function, if 
// available. The PFN datatypes are typdef'ed in GENTEXTOUT.H
PFNSCRIPTSTRINGANALYSE pfnScriptStringAnalyse // Set to initialization function
            = (PFNSCRIPTSTRINGANALYSE) ScriptStringInit ;
PFNSCRIPTSTRINGOUT     pfnScriptStringOut     = NULL ;
PFNSCRIPTSTRINGFREE    pfnScriptStringFree    = NULL ;

//
//  FUNCTION: HRESULT ScriptStringInit
//
//  PURPOSE:  Initialize ScriptString* function pointers. 
//
//  COMMENTS: 
//        The function pointer pfnScriptStringAnalyze is initially set to point to this
//        function, so that the first time it is called this function will load USP10.DLL
//        and set all three function pointers to the appropriate addresses. If that
//        completes successfully, it calls ScriptStringAnalyze with the parameters passed
//        in.
// 
HRESULT WINAPI ScriptStringInit(
    HDC                      hdc,       //In  Device context (required)
    const void              *pString,   //In  String in 8 or 16 bit characters
    int                      cString,   //In  Length in characters (Must be at least 1)
    int                      cGlyphs,   //In  Required glyph buffer size (default cString*3/2 + 1)
    int                      iCharset,  //In  Charset if an ANSI string, -1 for a Unicode string
    DWORD                    dwFlags,   //In  Analysis required
    int                      iReqWidth, //In  Required width for fit and/or clip
    SCRIPT_CONTROL          *psControl, //In  Analysis control (optional)
    SCRIPT_STATE            *psState,   //In  Analysis initial state (optional)
    const int               *piDx,      //In  Requested logical dx array
    SCRIPT_TABDEF           *pTabdef,   //In  Tab positions (optional)
    const BYTE              *pbInClass, //In  Legacy GetCharacterPlacement character classifications (deprecated)
    SCRIPT_STRING_ANALYSIS  *pssa)     //Out Analysis of string
{
    HMODULE hMUniscribe = LoadLibraryExA("USP10.DLL", NULL, 0 ) ;

    if(hMUniscribe &&  // Set function pointers to Uniscribe function, test for success
        (pfnScriptStringOut 
           = (PFNSCRIPTSTRINGOUT)     GetProcAddress(hMUniscribe, "ScriptStringOut"))
        &&
        (pfnScriptStringAnalyse 
           = (PFNSCRIPTSTRINGANALYSE) GetProcAddress(hMUniscribe, "ScriptStringAnalyse"))
        &&
        (pfnScriptStringFree 
           = (PFNSCRIPTSTRINGFREE)    GetProcAddress(hMUniscribe, "ScriptStringFree"))
    )
    {
        // Found Uniscribe, use it hereafter
        return pfnScriptStringAnalyse(
            hdc, pString, cString, cGlyphs, iCharset, dwFlags, iReqWidth, psControl,
                psState, piDx, pTabdef, pbInClass, pssa) ;
    }

    return E_NOTIMPL ;
}

//
//  FUNCTION:  BOOL UniscribeTextOut
//
//  PURPOSE:   Analogous to ExtTextOut, but uses the Uniscribe plaintext (ScriptString) functions
//             to provide Unicode display on all Windows 9x and Windows NT 4.0+ platforms.
//
//  COMMENTS:  See the CSSAMP sample for more a more detailed example of the use of Uniscribe
// 
BOOL WINAPI UniscribeTextOut(HDC hdc, int x, int y, UINT fuOptions, CONST RECT *lprt,
                      LPCWSTR lpString, UINT cbCount, const int *lpdx) 
{
    SCRIPT_STRING_ANALYSIS Ssa ;
    HRESULT hr                 ;

    DWORD dwFlags = SSA_GLYPHS | SSA_FALLBACK ;

    if (GetTextAlign(hdc) & TA_RTLREADING) 
    {
        dwFlags |= SSA_RTL ;
    } 

    // Perform initial BiDi and contextual analysis for complex scripts such as Arabic 
    // and Devanagari
    hr = pfnScriptStringAnalyse( 
            hdc          ,
            lpString     ,
            cbCount      ,
            cbCount*3/2+16, // Estimated worst case buffer size (theoretically could be worse)
            -1           ,
            dwFlags      ,
            0            ,
            NULL, NULL, NULL, NULL, NULL, &Ssa) ;


    // Display the text in the given device context
    if(SUCCEEDED(hr)) 
    {
        hr = pfnScriptStringOut(
                Ssa      ,
                x        , 
                y        , 
                fuOptions,
                lprt     ,
                0,0, FALSE ) ;

        // Free memory allocated by SSA
        pfnScriptStringFree(&Ssa) ;
    }

    if(SUCCEEDED(hr)) 
    {
        return TRUE ;
    }

    return FALSE ;
}

//
//  FUNCTION: HRESULT GenTextOutInit
//
//  PURPOSE:  Initialize pfnGenericTextOut function pointer. 
//
//  COMMENTS: 
//        The function pointer pfnGenericTextOut is initially set to point to this
//        function, so that the first time it is called this function will reroute it
//        to UniscribeTextOut and call that entry point. If that call fails, it uses
//        ExtTextOut as a fallback.
// 
BOOL WINAPI GenTextOutInit(HDC hdc, int x, int y, UINT fuOptions, CONST RECT *lprc,
                      LPCWSTR lpString, UINT cbCount, const int *lpdx)
{
    pfnGenericTextOut = UniscribeTextOut ; // Try using Uniscribe

    if(pfnGenericTextOut(hdc, x, y, fuOptions, lprc, lpString,  cbCount, lpdx))
    {
        return TRUE ;
    }

    // Couldn't use Uniscribe, give up and use ExtTextOut
    pfnGenericTextOut = ExtTextOutW ;

    return pfnGenericTextOut(hdc, x, y, fuOptions, lprc, lpString,  cbCount, lpdx) ;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */

