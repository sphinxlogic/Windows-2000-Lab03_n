//--odlist.cpp----------------------------------------------------------------
//
// implementation of the COwnerDrawListBox class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "oditem.h"
#include "odlist.h"
#include "miscgdi.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox

IMPLEMENT_DYNCREATE(COwnerDrawListBox, CListBox)

BEGIN_MESSAGE_MAP(COwnerDrawListBox, CListBox)
    //{{AFX_MSG_MAP(COwnerDrawListBox)
    ON_WM_GETDLGCODE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

COwnerDrawListBox::COwnerDrawListBox ()
{
    m_nCurSel = -1;
}

COwnerDrawListBox::~COwnerDrawListBox ()
{
}

int COwnerDrawListBox::SetCurSel (int index)
{
    if ((index != LB_ERR) && (index < GetCount()))
    {
        COwnerDrawItem *pODI = GetODI (index);
        ASSERTERROR (pODI != NULL, "No owner draw item object found");
    
        if (pODI->m_dwFlags & ODI_DISABLED) // can not select disabled item
        {
            MessageBeep (0);
            // check if previous selection is not disabled and if so - find undesabled one
            COwnerDrawItem *pODIPrev = GetODI (m_nCurSel);
            COwnerDrawItem *pODINext;
            int             nCount   = GetCount ();
            int             i;
                                      
            // select first enabled                                      
            if (pODIPrev->m_dwFlags & ODI_DISABLED)          
            {
                m_nCurSel = -1;
                for (i = 0; i < nCount; i++)
                {
                    pODINext = GetODI (i);
                    ASSERTERROR (pODINext != NULL,"No owner draw item found");
                    if (!(pODINext->m_dwFlags & ODI_DISABLED))
                    {
                        m_nCurSel = i;
                        break;
                    }    
                }    
            }
        }                                    
        else
        {
            m_nCurSel = index;
        }    
    }    
    else
    {
        m_nCurSel = index;
    }                 
    
    return CListBox::SetCurSel (m_nCurSel);
}
    
void COwnerDrawListBox::EnableString (int index, BOOL bEnable)
{
    ASSERTERROR (index != LB_ERR, "Invalid index used");
    
    COwnerDrawItem *pODI = GetODI (index);
    ASSERTERROR (pODI != NULL, "No owner draw item found");
    
    if (bEnable)
    {
        pODI->m_dwFlags &= ~(DWORD) ODI_DISABLED;
        pODI->m_crText   = RGB (0, 0, 0);
    }
    else
    {
        pODI->m_dwFlags |= ODI_DISABLED; 
        pODI->m_crText   = GetSysColor (COLOR_GRAYTEXT);
    }        
}

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox diagnostics

#ifdef _DEBUG
void COwnerDrawListBox::AssertValid() const
{
    CListBox::AssertValid();
}

void COwnerDrawListBox::Dump(CDumpContext& dc) const
{
    CListBox::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox commands

/////////////////////////////////////////////////////////////////////////////
// OWNER DRAW stuff

void COwnerDrawListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
    // all items are of fixed size
    // must use LBS_OWNERDRAWVARIABLE for this to work
    lpMIS->itemHeight = 20;
}

void COwnerDrawListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    ::DrawItem (lpDIS);    
}

void COwnerDrawListBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
    COwnerDrawItem *pItem = (COwnerDrawItem *)lpDeleteItemStruct->itemData;
    ASSERT_VALID (pItem);
    
    if (pItem->m_dwFlags & ODI_DELOBJECT)
        delete pItem->m_pObject;
                
    delete pItem;   
    SendMessage (LB_SETITEMDATA, lpDeleteItemStruct->itemID, NULL);  
}

UINT COwnerDrawListBox::OnGetDlgCode()
{
    return (DLGC_WANTMESSAGE | CListBox::OnGetDlgCode());
}
                                        
#ifdef _DEBUG
#define _MSX_INLINE
#include "odlist.inl"
#endif
