// --StdAfx.h------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------


#if !defined(AFX_STDAFX_H__8ABFADC7_1A6B_11D1_B612_00AA0042138E__INCLUDED_)
#define AFX_STDAFX_H__8ABFADC7_1A6B_11D1_B612_00AA0042138E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8ABFADC7_1A6B_11D1_B612_00AA0042138E__INCLUDED)
