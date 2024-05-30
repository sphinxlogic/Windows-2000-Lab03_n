/* --------------------------------------------------------------------------

The header file for ACE Object

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// ACE.h : Declaration of the CACE

#ifndef __ACE_H_
#define __ACE_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CACE
class ATL_NO_VTABLE CACE : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CACE, &CLSID_ACE>,
	public ISupportErrorInfo,
	public IDispatchImpl<IACE, &IID_IACE, &LIBID_MSExchangeACLLib>
{
public:
	CACE() : m_bDirty(FALSE),
             m_dwRights(ROLE_NONE)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ACE)
DECLARE_NOT_AGGREGATABLE(CACE)

BEGIN_COM_MAP(CACE)
	COM_INTERFACE_ENTRY(IACE)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IACE
public:
	STDMETHOD(get_Rights)(/*[out, retval]*/ ACLRIGHTS *pVal);
	STDMETHOD(put_Rights)(/*[in]*/ ACLRIGHTS newVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ID)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_DeleteOwn)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_DeleteOwn)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_FolderVisible)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_FolderVisible)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_FolderContact)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_FolderContact)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_FolderOwner)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_FolderOwner)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_CreateSubFolders)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_CreateSubFolders)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_DeleteAll)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_DeleteAll)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_EditAll)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_EditAll)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_EditOwn)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_EditOwn)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_CreateItems)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_CreateItems)(/*[in]*/ Boolean newVal);
	STDMETHOD(get_ReadItems)(/*[out, retval]*/ Boolean *pVal);
	STDMETHOD(put_ReadItems)(/*[in]*/ Boolean newVal);

// Class methods
	BOOL IsDirty() const
	{
		return m_bDirty;
	}
	void CleanDirty()
	{
		m_bDirty = FALSE;
	}
	DWORD GetRights() const
	{
		return m_dwRights;
	}
private:
	BOOL		m_bDirty;
	DWORD		m_dwRights;
	CComBSTR	m_bstrID;
};

#endif //__ACE_H_
