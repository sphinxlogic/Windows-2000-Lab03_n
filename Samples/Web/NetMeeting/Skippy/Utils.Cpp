//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       utils.cpp
//  Content:    This file contains utility functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"

//
int g_nOpen, g_nClosed, g_nDocument;


//****************************************************************************
// 
// void _cdecl MyTextOut (LPCTSTR szFmt, ...)
//
// This function displays the textual message in the application log box.
// 
//****************************************************************************

void _cdecl MyTextOut (LPCTSTR szFmt, ...)
{
	HWND hEdit;
	va_list VarArg;
	TCHAR   szText[256];

	va_start(VarArg,szFmt);
	wvsprintf(szText, szFmt, VarArg);

	hEdit = GetDlgItem(g_hwndMain, IDC_ACT_EDIT);
	Edit_SetSel(hEdit, 0xFFFF, 0xFFFF);
	Edit_ReplaceSel(hEdit, szText);
	return;
}

//****************************************************************************
// 
// void ErrorMessage(HWND hwnd, LPCTSTR szPrefix, HRESULT hr)
//
// This function prompts the end-user with the error message box.
// 
//****************************************************************************

void ErrorMessage(HWND hwnd, LPCTSTR szPrefix, HRESULT hr)
{
	TCHAR   szMessage[256];

	if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)
		hr = HRESULT_CODE(hr);
 
	wsprintf (szMessage, TEXT("\r\n%s: returns %s (%lx)\r\n"), szPrefix, GetErrorString(hr), hr);
	MessageBox(hwnd, szMessage, TEXT("Function return"), MB_OK | MB_ICONERROR);
	return;
}

//****************************************************************************
//
// LPTSTR AllocLPTSTR (ULONG cb)
//
// This function allocates a LPTSTR
//
//****************************************************************************

LPTSTR AllocLPTSTR (ULONG cb)
{
	LPTSTR psz;

	psz = (LPTSTR)LocalAlloc(LMEM_FIXED, cb*sizeof(TCHAR));
	return psz;
}

//****************************************************************************
//
// HRESULT FreeLPTSTR (LPTSTR psz)
//
// This function frees the LPTSTR 
//
//****************************************************************************

HRESULT FreeLPTSTR (LPTSTR psz)
{
	HLOCAL hRet;
	hRet = LocalFree(psz);
	return( hRet == NULL ? S_OK : E_FAIL);
}

//****************************************************************************
//
// HRESULT SetLPTSTR (LPTSTR *ppszName, LPCTSTR pszUserName)
//
// This function creates a name buffer
//
//****************************************************************************

HRESULT SetLPTSTR (LPTSTR *ppszName, LPCTSTR pszUserName)
{
	LPTSTR pszNew;

	// Allocate a name buffer
	//
	pszNew = AllocLPTSTR(lstrlen(pszUserName)+1);

	// It would be bad if the name buffer cannot be allocated,
	// but we can live with it.
	//
	if (pszNew != NULL)
	{
		lstrcpy(pszNew, pszUserName);

		// Free the old name
		//
		if (*ppszName != NULL)
		{
			FreeLPTSTR(*ppszName);
		};
		*ppszName = pszNew;
		return S_OK;
	}
	else
	{
		return E_OUTOFMEMORY;
	};
}

//****************************************************************************
//
// HRESULT LPTSTR_to_BSTR (BSTR *pbstr, LPCTSTR psz)
//
//****************************************************************************

HRESULT LPTSTR_to_BSTR (BSTR *pbstr, LPCTSTR psz)
{
#ifndef UNICODE

	BSTR bstr;
	int i;
	HRESULT hr;

	
	// compute the length of the required BSTR
	//
	i =  MultiByteToWideChar(CP_ACP, 0, psz, -1, NULL, 0);
	if (i <= 0)
	{
		return E_UNEXPECTED;
	};

	// allocate the widestr, +1 for terminating null
	//
	bstr = SysAllocStringLen(NULL, i-1); // SysAllocStringLen adds 1

	if (bstr != NULL)
	{ 
		MultiByteToWideChar(CP_ACP, 0, psz, -1, (LPWSTR)bstr, i);
		((LPWSTR)bstr)[i - 1] = 0;
		*pbstr = bstr;
		hr = S_OK;
	}
	else
	{
		hr = E_OUTOFMEMORY;
	};
	return hr;

#else

	BSTR bstr;

	bstr = SysAllocString(psz);

	if (bstr != NULL)
	{
		*pbstr = bstr;
		return S_OK;
	}
	else
	{
		return E_OUTOFMEMORY;
	};

#endif // UNICODE
}

