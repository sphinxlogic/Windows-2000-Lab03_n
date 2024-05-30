// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICSAgentNTService.h"
#include "cstm1dlg.h"
#include "ICSAgentNTServiceaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const GUID IID_IExchangeExportChanges = {0xa3ea9cc0,0xd1b2,0x11cd,0x80,0xfc,0x00,0xaa,0x00,0x4b,0xba,0x0b};


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	//}}AFX_DATA_INIT
	
	// Add extra initialization here 

	m_fIsInitialized = FALSE;
	m_lpszRootFolderName = "Microsoft Exchange";
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Control(pDX, IDC_EXCHANGE_TREE, m_TreeCtrl);
	//}}AFX_DATA_MAP
}


// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.

BOOL CCustom1Dlg::OnDismiss()
{
	CString cstrFolderdataFileName;
	HRESULT hResult;

	if (!UpdateData(TRUE))
		return FALSE;

	//  The dialog should not be dismissed if MAPI is not initialized
	if (!m_fIsInitialized)
		return FALSE;

	MakeList(m_TreeCtrl.GetChildItem(m_TreeCtrl.GetRootItem()));

	//
	// The file to which we will save the folder IDs
	cstrFolderdataFileName = "FOLDER_EIDS.sav";

	
	//
	// Create a file handle for the file to which we
	// will save the selected folder IDs.
	//
	HANDLE hFile = CreateFile(cstrFolderdataFileName, 
	 						  GENERIC_WRITE,
							  0,
							  NULL,
							  CREATE_ALWAYS,
							  FILE_ATTRIBUTE_NORMAL,
							  NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		CString err;
		err.Format("Error creating file: %s", cstrFolderdataFileName);
		MessageBox(err);
		return FALSE;
	}

	int iNumFolders = 0;

	vector<SMailID *>::iterator pMailIDs;

	for (pMailIDs = myList.begin(); pMailIDs != myList.end(); ++pMailIDs, iNumFolders++)
	{
		// Extract the SMailID structure.  It 
		// must be passed into the OpenFolder()
		// method, allowing us to get an IMAPIFolder
		// corresponding to this HTREEITEM
		SMailID * pMailID = *pMailIDs; 

		//
		// Extract an IMAPIFolder object
		//
		LPMAPIFOLDER lpMAPIFolder = NULL;
		hResult = OpenFolder(pMailID, &lpMAPIFolder);
		if (FAILED(hResult))
		{
			MessageBox("Could not open folder");
			iNumFolders--;
			continue;
		}

		//
		// Extract the entry ID of the store in which this
		// folder exists
		//
		SizedSPropTagArray(3,StoreProps) =
		{
			3,
			{
				PR_ENTRYID,
				PR_STORE_ENTRYID,
				PR_DISPLAY_NAME
			}
		};

		ULONG			uValuesCount;
		LPSPropValue	lpProps;

		// We want the store in which the selected folder resides
		hResult = lpMAPIFolder->GetProps(
			 (LPSPropTagArray)&StoreProps,
			 0,
			 &uValuesCount,
			 &lpProps
		);
		if (FAILED(hResult))
		{
			CString cstrErr;
			cstrErr.Format("Could not get properties of folder: %s", pMailID->lpszDisplayName);
			cstrErr += "\nEither the exchange server servicing this folder is down, or";
			cstrErr += "\nthe public folder has not been replicated to your site.";
			cstrErr += "\nSee your administrator.";
			MessageBox(cstrErr);
			iNumFolders--;
			continue;		// Do not write this folder to the file
		}

		ASSERT(uValuesCount == 3);
		ASSERT(lpProps[0].ulPropTag == PR_ENTRYID);
		ASSERT(lpProps[1].ulPropTag == PR_STORE_ENTRYID);
		ASSERT(lpProps[2].ulPropTag == PR_DISPLAY_NAME);

		if (!HasSynchronizer(lpMAPIFolder))
		{
			CString cstrErr;
			cstrErr = "A synchronizer property could not be extracted for the folder:\n\n";
			cstrErr += lpProps[2].Value.lpszA;
			cstrErr += "\n\nThe generate ICS agent will not synchronize this folder.";
			MessageBox(cstrErr);
			iNumFolders--;
			continue;
		}

		LPENTRYID lpFolderEid = (LPENTRYID)(lpProps[0].Value.bin.lpb);
		ULONG ulFolderCb = lpProps[0].Value.bin.cb;
		LPENTRYID lpStoreEid = (LPENTRYID)(lpProps[1].Value.bin.lpb);
		ULONG ulStoreCb = lpProps[1].Value.bin.cb;
		
		//
		// Add the folder CB to the macro list
		// 
		CString cstrFolderCb;
		cstrFolderCb.Format("FOLDER_CB_%d", iNumFolders);
		DefineIntMacro(cstrFolderCb, ulFolderCb);

		//
		// Add the store CB to the macro list
		//
		CString cstrStoreCb;
		cstrStoreCb.Format("STORE_CB_%d", iNumFolders);
		DefineIntMacro(cstrStoreCb, ulStoreCb);

		//
		// Variables to store the data we wish to write to the file
		// 
		
		DWORD numBytesWritten;
		LPCVOID lppBuffer[6]; 
		DWORD lpNumBytesToWrite[6];
		
		//
		// Gather the data which we will write to a file
		// 

		//
		// Data for the FOLDER
		//
		lppBuffer[0] = &ulFolderCb;
		lppBuffer[1] = lpFolderEid->abFlags;
		lppBuffer[2] = lpFolderEid->ab;
		
		//
		// Data for the associated store
		//
		lppBuffer[3] = &ulStoreCb;
		lppBuffer[4] = lpStoreEid->abFlags;
		lppBuffer[5] = lpStoreEid->ab;
		
		//
		// Sizes of the folder data
		//
		lpNumBytesToWrite[0] = sizeof(ULONG);
		lpNumBytesToWrite[1] = sizeof(BYTE) * 4;
		lpNumBytesToWrite[2] = sizeof(BYTE) * ulFolderCb;
		
		//
		// Sizes of the store data
		//
		lpNumBytesToWrite[3] = sizeof(ULONG);
		lpNumBytesToWrite[4] = sizeof(BYTE) * 4;
		lpNumBytesToWrite[5] = sizeof(BYTE) * ulStoreCb;

		for (int x = 0 ; x < 6; x++)
		{
			// Now write the data to a file:
			WriteFile(
				hFile, 
				lppBuffer[x],
				lpNumBytesToWrite[x],
				&numBytesWritten,
				NULL
			);
		}
		
		MAPIFreeBuffer(lpProps);

		lpMAPIFolder->Release();
	}
	
	DWORD dwNullTerminal = 0x00000000;
	DWORD dwNumBytesWritten;

	WriteFile(
		hFile,
		&dwNullTerminal,
		0x00000004,
		&dwNumBytesWritten,
		NULL);

	CloseHandle(hFile);

	DefineMacro("FOLDERDATA_FILENAME", cstrFolderdataFileName);
	DefineIntMacro("NUM_FOLDERS", iNumFolders);
	DefineIntMacro("NUM_STORES", m_lpMAPILogon->m_nMaxStores);
	DefineMacro("PROFILE_NAME", m_lpMAPILogon->m_lpszProfileName);
	DefineMacro("PROJTYPE_NTSERVICE", "TRUE");

	//
	// Clean up 
	//
	myList.erase(myList.begin(), myList.end());

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
	
}

