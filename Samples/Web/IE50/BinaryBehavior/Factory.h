//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
// Factory.h : Declaration of the CFactory

#ifndef __FACTORY_H_
#define __FACTORY_H_

#include "resource.h"       // main symbols
#include "behavior.h"

/////////////////////////////////////////////////////////////////////////////
// CFactory
class ATL_NO_VTABLE CFactory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFactory, &CLSID_Factory>,
	public IObjectSafetyImpl<CFactory,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IElementBehaviorFactory
{
public:
	CFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FACTORY)

BEGIN_COM_MAP(CFactory)
	COM_INTERFACE_ENTRY(IElementBehaviorFactory)
	COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// IFactory
public:
	STDMETHOD(FindBehavior)(BSTR pchNameSpace,
							BSTR pchTagName,
							IElementBehaviorSite* pUnkArg,
							IElementBehavior** ppBehavior);

// IObjectSafety override
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
	{	// Set the safety options we have been asked to set
		m_dwCurrentSafety = m_dwCurrentSafety  & ~dwEnabledOptions | dwOptionSetMask;
		return S_OK;
	}
};

#endif //__FACTORY_H_
