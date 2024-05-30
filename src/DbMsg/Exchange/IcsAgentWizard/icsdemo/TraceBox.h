// TraceBox.h: interface for the CTraceBox class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

class CTraceBox  
{
public:
	CTraceBox();
	virtual ~CTraceBox();
	void Config(CListBox *lpListBox);
	void Trace(LPCSTR lpszStr);
	void TraceFolderName(LPMAPIFOLDER lpFolder);
	void TraceBinary(LPCSTR lpszPropName, ULONG cb, LPBYTE lpb);

private:
	CListBox		*m_lpListBox;
	int			m_nVisibleItems;
};
