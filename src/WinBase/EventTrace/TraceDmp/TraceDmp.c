/*++

Copyright (c) 1997-1999  Microsoft Corporation

Module Name:

    tracedmp.c

Abstract:

    Sample trace consumer program. Converts binary trace file to CSV format

Author:

    Jee Fung Pang (jeepang) 03-Dec-1997

Revision History:

--*/

#ifdef __cplusplus
extern "C"{
#endif 
#define UNICODE
#define _UNICODE
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <shellapi.h>
#include <tchar.h>
#include <wmistr.h>
#include <objbase.h>
#include <initguid.h>
#include <evntrace.h>

#define MAXLOGFILES         16
#define MAXSTR              512
#define MAXTYPE             256
#define MAXGUIDS            256 
#define UC(x)               ( (UINT)((x) & 0xFF) )
#define NTOHS(x)            ( (UC(x) * 256) + UC((x) >> 8) )

#define DUMP_FILE_NAME          _T("DumpFile.csv")
#define SUMMARY_FILE_NAME       _T("Summary.txt")
#define GUID_FILE               _T("MofData")
#define GUID_EXT                _T("guid")
#define DEFAULT_LOGFILE_NAME    _T("C:\\Logfile.Evm")
#define KERNEL_LOGGER_NAME      _T("NT Kernel Logger")

#ifndef IsEqualGUID
#define IsEqualGUID(guid1, guid2) \
                (!memcmp((guid1), (guid2), sizeof(GUID)))
#endif

#define InitializeListHead(ListHead) (\
    (ListHead)->Flink = (ListHead)->Blink = (ListHead))

#define InsertTailList(ListHead,Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_ListHead;\
    _EX_ListHead = (ListHead);\
    _EX_Blink = _EX_ListHead->Blink;\
    (Entry)->Flink = _EX_ListHead;\
    (Entry)->Blink = _EX_Blink;\
    _EX_Blink->Flink = (Entry);\
    _EX_ListHead->Blink = (Entry);\
    }

#define RemoveEntryList(Entry) {\
    PLIST_ENTRY _EX_Blink;\
    PLIST_ENTRY _EX_Flink;\
    _EX_Flink = (Entry)->Flink;\
    _EX_Blink = (Entry)->Blink;\
    _EX_Blink->Flink = _EX_Flink;\
    _EX_Flink->Blink = _EX_Blink;\
    }

FILE* DumpFile = NULL;
FILE* SummaryFile = NULL;

static ULONG TotalBuffersRead = 0;
static ULONG TotalEventsLost = 0;
static ULONG TotalEventCount = 0;
static ULONG TimerResolution = 10;
static __int64 ElapseTime;

PCHAR  MofData    = NULL;
size_t MofLength  = 0;
BOOLEAN fSummaryOnly  = FALSE;
BOOLEAN fDebugDisplay = FALSE;
ULONG PointerSize = sizeof(PVOID) * 8;

typedef struct _MOF_INFO {
    LIST_ENTRY   Entry;
    LPTSTR       strDescription;        // Class Name
    ULONG        EventCount;            
    GUID         Guid;
    PLIST_ENTRY  ItemHeader;            
    LPTSTR       strType;
    LONG         TypeIndex;
    LPTSTR       strFormat;
}  MOF_INFO, *PMOF_INFO;

typedef struct _MOF_TYPE {
    TCHAR     strType[MAXSTR];
    LONG      TypeIndex;
    TCHAR     strFormat[MAXSTR];
} MOF_TYPE, *PMOF_TYPE;

PLIST_ENTRY EventListHead = NULL;

typedef enum _ITEM_TYPE {
    ItemChar,
    ItemUChar,
    ItemCharShort,
    ItemCharSign,
    ItemShort,
    ItemUShort,
    ItemLong,
    ItemULong,
    ItemULongX,
    ItemLongLong,
    ItemULongLong,
    ItemString,
    ItemWString,
    ItemRString,
    ItemRWString,
    ItemPString,
    ItemPWString,
    ItemDSString,
    ItemDSWString,
    ItemSid,
    ItemChar4,
    ItemIPAddr,
    ItemPort,
    ItemMLString,
    ItemNWString,        // Non-null terminated Wide Char String
    ItemPtr,
    ItemUnknown
} ITEM_TYPE;

typedef struct _ITEM_DESC *PITEM_DESC;
typedef struct _ITEM_DESC {
    LIST_ENTRY Entry;
    LPTSTR strDescription;
    ULONG DataSize;
    ITEM_TYPE ItemType;
} ITEM_DESC;

void 
DumpMofList();

VOID
AddMofInfo(
    const GUID *Guid,
    LPTSTR strType,
    ULONG typeIndex,
    LPTSTR strDesc,
    ITEM_TYPE ItemType,
    LPTSTR strFormat
    );

ULONG 
GetGuids(
    LPTSTR GuidFile, 
    LPGUID *GuidArray
    );

ULONG 
ahextoi(
    TCHAR *s
    );

void
PrintMofInfo();

ITEM_TYPE 
MapType(
   IN DWORD vtTest 
       );

PMOF_INFO
GetMofInfoHead(
    LPGUID pGuid,
    LPTSTR strType,
    LONG TypeIndex,
    LPTSTR strFormat,
    BOOL bBestMatch
    );

ULONG
CheckFile(
    LPTSTR fileName
    );

void
CleanupEventList(
    VOID
    );

ULONG
BufferCallback(
    PEVENT_TRACE_LOGFILE pLog
    );

void 
AddMofFromWbem(
    LPTSTR EventGuid,
    LPTSTR PropName,
    DWORD  PropType
    );

void
DumpEvent(
    PEVENT_TRACE pEvent
    );

BOOL 
wGUIDFromString(
    LPCTSTR lpsz, 
    LPGUID pguid
    );

void
RemoveMofInfo(
    PLIST_ENTRY pMofInfo
    );
PTCHAR GuidToString(
    PTCHAR s,
    LPGUID piid
    );

void
MapGuidToName(
    IN LPGUID pGuid,
    IN ULONG nType,
    OUT LPTSTR wstr
    );

ULONG
UserDefinedGuid(
    IN LPGUID Guid,
    OUT LPTSTR wstr);

static void reduceA(char *Src)
{
    char *Start = Src;
    if (!Src)
        return;
    while (*Src)
    {
        if ('\t' == *Src)
            *Src = ' ';
        else if (',' == *Src)
            *Src = ' ';
        else if ('\n' == *Src)
            *Src = ',';
        else if ('\r' == *Src)
            *Src = ' ';
        ++Src;
    }
    --Src;
    while ((Start < Src) && ((' ' == *Src) || (',' == *Src)))
    {
        *Src = 0x00;
        --Src;
    }
}

static void reduceW(WCHAR *Src)
{
    WCHAR *Start = Src;
    if (!Src)
        return;
    while (*Src)
    {
        if (L'\t' == *Src)
            *Src = L' ';
        else if (L',' == *Src)
            *Src = L' ';
        else if (L'\n' == *Src)
            *Src = L',';
        else if (L'\r' == *Src)
            *Src = L' ';
        ++Src;
    }
    --Src;
    while ((Start < Src) && ((L' ' == *Src) || (L',' == *Src)))
    {
        *Src = 0x00;
        --Src;
    }
}


#define GUID_TYPE_HEADER                _T("Header")
#define GUID_TYPE_UNKNOWN               _T("Unknown")
    
#define STR_ItemChar                    _T("ItemChar")
#define STR_ItemUChar                   _T("ItemUChar")
#define STR_ItemCharShort               _T("ItemCharShort")
#define STR_ItemCharSign                _T("ItemCharSign")
#define STR_ItemShort                   _T("ItemShort")
#define STR_ItemUShort                  _T("ItemUShort")
#define STR_ItemLong                    _T("ItemLong")
#define STR_ItemULong                   _T("ItemULong")
#define STR_ItemULongX                  _T("ItemULongX")
#define STR_ItemLongLong                _T("ItemLongLong")
#define STR_ItemULongLong               _T("ItemULongLong")
#define STR_ItemString                  _T("ItemString")
#define STR_ItemWString                 _T("ItemWString")
#define STR_ItemRString                 _T("ItemRString")
#define STR_ItemRWString                _T("ItemRWString")
#define STR_ItemPString                 _T("ItemPString")
#define STR_ItemPWString                _T("ItemPWString")
#define STR_ItemDSString                _T("ItemDSString")
#define STR_ItemDSWString               _T("ItemDSWString")
#define STR_ItemMLString                _T("ItemMLString")
#define STR_ItemSid                     _T("ItemSid")
#define STR_ItemChar4                   _T("ItemChar4")
#define STR_ItemIPAddr                  _T("ItemIPAddr")
#define STR_ItemPort                    _T("ItemPort")
#define STR_ItemNWString                _T("ItemNWString")
#define STR_ItemPtr                     _T("ItemPtr")