//****************************************************************************
//
// HRESULT BSTR_to_LPTSTR (LPTSTR *ppsz, BSTR bstr)
//
//****************************************************************************

HRESULT BSTR_to_LPTSTR (LPTSTR *ppsz, BSTR bstr)
{
#ifndef UNICODE

	LPTSTR psz;
	int i;
	HRESULT hr;

	// Whoa... handle the NULL string first.
	//
	if(bstr == NULL)  // if bstr is NULL we return E_UNEXPECTED and pass a default string
	{
		psz = AllocLPTSTR(lstrlen("")+1);
		if(psz != NULL)
		{
			strcpy(psz, "");
			*ppsz = psz;
		}
		return E_UNEXPECTED;
	}
		
	// compute the length of the required BSTR
	//
	i =  WideCharToMultiByte(CP_ACP, 0, (LPWSTR)bstr, -1, NULL, 0, NULL, NULL);
	if (i <= 0)
	{
		return E_UNEXPECTED;
	};

	// allocate the widestr, +1 for terminating null
	//
	psz = AllocLPTSTR(i);

	if (psz != NULL)
	{ 
		WideCharToMultiByte(CP_ACP, 0, (LPWSTR)bstr, -1, psz, i, NULL, NULL);
		*ppsz = psz;
		hr = S_OK;
	}
	else
	{
		hr = E_OUTOFMEMORY;
	};
	return hr;

#else

	LPTSTR psz = NULL;
	HRESULT hr;

	hr = SetName(&psz, (LPTSTR)bstr);

	if (hr == S_OK)
	{
		*ppsz = psz;
	};
	return hr;

#endif // UNICODE
}

//****************************************************************************
//
// HRESULT DisplayIlsNames(HWND hwnd, IEnumIlsNames *pEnum, LPTSTR szString)
//
// This function displays enumerated text in the output
//
//****************************************************************************

HRESULT DisplayIlsNames(HWND hwnd, IEnumIlsNames *pEnum, LPTSTR szString)
{
	BSTR bstrName;
	LPTSTR pszName;
	ULONG iIndex = 1;

	// For each name
	//
	MyTextOut(TEXT("******** Found the following %s ************\r\n"), szString);

	while (pEnum->Next(1, &bstrName, NULL) == NOERROR)
	{
		BSTR_to_LPTSTR(&pszName, bstrName);
		MyTextOut(TEXT("\t%d> %s\r\n"), iIndex, pszName);
		iIndex++;
		SysFreeString(bstrName);
		FreeLPTSTR(pszName);
	};
	pEnum->Release();

	MyTextOut(TEXT("*****************************************************\r\n"));
	return NOERROR;
}



//****************************************************************************
//
// HRESULT DisplayAboutBox(HWND hwnd)
//
// This function displays the application's about box
//
//****************************************************************************

VOID DisplayAboutBox(HWND hwnd)
{
	char szVersion[MAX_PATH];

	LoadString(ghInstance, IDS_VERSION, szVersion, sizeof(szVersion));

	ShellAbout(hwnd, szVersion, NULL, LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_APP_ICON)));
}


// STRING_CASE turns a #define into a case statement
#define STRING_CASE(val)  case val: pcsz = #val; break


