// MtsSpyPropPage.h : Declaration of the CMtsSpyPropPage

#ifndef __MTSSPYPROPPAGE_H_
#define __MTSSPYPROPPAGE_H_

#include "resource.h"       // main symbols

EXTERN_C const CLSID CLSID_MtsSpyPropPage;

 
/////////////////////////////////////////////////////////////////////////////
// CMtsSpyPropPage
class ATL_NO_VTABLE CMtsSpyPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMtsSpyPropPage, &CLSID_MtsSpyPropPage>,
	public IPropertyPageImpl<CMtsSpyPropPage>,
	public CDialogImpl<CMtsSpyPropPage>
{


public:
	CComPtr<IMtsSpy> m_pSpy;

	CMtsSpyPropPage() 
	{
		m_dwTitleID = IDS_TITLEMtsSpyPropPage;
		m_dwHelpFileID = IDS_HELPFILEMtsSpyPropPage;
		m_dwDocStringID = IDS_DOCSTRINGMtsSpyPropPage;
		m_bDirty = FALSE;
	}

	enum {IDD = IDD_MTSSPYPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_MTSSPYPROPPAGE)

BEGIN_COM_MAP(CMtsSpyPropPage) 
	COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CMtsSpyPropPage)
	CHAIN_MSG_MAP(IPropertyPageImpl<CMtsSpyPropPage>)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDC_COLUMN_NAMES, OnSelectColumn)
	COMMAND_HANDLER(IDC_WIDTH, EN_CHANGE, OnWidthChange)
	COMMAND_HANDLER(IDC_WIDTH, EN_CHANGE, OnLogFileChange)
	COMMAND_HANDLER(IDC_SHOW_GRID_LINES, BN_CLICKED, OnCheckBoxClick)
	COMMAND_HANDLER(IDC_LOG_TO_FILE, BN_CLICKED, OnCheckBoxClick)
	COMMAND_HANDLER(IDC_SHOW_ON_SCREEN, BN_CLICKED, OnCheckBoxClick)
END_MSG_MAP()

LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
LRESULT OnSelectColumn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

LRESULT OnWidthChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
	SetDirty(TRUE);
	int nSel = SendDlgItemMessage(IDC_COLUMN_NAMES, CB_GETCURSEL, 0, 0L);			   
	BOOL bSuccess;
	UINT nVal = GetDlgItemInt(IDC_WIDTH, &bSuccess, FALSE);
	SendDlgItemMessage(IDC_COLUMN_NAMES, CB_SETITEMDATA, nSel, nVal); // indicating that its width changed
	return 0;

}
LRESULT OnLogFileChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
	SetDirty(TRUE);
	return 0;

}

LRESULT OnCheckBoxClick(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SetDirty(TRUE);
	return 0;
	
}
	STDMETHOD(Apply)(void);

};

#endif //__MTSSPYPROPPAGE_H_
