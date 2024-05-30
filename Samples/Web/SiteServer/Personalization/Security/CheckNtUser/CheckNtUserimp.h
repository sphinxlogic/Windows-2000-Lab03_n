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
// CheckNTUserImp.h : Declaration of the CCheckNTUserImp

#ifndef __CHECKNTUSERIMP_H_
#define __CHECKNTUSERIMP_H_

#include "resource.h"       // main symbols
#include <asptlb.h>         // Active Server Pages Definitions

/////////////////////////////////////////////////////////////////////////////
// CCheckNTUserImp
class ATL_NO_VTABLE CCheckNTUserImp : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCheckNTUserImp, &CLSID_CheckNTUserImp>,
	public IDispatchImpl<ICheckNTUserImp, &IID_ICheckNTUserImp, &LIBID_CHECKNTUSERLib>
{
public:
	CCheckNTUserImp()
	{ 
		m_bOnStartPageCalled = FALSE;
	}

public:

DECLARE_REGISTRY_RESOURCEID(IDR_CHECKNTUSERIMP)

BEGIN_COM_MAP(CCheckNTUserImp)
	COM_INTERFACE_ENTRY(ICheckNTUserImp)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ICheckNTUserImp
public:
	STDMETHOD(CheckNTUser)(BSTR bszUserName, BSTR bszDomain, BSTR bszPassword, /*[out, retval]*/ LONG * plPasswordVerified);
	//Active Server Pages Methods
	STDMETHOD(OnStartPage)(IUnknown* IUnk);
	STDMETHOD(OnEndPage)();

private:
	CComPtr<IRequest> m_piRequest;					//Request Object
	CComPtr<IResponse> m_piResponse;				//Response Object
	CComPtr<ISessionObject> m_piSession;			//Session Object
	CComPtr<IServer> m_piServer;					//Server Object
	CComPtr<IApplicationObject> m_piApplication;	//Application Object
	BOOL m_bOnStartPageCalled;						//OnStartPage successful?
};

#endif //__CHECKNTUSERIMP_H_
