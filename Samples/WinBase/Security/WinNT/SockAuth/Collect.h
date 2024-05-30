/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996 - 1999.  Microsoft Corporation.  All rights reserved.

Module Name:

    collect.h

Abstract:

    Functions for a simple collection

Revision History:

--*/

#if !defined(INC_COLLECT_H)
#define INC_COLLECT_H

BOOL GetEntry (DWORD_PTR dwKey, PVOID *ppData);
BOOL AddEntry (DWORD_PTR dwKey, PVOID pData);
BOOL DeleteEntry (DWORD_PTR dwKey, PVOID *ppData);

#endif
