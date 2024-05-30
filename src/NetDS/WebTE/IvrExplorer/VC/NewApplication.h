#if !defined(AFX_NEWAPPLICATION_H__EA97FCAA_AB97_11D2_A419_006094EB33FB__INCLUDED_)
#define AFX_NEWAPPLICATION_H__EA97FCAA_AB97_11D2_A419_006094EB33FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NewApplication.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewApplication dialog

class CNewApplication : public CDialog
{
// Construction
public:
	CNewApplication(CWnd* pParent = NULL);   // standard constructor
    TCHAR m_appName[256];

// Dialog Data
	//{{AFX_DATA(CNewApplication)
	enum { IDD = IDD_APPLICATION_NAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewApplication)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:

	// Generated message map functions
	//{{AFX_MSG(CNewApplication)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWAPPLICATION_H__EA97FCAA_AB97_11D2_A419_006094EB33FB__INCLUDED_)