BOOL CCustom1Dlg::MakeList(HTREEITEM hItem)
{
	HTREEITEM hChild, hSibling;


	if (GetCheckState(hItem))
	{
		TV_ITEM sTVItem;
		sTVItem.hItem = hItem;
		m_TreeCtrl.GetItem(&sTVItem);

		// Extract the SMailID structure.  
		SMailID * pMailID = (SMailID *)(sTVItem.lParam);
		myList.push_back(pMailID);
	}
		
	hChild = m_TreeCtrl.GetChildItem(hItem);
	if (hChild != NULL)
	{
		MakeList(hChild);
	}
	hSibling = m_TreeCtrl.GetNextSiblingItem(hItem);
	if (hSibling != NULL)
	{
		MakeList(hSibling);
	}
	return TRUE;
}

BOOL CCustom1Dlg::GetCheckState(HTREEITEM hItem)
{
    TVITEM tvItem;

    // Prepare to receive the desired information.
    tvItem.mask = TVIF_HANDLE | TVIF_STATE;
    tvItem.hItem = hItem;
    tvItem.stateMask = TVIS_STATEIMAGEMASK;

    // Request the information.
    m_TreeCtrl.GetItem(&tvItem);

    // Return zero if it's not checked, or nonzero otherwise.
    return ((BOOL)(tvItem.state >> 12) -1);
}


