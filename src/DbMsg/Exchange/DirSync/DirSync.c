// --dirsync.c------------------------------------------------------------------
//
//  This file contains sample code showing how to do directory synchronization 
//  using DAPI.  It implements both the INBOUND and OUTBOUND direction.
//  I.E. importing an external mail system or other software system to the 
//  Exchange directory, and exporting the Exchange directory to an external 
//  mail system or other software system.
//
//  It compiles to an executable file which is run from the command line.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dirsync.h"
#include "dsynmsg.h"
#include "dirsync.chk"

//
// Bit Values and Defined Constants
//

// Direction of data flow

#define DIRECTION_EXPORT        0x00000001
#define DIRECTION_IMPORT        0x00000002

// Source of settings

#define SOURCE_COMMAND_LINE 0   // from command line only (no registry involved)
#define SOURCE_INSTANCE     1   // from named instance using <Instance>
#define SOURCE_KEY          2   // from registry key using /KEY=<Key>

// Number of elements by which to grow the imported object list 
// when it runs out of space.

#define IMPORTED_OBJECT_LIST_GROWTH_SIZE 1000

//
// Names of Command Line Arguments
//

#define ARG_PROGRAM_NAME        "DIRSYNC"
#define ARG_EXPORT              "EXPORT"
#define ARG_IMPORT              "IMPORT"
#define ARG_BOTH                "BOTH"
#define ARG_DSA                 "DSA"
#define ARG_BASEPOINT           "BASEPOINT"
#define ARG_CONTAINER           "CONTAINER"
#define ARG_SERVER              "SERVER"
#define ARG_HOMESERVER          "HOMESERVER"
#define ARG_EXPLIST             "EXPLIST"
#define ARG_EXPFILE             "EXPFILE"
#define ARG_IMPFILE             "IMPFILE"
#define ARG_OBJCLASS            "OBJCLASS"
#define ARG_MVAPPEND            "MVAPPEND"
#define ARG_NOMVAPPEND          "NOMVAPPEND"
#define ARG_EXPFULL             "EXPFULL"
#define ARG_NOEXPFULL           "NOEXPFULL"
#define ARG_IMPFULL             "IMPFULL"
#define ARG_NOIMPFULL           "NOIMPFULL"
#define ARG_PROGRESS            "PROGRESS"
#define ARG_NOPROGRESS          "NOPROGRESS"
#define ARG_SUBS                "SUBS"
#define ARG_NOSUBS              "NOSUBS"
#define ARG_NTCREATE            "NTCREATE"
#define ARG_NONTCREATE          "NONTCREATE"
#define ARG_NTDELETE            "NTDELETE"
#define ARG_NONTDELETE          "NONTDELETE"
#define ARG_USN                 "USN"
#define ARG_HELP1               "?"
#define ARG_HELP2               "HELP"
#define ARG_SET                 "SET"
#define ARG_DISPLAY             "DISPLAY"
#define ARG_KEY                 "KEY"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
    ARG_EXPORT,
    ARG_IMPORT,
    ARG_BOTH,
    ARG_DSA,
    ARG_BASEPOINT,
    ARG_CONTAINER,
    ARG_SERVER,
    ARG_HOMESERVER,
    ARG_EXPLIST,
    ARG_EXPFILE,
    ARG_IMPFILE,
    ARG_OBJCLASS,
    ARG_MVAPPEND,
    ARG_NOMVAPPEND,
    ARG_EXPFULL,
    ARG_NOEXPFULL,
    ARG_IMPFULL,
    ARG_NOIMPFULL,
    ARG_PROGRESS,
    ARG_NOPROGRESS,
    ARG_SUBS, 
    ARG_NOSUBS, 
    ARG_NTCREATE, 
    ARG_NONTCREATE, 
    ARG_NTDELETE, 
    ARG_NONTDELETE, 
    ARG_USN,
    ARG_HELP1,
    ARG_HELP2,
    ARG_SET,
    ARG_DISPLAY,
    ARG_KEY,
};

static char * rgpszObjClassValues[] = {
    OBJECT_CLASS_REMOTE,
    OBJECT_CLASS_MAILBOX,
};

//
// Command Line Parameters Also Stored In The Registry
//

// (Note: BOOL's in this category have been changed to DWORD's so
// they can be more easily read from or written to the registry.)

static DWORD    dwDirection                         = 0;
static TCHAR    szDSA           [MAX_PATH+1]        = {0};
static TCHAR    szBasePoint     [MAX_PATH+1]        = {0};
static TCHAR    szContainer     [MAX_PATH+1]        = {0};
static TCHAR    szServer        [MAX_PATH+1]        = {0};
static TCHAR    szHomeServer    [MAX_PATH+1]        = {0};
static TCHAR    szExportList    [2048]              = {0};
static TCHAR    szExportFile    [MAX_PATH+1]        = {0};
static TCHAR    szImportFile    [MAX_PATH+1]        = {0};
static TCHAR    szObjClass      [MAX_PATH+1]        = OBJECT_CLASS_REMOTE;
static DWORD    fFullExport                         = FALSE;
static DWORD    fFullImport                         = FALSE;
static DWORD    fProgressDialog                     = FALSE;
static DWORD    fSubs                               = FALSE;
static DWORD    fNTCreate                           = FALSE;
static DWORD    fNTDelete                           = FALSE;
static DWORD    fMVAppend                           = FALSE;
static DWORD    dwLastUSN                           = 0;

//
// Command Line Parameters Not Stored In The Registry
//

static BOOL     fHelp                               = FALSE;
static BOOL     fSet                                = FALSE;
static BOOL     fDisplay                            = FALSE;
static TCHAR    szKey           [MAX_PATH+1]        = {0};
static TCHAR    szKeyState      [MAX_PATH+1]        = {0};
static TCHAR    szInstanceName  [MAX_PATH+1]        = {0};

static LPDWORD  rgdwImportedObjectList              = NULL;
static DWORD    cdwImportedObjectList               = 0;
static DWORD    cdwMaxImportedObjectList            = 0;

//
// Other Variables Local to the File
//

static BOOL     fRespondedToUser                    = FALSE;

static DWORD    dwSettingsSource                    = SOURCE_COMMAND_LINE;
static TCHAR    szSourceStamp   [MAX_PATH+1]        = {0};
static HANDLE   hKey                                = NULL;
static HANDLE   hKeyState                           = NULL;

static LONG     iUSNCreatedAttribute                = -1;
static LONG     iUSNChangedAttribute                = -1;
static LONG     iIsDeletedAttribute                 = -1;
static LONG     iObjDistNameAttribute               = -1;
static LONG     iImportedFromAttribute              = -1;
static DIR_SYNC_ATTRIBUTE_INFO * rgdsAttributes     = NULL;
static DWORD    cdsAttributes                       = 0;

static DWORD    dwStartingUSN                       = 0;

static BOOL     fErrorInCallback                    = FALSE;
static DWORD    cDAPILoggedErrors                   = 0;

static DWORD    cObjectsImported                    = 0;
static DWORD    cObjectsExported                    = 0;

//
// Structures Used For Reading/Writing Registry Data
//

REG_VARIABLE rgrvInstanceData[] = {
    TEXT("Type"),               REG_DWORD,  sizeof(dwDirection),        &dwDirection, 
    TEXT("DSA"),                REG_SZ,     sizeof(szDSA),              szDSA, 
    TEXT("Basepoint"),          REG_SZ,     sizeof(szBasePoint),        szBasePoint, 
    TEXT("Container"),          REG_SZ,     sizeof(szContainer),        szContainer, 
    TEXT("Server"),             REG_SZ,     sizeof(szServer),           szServer, 
    TEXT("Home Server"),        REG_SZ,     sizeof(szHomeServer),       szHomeServer, 
    TEXT("Export List"),        REG_SZ,     sizeof(szExportList),       szExportList, 
    TEXT("Export File"),        REG_SZ,     sizeof(szExportFile),       szExportFile, 
    TEXT("Import File"),        REG_SZ,     sizeof(szImportFile),       szImportFile, 
    TEXT("Object Class"),       REG_SZ,     sizeof(szObjClass),         szObjClass, 
    TEXT("Full Export"),        REG_DWORD,  sizeof(fFullExport),        &fFullExport, 
    TEXT("Full Import"),        REG_DWORD,  sizeof(fFullImport),        &fFullImport, 
    TEXT("Progress Dialog"),    REG_DWORD,  sizeof(fProgressDialog),    &fProgressDialog, 
    TEXT("Sub-containers"),     REG_DWORD,  sizeof(fSubs),              &fSubs, 
    TEXT("NT Create"),          REG_DWORD,  sizeof(fNTCreate),          &fNTCreate, 
    TEXT("NT Delete"),          REG_DWORD,  sizeof(fNTDelete),          &fNTDelete, 
    TEXT("MV Append"),          REG_DWORD,  sizeof(fMVAppend),          &fMVAppend, 
};

REG_VARIABLE rgrvStateData[] = {
    // Note: Imported Object List must be the first element in this array.
    TEXT("Imported Object List"),   REG_BINARY,     0,                  NULL, 
    TEXT("Last USN"),           REG_DWORD,  sizeof(dwLastUSN),          &dwLastUSN, 
};

//
// Function Declarations
//

static HRESULT HrPreParseCommandLine(
    IN int argc,
    IN char *argv[]);

static VOID PrintUsage(void);

static VOID PrintHelp(void);

static VOID PrintSettings(void);

static HRESULT HrOpenRegistryKeys(void);

static BOOL fAskCreateInstance(void);

static HRESULT HrReadRegistryData(void);

static HRESULT HrParseCommandLine(
    IN int argc,
    IN char *argv[]);

static HRESULT HrWriteInstanceData(void);

static HRESULT HrWriteStateData(void);

static HRESULT HrCheckInfoCompleteness(void);

static HRESULT HrDoExport(void);

static DAPI_FNExportEntry fExportCallback;

static HRESULT HrProcessExportHeader(
    IN PDAPI_ENTRY pEntry);

static HRESULT HrProcessExportEntry(
    IN PDAPI_ENTRY pEntry);

