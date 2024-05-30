/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.


Module Name:

    SCardTestApp

Abstract:

        CWinApp implementation file for the smart card test/example program.
        This application implements a OLE container to test the smart card
        vendor wrapper COM object and associated Smart Card resources.

Environment:

    Win32, C++ w/Exceptions, COM/OLE

Revision History:

Notes:


--*/


/////////////////////////////////////////////////////////////////////////////
//
// Includes
//

#include "preapp.h"
#include "SCardTst.h"
#include "SCardDg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
// CSCardTestApp Message map
//

BEGIN_MESSAGE_MAP(CSCardTestApp, CWinApp)
        //{{AFX_MSG_MAP(CSCardTestApp)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG
        ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


/*++

CSCardTestApp::CSCardTestApp()

        Constructor for the Test application object

Arguments:

        none

Return Value:


Author:

--*/

CSCardTestApp::CSCardTestApp()
{
        /////////////////////////////////////////////////////////////////////////
        // NOTE:
        // Add any construction specific code here.
        // Most significant initialization should be placed in InitInstance.
        //
}

/////////////////////////////////////////////////////////////////////////////
//
//      Create CCardTestApp
//

CSCardTestApp theApp;


/*++

CSCardTestApp::InitInstance()

        Override to perform Windows instance initializatio for the dialog.

Arguments:

        none

Return Value:

        Nonzero if initialization is sucessful, zero (0) otherwise

Author:

--*/

BOOL CSCardTestApp::InitInstance()
{
        // locals
        BOOL    bReturn = FALSE;

        ////////////////////////////////////////////////////////////////////////
        //
        // Allow ActiveX/COM within the dialog.
        //
        AfxEnableControlContainer();

        /////////////////////////////////////////////////////////////////////////
        //
        // Standard initialization items
        // NOTE:
        // If you are not using these features and wish to reduce the size
        // of your final executable, you should remove those items which you
        // do not need
        //

#ifdef _AFXDLL
        Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
        Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

        ////////////////////////////////////////////////////////////////////////
        //
        // Since this is a dialog based app, create the dialog object, save window
        // handle, and open the dialog
        //
        CSCardTestDlg dlg;
        m_pMainWnd = &dlg;
        int nResponse = dlg.DoModal();

        /////////////////////////////////////////////////////////////////////////\
        //
        // Process the Dialog IDOK and IDCANCEL messages
        //
        if (nResponse == IDOK)
        {
                ///////////////////////////////////////////////////////////////////
                //
                // Place code here to handle when the dialog is dismissed with OK
                //
        }
        else if (nResponse == IDCANCEL)
        {
                /////////////////////////////////////////////////////////////////////
                //
                // Place code here to handle when the dialog is dismissed with Cancel
                //
        }

        ///////////////////////////////////////////////////////////////////////////
        //
        // Return value
        //
        return bReturn;
}