BOOL CCustom1Dlg::HasSynchronizer(LPMAPIFOLDER lpMAPIFolder)
{
	HRESULT hResult;
	BOOL fRetVal = FALSE;

	ULONG ulSynchProperty = PR_CONTENTS_SYNCHRONIZER;
	LPEXCHANGEEXPORTCHANGES lpSynchronizer = NULL;

	if (lpMAPIFolder)
	{
		hResult = lpMAPIFolder->OpenProperty(
										ulSynchProperty,
										&IID_IExchangeExportChanges,
										0,
										0,
										(LPUNKNOWN FAR *)&lpSynchronizer);
		if (SUCCEEDED(hResult))
		{
			lpSynchronizer->Release();
			fRetVal = TRUE;
		}
	}

	return fRetVal;
}

	

BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_NOTIFY(TVN_GETDISPINFO, IDC_EXCHANGE_TREE, OnGetdispinfoExchangeTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_EXCHANGE_TREE, OnSelchangedExchangeTree)
	ON_NOTIFY(TVN_DELETEITEM, IDC_EXCHANGE_TREE, OnDeleteitemExchangeTree)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_EXCHANGE_TREE, OnItemexpandingExchangeTree)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//------------------------------------------------------------------------- 
// Purpose: 
//    Returns a mapi folder on the selected item in the tree view. 
// 
STDMETHODIMP CCustom1Dlg::GetSelectedFolder (LPMAPIFOLDER * ppfld) 
{ 
	HRESULT  hr = NOERROR; 
	SMailID* pMailID = NULL; 
 
	if (ppfld)
	{
		// Get the current tree view selection's mail id 
		pMailID = (SMailID *)m_TreeCtrl.GetItemData(m_TreeCtrl.GetSelectedItem()); 
		if( pMailID) 
		{ 
			hr = OpenFolder(pMailID, ppfld); 
			if (FAILED(hr)) 
			{ 
				#ifdef _DEBUG 
				afxDump << TEXT("OpenFolder() failed for ");	
				afxDump << TEXT(pMailID->lpszDisplayName); 
				#endif 
			} 
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr; 
} 

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers


BOOL CCustom1Dlg::IsLegalContainer(CString cstr)
{
	if (cstr == m_lpszRootFolderName)
		return FALSE;

	return TRUE;
}


void CCustom1Dlg::OnItemexpandingExchangeTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR && pResult)
	{
		NM_TREEVIEW * pNMTreeView = (NM_TREEVIEW*)pNMHDR;

		SMailID * pMailID  = (SMailID*)pNMTreeView->itemNew.lParam; 
 
		if ((TVE_COLLAPSE == pNMTreeView->action) || (TVE_COLLAPSERESET == pNMTreeView->action)) 
		{ 
			if (pMailID->lpEntryID == NULL) 
			{ 
				// prevent tree view from collapsing the root 
				pNMTreeView->itemNew.mask  = TVIF_HANDLE | TVIF_STATE; 
				pNMTreeView->itemNew.state = TVIS_EXPANDED; 
				pNMTreeView->itemNew.stateMask = TVIS_EXPANDED; 
			} 
		} 
		else if ((TVE_EXPAND == pNMTreeView->action) && !(pNMTreeView->itemNew.state & TVIS_EXPANDEDONCE)) 
		{ 
			 if (FAILED(FirstTimeExpand(pNMTreeView->itemNew.hItem, pMailID))) 
			{ 

				#ifdef _DEBUG 
				afxDump << TEXT("FirstTimeExpand() failed for "); 
				afxDump << TEXT(pMailID->lpszDisplayName); 
				#endif 
			} 
		} 
		
		*pResult = 0;
	}
}