PEVENT_TRACE_LOGFILE EvmFile[MAXLOGFILES];
ULONG LogFileCount = 0;
ULONG UserMode = FALSE; // TODO: Pick this up from the stream itself.


int
 __cdecl main (argc, argv)
    int argc;
    char **argv;
{
    TCHAR GuidFileName[MAXSTR];
    TCHAR DumpFileName[MAXSTR];
    TCHAR SummaryFileName[MAXSTR];
    LPTSTR *targv;
#ifdef UNICODE
    LPTSTR *cmdargv;
#endif
    LPGUID *GuidArray;
    PEVENT_TRACE_LOGFILE pLogFile;
    ULONG Action = 0;
    ULONG Status;
    ULONG GuidCount = 0;
    ULONG i, j;
    TRACEHANDLE HandleArray[MAXLOGFILES];

    GuidArray = (LPGUID *) malloc(MAXGUIDS * sizeof(GuidArray));

    for (GuidCount=0; GuidCount<MAXGUIDS; GuidCount++)
        GuidArray[GuidCount] = (LPGUID) malloc(sizeof(GUID));
    GuidCount = 0;
    
#ifdef UNICODE
    if ((cmdargv = CommandLineToArgvW(
                        GetCommandLineW(),	// pointer to a command-line string
                        &argc				// receives the argument count
                        )) == NULL)
    {
        return(GetLastError());
    };
    targv = cmdargv ;
#else
    targv = argv;
#endif

    _tcscpy(DumpFileName, DUMP_FILE_NAME);
    _tcscpy(SummaryFileName, SUMMARY_FILE_NAME);

    // By default look for Define.guid in the image location

    Status = GetModuleFileName(NULL, GuidFileName, MAXSTR);

    if( Status != 0 ){
        TCHAR drive[10];
        TCHAR path[MAXSTR];
        TCHAR file[MAXSTR];
        TCHAR ext[MAXSTR];

        _tsplitpath( GuidFileName, drive, path, file, ext );
        _tcscpy(ext, GUID_EXT );
        _tcscpy(file, GUID_FILE );
        _tmakepath( GuidFileName, drive, path, file, ext );
    }else{
        _tcscpy( GuidFileName, GUID_FILE );
        _tcscat( GuidFileName, _T(".") );
        _tcscat( GuidFileName, GUID_EXT );
    }

    while (--argc > 0) {
        ++targv;
        if (**targv == '-' || **targv == '/') {  // argument found
            if( **targv == '/' ){
                **targv = '-';
            }
            //TODO: Add Start / End time windowing. 

            if ( !_tcsicmp(targv[0], _T("-begin") )) {
                if (argc > 1) {
                    if (targv[1][0] != '-' && targv[1][0] != '/') {
                        ++targv; --argc;
                    // Need to convert the start and end times to ULONGLONG 
                    }
                }
            }
            else if ( !_tcsicmp(targv[0], _T("-end")) ) {
                if (argc > 1) {
                    if (targv[1][0] != '-' && targv[1][0] != '/') {
                        ++targv; --argc;
                    }
                }
            }
           else if ( !_tcsicmp(targv[0], _T("-um")) ) {
               UserMode = TRUE;
           }
           else if ( !_tcsicmp(targv[0], _T("-summary")) ) {
               fSummaryOnly = TRUE;
           }
           else if ( !_tcsicmp(targv[0], _T("-debug")) ) {
               fDebugDisplay = TRUE;
           }
           else if (targv[0][1] == 'h' || targv[0][1] == 'H'
                                       || targv[0][1] == '?')
           {
               _tprintf(
                   _T("Usage: tracedmp [options]  <evmfile>| [-h | -?]\n")
                   _T("\t-o <file>    Output CSV file\n")
                   _T("\t-guid <file> MOF definition file\n")
                   _T("\t-rt          Realtime tracedmp\n")
                   _T("\t-summary     Summary.txt only\n")
                   _T("\t-debug       debug display\n")
                   _T("\t-begin\n")
                   _T("\t-end\n")
                   _T("\t-h\n")
                   _T("\t-?           Prints this information\n")
                   _T("\n")
                   _T("\tDefault evmfile if c:\\logfile.evm\n")
                   _T("\tDefault outputfile is dumpfile.csv\n")
                   _T("\tDefault GUID file is mofdata.guid\n")
                   );
               return 0;
           }
           else if ( !_tcsicmp(targv[0], _T("-rt")) ) {
               TCHAR LoggerName[MAXSTR];
               _tcscpy(LoggerName, KERNEL_LOGGER_NAME);
               if (argc > 1) {
                   if (targv[1][0] != '-' && targv[1][0] != '/') {
                       ++targv; --argc;
                       _tcscpy(LoggerName, targv[0]);
                   }
               }
               
               pLogFile = malloc(sizeof(EVENT_TRACE_LOGFILE));
               if (pLogFile == NULL){
                   _tprintf(_T("Allocation Failure\n"));
                   
                   goto cleanup;
               }
               RtlZeroMemory(pLogFile, sizeof(EVENT_TRACE_LOGFILE));
               EvmFile[LogFileCount] = pLogFile;
               
               EvmFile[LogFileCount]->LogFileName = NULL;
               EvmFile[LogFileCount]->LoggerName =
                   (LPTSTR) malloc(MAXSTR*sizeof(TCHAR));
               
               if ( EvmFile[LogFileCount]->LoggerName == NULL ) {
                   _tprintf(_T("Allocation Failure\n"));
                   goto cleanup;
               }
               _tcscpy(EvmFile[LogFileCount]->LoggerName, LoggerName);
               
               _tprintf(_T("Setting RealTime mode for  %s\n"),
                        EvmFile[LogFileCount]->LoggerName);
               
               EvmFile[LogFileCount]->Context = NULL;
               EvmFile[LogFileCount]->BufferCallback = BufferCallback;
               EvmFile[LogFileCount]->BuffersRead = 0;
               EvmFile[LogFileCount]->CurrentTime = 0;
               EvmFile[LogFileCount]->EventCallback = &DumpEvent;
               EvmFile[LogFileCount]->LogFileMode =
                   EVENT_TRACE_REAL_TIME_MODE;
               LogFileCount++;
           }
            else if ( !_tcsicmp(targv[0], _T("-guid")) ) {
                if (argc > 1) {
                    if (targv[1][0] != '-' && targv[1][0] != '/') {
                        _tcscpy(GuidFileName, targv[1]);
                        ++targv; --argc;
                    }
                }
            }
            else if ( !_tcsicmp(targv[0], _T("-o")) ) {
                if (argc > 1) {

                    if (targv[1][0] != '-' && targv[1][0] != '/') {
             		TCHAR drive[10];
                        TCHAR path[MAXSTR];
                        TCHAR file[MAXSTR];
                        TCHAR ext[MAXSTR];
                        ++targv; --argc;

                        _tfullpath(DumpFileName, targv[0], MAXSTR);
                        _tsplitpath( DumpFileName, drive, path, file, ext );
                        _tcscpy(ext,_T("csv"));
                        _tmakepath( DumpFileName, drive, path, file, ext );
                        _tcscpy(ext,_T("txt"));  
                        _tmakepath( SummaryFileName, drive, path, file, ext );

                    }
                }
            }
        }
        else {
            pLogFile = malloc(sizeof(EVENT_TRACE_LOGFILE));
            if (pLogFile == NULL){ 
                _tprintf(_T("Allocation Failure\n")); // Need to cleanup better. 
                goto cleanup;
            }
            RtlZeroMemory(pLogFile, sizeof(EVENT_TRACE_LOGFILE));
            EvmFile[LogFileCount] = pLogFile;

            EvmFile[LogFileCount]->LoggerName = NULL;
            EvmFile[LogFileCount]->LogFileName = 
                (LPTSTR) malloc(MAXSTR*sizeof(TCHAR));
            if (EvmFile[LogFileCount]->LogFileName == NULL) {
                _tprintf(_T("Allocation Failure\n"));
                goto cleanup;
            }
            
            _tfullpath(EvmFile[LogFileCount]->LogFileName, targv[0], MAXSTR);
            _tprintf(_T("Setting log file to: %s\n"),
                     EvmFile[LogFileCount]->LogFileName);
            
            if (!CheckFile(EvmFile[LogFileCount]->LogFileName)) {
                _tprintf(_T("Cannot open logfile for reading\n"));
                goto cleanup;
            }
            EvmFile[LogFileCount]->Context = NULL;
            EvmFile[LogFileCount]->BufferCallback = BufferCallback;
            EvmFile[LogFileCount]->BuffersRead = 0;
            EvmFile[LogFileCount]->CurrentTime = 0;
            EvmFile[LogFileCount]->EventCallback = &DumpEvent;
            LogFileCount++;
        }
    }

    if( _tcslen( GuidFileName ) ){
        TCHAR str[MAXSTR];
        _tfullpath( str, GuidFileName, MAXSTR);
        _tcscpy( GuidFileName, str );
        _tprintf(_T("Getting guids from %s\n"), GuidFileName);
        GuidCount = GetGuids(GuidFileName, GuidArray);
    }

    if (LogFileCount <= 0) {
        pLogFile = malloc(sizeof(EVENT_TRACE_LOGFILE));
        if (pLogFile == NULL){ 
            _tprintf(_T("Allocation Failure\n")); // Need to cleanup better. 
            goto cleanup;
        }
        RtlZeroMemory(pLogFile, sizeof(EVENT_TRACE_LOGFILE));
        EvmFile[0] = pLogFile;
        EvmFile[0]->LoggerName = NULL;
        LogFileCount = 1;
        EvmFile[0]->LogFileName = (LPTSTR) malloc(MAXSTR*sizeof(TCHAR));
        if (EvmFile[0]->LogFileName == NULL) {
            _tprintf(_T("Allocation Failure\n"));
            goto cleanup;
        }
        _tcscpy(EvmFile[0]->LogFileName, DEFAULT_LOGFILE_NAME);

        EvmFile[0]->Context        = NULL;
        EvmFile[0]->BuffersRead    = 0;
        EvmFile[0]->CurrentTime    = 0;
        EvmFile[0]->BufferCallback = BufferCallback;
        EvmFile[0]->EventCallback  = & DumpEvent;
    }

    for (i = 0; i < LogFileCount; i++) {
        TRACEHANDLE x;
        x = OpenTrace(EvmFile[i]);
        HandleArray[i] = x;
        if (HandleArray[i] == 0) {
            _tprintf(_T("Error Opening Trace %d with status=%d\n"), 
                                                           i, GetLastError());

            for (j = 0; j < i; j++)
                CloseTrace(HandleArray[j]);
            goto cleanup;
        }
    }

    if (!fSummaryOnly)
    {
        DumpFile = _tfopen(DumpFileName, _T("w"));
        if (DumpFile == NULL) {
            _tprintf(_T("DumpFile is NULL\n"));
            goto cleanup;
        }
    }
    SummaryFile = _tfopen(SummaryFileName, _T("w"));
    if (SummaryFile == NULL) {
        _tprintf(_T("SummaryFile is NULL\n"));
        goto cleanup;
    }

    if (!fSummaryOnly)
    {
        _ftprintf(DumpFile,
            _T("%-15s,%4s,%24s,%8s,%7s, User Data..., IID, PIID\n"),
            _T("Event Name"), _T("TID"), _T("Clock-Time"),
            _T("Kernel-ms"), _T("User-ms"));
    }

    Status = ProcessTrace(HandleArray,
                 LogFileCount,
                 NULL, NULL);
    if (Status != ERROR_SUCCESS) {
        _tprintf(_T("Error processing with status=%dL (GetLastError=0x%x)\n"),
                Status, GetLastError());
    }

    for (j = 0; j < LogFileCount; j++){
        Status = CloseTrace(HandleArray[j]);
        if (Status != ERROR_SUCCESS) {
            _tprintf(_T("Error Closing Trace %d with status=%d\n"), j, Status);
        }
    }

    _ftprintf(SummaryFile,_T("Files Processed:\n"));
    for (i=0; i<LogFileCount; i++) {
        _ftprintf(SummaryFile,_T("\t%s\n"),EvmFile[i]->LogFileName);
    }

    _ftprintf(SummaryFile,
              _T("Total Buffers Processed %d\n")
              _T("Total Events  Processed %d\n")
              _T("Total Events  Lost      %d\n")
              _T("Elapsed Time            %I64d sec\n"), 
              TotalBuffersRead,
              TotalEventCount,
              TotalEventsLost,
              (ElapseTime / 10000000) );

    _ftprintf(SummaryFile,
       _T("+-----------------------------------------------------------------------------------+\n")
       _T("|%10s    %-20s %-10s  %-36s|\n")
       _T("+-----------------------------------------------------------------------------------+\n"),
       _T("EventCount"),
       _T("EventName"),
       _T("EventType"),
       _T("Guid")
        );

    CleanupEventList();

    _ftprintf(SummaryFile,
           _T("+-----------------------------------------------------------------------------------+\n")
        );

cleanup:
    if (!fSummaryOnly && DumpFile != NULL)  {
        _tprintf(_T("Event traces dumped to %s\n"), DumpFileName);
        fclose(DumpFile);
    }

    if(SummaryFile != NULL){
        _tprintf(_T("Event Summary dumped to %s\n"), SummaryFileName);
        fclose(SummaryFile);
    }

    for (i = 0; i < LogFileCount; i ++)
    {
        if (EvmFile[i]->LoggerName != NULL)
        {
            free(EvmFile[i]->LoggerName);
            EvmFile[i]->LoggerName = NULL;
        }
        if (EvmFile[i]->LogFileName != NULL)
        {
            free(EvmFile[i]->LogFileName);
            EvmFile[i]->LogFileName = NULL;
        }
        free(EvmFile[i]);
    }
#ifdef UNICODE
    GlobalFree(cmdargv);
#endif
    for (GuidCount=0; GuidCount<MAXGUIDS; GuidCount++){
        free(GuidArray[GuidCount]);
        GuidArray[GuidCount] = NULL;
    }
    free(GuidArray);

    Status = GetLastError();
    if(Status != ERROR_SUCCESS ){
        _tprintf(_T("Exit Status: %d\n"), Status );
    }

    if (MofData != NULL)
        free(MofData);

    return 0;
}

