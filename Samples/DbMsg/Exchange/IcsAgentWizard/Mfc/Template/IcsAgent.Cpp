/************************************************************************
*                                                                       *
*   $$Root$$Agent.cpp													*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#include "stdafx.h"
#include "$$Root$$Agent.h"

C$$Root$$Agent::C$$Root$$Agent()
{
	lstrcpy(m_szFolderDataFile, _TEXT("$$FOLDERDATA_FILENAME$$"));
	lstrcpy(m_szSynchStateFile, _TEXT("synch.sav"));
	m_ulNumThreads = GetNumProcessors();

	if (!m_ulNumThreads) m_ulNumThreads = 1;
	
	m_lphThread				= NULL;
	m_lphIOCP				= NULL;
	m_fThreadsStarted		= FALSE;
	m_ulNumTables			= m_ulNumThreads;
	m_lppICSTable			= NULL;
	m_lpMAPIApp				= NULL;
	m_fICSStarted			= FALSE;	
	
}

C$$Root$$Agent::~C$$Root$$Agent()
{
	if (m_fICSStarted)
		this->Stop();
}



//
//	Initalize the agent in preparation for synchronization.
//  This method MUST be called before the Synch() method is
//  called, or the results are undefined (but probably 
//  catastrophic).  Returns ERROR_SUCCESS if successful,
//  and a win32 error code on failure
//

DWORD C$$Root$$Agent::Start() 
{
	DWORD		dwResult;
	HRESULT		hResult;

	dwResult	= ERROR_SUCCESS;


	//
	//	Check whether the system is already running.
	//
	if (m_fICSStarted)
	{
		dwResult = ERROR_ALREADY_INITIALIZED;
	}
	else
	{
		//
		// Initialize MAPI
		dwResult = InitMAPI(&m_lpMAPIApp);	
		if (dwResult == ERROR_SUCCESS)
		{
			//
			// Initialize the list of SynchID objects.  This procedure
			// merely allocates storage for all of the necessary SynchIDs.
			// These structures are populated in the call to LoadFolderData()
			dwResult = InitSynchIDs(&m_vecSynchIDs);
			if (dwResult == ERROR_SUCCESS)
			{
				//
				// Initialize the tables which will be used to store the 
				// C$$Root$$Synchronizer objects.  Recall that one collector is
				// mapped to one table.  
				dwResult = InitCollectors(m_ulNumTables, &m_lppICSTable, this);
				if (dwResult == ERROR_SUCCESS)
				{
					//
					// Propagate data from the folderdata file to the list
					// of SynchID structures
					dwResult = LoadFolderData();
					if (dwResult == ERROR_SUCCESS)
					{
						//
						// Create all of the C$$Root$$Synchronizer objects, and assign
						// them to the tables we have just created.  
						vector<LPSYNCHID>::iterator lppSynchID;
						for (lppSynchID = m_vecSynchIDs.begin(); 
							 lppSynchID != m_vecSynchIDs.end() && dwResult == ERROR_SUCCESS; 
							 ++lppSynchID)
						{
							LPMDB lpStore;
							LPSYNCHID lpSynchID;

							//ASSERT(lppSynchID != NULL);
						
							lpSynchID = *lppSynchID;
							if (lpSynchID == NULL)
							{
								dwResult = ERROR_INVALID_DATA;
							}
							else
							{
								//
								// Calls the C$$Root$$Agent's OpenMsgStore() method,
								// which caches open message stores to prevent them
								// from being opened more than once
								//
								hResult = this->OpenMsgStore(
									lpSynchID->ulStoreCb,
									lpSynchID->storeEID,
									&lpStore
									);
								if (HR_FAILED(hResult))
								{
									dwResult = ERROR_INVALID_DATA;
								}
								else
								{
									dwResult = InitSynchronizer(
										lpSynchID->ulFolderCb, 
										lpSynchID->folderEID,
										lpStore, 
										m_ulNumTables,
										m_lppICSTable
										);
								}
							}
						} // for (lppSynchID = m_vecSynchIDs.begin(); 
						  //	  lppSynchID != m_vecSynchIDs.end() && dwResult == ERROR_SUCCESS; 
						  //	  ++lppSynchID)

						//
						// Check that the loop terminated successfully 
						if (dwResult == ERROR_SUCCESS)
						{
							//
							// It may still be worthwhile to continue processing even without an
							// existing synchronization state
							dwResult = LoadSynchState();
							if (dwResult != ERROR_SUCCESS)
							{
								WarningMessage("Could not load synchronization state.");
							}

							dwResult = InitThreads(m_ulNumThreads,
												   &m_lphThread,
												   &m_lphIOCP,
												   SynchThreadProc);
							if (dwResult == ERROR_SUCCESS)
							{
								m_fThreadsStarted = TRUE;
							}
						}
					}
				}
			}
		}
	}
	
	//
	// Perform cleanup:
	//
	// If we have failed to completely start the $$Root$$ agent,
	// shut it down.  Otherwise, set a flag to show that
	// the agent has successfully started.
	//
	if (dwResult != ERROR_SUCCESS)
	{
		this->Stop();
		m_fICSStarted = FALSE;
	}
	else
	{
		m_fICSStarted = TRUE;
	}

	return dwResult;
}

											
			
//
//	Begin synchronization
//	Returns ERROR_SUCCESS if successful,
//  and a win32 error code on failure
//
DWORD C$$Root$$Agent::Synch() 
{
	DWORD dwResult = ERROR_SUCCESS;

	if (m_lphIOCP == NULL)
	{
		dwResult = ERROR_INVALID_DATA;
	}
	else
	{
		for (ULONG ulIndex = 0L; ulIndex < m_ulNumThreads; ulIndex++) 
		{
			if(m_lphIOCP[ulIndex] == NULL)
			{
				dwResult = ERROR_INVALID_HANDLE;
				break;
			}

			PostQueuedCompletionStatus(
				m_lphIOCP[ulIndex], 
				(DWORD)m_lppICSTable[ulIndex], 
				AGENT_SYNCH, 
				NULL
			);
		}
	}

	return dwResult;
}

//
// Performs synchronization on a given thread
//
DWORD WINAPI SynchThreadProc(LPVOID lpParameter)
{
	DWORD			dwBytesTransferred;
	DWORD			dwCompKey;
	HANDLE			hIOCP;
	HRESULT			hResult;
	OVERLAPPED *	lpOverlapped;

	dwCompKey		= AGENT_PAUSE;
	hIOCP			= *((HANDLE *)lpParameter);
	hResult			= S_OK;	

	while (dwCompKey != AGENT_STOP)
	{

		// Sleep until a control code comes 
		GetQueuedCompletionStatus(
			hIOCP, 
			&dwBytesTransferred, 
			&dwCompKey, 
			&lpOverlapped, 
			INFINITE
		);

		if (dwCompKey == AGENT_SYNCH)
		{
			
			// The table to be synchronized
			LP$$ROOT$$TABLE lpICSTable = (LP$$ROOT$$TABLE)dwBytesTransferred;
			if (lpICSTable == NULL)
			{
				ErrorMessage("Unexpected NULL pointer");
				return E_POINTER;
			}

			for (lpICSTable->ResetEnumeration(); 
				 lpICSTable->HasMoreElems() && HR_SUCCEEDED(hResult);)
			{
				// The next element in the table which must be synchronized
				LP$$ROOT$$SYNCHRONIZER lpNextICSSynchronizer = lpICSTable->NextElem();
				if (lpNextICSSynchronizer == NULL)
				{
					hResult = E_POINTER;
				}
				else
				{
					hResult = lpNextICSSynchronizer->Synchronize();
				}

			} // for (lpICSTable->ResetEnumeration(); lpICSTable->HasMoreElems();)

			if (HR_FAILED(hResult))
			{
				theTraceBox.Trace("ERROR in synchronization");
			}

		} // if (dwCompKey == AGENT_SYNCH)
	} // while (dwCompKey != AGENT_STOP)

	if (HR_FAILED(hResult))
	{
		return ERROR_INVALID_DATA;
	}
	else 
	{
		return ERROR_SUCCESS;
	}
}


//----------------------------------------------------------------------

//
//	Stop processing.
//

DWORD C$$Root$$Agent::Stop() 
{
	DWORD dwResult;
	dwResult = ERROR_SUCCESS;

	if (m_fThreadsStarted)
	{
		StopThreads(m_ulNumThreads,
					&m_lphThread,
					&m_lphIOCP);
		m_fThreadsStarted = FALSE;
	}

	if (m_fICSStarted)
	{
		dwResult = SaveSynchState();
		if (dwResult != ERROR_SUCCESS)
		{
			WarningMessage("Could not save synchronization state");
		}
	}

	//
	//	Delete all of the ICS tables.
	//

	if (m_lppICSTable != NULL)
	{
		for (ULONG i = 0; i < m_ulNumTables; i++)
		{
			if (m_lppICSTable[i] != NULL) {
				delete m_lppICSTable[i];
				m_lppICSTable[i] = NULL;
			}
		}
		delete[] m_lppICSTable;
		m_lppICSTable = NULL;
	}


	vector<LPSYNCHID>::iterator lppSynchID;
	for (lppSynchID = m_vecSynchIDs.begin(); lppSynchID != m_vecSynchIDs.end(); ++lppSynchID)
	{
		//ASSERT(lppSynchID != NULL);

		LPSYNCHID lpSynchID = *lppSynchID;
		if (lpSynchID != NULL)
		{
			MAPIFreeBuffer(lpSynchID);
			lpSynchID = NULL;
		}
	}
	m_vecSynchIDs.erase(m_vecSynchIDs.begin(), m_vecSynchIDs.end());


	//
	// Delete all elements of the StoreID list
	//
	
	vector<LPSTOREID>::iterator lppStoreIDs;
	for (lppStoreIDs = m_vecStoreIDs.begin(); lppStoreIDs != m_vecStoreIDs.end(); ++lppStoreIDs)
	{
		//ASSERT(lppStoreIDs != NULL);

		SStoreID * lpStoreID = *lppStoreIDs;
		if (lpStoreID != NULL)
		{
			// Log off message store
			LPMDB lpStore = lpStoreID->lpStore;
			if (lpStore != NULL)
			{
				ULONG fLogoffFlags = LOGOFF_ORDERLY;
				lpStore->StoreLogoff(&fLogoffFlags);
				lpStore->Release();
				lpStore = NULL;
			}
			MAPIFreeBuffer(lpStoreID);
			lpStoreID = NULL;
		}
	}
	m_vecStoreIDs.erase(m_vecStoreIDs.begin(), m_vecStoreIDs.end());


	// Closes down the current MAPI session, and
	// frees all memory it was using
	if (m_lpMAPIApp != NULL) 
	{
		delete m_lpMAPIApp;
		m_lpMAPIApp = NULL;
	}

	m_fICSStarted = FALSE;
	return dwResult;
}

//--------------------------------------------------------------//
//																//
//					Auxiliary methods							//
//																//
//--------------------------------------------------------------//

//
// Given an ENTRYID, returns the synchronizer object
// monitoring the object with that ENTRYID.  The synchronizer
// object is returned in the out parameter. The return value
// is a windows error code
// 
DWORD C$$Root$$Agent::GetSynchronizer(ULONG ulCb,
								 LPENTRYID lpeid,
								 LP$$ROOT$$SYNCHRONIZER * lppICSSynchronizer)
{
	DWORD dwResult;
	HRESULT hResult;

	dwResult = ERROR_SUCCESS;

	//
	// Check that the parameters are all valid
	if ((lpeid == NULL) ||
		(lppICSSynchronizer == NULL))
	{
		dwResult = ERROR_INVALID_PARAMETER;
	}
	else
	{
		*lppICSSynchronizer = NULL;

		for (ULONG ulNumTable = 0L; 
			 ulNumTable < m_ulNumTables && dwResult == ERROR_SUCCESS; 
			 ulNumTable++)
		{
			//
			// Do not search NULL tables
			if (m_lppICSTable[ulNumTable] == NULL) continue;

			//
			// Attempt to find a synchronizer monitoring an 
			// object with the specified ENTRYID
			hResult = m_lppICSTable[ulNumTable]->Get(ulCb, lpeid, lppICSSynchronizer);
			if (HR_FAILED(hResult))
			{
				dwResult = ERROR_INVALID_DATA;
			}
			else
			{
				if (*lppICSSynchronizer != NULL)
				{
					break;
				}
			}
		}

	    if (*lppICSSynchronizer == NULL)
		{
			dwResult = ERROR_NOT_FOUND;
		}
	}

	return dwResult;
}

//
// Given an ENTRYID, returns the synchronizer object
// monitoring the object with that ENTRYID.  The synchronizer
// object is returned in the out parameter.  The return value is
// a windows error code
// 
DWORD C$$Root$$Agent::GetSynchronizer(ULONG ulCb,
								 LPENTRYID lpeid,
								 short sCollectorType,
								 LP$$ROOT$$SYNCHRONIZER * lppICSSynchronizer)
{
	DWORD dwResult;
	HRESULT hResult;

	dwResult = ERROR_SUCCESS;

	//
	// Check that the parameters are all valid
	if ((lpeid == NULL) ||
		(lppICSSynchronizer == NULL))
	{
		dwResult = ERROR_INVALID_PARAMETER;
	}
	else
	{
		*lppICSSynchronizer = NULL;

		for (ULONG ulNumTable = 0L; 
			 ulNumTable < m_ulNumTables && dwResult == ERROR_SUCCESS; 
			 ulNumTable++)
		{
			//
			// Do not search NULL tables
			if ((m_lppICSTable[ulNumTable] == NULL) ||
				(m_lppICSTable[ulNumTable]->CollectorType() != sCollectorType)) continue;
		
			//
			// Attempt to find a synchronizer monitoring an 
			// object with the specified ENTRYID
			hResult = m_lppICSTable[ulNumTable]->Get(ulCb, lpeid, lppICSSynchronizer);
			if (HR_FAILED(hResult))
			{
				dwResult = ERROR_INVALID_DATA;
			}
			else
			{
				if (*lppICSSynchronizer != NULL)
				{
					break;
				}
			}
		}
		if (*lppICSSynchronizer == NULL)
		{
			dwResult = ERROR_NOT_FOUND;
		}
	}

	return dwResult;
}


	
//-----------------------------------------------------------------------//


//-----------------------------------------------------------------------//

//
// Opens the exchange store specified by ulStoreCb and lpStoreEID.
// Caches the stores it opens in m_lppStoreEIDs.  If the store
// can already be found in this list, returns this store from the list.
// The store is returned in the out parameter, lppStore.
//
HRESULT C$$Root$$Agent::OpenMsgStore(ULONG ulStoreCb,
									 LPENTRYID lpStoreEID,
									 LPMDB FAR * lppStore)
{
	TCHAR str[256];
	BOOL fFoundStore;
	HRESULT hResult;
	LPMAPISESSION lpMAPISession;
	ULONG ulResult;

	fFoundStore = FALSE;
	hResult = S_OK;

	if (lppStore == NULL)
	{
		hResult = E_INVALIDARG;
	}
	else
	{
		*lppStore = NULL;

		if (m_lpMAPIApp == NULL)
		{
			hResult = E_POINTER;
		}
		else
		{
			lpMAPISession = m_lpMAPIApp->Session();
			if (lpMAPISession == NULL)
			{
				hResult = E_POINTER;
			}
			else
			{			
				//
				// Attempt to find the message store in the vector
				// of opened store IDs
				vector<LPSTOREID>::iterator lppStoreIDs;
				for (lppStoreIDs = m_vecStoreIDs.begin(); 
					 lppStoreIDs != m_vecStoreIDs.end() && HR_SUCCEEDED(hResult); 
					 ++lppStoreIDs)
				{
					//ASSERT(lppStoreIDs != NULL);

					LPSTOREID lpStoreID = *lppStoreIDs;
					if (lpStoreID == NULL) break;
					
					hResult = lpMAPISession->CompareEntryIDs(
						lpStoreID->ulStoreCb,
						lpStoreID->storeEID,
						ulStoreCb,
						lpStoreEID,
						0L,
						&ulResult);
					if (HR_SUCCEEDED(hResult))
					{
						if (ulResult)
						{
							*lppStore = lpStoreID->lpStore;
							fFoundStore = TRUE;
						}
					}
				} // for (lppStoreIDs = m_vecStoreIDs.begin(); 
				  //	  lppStoreIDs != m_vecStoreIDs.end() && HR_SUCCEEDED(hResult); 
				  //	  ++lppStoreIDs)

				//
				// If we have not encountered an error, but we have not found
				// an open store matching the specified ENTRYID, attempt to 
				// open the store ourselves
				if (HR_SUCCEEDED(hResult) && !fFoundStore)
				{				
					hResult = m_lpMAPIApp->Session()->OpenMsgStore(
						NULL,
						ulStoreCb,
						lpStoreEID,
						&IID_IMsgStore,
						MAPI_BEST_ACCESS,
						lppStore
						);			
					if (HR_SUCCEEDED(hResult))
					{
						SizedSPropTagArray(1,storeProps) =
						{
							1,
							{
								PR_DISPLAY_NAME
							}
						};
								
						ULONG			uValuesCount;
						LPSPropValue	lpProps;
						
						hResult = (*lppStore)->GetProps(
							 (LPSPropTagArray)&storeProps,
							 0,
							 &uValuesCount,
							 &lpProps
						);
						if (HR_SUCCEEDED(hResult))
						{
							
							//ASSERT(uValuesCount == 1);
							//ASSERT(lpProps[0].ulPropTag == PR_DISPLAY_NAME);

							LPTSTR lpszDisplayName = lpProps[0].Value.lpszA;
							_stprintf(str, "Opened message store: %s\0", lpszDisplayName);
							StatusMessage(str);

							//
							// Create a StoreID representing the newly opened
							// IMsgStore
							//
							
							LPSTOREID lpStoreID;
							MAPIAllocateBuffer(sizeof(SStoreID),
											   (LPVOID *)&lpStoreID);

							lpStoreID->lpStore			= *lppStore;
							lpStoreID->lpszDisplayName	= lpszDisplayName;
							lpStoreID->storeEID			= lpStoreEID;
							lpStoreID->ulStoreCb		= ulStoreCb;

							m_vecStoreIDs.push_back(lpStoreID);
						}
					}
				}
			}
		}
	}
	
	//
	// Perform cleanup:
	// If an error was encountered, we must release
	// any stores we have opened.  
	if (HR_FAILED(hResult))
	{
		if (!fFoundStore)
		{
			if (lppStore != NULL)
			{
				if (*lppStore != NULL)
				{
					ULONG	fLogoffFlags = LOGOFF_ORDERLY;
					(*lppStore)->StoreLogoff(&fLogoffFlags);
					(*lppStore)->Release();
					(*lppStore) = NULL;
				}
			}
		}
	}
	
	return hResult;

}

/************************************************************************************
*																					*
*	The following functions are used to initialize the data structures				*
*	used by the $$Root$$ agent.														*
*	These functions include:														*
*																					*
*	static DWORD C$$Root$$Agent::InitCollectors(ULONG ulNumTables,					*
*										   LP$$ROOT$$TABLE ** lpppICSTable,			*
*										   C$$Root$$Agent * lpAgent);				*
*  	static DWORD C$$Root$$Agent::InitMAPI(C$$Root$$MAPIApp ** lppMAPIApp);			*
*	static DWORD C$$Root$$Agent::InitSynchIDs(vector<LPSYNCHID> * lpVecSynchIDs);	*
*
*   In each case, initialization is done through the modification of the input		*
*	parameter.  Success/failure is indicated by the value of the out parameter,		*
*	which is a win32 error code														*
*																					*
************************************************************************************/

