// DlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "DxeTest.h"
#include "DxeFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransitionDlg dialog


CTransitionDlg::CTransitionDlg() : 
    m_ulClsIdsUsed(0),
    m_iDirtyDirectionA(1),
    m_iDirtyDirectionB(1),
    m_bRepeat(FALSE),
    m_bPerfTest(FALSE),
    m_bBounce(FALSE),
    m_bFlatShading(FALSE),
    m_bInitializedList(FALSE)
{
    //{{AFX_DATA_INIT(CTransitionDlg)
    //}}AFX_DATA_INIT
}


void CTransitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
    CDialogBar::DoDataExchange(pDX);

    if( pDX->m_bSaveAndValidate )
    {
    }
    else
    {
        if (!m_bInitializedList)
        {
            CSliderCtrl *pSB = (CSliderCtrl *)GetDlgItem( IDC_SLIDER );
            pSB->SetRange( 0, 500 );
            pSB = (CSliderCtrl *)GetDlgItem( IDC_QUALITY_SLIDER );
            pSB->SetRange( 0, 500 );
            GetDlgItem(IDC_EDIT_DURATION)->SetWindowText("1");
            InitializeEffectList(pView);
            CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_BITDEPTH);
            pCombo->SetCurSel(0);
            pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_BITDEPTH_INA);
            pCombo->SetCurSel(0);
            pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_BITDEPTH_INB);
            pCombo->SetCurSel(0);
            pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_CLIP);
            pCombo->SetCurSel(0);
            pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_PLACE);
            pCombo->SetCurSel(1);
            pView->SetPlacement(1);       
            m_bInitializedList = TRUE;
        }
    }

    //{{AFX_DATA_MAP(CTransitionDlg)
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransitionDlg, CDialogBar)
    //{{AFX_MSG_MAP(CTransitionDlg)
    ON_BN_CLICKED(IDC_PROP_PAGE, OnPropertyPage)
    ON_BN_CLICKED(IDC_QUALITY_INCREASE, OnQualityIncrease)
    ON_BN_CLICKED(IDC_QUALITY_DECREASE, OnQualityDecrease)
    ON_BN_CLICKED(IDC_PLAY_FORWARDS, OnPlayForwards)
    ON_BN_CLICKED(IDC_PLAY_BACKWARDS, OnPlayBackwards)
    ON_WM_HSCROLL()
    ON_LBN_SELCHANGE(IDC_EFFECTLIST, OnSelchangeEffectlist)
	ON_BN_CLICKED(IDC_RADIO_0, OnRadio0)
	ON_BN_CLICKED(IDC_RADIO_1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO_2, OnRadio2)
	ON_BN_CLICKED(IDC_BLEND, OnBlend)
	ON_BN_CLICKED(IDC_DITHER, OnDither)
	ON_BN_CLICKED(IDC_BOUNDSCHECKING, OnBoundsChecking)
	ON_CBN_SELCHANGE(IDC_COMBO_BITDEPTH, OnSelchangeComboBitdepth)
	ON_CBN_SELCHANGE(IDC_COMBO_BITDEPTH_INA, OnSelchangeComboBitdepthIna)
	ON_CBN_SELCHANGE(IDC_COMBO_BITDEPTH_INB, OnSelchangeComboBitdepthInb)
	ON_BN_CLICKED(IDC_DIRTY_A, OnDirtyA)
	ON_BN_CLICKED(IDC_DIRTY_B, OnDirtyB)
	ON_BN_CLICKED(IDC_REPEAT, OnRepeat)
	ON_BN_CLICKED(IDC_PERFTEST, OnPerfTest)
	ON_BN_CLICKED(IDC_BOUNCE, OnBounce)
	ON_BN_CLICKED(IDC_ZERO_POSITION, OnZeroPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_CLIP, OnSelchangeComboClip)
	ON_CBN_SELCHANGE(IDC_COMBO_PLACE, OnSelchangeComboPlace)
	ON_BN_CLICKED(IDC_FLATSHADING, OnFlatShading)
	ON_BN_CLICKED(IDC_SCALE_TO_OUT, OnScaleToOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransitionDlg message handlers
void 
CTransitionDlg::OnPropertyPage()
{
	HRESULT hr;
    CAUUID cauuid;

    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

	if (!pView || !pView->m_cpSpecifyPropertyPages)
		return;

	if (FAILED(hr = pView->m_cpSpecifyPropertyPages->GetPages(&cauuid))) {
		TRACE("Failed to get Property Pages.  Error 0x%08x. Line %d. File: %s\n",
			hr, __LINE__, __FILE__);
		return;
	}
	OleCreatePropertyFrame(m_hWnd, 0, 0, L"Testing", 1, (IUnknown **) &pView->m_cpDXTransform.p,  
		cauuid.cElems, cauuid.pElems, GetUserDefaultLCID(), 0, NULL);
	CoTaskMemFree(cauuid.pElems);
	
	// force execution and repaint
	pView->ReExecuteTransform();
}

void CTransitionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
    int iCtrlId = pScrollBar->GetDlgCtrlID();

    UINT SliderVal;

    switch(iCtrlId)
    {
    case  IDC_SLIDER:
	SliderVal = (UINT)(500.0 * pView->GetPercentComplete());
	break;
    case IDC_QUALITY_SLIDER:
	SliderVal = (UINT)(500.0f * pView->Quality());
	break;
    default:
	ASSERT(0);
	return;
    }

    if( ( nSBCode == SB_THUMBPOSITION ) || ( nSBCode == SB_THUMBTRACK ) )
    {
        SliderVal = nPos;
    }
    else if( nSBCode == SB_LINERIGHT )
    {
        ++SliderVal;
    }
    else if( nSBCode == SB_LINELEFT )
    {
        --SliderVal;
    }
    else if( nSBCode == SB_PAGERIGHT )
    {
        SliderVal += 10;
    }
    else if( nSBCode == SB_PAGELEFT )
    {
        SliderVal -= 10;
    }

    switch(iCtrlId)
    {
    case  IDC_SLIDER:
	SetSlider((CSliderCtrl *)pScrollBar, SliderVal);
	pView->SetPercentComplete( SliderVal / 500.0f);
	break;
    case IDC_QUALITY_SLIDER:
	SetSuggestedQuality(SliderVal, (CSliderCtrl *)pScrollBar);
	pView->Quality(SliderVal / 500.0f);
	break;
    }

    //--- Cause repaint
    m_pFrameWnd->GetActiveView()->InvalidateRect( NULL, false );
} /* CTransitionDlg::OnHScroll */

