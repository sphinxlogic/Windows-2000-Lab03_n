// --MBLSampl.c-----------------------------------------------------------------
//
//  Privileged Access to logon and off of any message store.
//  
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "edkguid.h"
#include "mblsampl.chk"

#define TPRINTF(x)          _tprintf(TEXT(x))
#define TPRINTF1(x,y)       _tprintf(TEXT(x),(y))

#define MAX_INPUT_SZ        300  //Max. Terminal Input
#define MAX_MESSAGE_HDRS    50   //Max. messages per query

// Arguments from command line
BOOL    fHelpRequested      = FALSE;
LPTSTR  lpszProfileName     = NULL;
LPTSTR  lpszPassword        = NULL;

// This gets set to a string as it moves through the code.  If we fail before 
// interacting with the user then this will contain the reason.
LPTSTR  lpszReasonForFailure = TEXT( "ERROR: Unknown\n");

//$--HrInitialize---------------------------------------------------------------
//  Initialize the application by initializing MAPI, Logging on, and opening the
//  Exchange message store.
// -----------------------------------------------------------------------------
static HRESULT HrInitialize(                    // RETURNS: return code
    IN  LPTSTR lpszProfileName,     // MAPI profile name
    IN  LPTSTR lpszPassword,        // Profile password
    OUT LPMAPISESSION *lpplhSession,// ptr to MAPI session handle ptr.
    OUT LPMDB  *lppMDB)             // ptr to message store ptr.
{
    HRESULT     hr      = E_FAIL;
    ULONG       cbeid   = 0;    // count of bytes in entry ID
    LPENTRYID   lpeid   = NULL; // Entry ID of Exchange store

    DEBUGPRIVATE( "HrInitialize()");

    lpszReasonForFailure = TEXT( "ERROR: HrInitialize parameters are bad.\n");    
    hr = CHK_HrInitialize( lpszProfileName, lpszPassword, lpplhSession, lppMDB);
    if( FAILED( hr))
        RETURN( hr);

    lpszReasonForFailure = TEXT( "ERROR: Could not initialize MAPI.\n");    
    DEBUGACTION( "Initializing MAPI");
    hr = MAPIInitialize( NULL);
    if( FAILED( hr))
        goto cleanup;
    
    lpszReasonForFailure = TEXT( "ERROR: Could not logon using the profile that was given.\n");
    DEBUGACTION( "Logon to MAPI");
    *lpplhSession = NULL;
    hr = (HRESULT) MAPILogonEx( 
            0, 
            lpszProfileName,
            lpszPassword,
            MAPI_NO_MAIL | MAPI_NEW_SESSION | MAPI_LOGON_UI, 
            lpplhSession);
    
    if( FAILED( hr))
        goto cleanup;
    ASSERTERROR( *lpplhSession != NULL, "Null lphSession!" );

    // Open the Exchange message store.
    lpszReasonForFailure = TEXT( "ERROR: Could not open the Exchange message store.\n");
    DEBUGACTION( "Opening Exchange Message Store");
    hr = HrOpenExchangePrivateStore( *lpplhSession, lppMDB);
    if( FAILED(hr))
        goto cleanup;

    ASSERTERROR( *lppMDB != NULL, "NULL lppMDB pointer");

	lpszReasonForFailure = TEXT( "ERROR: Unknown\n");
    hr = NOERROR;

cleanup:
    MAPIFREEBUFFER( lpeid);
    
    if( FAILED( hr))
    {
        if( *lpplhSession)
        {   // Logoff a MAPI session
            MAPICALL((*lpplhSession))->Logoff( *lpplhSession, 0, 0, 0);
            ULRELEASE(*lpplhSession);
        }
        MAPIUninitialize();
    }

    RETURN( hr);
}

//$--HrShutDown-----------------------------------------------------------------
//  Shutdown the application by closing the Exchange message store, logging off, 
//  and uninitializing MAPI.
// -----------------------------------------------------------------------------
static HRESULT HrShutDown(                     // RETURNS: return code
    IN OUT LPMAPISESSION *lpplhSession, // ptr to MAPI session handle ptr.
    IN OUT LPMDB  *lppMDB)              // ptr to message store ptr.
{
    HRESULT hr;

    DEBUGPRIVATE( "HrShutDown()");
    
    hr = CHK_HrShutDown( lpplhSession, lppMDB);
    if( FAILED( hr))
        RETURN( hr);

    ULRELEASE( *lppMDB);

    // Logoff a MAPI session
    MAPICALL((*lpplhSession))->Logoff( *lpplhSession, 0, 0, 0);
    ULRELEASE(*lpplhSession);
   
    MAPIUninitialize();

    RETURN( NOERROR);
}

