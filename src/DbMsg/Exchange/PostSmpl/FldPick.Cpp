//=========================================================================
// FldPick.CPP
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
// 
//
// Purpose:
//    Implements the folder picker dialog.

//=========================================================================


#include "stdafx.h"
#include "PostSmpl.h"
#include "PostData.h"
#include "FldPick.h"



#include <initguid.h>
#define USES_IID_IMAPIFolder
#define USES_IID_IMsgStore
#include <mapiguid.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
SizedSPropTagArray(3, sptaFolderBrowse) = { 3, { PR_OBJECT_TYPE,
                                                    PR_ENTRYID,
                                                    PR_DISPLAY_NAME } };

/////////////////////////////////////////////////////////////////////////////
// CFolderPicker dialog


CFolderPicker::CFolderPicker(CWnd* pParent /*=NULL*/)
	: CDialog(CFolderPicker::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFolderPicker)
	//}}AFX_DATA_INIT
}


void CFolderPicker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFolderPicker)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_TREEVIEW, m_TreeCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFolderPicker, CDialog)
	//{{AFX_MSG_MAP(CFolderPicker)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREEVIEW, OnItemexpandingTreeview)
	ON_NOTIFY(TVN_GETDISPINFO, IDC_TREEVIEW, OnGetdispinfoTreeview)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEW, OnSelchangedTreeview)
	ON_NOTIFY(TVN_DELETEITEM, IDC_TREEVIEW, OnDeleteitemTreeview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFolderPicker message handlers

void CFolderPicker::OnOK() 
{
	// Add extra validation here
   GetSelectedFolder(&PostData.m_lpTempFld);
   CDialog::OnOK();
}

void CFolderPicker::OnCancel() 
{
	// Add extra cleanup here
	CDialog::OnCancel();
}



BOOL CFolderPicker::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Add extra initialization here
	m_TreeCtrl.SetImageList(&PostData.m_obImageListExchange, TVSIL_NORMAL);
	
	AddTreeViewItems();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CFolderPicker::AddTreeViewItems()
{
	HTREEITEM hTRoot = NULL;
	SMailID *pMailID = NULL;
	SCODE	sc       = S_OK;

	sc = CreateMailID(MAPI_SESSION, 0, NULL, "Microsoft Exchange\0", &pMailID);
	if (sc == S_OK)
	{

		// First add the root item
		hTRoot = AddOneItem ((HTREEITEM)TVI_ROOT, pMailID->lpszDisplayName, 
		(HTREEITEM)NULL, iimlExchange, (DWORD)pMailID);

		m_TreeCtrl.Expand(hTRoot, TVE_EXPAND);
		m_TreeCtrl.Select(hTRoot, TVGN_CARET);
	}
	
	return TRUE;
}


// This function fills out the TV_ITEM and TV_INSERTSTRUCT structures 
// and adds the item to the tree view control.

HTREEITEM CFolderPicker::AddOneItem (HTREEITEM hParent, LPSTR lpszText,
   HTREEITEM hInsAfter, int iImage, DWORD lparam)
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
//    Returns a mapi folder on the selected item in the tree view.
//
STDMETHODIMP CFolderPicker::GetSelectedFolder
   (
   LPMAPIFOLDER*  ppfld
   )
{
   HRESULT  hr		= NOERROR;
   SMailID* pMailID = NULL;

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

   return hr;
}

//-------------------------------------------------------------------------
// Purpose:
//    Add rows from a mapi table to the tree view.
//
STDMETHODIMP CFolderPicker::AddRows
   (
   HTREEITEM   hitemParent,
   LPMAPITABLE pmt
   )
{
   HRESULT     hr			  = NOERROR;
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

   return hr;
}


//-------------------------------------------------------------------------
// Purpose:
//    Fill the tree view from the "root" of exchange.
//
STDMETHODIMP CFolderPicker::TvmtFromRoot
   (
   HTREEITEM   hitemParent
   )
{
   HRESULT     hr  = NOERROR;
   LPMAPITABLE pmt = NULL;

   if (SUCCEEDED(hr = PostData.m_lpSession->GetMsgStoresTable(0, &pmt)))
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
STDMETHODIMP CFolderPicker::TvmtFromFolder
   (
   HTREEITEM      hitemParent,
   LPMAPIFOLDER   pfld
   )
{
   HRESULT        hr   = NOERROR;
   LPMAPITABLE    pmt  = NULL;

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
STDMETHODIMP CFolderPicker::FirstTimeExpand
   (
   HTREEITEM  hitem,
   SMailID*   pMailID
   )
{
   HRESULT  hr	= NOERROR;

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

   return hr;
}
//-------------------------------------------------------------------------
// Purpose:
//    Creates a *simple* pidl.
//
// static
STDMETHODIMP CFolderPicker::CreateMailID
   (
   ULONG          ulType,           // IN:  one of MAPI_SESSION, MAPI_STORE, or MAPI_FOLDER
   ULONG          cbEntryID,        // IN:  count of bytes in entry ID
   LPENTRYID      lpEntryID,        // IN:  entry ID
   LPCTSTR        lpszDisplayName,  // IN:  display name of item
   SMailID**      ppob              // OUT: pointer to resulting object
   )
{
  	SCODE sc	= S_OK;
 
	// Allocate space for the
	sc = MAPIAllocateBuffer( sizeof(SMailID), (LPVOID *)ppob);
    if (FAILED(sc))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateMailID(): MAPIAllocateBuffer failed");
		#endif
		goto CleanUp;						   // Allocate space for the
	}

	(*ppob)->cbEntryID = cbEntryID;
	(*ppob)->ulType   = ulType;
	(*ppob)->lpEntryID  = NULL;
	(*ppob)->lpszDisplayName   = NULL;

	sc = MAPIAllocateMore(cbEntryID, (LPVOID)*ppob, (LPVOID*)&((*ppob)->lpEntryID));
	if (FAILED(sc))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateMailID(): MAPIAllocateMore failed");
		#endif
		goto CleanUp;						   // Allocate space for the
	}
		
	CopyMemory((*ppob)->lpEntryID, lpEntryID, cbEntryID);

	sc = MAPIAllocateMore(lstrlen(lpszDisplayName)+1, (LPVOID)*ppob, (LPVOID*)&((*ppob)->lpszDisplayName));
	if (FAILED(sc))
	{
		#ifdef _DEBUG
		afxDump << TEXT("CreateMailID(): MAPIAllocateMore failed");
		#endif
		goto CleanUp;						   // Allocate space for the
	}

	lstrcpy((*ppob)->lpszDisplayName, lpszDisplayName);


CleanUp:
	return(sc);

}

STDMETHODIMP CFolderPicker::OpenFolder(SMailID *pMailID, LPMAPIFOLDER *ppfld)
{
   
   HRESULT        hr		= NOERROR;
   LPSPropValue   pval		= NULL;
   ULONG          ulObjType = 0;
			 
      
   if (MAPI_STORE == pMailID->ulType)
   {
      // Open the store. (only if not already open)
	  LPMDB lpMDB = NULL;
      if (SUCCEEDED(hr = PostData.OpenMsgStore(pMailID->cbEntryID, pMailID->lpEntryID, &lpMDB)))
      {
         // Open the IPM subtree as a folder.
         if (SUCCEEDED(hr = HrGetOneProp(lpMDB, PR_IPM_SUBTREE_ENTRYID, &pval)))
         {
            hr = PostData.m_lpSession->OpenEntry(pval->Value.bin.cb,
                                          (LPENTRYID)pval->Value.bin.lpb,
                                          &IID_IMAPIFolder,
                                          MAPI_MODIFY | MAPI_DEFERRED_ERRORS,
                                          &ulObjType,
                                          (LPUNKNOWN*)ppfld);

         
            MAPIFreeBuffer(pval);
         }
         
       }
   }
   else if (MAPI_FOLDER == pMailID->ulType)
   {
             // Open the folder.
            hr = PostData.m_lpSession->OpenEntry(pMailID->cbEntryID,
                                          pMailID->lpEntryID,
                                          &IID_IMAPIFolder,
                                          MAPI_MODIFY | MAPI_DEFERRED_ERRORS,
                                          &ulObjType,
                                          (LPUNKNOWN*)ppfld);
   }
         
   return hr;
}


void CFolderPicker::OnItemexpandingTreeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	// Add your control notification handler code here
	// Provide display info
  
   // An item is expanding,
      SMailID*       pMailID  = (SMailID*)pnmtv->itemNew.lParam;

	if ((TVE_COLLAPSE == pnmtv->action) || (TVE_COLLAPSERESET == pnmtv->action))
    {
		if (pMailID->lpEntryID == NULL)
        {
            // prevent tree view from collapsing the root
            pnmtv->itemNew.mask  = TVIF_HANDLE | TVIF_STATE;
            pnmtv->itemNew.state = TVIS_EXPANDED;
            pnmtv->itemNew.stateMask = TVIS_EXPANDED;
         }
	}
	else if ((TVE_EXPAND == pnmtv->action) && !(pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
	{
         if (FAILED(FirstTimeExpand(pnmtv->itemNew.hItem, pMailID)))
		 {
			#ifdef _DEBUG
			afxDump << TEXT("FirstTimeExpand() failed for ");
			afxDump << TEXT(pMailID->lpszDisplayName);
			#endif
		 }
	}      
       
	*pResult = 0;
}

void CFolderPicker::OnGetdispinfoTreeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pDispInfo = (TV_DISPINFO*)pNMHDR;
	// Add your control notification handler code here
	// Provide display info
  
     SMailID*       pMailID = (SMailID*)pDispInfo->item.lParam;

      if (pMailID)
      {
         // Set up the display text
         if (pDispInfo->item.mask & TVIF_TEXT)
         {
            pDispInfo->item.pszText    = (LPTSTR)pMailID->lpszDisplayName;
            pDispInfo->item.cchTextMax = lstrlen(pDispInfo->item.pszText);
         }

         // Set up the images to use
         if (pDispInfo->item.mask & TVIF_IMAGE)
         {
            INT   iImage;
            INT   iSelectedImage;

            iImage = MapTypeToExchangeImageListIndex(pMailID->ulType, &iSelectedImage);
			
            if ((pDispInfo->item.mask & TVIF_STATE) && (pDispInfo->item.state & TVIS_EXPANDED))
            {
               pDispInfo->item.iImage = iSelectedImage;
            }
            else
            {
               pDispInfo->item.iImage = iImage;
            }
            pDispInfo->item.iSelectedImage = iSelectedImage;
         }

         // Set up the count of children
         if (pDispInfo->item.mask & TVIF_CHILDREN)
         {
            pDispInfo->item.cChildren = I_CHILDRENCALLBACK;
         }
      }

	  *pResult = 0;
}


void CFolderPicker::OnSelchangedTreeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	// Add your control notification handler code here
	// Enable or disable buttons as appropriate due to the selection
   	           
	SMailID*       pMailID  = (SMailID*)pnmtv->itemNew.lParam;

    if (MAPI_SESSION != pMailID->ulType)
    {
        m_ok.EnableWindow(TRUE);
    }
    else
    {
        m_ok.EnableWindow(FALSE);
    }

	*pResult = 0;
}