void CCustom1Dlg::OnGetdispinfoExchangeTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR && pResult)
	{
		TV_DISPINFO * pTVDispInfo = (TV_DISPINFO*)pNMHDR;
		SMailID * pMailID = (SMailID*)pTVDispInfo->item.lParam; 
 
		if (pMailID) 
		{ 
			// Set up the display text 
			if (pTVDispInfo->item.mask & TVIF_TEXT) 
			{ 
				pTVDispInfo->item.pszText    = (LPTSTR)pMailID->lpszDisplayName; 
				pTVDispInfo->item.cchTextMax = lstrlen(pTVDispInfo->item.pszText); 
			} 
 
			// Set up the images to use 
			if (pTVDispInfo->item.mask & TVIF_IMAGE) 
			{ 
				INT   iImage; 
				INT   iSelectedImage; 
 
				//iImage = MapTypeToExchangeImageListIndex(pMailID->ulType, &iSelectedImage); 
 
				iImage = 0;
				iSelectedImage = 0;

				if ((pTVDispInfo->item.mask & TVIF_STATE) && (pTVDispInfo->item.state & TVIS_EXPANDED)) 
				{ 
				   pTVDispInfo->item.iImage = iSelectedImage; 
				} 
				else 
				{ 
				   pTVDispInfo->item.iImage = iImage; 
				} 
				pTVDispInfo->item.iSelectedImage = iSelectedImage; 
			} 
 
			// Set up the count of children 
			if (pTVDispInfo->item.mask & TVIF_CHILDREN) 
			{ 
				pTVDispInfo->item.cChildren = I_CHILDRENCALLBACK; 
			} 
		}
		
		*pResult = 0;

	}
}

void CCustom1Dlg::OnSelchangedExchangeTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR && pResult)
	{
		NM_TREEVIEW * pNMTreeView = (NM_TREEVIEW *)pNMHDR;
		
		*pResult = 0;
	}
}

void CCustom1Dlg::OnDeleteitemExchangeTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR && pResult)
	{
		NM_TREEVIEW * pNMTreeView = (NM_TREEVIEW *)pNMHDR;

		SMailID * pMailID = (SMailID *)pNMTreeView->itemOld.lParam; 
		MAPIFreeBuffer((LPVOID)pMailID); 
 		
		*pResult = 0;
	}
}



BOOL CCustom1Dlg::AddTreeViewItems() 
{ 
	HTREEITEM hTRoot = NULL; 
	SMailID *pMailID = NULL; 
	SCODE sc = S_OK; 
 
	sc = CreateMailID(MAPI_SESSION, 0, NULL, m_lpszRootFolderName, &pMailID); 
	if (sc == S_OK) 
	{  
		// First add the root item 
		hTRoot = AddOneItem ((HTREEITEM)TVI_ROOT, 
							 pMailID->lpszDisplayName,  
							 (HTREEITEM)NULL, 
							 -1, 
							 (DWORD)pMailID); 
 

		if (hTRoot == NULL)
		{
			MessageBox("Failed to insert item");
		}

		m_TreeCtrl.Expand(hTRoot, TVE_EXPAND); 
		m_TreeCtrl.Select(hTRoot, TVGN_CARET); 
	} 
 
	return TRUE; 
} 

// This function fills out the TV_ITEM and TV_INSERTSTRUCT structures  
// and adds the item to the tree view control. 
 
HTREEITEM CCustom1Dlg::AddOneItem (HTREEITEM hParent, 
								   LPSTR lpszText,
								   HTREEITEM hInsAfter, 
								   int iImage, 
								   DWORD lparam) 
{ 
 
	TV_INSERTSTRUCT   tvis; 

	tvis.hParent             = hParent; 
	tvis.hInsertAfter        = hInsAfter; 
	tvis.item.mask           = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN | TVIF_PARAM | TVIF_STATE; 
	tvis.item.pszText        = LPSTR_TEXTCALLBACK; 
	tvis.item.cchTextMax     = 0; 
	tvis.item.iImage         = I_IMAGECALLBACK; 
	tvis.item.iSelectedImage = I_IMAGECALLBACK; 
	tvis.item.cChildren      = I_CHILDRENCALLBACK; 
	tvis.item.lParam         = (LPARAM)lparam; 

	tvis.item.state          = 0; 
	tvis.item.stateMask      = 0; 
 

	return m_TreeCtrl.InsertItem(&tvis); 
} 


