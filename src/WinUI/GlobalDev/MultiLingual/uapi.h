//
// UAPI.h
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// Purpose:
// This is the header file for a Unicode API. It allows an application to use 
// Unicode on both Windows NT and Windows 9x. See the readme file for details.


#ifndef _UAPIH

// Uncomment this line to emmulate Windows 98 behavior when developing on
// Windows NT
//#define EMULATE9X

#include "UNIANSI.H"


// These macro save declaring globals variables twice
#ifdef GLOBALS_HERE
#define GLOBAL
#define GLOBALINIT(a) = a
#else
#define GLOBAL extern
#define GLOBALINIT(a)
#endif

GLOBAL UAPI_LoadString          LoadStringU         GLOBALINIT(LoadStringW)      ;
GLOBAL UAPI_RegisterClassEx     RegisterClassExU    GLOBALINIT(RegisterClassExW) ;
GLOBAL UAPI_CreateWindowEx      CreateWindowExU     GLOBALINIT(CreateWindowExW)  ;
GLOBAL UAPI_LoadAccelerators    LoadAcceleratorsU   GLOBALINIT(LoadAcceleratorsW);
GLOBAL UAPI_CreateFontIndirect  CreateFontIndirectU GLOBALINIT(CreateFontIndirectW) ;
GLOBAL UAPI_ChooseFont          ChooseFontU         GLOBALINIT(ChooseFontW)      ;
GLOBAL UAPI_LoadMenu            LoadMenuU           GLOBALINIT(LoadMenuW)        ;
GLOBAL UAPI_SetWindowText       SetWindowTextU      GLOBALINIT(SetWindowTextW)   ;
GLOBAL UAPI_GetWindowText       GetWindowTextU      GLOBALINIT(GetWindowTextW)   ;
GLOBAL UAPI_SendDlgItemMessage  SendDlgItemMessageU GLOBALINIT(SendDlgItemMessageW) ;
GLOBAL UAPI_SendMessage         SendMessageU        GLOBALINIT(SendMessageW)     ;
GLOBAL UAPI_GetModuleFileName   GetModuleFileNameU  GLOBALINIT(GetModuleFileNameW) ;
GLOBAL UAPI_CharLower           CharLowerU          GLOBALINIT(CharLowerW)       ;
GLOBAL UAPI_FindFirstFile       FindFirstFileU      GLOBALINIT(FindFirstFileW)   ;
GLOBAL UAPI_FindNextFile        FindNextFileU       GLOBALINIT(FindNextFileW)    ;
GLOBAL UAPI_LoadLibraryEx       LoadLibraryExU      GLOBALINIT(LoadLibraryExW)   ;
GLOBAL UAPI_GetLocaleInfo       GetLocaleInfoU      GLOBALINIT(GetLocaleInfoW)   ;
GLOBAL UAPI_DialogBoxParam      DialogBoxParamU     GLOBALINIT(DialogBoxParamW)  ;
GLOBAL UAPI_GetDateFormat       GetDateFormatU      GLOBALINIT(GetDateFormatW)   ;
// Special cases, with no corresponding Win32 API function
GLOBAL UAPI_ConvertMessage      ConvertMessage      GLOBALINIT(NULL)             ;
GLOBAL UAPI_UpdateUnicodeAPI    UpdateUnicodeAPI    GLOBALINIT(NULL)             ;

// Win32 entry points that have the same prototype for both the W and A versions.
// We don't use a typedef because we only have to declare the pointers here
GLOBAL HRESULT (WINAPI *DefWindowProcU)   (HWND, UINT, WPARAM, LPARAM) GLOBALINIT(DefWindowProcW)   ;
GLOBAL LONG    (WINAPI *DispatchMessageU) (CONST MSG *)                GLOBALINIT(DispatchMessageW) ;
GLOBAL BOOL    (WINAPI *GetMessageU)      (LPMSG, HWND, UINT, UINT)    GLOBALINIT(GetMessageW)      ;
GLOBAL int     (WINAPI *TranslateAcceleratorU) 
                         (HWND, HACCEL, LPMSG) GLOBALINIT(TranslateAcceleratorW) ;

// Implemented as a macro, just as DialogBoxW is on Windows NT
#define DialogBoxU(hInstance, lpTemplate, hWndParent, lpDialogFunc    ) \
   DialogBoxParamU(hInstance, lpTemplate, hWndParent, lpDialogFunc, 0L)

// External function prototypes. The client of the Unicode API calls this to 
// set the pointer functions as appropriate
BOOL   InitUnicodeAPI(HINSTANCE) ; 

#ifndef MIN
#define MIN(_aa, _bb) ((_aa) < (_bb) ? (_aa) : (_bb))
#endif

#define _UAPIH
#endif
