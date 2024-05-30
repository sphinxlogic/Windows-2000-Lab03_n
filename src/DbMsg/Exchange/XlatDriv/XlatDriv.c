// --xlatdriv.c-------------------------------------------------------------------
// 
//  Message translation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "edk.h"
#include "convcwrp.h"
#include "gwmain.h"
#include "ipmconv.h"        // for ipm_in & ipm_out conversion DLLs
#include "xlatmsg.h"        // resource string identifiers
#include "xlatdriv.chk"

// constants
#define MAX_MSG_LENGTH              1024            // maximum message length
#define APPLICATION_TITLE           TEXT("Message Translation Sample")    // application name
#define APPLICATION_EVENT_FILE      TEXT("EDKMSG.DLL")  // event logging message file

//  Defined for NT service shell
TCHAR szAppName[]       = TEXT("XLATDRIV");
TCHAR szWindowTitle[]   = APPLICATION_TITLE;

static LPMAPISESSION    lpSession       = NULL;
static LPMDB            lpStore         = NULL;
static LPMAPIFOLDER     lpRootFolder    = NULL;
static LPMAPIFOLDER     lpMtsInFolder   = NULL;
static LPMAPIFOLDER     lpMtsOutFolder  = NULL;
static ULONG            cbGalEid        = 0;
static LPENTRYID        lpGalEid        = NULL;

static HANDLE           hEventLog       = NULL;

static HINSTANCE        hInst           = NULL; // program instance handle

PVOID  pvConvInstance   = NULL;

// Prefix of output *.tmp files.
static const LPCTSTR    lpszPrefix      = TEXT("XLT");

// Default inbound/outbound file directory
const LPCTSTR           lpszDefaultDir  = TEXT(".\\");

// inbound and outbound file directory
static TCHAR    lpszDirectory[MAX_PATH + 1] =   TEXT("");

// Address type used for conversion (Currently "EX")
static TCHAR    lpszAddressType[]   =   TEXT(EXCHANGE_ADDRTYPE);   // address type

// Conversion options structure for the ipm_in & ipm_out conversion DLLs
static CONV_OPTIONS   sConvOptions = 
{
    FALSE,              // don't want TNEF decoding
    lpszAddressType     // address type
};

static ULONG    nMessages           =   0;              // # messages converted

