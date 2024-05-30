
/******************************************************************************\
********************************************************************************
* Filename: FileRmClientDlg.cpp
*
* Description:  Main UI for test app
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

#include "stdafx.h"
#include "FileRmClient.h"
#include "FileRmClientDlg.h"
#define IID_DEFINED
#include "..\..\..\common\inc\cpyimage.h"
#include "..\..\..\common\inc\cpyimage_i.c"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "afxpriv.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileRmClientDlg dialog

CFileRmClientDlg::CFileRmClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileRmClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileRmClientDlg)
	m_sSource = _T("c:\\test");
	m_sImgFileName = _T("");
	m_sMainColor = _T("<main color>");
	m_sTheme = _T("<theme>");
	m_sDescription = _T("<description>");
	m_sMsg = _T("");
	m_sDest = _T("c:\\images");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
;
}

void CFileRmClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileRmClientDlg)
	DDX_Text(pDX, IDC_IMG_FILENAME, m_sImgFileName);
	DDV_MaxChars(pDX, m_sImgFileName, 118);
	DDX_Text(pDX, IDC_MAINCOLOR, m_sMainColor);
	DDV_MaxChars(pDX, m_sMainColor, 255);
	DDX_Text(pDX, IDC_THEME, m_sTheme);
	DDV_MaxChars(pDX, m_sTheme, 255);
	DDX_Text(pDX, IDC_DESCRIPTION, m_sDescription);
	DDV_MaxChars(pDX, m_sDescription, 255);
	DDX_Text(pDX, IDC_MSG, m_sMsg);
	DDX_Text(pDX, IDC_DESTINATION, m_sDest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileRmClientDlg, CDialog)
	//{{AFX_MSG_MAP(CFileRmClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_BN_CLICKED(IDC_COPY_DIRECTORY, OnCopyDirectory)
	ON_BN_CLICKED(IDC_INSERT_DATA, OnInsertData)
	ON_BN_CLICKED(IDC_SELECT_PICTURE, OnSelectPicture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileRmClientDlg message handlers

BOOL CFileRmClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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
	

	CRect rect;

	CWnd * pWnd = GetDlgItem(IDC_PICT_SPOT);
	pWnd -> GetWindowRect(&rect);
	ScreenToClient(rect);
	pWnd -> ShowWindow(SW_HIDE);
	BOOL bRet = m_ctlPict.Create("", WS_VISIBLE|WS_CHILD, rect, this, IDC_PICTURECTL);
	if (!bRet)
		AfxMessageBox("Failed to create PictureCtl!", MB_ICONSTOP);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileRmClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileRmClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileRmClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileRmClientDlg::OnCopy() 
{
#if 0
	CWaitCursor wait;
	ITransactionDispenser	*pTransactionDispenser;
	ITransaction			*pTransaction;
	HRESULT					hr = S_OK ;
	BOOL					tf = 0 ;

	// Obtain the ITransactionDispenser Interface pointer
	// by calling DtcGetTransactionManager()
	hr = DtcGetTransactionManager(
				NULL,								// LPTSTR	 pszHost,
				NULL,								// LPTSTR	 pszTmName,
				IID_ITransactionDispenser,			// /* in  */ REFIID rid,
				0,									// /* in  */ DWORD	dwReserved1,
				0, 									// /* in  */ WORD	wcbReserved2,
				NULL,								// /* in  */ void FAR * pvReserved2,
				(void **)&pTransactionDispenser 	// /* out */ void** ppvObject
				);

	if (FAILED (hr))
	{
		CString s;
		s.Format("DtcGetTransactionManager failed: %x\n", hr);
		AfxMessageBox(s);
		return;
	}
	

	hr = pTransactionDispenser->BeginTransaction( 
					NULL,							//	/* [in]  */ IUnknown __RPC_FAR *punkOuter,
					ISOLATIONLEVEL_ISOLATED,		//	/* [in]  */ ISOLEVEL isoLevel,
					ISOFLAG_RETAIN_DONTCARE,		// 	/* [in]  */ ULONG isoFlags,
					NULL,							//	/* [in]  */ ITransactionOptions *pOptions 
					&pTransaction					//	/* [out] */ ITransaction **ppTransaction
					) ;
		
	if (FAILED (hr))
	{	
		pTransactionDispenser-> Release();

		CString s;
		s.Format("BeginTransaction failed: %x\n",hr);
		AfxMessageBox(s);
		return;
	}

