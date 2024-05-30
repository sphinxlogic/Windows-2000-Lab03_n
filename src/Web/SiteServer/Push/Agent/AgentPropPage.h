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
 **
 ** NOTES
 **     stdafx.cpp : source file that includes just the standard includes
 **     stdafx.pch will be the pre-compiled header
 **     stdafx.obj will contain the pre-compiled type information
 **
 ****************************************************************************/

#pragma once

#include "Resource.h"
#include "DispHelp.h"

/////////////////////////////////////////////////////////////////////////////
// CAgentPropPage dialog

class CAgentPropPage : public COlePropertyPage
{
    DECLARE_DYNCREATE(CAgentPropPage)
    DECLARE_OLECREATE_EX(CAgentPropPage)

// Construction
public:
    CAgentPropPage();
    ~CAgentPropPage();

    COleDispatchDriverEx m_dispProject;
    COleDispatchDriverEx m_dispChannel;
    COleDispatchDriverEx m_dispRefresh;

// Dialog Data
    //{{AFX_DATA(CAgentPropPage)
    enum { IDD = IDD_SAMPLEAGENTGENPAGE };
    CListCtrl   m_listFiles;
    CString     m_strDirectory;
    //}}AFX_DATA


// Overrides
    // ClassWizard generate virtual function overrides
    //{{AFX_VIRTUAL(CAgentPropPage)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    virtual BOOL OnHelpInfo( HELPINFO* lpHelpInfo );
    virtual BOOL OnHelp( LPCTSTR lpszHelpDir );
    virtual void OnContextMenu(CWnd* pWnd, CPoint point);
    //}}AFX_VIRTUAL

// Implementation
protected:
    // Generated message map functions
    //{{AFX_MSG(CAgentPropPage)
    virtual BOOL OnInitDialog();
    afx_msg void OnAdd();
    afx_msg void OnRemove();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