//$--ProcessMtsOut--------------------------------------------------------------------
//
//  DESCRIPTION: Process messages arriving at MTS-OUT.  This is a Windows thread
//  startup routine.
//
//  INPUT:  lpParameter --  pointer to gateway thread context structure 
//                          (LPGWTHREADCONTEXT).
//
//  RETURNS:    DWORD   --  0
//
// -----------------------------------------------------------------------------
DWORD ProcessMtsOut(           // RETURNS: DWORD
    IN LPVOID lpParameter)     // gateway thread context structure pointer
{
    HRESULT         hr                 = NOERROR;   // temporary return code
    ULONG           i                  = 0;
    ULONG           cRows              = 0;
    ULONG           cValues            = 0;
    ULONG           ulObjType          = 0;

    LPADRBOOK       lpAdrBook          = NULL;

    LPMESSAGE       lpEnvelope         = NULL;

    ULONG           cbeid              = 0;
    LPENTRYID       lpeid              = NULL;

    LPWSTR          pszMessageClassW   = NULL;
    ULONG           cbMessageClass     = 0;
    EDKCNVRES       crRes              = GCR_OK;

    LPSPropValue    lpProps            = NULL;

    LPSTREAM        lpStream           = NULL; // stream to write output to

    // message output file name
    TCHAR           pszFileName[MAX_PATH+1] =   TEXT("");       

    //
    //  Declare an environment for the conversion.
    //

    EDKCNVENV envTmp =
    { 
        1,
        L"SAMPLEGW.OUTBOUND",            // L = UNICODE string always.
        (LHANDLE)NULL,
        NULL,
        NULL,
        NULL
    };

	// Stream interface flags
	const ULONG	ulFlags	=	STGM_READWRITE | STGM_CREATE | 
	                        SOF_UNIQUEFILENAME | STGM_SHARE_EXCLUSIVE;

    DEBUGPUBLIC("ProcessMtsOut()\n");

    // check input parameters
    hr = CHK_Process(lpParameter);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    cRows = GetGWSRowSet(lpParameter)->cRows;

    // Open the Address Book
    hr = MAPICALL(lpSession)->OpenAddressBook(
        lpSession,
        0,
        NULL, 
        AB_NO_DIALOG,
        &lpAdrBook);

    if(FAILED(hr))                 
    {       
        goto cleanup;
    }

    // Initialize conversion environment structure
    envTmp.lphSession       = (LHANDLE)lpSession;
    envTmp.lpAB             = lpAdrBook;
    envTmp.pGatewayDefined  = &sConvOptions;

    for(i = 0; i < cRows; i++)
    {
        // Free MAPI buffer
        MAPIFREEBUFFER(pszMessageClassW);

        // Release MAPI objects
        ULRELEASE(lpEnvelope);
        ULRELEASE(lpStream);

        cValues = GetGWSRowSet(lpParameter)->aRow[i].cValues;

        lpProps = GetGWSRowSet(lpParameter)->aRow[i].lpProps;

        cbeid = lpProps[0].Value.bin.cb;
        lpeid = (LPENTRYID)lpProps[0].Value.bin.lpb;

        // Get the message in the MTS-OUT folder
        hr = MAPICALL(lpMtsOutFolder)->OpenEntry(
            lpMtsOutFolder,
            cbeid,
            lpeid,
            NULL,
            MAPI_MODIFY|MAPI_DEFERRED_ERRORS,
            &ulObjType,
            (LPUNKNOWN FAR *)&lpEnvelope);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        if(ulObjType != MAPI_MESSAGE)
        {
            goto cleanup;
        }

        // Initialize output file name.
        lstrcpy(pszFileName, lpszDirectory);

        // Open a buffered stream interface on a unique XLT*.tmp 
        // output file.
        hr = OpenStreamOnFile(
                MAPIAllocateBuffer,     // allocation routine
                MAPIFreeBuffer,         // deallocation routine
                ulFlags,				// stream interface flags
                pszFileName,            // file name
                (LPTSTR) lpszPrefix,    // file prefix
                &lpStream);             // stream pointer

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Get the message's wide character message class.
        hr = HrMAPIGetPropString(
                        (LPMAPIPROP) lpEnvelope,          // message envelope pointer
                        PR_MESSAGE_CLASS_W, // wide character message class
                        &cbMessageClass,
                        &pszMessageClassW);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        //
        //  Perform the conversion.
        //

        hr = HrConvConvert(
            pvConvInstance,
            &envTmp,
            pszMessageClassW, 
            lpEnvelope,
            lpStream,
            &crRes);

        if(FAILED(hr) || crRes != GCR_OK)
        {
            goto cleanup;
        }
        
        // Note: Conversion DLL commits changes to stream if
        // successful.


        ULRELEASE(lpEnvelope);

        // ---------------------------------------------------------------------

        //
        // Remove the converted message from the MTS-OUT folder.
        //

        hr = HrMAPIDeleteMessage(
                    lpMtsOutFolder,     // MAPI folder pointer
                    cbeid,              // # bytes in entry id
                    lpeid);             // message entry identifier
                    
        if(FAILED(hr))
        {
            goto cleanup;
        }

        // increment message count
        nMessages++;

    }   // end for

cleanup:

    // Release MAPI and OLE objects
    ULRELEASE(lpStream);
    ULRELEASE(lpEnvelope);
    ULRELEASE(lpAdrBook);

    // Free MAPI buffers
    MAPIFREEBUFFER(pszMessageClassW);

    if ( (FAILED(hr) || (crRes != GCR_OK)) && (pszFileName[0] != 0) )
    {
        // If we failed, we may have an empty file
        // siting around.
        if ( lstrcmp(pszFileName, lpszDefaultDir) != 0 )
        {
            // Remove the empty file
            DeleteFile(pszFileName);
        }
    }
             
    return(0);
}

