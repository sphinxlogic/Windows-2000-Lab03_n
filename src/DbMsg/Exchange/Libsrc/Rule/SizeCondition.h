// ----------------------------------------------------------------------------
//	SizeCondition.h : Declaration of the CSizeCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __SIZECONDITION_H_
#define __SIZECONDITION_H_

#include "resource.h"       // main symbols

// CSizeCondition
class ATL_NO_VTABLE CSizeCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSizeCondition, &CLSID_SizeCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<ISizeCondition, &IID_ISizeCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CSizeCondition(){m_lPropTag=0;m_lSize=0;m_relOperator=REL_EQ;}

DECLARE_REGISTRY_RESOURCEID(IDR_SIZECONDITION)

BEGIN_COM_MAP(CSizeCondition)
	COM_INTERFACE_ENTRY(ISizeCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,ISizeCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	HRESULT		load(LPSRestriction lpRes);
	HRESULT		pack(LPSRestriction lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// ISizeCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_Size)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Size)(/*[in]*/ long newVal);
	STDMETHOD(get_PropertyTag)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyTag)(/*[in]*/ long newVal);
	STDMETHOD(get_Operator)(/*[out, retval]*/ RELOP_TYPES *pVal);
	STDMETHOD(put_Operator)(/*[in]*/ RELOP_TYPES newVal);
private:
	long		m_lPropTag;
	long		m_lSize;
	RELOP_TYPES	m_relOperator;
};
typedef CComObject<CSizeCondition>	CSizeResObject;

#endif //__SIZECONDITION_H_
