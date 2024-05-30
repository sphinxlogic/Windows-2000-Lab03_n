//
// UPDTLANG.CPP
//
//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// Purpose: 
// Routines for intializing and updating the user interface for a
// particular language

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "uapi.h"
#include "updtlang.h"
#include "resource.h"

extern WCHAR g_szTitle[MAX_LOADSTRING] ;

LANGID GetDefaultUILang() ;

//
//  FUNCTION: InitUILang 
//
//  PURPOSE:  Determines the appropriate user interface language and
//            sets the user interface parameters
//
//  COMMENTS: If there is not an exact match between the user interface language ID
//            and the language ID of some resource DLL, then this routine uses
//            US English as a fallback. A better approach would be to look for a 
//            resource DLL with a match in the primary language only, ignoring 
//            the sublanguage. That could be done here or in GetResourseModule
//            below.
// 
BOOL InitUILang(HINSTANCE hInstance, PLANGSTATE pLState) 
{
    LANGID wUILang = GetDefaultUILang() ;

    if(ILLEGAL_LANGID == wUILang) 
    {
        return FALSE ;
    }
 
    if(!UpdateUILang(hInstance, wUILang, pLState)
        &&  // In case we can't find the desired resource DLL ...
       !UpdateUILang(hInstance, FALLBACK_UI_LANG, pLState)
       ) 
    { 

        return FALSE ;
    }

    return TRUE ;
}


//
//  FUNCTION: GetDefaultUILang 
//
//  PURPOSE:  Returns the default user interface language, using a method 
//            appropriate to the platform (Windows 9x, Windows NT, or Windows 2000)
//
LANGID GetDefaultUILang() 
{
    OSVERSIONINFO Osv ;
    BOOL IsWindowsNT ;

    LANGID wUILang = 0 ;

    Osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO) ;

    if(!GetVersionEx(&Osv)) 
    {
        return ILLEGAL_LANGID ;
    }

    IsWindowsNT = (BOOL) (Osv.dwPlatformId == VER_PLATFORM_WIN32_NT) ;

    // Get the UI language by one of three methods, depending on the system
    if(!IsWindowsNT) 
    {
        // Case 1: Running on Windows 9x. Get the system UI language from registry:
        CHAR szData[32]   ;
        DWORD dwErr, dwSize = sizeof(szData) ;
        HKEY hKey          ;

        dwErr = RegOpenKeyExA(
                    HKEY_USERS, 
                    ".Default\\Control Panel\\desktop\\ResourceLocale", 
                    0, 
                    KEY_READ, 
                    &hKey
                    ) ;

        if(ERROR_SUCCESS != dwErr) 
        {
            return ILLEGAL_LANGID ;
        }

        dwErr = RegQueryValueExA(   
                    hKey, 
                    "", 
                    NULL,  //reserved
                    NULL,  //type
                    (LPBYTE) szData,
                    &dwSize
                ) ; 

        if(ERROR_SUCCESS != dwErr) 
        {
            return ILLEGAL_LANGID ;
        }

        dwErr = RegCloseKey(hKey) ;

        // Convert string to number
        wUILang = (LANGID) strtol(szData, NULL, 16) ;
    }
// Disable this section to emulate Windows NT 4.0 or earlier, when testing
// on Windows 2000
#if 1   
    else if (Osv.dwMajorVersion >= 5.0) 
    {
    // Case 2: Running on Windows 2000 or later. Use GetUserDefaultUILanguage to find 
    // the user's prefered UI language

        // Declare function pointer
        LANGID (WINAPI *pfnGetUserDefaultUILanguage) () = NULL ;

        HMODULE hMKernel32 = LoadLibraryW(L"kernel32.dll") ;
        
        pfnGetUserDefaultUILanguage = 
            (unsigned short (WINAPI *)(void)) 
                GetProcAddress(hMKernel32, "GetUserDefaultUILanguage") ;

        if(NULL != pfnGetUserDefaultUILanguage) 
        {
            wUILang = pfnGetUserDefaultUILanguage() ;
        }
        else
        {   // GetProcAddress failed
            return ILLEGAL_LANGID ;
        }
    }