//$--HrGetMsgList-----------------------------------------------------------
//  Returns the next message list (<=cMaxNRows) in a given message table;
// -----------------------------------------------------------------------------
static HRESULT HrGetMsgList(
    IN  LPMAPITABLE lpTable,    // ptr.to the contents table
    IN  ULONG       cMaxNRows,  // Max.# of rows to return
    OUT LPSRowSet   *lppRows )  // ptr.to address variable for SRowSet
{
    HRESULT      hr  = NOERROR;
        
    DEBUGPRIVATE( "HrGetMsgList()" );

    hr = CHK_HrGetMsgList( lpTable, cMaxNRows, lppRows);
    if( FAILED( hr))
        RETURN( hr);

    // Get the next list of messages in the folder
    hr = MAPICALL(lpTable)->QueryRows( lpTable, cMaxNRows, 0L, lppRows );
    if( SUCCEEDED( hr) && (!(*lppRows) || (*lppRows)->cRows == 0))
    {
        FREEPROWS(*lppRows);
        hr = HR_LOG( EDK_E_END_OF_FILE);
    }

    RETURN(hr);
}

//$--HrReadMailboxHeaders-------------------------------------------------------
//  Reads and displays the subject of the mail messages found in the MDB.
// -----------------------------------------------------------------------------
static HRESULT HrDispMailboxSubjects(
    IN LPMDB  lpMDB)                // Message store ptr.
{
    HRESULT         hr                  = NOERROR;
    unsigned        iMsgIndx            = 0;
    unsigned        nCnt                = 0;
    ULONG           cbeid               = 0L;
    ULONG           ulObjType           = 0L;
    LPENTRYID       lpeid               = NULL;
    LPMAPIFOLDER    lpInboxFolder       = NULL;     // ptr to Inbox folder
    LPMAPITABLE     lpContentsTbl       = NULL;     // ptr to Contents folder table
    LPSRowSet       lpInRowSet          = NULL;     // ptr to Inbox rows
    LPSPropValue    lpProps             = NULL;     // Ptr to property array.

    static const SizedSSortOrderSet(1L,sSortPrioSet) = 
        { 1L, 0L, 0L, { PR_CLIENT_SUBMIT_TIME, TABLE_SORT_ASCEND}};

    static const SizedSPropTagArray(2L,sPropColumns) =
        { 2L, {PR_SUBJECT, PR_ENTRYID}};

    DEBUGPRIVATE( "HrDispMailboxSubjects()");

    hr = CHK_HrDispMailboxSubjects( lpMDB);
    if( FAILED( hr))
        RETURN( hr);

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Initialize an inbox folder object.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Find default (inbox) folder.
    hr = HrMAPIFindInbox( lpMDB, &cbeid, &lpeid);
    if( FAILED(hr))
        goto cleanup;
    ASSERTERROR ( lpeid != NULL, "NULL lpeid");
    
    // Open the default (inbox) folder.
    hr = MAPICALL( lpMDB)->OpenEntry( lpMDB, cbeid, lpeid, NULL,
        MAPI_MODIFY|MAPI_DEFERRED_ERRORS, &ulObjType, (LPUNKNOWN*)&lpInboxFolder);
    if( FAILED( hr))
        goto cleanup;
    if( ulObjType != MAPI_FOLDER)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Now that we have a folder we can initialize a contents table
// to look through.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Get the contents table for the folder.
    hr = MAPICALL( lpInboxFolder)->GetContentsTable(
        lpInboxFolder, MAPI_DEFERRED_ERRORS, &lpContentsTbl);
    if( FAILED( hr))
        goto cleanup;

    // Set the columns to return.
    hr = MAPICALL( lpContentsTbl)->SetColumns( lpContentsTbl, (LPSPropTagArray) &sPropColumns, 0L);
    if(FAILED(hr))
        goto cleanup;

    // Sort the table.
    hr = MAPICALL( lpContentsTbl)->SortTable( lpContentsTbl, (LPSSortOrderSet) &sSortPrioSet, 0L);
    if(FAILED(hr))
        goto cleanup;
    
    // Position to the beginning of the contents table.
    hr = MAPICALL( lpContentsTbl)->SeekRow( lpContentsTbl, BOOKMARK_BEGINNING, 0, NULL);
    if( FAILED(hr))
        goto cleanup;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Contents table has been initialize so lets display it.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Display INBOX subjects until end of table reached.
    while( TRUE)
    {   // Read a group of message headers from the contents table.
        hr = HrGetMsgList( lpContentsTbl, MAX_MESSAGE_HDRS, &lpInRowSet);
        if( hr == EDK_E_END_OF_FILE)
            break;
        if( FAILED( hr))
            goto cleanup;;
            
        ASSERTERROR( lpInRowSet != NULL, "NULL lpInRowSet!");
        
        // Process all messages in the current table.
        for( iMsgIndx = 0; iMsgIndx < lpInRowSet->cRows; ++iMsgIndx )
        {   // Display the subject name.
			if( lpInRowSet->aRow[iMsgIndx].cValues )
			{
				lpProps = lpInRowSet->aRow[iMsgIndx].lpProps;

				if(lpProps->ulPropTag == PR_SUBJECT )
				{
		            if(lpProps->Value.LPSZ == NULL || *(lpProps->Value.LPSZ) == 0)
			            printf( "  SUBJECT: (empty).\n");
				    else
					    printf( "  SUBJECT: %s\n", lpProps->Value.LPSZ);
				}
				else
				{
					//When the subject field was left empty while mail was sent,
					//lpProps->ulProTag may not be PR_SUBJECT, so print subject as empty

					printf( "  SUBJECT: (empty).\n");

					ASSERTERROR( FALSE, "Invalid property returned!");
				}

				nCnt ++;
			}
        }
 
        // Free the current message list structure.
        FREEPROWS( lpInRowSet);
    }
    
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// All done displaying the subjects.  Time to clean up.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    hr = NOERROR;

cleanup:
    if( hr == MAPI_E_NO_ACCESS)
        printf( "  Insufficient access rights.\n");
    else if( nCnt == 0)
        printf( "  No messages found in this mailbox.\n");

    ULRELEASE( lpContentsTbl);
    ULRELEASE( lpInboxFolder);
    MAPIFREEBUFFER( lpeid);
    
    RETURN( hr);
}

