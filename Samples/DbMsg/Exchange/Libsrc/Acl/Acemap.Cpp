/* --------------------------------------------------------------------------

CPP file for ACEMap
This cpp file implements a number of methods used by ACECollection class
to manipulate the collection

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
#include "stdafx.h"
#include "ACLCommon.h"
#include "ACEMap.h"
#include "ACE.h"
#include "util.h"
#include <comdef.h>

CACEMap::~CACEMap()
{
	for ( ACEMAP::iterator it = m_mapACE.begin(); it != m_mapACE.end(); it++ )
	{
		CItem* pItem = (*it).second;
		delete pItem;
		pItem = NULL;
	}
	if ( m_pMapiSession )
		m_pMapiSession->Release();
}

CItem*& CACEMap::operator[]( const CComBSTR& bstrID ) 
{
	return m_mapACE[bstrID];
}

HRESULT CACEMap::Find( const CComBSTR& bstrID, LPDISPATCH* ppdisp ) 
{
	if ( !ppdisp )
		return E_INVALIDARG;

	HRESULT hr = S_OK;
	*ppdisp = NULL;
	ACEMAP::iterator it;
	if ( ( it = m_mapACE.find( bstrID ) ) != m_mapACE.end() )
	{
		CItem* pItem = (*it).second;

		// if there is no valid pointer to ACE, create one with SRow
		if ( !pItem->m_ppACE || !(*pItem->m_ppACE) )
		{
			hr = srowToACE( pItem );
			if ( FAILED(hr) )
				return hr;
		}

		return ( *pItem->m_ppACE )->QueryInterface( IID_IDispatch, (void**)ppdisp );
	}
	// finally, cannot get anything
	else
		return DISP_E_BADINDEX;
}

HRESULT CACEMap::Find( const DWORD dwIndex, LPDISPATCH* ppdisp ) 
{
	if ( !ppdisp )
		return E_INVALIDARG;

	HRESULT hr = S_OK;
	*ppdisp = NULL;
	ACEMAP::iterator it;
	DWORD i;
	// To accomodate VB programmers, use 1-based index
	for ( i = 1, it = m_mapACE.begin(); it != m_mapACE.end(); it++, i++ )
	{
		if ( dwIndex == i )
		{
			CItem* pItem = (*it).second;

			// if there is no a pointer to ACE, create on with SRow
			if ( !pItem->m_ppACE || !(*pItem->m_ppACE) )
			{
				hr = srowToACE( pItem );
				if (FAILED(hr))
					return hr;
			}

			return ( *pItem->m_ppACE )->QueryInterface( IID_IDispatch, (void**)ppdisp );
		}
	}
	// finally, cannot get anything
	return DISP_E_BADINDEX;
}

HRESULT CACEMap::Delete( const CComBSTR& bstrID )
{
	ULONG cb=0;
	HRESULT hr = DISP_E_BADINDEX;
	if ( !m_mapACE.empty() )
	{
		if ( m_mapACE.count( bstrID ) )
		{
			CItem* pItem = m_mapACE[bstrID];
			if ( pItem )
			{
				// If it is the default or anonymous, deny deletion
				bstr_t b = pItem->m_bstrEntryID;
				if ( ( (bstr_t)ID_ACL_DEFAULT == b ) || ( (bstr_t)ID_ACL_ANONYMOUS == b ) )
				{
					hr = EDK_E_ACCESSDENIED;
				}
				else
				{
				// regardless of whether an item exists, return S_OK
					m_mapACE.erase( bstrID );
					hr = S_OK;
				}
			}
			else
				hr = E_FAIL;
		}
	}
	// Note: if cannot find anything, still return S_OK
	return hr;
}

HRESULT CACEMap::Delete( const DWORD dwIndex )
{
	HRESULT hr = DISP_E_BADINDEX;
	if ( !m_mapACE.empty() )
	{
		ACEMAP::iterator it;
		DWORD i;
		// To accomodate VB programmers, use 1-based index
		for ( i = 1, it = m_mapACE.begin(); it != m_mapACE.end(); it++, i++ )
		{
			if ( dwIndex == i )
			{
				CItem* pItem = ( *it ).second;
				if ( pItem )
				{
					// If it is the default or anonymous, deny deletion
					bstr_t b = pItem->m_bstrEntryID;
					if ( ( (bstr_t)ID_ACL_DEFAULT == b ) || ( (bstr_t)ID_ACL_ANONYMOUS == b ) )
					{
						hr = EDK_E_ACCESSDENIED;
					}
					else
					{
						m_mapACE.erase( it );
						hr = S_OK;
					}
				}
				else
				{
					hr = E_FAIL;
				}
				break;
			}
		}
	}
	return hr;
}

HRESULT CACEMap::BuildMap( LPSRowSet lpRows )
{
	/* BuildMap takes in a list of SRow and put them into a map with the BSTR-ized entry id 
	   obtained from the SRow as a map key.  The key is a long term key.  
	*/
	
	if ( !lpRows )
		return E_INVALIDARG;

	// Verify all rows have valid property
	for (ULONG i = 0; i < lpRows->cRows; i++)
	{
		if ( !isValidACLSRow( lpRows->aRow[i] ) )
		{
			FreeProws( lpRows );		
			return E_FAIL;
		}
	}

	HRESULT		hr = S_OK;
	CItem*		pNewItem = NULL;

	// Now add the SRow's in the SRowSet to the map.
	for ( i = 0; i < lpRows->cRows; i++ )
	{
		CComBSTR bstrID;
		hr = getEntryID( lpRows->aRow[i], bstrID );
		if ( SUCCEEDED(hr) && BSTR(bstrID) )
		{
			// Construct a new CItem using LPSRow, but do not construct an ACE yet
			pNewItem = new CItem( &lpRows->aRow[i], bstrID );
			if ( pNewItem )
			{
				m_mapACE[bstrID] = pNewItem;
				// The lpProps storage no longer belongs to the SRowSet, so:
				lpRows->aRow[i].cValues = 0;
				lpRows->aRow[i].lpProps = NULL;
				hr = S_OK;
			}
			else
			{
				hr = E_OUTOFMEMORY;
				break;
			}
		}
		else
		{
			hr = E_FAIL;
			break;
		}
	}
	// no longer need it
	FreeProws( lpRows );		

	return hr;
}