//****************************************************************************
//
// int GetErrorString(HRESULT hr)
//
// This function returns a pointer a string describing the error condition
// The error strings are lifted from ULS.H
//
//****************************************************************************
LPCTSTR GetErrorString(HRESULT hr)
{
	LPCTSTR pcsz;
	static CHAR sz[MAX_PATH];

	switch (hr)
	{
	default:
		wsprintf(sz, "(unknown)");
		pcsz = sz;
		break;

	STRING_CASE(S_OK);
	STRING_CASE(S_FALSE);

// The one success code 

	STRING_CASE(ILS_S_SERVER_MAY_NOT_SUPPORT);


// overloaded error codes

	STRING_CASE(ILS_E_FAIL);
	STRING_CASE(ILS_E_POINTER);
	STRING_CASE(ILS_E_HANDLE);
	STRING_CASE(ILS_E_ABORT);
	STRING_CASE(ILS_E_ACCESS_DENIED);
	STRING_CASE(ILS_E_NOT_IMPL);
	STRING_CASE(ILS_E_NO_INTERFACE);
	STRING_CASE(ILS_E_MEMORY);
	STRING_CASE(ILS_E_PARAMETER);

//  General error codes

	STRING_CASE(ILS_E_SERVER_SERVICE);
	STRING_CASE(ILS_E_SERVER_NAME);
	STRING_CASE(ILS_E_TIMEOUT);
	STRING_CASE(ILS_E_BIND);
	STRING_CASE(ILS_E_THREAD);
	STRING_CASE(ILS_E_SERVER_EXEC);
	STRING_CASE(ILS_E_WINSOCK);
	STRING_CASE(ILS_E_NO_MORE);
	STRING_CASE(ILS_E_NOT_INITIALIZED);
	STRING_CASE(ILS_E_NOTIFY_ID);
	STRING_CASE(ILS_E_NO_SUCH_OBJECT);
	STRING_CASE(ILS_E_NEED_RELOGON);
	STRING_CASE(ILS_E_NAME_CONFLICTS);
	STRING_CASE(ILS_E_NETWORK_DOWN);
	STRING_CASE(ILS_E_FILTER_STRING);
	STRING_CASE(ILS_E_FILTER_OBJECT);
	STRING_CASE(ILS_E_FILTER_TYPE);
	STRING_CASE(ILS_E_ACCESS_CONTROL);
	STRING_CASE(ILS_E_NOT_REGISTERED);
	STRING_CASE(ILS_E_NO_SUCH_MEMBER);
	STRING_CASE(ILS_E_NO_WRITE_ACCESS);
	STRING_CASE(ILS_E_ALREADY_REGISTERED);

//  LDAP specific error codes

	STRING_CASE(ILS_E_LDAP_OPERATIONS_ERROR);
	STRING_CASE(ILS_E_LDAP_PROTOCOL_ERROR);
	STRING_CASE(ILS_E_LDAP_TIMELIMIT_EXCEEDED);
	STRING_CASE(ILS_E_LDAP_SIZELIMIT_EXCEEDED);
	STRING_CASE(ILS_E_LDAP_COMPARE_FALSE);
	STRING_CASE(ILS_E_LDAP_COMPARE_TRUE);
	STRING_CASE(ILS_E_LDAP_AUTH_METHOD_NOT_SUPPORTED);
	STRING_CASE(ILS_E_LDAP_STRONG_AUTH_REQUIRED);
	STRING_CASE(ILS_E_LDAP_REFERRAL_V2);
	STRING_CASE(ILS_E_LDAP_PARTIAL_RESULTS);
	STRING_CASE(ILS_E_LDAP_REFERRAL);
	STRING_CASE(ILS_E_LDAP_ADMIN_LIMIT_EXCEEDED);
	STRING_CASE(ILS_E_LDAP_UNAVAILABLE_CRIT_EXTENSION);

	STRING_CASE(ILS_E_LDAP_NO_SUCH_ATTRIBUTE);
	STRING_CASE(ILS_E_LDAP_UNDEFINED_TYPE);
	STRING_CASE(ILS_E_LDAP_INAPPROPRIATE_MATCHING);
	STRING_CASE(ILS_E_LDAP_CONSTRAINT_VIOLATION);
	STRING_CASE(ILS_E_LDAP_ATTRIBUTE_OR_VALUE_EXISTS);
	STRING_CASE(ILS_E_LDAP_INVALID_SYNTAX);

	STRING_CASE(ILS_E_LDAP_ALIAS_PROBLEM);
	STRING_CASE(ILS_E_LDAP_INVALID_DN_SYNTAX);
	STRING_CASE(ILS_E_LDAP_IS_LEAF);
	STRING_CASE(ILS_E_LDAP_ALIAS_DEREF_PROBLEM);

	STRING_CASE(ILS_E_LDAP_INAPPROPRIATE_AUTH);
	STRING_CASE(ILS_E_LDAP_INVALID_CREDENTIALS);
	STRING_CASE(ILS_E_LDAP_INSUFFICIENT_RIGHTS);
	STRING_CASE(ILS_E_LDAP_BUSY);
	STRING_CASE(ILS_E_LDAP_UNAVAILABLE);
	STRING_CASE(ILS_E_LDAP_UNWILLING_TO_PERFORM);
	STRING_CASE(ILS_E_LDAP_LOOP_DETECT);

	STRING_CASE(ILS_E_LDAP_NAMING_VIOLATION);
	STRING_CASE(ILS_E_LDAP_OBJECT_CLASS_VIOLATION);
	STRING_CASE(ILS_E_LDAP_NOT_ALLOWED_ON_NONLEAF);
	STRING_CASE(ILS_E_LDAP_NOT_ALLOWED_ON_RDN);
	STRING_CASE(ILS_E_LDAP_NO_OBJECT_CLASS_MODS);
	STRING_CASE(ILS_E_LDAP_RESULTS_TOO_LARGE);
	STRING_CASE(ILS_E_LDAP_AFFECTS_MULTIPLE_DSAS);

	STRING_CASE(ILS_E_LDAP_OTHER);
	STRING_CASE(ILS_E_LDAP_SERVER_DOWN);
	STRING_CASE(ILS_E_LDAP_LOCAL_ERROR);
	STRING_CASE(ILS_E_LDAP_ENCODING_ERROR);
	STRING_CASE(ILS_E_LDAP_DECODING_ERROR);
	STRING_CASE(ILS_E_LDAP_TIMEOUT);
	STRING_CASE(ILS_E_LDAP_AUTH_UNKNOWN);
	STRING_CASE(ILS_E_LDAP_FILTER_ERROR);
	STRING_CASE(ILS_E_LDAP_USER_CANCELLED);
	STRING_CASE(ILS_E_LDAP_NO_MEMORY);
	}
return pcsz;
}





