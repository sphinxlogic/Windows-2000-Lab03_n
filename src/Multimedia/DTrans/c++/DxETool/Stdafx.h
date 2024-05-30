// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__53BE8351_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
#define AFX_STDAFX_H__53BE8351_4A55_11D1_81AA_0000F87557DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlconv.h>
#include <atlctl.h>
#include <afxdlgs.h>
#include <time.h>
#include <math.h>
#include <mmsystem.h>

#include <DXTrans.h>
#include <DXHelper.h>
#include <dxvector.h>
#include <ddraw.h>
#include <d3drm.h>

#define EMPTY_START 0

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__53BE8351_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