DWORD C$$Root$$Agent::InitCollectors(ULONG ulNumTables,
									 LP$$ROOT$$TABLE ** lpppICSTable,
									 LP$$ROOT$$AGENT lpAgent)
{
	DWORD dwResult;
	LPUNKNOWN * lppCollector;
	short sCollectorType;
	
	dwResult = ERROR_SUCCESS;

	//
	// Check that the parameter is valid
	if (lpppICSTable == NULL)
	{
		dwResult = ERROR_INVALID_PARAMETER;
	}
	else
	{
		// 
		// Allocate memory for a set of ICS tables
		//
		*lpppICSTable = new LP$$ROOT$$TABLE[ulNumTables];
		if (*lpppICSTable == NULL)
		{
			dwResult = ERROR_NOT_ENOUGH_MEMORY;
		}
		else
		{		
			ZeroMemory((LPVOID)(*lpppICSTable), sizeof(LP$$ROOT$$TABLE) * ulNumTables);

			//
			//	Create a set of collector objects
			//  (currently use only content collectors)
			//
			sCollectorType = CONTENT_COLLECTOR;
			lppCollector = new LPUNKNOWN[ulNumTables];
			if (lppCollector == NULL)
			{
				dwResult = ERROR_NOT_ENOUGH_MEMORY;
			}
			else
			{
				ZeroMemory((LPVOID)lppCollector, sizeof(C$$Root$$ContentCollector *) * ulNumTables);

				for (ULONG ulIndex = 0; 
					 ulIndex < ulNumTables && dwResult == ERROR_SUCCESS; 
					 ulIndex++) 
				{
					lppCollector[ulIndex] = new C$$Root$$ContentCollector();
					if (lppCollector[ulIndex] == NULL)
					{
						dwResult = ERROR_NOT_ENOUGH_MEMORY;
					}
					else
					{
						(*lpppICSTable)[ulIndex] = new C$$Root$$Table((LPUNKNOWN)lppCollector[ulIndex],
								 									  sCollectorType,
																	  lpAgent);
						if ((*lpppICSTable)[ulIndex] == NULL)
						{
							dwResult = ERROR_NOT_ENOUGH_MEMORY;
						}
						else
						{
							if (!((*lpppICSTable)[ulIndex]->Initialize()))
							{
								dwResult = ERROR_INVALID_DATA;
							}
						}
					}
				} // for (ULONG ulIndex = 0;
				  //      ulIndex < m_ulNumTables && dwResult == ERROR_SUCCESS; 
				  //      ulIndex++) 
			}
		}
	}

	//
	// Perform cleanup:
	// 
	// If we have failed to successfully initialize all of our
	// collector tables, we must deallocate everything we 
	// allocated in this procedure.  Otherwise, we need only deallocate
	// the array of LP$$ROOT$$TABLE objects, which is a local variable
	//
	if (dwResult != ERROR_SUCCESS)
	{
		if (lpppICSTable != NULL)
		{
			if (*lpppICSTable != NULL)
			{
				for (ULONG ulIndex = 0; ulIndex < ulNumTables; ulIndex++)
				{
					if ((*lpppICSTable)[ulIndex] != NULL)
					{
						delete (*lpppICSTable)[ulIndex];
						(*lpppICSTable)[ulIndex] = NULL;
					}
				}
				delete[] *lpppICSTable;
				*lpppICSTable = NULL;
			}
		}
		
		if (lppCollector != NULL)
		{
			for (ULONG ulIndex = 0; ulIndex < ulNumTables; ulIndex++)
			{
				if (lppCollector[ulIndex] != NULL)
				{
					delete lppCollector[ulIndex];
					lppCollector[ulIndex] = NULL;
				}
			}
		}
	}

	//
	// We must delete lppCollector regardless of success or failure
	//
	if (lppCollector != NULL)
	{
		delete[] lppCollector;
		lppCollector = NULL;
	}

	return dwResult;
}