//**********************************************************
// DisplayStdAttr - display all the standard attribute information
//
//    
//**********************************************************
void DisplayStdAtt(void *pobj, ILS_STD_ATTR_NAME stdAttr, LPTSTR szDesc, OBJECT_TYPE ot)
{
	HRESULT hr = E_FAIL;
	BSTR bstr = NULL;
	LPTSTR sz = NULL;

	switch(ot)
	{
	case USER:  // user objects
	{
		IIlsUser *pObject = (IIlsUser *)pobj;
		hr = pObject->GetStandardAttribute(stdAttr, &bstr);
		break;
	}
	case PROTOCOL:  // protocol objects
	{
		IIlsProtocol *pObject = (IIlsProtocol *)pobj;
		hr = pObject->GetStandardAttribute(stdAttr, &bstr);
		break;
	}
	default:
		MyTextOut(TEXT("ERROR - hit default in DumpStdAttr, no type?"));
	}
	
	if(SUCCEEDED(hr))
	{
		// retrieved the correct object, print out its value
		hr = BSTR_to_LPTSTR(&sz, bstr);
		if(!sz)
			MyTextOut(TEXT("%s    = <NULL>\r\n"), szDesc);
		else
			MyTextOut(TEXT("%s    = %s\r\n"), szDesc, sz);
	}
	else
	{
		MyTextOut(TEXT("ERROR retrieving %s, returns %s.\r\n"), szDesc, GetErrorString(hr));
	}

	if(sz)
		FreeLPTSTR(sz);

}






//**********************************************************
// DisplayExtAttr - display the requested extended attribute 
// information
//
//    
//**********************************************************
void DisplayExtAtt(void *pobj, DWORD dwExtAttr, LPTSTR szDesc, OBJECT_TYPE ot)
{
	HRESULT hr = E_FAIL;
	BSTR bstr = NULL, bstrName = NULL;
	LPTSTR sz = NULL;
	TCHAR szProperty[100];

	switch(ot)
	{
	case USER:  // user objects
	{
		IIlsUser *pObject = (IIlsUser *)pobj;
		wsprintf(szProperty, TEXT("%lu"), PROP_TAG(PT_STRING8, dwExtAttr));
		LPTSTR_to_BSTR(&bstrName, szProperty);
		hr = pObject->GetExtendedAttribute(bstrName, &bstr);
		break;
	}
	case PROTOCOL:  // protocol objects
	{
		IIlsProtocol *pObject = (IIlsProtocol *)pobj;
		wsprintf(szProperty, TEXT("%lu"), PROP_TAG(PT_STRING8, dwExtAttr));
		LPTSTR_to_BSTR(&bstrName, szProperty);
		hr = pObject->GetExtendedAttribute(bstrName, &bstr);
		break;
	}
	default:
		MyTextOut(TEXT("ERROR - hit default in DumpExtAttr, no type?"));
	}
	
	if(SUCCEEDED(hr))
	{
		// retrieved the correct object, convert back to a string
		hr = BSTR_to_LPTSTR(&sz, bstr);

		if(!sz)  // retrieved an empty string for some reason !!!
			MyTextOut(TEXT("%s    = <NULL>\r\n"), szDesc);
		else
			if( dwExtAttr == NM_RESTRICTION)
			{
				CHAR szType[MAX_PATH];
				
				switch (sz[0])
				{
				case '1':
					wsprintf(szType, "Business");
					break;
				case '2':
					wsprintf(szType, "Personal");
					break;
				case '4':
					wsprintf(szType, "Adult");
					break;
				default:
					wsprintf(szType, "(unknown)");

				}

				MyTextOut(TEXT("%s    = %s\r\n"), szDesc, szType);

			}
			else
				MyTextOut(TEXT("%s    = %s\r\n"), szDesc, 
						(lstrcmp(sz, "1") == 0) ? "yes" : "no");
	}
	else
	{
		MyTextOut(TEXT("ERROR retrieving %s, returns %s.\r\n"), szDesc, GetErrorString(hr));
	}

	if(sz)
		FreeLPTSTR(sz);

}