// create our filerm proxy

	IFileRmPxy * pPxy = NULL;

	hr = CoCreateInstance(CLSID_CoFileRmPxy, NULL, CLSCTX_ALL, IID_IFileRmPxy, (void **)&pPxy);
	ASSERT(hr==S_OK);

	BSTR sFileName = ::SysAllocString(L"FileRmClient");
	ULONG ul = 0;
	
	hr = pPxy -> Init(sFileName, &ul);
	::SysFreeString(sFileName);
	if (FAILED(hr))
	{
		pTransactionDispenser-> Release();
		AfxMessageBox("Failed to initialize the Resource manager");
		return;
	}

//	IUnknown * pUnk = NULL;
	//hr = pTransaction -> QueryInterface(IID_IUnknown, (void **)&pUnk);
	//ASSERT(hr == S_OK);
	hr = pPxy -> EnlistTx((IUnknown *)pTransaction);
//	pUnk -> Release();
	ASSERT(hr == S_OK);
	if (SUCCEEDED(hr))
	{
		// copy the file
		UpdateData(TRUE);

		BSTR sSource = m_sSource.AllocSysString();
		BSTR sDest = m_sDest.AllocSysString();

		hr = pPxy -> FileCopyTx(sSource, sDest);

		::SysFreeString(sSource);
		::SysFreeString(sDest);
		
		if (FAILED(hr))
		{
			pTransaction -> Abort(NULL, FALSE, FALSE);
		}
		else
		{
			pTransaction -> Commit(0,0,0);
		}


	}
		
	// Commit the transaction 
	pPxy -> Release();
	pTransactionDispenser-> Release();
#endif
}

void CFileRmClientDlg::OnCopyDirectory() 
{
#if 0
	CWaitCursor wait;
	IFileRmPxy * pPxy = NULL;
	HRESULT hr;
	hr = CoCreateInstance(CLSID_CoFileRmPxy, NULL, CLSCTX_ALL, IID_IFileRmPxy, (void **)&pPxy);
	ASSERT(hr==S_OK);
	if (SUCCEEDED(hr))
	{
		// copy the file
		UpdateData(TRUE);

		//BSTR sSource = m_sSource.AllocSysString();
		//BSTR sDest = m_sDest.AllocSysString();
		pPxy -> ConfirmCommit(TRUE, (long)GetSafeHwnd());
		hr = pPxy -> CopyDirTx(sSource, sDest);

		::SysFreeString(sSource);
		::SysFreeString(sDest);
		pPxy -> Release();
	}
#endif
}

void CFileRmClientDlg::OnInsertData() 
{
	CWaitCursor wait;
	UpdateData(TRUE);
	m_sMsg.Empty();
	UpdateData(FALSE);
	USES_CONVERSION;
	ICpyImage * pCpyImage;
	CString sDestination = m_sDest;
//
//	make sure the last char in the destination is a "\"
//

	if (sDestination.Right(1) != "\\")
		sDestination += "\\";

	HRESULT hr;
	hr = CoCreateInstance(CLSID_CpyImage, NULL, CLSCTX_ALL, IID_ICpyImage, (void **)&pCpyImage);
	if (FAILED(hr))
	{	
		AfxMessageBox("Failed to Create the CopyImage component (cpyimage.dll).\nMake sure that it is built and properly registered.", MB_ICONSTOP);
		return;
	}


	CString sSourceFile;
	sSourceFile = m_ctlPict.GetPictureFileName();	
	LPSTR p;
	LPSTR q;
	p = sSourceFile.GetBuffer(118);
	q = p+lstrlen(p) - 1;
	while (q != p) // scan backwards
	{
		q--;
		if (*q == '\\')
		{
			q++;
			break;
		}
	}
	
	// q points to the file name


	sDestination += q;
	sSourceFile.ReleaseBuffer();

	BSTR sSource = sSourceFile.AllocSysString();
	BSTR sDest = sDestination.AllocSysString();
	BSTR sDescr = m_sDescription.AllocSysString();
	BSTR sMain = m_sMainColor.AllocSysString();
	BSTR sThem = m_sTheme.AllocSysString();
	BSTR msg;

	// have the middle tier object do some work for us
	hr = pCpyImage -> InsertData(sSource,sDest ,sDescr ,sMain , sThem, &msg);
	
	::SysFreeString(sSource);
	::SysFreeString(sDest);
	::SysFreeString(sDescr);
	::SysFreeString(sMain);
	::SysFreeString(sThem);

	if (hr == S_OK)
	{
		SetDlgItemTextW(GetSafeHwnd(), IDC_MSG, msg);

		if (::MessageBox(GetSafeHwnd(), "Do you wish to commit the tx?", "FileRmClient", MB_YESNO|MB_ICONQUESTION) == IDYES)
			pCpyImage -> SetComplete();
		else
			pCpyImage -> SetAbort();
	}
	else
	{		
		USES_CONVERSION;
		m_sMsg.Format("Tx Aborted!\r\nCause: %s", OLE2T(msg));
		UpdateData(FALSE);
		int nLen = SysStringLen(msg);
		if (nLen != 0)
		{	
			::SysFreeString(msg);
		}
		
		pCpyImage -> SetAbort();
	}

	pCpyImage -> Release();
	

}


