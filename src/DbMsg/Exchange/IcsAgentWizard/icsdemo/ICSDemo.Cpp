// ICSDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ICSDemo.h"
#include "ICSDemoDlg.h"
#include "MAPIApp.h"

#include "TraceBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------------------------------------------------------------

//
// CICSDemoApp
//

BEGIN_MESSAGE_MAP(CICSDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CICSDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

//----------------------------------------------------------------------

//
// CICSDemoApp construction
//

CICSDemoApp::CICSDemoApp()
{
	m_lpMAPIApp = NULL;	
}

//----------------------------------------------------------------------

//
// The one and only CICSDemoApp object
//

CICSDemoApp theApp;

//----------------------------------------------------------------------

//
// The one and only CTraceBox object
//

CTraceBox	theTraceBox;

//----------------------------------------------------------------------

//
// CICSDemoApp initialization
//

BOOL CICSDemoApp::InitInstance()
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

	//
	//	Initialize MAPI by creating a new CMAPIApp object.
	//

	m_lpMAPIApp = new CMAPIApp;

	if (HR_FAILED(m_lpMAPIApp->Status()))
	{
		ShowErrorMessage("CMAPIApp construction",m_lpMAPIApp->Status());
	}
	else
	{
		//
		//	Show the main dialog.
		//

		CICSDemoDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}

	//
	//	Delete the CMAPIApp object, thereby shutting down
	//	MAPI.
	//
	
	delete m_lpMAPIApp;
	m_lpMAPIApp = NULL;

	return FALSE;
}

//----------------------------------------------------------------------

void CICSDemoApp::ShowErrorMessage(LPCSTR lpszInfoString,HRESULT hResult)
{
	CString		ErrorString;
	LPCSTR		strErrStr;

	//
	//	Look up the string equivalent of hResult. Note that
	//	TranslateErrorCode returns NULL if it can't find
	//	a translation for hResult.
	//

	if (m_lpMAPIApp != NULL)
		strErrStr = m_lpMAPIApp->TranslateErrorCode(hResult);
	else
		strErrStr = NULL;

	//
	//	If no string equivalent of hResult is available,
	//	then display hResult as a hex value.
	//

	if (strErrStr != NULL)
	{
		if (lpszInfoString != NULL)
			ErrorString.Format("%s [%s]",lpszInfoString,strErrStr);
		else
			ErrorString.Format("[%s]",strErrStr);
	}
	else
	{
		if (lpszInfoString != NULL)
			ErrorString.Format("%s [%08X]",lpszInfoString,hResult);
		else
			ErrorString.Format("[%08X]",hResult);
	}

	::MessageBox(0,ErrorString,"ERROR",MB_OK | MB_ICONINFORMATION);
}
