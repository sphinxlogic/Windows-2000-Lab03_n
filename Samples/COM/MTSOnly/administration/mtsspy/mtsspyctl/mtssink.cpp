
/******************************************************************************\
********************************************************************************
* Filename: MtsSink.cpp
*
* Description: implementation of CMtsSink
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/
#include "stdafx.h"
#include "mtsspyctl.h"
#include "mtsevents.h"
#include "MtsAudit.h"
#include "MTSSpy.h"
#include "MtsSink.h"
#include "packagesink.h"
#include "PackageInfo.h"


/////////////////////////////////////////////////////////////////////////////
// CMtsSink


STDMETHODIMP CMtsSink::Init(IConnectionPointContainer * pConPt, LPWSTR sPackageName)
{
	
	m_sPackageName = sPackageName;
	m_pCPC = pConPt;				
	m_pCPC -> AddRef();
	return S_OK;
}

STDMETHODIMP CMtsSink::Advise()
{
	if (m_dwAdviseCookie)
		return E_FAIL;

	_ASSERTE(m_pCPC);
	HRESULT hr;
	hr = m_pCPC -> FindConnectionPoint(GetIID(), &m_pConPt);
	if (hr == S_OK)
	{
		hr = m_pConPt -> Advise(GetControllingUnknown(), &m_dwAdviseCookie);						
		_ASSERTE(hr == S_OK);
	}

	return hr;
}

STDMETHODIMP CMtsSink::DAdvise()
{

	if (!m_pConPt)
		return E_FAIL;

	m_pConPt -> Unadvise(m_dwAdviseCookie);
	m_dwAdviseCookie = 0;
	return S_OK;
}


STDMETHODIMP CMtsSink::get_DeleteFlag(BOOL * pVal)
{
	
	*pVal = m_bReadyForDelete;
	return S_OK;
}

STDMETHODIMP CMtsSink::put_DeleteFlag(BOOL newVal)
{
	m_bReadyForDelete = newVal;
	return S_OK;
}
