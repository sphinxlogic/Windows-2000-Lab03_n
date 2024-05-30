/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
	STIstubs.h

Abstract:
	
	Stubs for STI functionality

--*/

#ifndef STISTUBS_H
#define STISTUBS_H

#include "sti.h"

extern BOOL  g_bSTIFunctionalityPresent;

extern HRESULT (STDMETHODCALLTYPE *g_pfnStiCreateInstanceA)(HINSTANCE, DWORD, interface IStillImageA **, LPUNKNOWN);
extern HRESULT (STDMETHODCALLTYPE *g_pfnStiCreateInstanceW)(HINSTANCE, DWORD, interface IStillImageW **, LPUNKNOWN);

#define StiCreateInstanceA   (*g_pfnStiCreateInstanceA)
#define StiCreateInstanceW   (*g_pfnStiCreateInstanceW)

VOID InitSTIStubs();
VOID FreeSTIStubs();

#endif //STISTUBS_H




#ifdef IMPLEMENT_STI_STUBS

HRESULT STDMETHODCALLTYPE xStiCreateInstanceA(HINSTANCE hinst, DWORD dwVer, interface IStillImageA **ppSti, LPUNKNOWN punkOuter) { return E_NOTIMPL; }
HRESULT STDMETHODCALLTYPE xStiCreateInstanceW(HINSTANCE hinst, DWORD dwVer, interface IStillImageW **ppSti, LPUNKNOWN punkOuter) { return E_NOTIMPL; }

HRESULT (STDMETHODCALLTYPE *g_pfnStiCreateInstanceA)(HINSTANCE, DWORD, interface IStillImageA **, LPUNKNOWN) = xStiCreateInstanceA;
HRESULT (STDMETHODCALLTYPE *g_pfnStiCreateInstanceW)(HINSTANCE, DWORD, interface IStillImageW **, LPUNKNOWN) = xStiCreateInstanceW;

BOOL     g_bSTIFunctionalityPresent = FALSE;

HMODULE  hSTI = 0;

#define StoreProcAddress(hModule, ProcName, Proc) \
	(pfn = GetProcAddress(hModule, ProcName), pfn ? *(FARPROC*) Proc = pfn : 0)

VOID InitSTIStubs()
{
	FARPROC pfn;

	g_bSTIFunctionalityPresent = 
		(hSTI = LoadLibrary(_T("STI.DLL"))) &&
        StoreProcAddress(hSTI, "StiCreateInstanceA", &g_pfnStiCreateInstanceA) &&
        StoreProcAddress(hSTI, "StiCreateInstanceW", &g_pfnStiCreateInstanceW);
}

VOID FreeSTIStubs()
{
	if (hSTI) {
	
		FreeLibrary(hSTI);
	}
}

#ifdef __cplusplus

static struct CSTIStubs
{
	CSTIStubs()
    {
        InitSTIStubs();
    }

    ~CSTIStubs()
    {
        FreeSTIStubs();
    }

} g_STIStubs;

#endif //__cplusplus

#endif //IMPLEMENT_STI_STUBS

