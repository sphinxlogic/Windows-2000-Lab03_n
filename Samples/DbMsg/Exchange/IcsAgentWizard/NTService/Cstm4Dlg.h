#if !defined(AFX_CSTM4DLG_H__2A802957_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
#define AFX_CSTM4DLG_H__2A802957_2D4D_11D2_9879_00C04FAE2339__INCLUDED_

// cstm4dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom4Dlg dialog

class CCustom4Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom4Dlg();
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CCustom4Dlg)
	enum { IDD = IDD_CUSTOM4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom4Dlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM4DLG_H__2A802957_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
