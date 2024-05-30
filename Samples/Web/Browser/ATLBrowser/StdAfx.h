//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
// Author: S. R.
//         Support Engineer - Internet Client SDK
//         Microsoft Developer Support
//
// stdafx.h : include file for standard system include files,
//            or project specific include files that are used frequently,
//            but are changed infrequently
//--------------------------------------------------------------------------
#define STRICT
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
#include "ExDisp.h"

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
private:
   HWND m_hwnd;
};

extern CExeModule _Module;

#include <atlcom.h>
#include <atlwin.h>
