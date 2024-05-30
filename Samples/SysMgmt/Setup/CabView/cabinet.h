//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  Cabinet.h
//
//////////////////////////////////////////////////////////////////////

#ifndef CABINET_H_INCLUDED
#define CABINET_H_INCLUDED

#include <fcntl.h>
#include <sys\stat.h>
#include "fdi.h"

HFDI CDECL Cabinet_Initialize ();
BOOL CDECL Cabinet_Uninitialize (HFDI hFdi);
LPVOID CDECL Cabinet_Alloc (ULONG cb);
LPVOID CDECL Cabinet_ReAlloc (LPVOID pv, ULONG cb);
VOID CDECL Cabinet_Free (LPVOID pv);
INT CDECL Cabinet_CreateFile (LPSTR lpFilename, INT nFlags, INT nMode);
UINT CDECL Cabinet_ReadFile (INT hFile, LPVOID lpBuffer, UINT cbBuffer);
UINT CDECL Cabinet_WriteFile (INT hFile, LPVOID lpBuffer, UINT cbBuffer);
INT CDECL Cabinet_CloseFile (INT hFile);
LONG CDECL Cabinet_SetFilePointer (INT hFile, LONG lOffset, INT nOrigin);
BOOL CDECL Cabinet_IsCabinet (HFDI hFdi, int hFile, PFDICABINETINFO pfdici);
BOOL CDECL Cabinet_Copy (HFDI hFdi, LPSTR lpCabinet, LPSTR lpCabinetDir, 
                          int nFlags, PFNFDINOTIFY pfnfdin, 
                          PFNFDIDECRYPT pfnfdid, LPVOID pvUser);

#endif