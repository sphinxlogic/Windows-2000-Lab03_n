
/******************************************************************************\
********************************************************************************
* Filename: MethodSink.h
*
* Description: Declration of Method Sink
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

#ifndef __METHODSINK_H__
#define __METHODSINK_H__

#include "resource.h"       // main symbols

typedef list<LONGLONG> TimeStack;
typedef map<MTS_OBJID, TimeStack *> TimeMap;
class CMtsSpy;

/////////////////////////////////////////////////////////////////////////////
// CMethodSink 
class ATL_NO_VTABLE CMethodSink : 
	public CMtsSink,
	public IMtsMethodEvents
{
public:

	TimeMap m_map;
	CMethodSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CMethodSink()
	{
		m_pSpy = NULL;
	}

DECLARE_NOT_AGGREGATABLE(CMethodSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CMethodSink)
	COM_INTERFACE_ENTRY(IMtsMethodEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

virtual REFIID GetIID(){return IID_IMtsMethodEvents;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = Method;return S_OK;}


STDMETHOD(OnMethodCall)(LONGLONG perfCount, MTS_OBJID oid, REFCLSID cid, REFIID rid, ULONG iMeth);
STDMETHOD(OnMethodReturn)(LONGLONG perfCount, MTS_OBJID oid, REFCLSID cid, REFIID rid, ULONG iMeth, HRESULT hr);
STDMETHOD(OnMethodException)(LONGLONG perfCount, MTS_OBJID oid, REFCLSID cid, REFIID rid, ULONG iMeth);
STDMETHOD(Advise)();

HRESULT GetClsidOfTypeLib2 (IID * piid, UUID * puuidClsid);
HRESULT GetMethodName (REFIID riid, int iMeth, _TCHAR** ppszMethodName);

};
#endif //__METHODSINK_H__


