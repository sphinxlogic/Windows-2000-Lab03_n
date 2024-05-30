//--mbxserv.cpp---------------------------------------------------------------
//
// implementation of the CMbxServApp class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "mbxserv.h"
#include "oditem.h"
#include "odlist.h"
#include "dchkmail.h"

#include "initguid.h"
#include "mapiguid.h"
#include "edkguid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SERVER_STORE_MASK   0x04

/////////////////////////////////////////////////////////////////////////////
// CMbxServApp

BEGIN_MESSAGE_MAP(CMbxServApp, CWinApp)
	//{{AFX_MSG_MAP(CMbxServApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbxServApp construction

CMbxServApp::CMbxServApp()
{
	m_lpSession = NULL;
	m_lpMDB		= NULL;
	m_lpAddrBook= NULL;
	m_lpGAL		= NULL;
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMbxServApp object

CMbxServApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMbxServApp initialization

BOOL CMbxServApp::InitInstance()
{
	char szMsg[255];

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    HRESULT hr;
	ULONG           ulObjType;
    ULONG           cbeid;
    LPENTRYID       lpeid = NULL;

	hr = MAPIInitialize (NULL);

    if (FAILED(hr))
    {
        AfxMessageBox ("MAPIInitialize() failed");
        return FALSE;
    }

	hr = (HRESULT) MAPILogonEx( 
			0, 
			NULL,           // lpszProfileName; let the user pick
			NULL,
			MAPI_NO_MAIL | MAPI_NEW_SESSION | MAPI_LOGON_UI, 
			&m_lpSession);

    if (FAILED(hr))
    {
        AfxMessageBox ("Could not logon to this profile.");
        return FALSE;
    }

    // Get the entry ID of the Exchange message store. We can't use default store,
    // as it may be a PST.
	ASSERT_IUNKNOWN_PTR (m_lpSession, "Invalid m_lpSession");


    hr = HrOpenExchangePrivateStore(m_lpSession, &m_lpMDB);

	if (FAILED(hr))
	{
		sprintf (szMsg, "Could not open exchange message store (0x%x)", hr);
		AfxMessageBox (szMsg);
		return FALSE;
	}

    ASSERT_IUNKNOWN_PTR (m_lpMDB, "Invalid m_lpMDB");

	hr = m_lpSession->OpenAddressBook (0, NULL, AB_NO_DIALOG, &m_lpAddrBook);

    if (FAILED(hr))
    {
        AfxMessageBox ("Could not open address book.");
        return FALSE;
    }
	
	hr = HrFindExchangeGlobalAddressList (m_lpAddrBook, &cbeid, &lpeid);

    if (FAILED(hr))
    {
        AfxMessageBox ("Could not find exchange global address list.");
        return FALSE;
    }

	hr = m_lpSession->OpenEntry (cbeid, lpeid, NULL, MAPI_BEST_ACCESS, &ulObjType, (LPUNKNOWN FAR *)&m_lpGAL);

    if (FAILED(hr))
    {
        AfxMessageBox ("Could not open exchange global address list.");
        return FALSE;
    }

    ASSERT_IUNKNOWN_PTR (m_lpGAL, "Invalid m_lpGAL");

	CCheckMailDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_lpGAL = m_lpGAL;
	dlg.m_lpSession = m_lpSession;
	dlg.m_lpMDB = m_lpMDB;
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

int CMbxServApp::ExitInstance() 
{
	if (m_lpSession)
	{
		m_lpSession->Logoff(0,0,0);
		ULRELEASE(m_lpSession);
	}

	ULRELEASE(m_lpMDB);
	ULRELEASE(m_lpAddrBook);
	ULRELEASE(m_lpGAL);

	MAPIUninitialize();
	
	return CWinApp::ExitInstance();
}