BEGIN_EVENTSINK_MAP(CFileRmClientDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CFileRmClientDlg)
	ON_EVENT(CFileRmClientDlg, IDC_PICTURECTL, 1 /* PictureChanged */, OnPictureChanged, VTS_PBSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CFileRmClientDlg::OnPictureChanged(BSTR FAR* PictureFileName) 
{
	m_sImgFileName = *PictureFileName;
	UpdateData(FALSE);
	
}

void CFileRmClientDlg::OnSelectPicture() 
{
	static char BASED_CODE szFilter[] = "All image files (*.bmp, *.wmf; *.gif)|*.bmp;*.gif;*.wmf|Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.giv|Windows Meta files (*.wmf)|*.wmf|All Files (*.*)|*.*||";
 

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDCANCEL)
		return;

	m_sImgFileName = dlg.GetPathName( );
	m_ctlPict.SetPictureFileName(m_sImgFileName);
	UpdateData(FALSE);

	
}

#if 0
void ShowError(HENV henv, HDBC hdbc, HSTMT hstmt)
{
		UCHAR szSqlState[64];
		SDWORD NativeError;
		UCHAR szErr[512];
		SWORD cbErrorMsg;
		SQLError(henv, hdbc, hstmt, szSqlState, &NativeError, szErr, 511, &cbErrorMsg);
		AfxMessageBox((LPCSTR)szErr);
}


{
	RETCODE                  rc = 0;
    RETCODE                  rc1 = 0;
    HENV                     henv = NULL;
    HDBC                     hdbc = NULL;
    HSTMT                    hstmt = NULL;
	long hPxyCon = 0;
    CString sSQL;
	CString sDestination = "c:\\images\\";
	CString sSourceFile;
	LPSTR p, q;

	BSTR sSource;
	BSTR sDest;
	
	CWaitCursor wait;
	
    HRESULT                  hr;
    ITransactionDispenser   *pITransDisp = NULL;
    ITransaction            *pITransaction = NULL;
	USES_CONVERSION;
	UpdateData(TRUE);

	sSourceFile = m_ctlPict.GetPictureFileName();	
	p = sSourceFile.GetBuffer(118);
	q = p+lstrlen(p) - 1;
	while (q != p) // scan backwards
	{
		q--;
		if (*q == '\\')
		{
			q++;
			break;
		}
	}
	
	// q points to the file name


	sDestination += q;
	sSourceFile.ReleaseBuffer();

// create the Proxy
   	IFileRmPxy * pPxy = NULL;

	hr = CoCreateInstance(CLSID_FileRmPxy, NULL, CLSCTX_ALL, IID_IFileRmPxy, (void **)&pPxy);
	ASSERT(hr==S_OK);




    //---------------------------------------------------------------
    //Obtain the transaction dispenser from DTC Proxy
    hr = DtcGetTransactionManager( 0x0,
                                   0x0,
                                   IID_ITransactionDispenser,
                                   0x0,
                                   0x0,
                                   0x0,
                                   (void **) &pITransDisp );

    if (hr != S_OK)
    {
         
        AfxMessageBox("Couldn't get the Tx Dispenser!  Make sure DTC is running!"); 
		goto Exit;
    }
    


    //---------------------------------------------------------------
    //Obtain a new transaction from the dispenser
    hr = pITransDisp->BeginTransaction( NULL,
                                        ISOLATIONLEVEL_ISOLATED,
                                        0x0,
                                        NULL,
                                        &pITransaction );


	pITransDisp -> Release();
	pITransDisp = NULL;
    if (hr != S_OK)
    {
         
         goto Exit;
    }
    

    /* Allocate the Environment handle */
    rc = SQLAllocEnv( &henv );
    if( rc )
    {
        
        goto Exit;
    }
    

    /* Allocate the Connection handle */
    rc = SQLAllocConnect( henv, &hdbc );
    if( rc )
    {
        
        goto Exit;
    }
    

	SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 5);

    /* Establish the database connection */
    rc = SQLConnect( hdbc, (UCHAR *)"FileRmTest", SQL_NTS, 
							(UCHAR *)"sa", SQL_NTS,
							(UCHAR *)"", SQL_NTS );

    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
        //printError( henv, hdbc, hstmt, SqlState );
        goto Exit;
    }
