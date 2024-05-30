/************************************************************************
*                                                                       *
*   $$Root$$Table.cpp													*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/


#include "StdAfx.h"
#include "$$Root$$Table.h"
#include "$$Root$$Agent.h"

C$$Root$$Table::C$$Root$$Table()
{
	m_lpAgent			= NULL;
	m_lpCollector		= NULL;
	m_lpTable			= NULL;
	m_sCollectorType	= 0;
	m_ulCurrentElem		= 0;
	m_ulNumElems		= 0;
	m_ulTableSize		= IT_DEFLT_SIZE;
}

C$$Root$$Table::C$$Root$$Table(LPUNKNOWN lpCollector, 
							   short sCollectorType, 
							   C$$Root$$Agent * lpAgent) 
{
	m_lpAgent			= lpAgent;
	m_lpCollector		= lpCollector;
	m_lpTable			= NULL;
	m_sCollectorType	= sCollectorType;
	m_ulCurrentElem		= 0;
	m_ulNumElems		= 0;
	m_ulTableSize		= IT_DEFLT_SIZE;
}

C$$Root$$Table::C$$Root$$Table(LPUNKNOWN lpCollector, 
							   short sCollectorType, 
							   C$$Root$$Agent * lpAgent, 
							   ULONG ulSize)
{
	m_lpAgent			= lpAgent;
	m_lpCollector		= lpCollector;
	m_lpTable			= NULL;
	m_sCollectorType	= sCollectorType;
	m_ulTableSize		= ulSize;
	m_ulNumElems		= 0;
	m_ulCurrentElem		= 0;
}

C$$Root$$Table::~C$$Root$$Table()
{
	LP$$ROOT$$SYNCHRONIZER lpSynchronizer = NULL;
	for (this->ResetEnumeration(); this->HasMoreElems(); )
	{
		lpSynchronizer = this->NextElem();
		if (lpSynchronizer != NULL) delete lpSynchronizer;
	}

	if (m_lpTable != NULL)
	{
		delete[] m_lpTable;
	}

	if (m_lpCollector != NULL)
	{
		m_lpCollector->Release();
		m_lpCollector = NULL;
	}
}


/********************************************************************************
*																				*
*	The following methods comprise the public interface to the					*
*	C$$Root$$Table class.  The Initialize() method MUST be called before		*
*	using the C$$Root$$Table class.  The Get() and Put() methods insert and		*
*	extract data from the C$$Root$$Table.  The HasMoreElems(), NextElem(),		*
*	and ResetEnumeration() methods are used to implement an enumeration			*
*	interface to the C$$Root$$Table.											*
*																				*
*	HRESULT C$$Root$$Table::Get(ULONG ulCb,										*
*								LPENTRYID lpEntryID,							*
*								LP$$Root$$SYNCHRONIZER * lppSynchronizer)		*
*	BOOL	C$$Root$$Table::HasMoreElems()										*
*	BOOL	C$$Root$$Table::Initialize()										*
*	LP$$ROOT$$SYNCHRONIZER	C$$Root$$Table::NextElem()							*
*	HRESULT C$$Root$$Table::Put(ULONG ulCb,										*
*								LPENTRYID lpEntryID,							*
*								lp$$Root$$SYNCHRONIZER * lppSynchronizer)		*
*	void	C$$Root$$Table::ResetEnumeration()									*
*																				*
********************************************************************************/

HRESULT C$$Root$$Table::Get(ULONG ulCb,
							LPENTRYID lpeid,
							LP$$ROOT$$SYNCHRONIZER * lppICSSynchronizer)
{
	HRESULT hResult;

	if (lpeid && lppICSSynchronizer)
	{
		hResult = GetFromTable(ulCb, 
							lpeid,
							m_ulTableSize,
							m_lpTable, 
							lppICSSynchronizer);
	}
	else
	{
		hResult = E_INVALIDARG;
	}

	return hResult;
}

BOOL C$$Root$$Table::HasMoreElems()
{
	BOOL fResult;
	fResult = FALSE;

	if (m_ulCurrentElem < m_ulTableSize) 
	{
		if (m_fNextElemReady) 
		{
			fResult = TRUE;
		}
		else
		{
			for (;m_ulCurrentElem < m_ulTableSize; m_ulCurrentElem++)
			{
				if (m_lpTable[m_ulCurrentElem] != NULL)
				{
					m_fNextElemReady = TRUE;
					fResult = TRUE;
					break;
				}
			}
		}
	}

	if (!fResult)
	{
		m_fNextElemReady = FALSE;
	}

	return fResult;
}

BOOL C$$Root$$Table::Initialize()
{
	BOOL fResult = FALSE;

	m_lpTable = new LP$$ROOT$$SYNCHRONIZER[m_ulTableSize];
	if (m_lpTable != NULL)
	{
		ZeroMemory((LPVOID)m_lpTable, m_ulTableSize * sizeof(LP$$ROOT$$SYNCHRONIZER));
		ResetEnumeration();
		fResult = TRUE;
	}

	return fResult;
}