ULONG
BufferCallback(
    PEVENT_TRACE_LOGFILE pLog
    )
{
    ULONG i;
    ULONG Status;
    EVENT_TRACE_PROPERTIES LoggerProp;

    TotalBuffersRead++;
    TotalEventsLost += pLog->EventsLost;

    //
    // Check to see if any logger is up. If not exit gracefully.
    //
    for (i=0; i<LogFileCount; i++) {
        if (EvmFile[i]->LogFileMode & EVENT_TRACE_REAL_TIME_MODE) {
            RtlZeroMemory(&LoggerProp, sizeof(EVENT_TRACE_PROPERTIES));
            LoggerProp.Wnode.BufferSize = sizeof(EVENT_TRACE_PROPERTIES);
            Status = QueryTrace(
                            0,
                            EvmFile[i]->LoggerName,
                            &LoggerProp);
            if (Status != ERROR_SUCCESS)
                return (FALSE);
        }
    }
    return (TRUE);
}

#define MAXBUFS    4096
#define MAXITEMS    256

TCHAR * pNoValueString = _T("<NoValue>");
TCHAR   ItemBuf[MAXBUFS];
TCHAR   ItemBBuf[MAXBUFS];
PTCHAR  pItemBuf[MAXITEMS];
TCHAR   EventBuf[MAXBUFS];