#if 0
	rc = SQLSetConnectOption( hdbc, SQL_TXN_ISOLATION_OPTION, (DWORD )SQL_TXN_READ_UNCOMMITTED);    
	if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     
		UCHAR szSqlState[64];
		SDWORD NativeError;
		UCHAR szErr[512];
		SWORD cbErrorMsg;
		SQLError(henv, hdbc, hstmt, szSqlState, &NativeError, szErr, 511, &cbErrorMsg);

		/* note: use SQLError from here on */
        //printError( henv, hdbc, hstmt, SqlState );
        goto Exit;
    }
#endif
	rc = SQLSetConnectOption( hdbc, SQL_COPT_SS_ENLIST_IN_DTC, (DWORD )pITransaction );
	if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     
		
		ShowError(henv, hdbc, hstmt);
		goto Exit;
    }

	rc = SQLSetConnectOption( hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
        ShowError(henv, hdbc, hstmt);
		goto Exit;
    }
    
    
	
	
	hr = pPxy -> Connect(&hPxyCon);
	_ASSERTE(hr == S_OK);
	hr = pPxy -> Enlist(hPxyCon, (IUnknown *)pITransaction);
	_ASSERTE(hr == S_OK);

   

    /* Allocate the statement handle */
    rc = SQLAllocStmt( hdbc, &hstmt );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
        ShowError(henv, hdbc, hstmt);
        goto Exit;
    }

     /* Execute to Insert */
	
	sSQL.Format("insert into image values ('%s', '%s', '%s', '%s')", 
				m_sDescription, m_sMainColor, m_sTheme, sDestination);

// insert the row into the database
    rc = SQLExecDirect( hstmt, ( UCHAR * )(LPCSTR)sSQL, SQL_NTS );	
	
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
		ShowError(henv, hdbc, hstmt);
		pITransaction -> Abort(NULL, FALSE, FALSE);
        goto Exit;
    }

	sSource = ::SysAllocString(T2OLE(sSourceFile));
	sDest = ::SysAllocString(T2OLE(sDestination));
    
// copy the image to the images directory
	
	hr = pPxy -> CopyFileTx(hPxyCon, sSource, sDest, TRUE);
	::SysFreeString(sSource);
	::SysFreeString(sDest);
	if (FAILED(hr))
	{
		pITransaction -> Abort(NULL, FALSE, FALSE);
		goto Exit;
	}
   
	/* Commit the DTC transaction */
	if (::MessageBox(GetSafeHwnd(), "Commit Transaction?", "File Resource Manager", MB_YESNO) == IDYES)
        hr = pITransaction->Commit( FALSE, XACTTC_SYNC_PHASEONE, 0x0 );
	else
		hr = pITransaction->Abort( 0,0,0);

    if (hr != S_OK)
    {
        
        goto Exit;
    }

    /* Free the statement handle */
    rc = SQLFreeStmt( hstmt, SQL_DROP );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
        goto Exit;
    }

    
    Exit:
	if (pITransaction)
	   pITransaction -> Release();

	if (pPxy)
	{
		hr = pPxy -> Disconnect(hPxyCon);
	    pPxy -> Release();
	}

    if (hdbc)
	{
		rc1 = SQLDisconnect( hdbc );
	   SQLFreeConnect( hdbc );
       SQLFreeEnv( henv );
	}

     
	if( rc1 != SQL_SUCCESS && rc1 != SQL_SUCCESS_WITH_INFO )
       {
		// print message
	   }

    
    
       if( rc == 0 )
       {
		   // success
       }
       else
       {
		   // failed
	   }
	
}
#endif
