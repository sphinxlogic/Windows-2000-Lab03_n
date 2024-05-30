/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/





// MFCIEEvtSpyDlg.cpp : implementation file
//
// This source code is provided as-is, without warranty.
//
// Created by S. R.
// Microsoft Developer Support - Internet Client SDK
/////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxctl.h>
#include <comdef.h>
#include "MFCIEEvtSpy.h"
#include "MFCIEEvtSpyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// Manually added event sink map
BEGIN_EVENTSINK_MAP(CMFCIEEvtSpyDlg, CDialog)
	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_BEFORENAVIGATE2,
            OnBeforeNavigate2, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT
            VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_COMMANDSTATECHANGE,
            OnCommandStateChange, VTS_I4 VTS_BOOL)

   ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_DOCUMENTCOMPLETE,
            OnDocumentComplete, VTS_DISPATCH VTS_PVARIANT)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_DOWNLOADCOMPLETE,
            OnDownloadComplete, VTS_NONE)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_NEWWINDOW2,
            OnNewWindow2, VTS_DISPATCH VTS_PBOOL)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_NAVIGATECOMPLETE2,
            OnNavigateComplete2, VTS_DISPATCH VTS_PVARIANT)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_ONQUIT, OnQuit, VTS_NONE)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_PROGRESSCHANGE,
            OnProgressChange, VTS_I4 VTS_I4)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_STATUSTEXTCHANGE,
            OnStatusTextChange, VTS_BSTR)

	ON_EVENT(CMFCIEEvtSpyDlg, IDC_WEBBROWSER, DISPID_TITLECHANGE,
            OnTitleChange, VTS_BSTR)
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCIEEvtSpyDlg dialog

CMFCIEEvtSpyDlg::CMFCIEEvtSpyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCIEEvtSpyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCIEEvtSpyDlg)
	m_strAddress = _T("");
	//}}AFX_DATA_INIT

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   m_dwCookie = 0;

   m_pConnectionPoint = NULL;
   m_pIE = NULL;
   m_pIE4Events = new CIE4Events(this);
}

CMFCIEEvtSpyDlg::~CMFCIEEvtSpyDlg()
{
   delete m_pIE4Events;
}

void CMFCIEEvtSpyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCIEEvtSpyDlg)
	DDX_Control(pDX, IDC_STARTIE, m_btnStartIE);
	DDX_Control(pDX, IDC_IE4_EVENTS_LST, m_lstIE4Events);
	DDX_Control(pDX, IDC_WB_EVENTS_LST, m_lstWBEvents);
	DDX_Control(pDX, IDC_WEBBROWSER, m_webBrowser);
	DDX_Text(pDX, IDC_ADDRESS_EDITBOX, m_strAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCIEEvtSpyDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCIEEvtSpyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTIE, OnStartIE)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CLEAR_LISTBOXES, OnClearListboxes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCIEEvtSpyDlg message handlers