void
DumpEvent(
    PEVENT_TRACE pEvent
    )
{
    PEVENT_TRACE_HEADER pHeader;
    TCHAR tstr[MAXSTR];
    TCHAR * strFormat = NULL;
    ULONG   iItemCount = 0;
    ULONG   i;
    size_t  ItemsInBuf = 0;

    TotalEventCount++;

    if (pEvent == NULL) {
        _tprintf(_T("pEvent is NULL\n"));
        return;
    }

    pHeader = (PEVENT_TRACE_HEADER) &pEvent->Header;

    MapGuidToName(&pEvent->Header.Guid, pEvent->Header.Class.Type, tstr);

    if (IsEqualGUID(&pEvent->Header.Guid, &EventTraceGuid) && 
            pEvent->Header.Class.Type == EVENT_TRACE_TYPE_INFO) {
        PTRACE_LOGFILE_HEADER head = (PTRACE_LOGFILE_HEADER)pEvent->MofData;
        if(head->TimerResolution > 0){
            TimerResolution = head->TimerResolution / 10000;
        }
        ElapseTime = head->EndTime.QuadPart - 
            pEvent->Header.TimeStamp.QuadPart;
        PointerSize =  head->Reserved32;
        if (PointerSize < 16)       // minimum is 16 bits
            PointerSize = 32;       // defaults = 32 bits
    }

    if (pEvent != NULL) {
        PITEM_DESC pItem;
        char str[MAXSTR];
        WCHAR wstr[MAXSTR];
        PCHAR ptr;
        ULONG ulongword;
        LONG  longword;
        USHORT ushortword;
        SHORT  shortword;
        PMOF_INFO pMofInfo;
        PLIST_ENTRY Head, Next;
        
        char iChar;

        if (MofData == NULL) {
            MofLength = pEvent->MofLength + sizeof(UNICODE_NULL);
            MofData = malloc(MofLength);
        }
        else if ((pEvent->MofLength + sizeof(UNICODE_NULL)) > MofLength) {
            MofLength = pEvent->MofLength + sizeof(UNICODE_NULL);
            MofData = realloc(MofData, MofLength);
        }
        if (MofData == NULL) {
            _tprintf(_T("Cannot allocate memory\n"));
            return;
        }

        memcpy(MofData, pEvent->MofData, pEvent->MofLength);
        MofData[pEvent->MofLength] = 0;
        MofData[pEvent->MofLength+1] = 0;
        ptr = MofData;

        pMofInfo = GetMofInfoHead( &pEvent->Header.Guid, NULL, pEvent->Header.Class.Type, NULL, TRUE );
        if(pMofInfo->strType != NULL){
            _tcscat(tstr,pMofInfo->strType);
        }
        strFormat = pMofInfo->strFormat;

        iItemCount = 0 ;    // How many Items we process
        for (i = 0; i < MAXITEMS; i ++)
        {
            pItemBuf[i] = pNoValueString;
        }

        RtlZeroMemory(ItemBBuf, MAXBUFS * sizeof(TCHAR));
        pItemBuf[iItemCount] = ItemBBuf;    // Where they go

        strFormat = pMofInfo->strFormat;  //  Pointer to the format string

        // Make Parameter %1 Type Name and SubType Name
        //
        if ((LONG) ((ItemsInBuf + _tcslen(tstr) + 1)) < (LONG) MAXBUFS)
        {
            _stprintf(pItemBuf[iItemCount], _T("%s"), tstr);
            pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                   + _tcslen(tstr) + 1;
            iItemCount ++;
            ItemsInBuf = ItemsInBuf + _tcslen(tstr) + 1;
        }

        // Make Parameter %2 ThreadId
        //
        _stprintf(ItemBuf,_T("%X"),pHeader->ThreadId);
        if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
        {
            _stprintf(pItemBuf[iItemCount],_T("%s"),ItemBuf);
            pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                   + _tcslen(ItemBuf) + 1;
            iItemCount ++;
            ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
        }

        // Make Parameter %3 System Time
        //
        _stprintf(ItemBuf, _T("%20I64u"), pHeader->TimeStamp.QuadPart);
        if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
        {
            _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
            pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                   + _tcslen(ItemBuf) + 1;
            iItemCount ++;
            ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
        }

        if (!UserMode)
        {
            // Make Parameter %4 Kernel Time
            //
            _stprintf(ItemBuf, _T("%10lu"),
                      pHeader->KernelTime * TimerResolution);
            if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
            {
                _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
                pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                       + _tcslen(ItemBuf) + 1;
                iItemCount ++;
                ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
            }

            // Make Parameter %5 User Time
            //
            _stprintf(ItemBuf, _T("%10lu"),
                    pHeader->UserTime * TimerResolution);
            if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
            {
                _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
                pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                       + _tcslen(ItemBuf) + 1;
                iItemCount ++;
                ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
            }
        }
        else
        {
            // Make Parameter %4 processor Time
            //
            _stprintf(ItemBuf, _T("%I64u"), pHeader->ProcessorTime);
            if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
            {
                _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
                pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                       + _tcslen(ItemBuf) + 1;
                iItemCount ++;
                ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) +1 ;
            }

            // Make Parameter %5 NULL
            //
            _stprintf(ItemBuf, _T("%s"), NULL);
            if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
            {
                _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
                pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                       + _tcslen(ItemBuf) + 1;
                iItemCount ++;
                ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
            }
        }

        // Make Parameter %6 Instance ID
        //
        _stprintf(ItemBuf, _T("%d"), pEvent->InstanceId);
        if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
        {
            _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
            pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                   + _tcslen(ItemBuf) + 1;
            iItemCount ++;
            ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
        }

        // Make Parameter %7 Parent Instance Id
        //
        _stprintf(ItemBuf, _T("%d"), pEvent->ParentInstanceId);
        if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
        {
            _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
            pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                   + _tcslen(ItemBuf) + 1;
            iItemCount ++;
            ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
        }

        // Make Parameter %8 NULL room for expansion
        //
        _stprintf(ItemBuf, _T("%s"), NULL);
        if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
        {
            _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
            pItemBuf[iItemCount+1] = pItemBuf[iItemCount]
                                   + _tcslen(ItemBuf) + 1;
            iItemCount ++;
            ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
        }

        Head = pMofInfo->ItemHeader;
        pMofInfo->EventCount++;
        Next = Head->Flink;

        while (Head != Next) {
            pItem = CONTAINING_RECORD(Next, ITEM_DESC, Entry);
            if ((ULONG) (ptr - MofData) >= pEvent->MofLength)
            {
                break;
            }

            RtlZeroMemory(ItemBuf, MAXBUFS * sizeof(TCHAR));
            switch (pItem->ItemType)
            {
            case ItemChar:
            case ItemUChar:
//                memcpy(&iChar, ptr, sizeof(CHAR));
                iChar = *((PCHAR) ptr);
                _stprintf(ItemBuf, _T("%c"), iChar);
                ptr += sizeof(CHAR);
                break;

            case ItemCharSign:
            {
                char sign[5];
                memcpy(&sign, ptr, sizeof(CHAR) * 2);
                sign[2] = '\0';
                strcpy(str, sign);
#ifdef UNICODE
                MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, MAXSTR);
                _stprintf(ItemBuf, _T("\"%ws\""), wstr);
#else
                _stprintf(ItemBuf, _T("\"%s\""), str);
#endif
                ptr += sizeof(CHAR)*2;
                break;
            }

            case ItemCharShort:
//                memcpy(&iChar, ptr, sizeof(CHAR));
                iChar = *((PCHAR) ptr);
                _stprintf(ItemBuf, _T("%d"), iChar);
                ptr += sizeof(CHAR);
                break;

            case ItemShort:
                shortword = * ((PSHORT) ptr);
                _stprintf(ItemBuf, _T("%6d"), shortword);
                ptr += sizeof (SHORT);
                break;

            case ItemUShort:
                ushortword = *((PUSHORT) ptr);
//                memcpy(&ushortword, ptr, sizeof(USHORT));
                _stprintf(ItemBuf, _T("%6u"), ushortword);
                ptr += sizeof (USHORT);
                break;

            case ItemLong:
                longword = *((PLONG) ptr);
//                memcpy(&longword, ptr, sizeof(LONG));
                _stprintf(ItemBuf, _T("%8l"), longword);
                ptr += sizeof (LONG);
                break;

            case ItemULong:
                ulongword = *((PULONG) ptr);
                _stprintf(ItemBuf, _T("%8lu"), ulongword);
                ptr += sizeof (ULONG);
                break;

            case ItemULongX:
//                memcpy(&ulongword, ptr, sizeof(ULONG));
                ulongword = *((PULONG) ptr);
                _stprintf(ItemBuf, _T("0x%08X"), ulongword);
                ptr += sizeof (ULONG);
                break;

            case ItemPtr :
            {
                unsigned __int64 pointer;
                if (PointerSize == 64) {
                    pointer = *((unsigned __int64 *) ptr);
                    _stprintf(ItemBuf, _T("0x%X"), pointer);
                }
                else {      // assumes 32 bit otherwise
                    ulongword = *((PULONG) ptr);
                    _stprintf(ItemBuf, _T("0x%08X"), ulongword);
                }
                ptr += PointerSize / 8;
//
// If target source is Win64, then use Ptr, else use ulongword
//
                break;
            }

            case ItemIPAddr:
            {
//                memcpy(&ulongword, ptr, sizeof(ULONG));
                ulongword = *((PULONG) ptr);

                // Convert it to readable form
                //
                _stprintf(ItemBuf,  _T("%03d.%03d.%03d.%03d"),
                        (ulongword >>  0) & 0xff,
                        (ulongword >>  8) & 0xff,
                        (ulongword >> 16) & 0xff,
                        (ulongword >> 24) & 0xff);
                ptr += sizeof (ULONG);
                break;
            }

            case ItemPort:
            {
                _stprintf(ItemBuf, _T("%u"), NTOHS((USHORT) *ptr));
                ptr += sizeof (USHORT);
                break;
            }

            case ItemLongLong:
            {
                LONGLONG n64;
                n64 = *((LONGLONG*) ptr);
                ptr += sizeof(LONGLONG);
                _stprintf(ItemBuf, _T("%16I64d"), n64);
                break;
            }

            case ItemULongLong:
            {
                ULONGLONG n64;
                n64 = *((ULONGLONG*) ptr);
                ptr += sizeof(ULONGLONG);
                _stprintf(ItemBuf, _T("%16I64u"), n64);
                break;
            }

            case ItemString:
            case ItemRString:
            {
                USHORT pLen = strlen((CHAR*) ptr);

                if (pLen > 0)
                {
                    strcpy(str, ptr);
                    if (pItem->ItemType == ItemRString)
                    {
                        reduceA(str);
                    }
#ifdef UNICODE
                    MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, MAXSTR);
                    _stprintf(ItemBuf, _T("\"%ws\""), wstr);
#else
                    _stprintf(ItemBuf, _T("\"%s\""), str);
#endif
                }
                ptr += (pLen + 1);
                break;
            }
            case ItemRWString:
            case ItemWString:
            {
                size_t  pLen = 0;
                size_t     i;

                if (*(WCHAR *) ptr)
                {
                    if (pItem->ItemType == ItemRWString)
                    {
                        reduceW((WCHAR *) ptr);
                    }
                    pLen = ((wcslen((WCHAR*)ptr) + 1) * sizeof(WCHAR));
                    memcpy(wstr, ptr, pLen);
                    for (i = 0; i < pLen / 2; i++)
                    {
                        if (((USHORT) wstr[i] == (USHORT) 0xFFFF))
                        {
                            wstr[i] = (USHORT) 0;
                        }
                    }

                    wstr[pLen / 2] = wstr[(pLen / 2) + 1]= '\0';
                    _stprintf(ItemBuf, _T("\"%ws\""), wstr);
                }
                ptr += pLen; // + sizeof(ULONG);

                break;
            }

            case ItemDSString:   // Counted String
            {
                USHORT pLen = 256 * ((USHORT) * ptr) + ((USHORT) * (ptr + 1));
                ptr += sizeof(USHORT);
                if (pLen > 0)
                {
                    strcpy(str, ptr);
#ifdef UNICODE
                    MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, MAXSTR);
                    _stprintf(ItemBuf, _T("\"%ws\""), wstr);
#else
                    _stprintf(ItemBuf, _T("\"%s\""), str);
#endif
                }
                ptr += (pLen + 1);
                break;
            }

            case ItemPString:   // Counted String
            {
                USHORT pLen = * ((USHORT *) ptr);
                ptr += sizeof(USHORT);

                if (pLen > MAXSTR * sizeof(CHAR))
                {
                    pLen = MAXSTR * sizeof(CHAR);
                }
                if (pLen > 0)
                {
                    memcpy(str, ptr, pLen);
                    str[pLen] = '\0';
#ifdef UNICODE
                    MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, MAXSTR);
                    _stprintf(ItemBuf, _T("\"%ws\""), wstr);
#else
                    _stprintf(ItemBuf, _T("\"%s\""), str);
#endif
                }
                ptr += pLen;
                break;
            }

            case ItemDSWString:  // DS Counted Wide Strings
            case ItemPWString:  // Counted Wide Strings
            {
                USHORT pLen = ( pItem->ItemType == ItemDSWString)
                            ? (256 * ((USHORT) * ptr) + ((USHORT) * (ptr + 1)))
                            : (* ((USHORT *) ptr));

                ptr += sizeof(USHORT);
                if (pLen > MAXSTR * sizeof(WCHAR))
                {
                    pLen = MAXSTR * sizeof(WCHAR);
                }
                if (pLen > 0)
                {
                    memcpy(wstr, ptr, pLen);
                    wstr[pLen / sizeof(WCHAR)] = L'\0';
                    _stprintf(ItemBuf, _T("\"%ws\""), wstr);
                }
                ptr += pLen;
                break;
            }

            case ItemNWString:   // Non Null Terminated String
            {
               USHORT Size;

               Size = (USHORT)(pEvent->MofLength - (ULONG)(ptr - MofData));
               if( Size > MAXSTR )
               {
                   Size = MAXSTR;
               }
               if (Size > 0)
               {
                   memcpy(wstr, ptr, Size);
                   wstr[Size / 2] = '\0';
                   _stprintf(ItemBuf, _T("\"%ws\""), wstr);
               }
               ptr += Size;
               break;
            }

            case ItemMLString:  // Multi Line String
            {
                USHORT   pLen;
                char   * src, * dest;
                BOOL     inQ       = FALSE;
                BOOL     skip      = FALSE;
                UINT     lineCount = 0;

                ptr += sizeof(UCHAR) * 2;
                pLen = strlen(ptr);
                if (pLen > 0)
                {
                    src = ptr;
                    dest = str;
                    while (* src != '\0')
                    {
                        if (* src == '\n')
                        {
                            if (!lineCount)
                            {
                                * dest++ = ' ';
                            }
                            lineCount++;
                        }
                        else if (* src == '\"')
                        { 
                            if (inQ)
                            {
                                char   strCount[32];
                                char * cpy;

                                sprintf(strCount, "{%dx}", lineCount);
                                cpy = & strCount[0];
                                while (* cpy != '\0')
                                {
                                    * dest ++ = * cpy ++;
                                }
                            }
                            inQ = !inQ;
                        }
                        else if (!skip)
                        {
                            *dest++ = *src;
                        }
                        skip = (lineCount > 1 && inQ);
                        src++;
                    }
                    *dest = '\0';
#ifdef UNICODE
                    MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, MAXSTR);
                    _stprintf(ItemBuf, _T("\"%ws\""), wstr);
#else
                    _stprintf(ItemBuf, _T("\"%s\""), str);
#endif
                }
                ptr += (pLen);
                break;
            }

            case ItemSid:
            {
                TCHAR        UserName[64];
                TCHAR        Domain[64];
                TCHAR        FullName[256];
                ULONG        asize = 0;
                ULONG        bsize = 0;
                ULONG        Sid[64];
                PULONG       pSid  = & Sid[0];
                SID_NAME_USE Se;
                ULONG        nSidLength;

                pSid = (PULONG) ptr;
                if (*pSid == 0)
                {
                    ptr += 4;
                    _stprintf(ItemBuf, _T("%4d"), *pSid);
                }
                else
                {
                    ptr += 8;           // skip the TOKEN_USER structure
                    nSidLength = 8 + (4*ptr[1]);

                    asize = 64;
                    bsize = 64;
                    if (LookupAccountSid(
                                    NULL,
                                   (PSID) ptr,
                                   (LPTSTR) & UserName[0],
                                   & asize,
                                   (LPTSTR) & Domain[0],
                                   & bsize,
                                   & Se))
                    {
                        LPTSTR pFullName = &FullName[0];

                        _tcscpy(pFullName, _T("\\\\"));
                        _tcscat(pFullName, Domain);
                        _tcscat(pFullName, _T("\\"));
                        _tcscat(pFullName, UserName);
                        asize = (ULONG) _tcslen(pFullName);
                        if (asize > 0)
                        {
                            _stprintf(ItemBuf, _T("\"%s\""), pFullName);
                        }
                    }
                    else
                    {
                        _stprintf(ItemBuf, _T("\"%s\""), _T("System"));
                    }
                    SetLastError( ERROR_SUCCESS );
                    ptr += nSidLength;
                }
                break;
            }

            case ItemChar4:
                _stprintf(ItemBuf,
                          _T("%c%c%c%c"),
                          *ptr, ptr[1], ptr[2], ptr[3]);
                ptr += 4;
                break;

            default:
                ptr += sizeof (int);
            }

            if ((LONG) ((ItemsInBuf + _tcslen(ItemBuf) + 1)) < (LONG) MAXBUFS)
            {
                _stprintf(pItemBuf[iItemCount], _T("%s"), ItemBuf);
                pItemBuf[iItemCount + 1] =
                        pItemBuf[iItemCount] + _tcslen(ItemBuf) + 1;
                iItemCount ++;
                ItemsInBuf = ItemsInBuf + _tcslen(ItemBuf) + 1;
                Next       = Next->Flink;
            }
            else
            {
                SetLastError(ERROR_INVALID_DATA);
                return;
            }
        }
    }

    if (!fSummaryOnly)
    {
        if ((strFormat == NULL) || (strFormat[0] == 0))
        {
            // Build our original format
            //

            RtlZeroMemory(EventBuf, MAXBUFS * sizeof(TCHAR));

            _stprintf(EventBuf, _T("%-18s, 0x%04X,"),
                            pItemBuf[0], pHeader->ThreadId);
            _tcscat(EventBuf, pItemBuf[2]);
            _tcscat(EventBuf, _T(","));
            _tcscat(EventBuf, pItemBuf[3]);
            _tcscat(EventBuf, _T(","));

            if (!UserMode)
            {
                _tcscat(EventBuf, pItemBuf[4]);
                _tcscat(EventBuf, _T(", "));
            }

            i = 8;
            while (i < iItemCount)
            {
                _tcscat(EventBuf,pItemBuf[i++]);
                _tcscat(EventBuf,_T(", "));
            }
            _tcscat(EventBuf,pItemBuf[5]);    //Instance Id
            _tcscat(EventBuf,_T(", "));
            _tcscat(EventBuf,pItemBuf[6]);    //Parent Instance Id
        }
        else
        {
            DWORD dwResult =  FormatMessage(
                    FORMAT_MESSAGE_FROM_STRING + FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                          // source and processing options
                    (LPCVOID) strFormat, // pointer to  message source
                    0,                    // requested message identifier
                    0,                    // language identifier
                    (LPTSTR) EventBuf,    // pointer to message buffer
                    MAXBUFS,              // maximum size of message buffer
                    (CHAR**)pItemBuf);    // pointer to array of message inserts

            if (dwResult == 0)
            {
                _stprintf(EventBuf,_T("FormatMessage Failed 0x%X (%s/%s)\n"),
                            GetLastError(),
                            pItemBuf[0],
                            pItemBuf[1]);
            }
        }

        fprintf(DumpFile, "%ws\n", EventBuf);

        if (fDebugDisplay)
        {
            _tprintf(_T("%ws"), EventBuf);
        }
    }
}

