// ExplodeProp.cpp : Implementation of CExplodeProp
#include "stdafx.h"
#include <dxtmsft.h>
#include "explode.h"
#include "ExplodeProp.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
// CExplodeProp

ULONG CExplodeProp::GetDlgItemInt(int id)
{
    TCHAR *pEnd;
    TCHAR szItemText[20];
    GetDlgItemText(id, szItemText, 20);
    return (ULONG)strtod(szItemText, &pEnd);
}

float CExplodeProp::GetDlgItemFloat(int id)
{
    TCHAR *pEnd;
    TCHAR szItemText[20];
    GetDlgItemText(id, szItemText, 20);
    return (float)strtod(szItemText, &pEnd);
}
void CExplodeProp::SetDlgItemFloat(int id, float val)
{
    TCHAR szItem[20];
    _stprintf(szItem, _T("%.2f"), val);
    SetDlgItemText(id, szItem);
}

LRESULT CExplodeProp::OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    CComQIPtr<IExplode, &IID_IExplode> pExplode(m_ppUnk[0]);
   
    BOOL b;
	pExplode->get_Tumble( &b);
	CheckDlgButton(IDC_Explode_Tumble, b);
	
	long v;
    pExplode->get_MaxRotations(&v);
	SetDlgItemInt(IDC_Explode_MaxRotations, v);
	
	float m;
	pExplode->get_FinalVelocity( &m);
	SetDlgItemFloat(IDC_Explode_FinalVelocity, m); 
	
	pExplode->get_PositionJump( &m);
	SetDlgItemFloat(IDC_Explode_PositionJump, m); 

	pExplode->get_DecayTime( &m);
	SetDlgItemFloat(IDC_Explode_DecayTime, m); 

    /////////////////////
    return TRUE;
}

LRESULT CExplodeProp::OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled)
{
    SetDirty(TRUE);
    return 0;
}


STDMETHODIMP CExplodeProp::Apply(void)
{
    
	ATLTRACE(_T("CExplodeProp::Apply\n"));
    for (UINT i = 0; i < m_nObjects; i++)
    {
        CComQIPtr<IExplode, &IID_IExplode> pExplode( m_ppUnk[i] );
//        TCHAR szText[40];
//        GetDlgItemText(IDC_Origin, szText, 40);
//        TCHAR *pEnd;
//        ULONG x = (ULONG)strtod(szText, &pEnd);
//        ULONG y = (ULONG)strtod(pEnd+1, &pEnd);

		pExplode->put_Tumble(IsDlgButtonChecked(IDC_Explode_Tumble));
		pExplode->put_MaxRotations(GetDlgItemInt(IDC_Explode_MaxRotations));
		
		pExplode->put_FinalVelocity(GetDlgItemFloat(IDC_Explode_FinalVelocity));
		pExplode->put_PositionJump(GetDlgItemFloat(IDC_Explode_PositionJump));
		pExplode->put_DecayTime(GetDlgItemFloat(IDC_Explode_DecayTime));
    } 
    m_bDirty = FALSE; 
    return S_OK;
}

