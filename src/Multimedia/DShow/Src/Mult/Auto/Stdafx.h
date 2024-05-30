// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E864AD85_D0C2_11D1_B30B_249710C1AA07__INCLUDED_)
#define AFX_STDAFX_H__E864AD85_D0C2_11D1_B30B_249710C1AA07__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if 0 // seems to conflict with our build environment
#define STRICT
#endif


#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <strmif.h>
#include <control.h>
#include <evcode.h>
#include <uuids.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E864AD85_D0C2_11D1_B30B_249710C1AA07__INCLUDED)