//------------------------------------------------------------------------- 
// Purpose: 
//    Add rows from a mapi table to the tree view. 
// 
STDMETHODIMP CCustom1Dlg::AddRows(HTREEITEM   hitemParent, 
					  			  LPMAPITABLE pmt) 

{ 
	HRESULT     hr  = NOERROR; 
	BOOL        fDone          = FALSE; 
	HTREEITEM   hitem          = TVI_FIRST; 
	LPSRowSet   prws           = NULL; 
	ULONG       cRowsTotal     = 0; 
	CONST UINT  cRowsBatch     = 256; 
	CONST UINT  cWanted        = 3; 
	UINT        cFound         = 0; 
	ULONG       ulType         = 0; 
	ULONG       cbeid          = 0; 
	LPENTRYID   peid           = NULL; 
	LPTSTR      pszDisplayName = NULL; 
	SMailID*    pMailID        = NULL; 
	SMailID*    pParentMailID  = NULL; 
 
	SizedSPropTagArray(3, sptaFolderBrowse) = 
	{ 
		3, 
		{ 
			PR_OBJECT_TYPE,
			PR_ENTRYID, 
            PR_DISPLAY_NAME 
		} 
	};  

	if (pmt)
	{
		// Set the columns to those needed for folder browsing 
		if (SUCCEEDED(hr = pmt->SetColumns((LPSPropTagArray)&sptaFolderBrowse, 0))) 
		{ 
			// Get all of the table's rows 
			while (!fDone && 
				   SUCCEEDED(hr = pmt->QueryRows(cRowsBatch, 0, &prws)) && 
				   prws) 
			{ 
				if (prws->cRows > 0) 
				{ 
					cRowsTotal += prws->cRows; 
					// Add them to the tree 
					for (ULONG iRow = 0; iRow < prws->cRows; iRow++) 
					{ 
						cFound = 0; 
						// Get the appropriate values from the columns 
						for (ULONG iCol = 0; iCol < prws->aRow[iRow].cValues; iCol++) 
						{ 
							if (PR_OBJECT_TYPE == prws->aRow[iRow].lpProps[iCol].ulPropTag) 
							{ 
								ulType = (ULONG)prws->aRow[iRow].lpProps[iCol].Value.l; 
								cFound++; 
							} 
							else if (PR_ENTRYID == prws->aRow[iRow].lpProps[iCol].ulPropTag) 
							{ 
								cbeid = prws->aRow[iRow].lpProps[iCol].Value.bin.cb; 
								peid  = (LPENTRYID)prws->aRow[iRow].lpProps[iCol].Value.bin.lpb; 
								cFound++; 
							} 
							else if (PR_DISPLAY_NAME == prws->aRow[iRow].lpProps[iCol].ulPropTag) 
							{ 
								pszDisplayName = prws->aRow[iRow].lpProps[iCol].Value.LPSZ; 
								cFound++; 
							} 
						}	 
 
						// if we found all of them... 
						if (cFound == cWanted) 
						{ 
							// Create a mail id and add it to the tree 
							if (SUCCEEDED(CreateMailID(ulType, cbeid, peid, pszDisplayName, &pMailID))) 
							{ 
								hitem = AddOneItem(hitemParent, pszDisplayName, hitem, iimlExchange, (DWORD)pMailID); 
								ASSERT(hitem); 
							} 
						} // if (cFound == cWanted) 
 
					} // for (iRow 
				} 
				else 
				{ 
					fDone = TRUE; 
				} 
 
				FreeProws(prws); 
			} // while 
 
			// Set the children count on the parent item now that we know it 
			//m_TreeCtrl.SetItemChildCount(hitemParent, cRowsTotal); 

			TV_ITEM  tvi; 
			tvi.mask      = TVIF_HANDLE | TVIF_CHILDREN; 
			tvi.hItem     = hitemParent; 
			tvi.cChildren = cRowsTotal; 
			m_TreeCtrl.SetItem(&tvi); 
		}
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr; 
} 

//------------------------------------------------------------------------- 
// Purpose: 
//    Fill the tree view from the "root" of exchange. 
// 
STDMETHODIMP CCustom1Dlg::TvmtFromRoot (HTREEITEM hitemParent) 
{ 
	HRESULT     hr  = NOERROR; 
	LPMAPITABLE pmt = NULL; 
 
	if (SUCCEEDED(hr = m_lpMAPILogon->m_lpSession->GetMsgStoresTable(0, &pmt))) 
	{ 
		hr = AddRows(hitemParent, pmt); 
		pmt->Release(); 
	} 
 
	return hr; 
} 
 
 
//------------------------------------------------------------------------- 
// Purpose: 
//    Fill the tree view from a folder. 
// 
STDMETHODIMP CCustom1Dlg::TvmtFromFolder (HTREEITEM hitemParent, 
											LPMAPIFOLDER pfld) 
{ 
	HRESULT hr = NOERROR; 
	LPMAPITABLE pmt  = NULL; 
 
	// Get the folder hierarchy table 
	if (SUCCEEDED(hr = pfld->GetHierarchyTable(MAPI_DEFERRED_ERRORS, &pmt))) 
	{ 
		hr = AddRows(hitemParent, pmt); 
		pmt->Release(); 
	} 
 
	return hr; 
} 
 
 
//------------------------------------------------------------------------- 
// Purpose: 
//    Expand a tree view item. 
// 
STDMETHODIMP CCustom1Dlg::FirstTimeExpand (HTREEITEM  hitem, 
											 SMailID*   pMailID) 
{ 
	HRESULT  hr= NOERROR; 

	if (pMailID)
	{
		if (MAPI_SESSION == pMailID->ulType) 
		{ 
			hr = TvmtFromRoot(hitem); 
		} 
		else 
		{ 
			LPMAPIFOLDER   pfld; 
 
			if (SUCCEEDED(hr = OpenFolder(pMailID, &pfld))) 
			{ 
				hr = TvmtFromFolder(hitem, pfld); 
				pfld->Release(); 
			} 
		} 
 
	}
	else
	{
		hr = E_INVALIDARG;
	}

	return hr; 
} 

//------------------------------------------------------------------------- 
// Purpose: 
//    Creates a *simple* pidl. 
// 
// static 
STDMETHODIMP CCustom1Dlg::CreateMailID 
   ( 
   ULONG          ulType,           // IN:  one of MAPI_SESSION, MAPI_STORE, or MAPI_FOLDER 
   ULONG          cbEntryID,        // IN:  count of bytes in entry ID 
   LPENTRYID      lpEntryID,        // IN:  entry ID 
   LPCTSTR        lpszDisplayName,  // IN:  display name of item 
   SMailID**      ppob              // OUT: pointer to resulting object 
   ) 
{ 
	SCODE sc= S_OK; 
 
	// lpszDisplayName and ppob should not be NULL
	// lpEntryID may be null when cbEntryID == 0
	if ((lpszDisplayName && ppob) && (lpEntryID || !cbEntryID))
	{
		// Allocate space for the 
		sc = MAPIAllocateBuffer( sizeof(SMailID), (LPVOID *)ppob); 
		if (FAILED(sc)) 
		{ 
			return sc;
		}	
 
		(*ppob)->cbEntryID = cbEntryID; 
		(*ppob)->ulType   = ulType; 
		(*ppob)->lpEntryID  = NULL; 
		(*ppob)->lpszDisplayName   = NULL; 
 
		sc = MAPIAllocateMore(cbEntryID, (LPVOID)*ppob, (LPVOID*)&((*ppob)->lpEntryID)); 
		if (FAILED(sc)) 
		{ 
			return sc;
		} 
 
		CopyMemory((*ppob)->lpEntryID, lpEntryID, cbEntryID); 
 
		sc = MAPIAllocateMore(lstrlen(lpszDisplayName)+1, (LPVOID)*ppob, (LPVOID*)&((*ppob)->lpszDisplayName)); 
		if (FAILED(sc)) 
		{ 
			return sc;
		} 
 
		lstrcpy((*ppob)->lpszDisplayName, lpszDisplayName); 

	}
	else
	{
		sc = E_INVALIDARG;
	}

	return(sc); 
} 
 

STDMETHODIMP CCustom1Dlg::OpenFolder(SMailID *pMailID, LPMAPIFOLDER *ppfld) 
{ 
	HRESULT        hr= NOERROR; 
	LPSPropValue   pval= NULL; 
	ULONG          ulObjType = 0; 
  

	if (pMailID && ppfld)
	{

		if (MAPI_STORE == pMailID->ulType) 
		{ 
			// Open the store. (only if not already open) 
			LPMDB lpMDB = NULL; 
			if (SUCCEEDED(hr = m_lpMAPILogon->OpenMsgStore(pMailID->cbEntryID, pMailID->lpEntryID, &lpMDB))) 
			{ 
				// Open the IPM subtree as a folder. 
				if (SUCCEEDED(hr = HrGetOneProp(lpMDB, PR_IPM_SUBTREE_ENTRYID, &pval))) 
				{ 
					hr = m_lpMAPILogon->m_lpSession->OpenEntry(pval->Value.bin.cb, 
														 (LPENTRYID)pval->Value.bin.lpb, 
														 &IID_IMAPIFolder, 
														 0L, 
														 &ulObjType, 
														 (LPUNKNOWN*)ppfld); 
 
          
					MAPIFreeBuffer(pval); 
				}  
			} 
		} 
		else if (MAPI_FOLDER == pMailID->ulType) 
		{ 
			// Open the folder. 
			hr = m_lpMAPILogon->m_lpSession->OpenEntry(pMailID->cbEntryID, 
												 pMailID->lpEntryID, 
												 &IID_IMAPIFolder, 
												 MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
												 &ulObjType, 
												 (LPUNKNOWN*)ppfld); 
		}   
    }
	else
	{
		hr = E_INVALIDARG;
	}

	return hr; 
} 
 
 
  

BOOL CCustom1Dlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CAppWizStepDlg::OnNotify(wParam, lParam, pResult);
}

