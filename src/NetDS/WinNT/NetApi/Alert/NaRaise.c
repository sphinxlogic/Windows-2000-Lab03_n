// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NARaise.c
// DESCRIPTION:   Notifies all registered clients that a particular
//                event occurred
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          3/10/98
//

#define UNICODE
#define _UNICODE

#define INCL_NETERRORS
#define INCL_NETALERT

#include <windows.h>
#include <lm.h>
#include <time.h>
#include <stdio.h>

//Setup some default strings

#define PROGRAM_NAME TEXT("NETALRT")
#define szComputerName  TEXT("\\\\GARYY2")
#define szUserName      TEXT("GARYY1")
#define szQueueName     TEXT("PQUEUE")
#define szDestName      TEXT("MYPRINTER")
#define szStatus     TEXT("OK")

//Setup some structure sizes
#define VAREDSIZE 216
#define BUFFSIZE  sizeof(STD_ALERT) + VAREDSIZE


int main()
{
    time_t now;
    PSTD_ALERT pStdAlert;
    PADMIN_OTHER_INFO pAdminInfo;
    PPRINT_OTHER_INFO pPrintInfo;
    PUSER_OTHER_INFO pUserInfo;
    TCHAR *p;

    DWORD res;


    time(&now);

    // Setup the default values for the STD_ALERT structure
    pStdAlert = (PSTD_ALERT) GlobalAlloc(GPTR, BUFFSIZE);
    pStdAlert->alrt_timestamp = now;
    lstrcpy(pStdAlert->alrt_servicename, PROGRAM_NAME);

    // SetupPointers to the Alert Structures

    // SendAdminAlert
    lstrcpy(pStdAlert->alrt_eventname, ALERT_ADMIN_EVENT);
    pAdminInfo = (PADMIN_OTHER_INFO) ALERT_OTHER_INFO(pStdAlert);
    pAdminInfo->alrtad_errcode = 2377;
    pAdminInfo->alrtad_numstrings = 1;

    p = (LPTSTR) ALERT_VAR_DATA(pAdminInfo);
    lstrcpy(p, TEXT("'C:\\MYLOG.TXT'"));

    res = NetAlertRaise(ALERT_ADMIN_EVENT, pStdAlert, BUFFSIZE);
    printf("%s\t%u\n", pStdAlert->alrt_eventname, res);

    // SendPrintAlert
    lstrcpy(pStdAlert->alrt_eventname, ALERT_PRINT_EVENT);

    pPrintInfo = (PPRINT_OTHER_INFO) ALERT_OTHER_INFO(pStdAlert);
    ZeroMemory(pPrintInfo, VAREDSIZE);
    pPrintInfo->alrtpr_jobid = 5457;
    pPrintInfo->alrtpr_status = 0;
    pPrintInfo->alrtpr_submitted = now;
    pPrintInfo->alrtpr_size = 1000;

    p = (LPTSTR) ALERT_VAR_DATA(pPrintInfo);
    lstrcpy(p, szComputerName);
    p += lstrlen(p) + 1;
    lstrcpy(p, szUserName);
    p += lstrlen(p) + 1;
    lstrcpy(p, szQueueName);
    p += lstrlen(p) + 1;
    lstrcpy(p, szDestName);
    p += lstrlen(p) + 1;
    lstrcpy(p, szStatus);

    res = NetAlertRaise(ALERT_PRINT_EVENT, pStdAlert, BUFFSIZE);
    printf("%s\t%u\n", pStdAlert->alrt_eventname, res);

    // SendUserAlert
    // To pass a user defined structure and pass valid strings
    // you must create a message file and link it with your application,
    // then register that application as the EventMessageFile in the
    // event log section of the registry.

    lstrcpy(pStdAlert->alrt_eventname, ALERT_USER_EVENT);

    pUserInfo = (PUSER_OTHER_INFO) ALERT_OTHER_INFO(pStdAlert);
    ZeroMemory(pUserInfo, VAREDSIZE);

    p = (LPTSTR) ALERT_VAR_DATA(pUserInfo);
    pUserInfo->alrtus_errcode = -1;
    pUserInfo->alrtus_numstrings = 1;
    lstrcpy(p, TEXT("C:\\USERLOG.TXT"));
    p += lstrlen(p) + 1;
    lstrcpy(p, szUserName);

    res = NetAlertRaise(ALERT_USER_EVENT, pStdAlert, BUFFSIZE);
    printf("%s\t%u\n", pStdAlert->alrt_eventname, res);

    GlobalFree(pStdAlert);
    return (res);
}