//$--ProcessMtsIn--------------------------------------------------------------------
//
//  DESCRIPTION: Process files arriving in input directory.  This is a Windows thread
//  startup routine.
//
//  INPUT:  lpParameter --  pointer to gateway thread context structure 
//                          (LPGWTHREADCONTEXT).
//
//  RETURNS:    DWORD   --  0
//
// -----------------------------------------------------------------------------
DWORD ProcessMtsIn(            // RETURNS: DWORD
    IN LPVOID lpParameter)     // gateway thread context structure pointer
{
    HRESULT         hr                 = NOERROR;   // temporary error code
    ULONG           i                  = 0;         // index
    ULONG           cRows              = 0;         // row count
    LPADRBOOK       lpAdrBook          = NULL;      // address book pointer
    LPMESSAGE       lpEnvelope         = NULL;      // envelope pointer
    EDKCNVRES       crRes              = GCR_OK;    // result of conversion
    LPSTREAM        lpStream           = NULL;      // stream to read input from
    BOOL            fRetVal            = FALSE;     // Win32 return code

    // File data
	LPWIN32_FIND_DATA   rgFindData               = NULL;
	LPWIN32_FIND_DATA   lpFindData               = NULL;

    // message output file name
    TCHAR           pszFileName[MAX_PATH+1] =   TEXT("");       

    //
    //  Declare an environment for the conversion.
    //

    EDKCNVENV envTmp =
    { 
        1,
        L"SAMPLEGW.INBOUND",            // L = UNICODE string always.
        (LHANDLE)NULL,
        NULL,
        NULL,
        NULL
    };

    const LPCWSTR   pszMessageClassW    =   L"ENVELOPE.IPM";    // dummy message class

    DEBUGPUBLIC("ProcessMtsIn()\n");

    // check input parameters
    hr = CHK_Process(lpParameter);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    cRows = GetGWFindDataSize(lpParameter);

    rgFindData = GetGWFindData(lpParameter);

    // Open the Address Book
    hr = MAPICALL(lpSession)->OpenAddressBook(
        lpSession,
        0,
        NULL, 
        AB_NO_DIALOG,
        &lpAdrBook);

    if(FAILED(hr))                 
    {       
        goto cleanup;
    }

    // Initialize the conversion environment structure
    envTmp.lphSession       = (LHANDLE)lpSession;
    envTmp.lpAB             = lpAdrBook;
    envTmp.pGatewayDefined  = &sConvOptions;

    for(i = 0; i < cRows; i++)
    {
        // Release MAPI objects
        ULRELEASE(lpEnvelope);
        ULRELEASE(lpStream);

    	// Build file name of incoming message

        lpFindData = &rgFindData[i];

    	lstrcpy(pszFileName, lpszDirectory);
    	lstrcat(pszFileName, lpFindData->cFileName);

        // Open a buffered stream on our input file.
    	hr = OpenStreamOnFile(
    	    MAPIAllocateBuffer,     // allocation routine
    	    MAPIFreeBuffer,         // deallocation routine
    		STGM_READ | STGM_SHARE_EXCLUSIVE,	// open for reading
    		pszFileName,            // file name
    		NULL,                   // prefix
    		&lpStream);             // stream pointer

        if ( (hr == MAPI_E_NO_ACCESS) || (hr == MAPI_E_NOT_FOUND) )
        {
            // These are not really errors
            hr = NOERROR;

            continue;
        }

    	if ( FAILED(hr) )
    	{
            hr = HR_LOG(E_FAIL);

            goto cleanup;
    	}

        // Create the message envelope in the MTS-IN folder.
        hr = MAPICALL(lpMtsInFolder)->CreateMessage(
            lpMtsInFolder,  // folder pointer
            NULL,
            MAPI_DEFERRED_ERRORS, // flags
            &lpEnvelope);   // message pointer

        if( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        //
        //  Perform the conversion.
        //
        hr = HrConvConvert(
            pvConvInstance,         // conversion instance pointer
            &envTmp,                // environment structure pointer
            pszMessageClassW,       // dummy message class
            lpStream,               // stream to read from
            lpEnvelope,             // message to convert to
            &crRes);                // result pointer

        if(FAILED(hr) || crRes != GCR_OK)
        {
            goto cleanup;
        }
        
        // Note: Conversion DLL saves changes to the envelope if
        // successful.

        // Save changes to the MTS-IN folder
        hr = MAPICALL(lpMtsInFolder)->SaveChanges(
                    lpMtsInFolder,
                    KEEP_OPEN_READWRITE);   // still need access to folder

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        ULRELEASE(lpStream);

        // Remove the converted file from the input directory.
        fRetVal = DeleteFile(pszFileName);

        if ( fRetVal == FALSE )
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }        

        // increment message count
        nMessages++;

    }   // end for

cleanup:

    // Release MAPI and OLE objects
    ULRELEASE(lpStream);
    ULRELEASE(lpEnvelope);
    ULRELEASE(lpAdrBook);
             
    return(0);
}

