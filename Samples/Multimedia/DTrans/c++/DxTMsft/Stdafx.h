// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__5E77EB07_937C_11D1_B047_00AA003B6061__INCLUDED_)
#define AFX_STDAFX_H__5E77EB07_937C_11D1_B047_00AA003B6061__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#define _ATL_STATIC_REGISTRY

#include <atlbase.h>
#pragma intrinsic(memset, memcpy)

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <ddraw.h>
#include <d3drm.h>
#include <dxtrans.h>
#include <dtbase.h>
#include <dxtmsft.h>
#include <dxhelp3.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5E77EB07_937C_11D1_B047_00AA003B6061__INCLUDED)