void CTransitionDlg::OnQualityIncrease()
{
    CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
    CWnd * pSB = (CWnd *)GetDlgItem( IDC_QUALITY );

    pSB->SetFocus();
    float SliderVal = 500.0f * pView->Quality();
    SliderVal += 5.0f;
    if(SliderVal > 500.0f)
	SliderVal = 500.0f;
    SetSuggestedQuality((ULONG)SliderVal);
    pView->Quality(SliderVal / 500.0f);
}
void CTransitionDlg::OnQualityDecrease()
{
    CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
    CWnd * pSB = (CWnd *)GetDlgItem( IDC_QUALITY );

    pSB->SetFocus();
    float SliderVal = 500.0f * pView->Quality();
    SliderVal -= 5.0;

    if(SliderVal < 0.0f)
	SliderVal = 0.0f;

    SetSuggestedQuality((ULONG)SliderVal);
    pView->Quality(SliderVal / 500.0f);
}
void CTransitionDlg::OnPlayForwards()
{
    CWnd * pSB = (CWnd *)GetDlgItem( IDC_SLIDER );
    pSB->SetFocus();
    Animate(0.0f);
} /* CTransitionDlg::OnPlayForwards */

void CTransitionDlg::OnPlayBackwards()
{
    CWnd * pSB = (CWnd *)GetDlgItem( IDC_SLIDER );
    pSB->SetFocus();
    Animate(1.0f);
} /* CTransitionDlg::OnPlayBackwards */



