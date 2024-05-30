//--miscdgi.cpp---------------------------------------------------------------
//
// implementation of the DrawItem
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "miscgdi.h" 
#include "oditem.h"

#define EXTRA_X 5

void DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC);
    COwnerDrawItem *pODI = (COwnerDrawItem *)lpDIS->itemData;

    if ((pODI == NULL) || (pODI == (COwnerDrawItem*)0xFFFFFFFF))
    {   
        TRACE ("COwnerDrawListBox::DrawItem - Got invalid data\n");
        return;
    }
    
    COLORREF crOldTextColor;
    COLORREF crOldBkColor;

    CString strText (pODI->m_strDescription);

    CFont fnBold;
	CFont * pOldFont = NULL;
	if (pODI->m_dwFlags & ODI_BOLDTEXT)
	{
		TEXTMETRIC tm;
		LOGFONT lf;
		CString strFont;

		memset (&lf, 0, sizeof (LOGFONT));

		pDC->GetTextMetrics (&tm);
		lf.lfHeight = tm.tmHeight;
		lf.lfWeight = 700;

		
		pDC->GetTextFace(strFont);
		strncpy (lf.lfFaceName, strFont, 32);
		fnBold.CreateFontIndirect(&lf);

		pOldFont = pDC->SelectObject (&fnBold);
	}

	// rcSelection is to move the selection rect over to the right 
	CRect rcSelection (lpDIS->rcItem);

    if ( (lpDIS->itemAction & ODA_DRAWENTIRE) || (lpDIS->itemAction & ODA_SELECT) )
    {
        if (lpDIS->itemState & ODS_SELECTED)
        {
            // item is selected
            COLORREF crHighlight		= GetSysColor (COLOR_HIGHLIGHT);
			COLORREF crHighlightText	= GetSysColor (COLOR_HIGHLIGHTTEXT);
            crOldTextColor = pDC->SetTextColor (crHighlightText);
            crOldBkColor = pDC->SetBkColor (crHighlight);   // For DrawText below
            CBrush br(crHighlight);
            CBrush bk(GetSysColor (COLOR_WINDOW));
            pDC->FillRect(&lpDIS->rcItem, &bk);
			pDC->FillRect(rcSelection, &br);
        }
    
        if (!lpDIS->itemState & ODS_SELECTED)
        {
            // Item has been de-selected -- remove frame
            crOldTextColor = pDC->SetTextColor (pODI->m_crText);
            CBrush br(GetSysColor (COLOR_WINDOW));
            pDC->FillRect(&lpDIS->rcItem, &br);
        }            
        
        CRect rcText (lpDIS->rcItem);

		rcText.left += EXTRA_X;
        pDC->DrawText (strText, -1, rcText, DT_LEFT);
    }
    
    if ((lpDIS->itemState & ODS_FOCUS) &&
        (lpDIS->itemAction & (ODA_FOCUS | ODA_DRAWENTIRE)))
    {
        // Item has gotten the focus
        // DrawFocusRect (lpDIS->hDC, &lpDIS->rcItem);
		DrawFocusRect (lpDIS->hDC, rcSelection);
    }
    
    if (!(lpDIS->itemState & ODS_FOCUS) &&
        (lpDIS->itemAction & ODA_FOCUS))
    {
        // Item has lost focus
        // DrawFocusRect (lpDIS->hDC, &lpDIS->rcItem);
		DrawFocusRect (lpDIS->hDC, rcSelection);
    }
                              
	// Cleanup
	if (pODI->m_dwFlags & ODI_BOLDTEXT)
	{
		pDC->SelectObject (pOldFont);
		fnBold.DeleteObject();
	}

    if ( (lpDIS->itemAction & ODA_DRAWENTIRE) || (lpDIS->itemAction & ODA_SELECT) )
    {
        if (lpDIS->itemState & ODS_SELECTED)
        {                              
            pDC -> SetBkColor(crOldBkColor);
            pDC -> SetTextColor(crOldTextColor);
        }
        else
        {
            // Item has been de-selected -- remove frame
            pDC -> SetTextColor(crOldTextColor);
        }
    }       
}

