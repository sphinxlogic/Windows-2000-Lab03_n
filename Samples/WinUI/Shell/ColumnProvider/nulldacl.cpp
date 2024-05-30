//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  NullDacl.cpp
//
//      Provides functions to allocate and free a SECURITY_DESCRIPTOR
//      with a NULL DACL
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"

PSECURITY_DESCRIPTOR WINAPI CreateNullDacl ()
{
    OSVERSIONINFO           osvi    = {0};

    //
    //  Get the OS version info. If not on NT, return NULL
    //
    osvi.dwOSVersionInfoSize    = sizeof (OSVERSIONINFO);
    GetVersionEx (&osvi);
    if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT)
    {
        SetLastError (NOERROR);
        return NULL;
    }

    //
    //  Allocate memory for the security descriptor
    //
    PSECURITY_DESCRIPTOR    psd     = NULL;

    psd = (PSECURITY_DESCRIPTOR) HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, 
                                            SECURITY_DESCRIPTOR_MIN_LENGTH);
    if (!psd) return NULL;

    //
    //  Initialize the security descriptor
    //
    InitializeSecurityDescriptor (psd, SECURITY_DESCRIPTOR_REVISION);

    //
    //  Add an NULL ACL to the security descriptor
    //
    SetSecurityDescriptorDacl (psd, TRUE, NULL, FALSE);

    return psd;
}


VOID WINAPI FreeNullDacl (PSECURITY_DESCRIPTOR psd)
{
    //
    //  Free the memory for the security descriptor
    //
    HeapFree (GetProcessHeap(), 0, (PVOID) psd);
}