//$--PrintUsage-----------------------------------------------------------------
// Print usage text
// -----------------------------------------------------------------------------
static VOID PrintUsage (
    IN	LPTSTR  lpszAppName )
{
    LPTSTR  baseName = NULL;

    DEBUGPRIVATE ("PrintUsage()");

    baseName = strrchr (lpszAppName, '\\');

    if (baseName)
        baseName++;
    else
        baseName = lpszAppName;

    printf ("Privileged Access to Message Store Example\n" \
            "\n" \
            "USAGE: %s [/?] profile [password]\n",
            baseName);

}

//$--PrintHelp------------------------------------------------------------------
// Print help text
// -----------------------------------------------------------------------------
static VOID PrintHelp (
    IN	LPTSTR  lpszAppName )
{
    DEBUGPRIVATE ("PrintHelp()");

    PrintUsage (lpszAppName);

    printf ("\n" \
            "   /?,/HELP    show help information\n" \
            "   profile     the MAPI profile name for logon\n" \
            "   password    the password associated with the profile\n");
}

//$--HrParseCommandLine---------------------------------------------------------
// Simple command line parsing
// -----------------------------------------------------------------------------
static HRESULT HrParseCommandLine (
    IN  int     argc,
    IN  char    **argv )
{
    HRESULT     hr = NOERROR;
    LPTSTR      pszArgument = NULL;
    int         i = 0;
    
    DEBUGPRIVATE ("HrParseCommandLine()");

    hr = CHK_main (argc, argv);
    if (FAILED(hr))
        RETURN (hr);
        

    if (argc < 2) {
        PrintUsage(argv[0]);
        printf ("\nUse /? for help details\n");
        fHelpRequested = TRUE;
        goto cleanup;
    }

    // Scan first for /? or /HELP
    for (i = 1; i < argc; i++)
    {
        pszArgument = argv[i];
        if (*pszArgument == '/' || *pszArgument == '-')
        {
            pszArgument++;
            if (*pszArgument && (*pszArgument == '?' ||
                _tcsnicmp (pszArgument, TEXT("HELP"), _tcslen (pszArgument)) == 0))
            {
                PrintHelp (argv[0]);
                fHelpRequested = TRUE;
                goto cleanup;
            }
            
            // We only recognize /? or /HELP
            printf ("ERROR: Unknown command flag '/%s'\n", pszArgument);
            hr = HR_LOG (E_FAIL);
            goto cleanup;
        }
    }

    if (argc > 3)
    {
        printf ("ERROR: Too many arguments on command line\n");
        hr = HR_LOG (E_FAIL);
        goto cleanup;
    }

    lpszProfileName = argv[1];

    if (argc == 3)
        lpszPassword = argv[2];

cleanup:
    RETURN (hr);
}
        
