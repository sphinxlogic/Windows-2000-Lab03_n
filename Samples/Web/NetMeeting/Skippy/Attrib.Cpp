//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       attrib.cpp
//  Content:    This file contains attribute functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"


//****************************************************************************
//
// HRESULT EnumUserExAttributes(HWND hwnd, IIlsUser *pu)
//
// Retrieve an all extended attributes for this user.
//  
//****************************************************************************
HRESULT EnumUserExAttributes(HWND hwnd, IIlsUser *pu)
{
	IIlsAttributes *pAttributes;
	IEnumIlsNames *pEnumAttr;
	HRESULT hr = E_FAIL;
	BSTR bstrName = NULL, bstrValue = NULL;
	LPTSTR pszName = NULL, pszValue = NULL;

	// Enumerate the extended attributes for this user
	//
	hr = pu->GetAllExtendedAttributes(&pAttributes);

	if (SUCCEEDED(hr))
	{
		// success, enum the attributes values.
		//
		hr = pAttributes->EnumAttributes( &pEnumAttr ) ;
		if (SUCCEEDED(hr))
		{
			// success, walk the enumerator and print to the screen.
			//
			MyTextOut(TEXT("***** Found the following extended attributes *******\r\n"));

			while (pEnumAttr->Next(1, &bstrName, NULL) == NOERROR)
			{
				pu->GetExtendedAttribute(bstrName, &bstrValue);
				
				BSTR_to_LPTSTR(&pszName, bstrName);
				BSTR_to_LPTSTR(&pszValue, bstrValue);

				// Hmm... these "names" are pretty hard to read
				MyTextOut(TEXT("%ld = %s\r\n"), PROP_ID(atol(pszName)), pszValue);
				
				SysFreeString(bstrName);
				SysFreeString(bstrValue);
				FreeLPTSTR(pszName);
				FreeLPTSTR(pszValue);
			};
			pEnumAttr->Release();

			MyTextOut(TEXT("*****************************************************\r\n"));
		}
		else
			ErrorMessage(hwnd, TEXT("IIlsAttributes::EnumAttributes fails."), hr);
	}
	else
		ErrorMessage(hwnd, TEXT("IIlsUser::GetAllExtendedAttributes fails."), hr);

  return hr;
}