HRESULT CACEMap::NewEnum ( ENUMVAR* pEnumVar )
{
	if ( !pEnumVar )
		return E_INVALIDARG;

	HRESULT hr = S_OK;
	long i = m_mapACE.size();
	VARIANT* pVar = new VARIANT[i];
	if ( pVar )
	{
		while ( i )
		{
			VariantInit( &pVar[--i] );
			V_VT( &pVar[i] ) = VT_DISPATCH;
		}

		ACEMAP::iterator it;
		for ( i = 0, it = m_mapACE.begin(); it != m_mapACE.end(); it++, i++ )
		{
			CItem* pItem = (*it).second;
			if ( !pItem->m_ppACE && !isValidACLSRow( pItem->m_SRow ) )
				break;
			else if ( !pItem->m_ppACE )  // there is no existing pACE, create one using info from SRow
			{
				// Transfer all info in SRow into pACE
				hr = srowToACE( pItem );
				if ( FAILED(hr) ) 
					break;
			}
			if ( *pItem->m_ppACE )
			{
				hr = ( *pItem->m_ppACE )->QueryInterface( IID_IDispatch, (void**)&(pVar[i].pdispVal) );
				if ( FAILED(hr) ) 
					break;
			}
			else
				break;
		}
		if ( SUCCEEDED(hr) )
			hr = pEnumVar->Init( &pVar[0], &pVar[i], NULL, AtlFlagCopy );
	}
	else
		return E_OUTOFMEMORY;

	i = m_mapACE.size();
	while ( i )
		VariantClear( &pVar[--i] );
	delete [] pVar;

	return hr;
}


