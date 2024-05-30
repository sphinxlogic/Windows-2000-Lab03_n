//--dchkmail.cpp--------------------------------------------------------------
//
// implementation of the CCheckMailDlg class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------


#include "stdafx.h"
#include "mbxserv.h"

#include "oditem.h"		// COwnerDrawItem
#include "odlist.h"		// COwnerDrawListBox
#include "dchkmail.h"
#include "dabout.h"		// CAboutDlg

#include "mbxdata.h"
#include "emsabtag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_MESSAGE_HDRS    50   //Max. messages per query

/////////////////////////////////////////////////////////////////////////////
// CCheckMailDlg dialog

CCheckMailDlg::CCheckMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckMailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckMailDlg)
	m_strAlias = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lpGAL = NULL;
	m_lpSession = NULL;
	m_lpMDB = NULL;
}

void CCheckMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckMailDlg)
	DDX_Control(pDX, IDC_MAIL, m_lbMail);
	DDX_Text(pDX, IDC_ALIAS, m_strAlias);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckMailDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckMailDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDOK, OnGetMail)
	ON_EN_CHANGE(IDC_ALIAS, OnChange)
	ON_EN_CHANGE(IDC_PASSWORD, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckMailDlg message handlers

BOOL CCheckMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERTERROR((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX,
            "IDM_ABOUTBOX is out of range");
    ASSERTERROR(IDM_ABOUTBOX < 0xF000,"IDM_ABOUTBOX is out of range");

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    SetClassLong (m_hWnd, GCL_HICON, (LONG)m_hIcon);

	OnChange();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCheckMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CCheckMailDlg::OnGetMail() 
{
	HRESULT hr;
	ULONG	ulLoop;
	LPSTR			lpszMsgStoreDN	= NULL;
	LPSTR			lpszMailboxDN	= NULL;
	SBinaryArray *	lpbaExtData		= NULL;

	LPMAPITABLE		lpGALTable		= NULL;
	LPMDB			lpMailboxMDB	= NULL;
	LPSRowSet		lpRowSet		= NULL;
    
	SRestriction	resNickname;
	SPropValue		prop;

	m_lbMail.ResetContent();				// Clear listbox

    UpdateData (TRUE);
	
    ASSERTERROR (!m_strAlias.IsEmpty(), "Can't get mail with out an alias");
	ASSERTERROR (!m_strPassword.IsEmpty(), "Can't get mail with out a password");

    ASSERTERROR (m_lpGAL != NULL, "No pointer to the global address list");

	static const SizedSPropTagArray(3, StoreAttributes) = 
	{
		3,
		{
			PR_EMAIL_ADDRESS,				// lpszMsgStoreDN
			PR_EMS_AB_HOME_MDB,				// lpszMailboxDN
			PR_EMS_AB_EXTENSION_DATA,     	// extension data
		}
	};

    hr = m_lpGAL->GetContentsTable (MAPI_DEFERRED_ERRORS, &lpGALTable);
    
    if (FAILED(hr))
		goto cleanup;

	resNickname.rt = RES_CONTENT;
	resNickname.res.resContent.ulFuzzyLevel = FL_PREFIX;	// FL_FULLSTRING == MAPI_E_TOO_COMPLEX 
	resNickname.res.resContent.ulPropTag = PR_ACCOUNT;
	resNickname.res.resContent.lpProp = &prop;
	prop.ulPropTag = PR_ACCOUNT;
	prop.Value.lpszA = (LPSTR)(LPCSTR)m_strAlias;

    hr = HrQueryAllRows (
            lpGALTable,
            (LPSPropTagArray)&StoreAttributes,
            &resNickname,
            NULL,
            2,
            &lpRowSet);

    if (FAILED(hr))
		goto cleanup;

	if (lpRowSet->cRows != 1)
	{
		AfxMessageBox ("Name not found or name is ambiguous.");
		goto cleanup;
	}

	ASSERTERROR (lpRowSet->cRows == 1, "Using ambiguous name");

	// go find the values we need
	for (ulLoop = 0;ulLoop < lpRowSet->aRow[0].cValues; ulLoop++)
	{
		switch (lpRowSet->aRow[0].lpProps[ulLoop].ulPropTag)
		{
		case PR_EMS_AB_EXTENSION_DATA:
			lpbaExtData = &lpRowSet->aRow[0].lpProps[ulLoop].Value.MVbin;
			break;
		case PR_EMS_AB_HOME_MDB:
			lpszMsgStoreDN = lpRowSet->aRow[0].lpProps[ulLoop].Value.lpszA;
			break;
		case PR_EMAIL_ADDRESS:
			lpszMailboxDN = lpRowSet->aRow[0].lpProps[ulLoop].Value.lpszA;
			break;
		}
	}

	if (lpbaExtData == NULL)
	{
		AfxMessageBox ("Mailbox has not been configured");
		goto cleanup;
	}
		
	if ((lpszMsgStoreDN == NULL) || (lpszMailboxDN == NULL))
	{
		AfxMessageBox ("Could not find message store information");
		goto cleanup;
	}

	hr = HrCheckPassword (lpbaExtData, m_strPassword);

    if (FAILED(hr))
		goto cleanup;

    hr = HrMailboxLogon (m_lpSession, m_lpMDB, lpszMsgStoreDN, lpszMailboxDN, 
            &lpMailboxMDB);

    if (FAILED(hr))
		goto cleanup;

    hr = HrDispMailboxSubjects (lpMailboxMDB);

    if (FAILED(hr))
        goto cleanup;

cleanup:
    if (lpMailboxMDB)
        hr = HrMailboxLogoff (&lpMailboxMDB);
    
    ULRELEASE(lpGALTable);
    ULRELEASE(lpMailboxMDB);
	MAPIFREEBUFFER(lpRowSet);
}

void CCheckMailDlg::OnChange() 
{
	// Enable Get Mail button only when we have an alias and password

	UpdateData (TRUE);

	CWnd * pWnd = GetDlgItem (IDOK);
	ASSERTERROR (pWnd != NULL, "Could not find OK button");

	if (m_strAlias.IsEmpty() || m_strPassword.IsEmpty())
	{
		pWnd->EnableWindow (FALSE);
	}
	else
	{
		pWnd->EnableWindow (TRUE);
	}	
}

HRESULT CCheckMailDlg::HrDispMailboxSubjects(LPMDB  lpMDB)
{
    HRESULT         hr                  = NOERROR;
    unsigned        iMsgIndx            = 0;
    unsigned        nCnt                = 0;
    ULONG           cbeid               = 0L;
    ULONG           ulObjType           = 0L;
    LPENTRYID       lpeid               = NULL;
    LPMAPIFOLDER    lpInboxFolder       = NULL;     // ptr to Inbox folder
    LPMAPITABLE     lpContentsTbl       = NULL;     // ptr to Contents folder table
    LPSRowSet       lpInRowSet          = NULL;     // ptr to Inbox rows
    LPSPropValue    lpProps             = NULL;     // Ptr to property array.

    static const SizedSSortOrderSet(1L,sSortPrioSet) = 
        { 1L, 0L, 0L, { PR_CLIENT_SUBMIT_TIME, TABLE_SORT_ASCEND}};

    static const SizedSPropTagArray(3L,sPropColumns) =
        { 3L, {PR_SUBJECT, PR_MESSAGE_FLAGS, PR_ENTRYID}};

    DEBUGPRIVATE( "HrDispMailboxSubjects()");

    if (lpMDB == NULL)
        return E_INVALIDARG;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Initialize an inbox folder object.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Find default (inbox) folder.
    hr = HrMAPIFindInbox( lpMDB, &cbeid, &lpeid);
    if( FAILED(hr))
        goto cleanup;
    ASSERTERROR ( lpeid != NULL, "NULL lpeid");
    
    // Open the default (inbox) folder.
    hr = lpMDB->OpenEntry(cbeid, lpeid, NULL,
			MAPI_MODIFY|MAPI_DEFERRED_ERRORS, &ulObjType, (LPUNKNOWN*)&lpInboxFolder);
    if( FAILED( hr))
        goto cleanup;
    if( ulObjType != MAPI_FOLDER)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Now that we have a folder we can initialize a contents table
// to look through.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Get the contents table for the folder.
    hr = lpInboxFolder->GetContentsTable(
			MAPI_DEFERRED_ERRORS, &lpContentsTbl);
    if( FAILED( hr))
        goto cleanup;

    // Set the columns to return.
    hr = lpContentsTbl->SetColumns((LPSPropTagArray) &sPropColumns, 0L);
    if(FAILED(hr))
        goto cleanup;

    // Sort the table.
    hr = lpContentsTbl->SortTable((LPSSortOrderSet) &sSortPrioSet, 0L);
    if(FAILED(hr))
        goto cleanup;
    
    // Position to the beginning of the contents table.
    hr = lpContentsTbl->SeekRow(BOOKMARK_BEGINNING, 0, NULL);
    if( FAILED(hr))
        goto cleanup;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Contents table has been initialize so lets display it.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Display INBOX subjects until end of table reached.
    while (TRUE)
    {   // Read a group of message headers from the contents table.
        hr = HrGetMsgList( lpContentsTbl, MAX_MESSAGE_HDRS, &lpInRowSet);
        if (hr == MAPI_E_NOT_FOUND)
            break;

        if (FAILED( hr))
            goto cleanup;;
            
        ASSERTERROR( lpInRowSet != NULL, "NULL lpInRowSet!");

        // Process all messages in the current table.
        for (iMsgIndx = 0; iMsgIndx < lpInRowSet->cRows; ++iMsgIndx )
        {   // Display the subject name.

			if( lpInRowSet->aRow[iMsgIndx].cValues )
			{
				lpProps = lpInRowSet->aRow[iMsgIndx].lpProps;

				ASSERTERROR(PROP_ID(lpProps->ulPropTag) == PROP_ID(PR_SUBJECT),
                        "Invalid property returned!");

				CString strSubject;

				if(lpProps->ulPropTag == PR_SUBJECT )
				{

					if (lpProps->Value.LPSZ == NULL || *(lpProps->Value.LPSZ) == 0)
					{
						strSubject = "  SUBJECT: (empty).";
					}
					else
					{
						strSubject = lpProps->Value.LPSZ;
					}
				}
				else
				{
					//When the subject field was left empty while mail was sent,
					//lpProps->ulProTag may not be PR_SUBJECT, so print subject as empty

					strSubject = "  SUBJECT: (empty).";
				}

				COwnerDrawItem * pODI = new COwnerDrawItem();
				if (lpProps[1].Value.l & MSGFLAG_READ)
				{
					pODI->Create (NULL, strSubject);
				}
				else
				{
					pODI->Create (NULL, strSubject,	ODI_BOLDTEXT);
				}

				m_lbMail.AddODI(pODI);
				nCnt ++;
			}
        }
 
		// Free the current message list structure.
        FREEPROWS( lpInRowSet);
    }

	if (nCnt == 0)
	{
		COwnerDrawItem * pODI = new COwnerDrawItem();
		pODI->Create (NULL, "No messages found");
		m_lbMail.AddODI(pODI);
	}

cleanup:
	return S_OK;
}

HRESULT CCheckMailDlg::HrGetMsgList(
    LPMAPITABLE lpTable,    // ptr.to the contents table
    LONG       cMaxNRows,  // Max.# of rows to return
    LPSRowSet   *lppRows )  // ptr.to address variable for SRowSet
{
    HRESULT      hr  = NOERROR;

    if ((lpTable == NULL) ||
        (lppRows == NULL))
    {
        return E_INVALIDARG;
    }

    DEBUGPRIVATE( "HrGetMsgList()" );

    // Get the next list of messages in the folder
    hr = lpTable->QueryRows(cMaxNRows, 0L, lppRows );
    if( SUCCEEDED(hr) && ((*lppRows) != NULL) && ((*lppRows)->cRows == 0))
    {
        FREEPROWS(*lppRows);
        hr = MAPI_E_NOT_FOUND;
    }

    return hr;
}

HRESULT CCheckMailDlg::HrCheckPassword (SBinaryArray * lpbaExtData, LPCTSTR szPassword)
{
	HRESULT hr = E_FAIL;

    if ((lpbaExtData == NULL) ||
        (szPassword == NULL))
    {
        return E_INVALIDARG;
    }
	// For each blob returned
	for (ULONG ulLoop = 0; ulLoop < lpbaExtData->cValues; ulLoop++)
	{
		// Find our blob (the name is the first thing; UNICODE)
		if (wcsicmp (MBXBLOBNAMEW, (LPWSTR)lpbaExtData->lpbin[ulLoop].lpb) == 0)
		{
			LPSPropValue pvData = NULL;
			ULONG ulData;
			
			hr = HrCfgUnpackData (
					lpbaExtData->lpbin[ulLoop].cb,
					lpbaExtData->lpbin[ulLoop].lpb, NULL, &ulData, &pvData);
		
			if (FAILED (hr))
				return hr;

			ASSERTERROR (ulData == 1, "Extension data in unknown format");

			if (lstrcmp (szPassword, pvData[0].Value.lpszA) == 0)
			{
				hr = S_OK;
			}
			else
			{
				AfxMessageBox ("Invalid Password");
				hr = E_FAIL;
			}
			MAPIFREEBUFFER (pvData);
		}
	}
	return hr;
}