void 
CTransitionDlg::OnSelchangeEffectlist() 
{ 
	CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
	CListBox *pLB = (CListBox *)GetDlgItem( IDC_EFFECTLIST );
	ULONG i = pLB->GetItemData(pLB->GetCurSel());
	
	BOOL bEnable = SUCCEEDED(pView->SetTransform(m_aclsids[i]));
	BOOL bEnableEffect = (bEnable && pView->m_cpDXEffect);

        if(pView->m_cpDXTransform)
        {
            EnableControl(IDC_COMBO_PLACE, pView->m_bEnablePlacement);
            EnableControl(IDC_COMBO_CLIP, pView->m_bEnableClip);
        }
	
	EnableControl(IDC_PLAY_FORWARDS, bEnableEffect);
	EnableControl(IDC_PLAY_BACKWARDS, bEnableEffect);
	EnableControl(IDC_SLIDER, bEnableEffect);
	EnableControl(IDC_REPEAT, bEnableEffect);
	EnableControl(IDC_BOUNCE, bEnableEffect);
	EnableControl(IDC_ZERO_POSITION, bEnable && pView->m_bOutputGeo);
        EnableControl(IDC_FLATSHADING, bEnable && pView->m_bOutputGeo);
        EnableControl(IDC_PERFTEST, bEnableEffect);
	EnableControl(IDC_PROP_PAGE, (bEnable && pView->m_cpSpecifyPropertyPages));
	EnableControl(IDC_BLEND, bEnable);
        EnableControl(IDC_DITHER, bEnable);
	EnableControl(IDC_BOUNDSCHECKING, bEnable && pView->m_bOutputGeo);
        EnableControl(IDC_SCALE_TO_OUT, pView->m_cpDXScaleOutput != NULL);

        if (bEnable)
        {
            CButton *pButton = (CButton *)GetDlgItem(IDC_BLEND);
            pButton->SetCheck(pView->GetBlend());

            pButton = (CButton *)GetDlgItem(IDC_DITHER);
            pButton->SetCheck(pView->GetDither());

	    pButton = (CButton *)GetDlgItem(IDC_SCALE_TO_OUT);
	    pButton->SetCheck(pView->m_bScaleToOut);

	    if (pView->m_bOutputGeo)
	    {
		pButton = (CButton *)GetDlgItem(IDC_FLATSHADING);
		pButton->SetCheck(m_bFlatShading);
		pView->SetFlatShading(m_bFlatShading);

		pButton = (CButton *)GetDlgItem(IDC_BOUNDSCHECKING);
		BOOL bBoundsChecking = pButton->GetCheck();
		pButton->SetCheck(bBoundsChecking);
		pView->SetBoundsChecking(bBoundsChecking);
	    }
        }

        if (bEnableEffect)
        {
            CButton *pButton = (CButton *)GetDlgItem(IDC_REPEAT);
            pButton->SetCheck(m_bRepeat);
	    pButton = (CButton *)GetDlgItem(IDC_BOUNCE);
            pButton->SetCheck(m_bBounce);
        }
	
	BOOL bEnable0, bEnable1, bEnable2;
	bEnable0 = bEnable1 = bEnable2 = FALSE;
	if (bEnable) {
		bEnable0 = ((pView->m_nInputsPossible >= 0) && (pView->m_nInputsRequired <= 0));
		bEnable1 = ((pView->m_nInputsPossible >= 1) && (pView->m_nInputsRequired <= 1));
		bEnable2 = ((pView->m_nInputsPossible >= 2) && (pView->m_nInputsRequired <= 2));
	}
	EnableControl(IDC_RADIO_0, bEnable0);
	EnableControl(IDC_RADIO_1, bEnable1);
	EnableControl(IDC_RADIO_2, bEnable2);
	if (bEnable)
		CheckRadioButton(IDC_RADIO_0, IDC_RADIO_2, IDC_RADIO_0 + pView->m_nCurInputsUsed);
	
	CSliderCtrl *pSB = (CSliderCtrl *)GetDlgItem( IDC_SLIDER );
	SetSlider(pSB, (UINT)(500.0f * pView->GetPercentComplete()));

	DWORD dwMiscFlags;
	if(pView->m_cpDXTransform &&
	    SUCCEEDED(pView->m_cpDXTransform->GetMiscFlags(&dwMiscFlags)) &&
	    (dwMiscFlags & DXTMF_QUALITY_SUPPORTED))
	{
	    SetSuggestedQuality((ULONG)(pView->Quality() * 500.0f));
	    EnableControl(IDC_QUALITY_SLIDER, bEnable);
	    EnableControl(IDC_QUALITY, bEnable);
	    EnableControl(IDC_QUALITY_DECREASE, bEnable);
	    EnableControl(IDC_QUALITY_INCREASE, bEnable);
	}
	else
	{
	    EnableControl(IDC_QUALITY, FALSE);
	    EnableControl(IDC_QUALITY_DECREASE, FALSE);
	    EnableControl(IDC_QUALITY_INCREASE, FALSE);
	    EnableControl(IDC_QUALITY_SLIDER, FALSE);
	}
}