BOOL CMFCIEEvtSpyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Navigate to MSJ
   COleVariant vtEmpty;
	m_strAddress.LoadString(IDS_MSJ_HOME_PAGE);
   m_webBrowser.Navigate(m_strAddress, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
	
   m_nIELstBoxHorizExtent = m_lstIE4Events.GetHorizontalExtent();
   m_nWBLstBoxHorizExtent = m_lstIE4Events.GetHorizontalExtent();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCIEEvtSpyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCIEEvtSpyDlg::OnPaint() 
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
//
// This source code is provided as-is, without warranty.
//
// Created by S. R.
///////////////////////////////////////////////////////////

HCURSOR CMFCIEEvtSpyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCIEEvtSpyDlg::OnStartIE() 
{
   if (m_pIE == NULL)  // Can only start one instance
   {
	   // Create an instance of Internet Explorer 4.0
      HRESULT hr = CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER, 
                                    IID_IWebBrowser2, (void**)&m_pIE);
      if (SUCCEEDED(hr))
      {
         // Set up the event sink
         BOOL bAdvised = AfxConnectionAdvise(m_pIE, DIID_DWebBrowserEvents2,
                                             m_pIE4Events->GetInterface(&IID_IUnknown),
                                             TRUE, &m_dwCookie);

         TRACE("Advise for DWebBrowserEvents2 %s\n", bAdvised ? "succeeded" : "failed");

         m_btnStartIE.EnableWindow(FALSE);

         // Make IE4 visible
         m_pIE->put_Visible(VARIANT_TRUE);

         CString strMsjHome;
         strMsjHome.LoadString(IDS_MSJ_HOME_PAGE);

         COleVariant vtEmpty;
         m_pIE->Navigate(strMsjHome.AllocSysString(), &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
      }
   }
}

void CMFCIEEvtSpyDlg::OnExit() 
{
   EndDialog(0);
}

void CMFCIEEvtSpyDlg::OnGo() 
{
   UpdateData(TRUE);

   COleVariant vtEmpty;
   m_webBrowser.Navigate(m_strAddress, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
}

void CMFCIEEvtSpyDlg::OnDestroy() 
{
   ShutDownIE4EventSink();

   if (m_pIE)
   {
      m_pIE->Quit();
      m_pIE->Release();
   }

	CDialog::OnDestroy();
}

void CMFCIEEvtSpyDlg::ShutDownIE4EventSink()
{
   if (m_dwCookie)
   {
      BOOL bUnadvised = AfxConnectionUnadvise(m_pIE, DIID_DWebBrowserEvents2,
                                              m_pIE4Events->GetInterface(&IID_IUnknown),
                                              TRUE, m_dwCookie);

      TRACE("Unadvise for DWebBrowserEvents2 %s\n", bUnadvised ? "succeeded" : "failed");
      m_dwCookie = 0;
   }
}

void CMFCIEEvtSpyDlg::AddEventToList(ListBoxType lst, CString strEvent)
{
   SIZE size;

   //
   // Set the Horizontal extent so that the horizontal scroll bar will be shown.
   //
   switch(lst)
   {
   case IE4ListBox:
   	m_lstIE4Events.AddString(strEvent);
      GetTextExtentPoint32(m_lstIE4Events.GetDC()->m_hDC, strEvent, strEvent.GetLength(), &size);

      if (size.cx > m_nIELstBoxHorizExtent)
         m_nIELstBoxHorizExtent = size.cx;
   
      m_lstIE4Events.SetHorizontalExtent(m_nIELstBoxHorizExtent);

      break;

   case WBListBox:
   	m_lstWBEvents.AddString(strEvent);
      GetTextExtentPoint32(m_lstWBEvents.GetDC()->m_hDC, strEvent, strEvent.GetLength(), &size);

      if (size.cx > m_nWBLstBoxHorizExtent)
         m_nWBLstBoxHorizExtent = size.cx;
   
      m_lstWBEvents.SetHorizontalExtent(m_nWBLstBoxHorizExtent);

      break;

   default:
      return;
   }
}

void CMFCIEEvtSpyDlg::OnIE4Quit()
{
   m_btnStartIE.EnableWindow(TRUE);

   ShutDownIE4EventSink();

   if (m_pIE)
   {
      m_pIE->Release();
      m_pIE = NULL;
   }
}

void CMFCIEEvtSpyDlg::OnClearListboxes() 
{
	m_lstIE4Events.ResetContent();
	m_lstWBEvents.ResetContent();

   m_nIELstBoxHorizExtent = 0;
   m_nWBLstBoxHorizExtent = 0;
}

/////////////////////////////////////////////////////////////////////////////
// WebBrowser event handlers
void CMFCIEEvtSpyDlg::OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
   USES_CONVERSION;

   CString strEvt("BeforeNavigate2: ");
   strEvt += OLE2T(URL->bstrVal);

   AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnCommandStateChange(long lCommand, BOOL bEnable)
{
   CString strEvt;
   strEvt.Format("CommandStateChange: Command = %ld  Enable = %d", lCommand, bEnable);

   AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
   USES_CONVERSION;

   CString strEvt("DocumentComplete: ");
   strEvt += OLE2T(URL->bstrVal);

   AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnDownloadComplete() 
{
   AddEventToList(WBListBox, "DownloadComplete");
}

void CMFCIEEvtSpyDlg::OnNavigateComplete2(LPDISPATCH pDisp, VARIANT* URL)
{
   USES_CONVERSION;

   CString strEvt("NavigateComplete2: ");
   strEvt += OLE2T(URL->bstrVal);

   AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{
	AddEventToList(WBListBox, "NewWindow2");
}

void CMFCIEEvtSpyDlg::OnProgressChange(long lProgress, long lProgressMax)
{
   CString strEvt;
   strEvt.Format("ProgressChange: Progress = %ld  ProgressMax = %ld", lProgress, lProgressMax);

	AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnStatusTextChange(LPCTSTR lpszText) 
{
   CString strEvt("StatusTextChange: ");
   strEvt += lpszText;

   AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnTitleChange(LPCTSTR lpszText) 
{
   CString strEvt("TitleChange: ");
   strEvt += lpszText;

   AddEventToList(WBListBox, strEvt);
}

void CMFCIEEvtSpyDlg::OnQuit()
{
	AddEventToList(WBListBox, "Quit");
}