DWORD C$$Root$$Agent::InitMAPI(C$$Root$$MAPIApp ** lppMAPIApp)
{
	DWORD dwResult;

	dwResult = ERROR_SUCCESS;

	//
	// Check that the parameter is valid
	if (lppMAPIApp == NULL)
	{
		dwResult = ERROR_INVALID_PARAMETER;
	}
	else
	{
		//
		// Attempt to start a new MAPI session
		// 
		*lppMAPIApp = new C$$Root$$MAPIApp;
		if (*lppMAPIApp == NULL)
		{
			dwResult = ERROR_NOT_ENOUGH_MEMORY;
		}
		else if (HR_FAILED((*lppMAPIApp)->Status()))
		{
			dwResult = ERROR_INVALID_DATA;
		}
	}

	//
	// Perform cleanup: 
	//
	// If MAPI did not start successfully, close the
	// MAPI session by deleting the C$$Root$$MAPIApp object
	//
	if (dwResult != ERROR_SUCCESS)
	{
		if (lppMAPIApp != NULL)
		{
			if (*lppMAPIApp != NULL)
			{
				delete *lppMAPIApp;
				*lppMAPIApp = NULL;
			}
		}
	}

	return dwResult;
}

//
// Initializes the member variable m_lppSynchIDs, which is 
// used to keep track of which folders are to be synchronized
//
DWORD C$$Root$$Agent::InitSynchIDs(vector<LPSYNCHID> * lpVecSynchIDs)
{
	DWORD dwResult;

	dwResult = ERROR_SUCCESS;
	//
	// This code is generated by the ICS Appwizard to 
	// initialize the data structures used in this program.
	// Modifying this code is extremely risky.
	//
$$BEGINLOOP(NUM_FOLDERS);
	{
		LPSYNCHID lpSynchID;

		// Create ENTRYID structures
		SizedENTRYID($$FOLDER_CB$$, folderEID);
		ULONG ulFolderCb = $$FOLDER_CB$$;
		SizedENTRYID($$STORE_CB$$, storeEID);
		ULONG ulStoreCb = $$STORE_CB$$;
		
		MAPIAllocateBuffer(sizeof(SSynchID),
						   (LPVOID *)&lpSynchID);

		lpSynchID->ulFolderCb	= $$FOLDER_CB$$;
		lpSynchID->ulStoreCb	= $$STORE_CB$$;

		MAPIAllocateMore(sizeof(folderEID),
						 (LPVOID)lpSynchID,
						 (LPVOID *)&(lpSynchID->folderEID));

		ZeroMemory((LPENTRYID)&folderEID, sizeof(folderEID));

		CopyMemory(lpSynchID->folderEID,
				   (LPENTRYID)&folderEID,
				   sizeof(folderEID));

		MAPIAllocateMore(sizeof(storeEID),
						 (LPVOID)lpSynchID,
						 (LPVOID *)&(lpSynchID->storeEID));

		ZeroMemory((LPENTRYID)&storeEID, sizeof(storeEID));

		CopyMemory(lpSynchID->storeEID,
				   (LPENTRYID)&storeEID,
				   sizeof(storeEID));
		
		lpVecSynchIDs->push_back(lpSynchID);
	}
$$ENDLOOP;

	return dwResult;
}