void AddClassToList(CListBox *pLB, HKEY hkClsIdRoot, CLSID & clsid, ULONG Index)
{
    OLECHAR szGUID[MAX_PATH];
    StringFromGUID2(clsid, szGUID, sizeof(szGUID));
#ifndef _UNICODE
    char szTcharGUID[MAX_PATH];
    WideCharToMultiByte(CP_ACP, 0, szGUID, -1, szTcharGUID, MAX_PATH, NULL, NULL);
#else
#define szTcharGUID szGUID
#endif
    TCHAR szDescription[MAX_PATH];
    LONG cbSize = sizeof(szDescription);
    LONG rrv = RegQueryValue(hkClsIdRoot, szTcharGUID, szDescription, &cbSize);
    if (rrv == ERROR_SUCCESS) {
        pLB->SetItemData(pLB->AddString(szDescription), Index);
    }
}



HRESULT CTransitionDlg::AddCatsToList(ICatInformation *pCatInfo, const GUID & catid, CListBox *pLB)
{
    IEnumCLSID *pEnumCLSID;
    HRESULT hr = pCatInfo->EnumClassesOfCategories(1, (GUID *)&catid, 0, NULL, &pEnumCLSID);

    if (SUCCEEDED(hr)) {
        ULONG ulUsed;
        pEnumCLSID->Next(MAX_CLSIDS - m_ulClsIdsUsed, m_aclsids + m_ulClsIdsUsed, &ulUsed);
        pEnumCLSID->Release();

        HKEY hkClsIdRoot;
        RegOpenKey(HKEY_CLASSES_ROOT, TEXT("CLSID"), &hkClsIdRoot);
        for (ULONG i = m_ulClsIdsUsed; i < m_ulClsIdsUsed+ulUsed; i++)
        {
            AddClassToList(pLB, hkClsIdRoot, m_aclsids[i], i);
        }
        RegCloseKey(hkClsIdRoot);
        m_ulClsIdsUsed += ulUsed;
    }
    else
    {
    	TRACE("Failed to Enum Classes Of Categories.  Error 0x%08x. Line %d. File: %s\n",
			hr, __LINE__, __FILE__);
    }
    return hr;
}



HRESULT CTransitionDlg::InitializeEffectList(CTestView * pView)
{
    ICatInformation *pCatInfo;
//    CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
    CListBox *pLB = (CListBox *)GetDlgItem( IDC_EFFECTLIST );
    HRESULT hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC, IID_ICatInformation, (void **)&pCatInfo);
    if (SUCCEEDED(hr)) {
        hr = AddCatsToList(pCatInfo, CATID_DXImageTransform, pLB);
        if (SUCCEEDED(hr) && pView->m_cpD3DRM)
        {
            hr = AddCatsToList(pCatInfo, CATID_DX3DTransform, pLB);
        }
        pCatInfo->Release();
    }
    else
    {
    	TRACE("Failed CoCreateInstance of Standard Conponent Categories.  Error 0x%08x. Line %d. File: %s\n",
			hr, __LINE__, __FILE__);
    }
    pLB->SetCurSel(0);
    OnSelchangeEffectlist();
    return hr;
}

void CTransitionDlg::EnableControl(int id, BOOL bEnable)
{
    CWnd *pWnd = (CWnd *)GetDlgItem(id);
    pWnd->EnableWindow(bEnable);
}

