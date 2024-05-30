// --fimport.c------------------------------------------------------------------
//
//  The Exchange SDK Folder Import sample allows bulk import of data 
//  into an Exchange folder.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "attrname.h"
#include "fimportm.h"
#include "fimport.chk"

//
// Names of Command Line Arguments
//

#define ARG_PROGRAM_NAME        "FIMPORT"
#define ARG_HELP1               "?"
#define ARG_HELP2               "HELP"
#define ARG_APPEND              "APPEND"
#define ARG_UPDATE              "UPDATE"
#define ARG_REPLACE             "REPLACE"
#define ARG_FILE                "FILE"
#define ARG_FOLDERPATH          "FOLDERPATH"
#define ARG_CLASS               "CLASS"
#define ARG_PROFILE             "PROFILE"
#define ARG_SETREAD             "SETREAD"
#define ARG_NOSETREAD           "NOSETREAD"
#define ARG_EFD                 "EFD"
#define ARG_NOEFD               "NOEFD"
#define ARG_PROGRESS            "PROGRESS"
#define ARG_NOPROGRESS          "NOPROGRESS"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
    ARG_HELP1,
    ARG_HELP2,
    ARG_APPEND,
    ARG_UPDATE,
    ARG_REPLACE,
    ARG_FILE,
    ARG_FOLDERPATH,
    ARG_CLASS,
    ARG_PROFILE,
    ARG_SETREAD,
    ARG_NOSETREAD,
    ARG_EFD,
    ARG_NOEFD,
    ARG_PROGRESS,
    ARG_NOPROGRESS,
};

//
// Table of Commands for First Line of .CSV File.
//

static char * rgpszFileCommandArray[] = {
    ARG_APPEND,
    ARG_UPDATE,
    ARG_REPLACE,
    ARG_FOLDERPATH,
    ARG_CLASS,
    ARG_SETREAD,
    ARG_NOSETREAD,
    ARG_EFD,
    ARG_NOEFD,
};

// These equates MUST equal the offset of the 
// corresponding entry in rgpszFileCommandArray.

typedef enum _FileCommand        // fc
{
    FILECOMMAND_APPEND          = 0,
    FILECOMMAND_UPDATE          = 1,
    FILECOMMAND_REPLACE         = 2,
    FILECOMMAND_FOLDERPATH      = 3,
    FILECOMMAND_CLASS           = 4,
    FILECOMMAND_SETREAD         = 5,
    FILECOMMAND_NOSETREAD       = 6,
    FILECOMMAND_EFD             = 7,
    FILECOMMAND_NOEFD           = 8,
}
FILECOMMAND, *LPFILECOMMAND;

//
// Enumerations, Structures and Type Definitions
//

typedef enum _Operation         // op
{
    OP_APPEND,
    OP_UPDATE,
    OP_REPLACE,
}
OPERATION, *LPOPERATION;


typedef enum _PropTypeCode      // ptc
{
    PROPTYPECODE_LONG           = 'L',
    PROPTYPECODE_STRING         = 'S',
    PROPTYPECODE_SYSTIME        = 'T',
    PROPTYPECODE_UNICODE        = 'U',
    PROPTYPECODE_BOOLEAN        = 'B',
    PROPTYPECODE_BINARY         = 'X',
    PROPTYPECODE_GUID           = 'G',
    PROPTYPECODE_MULTI          = 'M',
}
PROPTYPECODE, *LPPROPTYPECODE;

//
// Variables to store command line parameters
//

static BOOL             fHelp                           = FALSE;
static OPERATION        opOperation                     = OP_APPEND;
static CHAR             szFile          [MAX_PATH+1]    = {0};
static CHAR             szFolderPath    [MAX_PATH+1]    = {0};
static CHAR             szClass         [MAX_PATH+1]    = {0};
static CHAR             szProfile       [MAX_PATH+1]    = {0};
static BOOL             fSetRead                        = FALSE;
static BOOL             fEfd                            = FALSE;
static BOOL             fProgress                       = TRUE;

//
// Other Variables
//

static LPMAPISESSION    lpSession                       = NULL;
static LPMAPIFOLDER     lpFolder                        = NULL;
static LPSPropValue     rgMessageProps                  = NULL;
static ULONG            cCsvFileMessageProps            = 0;
static ULONG            cAllMessageProps                = 0;
static BOOL             fImportingAttachments           = FALSE;

#define                 MAX_CSV_FILE_LINE               1000
static FILE *           fpCsvFile                       = NULL;
static ULONG            iCsvLine                        = 0;
static BOOL             fCsvLineSaved                   = FALSE;
static CHAR             szCsvLine[MAX_CSV_FILE_LINE]    = {0};

// If cMessagesImported == DONT_REPORT_MSGS_IMPORTED then don't print 
// the number of messages imported.

#define                 DONT_REPORT_MSGS_IMPORTED       -1
static LONG             cMessagesImported               = DONT_REPORT_MSGS_IMPORTED;

//
// Function Declarations
//

static VOID PrintUsage(void);

static HRESULT HrPreParseCommandLine(
    IN int argc,
    IN char *argv[]);

static VOID PrintHelp(void);

static HRESULT HrParseCommandLine(
    IN int argc,
    IN char *argv[]);

static HRESULT HrCheckInfoCompleteness(void);

static HRESULT HrGetFolderFromPath(
    IN LPMAPISESSION lpSession, 
    IN LPSTR pszStoreFolderPath, 
    OUT LPMAPIFOLDER * lppFolder);

static HRESULT HrDoImport(void);

static HRESULT HrReadColumnHeaders(void);

static HRESULT HrProcessMessages(void);

static HRESULT HrParseMultiPropValue(
	IN ULONG            ulPropTag,
	IN LPTSTR           pszValueText,
	IN LPVOID           pBaseObject,
	OUT LPSPropValue    pProp);

static HRESULT HrParsePropValue(
	IN ULONG            ulPropTag,
	IN LPTSTR           pszValueText,
	IN LPVOID           pBaseObject,
	OUT LPSPropValue    pProp);

HRESULT HrCreateMessageAttachment(
	IN		LPMESSAGE	lpMsg,
	IN		LPSTR		lpszAttachPath);

static HRESULT HrStrAToStrWEx(
    IN  LPCSTR          lpszSource,
    IN  LPVOID          lpvBaseObject,
    OUT LPWSTR *        lppwszDest);

static HRESULT HrOpenCsvFile();

static HRESULT HrReadCsvSettings(void);

static HRESULT HrGetCsvLine(void);

static HRESULT HrUngetCsvLine(void);

static HRESULT HrCloseCsvFile(void);

//
// Inline Helper Functions
//

//$--SZ_BASE10------------------------------------------------------------------
//  Converts an integer to its decimal string equivalent.
//  For use as a parameter to EventLogMsg.
// -----------------------------------------------------------------------------
__inline static LPCTSTR SZ_BASE10(
    IN const INT iNumber)
{
    static TCHAR szTemp[16] = {0};
    return( (LPCTSTR)_itot( iNumber, szTemp, 10));
}

//$--SZ_BASE16------------------------------------------------------------------
//  Converts an integer to its hexidecimal string equivalent.
//  For use as a parameter to EventLogMsg.
// -----------------------------------------------------------------------------
__inline static LPCTSTR SZ_BASE16(
    IN const ULONG ulNumber)
{
    static TCHAR szTemp[16] = {0};
    return( (LPCTSTR)_itot( ulNumber, szTemp, 16));
}

//$--TRIM_WHITE_SPACE-----------------------------------------------------------
//  Trims white space from the front and back of a string.  Edits the string 
//  in place in the buffer.
// -----------------------------------------------------------------------------
__inline static VOID TRIM_WHITE_SPACE(
    IN OUT LPSTR psz)
{
    LPSTR pszSrc = psz;
    LPSTR pszDst = psz;
    LPSTR pszPlaceToNullTerminate = NULL;

    while (isspace(*pszSrc))
        pszSrc++;

    while (*pszSrc)
    {
        if (!isspace(*pszSrc))
            pszPlaceToNullTerminate = pszDst + 1;
        *pszDst++ = *pszSrc++;
    }

    if (pszPlaceToNullTerminate)
        *pszPlaceToNullTerminate = 0;
    else
        *pszDst = 0;
}

//
// Functions
//

