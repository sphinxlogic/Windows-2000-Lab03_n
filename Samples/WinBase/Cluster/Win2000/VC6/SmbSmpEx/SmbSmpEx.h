/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 1999 <company name>
//
//	Module Name:
//		SmbSmpEx.h
//
//	Implementation File:
//		SmbSmpEx.cpp
//
//	Description:
//		Global definitions across the DLL.
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 1999
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __SMBSMPEX_H__
#define __SMBSMPEX_H__

/////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// Constant Definitions
/////////////////////////////////////////////////////////////////////////////

#define REGPARAM_SMBSMP_SHARENAME L"ShareName"
#define REGPARAM_SMBSMP_PATH L"Path"
#define REGPARAM_SMBSMP_REMARK L"Remark"
#define REGPARAM_SMBSMP_MAXUSERS L"MaxUsers"

/////////////////////////////////////////////////////////////////////////////
// Global Function Declarations
/////////////////////////////////////////////////////////////////////////////

void FormatError( CString & rstrError, DWORD dwError );

// Defined in Extensn.cpp
extern const WCHAR g_wszResourceTypeNames[];
extern const DWORD g_cchResourceTypeNames;

/////////////////////////////////////////////////////////////////////////////

#endif // __SMBSMPEX_H__