HRESULT CACEMap::srowToACE ( CItem* pItem )
{
	// you must have a valid pointer to CItem->m_sRow
	if ( !pItem || !isValidACLSRow( pItem->m_SRow ) )
		return E_INVALIDARG;

	HRESULT				hr = E_FAIL;
	ULONG				lRights = 0;		
	CComObject<CACE>*	pACE = NULL;
	VARIANT				var;

	// create a new ACE first
	hr = CComObject<CACE>::CreateInstance( &pACE );
	if ( SUCCEEDED(hr) )
	{
		// the smart pointer is created using its copy constructor passing in an ACE object, 
		// AddRef is called on pACE, Release will be called when ppACE is deleted
		pItem->m_ppACE = new CComPtr<IACE>( pACE );
		if ( pItem->m_ppACE )
		{
			// save the rights to CACE from the SRow
			lRights = pItem->m_SRow.lpProps[I_MEMBER_RIGHTS].Value.l;
			if ( *pItem->m_ppACE )
			{
				hr = ( *pItem->m_ppACE )->put_Rights( static_cast<ACLRIGHTS>( lRights ) );
				if ( SUCCEEDED(hr) )
				{
					if ( BSTR(pItem->m_bstrEntryID) )
					{
						VariantInit( &var );
						V_VT(&var) = VT_BSTR;
						var.bstrVal = SysAllocString( BSTR(pItem->m_bstrEntryID) );
						hr = ( *pItem->m_ppACE )->put_ID( var );
						SysFreeString( var.bstrVal );
						VariantClear( &var );
						if ( SUCCEEDED(hr) )
						{
							IACE* pIACE = *pItem->m_ppACE;
							if ( pIACE )
							{
								pIACE->AddRef();
								CACE* pACE = dynamic_cast<CACE*>(pIACE);
								if ( pACE )
									pACE->CleanDirty();
								pIACE->Release();
							}
							else
								hr = E_FAIL;
						}
					}
					else
						hr = E_FAIL;
				}
			}
			else
				hr = E_FAIL;
		}
		else
		{	delete pACE;
			return E_OUTOFMEMORY;
		}
	}
	else
		return E_FAIL;

	if ( FAILED(hr) )
	{
		delete pItem->m_ppACE;
		// it is ok to free a null bstr
		SysFreeString( var.bstrVal );
	}
	return hr;
}

HRESULT CACEMap::Add( IACE* pACE )
{
	if ( !pACE )
		return E_INVALIDARG;

	HRESULT hr = S_OK;
	CComBSTR bstrID;
	VARIANT var;

	// construct a new CItem using pACE
	CItem* pNewItem = new CItem();
	if ( pNewItem )
	{
		hr = pNewItem->CreateACE( pACE );
		if ( SUCCEEDED(hr) )
		{
			// Construct SRow info from pACE
			hr = aceToSRow( pNewItem );
			if ( SUCCEEDED(hr) )
			{
				if ( !m_mapACE.count( pNewItem->m_bstrEntryID ) )
				{
					if ( pACE )
					{
						// update the ID in ACE with a long-term ID
						VariantInit( &var );
						V_VT(&var) = VT_BSTR;
						var.bstrVal = SysAllocString( BSTR(pNewItem->m_bstrEntryID) );
						hr = pACE->put_ID( var );
						SysFreeString( var.bstrVal );
						VariantClear( &var );
						if ( SUCCEEDED(hr) )
						{
							IACE* pIACE = *(pNewItem->m_ppACE);
							if ( pIACE )
							{
								pIACE->AddRef();
								CACE* pACE2 = dynamic_cast<CACE*>(pIACE);
								if ( pACE2 )
									pACE2->CleanDirty();
								pIACE->Release();
							}
							else
								hr = E_FAIL;

							m_mapACE[pNewItem->m_bstrEntryID] = pNewItem;  
						}
					}
				}
				else
					hr = EDK_E_ALREADY_EXISTS;
			}
		}
	}
	else
		hr = E_OUTOFMEMORY;

    // it is ok to delete a null pointer when memory allocation fails
	if ( FAILED(hr) )
		delete pNewItem;

	return hr;
}