//
// Prepares a folder for synchronization
//
DWORD C$$Root$$Agent::InitSynchronizer(ULONG ulFolderCb,
									   LPENTRYID lpFolderEntryID,
									   LPMDB lpStore, 
									   ULONG ulNumTables,
									   LP$$ROOT$$TABLE * lppICSTable)
{

	DWORD dwResult;
	HRESULT hResult;
	static ULONG ulCollectorNumber = 0;
	
	dwResult = ERROR_SUCCESS;
	hResult = lppICSTable[ulCollectorNumber]->Put(ulFolderCb,
												  lpFolderEntryID,
												  lpStore);
	if (HR_SUCCEEDED(hResult))
	{
		ulCollectorNumber = (ulCollectorNumber + 1) % ulNumTables;
	}
	else
	{	
		dwResult = ERROR_INVALID_DATA;
	}

	return dwResult;
}


/********************************************************************************
*																				*
*	The following functions are used to initialize and de-initialize			*
*   the threading constructs used by the $$Root$$ agent.						*
*	These functions include:													*
*																				*
*		static DWORD C$$Root$$Agent::InitThreads(ULONG,							*
*											HANDLE **,							*
*											HANDLE **,							*
*											LPTHREAD_START_ROUTINUE);			*
*		static DWORD C$$Root$$Agent::StopThreads(ULONG,						    *
*											HANDLE **,							*
*											HANDLE **);							*
*																				*
********************************************************************************/


