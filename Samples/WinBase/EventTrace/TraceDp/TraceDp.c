/*++

Copyright (c) 1997-1999  Microsoft Corporation

Module Name:

    tracedp.c

Abstract:

    Sample trace provider program.

Author:

    Jee Fung Pang (jeepang) 03-Dec-1997

Revision History:

--*/

#define _UNICODE
#define UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <ntverp.h>
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <ole2.h>
#include <wmistr.h>
#include <evntrace.h>
#include <time.h>

#define MAXEVENTS                       5000
#define MAXSTR                          1024

#define MOF_DATA_STRING        _T("This is an example of using MofPtrFlag")

TRACEHANDLE LoggerHandle;
#define ResourceName _T("MofResource")
TCHAR ImagePath[MAXSTR];

GUID TransactionGuid = 
    {0xce5b1020, 0x8ea9, 0x11d0, 0xa4, 0xec, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0x10};
GUID   ControlGuid  =
    {0xd58c126f, 0xb309, 0x11d1, 0x96, 0x9e, 0x00, 0x00, 0xf8, 0x75, 0xa5, 0xbc};

TRACE_GUID_REGISTRATION TraceGuidReg[] =
{
    { (LPGUID)&TransactionGuid,
      NULL
    }
};

typedef enum {
    TYPE_USER_EVENT,
    TYPE_INSTANCE_EVENT,
    TYPE_MOF_EVENT
} TypeEventType;

typedef struct _USER_EVENT {
    EVENT_TRACE_HEADER    Header;
    ULONG                 EventInfo;
} USER_EVENT, *PUSER_EVENT;

typedef struct _USER_INSTANCE_EVENT {
    EVENT_INSTANCE_HEADER    Header;
    ULONG                    mofData;
} USER_INSTANCE_EVENT, *PUSER_INSTANCE_EVENT;

typedef struct _USER_MOF_EVENT {
    EVENT_TRACE_HEADER    Header;
    MOF_FIELD             mofData;
} USER_MOF_EVENT, *PUSER_MOF_EVENT;

TypeEventType EventType = TYPE_USER_EVENT;
TRACEHANDLE RegistrationHandle;
BOOLEAN TraceOnFlag;
ULONG EnableLevel = 0;
ULONG EnableFlags = 0;

ULONG InitializeTrace(
    IN LPTSTR ExePath
    );

ULONG
ControlCallback(
    IN WMIDPREQUESTCODE RequestCode,
    IN PVOID Context,
    IN OUT ULONG *InOutBufferSize,
    IN OUT PVOID Buffer
    );

LPTSTR
DecodeStatus(
    IN ULONG Status
    );

TCHAR ErrorMsg[MAXSTR];

