/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    global.c

Abstract:

    Definition of the global variables

--*/

#include "pch.h"
#include "resource.h"

#include "global.h"

//////////////////////////////////////////////////////////////////////////
//
// Global variables
//

// Default ICM profile name - the sRGB color space
PCTSTR g_szDefaultICMProfile = _T("sRGB Color Space Profile.ICM");

// Class Name for the main bitmap window
PCTSTR BitmapWindow_szClassName  = _T("DIBVIEW");

// Registry key where we store the settings
PCTSTR BitmapWindow_szRegKeyName = _T("SOFTWARE\\Microsoft\\DibView");

// Location of the CMM list registry key under Windows NT
PCTSTR g_szCMMRegKeyNameNT = 
    _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\ICM\\ICMatchers");

// Location of the CMM list registry key under Windows 95/98
PCTSTR g_szCMMRegKeyName9x = 
    _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ICM\\ICMatchers");

// Current default CMM ID. 
DWORD g_DefaultCMMID = 0;

// Handle to the current instance of the application
HINSTANCE g_hInstance = 0;

// Global resource string table
PTSTR g_pResourceStrings[IDS_LAST - IDS_FIRST + 1];

// The OS version we are running on
OS_TYPE g_OS;

