// Pubdlg.h : Declaration of the CPubdlg

#ifndef __PUBDLG_H_
#define __PUBDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <comadmin.h>
#include "..\include\adminwrap.h"

/////////////////////////////////////////////////////////////////////////////
// CPubdlg
class CPubdlg : 
	public CAxDialogImpl<CPubdlg>
{
private:
	LRESULT PopulateCombo (int nCombo, int ncasespecific=0, BOOL bdef=TRUE);
	LRESULT FireDiskMethod(IUnknown* punk, WCHAR* wzmethod, BSTR bstrval);
	LRESULT FireFileMethod(IUnknown* punk, WCHAR* wzmethod, BSTR bstrval);
	LRESULT FireSystemMethod(IUnknown* punk, WCHAR* wzmethod, BSTR bstrval);

public:
	CPubdlg()
	{
		m_pcat			= NULL;
		m_fPersistent	= TRUE;
	}

	~CPubdlg()
	{
		if(m_pcat)
			m_pcat->Release();
	}

	enum { IDD = IDD_PUBDLG };

BEGIN_MSG_MAP(CPubdlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_HANDLER(IDC_REGEC, BN_CLICKED, OnClickedRegec)
	COMMAND_HANDLER(IDC_REGSUB, BN_CLICKED, OnClickedRegsub)
	COMMAND_HANDLER(IDC_INTERFACE, CBN_SELCHANGE, OnSelChange)
	COMMAND_HANDLER(IDC_FIREINTERFACE, CBN_SELCHANGE, OnSelChange)
	COMMAND_HANDLER(IDC_FIRE, BN_CLICKED, OnClickedFire)
	COMMAND_HANDLER(IDC_ALLINT, BN_CLICKED, OnClickedAlInterfaces)
	COMMAND_HANDLER(IDC_ALL, BN_CLICKED, OnClickedAllMethods)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// Wont't be used as we plucked off the OK button
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		//EndDialog(wID);
		DestroyWindow();
		PostQuitMessage(0);	
		return 0;
	}
	LRESULT OnClickedRegec(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedRegsub(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedFire(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedAlInterfaces(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedAllMethods(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);



private:
	CApp			 *m_pPubApp, *m_pSubApp;
	ICOMAdminCatalog *m_pcat;
	BOOL			 m_fPersistent;
};

HRESULT GetSubDllPathName(TCHAR tzfilename[MAX_PATH]);
HRESULT GetECDllPathName(TCHAR tzfilename[MAX_PATH]);


#endif //__PUBDLG_H_