#endif
    else {
    // Case 3: Running on Windows NT 4.0 or earlier. Get UI language
    // from locale of .default user in registry:
    // HKEY_USERS\.DEFAULT\Control Panel\International\Locale
        
        WCHAR szData[32]   ;
        DWORD dwErr, dwSize = sizeof(szData) ;
        HKEY hKey          ;

        dwErr = RegOpenKeyExW(
                    HKEY_USERS, 
                    L".DEFAULT\\Control Panel\\International", 
                    0, 
                    KEY_READ, 
                    &hKey
                    ) ;

        if(ERROR_SUCCESS != dwErr) 
        {
            return ILLEGAL_LANGID ;
        }

        dwErr = RegQueryValueExW(   
                    hKey, 
                    L"Locale", 
                    NULL,  //reserved
                    NULL,  //type
                    (LPBYTE) szData,
                    &dwSize
                ) ; 

        if(ERROR_SUCCESS != dwErr) 
        {
            return ILLEGAL_LANGID ;
        }

        dwErr = RegCloseKey(hKey) ;

        // Convert string to number
        wUILang = (LANGID) wcstol(szData, NULL, 16) ;

        if(0x0401 == wUILang || // Arabic
           0x040d == wUILang || // Hebrew
           0x041e == wUILang    // Thai
           )
        {
            // Special case these to the English UI.
            // These versions of Windows NT 4.0 were enabled only, i.e., the
            // UI was English. However, the registry setting 
            // HKEY_USERS\.DEFAULT\Control Panel\International\Locale was set  
            // to the respective locale for application compatibility.
            wUILang = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US) ;
        }

    }

    return wUILang ;
}

//
//  FUNCTION: UpdateUILang
//
//  PURPOSE:  Gets a module handle for the resource DLL of the specified language, then 
//            sets the state variables to the appropriate values using that module
//
BOOL UpdateUILang(IN HINSTANCE hInstance, IN LANGID wUILang, OUT PLANGSTATE pLState) 
{
    HMODULE hMRes = NULL ;
    HMENU      hNewMenu  = NULL ;

    pLState->UILang = wUILang ;

    // Find a resource dll file of the form .\resources\res<langid>.dll
    if(NULL == (hMRes = GetResourceModule(hInstance, pLState->UILang) )) 
    {
        return FALSE ;
    }

#if 0
    // To verify that the res<langid>.dll file has the right resource
    // language, activate this section. It will slow down the search if the
    // the resource DLLs are very big. 
    
    // To work properly, this requires that you mark the menu resource in each rc
    // file with the appropriate language. For example, for Hindi, you can use 
    // LANGUAGE 0x39, SUBLANG_DEFAULT
    // Also, you must use the appropriate resource ID. Here it's hardcoded to IDM_MENU.
    if(NULL == FindResourceExA(hMRes, RT_MENU, MAKEINTRESOURCEA(IDM_MENU), pLState->UILang)) 
    {
        return FALSE ;
    }
#endif 

    pLState->hMResource = hMRes ;

    hNewMenu = LoadMenuU(pLState->hMResource, MAKEINTRESOURCEW(IDM_MENU)) ;

    if(!hNewMenu) 
    {
        return FALSE ;
    }

    if(pLState->hMenu) 
    {        
        DestroyMenu(pLState->hMenu) ;
    }

    pLState->hMenu = hNewMenu ;

    pLState->hAccelTable = LoadAcceleratorsU (pLState->hMResource, MAKEINTRESOURCEW(IDA_MULTILING) ) ;

    pLState->InputCodePage = LangToCodePage( LOWORD(GetKeyboardLayout(0)) ) ;

    pLState->IsRTLLayout // Set right-to-left Window layout for relevant languages
        = PRIMARYLANGID(wUILang) == LANG_ARABIC 
       || PRIMARYLANGID(wUILang) == LANG_HEBREW ;

    if(pLState->IsRTLLayout) 
    {
        
        // Another case where we have to get the function pointer explicitly.
        // You should just call SetProcessDefaultLayout directly if you know  
        // you're on Windows 2000 or greater, or on Arabic or Hebrew Windows 98
        BOOL   (CALLBACK *pfnSetProcessDefaultLayout) (DWORD) ;
        HMODULE hInstUser32 = LoadLibraryA("user32.dll") ;
        
        if (
            pfnSetProcessDefaultLayout = 
                (BOOL (CALLBACK *) (DWORD)) GetProcAddress (hInstUser32, "SetProcessDefaultLayout")
            ) 
        {
                pfnSetProcessDefaultLayout(LAYOUT_RTL) ;
        }
    }

    UpdateUnicodeAPI(wUILang, pLState->InputCodePage) ;

    return TRUE ;
}