//$--main-----------------------------------------------------------------------
//  Main function that performs folder import.
// -----------------------------------------------------------------------------
int main(                                   // RETURNS: exit code
    IN int argc,                            // number of args on command line
    IN char *argv[])                        // array of command line arguments
{
    HRESULT             hr                  = NOERROR;
    BOOL                fEventLogOpen       = FALSE;
    BOOL                fMAPIInitialized    = FALSE;
    BOOL                fCsvFileIsOpen      = FALSE;
    MAPIINIT_0          MapiInit            = {0};

    DEBUGPUBLIC("main()");

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

    // Do preliminary parsing of the command line (prints a message on failure).

    hr = HrPreParseCommandLine(argc, argv);
    if (FAILED(hr))
        goto cleanup;

    // If they requested help, then print a help message and exit.

    if (fHelp)
    {
        PrintHelp();
        goto cleanup;
    }

    // Parse the command line arguments (prints a message on failure).

    hr = HrParseCommandLine(argc, argv);
    if (FAILED(hr))
        goto cleanup;

    // Start reporting the number of messages imported after here.

    cMessagesImported = 0;

    // Initialize event logging.

    hr = HrEventOpenLog(
        TEXT("EDK FImport"), NULL, NULL, NULL, NULL, NULL);

    if (FAILED(hr))
    {
        fprintf(stderr, 
            "WARNING: unable to initialize event logging.\n");
        hr = NOERROR;
    }
    else
    {
        fEventLogOpen = TRUE;
    }

    // Open the .CSV file.

    hr = HrOpenCsvFile(szFile);
    if (FAILED(hr))
        goto cleanup;
    fCsvFileIsOpen = TRUE;

    // Initialize MAPI.

    MapiInit.ulVersion = MAPI_INIT_VERSION;

    hr = MAPIInitialize(&MapiInit);
    if (FAILED(hr))
    {
        EventLogMsg(
            FIMPORT_CANNOT_INIT_MAPI, 
            0, 
            0);
        goto cleanup;
    }
    fMAPIInitialized = TRUE;

    // Logon to MAPI.

    if (szProfile[0])
    {
	    // If a profile was given on the command line then 
        // log on to the specified profile.

	    hr = MAPILogonEx(
            0,
            szProfile,
            NULL,
            MAPI_NEW_SESSION | MAPI_EXPLICIT_PROFILE , //| MAPI_NO_MAIL,
            &lpSession);

	    if (FAILED(hr))
	    {
		    EventLogMsg(
			    FIMPORT_PROFILE_LOGON_ERROR,
			    2, szProfile, SZ_BASE16(hr),
                0);

            hr = HR_LOG(E_FAIL);
		    goto cleanup;
	    }
    }
    else
    {
	    // Otherwise, log onto the existing session.

	    hr = MAPILogonEx(
            0,
            szProfile,
            NULL,
            MAPI_ALLOW_OTHERS , //| MAPI_NO_MAIL,
            &lpSession);

	    if (FAILED(hr))
	    {
		    EventLogMsg(
			    FIMPORT_LOGON_ERROR,
			    1, SZ_BASE16(hr),
                0);

            hr = HR_LOG(E_FAIL);
		    goto cleanup;
	    }
    }

    // Read the first line from the .CSV file, which contains 
    // arguments like those on the command line.

    hr = HrReadCsvSettings();
    if (FAILED(hr))
        goto cleanup;

    // Parse the command line arguments again, so that command 
    // line arguments will override the first line of the file.

    hr = HrParseCommandLine(argc, argv);
    if (FAILED(hr))
    {
        // Don't report number of messages imported.
        cMessagesImported = DONT_REPORT_MSGS_IMPORTED;
        goto cleanup;
    }

    // Make sure we got all the information we need from the 
    // command line/.CSV file (prints a message on failure).

    hr = HrCheckInfoCompleteness();
    if (FAILED(hr))
    {
        // Don't report number of messages imported.
        cMessagesImported = DONT_REPORT_MSGS_IMPORTED;
        goto cleanup;
    }

    // Get a pointer to the folder.

    hr = HrGetFolderFromPath(lpSession, szFolderPath, &lpFolder);
    if (FAILED(hr))
        goto cleanup;

    // Import from the .CSV file to the folder.

    hr = HrDoImport();
    if (FAILED(hr))
        goto cleanup;

cleanup:

    // Close .CSV file.

    if (fCsvFileIsOpen)
    {
        (void) HrCloseCsvFile();
        fCsvFileIsOpen = FALSE;
    }

    // Print the number of events logged, then close event logging.

    if (fEventLogOpen)
    {
        HRESULT hrT = NOERROR;
        EDKEVENTCOUNT sEventCount = {0};

        hrT = HrEventGetCounts(&sEventCount);
        if (SUCCEEDED(hrT))
        {
            if (sEventCount.cError == 1)
            {
                fprintf(stderr, 
                    "ERROR: 1 error written to the event log.\n");
            }
            else if (sEventCount.cError)
            {
                fprintf(stderr, 
                    "ERROR: %d errors written to the event log.\n", 
                    sEventCount.cError);
            }

            if (sEventCount.cWarning == 1)
            {
                fprintf(stderr, 
                    "WARNING: 1 warning written to the event log.\n");
            }
            else if (sEventCount.cWarning)
            {
                fprintf(stderr, 
                    "WARNING: %d warnings written to the event log.\n", 
                    sEventCount.cWarning);
            }
        }

        (void) HrEventCloseLog();
        fEventLogOpen = FALSE;
    }

    // Print the number of messages imported.

    if (cMessagesImported != DONT_REPORT_MSGS_IMPORTED)
    {
        if (cMessagesImported == 1)
        {
            fprintf(stderr, "There was 1 message imported.\n");
        }
        else
        {
            fprintf(stderr, 
                "There were %d message(s) imported.\n", cMessagesImported);
        }
    }

    // Release MAPI objects and de-initialize MAPI.

    if (fMAPIInitialized)
    {
        ULRELEASE(lpFolder);
        ULRELEASE(lpSession);

        MAPIUninitialize();
        fMAPIInitialized = FALSE;
    }

    return(_nEcFromHr(hr));
}



//$--PrintUsage-----------------------------------------------------------------
//  Print information about how to use this program.
// -----------------------------------------------------------------------------
static VOID PrintUsage(void)                // RETURNS: nothing
{
    DEBUGPRIVATE("PrintUsage()");

    printf("USAGE: %s [Flags]\n\n", ARG_PROGRAM_NAME);
    printf("  [Flags]        Enter %s /%s for details\n", ARG_PROGRAM_NAME, 
        ARG_HELP1);
}



//$--HrPreParseCommandLine------------------------------------------------------
//  Does preliminary parsing of the command line that is needed to decide 
//  if /HELP was included.
// -----------------------------------------------------------------------------
static HRESULT HrPreParseCommandLine(       // RETURNS: HRESULT
    IN int argc,                            // number of args on command line
    IN char *argv[])                        // array of command line arguments
{
    HRESULT             hr                  = NOERROR;
    int                 i                   = 0;
    char *              pszArgument         = NULL;
    char *              pszValue            = NULL;

    DEBUGPRIVATE("HrPreParseCommandLine()");

    // Check parameters.

    hr = CHK_main(argc, argv);
    if (FAILED(hr))
        RETURN(hr);

    // Check for /? or /HELP.

    for (i = 1; i < argc; i++)
    {
        hr = _HrExpandCommandLineArgument(
            argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
            &pszArgument, &pszValue);

        if (SUCCEEDED(hr) && pszArgument && 
            (!_stricmp(pszArgument,ARG_HELP1) || 
             !_stricmp(pszArgument,ARG_HELP2)))
        {
            fHelp = TRUE;
            break;
        }
    }

    RETURN(NOERROR);
}



//$--PrintHelp------------------------------------------------------------------
//  Print information about the flags.
// -----------------------------------------------------------------------------
static VOID PrintHelp(void)                 // RETURNS: nothing
{
    DEBUGPRIVATE("PrintHelp()");

    printf("Folder Import sample.\n\n");
    printf("USAGE: %s [Flags]\n\n", ARG_PROGRAM_NAME);
    printf("  Flags\n");
    printf("  /FILE=         Filename of the .CSV file to import\n");
    printf("  /APPEND        The content of the .CSV file is appended to the folder\n");
    printf("  /UPDATE        The columns in the .CSV file replace the associated\n");
    printf("                 properties in the messages in the folder.  The replacement\n");
    printf("                 is carried out starting with the first message in the folder.\n");
    printf("  /REPLACE       The existing messages in the folder are replaced with the\n");
    printf("                 content of the .CSV file\n");
    printf("  /FOLDERPATH=   Path of the folder where messages will be placed\n");
    printf("  /CLASS=        Message class of the messages to place in the folder\n");
    printf("  /PROFILE=      Profile to log into message store\n");
    printf("  /[NO]SETREAD   Set the read flag on each new message\n");
    printf("  /[NO]EFD       Set the property MS_EXCHANGE_01=1 on each new message\n");
    printf("  /[NO]PROGRESS  Display progress dialog\n");
    printf("  /HELP or /?    Display help screen\n");
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
    HRESULT             hrT                 = NOERROR;
    int                 i                   = 0;
    char *              pszArgument         = NULL;
    char *              pszValue            = NULL;

    DEBUGPRIVATE("HrParseCommandLine()");

    // Check parameters.

    hr = CHK_main(argc, argv);
    if (FAILED(hr))
        RETURN(hr);

    for (i = 1; i < argc; i++)
    {
        hrT = _HrExpandCommandLineArgument(
            argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
            &pszArgument, &pszValue);

        if (hrT == EDK_E_NOT_FOUND)
        {
            fprintf(stderr, 
                "ERROR: unknown command line flag: %s\n", 
                argv[i]);
            hr = hrT;

            // Keep parsing to show all invalid flags.
        }

        else if (hrT == EDK_E_AMBIGUOUS)
        {
            fprintf(stderr, 
                "ERROR: ambiguous command line flag: %s\n", 
                argv[i]);
            hr = hrT;

            // Keep parsing to show all invalid flags.
        }

        else if (FAILED(hrT))
        {
            fprintf(stderr, 
                "ERROR: general error while parsing command line flag: %s\n", 
                argv[i]);
            hr = hrT;
            goto cleanup;
        }

        if (pszArgument)
        {
            // Put all the flags that do not take a value here.

            if (!_stricmp(pszArgument,ARG_APPEND))
            {
                opOperation = OP_APPEND;
            }
            else if (!_stricmp(pszArgument,ARG_UPDATE))
            {
                opOperation = OP_UPDATE;
            }
            else if (!_stricmp(pszArgument,ARG_REPLACE))
            {
                opOperation = OP_REPLACE;
            }
            else if (!_stricmp(pszArgument,ARG_SETREAD))
            {
                fSetRead = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOSETREAD))
            {
                fSetRead = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_EFD))
            {
                fEfd = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOEFD))
            {
                fEfd = FALSE;
            }
            else if (!_stricmp(pszArgument,ARG_PROGRESS))
            {
                fProgress = TRUE;
            }
            else if (!_stricmp(pszArgument,ARG_NOPROGRESS))
            {
                fProgress = FALSE;
            }

            // If we got this far we know it's a flag that requires a value, 
            // so if they didn't give one then it's an error.  We know it 
            // is a valid flag because pszArgument != NULL, and that means 
            // the flag is in the list.

            else if (pszValue == NULL)
            {
                fprintf(stderr, "ERROR: flag /%s requires a value\n", 
                    pszArgument);
                hr = HR_LOG(E_FAIL);
            }

            // Put all the flags that take a value here.

            else if (!_stricmp(pszArgument,ARG_FILE))
            {
                STRNCPY(szFile, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_FOLDERPATH))
            {
                STRNCPY(szFolderPath, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_CLASS))
            {
                STRNCPY(szClass, pszValue);
            }
            else if (!_stricmp(pszArgument,ARG_PROFILE))
            {
                STRNCPY(szProfile, pszValue);
            }
        }
    }

    // If any of the parsing failed then stop here.

    if (FAILED(hr))
        goto cleanup;

    // Make sure all required information has been given.

    if (szFile[0] == 0)
    {
        fprintf(stderr, "ERROR: please specify /%s\n", ARG_FILE);
        hr = HR_LOG(E_FAIL);
    }

