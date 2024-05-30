// ----------------------------------------------------------------------------
//	Rule.h : Declaration of the CRule
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __RULE_H_
#define __RULE_H_

#include "resource.h"		// main symbols

// Rule properties in the SRow
#define PR_RULE_NAMEA	PROP_TAG(PT_STRING8,PROP_ID(PR_RULE_NAME))
#define PR_RULE_NAMEW	PROP_TAG(PT_UNICODE,PROP_ID(PR_RULE_NAME))

enum RULE_PROPS
{
	I_RULE_SEQUENCE,
	I_RULE_STATE,
	I_RULE_CONDITION,
	I_RULE_ACTIONS,
	I_RULE_PROVIDER,
	I_RULE_NAME,
	I_RULE_NAMEA=I_RULE_NAME,
	I_RULE_LEVEL,
	I_RULE_ID,
	I_RULE_NAMEW,
	C_RULEPROPS,
};

enum PERSIST_STATES
{
	PERS_ADD	= ROW_ADD,
	PERS_MODIFY	= ROW_MODIFY,
	PERS_REMOVE	= ROW_REMOVE,
	PERS_EMPTY	= ROW_EMPTY
};

// CRule
class ATL_NO_VTABLE CRule : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRule, &CLSID_Rule>,
	public ISupportErrorInfo,
	public IDispatchImpl<IRule, &IID_IRule, &LIBID_MSExchange>
{
public:
	CRule();
	~CRule();

DECLARE_REGISTRY_RESOURCEID(IDR_RULE)

BEGIN_COM_MAP(CRule)
	COM_INTERFACE_ENTRY(IRule)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IRule
	STDMETHOD(get_ReadOnly)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_NewIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NewIndex)(/*[in]*/ long newVal);
	STDMETHOD(get_Actions)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(get_Condition)(/*[out, retval]*/ LPDISPATCH *pVal);
	STDMETHOD(put_Condition)(/*[in]*/ LPDISPATCH newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Level)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Level)(/*[in]*/ long newVal);
	STDMETHOD(get_Provider)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Provider)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_State)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_State)(/*[in]*/ long newVal);
	STDMETHOD(get_Index)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Sequence)(/*[out, retval]*/ long *pVal);

// helper routines
	void		setIndex(long lIndex){m_lIndex=lIndex;}
	void		setNewIndex(long lIndex){m_lNewIndex=lIndex;}
	void		setSequence(long lSequence){m_lSequence=lSequence;}
	void		setReadOnly(){m_bReadOnly=TRUE;}
	void		setReadWrite(){m_bReadOnly=FALSE;}
	void		setProvider(LPCSTR lpcStrProv);
	const char	*getProvider(){return m_lpszAProvider;}
	long		getPersistence(){return m_lPersist;}
	void		setPersistence(long lPersist){m_lPersist=lPersist;}
	LARGE_INTEGER	getRuleID(){return m_liRuleId;}

	void		cleanup();
	HRESULT		load(LPSRow lpSRow,ULONG ulIndex);
	HRESULT		pack(LPROWENTRY	lpRowEntry,LPVOID lpObject);

private:
	LARGE_INTEGER			m_liRuleId;
	long					m_lSequence;
	long					m_lState;
	long					m_lLevel;
	long					m_lIndex;
	long					m_lNewIndex;
	long					m_lPersist;
	unsigned long			m_lNameType;
	BOOL					m_bReadOnly;
	LPSTR					m_lpszAProvider;
	LPTSTR					m_lpszTName;
	CActionsPtr				*m_pActions;
	CConditionPtr			*m_pCondition;
};
typedef CComObject<CRule>	CRuleObject;

#endif //__RULE_H_