void CTransitionDlg::Animate(float fStart)
{
    CString Text;
    GetDlgItem(IDC_EDIT_DURATION)->GetWindowText(Text);
    float Duration = (float)atof(Text);
    if (Duration < 0.01f)
    {
        Duration = 1.0f;
        GetDlgItem(IDC_EDIT_DURATION)->SetWindowText("1");
    }

    ((CMainFrame*)m_pFrameWnd)->m_wndStatusBar.SetPaneText( 0, "Press ESC to stop animation" );


    CTestView* pView = ((CTestApp*)AfxGetApp())->m_pView;
    float PercentComplete = fStart;
    BOOL bBackward = (fStart > 0.5f);
    BOOL bContinue = m_bRepeat || m_bBounce;

    CSliderCtrl *pSB = (CSliderCtrl *)GetDlgItem( IDC_SLIDER );
    
    pView->m_cpDXEffect->put_Duration( Duration );
    DWORD msStartTime = timeGetTime();
    DWORD msCurTime;
    ULONG ulFrames = 0;

    pView->m_bDontRender = m_bPerfTest;

    do
    {
	do
	{
	    if ((GetAsyncKeyState(VK_ESCAPE) & 1) == 1)
	    {
		bContinue = FALSE;
		break;
	    }
            if (!m_bPerfTest)
            {
	        SetSlider(pSB, (UINT)(PercentComplete * 500.));
            }
            RECT r;
            pView->SetPercentComplete(PercentComplete, pView->Get2DOutRect(r) ? &r : NULL);
	    //--- Next
            msCurTime = timeGetTime();
	    PercentComplete = (float)(( (msCurTime - msStartTime) / 1000. ) / Duration);
	    if (bBackward)
	    {
		PercentComplete = 1.0f - PercentComplete;
	    }
	    ++ulFrames;
	} while( PercentComplete >= 0. && PercentComplete <= 1. );

        if ((!m_bPerfTest) || (!bContinue))
        {
            SetSlider(pSB, bBackward ? 0 : 500 );
        }
	pView->SetPercentComplete(bBackward ? 0.f : 1.f);

	TCHAR szFrames[100];
        if (msCurTime > msStartTime)
        {
            double fTime = (double)(msCurTime-msStartTime) / 1000.;
            if (bContinue)
            {
	        sprintf( szFrames, _T("Frames/Sec = %.2f  (Press ESC to stop)"), (double)ulFrames / fTime );
            }
            else
            {
	        sprintf( szFrames, _T("Frames/Sec = %.2f"), (double)ulFrames / fTime );
            }
	    ((CMainFrame*)m_pFrameWnd)->m_wndStatusBar.SetPaneText( 0, szFrames );
        }
        else
        {
	    ((CMainFrame*)m_pFrameWnd)->m_wndStatusBar.SetPaneText( 0, _T("No frames rendered") );
        }

	ulFrames = 0;
	if(m_bBounce)
	{
	    bBackward = !bBackward;
	}
        //
        //  Now pause for 1 second at each end
        //
        if (!m_bPerfTest)
        {
            for (ULONG t = 0; t < 10 && bContinue; t++)
            {
                Sleep(100);
                if ((GetAsyncKeyState(VK_ESCAPE) & 1) == 1)
                {
		    bContinue = FALSE;
	        }
            }
        }
	msStartTime = timeGetTime();
        msCurTime = msStartTime;
    } while(bContinue);

    pView->m_bDontRender = FALSE;
    pView->ReExecuteTransform();

}

void CTransitionDlg::SetSlider(CSliderCtrl * pSlider, ULONG ulPosition)
{

    pSlider->SetPos(ulPosition);
    TCHAR szCaption[100];
    wsprintf(szCaption, _T("Progress %lu%%"), ulPosition / 5);
    GetDlgItem(IDC_PROGRESS_PERCENT)->SendMessage(WM_SETTEXT, 0, (LPARAM)szCaption); 
}


void CTransitionDlg::OnRadio0() 
{
    SetNumInputs(0);	
}

void CTransitionDlg::OnRadio1() 
{
    SetNumInputs(1);	
}

void CTransitionDlg::OnRadio2() 
{
    SetNumInputs(2);	
}


