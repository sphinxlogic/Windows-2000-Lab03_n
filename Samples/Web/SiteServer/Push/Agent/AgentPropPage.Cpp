/****************************************************************************
 ** 
 ** Microsoft Site Server v3.00
 ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
 ** 
 ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
 ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
 ** PURPOSE.
 **
 **
 ** CONTENTS
 **     CAgentPropPage
 **     CAgentPropPage::CAgentPropPageFactory
 **
 ** NOTES
 **     OLE Property page implementation for the agent (MFC based.)
 **     
 ****************************************************************************/

#include "stdafx.h"
#include "Agent.h"
#include "DispHelp.h"
#include "AgentPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgentPropPage property page

IMPLEMENT_DYNCREATE(CAgentPropPage, COlePropertyPage)

BEGIN_MESSAGE_MAP(CAgentPropPage, COlePropertyPage)
    //{{AFX_MSG_MAP(CAgentPropPage)
    ON_BN_CLICKED(IDC_ADD,    OnAdd)
    ON_BN_CLICKED(IDC_REMOVE, OnRemove)
    ON_WM_HELPINFO()
    ON_WM_CONTEXTMENU()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid
IMPLEMENT_OLECREATE_EX(CAgentPropPage, "Push.SampleAgentPropPage.1",
0xCE799C1C, 0x84DE, 0x11D1, 0x9C, 0x43, 0x00, 0x00, 0xF8, 0x75, 0x67, 0x57);


/*==========================================================================
  %%Function:   UpdateRegistry
  %%Parameters: BOOL    -- Determines whether the control class's 
                           object factory is to be [un]registered.
  %%Returns:    BOOL    -- Nonzero if the control or property page class was
                           successfully [un]registered; otherwise 0.
  %%Desc:       Calls helper routines supplied by MFC.
  ==========================================================================*/
BOOL CAgentPropPage::CAgentPropPageFactory::UpdateRegistry(BOOL bRegister)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (bRegister)
        return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
            m_clsid, IDS_AGENT_PAGENAME, afxRegApartmentThreading);
    else
        return AfxOleUnregisterClass(m_clsid, NULL);
}


/*==========================================================================
  %%Function:   CAgentPropPage
  %%Parameters: 
  %%Returns:    
  %%Desc:       
  ==========================================================================*/
CAgentPropPage::CAgentPropPage() : COlePropertyPage(IDD, IDS_AGENT_PAGENAME)
{
    //{{AFX_DATA_INIT(CAgentPropPage)
    m_strDirectory = _T("");
    //}}AFX_DATA_INIT

    // Let MFC know that you support Help.
    SetHelpInfo(_T("ACS"), AfxGetApp()->m_pszHelpFilePath, IDD);
}


/*==========================================================================
  %%Function:   ~CAgentPropPage
  %%Parameters: 
  %%Returns:    
  %%Desc:       
  ==========================================================================*/
CAgentPropPage::~CAgentPropPage()
{
}


/*==========================================================================
  %%Function:   DoDataExchange
  %%Parameters: CDataExchange* pDX
  %%Returns:    
  %%Desc:       Called by the framework to exchange and validate dialog data.
  ==========================================================================*/
void CAgentPropPage::DoDataExchange(CDataExchange* pDX)
{
    COlePropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAgentPropPage)
    DDX_Control(pDX, IDC_FILES, m_listFiles);
    DDX_Text(pDX, IDC_DIRECTORY, m_strDirectory);
    //}}AFX_DATA_MAP

    if ( pDX->m_bSaveAndValidate )
    {
        CStringArray rgstrFiles;
        for (int n=0, nMax=m_listFiles.GetItemCount(); n<nMax; n++)
        {
            rgstrFiles.Add(m_listFiles.GetItemText(n, 0));
        }

        CComVariant vtData, vtResult;
        PutIntoVariant(&vtData, rgstrFiles);

        BYTE rgbParams[] = { VT_BSTR, VT_VARIANT, 0 };
        m_dispRefresh.InvokeHelper(
                _T("Item"), 
                DISPATCH_PROPERTYPUT, 
                NULL, 
                rgbParams, 
                _T("Files"), 
                &vtData);
        m_dispRefresh.InvokeHelper(
                _T("Item"),
                DISPATCH_PROPERTYPUT,
                NULL,
                rgbParams,
                _T("Directory"),
                &CComVariant(m_strDirectory));
    }
}


/*==========================================================================
  %%Function:   WindowProc
  %%Parameters: UINT msg, WPARAM wParam, LPARAM lParam
  %%Returns:    LRESULT
  %%Desc:       If you press an ALT+key combination (generating a 
                WM_SYSCOMMAND) with keyboard focus on the property page
                for an MFC ActiveX control and the key does not correspond
                to a mnemonic on the page, you will get a stack overflow.)
                For more details go to:
                http://premium.microsoft.com/support/kb/articles/q177/1/03.asp
  ==========================================================================*/
