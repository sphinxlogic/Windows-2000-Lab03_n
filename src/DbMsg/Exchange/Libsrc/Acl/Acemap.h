/* --------------------------------------------------------------------------

The header file for ACEMap class

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
#ifndef _ACEMAP_H_
#define _ACEMAP_H_
#include "ACL.h"

#pragma warning(disable:4786)
#include <map>
#include <list>
using namespace std;
#include <assert.h>

typedef CComObject< CComEnum< IEnumVARIANT,
                              &IID_IEnumVARIANT,
                              VARIANT,
                              _Copy<VARIANT> > > ENUMVAR;



class CItem
{
public:
	SRow                m_SRow;
	CComPtr<IACE>*      m_ppACE;
	CComBSTR            m_bstrEntryID;  // BSTR-ized entry id

	CItem() :  m_ppACE( NULL )
	{
	}

	CItem(LPSRow pSRow, CComBSTR bstrID ) : m_SRow( *pSRow ),
                                            m_ppACE( NULL ),
                                            m_bstrEntryID( bstrID )
	{
	}
	
	~CItem()
	{
		delete m_ppACE;  // the smart pointer is delete, it in turns
		m_ppACE = NULL;		// calls Release on pACE
	}

	HRESULT CreateACE( IACE* pACE )
	{
		HRESULT hr = E_FAIL;
		if ( pACE )
		{
			// a copy constructor of the smart pointer is called 
			// and AddRef is called on pACE
			m_ppACE = new CComPtr<IACE>(pACE);
			if ( m_ppACE )
				hr = S_OK;
			else
				hr = E_OUTOFMEMORY;
		}
		else
			hr = E_INVALIDARG;

		return hr;
	}

};

struct BSTRless : binary_function<CComBSTR, CComBSTR, bool>
{
	bool operator()( const CComBSTR& _X, const CComBSTR& _Y ) const
	{
		return ( wcscmp( _X.m_str, _Y.m_str ) > 0 );
	}
};

typedef map<CComBSTR, CItem*, BSTRless> ACEMAP;
typedef list<SRow*> SROWLIST;

class CACEMap
{
private:
	ACEMAP			m_mapACE;
	LPMAPISESSION	m_pMapiSession;
public:
	CACEMap() : m_pMapiSession(NULL)
	{
	}
	CACEMap( LPMAPISESSION pMapiSession ) : m_pMapiSession(pMapiSession)
	{
		if ( m_pMapiSession )
			m_pMapiSession->AddRef();
	}
	~CACEMap();

	DWORD Size() const
	{
		return m_mapACE.size();
	}

	CItem*& operator[]( const CComBSTR& bstrID );
	HRESULT Add( IACE* pACE );
	HRESULT BuildMap( LPSRowSet lpRows );
	HRESULT Delete( const CComBSTR& bstrID );
	HRESULT Delete( const DWORD dwIndex );
	HRESULT Find( const CComBSTR& bstrID, LPDISPATCH* ppdisp );
	HRESULT Find( const DWORD dwIndex, LPDISPATCH* ppdisp );
	HRESULT NewEnum( ENUMVAR* pEnumVar );
	HRESULT GetSRowList( SROWLIST* pSRowList );

private:
	BOOL	isValidACLSRow( const SRow& srow ) const;
	HRESULT getEntryID( const SRow& sRow, CComBSTR& bstrID );
	HRESULT getEntryID( IACE* pACE, SBinary& sbEID );
	HRESULT srowToACE ( CItem* pItem );
	HRESULT aceToSRow ( CItem* pItem );
	HRESULT getDisplayName( const SBinary& SBin, LPTSTR* lppszDisplayName );
    BSTR    binaryToBSTR( SBinary* pBinary );

};

#endif  // _ACEMAP_H_