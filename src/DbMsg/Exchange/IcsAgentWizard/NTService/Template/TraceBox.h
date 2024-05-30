// $$Root$$TraceBox.h: interface for the C$$Root$$TraceBox class.
//
//////////////////////////////////////////////////////////////////////

#ifndef $$ROOT$$_TRACEBOX_H
#define $$ROOT$$_TRACEBOX_H
#pragma once

#include "stdafx.h"

class C$$Root$$TraceBox  
{
public:
	C$$Root$$TraceBox();
	virtual ~C$$Root$$TraceBox();
	void Config(CListBox *lpListBox);
	void Trace(LPCSTR lpszStr);
	void TraceFolderName(LPMAPIFOLDER lpFolder);
	void TraceBinary(LPCSTR lpszPropName, ULONG cb, LPBYTE lpb);

private:
	CListBox	*m_lpListBox;
	int			m_nVisibleItems;
};


#endif $$ROOT$$_TRACEBOX_H