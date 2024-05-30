// IvrExplorer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "IvrExplorerDoc.h"
#include "NewApplication.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerApp

BEGIN_MESSAGE_MAP(CIvrExplorerApp, CWinApp)
	//{{AFX_MSG_MAP(CIvrExplorerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_CONNECT, OnFileConnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_CONNECT, OnUpdateFileConnect)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerApp construction

CIvrExplorerApp::CIvrExplorerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
    m_numberOfRows = 1000;
    m_fConnected = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIvrExplorerApp object

CIvrExplorerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerApp initialization

BOOL CIvrExplorerApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_IVREXPTYPE,
		RUNTIME_CLASS(CIvrExplorerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CIvrExplorerView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CIvrExplorerApp::ExitInstance()
{
    if (m_pIvr)
        m_pIvr->Release();
    
    CoUninitialize();

    return CWinApp::ExitInstance();
}

BOOL
CIvrExplorerApp::InitIvr()
{
    HRESULT hr;

    CoInitialize(NULL);

    hr = CoCreateInstance(CLSID_WebIvrService,
                          NULL,
                          CLSCTX_LOCAL_SERVER,
                          IID_IWebIvrService,
                          (void **)&m_pIvr);

    if (hr != 0)
    {
        return FALSE;
    }

    m_fConnected = TRUE;

    return TRUE;
}

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
		// No message handlers
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

// App command to run the dialog
void CIvrExplorerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerApp commands

void CIvrExplorerApp::OnFileNew() 
{
    HRESULT      hr;
    CString      cs;
    CDocument   *pDoc;
    POSITION     pos;
    CDocTemplate       *pDocTemp;
    CIvrExplorerView   *pIvrExp;

    //
    // Pop the new application dialog box.
    //
    CNewApplication aNewApp;
	aNewApp.DoModal();

    //
    // If an empty string return.
    //
    if (lstrlen(aNewApp.m_appName) == 0)
    {
        return;
    }    

    BeginWaitCursor();

	//
    // Create the new window.
    //
    CWinApp::OnFileNew();

    //
    // Get a pointer to the document template (we have only one).
    //
    pos = GetFirstDocTemplatePosition();
    pDocTemp = GetNextDocTemplate(pos);

    //
    // Iterating over open documents. We are interesting the document that its
    // title is still IvrExp...
    //
	pos = pDocTemp->GetFirstDocPosition();

    do
    {
        pDoc = pDocTemp->GetNextDoc(pos);
        cs = pDoc->GetTitle();

    }while (_tcsncmp(cs,L"IvrExp", 6));

    //
    // Get the pointer to the class (which inherits from CView).
    //
    pos = pDoc->GetFirstViewPosition();
    pIvrExp = (CIvrExplorerView *)pDoc->GetNextView(pos);

    //
    // Connect to the IVR application.
    //
    hr = pIvrExp->Connect(aNewApp.m_appName);
    if (hr != 0)
    {
        //
        // Kill the new window.
        //
        pIvrExp->GetParentFrame()->DestroyWindow();
    }

    EndWaitCursor();
}

void CIvrExplorerApp::OnFileConnect() 
{
    CString cs;

    BeginWaitCursor();

	//
    // Create the service
    //
    if (!InitIvr())
    {
        EndWaitCursor();
        return;
    }

    EndWaitCursor();

    //
    // We are now connected. enable OnFileNew.
    //
    m_pMainWnd->GetWindowText(cs);
    cs += " - Connected";
    m_pMainWnd->SetWindowText(cs);

    CMenu* pmenu = m_pMainWnd->GetMenu();
    UINT u = pmenu->EnableMenuItem(ID_FILE_CONNECT, MF_DISABLED);
}

void CIvrExplorerApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_fConnected ? TRUE : FALSE);
}

void CIvrExplorerApp::OnUpdateFileConnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_fConnected ? FALSE : TRUE);	
}