static int __cdecl nDWORDCompare(
    const void * pdw1,
    const void * pdw2);

static BOOL fFindAttributeInList(
    IN LPTSTR pszAttributeName,
    IN LPTSTR pszAttributeList,
    OUT LPTSTR * ppszMatch);

static VOID CleanupAttributeList(
    IN OUT LPTSTR pszAttributeList);

static HRESULT HrDoImport(void);

static HRESULT HrReadRegistryVariables(
    IN      HANDLE          hRegistryKey,
    IN      LPTSTR          pszRegistryKey,
    IN      DWORD           cVariables,
    IN OUT  LPREG_VARIABLE  rgrvVariables);

static HRESULT HrWriteRegistryVariables(
    IN      HANDLE          hRegistryKey,
    IN      LPTSTR          pszRegistryKey,
    IN      DWORD           cVariables,
    IN OUT  LPREG_VARIABLE  rgrvVariables);

static VOID PrintResults(
    IN  HRESULT     hr,
    IN  BOOL        fEventLogOpen);

//
// Functions
//

//$--main-----------------------------------------------------------------------
//  Main function that performs directory synchronization.
// -----------------------------------------------------------------------------
int main(                                   // RETURNS: exit code
    IN int argc,                            // number of args on command line
    IN char *argv[])                        // array of command line arguments
{
    HRESULT             hr                  = NOERROR;
    BOOL                fEventLogOpen       = FALSE;
    BOOL                fMAPIInitialized    = FALSE;
    MAPIINIT_0          MapiInit            = {0};

    DEBUGPUBLIC("main()\n");

    // Check parameters.

    hr = CHK_main(argc, argv);
    if (FAILED(hr))
        return _nEcFromHr(hr);

    printf( "\n" );

    // If there are no command line arguments then print the usage message 
    // and exit.

    if (argc < 2)
    {
        PrintUsage();
        goto cleanup;
    }

    // Do preliminary parsing of the command line.

    hr = HrPreParseCommandLine(argc, argv);
    if (FAILED(hr))
        goto cleanup;

    // If they requested help, then print a help message and exit.

    if (fHelp)
    {
        PrintHelp();
        goto cleanup;
    }

    // Initialize event logging.

    hr = HrEventOpenLog(
        TEXT("EDK DirSync"), NULL, NULL, NULL, NULL, NULL);

    if (SUCCEEDED(hr))
    {
        fEventLogOpen = TRUE;
    }
    hr = NOERROR;

    // Initialize MAPI (for memory allocation).

    MapiInit.ulVersion = MAPI_INIT_VERSION;

    hr = MAPIInitialize(&MapiInit);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_CANNOT_INIT_MAPI, 
            0, 
            0);
        goto cleanup;
    }
    fMAPIInitialized = TRUE;

    // If we are using the registry, then open or create (depending on the 
    // /SET flag) the registry keys where the parameters and state information 
    // are kept.  Then, read the parameters and state information from the 
    // registry.

    if (dwSettingsSource != SOURCE_COMMAND_LINE)
    {
        hr = HrOpenRegistryKeys();
        if (FAILED(hr))
            goto cleanup;

        hr = HrReadRegistryData();
        if (FAILED(hr))
            goto cleanup;
    }

    // Parse the command line arguments.

    hr = HrParseCommandLine(argc, argv);
    if (FAILED(hr))
        goto cleanup;

    // If they specified the /SET flag or requested creation of a new instance 
    // or key, then write the (possibly changed) values back to the registry 
    // but don't do any actual directory synchronization.

    if (fSet)
    {
        hr = HrWriteInstanceData();
        if (FAILED(hr))
            goto cleanup;

        hr = HrWriteStateData();
        if (FAILED(hr))
            goto cleanup;
    }

    // If they requested to display current settings then do it and then quit.

    if (fDisplay)
    {
        PrintSettings();
        goto cleanup;
    }

    // If we are not creating a new instance or key then do the actual 
    // directory synchronization.

    if (!fSet)
    {
        // Make sure we have all the information we need to do directory 
        // synchronization.

        hr = HrCheckInfoCompleteness();
        if (FAILED(hr))
            goto cleanup;

        // Create the source stamp.

        STRNCPY(szSourceStamp, TEXT("EDKDirSync:"));
        STRNCAT(szSourceStamp, szInstanceName);

        // Do import

        if (dwDirection & DIRECTION_IMPORT)
        {
            hr = HrDoImport();
            if (FAILED(hr))
                goto cleanup;

            if (cObjectsImported == 1)
            {
                fprintf(stderr, "1 object imported to server %s.\n", 
                    szDSA);
                fRespondedToUser = TRUE;
            }
            else
            {
                fprintf(stderr, "%d objects imported to server %s.\n", 
                    cObjectsImported, szDSA);
                fRespondedToUser = TRUE;
            }
        }

        // Do export

        if (dwDirection & DIRECTION_EXPORT)
        {
            hr = HrDoExport();
            if (FAILED(hr))
                goto cleanup;

            if (cObjectsExported == 1)
            {
                fprintf(stderr, "1 object exported from server %s.\n", 
                    szDSA);
                fRespondedToUser = TRUE;
            }
            else
            {
                fprintf(stderr, "%d objects exported from server %s.\n", 
                    cObjectsExported, szDSA);
                fRespondedToUser = TRUE;
            }
        }
    }

cleanup:
    // Print the results of the operation.

    PrintResults(hr, fEventLogOpen);

    // Close the registry.

    if (hKeyState)
    {
        RegFlushKey(hKeyState);
        CloseHandle(hKeyState);
    }

    if (hKey)
    {
        RegFlushKey(hKey);
        CloseHandle(hKey);
    }

    // Close event logging.

    if (fEventLogOpen)
    {
        (void) HrEventCloseLog();
    }

    // De-Initialize MAPI.

    if (fMAPIInitialized)
    {
        MAPIUninitialize();
        fMAPIInitialized = FALSE;
    }

    return(_nEcFromHr(hr));
}



//$--HrPreParseCommandLine------------------------------------------------------
//  Does preliminary parsing of the command line that is needed to decide how 
//  (and whether) to read data from the registry key before parsing the command 
//  line for real.  It looks for the following:
//
//  /? (Help)               If present, just print a help message and no other 
//                          processing takes place.
//
//  /DISPLAY                If present then display the current values of 
//                          data in the registry.
//
//  <Instance Name>         Used to construct a registry key name where 
//                          parameters should be stored.
//
//  /KEY=<Registry Key>     Used to specify an absolute registry key location 
//                          instead of using <Instance Name>.
//
//  /SET                    Indicates that we should create a new instance in 
//                          the registry but NOT do any actual directory 
//                          synchronization.
//
//  Note: if neither /KEY= nor <Instance Name> is specified, then we do not 
//  use the registry and all data must come from the command line.
// -----------------------------------------------------------------------------
static HRESULT HrPreParseCommandLine(       // RETURNS: HRESULT
    IN int argc,                            // number of args on command line
    IN char *argv[])                        // array of command line arguments
{
    HRESULT             hr                  = NOERROR;
    HRESULT             hrT                 = NOERROR;
    int                 i                   = 0;
    char *              pszArgument         = NULL;
    char *              pszValue            = NULL;

    DEBUGPRIVATE("HrPreParseCommandLine()\n");

    // Check parameters.

    hr = CHK_main(argc, argv);
    if (FAILED(hr))
        RETURN(hr);

    // Do an initial check for /? or /HELP or /DISPLAY.
    // If found, don't do any other parsing.

    for (i = 1; i < argc; i++)
    {
        hrT = _HrExpandCommandLineArgument(
            argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
            &pszArgument, &pszValue);

        if (SUCCEEDED(hrT) && pszArgument && 
            (!_stricmp(pszArgument,ARG_HELP1) || 
             !_stricmp(pszArgument,ARG_HELP2)))
        {
            fHelp = TRUE;
            goto cleanup;
        }
    }

    // Search the command line arguments for /KEY=<Registry Key> or 
    // <Instance Name>.  Use whichever we find first to build a registry 
    // key name.

    for (i = 1; i < argc; i++)
    {
        hrT = _HrExpandCommandLineArgument(
            argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
            &pszArgument, &pszValue);

        if (FAILED(hrT))
        {
            hr = hrT;
            if (hr == EDK_E_NOT_FOUND)
            {
                fprintf(stderr, "ERROR: unknown command line flag: %s\n", 
                    argv[i]);
                fRespondedToUser = TRUE;
                continue;
            }
            else
            {
                fprintf(stderr, "ERROR: ambiguous command line flag: %s\n", 
                    argv[i]);
                fRespondedToUser = TRUE;
                goto cleanup;
            }
        }

        // Check for <Instance Name>

        if (pszArgument == NULL && pszValue != NULL)
        {
            // Make sure this isn't a duplicate parameter.

            if (dwSettingsSource != SOURCE_COMMAND_LINE)
            {
                fprintf(stderr, "ERROR: duplicate instance name or /%s: %s\n", 
                    ARG_KEY, argv[i]);
                fRespondedToUser = TRUE;
                hr = HR_LOG(E_FAIL);
            }

            // Create registry key name and state key name.

            STRNCPY(szInstanceName, argv[i]);

            STRNCPY(szKey, 
                "HKEY_LOCAL_MACHINE\\SOFTWARE\\MS Exchange SDK Samples\\DirSync\\");
            STRNCAT(szKey, szInstanceName);

            STRNCPY(szKeyState, szKey);
            STRNCAT(szKeyState, TEXT("\\State"));

            dwSettingsSource = SOURCE_INSTANCE;
        }

        // Check for /KEY=<Registry Key>

        else if (pszArgument && !_stricmp(pszArgument,ARG_KEY))
        {
            // Make sure they gave a value.

            if (pszValue == NULL)
            {
                fprintf(stderr, "ERROR: flag /%s requires a value\n", 
                    pszArgument);
                fRespondedToUser = TRUE;
                hr = HR_LOG(E_FAIL);
            }

            // Make sure this isn't a duplicate parameter.

            if (dwSettingsSource != SOURCE_COMMAND_LINE)
            {
                fprintf(stderr, "ERROR: duplicate instance name or /%s: %s\n", 
                    ARG_KEY, argv[i]);
                fRespondedToUser = TRUE;
                hr = HR_LOG(E_FAIL);
            }

            // Get registry key name.

            if (SUCCEEDED(hr))
            {
                STRNCPY(szKey, pszValue);

                STRNCPY(szKeyState, szKey);
                STRNCAT(szKeyState, TEXT("\\State"));

                dwSettingsSource = SOURCE_KEY;
            }
        }

        // Check for /SET (create a new instance)

        else if (pszArgument && 
            (!_stricmp(pszArgument,ARG_SET)))
        {
            fSet = TRUE;
        }

        // Check for /DISPLAY (display settings)

        else if (pszArgument && !_stricmp(pszArgument,ARG_DISPLAY))
        {
            fDisplay = TRUE;
        }
    }

    // If they use /SET then they must specify an instance name or use /KEY.
    // Otherwise, it's an error.

    if (SUCCEEDED(hr) && fSet && dwSettingsSource == SOURCE_COMMAND_LINE)
    {
        fprintf(stderr, "ERROR: /%s requires instance name or /%s\n", 
            ARG_SET, ARG_KEY);
        fRespondedToUser = TRUE;
        hr = HR_LOG(E_FAIL);
    }

cleanup:
    RETURN(hr);
}