void 
CTransitionDlg::SetNumInputs(ULONG nInputs)
{
	CheckRadioButton(IDC_RADIO_0, IDC_RADIO_2, IDC_RADIO_0 + nInputs);
	CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
	if (pView == NULL)
		return;
	pView->SetDesiredInputs(nInputs);
}

void 
CTransitionDlg::SetupTime(DWORD dwTime)
{
    TCHAR szCaption[100];
    sprintf(szCaption, _T("Setup time: %0.4f"), float(dwTime)/1000.f);
    //
    //  During initialization we can get here before the status bar m_hWnd has been
    //  initialized.  Just return.
    //  
    if (((CMainFrame*)m_pFrameWnd)->m_wndStatusBar.m_hWnd)
    {
        ((CMainFrame*)m_pFrameWnd)->m_wndStatusBar.SetPaneText( 0, szCaption );
    }
}

void CTransitionDlg::OnBlend() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CButton *pButton = (CButton *)GetDlgItem(IDC_BLEND);
    BOOL bBlend = pButton->GetCheck();
    pButton->SetCheck(pView->SetBlend(bBlend));
}

void CTransitionDlg::OnDither() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CButton *pButton = (CButton *)GetDlgItem(IDC_DITHER);
    BOOL bDither = pButton->GetCheck();
    pButton->SetCheck(pView->SetDither(bDither));
}



void CTransitionDlg::OnBoundsChecking() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CButton *pButton = (CButton *)GetDlgItem(IDC_BOUNDSCHECKING);
    BOOL bBoundsChecking = pButton->GetCheck();
    pButton->SetCheck(pView->SetBoundsChecking(bBoundsChecking));
}

void CTransitionDlg::OnSelchangeComboBitdepth() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_BITDEPTH);
    pView->SetBitDepth(pCombo->GetCurSel());
}

void CTransitionDlg::OnSelchangeComboBitdepthIna() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_BITDEPTH_INA);
    pView->SetInputBitDepth(0, pCombo->GetCurSel());
}

void CTransitionDlg::OnSelchangeComboBitdepthInb() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_BITDEPTH_INB);
    pView->SetInputBitDepth(1, pCombo->GetCurSel());
}

void CTransitionDlg::OnDirtyA() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL || pView->m_cpBitDepthCorrectInSurf[0] == NULL)
	        return;
    DirtySurface(pView->m_cpBitDepthCorrectInSurf[0]);

    if (pView->m_cpInMeshA)
    {
        DirtyMesh(pView->m_cpInMeshA, m_iDirtyDirectionA);
        m_iDirtyDirectionA = -m_iDirtyDirectionA;
    }
    m_pFrameWnd->GetActiveView()->InvalidateRect( NULL, false );
}

void CTransitionDlg::OnDirtyB() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL || pView->m_cpBitDepthCorrectInSurf[1] == NULL)
	    return;
    DirtySurface(pView->m_cpBitDepthCorrectInSurf[1]);

    if (pView->m_cpInMeshB)
    {
        DirtyMesh(pView->m_cpInMeshB, m_iDirtyDirectionB);
        m_iDirtyDirectionB = -m_iDirtyDirectionB;
    }
    m_pFrameWnd->GetActiveView()->InvalidateRect( NULL, false );
}

void CTransitionDlg::DirtySurface(IDXSurface * pSurface)
{
    HRESULT hr;
    CDXDBnds bnds(pSurface, hr);
    if (SUCCEEDED(hr))
    {
        CComPtr <IDXARGBReadWritePtr> cpPtr;
        hr = pSurface->LockSurface(NULL, INFINITE, DXLOCKF_READWRITE, 
                                   IID_IDXARGBReadWritePtr, (void **)&cpPtr, NULL);
        if (SUCCEEDED(hr))
        {
            ULONG Height = bnds.Height();
            ULONG Width = bnds.Width();
            DXSAMPLE * pBuffer = DXSAMPLE_Alloca(Width);
            for (ULONG Row = 0; Row < Height; Row++)
            {
                cpPtr->MoveToRow(Row);
                cpPtr->Unpack(pBuffer, Width, FALSE);
                for (ULONG Col = 0; Col < Width; Col++)
                {
                    DWORD dwCur = pBuffer[Col];
                    dwCur ^= 0x00FFFFFF;
                    pBuffer[Col] = dwCur;
                }
                cpPtr->PackAndMove(pBuffer, Width);
            }
        }
    }
}

