//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  Cabinet.cpp
//
//      Implementation of Cabinet_* functions. These functions call 
//      the FDI* functions defined in FDI.H.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <io.h>
#include "fdi.h"

#ifndef TRACE
#if 0
#define TRACE(x)   OutputDebugString(x); \
                   OutputDebugString("\r\n")
#else 
#define TRACE(x)
#endif
#endif

LPVOID CDECL Cabinet_Alloc (ULONG cb)
{
    TRACE("Cabinet_Alloc");
    return LocalAlloc (LPTR, (UINT)cb);
}


LPVOID CDECL Cabinet_ReAlloc (LPVOID pv, ULONG cb)
{
    TRACE("Cabinet_ReAlloc");
    return LocalReAlloc (pv, cb, LPTR);
}

VOID CDECL Cabinet_Free (LPVOID pv)
{
    TRACE("Cabinet_Free");
    LocalFree (pv);
}


INT CDECL Cabinet_CreateFile (LPSTR lpFilename, INT nFlags, INT nMode)
{
    TRACE("Cabinet_CreateFile");
    return _open (lpFilename, nFlags, nMode);
}


UINT CDECL Cabinet_ReadFile (INT hFile, LPVOID lpBuffer, UINT cbBuffer)
{
    TRACE("Cabinet_ReadFile");
    return _read (hFile, lpBuffer, cbBuffer);
}


UINT CDECL Cabinet_WriteFile (INT hFile, LPVOID lpBuffer, UINT cbBuffer)
{
    TRACE("Cabinet_WriteFile");
    return _write (hFile, lpBuffer, cbBuffer);
}


INT CDECL Cabinet_CloseFile (INT hFile)
{
    TRACE("Cabinet_CloseFile");
    return _close (hFile);
}


LONG CDECL Cabinet_SetFilePointer (INT hFile, LONG lOffset, INT nOrigin)
{
    TRACE("Cabinet_SetFilePointer");
    return _lseek (hFile, lOffset, nOrigin);
}


HFDI CDECL Cabinet_Initialize ()
{
    ERF perf = {0};
    HFDI hFdi = FDICreate (Cabinet_Alloc, 
                           Cabinet_Free, 
                           Cabinet_CreateFile, 
                           Cabinet_ReadFile,
                           Cabinet_WriteFile, 
                           Cabinet_CloseFile,
                           Cabinet_SetFilePointer, 
                           cpu80386, &perf);
    return hFdi;
}


BOOL CDECL Cabinet_Uninitialize (HFDI hFdi)
{
    return FDIDestroy (hFdi);
}


BOOL CDECL Cabinet_IsCabinet (HFDI hFdi, int hFile, PFDICABINETINFO pfdici)
{
    return FDIIsCabinet (hFdi, hFile, pfdici);
}


BOOL CDECL Cabinet_Copy (HFDI hFdi, LPSTR lpCabinet, LPSTR lpCabinetDir, 
                          int nFlags, PFNFDINOTIFY pfnfdin, 
                          PFNFDIDECRYPT pfnfdid, LPVOID pvUser)
{
    return FDICopy (hFdi, lpCabinet, lpCabinetDir, nFlags, pfnfdin, pfnfdid, pvUser);
}