LP$$ROOT$$SYNCHRONIZER C$$Root$$Table::NextElem()
{
	LP$$ROOT$$SYNCHRONIZER lpSynchronizer = NULL;

	if (m_fNextElemReady) 
	{
		lpSynchronizer = m_lpTable[m_ulCurrentElem++];
	}
	else 
	{
		for (;m_ulCurrentElem < m_ulTableSize; m_ulCurrentElem++)
		{
			if (m_lpTable[m_ulCurrentElem] != NULL)
			{
				lpSynchronizer = m_lpTable[m_ulCurrentElem++];
			}
		}
	}

	m_fNextElemReady = FALSE;
	return lpSynchronizer;
}

HRESULT C$$Root$$Table::Put(ULONG ulCb,
							LPENTRYID lpEntryID,
							LPMDB lpStore)
{
	HRESULT hResult = S_OK;
	LP$$ROOT$$SYNCHRONIZER lpSynchronizer = NULL;


	if ((m_ulNumElems << 1) >= m_ulTableSize) // If the table is more than half-full,
	{										  // increase the size of the table
		hResult = this->IncreaseSize();
	}

	if (SUCCEEDED(hResult))
	{
		lpSynchronizer = new C$$Root$$Synchronizer(lpStore,
												   ulCb,
												   lpEntryID,
												   this);
		if (lpSynchronizer == NULL)
		{
			hResult = E_OUTOFMEMORY;
		}
		else
		{
			hResult = lpSynchronizer->Initialize();
			if (SUCCEEDED(hResult))
			{
				hResult = AddToTable(lpSynchronizer->EntryIDCb(), 
									 lpSynchronizer->EntryID(), 
									 m_ulTableSize,
									 m_lpTable, 
									 lpSynchronizer
									 );
				if (SUCCEEDED(hResult))
				{
					m_ulNumElems++;
				}
			}
		}
	}

	//
	// Perform cleanup: 
	//
	if (FAILED(hResult))
	{
		if (lpSynchronizer != NULL) delete lpSynchronizer;
		lpSynchronizer = NULL;
	}

	return hResult;
}

void C$$Root$$Table::ResetEnumeration()
{ 
	m_ulCurrentElem = 0; 
	m_fNextElemReady = FALSE; 
}

void C$$Root$$Table::SetCurrentSynchronizer(LP$$ROOT$$SYNCHRONIZER lpSynchronizer)
{
	if (m_sCollectorType == CONTENT_COLLECTOR)
	{
		((LP$$ROOT$$CONTENTCOLLECTOR)m_lpCollector)->m_lpSynchronizer = lpSynchronizer;
	}
	else
	{
		((LP$$ROOT$$HIERARCHYCOLLECTOR)m_lpCollector)->m_lpSynchronizer = lpSynchronizer;
	}
}


/****************************************************************************************
*																						*
*	Auxiliary methods																	*
*																						*
****************************************************************************************/



//----------------------------------------------------------------------------//
//
// A static member function, used internally to add the 
// specified C$$Root$$Synchronizer object to the specified C$$Root$$Table.
//
//----------------------------------------------------------------------------//
HRESULT C$$Root$$Table::AddToTable(ULONG cb,
								   LPENTRYID lpEntryID, 
								   ULONG ulTableSize, 
								   LP$$ROOT$$SYNCHRONIZER * lpTable, 
								   LP$$ROOT$$SYNCHRONIZER lpSynchronizer  
								   ) 
{
	HRESULT hResult;
	ULONG ulEntryID;		
	ULONG ulHashKey;	
	ULONG ulOffset;
	ULONG ulNextIndex;

	hResult		= S_OK;

	if (lpSynchronizer && lpTable && lpEntryID)
	{
		// Convert the unusable ENTRYID data-structure to a ULONG
		ulEntryID	= lpeidToUl(lpEntryID, cb);		

		// Apply the hashfunction to converted ENTRYID
		ulHashKey	= HashFunction(ulEntryID, ulTableSize);

		// The current offset of the hashtable pointer
		ulOffset	= 0;

		// The current position of the hashtable pointer
		ulNextIndex = ulHashKey % ulTableSize; 

		for (; 
			 lpTable[ulNextIndex] != NULL && SUCCEEDED(hResult); 
			 ulOffset++, ulNextIndex = (ulHashKey + ulOffset) % ulTableSize)
		{
			ULONG ulResult;

			if (ulOffset == ulTableSize)  // We have cycled through the entire table
			{
				hResult = E_FAIL;
			}
			else
			{
				hResult = lpSynchronizer->equals(lpTable[ulNextIndex], &ulResult);
				if (SUCCEEDED(hResult))
				{
					if (ulResult) // We have found a synchronizer with 
					{			  // the same ENTRYID as the current table elem
						break;
					}
				}
			}
		}
	}
	else
	{
		hResult = E_INVALIDARG;
	}

	if (SUCCEEDED(hResult))
	{
		if (lpTable[ulNextIndex] != lpSynchronizer)
		{
			//
			// Delete the current entry if 
			// it is a different object than the new
			// entry
			if (lpTable[ulNextIndex] != NULL)
			{
				delete lpTable[ulNextIndex];
			}
		}
		lpTable[ulNextIndex] = lpSynchronizer;
	}

	return hResult;
}