HRESULT CACEMap::aceToSRow( CItem* pItem )
{
	if ( !pItem || !pItem->m_ppACE || !*(pItem->m_ppACE) )
		return E_INVALIDARG;

	HRESULT			hr = S_OK;
	SBinary			sbEID = { 0, NULL };

	LPENTRYID		lpentryidCopy = NULL;

	// The entry ID obtained is guaranteered to be a long-term one
	hr = MAPIAllocateBuffer( sizeof( SPropValue ) * C_ACLPROPS, (void**)&(pItem->m_SRow.lpProps) );
	if ( SUCCEEDED(hr) )
    {
	    memset( pItem->m_SRow.lpProps, 0, sizeof( SPropValue ) * C_ACLPROPS );

	    // get entry id
        hr = getEntryID( *(pItem->m_ppACE), sbEID );
	    if ( SUCCEEDED(hr) )
        {
	        hr = MAPIAllocateMore( sbEID.cb, pItem->m_SRow.lpProps, (void**)&lpentryidCopy );
	        if ( SUCCEEDED(hr) )
            {
	            memcpy( lpentryidCopy, reinterpret_cast<LPENTRYID>(sbEID.lpb), sbEID.cb );

	            if ( SUCCEEDED(hr) )
                {
	                // get rights
	                ACLRIGHTS lRights;
	                hr = ( *(pItem->m_ppACE) )->get_Rights( &lRights );
	                if ( SUCCEEDED(hr) )
	                {
	                    // save everything into SRow
	                    pItem->m_SRow.lpProps[I_MEMBER_ENTRYID].ulPropTag = PR_MEMBER_ENTRYID;
	                    pItem->m_SRow.lpProps[I_MEMBER_ENTRYID].Value.bin.cb =	sbEID.cb;
	                    pItem->m_SRow.lpProps[I_MEMBER_ENTRYID].Value.bin.lpb = reinterpret_cast<LPBYTE>(lpentryidCopy);
						// save a long-term ID 
						BSTR bID = binaryToBSTR( &sbEID );
						delete [] sbEID.lpb;
						pItem->m_bstrEntryID = bID;
						SysFreeString( bID );
	                    pItem->m_SRow.lpProps[I_MEMBER_RIGHTS].ulPropTag =	PR_MEMBER_RIGHTS;
	                    pItem->m_SRow.lpProps[I_MEMBER_RIGHTS].Value.l = lRights;

						pItem->m_SRow.lpProps[I_MEMBER_ID].ulPropTag = PR_MEMBER_ID;
						pItem->m_SRow.lpProps[I_MEMBER_ID].Value.l = ID_NEWACE;
                    }
                }
            }
        }
    }
    else
        return hr;

    if ( FAILED(hr) )
        MAPIFREEBUFFER( pItem->m_SRow.lpProps );

	return hr;
}

BOOL CACEMap::isValidACLSRow( const SRow& srow ) const
{
	return ( srow.cValues == C_ACLPROPS && 
             srow.lpProps[I_MEMBER_ENTRYID].ulPropTag == PR_MEMBER_ENTRYID && 
             srow.lpProps[I_MEMBER_RIGHTS].ulPropTag == PR_MEMBER_RIGHTS );
}

