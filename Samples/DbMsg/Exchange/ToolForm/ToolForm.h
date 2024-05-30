// --toolform.h---------------------------------------------------------------
// 
//  Declaration for the CToolForm class
//
//	Copyright (C) 1986-1996. Microsoft Corporation.  All Rights Reserved.
//
// ---------------------------------------------------------------------------

class CToolDoc;

/////////////////////////////////////////////////////////////////////////////
// CToolForm form view

class CToolForm : public CFormView
{
protected:
	CToolForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CToolForm)

// Form Data
public:
	//{{AFX_DATA(CToolForm)
	enum { IDD = IDD_FORM };
	CString	m_strDevelopedBy;
	CString	m_strIntroduction;
	CString	m_strLocation;
	CString	m_strOS;
	CString	m_strPlatform;
	CString	m_strToolName;
	CString	m_strToolType;
	CString	m_strTopic;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:	
	CToolDoc * GetDocument();

// *** ADDED CODE ***
	void PutDataIntoWindow(void);
	void GetDataFromWindow(void);
// *** END ADDED CODE ***

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolForm)
	public:
	virtual void OnFinalRelease();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CToolForm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUG  // debug version in toolform.cpp
inline CToolDoc* CToolForm::GetDocument()
   { return (CToolDoc*)m_pDocument; }
#endif

