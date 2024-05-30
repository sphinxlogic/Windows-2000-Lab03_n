/************************************************************************
*                                                                       *
*   $$Root$$Synchronizer.cpp										*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#include "StdAfx.h"
#include "$$Root$$Synchronizer.h"
#include "$$Root$$Table.h"
#include "$$Root$$Agent.h"

C$$Root$$Synchronizer::C$$Root$$Synchronizer(LPMDB lpStore,
											 ULONG ulCb,
											 LPENTRYID lpEntryID,
											 LP$$ROOT$$TABLE lpICSTable)
{
	m_lpStore			= lpStore;
	m_ulCb				= ulCb;
	m_lpEntryID			= lpEntryID;
	m_lpICSTable		= lpICSTable;

	m_hMemBlock			= NULL;
	m_lpFolder			= NULL;
	m_lpSynchronizer	= NULL;
	m_lpSynchState		= NULL;
	m_lpszFolderName	= NULL;

	m_fIsInitialized	= FALSE;
	
}

HRESULT C$$Root$$Synchronizer::RefreshState()
{
	HRESULT		hResult;
	ULONG		ulSynchType;

	//
	// The RefreshState method needs to re-acquire the 
	// synchronizer property from the Exchange server.
	// We must first determine the type of synchronizer
	// which we need:
	if (m_lpICSTable->CollectorType() == CONTENT_COLLECTOR)
	{
		ulSynchType = PR_CONTENTS_SYNCHRONIZER;
	}
	else
	{
		ulSynchType = PR_HIERARCHY_SYNCHRONIZER;
	}

	if (m_lpFolder == NULL)
	{
		hResult = E_POINTER;
	}
	else
	{
		hResult = m_lpFolder->OpenProperty(
			ulSynchType,
			&__IID_IExchangeExportChanges,
			0,
			0,
			(LPUNKNOWN FAR *)&m_lpSynchronizer
			);
		if (SUCCEEDED(hResult))
		{
			SizedSPropTagArray(2,rgSynchronizerProps) =
			{
				2,
				{
					PR_ENTRYID,
					PR_MESSAGE_SIZE
				}
			};

			hResult = m_lpSynchronizer->Config(
				m_lpSynchState,
				SYNC_NORMAL | SYNC_READ_STATE,
				m_lpICSTable->Collector(),
				NULL,
				(LPSPropTagArray)&rgSynchronizerProps,
				NULL,
				0
				);
		}
	}

	//
	// Return a value to indicate success/failure
	//
	return hResult;
}

//
// Opens the folder corresponding to this C$$Root$$Synchronizer's
// ENTRYID, and extracts the PR_*_SYNCHRONIZER property from it
//
HRESULT C$$Root$$Synchronizer::Initialize()
{
	HRESULT		hResult;
	LPUNKNOWN	lpUnknown = NULL;
	TCHAR		str[256];
	ULONG		ulObjType;
	ULONG		ulSynchProperty;

	//
	// Open the folder with the specified ENTRYID.
	// Note that according to MSDN, IMAPIContainer::OpenEntry is faster
	//

	if (m_lpStore == NULL)
	{
		hResult = E_POINTER;
	}
	else
	{
		hResult = m_lpStore->OpenEntry(
			m_ulCb,
			m_lpEntryID,
			&IID_IMAPIFolder,
			MAPI_BEST_ACCESS,
			&ulObjType,
			&lpUnknown);
		if (SUCCEEDED(hResult))
		{
			//ASSERT(lpUnknown != NULL);

			m_lpFolder = (LPMAPIFOLDER)lpUnknown;		

			//
			// Extract some information about the folder we opened
			//
			SizedSPropTagArray(1,fldrProps) =
			{
				1,
				{
					PR_DISPLAY_NAME
				}
			};
					
			ULONG			uValuesCount;
			LPSPropValue	lpProps;

			hResult = m_lpFolder->GetProps(
				 (LPSPropTagArray)&fldrProps,
				 0,
				 &uValuesCount,
				 &lpProps
			);
			if (SUCCEEDED(hResult))
			{
			
				// MUST MAKE UNICODE GENERIC
				m_lpszFolderName = lpProps[0].Value.lpszA;

				//
				// Display information about the newly opened folder
				//
				_stprintf(str, "Opened folder: %s\0", m_lpszFolderName);
				StatusMessage(str);
			
				//
				//	Create a memory blob with an IStream interface
				//

				m_lpSynchState = NULL;
				m_hMemBlock = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, 0);

				if (m_hMemBlock)
				{
					hResult = CreateStreamOnHGlobal(
													m_hMemBlock,
													TRUE,  
													&m_lpSynchState);
					if (SUCCEEDED(hResult))
					{
						//
						// Create a synchronizer object
						//
								
						// Determine which type of synchronizer the collector requires
						if (m_lpICSTable->CollectorType() == CONTENT_COLLECTOR)
						{
							ulSynchProperty = PR_CONTENTS_SYNCHRONIZER;
						}
						else if (m_lpICSTable->CollectorType() == HIERARCHY_COLLECTOR)
						{
							ulSynchProperty = PR_HIERARCHY_SYNCHRONIZER;
						}
						else
						{
							hResult = E_FAIL;
						}
						
						if (SUCCEEDED(hResult))
						{
							m_lpSynchronizer = NULL;

							hResult = m_lpFolder->OpenProperty(
															ulSynchProperty,
															&__IID_IExchangeExportChanges,
															0,
															0,
															(LPUNKNOWN FAR *)&m_lpSynchronizer);
							if (SUCCEEDED(hResult))
							{
								//
								//	Configure synchronizer.
								//

								SizedSPropTagArray(2,rgSynchronizerProps) =
								{
									2,
									{
										PR_ENTRYID,
										PR_MESSAGE_SIZE
									}
								};

								hResult = m_lpSynchronizer->Config(
																m_lpSynchState,
																SYNC_NORMAL | SYNC_READ_STATE,
																m_lpICSTable->Collector(),
																NULL,
																(LPSPropTagArray)&rgSynchronizerProps,
																NULL,
																0);
							}
						}
					}
				}
				else
				{
					hResult = E_OUTOFMEMORY;
				}
			}
		}
	}

	//
	// Perform cleanup: (incomplete)
	//
	if (SUCCEEDED(hResult))
	{
		m_fIsInitialized = TRUE;
	}

	return hResult;
}

HRESULT C$$Root$$Synchronizer::Synchronize()
{
	HRESULT hResult;
	ULONG ulProgress;
	ULONG ulSteps;

	m_lpICSTable->SetCurrentSynchronizer(this);

	hResult = this->RefreshState();
	if (HR_SUCCEEDED(hResult))
	{		
		//
		// The actual synchronization
		//	
		do
		{
			hResult = m_lpSynchronizer->Synchronize(&ulSteps,&ulProgress);
		}
		while (hResult == SYNC_W_PROGRESS);

		if (HR_SUCCEEDED(hResult))
			m_lpSynchronizer->UpdateState(m_lpSynchState);
	}

	if (m_lpSynchronizer != NULL)
	{
		//m_lpSynchronizer was got in this->RefreshState()
		m_lpSynchronizer->Release();
		m_lpSynchronizer = NULL;	
	}

	return hResult;
}

C$$Root$$Synchronizer::~C$$Root$$Synchronizer()
{
	if ( m_lpSynchronizer != NULL )
	{
		m_lpSynchronizer->Release();
		m_lpSynchronizer = NULL;
	}

	//
	//	Release the IStream object, save state first
	//

	if (m_lpSynchState != NULL)
	{
		m_lpSynchState->Release();
		m_lpSynchState = NULL;
	}

	if (m_hMemBlock != NULL)
	{
		GlobalFree(m_hMemBlock);
		m_hMemBlock = NULL;
	}

	//
	//	Release the folder object.
	//

	if (m_lpFolder != NULL)
	{
		m_lpFolder->Release();
		m_lpFolder = NULL;
	}
}

HRESULT C$$Root$$Synchronizer::equals(ULONG ulCb,
									LPENTRYID lpEntryID,
									ULONG FAR * lpulResult)
{
	HRESULT hResult;

	ULONG cbEntryID1		= ulCb;
	LPENTRYID lpEntryID1	= lpEntryID;
	ULONG cbEntryID2		= m_ulCb;
	LPENTRYID lpEntryID2	= m_lpEntryID;
	ULONG ulFlags			= 0L;

	if (lpulResult)
	{
		hResult = m_lpStore->CompareEntryIDs(cbEntryID1,
				 							 lpEntryID1,
											 cbEntryID2,
											 lpEntryID2,
											 ulFlags,
											 lpulResult);
	}
	else
	{
		hResult = E_INVALIDARG;
	}

	return hResult;
}

HRESULT C$$Root$$Synchronizer::equals(C$$Root$$Synchronizer * icsSynchronizer, 
									  ULONG FAR * lpulResult)
{
	HRESULT hResult;

	if (icsSynchronizer && lpulResult)
	{
		hResult = this->equals(icsSynchronizer->EntryIDCb(),
						icsSynchronizer->EntryID(),
						lpulResult);
	}
	else
	{
		hResult = E_INVALIDARG;
	}

	return hResult;
}

C$$Root$$Synchronizer::operator string()
{
	const nRadix = 10;
	string strSynch = _TEXT("");
	TCHAR szTemp[33]; // Max size of string returned by ultoa()
	LPTSTR lpszTemp = NULL;
	
	//
	// The name of the folder stored in this C$$Root$$Synchronizer object
	//

	strSynch += _TEXT("\nFolder Name: ");
	strSynch += m_lpszFolderName;
	
	//
	// The number of bytes in the ENTRYID of this folder
	//

	strSynch += _TEXT("\nCb: ");
	_ultot(m_ulCb, szTemp, nRadix);  
	strSynch += szTemp;

	//
	// The ASCII output of the ENTRYID of this folder
	//
	
	HrSzFromEntryID(m_ulCb,
					m_lpEntryID,
					&lpszTemp);

	strSynch += _TEXT("\nASCII output of eid: ");
	strSynch += lpszTemp;

	//
	// Return the LPTSTR representing this C$$Root$$Synchronizer
	//

	return strSynch;
}
