// --lookup.c-------------------------------------------------------------------
//
//  A simple test driver for HrGWResolveAddress() & HrGWResolveProxy()
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

LPMAPISESSION lpSession        = NULL;
LPADRBOOK     lpAdrBook        = NULL;   // Pointer to address book
LPABCONT      lpGalABCont      = NULL;
ULONG         cbGalEid         = 0;      // count of bytes in GAL entry ID
LPENTRYID     lpGalEid         = NULL;   // pointer to GAL entry ID

static BOOL   fIsInit          = FALSE;

static BOOL   fInitializedMAPI = FALSE; // MAPI Initialized

#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

static char * rgpszArgArray[] = {
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))


//$--InitLookup-----------------------------------------------------------------
//  Initialize for address lookup
// -----------------------------------------------------------------------------
HRESULT HrInitLookup(                       // RETURNS: return code
    IN LPSTR lpszProfileName)               // MAPI profile name
{
    HRESULT hr        = NOERROR;
    HRESULT hrT       = NOERROR;
    SCODE   sc        = 0;
    ULONG   ulObjType = 0;

    DEBUGPUBLIC( "HrInitLookup()\n" );

    DEBUGACTION("Initializing MAPI\n");

    hrT = MAPIInitialize(NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    fInitializedMAPI = TRUE;

    hrT = MAPILogonEx(
        (ULONG) 0,
        lpszProfileName,
        NULL,
        MAPI_NEW_SESSION | MAPI_LOGON_UI | MAPI_EXTENDED | MAPI_NO_MAIL,
        &lpSession);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERTERROR(lpSession != NULL, "NULL lpSession variable");    

    hrT = MAPICALL(lpSession)->OpenAddressBook(
        lpSession,
        0,
        NULL, 
        AB_NO_DIALOG,
        &lpAdrBook);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERTERROR(lpAdrBook != NULL, "NULL lpAdrBook variable");

    hr = HrFindExchangeGlobalAddressList(
        lpAdrBook,
        &cbGalEid,
        &lpGalEid);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Open the global recipient container
    hrT = MAPICALL(lpAdrBook)->OpenEntry(
        lpAdrBook, 
        cbGalEid,
        lpGalEid,
        NULL,
        MAPI_DEFERRED_ERRORS,
        &ulObjType,
        (LPUNKNOWN FAR *)&lpGalABCont);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(ulObjType != MAPI_ABCONT)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    if(SUCCEEDED(hr))
    {
        fIsInit = TRUE;
    }
    else
    {
        if(fInitializedMAPI == TRUE)
        {
            MAPIFREEBUFFER(lpGalEid);

            ULRELEASE(lpGalABCont);

            ULRELEASE(lpAdrBook);

            ULRELEASE(lpSession);

            MAPIUninitialize();

            fInitializedMAPI = FALSE;
        }
    }

    RETURN(hr);
}


//$--HrUninitLookup------------------------------------------------------------
//  Free all global variables
// ----------------------------------------------------------------------------
HRESULT HrUninitLookup( void )      // RETURNS: return code
{
    HRESULT  hr = NOERROR;

    if(fIsInit == FALSE )
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    MAPIFREEBUFFER(lpGalEid);

    ULRELEASE(lpGalABCont);

    ULRELEASE(lpAdrBook);

    ULRELEASE(lpSession);
    
    fIsInit = FALSE;
        
cleanup:

    if(fInitializedMAPI == TRUE)
    {
        MAPIUninitialize();

        fInitializedMAPI = FALSE;
    }

    RETURN(hr);
}

//$--HrPrintAddress----------------------------------------------------------
// Prints the ADDRTYPE, DISPLAY_NAME & EMAIL_ADDRESS of a Recipient
// identified by a given Recipient ENTRYID
// --------------------------------------------------------------------------
HRESULT HrPrintAddress(         // RETURNS: return code
    IN BOOL      fMapiRecip,    // MAPI recipient
    IN ULONG     cbEntryID,     // count of bytes in entry ID
    IN LPENTRYID lpEntryID)     // pointer to entry ID
{
    HRESULT       hr        = NOERROR;  
    HRESULT       hrT       = NOERROR;
    ULONG         ulObjType = 0;
    ULONG         cValues   = 0;
    LPSPropValue  lpProps   = {0};
    LPMAPIPROP    lpRecip   = NULL;
    
    SizedSPropTagArray(5, sPropTags) =
    {
        5, 
        {
            PR_ENTRYID,
            PR_ADDRTYPE,
            PR_DISPLAY_NAME,
            PR_EMAIL_ADDRESS,
            PR_SEND_RICH_INFO
        }
    };

    DEBUGPUBLIC( "HrPrintAddress()\n" );
    
    // Open the Recipient object
    hrT = MAPICALL(lpSession)->OpenEntry(
        lpSession,
        cbEntryID,
        lpEntryID,
        NULL,
        MAPI_DEFERRED_ERRORS,
        &ulObjType,
        (LPUNKNOWN FAR *)&lpRecip); 

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Get the required properties of the user
    hrT = MAPICALL(lpRecip)->GetProps(
        lpRecip,
        (SPropTagArray *)&sPropTags,
        fMapiUnicode,
        &cValues,
        &lpProps); 

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }


    printf( " MAPI Recipient = %s\n", (fMapiRecip ? "TRUE" : "FALSE"));    
    printf( " Address Type   = \"%s\"\n",   lpProps[1].Value.LPSZ);
    printf( " Display Name   = \"%s\"\n",   lpProps[2].Value.LPSZ);
    printf( " Email Address  = \"%s\"\n\n", lpProps[3].Value.LPSZ);

    ASSERTERROR(
        lpProps[4].Value.b == fMapiRecip,
        "PR_SEND_RICH_INFO not equal to entry ID flag");

cleanup:

    MAPIFREEBUFFER(lpProps);

    ULRELEASE(lpRecip);

    RETURN(hr);
}


