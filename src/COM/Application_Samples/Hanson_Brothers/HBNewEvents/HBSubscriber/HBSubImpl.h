// HBSubImpl.h : Declaration of the CHBSubImpl

#ifndef __HBSUBIMPL_H_
#define __HBSUBIMPL_H_

#include "resource.h"       // main symbols

typedef void (*NEWSHEADLINE)(BSTR);

/////////////////////////////////////////////////////////////////////////////
// CHBSubImpl
class ATL_NO_VTABLE CHBSubImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHBSubImpl, &__uuidof(HBSubscriber)>,
	public IDispatchImpl<IHB, &__uuidof(IHB), &LIBID_HBSUBSCRIBERLib>,
	public INewsService
	{
public:
	CHBSubImpl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_HBSUBIMPL)

//DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_NOT_AGGREGATABLE(CHBSubImpl)

BEGIN_COM_MAP(CHBSubImpl)
	COM_INTERFACE_ENTRY(IHB)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(INewsService)
END_COM_MAP()

// IHBSub
public:

			// IDispatch methods
	STDMETHOD (GetTypeInfo)(UINT, LCID, ITypeInfo**){return E_NOTIMPL;}
	STDMETHOD (GetIDsOfNames)(REFIID, LPOLESTR*, UINT, LCID, DISPID*) {return E_NOTIMPL;}
	STDMETHOD (GetTypeInfoCount)(UINT*){return E_NOTIMPL;}
	STDMETHOD (Invoke)(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*){return E_NOTIMPL;}

	// Store notification call
	STDMETHOD (NewsHeadlineNotify)( NEWSHEADLINE);


		// IHB methods
	STDMETHOD (NewEvent)(BSTR);

	// INewsService methods
	STDMETHOD (NewsHeadline)(BSTR);
	STDMETHOD (HotNews)(BSTR);

private:
	HRESULT CommonMethod(TCHAR* tzmethod, BSTR bstr);

	NEWSHEADLINE m_pgb; // Pointer to client function
};

#endif //__HBSUBIMPL_H_
