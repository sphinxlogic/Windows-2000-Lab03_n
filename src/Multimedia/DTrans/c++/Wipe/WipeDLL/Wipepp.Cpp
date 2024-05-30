// WipePP.cpp : Implementation of CDXTWipePropPage
#include "stdafx.h"
#include "WipePP.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
// CDXTWipePropPage

LRESULT CDXTWipePropPage::
    OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    TCHAR szItem[20];
    CComQIPtr<IDXTWipeSample, &IID_IDXTWipeSample> cpWipe(m_ppUnk[0]);
    float GradSize;
    cpWipe->get_GradientSize( &GradSize );
     _stprintf( szItem, _T("%.2f"), GradSize );
    SetDlgItemText( IDC_GRAD_SIZE, szItem );

    CComQIPtr<IDXEffect, &IID_IDXEffect> cpEffect( m_ppUnk[0] );
    float Duration;
    cpEffect->get_Duration( &Duration );
     _stprintf( szItem, _T("%.2f"), Duration );
    SetDlgItemText( IDC_DURATION, szItem );

    //--- Init the combo box
    DXWIPEDIRECTION WipeStyle;
    cpWipe->get_WipeStyle( &WipeStyle );
//    SendDlgItemMessage( IDC_WIPE_STYLE, CB_ADDSTRING,  );
    return TRUE;
}

STDMETHODIMP CDXTWipePropPage::Apply(void)
{
    ATLTRACE(_T("CPolyProp::Apply\n"));
    for (UINT i = 0; i < m_nObjects; i++)
    {
        CComQIPtr<IDXTWipeSample, &IID_IDXTWipeSample> cpWipe( m_ppUnk[i] );
        float GradSize = GetDlgItemFloat( IDC_GRAD_SIZE );
        cpWipe->put_GradientSize( GradSize );

        CComQIPtr<IDXEffect, &IID_IDXEffect> cpEffect( m_ppUnk[i] );
        float Duration = GetDlgItemFloat( IDC_DURATION );
        cpEffect->put_Duration( Duration );

//        DXWIPEDIRECTION WipeStyle;
//        WipeStyle = (DXWIPEDIRECTION)GetDlgItemInt( IDC_WIPE_STYLE, NULL, false );
//        cpWipe->put_WipeStyle( WipeStyle );
    }
    m_bDirty = FALSE; 
    return S_OK;
}

float CDXTWipePropPage::GetDlgItemFloat(int id)
{
    TCHAR *pEnd;
    TCHAR szItemText[20];
    GetDlgItemText(id, szItemText, 20);
    return (float)strtod(szItemText, &pEnd);
}

LRESULT CDXTWipePropPage::OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
    SetDirty(TRUE);
    return 0;
}

