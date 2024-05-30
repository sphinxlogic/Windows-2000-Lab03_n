// RipProp.cpp : Implementation of CRipProp
#include "stdafx.h"
#include "ripple.h"
#include "RipProp.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
// CRipProp

void CRipProp::SetDlgItemFloat(int id, float val)
{
    TCHAR szItem[20];
    _stprintf(szItem, _T("%.2f"), val);
    SetDlgItemText(id, szItem);
}

LRESULT CRipProp::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    TCHAR szItem[40];
    CComQIPtr<IRipple, &IID_IRipple> pRipple(m_ppUnk[0]);
    float x, y;
    pRipple->get_XOrigin(&x);
    pRipple->get_YOrigin(&y);
    _stprintf(szItem, _T("%.2f, %.2f"), x, y);
    SetDlgItemText(IDC_ORIGIN, szItem);
    float v;
    pRipple->get_Wavelength(&v);
    SetDlgItemFloat(IDC_WAVELEN, v);
    pRipple->get_Amplitude(&v);
    SetDlgItemFloat(IDC_AMPLITUDE, v);
    long n;
    pRipple->get_NumberOfWaves(&n);
    SetDlgItemInt(IDC_NUMWAVES, n);
    pRipple->get_MinSteps(&n);
    SetDlgItemInt(IDC_MINSTEPS, n);
    pRipple->get_MaxSteps(&n);
    SetDlgItemInt(IDC_MAXSTEPS, n);
    return TRUE;
}


HRESULT CRipProp::ShowError(void)
{
    USES_CONVERSION;
    CComPtr<IErrorInfo> pError;
    CComBSTR            strError;
    GetErrorInfo(0, &pError);
    MessageBox(OLE2T(strError), _T("Error"), MB_ICONEXCLAMATION);
    return E_FAIL;
}

float CRipProp::GetDlgItemFloat(int id)
{
    TCHAR *pEnd;
    TCHAR szItemText[20];
    GetDlgItemText(id, szItemText, 20);
    return (float)strtod((const char*)szItemText, (char**)&pEnd);
}

STDMETHODIMP CRipProp::Apply(void)
{
    ATLTRACE(_T("CPolyProp::Apply\n"));
    for (UINT i = 0; i < m_nObjects; i++)
    {
        CComQIPtr<IRipple, &IID_IRipple> pRipple(m_ppUnk[i]);
        TCHAR szText[40];
        GetDlgItemText(IDC_ORIGIN, szText, sizeof(szText));
        TCHAR *pEnd;
        float x = (float)strtod((const char*)szText, (char**)&pEnd);
        if (*pEnd != ',') {
            MessageBox(_T("Origin must be entered as x, y"), _T("Error"), MB_ICONEXCLAMATION);
            return E_FAIL;
        }
        float y = (float)strtod((const char*)pEnd+1, (char**)&pEnd);

        if FAILED(pRipple->put_XOrigin(x)) {
            return ShowError();
        }
        if FAILED(pRipple->put_YOrigin(y)) {
            return ShowError();
        }

        if FAILED(pRipple->put_Wavelength(GetDlgItemFloat(IDC_WAVELEN))) {
            return ShowError();
        }

        if FAILED(pRipple->put_Amplitude(GetDlgItemFloat(IDC_AMPLITUDE))) {
            return ShowError();
        }

        if FAILED(pRipple->put_NumberOfWaves(GetDlgItemInt(IDC_NUMWAVES))) {
            return ShowError();
        }

        if FAILED(pRipple->put_MinSteps(GetDlgItemInt(IDC_MINSTEPS))) {
            return ShowError();
        }

        if FAILED(pRipple->put_MaxSteps(GetDlgItemInt(IDC_MAXSTEPS))) {
            return ShowError();
        }
    }
    m_bDirty = FALSE; 
    return S_OK;
}

LRESULT CRipProp::OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
    SetDirty(TRUE);
    return 0;
}

