/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

Module Name:

    stdafx

Abstract:

        Include file for standard system include files, or project
        specific include files that are used frequently, but are
        changed infrequently for this in-process server (DLL) for
        the Smartcard Vendor Wrapper Service Provider (SSP).

Environment:

    Win32, C++ w/Exceptions, COM/OLE

Revision History:

Notes:


--*/

#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxpriv.h>            // MFC Conversion macros, etc.
#include <initguid.h>           // include to avoid DEFINE_MACRO problems
