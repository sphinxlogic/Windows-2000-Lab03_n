// Filename: CAccount.cpp
//
// Description: Implementation of CAccount
//
// This file is provided as part of the Microsoft Transaction Server
// Software Development Kit
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 Microsoft Corporation, All rights reserved
#include "stdafx.h"
#include "Account.h"
#include "CAccount.h"
#include <stdio.h>

#include <mtx.h>

#include <adoid.h>
#include <adoint.h>

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CAccount::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAccount,
	};
	
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	Post: modifies the specified account by the specified amount
//
//	pbstrResult: a BSTR giving information.  NOTE: this is set to NULL when an error occurs
//
//	returns:  S_OK or E_FAIL

STDMETHODIMP CAccount::Post (IN long lAccount, IN long lAmount, OUT BSTR* pbstrResult) {

	HRESULT hr = S_OK;

	IObjectContext* pObjectContext = NULL;

	ADOConnection* adoCoConnection = NULL;
	ADORecordset* adoRsBalance = NULL;
	ADOFields* pFields = NULL;
	ADOField* pField = NULL;

	*pbstrResult = NULL;

	long lErrFlag = 0;
	TCHAR* pErrMsg = NULL;

	try {

		// Get our object context
		THROW_ERR (GetObjectContext(&pObjectContext), "GetObjectContext" );

		// Check security for large transfers
		if (lAmount > 500 || lAmount < -500) {
			BOOL bInRole;
			BSTR bstrRole;
		
			bstrRole = ::SysAllocString(L"Managers");
			hr = pObjectContext->IsCallerInRole (bstrRole, &bInRole);
			::SysFreeString(bstrRole);
			
			if (!SUCCEEDED ( hr )) {
				THROW_STR ( _T("IsCallerInRole() call failed!  Please add the 'Managers' Roll to the package."));
			}
			
			if (!bInRole) {
				THROW_STR ( _T("Need 'Managers' role for amounts over $500") );
			}
		}

		// Create ADOConnection object and initialize the connection
		THROW_ERR ( CoCreateInstance (CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER, IID_IADOConnection,
			(LPVOID *) &adoCoConnection), "CoCreateInstance(CADOConnection)" );

		BSTR bstrDSN = ::SysAllocString (L"FILEDSN=MTSSamples");
		hr = adoCoConnection->Open (bstrDSN, NULL, NULL, adCmdUnspecified);
		::SysFreeString (bstrDSN);
		RETHROW_ERR(hr);			

		// Update the account balance and
		// then check to see if account would be overdrawn
		TCHAR szBuffer [512];
		wsprintf (szBuffer, _T("UPDATE Account SET Balance = Balance + %li WHERE AccountNo = %li"),
			lAmount, lAccount);
		BSTR bstrSQL = TCHAR2BSTR (szBuffer);
		CComVariant vRecordCount;
		vRecordCount.Clear();
		hr = adoCoConnection->Execute(bstrSQL, &vRecordCount, -1, NULL);
		::SysFreeString (bstrSQL);
		RETHROW_ERR(hr);			

		// If no records got updated, the account doesn't exist
		if (vRecordCount.lVal == 0) {
			TCHAR szBuffer1 [512];
			wsprintf (szBuffer1, _T("Error. Account %ld not on file."), lAccount);		
			THROW_STR ( szBuffer1 );
		}

		wsprintf (szBuffer, _T("SELECT Balance FROM Account WHERE AccountNo = %ld"), lAccount);
		bstrSQL = TCHAR2BSTR (szBuffer);
		hr = adoCoConnection->Execute (bstrSQL, &vRecordCount, -1, &adoRsBalance);
		::SysFreeString (bstrSQL);
		RETHROW_ERR(hr);			
		// Get the appropriate fields
		hr =  adoRsBalance->get_Fields(&pFields);
		RETHROW_ERR(hr);

		// Get the appropriate field
		CComVariant vField = L"Balance";
		CComVariant vBalance;
		hr = pFields->get_Item (vField, &pField) ;
		RETHROW_ERR(hr);			
		hr = pField->get_Value (&vBalance) ;
		RETHROW_ERR(hr);

		// Check for overdraw, then prepare return string
		if (vBalance.lVal < 0) {
	
			TCHAR szBuffer2 [512];
			wsprintf (szBuffer2, _T("Error. Account %ld would be overdrawn by %ld.  Balance is still %ld"),
				lAccount, vBalance.lVal, vBalance.lVal - lAmount);		
			THROW_STR ( szBuffer2 );
		}
		
		TCHAR szBuffer3 [512];
		wsprintf (szBuffer3, _T("%s account %ld, balance is $%ld. (VC++)"),
			((lAmount >= 0) ? _T("Credit to") : _T("Debit from")), lAccount, vBalance.lVal);
		*pbstrResult = TCHAR2BSTR (szBuffer3);

		// Resource cleanup
		if (pField) pField->Release();
		if (pFields) pFields->Release();
		if (adoRsBalance) adoRsBalance->Release();
		if (adoCoConnection) adoCoConnection->Release();
		
		// We are finished and happy
		pObjectContext->SetComplete();
	
		
	} catch (HRESULT hr) {

		//
		//	ErrorInfo is saved here because the following ADO cleanup code 
		//	may clear it.
		//
		IErrorInfo * pErrorInfo = NULL;
		GetErrorInfo(NULL, &pErrorInfo);

		if (pField)	pField->Release();
		if (pFields) pFields->Release();
		if (adoRsBalance) adoRsBalance->Release();
		if (adoCoConnection) adoCoConnection->Release();

		// Fill in error information
		switch (lErrFlag) {
		
		// Unknown error occurred in this object
		case (0):
			TCHAR szErr [512];
			wsprintf (szErr, _T("Error 0x%x from CAccount calling %s."), hr, pErrMsg);
			pErrMsg = szErr;
			// Fall through
		
		// An application error occurred in this object
		case (1):
			//
			//	we are going to put our own error in TLS, so if there is one there, clear it
			//
			if (pErrorInfo)
				pErrorInfo -> Release();
			
			AtlReportError( CLSID_CAccount, pErrMsg, IID_IAccount, hr);
			break;
		case (2): // ADO error
		{
			//
			//	put the error back in TLS
			//
			SetErrorInfo(NULL, pErrorInfo);

		}
		break;
		// Will never reach here
		default:			
			break;
		}
		
		// Indicate our unhappiness
		if (pObjectContext)
			pObjectContext->SetAbort();

	}

	if (pObjectContext)	pObjectContext->Release();

	return hr;
}