//====================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//=====================================================================
// CheckNTUserImp.cpp : Implementation of CCheckNTUserImp
#include "stdafx.h"
#include "CheckNTUser.h"
#include "CheckNTUserImp.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckNTUserImp

STDMETHODIMP CCheckNTUserImp::OnStartPage (IUnknown* pUnk)  
{
	if(!pUnk)
		return E_POINTER;

	CComPtr<IScriptingContext> spContext;
	HRESULT hr;

	// Get the IScriptingContext Interface
	hr = pUnk->QueryInterface(IID_IScriptingContext, (void **)&spContext);
	if(FAILED(hr))
		return hr;

	// Get Request Object Pointer
	hr = spContext->get_Request(&m_piRequest);
	if(FAILED(hr))
	{
		spContext.Release();
		return hr;
	}

	// Get Response Object Pointer
	hr = spContext->get_Response(&m_piResponse);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		return hr;
	}
    
#if 0	
	// Get Server Object Pointer
	hr = spContext->get_Server(&m_piServer);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		m_piResponse.Release();
		return hr;
	}
	
	// Get Session Object Pointer
	hr = spContext->get_Session(&m_piSession);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		m_piResponse.Release();
		m_piServer.Release();
		return hr;
	}

	// Get Application Object Pointer
	hr = spContext->get_Application(&m_piApplication);
	if(FAILED(hr))
	{
		m_piRequest.Release();
		m_piResponse.Release();
		m_piServer.Release();
		m_piSession.Release();
		return hr;
	}
#endif
    
	m_bOnStartPageCalled = TRUE;
	return S_OK;
}

STDMETHODIMP CCheckNTUserImp::OnEndPage ()  
{
	m_bOnStartPageCalled = FALSE;
	// Release all interfaces
	m_piRequest.Release();
	m_piResponse.Release();
#if 0    
	m_piServer.Release();
	m_piSession.Release();
	m_piApplication.Release();
#endif
    
	return S_OK;
}


STDMETHODIMP CCheckNTUserImp::CheckNTUser(BSTR bszUserName, BSTR bszDomain, BSTR bszPassword, LONG * plPasswordVerified)
{
	 HANDLE hToken;
    
    if (bszDomain == NULL || bszDomain[0] == L'\0')
        bszDomain = L".";

    if (LogonUserW(bszUserName, bszDomain, bszPassword, LOGON32_LOGON_NETWORK, LOGON32_PROVIDER_DEFAULT, &hToken) == FALSE)
    {
        *plPasswordVerified = FALSE;
        return NOERROR;
    }

    *plPasswordVerified = TRUE;    
    CloseHandle(hToken);

	return S_OK;
}
