
/******************************************************************************\
********************************************************************************
* Filename: ResourceSink.cpp
*
* Description: Sink for resource events
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
// ResourceSink.cpp : Implementation of CResourceSink
#include "stdafx.h"
#include "mtsspyctl.h"
#include "mtsevents.h"
#include "MtsAudit.h"
#include "MTSSpy.h"
#include "MtsSink.h"
#include "packagesink.h"
#include "PackageInfo.h"
#include "ResourceSink.h"

/////////////////////////////////////////////////////////////////////////////
// CResourceSink

STDMETHODIMP CResourceSink::OnResourceCreate(
    LONGLONG perfCount, 
	REFGUID guidActivity,
	MTS_OBJID ObjectID,
    LPCOLESTR pszType,
    MTS_RESID resId)
{
	
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnResourceCreate"), m_sPackageName);

	CComBSTR sActivity = GuidToBstr(guidActivity);
	m_pSpy -> AddParamValueToList(L"ActivityGuid", sActivity);

	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR p2[16];
	wsprintfW(p2, L"0x%08X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", p2);


	wsprintfW(p2, L"0x%08X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", p2);


	IF_AUDIT_DO(OnResourceCreate)(perfCount, sActivity, ObjectID, pszType, resId);


	return S_OK;
}


STDMETHODIMP CResourceSink::OnResourceAllocate(
	LONGLONG perfCount, 
	REFGUID guidActivity,    
	MTS_OBJID ObjectID,
    LPCOLESTR pszType,
    MTS_RESID resId)
{
	
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnResourceAllocate"),m_sPackageName);
	CComBSTR sActivity = GuidToBstr(guidActivity);
	m_pSpy -> AddParamValueToList(L"ActivityGuid", sActivity);

	m_pSpy -> AddParamValueToList(L"Type", pszType);

	

	WCHAR p2[16];
	wsprintfW(p2, L"0x%08X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", p2);


	wsprintfW(p2, L"0x%08X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", p2);
	IF_AUDIT_DO(OnResourceAllocate)(perfCount, sActivity, ObjectID, pszType, resId);
	return S_OK;
}


STDMETHODIMP CResourceSink::OnResourceRecycle(
	LONGLONG perfCount, 
	MTS_OBJID ObjectID,
    LPCOLESTR pszType,
    MTS_RESID resId)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnResourceRecycle"),m_sPackageName);
	
	m_pSpy -> AddParamValueToList(L"Type", pszType);


	WCHAR p2[16];
	if (ObjectID)
	{
		wsprintfW(p2, L"0x%08X", ObjectID);
		m_pSpy -> AddParamValueToList(L"ObjectID", p2);
	}


	wsprintfW(p2, L"0x%08X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", p2);
	IF_AUDIT_DO(OnResourceRecycle)(perfCount, ObjectID, pszType, resId);
	return S_OK;
}


STDMETHODIMP CResourceSink::OnResourceDestroy(
    LONGLONG perfCount, 
	MTS_OBJID ObjectID,
    LPCOLESTR pszType,
    MTS_RESID resId)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnResourceDestroy"),m_sPackageName);
	
	m_pSpy -> AddParamValueToList(L"Type", pszType);

	WCHAR p2[16];
	if (ObjectID)
	{
		wsprintfW(p2, L"0x%08X", ObjectID);
		m_pSpy -> AddParamValueToList(L"ObjectID", p2);
	}


	wsprintfW(p2, L"0x%08X", resId);
	m_pSpy -> AddParamValueToList(L"ResourceID", p2);

	IF_AUDIT_DO(OnResourceDestroy)(perfCount, ObjectID, pszType, resId);
	return S_OK;
}
