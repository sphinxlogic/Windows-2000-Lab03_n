/*
Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iaccess.h>     // IAccessControl
#include "iac.h"


void Message(LPTSTR szPrefix, HRESULT hr);
extern TCHAR szAccessPermissions[];
    
BOOL GetAccessControl(IAccessControl **p)
{
    HRESULT                    hr;
    ACTRL_ACCESSW               access;
    ACTRL_PROPERTY_ENTRYW       propEntry;
    ACTRL_ACCESS_ENTRY_LISTW    entryList;
    ACTRL_ACCESS_ENTRYW         entry;
    HKEY                       key = 0;
    IAccessControl             *accctrl;
    *p = NULL;

	// 
    hr = CoCreateInstance (CLSID_DCOMAccessControl, 
                                NULL,
                                CLSCTX_INPROC_SERVER,
                                IID_IAccessControl,
                                (void **) &accctrl);
	if (FAILED(hr))
	{
		Message(TEXT("Client: CoCreateInstance CLSID_DCOMAccessControl Error"), hr);
		return FALSE;
	}

    
    access.cEntries = 1;
    access.pPropertyAccessList = &propEntry;
    
    propEntry.lpProperty = NULL;
    propEntry.pAccessEntryList = &entryList;
    propEntry.fListFlags = 0;

    
    entryList.cEntries = 1;
    entryList.pAccessList = &entry;

    //
    // Setup the access control entry
    //

    entry.fAccessFlags = ACTRL_ACCESS_ALLOWED;
    entry.Access = COM_RIGHTS_EXECUTE;
    entry.ProvSpecificAccess = 0;
    entry.Inheritance = NO_INHERITANCE;
    entry.lpInheritProperty = NULL;

	entry.Trustee.pMultipleTrustee = NULL;
	entry.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
	entry.Trustee.TrusteeForm = TRUSTEE_IS_NAME;
	entry.Trustee.TrusteeType = TRUSTEE_IS_USER;
	
	entry.Trustee.ptstrName = L"NT Authority\\System";
	hr = accctrl->GrantAccessRights (&access);
	if (FAILED(hr))
	{
		Message(TEXT("Client: SetAccessRights Error"), hr);
		return FALSE;
	}
#ifndef UNICODE
	WCHAR szw[100];
#endif

	TCHAR *token;
	token = _tcstok(szAccessPermissions, TEXT(","));
	while(token)
	{

		entry.fAccessFlags        = ACTRL_ACCESS_ALLOWED;
		
		// Special-case Everyone,INTERACTIVE,NETWORK groups
		
		if (!lstrcmpi(token, TEXT("*")) ) 
			entry.Trustee.TrusteeType = TRUSTEE_IS_GROUP;
		else
			entry.Trustee.TrusteeType = TRUSTEE_IS_USER;
#ifdef UNICODE
		entry.Trustee.ptstrName = token;
#else
		MultiByteToWideChar(0,0,token,-1,szw, sizeof(szw));
		entry.Trustee.ptstrName = szw;
#endif
		hr = accctrl->GrantAccessRights (&access);
		if (FAILED(hr))
		{
			Message(TEXT("Client: GrantAccessRights Error"), hr);
			return FALSE;
		}
		token = _tcstok(NULL, TEXT(","));
	}
	*p = accctrl;
	return TRUE;
}
