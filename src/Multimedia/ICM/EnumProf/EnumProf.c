/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    EnumProfiles.c

Abstract:

    ICM Profiles Enumeration sample

--*/

#include "pch.h"
#include "EnumProf.h"
#define IMPLEMENT_CHECK
#include "check.h"

//////////////////////////////////////////////////////////////////////////
//
// _tmain
//
// Routine Description:
//   The initial entry point - unicode aware version
//
// Arguments:
//  int   argc     Number of command line arguments
//  PTSTR argv[]   Array of command line argument strings
//
// Return Value:
//   The exit code (== 0 for this program)
//

int
__cdecl
_tmain(
    int   argc,
    PTSTR argv[]
)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    EnumAllProfiles();
    EnumMonitorProfiles();
    EnumPrinterProfiles();
    EnumSTIProfiles();
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// EnumAllProfiles
//
// Routine Description:
//   Prints all profiles in the system
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EnumAllProfiles()
{
    USES_BRESULT;

    ENUMTYPE et;

    _tprintf(_T("\nAll Installed Profiles:\n"));

    ZeroMemory(&et, sizeof(et));
    et.dwSize        = sizeof(et);
    et.dwVersion     = ENUM_TYPE_VERSION;

    CHECK(PrintEnumColorProfiles(&et));

    
    _tprintf(_T("\nInstalled Scanner Profiles:\n"));
    
    ZeroMemory(&et, sizeof(et));
    et.dwSize        = sizeof(et);
    et.dwVersion     = ENUM_TYPE_VERSION;
    et.dwFields      = ET_DEVICECLASS;
    et.dwDeviceClass = CLASS_SCANNER;

    CHECK(PrintEnumColorProfiles(&et));
    
    
    _tprintf(_T("\nInstalled Monitor Profiles:\n"));

    ZeroMemory(&et, sizeof(et));
    et.dwSize        = sizeof(et);
    et.dwVersion     = ENUM_TYPE_VERSION;
    et.dwFields      = ET_DEVICECLASS;
    et.dwDeviceClass = CLASS_MONITOR;

    CHECK(PrintEnumColorProfiles(&et));
    
    
    _tprintf(_T("\nInstalled Printer Profiles:\n"));

    ZeroMemory(&et, sizeof(et));
    et.dwSize        = sizeof(et);
    et.dwVersion     = ENUM_TYPE_VERSION;
    et.dwFields      = ET_DEVICECLASS;
    et.dwDeviceClass = CLASS_PRINTER;

    CHECK(PrintEnumColorProfiles(&et));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EnumMonitorProfiles
//
// Routine Description:
//   Enumerates the monitors in the system calls PrintEnumColorProfiles
//   for each monitor
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EnumMonitorProfiles()
{
    USES_BRESULT;

    CHECK(EnumDisplayMonitors(
        0,
        0,
        MonitorEnumProc,
        0
    ));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// MonitorEnumProc
//
// Routine Description:
//   Callback function for EnumMonitorProfiles. This function is called
//   for each monitor in the system
//
// Arguments:
//  HMONITOR hMonitor     handle to display monitor
//  HDC      hdcMonitor   handle to monitor-appropriate device context
//  PRECT    prcMonitor   pointer to monitor intersection rectangle
//  LPARAM   dwData       data passed from EnumDisplayMonitors
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
CALLBACK 
MonitorEnumProc(  
    HMONITOR hMonitor,
    HDC      hdcMonitor,
    PRECT    prcMonitor,
    LPARAM   dwData
)
{
    USES_BRESULT;

    MONITORINFOEX   miex;
    ENUMTYPE        et;

    UNREFERENCED_PARAMETER(hdcMonitor);
    UNREFERENCED_PARAMETER(prcMonitor);
    UNREFERENCED_PARAMETER(dwData);

    // Obtain the name of the monitor
    
    miex.cbSize = sizeof(miex);

    CHECK(GetMonitorInfo(
        hMonitor,
        (LPMONITORINFO) &miex
    ));

    // Call PrintEnumColorProfiles for this monitor

    _tprintf(_T("\nProfiles for monitor \"%s\":\n"), miex.szDevice);

    ZeroMemory(&et, sizeof(et));
    et.dwSize        = sizeof(et);
    et.dwVersion     = ENUM_TYPE_VERSION;
    et.dwFields      = ET_DEVICENAME | ET_DEVICECLASS;
    et.pDeviceName   = miex.szDevice;
    et.dwDeviceClass = CLASS_MONITOR;
    
    CHECK(PrintEnumColorProfiles(&et));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EnumPrinterProfiles
//
// Routine Description:
//   Enumerates the installed printers and calls PrintEnumColorProfiles
//   for each printer
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EnumPrinterProfiles()
{
    USES_BRESULT;

    BOOL            bEnumResult;
    INT             nRetries = NUM_RETRIES;
    DWORD           dwNum;
    PPRINTER_INFO_1 ppi1;
    DWORD           i;

    // Begin the enumeration with a default size buffer

    BYTE            szBuffer[BUFFER_SIZE];
    DWORD           dwSize = sizeof(szBuffer);
    PBYTE           pBuffer = szBuffer;

    bEnumResult = EnumPrinters(
        PRINTER_ENUM_LOCAL,
        0,
        1,
        pBuffer,
        dwSize,
        &dwSize,
        &dwNum
    );

    // If the enumeration fails because of insufficient buffer
    // size, resize the buffer and retry (at most NUM_RETRIES times)

    while (!bEnumResult && --nRetries) {

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // If we have previously allocated a new buffer, 
            // deallocate it first

            if (pBuffer != szBuffer) {

                CHECK(GlobalFree(pBuffer) == 0);
            }

            // Allocate the new buffer (according to dwSize 
            // returned from the last enum call)

            CHECK(pBuffer = GlobalAlloc(
                GMEM_FIXED,
                dwSize
            ));

            // Retry

            bEnumResult = EnumPrinters(
                PRINTER_ENUM_LOCAL,
                0,
                1,
                pBuffer,
                dwSize,
                &dwSize,
                &dwNum
            );

        } else {

            SYSTEM_ERROR_MESSAGE(GetLastError());
        }
    }

    if (nRetries == 0) {

        SYSTEM_ERROR_MESSAGE(GetLastError());
    }

    // The printer names are returned as an array of PRINTER_INFO_1
    // structures. Call PrintEnumColorProfiles for each printer

    ppi1 = (PPRINTER_INFO_1) pBuffer;

    for (i = 0; i < dwNum; ++i) {

        ENUMTYPE et;

        _tprintf(_T("\nProfiles for printer \"%s\":\n"), ppi1[i].pName);

        ZeroMemory(&et, sizeof(et));
        et.dwSize        = sizeof(et);
        et.dwVersion     = ENUM_TYPE_VERSION;
        et.dwFields      = ET_DEVICENAME | ET_DEVICECLASS;
        et.pDeviceName   = ppi1[i].pName;
        et.dwDeviceClass = CLASS_PRINTER;
        
        CHECK(PrintEnumColorProfiles(&et));
    }

    BEGIN_CLEANUP;

    // If we have re-allocated a new buffer, deallocate it

    if (pBuffer != szBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EnumSTIProfiles
//
// Routine Description:
//   Enumerates the STI devices in the system and calls PrintEnumSTIProfiles
//   for each device
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EnumSTIProfiles()
{
    USES_BRESULT;

    IStillImage             *pSti;
    DWORD                   dwNum;
    PSTI_DEVICE_INFORMATION pdi = 0;
    DWORD                   i;

    CHECK(StiCreateInstance(
        GetModuleHandle(0),
        STI_VERSION,
        &pSti,
        0
    ) == S_OK);

    CHECK(IStillImage_GetDeviceList(
        pSti, 
        0,
        0,
        &dwNum,
        &pdi
    ) == S_OK);

    // IStillImage_GetDeviceList returns a list of STI_DEVICE_INFORMATION
    // structures. Process that list one by one...

    for (i = 0; i < dwNum; ++i) {

        PCWSTR pDeviceTypeName;

        switch (GET_STIDEVICE_TYPE(pdi[i].DeviceType)) {

        case StiDeviceTypeScanner:
            pDeviceTypeName = L"scanner";
            break;

        case StiDeviceTypeDigitalCamera:
            pDeviceTypeName = L"digital camera";
            break;

        case StiDeviceTypeDefault:
            pDeviceTypeName = L"still image device";
            break;

        default:
            pDeviceTypeName = L"unknown device";
            break;
        }

        wprintf(
            L"\nProfiles for %s \"%s\":\n", 
            pDeviceTypeName,
            pdi[i].pszLocalName
        );

        PrintEnumSTIProfiles(
            pSti, 
            pdi[i].szDeviceInternalName
        );
    }

    BEGIN_CLEANUP;

    // We need to free the STI_DEVICE_INFORMATION pointer returned by 
    // IStillImage_GetDeviceList

    if (pdi) {
    
        CHECK(LocalFree(pdi) == 0);
    }

    if (pSti) {
    
        CHECK(IStillImage_Release(pSti) == S_OK);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// PrintEnumColorProfiles
//
// Routine Description:
//   Prints all of the color profiles according to the given criteria
//
// Arguments:
//   PENUMTYPE pet  Pointer to a structure specifying the enumeration criteria
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
PrintEnumColorProfiles(
    PENUMTYPE pet
)
{
    USES_BRESULT;

    BOOL    bEnumResult;
    INT     nRetries = NUM_RETRIES;
    DWORD   dwNum;
    PCTSTR  pProfileName;

    // Begin the enumeration with a default size buffer
    
    BYTE    szBuffer[BUFFER_SIZE];
    DWORD   dwSize = sizeof(szBuffer);
    PBYTE   pBuffer = szBuffer;

    bEnumResult = EnumColorProfiles(
        0,
        pet,
        pBuffer,
        &dwSize,
        &dwNum
    );

    // If the enumeration fails because of insufficient buffer
    // size, resize the buffer and retry (at most NUM_RETRIES times)

    while (!bEnumResult && --nRetries) {

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // If we have previously allocated a new buffer, 
            // deallocate it first

            if (pBuffer != szBuffer) {

                CHECK(GlobalFree(pBuffer) == 0);
            }

            // Allocate the new buffer (according to dwSize 
            // returned from the last enum call)

            CHECK(pBuffer = GlobalAlloc(
                GMEM_FIXED,
                dwSize
            ));

            // Retry

            bEnumResult = EnumColorProfiles(
                0,
                pet,
                pBuffer,
                &dwSize,
                &dwNum
            );

        } else {

            SYSTEM_ERROR_MESSAGE(GetLastError());
        }
    }

    if (nRetries == 0) {

        SYSTEM_ERROR_MESSAGE(GetLastError());
    }

    // the profile names are returned as a MULTI_SZ string, i.e. 
    // a double null terminated list of null terminated strings.
    // Process this string as follows and print each profile name

    pProfileName = (PCTSTR) pBuffer;

    while (*pProfileName) {

        _tprintf(_T("- %s\n"), pProfileName);

        pProfileName += _tcslen(pProfileName) + 1;
    }

    BEGIN_CLEANUP;

    // If we have re-allocated a new buffer, deallocate it

    if (pBuffer != szBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// PrintEnumSTIProfiles
//
// Routine Description:
//   Prints all of the color profiles associated with an STI device
//
// Arguments:
//  IStillImage *pSti   COM interface pointer
//  PWSTR pDeviceName   Name of the STI device
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
PrintEnumSTIProfiles(
    IStillImage *pSti,
    PWSTR pDeviceName
)
{
    USES_BRESULT;

    BOOL    bEnumResult;
    INT     nRetries = NUM_RETRIES;
    DWORD   dwType;
    PCWSTR  pProfileName;

    // Begin the enumeration with a default size buffer

    BYTE    szBuffer[BUFFER_SIZE];
    DWORD   dwSize = sizeof(szBuffer);
    PBYTE   pBuffer = szBuffer;

    bEnumResult = IStillImage_GetDeviceValue(
        pSti, 
        pDeviceName,
        STI_DEVICE_VALUE_ICM_PROFILE, 
        &dwType, 
        pBuffer, 
        &dwSize
    );
    
    // If the enumeration fails because of insufficient buffer
    // size, resize the buffer and retry (at most NUM_RETRIES times)

    while (bEnumResult != S_OK && --nRetries) {

        if (bEnumResult == ERROR_MORE_DATA) {

            // If we have previously allocated a new buffer, 
            // deallocate it first

            if (pBuffer != szBuffer) {

                CHECK(GlobalFree(pBuffer) == 0);
            }

            // Allocate the new buffer (according to dwSize 
            // returned from the last enum call)

            CHECK(pBuffer = GlobalAlloc(
                GMEM_FIXED,
                dwSize
            ));

            // Retry

            bEnumResult = IStillImage_GetDeviceValue(
                pSti, 
                pDeviceName,
                STI_DEVICE_VALUE_ICM_PROFILE, 
                &dwType, 
                pBuffer, 
                &dwSize
            );

        } else {

            SYSTEM_ERROR_MESSAGE(bEnumResult);
        }
    }

    if (nRetries == 0) {

        SYSTEM_ERROR_MESSAGE(bEnumResult);
    }

    // the profile names are returned as a MULTI_SZ string, i.e. 
    // a double null terminated list of null terminated strings.
    // Process this string as follows and print each profile name

    pProfileName = (PCWSTR) pBuffer;

    while (*pProfileName) {

        wprintf(L"- %s\n", pProfileName);

        pProfileName += wcslen(pProfileName) + 1;
    }

    BEGIN_CLEANUP;

    // If we have re-allocated a new buffer, deallocate it

    if (pBuffer != szBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    return BRESULT;
}