//$--PrintUsage-----------------------------------------------------------------
//  Print information about how to use this program.
// -----------------------------------------------------------------------------
static VOID PrintUsage(void)                // RETURNS: nothing
{
    DEBUGPRIVATE("PrintUsage()\n");

    printf("USAGE: %s Instance [Flags]\n\n", ARG_PROGRAM_NAME);
    printf("  Instance       %s instance name\n", ARG_PROGRAM_NAME);
    printf("  [Flags]        Enter %s /%s for details\n", ARG_PROGRAM_NAME, 
        ARG_HELP1);
    fRespondedToUser = TRUE;
}



//$--PrintHelp------------------------------------------------------------------
//  Print information about the flags.
// -----------------------------------------------------------------------------
static VOID PrintHelp(void)                 // RETURNS: nothing
{
    DEBUGPRIVATE("PrintHelp()\n");

    printf("Directory Synchronization sample.\n\n");
    printf("USAGE: %s Instance [Flags]\n\n", ARG_PROGRAM_NAME);
    printf("  Instance       %s instance name\n", ARG_PROGRAM_NAME);
    printf("  General Flags\n");
    printf("  /BASEPOINT=    DN of Directory basepoint object\n");
    printf("  /BOTH          Perform both import and export operations\n");
    printf("  /CONTAINER=    RDN of Directory container beneath BASEPOINT\n");
    printf("  /DISPLAY       Display current settings\n");
    printf("  /DSA=          Directory Service Agent name\n");
    printf("  /HELP or /?    Display help screen\n");
    printf("  /KEY=          Override default registry key\n");
    printf("  /SET           Create or update DirSync instance and registry value\n");
    printf("  /[NO]PROGRESS  Display progress dialog\n");
    printf("  /USN=          Universal Sequence Number filter\n");
    printf("  Export Flags\n");
    printf("  /EXPLIST=      Attribute list for Export\n");
    printf("  /EXPFILE=      Export data file\n");
    printf("  /[NO]EXPFULL   Perform full export (no USN filter)\n");
    printf("  /EXPORT        Perform export operation\n");
    printf("  /SERVER=       Exchange server name\n");
    printf("  /[NO]SUBS      Export contents of sub-containers\n");
    printf("  Import Flags\n");
    printf("  /IMPFILE=      Import data file\n");
//  printf("  /[NO]IMPFULL   Perform full import (replace entire container)\n");
    printf("  /IMPORT        Perform import operation\n");
    printf("  /[NO]NTCREATE  Create NT accounts for added/modified mailboxes\n");
    printf("  /[NO]NTDELETE  Delete NT accounts for deleted mailboxes\n");
    printf("  /OBJCLASS=     Type of imported objects to create (%s or %s)\n", 
        OBJECT_CLASS_MAILBOX, OBJECT_CLASS_REMOTE);
    printf("  /HOMESERVER=   Default home server for created mailboxes\n");
    printf("  /[NO]MVAPPEND  Append multivalued properties\n\n");
    printf("%s uses the NT registry key HKEY_LOCAL_MACHINE\\SOFTWARE\\\n", 
        ARG_PROGRAM_NAME);
    printf("MS Exchange SDK Samples\\DirSync\\<Instance> for configuration "
        "information.\n");
    fRespondedToUser = TRUE;
}



//$--PrintSettings--------------------------------------------------------------
//  Print the current settings.
// -----------------------------------------------------------------------------
static VOID PrintSettings(void)             // RETURNS: nothing
{
    DWORD iObjectUSN = 0;

    DEBUGPRIVATE("PrintSettings()\n");

    switch (dwSettingsSource)
    {
        case SOURCE_COMMAND_LINE:
            printf("Current settings from command line:\n\n");
            break;

        case SOURCE_INSTANCE:
            printf("Current settings for instance \"%s\":\n\n", szInstanceName);
            break;

        case SOURCE_KEY:
            printf("Current settings for registry key \"%s\":\n\n", szKey);
            break;

        default:
            printf("Current settings:\n\n");
            break;
    }

    printf("  Type                 = ");
    switch (dwDirection)
    {
        case DIRECTION_IMPORT:
            printf("Import\n");
            break;

        case DIRECTION_EXPORT:
            printf("Export\n");
            break;

        case DIRECTION_IMPORT | DIRECTION_EXPORT:
            printf("Import & Export\n");
            break;

        default:
            printf("Unknown\n");
            break;
    }

    printf("  DSA                  = %s\n", szDSA);
    printf("  Base Point           = %s\n", szBasePoint);
    printf("  Object Class         = %s\n", szObjClass);
    printf("  Container            = %s\n", szContainer);
    printf("  Server               = %s\n", szServer);
    printf("  Home Server          = %s\n", szHomeServer);
    printf("  Export List          = %s\n", szExportList);
    printf("  Export File          = %s\n", szExportFile);
    printf("  Import File          = %s\n", szImportFile);
    printf("  Full Export          = %s\n", fFullExport ? "Yes" : "No");
//  printf("  Full Import          = %s\n", fFullImport ? "Yes" : "No");
    printf("  Progress Dialog      = %s\n", fProgressDialog ? "Yes" : "No");
    printf("  NT Create            = %s\n", fNTCreate ? "Yes" : "No");
    printf("  NT Delete            = %s\n", fNTDelete ? "Yes" : "No");
    printf("  Sub-containers       = %s\n", fSubs ? "Yes" : "No");
    printf("  Multi-Value Append   = %s\n", fMVAppend ? "Yes" : "No");
    printf("  Last USN             = %d\n", dwLastUSN);

    printf("  Imported Object List = ");
    for (iObjectUSN = 0; iObjectUSN < cdwImportedObjectList; iObjectUSN++)
    {
        printf("%d", rgdwImportedObjectList[iObjectUSN]);
        if (iObjectUSN < (cdwImportedObjectList - 1))
            printf(", ");
    }
    printf("\n");

    fRespondedToUser = TRUE;
}



