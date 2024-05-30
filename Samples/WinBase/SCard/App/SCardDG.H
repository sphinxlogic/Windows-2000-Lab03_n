/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.


Module Name:

    CSCardTestDlg

Abstract:

        CSCardTestDlg object description file.

Environment:

    Win32, C++ w/Exceptions, COM/OLE

Revision History:

Notes:


--*/

#ifndef __SCARDTSTDLG_H__
#define __SCARDTSTDLG_H__


/////////////////////////////////////////////////////////////////////////////
//
// Includes
//

/////////////////////////////////////////////////////////////////////////////
// CSCardTestDlg dialog

class CSCardTestDlg : public CDialog
{
        // member Variables
private:

// Construction
public:
        CSCardTestDlg(CWnd* pParent = NULL);    // standard constructor

private:

// Dialog Data
        //{{AFX_DATA(CSCardTestDlg)
        enum { IDD = IDD_SCARDTST_DIALOG };
        CEdit   m_editICCStatus;
        CEdit   m_editComStatus;
        CComboBox       m_cbRequestList;
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CSCardTestDlg)
        public:
        virtual BOOL DestroyWindow();
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support
        //}}AFX_VIRTUAL

protected:
        // Implementation
        HICON m_hIcon;

        // Generated message map functions
        //{{AFX_MSG(CSCardTestDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
        afx_msg void OnPaint();
        afx_msg HCURSOR OnQueryDragIcon();
        afx_msg void OnPerformRequestButtonClick();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif //__SCARDTSTDLG_H__
