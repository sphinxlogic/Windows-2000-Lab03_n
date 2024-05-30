#if !defined(AFX_DLGBAR_H__DAF79DDE_4B08_11D1_81AB_0000F87557DB__INCLUDED_)
#define AFX_DLGBAR_H__DAF79DDE_4B08_11D1_81AB_0000F87557DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTransitionDlg dialog

//#include "Resource.h"
#include "comcat.h"

#define MAX_CLSIDS 100

class CTransitionDlg : public CDialogBar
{
public:
    void SetSuggestedQuality(ULONG ulPosition, CSliderCtrl *pSlider = NULL);
    void SetSuggestedQuality(float fQ) {SetSuggestedQuality((ULONG)(fQ * 500.0f));}
    void SetSuggestedDuration(float fDuration);
    void DirtySurface(IDXSurface *);
    void SetNumInputs(ULONG ulNumInputs);
    void SetupTime(DWORD dwTime);
    void SetSlider(CSliderCtrl *pSlider, ULONG ulPosition);
    void Animate(float fStart);
    void EnableControl(int id, BOOL bEnable);
    BOOL m_bInitializedList;
    HRESULT InitializeEffectList(CTestView *pView);
    GUID m_aclsids[MAX_CLSIDS];
    ULONG m_ulClsIdsUsed;
    CFrameWnd*  m_pFrameWnd;
    HRESULT AddCatsToList(ICatInformation *pCatInfo, const GUID & catid, CListBox *pLB);

// Construction
    CTransitionDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransitionDlg)
	enum { IDD = IDD_DLGBAR };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransitionDlg)
	protected:
        virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransitionDlg)
	afx_msg void OnPropertyPage();
	afx_msg void OnQualityIncrease();
	afx_msg void OnQualityDecrease();
	afx_msg void OnPlayForwards();
	afx_msg void OnPlayBackwards();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelchangeEffectlist();
	afx_msg void OnRadio0();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnBlend();
        afx_msg void OnDither();
	afx_msg void OnBoundsChecking();
	afx_msg void OnSelchangeComboBitdepth();
	afx_msg void OnSelchangeComboBitdepthIna();
	afx_msg void OnSelchangeComboBitdepthInb();
	afx_msg void OnDirtyA();
	afx_msg void OnDirtyB();
	afx_msg void OnRepeat();
        afx_msg void OnPerfTest();
	afx_msg void OnBounce();
	afx_msg void OnZeroPosition();
	afx_msg void OnSelchangeComboClip();
	afx_msg void OnSelchangeComboPlace();
	afx_msg void OnFlatShading();
	afx_msg void OnScaleToOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bFlatShading;
	BOOL m_bBounce;
	BOOL m_bRepeat;
        BOOL m_bPerfTest;
	void DirtyMesh(LPDIRECT3DRMMESHBUILDER3 lpMeshBuilder, int iDirection);
	int m_iDirtyDirectionA, m_iDirtyDirectionB;
};

inline void CTransitionDlg::OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler )
{
    CDialogBar::OnUpdateCmdUI( pTarget, false );
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBAR_H__DAF79DDE_4B08_11D1_81AB_0000F87557DB__INCLUDED_)