//-------------------------------------------------------------------------
// Purpose:
//    Get the image list index corresponding to a MAPI object type.
//
INT CFolderPicker::MapTypeToExchangeImageListIndex
   (
   ULONG ulType,
   INT*  piSelectedImage
   )
{
   INT iImage = iimlFolder;
   
   if (MAPI_SESSION == ulType)
   {
		iImage           = iimlExchange;
		*piSelectedImage = iimlExchangeOpen;
   }
   else if (MAPI_STORE == ulType)
   {
		iImage           = iimlMdb;
		*piSelectedImage = iimlMdbOpen;	
   }
   else if (MAPI_FOLDER == ulType)
   {
		iImage           = iimlFolder;
		*piSelectedImage = iimlFolderOpen;
   }
   else
   {
		#ifdef _DEBUG
	    afxDump << TEXT("MapTypeToExchangeImageListIndex: Incorrect ulType");
		#endif
		iImage = iimlFolder;
		*piSelectedImage = iimlFolder;
	}
  
   return iImage;
}



void CFolderPicker::OnDeleteitemTreeview(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	// Add your control notification handler code here
	// Delete our user data
    SMailID*       pMailID = (SMailID *)pnmtv->itemOld.lParam;
	
	MAPIFreeBuffer((LPVOID)pMailID);

	*pResult = 0;
}




