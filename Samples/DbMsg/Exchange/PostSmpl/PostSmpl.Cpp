//=========================================================================
// PostSmpl.CPP
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
// 
//
// Purpose:
//     Defines the class behaviors for the application.
//
//=========================================================================


#include "stdafx.h"
#include "PostSmpl.h"

#include "MainFrm.h"
#include "PostDoc.h"
#include "PostView.h"
#include "PostData.h"
#include "SummInfo.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// {5BE4EF30-71F7-11CF-A352-00AA006C41F8}
static const CLSID clsid =
{ 0x5be4ef30, 0x71f7, 0x11cf, { 0xa3, 0x52, 0x0, 0xaa, 0x0, 0x6c, 0x41, 0xf8 } };


/////////////////////////////////////////////////////////////////////////////
// CPostSmplApp

BEGIN_MESSAGE_MAP(CPostSmplApp, CWinApp)
	//{{AFX_MSG_MAP(CPostSmplApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_POSTMSG, OnFilePostmsg)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_SUM_INFO, OnFileSumInfo)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostSmplApp construction

CPostSmplApp::CPostSmplApp()
{
	//  add construction code here,
	// Place all significant initialization in InitInstance
	m_bEmbedded = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPostSmplApp object

CPostSmplApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPostSmplApp initialization

BOOL CPostSmplApp::InitInstance()
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

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPostSmplDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPostSmplView));
	AddDocTemplate(pDocTemplate);
	
	// enable file manager drag/drop and DDE Execute open
   EnableShellOpen();
   RegisterShellFileTypes();

   if (FAILED(PostData.HrInitialize()))
	{	
		#ifdef _DEBUG
		afxDump << "Logon failure\n" ;
		#endif
		return FALSE;
	}
	
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	//If some filename was passed in command line, then display its contents in view
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen && cmdInfo.m_strFileName)
	{
		if (cmdInfo.m_bRunEmbedded)
			m_bEmbedded = TRUE;

		//Update all views		
		POSITION nPos = pDocTemplate->GetFirstDocPosition(); 
		CDocument *pDoc = pDocTemplate->GetNextDoc(nPos);
		pDoc->UpdateAllViews(NULL);
	}

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
void CPostSmplApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPostSmplApp commands



int CPostSmplApp::ExitInstance() 
{
	//  Add your specialized code here and/or call the base class
	PostData.HrUninitialize();
	m_lpBuffer.Empty();
	return CWinApp::ExitInstance();
}


void CPostSmplApp::OnFilePostmsg() 
{
	//  Add your command handler code here
	PostData.CreateAndPostMessage();
}


void CPostSmplApp::OnFileOpen() 
{
	//  Add your command handler code here
	CWinApp::OnFileOpen();
	
}

void CPostSmplApp::OnFileNew() 
{
	//  Add your command handler code here
	m_lpBuffer				= TEXT("");

	//clear up the variables related to document.
	PostData.szFile			 = TEXT("");
	PostData.szFileTitle	 = TEXT("");
	PostData.m_psTitle		 = TEXT("");
	PostData.m_psAuthor		 = TEXT("");
	PostData.m_psComments	 = TEXT("");
	PostData.m_psKeywords	 = TEXT("");
	PostData.m_psSubject	 = TEXT("");
	PostData.m_psTitle		 = TEXT("");

	CWinApp::OnFileNew();
}
					 
void CPostSmplApp::OnFileSumInfo() 
{
	// TODO: Add your command handler code here
	CSummInfo sumDlg;

	sumDlg.m_pstitle   	 = 	 	PostData.m_psTitle;     
	sumDlg.m_psauthor  	 = 	 	PostData.m_psAuthor;    
	sumDlg.m_pscomments	 = 	 	PostData.m_psComments;  
	sumDlg.m_psdirectory = 	 	PostData.szFile; 
	sumDlg.m_psfilename	 = 	 	PostData.szFileTitle;  
	sumDlg.m_pskeywords	 = 	 	PostData.m_psKeywords;  
	sumDlg.m_pssubject 	 = 	 	PostData.m_psSubject;   
	sumDlg.m_pstitle   	 = 	 	PostData.m_psTitle;     


	if (IDOK == sumDlg.DoModal())
	{
		PostData.m_psTitle       = sumDlg.m_pstitle;
		PostData.m_psAuthor      = sumDlg.m_psauthor;
		PostData.m_psComments    = sumDlg.m_pscomments;
		PostData.m_psKeywords    = sumDlg.m_pskeywords;
		PostData.m_psSubject     = sumDlg.m_pssubject;
		PostData.m_psTitle       = sumDlg.m_pstitle;
	}
}