cleanup:
    RETURN(hr);
}



//$--HrCheckInfoCompleteness----------------------------------------------------
//  Make sure that all required information has been given either on the 
//  command line or in the first line of the file.  If not, print an error 
//  message describing what is missing and return an error.
// -----------------------------------------------------------------------------
static HRESULT HrCheckInfoCompleteness(void) // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrCheckInfoCompleteness()");

    if (szFolderPath[0] == 0)
    {
        fprintf(stderr, 
            "ERROR: Folder Path must be specified on the command "
            "line or in the file.\n");
        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}



//$--HrGetFolderFromPath--------------------------------------------------------
//  Given a path string made up of the store name and folder, return a 
//  pointer to a MAPI folder object.
// -----------------------------------------------------------------------------
static HRESULT HrGetFolderFromPath(         // RETURNS: HRESULT
    IN  LPMAPISESSION   lpSession,          // current MAPI session
    IN  LPSTR           pszStoreFolderPath, // "storename\folderpath"
    OUT LPMAPIFOLDER *  lppFolder)          // folder pointer
{
    HRESULT             hr                  = NOERROR;
    LPSTR               pszStore            = NULL;
    ULONG               cchStore            = 0;
    LPSTR               pszFolderPath       = NULL;
    ULONG               cbEntryId           = 0;
    LPENTRYID           pEntryId            = NULL;
    LPMDB               pMdb                = NULL;
    ULONG               ulObjType           = 0;

    DEBUGPRIVATE("HrGetFolderFromPath()");

    // Check parameters.

    hr = CHK_HrGetFolderFromPath(
        lpSession, 
        pszStoreFolderPath, 
        lppFolder);

    if (FAILED(hr))
        RETURN(hr);

    // Find the first '\' in the folder path.  This separates the name 
    // of the store from the folder only path.  If there is no '\' then 
    // the path must be invalid.

    pszFolderPath = strchr(pszStoreFolderPath, '\\');

    if (pszFolderPath == NULL)
    {
		EventLogMsg(
			FIMPORT_INVALID_FOLDER_PATH,
			1, pszStoreFolderPath,
            0);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Allocate a separate piece of memory and copy the store name into it.

    cchStore = pszFolderPath - pszStoreFolderPath;

    hr = MAPIAllocateBuffer(
        cchStore + 1, 
        &pszStore);
    if (FAILED(hr))
    {
		EventLogMsg(
			FIMPORT_ERROR,
			0,
            1, ERROR_NOT_ENOUGH_MEMORY);
        goto cleanup;
    }

    strncpy(pszStore, pszStoreFolderPath, cchStore);
    pszStore[cchStore] = 0;

    TRIM_WHITE_SPACE(pszStore);

    // Set pszFolderPath to point to the folder path.

    pszFolderPath++;

    // Find the requested store, or the default store if 
    // they use the name "@DEFAULT".

    if (!stricmp(pszStore, "@DEFAULT"))
    {
        hr = HrMAPIFindDefaultMsgStore(
            lpSession, 
            &cbEntryId, 
            &pEntryId);
        if (FAILED(hr))
        {
		    EventLogMsg(
			    FIMPORT_CANNOT_FIND_DEFAULT_STORE,
			    1, SZ_BASE16(hr),
                0);
            goto cleanup;
        }
    }
    else
    {
        hr = HrMAPIFindStoreA(
            lpSession, 
            pszStore, 
            &cbEntryId, 
            &pEntryId);
        if (FAILED(hr))
        {
		    EventLogMsg(
			    FIMPORT_CANNOT_FIND_STORE,
			    2, pszStore, SZ_BASE16(hr),
                0);
            goto cleanup;
        }
    }

    // Open the requested store.

    hr = MAPICALL(lpSession)->OpenEntry(
        lpSession, 
        cbEntryId, 
        pEntryId, 
        NULL, 
        MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
        &ulObjType, 
        (LPUNKNOWN *)&pMdb);
    if (FAILED(hr))
    {
		EventLogMsg(
			FIMPORT_CANNOT_OPEN_STORE,
			2, pszStore, SZ_BASE16(hr),
            0);
        goto cleanup;
    }
    if (ulObjType != MAPI_STORE)
    {
		EventLogMsg(
			FIMPORT_WRONG_STORE_TYPE,
			2, pszStore, SZ_BASE16(ulObjType),
            0);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Open the folder indicated by the folder path.

    MAPIFREEBUFFER(pEntryId);
    cbEntryId = 0;

    hr = HrMAPIFindFolderExA(
        pMdb, 
        '\\', 
        pszFolderPath, 
        &cbEntryId, 
        &pEntryId);
    if (FAILED(hr))
    {
		EventLogMsg(
			FIMPORT_CANNOT_FIND_FOLDER,
			3, pszFolderPath, pszStore, SZ_BASE16(hr),
            0);
        goto cleanup;
    }

    hr = MAPICALL(lpSession)->OpenEntry(
        lpSession, 
        cbEntryId, 
        pEntryId, 
        NULL, 
        MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
        &ulObjType, 
        (LPUNKNOWN *)lppFolder);
    if (FAILED(hr))
    {
		EventLogMsg(
			FIMPORT_CANNOT_OPEN_FOLDER,
			3, pszFolderPath, pszStore, SZ_BASE16(hr),
            0);
        goto cleanup;
    }
    if (ulObjType != MAPI_FOLDER)
    {
		EventLogMsg(
			FIMPORT_WRONG_FOLDER_TYPE,
			3, pszFolderPath, pszStore, SZ_BASE16(ulObjType),
            0);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    MAPIFREEBUFFER(pEntryId);
    MAPIFREEBUFFER(pszStore);
    ULRELEASE(pMdb);

    RETURN(hr);
}



//$--HrDoImport-----------------------------------------------------------------
//  Import the messages from the .CSV file into the folder.
// -----------------------------------------------------------------------------
static HRESULT HrDoImport(void)             // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrDoImport()");

    // Read the column headers line from the .CSV file and use it 
    // to build an SPropValue array.

    hr = HrReadColumnHeaders();
    if (FAILED(hr))
        goto cleanup;

    // Read messages from the .CSV file and write them to the folder.

    hr = HrProcessMessages();
    if (FAILED(hr))
        goto cleanup;

cleanup:
    MAPIFREEBUFFER(rgMessageProps);
    RETURN(hr);
}



//$--HrReadColumnHeaders--------------------------------------------------------
//  Read the list of column headers from the next line of the .CSV file, 
//  and place the resulting properties in rgMessageProps.  Use PR_NULL 
//  for a column that says "ATTTACH".
// -----------------------------------------------------------------------------
static HRESULT HrReadColumnHeaders(void)    // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    ULONG               iToken              = 0;
    ULONG               cToken              = 0;
    LPSTR *             rgpszToken          = NULL;
    LPSTR               pszToken            = NULL;
    LPWSTR              pwszToken           = NULL;
    ULONG               ulNamedPropType     = 0;
	MAPINAMEID		    sNameID			    = {0};
	LPMAPINAMEID	    rglpNameID[1]	    = {&sNameID};
	LPSPropTagArray	    lpPropTags		    = NULL;
    ULONG               iGeneratedProp      = 0;

    DEBUGPRIVATE("HrReadColumnHeaders()");

    // Read a line from the file.

    hr = HrGetCsvLine();
    if (FAILED(hr))
    {
	    EventLogMsg(
		    FIMPORT_UNEXPECTED_END_OF_FILE, 
		    2, szFile, SZ_BASE10(iCsvLine), 
		    0);
	    goto cleanup;
    }

    // Break the line up into tokens separated by commas.  At the same time, 
    // count how many properties are in the line.

    hr = HrStrTokAll(
        szCsvLine, 
        ",", 
        &cToken, 
        &rgpszToken);
    if (FAILED(hr))
    {
        EventLogMsg(
            FIMPORT_INTERNAL_ERROR, 
            1, "HrStrTokAll", 
            0);
        goto cleanup;
    }

    // Calculate the number of properties, both the number coming from the 
    // .CSV file, as well as the number being generated in other ways 
    // (i.e. from /EFD and /CLASS).

    cCsvFileMessageProps = cToken;
    cAllMessageProps = cToken;
    iGeneratedProp = cToken;

    if (fEfd)
        cAllMessageProps++;

    if (szClass[0] != 0)
        cAllMessageProps++;

    // Allocate an SPropValue array big enough to hold all the properties.

    hr = MAPIAllocateBuffer(
        cAllMessageProps * sizeof(SPropValue), 
        &rgMessageProps);
    if (FAILED(hr))
    {
		EventLogMsg(
			EDKEVENT_ERROR, 
			0, 
			1, ERROR_OUTOFMEMORY);
		goto cleanup;
    }

    ZeroMemory(
        rgMessageProps, 
        cAllMessageProps * sizeof(SPropValue));

    // If they specified /EFD then we need to set the MS_EXCHANGE_01 
    // property on each message, so get/create the property tag 
    // for that property and add it at the end of the SPropValue array.

    if (fEfd)
    {
	    // Construct the MAPINAMEID.
	    sNameID.lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
	    sNameID.ulKind = MNID_STRING;
	    sNameID.Kind.lpwstrName = L"MS_EXCHANGE_01";

	    // Get the MS_EXCHANGE_01 property tag.

	    hr = MAPICALL(lpFolder)->GetIDsFromNames(
		    lpFolder, 
		    1, 
		    rglpNameID, 
		    MAPI_CREATE, 
		    &lpPropTags);
	    if (FAILED(hr))
		    goto cleanup;

        // Add the MS_EXCHANGE_01 property tag to the end of 
        // the SPropValue array.

        rgMessageProps[iGeneratedProp].ulPropTag = 
            CHANGE_PROP_TYPE(lpPropTags->aulPropTag[0], PT_LONG);
        rgMessageProps[iGeneratedProp].Value.ul = 1;

	    MAPIFREEBUFFER(lpPropTags);

        iGeneratedProp++;
    }

    // If the specified /CLASS then we need to set the PR_MESSAGE_CLASS 
    // property on each message, so add it at the end of the SPropValue array.

    if (szClass[0] != 0)
    {
        rgMessageProps[iGeneratedProp].ulPropTag = PR_MESSAGE_CLASS;
        rgMessageProps[iGeneratedProp].Value.lpszA = szClass;

        iGeneratedProp++;
    }

    // Loop to translate each column heading into a property id.

    for (iToken = 0; iToken < cToken; iToken++)
    {
        pszToken = rgpszToken[iToken];

        TRIM_WHITE_SPACE(pszToken);

        // If it's "ATTACH" then it must be an attachment, so use 
        // PR_NULL as a placeholder to indicate an attachment.

        if (!stricmp(pszToken, "ATTACH"))
        {
            rgMessageProps[iToken].ulPropTag = PR_NULL;
            fImportingAttachments = TRUE;
            continue;       // skip validity check for this property
        }

        // If it has a type on it like [M]<type_char>:<property_name> 
        // then it must be a named property.

        else if (
            (pszToken[0] != 0 && pszToken[1] == ':')
                || 
            (pszToken[0] != 0 && pszToken[1] != 0 && pszToken[2] == ':')
            )
        {
            // Get the property type from the prefix.

            ULONG   ulMVFlag = 0L;

            if( toupper(*pszToken) == PROPTYPECODE_MULTI)
            {
                ulMVFlag = MV_FLAG;
                pszToken++;
            }

            switch (toupper(*pszToken))
            {
            case PROPTYPECODE_LONG:
                ulNamedPropType = PT_LONG | ulMVFlag;
                break;

            case PROPTYPECODE_STRING:
                ulNamedPropType = PT_STRING8 | ulMVFlag;
                break;

            case PROPTYPECODE_SYSTIME:
                ulNamedPropType = PT_SYSTIME | ulMVFlag;
                break;

            case PROPTYPECODE_UNICODE:
                ulNamedPropType = PT_UNICODE | ulMVFlag;
                break;

            case PROPTYPECODE_BOOLEAN:
                ulNamedPropType = PT_BOOLEAN | ulMVFlag;
                break;

            case PROPTYPECODE_BINARY:
                ulNamedPropType = PT_BINARY | ulMVFlag;
                break;
            
            case PROPTYPECODE_GUID:
                ulNamedPropType = PT_CLSID | ulMVFlag;
                break;

            default:
                {
                    CHAR szTypePrefix[2] = {pszToken[0], 0};

                    EventLogMsg(
                        FIMPORT_INVALID_TYPE_PREFIX, 
                        4, szFile, SZ_BASE10(iCsvLine), szCsvLine, szTypePrefix, 
                        0);
                    goto cleanup;
                }
            }

            // Skip past explicit property type code and colon.

            pszToken += 2;

            // Convert the string to UNICODE so we can look up its property tag.

            hr = HrStrAToStrWEx(pszToken, rgpszToken, &pwszToken);
            if (FAILED(hr))
            {
                EventLogMsg(
                    FIMPORT_INTERNAL_ERROR, 
                    1, "HrStrAToStrWEx", 
                    0);
                goto cleanup;
            }

	        // Construct the MAPINAMEID.

	        sNameID.lpguid = (LPGUID)&PS_PUBLIC_STRINGS;
	        sNameID.ulKind = MNID_STRING;
	        sNameID.Kind.lpwstrName = pwszToken;

	        // Get the property tag.

	        hr = MAPICALL(lpFolder)->GetIDsFromNames(
		        lpFolder, 
		        1, 
		        rglpNameID, 
		        MAPI_CREATE, 
		        &lpPropTags);
	        if (FAILED(hr))
		        goto cleanup;

            // Add the property type to the property tag we got and 
            // store it in the array.

            rgMessageProps[iToken].ulPropTag = CHANGE_PROP_TYPE(
                lpPropTags->aulPropTag[0], 
                ulNamedPropType);

	        MAPIFREEBUFFER(lpPropTags);
        }

        // Otherwise it must be a normal property, so look up its 
        // property tag id in the table.

        else
        {
            // Get the property tag id from the name.

            hr = HrGetPropTagValue(
                pszToken, 
                &rgMessageProps[iToken].ulPropTag);
            if (FAILED(hr))
            {
                EventLogMsg(
                    FIMPORT_UNKNOWN_PROPERTY, 
                    4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszToken, 
                    0);
                goto cleanup;
            }

        }

        // Make sure the property type is one of the ones we support.

        switch (PROP_TYPE(rgMessageProps[iToken].ulPropTag))
        {
        case PT_BINARY:
        case PT_MV_BINARY:
        case PT_BOOLEAN:
        case PT_LONG:
        case PT_MV_LONG:
        case PT_STRING8:
        case PT_MV_STRING8:
        case PT_SYSTIME:
        case PT_UNICODE:
        case PT_MV_UNICODE:
        case PT_CLSID:
            // OK.
            break;

        default:
			EventLogMsg(
				FIMPORT_UNSUPPORTED_PROPERTY_TYPE, 
				4, szFile, SZ_BASE10(iCsvLine), szCsvLine, 
                    SZ_BASE16(rgMessageProps[iToken].ulPropTag), 
				0);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

cleanup:
    if (FAILED(hr))
    {
        MAPIFREEBUFFER(rgMessageProps);
    }
    MAPIFREEBUFFER(rgpszToken);
	MAPIFREEBUFFER(lpPropTags);
    RETURN(hr);
}



//$--HrProcessMessages----------------------------------------------------------
//  Read messages from the .CSV file and write them to the folder.
// -----------------------------------------------------------------------------
static HRESULT HrProcessMessages(void)      // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    ULONG               iToken              = 0;
    ULONG               cToken              = 0;
    LPSTR *             rgpszToken          = NULL;
    LPMESSAGE           pMsg                = NULL;
    LPSPropProblemArray pProblems           = NULL;
    LPMAPITABLE         lpContentsTable     = NULL;
    SizedSPropTagArray(1, sEntryIdOnly)     = {1, PR_ENTRYID};
    LPSRowSet           pFolderRow          = NULL;
    ULONG               ulObjType           = 0;
    BOOL                fUpdateMessages     = FALSE;
    LPMAPITABLE         pAttachmentTable    = NULL;
    LPSRowSet           pAttachments        = NULL;
    ULONG               iAttachment         = 0;

    DEBUGPRIVATE("HrProcessMessages()");

    // If they said /REPLACE then delete all the messages in the folder.

    if (opOperation == OP_REPLACE)
    {
        hr = MAPICALL(lpFolder)->EmptyFolder(
            lpFolder, 
            0, 
            NULL, 
            0);
        if (FAILED(hr))
        {
			EventLogMsg(
				FIMPORT_INTERNAL_ERROR, 
				1, "EmptyFolder", 
				0);
            goto cleanup;
        }
    }

    // If they said /UPDATE then open the folder's contents table.

    if (opOperation == OP_UPDATE)
    {
        // Open the table and set to get only the entry ids.

        hr = MAPICALL(lpFolder)->GetContentsTable(
            lpFolder, 
            MAPI_DEFERRED_ERRORS, 
            &lpContentsTable);
        if (FAILED(hr))
        {
			EventLogMsg(
				FIMPORT_INTERNAL_ERROR, 
				1, "GetContentsTable", 
				0);
            goto cleanup;
        }

        hr = MAPICALL(lpContentsTable)->SetColumns(
            lpContentsTable, 
            (LPSPropTagArray) &sEntryIdOnly, 
            0);
        if (FAILED(hr))
        {
			EventLogMsg(
				FIMPORT_INTERNAL_ERROR, 
				1, "SetColumns", 
				0);
            goto cleanup;
        }

        // Set the flag that shows we are updating messages.
        // (If we run out of messages to update, this flag will 
        // be set to false and we will then start creating new 
        // messages).

        fUpdateMessages = TRUE;
    }

    // Loop to import messages.

    while (TRUE)
    {
        // Read a line from the file.

        hr = HrGetCsvLine();

        // If we got an end of file then we're done.

        if (hr == EDK_E_END_OF_FILE)
        {
            hr = NOERROR;
            break;
        }

        if (FAILED(hr))
            goto cleanup;

        // Display a progress indicator.

        if (fProgress)
        {
            printf("\rImporting message %d...", cMessagesImported + 1);
        }

        // Break the line up into tokens separated by commas.

        hr = HrStrTokAll(
            szCsvLine, 
            ",", 
            &cToken, 
            &rgpszToken);
        if (FAILED(hr))
        {
            EventLogMsg(
                FIMPORT_INTERNAL_ERROR, 
                1, "HrStrTokAll", 
                0);
            goto cleanup;
        }

        // Make sure the number of properties in this line matches 
        // the number in the header line.

        if (cToken != cCsvFileMessageProps)
        {
            EventLogMsg(
                FIMPORT_WRONG_NUMBER_OF_PROPERTY_VALUES, 
                3, szFile, SZ_BASE10(iCsvLine), szCsvLine, 
                0);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // If we are updating messages then open the next message in the folder.

        if (fUpdateMessages)
        {
            // Get the next message entry id from the contents table.

            hr = MAPICALL(lpContentsTable)->QueryRows(
                lpContentsTable, 
                1, 
                0, 
                &pFolderRow);
            if (FAILED(hr))
            {
                EventLogMsg(
                    FIMPORT_INTERNAL_ERROR, 
                    1, "QueryRows", 
                    0);
                goto cleanup;
            }

            // If we got a message then open it.

            if (pFolderRow->cRows)
            {
                // Open the message.

                hr = MAPICALL(lpFolder)->OpenEntry(
                    lpFolder, 
                    pFolderRow->aRow[0].lpProps[0].Value.bin.cb, 
                    (LPENTRYID)pFolderRow->aRow[0].lpProps[0].Value.bin.lpb, 
                    NULL, 
                    MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
                    &ulObjType, 
                    (LPUNKNOWN *) &pMsg);
                if (FAILED(hr))
                {
		            EventLogMsg(
			            FIMPORT_INTERNAL_ERROR,
			            1, "OpenEntry",
                        0);
                    goto cleanup;
                }
                if (ulObjType != MAPI_MESSAGE)
                {
		            EventLogMsg(
			            FIMPORT_WRONG_MESSAGE_TYPE,
			            1, SZ_BASE16(ulObjType),
                        0);
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                // If we are importing attachments then clear 
                // out any old attachments in the message.

                if (fImportingAttachments)
                {
                    SizedSPropTagArray(1, sGetAttachNums) = {1, PR_ATTACH_NUM};

                    // Get the attachment numbers of all the attachments.

                    hr = MAPICALL(pMsg)->GetAttachmentTable(
                        pMsg, 
                        0, 
                        &pAttachmentTable);
                    if (FAILED(hr))
                    {
		                EventLogMsg(
			                FIMPORT_INTERNAL_ERROR,
			                1, "GetAttachmentTable",
                            0);
                        goto cleanup;
                    }

                    hr = HrQueryAllRows(
                        pAttachmentTable, 
                        (LPSPropTagArray) &sGetAttachNums, 
                        NULL, 
                        NULL, 
                        0, 
                        &pAttachments);
                    if (FAILED(hr))
                    {
		                EventLogMsg(
			                FIMPORT_INTERNAL_ERROR,
			                1, "HrQueryAllRows",
                            0);
                        goto cleanup;
                    }

                    // Delete them all.

                    for (
                        iAttachment = 0; 
                        iAttachment < pAttachments->cRows; 
                        iAttachment++)
                    {
                        hr = MAPICALL(pMsg)->DeleteAttach(
                            pMsg, 
                            pAttachments->aRow[iAttachment].lpProps[0].Value.ul, 
                            0, 
                            NULL, 
                            0);
                        if (FAILED(hr))
                        {
		                    EventLogMsg(
			                    FIMPORT_INTERNAL_ERROR,
			                    1, "DeleteAttach",
                                0);
                            goto cleanup;
                        }
                    }

                    ULRELEASE(pAttachmentTable);
                    MAPIFREEBUFFER(pAttachments);
                }
            }

            // If we ran out of messages then clear the flag 
            // and we will start creating them instead.

            else
                fUpdateMessages = FALSE;

            MAPIFREEBUFFER(pFolderRow);
        }

        // If we don't have a message yet then create one.

        if (pMsg == NULL)
        {
            hr = MAPICALL(lpFolder)->CreateMessage(
                lpFolder, 
                NULL, 
                MAPI_DEFERRED_ERRORS, 
                &pMsg);
            if (FAILED(hr))
            {
		        EventLogMsg(
			        FIMPORT_INTERNAL_ERROR,
			        1, "CreateMessage",
                    0);
                goto cleanup;
            }
        }

        // Loop to fill in values for each property.

        for (iToken = 0; iToken < cToken; iToken++)
        {
            // Clear the Value part of the SPropValue structure 
            // so we are sure there isn't any garbage left 
            // there from the previous pass through this loop.

            ZeroMemory(
                &(rgMessageProps[iToken].Value), 
                sizeof(rgMessageProps[iToken].Value));

            // If this "property" is really an attachment then add it 
            // to the message.

            if (rgMessageProps[iToken].ulPropTag == PR_NULL)
            {
                TRIM_WHITE_SPACE(rgpszToken[iToken]);

                hr = HrCreateMessageAttachment(
                    pMsg, 
                    rgpszToken[iToken]);
                if (FAILED(hr))
                    goto cleanup;
            }

            // Otherwise add the property to the SPropValue array.

            else
            {
                if( rgMessageProps[iToken].ulPropTag & MV_FLAG)
                    hr = HrParseMultiPropValue(
                        rgMessageProps[iToken].ulPropTag, 
                        rgpszToken[iToken], 
                        rgpszToken, 
                        &rgMessageProps[iToken]);
                else
                    hr = HrParsePropValue(
                        rgMessageProps[iToken].ulPropTag, 
                        rgpszToken[iToken], 
                        rgpszToken, 
                        &rgMessageProps[iToken]);
                if (FAILED(hr))
                    goto cleanup;
            }
        }

        // Set the properties on the message.

        hr = MAPICALL(pMsg)->SetProps(
            pMsg, 
            cAllMessageProps, 
            rgMessageProps, 
            &pProblems);
        if (FAILED(hr))
        {
		    EventLogMsg(
			    FIMPORT_INTERNAL_ERROR,
			    1, "SetProps",
                0);
            goto cleanup;
        }
		if (pProblems != NULL)
		{
		    EventLogMsg(
			    FIMPORT_PROBLEMS_SETTING_MESSAGE_PROPERTIES,
			    0,
                0);

			MAPIFREEBUFFER(pProblems);

            hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

        // Set or clear the read flag according to /SETREAD.

        hr = MAPICALL(pMsg)->SetReadFlag(
            pMsg, 
            fSetRead ? SUPPRESS_RECEIPT : CLEAR_READ_FLAG);
        if (FAILED(hr))
        {
		    EventLogMsg(
			    FIMPORT_INTERNAL_ERROR,
			    1, "SetReadFlag",
                0);
            goto cleanup;
        }

        // Save the changes to the message and release it.

        hr = MAPICALL(pMsg)->SaveChanges(pMsg, 0);
        if (FAILED(hr))
        {
		    EventLogMsg(
			    FIMPORT_INTERNAL_ERROR,
			    1, "SaveChanges",
                0);
            goto cleanup;
        }

        ULRELEASE(pMsg);

        // Increment the imported messages count.

        cMessagesImported++;

        // Free the allocated list of tokens.

        MAPIFREEBUFFER(rgpszToken);
    }

cleanup:
    // Clean up the progress indicator.

    if (fProgress && cMessagesImported)
    {
        printf("\r                                          \r");
    }

    // Free resources.
    ULRELEASE(pAttachmentTable);
    ULRELEASE(lpContentsTable);
    ULRELEASE(pMsg);
    MAPIFREEBUFFER(pAttachments);
    MAPIFREEBUFFER(pFolderRow);
    MAPIFREEBUFFER(rgpszToken);
    MAPIFREEBUFFER(pProblems);
    RETURN(hr);
}

//$--HrParseMultiPropValue-------------------------------------------------------
//  Takes a text version of a multi-valued property and fills in an SPropValue 
//  structure.  If memory needs to be allocated, it is allocated using 
//  MAPIAllocateMore() based on the object passed in pBaseObject.
// -----------------------------------------------------------------------------
static HRESULT HrParseMultiPropValue(       // RETURNS: HRESULT
	IN ULONG            ulPropTag,          // property tag of this property
	IN LPTSTR           pszValueText,       // text of property value to parse
	IN LPVOID           pBaseObject,        // base object for MAPIAllocateMore()
	OUT LPSPropValue    pProp)              // structure to write results
{
	HRESULT             hr                  = NOERROR;
    ULONG               cToken              = 0L;
    LPTSTR*             rgpszToken          = NULL;
    SPropValue          pvaSingleProp       = {0};
    ULONG               i;  // loop

	DEBUGPRIVATE("HrParseMultiPropValue()");

	hr = CHK_HrParseMultiPropValue(
		ulPropTag, 
		pszValueText, 
		pBaseObject, 
		pProp);
	if (FAILED(hr))
		RETURN(hr);

    hr = HrStrTokAll(
        pszValueText, 
        "%", 
        &cToken, 
        &rgpszToken);
    if (FAILED(hr))
    {
        EventLogMsg(
            FIMPORT_INTERNAL_ERROR, 
            1, "HrStrTokAll", 
            0);
        goto cleanup;
    }

    for( i=0; i<cToken; i++)
    {
        hr = HrParsePropValue(
            ulPropTag & ~MV_FLAG,
            rgpszToken[i],
            pBaseObject,
            (LPSPropValue)&pvaSingleProp);
        if( FAILED (hr))
        {
            goto cleanup;
        }

        switch (PROP_TYPE(ulPropTag))
	    {
            // PT_MV_BINARY

		    case PT_MV_BINARY:
		    {
                if( !pProp->Value.MVbin.lpbin)
                {
                    hr = MAPIAllocateMore( cToken * sizeof(SBinary), pBaseObject, &pProp->Value.MVbin.lpbin);
			        if (FAILED(hr))
			        {
				        EventLogMsg(
					        EDKEVENT_ERROR, 
					        0, 
					        1, ERROR_OUTOFMEMORY);
				        goto cleanup;
			        }

                    pProp->Value.MVbin.cValues = cToken;
                }

                // Relocate single value to MV property array

                pProp->Value.MVbin.lpbin[i].cb  = pvaSingleProp.Value.bin.cb;
                pProp->Value.MVbin.lpbin[i].lpb = pvaSingleProp.Value.bin.lpb;

			    break;
		    }

            // PT_MV_LONG

		    case PT_MV_LONG:
            {
                if( !pProp->Value.MVl.lpl)
                {
                    hr = MAPIAllocateMore( cToken * sizeof(LONG), pBaseObject, &pProp->Value.MVl.lpl);
			        if (FAILED(hr))
			        {
				        EventLogMsg(
					        EDKEVENT_ERROR, 
					        0, 
					        1, ERROR_OUTOFMEMORY);
				        goto cleanup;
			        }

                    pProp->Value.MVl.cValues = cToken;
                }

                // Relocate single value to MV property array

                pProp->Value.MVl.lpl[i] = pvaSingleProp.Value.l;

			    break;
            }

            // PT_MV_STRING8

		    case PT_MV_STRING8:
		    {
                if( !pProp->Value.MVszA.lppszA)
                {
                    hr = MAPIAllocateMore( cToken * sizeof(LPSTR), pBaseObject, (PVOID*)&pProp->Value.MVszA.lppszA);
			        if (FAILED(hr))
			        {
				        EventLogMsg(
					        EDKEVENT_ERROR, 
					        0, 
					        1, ERROR_OUTOFMEMORY);
				        goto cleanup;
			        }

                    pProp->Value.MVszA.cValues = cToken;
                }

                // Relocate single value to MV property array

                pProp->Value.MVszA.lppszA[i] = pvaSingleProp.Value.lpszA;

			    break;
		    }

            // PT_MV_UNICODE

		    case PT_MV_UNICODE:
		    {
                if( !pProp->Value.MVszW.lppszW)
                {
                    hr = MAPIAllocateMore( cToken * sizeof(LPWSTR), pBaseObject, (PVOID*)&pProp->Value.MVszW.lppszW);
			        if (FAILED(hr))
			        {
				        EventLogMsg(
					        EDKEVENT_ERROR, 
					        0, 
					        1, ERROR_OUTOFMEMORY);
				        goto cleanup;
			        }

                    pProp->Value.MVszW.cValues = cToken;
                }

                // Relocate single value to MV property array

                pProp->Value.MVszW.lppszW[i] = pvaSingleProp.Value.lpszW;

			    break;
		    }

            // Non-Supported Property Types

		    default:
		    {
			    hr = HR_LOG(E_NOTIMPL);
			    EventLogMsg(
				    FIMPORT_UNSUPPORTED_PROPERTY_TYPE, 
				    4, szFile, SZ_BASE10(iCsvLine), szCsvLine, SZ_BASE16(PROP_TYPE(ulPropTag)), 
				    0);
			    goto cleanup;
		    }
	    } // switch
    }   // for

	pProp->ulPropTag = ulPropTag;

cleanup:
	RETURN(hr);
}



//$--HrParsePropValue-----------------------------------------------------------
//  Takes a text version of a property value and fills in an SPropValue 
//  structure.  If memory needs to be allocated, it is allocated using 
//  MAPIAllocateMore() based on the object passed in pBaseObject.
//
//  Valid property value formats for property types are as follows (and do 
//  not include the quotes):
//
//  PT_BINARY   a series of two digit hex numbers separated by spaces
//              (e.g. "01 fe 2a 00 1c")
//
//  PT_BOOLEAN  the value 1 or 0 (1=True, 0=False)
//
//  PT_LONG     a decimal or hex constant (e.g. "127" or "0x0fff0003")
//
//  PT_STRING8  any string of characters (e.g. "Exchange is fun!")
//
//  PT_SYSTIME  a date in the format "yyyy/mm/dd hh:mm:ss" 
//              (e.g. "1995/12/31 23:59:59")
//
//  PT_CLSID    fully formatted GUID (e.g. "{########-####-####-####-############}"
//              where '#' is any hex digit)
// 
// -----------------------------------------------------------------------------
static HRESULT HrParsePropValue(            // RETURNS: HRESULT
	IN ULONG            ulPropTag,          // property tag of this property
	IN LPTSTR           pszValueText,       // text of property value to parse
	IN LPVOID           pBaseObject,        // base object for MAPIAllocateMore()
	OUT LPSPropValue    pProp)              // structure to write results
{
	HRESULT             hr                  = NOERROR;
	LPTSTR              psz                 = NULL;
	LPTSTR              pszPrev             = NULL;

	DEBUGPRIVATE("HrParsePropValue()");

	hr = CHK_HrParsePropValue(
		ulPropTag, 
		pszValueText, 
		pBaseObject, 
		pProp);
	if (FAILED(hr))
		RETURN(hr);

	switch (PROP_TYPE(ulPropTag))
	{
        // PT_BINARY

		case PT_BINARY:
		{
			ULONG cb = 0;
			ULONG ib = 0;
			LPBYTE pb = NULL;
			LONG lNumber = 0;

			// Count the bytes and check that all the bytes are valid.

			psz = pszValueText;
			while (*psz)
			{
				if (isspace(*psz))
					psz++;
				else
				{
					pszPrev = psz;
					lNumber = strtol(psz, &psz, 16);
					if (psz == pszPrev || lNumber > UCHAR_MAX || lNumber < 0)
		            {
					    hr = HR_LOG(E_FAIL);
					    EventLogMsg(
						    FIMPORT_ILLEGAL_BINARY_VALUE, 
						    4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszValueText, 
						    0);
					    goto cleanup;
		            }
					cb++;
				}
			}

			// Allocate a buffer big enough for the number of bytes.

			hr = MAPIAllocateMore(cb, pBaseObject, &pProp->Value.bin.lpb);
			if (FAILED(hr))
			{
				EventLogMsg(
					EDKEVENT_ERROR, 
					0, 
					1, ERROR_OUTOFMEMORY);
				goto cleanup;
			}
			pProp->Value.bin.cb = cb;

			// Write the bytes into the buffer.

			psz = pszValueText;
			for (ib = 0, pb = pProp->Value.bin.lpb; ib < cb; ib++, pb++)
			{
				*pb = (BYTE)strtol(psz, &psz, 16);
			}

			break;
		}

        // PT_CLSID

		case PT_CLSID:
		{
            CLSID     clsidTemp;
            LPOLESTR  pwszValueText;
            
            hr = HrStrToStrW( pszValueText, &pwszValueText);
            if( FAILED( hr))
                goto cleanup;

            hr = CLSIDFromString( pwszValueText, &clsidTemp);

            MAPIFREEBUFFER( pwszValueText);

            if( FAILED( hr))
            {
				EventLogMsg(
					FIMPORT_ILLEGAL_GUID_VALUE, 
					4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszValueText, 
					0);
				goto cleanup;
			}

			// Allocate a buffer big enough for a GUID.

			hr = MAPIAllocateMore(sizeof(GUID), pBaseObject, &pProp->Value.lpguid);
			if (FAILED(hr))
			{
				EventLogMsg(
					EDKEVENT_ERROR, 
					0, 
					1, ERROR_OUTOFMEMORY);
				goto cleanup;
			}

			// Write the bytes into the buffer.

			CopyMemory( pProp->Value.lpguid, &clsidTemp, sizeof( GUID));

			break;
		}

        // PT_BOOLEAN

		case PT_BOOLEAN:
        {
	        psz = pszValueText;

	        while (isspace(*psz))
		        psz++;

	        pszPrev = psz;
			pProp->Value.l = strtol(psz, &psz, 0);

	        while (isspace(*psz))
		        psz++;

	        if (psz == pszPrev || *psz || 
		        (pProp->Value.l != 0 && pProp->Value.l != 1))
	        {
			    hr = HR_LOG(E_FAIL);
			    EventLogMsg(
				    FIMPORT_ILLEGAL_BOOLEAN_VALUE, 
					4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszValueText, 
				    0);
				    goto cleanup;
	        }
		    break;
        }

        // PT_LONG

		case PT_LONG:
        {
	        psz = pszValueText;

	        while (isspace(*psz))
		        psz++;

	        pszPrev = psz;
			pProp->Value.l = strtol(psz, &psz, 0);

	        while (isspace(*psz))
		        psz++;

	        if (psz == pszPrev || *psz)
	        {
			    hr = HR_LOG(E_FAIL);
			    EventLogMsg(
				    FIMPORT_ILLEGAL_LONG_VALUE, 
					4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszValueText, 
				    0);
			    goto cleanup;
	        }
			break;
        }

        // PT_STRING8

		case PT_STRING8:
		{
			ULONG cb = cbStrLenA(pszValueText);

			hr = MAPIAllocateMore(cb, pBaseObject, &pProp->Value.lpszA);
			if (FAILED(hr))
			{
			    hr = HR_LOG(E_FAIL);
				EventLogMsg(
					EDKEVENT_ERROR, 
					0, 
					1, ERROR_OUTOFMEMORY);
				goto cleanup;
			}
			CopyMemory(pProp->Value.lpszA, pszValueText, cb);
			break;
		}

        // PT_UNICODE

		case PT_UNICODE:
		{
            hr = HrStrAToStrWEx(
                pszValueText, 
                pBaseObject, 
                &pProp->Value.lpszW);
			if (FAILED(hr))
			{
			    hr = HR_LOG(E_FAIL);
				EventLogMsg(
					EDKEVENT_ERROR, 
					0, 
					1, ERROR_OUTOFMEMORY);
				goto cleanup;
			}
			break;
		}

        // PT_SYSTIME

		case PT_SYSTIME:
		{
			SYSTEMTIME st = {0};
	        CHAR chBogus = 0;
			int lReturn = 0;
			BOOL fItWorked = TRUE;

			lReturn = sscanf(
				pszValueText, 
				" %hd/%hd/%hd %hd:%hd:%hd %c", 
				&st.wYear, 
				&st.wMonth, 
				&st.wDay, 
				&st.wHour, 
				&st.wMinute, 
				&st.wSecond, 
				&chBogus);
			if (lReturn == 0 || lReturn == EOF || chBogus)
			{
				hr = HR_LOG(E_FAIL);
				EventLogMsg(
					FIMPORT_ILLEGAL_SYSTIME_VALUE, 
					4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszValueText, 
					0);
				goto cleanup;
			}

			fItWorked = SystemTimeToFileTime(&st, &pProp->Value.ft);
			if (!fItWorked)
			{
				hr = HR_LOG(E_FAIL);
				EventLogMsg(
					FIMPORT_INTERNAL_ERROR, 
					1, "SystemTimeToFileTime", 
					0);
				goto cleanup;
			}

			break;
		}

        // Non-Supported Property Types

		default:
		{
			hr = HR_LOG(E_NOTIMPL);
			EventLogMsg(
				FIMPORT_UNSUPPORTED_PROPERTY_TYPE, 
				4, szFile, SZ_BASE10(iCsvLine), szCsvLine, SZ_BASE16(ulPropTag), 
				0);
			goto cleanup;
		}
	}

	pProp->ulPropTag = ulPropTag;

cleanup:
	RETURN(hr);
}



//$--HrCreateMessageAttachment-----------------------------------------------
//
// DESCRIPTION: Create a message attachment and write the contents of the
//				specified file to it.  Also create various required properties
//				for the message attachment.
//
// INPUT:
//
//		[lpMsg]			-- Message for which attachment is to be created.
//		[lpszAttachPath]-- Path of file containing attachment text.
//
// RETURNS: HRESULT --  NOERROR if O.K., 
//                      E_INVALIDARG if invalid parameter,
//                      E_OUTOFMEMORY if memory problems,
//                      E_FAIL if call fails
//
//---------------------------------------------------------------------------


HRESULT HrCreateMessageAttachment(          // RETURNS: HRESULT
	IN		LPMESSAGE	lpMsg,              // MAPI message pointer
	IN		LPSTR		lpszAttachPath      // list of attachment file names
	)
{
    HRESULT         hr              =   NOERROR;    // return code
	ULONG			cb              =   0;
	LPATTACH		lpAttach        =	NULL;
	ULONG			ulAttachmentNum =   0;
    ULONG           nAttachments    =   0;      // # of attachments
    ULONG           iAttach         =   0;      // attachment index
    LPSTR           lpszCurrent     =   NULL;   // current attachment
	LPSTR *			lppszAttachTok	=	NULL;	// array of tokenized attachments

    // MAPI property creation flags.    
    const ULONG     ulFlags     =   MAPI_CREATE | MAPI_MODIFY | 
                                    MAPI_DEFERRED_ERRORS;   // reduces RPCs

    // # of attachment properties
    #define CVALUES 3

    // property value array
    SPropValue      aPropVals[CVALUES]  =   {0};

    DEBUGPRIVATE("HrCreateMessageAttachment()");

    // Check input parameters
    hr = CHK_HrCreateMessageAttachment(lpMsg, lpszAttachPath);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Determine number of attachments by breaking into tokens
	hr = HrStrTokAll(
		lpszAttachPath,			// file name list
		";",	                // separator character
		&nAttachments,			// # of file names
		&lppszAttachTok);		// array of strings pointer
    if (FAILED(hr))
    {
        EventLogMsg(
            FIMPORT_INTERNAL_ERROR, 
            1, "HrStrTokAll", 
            0);
        goto cleanup;
    }

    ASSERTERROR((nAttachments != 0), "Bad nAttachments");
	ASSERT_READ_PTR(lppszAttachTok, sizeof(LPSTR) * nAttachments, 
		"Bad lppszAttachTok");

    // Process each attachment.
    for ( iAttach = 0; iAttach < nAttachments; iAttach++ )
    {
	    // Create required additional properties.
		LPSPropProblemArray	lpProblems 		=	NULL;
		LPSTR				lpszFileName    =   NULL;

        // Release MAPI objects
	    ULRELEASE(lpAttach);

		// Retrieve next attachment
		lpszCurrent = lppszAttachTok[iAttach];

		ASSERT_STRINGA_PTR(lpszCurrent, "Bad lpszCurrent");

	    // Create the attachment in the message.
	    hr = MAPICALL(lpMsg)->CreateAttach(lpMsg, 
                             NULL,
							 MAPI_DEFERRED_ERRORS,  // reduces RPCs
							 &ulAttachmentNum,
							 &lpAttach);
        if (FAILED(hr))
        {
            EventLogMsg(
                FIMPORT_INTERNAL_ERROR, 
                1, "IMessage::CreateAttach()", 
                0);
            goto cleanup;
        }

        ASSERT_IUNKNOWN_PTR(lpAttach, "Bad lpAttach");
        	
		aPropVals[0].ulPropTag =	PR_ATTACH_METHOD;
		aPropVals[0].Value.l =		ATTACH_BY_VALUE;

		lpszFileName = strrchr(lpszCurrent, '\\');

		if (!lpszFileName)
			lpszFileName = lpszCurrent;
		else
			lpszFileName++;	// Advance past the backslash.

		// CAVEAT - We don't do anything here to check for 
        // invalid FAT 8.3 names.
		aPropVals[1].ulPropTag =	PR_ATTACH_FILENAME;
		aPropVals[1].Value.lpszA =	lpszFileName;

		aPropVals[2].ulPropTag =	PR_ATTACH_LONG_FILENAME;
		aPropVals[2].Value.lpszA =	lpszFileName;

		hr = MAPICALL(lpAttach)->SetProps(lpAttach, 
            CVALUES, 
            aPropVals, 
            &lpProblems);
        if (FAILED(hr))
        {
            EventLogMsg(
                FIMPORT_INTERNAL_ERROR, 
                1, "IMAPIProp::SetProps()", 
                0);
            goto cleanup;
        }

		if (lpProblems != NULL)
		{
		    EventLogMsg(
			    FIMPORT_PROBLEMS_SETTING_MESSAGE_PROPERTIES,
			    0,
                0);

			MAPIFREEBUFFER(lpProblems);

            hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

        // Create the PR_ATTACH_DATA_BIN property from the attachment
        // file text.
        hr = HrMAPISetPropFromFile(
            (LPMAPIPROP) lpAttach,  // pointer to attachment object
            PR_ATTACH_DATA_BIN,     // property tag
            lpszCurrent,            // fully-pathed file name from which to read data
            &cb);                   // # bytes read in
        if (FAILED(hr))
        {
            EventLogMsg(
                FIMPORT_CANNOT_ADD_ATTACHMENT, 
					4, szFile, SZ_BASE10(iCsvLine), szCsvLine, lpszCurrent, 
                0);
            goto cleanup;
        }

	    // Commit the attachment changes.
	    hr = MAPICALL(lpAttach)->SaveChanges(lpAttach, 0);
        if (FAILED(hr))
        {
            EventLogMsg(
                FIMPORT_INTERNAL_ERROR, 
                1, "IMAPIProp::SaveChanges()", 
                0);
            goto cleanup;
        }
    }   // end for each attachment

    // we are done

cleanup:

    // Release MAPI and OLE objects
	ULRELEASE(lpAttach);

	// Free MAPI buffers
	MAPIFREEBUFFER(lppszAttachTok);

	RETURN(hr);

}



//$--HrStrAToStrWEx-------------------------------------------------------------
//  Convert a byte string to a word string.  The resulting string is placed in 
//  a buffer allocated using MAPIAllocateBuffer if lpvBaseObject == NULL, 
//  or MAPIAllocateMore if lpvBaseObject != NULL.
// -----------------------------------------------------------------------------
static HRESULT HrStrAToStrWEx(
    IN  LPCSTR          lpszSource,     // source string
    IN  LPVOID          lpvBaseObject,  // base object for MAPIAllocateMore
    OUT LPWSTR *        lppwszDest)     // destination string
{
    HRESULT             hr              = NOERROR;
    LONG                cchDest         = 0;
    LPWSTR              lpwszDest       = NULL;

    DEBUGPUBLIC("HrStrAToStrWEx()");

    hr = CHK_HrStrAToStrWEx(lpszSource, lpvBaseObject, lppwszDest);
    if (FAILED(hr))
        RETURN(hr);

    // Compute the number of word characters needed for the destination buffer.

    if (*lpszSource)
    {
        cchDest = MultiByteToWideChar(
            CP_ACP, 
            MB_PRECOMPOSED, 
            lpszSource, 
            strlen(lpszSource), 
            NULL, 
            0);
        if (cchDest == 0)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    // Allocate the destination string buffer.

    if (lpvBaseObject == NULL)
    {
        hr = MAPIAllocateBuffer(
            (cchDest + 1) * sizeof(WCHAR), 
            &lpwszDest);
    }
    else
    {
        hr = MAPIAllocateMore(
            (cchDest + 1) * sizeof(WCHAR), 
            lpvBaseObject, 
            &lpwszDest);
    }

    if (FAILED(hr))
        goto cleanup;

    // Convert from byte string to word string.

    if (*lpszSource)
    {
        cchDest = MultiByteToWideChar(
            CP_ACP, 
            MB_PRECOMPOSED, 
            lpszSource, 
            strlen(lpszSource), 
            lpwszDest, 
            cchDest);
        if (cchDest == 0)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
    lpwszDest[cchDest] = 0;

    // Store in output parameter.

    *lppwszDest = lpwszDest;

cleanup:
    if (FAILED(hr))
    {
        MAPIFREEBUFFER(lpwszDest);
    }

    RETURN(hr);
}



//
// File Access Routines
//

// The import source may be changed from a file to some other 
// source by replacing the following routines.



//$--HrOpenCsvFile--------------------------------------------------------------
//  Open the .CSV file and prepare to read lines from it.
// -----------------------------------------------------------------------------
static HRESULT HrOpenCsvFile(void)          // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrOpenCsvFile()");

    // Open the file.

    fpCsvFile = fopen(szFile, "r");
    if (fpCsvFile == NULL)
    {
        EventLogMsg(
            FIMPORT_CANNOT_OPEN_IMPORT_FILE, 
            1, szFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Reset the line number counter.

    iCsvLine = 0;
    fCsvLineSaved = FALSE;

cleanup:
    RETURN(hr);
}



//$--HrReadCsvSettings----------------------------------------------------------
//  Read the settings information from the .CSV file.
// -----------------------------------------------------------------------------
static HRESULT HrReadCsvSettings(void)      // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    ULONG               iToken              = 0;
    ULONG               cToken              = 0;
    LPSTR *             rgpszToken          = NULL;
    LPSTR               pszKeyword          = NULL;
    LPSTR               pszValue            = NULL;
    FILECOMMAND         fcCommand           = 0;

    DEBUGPRIVATE("HrReadCsvSettings()");

    // Read a line from the file.

    hr = HrGetCsvLine();
    if (FAILED(hr))
        goto cleanup;

    // Break the line up into tokens separated by commas.

    hr = HrStrTokAll(
        szCsvLine, 
        ",", 
        &cToken, 
        &rgpszToken);
    if (FAILED(hr))
    {
        EventLogMsg(
            FIMPORT_INTERNAL_ERROR, 
            1, "HrStrTokAll", 
            0);
        goto cleanup;
    }

    // If the first token is not "COMMAND" then the file does 
    // not contain a settings line.

    TRIM_WHITE_SPACE(rgpszToken[0]);
    if (cToken == 0 || stricmp(rgpszToken[0], "COMMAND"))
    {
        hr = HrUngetCsvLine();
        goto cleanup;
    }

    // Parse each token and store the resulting setting into 
    // the appropriate variable.

    for (iToken = 1; iToken < cToken; iToken++)
    {
        // Break each token into keyword and value, separated 
        // by an equals sign.

        pszKeyword = rgpszToken[iToken];
        pszValue = strchr(pszKeyword, '=');
        if (pszValue)
            *pszValue++ = 0;
        TRIM_WHITE_SPACE(pszKeyword);

        // Try to match the keyword to a valid command.

        hr = _HrFindArrayValue(
            pszKeyword, 
            rgpszFileCommandArray, 
            ARRAY_CNT(rgpszFileCommandArray), 
            &fcCommand);

        if (FAILED(hr))
        {
            if (hr == EDK_E_NOT_FOUND)
            {
                EventLogMsg(
                    FIMPORT_INVALID_KEYWORD, 
                    4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszKeyword, 
                    0);
            }
            else if (hr == EDK_E_AMBIGUOUS)
            {
                EventLogMsg(
                    FIMPORT_AMBIGUOUS_KEYWORD, 
                    4, szFile, SZ_BASE10(iCsvLine), szCsvLine, pszKeyword, 
                    0);
            }
            else
            {
                EventLogMsg(
                    FIMPORT_INTERNAL_ERROR, 
                    1, "_HrFindArrayValue", 
                    0);
            }

            goto cleanup;
        }

        // Set the setting variable for this keyword.

        switch (fcCommand)
        {
        case FILECOMMAND_APPEND:
            opOperation = OP_APPEND;
            break;

        case FILECOMMAND_UPDATE:
            opOperation = OP_UPDATE;
            break;

        case FILECOMMAND_REPLACE:
            opOperation = OP_REPLACE;
            break;

        case FILECOMMAND_FOLDERPATH:
            STRNCPY(szFolderPath, pszValue);
            break;

        case FILECOMMAND_CLASS:
            STRNCPY(szClass, pszValue);
            break;

        case FILECOMMAND_SETREAD:
            fSetRead = TRUE;
            break;

        case FILECOMMAND_NOSETREAD:
            fSetRead = FALSE;
            break;

        case FILECOMMAND_EFD:
            fEfd = TRUE;
            break;

        case FILECOMMAND_NOEFD:
            fEfd = FALSE;
            break;
        
        default:
            EventLogMsg(
                FIMPORT_INTERNAL_ERROR, 
                1, "switch (fcCommand)", 
                0);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    } // end for

cleanup:
    MAPIFREEBUFFER(rgpszToken);

    RETURN(hr);
}



//$--HrGetCsvLine---------------------------------------------------------------
//  Read a line from the .CSV file into szCsvLine.  Setting fCsvLineSaved 
//  == TRUE acts as an "unget", and causes the current contents of szCsvLine 
//  to be used the next time this routine is called.
//
//  HrGetCsvLine automatically skips empty lines.
//
//  Returns:    NOERROR             = success
//              EDK_E_END_OF_FILE   = end of file
//              E_FAIL              = error
// -----------------------------------------------------------------------------
static HRESULT HrGetCsvLine(void)           // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    int                 ch                  = 0;
    int                 cMatch              = 0;
    char *              pszResult           = NULL;
    int                 cchCsvLine          = 0;

    DEBUGPRIVATE("HrGetCsvLine()");

    // Loop until we get a line we can use.

    do
    {
        // If we have a line saved from last time then just use that one.

        if (fCsvLineSaved)
            fCsvLineSaved = FALSE;

        // Otherwise read another line from the file.

        else
        {
            pszResult = 
                fgets(szCsvLine, sizeof(szCsvLine) - 1, fpCsvFile);
            if (pszResult == NULL)
            {
                if (ferror(fpCsvFile))
                {
                    EventLogMsg(
                        FIMPORT_CANNOT_READ_IMPORT_FILE, 
                        1, szFile, 
                        1, _doserrno);
                    hr = HR_LOG(E_FAIL);
                }
                else
                {
                    hr = EDK_E_END_OF_FILE;
                }

                goto cleanup;
            }

            // Increment the line number.

            iCsvLine++;

            // Strip newline from end of line.

            cchCsvLine = strlen(szCsvLine);
            if (cchCsvLine && szCsvLine[cchCsvLine - 1] == '\n')
                szCsvLine[cchCsvLine - 1] = 0;
            else
            {
                EventLogMsg(
                    FIMPORT_IMPORT_LINE_TOO_LONG, 
                    3, szFile, SZ_BASE10(iCsvLine), 
                        szCsvLine, 
                    0);
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        // Get the first non-whitespace character in the line so we 
        // can make sure it isn't a blank line.

        cMatch = sscanf(szCsvLine, " %c", &ch);
    }
    while (cMatch != 1);

cleanup:
    RETURN(hr);
}



//$--HrUngetCsvLine-------------------------------------------------------------
//  Push the current line back on the input stream so that it will be 
//  returned by the next call to HrGetCsvLine.
// -----------------------------------------------------------------------------
static HRESULT HrUngetCsvLine(void)         // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;

    DEBUGPRIVATE("HrUngetCsvLine()");

    // Make sure that there isn't already another saved line and 
    // that we have read at least one line from the file.

    if (fCsvLineSaved || iCsvLine == 0)
    {
        EventLogMsg(
            FIMPORT_INTERNAL_ERROR, 
            1, "HrUngetCsvLine", 
            0);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Set the flag to "unget" the current line.

    fCsvLineSaved = TRUE;

cleanup:
    RETURN(hr);
}



//$--HrCloseCsvFile-------------------------------------------------------------
//  Close the .CSV file.
// -----------------------------------------------------------------------------
static HRESULT HrCloseCsvFile(void)         // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    int                 nResult             = 0;

    DEBUGPRIVATE("HrCloseCsvFile()");

    // Close the file.

    nResult = fclose(fpCsvFile);

    if (nResult)
    {
        EventLogMsg(
            FIMPORT_CANNOT_CLOSE_IMPORT_FILE, 
            1, szFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}