int CCustom1Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CAppWizStepDlg::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_lpMAPILogon = new CMAPILogon;
	if (!m_lpMAPILogon)
	{
		MessageBox("MAPI failed to initialize");
		return -1;
	}

	m_lpMAPILogon->HrInitialize(m_hWnd);
	if (!m_lpMAPILogon->m_fMAPIInitialized)
	{
		MessageBox("MAPI failed to initialize");
		return -1;
	}

	m_fIsInitialized = TRUE;

	return 0;
}

BOOL CCustom1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();

	CreateImageListExchange();
	m_TreeCtrl.SetImageList(&m_obImageListExchange, TVSIL_NORMAL);  
	AddTreeViewItems(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//------------------------------------------------------------------------- 
// Purpose: 
//    Create our global image list used to draw mail items. 
// 
//  
BOOL CCustom1Dlg::CreateImageListExchange(VOID) 
{ 
	BOOL  fRet = FALSE; 
 
	static struct SImageListInfo 
	{ 
		UINT  nIdIcon; 
    } aImageListInfo[cimlExchange] = { 
		ICO_Exchange, 
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
		UINT ii= 0; 
		HICON hicon = NULL; 
 
		for (ii = 0; ii < cimlExchange; ii++) 
		{ 
			hicon = ::LoadIcon(AfxGetResourceHandle(),
							   MAKEINTRESOURCE(aImageListInfo[ii].nIdIcon)); 
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
 

void CCustom1Dlg::OnDestroy() 
{
	CAppWizStepDlg::OnDestroy();
	
	if (m_lpMAPILogon != NULL)
	{
		m_lpMAPILogon->HrUninitialize();
		delete m_lpMAPILogon;
		m_lpMAPILogon = NULL;
	}	
}

