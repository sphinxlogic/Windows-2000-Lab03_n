// ----------------------------------------------------------------------------
//	Action.h : Declaration of the CAction
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#ifndef __ACTION_H_
#define __ACTION_H_

#include "resource.h"       // main symbols

typedef struct
{
	SBinary			sReplyEntryId;		// Reply ID 
	GUID			guidReplyTemplate;	// the reply template
}sReplyTemplate;

typedef union
{
	LPDISPATCH		lpMoveCopyFolder;	// CDO Folder object for Move/Copy actions
	SAFEARRAY		*lpAdressList;		// SAFEARRAY of addressEntry IDs for Forward/Delegate Actions
	sReplyTemplate	lReplyTemplate;		// reply template structure for actions reply/OOF reply
	SCODE			scBounceCode;		// Bounce code for Bounce action
	CPropValPtr		*pPropValPtr;		// PropValue smart pointer for Tag Action
} uActionArgs;

// CAction
class ATL_NO_VTABLE CAction : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAction, &CLSID_Action>,
	public ISupportErrorInfo,
	public IDispatchImpl<IAction, &IID_IAction, &LIBID_MSExchange>
{
public:
	CAction();
	~CAction();

DECLARE_REGISTRY_RESOURCEID(IDR_ACTION)

BEGIN_COM_MAP(CAction)
	COM_INTERFACE_ENTRY(IAction)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IAction
	STDMETHOD(get_ActionType)(/*[out, retval]*/ ACTION_TYPES *pVal);
	STDMETHOD(put_ActionType)(/*[in]*/ ACTION_TYPES newVal);
	STDMETHOD(get_Arg)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Arg)(/*[in]*/ VARIANT newVal);

	void		cleanup();
	void		setIndex(long lIndex){m_lIndex=lIndex;}
	long		getIndex(){return m_lIndex;}
	HRESULT		load(LPACTION pAction);
	HRESULT		pack(LPACTION pAction,LPVOID lpObject=NULL);

private:
	long			m_lIndex;		// just an internal variable to indicate posn
	ACTION_TYPES	m_actionType;	// the action Type
	uActionArgs		m_uActionArgs;	// the arguments
};
typedef CComObject<CAction>	CActionObject;

#endif //__ACTION_H_
