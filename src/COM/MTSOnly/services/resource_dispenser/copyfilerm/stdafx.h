
/******************************************************************************\
********************************************************************************
* Filename: StdAfx.h
*
* Description:

	  stdafx.h : include file for standard system include files,
      or project specific include files that are used frequently,
      but are changed infrequently

*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

#if !defined(AFX_STDAFX_H__BACEDF7E_74AB_11D0_B162_00AA00BA3258__INCLUDED_)
#define AFX_STDAFX_H__BACEDF7E_74AB_11D0_B162_00AA00BA3258__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0500
#endif // !defined(_WIN32_WINNT)

#define _ATL_FREE_THREADED



#define SafeRelease(pUnk) {if (pUnk){pUnk -> Release();pUnk = NULL; }}

#include <atlbase.h>
#pragma warning( disable : 4786)
class CRmDlg;
interface ISimpleLog;



interface IResourceManager;
class CExeModule : public CComModule
{
public:
	
	CRmDlg * m_dlg;
	LONG Unlock();
	DWORD dwThreadID;
	LONG Lock( );


};
extern CExeModule _Module;
#include <atlcom.h>
#include <atlwin.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BACEDF7E_74AB_11D0_B162_00AA00BA3258__INCLUDED)