LRESULT CAgentPropPage::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam) 
{
    if (WM_SYSCOMMAND != msg)
        return COlePropertyPage::WindowProc(msg, wParam, lParam);

    // Translate the Help accelerator into a notification
    // OleFrame does not handle &H accelerator.

    CWnd *pWndParent = GetParent();
    CWnd *pWndHelp   = NULL;

    if (   pWndParent 
        && pWndParent->GetParent())
        pWndHelp = pWndParent->GetParent()->GetDlgItem(IDHELP);

    if (   pWndHelp
        && pWndHelp->IsWindowEnabled()
        && SC_KEYMENU == wParam)
    {
        CString strHelp;
        pWndHelp->GetWindowText(strHelp);

        TCHAR tchHelpMnemonic = 0;
        int   nMnemonicPos = strHelp.Find(_T('&'));
        if (nMnemonicPos != -1)
            tchHelpMnemonic = strHelp[nMnemonicPos+1];

        if (_totupper(tchHelpMnemonic) == LOWORD(lParam) || 
            _totlower(tchHelpMnemonic) == LOWORD(lParam))
        {
            NMHDR nmhdr;
            nmhdr.hwndFrom = pWndParent->m_hWnd;
            nmhdr.idFrom   = IDHELP;
            nmhdr.code     = PSN_HELP;
    
            pWndParent->SendMessage(
                    WM_NOTIFY, 
                    IDHELP,
                    (LPARAM) &nmhdr);
        }
    }
    return TRUE;
}


/*==========================================================================
  %%Function:   PreTranslateMessage
  %%Parameters: pMsg -- Points to a MSG structure that contains the message
                        to process.
  %%Returns:    Nonzero if the message was translated and should not be
                dispatched; 0 if the message was not translated and should
                be dispatched
  %%Desc:       This is a workaround for building UNICODE OLE property pages.
                OleCreatePropertyFrame is built ANSI and calls GetMessageA
                to retrieve messages.  IsDialogMessageW can't handle
                translating messages retrieved from GetMessageA.  The nasty
                problem is that there is no way for a control to determine
                whether or not pMsg was retrieved through GetMessageA or
                GetMessageW.
  ==========================================================================*/
BOOL CAgentPropPage::PreTranslateMessage(MSG* pMsg) 
{
    if (   pMsg->message == WM_CHAR
        && ::IsDialogMessageA(m_hWnd, pMsg))
        return TRUE;

    return COlePropertyPage::PreTranslateMessage(pMsg);
}


/*==========================================================================
  %%Function:   OnInitDialog
  %%Parameters: 
  %%Returns:    BOOL
  %%Desc:       The framework calls this function when the property page's 
                dialog is initialized. At this point, do:
                    * Get the Project and Channel objects
                    * Load persisted data and display them in the dialog.
                    * Dialog intialization (Help and ListView control)
  ==========================================================================*/
BOOL CAgentPropPage::OnInitDialog() 
{
    COlePropertyPage::OnInitDialog();
    
    //
    // PROJECT & CHANNEL objects
    //
    ULONG nObjects;
    LPDISPATCH* rgpDisp = GetObjectArray( &nObjects );
    ASSERT(rgpDisp!=NULL && nObjects >= 2);

    m_dispProject = rgpDisp[0];
    m_dispChannel = rgpDisp[1];

    //
    // Load old settings
    //
    CComVariant vtResult;
    m_dispChannel.InvokeHelper(
            _T("RefreshOptions"), 
            DISPATCH_PROPERTYGET, 
            &vtResult);

    ASSERT(V_VT(&vtResult) == VT_DISPATCH);
    m_dispRefresh = V_DISPATCH(&vtResult);

    BYTE rgbParams[] = { VT_BSTR, 0 };
    m_dispRefresh.InvokeHelper(
            _T("Item"), 
            DISPATCH_PROPERTYGET, 
            &vtResult, 
            rgbParams, 
            _T("Files"));
    CStringArray rgstrFiles;
    GetFromVariant(rgstrFiles, &vtResult);

    m_dispRefresh.InvokeHelper(
            _T("Item"),
            DISPATCH_PROPERTYGET,
            &vtResult,
            rgbParams,
            _T("Directory"));
    if (V_VT(&vtResult)==VT_BSTR)
    {
        m_strDirectory = V_BSTR(&vtResult);
        UpdateData(FALSE);
    }

    //
    // Dialog initialization
    //
    CRect rect;
    m_listFiles.GetClientRect(rect);
    rect.right -= GetSystemMetrics(SM_CXVSCROLL);
    m_listFiles.InsertColumn(0, _T("Files"), LVCFMT_LEFT, rect.Width());

    for (int n=0, nMax=rgstrFiles.GetSize(); n<nMax; n++)
        m_listFiles.InsertItem(0, rgstrFiles[n]);

    //
    // HELP initialization
    //
    ASSERT(GetParent() != NULL);
    ASSERT(GetParent()->GetParent() != NULL);

    HWND hWndParent = GetParent()->GetParent()->m_hWnd;
    SetWindowLong(hWndParent, GWL_EXSTYLE,
        GetWindowLong(hWndParent, GWL_EXSTYLE) | WS_EX_CONTEXTHELP);
    
    CString strHelp;
    strHelp.LoadString(IDS_HELP);
    CWnd *pWndHelp = FromHandle(hWndParent)->GetDlgItem(IDHELP);
    if (pWndHelp)
        pWndHelp->SetWindowText(strHelp);

    return TRUE;
}