//$--main----------------------------------------------------------------------
//  Test driver main entry point.
//  
//  This program loops, until terminated by the user, prompting alternately 
//  for input values to HrGWResolveAddress() and HrGWResolveProxy()
//  and prints the resolved results to a default output stream.
// ----------------------------------------------------------------------------

#define    MAX_INPUT_SZ        1024

int main(int argc, char *argv[])
{
    HRESULT    hr                       = NOERROR;
    SCODE      sc                       = 0;
    CHAR       szInput[MAX_INPUT_SZ]    = "";
    LPSTR      lpszProfileName          = NULL;
    ULONG      cbEntryID                = 0;
    LPENTRYID  lpEntryID                = NULL;
    LPSTR      lpszProxyAddr            = NULL;
	int        i                        = 0;
	LPSTR      lpszArgument             = NULL;
	LPSTR      lpszValue                = NULL;
	BOOL       fFinishedCommandLine     = FALSE;
    BOOL       fMapiRecip               = FALSE;

    printf( "\n" );

	// If they didn't give command line args then print a usage message.

	if (argc < 2)
	{
	    printf("USAGE: LOOKUP Profile\n\n");
		printf("  [Flags]        Enter LOOKUP /? for details\n");
		goto cleanup;
	}

	// If they used /? or /HELP (the only defined flags with labels) then 
	// print a help message.

	for (i = 1; i < argc; i++)
	{
		hr = _HrExpandCommandLineArgument(
			argv[i], rgpszArgArray, ARGARRAYSIZE, NULL, &lpszArgument, &lpszValue);

		if (SUCCEEDED(hr) && lpszArgument && 
			(!_stricmp(lpszArgument,ARG_HELP1) || 
			!_stricmp(lpszArgument,ARG_HELP2)))
		{
			printf("Profile Lookup sample.\n\n");
			printf("USAGE: LOOKUP Profile\n\n");
			printf("  Profile        Name of profile to look up\n");
			printf("  /HELP or /?    Display help screen\n");
			goto cleanup;
		}
	}

    // Get MAPI profile name from command line

	if (argc > 2)
	{
		fprintf(stderr, "ERROR: too many command line arguments\n");
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	hr = _HrExpandCommandLineArgument(
		argv[1], rgpszArgArray, ARGARRAYSIZE, NULL, &lpszArgument, &lpszProfileName);

	if (FAILED(hr) || lpszArgument)
	{
		fprintf(stderr, "ERROR: unknown command line argument %s\n", argv[1]);
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	fFinishedCommandLine = TRUE;

	// Do initialization

    hr = HrInitLookup(lpszProfileName);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    //  Loop until terminated by user.
    //
    for(;;)
    {
        int iTmp = 0;

        printf( "\n\n"
                 "Enter address to be resolved in <type>:<value> format\n"
                 "or EXIT to terminate.\n"
                 "NOTE:  The address that you type must match exactly,\n"
                 "       including case.\n"
                 ": ");

        //
        //  Get next line of number.  EOF = terminate.
        //
        if (_fgetts( szInput, MAX_INPUT_SZ, stdin ) == NULL)
            break;

        //
        // trim the trailing '\n'
        //
        iTmp = strlen(szInput);

        if (iTmp > 0 && szInput[iTmp-1] == '\n')
            szInput[iTmp-1] = 0;

        //
        //  Check for exit.
        //
        if (_stricmp( szInput, TEXT("EXIT")) == 0)
            break ;

        fMapiRecip = FALSE;

        //
        //  Resolve the address.
        //

        hr = HrGWResolveAddress(
            lpGalABCont,
            szInput,
            &fMapiRecip,
            &cbEntryID,
            &lpEntryID);

        if(SUCCEEDED(hr))
        {
            printf("\n") ;

            hr = HrPrintAddress(fMapiRecip, cbEntryID, lpEntryID);

            if(FAILED(hr))
            {
                printf("ERROR: could not print address [%08lX]\n", hr);
                continue;
            }

            printf(" Enter address type to be resolved\n"
                     " :");

            if(gets(szInput) != NULL)
            {
                printf("\n") ;

                fMapiRecip = FALSE;

                //
                //  Check for exit.
                //
                if (_stricmp( szInput, TEXT("EXIT")) == 0)
                    break;

                hr = HrGWResolveProxy(
                    lpAdrBook,
                    cbEntryID,
                    lpEntryID,
                    szInput,
                    &fMapiRecip,
                    &lpszProxyAddr);

                printf("\n");

                if(FAILED(hr))
                {
        		    fprintf(stderr, "ERROR: could not resolve proxy [%08lX]\n", hr);
                }
                else
                {
                    printf( " MAPI Recipient = %s\n", (fMapiRecip ? "TRUE" : "FALSE"));
                    printf( " Resolved Proxy = %-30s\n", lpszProxyAddr);

                    MAPIFREEBUFFER(lpszProxyAddr);
                }
            }
        }
        else
        {
		    fprintf(stderr, "ERROR: could not resolve address [%08lX]\n", hr);
        }
        
        MAPIFREEBUFFER(lpEntryID);
    }
            
cleanup:

    MAPIFREEBUFFER(lpEntryID);

    // Terminate the MAPI session properly

    if(fIsInit == TRUE)
    {
        hr = HR_LOG(HrUninitLookup());
    }

	// Display results of operation.

	if (fFinishedCommandLine)
	{
		if (SUCCEEDED(hr))
		{
			fprintf(stderr, "Done.\n");
		}
		else
		{
			fprintf(stderr, "Lookup not successful.\n");
		}
	}

    // return exit code
    return _nEcFromHr(hr);

}
