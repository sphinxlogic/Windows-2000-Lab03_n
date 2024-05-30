// --gwclean.cpp--------------------------------------------------------------
//
// Implements the GWCLEAN gateway utility which
// moves all messages in a gateway's folder before a particular
// date and time to a PST (personal information store).
//
// Syntax:
// 
// GWCLEAN GatewayProfileName [flags]
//
// where the flags are:
//
//  -DAYS=<#DaysPriorToToday>    --  # of days prior to today
//                                   defaults to yesterday
//  -FILE=<PSTFileName>          --  PST file name to move messages to
//                                   defaults to GWCLEAN.PST in current
//                                   directory
//  -FOLDER=<GatewayFolderName>  --  folder to move gateway message from
//                                   defaults to MTS-OUT
//
// Copyright (C) Microsoft Corporation 1986-1996.  All Rights Reserved
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "mspst.h"

#include "gwstring.h"
#include "gwobjcls.h"
#include "gwevents.h"	// compiled from gwevents.mc
#include "gwclean.chk"

// Globals
CGWClean * lpCGWClean  =   NULL;    // global GWCLEAN class object pointer

// external function declarations
extern HRESULT HrParseCommandLine(
                    IN INT argc,    // argument count
                    IN CHAR * argv[],   // list of arguments
                    OUT LPTSTR lpProfile,      // GW profile name
                    OUT LPTSTR lpPSTName,      // PST name
                    OUT LPTSTR lpFolder,       // GW folder name
                    OUT LPFILETIME lpBeforeTime); // date/time before structure pointer

extern VOID DisplayUserMsg(         // RETURNS: VOID
                    IN UINT uResID,            // resource identifier
                    ...);           // variable arguments

extern HRESULT HrComputeDate(           // RETURNS: HRESULT
                    IN UINT,            // number of days before today
                    OUT LPFILETIME);    // file time structure pointer

extern HRESULT HrCheckFileName(     // RETURNS: HRESULT
            IN LPTSTR lpFileName);  // file name to check

// useful constants
LPTSTR	pszAppName	=	TEXT("GWCLEAN");

//$--INTERNAL_ERROR-----------------------------------------------------------
//  Helper function for EventLogMsg
// ---------------------------------------------------------------------------
extern inline VOID INTERNAL_ERROR(
    IN LPCTSTR str,
    IN const HRESULT hr)
{
    TCHAR szErrorCode[16] = {0};

    EventLogMsg(
        GWCLEAN_INTERNALERR,
        2, str, _itot( hr, szErrorCode, 16),
        0);
}

//$--main---------------------------------------------------------------------
//
// DESCRIPTION: Implement GWCLEAN gateway utility described above.
//
// INPUT:       INT   --  number of command line arguments
//              TCHAR[] *    --  command line arguments
//
// RETURNS:     int              --  0 if successful,
//                                  non-zero otherwise:
//                                  (See edkcode.h for more specifics)
//
// ----------------------------------------------------------------------------

