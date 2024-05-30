// MtsSpyPropPage.cpp : Implementation of CMtsSpyPropPage
#include "stdafx.h"
#include "MtsSpyCtl.h"
#include "MtsAudit.h"
#include "MtsSpy.h"
#include "MtsSpyPropPage.h"
#include "mtsevents.h"
#include "MtsSink.h"
#include "objsink.h"
#include "PackageSink.h"
#include "PackageInfo.h"

TCHAR * szColNames[] = 
{
	_T("Count"),
	_T("Event"),
	_T("TickCount"),
	_T("Package"),
	_T("Parameter"),
	_T("Value")
};
/////////////////////////////////////////////////////////////////////////////
// CMtsSpyPropPage

LRESULT CMtsSpyPropPage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	bHandled = FALSE;

	m_ppUnk[0]->QueryInterface(IID_IMtsSpy, (void**)&m_pSpy);
	_ASSERTE(m_pSpy);
	CComBSTR bstr;
	m_pSpy -> get_LogFile(&bstr);
	SetDlgItemText(IDC_LOG_FILE, bstr);
	
	// grid lines
	BOOL bVal;
	m_pSpy -> get_ShowGridLines(&bVal);
	SendDlgItemMessage(IDC_SHOW_GRID_LINES, BM_SETCHECK,  (bVal) ? BST_CHECKED : BST_UNCHECKED);

	// show on screen
	m_pSpy -> get_ShowOnScreen(&bVal);
	SendDlgItemMessage(IDC_SHOW_ON_SCREEN, BM_SETCHECK,  (bVal) ? BST_CHECKED : BST_UNCHECKED);

	// log to file
	m_pSpy -> get_LogToFile(&bVal);
	SendDlgItemMessage(IDC_LOG_TO_FILE, BM_SETCHECK,  (bVal) ? BST_CHECKED : BST_UNCHECKED);

	int i;
	for (i=0;i<sizeof(szColNames)/sizeof(szColNames[0]);i++)
		SendDlgItemMessage(IDC_COLUMN_NAMES, CB_ADDSTRING, 0, (LPARAM)(LPTSTR)szColNames[i]);


	SendDlgItemMessage(IDC_COLUMN_NAMES, CB_SETCURSEL, 0, 0);
	BOOL bH;
	OnSelectColumn(CBN_SELCHANGE, 0,0, bH);	
	return 0;
}

LRESULT CMtsSpyPropPage::OnSelectColumn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (wNotifyCode == CBN_SELCHANGE)
	{		
		int nSel = SendDlgItemMessage(IDC_COLUMN_NAMES, CB_GETCURSEL, 0, 0L);			   
		if (nSel != CB_ERR)
		{
			// get the width

			long lWidth;
			_ASSERTE(m_pSpy);
			m_pSpy -> get_ColWidth(nSel, &lWidth);
			SetDlgItemInt(IDC_WIDTH, lWidth);			
		}

	}

	return 0;
}


STDMETHODIMP CMtsSpyPropPage::Apply()
{
	ATLTRACE(_T("CMtsSpyPropPage::Apply\n"));
	for (UINT i = 0; i < m_nObjects; i++)
	{
		
		CComQIPtr<IMtsSpy, &IID_IMtsSpy> pSpy(m_ppUnk[i]);						
		BSTR bstr;
		GetDlgItemText(IDC_LOG_FILE, bstr);
		pSpy -> put_LogFile(bstr);
		::SysFreeString(bstr);
		// grid lines
		BOOL bVal = (SendDlgItemMessage(IDC_SHOW_GRID_LINES, BM_GETCHECK) == BST_CHECKED);
		pSpy -> put_ShowGridLines(bVal);	

		// log to file
		bVal = (SendDlgItemMessage(IDC_LOG_TO_FILE, BM_GETCHECK) == BST_CHECKED);
		pSpy -> put_LogToFile(bVal);	

		// show on screen
		bVal = (SendDlgItemMessage(IDC_SHOW_ON_SCREEN, BM_GETCHECK) == BST_CHECKED);
		pSpy -> put_ShowOnScreen(bVal);	

		int j;
		UINT nWidth;
		for (j=0;j<sizeof(szColNames)/sizeof(szColNames[0]);j++)
		{
			
			nWidth = SendDlgItemMessage(IDC_COLUMN_NAMES, CB_GETITEMDATA, j) ;
			if (nWidth)
			{
				pSpy -> put_ColWidth(j,nWidth);
				SendDlgItemMessage(IDC_COLUMN_NAMES, CB_SETITEMDATA, j, 0); 
			}
		}

	}
	SetDirty(FALSE);
	m_bDirty = FALSE;
	return S_OK;
}
