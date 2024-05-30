/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 1999 <company name>
//
//	Module Name:
//		ClRes.h
//
//	Implementation File:
//		ClRes.cpp
//
//	Description:
//		Main header file for the resource DLL for SMB Sample (SmbSmp).
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 1999
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __CLRES_H__
#define __CLRES_H__
#pragma once

/////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#pragma comment( lib, "clusapi.lib" )
#pragma comment( lib, "resutils.lib" )
#pragma comment( lib, "advapi32.lib" )

#define UNICODE 1
#define _UNICODE 1

#pragma warning( disable : 4115 )	// named type definition in parentheses
#pragma warning( disable : 4201 )	// nonstandard extension used : nameless struct/union
#pragma warning( disable : 4214 )	// nonstandard extension used : bit field types other than int

#include <windows.h>

#pragma warning( default : 4214 )	// nonstandard extension used : bit field types other than int
#pragma warning( default : 4201 )	// nonstandard extension used : nameless struct/union
#pragma warning( default : 4115 )	// named type definition in parentheses

#pragma warning( error : 4706 )		// assignment within conditional expression

#include <clusapi.h>
#include <resapi.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// SMB Sample Definitions
/////////////////////////////////////////////////////////////////////////////

#define SMBSMP_RESNAME	L"SMB Sample"
#define SMBSMP_SVCNAME	TEXT("LanmanServer")

BOOLEAN WINAPI SmbSmpDllMain(
	IN	HINSTANCE	hDllHandle,
	IN	DWORD		nReason,
	IN	LPVOID		Reserved
	);

DWORD WINAPI SmbSmpStartup(
	IN	LPCWSTR							pszResourceType,
	IN	DWORD							nMinVersionSupported,
	IN	DWORD							nMaxVersionSupported,
	IN	PSET_RESOURCE_STATUS_ROUTINE	pfnSetResourceStatus,
	IN	PLOG_EVENT_ROUTINE				pfnLogEvent,
	OUT PCLRES_FUNCTION_TABLE *			pFunctionTable
	);

/////////////////////////////////////////////////////////////////////////////
// General Definitions
/////////////////////////////////////////////////////////////////////////////

#define DBG_PRINT printf

/////////////////////////////////////////////////////////////////////////////
// Global Variables and Prototypes
/////////////////////////////////////////////////////////////////////////////

// Event Logging routine.

extern PLOG_EVENT_ROUTINE g_pfnLogEvent;

// Resource Status routine for pending Online and Offline calls.

extern PSET_RESOURCE_STATUS_ROUTINE g_pfnSetResourceStatus;

// Handle to Service Control Manager set by the first Open resource call.

extern SC_HANDLE g_schSCMHandle;

DWORD ConfigureRegistryCheckpoints(
	IN		HRESOURCE		hResource,
	IN		RESOURCE_HANDLE	hResourceHandle,
	IN		LPCWSTR *		ppszKeys
	);

DWORD ConfigureCryptoKeyCheckpoints(
	IN		HRESOURCE		hResource,
	IN		RESOURCE_HANDLE	hResourceHandle,
	IN		LPCWSTR *		ppszKeys
	);

DWORD ConfigureDomesticCryptoKeyCheckpoints(
	IN		HRESOURCE		hResource,
	IN		RESOURCE_HANDLE	hResourceHandle,
	IN		LPCWSTR *		ppszKeys
	);

/////////////////////////////////////////////////////////////////////////////

#endif // __CLRES_H__
