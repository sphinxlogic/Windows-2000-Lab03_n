// ----------------------------------------------------------------------------
//	ContentCondition.h : Declaration of the CContentCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __CONTENTCONDITION_H_
#define __CONTENTCONDITION_H_

#include "resource.h"       // main symbols

// CContentCondition
class ATL_NO_VTABLE CContentCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CContentCondition, &CLSID_ContentCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<IContentCondition, &IID_IContentCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CContentCondition();
	~CContentCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_CONTENTCONDITION)

BEGIN_COM_MAP(CContentCondition)
	COM_INTERFACE_ENTRY(IContentCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,IContentCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	HRESULT		load(LPSRestriction	lpRes);
	HRESULT		pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);
	void		cleanup();

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IContentCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(get_Value)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Value)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(get_PropertyType)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PropertyType)(/*[in]*/ long newVal);
	STDMETHOD(get_Operator)(/*[out, retval]*/ FUZZYLEVEL_TYPES *pVal);
	STDMETHOD(put_Operator)(/*[in]*/ FUZZYLEVEL_TYPES newVal);
private:
	CPropValPtr			*m_pPropValPtr;
	long				m_lPropType;
	ULONG				m_fuzzyTypeOp;
};
typedef CComObject<CContentCondition>	CContentResObject;

#endif //__CONTENTCONDITION_H_
