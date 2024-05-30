
/******************************************************************************\
********************************************************************************
* Filename: ObjSink.h
*
* Description: Sink for Object events.
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

#ifndef __OBJSINK_H__
#define __OBJSINK_H__

#include "resource.h"       // main symbols
//#include "..\mtsevents\eventcpts.h"

class CMtsSpy;
/////////////////////////////////////////////////////////////////////////////
// CObjSink 
class ATL_NO_VTABLE CObjSink : 
	public CMtsSink,
	public IMtsObjectEvents
{
public:
	CObjSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}

	CObjSink()
	{
		m_pSpy = NULL;
	}


DECLARE_NOT_AGGREGATABLE(CObjSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CObjSink)
	COM_INTERFACE_ENTRY(IMtsObjectEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

virtual REFIID GetIID(){return IID_IMtsObjectEvents;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = Object;return S_OK;}

STDMETHODIMP OnDisableCommit(LONGLONG perfCount, MTS_OBJID ObjectID)
{
	WCHAR p1[16];
	wsprintfW(p1, L"0x%08X", ObjectID);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnDisableCommit"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ObjectID", p1);
	return S_OK;
}

STDMETHODIMP  OnEnableCommit(LONGLONG perfCount, MTS_OBJID ObjectID)
{
	WCHAR p1[16];
	wsprintfW(p1, L"0x%08X", ObjectID);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnEnableCommit"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ObjectID", p1);
	IF_AUDIT_DO(OnEnableCommit)(perfCount, ObjectID);
	return S_OK;
}

STDMETHODIMP  OnSetComplete(LONGLONG perfCount, MTS_OBJID ObjectID)
{
	WCHAR p1[16];
	wsprintfW(p1,  L"0x%08X", ObjectID);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnSetComplete"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ObjectID", p1);
	IF_AUDIT_DO(OnSetComplete)(perfCount, ObjectID);
	return S_OK;
}

STDMETHODIMP  OnObjectDeactivate(LONGLONG perfCount, MTS_OBJID ObjectID)
{
	WCHAR p1[16];
	wsprintfW(p1,L"0x%08X", ObjectID);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnObjectDeactivate"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ObjectID", p1);
	IF_AUDIT_DO(OnObjectDeactivate)(perfCount, ObjectID);

	return S_OK;
}

STDMETHODIMP  OnObjectActivate(LONGLONG perfCount, MTS_OBJID ObjectID)
{
	WCHAR p1[16];
	wsprintfW(p1,L"0x%08X", ObjectID);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnObjectActivate"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ObjectID", p1);
	IF_AUDIT_DO(OnObjectActivate)(perfCount, ObjectID);
	return S_OK;
}

};

#endif //__OBJSINK_H__
