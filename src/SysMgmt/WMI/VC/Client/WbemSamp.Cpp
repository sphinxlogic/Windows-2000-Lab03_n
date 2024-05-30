// **************************************************************************
// Copyright (c) 1997-1999 Microsoft Corporation.
//
// File:  HMMSamp.cpp
//
// Description:
//	This file implements the CHMMSampleApp class which 
//		is the main class for the tutorial.
// 
// History:
//
// **************************************************************************


#include "stdafx.h"
#include <objbase.h>
#include "WBEMSamp.h"
#include "WBEMSampDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHMMSampleApp

BEGIN_MESSAGE_MAP(CHMMSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CHMMSampleApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMMSampleApp construction

CHMMSampleApp::CHMMSampleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHMMSampleApp object

CHMMSampleApp theApp;

// **************************************************************************
//
//	CHMMSampleApp::InitSecurity()
//
// Description:
//		Initializes COM security if DCOM is installed.
// Parameters:
//		None.
//
// Returns:
//		nothing.
//
// Globals accessed:
//		None.
//
// Globals modified:
//		None.
//
//===========================================================================
// definition for call CoInitializeSecurity indirectly.
HRESULT (STDAPICALLTYPE *g_pfnCoInitializeSecurity)(PSECURITY_DESCRIPTOR pVoid,
													DWORD cAuthSvc,
													SOLE_AUTHENTICATION_SERVICE * asAuthSvc, 
													void * pReserved1,
													DWORD dwAuthnLevel,
													DWORD dwImpLevel,
													RPC_AUTH_IDENTITY_HANDLE pAuthInfo,
													DWORD dwCapabilities,
													void * pvReserved2 );

void CHMMSampleApp::InitSecurity(void)
{
    UINT    uSize;
    BOOL    bRetCode = FALSE;

	// find the system directory.
    LPTSTR   pszSysDir = new TCHAR[MAX_PATH + 10];

    if(pszSysDir == NULL)
        return;

    uSize = GetSystemDirectory(pszSysDir, MAX_PATH);

    if(uSize > MAX_PATH) 
	{
        delete[] pszSysDir;
        pszSysDir = new TCHAR[ uSize +10 ];
        if(pszSysDir == NULL)
            return;
        uSize = GetSystemDirectory(pszSysDir, uSize);
    }

	// manually load the ole32.dll and see if CoInitializeSecurity() exists. This routine wont exist
	// on win95 OS's that dont have DCOM installed separately. If this routine doesn't exist, the 
	// async routines in this sample wont work because of mismatched security level problems. The
	// synchronous techniques will still work.
    lstrcat(pszSysDir, _T("\\ole32.dll"));

    HINSTANCE hOle32 = LoadLibraryEx(pszSysDir, NULL, 0);
    delete[] pszSysDir;

    if(hOle32 != NULL) 
	{
        (FARPROC&)g_pfnCoInitializeSecurity = GetProcAddress(hOle32, "CoInitializeSecurity");

		// if it exports CoInitializeSecurity then DCOM is installed.
        if(g_pfnCoInitializeSecurity != NULL) 
		{
			// NOTE: This is needed to work around a security problem
			// when using IWBEMObjectSink. The sink wont normally accept
			// calls when the caller wont identify themselves. This
			// adjusts that process.
			HRESULT hres = g_pfnCoInitializeSecurity(NULL, -1, NULL, NULL, 
														RPC_C_AUTHN_LEVEL_CONNECT, 
														RPC_C_IMP_LEVEL_IDENTIFY, 
														NULL, 0, 0);

        } 
        FreeLibrary(hOle32);
    }
}
// **************************************************************************
//
//	CHMMSampleApp::InitInstance()
//
// Description:
//		Initializes COM then initializes security in a way that allows
//		objectSink to be called.
// Parameters:
//		None.
//
// Returns:
//		whether or not it initialized everything.
//
// Globals accessed:
//		None.
//
// Globals modified:
//		None.
//
//===========================================================================
BOOL CHMMSampleApp::InitInstance()
{
	// OLE initialization. This is 'lighter' than OleInitialize()
	//  which also setups DnD, etc.
	if(SUCCEEDED(CoInitialize(NULL))) 
	{
		InitSecurity();
	}
	else // didnt CoInitialize()
	{
		AfxMessageBox(_T("CoInitialize Failed"));
		return FALSE;
	} // endif OleInitialize()

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CWBEMSampleDlg dlg;
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

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
// **************************************************************************
//
//	CHMMSampleApp::ExitInstance()
//
// Description:
//		Uninitialize COM.
// Parameters:
//		None.
//
// Returns:
//		the value of the base class's routine.
//
// Globals accessed:
//		None.
//
// Globals modified:
//		None.
//
//===========================================================================
int CHMMSampleApp::ExitInstance()
{
	CoUninitialize();

	return CWinApp::ExitInstance();
}


