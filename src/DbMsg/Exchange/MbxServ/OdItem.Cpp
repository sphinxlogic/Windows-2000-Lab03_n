//--dabout.cpp----------------------------------------------------------------
//
// implementation of the COwnerDrawItem class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "oditem.h"
#include "miscgdi.h" 

#define new DEBUG_NEW
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawItem

IMPLEMENT_DYNAMIC(COwnerDrawItem, CObject)

COwnerDrawItem::COwnerDrawItem()
 : m_crText (GetSysColor (COLOR_WINDOWTEXT))
{ 
}

COwnerDrawItem::~COwnerDrawItem()
{
}

void COwnerDrawItem::Create (CObject *pObject, const char *szDescription,
                             DWORD dwFlags)
{
    m_pObject           = pObject;
    m_strDescription    = szDescription;
    m_dwFlags           = dwFlags;                    
}

COwnerDrawItem& COwnerDrawItem::operator= (const COwnerDrawItem &rhs)
{    
    if (this == &rhs)
        return *this;

    m_strDescription = rhs.m_strDescription;
    m_pObject        = rhs.m_pObject;         
    m_dwFlags        = rhs.m_dwFlags;  
    m_crText         = rhs.m_crText;  
    m_crBkText       = rhs.m_crBkText;
    
    return *this;
}
/////////////////////////////////////////////////////////////////////////////
// COwnerDrawItem diagnostics

#ifdef _DEBUG
void COwnerDrawItem::AssertValid() const
{
    CObject::AssertValid();
}

void COwnerDrawItem::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
}
#endif
