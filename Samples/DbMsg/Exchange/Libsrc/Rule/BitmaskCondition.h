// ----------------------------------------------------------------------------
//	BitmaskCondition.h : Declaration of the CBitmaskCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __BITMASKCONDITION_H_
#define __BITMASKCONDITION_H_

#include "resource.h"       // main symbols

// CBitmaskCondition
class ATL_NO_VTABLE CBitmaskCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBitmaskCondition, &CLSID_BitmaskCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<IBitmaskCondition, &IID_IBitmaskCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CBitmaskCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_BITMASKCONDITION)

BEGIN_COM_MAP(CBitmaskCondition)
	COM_INTERFACE_ENTRY(IBitmaskCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,IBitmaskCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	virtual HRESULT	load(LPSRestriction lpRes);
	virtual HRESULT	pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IBitmaskCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_Value)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Value)(/*[in]*/ long newVal);
	STDMETHOD(get_PropertyTag)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyTag)(/*[in]*/ long newVal);
	STDMETHOD(get_Operator)(/*[out, retval]*/ BITMAPOP_TYPES *pVal);
	STDMETHOD(put_Operator)(/*[in]*/ BITMAPOP_TYPES newVal);
private:
	long			m_lValue;
	BITMAPOP_TYPES	m_bmpOp;
	long			m_lPropTag;
};
typedef CComObject<CBitmaskCondition>	CBitmaskResObject;

#endif //__BITMASKCONDITION_H_
