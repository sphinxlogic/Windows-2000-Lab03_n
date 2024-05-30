//	stdafx.h : include file for standard system include files,
//		or project specific include files that are used frequently,
//		but are changed infrequently

#ifndef _STDAFX_H_
#define _STDAFX_H_

#if _MSC_VER >= 1000
#pragma once
#endif	// _MSC_VER >= 1000

#define STRICT

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
#include <map>
#include <list>
#define _EDKDEBUG_H		// do not include edkdebug.h
#include "edk.h"
#include "comdef.h"
#include "mapidefs.h"
#include "mapitags.h"
#include "Module.h"

//	You may derive a class from CComModule and use it if you want to override
//	something, but do not change the name of _Module
extern CEDKRulesComModule _Module;

#pragma warning ( disable : 4786 )
#include <atlcom.h>
#include "objbase.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // define _STDAFX_H_
