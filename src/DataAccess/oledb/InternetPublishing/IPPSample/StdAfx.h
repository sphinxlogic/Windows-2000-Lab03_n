/*------------------------------------------------------------------------------
	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
	ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
	TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

	stdafx.h

	the header to be included in each source file for pre-compiled header
------------------------------------------------------------------------------*/

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BB6C072B_AA52_11D2_8E8A_00C04FB9C68B__INCLUDED_)
#define AFX_STDAFX_H__BB6C072B_AA52_11D2_8E8A_00C04FB9C68B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>

// TODO: reference additional headers your program requires here

/*------------------------------------------------------------------------------
  Please note that oledb.h and oledberr.h from the OLEDB 2.5 SDK is required.
  In addition, oledb.lib from the OLEDB 2.5 is required for linking.
------------------------------------------------------------------------------*/
#include <oledb.h>
#include <oledberr.h>

/*------------------------------------------------------------------------------
  msdaipp.h has the definition MSDAIPP-specific properties.
------------------------------------------------------------------------------*/
#include <msdaipp.h>

/*------------------------------------------------------------------------------
  msdasc.h has the definition of CLSID_RootBinder and some URLMON integration 
  necessities
  Link to msdasc.lib for its symbol.
------------------------------------------------------------------------------*/
#include <msdasc.h>

#include "sample1.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BB6C072B_AA52_11D2_8E8A_00C04FB9C68B__INCLUDED_)
