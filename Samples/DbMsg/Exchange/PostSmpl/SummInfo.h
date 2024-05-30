// SummInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSummInfo dialog

class CSummInfo : public CDialog
{
// Construction
public:
	CSummInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSummInfo)
	enum { IDD = IDD_SUMMARYINFO };
	CString	m_psauthor;
	CString	m_pscomments;
	CString	m_psdirectory;
	CString	m_psfilename;
	CString	m_pskeywords;
	CString	m_pssubject;
	CString	m_pstitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSummInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSummInfo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
