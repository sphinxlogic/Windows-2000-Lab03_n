/* --------------------------------------------------------------------------

The cpp file for ACLObject
This object serves an entry point to ACL objects.
It allows to set a CDO doc, which is delegated to ACECollection
It also provides a methods to get a pointer to ACECollection object, which
is not cocreatable.

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// ACLObject.cpp : Implementation of CACLObject
#include "stdafx.h"
#include "ACL.h"
#include "ACLObject.h"
#include "ACLCommon.h"

/////////////////////////////////////////////////////////////////////////////
// CACLObject

STDMETHODIMP CACLObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IACLObject,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CACLObject::FinalConstruct()
{
	HRESULT hr = E_FAIL;
	CComObject<CACECollection>*	pACEColl = NULL;

	hr = CComObject<CACECollection>::CreateInstance( &pACEColl );
	if ( SUCCEEDED(hr) )
	{
		// addref is called by the assignment operator
		m_pACECollection = pACEColl;
		IACEs* pIACEColl = m_pACECollection;
		if ( pIACEColl )
		{
			pIACEColl->AddRef();
			// downcast pIACEColl to CACECollection to use the class method Update 
			CACECollection* pCACEColl = dynamic_cast<CACECollection*>(pIACEColl);
			if ( pCACEColl ) 
				hr = pCACEColl->Initialize(); 
			else
				hr = E_FAIL;
			pIACEColl->Release();
		}
	}
	return hr;
}

STDMETHODIMP CACLObject::FinalRelease()
{
	return S_OK;
}



STDMETHODIMP CACLObject::put_CDOItem( LPDISPATCH newVal )
{
	HRESULT hr = E_FAIL;

	IACEs* pIACEColl = m_pACECollection;
	if ( pIACEColl )
	{
		pIACEColl->AddRef();
		// downcast pIACEColl to CACECollection to use the class method SetDoc 
		CACECollection* pCACEColl = dynamic_cast<CACECollection*>(pIACEColl);
		if ( pCACEColl ) 
			hr = pCACEColl->SetDoc( newVal ); 
		else
			hr = E_FAIL;
		pIACEColl->Release();
	}
	
	return hr;
}

STDMETHODIMP CACLObject::putref_CDOItem( LPDISPATCH newVal )
{
	return put_CDOItem( newVal );
}

STDMETHODIMP CACLObject::get_ACEs( LPDISPATCH * pVal )
{
	HRESULT hr = E_FAIL;
	if ( pVal ) 
	{
		hr = m_pACECollection->QueryInterface( IID_IDispatch, (void**)pVal );
	}
	else
		hr = E_INVALIDARG;

	return hr;
}


STDMETHODIMP CACLObject::Update()
{
	HRESULT hr = E_FAIL;

	IACEs* pIACEColl = m_pACECollection;
	if ( pIACEColl )
	{
		pIACEColl->AddRef();
		// downcast pIACEColl to CACECollection to use the class method Update 
		CACECollection* pCACEColl = dynamic_cast<CACECollection*>(pIACEColl);
		if ( pCACEColl ) 
			hr = pCACEColl->Update(); 
		else
			hr = E_FAIL;
		pIACEColl->Release();
	}
	
	return hr;
}