INT main(                   // RETURNS: INT
        INT argc,           // number of command line arguments
        TCHAR * argv[])     // command line arguments
{
    HRESULT     	hr          			=   NOERROR;
	HRESULT			hrT						=	NOERROR;// temporary return code
    FILETIME    	sBeforeTime 			=   {0};    // before date/time structure
    TCHAR       	lpProfile[MAX_PATH+1]   =   ""; 	// GW profile name
    TCHAR       	lpPSTName[MAX_PATH+1]   =   ""; 	// PST file name
    TCHAR       	lpFolder[MAX_PATH+1]    =   ""; 	// GW folder name
	HANDLE			hEvent					=	NULL;	// event logging handle
	EDKEVENTCOUNT	sEventCount				=	{0};	// event log count structure
	BOOL			fEventLogOpened			=	FALSE;	// TRUE if event log is open
    TCHAR           szErrorCode[16]         =   {0};

    // Special base class which guarantees that MAPI is
    // unitialized when it goes out of scope.
    BOOL        fInitialized    =   FALSE;  // TRUE if MAPI is initialized

    DEBUGPUBLIC("main()\n");

    // check command line arguments
    hr = CHK_main(argc, argv);

    if ( FAILED(hr) )
    {
        // This should never happen
		MODULE_ERROR("Arguments to main() invalid");
        return _nEcFromHr(hr);
    }

	// Open the NT event log for this application.
 	hr = HrEventOpenLog(
		pszAppName,					// application name
		NULL,						// executable name (computed)
    	NULL,						// event message file (computed)
		NULL,						// parameter message file
		NULL,						// category message file
		&hEvent);					// event logging handle

	if ( FAILED(hr) )
	{
		DisplayUserMsg(
			IDS_EVENT_LOG,
			hr);

		goto cleanup;
	}

	ASSERTERROR((hEvent != NULL), "Bad hEvent");

	fEventLogOpened = TRUE;

    // Instantiate a GWCLEAN object.
    lpCGWClean = new CGWClean();

    if ( !lpCGWClean )
    {
		EventLogMsg(
			GWCLEAN_OUTOFMEMORY,
			0,	// # of string replacements
			0);	// # of Win32 error arguments

        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    // Parse command line arguments.  The syntax is:
    //
    // GWCLEAN <GWProfileName> -FILE=<PSTName> -DAYS=<#days> -FOLDER=<folder>
    //
    // where PSTName is a fully-pathed file name, #days
    // is a positive integer representing the number of days before
    // today for which to move all gateway <folder> messages which were
    // sent on before that date, and GWProfileName is the name of an
    // gateway profile.
    //
    hr = HrParseCommandLine(argc, argv,
            lpProfile,      // GW profile name
            lpPSTName,      // PST file name
            lpFolder,       // GW folder name
            &sBeforeTime);  // before time pointer

    if ( FAILED(hr) )
    {   
        // User errors are displayed in HrParseCommandLine()
        goto cleanup;
    }

    // Initialize use of extended MAPI.
    hr = MAPIInitialize(NULL);

    if ( FAILED(hr) )
    {
		EventLogMsg(
			GWCLEAN_MAPIINIT,
			1, _itot( hr, szErrorCode, 16),
			0);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    fInitialized = TRUE; // MAPI is initialized

    // Initialize our CGWClean class instance.  This
    // function takes care of creating the new PST, logging
    // on to the gateway and temporary profiles, etc...
    hr = lpCGWClean->HrInitialize(
    	lpProfile,
        lpPSTName,
        lpFolder,
        &sBeforeTime);

    if ( FAILED(hr) )
    {
        // User messages are taken care of in HrInitialize().
        goto cleanup;
    }

    // Move messages in GW MTS-OUT folder before date/time to
    // new PST folder.
    hr = lpCGWClean->HrMoveMsgs();

    if ( FAILED(hr) )
    {
        // user messages displayed in HrMoveMsgs
        goto cleanup;
    }

cleanup:

	// If doing event logging
	if ( fEventLogOpened == TRUE )
	{
		// Retrieve number of errors and warnings written to the event log.
		ZeroMemory(&sEventCount, sizeof(sEventCount));
		hrT = HrEventGetCounts(
			&sEventCount);		// structure to hold event logging statistics

		if ( FAILED(hrT) )
		{
            INTERNAL_ERROR( TEXT("HrEventGetCounts()"), hrT);
			sEventCount.cError = 1;	// have at least one error
		}

		if ( sEventCount.cError == 1 )
		{
			// print one error message
			DisplayUserMsg(
				IDS_1ERROR);
		}
	
		else if ( sEventCount.cError > 1 )
		{
			// print multiple error message
			DisplayUserMsg(
				IDS_ERRORS);
		}

		if ( sEventCount.cWarning == 1 )
		{
			// print out one warning message
			DisplayUserMsg(
				IDS_1WARNING);
		}

		else if ( sEventCount.cWarning > 1 )
		{
			// print out multiple warnings message
			DisplayUserMsg(
				IDS_WARNINGS);
		}

		// close event log
		(VOID)HrEventCloseLog();
		hEvent = NULL;
		fEventLogOpened = FALSE;

	}	// end if doing event logging
	 
    if ( lpCGWClean )
    {        
        // delete gwclean object.
        // A side effect of this is that all MAPI objects are freed
        // and all sessions are logged off.
        delete lpCGWClean;

    }   // end if lpCGWClean

    if ( fInitialized )
    {
        // Unitialize MAPI
        (VOID)MAPIUninitialize();
    }

    // We are done.
    // return the appropriate exit code
    return _nEcFromHr(hr);
        
}   // end main()

//$--HrParseCommandLine---------------------------------------
//
// DESCRIPTION: Parse GWCLEAN command line
//
// INPUT:   argc    --  argument count
//          argv    --  list of arguments
//
// OUTPUT:  lpProfile   --  GW profile name pointer (MAX_PATH + 1 character buffer)
//          lpPSTName   --  PST file name (MAX_PATH + 1 character buffer)
//          lpFolder    --  GW folder name (MAX_PATH + 1 character buffer)
//          pnDays      --  #days before pointer
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise
//
// ------------------------------------------------------------
HRESULT HrParseCommandLine(                     // RETURNS: HRESULT
                    IN INT argc,                // argument count
                    IN TCHAR * argv[],          // list of arguments
                    OUT LPTSTR lpProfile,      // GW profile name
                    OUT LPTSTR lpPSTName,      // PST name
                    OUT LPTSTR lpFolder,       // GW folder name
                    OUT LPFILETIME lpBeforeTime)// before time pointer
{
    HRESULT     hr          =   NOERROR;
    LPTSTR      lpData      =   NULL;       // pointer to flag data
    LPTSTR      lpFlag      =   NULL;       // pointer to flag name
    ULONG       iFlag       =   0;          // flag index
    INT         iArg        =   0;          // argument index
    UINT        nDays       =   0;          // number of days before today
    BOOL        fDaysFound  =   FALSE;      // TRUE if user specifies DAYS flag
    LPTSTR      lpTemp      =   0;          // temporary string pointer
    UINT        cchExeName  =   0;          // # characters in executable name
    DWORD       dwRetVal    =   0;          // Win32 API return code

    // fully-pathed module file name
    TCHAR       lpszExeName[MAX_PATH + 1]   = TEXT("");

    // default values
    TCHAR       lpszPath[MAX_PATH + 1]      = TEXT(""); // default path
    TCHAR       lpszPSTName[MAX_PATH + 1]   = TEXT(""); // default PST name

    const LPTSTR    lpszFolder  =   TEXT("MTS-OUT");        // gw folder
    const UINT      nDefDays    =   1;                      // #days

    const TCHAR     chBackSlash =   TEXT('\\');             // back slash
    const LPTSTR    lpszPSTExt  =   TEXT("PST");             // PST extension
    const LPTSTR    lpszEXEExt  =   TEXT("EXE");            // EXE extension

    // argument indices into the argument flag array
    const UINT      iHelp1      =   0;                      // HELP index
    const UINT      iHelp2      =   1;                      // HELP index
    const UINT      iDays       =   2;                      // DAYS index
    const UINT      iFile       =   3;                      // FILE index
    const UINT      iFolder     =   4;                      // FOLDER index

    // # of command line flags
    const ULONG     nFlags      =   5;                      

    // Array of known flags for this program.
    const LPCTSTR rgpszFlags[nFlags]  =
    {
        TEXT("HELP"),   // help flag
        TEXT("?"),      // help flag
        TEXT("DAYS"),   // # days before today flag
        TEXT("FILE"),   // PST file name flag
        TEXT("FOLDER")  // gateway folder name flag
    };

    DEBUGPRIVATE("HrParseCommandLine()\n");

    hr = CHK_HrParseCommandLine(argc, argv,
                    lpProfile, lpPSTName, lpFolder, lpBeforeTime);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // If no arguments are passed in, print the syntax
    // message
    if ( argc < 2 )
    {
        DisplayUserMsg(
                IDS_USAGE);
        DisplayUserMsg(
                IDS_BLANK);
        DisplayUserMsg(
                IDS_USAGEPROF);
        DisplayUserMsg(
                IDS_USAGEDAYS);
        DisplayUserMsg(
                IDS_USAGEPST);
        DisplayUserMsg(
                IDS_USAGEFOLDER);
        DisplayUserMsg(
                IDS_USAGEHELP);
                
        hr = HR_LOG(E_INVALIDARG);
        
        goto cleanup;    
    }

    // Build the default default PST file
    // name from the fully-pathed executable name.
    dwRetVal = GetModuleFileName(
                NULL,      		// module handle (default is current application)
                lpszExeName,    // string buffer
                MAX_PATH);      // maximum length

    if ( dwRetVal == 0 )
    {
        INTERNAL_ERROR( TEXT("GetModuleFileName()"), dwRetVal);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cchExeName = lstrlen(lpszExeName);  // # characters in executable name
    lstrcpy(lpszPSTName, lpszExeName);

    // Replace the EXE extension with the PST extension.
    lpTemp = lpszPSTName + (cchExeName - lstrlen(lpszEXEExt));
    lstrcpy(lpTemp,
            lpszPSTExt);

    // Retrieve the default path name
    lstrcpy(lpszPath, lpszExeName);
    
    // Strip off the executable name.
    lpTemp = lpszPath + (cchExeName - 1);
    while ( *lpTemp != chBackSlash )
    {
        if ( lpTemp == lpszPath )
        {
            // back at the beginning.  This is an error.
            INTERNAL_ERROR( TEXT("HrParseCommandLine()"), E_FAIL);

            hr = HR_LOG(E_FAIL);
            goto cleanup;

        }   // if can't find back slash

        lpTemp--;

    }   // end while

    // When we get to here, lpTemp is pointing to the back slash.
    *(lpTemp + 1) = 0;  // null terminate path

    // loop throught the command line arguments
    // Start with the first user-supplied argument
    for ( iArg = 1; iArg < argc; iArg++ )
    {
        hr = _HrExpandCommandLineArgument(
            argv[iArg],     // argument user entered
            (LPTSTR *) rgpszFlags,     // array of recognized switches
            nFlags,         // number of known flags
            &iFlag,         // pointer to flag index into array
            &lpFlag,        // pointer to flag name
            &lpData);       // pointer to flag data
        
        if ( FAILED(hr) )
        {
            if ( hr == EDK_E_NOT_FOUND )
            {
                // Bad command line argument.
                // Display error message.
                DisplayUserMsg(
                    IDS_PARAMERR);

                hr = HR_LOG(E_INVALIDARG);
            
                goto cleanup;
            }

            else
            {
                INTERNAL_ERROR( TEXT("_HrExpandCommandLineArgument()"), hr);
                                    
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }            

        if ( (lpFlag == NULL) && (*lpData != 0) )
        {
            // This should be the gateway profile name
            // (The profile name doesn't have a flag.)
            lstrcpyn(lpProfile, lpData, MAX_PATH);

            continue;   // go on to next argument
        }

        // We have a valid flag.  Copy the data
        // to the appropriate parameter and test it.
        switch ( iFlag )
        {
            case iHelp1:
            case iHelp2:
                // user wants help message.
                // Print it out.
                DisplayUserMsg(
                        IDS_HELPDESCR);
                DisplayUserMsg(
                        IDS_BLANK);
                DisplayUserMsg(
                        IDS_USAGE);
                DisplayUserMsg(
                        IDS_BLANK);
                DisplayUserMsg(
                        IDS_USAGEPROF);
                DisplayUserMsg(
                        IDS_HELPDAYS1);
                DisplayUserMsg(
                        IDS_HELPDAYS2);
                DisplayUserMsg(
                        IDS_HELPDAYS3);
                DisplayUserMsg(
                        IDS_HELPDAYS4);
                DisplayUserMsg(
                        IDS_HELPDAYS5);
                DisplayUserMsg(
                        IDS_USAGEPST);
                DisplayUserMsg(
                        IDS_HELPPST);
                DisplayUserMsg(
                        IDS_USAGEFOLDER);
                DisplayUserMsg(
                        IDS_HELPFOLDER);
                DisplayUserMsg(
                        IDS_HELPHELP);

                hr = HR_LOG(E_INVALIDARG);

                goto cleanup;

            case iDays:
                // Check number of days variable
                if ( (lpData == NULL) || (*lpData == 0) )
                {
                    // Bad command line argument.
                    // Display error message.
                    DisplayUserMsg(
                        IDS_BADDAYS);

                    hr = HR_LOG(E_INVALIDARG);

                    goto cleanup;
                }

                // Make sure number of days is a valid decimal
                // number less than or equal to 9999.
                if ( lstrlen(lpData) > 4 )
                {
                    // number of days is greater than 9999.
                    DisplayUserMsg( 
                            IDS_BADDAYS);

                    hr = HR_LOG(E_INVALIDARG);

                    goto cleanup;
                }

                // check individual characters of days value
                lpTemp = lpData;
                while ( *lpTemp )
                {
                    if ( ! isdigit(*lpTemp) )
                    {
                        // number of days is not a non-negative
                        // integer!
                        DisplayUserMsg( 
                            IDS_BADDAYS);

                        hr = HR_LOG(E_INVALIDARG);

                        goto cleanup;
                    }

                    lpTemp++;

                }   // end while

                // Try to convert #days to an integer.
                nDays = atoi(lpData);

                fDaysFound = TRUE;  // user specified DAYS value

                break;
        
            case iFile:
                // check PST output file name
                if ( (lpData == NULL) || (*lpData == 0) )
                {
                    // invalid file name.
                    DisplayUserMsg( 
                            IDS_NOFILE);

                    hr = HR_LOG(E_INVALIDARG);

                    goto cleanup;
                }

                // Save PST file name
                if ( strchr(lpData, chBackSlash) == NULL )
                {
                    lstrcpyn(lpPSTName, lpszPath, MAX_PATH);
                    strncat(lpPSTName, lpData, MAX_PATH);
                }
                
                else
                {
                    // already have full path
                    lstrcpyn(lpPSTName, lpData, MAX_PATH);
                }

                break;

            case iFolder:
                // check gateway folder name
                if ( (lpData == NULL) || (*lpData == 0) )
                {
                    // invalid folder name.
                    DisplayUserMsg( 
                            IDS_NOFOLDER);

                    hr = HR_LOG(E_INVALIDARG);

                    goto cleanup;
                }

                // save folder name
                lstrcpyn(lpFolder, lpData, MAX_PATH);

                // let open folder call determine if its a valid
                // folder name.

                break;

            default:                
                // shouldn't happen!
                INTERNAL_ERROR( TEXT("HrParseCommandLine()"), E_FAIL);

                hr = HR_LOG(E_FAIL);
                goto cleanup;

        }   // end switch
    }   // end for

    // Check required parameters
    if ( *lpProfile == 0 )
    {
        DisplayUserMsg( 
                   IDS_NOPROFILE);

        hr = HR_LOG(E_INVALIDARG);

        goto cleanup;
    }
        
    // Handle default values.
    if ( !fDaysFound )
    {
        // use default days value (yesterday)
        nDays = nDefDays;
    }

    // Convert # days to a data and time.
    hr = HrComputeDate(nDays, lpBeforeTime);

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrComputeDate()"), hr);

        goto cleanup;
    }

    if ( *lpFolder == 0 )
    {
        // use default folder.
        lstrcpyn(lpFolder, lpszFolder, MAX_PATH); 
    }

    if ( *lpPSTName == 0 )
    {
        // use default PST name
        lstrcpyn(lpPSTName, lpszPSTName, MAX_PATH);
    }

    // Check to see if this file is valid
    // and can be created or overwritten
    hr = HrCheckFileName(lpPSTName);

    if ( FAILED(hr) )
    {
        // HrCheckFileName prints out error
        // messages.
        goto cleanup;
    }

    // We are done.

cleanup:

    RETURN(hr);

}

//$--HrCheckFileName----------------------------------------------
//
// DESCRIPTION: Checks to see if file exists.  If it does
//              prompts user as to whether or not to overwrite
//              it.  If file is valid file name and can be over-written,
//              returns NOERROR.  Otherwise, returns E_FAIL.
//
// INPUT:   lpFileName  --  file name to test for existence
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// ---------------------------------------------------------------
HRESULT HrCheckFileName(           // RETURNS: HRESULT
            IN LPTSTR lpFileName)   // file name to check
{
    HRESULT hr                  =   NOERROR;
    HANDLE  hFile               =   NULL;   // file handle
    DWORD   dwLastError         =   0;      // last Win32 error
    TCHAR   szLine[MAX_PATH]    =   {0};    // large input buffer

    DEBUGPRIVATE("HrCheckFileName()\n");

    // check input parameters
    hr = CHK_HrCheckFileName(lpFileName);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    hFile = CreateFile(lpFileName, 
                GENERIC_READ | GENERIC_WRITE,  
                0, 
                0,
                CREATE_NEW, 
                FILE_ATTRIBUTE_NORMAL, 
                0);

    if ( hFile == INVALID_HANDLE_VALUE )
    {
        dwLastError = GetLastError();   // Get windows error code
        if ( dwLastError == ERROR_FILE_EXISTS )
        {
            // File already exists.  Ask user is he/she wants to
            // overwrite it.
            while ( hFile == INVALID_HANDLE_VALUE )
            {
                DisplayUserMsg( 
                        IDS_OVERWRITEFILE,
                        lpFileName);

                if ( gets(szLine) == NULL )
                {
                    INTERNAL_ERROR( TEXT("gets()"), GetLastError());

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                switch ( szLine[0] )
                {
                    case TEXT('Y'):
                    case TEXT('y'):
                        // overwrite the file.
                        hFile = CreateFile(lpFileName, 
                                           GENERIC_READ | GENERIC_WRITE, 
                                           0, 
                                           0,
                                           TRUNCATE_EXISTING, 
                                           FILE_ATTRIBUTE_NORMAL, 
                                           0);

                        if ( hFile == INVALID_HANDLE_VALUE )
                        {
                            DisplayUserMsg( 
                            	IDS_OUTPUTERR,
                                lpFileName);

                            hr = HR_LOG(E_FAIL);

                            goto cleanup;
                        }

                        break;

                    case TEXT('n'):
                    case TEXT('N'):
                        // Give up!
                        DisplayUserMsg( 
                            IDS_USERCANCEL);

                        // This is not really an error.  The user
                        // just wishes to terminate the program early.
                        hr = HR_LOG(E_FAIL);

                        goto cleanup;

                    default:
                        // ask again!
                        continue;

                }   // end switch 
            }   // end while
        }   // end if file already exits.

        else
        {
            // some other file path or permission-type error
            DisplayUserMsg( 
                    IDS_OUTPUTERR, 
                    lpFileName);

            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

    }   // end if can't create new file

    // O.K. to overwrite file.
    // Delete the file just created.
    if ( hFile != INVALID_HANDLE_VALUE )
    {
        CLOSEHANDLE(hFile);

        (VOID)DeleteFile(lpFileName);
    }

cleanup:

    // close the opened file.
    CLOSEHANDLE(hFile);

    RETURN(hr);

}

//$--DisplayUserMsg----------------------------------------------------------
//
// DESCRIPTION: Utility to display message to command line user.
//
// INPUT: 		UINT        --  Resource string identifier
//
// NOTES:       This function can handle up to nine variable string arguments.
// 
// RETURNS:     nothing
//
// ----------------------------------------------------------------------------

VOID DisplayUserMsg(            // RETURNS: VOID
            IN UINT nResID,     // resource string identifier
            ...)                // additional arguments
{    
    INT     		nRetCode	= 	0;          // return value
    va_list 		vArgList	=   {0};        // variable argument list
	static 	HMODULE	hInst		=	NULL;		// application handle
	static	BOOL	fInit		=	FALSE;		// TRUE if hInst is initialized

    const   INT 	cbMsgLength	=   256;        // maximum length of printed messageso

	// LoadString message buffer
    TCHAR   szMessage[cbMsgLength]	=   TEXT(""); 

    DEBUGPRIVATE("DisplayUserMsg()\n");

    // No CHK_DisplayUserMsg() call.
    // We check arguments as we go, as we are already in an error state.

    // Check the instance handle passed in.
    if ( fInit == FALSE )
    {
		// Retrieve this applications module handle.
		hInst = GetModuleHandle(NULL);

		fInit = TRUE;

		if ( hInst == NULL )
		{
	        // Print out default error string.
    	    fprintf(stderr, "ERROR: Can't dipslay resource strings.\n");

	        HR_LOG(E_FAIL);

    	    goto cleanup;
    	}
	}

	if ( hInst == NULL )
	{
		// nothing to do
		goto cleanup;
	}

    nRetCode = LoadString(hInst, nResID, szMessage, cbMsgLength);

    if ( nRetCode == 0 )
    {
        // Print out default error string.
        fprintf(stderr, "ERROR: Can't load resource string %d.\n", nRetCode);

        HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Get an optional argument list pointer
    va_start(vArgList, nResID);

    // Print the message to standard out
    _vtprintf(szMessage,        // format string
            vArgList);          // variable argument list

    va_end(vArgList);

cleanup:

    // Return
    return;

}   // end DisplayUserMsg()

//$--HrComputeDate-----------------------------------------------------------
//
// DESCRIPTION: Computes the date of today minus the number of days passed
//              in and fills in the file time structure buffer passed in.
//
// OUTPUT:      lpSysFileTime   --  pointer to file time buffer
//
// RETURNS:     HRESULT --  NOERROR if O.K.,
//                          E_INVALIDARG if bad input.
//
// ---------------------------------------------------------------------------

static HRESULT HrComputeDate(                      // RETURNS: HRESULT
            IN  UINT uDaysBack,             // number of days before today
            OUT LPFILETIME lpSysFileTime)   // pointer to system file time
{
    HRESULT     hr              =   NOERROR;    // return code
    INT         iCounter        =   0;          // loop counter
    SYSTEMTIME  sLocalSysTime   =   {0};        // Local system time structure
    FILETIME    sLocalFileTime  =   {0};        // Local file time structure    
    DWORDLONG   dwlFileTime     =   0;          // file time converted to DWORDLONG

    const DWORDLONG dwlNum100nsPerDay = 864000000000; // number of 100 nanoseconds in one day!

    DEBUGPRIVATE("HrComputeDate\n");

    hr = CHK_HrComputeDate(uDaysBack, lpSysFileTime);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Compute desired system time of the before date/time variable
    // before which all gateway MTS-OUT messages are to be moved.
    // Algorithm:
    //  1) Today's date and time.
    //  2) Modify
    // from # days before today parameter passed in by user.
    // First, get the current system time and adjust it to the end
    // of today and convert that to a FILETIME value.  Then, convert the
    // FILETIME value to a DWORDLONG (64 bit) value.
    GetLocalTime(&sLocalSysTime);    // Get local time
    sLocalSysTime.wHour = 23;
    sLocalSysTime.wMinute = 59;
    sLocalSysTime.wSecond = 59;
    sLocalSysTime.wMilliseconds = 999;
    if ( sLocalSysTime.wDayOfWeek )
    {
        sLocalSysTime.wDayOfWeek--;
    }
    else
    {
        sLocalSysTime.wDayOfWeek = 6;    // Sunday to Saturday
    }
    SystemTimeToFileTime(&sLocalSysTime, &sLocalFileTime);   // local time to local file time
    LocalFileTimeToFileTime(&sLocalFileTime, lpSysFileTime);   // local file time to system file time
    dwlFileTime = ((DWORDLONG)((DWORDLONG) lpSysFileTime->dwLowDateTime) |
        (DWORDLONG)(((DWORDLONG)(((DWORDLONG)lpSysFileTime->dwHighDateTime) << 32)) & 0xFFFFFFFF00000000));

    // Subtract off the desired number of 100 nanoseconds from this mornings
    // time.
    // (The FILETIME structure measures time in 100 nanoseconds intervals.)
    // Then, convert this value back to a FILETIME value.
    dwlFileTime -= (DWORDLONG)(((DWORDLONG) uDaysBack) * dwlNum100nsPerDay);
    lpSysFileTime->dwLowDateTime = (DWORD) dwlFileTime;
    lpSysFileTime->dwHighDateTime = 
        (DWORD) (((DWORDLONG) (dwlFileTime >> 32)) & 0xFFFFFFFF);

    RETURN(hr);

}   // end HrComputeDate()

/*
 * EOF
 */
