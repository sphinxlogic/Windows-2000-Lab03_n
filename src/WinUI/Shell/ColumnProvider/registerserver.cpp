//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  RegisterServer.cpp
//
//      Registers the Column Provider in the registry. The following
//      registry keys will be created to register the column provider.
//
//          HKEY_CLASSES_ROOT\CLSID\{CLSID}
//          HKEY_CLASSES_ROOT\CLSID\{CLSID}\InProcServer32
//          HKEY_CLASSES_ROOT\Folder\ShellEx\ColumnHandlers
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"
#include "Resource.h"

PSECURITY_DESCRIPTOR WINAPI CreateNullDacl ();
VOID WINAPI FreeNullDacl (PSECURITY_DESCRIPTOR psd);

extern HINSTANCE hDllInstance;

STDAPI DllRegisterServer (VOID)
{
    SECURITY_ATTRIBUTES sa = {0};
    TCHAR       szModuleName[MAX_PATH]; 
    HRESULT     hResult = S_OK;
    TCHAR       szBuffer[MAX_PATH+10] = TEXT("");
    TCHAR       szClsid[MAX_PATH] = TEXT("");
    TCHAR       szSubKey[MAX_PATH] = TEXT("");
    TCHAR       szColumnProvider[MAX_PATH] = TEXT("");
    TCHAR       szDescription[MAX_PATH] = TEXT("");

    //
    //  Load some necessary string values
    //
    LoadString (hDllInstance, IDS_CLSID, szClsid, MAX_PATH);
    LoadString (hDllInstance, IDS_DESCRIPTION, szDescription, MAX_PATH);
    LoadString (hDllInstance, IDS_REGKEY_COLUMNPROVIDER, szColumnProvider, MAX_PATH);

    //
    //  Initialize the security attributes structure
    //
    sa.nLength              = sizeof (SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = CreateNullDacl ();
    sa.bInheritHandle       = FALSE;

    //
    //  Get the name of this module
    //
    GetModuleFileName (hDllInstance, szModuleName, MAX_PATH);

    //
    //  Register the component under HKCR\CLSID
    //
    HKEY    hKey            = NULL;
    DWORD   dwDisposition   = 0;
    LRESULT lResult         = 0;

    wsprintf (szSubKey, TEXT("CLSID\\%s"), szClsid);
    lResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              &sa, &hKey, &dwDisposition);

    if (lResult == NOERROR)
    {
        lResult = RegSetValueEx (hKey, TEXT(""), 0, REG_SZ, (LPBYTE) szDescription, GetStringByteSize(szDescription));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;
        RegCloseKey (hKey);
        hKey = NULL;
    }
    else
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Register component information under HKCR\CLSID\{CLSID}
    //
    lstrcat (szSubKey, TEXT("\\InprocServer32"));
    lResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              &sa, &hKey, &dwDisposition);

    if (lResult == NOERROR)
    {
        lstrcpy (szBuffer, TEXT("Apartment"));
        lResult = RegSetValueEx (hKey, TEXT("ThreadingModel"), 0, REG_SZ, (LPBYTE) szBuffer, GetStringByteSize (szBuffer));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        lResult = RegSetValueEx (hKey, TEXT(""), 0, REG_SZ, (LPBYTE) szModuleName, GetStringByteSize(szModuleName));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        RegCloseKey (hKey);
        hKey = NULL;
    }
    else
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Register the component as a column provider extension under
    //  HKCR\Folder\shellex\ColumnHandlers
    //
    wsprintf (szSubKey, TEXT("%s\\%s"), szColumnProvider, szClsid);
    lResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              &sa, &hKey, &dwDisposition);

    if (lResult != NOERROR)
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Free the security descriptor
    //
    FreeNullDacl (sa.lpSecurityDescriptor);

    return hResult;
}