DWORD C$$Root$$Agent::InitThreads(ULONG ulNumThreads,
							 HANDLE ** lpphThread,
							 HANDLE ** lpphIOCP,
							 LPTHREAD_START_ROUTINE lpThreadProc)
{
	DWORD				dwResult;
	ULONG				ulStartedThreads;
	
	dwResult			= ERROR_SUCCESS;
	ulStartedThreads	= 0;
	
	//
	// Check for invalid parameters
	//
	if ((ulNumThreads <= 0) || (lpphThread == NULL) || (lpphIOCP == NULL))
	{
		dwResult = ERROR_INVALID_PARAMETER;
	}
	else
	{
		*lpphThread = NULL;
		*lpphIOCP = NULL;

		// Allocate memory for an array of threads
		*lpphThread = new HANDLE[ulNumThreads];
		if (*lpphThread == NULL)
		{
			dwResult = ERROR_NOT_ENOUGH_MEMORY;
		}
		else
		{
			ZeroMemory((LPVOID)(*lpphThread), sizeof(HANDLE) * ulNumThreads);

			// Allocate memory for an array of IOCP's
			*lpphIOCP = new HANDLE[ulNumThreads];
			if (*lpphIOCP == NULL)
			{
				dwResult = ERROR_NOT_ENOUGH_MEMORY;
			}
			else
			{
				ZeroMemory((LPVOID)(*lpphIOCP), sizeof(HANDLE) * ulNumThreads);

				for (ulStartedThreads = 0; ulStartedThreads < ulNumThreads; ulStartedThreads++)
				{
					DWORD dwThreadId;

					//
					// Create an IOCP
					//
					(*lpphIOCP)[ulStartedThreads] = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
					if (((*lpphIOCP)[ulStartedThreads]) == NULL)
					{
						dwResult = GetLastError();
						break;
					}

					//
					// Create a new thread, passing the new IOCP as a parameter.
					// This IOCP will be used to communicate with the thread.
					//
					(*lpphThread)[ulStartedThreads] = CreateThread(
						NULL,										// Security attributes							 
						0L,											// Initial stack size of new thread
						lpThreadProc,								// Starting point of new thread
						(LPVOID)((*lpphIOCP) + ulStartedThreads),	// The address of the new IOCP
						0L,											// Creation flags
						&dwThreadId);								// The thread ID
					if ((*lpphThread)[ulStartedThreads] == NULL)
					{
						dwResult = GetLastError();
						break;
					}

				} // for (ULONG ulStartedThreads = 0; ulStartedThreads < ulNumThreads; ulStartedThreads++)
			} // if (*lpphIOCP == NULL)
		} // if (*lppThread == NULL)
	} // if (ulNumThreads <= 0)

	if (dwResult != ERROR_SUCCESS)
	{
		StopThreads(ulNumThreads,
					lpphThread,
					lpphIOCP);
	}

	//
	// Return a value to indicate success/failure
	//
	return dwResult;
}

