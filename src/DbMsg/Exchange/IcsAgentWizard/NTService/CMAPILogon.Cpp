//========================================================================= 
// 
// Purpose: 
//    implementation of the CMAPILogon class 
// 
//========================================================================= 
 
 
#include "stdafx.h" 
#include <mapix.h>
#include <mapiutil.h>
#include <mapidefs.h>
#include "resource.h"

#include <initguid.h> 
#define USES_IID_IMAPIFolder 
#define USES_IID_IMsgStore 
#include <mapiguid.h> 

#include "CMAPILogon.h" 
  
const CHARcBackSlash='\\';  // backslash character 
 
#ifdef _DEBUG 
#define new DEBUG_NEW 
#undef THIS_FILE 
static char THIS_FILE[] = __FILE__; 
#endif 
 
 
 
//------------------------------------------------------------------------- 
// Purpose: 
//    Open a message store if we don't already have it open. 
// 
//
HRESULT CMAPILogon::OpenMsgStore(ULONG cbeid, 
								 LPENTRYID  peid, 
								 LPMDB * lppMDB) 
{ 
	HRESULT	hr = NOERROR; 
	ULONG fulIsSameStore = FALSE; 
	ULONG nStore = 0; 
	ULONG ii = 0; 
    
	if (peid && lppMDB)
	{
		for (ii = 0; ii < m_nMaxStores; ii++) 
		{ 
			if (m_pcbeidStore[ii]) 
			{ 
				// If we have a store already open, then simply return 
				hr = m_lpSession->CompareEntryIDs(cbeid, 
												  peid, 
												  m_pcbeidStore[ii], 
												  m_lppeidStore[ii], 
												  0L, 
												  &fulIsSameStore);  // fulIsSameStore == TRUE if match 

				if (SUCCEEDED(hr) && fulIsSameStore) 
				{  
					*lppMDB = m_lppMDB[ii]; 
					return hr; 
				} 
			} 
		} 
 
		//Find next available slot  
		BOOL bFound = FALSE; 
		for (ii = 0; ii < m_nMaxStores && !bFound; ii++) 
		{ 
			if (!m_pcbeidStore[ii]) 
			{ 
				nStore = ii; 
				bFound = TRUE; 
			} 
		} 
 
		if (nStore == m_nMaxStores) 
		{ 
			hr = E_FAIL; 
			return hr; 
		} 
 
		// Open the new one. 
		hr = m_lpSession->OpenMsgStore(NULL, 
									   cbeid, 
									   peid, 
									   &IID_IMsgStore, 
									   MDB_WRITE | MAPI_DEFERRED_ERRORS, 
									   &m_lppMDB[nStore]); 
		if (SUCCEEDED(hr)) 
		{ 
			// Save the entry of the one we just opened in case we get called later. 
			if (SUCCEEDED(hr = MAPIAllocateBuffer(cbeid, (LPVOID*)&m_lppeidStore[nStore]))) 
			{ 
				CopyMemory(m_lppeidStore[nStore], peid, cbeid); 
				m_pcbeidStore[nStore] = cbeid; 
          
			} 
		} 
    
		*lppMDB = m_lppMDB[nStore]; 
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr; 
} 

HRESULT CMAPILogon::InitializeProfileName()
{
	HRESULT			hResult;
	LPMAPITABLE		lpMAPITable = NULL;
	LPSRowSet		lpRows = NULL;

	hResult = m_lpSession->GetStatusTable(
		0L,
		&lpMAPITable
		);
	if (SUCCEEDED(hResult))
	{
		SizedSPropTagArray(2, tableProps) = 
		{
			2,
			{
				PR_DISPLAY_NAME,
				PR_RESOURCE_TYPE

			}
		};

		hResult = HrQueryAllRows(
			lpMAPITable,
			(LPSPropTagArray)&tableProps,
			NULL,
			NULL,
			0L,
			&lpRows
			);

		lpMAPITable->Release();

		if (SUCCEEDED(hResult))
		{
			for (ULONG ulIndex = 0; ulIndex < lpRows->cRows; ulIndex++)
			{
				SRow sRow = lpRows->aRow[ulIndex];
				LPTSTR lpszDisplayName;
				BOOL fIsMAPISubsystem;

				//
				// Check the properties in the current row to see if
				// the PR_RESOURCE_TYPE property is MAPI_SUBSYSTEM.  If it is,
				// we know that the PR_DISPLAY_NAME property in the same row
				// represents the profile name of the current session,  
				// (See: "Finding a Profile Name" in MSDN)
				// 
				for (ULONG ulPropsIndex = 0; ulPropsIndex < sRow.cValues; ulPropsIndex++)
				{
					if (sRow.lpProps[ulPropsIndex].ulPropTag == PR_RESOURCE_TYPE)
					{
						if (sRow.lpProps[ulPropsIndex].Value.ul == MAPI_SUBSYSTEM)
						{
							fIsMAPISubsystem = TRUE;
						}
						else
						{
							fIsMAPISubsystem = FALSE;
						}
					}
					else if (sRow.lpProps[ulPropsIndex].ulPropTag == PR_DISPLAY_NAME)
					{
						lpszDisplayName = sRow.lpProps[0].Value.lpszA;
					}
					else
					{
						return E_UNEXPECTED;
					}
				} // for (ULONG ulPropsIndex = 0; ulPropsIndex < sRow.cValues; ulPropsIndex++)

				//
				// See if the PR_RESOURCE_TYPE for this row was MAPI subsystem.
				// If it was, assign the member variable representing the profile
				// name of the session to be the value of the PR_DISPLAY_NAME property
				// in this row.
				// 
				if (fIsMAPISubsystem)
				{
					m_lpszProfileName = lpszDisplayName;
				}
			} // for (ULONG ulIndex = 0; ulIndex < lpRows->cRows; ulIndex++)
		}
	}

	if (FAILED(hResult))
	{
		m_lpszProfileName = NULL;
	}

	return hResult;
}
 
 
//------------------------------------------------------------------------- 
// Purpose: 
//    Logoff of the open message store and release it. 
// 

void CMAPILogon::LogoffMessageStore(VOID) 
{ 
	for(ULONG ii = 0; ii < m_nMaxStores; ii++) 
	{ 
		HRESULT hr = NOERROR; 
		if (m_lppMDB[ii]) 
		{ 
			ULONG ulFlags = LOGOFF_ORDERLY; 

			m_lppMDB[ii]->StoreLogoff(&ulFlags);
			m_lppMDB[ii]->Release(); 
			m_lppMDB[ii]       = NULL; 
			m_pcbeidStore[ii]  = 0; 
			MAPIFreeBuffer(m_lppeidStore[ii]); 
			m_lppeidStore[ii]  = NULL; 
		} 
	} 
} 
 
 
     
HRESULT CMAPILogon::HrInitialize(HWND hWnd) 
{ 
	HRESULT		hr = NOERROR; 
	LPMAPITABLE pTable = NULL; 
	LPSRowSet	pRows = NULL; 
	ULONG		ii = 0; 
 
	// Initialize MAPI. 
    hr = MAPIInitialize( NULL); 
    if(FAILED( hr)) 
		goto cleanup; 
     
    m_fMAPIInitialized = TRUE; 
 
	// Open session  
    hr = MAPILogonEx((ULONG)hWnd,		// UI flags, 
					 NULL,				// profile name 
					 NULL,              // password 
					 MAPI_NEW_SESSION | MAPI_LOGON_UI | MAPI_ALLOW_OTHERS,            // MAPI flags 
					 &m_lpSession); 
 
 
	if FAILED(hr) 
	{ 
		goto cleanup; 
	} 
 
   
	// Open the address book and get the user entryid. 
	hr = m_lpSession->OpenAddressBook(0, NULL, AB_NO_DIALOG, &m_lpAdrBook); 
 
	if (FAILED(hr)) 
	{ 
		goto cleanup; 
	} 
 
	//Get the number of stores in available session 
	if(SUCCEEDED( hr = m_lpSession->GetMsgStoresTable (0, &pTable))) 
	{ 
        hr = HrQueryAllRows (pTable, 
                             NULL, 
                             NULL, 
                             NULL, 
                             0, 
                             &pRows); 
 
		m_nMaxStores = pRows->cRows;
		
		pTable->Release();
	} 
 
	// Allocate all the store handles and entryids 
	hr = MAPIAllocateBuffer(pRows->cRows * sizeof(LPMDB), (LPVOID *)&m_lppMDB); 
	if (FAILED(hr)) 
	{ 
		goto cleanup; 
	} 
 
 
	hr = MAPIAllocateBuffer(pRows->cRows * sizeof(ULONG), (LPVOID *)&m_pcbeidStore); 
	if (FAILED(hr)) 
	{ 
		goto cleanup; 
	} 
 
	hr = MAPIAllocateBuffer(pRows->cRows * sizeof(LPENTRYID), (LPVOID *)&m_lppeidStore); 
	if (FAILED(hr)) 
	{ 
		goto cleanup; 
	} 
 
	for (ii = 0; ii < m_nMaxStores; ii++) 
	{ 
		m_lppMDB[ii]  = NULL; 
		m_pcbeidStore[ii] = 0; 
		m_lppeidStore[ii] = NULL; 
	} 

	hr = InitializeProfileName();
	if (FAILED(hr))
	{
		goto cleanup;
	}

	cleanup: 
	if (FAILED(hr)) 
		HrUninitialize(); 


	return hr; 
 
} 
 
 
HRESULT CMAPILogon::HrUninitialize() 
{ 
	HRESULT hr = NOERROR; 
 
	if (m_lpAdrBook) 
		m_lpAdrBook->Release(); 
 
	if (m_lpSession) 
	{ 
		LogoffMessageStore(); 
		hr = m_lpSession->Logoff(0, 0, 0); 
		m_lpSession->Release(); 
	} 

	if (m_lppMDB)
		MAPIFreeBuffer(m_lppMDB);

	if (m_pcbeidStore)
		MAPIFreeBuffer(m_pcbeidStore);

	if (m_lppeidStore)
		MAPIFreeBuffer(m_lppeidStore);
 
	if( m_fMAPIInitialized ) 
		MAPIUninitialize(); 

	m_pcbeidStore= NULL;  
	m_lppeidStore= NULL; 
	m_lppMDB= NULL; 
	
	m_fMAPIInitialized = FALSE;
	
	return hr; 
} 
 
  
CMAPILogon::CMAPILogon()
{ 
	m_lpSession= NULL; 
	m_lpAdrBook= NULL; 
	m_fMAPIInitialized= FALSE; 
	m_lpTempFld= NULL; 
 
	m_nMaxStores= 5; 
	m_pcbeidStore= NULL;  
	m_lppeidStore= NULL; 
	m_lppMDB= NULL;      
 
 
	m_szFile= TEXT(""); 
	m_szFileTitle = TEXT(""); 
	m_psTitle= TEXT(""); 
	m_psAuthor= TEXT(""); 
	m_psComments= TEXT(""); 
	m_psKeywords= TEXT(""); 
	m_psSubject= TEXT(""); 
	m_psTitle= TEXT(""); 
  
} 
 
CMAPILogon::~CMAPILogon()
{ 
	m_szFile.Empty(); 
	m_szFileTitle.Empty(); 
	m_psAuthor.Empty();  
	m_psComments.Empty(); 
	m_psKeywords.Empty(); 
	m_psSubject.Empty();  
	m_psTitle.Empty();   
} 
 
 
 


  