//$--HrOpenRegistryKeys---------------------------------------------------------
//  Open or create (depending on the flag fSet) two registry keys.
//  One key is where the default parameters for a given instance are stored.  
//  The other is where the state information for the instance is stored that 
//  tells what information was retrieved during the last dir sync, and what to 
//  get next.  The state key is always a subkey of the parameter key called 
//  "State".
// -----------------------------------------------------------------------------
static HRESULT HrOpenRegistryKeys(void)     // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    DWORD               dwStatus            = ERROR_SUCCESS;
    DWORD               dwDisposition       = 0;
    HKEY                hBaseKey            = NULL;
    char *              pszSubKey           = NULL;

    DEBUGPRIVATE("HrOpenRegistryKeys()\n");

    // First, get the base key handle and sub key name from the string passed 
    // in /KEY or built from the instance name.

    hr = HrIdentifyRegistryRootKey(szKey, &hBaseKey, &pszSubKey);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_INVALID_REGISTRY_KEY_NAME, 
            1, szKey, 
            0);
        goto cleanup;
    }

    // Try to open the parameter key.

    dwStatus = RegOpenKeyEx(
        hBaseKey, 
        pszSubKey, 
        0L, 
        KEY_ALL_ACCESS, 
        (struct HKEY__ **) &hKey);

    // If the key doesn't exist, then we need to create it...
    
    if (dwStatus == ERROR_FILE_NOT_FOUND)
    {
        // If the user didn't already ask to create a new instance with the 
        // /SET flag, then ask the user whether to create a new instance.

        if (!fSet)
        {
            if (fAskCreateInstance() == FALSE)
            {
                // User said "no", so terminate.

                switch (dwSettingsSource)
                {
                    case SOURCE_KEY:
                        fprintf(stderr, "NT registry key not created.\n");
                        fRespondedToUser = TRUE;
                        break;

                    default:
                    case SOURCE_INSTANCE:
                        fprintf(stderr, "Instance not created.\n");
                        fRespondedToUser = TRUE;
                        break;
                }
                hr = E_FAIL;
                goto cleanup;
            }
            else
            {
                // User said "yes", so set the flag the same as if it had been 
                // set using /SET.

                fSet = TRUE;
            }
        }
    }

    // ...otherwise, if we got some other error trying to open the parameter 
    // key then log it and return...

    else if (dwStatus != ERROR_SUCCESS)
    {
        if (fSet)
        {
            EventLogMsg(
                DIRSYNC_CANNOT_CREATE_KEY, 
                1, szKey, 
                1, dwStatus);
        }
        else
        {
            EventLogMsg(
                DIRSYNC_CANNOT_OPEN_KEY, 
                1, szKey, 
                1, dwStatus);
        }
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // ...otherwise the parameter key was opened successfully, so open 
    // the state key.

    else
    {
        dwStatus = RegOpenKeyEx(
            hKey, 
            TEXT("State"), 
            0L, 
            KEY_ALL_ACCESS, 
            (struct HKEY__ **) &hKeyState);
        if (dwStatus != ERROR_SUCCESS)
        {
            EventLogMsg(
                DIRSYNC_CANNOT_OPEN_KEY, 
                1, szKeyState, 
                1, dwStatus);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    // If we've gotten to here and the keys have not been opened yet, 
    // then the user must have requested that we create them.

    if (hKey == NULL || hKeyState == NULL)
    {
        // Create a new parameter key.

        if (hKey == NULL)
        {
            dwStatus = RegCreateKeyEx(
                hBaseKey, 
                pszSubKey, 
                0L, 
                NULL, 
                REG_OPTION_NON_VOLATILE, 
                KEY_ALL_ACCESS, 
                NULL, 
                (struct HKEY__ **) &hKey, 
                &dwDisposition);
            if (dwStatus != ERROR_SUCCESS)
            {
                EventLogMsg(
                    DIRSYNC_CANNOT_CREATE_KEY, 
                    1, szKey, 
                    1, dwStatus);
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        // Create a new state key.

        if (hKeyState == NULL)
        {
            dwStatus = RegCreateKeyEx(
                hKey, 
                TEXT("State"), 
                0L, 
                NULL, 
                REG_OPTION_NON_VOLATILE, 
                KEY_ALL_ACCESS, 
                NULL, 
                (struct HKEY__ **) &hKeyState, 
                &dwDisposition);
            if (dwStatus != ERROR_SUCCESS)
            {
                EventLogMsg(
                    DIRSYNC_CANNOT_CREATE_KEY, 
                    1, szKey, 
                    1, dwStatus);
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        // Display a message that we created the keys.

        switch (dwSettingsSource)
        {
            case SOURCE_KEY:
                fprintf(stderr, "Created new NT registry key:\n%s\n", szKey);
                fRespondedToUser = TRUE;
                break;

            default:
            case SOURCE_INSTANCE:
                fprintf(stderr, 
                    "Created new NT registry key for instance %s:\n%s\n", 
                    szInstanceName, szKey);
                fRespondedToUser = TRUE;
                break;
        }
    }

cleanup:
    if (FAILED(hr))
    {
        CLOSEHANDLE(hKey);
        CLOSEHANDLE(hKeyState);
    }

    RETURN(hr);
}



//$--fAskCreateInstance---------------------------------------------------------
//  Ask the user whether or not to create a new key or instance.
// -----------------------------------------------------------------------------
static BOOL fAskCreateInstance(void)        // RETURNS: TRUE=create, FALSE=don't
{
    BOOL                fReturn             = TRUE;
    TCHAR               chAnswer            = 0;

    DEBUGPRIVATE("fAskCreateInstance()\n");

    // Ask the user whether to create a new key or instance.  Keep asking until 
    // we get a yes or no.

    do
    {
        if (*szInstanceName)
        {
            printf(
                "The instance %s is unknown.  "
                "Create a new instance?  (Y/N) ", szInstanceName);
        }
        else
        {
            printf(
                "The NT registry key\n"
                "%s does not exist.\n"
                "Create a new key? (Y/N) ", szKey);
        }

        chAnswer = toupper(_getche());
        printf("\n");
    }
    while (chAnswer != 'Y' && chAnswer != 'N');

    // Give a confirmation message telling whether we are creating a new 
    // key/instance or not.

    if (chAnswer == 'Y')
    {
        fReturn = TRUE;
    }
    else
    {
        fReturn = FALSE;
    }

    return(fReturn);
}



//$--HrReadRegistryData---------------------------------------------------------
//  Reads the default parameters and state information from the registry.
// -----------------------------------------------------------------------------
static HRESULT HrReadRegistryData(void)     // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    DWORD               dwType              = 0;
    DWORD               cbImportedObjectList = 0;

    DEBUGPRIVATE("HrReadRegistryData()\n");

    hr = HrReadRegistryVariables(
        hKey, 
        szKey, 
        ARRAY_CNT(rgrvInstanceData), 
        rgrvInstanceData);
    if (FAILED(hr))
        goto cleanup;

    CleanupAttributeList(szExportList);

    // Find the length of the imported object list (if the value doesn't exist 
    // then assume it has zero length).

    hr = RegQueryValueEx(
        hKeyState, 
        TEXT("Imported Object List"), 
        NULL, 
        NULL, 
        NULL, 
        &cbImportedObjectList);

    if (hr == ERROR_FILE_NOT_FOUND)
    {
        cbImportedObjectList = 0;
        hr = NOERROR;
    }
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_CANNOT_READ_REGISTRY_VALUE, 
            2, TEXT("Imported Object List"), szKeyState, 
            1, hr);
        goto cleanup;
    }

    // Set the current size of the imported object list.

    cdwImportedObjectList = cbImportedObjectList / sizeof(DWORD);

    // Allocate a buffer for the imported object list with room to grow.

    cbImportedObjectList += (IMPORTED_OBJECT_LIST_GROWTH_SIZE * sizeof(DWORD));

    hr = MAPIAllocateBuffer(
        cbImportedObjectList, 
        &rgdwImportedObjectList);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_ERROR, 
            0, 
            1, ERROR_OUTOFMEMORY);
        goto cleanup;
    }

    cdwMaxImportedObjectList = cbImportedObjectList / sizeof(DWORD);

    // Set the buffer address and size in the REG_VARIABLE structure.

    rgrvStateData[0].cbData = cbImportedObjectList;
    rgrvStateData[0].pbData = rgdwImportedObjectList;

    // Read the state data from the registry.

    hr = HrReadRegistryVariables(
        hKeyState, 
        szKeyState, 
        ARRAY_CNT(rgrvStateData), 
        rgrvStateData);
    if (FAILED(hr))
        goto cleanup;

    // If the binary data was not an integral number of DWORD's 
    // then it's an error.

    if (rgrvStateData[0].cbData % sizeof(DWORD))
    {
        CHAR szDWORDSize[20] = {0};

        _itoa(sizeof(DWORD), szDWORDSize, 10);

        EventLogMsg(
            DIRSYNC_INVALID_REGISTRY_VALUE_SIZE, 
            3, TEXT("Imported Object List"), szKeyState, szDWORDSize, 
            0);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    RETURN(hr);
}



//$--HrParseCommandLine---------------------------------------------------------
//  Parse the command line arguments and put their values in the appropriate 
//  variables.
// -----------------------------------------------------------------------------
static HRESULT HrParseCommandLine(          // RETURNS: HRESULT
    IN int argc,                            // number of arguments on command line
    IN char *argv[])                        // array of command line arguments
{
    HRESULT             hr                  = NOERROR;
    int                 i                   = 0;
    char *              pszArgument         = NULL;
    char *              pszValue            = NULL;

    DEBUGPRIVATE("HrParseCommandLine()\n");

    // Check parameters.

    hr = CHK_main(argc, argv);
    if (FAILED(hr))
        RETURN(hr);

    for (i = 1; i < argc; i++)
    {
        hr = _HrExpandCommandLineArgument(
            argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
            &pszArgument, &pszValue);

        if (FAILED(hr))
        {
            fprintf(stderr, "ERROR: ambiguous command line flag: %s\n", 
            argv[i]);
            fRespondedToUser = TRUE;
            goto cleanup;
        }

        if (pszArgument)
        {
            // Put all the flags that do not take a value here.

            if (!_stricmp(pszArgument,ARG_EXPORT))
            {
                dwDirection = DIRECTION_EXPORT;
            }
            else if (!_stricmp(pszArgument,ARG_IMPORT))
            {
                dwDirection = DIRECTION_IMPORT;
            }
            else if (!_stricmp(pszArgument,ARG_BOTH))
            {
                dwDirection = DIRECTION_IMPORT | DIRECTION_EXPORT;
            }
            else if (!_stricmp(pszArgument,ARG_EXPFULL))
            {
                fFullExport = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOEXPFULL))
            {
                fFullExport = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_IMPFULL))
            {
                fFullImport = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOIMPFULL))
            {
                fFullImport = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_PROGRESS))
            {
                fProgressDialog = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOPROGRESS))
            {
                fProgressDialog = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_SUBS))
            {
                fSubs = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOSUBS))
            {
                fSubs = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_NTCREATE))
            {
                fNTCreate = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NONTCREATE))
            {
                fNTCreate = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_NTDELETE))
            {
                fNTDelete = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NONTDELETE))
            {
                fNTDelete = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_MVAPPEND))
            {
                fMVAppend = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOMVAPPEND))
            {
                fMVAppend = FALSE;
            }
            else if (
                !_stricmp(pszArgument,ARG_SET) || 
                !_stricmp(pszArgument,ARG_DISPLAY))
            {
                // We already parsed these, but keep this if statement as 
                // a placeholder so it doesn't think /SET or /DISPLAY needs 
                // a value.
            }

            // If we got this far we know it's a flag that requires a value, 
            // so if they didn't give one then it's an error.  We know it 
            // is a valid flag because pszArgument != NULL, and that means 
            // the flag is in the list.

            else if (pszValue == NULL)
            {
                fprintf(stderr, "ERROR: flag /%s requires a value\n", 
                    pszArgument);
                fRespondedToUser = TRUE;
                hr = HR_LOG(E_FAIL);
            }

            // Put all the flags that take a value here.

            else if (!_stricmp(pszArgument,ARG_DSA))
            {
                STRNCPY(szDSA, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_BASEPOINT))
            {
                STRNCPY(szBasePoint, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_CONTAINER))
            {
                STRNCPY(szContainer, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_SERVER))
            {
                STRNCPY(szServer, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_HOMESERVER))
            {
                STRNCPY(szHomeServer, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_EXPLIST))
            {
                STRNCPY(szExportList, pszValue);
                CleanupAttributeList(szExportList);
            }
            else if (!_stricmp(pszArgument,ARG_EXPFILE))
            {
                STRNCPY(szExportFile, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_IMPFILE))
            {
                STRNCPY(szImportFile, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_USN))
            {
                dwLastUSN = atol(pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_OBJCLASS))
            {
                ULONG iObjClass = 0;

                hr = _HrFindArrayValue(
                    pszValue, 
                    rgpszObjClassValues, 
                    ARRAY_CNT(rgpszObjClassValues), 
                    &iObjClass);
                if (hr == EDK_E_NOT_FOUND || *pszValue == 0)
                {
                    fprintf(
                        stderr, 
                        "ERROR: \"%s\" is an invalid value for flag /%s.\n", 
                        pszValue, 
                        ARG_OBJCLASS);
                    fRespondedToUser = TRUE;
                    hr = HR_LOG(E_FAIL);
                }
                else if (FAILED(hr))
                {
                    fprintf(stderr, "ERROR: unable to parse argument %s.\n", argv[i]);
                    fRespondedToUser = TRUE;
                    hr = HR_LOG(E_FAIL);
                }
                else
                {
                    STRNCPY(szObjClass, rgpszObjClassValues[iObjClass]);
                }
            }
        }
    }

