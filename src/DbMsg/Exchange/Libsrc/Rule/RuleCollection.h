// ----------------------------------------------------------------------------
//	RuleCollection.h : Declaration of the CRules
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __RULECOLLECTION_H_
#define __RULECOLLECTION_H_

#include "resource.h"

typedef std::list<CRulePtr*>				CRuleList;
typedef std::list<CRulePtr*>::iterator		CRuleIterator;
typedef CComObject<CComEnum<IEnumVARIANT, 
							&IID_IEnumVARIANT,
							VARIANT,
							_Copy<VARIANT> > >	CRuleEnumVar;

// CRules
class ATL_NO_VTABLE CRules : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRules, &CLSID_Rules>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRules, &IID_IRules, &LIBID_MSExchange>
{
public:
	CRules();
	~CRules();
	
DECLARE_REGISTRY_RESOURCEID(IDR_RULECOLLECTION)

BEGIN_COM_MAP(CRules)
	COM_INTERFACE_ENTRY(IRules)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IRules
public:
	STDMETHOD(Clear)();
	STDMETHOD(UpdateIndices)();
	STDMETHOD(Update)();

	// IRules interaface functions accessible through IDispatch
	STDMETHOD (get_Folder)	( /*[out, retval]*/ LPDISPATCH *pVal );
	STDMETHOD (put_Folder)	( /*[in]*/ LPDISPATCH newVal );

	// Interface for VB collection iteration
	STDMETHOD (get__NewEnum)( /*[out, retval]*/ LPUNKNOWN *pVal );
	STDMETHOD(Item)			(/*[in]*/ VARIANT index, /*[out, retval]*/ LPDISPATCH *pItem);
	STDMETHOD(Add)			(/*[in]*/ VARIANT index, /*[in]*/  LPDISPATCH pRule );
	STDMETHOD(Delete)		(/*[in]*/ VARIANT index);
	STDMETHOD(get_Count)	(/*[out, retval]*/ long *pVal);

private:
	HRESULT		getRulesTable();				// get MAPI rules table interfaces
	HRESULT		getRowSet(LPSRowSet *ppRowSet);	// get rules from rules table
	HRESULT		load(LPSRowSet lpRowSet);		// load rule datstructures into rule interfaces
	HRESULT		reIndex();						// adjust the indices
	HRESULT		reSequence();					// adjust the sequence numbers
	void		cleanup();						// free memory allocations, references
private:
	BOOL					m_bMAPIInitialized;	// TRUE if MAPIInitialize returns SUCCESS
	LPMAPIFOLDER			m_pMAPIFolder;		// MAPI Folder
	LPEXCHANGEMODIFYTABLE	m_pExchTbl;			// exchange modifiy table 
	LPMAPITABLE				m_pMAPITbl;			// MAPI rules table
	LPSTR					m_pszAProvider;		// default provider name
	CRuleList				m_rulesCollection;	// collection of rules
	CRuleList				m_DeletedRules;		// collection of deleted rules
};

typedef CComObject<CRules>	CRulesObject;

#endif // __RULECOLLECTION_H_
