/*++

Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.

Module Name:

    service.cxx

Abstract:

    Start the content indexing service (CISVC)

Revision History:

    Steve Firebaugh     9-97          Created from previous samples

--*/


#include <windows.h>
#include "catq.h"



int catqStartCIService ( HWND hwnd )
/*++

    Query the state of the content indexing service.  If it is not
     running, then attempt to start it up.  Access to the service
     is via the Windows NT "service control manager."

--*/
{

    SC_HANDLE   schCIService = NULL;
    SC_HANDLE   schSCManager = NULL;
    int iFunctionRet = TRUE;     // store function return value, assume success.
    int iLocalRet;
    SERVICE_STATUS ssStatus;
    TCHAR szBuffer[MAX_PATH];


    //
    // Service control manager works by first "opening" it...
    //

    schSCManager = OpenSCManager(
                        NULL,                   // machine (NULL == local)
                        NULL,                   // database (NULL == default)
                        SC_MANAGER_ALL_ACCESS); // access required

    if (!schSCManager) {
        catqReportError ( GetLastError() );
        iFunctionRet = FALSE;
        goto CloseSCAndReturn;
    }


    //
    // With the service control manager handle, now try and open the
    //  specific service that we are interested in.
    //

    schCIService = OpenService (schSCManager,
                              SZ_CISERVICE_NAME,  // known name from .h file
                              SERVICE_ALL_ACCESS);

    if (!schCIService) {
        catqReportError ( GetLastError() );
        iFunctionRet = FALSE;
        goto CloseSCAndReturn;
    }


    //
    // With the CI service handle, now query its status
    //

    iLocalRet = QueryServiceStatus (schCIService, &ssStatus);

    if (!iLocalRet) {
        catqReportError ( GetLastError() );
        iFunctionRet = FALSE;
        goto CloseCIAndReturn;
    }


    //
    // Report to the user the status of the service
    //

    wsprintf (szBuffer, TEXT("The service %s "), SZ_CISERVICE_NAME);
    switch ( ssStatus.dwCurrentState ) {
        case SERVICE_RUNNING: lstrcat (szBuffer, TEXT("is running.")); break;
        case SERVICE_PAUSED:  lstrcat (szBuffer, TEXT("was paused."));  break;
        case SERVICE_STOPPED: lstrcat (szBuffer, TEXT("was stopped.")); break;
        default:              lstrcat (szBuffer, TEXT("is pending.")); break;
    } // end switch

    //
    // If it is stopped or paused, then try to start it.
    //

    if ((ssStatus.dwCurrentState == SERVICE_STOPPED) ||
        (ssStatus.dwCurrentState == SERVICE_PAUSED)) {
            lstrcat (szBuffer, TEXT(" ... Attempting to start it."));

            iLocalRet = StartService (schCIService, 0, NULL);
            if (!iLocalRet) {
                catqReportError ( GetLastError() );
                iFunctionRet = FALSE;
                goto CloseCIAndReturn;
            }
    }


    //
    // Exit this function here at the end to ensure that the SC Manager
    //  handle is freed correctly.
    //

CloseCIAndReturn:

    catqLogComment (szBuffer);

    CloseServiceHandle(schCIService);

CloseSCAndReturn:

    CloseServiceHandle(schSCManager);

    return iFunctionRet;
}