DWORD C$$Root$$Agent::StopThreads(ULONG ulNumThreads,
							 HANDLE ** lpphThread,
							 HANDLE ** lpphIOCP)
{
	BOOL					fForcibleTermination;
	DWORD					dwResult; 
	
	fForcibleTermination	= TRUE;
	dwResult				= ERROR_SUCCESS;


	if ((lpphThread != NULL)	&&
		(lpphIOCP != NULL)		&&
		(*lpphThread != NULL)	&&
		(*lpphIOCP != NULL))
	{
		fForcibleTermination = FALSE;
	}

	if (!fForcibleTermination)
	{
		//
		// Stop all started threads.
		//
		for (ULONG ulIndex = 0; ulIndex < ulNumThreads; ulIndex++)
		{
			HANDLE hThread;
			HANDLE hIOCP;

			hThread = (*lpphThread)[ulIndex];
			hIOCP	= (*lpphIOCP)[ulIndex];

			if ((hThread != NULL) && (hIOCP != NULL))
			{
				// Tell the thread to terminate
				PostQueuedCompletionStatus(
					hIOCP, 
					NULL, 
					AGENT_STOP, 
					NULL
				);

				// Wait for the thread to terminate
				WaitForSingleObjectEx(
					hThread,
					INFINITE,
					FALSE
					);

				// Close the handle to the thread
				CloseHandle(hThread);
				(*lpphThread)[ulIndex] = NULL;
			}
			else
			{
				fForcibleTermination = TRUE;
				break;
			}
		}
		delete[] *lpphThread;
		*lpphThread = NULL;
	}

	//
	// This flag is set to TRUE if something has gone wrong, and
	// the state of the threads executing is unknown.  The threads
	// are forcibly terminated with the TerminateThread() function.
	//
	if (fForcibleTermination)
	{
		if (lpphThread != NULL)
		{
			if (*lpphThread != NULL)
			{
				for (ULONG ulIndex = 0; ulIndex < ulNumThreads; ulIndex++)
				{
					HANDLE hThread;

					hThread = (*lpphThread)[ulIndex];
					if (hThread != NULL)
					{
						TerminateThread(hThread, ERROR_INVALID_DATA);
						CloseHandle(hThread);
						(*lpphThread)[ulIndex] = NULL;
					}
				}
				delete[] *lpphThread;
				*lpphThread = NULL;
			}
		}					

		if (lpphIOCP != NULL)
		{
			if (*lpphIOCP != NULL)
			{
				//
				// Close all IOCPs
				//
				for (ULONG ulIndex = 0; ulIndex < ulNumThreads; ulIndex++)
				{
					HANDLE hIOCP;

					hIOCP = (*lpphIOCP)[ulIndex];
					if (hIOCP != NULL)
					{
						CloseHandle(hIOCP);
						(*lpphIOCP)[ulIndex] = NULL;
					}
				}
				delete[] *lpphIOCP;
				*lpphIOCP = NULL;
			}
		}
		dwResult = ERROR_INVALID_DATA;
	}
	return dwResult;
}
		


/********************************************************************************
*																				*
*	The following functions are used to implement the persisted state			*
*	of the $$Root$$ agent.  These functions include:							*
*																				*
*		DWORD C$$Root$$Agent::LoadFolderData()								*
*		DWORD C$$Root$$Agent::LoadSynchState()								*
*		DWORD C$$Root$$Agent::SaveSynchState()								*
*																				*
********************************************************************************/


//
// Assigns ENTRYIDs to the member variable m_lppSynchIDs
// based on data found in the folderdata file.  
//
DWORD C$$Root$$Agent::LoadFolderData()
{
	BOOL bResult;
	DWORD dwNumBytesRead;
	DWORD dwResult;
	HANDLE hFile;

	dwResult = ERROR_SUCCESS;

$$IF(PROJTYPE_NTSERVICE)
	SetCurrentDirectory(g_szICSDataDirectory);  

$$ENDIF
	//
	// Attempt to open the file in which the folder data
	// is stored
	hFile = CreateFile(
		m_szFolderDataFile,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		dwResult = GetLastError();
	}
	else
	{
		//
		// Parse the contents of the folder datafile.
		// The folder datafile has the following format
		// (expressed in BNF syntax):
		//
		// FOLDER DATA	<-- (FLDR_CB FLDR_EID STORE_CB STORE_CB)*  NULL_TERMINAL
		// FLDR_CB		<-- DWORD  (represents the count in bytes of the folder ENTRYID)
		// FLDR_EID		<-- FLDR_EID_ABFLAGS  FLDR_EID_AB  (represents fields of the 
		//													folder's ENTRYID structure)
		// STORE_CB		<-- DWORD  (represents the count in bytes of the store ENTRYID.  
		//							The store will be the store in which the given folder
		//							is located)
		// STORE_EID	<-- STORE_EID_ABFLAGS STORE_EID_AB (represents fields of the
		//													store's ENTRYID structure)
		//
		// NOTE:  The CB fields in the folder datafile are not actually
		//		  used.  The CB of both the folder and the store are assigned
		//		  to the SynchID strucure in the InitSynchIDs() method.  
		//
		vector<LPSYNCHID>::iterator lppSynchIDs;
		for (lppSynchIDs = m_vecSynchIDs.begin(); 
			 lppSynchIDs != m_vecSynchIDs.end() && dwResult == ERROR_SUCCESS; 
			 ++lppSynchIDs)
		{
			const int	NUM_BUFFERS = 6;
			LPSYNCHID	lpSynchID;	
			LPVOID		lppBuffer[NUM_BUFFERS];		
			ULONG		ulBufferSize[NUM_BUFFERS];	
			ULONG		ulCbOut;


			//ASSERT(lppSynchIDs != NULL);

			lpSynchID	= *lppSynchIDs;

			//
			// We wish to write data from the file into members
			// of the lpSynchID data structure.  For convenience,
			// we assign store the locate locations to which 
			// we will write data in an array.
			lppBuffer[0] = (LPVOID)&ulCbOut;
			lppBuffer[1] = (LPVOID)lpSynchID->folderEID->abFlags;
			lppBuffer[2] = (LPVOID)lpSynchID->folderEID->ab;
			lppBuffer[3] = (LPVOID)&ulCbOut;
			lppBuffer[4] = (LPVOID)lpSynchID->storeEID->abFlags;
			lppBuffer[5] = (LPVOID)lpSynchID->storeEID->ab;

			//
			// Here we specify the amount of data we are going to
			// write to each of the above buffers.
			ulBufferSize[0] = sizeof(ULONG);
			ulBufferSize[1] = sizeof(BYTE) * 4;
			ulBufferSize[2] = sizeof(BYTE) * lpSynchID->ulFolderCb;
			ulBufferSize[3] = sizeof(ULONG);
			ulBufferSize[4] = sizeof(BYTE) * 4;
			ulBufferSize[5] = sizeof(BYTE) * lpSynchID->ulStoreCb;

			for (int i = 0; 
				 i < NUM_BUFFERS && dwResult == ERROR_SUCCESS; 
				 i++)
			{
				bResult = ReadFile(hFile,
								   lppBuffer[i],
								   ulBufferSize[i],
								   &dwNumBytesRead,
								   NULL);
				if (!bResult)
				{
					dwResult = GetLastError();
				}
				else if (dwNumBytesRead != ulBufferSize[i])
				{
					dwResult = ERROR_INVALID_DATA;
				}
			}
		}
	}
	
	//
	// Do cleanup
	//
	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		CloseHandle(hFile);
		hFile = NULL;
	}

	return dwResult;
}