cleanup:
    RETURN(hr);
}



//$--HrWriteInstanceData--------------------------------------------------------
//  Write the instance variables to the registry.
// -----------------------------------------------------------------------------
static HRESULT HrWriteInstanceData(void)    // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrWriteInstanceData()\n");

    hr = HrWriteRegistryVariables(
        hKey, 
        szKey, 
        ARRAY_CNT(rgrvInstanceData), 
        rgrvInstanceData);
    if (FAILED(hr))
        goto cleanup;

cleanup:
    RETURN(hr);
}



//$--HrWriteStateData-----------------------------------------------------------
//  Write the state variables to the registry.
// -----------------------------------------------------------------------------
static HRESULT HrWriteStateData(void)       // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrWriteStateData()\n");

    rgrvStateData[0].pbData = rgdwImportedObjectList;
    rgrvStateData[0].cbData = cdwImportedObjectList * sizeof(DWORD);

    hr = HrWriteRegistryVariables(
        hKeyState, 
        szKeyState, 
        ARRAY_CNT(rgrvStateData), 
        rgrvStateData);
    if (FAILED(hr))
        goto cleanup;

cleanup:
    RETURN(hr);
}



//$--HrCheckInfoCompleteness----------------------------------------------------
//  Make sure that we have all the information to do directory synchronization.
//  This information can come from the command line and/or the registry.
// -----------------------------------------------------------------------------
static HRESULT HrCheckInfoCompleteness(void) // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrCheckInfoCompleteness()\n");

    // If we are doing an import, then make sure the Object Class is valid.

    if (dwDirection & DIRECTION_IMPORT)
    {
        DWORD iObjClass = 0;
        BOOL fObjClassIsValid = FALSE;

        for (iObjClass = 0; iObjClass < ARRAY_CNT(rgpszObjClassValues); iObjClass++)
        {
            if (!_stricmp(szObjClass, rgpszObjClassValues[iObjClass]))
            {
                fObjClassIsValid = TRUE;
                break;
            }
        }
        if (!fObjClassIsValid)
        {
            fprintf(
                stderr, 
                "ERROR: Invalid Object Class value \"%s\" in registry\n", 
                szObjClass);
            hr = HR_LOG(E_FAIL);
        }
    }

    if (*szKey == 0 && dwSettingsSource != SOURCE_COMMAND_LINE)
    {
        fprintf(stderr, "ERROR: please specify instance name or /%s\n", 
            ARG_KEY);
        fRespondedToUser = TRUE;
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if (dwDirection == 0)
    {
        fprintf(stderr, "ERROR: no action specified; "
            "please specify /%s, /%s or /%s.\n", 
            ARG_IMPORT, ARG_EXPORT, ARG_BOTH);
        fRespondedToUser = TRUE;
        hr = HR_LOG(E_FAIL);

        // Don't give any more messages if they didn't specify an action.

        goto cleanup;
    }

    if (*szDSA == 0)
    {
        fprintf(stderr, "ERROR: please specify /%s\n", ARG_DSA);
        fRespondedToUser = TRUE;
        hr = HR_LOG(E_FAIL);
    }

    if (*szBasePoint == 0)
    {
        fprintf(stderr, "ERROR: please specify /%s\n", ARG_BASEPOINT);
        fRespondedToUser = TRUE;
        hr = HR_LOG(E_FAIL);
    }

    if (*szContainer == 0)
    {
        fprintf(stderr, "ERROR: please specify /%s\n", ARG_CONTAINER);
        fRespondedToUser = TRUE;
        hr = HR_LOG(E_FAIL);
    }

    if (dwDirection & DIRECTION_EXPORT)
    {
        if (*szExportFile == 0)
        {
            fprintf(stderr, "ERROR: please specify /%s\n", ARG_EXPFILE);
            fRespondedToUser = TRUE;
            hr = HR_LOG(E_FAIL);
        }
    }

    if (dwDirection & DIRECTION_IMPORT)
    {
        if (*szImportFile == 0)
        {
            fprintf(stderr, "ERROR: please specify /%s\n", ARG_IMPFILE);
            fRespondedToUser = TRUE;
            hr = HR_LOG(E_FAIL);
        }
    }

cleanup:
    RETURN(hr);
}



//$--HrDoExport-----------------------------------------------------------------
//  Export to a file all objects in the DIT with USN > dwLastUSN.  After each 
//  exported object, update dwLastUSN and write the updated copy to the 
//  registry.
// -----------------------------------------------------------------------------
static HRESULT HrDoExport(void)             // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    HRESULT             hrT                 = NOERROR;
    BEXPORT_PARMS       BExportParms        = {0};
    DAPI_ENTRY          AttributesEntry     = {0};
    ATT_VALUE           AttributesValue     = {0};
    LPBEXPORT_PARMS     bp                  = &BExportParms;
    LPTSTR              pszExportListCopy   = NULL;
    DWORD               i                   = 0;
    LPTSTR              pszObjClass         = NULL;
    BOOL                fExportOpened       = FALSE;

    DEBUGPRIVATE("HrDoExport()\n");

    // Allocate a copy of the export list, and add the attributes we need if 
    // the user didn't include them.  We are allowing 200 bytes to add the 
    // extra attributes.

    hr = MAPIAllocateBuffer(strlen(szExportList) + 200, &pszExportListCopy);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_ERROR, 
            0, 
            1, ERROR_OUTOFMEMORY);
        goto cleanup;
    }

    // DAPI requires that there be exactly one "Obj-Class", and that it 
    // be the first attribute in the list.  So, we must add it to the front 
    // of the string and then remove it from anywhere else.

    // Begin the copy string with "Obj-Class," + the user's export list.

    strcpy(pszExportListCopy, OBJ_CLASS ",");
    strcat(pszExportListCopy, szExportList);

    // Search the resulting string for any instances of "Obj-Class" besides 
    // the one we just added to the front.  If we find any, remove them by 
    // overwriting them with spaces.  The spaces and extra commas will be 
    // cleaned up later when we call CleanupAttributeList().

    pszObjClass = pszExportListCopy + 1;
    while (fFindAttributeInList(OBJ_CLASS, pszObjClass, &pszObjClass))
    {
        _strnset(pszObjClass, ' ', strlen(OBJ_CLASS));
    }

    // Now add USN-Created, USN-Changed, Is-Deleted, Obj-Dist-Name 
    // and Imported-From to the string if they aren't already there.

    if (!fFindAttributeInList(USN_CREATED, pszExportListCopy, NULL))
    {
        strcat(pszExportListCopy, "," USN_CREATED);
    }

    if (!fFindAttributeInList(USN_CHANGED, pszExportListCopy, NULL))
    {
        strcat(pszExportListCopy, "," USN_CHANGED);
    }

    if (!fFindAttributeInList(IS_DELETED, pszExportListCopy, NULL))
    {
        strcat(pszExportListCopy, "," IS_DELETED);
    }

    if (!fFindAttributeInList(OBJ_DIST_NAME, pszExportListCopy, NULL))
    {
        strcat(pszExportListCopy, "," OBJ_DIST_NAME);
    }

    if (!fFindAttributeInList(IMPORTED_FROM, pszExportListCopy, NULL))
    {
        strcat(pszExportListCopy, "," IMPORTED_FROM);
    }

    // Finally, get rid of extra spaces and commas in the string.

    CleanupAttributeList(pszExportListCopy);

    // Set up the structure that defines how to do the export.

    bp->dwDAPISignature = DAPI_SIGNATURE;
    bp->dwFlags = 
        DAPI_SUPPRESS_COMPLETION | 
        DAPI_EVENT_ALL | 
        DAPI_EXPORT_MAILBOX | 
        DAPI_EXPORT_HIDDEN;
    if (!fProgressDialog)
    {
        bp->dwFlags |= DAPI_SUPPRESS_PROGRESS;
    }
    if (fSubs)
    {
        bp->dwFlags |= DAPI_EXPORT_SUBTREE;
    }

    // If they set the full export flag then get all USN's.

    if (fFullExport)
    {
        dwLastUSN = 0;
    }

    // If they didn't explicitly set the full export flag but the 
    // starting USN is 0, then set the full export flag.  This lets 
    // us treat the first running of an incremental export the same 
    // as a full export, so we won't get Delete records exported.

    else if (dwLastUSN == 0)
    {
        fFullExport = TRUE;
    }

    // Only get USN's greater than what we got last time.

    if (dwLastUSN)
    {
        bp->ulUSNBase = dwLastUSN + 1;
    }

    // Store the starting USN value so we use it to distinguish 
    // adds from modifies and other things like that.

    dwStartingUSN = bp->ulUSNBase;

    // Fill in the rest of the structure.

    bp->pszHomeServer = szServer;
    bp->pszDSAName = szDSA;
    bp->pszBasePoint = szBasePoint;
    bp->pszContainer = szContainer;
    bp->chColSep = DAPI_DEFAULT_DELIM;
    bp->chQuote = DAPI_DEFAULT_QUOTE;
    bp->chMVSep = DAPI_DEFAULT_MV_SEP;
    bp->ExportCallback.pfnExportEntry = fExportCallback;
    bp->ExportCallback.ulEvalTag = TEXT_VALUE_ARRAY;
    bp->pszExportFile = szExportFile;
    bp->pAttributes = &AttributesEntry;

    AttributesEntry.unAttributes = 1;
    AttributesEntry.ulEvalTag = TEXT_LINE;
    AttributesEntry.rgEntryValues = &AttributesValue;

    AttributesValue.DapiType = DAPI_TEXT;
    AttributesValue.Value.pszValue = pszExportListCopy;
    AttributesValue.size = lstrlen(pszExportListCopy);

    // Call foreign system open export routine.

    hr = HrOpenExport(szExportFile);
    if (FAILED(hr))
    {
        goto cleanup;
    }
    fExportOpened = TRUE;

    // Export the records (call fExportCallback for each one).

    fErrorInCallback = FALSE;
    cDAPILoggedErrors += BatchExport(bp);

    if (cDAPILoggedErrors || fErrorInCallback)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Call foreign system close export routine.

    fExportOpened = FALSE;
    hr = HrCloseExport();
    if (FAILED(hr))
    {
        goto cleanup;
    }

    // If we are doing an incremental export then clear the imported 
    // objects list.

    if (!fFullExport)
    {
        cdwImportedObjectList = 0;
    }

    // Update the state data in the registry (if we are using the registry).

    if (dwSettingsSource != SOURCE_COMMAND_LINE)
    {
        hr = HrWriteStateData();
        if (FAILED(hr))
            goto cleanup;
    }

    // Log success event.

    switch (dwSettingsSource)
    {
        case SOURCE_INSTANCE:
            EventLogMsg(
                DIRSYNC_EXPORT_SUCCEEDED_INSTANCE, 
                1, szInstanceName, 
                0);
            break;

        case SOURCE_KEY:
            EventLogMsg(
                DIRSYNC_EXPORT_SUCCEEDED_KEY, 
                1, szKey, 
                0);
            break;

        default:
        case SOURCE_COMMAND_LINE:
            EventLogMsg(
                DIRSYNC_EXPORT_SUCCEEDED, 
                0, 
                0);
            break;
    }

