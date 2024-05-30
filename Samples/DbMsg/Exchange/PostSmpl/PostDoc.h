//=========================================================================
// PostSmplDoc.h
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//   interface of the CPostSmplDoc class
//=========================================================================


class CPostSmplDoc : public COleDocument
{
protected: // create from serialization only
	CPostSmplDoc();
	DECLARE_DYNCREATE(CPostSmplDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostSmplDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPostSmplDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSave();
	LPSTORAGE GetStorage(){ return m_lpRootStg;};

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPostSmplDoc)
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
