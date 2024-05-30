/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1999 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/




// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
// This source code is provided as-is, without warranty.
//
// Created by S. R.
// Microsoft Developer Support - Internet Client SDK
/////////////////////////////////////////////////////////

#if !defined(AFX_STDAFX_H__A654394B_9D7F_11D1_ABEE_00D049C10000__INCLUDED_)
#define AFX_STDAFX_H__A654394B_9D7F_11D1_ABEE_00D049C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxconv.h>
#include <ExDispID.h>   // For WebBrowser and Internet Explorer 4.0x events.

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A654394B_9D7F_11D1_ABEE_00D049C10000__INCLUDED_)