ULONG
CheckFile(
    LPTSTR fileName
    )
{
    HANDLE hFile;
    ULONG Status;

    hFile = CreateFile(
                fileName,
                GENERIC_READ,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
                );
    Status = (hFile != INVALID_HANDLE_VALUE);
    CloseHandle(hFile);
    return Status;
}

PMOF_INFO
GetMofInfoHead(
    LPGUID pGuid,
    LPTSTR strType,
    LONG TypeIndex,
    LPTSTR strFormat,
    BOOL bBestMatch
    )
{
    PLIST_ENTRY Head, Next;
    PMOF_INFO pMofInfo;

    // Search the eventList for this Guid and find the head
    //

    if (EventListHead == NULL) {
        EventListHead = (PLIST_ENTRY) malloc(sizeof(LIST_ENTRY));
        InitializeListHead(EventListHead);
    }

    //
    // Traverse the list and look for the Mof info head for this Guid. 

    Head = EventListHead;
    Next = Head->Flink;
    if( bBestMatch ){
        PMOF_INFO pBestMatch = NULL;
        while (Head != Next) {
            pMofInfo = CONTAINING_RECORD(Next, MOF_INFO, Entry);
            if( IsEqualGUID(&pMofInfo->Guid, pGuid) ){
                if(pMofInfo->TypeIndex == TypeIndex){
                    return  pMofInfo;
                }
                else if(pMofInfo->strType == NULL){
                    pBestMatch = pMofInfo;
                }
            }
            Next = Next->Flink;
        } 
        if(pBestMatch != NULL)
            return pBestMatch;
    }else{
        while (Head != Next) {
            pMofInfo = CONTAINING_RECORD(Next, MOF_INFO, Entry);
            if ( (strType != NULL && pMofInfo->strType != NULL) &&
                 IsEqualGUID(&pMofInfo->Guid, pGuid) &&
                 !_tcscmp(strType, pMofInfo->strType)
                ) {
                return  pMofInfo;
            }
            else if( (strType == NULL && pMofInfo->strType == NULL) &&
                     IsEqualGUID(&pMofInfo->Guid, pGuid) ){
                return  pMofInfo;
            }
            Next = Next->Flink;
        } 
    }
    //
    // If One does not exist, create one. 
    //

    pMofInfo = (PMOF_INFO)malloc(sizeof(MOF_INFO));
    RtlZeroMemory(pMofInfo, sizeof(MOF_INFO));
    memcpy(&pMofInfo->Guid, pGuid, sizeof(GUID));
    pMofInfo->ItemHeader = (PLIST_ENTRY)malloc(sizeof(LIST_ENTRY));
    if(strType != NULL){
        pMofInfo->strType = (LPTSTR)malloc((_tcslen(strType)+1)*sizeof(TCHAR));
        _tcscpy(pMofInfo->strType,strType);
    }
    if(strFormat != NULL){
        pMofInfo->strFormat =
                (LPTSTR) malloc((_tcslen(strFormat)+1)*sizeof(TCHAR));
        _tcscpy(pMofInfo->strFormat, strFormat);
    }
    pMofInfo->TypeIndex = bBestMatch ? -1 : TypeIndex;
    InitializeListHead(pMofInfo->ItemHeader);
    InsertTailList(EventListHead, &pMofInfo->Entry);
    return pMofInfo;

}

