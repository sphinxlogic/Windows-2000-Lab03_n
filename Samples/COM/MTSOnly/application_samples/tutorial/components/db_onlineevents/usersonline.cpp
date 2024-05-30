// UsersOnline.cpp : Implementation of CDb_OnlineEventsApp and DLL registration.

#include "stdio.h"
#include "stdafx.h"
#include "db_OnlineEvents.h"
#include "UsersOnline.h"

//#include <public.h>

#import "msado15.dll" rename("EOF","ADOEOF")
using namespace ADODB;

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP UsersOnline::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUsersOnline,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP UsersOnline::Update(BSTR strCustomerID)
{
	HRESULT hr = S_OK;

	IObjectContext* pObjectContext = NULL;	

	long lErrFlag = 0;
	hr = GetObjectContext(&pObjectContext);
	if (!pObjectContext)
	{
		AtlReportError( CLSID_UsersOnline, "No Object Context", IID_IUsersOnline, hr);
		return hr;
	}

	if (wcscmp(strCustomerID,m_strTableName) == 0) return S_FALSE;

	// Pointer to an ADO connection
	_ConnectionPtr pObjADO_Connection;

	// Create ADO connection
	hr = ::CoCreateInstance(__uuidof(Connection), NULL, CLSCTX_SERVER,
		__uuidof(_Connection), (LPVOID*)&pObjADO_Connection);
	if (FAILED(hr)) 
	{
		AtlReportError( CLSID_UsersOnline, "No Object Context", IID_IUsersOnline, hr);
		return hr;
	}


	// DSN file specification
	bstr_t strDSN = L"DSN=Tracey_Online;UID=sa;PWD=;";

	// Setup the insert statement
	TCHAR szBuffer [512];
	wsprintf (szBuffer, _T("Insert into %s  (EventType, EventID, EventDesc, EventLink) VALUES (%d, '%s', '%s', '%s')"),
		m_strTableName, 1, strCustomerID, L"", L"");
	BSTR bstrSQL = TCHAR2BSTR (szBuffer);

	// Open the connection
	hr = pObjADO_Connection->Open(strDSN, (BSTR) NULL, (BSTR) NULL, -1);

	if (FAILED(hr))
	{
		//pObjectContext -> SetAbort();
		//SafeRelease(pObjectContext);
		AtlReportError( CLSID_UsersOnline, "Error opening connection", IID_IUsersOnline, hr);
		return hr;
	}

	// Execute the SQL statement
	hr = pObjADO_Connection->Execute(bstrSQL, NULL, adCmdText);

	if (FAILED(hr))
	{
		//pObjectContext -> SetAbort();
		//SafeRelease(pObjectContext);
		AtlReportError( CLSID_UsersOnline, "Error updating OnlineEvents Table", IID_IUsersOnline, hr);
		return hr;
	}


	// We are finished and happy
	// pObjectContext->SetComplete();

	return hr;
}

STDMETHODIMP UsersOnline::PreEventCall(IUnknown *pIUnknown)
{
	HRESULT hr;
    IEventSubscription* pIEventSubscription = NULL;
	BSTR		PropertyBagName;
	CComVariant	PropertyBagValue;

	PropertyBagName = ::SysAllocString(L"Table");
	// VariantInit (&PropertyBagValue);

    hr = pIUnknown->QueryInterface(IID_IEventSubscription, (void **) &pIEventSubscription);
	if (FAILED(hr))
		return hr;
    
    hr = pIEventSubscription->GetSubscriberProperty(PropertyBagName, &PropertyBagValue);
	if (FAILED(hr))
		return hr;

	::SysFreeString(PropertyBagName);

	wcscpy(m_strTableName, PropertyBagValue.bstrVal);

	return hr;
}
