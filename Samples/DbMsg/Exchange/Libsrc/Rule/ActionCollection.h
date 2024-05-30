// ----------------------------------------------------------------------------
//	ActionCollection.h : Declaration of the CActions
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __ACTIONCOLLECTION_H_
#define __ACTIONCOLLECTION_H_

#include "resource.h"       // main symbols

typedef std::list<CActionPtr*>					CActionsList;
typedef std::list<CActionPtr*>::iterator		CActionsIterator;
typedef CComObject< CComEnum< IEnumVARIANT, 
								  &IID_IEnumVARIANT,
								  VARIANT,
								  _Copy<VARIANT> > >	CActionsEnumVar;
typedef ACTIONS FAR *   LPACTIONS;

// CActions
class ATL_NO_VTABLE CActions : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CActions, &CLSID_Actions>,
	public ISupportErrorInfo,
	public IDispatchImpl<IActions, &IID_IActions, &LIBID_MSExchange>
{
public:
	CActions(){}
	~CActions();

DECLARE_REGISTRY_RESOURCEID(IDR_ACTIONCOLLECTION)

BEGIN_COM_MAP(CActions)
	COM_INTERFACE_ENTRY(IActions)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IActions
	STDMETHOD(Delete)		(/*[in]*/ VARIANT index);
	STDMETHOD(Add)			(/*[in]*/ VARIANT index, /*[in]*/  LPDISPATCH pRule );
	STDMETHOD(Item)			(/*[in]*/ VARIANT index, /*[out, retval]*/ LPDISPATCH *pItem);
	STDMETHOD(get_Count)	(/*[out, retval]*/ long *pVal);
	STDMETHOD(get__NewEnum)	(/*[out, retval]*/ LPUNKNOWN *pVal);
	STDMETHOD(Clear)();

//	helper functions
	HRESULT		load(LPACTIONS lpActions);
	HRESULT		pack(LPACTIONS lpActions,LPVOID lpObject=NULL);
	HRESULT		reIndex();
	void		cleanup();

private:
	CActionsList	m_actionsCollection;
};
typedef CComObject<CActions>	CActionsObject;

#endif //__ACTIONCOLLECTION_H_