//****************************************************************************
//
// int StringFromGuid (REFIID riid, LPTSTR pszBuf)
//
// This function returns a string from a CLSID or GUID
//
//****************************************************************************

int StringFromGuid (REFIID   riid, LPTSTR pszBuf)
{
	return wsprintf(pszBuf, 
			TEXT("{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"),
			riid.Data1, riid.Data2, riid.Data3, riid.Data4[0], riid.Data4[1], 
			riid.Data4[2], riid.Data4[3], riid.Data4[4], riid.Data4[5], 
			riid.Data4[6], riid.Data4[7]);
}


//****************************************************************************
// 
// int GetRadioButton(HWND hdlg, int idrFirst, int idrLast);
//
// return the id of the radio button in a given range
//
//****************************************************************************
int GetRadioButton(HWND hdlg, int idrFirst, int idrLast)
{
	int id;
	for (id = idrFirst; id<=idrLast; id++)
	{
		if(IsDlgButtonChecked(hdlg, id))
			return id;
	}
	
	return idrFirst;
}


//****************************************************************************
// 
// BOOL MyIsGoodString(LPTSTR psz)
//
// determine if a string is NULL or empty
//
//****************************************************************************
BOOL MyIsGoodString(LPTSTR psz)
{
	if((psz == NULL) || 0 == strcmp(psz, ""))
		return FALSE;
	else
		return TRUE;
	
}


//****************************************************************************
// 
// HRESULT GetNMAttributesObject( IIlsAttributes **ppa )
//
// return a pointer to an Attribute object with NetMeeting
// ExtendedAttributes specified.
//
//****************************************************************************
HRESULT GetNMAttributesObject( IIlsMain *pIls, IIlsAttributes **ppa )
{
	HRESULT hr = E_FAIL;
	IIlsAttributes *pAttrib = NULL;


	hr = pIls->CreateAttributes(ILS_ATTRTYPE_NAME_VALUE, &pAttrib);

	if (SUCCEEDED(hr))
	{

		// got an Attributes object, now fill it in.
		BSTR bstrEmpty = NULL, bstrName = NULL;
		TCHAR szProperty[100];

		LPTSTR_to_BSTR(&bstrEmpty, "");

		wsprintf(szProperty, TEXT("%lu"), PROP_TAG(PT_STRING8, NM_IN_A_CALL));  // 400
		LPTSTR_to_BSTR(&bstrName, szProperty);
		hr = pAttrib->SetAttribute(bstrName, bstrEmpty);

		wsprintf(szProperty, TEXT("%lu"), PROP_TAG(PT_STRING8, NM_RESTRICTION));  // 600
		LPTSTR_to_BSTR(&bstrName, szProperty);
		hr = pAttrib->SetAttribute(bstrName, bstrEmpty);

		wsprintf(szProperty, TEXT("%lu"), PROP_TAG(PT_STRING8, NM_SEND_AUDIO));  // 501
		LPTSTR_to_BSTR(&bstrName, szProperty);
		hr = pAttrib->SetAttribute(bstrName, bstrEmpty);

		wsprintf(szProperty, TEXT("%lu"), PROP_TAG(PT_STRING8, NM_SEND_VIDEO));  // 503
		LPTSTR_to_BSTR(&bstrName, szProperty);
		hr = pAttrib->SetAttribute(bstrName, bstrEmpty);

	}
	*ppa = pAttrib;
	
	return hr;
}
