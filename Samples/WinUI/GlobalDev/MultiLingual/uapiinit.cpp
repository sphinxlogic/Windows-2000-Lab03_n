//
// UAPIINIT.CPP
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// Purpose: 
// This module initializes the Unicode-ANSI API function pointers (the 'U' API).
// This is a set of entry points that parallel selected functions in the Win32 API.
// Each pointer is typedefed as a pointer to the corresponding W API entry point.
// See description of InitUnicodeAPI for more details.
//

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GLOBALS_HERE

#include "uapi.h"

//
//  FUNCTION: ConvertMessageUStub
//
//  PURPOSE:  Stub that does nothing
//
//  COMMENTS: Dummy routine used on Windows NT only. See ConvertMessageAU in UNIANSI.CPP for
//            an example of a real message converter for use on Windows 9x
//
BOOL WINAPI ConvertMessageUStub(HWND hWnd, UINT message, WPARAM *pwParam, LPARAM *plParam)
{
    return TRUE ;
}

//
//  FUNCTION: UpdateUnicodeAPIStub
//
//  PURPOSE:  Stub that does nothing
//
//  COMMENTS: Dummy routine used on Windows NT only. See UpdateUnicodeAPIAU in UNIANSI.CPP for
//            an example of an implementation for use on Windows 9x
//
BOOL WINAPI UpdateUnicodeAPIStub(LANGID wCurrentUILang, UINT InputCodePage)
{
    return TRUE ;
}


//
//  FUNCTION: InitUnicodeAPI
//
//  PURPOSE:  Set U API function pointers to point appropriate entry point.
//            
//  COMMENTS: The U function pointers are set to the corresponding W entry
//            point by default in the header file UAPI.H. If running on 
//            Windows NT we leave these function pointers as is. Otherwise, 
//            we load a library of wrapper routines (UNIANSI.DLL) and set
//            the function pointer to the corresponding wrapper routine.
//            For example, LoadStringU is set to LoadStringW at compile time,
//            but if running on Windows 9x, it is set to LoadStringAU, which
//            calls LoadStringA and converts ANSI to Unicode.
// 
BOOL InitUnicodeAPI(HINSTANCE hInstance)
{
    OSVERSIONINFO Osv ;
    BOOL IsWindowsNT  ;

    Osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO) ;

    if(!GetVersionEx(&Osv)) 
    {
        return FALSE ;
    }

// define this symbol in UAPI.H to emulate Windows 9x when testing on Windows NT.
#ifdef EMULATE9X
    IsWindowsNT = FALSE ;
#else
    IsWindowsNT = (BOOL) (Osv.dwPlatformId == VER_PLATFORM_WIN32_NT) ;