// $--DisplayUserMsg----------------------------------------------------------
//
// DESCRIPTION: Utility to display message to command line user.
//
// INPUT:       HINSTANCE   --  XLATDRIV instance handle
//              UINT        --  Resource string identifier
// 
// RETURNS:     VOID
//
// ----------------------------------------------------------------------------

static VOID DisplayUserMsg(     // RETURNS: nothing
            IN HINSTANCE hInst, // program handle
            IN UINT nResID,     // resource string identifier
            ...)                // additional arguments
{    
    INT         nRetCode        =   0;              // return value
    va_list     vArgList        =   {0};            // variable argument list
    HANDLE      hFile           =   NULL;           // file handle

    TCHAR       szMessage[MAX_MSG_LENGTH]   = TEXT(""); // message buffer
    TCHAR       szFormatted[MAX_MSG_LENGTH] = TEXT(""); // formatted message

    DEBUGPRIVATE("DisplayUserMsg()\n");

    // No CHK_DisplayUserMsg() call.
    // This function can take a NULL HINSTANCE

    // Check the instance handle passed in.
    if ( !hInst )
    {
        HR_LOG(E_FAIL);

        goto cleanup;
    }

    nRetCode = LoadString(hInst, nResID, szMessage, MAX_MSG_LENGTH);
    if ( nRetCode == 0 )
    {
        HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Get an optional argument list pointer
    va_start(vArgList, nResID);

    // Fromat the message.
    _vstprintf(
            szFormatted,        // formatted message buffer
            szMessage,          // format string
            vArgList);          // variable argument list

    va_end(vArgList);

    // Display the error in a message box
    MessageBox(
            NULL,           // use parent window handle
            szFormatted,    // message text
            APPLICATION_TITLE,  // message box title
            MB_OK);

cleanup:

    // close console file
    CLOSEHANDLE(hFile);

    // Return
    return;

}   // end DisplayUserMsg()

// $--HrParseOptions-----------------------------------------------------------
//
// DESCRIPTION: parse command line flags.
//
// INPUT:   cArgs   --  # arguments
//          pArgv   --  argument array
//
// OUTPUT:
//          pfInbound    --  inbound flag
//          pfTnef       --  TNEF flag
//          pcThreads    --  # threads
//          lpszDirectory   --  file directory
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
static HRESULT HrParseOptions(
        IN DWORD cArgs,         // argument count
        IN LPTSTR * pArgv,      // argument array
        OUT BOOL * pfInbound,   // inbound flag
        OUT BOOL * pfTnef,      // TNEF encoding desired flag
        OUT DWORD * pcThreads,  // # threads
        OUT LPTSTR  lpszDirectory) // file directory
{
// Number of flag arguments and array indeces
#define             iDirection      0
#define             iThreads        1
#define             iLocation       2
#define             iHelp1          3
#define             iHelp2          4
#define             iTnef           5
#define             nFlags          6

    HRESULT         hr              =   NOERROR;
    UINT            iLoop           =   0;          // loop index
    ULONG           iFlag           =   0;          // flag index
    LPTSTR          lpFlagName      =   NULL;       // flag name pointer
    LPTSTR          lpData          =   NULL;       // flag data
    HANDLE          hFile           =   NULL;       // file handle
    BOOL            fInbound        =   FALSE;      // TRUE if direction inbound
    BOOL            fOutbound       =   FALSE;      // TRUE if direction outbound
    UINT            nRet            =   0;          // Win32 API return code
    UINT            nChars          =   0;

    const LPCTSTR   lpszInbound     =   TEXT("In");     // inbound value
    const LPCTSTR   lpszOutbound    =   TEXT("Out");    // outbound value
    const TCHAR     chBackSlash     =   TEXT('\\');     // back slash

    // array of valid flags
    LPTSTR                rgFlags[nFlags]   =
    {
        TEXT("DIRECTION"),      // Inbound or outbound
        TEXT("THREADS"),        // # of threads
        TEXT("LOCATION"),       // location of input/output files
        TEXT("HELP"),
        TEXT("?"),
        TEXT("ENCODE")          // TNEF encoding/decoding desired
    };

    // temporary file name
    TCHAR           szTempFile[MAX_PATH + 1]    =   TEXT("");

    DEBUGPRIVATE("HrParseOptions()\n");

    // check input parameters
    hr = CHK_HrParseOptions(cArgs, pArgv, pfInbound, pfTnef, pcThreads,
                    lpszDirectory);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Check to make sure that we have enough arguments.
    // Note:  If the use originally typed
    // xlatdriv notserv gdk-sample, then the arguments
    // which are passed to this program are everything
    // after the program name and the notserv option.
    if ( cArgs < 1 )
    {
        hr = HR_LOG(E_INVALIDARG);

        // Print out the syntax error message.
        DisplayUserMsg(hInst, IDS_ERROR_USAGE);

        goto cleanup;
    }
        
    // initialize output parameters
    *pfInbound = FALSE;
    *pfTnef = FALSE;
    *pcThreads = 1;
    lstrcpy(lpszDirectory, lpszDefaultDir);

    // Parse each argument, looking for a supported flag
    for ( iLoop = 0; iLoop < cArgs; iLoop++ )
    {
        hr = _HrExpandCommandLineArgument(
                pArgv[iLoop],       // command line argument
                rgFlags,            // array of flag names
                nFlags,             // number of flags
                &iFlag,             // flag index            
                &lpFlagName,        // flag name
                &lpData);           // flag data

        if ( FAILED(hr) )
        {
            DisplayUserMsg(
                        hInst,              // instance handle
                        IDS_INVALID_ARG,    // string identifier
                        pArgv[iLoop]);      // argument

            goto cleanup;
        }

        if ( lpFlagName == NULL )
        {
            // not a flag.  We are only interested in flags
            continue;
        }

        // switch off of flag found
        switch ( iFlag )
        {
            case iDirection:         // direction index
                if ( (lpData == NULL) || (*lpData == 0) )
                {
                    hr = HR_LOG(E_INVALIDARG);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_ERROR_NOVALUE,  // string identifier
                            lpFlagName);        // argument

                    goto cleanup;
                }

                // Determine if inbound or outbound
                if ( _tcsnicmp(lpData, lpszInbound, lstrlen(lpszInbound))
                     == 0 )
                {
                    fInbound = TRUE; 
                    *pfInbound = TRUE;                   
                }

                else if ( _tcsnicmp(lpData, lpszOutbound, lstrlen(lpszOutbound))
                          == 0 )
                {
                    fOutbound = TRUE;
                    *pfInbound = FALSE;
                }

                else
                {
                    // print out error.
                    hr = HR_LOG(E_INVALIDARG);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_INVALID_VALUE,  // string identifier
                            lpData,
                            lpFlagName);        // argument

                    goto cleanup;
                }

                break;
                                
            case iThreads:     // threads index
                // Initialize number of threads
                if ( (lpData == NULL) || (*lpData == 0) )
                {
                    // print out error
                    hr = HR_LOG(E_INVALIDARG);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_ERROR_NOVALUE,  // string identifier
                            lpFlagName);        // argument

                    goto cleanup;
                }

                *pcThreads = atol(lpData);

                if ( *pcThreads == 0 )
                {
                    // print out error
                    hr = HR_LOG(E_INVALIDARG);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_INVALID_VALUE,  // string identifier
                            lpData,
                            lpFlagName);         // argument

                    goto cleanup;
                }

                break;

            case iLocation:         // location index
                if ( (lpData == NULL) || (*lpData == 0) )
                {
                    hr = HR_LOG(E_INVALIDARG);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_ERROR_NOVALUE,  // string identifier
                            lpFlagName);        // argument

                    goto cleanup;
                }

                // Make sure that we can create a file in the
                // directory.
                // First, get a temporary file name
                nRet = GetTempFileName(
                        lpData,     // directory
                        lpszPrefix, // file prefix
                        0,          // use time to create number
                        szTempFile);    // file name

                if ( nRet == 0 )
                {
                    hr = HR_LOG(E_FAIL);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_INVALID_VALUE,    // string identifier
                            lpData,
                            lpFlagName);      // argument

                    goto cleanup;
                }

                hFile = CreateFile(
                        szTempFile,            // file name
                        GENERIC_READ | GENERIC_WRITE,
                        0, 
                        0,
                        CREATE_ALWAYS, 
                        FILE_ATTRIBUTE_NORMAL, 
                        0);

                if ( hFile == INVALID_HANDLE_VALUE )
                {
                    // print out error
                    hr = HR_LOG(E_INVALIDARG);

                    DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_INVALID_VALUE,  // string identifier
                            lpData,
                            lpFlagName);        // argument

                    goto cleanup;
                }

                // Close the file
                CLOSEHANDLE(hFile);

                // Delete the file
                (VOID)DeleteFile(
                        szTempFile);   // file name
                                
                lstrcpy(lpszDirectory, lpData);

                // Append a back slash to the directory
                // name if it doesn't alredy have one.
                nChars = lstrlen(lpszDirectory);
                if ( lpszDirectory[nChars - 1] != chBackSlash )
                {
                    lpszDirectory[nChars] = chBackSlash;
                    lpszDirectory[nChars + 1] = 0;  // null terminate
                }

                break;

            case iHelp1:     // help index
            case iHelp2:     // ? index
                // print out help.

                // Not really an error, but we need
                // to exit early.
                hr = HR_LOG(E_INVALIDARG);

                DisplayUserMsg(hInst, IDS_ERROR_HELP);

                goto cleanup;

            case iTnef:     // TNEF index
                // User wants TNEF encoding/decoding
                // Data portion of flag is ignored.
                *pfTnef = TRUE;

                break;

            default:

                hr = HR_LOG(E_FAIL);

                DisplayUserMsg(
                            hInst,              // instance handle
                            IDS_INVALID_ARG,    // string identifier
                            lpData);            // argument

                goto cleanup;

        }   // end switch

    }   // end for

    // make sure that haven't received conflicting directions
    if ( fInbound && fOutbound )
    {
        // print out error.
        hr = HR_LOG(E_INVALIDARG);

        DisplayUserMsg(
                    hInst,                      // instance handle
                    IDS_CONFLICTING_DIRECTION); // string identifier

        goto cleanup;
    }

