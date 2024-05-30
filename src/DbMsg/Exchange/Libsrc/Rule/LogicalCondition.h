// ----------------------------------------------------------------------------
//	LogicalCondition.h : Declaration of the CLogicalCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __LOGICALCONDITION_H_
#define __LOGICALCONDITION_H_

#include "resource.h"       // main symbols

typedef std::list<CConditionPtr*>					CConditionsList;
typedef std::list<CConditionPtr*>::iterator			CConditionsIterator;
typedef CComObject< CComEnum< IEnumVARIANT, 
							  &IID_IEnumVARIANT,
							  VARIANT,
							  _Copy<VARIANT> > >	CConditionsEnumVar;

// CLogicalCondition
class ATL_NO_VTABLE CLogicalCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLogicalCondition, &CLSID_LogicalCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<ILogicalCondition, &IID_ILogicalCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CLogicalCondition();
	~CLogicalCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_LOGICALCONDITION)

BEGIN_COM_MAP(CLogicalCondition)
	COM_INTERFACE_ENTRY(ILogicalCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,ILogicalCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()


// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// ILogicalCondition
public:
	STDMETHOD(get_Type)		(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(Item)			(/*[in]*/ VARIANT index, /*[out, retval]*/ LPDISPATCH *pItem);
	STDMETHOD(Delete)		(/*[in]*/ VARIANT index);
	STDMETHOD(Add)			(/*[in]*/  LPDISPATCH pRule );
	STDMETHOD(get__NewEnum)	(/*[out, retval]*/ LPUNKNOWN *pVal);
	STDMETHOD(get_Count)	(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Operator)	(/*[out, retval]*/ LOGICALOP_TYPES *pVal);
	STDMETHOD(put_Operator)	(/*[in]*/ LOGICALOP_TYPES newVal);
	STDMETHOD(Clear)();

public:
	void		cleanup();
	HRESULT		load(LPSRestriction lpRes);
	HRESULT		pack(LPSRestriction lpRes,LPVOID lpObject=NULL);
	LOGICALOP_TYPES	getType(){return m_logicalOperator;}

private:
	LOGICALOP_TYPES		m_logicalOperator;
	CConditionsList		m_conditionsCollection;
};
typedef CComObject<CLogicalCondition>	CLogicalResObject;

#endif //__LOGICALCONDITION_H_
