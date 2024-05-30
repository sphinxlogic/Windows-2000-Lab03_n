/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    global.h

Abstract:

    Declerations the global variables

--*/

#ifndef GLOBAL_H
#define GLOBAL_H

//
// Global variables
//

// Default ICM profile name - the sRGB color space
extern PCTSTR g_szDefaultICMProfile;

// Class Name for the main bitmap window
extern PCTSTR BitmapWindow_szClassName;

// Registry key where we store the settings
extern PCTSTR BitmapWindow_szRegKeyName;

// Location of the CMM list registry key under Windows NT
extern PCTSTR g_szCMMRegKeyNameNT;

// Location of the CMM list registry key under Windows 95/98
extern PCTSTR g_szCMMRegKeyName9x;

// Current default CMM ID. 
extern DWORD g_DefaultCMMID;

// Handle to the current instance of the application
extern HINSTANCE g_hInstance;

// Global resource string table
extern PTSTR g_pResourceStrings[IDS_LAST - IDS_FIRST + 1];

typedef enum _OS_TYPE {

    OS_WIN32s,
    OS_WIN95,
    OS_WIN98,
    OS_WINNT3,
    OS_WINNT4,
    OS_WIN2000

} OS_TYPE;

// The OS version we are running on
extern OS_TYPE g_OS;

#endif //GLOBAL_H