//
// This routine is called by the WBEM interface routine for each property 
// found for this Guid. The ITEM_DESC structure is allocted for each Property.

VOID
AddMofInfo(
    const GUID *Guid,
    LPTSTR strType,
    ULONG typeIndex,
    LPTSTR strDesc,
    ITEM_TYPE ItemType,
    LPTSTR strFormat
    )
{
    PITEM_DESC pItem;
    PLIST_ENTRY pListHead;
    PMOF_INFO pMofInfo;

    if (strDesc == NULL)
        return;

    pItem = (PITEM_DESC) malloc(sizeof(ITEM_DESC));
    pItem->strDescription = (LPTSTR) malloc( (_tcslen(strDesc)+1)*sizeof(TCHAR));
    _tcscpy(pItem->strDescription, strDesc);
    pItem->ItemType = ItemType;
    pMofInfo = GetMofInfoHead( (LPGUID)Guid, strType, typeIndex, strFormat, FALSE );
    if (pMofInfo != NULL) {
        pListHead = pMofInfo->ItemHeader;
        InsertTailList(pListHead, &pItem->Entry);
    }
}

void 
AddMofFromWbem(
    LPTSTR EventGuid,
    LPTSTR PropName,
    DWORD  PropType
    )
{
    GUID Guid;
    PEVENT_TRACE pEvent = NULL;

    ULONG len = 0;

    if (!wGUIDFromString((LPTSTR)EventGuid, (LPGUID)&Guid)) {
        return;
    }

    PropType;
    AddMofInfo(&Guid, NULL, -1, PropName, MapType(PropType), NULL);
}

// *** Following routine copied from WMI\MofCheck. to convert 
// a guid string to a GUID. 
// The routines below were blantenly stolen without remorse from the ole
// sources in \nt\private\ole32\com\class\compapi.cxx. They are copied here
// so that WMI doesn't need to load in ole32 only to convert a guid string
// into its binary representation.
//

//+-------------------------------------------------------------------------
//
//  Function:   HexStringToDword   (private)
//
//  Synopsis:   scan lpsz for a number of hex digits (at most 8); update lpsz
//              return value in Value; check for chDelim;
//
//  Arguments:  [lpsz]    - the hex string to convert
//              [Value]   - the returned value
//              [cDigits] - count of digits
//
//  Returns:    TRUE for success
//
//--------------------------------------------------------------------------
BOOL HexStringToDword(LPCTSTR lpsz, DWORD * RetValue,
                             int cDigits, WCHAR chDelim)
{
    int Count;
    DWORD Value;

    Value = 0;
    for (Count = 0; Count < cDigits; Count++, lpsz++)
    {
        if (*lpsz >= '0' && *lpsz <= '9')
            Value = (Value << 4) + *lpsz - '0';
        else if (*lpsz >= 'A' && *lpsz <= 'F')
            Value = (Value << 4) + *lpsz - 'A' + 10;
        else if (*lpsz >= 'a' && *lpsz <= 'f')
            Value = (Value << 4) + *lpsz - 'a' + 10;
        else
            return(FALSE);
    }
    *RetValue = Value;

    if (chDelim != 0)
        return *lpsz++ == chDelim;
    else
        return TRUE;
}