cleanup:

    RETURN(hr);

}

//$--GWMain----------------------------------------------------------------
//
//  DESCRIPTION: Start threads.
//
//  INPUT:  none
//
//  RETURNS: VOID
//
// -----------------------------------------------------------------------------
VOID GWMain(       // RETURNS: VOID
    VOID)
{
    HRESULT               hr                     = NOERROR;
    EDK_SERVICE_CONTROL_T sc                     = 0;
    DWORD                 cArgs                  = 0;
    LPTSTR *              pArgv                  = NULL;
    BOOL                  fInbound               = FALSE;
    BOOL                  fTnef                  = FALSE;
    DWORD                 cThreads               = 1;
    TCHAR                 szTempPath[MAX_PATH+1] = {0};
    const DWORD           cMessages              = 1;
    DWORD                 cch                    = 0;

    DEBUGPUBLIC("GWMain()\n");

    // Get this program's instance handle.
    hInst = GetModuleHandle(NULL);

    if ( hInst == NULL )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Retrieve the command line arguments
    // Command line is of the form
    //
    //  XLATDRIV [notserv] GWProfileName [flags]
    //
    // where flags are:
    //
    //  /DIRECTION=Inbound or /DIRECTION=Outbound
    //  /THREADS=#Thread
    //  /LOCATION=DirectoryName     (for input or output files)
    //  /ENCODE                     (TNEF encoding/decoding desired)
    //
    // By default, the direction is assumed to be outbound,
    // TNEF encoding is assumed to be FALSE,
    // the file location is assumed to be the current directory
    // and the number of threads is assumed to be 1.  (If
    // notserv is not specified, winwrap.c assumes that XLATDRIV
    // is to be run as a service.)

    hr = HrServiceGetArgv(
                &cArgs,         // argument count pointer
                &pArgv);        // pointer to argument array pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Parse out options.
    hr = HrParseOptions(
                cArgs,      // argument count
                pArgv,      // pointer to argument array
                &fInbound,  // inbound flag
                &fTnef,     // TNEF desired flag
                &cThreads,  // # threads
                lpszDirectory);    // file directory

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Set TNEF flag in gateway options.
    sConvOptions.fTnefEncode = fTnef;

    if ( fInbound )
    {
        // Want to do inbound conversion.
        // (Read files in and convert to messages in MTS-IN)
        hr = HrGWStartNewFileHandler(
            1000,                   // sleep interval
            (ULONG) -1,             // poll interval
            cMessages,              // # messages per thread
            cThreads,               // # of threads
            lpszAddressType,        // address type
            TEXT("XLT*.TMP"),       // file name template
            lpszDirectory,          // input file directory
            (LPTHREAD_START_ROUTINE)ProcessMtsIn);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }

    else
    {
        cch = GetTempPath(MAX_PATH+1, szTempPath);
        
        if((cch == 0) || (cch > (MAX_PATH+1)))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Want to do outbound conversions.  
        // (Read messages from MTS-OUT and convert to output
        // files.
        hr = HrGWStartNewMailHandler(
            1000,
            (ULONG)-1,
            cMessages,
            cThreads,
            lpszAddressType,
            szTempPath,
            (LPTHREAD_START_ROUTINE)ProcessMtsOut);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }   // end if doing out bound conversions

cleanup:

    if(FAILED(hr))
    {
        ServiceStop();
    }

    //
    // Wait for a request for the service to stop.
    //

    hr = HR_LOG(HrServiceWaitForStop(INFINITE, &sc));

    return;
}

