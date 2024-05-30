/****************************************************************************
 ** 
 ** Microsoft Site Server v3.00
 ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
 ** 
 ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
 ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
 ** PURPOSE.
 **
 **
 ** CONTENTS
 **
 ** NOTES
 **     stdafx.h : include file for standard system include files,
 **     or project specific include files that are used frequently,
 **     but are changed infrequently
 **
 ****************************************************************************/

#pragma once

#define STRICT
#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#define _ATL_STATIC_REGISTRY

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxdlgs.h>        // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#include <afxctl.h>         // MFC OLE property page classes
#include <afxcmn.h>         // MFC support for Windows Common Controls

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

// Global settings
#define  AGENTS_KEY _T("Software\\Microsoft\\Site Server\\3.0\\Active Channel Agents")

// Useful macros
#define  RET_IF_ERR(x)      if (FAILED(hRes = x)) return hRes
#define  RET_IF_WIN32ERR(x) if (FAILED(hRes = HRESULT_FROM_WIN32(x))) return hRes

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
