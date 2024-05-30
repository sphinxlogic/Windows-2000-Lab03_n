#if !defined(AFX_CSTM1DLG_H__64382B35_168D_11D2_B824_00A0C905427E__INCLUDED_)
#define AFX_CSTM1DLG_H__64382B35_168D_11D2_B824_00A0C905427E__INCLUDED_


// cstm1dlg.h : header file
//

#include <mapix.h>
#include <mapiutil.h>
#include <mapidefs.h>
#include <afxtempl.h>

#include "CMAPILogon.h"

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg();
	virtual BOOL OnDismiss();

	BOOL CreateImageListExchange(); 
	BOOL AddTreeViewItems(); 
	HTREEITEM AddOneItem (HTREEITEM hParent, 
						  LPSTR szText,
						  HTREEITEM hInsAfter, 
						  int iImage, 
						  DWORD lparam); 
	STDMETHODIMP TvmtFromRoot(HTREEITEM   hitemParent); 
	STDMETHODIMP TvmtFromFolder(HTREEITEM hitemParent, 
								LPMAPIFOLDER   pfld); 
	STDMETHODIMP FirstTimeExpand(HTREEITEM  hitem, 
								 SMailID*   pMailID); 
	STDMETHODIMP CreateMailID(ULONG ulType, 
							  ULONG cbEntryID,
							  LPENTRYID pEntryID,  
							  LPCTSTR lpszDisplayName, 
							  SMailID**  ppob ); 
	STDMETHODIMP OpenFolder(SMailID *pMailID, 
							LPMAPIFOLDER *lppFld); 
  
	STDMETHODIMP GetSelectedFolder(LPMAPIFOLDER*  ppfld); 
	STDMETHODIMP AddRows(HTREEITEM   hitemParent, 
						 LPMAPITABLE pmt); 

	//INT MapTypeToExchangeImageListIndex(ULONG ulType, INT*  piSelectedImage); 

	// Dialog Data
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_CUSTOM1 };
	CTreeCtrl	m_TreeCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	afx_msg void OnGetdispinfoExchangeTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedExchangeTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemExchangeTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandingExchangeTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangingExchangeTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL HasSynchronizer(LPMAPIFOLDER lpMAPIFolder);
	BOOL GetCheckState(HTREEITEM hItem);
	BOOL MakeList(HTREEITEM hItem);
private:
	CMAPILogon * m_lpMAPILogon;
	BOOL m_fIsInitialized;

	CImageList m_obImageListExchange;

	vector<SMailID *> myList;

	LPTSTR m_lpszRootFolderName;

	BOOL IsLegalContainer(CString cstr);
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSTM1DLG_H__64382B35_168D_11D2_B824_00A0C905427E__INCLUDED_)
