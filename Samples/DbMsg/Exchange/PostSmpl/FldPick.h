//=========================================================================
// FldPick.H
//
// Copyright (C) 1986-1996.  Microsoft Corp.  All Rights Reserved.
//
// Purpose:
//    Definition of CFolderPicker class
//=========================================================================


extern void WINAPI CreateAndPostMessage();

/////////////////////////////////////////////////////////////////////////////
// CFolderPicker dialog

class CFolderPicker : public CDialog
{
// Construction
public:
	CFolderPicker(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFolderPicker)
	enum { IDD = IDD_FOLDERPICKER };
	CButton	m_ok;
	CButton	m_cancel;
	CTreeCtrl	m_TreeCtrl;
	//}}AFX_DATA

	
	BOOL AddTreeViewItems();
	HTREEITEM AddOneItem (HTREEITEM hParent, LPSTR szText,HTREEITEM hInsAfter, int iImage, DWORD lparam);
	STDMETHODIMP TvmtFromRoot(HTREEITEM   hitemParent);
	STDMETHODIMP TvmtFromFolder(HTREEITEM      hitemParent, LPMAPIFOLDER   pfld);
	STDMETHODIMP FirstTimeExpand(HTREEITEM  hitem, SMailID*   pMailID);
	STDMETHODIMP CreateMailID(ULONG ulType, ULONG cbEntryID,LPENTRYID pEntryID, 
								LPCTSTR lpszDisplayName, SMailID**  ppob );
	STDMETHODIMP OpenFolder(SMailID *pMailID, LPMAPIFOLDER *lppFld);
 	
	STDMETHODIMP GetSelectedFolder(LPMAPIFOLDER*  ppfld);
	STDMETHODIMP AddRows(HTREEITEM   hitemParent, LPMAPITABLE pmt);
	INT MapTypeToExchangeImageListIndex(ULONG ulType, INT*  piSelectedImage);
   	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderPicker)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFolderPicker)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemexpandingTreeview(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoTreeview(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreeview(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemTreeview(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