void CTransitionDlg::DirtyMesh(LPDIRECT3DRMMESHBUILDER3 lpMeshBuilder, int iDirection)
{
    D3DRMBOX boxMesh;

    lpMeshBuilder->GetBox(&boxMesh);
    const float fDeltaX = iDirection * (boxMesh.max.x - boxMesh.min.x)/10.0f;
    const float fDeltaY = iDirection * (boxMesh.max.y - boxMesh.min.y)/10.0f;
    const float fDeltaZ = iDirection * (boxMesh.max.z - boxMesh.min.z)/10.0f;

    const int ciNumVertices = lpMeshBuilder->GetVertexCount();
    int iVertexNum;

    for(iVertexNum = 0; iVertexNum < ciNumVertices; iVertexNum++)
    {
	D3DVECTOR d3dVector;

	HRESULT hr = lpMeshBuilder->GetVertex(iVertexNum,&d3dVector);
	_ASSERT(hr == DD_OK);
	hr = lpMeshBuilder->SetVertex(iVertexNum,
				d3dVector.x + fDeltaX,
				d3dVector.y + fDeltaY,
				d3dVector.z + fDeltaZ);
	_ASSERT(hr == DD_OK);
    }
}

void CTransitionDlg::OnRepeat() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_REPEAT);
    m_bRepeat = pButton->GetCheck();
    if(m_bRepeat)   // Turn off the Bouncing?
    {
	m_bBounce = FALSE;
	pButton = (CButton *)GetDlgItem(IDC_BOUNCE);
	pButton->SetCheck(0);
    }
}

void CTransitionDlg::SetSuggestedDuration(float fDuration)
{
    CString csText;

    csText.Format("%.1f", fDuration);
    CWnd *lpcwndDuration = GetDlgItem(IDC_EDIT_DURATION);
    if(lpcwndDuration)
	lpcwndDuration->SetWindowText(csText);
}

void CTransitionDlg::OnBounce() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_BOUNCE);
    m_bBounce = pButton->GetCheck();
    if(m_bBounce)    // Turn off the Repeat?
    {
	m_bRepeat = FALSE;
	pButton = (CButton *)GetDlgItem(IDC_REPEAT);
	pButton->SetCheck(0);
    }
}

void CTransitionDlg::OnZeroPosition() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	return;

    pView->ZeroPosition();
}


void CTransitionDlg::OnPerfTest() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_PERFTEST);
    m_bPerfTest = pButton->GetCheck();
}

void CTransitionDlg::SetSuggestedQuality(ULONG ulPosition, CSliderCtrl *pSB)
{
    if(!pSB)
    {
	pSB = (CSliderCtrl *)GetDlgItem( IDC_QUALITY_SLIDER );
    }

    ASSERT(pSB);
    pSB->SetPos(ulPosition);

    TCHAR szCaption[100];
    wsprintf(szCaption, _T("Quality %lu%%"), ulPosition / 5);
    GetDlgItem(IDC_QUALITY)->SendMessage(WM_SETTEXT, 0, (LPARAM)szCaption); 
}

void CTransitionDlg::OnSelchangeComboClip() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_CLIP);
    pView->SetClip(pCombo->GetCurSel());
}

void CTransitionDlg::OnSelchangeComboPlace() 
{
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    if (pView == NULL)
	    return;
    CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO_PLACE);
    pView->SetPlacement(pCombo->GetCurSel());

}

void CTransitionDlg::OnFlatShading() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_FLATSHADING);
    m_bFlatShading = pButton->GetCheck();

    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    pView->SetFlatShading(m_bFlatShading);
}

void CTransitionDlg::OnScaleToOut() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_SCALE_TO_OUT);
    CTestView *pView = ((CTestApp *) AfxGetApp())->m_pView;
    pView->SetScaleOutput(pButton->GetCheck());
}