cleanup:
    // Call foreign system close export routine if it's open.

    if (fExportOpened)
    {
        (void) HrCloseExport();
    }

    // Free the copy of the attribute list.

    MAPIFREEBUFFER(pszExportListCopy);

    // Free the allocated memory for the attribute names.

    MAPIFREEBUFFER(rgdsAttributes);

    RETURN(hr);
}



//$--fExportCallback------------------------------------------------------------
//  Callback function called by DAPI first to give the list of attributes, 
//  then once for each record being exported.
// -----------------------------------------------------------------------------
static BOOL PASCAL fExportCallback(         // RETURNS: TRUE=continue, FALSE=stop
    IN EXP_TYPE ExportDataType,             // tells whether header or data
    IN LPVOID lpvAppDefined,                // the user's context
    IN PDAPI_ENTRY pDAPIEntry)              // array of attribute data
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("fExportCallback()\n");

    // Check parameters.

    hr = CHK_fExportCallback(
        ExportDataType, 
        lpvAppDefined, 
        pDAPIEntry);
    if (FAILED(hr))
        return(FALSE);

    switch (ExportDataType)
    {
        // Called at start of export operation

        case EXPORT_HEADER:
            hr = HrProcessExportHeader(pDAPIEntry);
            if (FAILED(hr))
                goto cleanup;
            break;

        // Called for each exported record.

        case EXPORT_ENTRY:
            hr = HrProcessExportEntry(pDAPIEntry);
            if (FAILED(hr))
                goto cleanup;
            break;

        // Unknown ExportDataType.

        default:
            EventLogMsg(
                DIRSYNC_INTERNAL_ERROR, 
                0, 
                0);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
    }

cleanup:
    if (FAILED(hr))
    {
        fErrorInCallback = TRUE;
    }

    return(SUCCEEDED(hr));
}



//$--HrProcessExportHeader------------------------------------------------------
//  Function that takes the export header and uses it to save away an allocated 
//  array of attribute names.  It also locates certain attributes needed for 
//  processing of the records.
// -----------------------------------------------------------------------------
static HRESULT HrProcessExportHeader(       // RETURNS: HRESULT
    IN PDAPI_ENTRY pEntry)                  // record to export
{
    HRESULT             hr                  = NOERROR;
    DWORD               i                   = 0;

    DEBUGPRIVATE("fProcessExportHeader()\n");

    // Check parameters.

    hr = CHK_HrProcessExportHeader(pEntry);
    if (FAILED(hr))
        RETURN(hr);

    // Get the number of attribute name strings.

    cdsAttributes = pEntry->unAttributes;

    // Allocate space for an array of structures representing the attributes 
    // that are being sent to us via DAPI callback.

    hr = MAPIAllocateBuffer(
        cdsAttributes * sizeof(*rgdsAttributes), 
        &rgdsAttributes);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_ERROR, 
            0, 
            1, ERROR_OUTOFMEMORY);
        goto cleanup;
    }

    ZeroMemory(rgdsAttributes, cdsAttributes * sizeof(*rgdsAttributes));

    // Loop to make allocated copies of each attribute name and store them 
    // in the array of structures.  Look up each attribute name to see if 
    // the user requested it on the command line, and if so, set the flag.
    // Also, search for the attributes USN-Created, USN-Changed, Is-Deleted 
    // and Obj-Dist-Name and store away their offsets in the array.

    iUSNCreatedAttribute = -1;
    iUSNChangedAttribute = -1;
    iIsDeletedAttribute = -1;
    iObjDistNameAttribute = -1;
    iImportedFromAttribute = -1;

    for  (i = 0; i < cdsAttributes; i++)
    {
        // Allocate a copy of the attribute name string.

        hr = MAPIAllocateMore(
            strlen(pEntry->rgEntryValues[i].Value.pszValue) + 1, 
            rgdsAttributes, 
            &rgdsAttributes[i].pszName);
        if (FAILED(hr))
        {
            EventLogMsg(
                DIRSYNC_ERROR, 
                0, 
                1, ERROR_OUTOFMEMORY);
            goto cleanup;
        }

        strcpy(
            rgdsAttributes[i].pszName, 
            pEntry->rgEntryValues[i].Value.pszValue);

        // See if it's one of the special ones we're looking for.

        if (!_stricmp(rgdsAttributes[i].pszName, USN_CREATED))
        {
            iUSNCreatedAttribute = i;
        }
        else if (!_stricmp(rgdsAttributes[i].pszName, USN_CHANGED))
        {
            iUSNChangedAttribute = i;
        }
        else if (!_stricmp(rgdsAttributes[i].pszName, IS_DELETED))
        {
            iIsDeletedAttribute = i;
        }
        else if (!_stricmp(rgdsAttributes[i].pszName, OBJ_DIST_NAME))
        {
            iObjDistNameAttribute = i;
        }
        else if (!_stricmp(rgdsAttributes[i].pszName, IMPORTED_FROM))
        {
            iImportedFromAttribute = i;
        }

        // See if it was in the user's original request.

        if (fFindAttributeInList(rgdsAttributes[i].pszName, szExportList, NULL))
        {
            rgdsAttributes[i].fRequested = TRUE;
        }
    }

    // If we didn't find all the attributes we were looking for then 
    // that's an error and we can't continue.

    if (iUSNCreatedAttribute == -1 || 
        iUSNChangedAttribute == -1 || 
        iIsDeletedAttribute == -1 || 
        iObjDistNameAttribute == -1 || 
        iImportedFromAttribute == -1)
    {
        EventLogMsg(
            DIRSYNC_INTERNAL_ERROR, 
            0, 
            0);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    // In case of error, free all the allocated memory.

    if (FAILED(hr))
    {
        MAPIFREEBUFFER(rgdsAttributes);
    }

    RETURN(hr);
}



//$--HrProcessExportEntry-------------------------------------------------------
//  Function to process an export entry.  This routine decides whether or not 
//  to write the entry, and whether it should be written as an Add, Modify, or 
//  Delete.
// -----------------------------------------------------------------------------
static HRESULT HrProcessExportEntry(        // RETURNS: HRESULT
    IN PDAPI_ENTRY pDAPIEntry)              // array of attribute data
{
    HRESULT             hr                  = NOERROR;

    PATT_VALUE          pav                 = NULL;

    DWORD               dwUSNCreated        = 0;
    DWORD               dwUSNChanged        = 0;
    BOOL                fIsDeleted          = FALSE;

    BOOL                fExport             = FALSE;
    DIR_SYNC_OPERATION  eOperation          = OPERATION_ADD;

    DEBUGPRIVATE("HrProcessExportEntry()\n");

    // Check parameters.

    hr = CHK_HrProcessExportEntry(pDAPIEntry);
    if (FAILED(hr))
        RETURN(hr);

    // Get USN-Created, USN-Changed, and Is-Deleted for this object.

    pav = &pDAPIEntry->rgEntryValues[iUSNCreatedAttribute];
    if (pav->DapiType != DAPI_NO_VALUE)
    {
        dwUSNCreated = atol(pav->Value.pszValue);
    }

    pav = &pDAPIEntry->rgEntryValues[iUSNChangedAttribute];
    if (pav->DapiType != DAPI_NO_VALUE)
    {
        dwUSNChanged = atol(pav->Value.pszValue);
    }

    pav = &pDAPIEntry->rgEntryValues[iIsDeletedAttribute];
    if (pav->DapiType != DAPI_NO_VALUE && atol(pav->Value.pszValue))
    {
        fIsDeleted = TRUE;
    }

    // Decide whether to export this record, and whether the operation 
    // is Add, Modify or Delete.

    if (dwUSNChanged >= dwStartingUSN)
    {
        if (fIsDeleted)
        {
            if (dwUSNCreated < dwStartingUSN && !fFullExport)
            {
                fExport = TRUE;
                eOperation = OPERATION_DELETE;
            }
        }
        else
        {
            if (dwUSNCreated < dwStartingUSN)
            {
                fExport = TRUE;
                eOperation = OPERATION_MODIFY;
            }
            else
            {
                fExport = TRUE;
                eOperation = OPERATION_ADD;
            }
        }
    }

    // If this item was imported from the foreign system then 
    // don't re-export it.

    if (fExport && cdwImportedObjectList && bsearch(
        &dwUSNChanged, 
        rgdwImportedObjectList, 
        cdwImportedObjectList, 
        sizeof(DWORD), 
        nDWORDCompare))
    {
        fExport = FALSE;
    }

    // Export the record.

    if (fExport)
    {
        hr = HrWriteExport(
            pDAPIEntry, 
            rgdsAttributes, 
            pDAPIEntry->rgEntryValues[iObjDistNameAttribute].Value.pszValue, 
            eOperation);
        if (FAILED(hr))
            goto cleanup;

        cObjectsExported++;
    }

    // If the USN of this record is greater than the highest USN 
    // so far, then update the highest USN.

    if (dwSettingsSource != SOURCE_COMMAND_LINE && 
        dwUSNChanged > dwLastUSN)
    {
        dwLastUSN = dwUSNChanged;
    }

cleanup:
    RETURN(hr);
}



