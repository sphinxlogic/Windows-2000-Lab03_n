/* --------------------------------------------------------------------------
CPP file CExchTable.

The cpp file implements a number of methods related to manipulate 
the Exchange table such as writing to the table and getting ACL
from the table initially.

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
#include "stdafx.h"
#include "atlctl.h"
#include "atlctl.cpp"
#include "aclcommon.h"
#include "ExchTable.h"
#include "Util.h"


CExchTable::CExchTable() : m_pExchModifyTable(NULL),
		                   m_pMapiFolder(NULL),
						   m_pMapiTable(NULL),
						   m_pdispCDODoc(NULL),
						   m_pMapiSession(NULL)
{
}

CExchTable::~CExchTable()
{
	MAPIUninitialize();
}	

HRESULT CExchTable::Initialize()
{
	return MAPIInitialize( NULL );
}

HRESULT CExchTable::Cleanup()
{
	ULRELEASE( m_pMapiTable );
	ULRELEASE( m_pExchModifyTable );
	ULRELEASE( m_pMapiFolder );
	ULRELEASE( m_pdispCDODoc );
	ULRELEASE( m_pMapiSession );

	return S_OK;
}

HRESULT CExchTable::SetDoc( LPDISPATCH lpdispDoc )
{
	if ( !lpdispDoc )
		return E_INVALIDARG;

	// release the old CDO doc
	HRESULT hr;
	if ( m_pdispCDODoc )
		ULRELEASE( m_pdispCDODoc );
	hr = lpdispDoc->QueryInterface( IID_IDispatch, (void**)&m_pdispCDODoc );

	return S_OK;

}

HRESULT CExchTable::Initialize( LPSRowSet* lppRows )
{
    if ( !lppRows )
        return E_INVALIDARG;

	*lppRows = NULL;

	// The CDO object does not exist.
	if ( !m_pdispCDODoc )
		return E_INVALIDARG;

	// Don't allow multiple opens on one object.
	if ( m_pMapiFolder != NULL )
		return E_INVALIDARG;

    HRESULT		hr			= E_FAIL;
	ULONG		ulObjType   = 0;
	LPSRowSet	lpRows		= NULL;

    SizedSPropTagArray ( C_ACLPROPS, rgPropTag ) =
    {
    	C_ACLPROPS,
    	{
            PR_MEMBER_ENTRYID,	    // its unique across directory
            PR_MEMBER_RIGHTS,		
            PR_MEMBER_ID/*,			// unique within a table, used for table modification	
            PR_MEMBER_NAME*/			// display name
   		}
    };

	// set the pointer to the session
	OLECHAR* pszName = L"Session";
	DISPID dispID;
	hr = m_pdispCDODoc->GetIDsOfNames( IID_NULL, &pszName, 1, LOCALE_USER_DEFAULT, &dispID );
	if ( FAILED(hr) )
		return hr;
	VARIANT var;
	VariantInit( &var );
	CComDispatchDriver pDisp(m_pdispCDODoc);
	hr = pDisp.GetProperty( dispID, &var );
	if ( FAILED(hr) )
	{
		VariantClear( &var );
		return hr;
	}
	hr = VariantToMAPIObject( var, IID_IMAPISession, (void**)&m_pMapiSession );
	VariantClear( &var );
	if ( SUCCEEDED(hr) )
    {
	    // convert a cdo object (folder) to a mapi folder object
	    hr = AMObjectToMAPIObject( m_pdispCDODoc, IID_IMAPIFolder, (void**)&m_pMapiFolder );
	    if ( SUCCEEDED(hr) )
        {
            // Open the ACL table property on the folder.  The returned table
	        // ptr may be used to get a MAPI table for reading and it can
	        // also be used to modify the ACLs table.  If there is no acl table,
	        // this call will fail with E_NOINTERFACE.
            hr = m_pMapiFolder->OpenProperty( PR_ACL_TABLE,
								              (LPGUID)&IID_IExchangeModifyTable,
								              0,
								              MAPI_DEFERRED_ERRORS,
								              (LPUNKNOWN*)&m_pExchModifyTable );
            if ( SUCCEEDED(hr) )
            {
                // Open a MAPI table on the ACL table property.  This table can be
	            // read to determine what the ACLs table looks like.
                hr = m_pExchModifyTable->GetTable( 0, &m_pMapiTable );
                if ( SUCCEEDED(hr) )
                {
	                // Select columns needed.
	                hr = m_pMapiTable->SetColumns( (LPSPropTagArray)&rgPropTag, 0 );
                    if ( SUCCEEDED(hr) )
                    {
	                    // Get all the rows in the table up to EDK_MAX_QUERY_ROWS.  If there
	                    // are more rows than this, fail with MAPI_E_TABLE_TOO_BIG.
						hr = HrQueryAllRows( m_pMapiTable, NULL, NULL, NULL, EDK_MAX_QUERY_ROWS, &lpRows );
//	                    hr = m_pMapiTable->QueryRows( EDK_MAX_QUERY_ROWS, 0, &lpRows );
                        if ( SUCCEEDED(hr) )
                        {
 	                        // Check to be sure that table is not bigger than EDK_MAX_QUERY_ROWS.
	                        // We do this by checking whether or not the cursor is positioned at
	                        // the end of the table.
	                        if ( lpRows->cRows == EDK_MAX_QUERY_ROWS )
	                        {
		                        ULONG	ulRow =			0;
		                        ULONG	ulNumerator =	0;
		                        ULONG	ulDenominator =	0;

                        		hr = m_pMapiTable->QueryPosition( &ulRow, &ulNumerator, &ulDenominator );
		                        if ( SUCCEEDED(hr) )
                                {
		                            // SeekRowApprox() doc states that if ulNumerator == ulDenominator, you
		                            // are at the end of the table.
		                            if ( ulNumerator != ulDenominator )
                                        hr = E_FAIL;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
                                    
	// Finally assign lpRows to the returning pointer
    if ( SUCCEEDED(hr) )
    {
	    *lppRows = lpRows;
    }
    else
    {
		MAPIFREEBUFFER( lpRows );
		Cleanup();
	}

    return hr;
}

HRESULT CExchTable::Update( SROWLIST* pSRowList )
{
	if ( !pSRowList )
		return E_INVALIDARG;

	// if it is an empty list, return fail
	// remember the default and anonymous entries will never be deleted
	if ( !pSRowList->size() )
		return E_INVALIDARG;

    if ( !m_pExchModifyTable )
		return E_FAIL;

	HRESULT		hr =			E_FAIL;
	LPROWENTRY	lpRowEntry =	NULL;
	LPROWLIST	lpRowList =		NULL;

	// Make a ROWLIST for use with the IExchangeModifyTable interface.  We
	// explicitly call MAPIAllocateBuffer() here due to the size vagaries 
	// of MAPI structures.  In writing to the table, we have to drop off
	// the PR_MEMBER_NAME property, which we have conveniently placed last
	// in the SPropValue array.
	hr = MAPIAllocateBuffer( CbNewROWLIST(pSRowList->size()), (void**)&lpRowList );
	if ( SUCCEEDED(hr) )
    {
	    // First we'll clear and add all rows back to table
	    lpRowList->cEntries = pSRowList->size();
	    SROWLIST::iterator it;
	    for ( lpRowEntry = lpRowList->aEntries, it = pSRowList->begin(); it != pSRowList->end(); it++, lpRowEntry++ )
	    {
			lpRowEntry->ulRowFlags = ROW_ADD;
			lpRowEntry->cValues = (*it)->cValues - 1; 
			lpRowEntry->rgPropVals = (*it)->lpProps;
	    }

	    // Add rows
	    hr = m_pExchModifyTable->ModifyTable( ROWLIST_REPLACE, lpRowList ); 

	    if ( SUCCEEDED(hr) )
        {	
	        // Now we'll modify the new default and anonymous rows since the above actions
	        // screwed them up
	        lpRowList->cEntries = 0;
			lpRowEntry = lpRowList->aEntries;
	        for ( it = pSRowList->begin(); it != pSRowList->end(); it++ )
	        {
		        if ( ( ID_DEFAULT == (*it)->lpProps[I_MEMBER_ID].Value.l ) || 
		             ( ID_ANONYMOUS == (*it)->lpProps[I_MEMBER_ID].Value.l ) )
		        {
					lpRowEntry->ulRowFlags = ROW_MODIFY;
			        lpRowEntry->cValues = 2;										// use member id and member rights; 
			        lpRowEntry->rgPropVals = &((*it)->lpProps[I_MEMBER_RIGHTS]);    
			        lpRowList->cEntries++;
		        }
				lpRowEntry++;
	        } 

	        // Repair Default and Anonymous rows in the table.
	        hr = m_pExchModifyTable->ModifyTable( 0L, lpRowList );  
        } 

    }
    else
        return hr;

	// Deallocate the ROWLIST (not including the SPropValue ptrs, since they
	// still actually belong to the ACEMap).
	MAPIFREEBUFFER( lpRowList );

	return hr;
}

