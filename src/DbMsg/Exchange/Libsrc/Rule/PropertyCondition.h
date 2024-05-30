// ----------------------------------------------------------------------------
//	PropertyCondition.h : Declaration of the CPropertyCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __PROPERTYCONDITION_H_
#define __PROPERTYCONDITION_H_

#include "resource.h"       // main symbols

// CPropertyCondition
class ATL_NO_VTABLE CPropertyCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropertyCondition, &CLSID_PropertyCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<IPropertyCondition, &IID_IPropertyCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CPropertyCondition();
	~CPropertyCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYCONDITION)

BEGIN_COM_MAP(CPropertyCondition)
	COM_INTERFACE_ENTRY(IPropertyCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,IPropertyCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	HRESULT		load(LPSRestriction lpRes);
	HRESULT		pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IPropertyCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_Operator)(/*[out, retval]*/ RELOP_TYPES *pVal);
	STDMETHOD(put_Operator)(/*[in]*/ RELOP_TYPES newVal);
	STDMETHOD(get_Value)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Value)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(get_PropertyTag)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyTag)(/*[in]*/ long newVal);
private:
	CPropValPtr		*m_pPropValPtr;
	long			m_lPropTag;
	RELOP_TYPES		m_relOperator;
};
typedef CComObject<CPropertyCondition>	CPropertyResObject;

#endif //__PROPERTYCONDITION_H_