//+-------------------------------------------------------------------------
//
//  Function:   wUUIDFromString    (internal)
//
//  Synopsis:   Parse UUID such as 00000000-0000-0000-0000-000000000000
//
//  Arguments:  [lpsz]  - Supplies the UUID string to convert
//              [pguid] - Returns the GUID.
//
//  Returns:    TRUE if successful
//
//--------------------------------------------------------------------------
BOOL wUUIDFromString(LPCTSTR lpsz, LPGUID pguid)
{
        DWORD dw;

        if (!HexStringToDword(lpsz, &pguid->Data1, sizeof(DWORD)*2, '-'))
                return FALSE;
        lpsz += sizeof(DWORD)*2 + 1;

        if (!HexStringToDword(lpsz, &dw, sizeof(WORD)*2, '-'))
                return FALSE;
        lpsz += sizeof(WORD)*2 + 1;

        pguid->Data2 = (WORD)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(WORD)*2, '-'))
                return FALSE;
        lpsz += sizeof(WORD)*2 + 1;

        pguid->Data3 = (WORD)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[0] = (BYTE)dw;
        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, '-'))
                return FALSE;
        lpsz += sizeof(BYTE)*2+1;

        pguid->Data4[1] = (BYTE)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[2] = (BYTE)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[3] = (BYTE)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[4] = (BYTE)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[5] = (BYTE)dw;

        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[6] = (BYTE)dw;
        if (!HexStringToDword(lpsz, &dw, sizeof(BYTE)*2, 0))
                return FALSE;
        lpsz += sizeof(BYTE)*2;

        pguid->Data4[7] = (BYTE)dw;

        return TRUE;
}

//+-------------------------------------------------------------------------
//
//  Function:   wGUIDFromString    (internal)
//
//  Synopsis:   Parse GUID such as {00000000-0000-0000-0000-000000000000}
//
//  Arguments:  [lpsz]  - the guid string to convert
//              [pguid] - guid to return
//
//  Returns:    TRUE if successful
//
//--------------------------------------------------------------------------
BOOL wGUIDFromString(LPCTSTR lpsz, LPGUID pguid)
{
    if (*lpsz == '{' )
        lpsz++;
    if(wUUIDFromString(lpsz, pguid) != TRUE)
        return FALSE;

    lpsz +=36;

    if (*lpsz == '}' )
        lpsz++;

    if (*lpsz != '\0')   // check for zero terminated string - test bug #18307
    {
       return FALSE;
    }

    return TRUE;
}

ITEM_TYPE 
MapType(
   IN DWORD vtTest 
    )
{
    ITEM_TYPE iRet;
    vtTest &= ~ VT_ARRAY; // get rid of possible array bit
    vtTest &= ~ VT_BYREF; // get rid of possible byref bit

    return ItemULongX;

    switch (vtTest) {
        case VT_UI1:
        case VT_LPSTR:
            iRet = ItemString;
            break;
        case VT_LPWSTR:
        case VT_BSTR:
            iRet = ItemString;
            break;
        case VT_UI2:
            iRet = ItemUShort;
            break;
        case VT_I2:
            iRet = ItemShort;
            break;
        case VT_UI4:
            iRet = ItemULongX;
            break;
        case VT_I4:
        case VT_R4:
            iRet = ItemLong;
            break;
        case VT_R8:
            iRet = ItemULongLong;
            break;
        case VT_BOOL:
            break;
        case VT_ERROR:
            break;
        case VT_CY:
            break;
        case VT_DATE:
            break;

        default:
            iRet = ItemULongX;
        }
    return iRet;
}

void
RemoveMofInfo(
    PLIST_ENTRY pMofInfo
    )
{
    PLIST_ENTRY Head, Next;
    PITEM_DESC pItem;

    Head = pMofInfo;
    Next = Head->Flink;
    while (Head != Next) {
        pItem = CONTAINING_RECORD(Next, ITEM_DESC, Entry);
        Next = Next->Flink;
        RemoveEntryList(&pItem->Entry);
        free(pItem);
    } 
}

void
CleanupEventList(
    VOID
    )
{
    PLIST_ENTRY Head, Next;
    PMOF_INFO pMofInfo;
    TCHAR s[256];
    TCHAR wstr[256];
    PTCHAR str;

    if (EventListHead == NULL) {
        return;
    }

    Head = EventListHead;
    Next = Head->Flink;
    while (Head != Next) {
        RtlZeroMemory(&wstr, 256);

        pMofInfo = CONTAINING_RECORD(Next, MOF_INFO, Entry);

        if (pMofInfo->EventCount > 0) {
            str = GuidToString(&s[0], &pMofInfo->Guid);
            MapGuidToName(&pMofInfo->Guid, 0, wstr);
            _ftprintf(SummaryFile,_T("|%10d    %-20s %-10s  %36s|\n"),
                      pMofInfo->EventCount, 
                      wstr, 
                      pMofInfo->strType ? pMofInfo->strType : _T("General"), 
                      str);
        }

        RemoveEntryList(&pMofInfo->Entry);
        RemoveMofInfo(pMofInfo->ItemHeader);
        free(pMofInfo->ItemHeader);

        if (pMofInfo->strDescription != NULL)
            free(pMofInfo->strDescription);
        if (pMofInfo->strType != NULL)
            free(pMofInfo->strType);
        if (pMofInfo->strFormat != NULL)
            free(pMofInfo->strFormat);

        Next = Next->Flink;
        free(pMofInfo);
    }

    free(EventListHead);
}

void
PrintMofInfo(
    PLIST_ENTRY pMofInfo
    )
{
    PLIST_ENTRY Head, Next;
    PITEM_DESC pItem;

    Head = pMofInfo;
    Next = Head->Flink;
    while (Head != Next) {
        pItem = CONTAINING_RECORD(Next, ITEM_DESC, Entry);
        _tprintf(_T("%s\n"), pItem->strDescription);
        Next = Next->Flink;
    }
}

void
DumpMofList()
{
    PLIST_ENTRY Head, Next;
    PMOF_INFO pMofInfo;

    if (EventListHead == NULL) {
        return;
    }

    Head = EventListHead;
    Next = Head->Flink;
    while (Head != Next) {
        pMofInfo = CONTAINING_RECORD(Next, MOF_INFO, Entry);
        Next = Next->Flink;
    }
}

PTCHAR GuidToString(
    PTCHAR s,
    LPGUID piid
    )
{
    _stprintf(s, _T("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"),
               piid->Data1, piid->Data2,
               piid->Data3,
               piid->Data4[0], piid->Data4[1],
               piid->Data4[2], piid->Data4[3],
               piid->Data4[4], piid->Data4[5],
               piid->Data4[6], piid->Data4[7]);
    return(s);
}

void
MapGuidToName(
    IN LPGUID pGuid,
    IN ULONG nType,
    OUT LPTSTR wstr
    )
{
    if (IsEqualGUID(pGuid, &EventTraceGuid)) {
        _tcscpy(wstr, GUID_TYPE_HEADER );
    }
    else if (!UserDefinedGuid(pGuid, wstr)) {
        _tcscpy(wstr, GUID_TYPE_UNKNOWN );
    }
}

ULONG
UserDefinedGuid(
    IN LPGUID pGuid,
    OUT LPTSTR wstr
    )
{
    PLIST_ENTRY Head, Next;
    PMOF_INFO pMofInfo;

    // Search the eventList for this Guid and find the head
    //

    if (EventListHead == NULL) {
        EventListHead = (PLIST_ENTRY) malloc(sizeof(LIST_ENTRY));
        InitializeListHead(EventListHead);
        return FALSE;
    }

    //
    // Traverse the list and look for the Mof info head for this Guid.

    Head = EventListHead;
    Next = Head->Flink;

    while (Head  != Next) {
        pMofInfo = CONTAINING_RECORD(Next, MOF_INFO, Entry);
        if (IsEqualGUID(&pMofInfo->Guid, pGuid)) {
            if (pMofInfo->strDescription == NULL) 
                return FALSE;
            else 
                _tcscpy(wstr, pMofInfo->strDescription);
            return TRUE;
        }
        Next = Next->Flink;
    } 

    return FALSE;
}

