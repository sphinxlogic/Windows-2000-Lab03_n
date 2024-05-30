// NShowMFCDlg.h : header file
//

#if !defined(AFX_NSHOWMFCDLG_H__4DD2ED98_AE23_11D1_9F80_00C04FD7AC7F__INCLUDED_)
#define AFX_NSHOWMFCDLG_H__4DD2ED98_AE23_11D1_9F80_00C04FD7AC7F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CNShowMFCDlg dialog
class CNShowMFCDlg : public CDialog
{
// Construction
public:
	CNShowMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNShowMFCDlg)
	enum { IDD = IDD_NSHOWMFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNShowMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNShowMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnPlay();
	afx_msg void OnBtnPause();
	afx_msg void OnBtnStop();
	afx_msg void OnScriptCommandMediaplayer1(LPCTSTR scType, LPCTSTR Param);
	afx_msg void OnMarkerHitMediaplayer1(long MarkerNum);
	afx_msg void OnOpenStateChangeMediaplayer1(long OldState, long NewState);
	afx_msg void OnPlayStateChangeMediaplayer1(long OldState, long NewState);
	afx_msg void OnReadyStateChangeMediaplayer1(long ReadyState);
	afx_msg void OnBufferingMediaplayer1(BOOL Start);
	afx_msg void OnFileOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    int m_CurrentTime;

    void calc_time (double, int *, int *);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSHOWMFCDLG_H__4DD2ED98_AE23_11D1_9F80_00C04FD7AC7F__INCLUDED_)
