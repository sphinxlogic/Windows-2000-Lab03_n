/* --------------------------------------------------------------------------

CPP file for acecollection.h
The ACECollection object is not cocreatable, and is used to access the 
collection of ACE obect.
It contains the following methods:
Add:     Add a new ACE object to the collection
Item:    Find an entry using ID or index
Delete:  Delete an entry in ACL
Update:  Save changes to the Exchange table
GetEnum: Used for Each xxx in XXXX in VB
getCount: Get the number of ACE objects in the collection
SetDoc:  Set a CDO doc 

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
// ACECollection.cpp : Implementation of CACECollection
#include "stdafx.h"
#include "ACL.h"
#include "ACECollection.h"

/////////////////////////////////////////////////////////////////////////////
// CACECollection

STDMETHODIMP CACECollection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IACEs,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CACECollection::Initialize()
{
	HRESULT hr = S_OK;
	m_pExchTable = new CExchTable();
	if ( m_pExchTable )
	{
		hr = m_pExchTable->Initialize();
	}
	else
		hr = E_OUTOFMEMORY;

	return hr;
}

STDMETHODIMP CACECollection::Add( IACE * ACE  )
{
	HRESULT hr = E_FAIL;
	if ( ACE )
	{
		if ( m_pACEMap && m_pExchTable )
			hr = m_pACEMap->Add( ACE );
		else
			hr = E_FAIL;
	}
	else
		hr = E_INVALIDARG;

	return hr;
}

STDMETHODIMP CACECollection::get_Count( long * pVal )
{
	HRESULT hr = E_FAIL;
	if ( pVal ) 
	{
		*pVal = 0;
		if ( m_pACEMap && m_pExchTable )
		{
			*pVal = m_pACEMap->Size();
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	else
		hr = E_INVALIDARG;

	return hr;
}

STDMETHODIMP CACECollection::Item( VARIANT Index, LPVARIANT pItem )
{
	HRESULT hr = E_FAIL;
	DWORD dwIndex = 0;
	VariantInit( pItem );
	V_VT(pItem) = VT_DISPATCH;
	LPDISPATCH pdisp = NULL;

	if ( m_pACEMap && m_pExchTable )
	{
		if ( VT_I2 == V_VT(&Index) )
		{
			dwIndex = static_cast<DWORD>(V_I2(&Index));
			hr = m_pACEMap->Find( dwIndex, &pdisp );
		}
		else if ( VT_I4 == V_VT(&Index) ) 
		{	
			dwIndex = V_I4(&Index);
			hr = m_pACEMap->Find( dwIndex, &pdisp );
		}
		else if ( VT_BSTR == V_VT(&Index) )
		{
			CComBSTR bstrID = V_BSTR(&Index);
			hr = m_pACEMap->Find( bstrID, &pdisp );
		}
		else
			hr = E_INVALIDARG;

	}
	else
		hr = E_FAIL;
		
	V_DISPATCH(pItem) = pdisp;

	return hr;
}

STDMETHODIMP CACECollection::get__NewEnum( LPUNKNOWN * pVal )
{

	HRESULT hr = E_FAIL;
	if ( pVal )
	{
		*pVal = NULL;
		if ( m_pACEMap && m_pExchTable )
		{
			ENUMVAR* pEnumVar = new ENUMVAR;
			if ( pEnumVar )
			{
				hr = m_pACEMap->NewEnum( pEnumVar );
				if ( SUCCEEDED(hr) )
				{
					hr = pEnumVar->QueryInterface( IID_IUnknown, (void**)pVal );
				}
				else
				{
					delete pEnumVar;
					pEnumVar = NULL;
					hr = E_FAIL;
				}
			}
			else
				hr = E_OUTOFMEMORY; 
		}
		else
			hr = E_FAIL;
	}
	else
		return E_INVALIDARG;

	return hr;
}

STDMETHODIMP CACECollection::SetDoc( LPDISPATCH lpdispDoc )
{
	HRESULT hr = E_FAIL;

	if ( !lpdispDoc )
		return E_INVALIDARG;

	// Delete the old map object
	delete m_pACEMap;
	m_pACEMap = NULL;

	if ( m_pExchTable )
	{
		hr = m_pExchTable->Cleanup();
		hr = m_pExchTable->SetDoc( lpdispDoc );
		if ( SUCCEEDED(hr) )
		{
			// The exchange table initialization contains conversion from CDO to mapi folder.
			LPSRowSet lpRows = NULL;
			hr = m_pExchTable->Initialize( &lpRows );
			if ( SUCCEEDED(hr) )
			{
				if ( lpRows )
				{
					// Create a new map
					m_pACEMap = new CACEMap( m_pExchTable->GetMapiSession() );
					if ( m_pACEMap )
					{
						// Save the SRow set to a map for easy management
						hr = m_pACEMap->BuildMap( lpRows );
					}
					else
					{
						hr = E_OUTOFMEMORY;
					}
				}
				else
                    // the list is just empty.
					hr = S_OK;
			}
		}
	}
	else
		hr = E_OUTOFMEMORY;

    if ( FAILED(hr) )
    {
	    delete m_pExchTable;
	    m_pExchTable = NULL;
	    delete m_pACEMap;
	    m_pACEMap = NULL;
    }

	return hr;
}

STDMETHODIMP CACECollection::Delete( VARIANT Index )
{
	HRESULT hr = E_FAIL;
	if ( m_pACEMap && m_pExchTable )
	{
		if ( VT_BSTR == V_VT(&Index) )
		{
			CComBSTR bstrID = Index.bstrVal;
			hr = m_pACEMap->Delete( bstrID );
		}
		else if ( VT_I4 == V_VT(&Index) ) 
		{
			DWORD dwIndex = V_I4(&Index);
			hr = m_pACEMap->Delete( dwIndex );
		}
		else if ( VT_I2 == V_VT(&Index) )
		{
			DWORD dwIndex = static_cast<DWORD>( V_I2(&Index) );
			hr = m_pACEMap->Delete( dwIndex );
		}
		else
			hr = E_INVALIDARG;
	}

	return hr;
}

STDMETHODIMP CACECollection::Update()
{
	HRESULT hr = E_FAIL;

	if ( m_pACEMap && m_pExchTable )
	{
		SROWLIST* pSRowList = new SROWLIST;
		if ( pSRowList )
        {
		    hr = m_pACEMap->GetSRowList( pSRowList );
		    if ( SUCCEEDED(hr) )
			    hr = m_pExchTable->Update( pSRowList );
            // even in case of failure, pSRowList may contain partial list
            // so it still needs cleanup.
		    for ( SROWLIST::iterator it = pSRowList->begin(); it != pSRowList->end(); it++ )
			{
			    MAPIFREEBUFFER( (*it)->lpProps );
				delete (*it);
			}

		    delete pSRowList;
        }
        else
            hr = E_OUTOFMEMORY;
	}

	return hr;
}

