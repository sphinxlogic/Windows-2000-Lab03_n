// HBImpl.h : Declaration of the CHBImpl

#ifndef __HBIMPL_H_
#define __HBIMPL_H_

#include "resource.h"       // main symbols

typedef void (*NEWSHEADLINE)(BSTR);

/////////////////////////////////////////////////////////////////////////////
// CHBImpl
class ATL_NO_VTABLE CHBImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHBImpl, &__uuidof(HBEventClass)>,
	public IDispatchImpl<IHB, &__uuidof(IHB), &LIBID_HBEVENTCLASSLib>,
	public INewsService
	{
public:
	CHBImpl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_HBIMPL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

//DECLARE_NOT_AGGREGATABLE(CHBImpl)

BEGIN_COM_MAP(CHBImpl)
	COM_INTERFACE_ENTRY(IHB)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(INewsService)
END_COM_MAP()

// IHB
public:

		// IDispatch methods
	STDMETHOD (GetTypeInfo)(UINT, LCID, ITypeInfo**){return E_NOTIMPL;}
	STDMETHOD (GetIDsOfNames)(REFIID, LPOLESTR*, UINT, LCID, DISPID*) {return E_NOTIMPL;}
	STDMETHOD (GetTypeInfoCount)(UINT*){return E_NOTIMPL;}
	STDMETHOD (Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*){return E_NOTIMPL;}

	STDMETHOD (NewsHeadlineNotify)( NEWSHEADLINE){ return E_NOTIMPL;}

		// IHB methods
	STDMETHOD (NewEvent)(BSTR) {return E_NOTIMPL;}

	// INewsService methods
	STDMETHOD (NewsHeadline)(BSTR) {return E_NOTIMPL;}
	STDMETHOD (HotNews)(BSTR) {return E_NOTIMPL;}
};

#endif //__HBIMPL_H_
