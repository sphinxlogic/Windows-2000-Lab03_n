/*++

Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.

Module Name:

    pdhprog.cxx

Abstract:

    functions to query the performance data helper (PDH) DLL in order to
     get the current status of the content indexing effort.

Revision History:

    Steve Firebaugh     9-97          Created from previous samples

--*/


#include <windows.h>
#include <pdh.h>
#include "catq.h"


//
// Here are the names of two of the performance counters that the CISVC
//  service logs to the performance registry.  See Content Indexing doc.
//  (or perfmon) for the others.
//

#define PSZ_COUNTER_TOBEFILTERED TEXT ("\\\\.\\Indexing Service(system)\\Files to be indexed")
#define PSZ_COUNTER_TOTALNUMDOCS TEXT ("\\\\.\\Indexing Service(system)\\Total # documents")



int catqPDHQueryProgress ( LPLONG lpToBeFiltered, LPLONG lpTotal)
/*++

    Query the current status of the content indexing service by
     querying performance data via the "performance data helper" DLL
     (first introduced in NT4 and now a part of the operating system).
     The return value is the approximate percentage complete, the two
     long parameters are the numerator and denominator of that ratio.

    Return value in [0,100] if success, else CATQ_PROGRESS_ERROR

--*/
{
    int        iReturn = CATQ_PROGRESS_ERROR;
    HQUERY     hQuery;
    HCOUNTER   arCounter[2] = {0,0};
    PDH_STATUS pdhStatus;
    PDH_FMT_COUNTERVALUE   arFmtValue[2];
    DWORD           ctrType;

    //
    // First step in using PDH is to open a "query"...
    //

    pdhStatus = PdhOpenQuery (0, 0, &hQuery);
    if (pdhStatus != ERROR_SUCCESS) {
      catqLogComment (TEXT("PdhOpenQuery failed"));
      goto ClosePDHAndReturn;
    }


    //
    // With the query handle, we now add two "counters"...
    //  If this fails, see error codes in pdhmsg.h
    //

    pdhStatus = PdhAddCounter (hQuery,
                               PSZ_COUNTER_TOBEFILTERED,
                               0,
                               &arCounter[0]);
    if (pdhStatus != ERROR_SUCCESS) {
      catqLogComment (TEXT("PdhAddCounter failed"));
      goto ClosePDHAndReturn;
    }

    pdhStatus = PdhAddCounter (hQuery,
                               PSZ_COUNTER_TOTALNUMDOCS,
                               0,
                               &arCounter[1]);
    if (pdhStatus != ERROR_SUCCESS) {
      catqLogComment (TEXT("PdhAddCounter failed"));
      goto ClosePDHAndReturn;
    }

    //
    // Now that everything is setup, actually do the query to bind
    //  values to the counters...
    //

    pdhStatus = PdhCollectQueryData (hQuery);
    if (pdhStatus != ERROR_SUCCESS) {
      catqLogComment (TEXT("PdhCollectQueryData failed"));
      goto ClosePDHAndReturn;
    }


    //
    // And finally, get the formatted values...
    //

    pdhStatus = PdhGetFormattedCounterValue (arCounter[0],
                                             PDH_FMT_LONG,
                                             &ctrType,
                                             &arFmtValue[0]);

    if (pdhStatus != ERROR_SUCCESS) {
      catqLogComment (TEXT("PdhGetFormattedCounterValue failed"));
      goto ClosePDHAndReturn;
    }

    *lpToBeFiltered = arFmtValue[0].longValue;

    pdhStatus = PdhGetFormattedCounterValue (arCounter[1],
                                             PDH_FMT_LONG,
                                             &ctrType,
                                             &arFmtValue[1]);

    if (pdhStatus != ERROR_SUCCESS) {
      catqLogComment (TEXT("PdhGetFormattedCounterValue failed"));
      goto ClosePDHAndReturn;
    }

    *lpTotal = arFmtValue[1].longValue;


    //
    // We succeeded in getting formatted performance data.
    //  Compute the return value, clip it to the spec.ed bounds...
    //

    if (*lpTotal != 0)
      iReturn = (int) (((*lpTotal - *lpToBeFiltered) *100 ) / *lpTotal);

    if (iReturn <0 )   iReturn = 0;
    if (iReturn >100 ) iReturn = 100;


    //
    // Close the handle and return.
    //

ClosePDHAndReturn:

    PdhRemoveCounter( arCounter[0] );
    PdhRemoveCounter( arCounter[1] );

    pdhStatus = PdhCloseQuery (hQuery);
    return iReturn;

}
