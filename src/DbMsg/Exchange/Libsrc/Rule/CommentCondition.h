// ----------------------------------------------------------------------------
//	CommentCondition.h : Declaration of the CCommentCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __COMMENTCONDITION_H_
#define __COMMENTCONDITION_H_

#include "resource.h"       // main symbols

typedef std::list<CPropValPtr*>						CPropValsList;
typedef std::list<CPropValPtr*>::iterator			CPropValsIterator;
typedef CComObject< CComEnum< IEnumVARIANT, 
							  &IID_IEnumVARIANT,
							  VARIANT,
							  _Copy<VARIANT> > >	CPropValsEnumVar;

// CCommentCondition
class ATL_NO_VTABLE CCommentCondition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCommentCondition, &CLSID_CommentCondition>,
	public ISupportErrorInfo,
	public CBaseCondition,
	public IDispatchImpl<ICommentCondition, &IID_ICommentCondition, &LIBID_MSExchange>,
	public IDispatchImpl<ICondition, &IID_ICondition, &LIBID_MSExchange>
{
public:
	CCommentCondition();
	~CCommentCondition();

DECLARE_REGISTRY_RESOURCEID(IDR_COMMENTCONDITION)

BEGIN_COM_MAP(CCommentCondition)
	COM_INTERFACE_ENTRY(ICommentCondition)
	COM_INTERFACE_ENTRY(ICondition)
	COM_INTERFACE_ENTRY2(IDispatch,ICommentCondition)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

public:
	void		cleanup();
	HRESULT		load(LPSRestriction	lpRes);
	HRESULT		pack(LPSRestriction	lpRes,LPVOID lpObject=NULL);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// ICommentCondition
public:
	STDMETHOD(get_Type)(/*[out, retval]*/ CONDITION_TYPES *pVal);
	STDMETHOD(Delete)		(/*[in]*/ VARIANT index );
	STDMETHOD(Add)			(/*[in]*/ LPDISPATCH lpDispCondition);
	STDMETHOD(get_Condition)(/*[out, retval]*/ LPDISPATCH *ppDispCondition);
	STDMETHOD(put_Condition)(/*[in]*/ LPDISPATCH lpDispCondition);
	STDMETHOD(Item)			(/*[in]*/ VARIANT index, /*[out, retval]*/ LPDISPATCH *ppDispCondition);
	STDMETHOD(get__NewEnum)	(/*[out, retval]*/ LPUNKNOWN *pVal);
	STDMETHOD(get_Count)	(/*[out, retval]*/ long *pVal);
	STDMETHOD(Clear)();
private:
	CPropValsList		m_propValsCollection;
	CConditionPtr		*m_pConditionPtr;
};
typedef CComObject<CCommentCondition>	CCommentResObject;

#endif //__COMMENTCONDITION_H_