//$--nDWORDCompare--------------------------------------------------------------
//  Compares two DWORDS and returns n>0, n==0, n<0 depending on which is 
//  larger.  This is required for bsearch.
// -----------------------------------------------------------------------------
static int __cdecl nDWORDCompare(           // RETURNS: int
    const void * pdw1,                      // first element to compare
    const void * pdw2)                      // second element to compare
{
    return( (*((int *)pdw1)) - (*((int *)pdw2)) );
}



//$--fFindAttributeInList-------------------------------------------------------
//  Sets *ppszMatch to the address of the first occurance of the attribute 
//  name in the attribute list.  This routine can distinguish between a true 
//  match and an attribute name that is only a subset of another attribute name.
//  Returns TRUE if a match was found, or FALSE if not.
//  If ppszMatch is null, the address of the attribute is not returned, but 
//  the return value tells whether or not the attribute is present.
// -----------------------------------------------------------------------------
static BOOL fFindAttributeInList(           // RETURNS: TRUE if attribute found
    IN LPTSTR pszAttributeName,             // name of attribute to search for
    IN LPTSTR pszAttributeList,             // list of attributes
    OUT LPTSTR * ppszMatch)                 // address of match found (or NULL)
{
    HRESULT             hr                  = NOERROR;
    BOOL                fReturn             = FALSE;
    LPTSTR              psz                 = NULL;
    LPTSTR              pszFound            = NULL;
    DWORD               cchNameLength       = strlen(pszAttributeName);

    DEBUGPRIVATE("fFindAttributeInList()\n");

    // Check parameters.

    hr = CHK_fFindAttributeInList(
        pszAttributeName, 
        pszAttributeList, 
        ppszMatch);
    if (FAILED(hr))
        return(FALSE);

    // Find each occurance of the attribute name in the list.

    for (psz = pszAttributeList; *psz; psz++)
    {
        // If we found the substring, 
        // and it is immediately preceeded by either the beginning of the list 
        // or a comma, 
        // and it is immediately followed by either the end of the list 
        // or a comma,
        // the we have a true match.

        if (!_strnicmp(psz, pszAttributeName, cchNameLength) && 
            (psz == pszAttributeList || *(psz - 1) == ',') && 
            (psz[cchNameLength] == 0 || psz[cchNameLength] == ','))
        {
            pszFound = psz;
            break;
        }
    }

    if (ppszMatch != NULL)
    {
        *ppszMatch = pszFound;
    }

    if (pszFound)
    {
        fReturn = TRUE;
    }

    return(fReturn);
}



//$--CleanupAttributeList-------------------------------------------------------
//  Remove white space and extra commas from an attribute list.  Editing is 
//  done in place.
// -----------------------------------------------------------------------------
static VOID CleanupAttributeList(           // RETURNS: nothing
    IN OUT LPTSTR pszAttributeList)         // attribute list to be cleaned up
{
    HRESULT             hr                  = NOERROR;
    TCHAR *             pSrc                = pszAttributeList;
    TCHAR *             pDst                = pszAttributeList;

    DEBUGPRIVATE("CleanupAttributeList()\n");

    // Check parameters.

    hr = CHK_CleanupAttributeList(pszAttributeList);
    if (FAILED(hr))
    {
        HR_LOG(hr);
        return;
    }

    // Go through the string and strip out bogus characters.

    while (*pSrc)
    {
        // If this char is white space, or a comma at the beginning of the 
        // string, or a double comma then strip it out.

        if (isspace(*pSrc) || (*pSrc == ',' && pDst == pszAttributeList) || 
            (*pSrc == ',' && pDst > pszAttributeList && *(pDst - 1) == ','))
        {
            pSrc++;
        }

        // Otherwise copy it over.

        else
        {
            *pDst++ = *pSrc++;
        }
    }

    // If there's an extra comma at the end then get rid of it.

    if (pDst > pszAttributeList && *(pDst - 1) == ',')
    {
        --pDst;
    }

    // Null terminate the destination string.

    *pDst = 0;
}



//$--HrDoImport-----------------------------------------------------------------
//  Import objects from a file.
// -----------------------------------------------------------------------------
static HRESULT HrDoImport(void)             // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DAPI_PARMS          sDAPIParms          = {0};
    DAPI_HANDLE         hDAPISession        = NULL;
    PDAPI_EVENT         pDAPIEvent          = NULL;
    PDAPI_EVENT         pde                 = NULL;

    PDAPI_ENTRY         pAttributes         = NULL;
    PDAPI_ENTRY         pValues             = NULL;

    DIR_SYNC_OPERATION  eOperation          = 0;
    DWORD               dwWriteFlags        = 0;
    ULONG               ulNewUSN            = 0;

    BOOL                fImportOpened       = FALSE;
    BOOL                fDAPIInitialized    = FALSE;
    HANDLE              hDAPIEventSource    = NULL;

    CHAR                szTemp1[20]         = {0};

    DEBUGPRIVATE("rcDoImport()\n");

    // Log that we are beginning the import operation.

    switch (dwSettingsSource)
    {
        case SOURCE_INSTANCE:
            EventLogMsg(
                DIRSYNC_BEGIN_IMPORT_INSTANCE, 
                2, szDSA, szInstanceName, 
                0);
            break;

        case SOURCE_KEY:
            EventLogMsg(
                DIRSYNC_BEGIN_IMPORT_KEY, 
                2, szDSA, szKey, 
                0);
            break;

        default:
        case SOURCE_COMMAND_LINE:
            EventLogMsg(
                DIRSYNC_BEGIN_IMPORT, 
                1, szDSA, 
                0);
            break;
    }

    // Reset to count of objects imported.

    cObjectsImported = 0;

    // Get handle to report DAPI events.

    hDAPIEventSource = RegisterEventSource(NULL, TEXT("Directory Import"));
    if (hDAPIEventSource == NULL)
    {
        // Log a warning.

        EventLogMsg(
            DIRSYNC_CANNOT_REGISTER_DAPI_EVENT_SOURCE, 
            0, 
            1, GetLastError());
    }

    // Initialize DAPI.

    sDAPIParms.dwDAPISignature = DAPI_SIGNATURE;
    sDAPIParms.pszDSAName = szDSA;
    if (fNTCreate)
    {
        sDAPIParms.dwFlags |= DAPI_CREATE_NT_ACCOUNT;
    }
    if (fNTDelete)
    {
        sDAPIParms.dwFlags |= DAPI_DELETE_NT_ACCOUNT;
    }

    pDAPIEvent = DAPIStart(
        &hDAPISession, 
        &sDAPIParms);
    if (pDAPIEvent)
    {
        if (hDAPIEventSource)
        {
            for (pde = pDAPIEvent; pde; pde = pde->pNextEvent)
            {
                (void) ReportEvent(
                    hDAPIEventSource, 
                    (WORD)EVENTLOG_ERROR_TYPE, 
                    0, 
                    pde->dwDAPIError, 
                    NULL, 
                    (WORD)pde->unSubst, 
                    0, 
                    pde->rgpszSubst, 
                    NULL);
                ++cDAPILoggedErrors;
            }
        }
        DAPIFreeMemory(pDAPIEvent);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
    fDAPIInitialized = TRUE;

    // Call foreign system open import routine.

    hr = HrOpenImport(
        szImportFile, 
        szObjClass, 
        szSourceStamp, 
        szBasePoint, 
        szContainer, 
        szHomeServer);
    if (FAILED(hr))
        goto cleanup;
    fImportOpened = TRUE;

    // Loop for each record in the file.

    while (TRUE)
    {
        // Import a record.

        hr = HrReadImport(
            &eOperation, 
            &pAttributes, 
            &pValues);
        if (FAILED(hr))
        {
            // If end of file then we're done (no error).

            if (hr == EDK_E_END_OF_FILE)
            {
                hr = NOERROR;
                break;
            }
            goto cleanup;
        }

        // Reset write flags for this loop iteration.

        dwWriteFlags = 0;

        // Set the flags based on the type of operation.

        switch (eOperation)
        {
            case OPERATION_ADD:
                dwWriteFlags |= DAPI_WRITE_CREATE;
                break;

            case OPERATION_MODIFY:
                dwWriteFlags |= DAPI_WRITE_UPDATE;
                if (!fMVAppend)
                {
                    dwWriteFlags |= DAPI_MODIFY_REPLACE_PROPERTIES;
                }
                break;

            case OPERATION_DELETE:
                dwWriteFlags |= DAPI_WRITE_DELETE;
                break;

            default:
                EventLogMsg(
                    DIRSYNC_INTERNAL_ERROR, 
                    0, 
                    0);
                hr = HR_LOG(E_FAIL);
                goto cleanup;
        }

        // Write the record to the DSA.
        // (NOTE: DAPIWrite may return events even if it was successful.
        // The true indicator of a successful write is that a new USN 
        // is returned.)

        ulNewUSN = 0;
        pDAPIEvent = DAPIWrite(
            hDAPISession, 
            dwWriteFlags, 
            pAttributes, 
            pValues, 
            &ulNewUSN, 
            NULL, 
            NULL);

        // Log any events returned by DAPIWrite.

        if (pDAPIEvent)
        {
            if (hDAPIEventSource)
            {
                for (pde = pDAPIEvent; pde; pde = pde->pNextEvent)
                {
                    (void) ReportEvent(
                        hDAPIEventSource, 
                        (WORD)EVENTLOG_ERROR_TYPE, 
                        0, 
                        pde->dwDAPIError, 
                        NULL, 
                        (WORD)pde->unSubst, 
                        0, 
                        pde->rgpszSubst, 
                        NULL);
                    ++cDAPILoggedErrors;
                }
            }
            DAPIFreeMemory(pDAPIEvent);
        }

        // If DAPIWrite succeeded...

        if (ulNewUSN != 0)
        {
            // Count this object as succesfully imported.

            cObjectsImported++;

            // Expand the imported object list list if it's full.

            if (cdwImportedObjectList >= cdwMaxImportedObjectList)
            {
                LPDWORD rgdwNew = NULL;
                DWORD cdwNew = 
                cdwMaxImportedObjectList + IMPORTED_OBJECT_LIST_GROWTH_SIZE;

                // Allocate the new memory.

                hr = MAPIAllocateBuffer(
                    cdwNew * sizeof(DWORD), 
                    &rgdwNew);
                if (FAILED(hr))
                {
                    EventLogMsg(
                        DIRSYNC_ERROR, 
                        0, 
                        1, ERROR_OUTOFMEMORY);
                    goto cleanup;
                }

                // Copy the data from the old memory to the new.

                if (cdwImportedObjectList && rgdwImportedObjectList)
                {
                    CopyMemory(
                        rgdwNew, 
                        rgdwImportedObjectList, 
                        cdwImportedObjectList * sizeof(DWORD));
                }

                // Free the old memory.

                MAPIFREEBUFFER(rgdwImportedObjectList);

                // Replace the old memory pointer with the new.

                rgdwImportedObjectList = rgdwNew;
                cdwMaxImportedObjectList = cdwNew;
            }

            // Add the USN of the record we wrote to the imported object list.

            rgdwImportedObjectList[cdwImportedObjectList++] = ulNewUSN;
        }

        // Free the structures that were returned from HrReadImport().

        MAPIFREEBUFFER(pAttributes);
        MAPIFREEBUFFER(pValues);
    }

    // Update the state data in the registry.

    if (dwSettingsSource != SOURCE_COMMAND_LINE)
    {
        hr = HrWriteStateData();
        if (FAILED(hr))
            goto cleanup;
    }

    // Call foreign system close import routine.

    fImportOpened = FALSE;
    hr = HrCloseImport();
    if (FAILED(hr))
        goto cleanup;

cleanup:
    // Log the number of objects imported.

    switch (dwSettingsSource)
    {
        case SOURCE_INSTANCE:
            EventLogMsg(
                DIRSYNC_END_IMPORT_INSTANCE, 
                3, _itoa(cObjectsImported,szTemp1,10), szDSA, szInstanceName, 
                0);
            break;

        case SOURCE_KEY:
            EventLogMsg(
                DIRSYNC_END_IMPORT_KEY, 
                3, _itoa(cObjectsImported,szTemp1,10), szDSA, szKey, 
                0);
            break;

        default:
        case SOURCE_COMMAND_LINE:
            EventLogMsg(
                DIRSYNC_END_IMPORT, 
                2, _itoa(cObjectsImported,szTemp1,10), szDSA, 
                0);
            break;
    }

    // Free any leftover memory structures.

    MAPIFREEBUFFER(pAttributes);
    MAPIFREEBUFFER(pValues);

    // Call foreign system close import routine if it's open.

    if (fImportOpened)
    {
        (void) HrCloseImport();
    }

    // De-Initialize DAPI.

    if (fDAPIInitialized)
    {
        DAPIEnd(&hDAPISession);
    }

    // Close DAPI event logging.

    CLOSEHANDLE(hDAPIEventSource);

    RETURN(hr);
}



