// IvrExplorerDoc.h : interface of the CIvrExplorerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVREXPLORERDOC_H__848B68E4_AB7D_11D2_A419_006094EB33FB__INCLUDED_)
#define AFX_IVREXPLORERDOC_H__848B68E4_AB7D_11D2_A419_006094EB33FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CIvrExplorerDoc : public CDocument
{
protected: // create from serialization only
	CIvrExplorerDoc();
	DECLARE_DYNCREATE(CIvrExplorerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIvrExplorerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIvrExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIvrExplorerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IVREXPLORERDOC_H__848B68E4_AB7D_11D2_A419_006094EB33FB__INCLUDED_)
