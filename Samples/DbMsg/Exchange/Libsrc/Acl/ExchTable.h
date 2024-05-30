/* --------------------------------------------------------------------------

The header file for ExchTable class

Copyright (C) 1993-1999 Microsoft Corporation

-------------------------------------------------------------------------- */
#ifndef _EXCH_TABLE_H_
#define _EXCH_TABLE_H_

#include "ACLCommon.h"
#include "ACEMap.h"

class CExchTable 
{
private:
	// a pointer to CDO document (ie folder)
	LPEXCHANGEMODIFYTABLE	m_pExchModifyTable;
    LPMAPIFOLDER			m_pMapiFolder;		
	LPMAPITABLE				m_pMapiTable;
	LPDISPATCH				m_pdispCDODoc;
	LPMAPISESSION			m_pMapiSession;
	
public:
	CExchTable(); 

	~CExchTable();

	HRESULT SetDoc ( LPDISPATCH lpdispDoc );
	HRESULT Initialize ( LPSRowSet* lppRows );
	HRESULT	Update ( SROWLIST* pSRowList );
	HRESULT Initialize();
	HRESULT Cleanup ();
	LPMAPISESSION GetMapiSession ()
	{
		return m_pMapiSession;
	}

};

#endif   // _EXCH_TABLE_H_