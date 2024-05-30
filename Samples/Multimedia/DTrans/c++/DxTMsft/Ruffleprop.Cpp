// RuffleProp.cpp : Implementation of CRuffleProp
#include "stdafx.h"


#include <dxtmsft.h>
#include "Ruffle.h"
#include "RuffleProp.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
// CRuffleProp

// CRuffleProp

ULONG CRuffleProp::GetDlgItemInt(int id)
{
    TCHAR *pEnd;
    TCHAR szItemText[20];
    GetDlgItemText(id, szItemText, 20);
    return (ULONG)strtod(szItemText, &pEnd);
}



LRESULT CRuffleProp::OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    CComQIPtr<IRuffle, &IID_IRuffle> pRuffle(m_ppUnk[0]);
	LONG v;
    pRuffle->get_MaxRotations(&v);
	SetDlgItemInt(IDC_Ruffle_MaxRotations, v);
    return TRUE;
}

LRESULT CRuffleProp::OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
    SetDirty(TRUE);
    return 0;
}


STDMETHODIMP CRuffleProp::Apply(void)
{
    
	ATLTRACE(_T("CRuffleProp::Apply\n"));
    for (UINT i = 0; i < m_nObjects; i++)
    {
        CComQIPtr<IRuffle, &IID_IRuffle> pRuffle( m_ppUnk[i] );
		pRuffle->put_MaxRotations(GetDlgItemInt(IDC_Ruffle_MaxRotations));
    } 
    m_bDirty = FALSE; 
    return S_OK;
}