HRESULT CACEMap::getEntryID( const SRow& sRow, CComBSTR& bstrID )
{
	HRESULT		hr = E_FAIL;
	ULONG		cbentryid = 0;				
	SBinary		sbEID = { 0, NULL };		
	LPSBinary	psb = NULL;
	BSTR		bID;

	if ( isValidACLSRow( sRow ) )
	{
		// here the entry id from a srow is guaranteed to be a long-term id 
		cbentryid = sRow.lpProps[I_MEMBER_ENTRYID].Value.bin.cb;
		if ( cbentryid && sRow.lpProps[I_MEMBER_ENTRYID].Value.bin.lpb )
		{
			sbEID = sRow.lpProps[I_MEMBER_ENTRYID].Value.bin;
  			if ( sbEID.lpb )
			{
				if ( ::IsShortTerm( sbEID ) )
				{
					// it is a short term entry id, convert it to a long term id
					hr = ::ConvertToLongTerm( m_pMapiSession, sbEID, &psb );
					if ( SUCCEEDED(hr) )
					{
						hr = CopyBinary( *psb, &sbEID );
						MAPIFREEBUFFER( psb );
					}
				}
				bID = binaryToBSTR( &sbEID );
				bstrID = bID;
				SysFreeString( bID );
				hr = S_OK;
			}
			else
			{
				hr = E_FAIL;
			}
		}
		// Judge whether it is for default or anonymous by looking at its I_MEMBER_ID
		else if ( ID_DEFAULT  == sRow.lpProps[I_MEMBER_ID].Value.l )
		{
			bstrID = ID_ACL_DEFAULT;
			hr = S_OK;
		}
		else if ( ID_ANONYMOUS == sRow.lpProps[I_MEMBER_ID].Value.l )
		{
			bstrID = ID_ACL_ANONYMOUS;
			hr = S_OK;
		}
		else
		{
			bstrID = "";
			hr = E_FAIL;
		}

		if ( NULL == BSTR(bstrID) )
			hr = E_FAIL;
	}
	else
		hr = E_FAIL;

	return hr;
}

HRESULT CACEMap::getEntryID( IACE* pACE, SBinary& sbEID )
{
	if ( !pACE )
		return E_INVALIDARG;

	HRESULT			hr	= E_FAIL;
	SBinary			sb	= { 0, NULL };
	LPSBinary		psb = NULL;

	VARIANT var;
	VariantInit( &var );
	hr = pACE->get_ID( &var );
	if ( SUCCEEDED(hr) )
	{
		CComBSTR bstrID = V_BSTR(&var);
		if ( BSTR(bstrID) )
		{
			sb = ::BSTRToBinary( BSTR(bstrID) );
			if ( ::IsShortTerm( sb ) )
			{
				// it is a short term entry id, convert it to a long term id
				hr = ::ConvertToLongTerm( m_pMapiSession, sb, &psb );
				if ( SUCCEEDED(hr) )
				{
					hr = CopyBinary( *psb, &sbEID );
					MAPIFREEBUFFER( psb );
				}
			}
			else  // it is a long term entry id
				hr = CopyBinary( sb, &sbEID );
		}
		else
			hr = E_FAIL;
	}

    // it is ok to free a NULL string if get_ID fails
	SysFreeString ( var.bstrVal );
	VariantClear(&var);
    // it is ok to pass a null pointer
	delete [] sb.lpb ;

	return hr;
}