#endif

    if(IsWindowsNT) 
    {
        // On Windows NT, we just set the U function pointer to the W 
        // entry point. This was already done at compile time by the 
        // default assignment in UAPI.H
        // For these special cases (not Win32 functions) we do
        // the assignment here
        ConvertMessage   = (UAPI_ConvertMessage)    ConvertMessageUStub ;
        UpdateUnicodeAPI = (UAPI_UpdateUnicodeAPI)  UpdateUnicodeAPIStub;
    }
    else {
        HMODULE hMUniAnsi   ;
        BOOL (*InitUniAnsi)(PUAPIINIT) ;
        UAPIINIT UAInit   ;

    // On Windows 9x, there are two broad implementation classes of Win32 APIs:

        // Case 1: The W and A versions pass exactly the same
        // parameters, so we can just set the U function pointer to the
        // A entry point without using a wrapper function
        GetMessageU           = GetMessageA           ;
        TranslateAcceleratorU = TranslateAcceleratorA ;
        DispatchMessageU      = DispatchMessageA      ;
        DefWindowProcU        = DefWindowProcA        ;

        // Case 2: Most functions require hand-written routines to convert between 
        // Unicode and ANSI and call the A entry point in the Win32 API. 
        // We set the U function pointer to those handwritten routines, 
        // which are in the following DLL:
        hMUniAnsi = LoadLibraryA("UniAnsi.DLL") ;

        if(!hMUniAnsi) 
        {
            
            // Too early in intialization phase to use a localized message, so 
            // fall back to hard-coded English message
            MessageBoxW(
                NULL, 
                L"Cannot load Unicode conversion module. Press OK to exit ...", 
                L"Initialization Error",  
                MB_OK | MB_ICONERROR) ;

            return FALSE ;
        }

        // Get Initialization routine from the DLL
        InitUniAnsi = (BOOL (*)(PUAPIINIT)) GetProcAddress(hMUniAnsi, "InitUniAnsi") ;

        // Set up structure containing locations of U function pointers
        UAInit.pCharLowerU          = &CharLowerU          ;
        UAInit.pChooseFontU         = &ChooseFontU         ;
        UAInit.pCreateWindowExU     = &CreateWindowExU     ;
        UAInit.pCreateFontIndirectU = &CreateFontIndirectU ;
        UAInit.pDialogBoxParamU     = &DialogBoxParamU     ;
        UAInit.pFindFirstFileU      = &FindFirstFileU      ;
        UAInit.pFindNextFileU       = &FindNextFileU       ;
        UAInit.pGetDateFormatU      = &GetDateFormatU      ;
        UAInit.pGetLocaleInfoU      = &GetLocaleInfoU      ;
        UAInit.pGetModuleFileNameU  = &GetModuleFileNameU  ;
        UAInit.pLoadAcceleratorsU   = &LoadAcceleratorsU   ;
        UAInit.pLoadLibraryExU      = &LoadLibraryExU      ;
        UAInit.pLoadMenuU           = &LoadMenuU           ;
        UAInit.pLoadStringU         = &LoadStringU         ;
        UAInit.pRegisterClassExU    = &RegisterClassExU    ;
        UAInit.pSendDlgItemMessageU = &SendDlgItemMessageU ;
        UAInit.pSendMessageU        = &SendMessageU        ;
        UAInit.pSetWindowTextU      = &SetWindowTextU      ;
        UAInit.pGetWindowTextU      = &GetWindowTextU      ;
        // Add new entries here

        // Special cases, not corresponding to any Win32 API
        UAInit.pConvertMessage      = &ConvertMessage     ;
        UAInit.pUpdateUnicodeAPI    = &UpdateUnicodeAPI   ;

        if( NULL == InitUniAnsi    // Make sure we have a valid initialization function
             ||
            !InitUniAnsi(&UAInit) // Initialize U function pointers
          ) 
        {
            // Too early in intialization phase to use a localized message, so 
            // fall back to hard-coded English message
            MessageBoxW(
                NULL, 
                L"Cannot initialize Unicode functions. Press OK to exit ...", 
                L"Initialization Error",  
                MB_OK | MB_ICONERROR) ;
            
            return FALSE ;
        }
    }

    if(!(       // Confirm that the initialization was OK
       LoadStringU          &&
       RegisterClassExU     &&
       CreateWindowExU      &&
       LoadAcceleratorsU    &&
       CreateFontIndirectU  &&
       ChooseFontU          &&
       LoadMenuU            &&
       SetWindowTextU       &&
       SendDlgItemMessageU  &&
       SendMessageU         &&
       GetModuleFileNameU   &&
       CharLowerU           &&
       FindFirstFileU       &&
       FindNextFileU        &&
       LoadLibraryExU       &&
       GetLocaleInfoU       &&
       DialogBoxParamU      &&
       GetDateFormatU       &&
       DefWindowProcU       &&
       DispatchMessageU     &&
       GetMessageU          &&
       TranslateAcceleratorU&&
        // Add test for new U functions here

       UpdateUnicodeAPI     &&
       ConvertMessage
       ) ) 
    {
        // Too early in intialization phase to use a localized message, so 
        // fall back to hard-coded English message
        MessageBoxW(
            NULL, 
            L"Cannot initialize Unicode functions. Press OK to exit ...", 
            L"Initialization Error",  
            MB_OK | MB_ICONERROR) ;

        return FALSE ;
    }

    return TRUE ;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
