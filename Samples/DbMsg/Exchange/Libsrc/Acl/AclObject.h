/* --------------------------------------------------------------------------

The header file for ACLObject Object

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// ACLObject.h : Declaration of the CACLObject

#ifndef __ACLOBJECT_H_
#define __ACLOBJECT_H_

#include "resource.h"       // main symbols
#include "ACECollection.h"

/////////////////////////////////////////////////////////////////////////////
// CACLObject
class ATL_NO_VTABLE CACLObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CACLObject, &CLSID_ACLObject>,
	public ISupportErrorInfo,
	public IDispatchImpl<IACLObject, &IID_IACLObject, &LIBID_MSExchangeACLLib>
{
public:
	CACLObject() : m_pACECollection(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ACLOBJECT)
DECLARE_NOT_AGGREGATABLE(CACLObject)

BEGIN_COM_MAP(CACLObject)
	COM_INTERFACE_ENTRY(IACLObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IACLObject
public:
	STDMETHOD(Update)();
	STDMETHOD(get_ACEs)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_CDOItem)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(putref_CDOItem)(/*[in]*/ LPDISPATCH newVal);
	
	STDMETHOD(FinalConstruct)();
	STDMETHOD(FinalRelease)();

private:
	// a smart pointer to ACE Collection
	CComPtr<IACEs> m_pACECollection;
};

#endif //__ACLOBJECT_H_