//$--HrGWLogon-------------------------------------------------------------
//
//  Logon to the gateway.
//
// -----------------------------------------------------------------------------
HRESULT HrGWLogon(                 // RETURNS: return code
        VOID)
{
    HRESULT hr = NOERROR;

    lpSession      = GetGWSession();
    lpStore        = GetGWDefaultStore();
    lpRootFolder   = GetGWRootFolder();
    lpMtsInFolder  = GetGWMtsInFolder();
    lpMtsOutFolder = GetGWMtsOutFolder();
    cbGalEid       = GetGWGALEntryIdSize();
    lpGalEid       = GetGWGALEntryId();

    DEBUGPUBLIC("HrGWLogon()\n");

    // Open an event log for this application.
    hr = HrEventOpenLog(
                APPLICATION_TITLE,  // application name
                NULL,           // executable name (will be computed)
                APPLICATION_EVENT_FILE, // event message file (will be computed)
                NULL,           // parameter message file (will be computed)
                NULL,           // category message file (will be computed)
                &hEventLog);    // event source handle

    if ( FAILED(hr) || (hEventLog == NULL) )
    {
        goto cleanup;
    }

    // Initialize conversion engine global data.
    hr = HrConvInitGlobals();
    
    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Initialize conversion engine instance data.
    hr = HrConvInitInstance(hEventLog, &pvConvInstance);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrGWLogoff------------------------------------------------------------
//
//  Logoff of the gateway.
//
// -----------------------------------------------------------------------------
HRESULT HrGWLogoff(                // RETURNS: return code
    VOID)
{
    HRESULT         hr          =   NOERROR;
    EDKEVENTCOUNT   sEventCount =   {0};        // EDK event count structure

    DEBUGPUBLIC("HrGWLogoff()\n");

    // De-initialize conversion engine instance data.
    (VOID)HrConvUninitInstance(pvConvInstance);
    pvConvInstance = NULL;

    // De-intialize global conversion engine data.
    ConvUninitGlobals();

    // Display number of messages processed.
    if ( nMessages >= 0 )
    {
        DisplayUserMsg(
            hInst,              // instance handle
            IDS_SUCCESS,        // string identifier
            nMessages);         // # messages processed
    }

    // Determine number of messages written to the event log.
    hr = HrEventGetCounts(
            &sEventCount);

    if ( SUCCEEDED(hr) )
    {
        // print out number of errors printed to the
        // event log. 
        if ( sEventCount.cError == 1 )
        {
            DisplayUserMsg(
                hInst,
                IDS_1_ERROR);
        }

        else if ( sEventCount.cError > 1 )
        {
            DisplayUserMsg(
                hInst,
                IDS_NUM_ERRORS,
                sEventCount.cError);
        }

        // Print out the number of warnings logged
        if ( sEventCount.cWarning == 1 )
        {
            DisplayUserMsg(
                hInst,
                IDS_1_WARNING);
        }

        else if ( sEventCount.cWarning > 1 )
        {
            DisplayUserMsg(
                hInst,
                IDS_NUM_WARNINGS,
                sEventCount.cWarning);
        }
    }   // end if know # of messages logged to event file

    // Close the event log.
    (VOID)HrEventCloseLog();
    hEventLog = NULL;
            
    RETURN(hr);
}
