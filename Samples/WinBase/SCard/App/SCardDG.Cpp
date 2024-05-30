/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.


Module Name:

    CSCardTestDlg
        CAboutDlg

Abstract:

        CSCardTestDlg object implementation file. It creates a com vendor
        g_Wrapper object to interact with a smart card. Also contains the
        CAboutDlg (about box) class and implementation.

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
#include "SCardWrp.h"

// Declare Simple global g_Wrapper object
CSCardWrapper   g_Wrapper;

// Used for parameters
WCHAR g_wszReaderName[] = L"Bull CP8 Transac 0";
WCHAR g_wszFilename[] = L"3F00";

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
// CAboutDlg dialog used for application about box
//

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

        //////////////////////////////////////////////////////////////////////////
        //
        // Dialog Data exchange member varialbe declaration
        //
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        //////////////////////////////////////////////////////////////////////////
        //
        // Virtual method overrides
        //
        //{{AFX_VIRTUAL(CAboutDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

protected:
        // CAboutDlg Implementation

        /////////////////////////////////////////////////////////////////////////
        //
        // Dialog message map
        //
        //{{AFX_MSG(CAboutDlg)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};


/*++

CAboutDlg::CAboutDlg()

        Constructor for the about dialog

Arguments:

        none

Return Value:


Author:

--*/

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        ////////////////////////////////////////////////////////////////////////
        //
        // Dialog Data Exchange member variable initialization
        //
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}


/*++

CAboutDlg::DoDataExchange()

        Method allows the exchange and validation of dialog data

Arguments:

        pDX - pointer to CDataExchange object

Return Value:


Author:

--*/

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

//////////////////////////////////////////////////////////////////////////////
//
// Dialog message map
//

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
                // No message handlers
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
// CSCardTestDlg dialog
//


/*++

CCardTstDlg::CCardTstDlg()

        Constructor for the card test dialog gui

Arguments:

        none

Return Value:


Author:

--*/

CSCardTestDlg::CSCardTestDlg(CWnd* pParent /*=NULL*/)
        : CDialog(CSCardTestDlg::IDD, pParent)
{

        ////////////////////////////////////////////////////////////////////////
        //
        // Dialog Data Exchange member variable initialization
        //
        //{{AFX_DATA_INIT(CSCardTestDlg)
        //}}AFX_DATA_INIT

        // load the application icon
        // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
        m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


/*++

CCardTstDlg::DoDataExchange()

        Method allows the exchange and validation of dialog data

Arguments:

        pDX - pointer to CDataExchange object

Return Value:


Author:

--*/

void CSCardTestDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CSCardTestDlg)
        DDX_Control(pDX, IDC_SCARD_STATUS, m_editICCStatus);
        DDX_Control(pDX, IDC_COM_STATUS, m_editComStatus);
        DDX_Control(pDX, IDC_REQUEST_LIST, m_cbRequestList);
        //}}AFX_DATA_MAP
}


//////////////////////////////////////////////////////////////////////////////
//
// Dialog message map
//

BEGIN_MESSAGE_MAP(CSCardTestDlg, CDialog)
        //{{AFX_MSG_MAP(CSCardTestDlg)
        ON_WM_SYSCOMMAND()
        ON_WM_PAINT()
        ON_WM_QUERYDRAGICON()
        ON_BN_CLICKED(IDC_PERFORM_REQUEST, OnPerformRequestButtonClick)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
// CSCardTestDlg message handlers
//


/*++

CCardTstDlg::OnInitDialog()

        Allows initialization of smart card test dialog

Arguments:

        none

Return Value:

        Specifies whether the application has set the input focus to one of the
        controls in the dialog box. If OnInitDialog returns nonzero, Windows sets
        the input focus to the first control in the dialog box. The application
        can return 0 only if it has explicitly set the input focus to one of the
        controls in the dialog box.


Author:

--*/

BOOL CSCardTestDlg::OnInitDialog()
{
        // locals
        BOOL    fReturn = TRUE;

        CDialog::OnInitDialog();

        /////////////////////////////////////////////////////////////////////////
        //
        // Add "About..." menu item to system menu.
        // IDM_ABOUTBOX must be in the system command range.
        //
        ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
        ASSERT(IDM_ABOUTBOX < 0xF000);

        // Retrieve pointer to system menu
        CMenu* pSysMenu = GetSystemMenu(FALSE);
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        // Append the About menu item
        if (!strAboutMenu.IsEmpty())
        {
                pSysMenu->AppendMenu(MF_SEPARATOR);
                pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }

        /////////////////////////////////////////////////////////////////////////
        //
        //  Set the icon for this dialog.  The framework does this automatically
        //  when the application's main window is not a dialog
        //
        SetIcon(m_hIcon, TRUE);                 // Set big icon
        SetIcon(m_hIcon, FALSE);                // Set small icon

        ///////////////////////////////////////////////////////////////////////////
        // Add extra initialization Below

        return fReturn;  // return TRUE  unless you set the focus to a control
}


/*++

CCardTstDlg::OnSysCommand()

        Contains system menu functionality and max and min button functionality

Arguments:

        pID - specifies the type of system command requested
        lParam - contains cursor coordinates if the control-menu command
        is chosen with the mouse. (low order word contains the x coordinate and
        high order word contains the y coordinate)


Return Value:


Author:

--*/

void CSCardTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
        ////////////////////////////////////////////////////////////////////////
        //
        // open the about dialog box if requested, else pass data through to MFC
        //
        if ((nID & 0xFFF0) == IDM_ABOUTBOX){
                CAboutDlg dlgAbout;
                dlgAbout.DoModal();
        }
        else{
                CDialog::OnSysCommand(nID, lParam);
        }
}


/*++

CCardTstDlg::OnPaint()

        Allows general window/dialog painting. Allows draws icon when
        dialog is minimized or maximized.

Arguments:

        none

Return Value:


Author:

--*/

void CSCardTestDlg::OnPaint()
{
        // locals

        ///////////////////////////////////////////////////////////////////////////
        // Test status of dialog...If iconic paint the icon, else pass through paint
        // for MFC to handle
        //
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


/*++

CCardTstDlg::OnQueryDragIcon()

        System calls this to obtain the type of cursor to display while the
        iconized dialog is dragged

Arguments:

        none

Return Value:

        A doubleword value that contains a cursor or icon handle in the low-order
        word. The cursor or icon must be compatible with the display
        driver’s resolution. If the application returns NULL, the system displays
        the default cursor. The default return value is NULL

Author:

--*/

HCURSOR CSCardTestDlg::OnQueryDragIcon()
{
        return (HCURSOR) m_hIcon;
}


/*++

CCardTstDlg::OnPerformRequestButtonClick()

        Processes the selected request in the drop down. This could be a request to
        load the COM vendor g_Wrapper, communicate with the smart card, etc.

Arguments:

        none

Return Value:


Author:

--*/

void CSCardTestDlg::OnPerformRequestButtonClick()
{
        // locals
        int                             iCurrentSelection = m_cbRequestList.GetCurSel();
        HRESULT                 hresult = S_OK;
        TCHAR                   szStringBuffer[255];
        SCARD_STATES    Status;
        SCARD_PROTOCOLS Protocol;
        BYTE                    byChal[8];
        LONG                    lLength = 8;

        //HSCARD_FILE           hFile;
        //BYTE                  byData[255];

        try {
                // What action should be performed
                switch (iCurrentSelection) {
                // run through the cases
                case 0:
                        // Load COM
                        hresult = g_Wrapper.LoadCOM();
                        if (FAILED(hresult))
                                throw hresult;
                        else
                                m_editComStatus.SetWindowText("COM Loaded...");
                        break;
                case 1:
                        // Attach to reader
                        hresult = g_Wrapper.AttachToReaderByName(g_wszReaderName);
                        if (FAILED(hresult))
                                throw (hresult);
                        else
                                m_editComStatus.SetWindowText("Attach to reader was successful.");
                        break;
                case 2:
                        //Return ICC/IFD status
                        hresult = g_Wrapper.Status(&Status, &Protocol);
                        if (FAILED(hresult))
                                throw(hresult);
                        m_editComStatus.SetWindowText("Get Status...See Below.");
                        sprintf(szStringBuffer, "State: %d      Protocol: %d",
                                        (int) Status, (int) Protocol);
                        m_editICCStatus.SetWindowText(szStringBuffer);
                        break;
                case 3:
                        //Get challenge..
                        hresult = g_Wrapper.GetChallenge( (LPBYTE) byChal, &lLength);
                        if (FAILED(hresult))
                                throw (hresult);
                        m_editComStatus.SetWindowText("Get challenge ok...See Below.");
                        sprintf(szStringBuffer, "%d %d %d %d %d %d %d %d",
                                        (int) byChal[0], (int) byChal[1], (int) byChal[2], (int) byChal[3],
                                        (int) byChal[4], (int) byChal[5], (int) byChal[6], (int) byChal[7]);
                        m_editICCStatus.SetWindowText(szStringBuffer);
                        break;
                case 4:
                        // Change Dir to Master
                        hresult = g_Wrapper.ChangeDirectory( g_wszFilename );
                        if (FAILED(hresult))
                                throw (hresult);
                        else {
                                m_editComStatus.SetWindowText("3F00 now selected.");
                                m_editICCStatus.SetWindowText(" ");
                        };//else
                        break;
                case 5:
                        // Open read file
                        if (FAILED(hresult))
                                throw (hresult);
                        break;
                case 6:
                        // Verify PIN
                        if (FAILED(hresult))
                                throw;
                        else
                                m_editComStatus.SetWindowText("PIN Verified.");
                        break;
                case 7:
                        // Detach
                        hresult = g_Wrapper.Detach();
                        if (FAILED(hresult))
                                throw (hresult);
                        else {
                                m_editComStatus.SetWindowText("Detached.");
                                m_editICCStatus.SetWindowText(" ");
                        }; //else
                default:
                        break;
                };//end switch
        }

        catch (HRESULT) {
                // todo: add error handling
                m_editComStatus.SetWindowText("Command Failed...");
                m_editICCStatus.SetWindowText(" ");
        }

        catch (...) {
                // todo: add error handling
        }
}


/*++

CCardTstDlg::DestroyWindow()

        Dialog destroy window override to clean up on dialog close

Arguments:

        none

Return Value:


Author:

--*/

BOOL CSCardTestDlg::DestroyWindow()
{
        // Unload COM
        g_Wrapper.UnloadCOM();

        //////////////////////////////////////////////////////////////////////
        // Pass back through MFC
        return CDialog::DestroyWindow();
}
