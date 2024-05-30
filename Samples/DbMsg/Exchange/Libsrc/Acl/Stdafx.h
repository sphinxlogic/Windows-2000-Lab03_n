// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__A0E483F1_F971_11D1_A956_00C04FB155E5__INCLUDED_)
#define AFX_STDAFX_H__A0E483F1_F971_11D1_A956_00C04FB155E5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#pragma warning (disable : 4786)


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <comdef.h>

#include <MAPIDEFS.H>
#include <mapicode.h>
#include <mapiform.h>
#include <mapiguid.h>
#include <mapispi.h>
#include <mapitags.h>
#include <mapiutil.h>
#include <mapival.h>
#include <mapiwin.h>
#include <mapix.h>
#include <edkmdb.h>


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A0E483F1_F971_11D1_A956_00C04FB155E5__INCLUDED)