__cdecl main(argc, argv)
	int argc;
	char **argv;
{
	ULONG status;
    USER_EVENT          UserEvent;
    USER_INSTANCE_EVENT UserInstanceEvent;
    USER_MOF_EVENT      UserMofEvent;
    EVENT_INSTANCE_INFO InstInfo;
    PMOF_FIELD          mofField;
    ULONG i;
    ULONG    MaxEvents;
    ULONG   InstanceId;
    LPGUID  Guid = NULL;
    PWNODE_HEADER Wnode;
    TCHAR   strMofData[MAXSTR];

    MaxEvents = MAXEVENTS;
    TraceOnFlag = FALSE;

    // process command line arguments to override defaults
    //
    while (--argc > 0)
    {
        argv ++;
        if (**argv == '-' || **argv == '/')
        {
            **argv = '-';

            if (!_stricmp(argv[0],"-UseEventTraceHeader"))
            {
                EventType = TYPE_USER_EVENT;
            }
            else if (!_stricmp(argv[0],"-UseEventInstanceHeader"))
            {
                EventType = TYPE_INSTANCE_EVENT;
            }
            else if (!_stricmp(argv[0],"-UseMofPtrFlag"))
            {
                EventType = TYPE_MOF_EVENT;
            }
            else
            {
                printf("Usage: TraceDp [options] [event#]\n");
                printf("\t-UseEventTraceHeader\n");
                printf("\t-UseEventInstanceHeader\n");
                printf("\t-UseMofPtrFlag\n");
                return 0;
            }
        }
        else if (** argv >= '0' && ** argv <= '9')
        {
            MaxEvents = atoi(argv[0]);
        }
    }

    status = InitializeTrace(_T("tracedp.exe"));
    if (status != ERROR_SUCCESS) {
       return 0;
    }

    _tprintf(_T("Testing Logger with %d events\n"), MaxEvents);


    RtlZeroMemory(&UserEvent, sizeof(UserEvent));
    Wnode = (PWNODE_HEADER) &UserEvent;
    UserEvent.Header.Size  = sizeof(USER_EVENT);
    UserEvent.Header.Flags = WNODE_FLAG_TRACED_GUID;
    UserEvent.Header.Guid  =  TransactionGuid;

    RtlZeroMemory(&UserInstanceEvent, sizeof(UserInstanceEvent));
    UserInstanceEvent.Header.Size  = sizeof(UserInstanceEvent);
    UserInstanceEvent.Header.Flags = WNODE_FLAG_TRACED_GUID;

    RtlZeroMemory(&UserMofEvent, sizeof(UserMofEvent));
    Wnode = (PWNODE_HEADER) &UserMofEvent;
    UserMofEvent.Header.Size  = sizeof(UserMofEvent);
    UserMofEvent.Header.Flags = WNODE_FLAG_TRACED_GUID;
    UserMofEvent.Header.Guid  =  TransactionGuid;
    _tcscpy(strMofData, MOF_DATA_STRING);

    while (! TraceOnFlag)
        _sleep(1000);

    i = 0;
    while (TraceOnFlag) {

        if (i == ((i / 2) * 2) ) {
            UserEvent.Header.Class.Type         = EVENT_TRACE_TYPE_START;
            UserInstanceEvent.Header.Class.Type = EVENT_TRACE_TYPE_START;
            UserMofEvent.Header.Class.Type      = EVENT_TRACE_TYPE_START;
        }
        else {
            UserEvent.Header.Class.Type         = EVENT_TRACE_TYPE_END;
            UserInstanceEvent.Header.Class.Type = EVENT_TRACE_TYPE_END;
            UserMofEvent.Header.Class.Type      = EVENT_TRACE_TYPE_END;
        }

        switch (EventType)
        {
        case TYPE_INSTANCE_EVENT:
            if (UserInstanceEvent.Header.Class.Type == EVENT_TRACE_TYPE_START) {
                status = CreateTraceInstanceId(
                                (PVOID) TraceGuidReg[0].RegHandle,
                                & InstInfo);

                if (status != ERROR_SUCCESS) {
                    fprintf(stderr, 
                             "CreatTraceInstanceId() status=%d, %s\n",
                             status, DecodeStatus(status)
                             );
                    goto Cleanup;
                }
            }
            status = TraceEventInstance(
                        LoggerHandle, 
                        (PEVENT_INSTANCE_HEADER) & UserInstanceEvent,
                        & InstInfo,
                        NULL);
            break;

        case TYPE_USER_EVENT:
            status = TraceEvent(
                            LoggerHandle,
                            (PEVENT_TRACE_HEADER) & UserEvent);
            break;

        case TYPE_MOF_EVENT:
            UserMofEvent.Header.Flags |= WNODE_FLAG_USE_MOF_PTR;
            mofField          = (PMOF_FIELD) & UserMofEvent.mofData;
            mofField->DataPtr = (ULONGLONG) (strMofData);
            mofField->Length  = sizeof(TCHAR) * (_tcslen(strMofData) + 1);
            status = TraceEvent(
                            LoggerHandle,
                            (PEVENT_TRACE_HEADER) & UserMofEvent);
            break;

        default:
            status = ERROR_SUCCESS;
            break;
        }

        // logger buffers out of memory should not prevent provider from
        // generating events. This will only cause events lost.
        //
        if (status == ERROR_NOT_ENOUGH_MEMORY) {
            status = ERROR_SUCCESS;
        }

        if (status != ERROR_SUCCESS) {
            _ftprintf(stderr, _T("\nError %s while writing event\n"),
                      DecodeStatus(status));
            _ftprintf( stderr, _T("Use GUID to disable Logger\n"));
            _ftprintf( stderr, _T("Logging Terminated\n"));
            goto Cleanup;
        }

        i++;
        if (i >= MaxEvents)
            break;

        if ( !(i % 100) )
            _tprintf(_T("."));
        _sleep(1);
    }

Cleanup:
    UnregisterTraceGuids(RegistrationHandle);
    return status;
}

LPTSTR
DecodeStatus(
    IN ULONG Status
    )
{
    memset( ErrorMsg, 0, MAXSTR );
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        Status,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) ErrorMsg,
        MAXSTR,
        NULL );
    return ErrorMsg;
}

ULONG InitializeTrace(
    IN LPTSTR ExePath
    )
{
    ULONG Status;
    Status = GetModuleFileName(NULL, &ImagePath[0], MAXSTR*sizeof(TCHAR));
    if (Status == 0) {
        return (ERROR_FILE_NOT_FOUND);
    }

    Status = RegisterTraceGuids(
                ControlCallback,
                NULL,                 // RequestContext
                (LPGUID)&ControlGuid,
                1,
                TraceGuidReg,
                (LPCTSTR)&ImagePath[0],
                (LPCTSTR)ResourceName,
                &RegistrationHandle);

    if (Status != ERROR_SUCCESS) {
        _tprintf(_T("Trace registration failed\n"));
    }
    else {
        _tprintf(_T("Trace registered successfully\n"));
    }
    return(Status);
}

ULONG
ControlCallback(
    IN WMIDPREQUESTCODE RequestCode,
    IN PVOID Context,
    IN OUT ULONG *InOutBufferSize,
    IN OUT PVOID Buffer
    )
{
    ULONG Status;
    ULONG RetSize;

    Status = ERROR_SUCCESS;

    switch (RequestCode)
    {
        case WMI_ENABLE_EVENTS:
        {
            RetSize = 0;
            LoggerHandle = GetTraceLoggerHandle( Buffer );
            EnableLevel = GetTraceEnableLevel(LoggerHandle);
            EnableFlags = GetTraceEnableFlags(LoggerHandle);
            _tprintf(_T("Logging enabled to 0x%016I64x\n"), LoggerHandle);
            TraceOnFlag = TRUE;
            break;
        }

        case WMI_DISABLE_EVENTS:
        {
            TraceOnFlag = FALSE;
            RetSize = 0;
            LoggerHandle = 0;
            _tprintf(_T("\nLogging Disabled\n"));
            break;
        }
        default:
        {
            RetSize = 0;
            Status = ERROR_INVALID_PARAMETER;
            break;
        }

    }

    *InOutBufferSize = RetSize;
    return(Status);
}
