
/******************************************************************************\
********************************************************************************
* Filename: InstanceSink.h
*
* Description:  Sink for Instance Events
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

#ifndef __INSTANCESINK_H__
#define __INSTANCESINK_H__

#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

class CMtsSpy;

/////////////////////////////////////////////////////////////////////////////
// CInstanceSink 
class ATL_NO_VTABLE CInstanceSink : 
	public CMtsSink,
	public IMtsInstanceEvents
{
public:
	CInstanceSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}

	CInstanceSink()
	{
		m_pSpy = NULL;
	}

DECLARE_NOT_AGGREGATABLE(CInstanceSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CInstanceSink)
	COM_INTERFACE_ENTRY(IMtsInstanceEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

virtual REFIID GetIID(){return IID_IMtsInstanceEvents;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = Instance;return S_OK;}

STDMETHODIMP OnObjectCreate(LONGLONG perfCount, REFGUID guidActivity, REFCLSID clsid, REFGUID tsid, MTS_OBJID ObjectID)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnObjectCreate"), m_sPackageName);
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", ObjectID);

    CComBSTR sGuidActivity = GuidToBstr(guidActivity);
    CComBSTR sClsid = GuidToBstr(clsid);
    CComBSTR sTsid = GuidToBstr(tsid);

	m_pSpy -> AddParamValueToList(L"ObjectID", id);
	m_pSpy -> AddParamValueToList(L"guidActivity", sGuidActivity);
	m_pSpy -> AddParamValueToList(L"clsid", sClsid);
	m_pSpy -> AddParamValueToList(L"tsid", sTsid);
	IF_AUDIT_DO(OnObjectCreate)(perfCount,							
								sGuidActivity,						
								sClsid,						
								sTsid,			
								ObjectID);

	return S_OK;
}

STDMETHODIMP OnObjectRelease(LONGLONG perfCount, MTS_OBJID ObjectID)
{
	WCHAR p1[32];
	wsprintfW(p1, L"ObjectID: %ld", ObjectID);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnObjectRelease"), m_sPackageName);
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", ObjectID);
	m_pSpy -> AddParamValueToList(L"ObjectID", id);
	IF_AUDIT_DO(OnObjectRelease)(perfCount,														
								 ObjectID);

	return S_OK;
}

};

#endif //__INSTANCESINK_H__