//
// Reads the SynchState file, and propagates the synchronization 
// state to all synchronizers.  
//
DWORD C$$Root$$Agent::LoadSynchState()
{
	BOOL			bResult;
	DWORD			dwResult;
	HANDLE			hFile;
	HRESULT			hResult;
	LARGE_INTEGER	zero;
	LPVOID			lpBuffer;
	
	dwResult = ERROR_SUCCESS;
	lpBuffer = NULL;

$$IF(PROJTYPE_NTSERVICE)
	SetCurrentDirectory(g_szICSDataDirectory);  

$$ENDIF

	//
	// Open the SynchState file for reading
	//
	hFile = CreateFile(m_szSynchStateFile, 
				   	   GENERIC_READ,
					   0,
					   NULL,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL,
					   NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		dwResult = GetLastError();
	}
	else
	{	
		//
		// Initialize the LARGE_INTEGER structure
		// This will be used to set the seek pointer
		// of the IStream interface which we will
		// write the synchronization state to
  		zero.HighPart	= 0x00000000;
		zero.LowPart	= 0x00000000;
		zero.QuadPart	= 0x0000000000000000;  // Used on 64-bit machines

		//
		// If the agent was initialized correctly, each SynchID in 
		// the vector m_vecSynchIDs will have a corresponding entry
		// in the synchstate file.  
		//
		vector<LPSYNCHID>::iterator lppSynchIDs;
		for (lppSynchIDs = m_vecSynchIDs.begin(); 
			 lppSynchIDs != m_vecSynchIDs.end() && dwResult == ERROR_SUCCESS; 
			 ++lppSynchIDs)
		{
			DWORD				dwNumBytesRead;
			DWORD				dwSynchStateSize;
			LP$$ROOT$$SYNCHRONIZER	lpICSSynchronizer;
			LPSTREAM			lpSynchState;
			LPSYNCHID			lpSynchID;

			//ASSERT(lppSynchIDs != NULL);

			lpBuffer		= NULL;
			lpSynchID		= *lppSynchIDs;

			//
			// The GetSynchronizer() method finds the synchronizer object
			// that corresponds to lpSynchID->folderEID, and stores it
			// in lpICSSynchronizer
			//
			dwResult = GetSynchronizer(lpSynchID->ulFolderCb, 
					 				   lpSynchID->folderEID, 
									   &lpICSSynchronizer);
			if (dwResult == ERROR_SUCCESS)
			{
				//
				// Extract the synchronization state from this
				// C$$Root$$Synchronizer object.  We will ultimately be
				// writing the new synchstate to this IStream interface
				lpSynchState	= lpICSSynchronizer->SynchState();

				//ASSERT(lpSynchState != NULL);

				//
				// Read the length of the synchstate data
				bResult = ReadFile(hFile,
								   &dwSynchStateSize,
								   sizeof(DWORD),
								   &dwNumBytesRead,
								   NULL);
				if (!bResult)
				{
					dwResult = GetLastError();
				}
				else
				{
					// Now that we know the size of the synchstate data,
					// we can create a buffer large enough to hold it
					lpBuffer = new BYTE[dwSynchStateSize];
					if (lpBuffer == NULL)
					{
						dwResult = ERROR_NOT_ENOUGH_MEMORY;
					}
					else
					{
						//
						// Read the synchstate into the buffer we just created
						bResult = ReadFile(hFile,
										   lpBuffer,
										   sizeof(BYTE) * dwSynchStateSize,
										   &dwNumBytesRead,
										   NULL);
						if (!bResult)
						{
							dwResult = GetLastError();
						}
						else
						{
							//
							// Set the synchstate's seek pointer to zero
							// in order to write the synchstate to the beginning
							// of the IStream interface
							hResult = lpSynchState->Seek(zero, STREAM_SEEK_SET, NULL);
							if (HR_FAILED(hResult))
							{
								dwResult = ERROR_INVALID_DATA;
							}
							else
							{
								//
								// Write the synchstate to the IStream interface
								hResult = lpSynchState->Write(lpBuffer, dwSynchStateSize, NULL);
								if (HR_FAILED(hResult))
								{
									dwResult = ERROR_INVALID_DATA;
								}
								else
								{
									hResult = lpICSSynchronizer->RefreshState();
									if (HR_FAILED(hResult))
									{
										dwResult = ERROR_INVALID_DATA;
									}
									else
									{
										//
										// Deallocate the temporary buffer we used
										if (lpBuffer != NULL) 
										{
											delete[] lpBuffer;
											lpBuffer = NULL;
										}
									}
								}
							}
						}
					}
				}
			}
		} // for (lppSynchIDs = m_vecSynchIDs.begin(); lppSynchIDs != m_vecSynchIDs.end(); ++lppSynchIDs)
	}
	
	//
	// Do cleanup
	//

	if (lpBuffer != NULL)
	{
		delete[] lpBuffer;
		lpBuffer = NULL;
	}

	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{		
		CloseHandle(hFile);
		hFile = NULL;
	}

	//
	// Return a value to indicate success/failure
	//
	return dwResult;
}

  
//
// Saves the synchronization state in the 
// class's synchstate file.
//
DWORD C$$Root$$Agent::SaveSynchState()
{
	BOOL bResult;
	DWORD dwResult;
    HANDLE hFile;
	HRESULT hResult;
	LARGE_INTEGER zero;
	LPVOID lpBuffer;
	ULARGE_INTEGER nextSeek;

	dwResult = ERROR_SUCCESS;
	lpBuffer = NULL;

$$IF(PROJTYPE_NTSERVICE)
	SetCurrentDirectory(g_szICSDataDirectory);  

$$ENDIF
	//
	// Create a new file to write the synchronization state
	// of the agent to. This overwrites the previous synchstate
	// file.
    hFile = CreateFile(m_szSynchStateFile, 
					   GENERIC_WRITE,
					   0,
					   NULL,
					   CREATE_ALWAYS,
					   FILE_ATTRIBUTE_NORMAL,
					   NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		dwResult = GetLastError();
	}
	else
	{
		//
		// Initialize the LARGE_INTEGER structure
		// This will be used to set the seek pointer
		// of the IStream interface from which we will
		// read the synchronization state 
		//
  		zero.HighPart	= 0x00000000;
		zero.LowPart	= 0x00000000;
		zero.QuadPart	= 0x0000000000000000;  // Used on 64-bit machines

		//
		// Each SynchID in the vector m_vecSynchIDs must have
		// have a corresponding entry in the synchstate file.  
		//
		vector<LPSYNCHID>::iterator lppSynchIDs;
		for (lppSynchIDs = m_vecSynchIDs.begin(); 
			 lppSynchIDs != m_vecSynchIDs.end() && dwResult == ERROR_SUCCESS;
			 ++lppSynchIDs)
		{
			DWORD					dwNumBytesWritten;
			LP$$ROOT$$SYNCHRONIZER	lpICSSynchronizer;
			LPSTREAM				lpSynchState;
			LPSYNCHID				lpSynchID;
			STATSTG					sSynchStateStats;
			ULONG					ulStateSize;

			//ASSERT(lppSynchIDs != NULL);
			
			lpSynchID	= *lppSynchIDs;
			lpBuffer	= NULL;

			//
			// The GetSynchronizer() method finds the synchronizer object
			// that corresponds to lpSynchID->folderEID, and stores it
			// in lpICSSynchronizer
			//
			dwResult = GetSynchronizer(lpSynchID->ulFolderCb, 
					 				   lpSynchID->folderEID, 
									   &lpICSSynchronizer);
			if (dwResult == ERROR_SUCCESS)
			{
				//
				// Extract the synchronization state from this
				// C$$Root$$Synchronizer object.  We will be
				// read the synchstate to this IStream interface
				// and writing this data out to a file
				lpSynchState	= lpICSSynchronizer->SynchState();

				//
				// Save the state of the transacted IStream
				hResult = lpSynchState->Commit(STGC_DEFAULT);
				if (HR_FAILED(hResult))
				{
					dwResult = ERROR_INVALID_DATA;
				}
				else
				{
					//
					// Retrieve information about the synchstate
					hResult = lpSynchState->Stat(&sSynchStateStats, 
												 STATFLAG_DEFAULT);
					if (HR_FAILED(hResult))
					{
						dwResult = ERROR_INVALID_DATA;
					}
					else
					{	
						ulStateSize = sSynchStateStats.cbSize.LowPart;

						//
						// Now that we know the size of the synchstate data,
						// we can create a buffer large enough to hold it
						lpBuffer = new BYTE[ulStateSize + sizeof(ulStateSize)];
						if (lpBuffer == NULL)
						{
							dwResult = ERROR_NOT_ENOUGH_MEMORY;
						}
						else
						{
							CopyMemory(lpBuffer, (LPVOID)&ulStateSize, sizeof(ulStateSize));

							//
							// Set the synchstate's seek pointer to zero
							// in order to write the synchstate to the beginning
							// of the IStream interface
							hResult = lpSynchState->Seek(zero,
														 STREAM_SEEK_SET,
														 &nextSeek);
							if (HR_FAILED(hResult))
							{
								dwResult = ERROR_INVALID_DATA;
							}
							else
							{
								//
								// Read the synchstate from the IStream interface
								hResult = lpSynchState->Read((LPVOID)((LPBYTE)lpBuffer + sizeof(ulStateSize)), 
															 ulStateSize,
															 NULL);
								if (HR_FAILED(hResult))
								{
									dwResult = ERROR_INVALID_DATA;
								}
								else
								{
									//
									// Write the synchronization state out to a file
									bResult = WriteFile(hFile,
														lpBuffer,
														ulStateSize + sizeof(ulStateSize),
														&dwNumBytesWritten,
														NULL);
									if (!bResult)
									{
										dwResult = GetLastError();
									}
									else
									{

										// 
										// Revert the transacted stream to whatever
										// state it was in before we used it.  This
										// method always returns S_OK.
										lpSynchState->Revert();

										//
										// Deallocate the temporary buffer we used
										if (lpBuffer != NULL) 
										{
											delete[] lpBuffer;
											lpBuffer = NULL;
										}
									}
								}
							}
						}
					}
				}
			}
		} // for (lppSynchIDs = m_vecSynchIDs.begin(); lppSynchIDs != m_vecSynchIDs.end(); ++lppSynchIDs)
	}	

	//
	// Do cleanup
	//
	if (lpBuffer != NULL)
	{
		delete[] lpBuffer;
		lpBuffer = NULL;
	}

	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		CloseHandle(hFile);
		hFile = NULL;
	}

	//
	// Return a value to indicate success/failure
	// 
	return dwResult;
}