HRESULT CACEMap::GetSRowList( SROWLIST* pSRowList )
{
	if ( !pSRowList )
		return E_INVALIDARG;
	if ( !m_mapACE.size() )
		return S_OK;

	HRESULT hr = E_FAIL;
	ULONG cb = 0;
	ULONG ulstrlen = 0;
	LPENTRYID lpentryid = NULL;
	SRow* psr = NULL;
	LPTSTR lpszDisplayName = NULL;

	for ( ACEMAP::iterator it = m_mapACE.begin(); it != m_mapACE.end(); it++ )
	{
		cb = 0;
		ulstrlen = 0;
		lpentryid = NULL;
		psr = NULL;

		CItem* pItem = (*it).second;
		if ( pItem )
		{
			psr = new SRow;
			if ( psr )
			{
				psr->ulAdrEntryPad = 0;
				psr->cValues = C_ACLPROPS;
				hr = MAPIAllocateBuffer( sizeof( SPropValue ) * C_ACLPROPS, (LPVOID*)&psr->lpProps );
				if ( SUCCEEDED(hr) )
				{
					memset( psr->lpProps, 0, sizeof( SPropValue ) * C_ACLPROPS );
					cb = pItem->m_SRow.lpProps[I_MEMBER_ENTRYID].Value.bin.cb;
					hr = MAPIAllocateMore( cb, psr->lpProps, (void**)&lpentryid );
					if ( SUCCEEDED(hr) )
					{
						memcpy( lpentryid, pItem->m_SRow.lpProps[I_MEMBER_ENTRYID].Value.bin.lpb, cb );

						psr->lpProps[I_MEMBER_ENTRYID].ulPropTag = PR_MEMBER_ENTRYID;
						psr->lpProps[I_MEMBER_ENTRYID].Value.bin.cb = cb;
						psr->lpProps[I_MEMBER_ENTRYID].Value.bin.lpb = (LPBYTE)lpentryid;

						psr->lpProps[I_MEMBER_ID].ulPropTag = PR_MEMBER_ID;
						psr->lpProps[I_MEMBER_ID].Value.l = pItem->m_SRow.lpProps[I_MEMBER_ID].Value.l;
						psr->lpProps[I_MEMBER_ID].Value.li = pItem->m_SRow.lpProps[I_MEMBER_ID].Value.li;

						psr->lpProps[I_MEMBER_RIGHTS].ulPropTag = PR_MEMBER_RIGHTS;

						if ( pItem->m_ppACE && *pItem->m_ppACE )
						{
							IACE* pIACE = *pItem->m_ppACE;
							if ( pIACE )
							{
								pIACE->AddRef();
								// downcast IACE to CACE in order to use the class method,
								// rather than an interface method
								CACE* pACE = dynamic_cast<CACE*>(pIACE);
								if ( pACE )
								{
									if ( pACE->IsDirty() )
									{
										// update the m_SRow with new rights
										pItem->m_SRow.lpProps[I_MEMBER_RIGHTS].Value.l = pACE->GetRights();
										pACE->CleanDirty();
									}
								}
								else
								{
									hr = E_FAIL;
									pIACE->Release();
									break;
								}
								pIACE->Release();
							}
							else
							{
								hr = E_FAIL;
                                break;
							}
						}
						psr->lpProps[I_MEMBER_RIGHTS].Value.l = pItem->m_SRow.lpProps[I_MEMBER_RIGHTS].Value.l;
                        pSRowList->push_back( psr );
					}
					else
						break;
				}
				else
					break;
			}
			else
			{
				hr = E_OUTOFMEMORY;
				break;
			}
		}
		else
		{
			hr = E_FAIL;
			break;
		}
	}

    if ( FAILED(hr) )
    {
		if ( psr )
		{
			MAPIFREEBUFFER( psr->lpProps );
			delete psr;
			psr = NULL;
		}
    }
	return hr;
}

BSTR CACEMap::binaryToBSTR( SBinary* pBinary )
{
	LPBYTE pb = pBinary->lpb;
	ULONG cb = pBinary->cb;
    BSTR strReturn = pBinary ? SysAllocStringLen(NULL, _cpp_max(pBinary->cb * 2, (ULONG)1)) : NULL;
	LPWSTR psz = strReturn;
	  
	if(psz)
	{
		while (cb--)
		{
            // first of all, convert all lower case alphabetics to upper case
            if ( *pb >= 'a' && *pb <= 'z' )
                *pb = 'A' + ( *pb - 'a' );

			int n1 = *pb & 0x0f;
			int n2 = (*pb >> 4) & 0x0f;

			*psz++ = (BYTE) (n2 + (n2 >= 10 ? (L'A' - 10) : L'0'));
			*psz++ = (BYTE) (n1 + (n1 >= 10 ? (L'A' - 10) : L'0'));
			++pb;
		}
		*psz = 0;
	}

	return strReturn;
}
