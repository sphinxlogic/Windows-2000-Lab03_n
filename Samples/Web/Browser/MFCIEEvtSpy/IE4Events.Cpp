/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/




// IE4Events.cpp : implementation file
//
// This source code is provided as-is, without warranty.
//
// Created by S. R.
// Microsoft Developer Support - Internet Client SDK
/////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MFCIEEvtSpy.h"
#include "IE4Events.h"
#include "MFCIEEvtSpyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIE4Events

IMPLEMENT_DYNCREATE(CIE4Events, CCmdTarget)

CIE4Events::CIE4Events(CMFCIEEvtSpyDlg* pParent /* = NULL */) : m_pParent(pParent)
{
   ASSERT(m_pParent);

   EnableAutomation();  // Needed in order to sink events.
}

CIE4Events::~CIE4Events()
{
}


BEGIN_MESSAGE_MAP(CIE4Events, CCmdTarget)
	//{{AFX_MSG_MAP(CIE4Events)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CIE4Events, CCmdTarget)
	DISP_FUNCTION_ID(CIE4Events, "BeforeNavigate2", DISPID_BEFORENAVIGATE2,
                    OnBeforeNavigate2, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT
                    VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)

	DISP_FUNCTION_ID(CIE4Events, "CommandStateChange", DISPID_COMMANDSTATECHANGE,
                    OnCommandStateChange, VT_EMPTY, VTS_I4 VTS_BOOL)

   DISP_FUNCTION_ID(CIE4Events, "DocumentComplete", DISPID_DOCUMENTCOMPLETE,
                    OnDocumentComplete, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT)

	DISP_FUNCTION_ID(CIE4Events, "DownloadComplete", DISPID_DOWNLOADCOMPLETE,
                    OnDownloadComplete, VT_EMPTY, VTS_NONE)

	DISP_FUNCTION_ID(CIE4Events, "NavigateComplete2", DISPID_NAVIGATECOMPLETE2,
                    OnNavigateComplete2, VT_EMPTY, VTS_DISPATCH VTS_PVARIANT)

	DISP_FUNCTION_ID(CIE4Events, "NewWindow2", DISPID_NEWWINDOW2, 
                    OnNewWindow2, VT_EMPTY, VTS_DISPATCH VTS_PBOOL)

	DISP_FUNCTION_ID(CIE4Events, "OnQuit", DISPID_ONQUIT, OnQuit, VT_EMPTY, VTS_NONE)

	DISP_FUNCTION_ID(CIE4Events, "ProgressChange", DISPID_PROGRESSCHANGE,
                    OnProgressChange, VT_EMPTY, VTS_I4 VTS_I4)

	DISP_FUNCTION_ID(CIE4Events, "StatusTextChange", DISPID_STATUSTEXTCHANGE,
                    OnStatusTextChange, VT_EMPTY, VTS_BSTR)

	DISP_FUNCTION_ID(CIE4Events, "TitleChange", DISPID_TITLECHANGE,
                    OnTitleChange, VT_EMPTY, VTS_BSTR)
END_DISPATCH_MAP()

//
// Add DIID_DWebBrowserEvents2 to the interface map to tell
// IE4 that we support this event sink.  IE4 will QI for 
// this interface when we call AfxConnectionAdvise.  If IE4
// does not find this interface, it will then QI for IDispatch.
//
BEGIN_INTERFACE_MAP(CIE4Events, CCmdTarget)
	INTERFACE_PART(CIE4Events, DIID_DWebBrowserEvents2, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIE4Events event handlers
void CIE4Events::OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
   USES_CONVERSION;

   CString strEvt("BeforeNavigate2: ");
   strEvt += OLE2T(URL->bstrVal);

   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnCommandStateChange(long lCommand, BOOL bEnable)
{
   CString strEvt;
   strEvt.Format("CommandStateChange: Command = %ld  Enable = %d", lCommand, bEnable);

   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
   USES_CONVERSION;

   CString strEvt("DocumentComplete: ");
   strEvt += OLE2T(URL->bstrVal);

   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnDownloadComplete() 
{
   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, "OnDownloadComplete");
}

void CIE4Events::OnNavigateComplete2(LPDISPATCH pDisp, VARIANT* URL)
{
   USES_CONVERSION;

   CString strEvt("NavigateComplete2: ");
   strEvt += OLE2T(URL->bstrVal);

   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{
	m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, "NewWindow2");
}

void CIE4Events::OnProgressChange(long lProgress, long lProgressMax)
{
   CString strEvt;
   strEvt.Format("ProgressChange: Progress = %ld  ProgressMax = %ld", lProgress, lProgressMax);

	m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnStatusTextChange(LPCTSTR lpszText) 
{
   CString strEvt("StatusTextChange: ");
   strEvt += lpszText;

   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnTitleChange(LPCTSTR lpszText) 
{
   CString strEvt("TitleChange: ");
   strEvt += lpszText;

   m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, strEvt);
}

void CIE4Events::OnQuit()
{
	m_pParent->AddEventToList(CMFCIEEvtSpyDlg::IE4ListBox, "Quit");
   m_pParent->OnIE4Quit();
}
