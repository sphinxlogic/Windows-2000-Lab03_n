/************************************************************************
*                                                                       *
*   $$Root$$TraceBox.cpp											*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#include "stdafx.h"
#include "$$Root$$TraceBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRITICAL_SECTION g_hCriticalSection;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C$$Root$$TraceBox::C$$Root$$TraceBox()
{
	m_lpListBox = NULL;
	m_nVisibleItems = 0;
}

C$$Root$$TraceBox::~C$$Root$$TraceBox()
{

}

void C$$Root$$TraceBox::Config(CListBox *lpListBox)
{
	//
	//	Bind the trace list box to a visible dialog control.
	//
	
	m_lpListBox = lpListBox;

	//
	//	Calculate the number of visible lines that can be
	//	displayed in the list box.
	//

	CRect		objListBoxRect;
	int		nListBoxHeight;
	int		nListBoxItemHeight;

	m_lpListBox->GetClientRect(&objListBoxRect);
	nListBoxHeight = objListBoxRect.bottom - objListBoxRect.top;
	nListBoxItemHeight = m_lpListBox->GetItemHeight(0);
	m_nVisibleItems = nListBoxHeight / nListBoxItemHeight;
}

void C$$Root$$TraceBox::Trace(LPCSTR lpszStr)
{
	int nIndex;
	char * pDest;

	EnterCriticalSection(&g_hCriticalSection);

	if (lpszStr != NULL)
	{
		//
		// Find the first carriage return
		pDest = strchr(lpszStr, '\n');
		if (pDest == NULL)
		{
			//
			// If the string contains no carriage returns,
			// simply display it
			nIndex = m_lpListBox->AddString(lpszStr);
			m_lpListBox->UpdateWindow();

			if (nIndex >= m_nVisibleItems)
				m_lpListBox->SetTopIndex(nIndex - m_nVisibleItems + 1);
		}
		else
		{
			//
			// If the string DOES contain carriage returns, 
			// break it into two smaller pieces
			LPTSTR str = new TCHAR[lstrlen(lpszStr) - lstrlen(pDest) + 1];
			strncpy(str, lpszStr, lstrlen(lpszStr) - lstrlen(pDest));
			_stprintf(str + lstrlen(lpszStr) - lstrlen(pDest), "\0");
			Trace(str);
			Trace(pDest + 1);
		}
	}

	LeaveCriticalSection(&g_hCriticalSection);
}

void C$$Root$$TraceBox::TraceFolderName(LPMAPIFOLDER lpFolder)
{
	CString	str;
	HRESULT	hResult;

	SizedSPropTagArray(1,rgProps) =
	{
		1,
		{
			PR_DISPLAY_NAME
		}
	};

	ULONG				uValuesCount;
	LPSPropValue	lpProps;

	if (lpFolder == NULL)
		return;
	
	hResult = lpFolder->GetProps(
								(LPSPropTagArray)&rgProps,
								0,
								&uValuesCount,
								&lpProps);

	if (HR_FAILED(hResult))
		return;

	ASSERT(uValuesCount == 1);
	ASSERT(lpProps[0].ulPropTag == PR_DISPLAY_NAME);
	
	str.Format(" PR_DISPLAY_NAME=%s",lpProps[0].Value.lpszA);
	Trace(str);

	MAPIFreeBuffer(lpProps);
}

void C$$Root$$TraceBox::TraceBinary(LPCSTR lpszPropName, ULONG cb, LPBYTE lpb)
{
	CString objStr;
	CString objHexDigits;

	objStr.Format(" %s=",lpszPropName);

	while (cb--)
	{
		objHexDigits.Format("%02X",*lpb);
		objStr += objHexDigits;
		++lpb;
	}

	Trace(objStr);
}

