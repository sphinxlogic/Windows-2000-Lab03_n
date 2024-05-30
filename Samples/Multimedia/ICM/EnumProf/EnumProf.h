/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    EnumProfiles.h

Abstract:
    
    Header file for EnumProfiles.c

--*/

#ifndef ENUMPROFILES_H
#define ENUMPROFILES_H

// Default buffer size for EnumXXX APIs
#define BUFFER_SIZE  1024

// Maximum number of retries for EnumXXX APIs
#define NUM_RETRIES  10

//////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//

BOOL
EnumAllProfiles();

BOOL
EnumMonitorProfiles();

BOOL 
CALLBACK 
MonitorEnumProc(  
    HMONITOR hMonitor,
    HDC      hdcMonitor,
    PRECT    prcMonitor,
    LPARAM   dwData
);

BOOL
EnumPrinterProfiles();

BOOL
EnumSTIProfiles();

BOOL
PrintEnumColorProfiles(
    PENUMTYPE pet
);

BOOL
PrintEnumSTIProfiles(
    IStillImage *pSti,
    PWSTR pDeviceName
);

#endif //ENUMPROFILES_H