/*==========================================================================
  %%Function:   OnAdd
  %%Parameters: 
  %%Returns:    
  %%Desc:       Called when the Add button is clicked.
                Shows a file dialog to let the user multi-select additional
                files.
  ==========================================================================*/
void CAgentPropPage::OnAdd() 
{
    CString strFilter;
    strFilter.LoadString(IDS_SAMPLE_FILTER);

    CFileDialog filDlg(
            TRUE,
            NULL, 
            NULL, 
            OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY,
            strFilter);
    filDlg.m_ofn.lpstrInitialDir = m_strDirectory;

    if (filDlg.DoModal() != IDOK)
        return;

    // Add files to the list
    for (POSITION pos = filDlg.GetStartPosition(); pos != NULL; )
    {
        CString strNew = filDlg.GetNextPathName(pos);
        int     nFind  = 1 + strNew.ReverseFind(_T('\\'));
        CString strDir = strNew.Left(nFind);

        //
        // Directory change?  Overwrite older selection.
        //
        if (strDir.CompareNoCase(m_strDirectory) != 0)
        {
            if (!m_strDirectory.IsEmpty()
                && AfxMessageBox(IDS_DIR_CHANGED, MB_YESNO) != IDYES)
                return;

            m_listFiles.DeleteAllItems();
            m_strDirectory = strDir;
            UpdateData(FALSE);
        }

        //
        // Look for the item if it is already present
        //
        strNew = strNew.Mid(nFind);
        BOOL bFound = FALSE;
        for (int n=0, nMax=m_listFiles.GetItemCount(); n<nMax; n++)
        {
            bFound = bFound || 
                     0 == m_listFiles.GetItemText(n, 0).CompareNoCase(strNew);
        }

        // Add the item if not found in the list
        if (!bFound)
            m_listFiles.InsertItem(0, strNew);
    }
}


/*==========================================================================
  %%Function:   OnRemove
  %%Parameters: 
  %%Returns:    
  %%Desc:       Removes all selected items in the ListView control.
  ==========================================================================*/
void CAgentPropPage::OnRemove() 
{
    m_listFiles.SetFocus();
    
    int nItem = -1;
    while ((nItem = m_listFiles.GetNextItem(-1, LVNI_SELECTED)) != -1)
    {
        m_listFiles.DeleteItem(nItem);
    }
}


/*==========================================================================
  %%Function:   OnHelp
  %%Parameters: LPCTSTR lpszHelpDir -- Directory containing the property 
                                       page's help file.
  %%Returns:    BOOL                -- TRUE if handled
  %%Desc:       The framework calls this function when the user requests 
                online help.
  ==========================================================================*/
BOOL CAgentPropPage::OnHelp(LPCTSTR lpszHelpDir)
{
    ASSERT(FALSE); // Plug in your help routine here.
    return TRUE;

    // HTMLHelp API Reference is located at:
    // http://www.microsoft.com/msdn/sdk/inetsdk/help/htmlhelp/hhwapi.htm
}


/*==========================================================================
  %%Function:   OnHelpInfo
  %%Parameters: HELPINFO* lpHelpInfo -- Pointer to a HELPINFO structure that 
                                        contains information about the menu 
                                        item, control, dialog box, or window 
                                        for which help is requested
  %%Returns:    BOOL                 -- TRUE if handled
  %%Desc:       Called by the framework when the user presses the F1 key.
  ==========================================================================*/
BOOL CAgentPropPage::OnHelpInfo(HELPINFO* lpHelpInfo)
{
    ASSERT(FALSE); // Plug in your help routine here.
    return TRUE;

    // To show context sensitive help, call ::WinHelp with HELP_WM_HELP
    // Refer to MFC online documentation for more details on supporting
    // Context-Sensitive Help.
}


/*==========================================================================
  %%Function:   OnContextMenu
  %%Parameters: CWnd*   -- Handle to the window in which the user 
                           right clicked the mouse.
                CPoint  -- Position of the cursor, in screen coordinates, 
                           at the time of the mouse click.

  %%Returns:    
  %%Desc:       Called by the framework when the user has clicked the right 
                mouse button (right clicked) in the window. 
  ==========================================================================*/
void CAgentPropPage::OnContextMenu(CWnd* pWnd, CPoint point) 
{
    ASSERT(FALSE); // Plug in your help routine here.

    // To show context sensitive help, call ::WinHelp with HH_DISPLAY_TOPIC.
    // Refer to MFC online documentation for more details on supporting
    // Context-Sensitive Help.
}

