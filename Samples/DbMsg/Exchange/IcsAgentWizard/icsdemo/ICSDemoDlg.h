// ICSDemoDlg.h : header file
//

#pragma once

#include "mapix.h"
#include "edkmdb.h"

/////////////////////////////////////////////////////////////////////////////
// CICSDemoDlg dialog

class CICSDemoDlg : public CDialog
{
// Construction
public:
	CICSDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CICSDemoDlg)
	enum { IDD = IDD_ICSDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CICSDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CICSDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnSynch();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	LPMDB							m_lpStore;
	LPMAPIFOLDER					m_lpFolder;
	LPEXCHANGEEXPORTCHANGES			m_lpSynchronizer;
	HGLOBAL							m_hMemBlock;
	LPSTREAM						m_lpSynchState;
	LPUNKNOWN						m_lpCollectorIUnknown;
	LPEXCHANGEIMPORTCONTENTSCHANGES	m_lpCollector;

	BOOL							m_fICSStarted;
	BOOL							m_fICSBackupState; // Does backup state exist?
	LPSTREAM						m_lpBackupState;   // Backup state

	void SynchStopped(void);
	void SynchStarted(void);

	HRESULT Load();
	HRESULT Save();
	
public:
	LPMDB Store(){return m_lpStore;};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
