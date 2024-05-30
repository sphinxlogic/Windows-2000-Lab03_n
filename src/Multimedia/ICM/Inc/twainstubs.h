/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
	twainstubs.h

Abstract:
	
	Stubs for Twain functionality

--*/

#ifndef TWAINSTUBS_H
#define TWAINSTUBS_H

#include "twain.h"

extern BOOL         g_bTwainFunctionalityPresent;

extern DSMENTRYPROC g_pfnDSM_Entry;

#define DSM_Entry   (*g_pfnDSM_Entry)

VOID InitTwainStubs();
VOID FreeTwainStubs();

#endif //TWAINSTUBS_H




#ifdef IMPLEMENT_TWAIN_STUBS

TW_UINT16 
WINAPI 
xDSM_Entry(
    pTW_IDENTITY pOrigin,
    pTW_IDENTITY pDest,
    TW_UINT32    DG,
    TW_UINT16    DAT,
    TW_UINT16    MSG,
    TW_MEMREF    pData
)
{
    return TWRC_FAILURE;
}

BOOL         g_bTwainFunctionalityPresent = FALSE;

DSMENTRYPROC g_pfnDSM_Entry = xDSM_Entry;

HMODULE      hTwain = 0;

#define StoreProcAddress(hModule, ProcName, Proc) \
	(pfn = GetProcAddress(hModule, ProcName), pfn ? *(FARPROC*) Proc = pfn : 0)

VOID InitTwainStubs()
{
	FARPROC pfn;

	g_bTwainFunctionalityPresent = 
		(hTwain = LoadLibrary(_T("TWAIN_32.DLL"))) &&
        StoreProcAddress(hTwain, "DSM_Entry", &g_pfnDSM_Entry);
}

VOID FreeTwainStubs()
{
	if (hTwain) {
	
		FreeLibrary(hTwain);
	}
}

#ifdef __cplusplus

static struct CTwainStubs
{
	CTwainStubs()
    {
        InitTwainStubs();
    }

	~CTwainStubs()
    {
        FreeTwainStubs();
    }

} TwainStubs;

#endif //__cplusplus

#endif //IMPLEMENT_TWAIN_STUBS

