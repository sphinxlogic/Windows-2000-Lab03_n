
/******************************************************************************\
********************************************************************************
* Filename: ThreadSink.h
*
* Description: Declaration of the CThreadSink -- the sink for Thread Events
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


#ifndef __THREADSINK_H__
#define __THREADSINK_H__

#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

class CMtsSpy;

/////////////////////////////////////////////////////////////////////////////
// CThreadSink 
class ATL_NO_VTABLE CThreadSink : 
	public CMtsSink,
	public IMtsThreadEvents
{
public:

	CThreadSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CThreadSink()
	{
		m_pSpy = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TXSINK)
DECLARE_NOT_AGGREGATABLE(CThreadSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CThreadSink)
	COM_INTERFACE_ENTRY(IMtsThreadEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

virtual REFIID GetIID(){return IID_IMtsThreadEvents;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = Thread;return S_OK;}

STDMETHODIMP OnThreadStart(LONGLONG perfCount, ULONG ThreadId)
{
	WCHAR p1[16];
	wsprintfW(p1,L"0x%08X", ThreadId);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnThreadStart"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ThreadID", p1);
	IF_AUDIT_DO(OnThreadStart)(perfCount, ThreadId);
	return S_OK;
}

STDMETHODIMP OnThreadTerminate(LONGLONG perfCount, ULONG ThreadId)
{
	WCHAR p1[16];
	wsprintfW(p1,L"0x%08X", ThreadId);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnThreadTerminate"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ThreadID", p1);
	IF_AUDIT_DO(OnThreadTerminate)(perfCount, ThreadId);
	return S_OK;
}

STDMETHODIMP OnThreadAssignToActivity(LONGLONG perfCount, REFGUID guidActivity, ULONG ThreadId)
{
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", ThreadId);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnThreadAssignToActivity"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ThreadID", id);

    CComBSTR sGuidActivity = GuidToBstr(guidActivity);
	m_pSpy -> AddParamValueToList(L"guidActivity", sGuidActivity);
	IF_AUDIT_DO(OnThreadAssignToActivity)(perfCount, sGuidActivity, ThreadId);
	return S_OK;
}

STDMETHODIMP OnThreadUnassignFromActivity(LONGLONG perfCount, REFGUID guidActivity, ULONG ThreadId)
{
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", ThreadId);
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnThreadUnassignFromActivity"), m_sPackageName);
	m_pSpy -> AddParamValueToList(L"ThreadID", id);

    CComBSTR sGuidActivity = GuidToBstr(guidActivity);
	m_pSpy -> AddParamValueToList(L"guidActivity", sGuidActivity);
	IF_AUDIT_DO(OnThreadUnassignFromActivity)(perfCount, sGuidActivity, ThreadId);
	return S_OK;
}

};

#endif //__THREADSINK_H__