ULONG
GetGuids(LPTSTR GuidFile, LPGUID *GuidArray)
{
    FILE *f;
    TCHAR line[MAXSTR], arg[MAXSTR];
    TCHAR strGuid[MAXSTR];
    PMOF_TYPE types;
    LPGUID Guid;
    UINT i, n;
    TCHAR *name, *s, *guidName;
    PMOF_INFO pMofInfo;
    size_t len = 0;
    UINT typeCount = 0;
    BOOL inInfo = FALSE;

    types = (PMOF_TYPE) malloc(MAXTYPE * sizeof(MOF_TYPE));
    if (types == NULL) {
        return 0;
    }

    RtlZeroMemory(types,   MAXTYPE * sizeof(MOF_TYPE));
    RtlZeroMemory(line,    MAXSTR * sizeof(TCHAR));
    RtlZeroMemory(strGuid, MAXSTR * sizeof(TCHAR));

    f = _tfopen( GuidFile, _T("r"));
    if (f == NULL)
    {
        free(types);
        return 0;
    }

    n = 0;
    while ( _fgetts(line, MAXSTR, f) != NULL ) {
        if(line[0] == '/'){
            continue;
        }
        if(line[0] == '{'){
            inInfo = TRUE;
        } 
        else if ( line[0] == '}'){
            typeCount = 0;
            inInfo = FALSE;
        }
        else if( inInfo ){
            ITEM_TYPE type;
            name = _tcstok(line,_T("\n\t,"));
            s = _tcstok( NULL, _T(" \n\t,"));
            if(s != NULL && name != NULL ){
                if(!_tcsicmp(s,STR_ItemChar)) type = ItemChar;
                else if(!_tcsicmp(s,STR_ItemUChar)) type = ItemUChar;
                else if(!_tcsicmp(s,STR_ItemCharShort))type = ItemCharShort;
                else if(!_tcsicmp(s,STR_ItemCharSign)) type = ItemCharSign;
                else if(!_tcsicmp(s,STR_ItemShort)) type = ItemShort;
                else if(!_tcsicmp(s,STR_ItemUShort)) type = ItemUShort;
                else if(!_tcsicmp(s,STR_ItemLong)) type = ItemLong;
                else if(!_tcsicmp(s,STR_ItemULong)) type = ItemULong;
                else if(!_tcsicmp(s,STR_ItemULongX)) type = ItemULongX;
                else if(!_tcsicmp(s,STR_ItemLongLong)) type = ItemLongLong;
                else if(!_tcsicmp(s,STR_ItemULongLong)) type = ItemULongLong;
                else if(!_tcsicmp(s,STR_ItemString)) type = ItemString;
                else if(!_tcsicmp(s,STR_ItemWString)) type = ItemWString;
                else if(!_tcsicmp(s,STR_ItemRString)) type = ItemRString;
                else if(!_tcsicmp(s,STR_ItemRWString)) type = ItemRWString;
                else if(!_tcsicmp(s,STR_ItemPString)) type = ItemPString;
                else if(!_tcsicmp(s,STR_ItemMLString)) type = ItemMLString;
                else if(!_tcsicmp(s,STR_ItemNWString)) type = ItemNWString;
                else if(!_tcsicmp(s,STR_ItemPWString)) type = ItemPWString;
                else if(!_tcsicmp(s,STR_ItemDSString)) type = ItemDSString;
                else if(!_tcsicmp(s,STR_ItemDSWString)) type = ItemDSWString;
                else if(!_tcsicmp(s,STR_ItemSid)) type = ItemSid;
                else if(!_tcsicmp(s,STR_ItemChar4)) type = ItemChar4;
                else if(!_tcsicmp(s,STR_ItemIPAddr)) type = ItemIPAddr;
                else if(!_tcsicmp(s,STR_ItemPort)) type = ItemPort;
                else if(!_tcsicmp(s,STR_ItemPtr)) type = ItemPtr;
                else type = ItemUnknown;
                if(typeCount == 0){
                    AddMofInfo(Guid, NULL, -1, name, type, NULL);
                }else{
                    for(i=0;i<typeCount;i++){
                        AddMofInfo(Guid, types[i].strType, types[i].TypeIndex, name, type, types[i].strFormat);                        
                    }
                }
            }
        } 
        else if( line[0] == '#'){
            TCHAR *token, * etoken;

            _tcstok(line,_T(" \t"));
            _tcscpy(types[typeCount].strType,_tcstok( NULL, _T(" \t\n")));
            types[typeCount].TypeIndex = _ttoi(_tcstok( NULL, _T("\"\n,")));

            token  = _tcstok(NULL, _T("\n"));
            etoken = NULL;
            if (token != NULL)
            {
                etoken = _tcsrchr(token, _T('\"'));
            }
            if (etoken != NULL)
            {
                etoken[0] = 0;
            }
            else
            {
                token = NULL;
            }
            if (token != NULL)
            {
                _tcscpy(types[typeCount].strFormat, token);
            }
            else
            {
                types[typeCount].strFormat[0] = types[typeCount].strFormat[1]
                                              = 0;
            }

            if (   types[typeCount].strFormat[0] == 0
                && types[typeCount].strFormat[1] == 0)
            {
                pMofInfo = GetMofInfoHead(
                                Guid,
                                types[typeCount].strType,
                                types[typeCount].TypeIndex,
                                NULL,
                                FALSE);
            }
            else
            {
                pMofInfo = GetMofInfoHead(
                                Guid,
                                types[typeCount].strType,
                                types[typeCount].TypeIndex,
                                types[typeCount].strFormat,
                                FALSE);
            }
            if (_tcslen(strGuid) != 0)
            {
                pMofInfo->strDescription =
                        malloc((_tcslen(strGuid)+1) * sizeof(TCHAR));
                _tcscpy(pMofInfo->strDescription, strGuid);
            }

            typeCount++;
            if(typeCount >= MAXTYPE){
                _ftprintf(stderr,_T("TO MANY TYPES DEFINED IN GUID FILE"));
                fclose(f);
                free(types);
                exit(1);
            }
        }
        else if (   (line[0] >= '0' && line[0] <= '9')
                 || (line[0] >= 'a' && line[0] <= 'f')
                 || (line[0] >= 'A' && line[0] <= 'F')) {
            typeCount = 0;
            Guid = (LPGUID) GuidArray[n++];
            _tcsncpy(arg, line, 8);
            arg[8] = 0;
            Guid->Data1 = ahextoi(&arg[0]);
            _tcsncpy(arg, &line[9], 4);
            arg[4] = 0;
            Guid->Data2 = (USHORT) ahextoi(&arg[0]);
            _tcsncpy(arg, &line[14], 4);
            arg[4] = 0;
            Guid->Data3 = (USHORT) ahextoi(arg);
            
            for (i=0; i<2; i++) {
                _tcsncpy(arg, &line[19 + (i*2)], 2);
                arg[2] = 0;
                Guid->Data4[i] = (UCHAR) ahextoi(arg);
            }
            for (i=2; i<8; i++) {
                _tcsncpy(arg, &line[20 + (i*2)], 2);
                arg[2] = 0;
                Guid->Data4[i] = (UCHAR) ahextoi(arg);
            }
            
        //
        // Find the next non whitespace character 
        //
    
            guidName = &line[36];

            while (*guidName == ' '|| *guidName == '\t') guidName++;
            len = _tcslen(guidName);
            s = guidName;
            
            while (--len >= 0) {
                if (*s == '\n' || *s == '\0' || *s == '\t') {
                    *s = '\0';
                    break;
                }
                s++;
            }

            pMofInfo = GetMofInfoHead(Guid, NULL, -1, NULL, FALSE );

            _tcscpy(strGuid, guidName);
            pMofInfo->strDescription =
                    malloc((_tcslen(guidName)+1) * sizeof(TCHAR));
            _tcscpy(pMofInfo->strDescription, guidName);            
        }

        RtlZeroMemory(line,     MAXSTR * sizeof(TCHAR));
    }
    fclose(f);
    free(types);
    return (ULONG)n;
}

ULONG ahextoi( TCHAR *s)
{
    long len;
    ULONG num, base, hex;

    if (s == NULL)
        return 0;
    if (*s == 0)
        return 0;
    len = (long) _tcslen(s); // we expect all strings to be less than MAXSTR
    if (len == 0)
        return 0;
    hex = 0; base = 1; num = 0;
    while (--len >= 0) {
        if ( (s[len] == 'x' || s[len] == 'X') &&
             (s[len-1] == '0') )
            break;
        if (s[len] >= '0' && s[len] <= '9')
            num = s[len] - '0';
        else if (s[len] >= 'a' && s[len] <= 'f')
            num = (s[len] - 'a') + 10;
        else if (s[len] >= 'A' && s[len] <= 'F')
            num = (s[len] - 'A') + 10;
        else
            continue;

        hex += num * base;
        base = base * 16;
    }
    return hex;
}

#ifdef __cplusplus
}
#endif 
