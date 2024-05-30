// Imp_DrawDlg.h : header file
//

#import <mqoa.tlb> no_namespace
#include "MQEventHandler.h"
#include "drawarea.h"

#if !defined(AFX_IMP_DRAWDLG_H__02EE0038_FC6D_11D0_A14D_00C04FB9D5DF__INCLUDED_)
#define AFX_IMP_DRAWDLG_H__02EE0038_FC6D_11D0_A14D_00C04FB9D5DF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define MAXNUMLEN 7

/////////////////////////////////////////////////////////////////////////////
// CImp_DrawDlg dialog

class CImp_DrawDlg : public CDialog
{
// Construction
public:
	CImp_DrawDlg(CWnd* pParent = NULL);	// standard constructor
	~CImp_DrawDlg();

// Dialog Data
	//{{AFX_DATA(CImp_DrawDlg)
	enum { IDD = IDD_IMP_DRAW_DIALOG };
	CDrawArea	m_drawScribble;
	CString	m_csFriendName;
	int		m_iRadio;
	//}}AFX_DATA

	struct Line 
	{
		long X1;
		long Y1;
		long X2;
		long Y2;
	};

	_variant_t			m_vtLogin;
	_variant_t			m_vtFriendName;
	_variant_t			m_vtguidDraw;

	long	m_lLastX;
	long	m_lLastY;
	
	int			m_cLines;
	int			m_iArraySize;
	CString		m_csScreenText;
	int			m_iWasText;
	CString		m_csLogin;

	IMSMQQueuePtr		m_queue;
	IMSMQEventPtr		m_qevent;
	IMSMQQueuePtr		m_qFriend;
	IMSMQMessagePtr		m_msgOut;

	void SendMouseMovement(LINE line);
	void SendKeystroke(UINT uChar);

	void Arrived(	/*[in]*/ IDispatch* pdispQueue, 
					/*[in]*/ long lErrorCode, 
					/*[in]*/ long lCursor);

	void HandleErrors(_com_error comerr);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImp_DrawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CString GetUserName();
	CString GetComputerName();
	CString	LoginPrompt(CString DefaultName);

	CMSMQEventHandler*	m_pHandler;
	// Generated message map functions
	//{{AFX_MSG(CImp_DrawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAttach();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMP_DRAWDLG_H__02EE0038_FC6D_11D0_A14D_00C04FB9D5DF__INCLUDED_)
