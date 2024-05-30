// TraceBox.cpp: implementation of the CTraceBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICSDemo.h"
#include "TraceBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTraceBox::CTraceBox()
{
	m_lpListBox = NULL;
	m_nVisibleItems = 0;
}

CTraceBox::~CTraceBox()
{

}

void CTraceBox::Config(CListBox *lpListBox)
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

void CTraceBox::Trace(LPCSTR lpszStr)
{
	int nIndex;

	nIndex = m_lpListBox->AddString(lpszStr);
	m_lpListBox->UpdateWindow();

	if (nIndex >= m_nVisibleItems)
		m_lpListBox->SetTopIndex(nIndex - m_nVisibleItems + 1);
}

void CTraceBox::TraceFolderName(LPMAPIFOLDER lpFolder)
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

void CTraceBox::TraceBinary(LPCSTR lpszPropName, ULONG cb, LPBYTE lpb)
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