#if !defined(AFX_CSTM5DLG_H__2A802959_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
#define AFX_CSTM5DLG_H__2A802959_2D4D_11D2_9879_00C04FAE2339__INCLUDED_

// cstm5dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom5Dlg dialog

class CCustom5Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom5Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom5Dlg)
	enum { IDD = IDD_CUSTOM5 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom5Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom5Dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM5DLG_H__2A802959_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
