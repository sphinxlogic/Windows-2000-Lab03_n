// ----------------------------------------------------------------------------
//	ExistsCondition.h : Declaration of the CExistsCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __EXISTSCONDITION_H_
#define __EXISTSCONDITION_H_

#include "resource.h"       // main symbols

// CExistsCondition
class ATL_NO_VTABLE CExistsCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExistsCondition, &CLSID_ExistsCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<IExistsCondition, &IID_IExistsCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CExistsCondition(){m_lPropTag=0;}

DECLARE_REGISTRY_RESOURCEID(IDR_EXISTSCONDITION)

BEGIN_COM_MAP(CExistsCondition)
	COM_INTERFACE_ENTRY(IExistsCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,IExistsCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	HRESULT		load(LPSRestriction	lpRes);
	HRESULT		pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IExistsCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_PropertyTag)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyTag)(/*[in]*/ long newVal);
private:
	long	m_lPropTag;
};
typedef CComObject<CExistsCondition>	CExistsResObject;

#endif //__EXISTSCONDITION_H_
