/* --------------------------------------------------------------------------

CPP file for ACE Object
ACE object is used to access, change, create an Access Control entry in ACL
It has get and put methods for all permissions and ID and rights

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// ACE.cpp : Implementation of CACE
#include "stdafx.h"
#include "aclcommon.h"
#include "ACL.h"
#include "ACE.h"


/////////////////////////////////////////////////////////////////////////////
// CACE
				


STDMETHODIMP CACE::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IACE,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CACE::get_ReadItems( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_READ_ITEMS & m_dwRights) == RIGHTS_READ_ITEMS ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_ReadItems( Boolean newVal )
{
	if ( True == newVal )
		m_dwRights |= RIGHTS_READ_ITEMS;
	else
		m_dwRights &= ~RIGHTS_READ_ITEMS;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_CreateItems( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_CREATE_ITEMS & m_dwRights) == RIGHTS_CREATE_ITEMS ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_CreateItems( Boolean newVal )
{
	if ( True == newVal )
		m_dwRights |= RIGHTS_CREATE_ITEMS;
	else
		m_dwRights &= ~RIGHTS_CREATE_ITEMS;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_EditOwn( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_EDIT_OWN & m_dwRights) == RIGHTS_EDIT_OWN ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_EditOwn( Boolean newVal )
{
	if ( True == newVal )
	{
		// since edit own is exclusive with edit all, so take out edit all first
		m_dwRights &= ~RIGHTS_EDIT_ALL;
		// then set edit own
		m_dwRights |= RIGHTS_EDIT_OWN;
	}
	else
		m_dwRights &= ~RIGHTS_EDIT_OWN;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_EditAll( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_EDIT_ALL & m_dwRights) == RIGHTS_EDIT_ALL ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_EditAll( Boolean newVal )
{
	if ( True == newVal )
	{
		// since edit own is exclusive with edit all, so take out edit own first
		m_dwRights &= ~RIGHTS_EDIT_OWN;
		// then set edit all
		m_dwRights |= RIGHTS_EDIT_ALL;
	}
	else
		m_dwRights &= ~RIGHTS_EDIT_ALL;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_DeleteAll( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_DELETE_ALL & m_dwRights) == RIGHTS_DELETE_ALL ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_DeleteAll( Boolean newVal )
{
	if ( True == newVal )
	{
		// since delete all is exclusive with delete own, so take out delete own first
		m_dwRights &= ~RIGHTS_DELETE_OWN;
		// then set delete all
		m_dwRights |= RIGHTS_DELETE_ALL;
	}
	else
		m_dwRights &= ~RIGHTS_DELETE_ALL;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_DeleteOwn( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_DELETE_OWN & m_dwRights) == RIGHTS_DELETE_OWN ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_DeleteOwn( Boolean newVal )
{
	if ( True == newVal )
	{
		// since delete own is exclusive with delete all, so take out delete all first
		m_dwRights &= ~RIGHTS_DELETE_ALL;
		// then set delete own
		m_dwRights |= RIGHTS_DELETE_OWN;
	}
	else
		m_dwRights &= ~RIGHTS_DELETE_OWN;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_CreateSubFolders( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_CREATE_SUBFOLDERS & m_dwRights) == RIGHTS_CREATE_SUBFOLDERS ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_CreateSubFolders( Boolean newVal )
{
	if ( True == newVal )
		m_dwRights |= RIGHTS_CREATE_SUBFOLDERS;
	else
		m_dwRights &= ~RIGHTS_CREATE_SUBFOLDERS;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_FolderOwner( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_FOLDER_OWNER & m_dwRights) == RIGHTS_FOLDER_OWNER ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_FolderOwner( Boolean newVal  )
{
	if ( True == newVal )
		m_dwRights |= RIGHTS_FOLDER_OWNER;
	else
		m_dwRights &= ~RIGHTS_FOLDER_OWNER;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_FolderContact( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_FOLDER_CONTACT & m_dwRights) == RIGHTS_FOLDER_CONTACT ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_FolderContact( Boolean newVal )
{
	if ( True == newVal )
		m_dwRights |= RIGHTS_FOLDER_CONTACT;
	else
		m_dwRights &= ~RIGHTS_FOLDER_CONTACT;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_FolderVisible( Boolean * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = ( (RIGHTS_FOLDER_VISIBLE & m_dwRights) == RIGHTS_FOLDER_VISIBLE ) ? True : False;

	return S_OK;
}

STDMETHODIMP CACE::put_FolderVisible( Boolean newVal )
{
	if ( True == newVal )
		m_dwRights |= RIGHTS_FOLDER_VISIBLE;
	else
		m_dwRights &= ~RIGHTS_FOLDER_VISIBLE;
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_ID( VARIANT * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	VariantInit( pVal );
	V_VT(pVal) = VT_BSTR;
	pVal->bstrVal = SysAllocString( BSTR(m_bstrID) );
	return S_OK;
}

STDMETHODIMP CACE::put_ID( VARIANT newVal )
{
    if ( VT_BSTR != V_VT(&newVal) )
		return E_INVALIDARG;
	
	m_bstrID = V_BSTR(&newVal);
	m_bDirty = TRUE;
	return S_OK;
}

STDMETHODIMP CACE::get_Rights( ACLRIGHTS * pVal )
{
	if ( !pVal )
		return E_INVALIDARG;

	*pVal = static_cast<ACLRIGHTS>(m_dwRights);

	return S_OK;
}

STDMETHODIMP CACE::put_Rights( ACLRIGHTS newVal )
{
	m_dwRights = static_cast<DWORD>(newVal);
	m_bDirty = TRUE;
	return S_OK;
}



