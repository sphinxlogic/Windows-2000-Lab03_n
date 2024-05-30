//=========================================================================
// PostData.CPP
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
// 
//
// Purpose:
//    implementation of the CPostData class
//
//=========================================================================


#include "stdafx.h"
#include "PostSmpl.h"
#include "PostData.h"
#include "fldpick.h"
#include "freedoc.h"


CPostData	PostData;


const CHAR	cBackSlash		=	'\\';			// backslash character

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



 //-------------------------------------------------------------------------
// Purpose:
//    Open a message store if we don't already have it open.
//
//static
HRESULT CPostData::OpenMsgStore
   (
   ULONG      cbeid,
   LPENTRYID  peid,
   LPMDB	  *lppMDB
   )
{
   HRESULT  hr             = NOERROR;
   ULONG    fulIsSameStore = FALSE;
   ULONG	nStore		   = 0;
   ULONG	ii			   = 0;
   
   for (ii = 0; ii < nMaxStores; ii++)
   {
   		if (m_pcbeidStore[ii])
		{
			// If we have a store already open, then simply return
			hr = m_lpSession->CompareEntryIDs(cbeid,
				                       peid,
					                   m_pcbeidStore[ii],
						               m_lppeidStore[ii],
							           0,
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
    for (ii = 0; ii < nMaxStores & !bFound; ii++)
	{
		if (!m_pcbeidStore[ii])
		{
			nStore = ii;
			bFound = TRUE;
		}
	}

	if (nStore == nMaxStores)
	{
		hr = E_FAIL;
		return hr;
	}

   // Open the new one.
   hr = m_lpSession->OpenMsgStore(NULL,
                             cbeid,
                             peid,
                             &IID_IMsgStore,
                             MDB_WRITE | MAPI_DEFERRED_ERRORS | MDB_NO_DIALOG,
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
   return hr;
}


//-------------------------------------------------------------------------
// Purpose:
//    Logoff of the open message store and release it.
//
//static
void CPostData::LogoffMessageStore(VOID)
{
	for( ULONG ii = 0; ii < nMaxStores; ii++)
	{
		HRESULT hr = NOERROR;
		if (m_lppMDB[ii])
		{
			ULONG ulFlags = LOGOFF_ORDERLY;
			if (FAILED(hr = m_lppMDB[ii]->StoreLogoff(&ulFlags)))
			{       
				#ifdef _DEBUG
				afxDump << TEXT("LogoffMessageStore:StoreLogoff failed");
				#endif
			}

			m_lppMDB[ii]->Release();
			m_lppMDB[ii]       = NULL;
			m_pcbeidStore[ii]  = 0;
			MAPIFreeBuffer(m_lppeidStore[ii]);
			m_lppeidStore[ii]  = NULL;
		}
	}
}


					    
HRESULT CPostData::HrInitialize()
{
	HRESULT hr		   = NOERROR;
	LPMAPITABLE pTable = NULL;
    LPSRowSet	pRows  = NULL;
	ULONG			ii	   = 0;


	// Initialize MAPI.
    hr = MAPIInitialize( NULL);
    if( FAILED( hr))
        goto cleanup;
    
    fMAPIInitialized = TRUE;

	// Open session 
    hr = MAPILogonEx(NULL,// UI flags,
                NULL,    // profile name
                NULL,               // password
                MAPI_NEW_SESSION | MAPI_LOGON_UI | MAPI_ALLOW_OTHERS,            // MAPI flags
                &m_lpSession);
	

	if FAILED(hr)
	{
		#ifdef _DEBUG
		afxDump << TEXT("HrInitialize:MAPILogonEx failed");
		#endif
		goto cleanup;
	}
	
  
	// Open the address book and get the user entryid.
	hr = m_lpSession->OpenAddressBook(0, NULL, AB_NO_DIALOG, &m_lpAdrBook);

	if (FAILED(hr))
	{
		#ifdef _DEBUG
		afxDump << TEXT("HrInitialize:OpenAddressBook failed");
		#endif
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
		
		nMaxStores = pRows->cRows;
	}
	
	// Allocate all the store handles and entryids
	hr = MAPIAllocateBuffer(pRows->cRows * sizeof(LPMDB), (LPVOID *)&m_lppMDB);
	if (FAILED(hr))
	{
		#ifdef _DEBUG
		afxDump << TEXT("HrInitialize:MAPIAllocateBuffer failed");
		#endif
		goto cleanup;
	}
	

	hr = MAPIAllocateBuffer(pRows->cRows * sizeof(ULONG), (LPVOID *)&m_pcbeidStore);
	if (FAILED(hr))
	{
		#ifdef _DEBUG
		afxDump << TEXT("HrInitialize:MAPIAllocateBuffer failed");
		#endif
		goto cleanup;
	}

	hr = MAPIAllocateBuffer(pRows->cRows * sizeof(LPENTRYID), (LPVOID *)&m_lppeidStore);
	if (FAILED(hr))
	{
		#ifdef _DEBUG
		afxDump << TEXT("HrInitialize:MAPIAllocateBuffer failed");
		#endif
		goto cleanup;
	}

	for (ii = 0; ii < nMaxStores; ii++)
	{
		m_lppMDB[ii]	  = NULL;
		m_pcbeidStore[ii] = 0;
		m_lppeidStore[ii] = NULL;
	}

	if ( !CreateImageListExchange() )
	{
		#ifdef _DEBUG
		afxDump << TEXT("HrInitialize:CreateImageListExchange failed");
		#endif
		goto cleanup;
	}
	

cleanup:
	if (FAILED(hr))
		HrUninitialize();

	return hr;

}


HRESULT CPostData::HrUninitialize()
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

	if( fMAPIInitialized )
		MAPIUninitialize();

	m_obImageListExchange.DeleteImageList();

	return hr;
}


/////////////////////////////////////////////////////////////////////////////
// CPostData

CPostData::CPostData()
{
	m_lpSession		= NULL;
	m_lpAdrBook		= NULL;
	fMAPIInitialized= FALSE;
	m_lpTempFld		= NULL;
	
	nMaxStores		= 5;
	m_pcbeidStore	= NULL; 
	m_lppeidStore	= NULL;
	m_lppMDB		= NULL;	     


	szFile		= TEXT("");
	szFileTitle = TEXT("");
	m_psTitle	= TEXT("");
	m_psAuthor	= TEXT("");
	m_psComments= TEXT("");
	m_psKeywords= TEXT("");
	m_psSubject	= TEXT("");
	m_psTitle	= TEXT("");
 
}

CPostData::~CPostData()
{
	szFile.Empty();
	szFileTitle.Empty();
	m_psAuthor.Empty(); 
	m_psComments.Empty();
	m_psKeywords.Empty();
	m_psSubject.Empty(); 
	m_psTitle.Empty();  
}



//-------------------------------------------------------------------------
// Purpose:
//    Create our global image list used to draw mail items.
//
// 
BOOL CPostData::CreateImageListExchange(VOID)
{
   BOOL  fRet = FALSE;

   static struct SImageListInfo
		  {
			UINT  nIdIcon;
	      } aImageListInfo[cimlExchange] = { ICO_Exchange,
											 ICO_Exchange,
											 ICO_Mdb,
											 ICO_MdbOpen,
											 ICO_Folder,
											 ICO_FolderOpen,
											 ICO_DefaultMdb,
											 ICO_DefaultMdbOpen,
										   };

   if (m_obImageListExchange.Create(cxSmallIcon, cySmallIcon, TRUE, cimlExchange, 1))
   {
		UINT ii		= 0;
		HICON hicon = NULL;
	
		for (ii = 0; ii < cimlExchange; ii++)
		{
         	hicon = theApp.LoadIcon(MAKEINTRESOURCE(aImageListInfo[ii].nIdIcon));
			if (hicon)
			{
				if (-1 == m_obImageListExchange.Add(hicon))
		            break;
            }
        }

		fRet = (cimlExchange == ii);
      }

   return fRet;
}


BOOL CPostData::FilePost(LPSTORAGE pstg)
{
	BOOL fRet  = FALSE;
	HRESULT hr = NOERROR;
	CFolderPicker  FilePostDlg;
	CString szTitle;
	CString szSubject;
	CString szAuthor;
	CString szKeywords;
	CString szComments;

	fRet = (FilePostDlg.DoModal() == IDOK);

	if (!fRet)
		goto cleanup;
   
	if (m_lpTempFld == NULL)
	{
		fRet = FALSE;
		goto cleanup;
	}
	

	GetSummaryInfo(pstg, &szTitle, &szSubject, &szAuthor, &szKeywords, &szComments);
	
	// Create the free doc
	hr = ScCreateFreeDoc( 	pstg,
							m_lpTempFld,
                           (LPSTR)(LPCSTR)szFile,
						   (LPSTR)(LPCSTR)szFileTitle,
                           (LPSTR)(LPCSTR)szTitle,
		                   (LPSTR)(LPCSTR)szSubject,
                           (LPSTR)(LPCSTR)szAuthor,
                           (LPSTR)(LPCSTR)szKeywords,
                           (LPSTR)(LPCSTR)szComments);
	if (FAILED(hr))
	{
		#ifdef _DEBUG
		afxDump << TEXT("Post Doc failed");
		#endif
		fRet = FALSE;
		goto cleanup;
	}

cleanup:
	if (m_lpTempFld)
	{
		m_lpTempFld->Release();
		m_lpTempFld = NULL;
	}
  	return fRet;
}



void CPostData::CreateAndPostMessage()
{
	HRESULT				hResult			= NOERROR;
	SCODE				sCode			= S_OK;
	LPMESSAGE			pMessage		= NULL;
	FLAGS				fCreateMessageFlags		= 0L;
	LPSPropValue		pMessagePropValues		= NULL;
	ULONG				cbSenderEntryIDSize		= 0;
	LPENTRYID			pSenderEntryID	= NULL;
	ULONG				uObjectType		= 0;
	ULONG				uCount			= 0;
	LPMAPIPROP			pSender			= NULL;
	static SizedSPropTagArray(1, aSenderProps) = {1L, PR_DISPLAY_NAME};
	LPSPropValue		pSenderProps	= NULL;
	BOOL				fRet			= FALSE;
	UINT				c				= 0;
	UINT				uSize			= 20;
	
	CFolderPicker  FilePostDlg;
    fRet = (FilePostDlg.DoModal() == IDOK);

	if (!fRet) 
		goto cleanup;

   if (m_lpTempFld == NULL)
		goto cleanup;

	//	Recover sender information
	hResult = m_lpSession->QueryIdentity(&cbSenderEntryIDSize,&pSenderEntryID);

	if (HR_FAILED(hResult))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): QueryIdentiry failed");
		#endif
		goto cleanup;
	}

	hResult = m_lpSession->OpenEntry(cbSenderEntryIDSize,
												pSenderEntryID,
												NULL,
												MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS,
												&uObjectType,
												(LPUNKNOWN FAR *)&pSender);

   	if (HR_FAILED(hResult))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): OpenEntry failed");
		#endif
		goto cleanup;
	}

	hResult = pSender->GetProps((LPSPropTagArray)&aSenderProps,
								0,
								&uCount,
								&pSenderProps);
	
	if (FAILED(hResult))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): GetProps failed");
		#endif
		goto cleanup;
	}

	_ASSERT(pSenderProps[0].ulPropTag == PR_DISPLAY_NAME);

	//	Create a message in the folder.
	hResult = m_lpTempFld->CreateMessage(NULL,fCreateMessageFlags,&pMessage);
	
	if (HR_FAILED(hResult))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): CreateMessage failed");
		#endif
		goto cleanup;
	}

	//	Grab memory for a message property array
	sCode = MAPIAllocateBuffer(uSize * sizeof(SPropValue),(void **)&pMessagePropValues);
	
	if (FAILED(sCode))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): MAPIAllocateBuffer failed");
		#endif
		goto cleanup;
	}

	//	Set some properties on the message.
	pMessagePropValues[c  ].ulPropTag = PR_MESSAGE_CLASS;
	pMessagePropValues[c++].Value.lpszA = "IPM.POST";

	pMessagePropValues[c  ].ulPropTag = PR_SUBJECT;
	pMessagePropValues[c++].Value.lpszA = "";

	////////////////////////////////////////////////////////////////
	// This property PR_BODY needs to be set with approriate text.
	// PR_BODY property holds the message body text.
	// Here it is modified with edit box text.
	/////////////////////////////////////////////////////////////////
	
	pMessagePropValues[c  ].ulPropTag = PR_BODY;
	pMessagePropValues[c++].Value.lpszA = (LPSTR)(LPCSTR)theApp.m_lpBuffer;

	pMessagePropValues[c  ].ulPropTag = PR_SENDER_ENTRYID;
	pMessagePropValues[c  ].Value.bin.cb = cbSenderEntryIDSize;
	pMessagePropValues[c++].Value.bin.lpb = (LPBYTE)pSenderEntryID;

	pMessagePropValues[c  ].ulPropTag = PR_SENDER_NAME;
	pMessagePropValues[c++].Value.lpszA = pSenderProps[0].Value.lpszA;

	pMessagePropValues[c  ].ulPropTag = PR_SENT_REPRESENTING_ENTRYID;
	pMessagePropValues[c  ].Value.bin.cb = cbSenderEntryIDSize;
	pMessagePropValues[c++].Value.bin.lpb = (LPBYTE)pSenderEntryID;

	pMessagePropValues[c  ].ulPropTag = PR_SENT_REPRESENTING_NAME;
	pMessagePropValues[c++].Value.lpszA = pSenderProps[0].Value.lpszA;

	pMessagePropValues[c  ].ulPropTag = PR_DELETE_AFTER_SUBMIT;
	pMessagePropValues[c++].Value.b = 0;

	pMessagePropValues[c  ].ulPropTag = PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED;
	pMessagePropValues[c++].Value.b = 0;

	pMessagePropValues[c  ].ulPropTag = PR_READ_RECEIPT_REQUESTED;
	pMessagePropValues[c++].Value.b = 0;

	pMessagePropValues[c  ].ulPropTag = PR_PRIORITY;
	pMessagePropValues[c++].Value.ul = PRIO_NORMAL;

	//	Test that the property array has not been overrun
	_ASSERT(c <= uSize);
	
	//	Write message properties.
	hResult = pMessage->SetProps(c,pMessagePropValues,NULL);
	if (HR_FAILED(hResult))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): SetProps failed");
		#endif
		goto cleanup;
	}

	//	Clear the read flag.  This operation requires a
	//	separate MAPI call.
	pMessage->SetReadFlag(CLEAR_READ_FLAG);

	//	Save changes made to the message
	hResult = pMessage->SaveChanges(FORCE_SAVE);
	if (HR_FAILED(hResult))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateAndPostMessage(): SaveChanges failed");
		#endif

		goto cleanup;
	}

cleanup:
	//	Release MAPI objects
	if (pMessage)
		pMessage->Release();
	if (pSender)
		pSender->Release();

	//	Free memory allocations
	if (m_lpTempFld)
		m_lpTempFld->Release();
	
	MAPIFreeBuffer(pMessagePropValues);
	MAPIFreeBuffer(pSenderEntryID);
	MAPIFreeBuffer(pSenderProps);
}



BEGIN_MESSAGE_MAP(CPostData, CWnd)
	//{{AFX_MSG_MAP(CPostData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPostData message handlers