//
//  FUNCTION: LangToCodePage
//
//  PURPOSE:  Gets the default codepage for a given langID.
//
UINT LangToCodePage(IN LANGID wLangID)
{
    CHAR szLocaleData[6] ;

    // In this case there is no advantage to using the W or U
    // interfaces. We know the string in szLocaleData will consist of
    // digits 0-9, so there is no multilingual functionality lost by
    // using the A interface.
    GetLocaleInfoA(MAKELCID(wLangID, SORT_DEFAULT) , LOCALE_IDEFAULTANSICODEPAGE, szLocaleData, 6);

    return strtoul(szLocaleData, NULL, 10);
}


//
//  FUNCTION: GetResourceModule
//
//  PURPOSE:  Loads a resource DLL with resources in the language given 
//            by dwLocaleID, and returns a handle to that module.
//
HMODULE GetResourceModule(HINSTANCE hInstance, LCID dwLocaleID)
{
    WCHAR  szResourceFileName[MAX_PATH] = {L'\0'} ;

    if(!FindResourceDirectory(hInstance, szResourceFileName)) 
    {
        return NULL ;
    }

    wcscat(szResourceFileName, L"\\res") ;

    // Convert the LocaleID to Unicode and append to resourcefile name.
    _itow(dwLocaleID, szResourceFileName+wcslen(szResourceFileName), 16) ;

    // Add DLL extention to file name
    wcscat(szResourceFileName, L".dll") ;

    return LoadLibraryExU(szResourceFileName, NULL, 0) ;

}


//
//  FUNCTION: FindResourceDirectory
//
//  PURPOSE:  Finds the path were the resource DLLs are located  
//            and puts it into szResourceDirectory
//
//  COMMENTS: Assumes that all resources DLLs are in a directory called
//            "resources" below the directory where the application exe
//            file is
BOOL FindResourceDirectory(IN HINSTANCE hInstance, OUT LPWSTR szResourceDirectory)
{
    LPWSTR pExeName ;

    if(!GetModuleFileNameU(hInstance, szResourceDirectory, MAX_PATH)) 
    {
        return FALSE;
    }

    CharLowerU(szResourceDirectory) ;

    if((pExeName = wcsstr(szResourceDirectory, L"multilingual.exe"))) 
    {
        *pExeName = L'\0' ;
    }

    wcscat(szResourceDirectory, L"resources") ;

    return TRUE ;
}


//
//  FUNCTION: RcMessageBox 
//
//  PURPOSE: Display a message box with formated output similar to sprintf
//
//  COMMENTS:
//      This function loads the string identified by nMessageID from the 
//      resource segment, uses vswprintf to format it using the variable
//      parameters, and displays it to the user in a message box using the
//      icons and options specified by nOptions.
//
int RcMessageBox(
        HWND hWnd         ,   // Window handle for displaying MessageBox
        PLANGSTATE pLState,   // Language data
        int nMessageID    ,   // Message ID in resources
        int nOptions      ,   // Options to pass to MessageBox
        ...)                  // Optional parameters, depending on string resource 
{
    WCHAR szLoadBuff[MAX_LOADSTRING], szOutPutBuff[3*MAX_LOADSTRING] ;
    va_list valArgs ;

    va_start(valArgs, nOptions) ;
    
    if (!LoadStringU(pLState->hMResource, nMessageID, szLoadBuff, MAX_LOADSTRING))
    {
        return 0 ;
    }

    vswprintf(szOutPutBuff, szLoadBuff, valArgs) ;
    
    va_end(valArgs) ;

    if (pLState->IsRTLLayout)  
    {
        nOptions |= MB_RTLREADING ;
    }

    return (MessageBoxExW(hWnd, szOutPutBuff, g_szTitle, nOptions, pLState->UILang)) ;
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
