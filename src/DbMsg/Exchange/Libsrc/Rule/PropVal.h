// ----------------------------------------------------------------------------
//	PropVal.h : Declaration of the CPropVal
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __PROPVAL_H_
#define __PROPVAL_H_

#include "resource.h"       // main symbols

// CPropVal
class ATL_NO_VTABLE CPropVal : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropVal, &CLSID_PropVal>,
	public ISupportErrorInfo,
	public IDispatchImpl<IPropVal, &IID_IPropVal, &LIBID_MSExchange>
{
public:
	CPropVal(){m_ulPropTag=0;::VariantInit(&m_lVariant);}
	~CPropVal();

DECLARE_REGISTRY_RESOURCEID(IDR_PROPVAL)

BEGIN_COM_MAP(CPropVal)
	COM_INTERFACE_ENTRY(IPropVal)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IPropVal
	STDMETHOD(get_Value)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Value)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_Tag)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Tag)(/*[in]*/ long newVal);

	void		cleanup();
	HRESULT		load(LPSPropValue lpPropValue);
	HRESULT		pack(LPSPropValue lpPropValue,LPVOID lpObject=NULL);
private:
	ULONG		m_ulPropTag;
	VARIANT		m_lVariant;
};
typedef CComObject<CPropVal>			CPropValObject;

#endif //__PROPVAL_H_