HRESULT C$$Root$$Table::GetFromTable(ULONG ulCb, 
									 LPENTRYID lpEntryID,
									 ULONG ulTableSize,
 									 LP$$ROOT$$SYNCHRONIZER * lpTable,
									 LP$$ROOT$$SYNCHRONIZER * lppSynchronizer  // Out parameter
									 )
{
	HRESULT hResult;
	ULONG	ulEntryID;
	ULONG	ulHashKey;
	ULONG	ulOffset;
	ULONG	ulNextIndex;

	hResult		= S_OK;

	if ((lppSynchronizer == NULL) || (lpTable == NULL) || (lpEntryID == NULL))
	{
		hResult = E_INVALIDARG;
	}
	else
	{
		*lppSynchronizer = NULL;

		// Convert the unusable ENTRYID data-structure to a ULONG
		ulEntryID	= lpeidToUl(lpEntryID, ulCb);
		
		// Apply the hashfunction to ulKey
		ulHashKey	= HashFunction(ulEntryID, ulTableSize);

		// The current offset of the hashtable pointer
		ulOffset	= 0;  
		
		// The current position of the hashtable pointer
		ulNextIndex = ulHashKey % ulTableSize;  

		for (; 
			   lpTable[ulNextIndex] != NULL && SUCCEEDED(hResult); 
			   ulOffset++, ulNextIndex = (ulHashKey + ulOffset) % ulTableSize
			)
		{
			ULONG ulResult;
			
			if (ulOffset == ulTableSize) // We have cycled through the entire table
			{
				hResult = E_FAIL;
			}
			else
			{
				hResult = lpTable[ulNextIndex]->equals(
					ulCb,
					lpEntryID,
					&ulResult
					);
				if (SUCCEEDED(hResult))
				{
					if (ulResult)  // We have found an item with the correct ENTRYID
					{
						// Assign the out param
						*lppSynchronizer = lpTable[ulNextIndex];
						break;
					}
				}
			}
		}		
	}


	return hResult;
}


//
// Note that this corrupts enumeration data
//
HRESULT C$$Root$$Table::IncreaseSize()
{	
	HRESULT						hResult = S_OK;
	LP$$ROOT$$SYNCHRONIZER *	lpNewTable = NULL;
	ULONG						ulNewTableSize;

	//
	// Create a new array to store our larger table
	// 

	ulNewTableSize	= m_ulTableSize << 1;
	lpNewTable		= new LP$$ROOT$$SYNCHRONIZER[ulNewTableSize];
	if (lpNewTable == NULL)
	{
		hResult = E_OUTOFMEMORY;
	}
	else
	{
		ZeroMemory(lpNewTable, ulNewTableSize * sizeof(LP$$ROOT$$SYNCHRONIZER));
	
		//
		// Fill the new table with the elements of our current table
		//
		for (this->ResetEnumeration(); 
			 this->HasMoreElems() && SUCCEEDED(hResult);)
		{
			LP$$ROOT$$SYNCHRONIZER lpSynchronizer = this->NextElem();
			hResult = AddToTable(lpSynchronizer->EntryIDCb(), 
								 lpSynchronizer->EntryID(), 
	 							 ulNewTableSize,
								 lpNewTable, 
								 lpSynchronizer
								 );			
		}
	}

	//
	// Perform cleanup:
	//
	if (SUCCEEDED(hResult))
	{
		if (m_lpTable != NULL) 
		{
			delete[] m_lpTable; // Delete the array containing the old table
		}
		m_lpTable = lpNewTable;
		m_ulTableSize = ulNewTableSize;
	}
	else
	{
		if (lpNewTable != NULL)
		{
			delete[] lpNewTable;
			lpNewTable = NULL;
		}
	}

	this->ResetEnumeration();
	return hResult;
}

//
// Adds all bytes in the ab field of the ENTRYID
//
ULONG C$$Root$$Table::lpeidToUl(LPENTRYID lpeid, ULONG cb)
{
	ULONG ulEntryID = 0;

	//ASSERT(lpeid);

	for (ULONG i = 0; i < cb; i++) 
	{
		ulEntryID += (ULONG)(lpeid->ab[i]);
	}
	return ulEntryID;
}


C$$Root$$Table::operator string()
{
	string strTable;
	TCHAR szTemp[33];  // 33 is largest character string returned by ultoa()

	strTable = _TEXT("\nBegin output of table:"); 
	strTable += _TEXT("\nSize: ");
	_ultot(m_ulTableSize, szTemp, 10);
	strTable += szTemp;
	
	for (ULONG i = 0; i < m_ulTableSize; i++) 
	{
		if (m_lpTable[i] != NULL)
		{
			string strTableElem = *m_lpTable[i];
			strTable += _TEXT("\nElement");
			_ultot(i, szTemp, 10);
			strTable += szTemp;
			strTable += _TEXT(": ");
			strTable += strTableElem;
		}
	}

	return strTable;
}