//$--main-----------------------------------------------------------------------
// Initialize the application, loop on asking user for mailboxes and display 
// their subject properties.
// -----------------------------------------------------------------------------
int main( int argc, char *argv[])
{
    HRESULT     hr                      = NOERROR;
    TCHAR       szMailbox[MAX_INPUT_SZ] = TEXT("");
    TCHAR       szServer[MAX_INPUT_SZ]  = TEXT("");
    LPENTRYID   lpEntryID               = NULL;
    LPMDB       lpMDB                   = NULL;     // Message store ptr.
    LPMAPISESSION lplhSession           = NULL;     // MAPI session handle ptr.
    LPMDB       lpMailboxMDB            = NULL;     // Mailbox message store ptr.
    ULONG       cStrLen                 = 0L;


    hr = HrParseCommandLine (argc, argv);
    if (FAILED(hr) || fHelpRequested)
        goto cleanup;

    hr = HrInitialize( lpszProfileName, lpszPassword, &lplhSession, &lpMDB);
    if( FAILED( hr))
    {
        printf( lpszReasonForFailure);        
        goto cleanup;
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Loop until terminated by user.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    while( TRUE)
    {
        TCHAR *pNewLine;

        printf( "\n---------------------------------------------------------------------------\n"
                "Enter the name of the SERVER that contains the mail box\n"
                "or EXIT to terminate.\n"
                "EXAMPLE: /O=<Organization>/OU=<Site>/CN=Configuration/CN=Servers/CN=<ServerName>\n"
                ": ");
        
        // Get next address.  EOF = terminate.
        if( _fgetts( szServer, MAX_INPUT_SZ, stdin) == NULL)
            break;

        // Trim the trailing newline ('\n').
        pNewLine = _tcschr( szServer, '\n');
        if( pNewLine != NULL)
            *pNewLine = 0;
        
        //  Check for exit.
        if( _tcsicmp( szServer, TEXT( "EXIT")) == 0)
            break;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        printf( "\n\n"
                "Enter the name of the mail box to access\n"
                "or EXIT to terminate.\n"
                "EXAMPLE: /O=<Organization>/OU=<Site>/CN=Recipients/CN=<MailboxName>\n"
                ": ");
        
        // Get next address.  EOF = terminate.
        if( _fgetts( szMailbox, MAX_INPUT_SZ, stdin) == NULL)
            break;
            
        // Trim the trailing newline ('\n').
        pNewLine = _tcschr( szMailbox, '\n');
        if( pNewLine != NULL)
            *pNewLine = 0;
        
        //  Check for exit.
        if( _tcsicmp( szMailbox, TEXT( "EXIT")) == 0)
            break;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // Change Server DN to Message Store DN by adding next container in heirarchy.
        // Don't need to do this if '/cn=' has already been supplied.
         
        cStrLen = _tcslen( szServer);
    
        if( cStrLen >= _tcslen(TEXT("/cn=NULL")) &&
            ( _tcsicmp( &szServer[cStrLen - _tcslen(TEXT("/cn="))], TEXT("/cn=")) != 0 &&
              _tcsicmp( &szServer[cStrLen - _tcslen(TEXT("/cn=NULL"))], TEXT("/cn=NULL")) != 0))
        {
            _tcsncat( szServer, TEXT("/cn=Microsoft Private MDB"), MAX_INPUT_SZ - cStrLen);
        }
        
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // Logon to the mailbox specified by the user.
        hr = HrMailboxLogon( lplhSession, lpMDB, szServer, szMailbox, &lpMailboxMDB);
        if( FAILED( hr))
        {
            switch( hr)
            {
                case EDK_E_NOT_FOUND:
                    printf( "\nYou do not have permission to access this server\n"
                            "or the expected registry key does not exist.\n");
                    break;

                default:
                    printf( "\nFailed to logon to the mailbox:\n"
                            "  Server:  %s\n"
                            "  Mailbox: %s\n", szServer, szMailbox);
            }
        }
        else            
        {   // Display the subject property of the messages found in the mailbox.
            hr = HrDispMailboxSubjects( lpMailboxMDB);
            if( FAILED( hr));

            // Logoff the mailbox.
            hr = HrMailboxLogoff( &lpMailboxMDB);
            if( FAILED( hr));
        }
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Clean up
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -                 

    // Terminate the MAPI session properly.
    hr = HrShutDown( &lplhSession, &lpMDB);
    if( FAILED( hr));

cleanup:
    // return exit code
    return _nEcFromHr(hr) ;
}

// -----------------------------------------------------------------------------
