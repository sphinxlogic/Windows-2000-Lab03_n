#if !defined(AFX_CSTM2DLG_H__2A802953_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
#define AFX_CSTM2DLG_H__2A802953_2D4D_11D2_9879_00C04FAE2339__INCLUDED_

// cstm2dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog

class CCustom2Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom2Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom2Dlg)
	enum { IDD = IDD_CUSTOM2 };
	CButton	m_ManualButton;
	CButton	m_PollBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom2Dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM2DLG_H__2A802953_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
