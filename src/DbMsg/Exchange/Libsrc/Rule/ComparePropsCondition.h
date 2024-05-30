// ----------------------------------------------------------------------------
//	ComparePropsCondition.h : Declaration of the CComparePropsCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __COMPAREPROPSCONDITION_H_
#define __COMPAREPROPSCONDITION_H_

#include "resource.h"       // main symbols

// CComparePropsCondition
class ATL_NO_VTABLE CComparePropsCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CComparePropsCondition, &CLSID_ComparePropsCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<IComparePropsCondition, &IID_IComparePropsCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CComparePropsCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_COMPAREPROPSCONDITION)

BEGIN_COM_MAP(CComparePropsCondition)
	COM_INTERFACE_ENTRY(IComparePropsCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,IComparePropsCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	HRESULT		load(LPSRestriction	lpRes);
	HRESULT		pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IComparePropsCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_PropertyTag2)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyTag2)(/*[in]*/ long newVal);
	STDMETHOD(get_PropertyTag1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyTag1)(/*[in]*/ long newVal);
	STDMETHOD(get_Operator)(/*[out, retval]*/ RELOP_TYPES *pVal);
	STDMETHOD(put_Operator)(/*[in]*/ RELOP_TYPES newVal);
private:
	long			m_lPropTag1;
	long			m_lPropTag2;
	RELOP_TYPES		m_relOperator;
};
typedef CComObject<CComparePropsCondition>	CComparePropsResObject;

#endif //__COMPAREPROPSCONDITION_H_
