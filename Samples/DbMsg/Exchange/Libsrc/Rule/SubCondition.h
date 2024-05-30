// ----------------------------------------------------------------------------
//	SubCondition.h : Declaration of the CSubCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __SUBCONDITION_H_
#define __SUBCONDITION_H_

#include "resource.h"       // main symbols

// CSubCondition
class ATL_NO_VTABLE CSubCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSubCondition, &CLSID_SubCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<ISubCondition, &IID_ISubCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CSubCondition();
	~CSubCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_SUBCONDITION)

BEGIN_COM_MAP(CSubCondition)
	COM_INTERFACE_ENTRY(ISubCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,ISubCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	void		cleanup();
	virtual HRESULT	load(LPSRestriction lpRes);
	virtual HRESULT	pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// ISubCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_Condition)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Condition)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(get_Operator)(/*[out, retval]*/ SUBOBJECT_TYPES *pVal);
	STDMETHOD(put_Operator)(/*[in]*/ SUBOBJECT_TYPES newVal);
private:
	SUBOBJECT_TYPES		m_subObjType;
	CConditionPtr		*m_pConditionPtr;
};
typedef CComObject<CSubCondition>	CSubResObject;

#endif //__SUBCONDITION_H_
