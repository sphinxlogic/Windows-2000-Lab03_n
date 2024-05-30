// Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.
//
//    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//    PARTICULAR PURPOSE.

#ifndef _WIN32_WINNT
#define _WIN32_WINNT  0x0402
#endif

#include <windows.h>
#include <assert.h>

#define MAX_GUIDSTR_LEN 40

const CHAR szClsidKeyName[] = "CLSID";
const CHAR szAppidValueName[] = "AppID";

#ifndef __ISurrogate_INTERFACE_DEFINED__
#error "You need SP2-Compliant SDK headers to compile this file."
#endif