//$--HrReadRegistryVariables----------------------------------------------------
//  Read a group of registry values into variables as defined by the array of 
//  REG_VARIABLE structures.
// -----------------------------------------------------------------------------
static HRESULT HrReadRegistryVariables(     // RETURNS: HRESULT
    IN      HANDLE          hRegistryKey,   // handle of reg key to read from
    IN      LPTSTR          pszRegistryKey, // name of registry key to read from
    IN      DWORD           cVariables,     // number of values to read
    IN OUT  LPREG_VARIABLE  rgrvVariables)  // array of structures that map 
                                            // values to variables
{
    HRESULT             hr                  = NOERROR;
    DWORD               iVariable           = 0;
    DWORD               dwType              = 0;

    DEBUGPRIVATE("HrReadRegistryVariables()\n");

    hr = CHK_HrReadWriteRegistryVariables(
        hRegistryKey, 
        pszRegistryKey, 
        cVariables, 
        rgrvVariables);
    if (FAILED(hr))
        RETURN(hr);

    if (dwSettingsSource != SOURCE_COMMAND_LINE)
    {
        for (iVariable = 0; iVariable < cVariables; iVariable++)
        {
            hr = RegQueryValueEx(
                hRegistryKey, 
                rgrvVariables[iVariable].pszValueName, 
                NULL, 
                &dwType, 
                rgrvVariables[iVariable].pbData, 
                &rgrvVariables[iVariable].cbData);
            if (hr == ERROR_FILE_NOT_FOUND)
            {
                hr = NOERROR;
            }
            else if (FAILED(hr) || rgrvVariables[iVariable].dwType != dwType)
            {
                EventLogMsg(
                    DIRSYNC_CANNOT_READ_REGISTRY_VALUE, 
                    2, rgrvVariables[iVariable].pszValueName, pszRegistryKey, 
                    1, hr);
                goto cleanup;
            }
            else if (dwType == REG_SZ)
            {
                LPTSTR psz = rgrvVariables[iVariable].pbData;
                DWORD cch = rgrvVariables[iVariable].cbData / sizeof(TCHAR);
                psz[cch] = 0;
            }
        }
    }

cleanup:
    RETURN(hr);
}



//$--HrWriteRegistryVariables---------------------------------------------------
//  Write a group of variables to a registry key, as defined by the array of 
//  REG_VARIABLE structures.
// -----------------------------------------------------------------------------
static HRESULT HrWriteRegistryVariables(    // RETURNS: HRESULT
    IN      HANDLE          hRegistryKey,   // handle of reg key to write to
    IN      LPTSTR          pszRegistryKey, // name of registry key to write to
    IN      DWORD           cVariables,     // number of values to write
    IN OUT  LPREG_VARIABLE  rgrvVariables)  // array of structures that map 
                                            // values to variables
{
    HRESULT             hr                  = NOERROR;
    DWORD               iVariable           = 0;
    DWORD               cbData              = 0;

    DEBUGPRIVATE("HrWriteRegistryVariables()\n");

    hr = CHK_HrReadWriteRegistryVariables(
        hRegistryKey, 
        pszRegistryKey, 
        cVariables, 
        rgrvVariables);
    if (FAILED(hr))
        RETURN(hr);

    if (dwSettingsSource != SOURCE_COMMAND_LINE)
    {
        for (iVariable = 0; iVariable < cVariables; iVariable++)
        {
            switch (rgrvVariables[iVariable].dwType)
            {
                case REG_SZ:
                    cbData = strlen(rgrvVariables[iVariable].pbData);
                    break;

                default:
                    cbData = rgrvVariables[iVariable].cbData;
                    break;
            }

            hr = RegSetValueEx(
                hRegistryKey, 
                rgrvVariables[iVariable].pszValueName, 
                0, 
                rgrvVariables[iVariable].dwType, 
                rgrvVariables[iVariable].pbData, 
                cbData);
            if (FAILED(hr))
            {
                EventLogMsg(
                    DIRSYNC_CANNOT_WRITE_REGISTRY_VALUE, 
                    2, rgrvVariables[iVariable].pszValueName, pszRegistryKey, 
                    1, hr);
                goto cleanup;
            }
        }
    }

cleanup:
    RETURN(hr);
}



//$--PrintResults---------------------------------------------------------------
//  Print the results of the directory synchronization operation.
//  This routine prints the number of errors and warnings logged, 
//  and whether the operation succeeded or failed.
// -----------------------------------------------------------------------------
static VOID PrintResults(                   // RETURNS: nothing
    IN  HRESULT         hr,                 // result code from operation
    IN  BOOL            fEventLogOpen)      // TRUE if EDK event logging is open
{
    HRESULT             hrT                 = NOERROR;
    EDKEVENTCOUNT       sEventCount         = {0};

    DEBUGPRIVATE("PrintResults()\n");

    if (fEventLogOpen)
    {
        HRESULT hrT = NOERROR;

        hrT = HrEventGetCounts(&sEventCount);
        if (FAILED(hrT))
        {
            fprintf(stderr, 
                "WARNING: unable to get number of errors logged.\n");
        }
        else
        {
            // Add in any errors logged by DAPI.

            sEventCount.cError += cDAPILoggedErrors;

            // Print the number of errors logged.

            if (sEventCount.cError == 1)
            {
                fprintf(stderr, 
                    "ERROR: 1 error written to NT event log.\n");
                fRespondedToUser = TRUE;
            }
            else if (sEventCount.cError > 1)
            {
                fprintf(stderr, 
                    "ERROR: %d errors written to NT event log.\n", 
                    sEventCount.cError);
                fRespondedToUser = TRUE;
            }

            // Print the number of warnings logged.

            if (sEventCount.cWarning == 1)
            {
                fprintf(stderr, 
                    "WARNING: 1 warning written to NT event log.\n");
            }
            else if (sEventCount.cWarning > 1)
            {
                fprintf(stderr, 
                    "WARNING: %d warnings written to NT event log.\n", 
                    sEventCount.cWarning);
            }
        }
    }

    if (!fRespondedToUser)
    {
        if (SUCCEEDED(hr))
        {
            fprintf(stderr, "Done.\n");
        }
        else
        {
            fprintf(stderr, "Operation failed.\n");
        }
    }
}
