// --track.c--------------------------------------------------------------------
//
// Gateway message tracking sample application.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

#define MAX_INPUT_SIZ   1024

#define MAX_RECIPIENTS  7

PVOID       pvSession                           = NULL;

UINT        nEventType                          = 0;

SYSTEMTIME  stEvent                             = {0};

TCHAR       szGatewayName[MAX_INPUT_SIZ+1]      = {0};

TCHAR       szPartnerName[MAX_INPUT_SIZ+1]      = {0};

TCHAR       szMtsID[MAX_INPUT_SIZ+1]            = {0};

TCHAR       szSubjectMtsID[MAX_INPUT_SIZ+1]     = {0};

TCHAR       szRemoteID[MAX_INPUT_SIZ+1]         = {0};

TCHAR       szOriginatorName[MAX_INPUT_SIZ+1]   = {0};

INT         nPriority                           = 0;

INT         nLength                             = 0;

INT         nSeconds                            = 0;

INT         nCost                               = 0;

INT         cRecipients                         = 0;

TCHAR       szRecip1[MAX_INPUT_SIZ+1]           = {0};
TCHAR       szRecip2[MAX_INPUT_SIZ+1]           = {0};
TCHAR       szRecip3[MAX_INPUT_SIZ+1]           = {0};
TCHAR       szRecip4[MAX_INPUT_SIZ+1]           = {0};
TCHAR       szRecip5[MAX_INPUT_SIZ+1]           = {0};
TCHAR       szRecip6[MAX_INPUT_SIZ+1]           = {0};
TCHAR       szRecip7[MAX_INPUT_SIZ+1]           = {0};

LPTSTR      lpszRecipients[MAX_RECIPIENTS]      = {0};

static BOOL fInitializedMAPI                    = FALSE;

#include "track.chk"

//
// Names of Command Line Arguments
//

#define ARG_SERVER			"SERVER"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_SERVER,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char szServer[MAX_PATH+1]				= {0};
BOOL fDisplayedHelp						= FALSE;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: TRACK [Flags]\n\n");
	printf("  [Flags]        Enter TRACK /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Message Tracking sample.\n\n");
	printf("USAGE: TRACK [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /SERVER=             Server computer name\n");
	printf("\n");
	printf("  Optional Flags\n");
	printf("  /HELP or /?          Display help\n");

	fDisplayedHelp = TRUE;
}

//$--HrConfig-------------------------------------------------------------------
//  Read configuration from command line.
// -----------------------------------------------------------------------------
HRESULT HrConfig(           // RETURNS: return code
    IN int argc,            // number of arguments on command line
    IN char *argv[])        // array of command line arguments
{
    HRESULT		hr				= NOERROR;
    HRESULT		hrT				= NOERROR;
	char *		pszArgument		= NULL;
	char *		pszValue		= NULL;
    int			i				= 0;

	DEBUGPRIVATE("HrConfig()\n");

	// If there are no command line arguments then show a usage message.

	if (argc < 2)
	{
		ShowUsage();
		hr = E_FAIL;
		goto cleanup;
	}

	// Do an initial check for /? or /HELP.  If found, show a help message 
	// and don't do any other parsing.

	for (i = 1; i < argc; i++)
	{
		hr = _HrExpandCommandLineArgument(
			argv[i], rgpszArgArray, ARGARRAYSIZE, NULL, &pszArgument, &pszValue);

		if (SUCCEEDED(hr) && pszArgument && 
			(!_stricmp(pszArgument,ARG_HELP1) || 
			!_stricmp(pszArgument,ARG_HELP2)))
		{
			ShowHelp();
			hr = E_FAIL;
			goto cleanup;
		}
	}

	// Loop through and parse all the command line arguments.

	for (i = 1; i < argc; i++)
	{
		hrT = _HrExpandCommandLineArgument(
			argv[i], rgpszArgArray, ARGARRAYSIZE, NULL, &pszArgument, &pszValue);

		if (FAILED(hrT))
		{
			hr = hrT;

			if (hr == EDK_E_NOT_FOUND)
			{
				fprintf(stderr, "ERROR: unknown command line flag: %s\n", 
					argv[i]);
				continue;
			}
			else
			{
				fprintf(stderr, "ERROR: unable to parse command line.\n");
				goto cleanup;
			}
		}

		// Parse flag arguments that don't take a value.

		else if (pszArgument != NULL && pszValue == NULL)
		{
			// Other flag (must take a value).
			fprintf(stderr, "ERROR: flag /%s requires a value\n", 
				pszArgument);
			hr = HR_LOG(E_FAIL);
		}

		// Parse flag arguments that take a value.

		else if (pszArgument != NULL && pszValue != NULL)
		{
			if (!_stricmp(pszArgument,ARG_SERVER))
			{				   
				strncpy(szServer, pszValue, MAX_PATH);
			}

			// Other flag (must not take a value).

			else
			{
				fprintf(stderr, "ERROR: flag /%s does not take a value\n", 
					pszArgument);
				hr = HR_LOG(E_FAIL);
			}
		}

		// Catch unknown arguments.

		else
		{
			fprintf(stderr, "ERROR: unknown argument %s\n", argv[i]);
			hr = HR_LOG(E_FAIL);
		}
	}

	// Make sure we have all the info we need.

	if (SUCCEEDED(hr))
	{
	    if (szServer[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SERVER);
			hr = HR_LOG(E_FAIL);
		}
        else
        {
            DWORD dwService      = 0;
            DWORD dwCurrentState = 0;

            hr = HrGetExchangeServiceStatus(
                szServer,
                EXCHANGE_SA,
                &dwCurrentState);

            if(FAILED(hr))
            {
			    fprintf(
			        stderr,
			        "ERROR: please start Exchange system attendant on %s\n",
			        szServer);
			    hr = HR_LOG(E_FAIL);
            }
        }
	}

cleanup:
    RETURN(hr);
}

//$--HrDoEnterString------------------------------------------------------------
//  Enter a string.
// -----------------------------------------------------------------------------
HRESULT HrDoEnterString(                // RETURNS: return code
    IN LPTSTR lpszPrompt,               // prompt
    OUT LPTSTR lpszString)              // string buffer
{
    HRESULT hr                       = NOERROR;
    TCHAR   szInput[MAX_INPUT_SIZ+1] = {0};

    hr = CHK_HrDoEnterString(
        lpszPrompt,
        lpszString);

    if(FAILED(hr))
        RETURN(hr);

    lpszString[0] = 0;

    printf("\n%s: ", (lpszPrompt != NULL ? lpszPrompt : ""));

    if(gets(szInput) == NULL)
    {
        hr = HR_LOG(E_FAIL);

        printf("\nERROR: gets() failed\n");
    }
    else
    {
        strncpy(lpszString, szInput, MAX_INPUT_SIZ);
        lpszString[MAX_INPUT_SIZ] = 0;
    }

    RETURN(hr);
}

//$--HrDoEnterNumber------------------------------------------------------------
//  Enter a number.
// -----------------------------------------------------------------------------
HRESULT HrDoEnterNumber(                // RETURNS: return code
    IN LPTSTR lpszPrompt,               // prompt
    IN BOOL fAllowNegative,             // TRUE=allow negative number
    OUT LONG *lplNumber)                // number
{
    HRESULT hr                       = NOERROR;
    TCHAR   szInput[MAX_INPUT_SIZ+1] = {0};
    LONG    lNumber                  = 0;
    LONG    cMatch                   = 0;

    hr = CHK_HrDoEnterNumber(
        lpszPrompt,
        fAllowNegative,
        lplNumber);

    if(FAILED(hr))
        RETURN(hr);

    *lplNumber = 0;

    printf("\n%s: ", (lpszPrompt != NULL ? lpszPrompt : ""));

    if(gets(szInput) == NULL)
    {
        hr = HR_LOG(E_FAIL);

        printf("\nERROR: gets() failed\n");
    }
    else
    {
        cMatch = sscanf(szInput, "%ld", &lNumber);
        if (cMatch == 0 || cMatch == EOF)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if (!fAllowNegative && lNumber < 0)
        {
            printf("ERROR: negative number not allowed\n");
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        *lplNumber = lNumber;
    }

cleanup:

    RETURN(hr);
}

//$--DoEnterCommand-------------------------------------------------------------
//  Enter a command.
// -----------------------------------------------------------------------------
void DoEnterCommand(void)
{
    ULONG   ulInput                  = 0;
    TCHAR   szInput[MAX_INPUT_SIZ+1] = {0};
    ULONG   i                        = 0;

    nEventType = 0;

    ZeroMemory(&stEvent, sizeof(SYSTEMTIME));

    ZeroMemory(szGatewayName ,MAX_INPUT_SIZ+1);

    ZeroMemory(szPartnerName ,MAX_INPUT_SIZ+1);

    ZeroMemory(szMtsID, MAX_INPUT_SIZ+1);

    ZeroMemory(szSubjectMtsID, MAX_INPUT_SIZ+1);

    ZeroMemory(szRemoteID, MAX_INPUT_SIZ+1);

    ZeroMemory(szOriginatorName, MAX_INPUT_SIZ+1);

    nPriority   = 0;

    nLength     = 0;

    nSeconds    = 0;

    nCost       = 0;

    cRecipients = 0;

    ZeroMemory(szRecip1, MAX_INPUT_SIZ+1);

    ZeroMemory(szRecip2, MAX_INPUT_SIZ+1);

    ZeroMemory(szRecip3, MAX_INPUT_SIZ+1);

    ZeroMemory(szRecip4, MAX_INPUT_SIZ+1);

    ZeroMemory(szRecip5, MAX_INPUT_SIZ+1);

    ZeroMemory(szRecip6, MAX_INPUT_SIZ+1);

    ZeroMemory(szRecip7, MAX_INPUT_SIZ+1);

    for(;;)
    {
        ULONG ulChoice = 0;

        printf("\nMENU:\n");
        printf("\t 1. event type      [%u]\n", nEventType);
        printf("\t 2. gateway name    [%s]\n", szGatewayName);
        printf("\t 3. partner name    [%s]\n", szPartnerName);
        printf("\t 4. MTS-ID          [%s]\n", szMtsID);
        printf("\t 5. subject MTS-ID  [%s]\n", szSubjectMtsID);
        printf("\t 6. Remote-ID       [%s]\n", szRemoteID);
        printf("\t 7. originator name [%s]\n", szOriginatorName);
        printf("\t 8. priority        [%u]\n", nPriority);
        printf("\t 9. length          [%u]\n", nLength);
        printf("\t10. seconds         [%u]\n", nSeconds);
        printf("\t11. cost            [%u]\n", nCost);
        printf("\t12. #recipients     [%u]\n", cRecipients);
        printf("\t13. recipient #1    [%s]\n", szRecip1);
        printf("\t14. recipient #2    [%s]\n", szRecip2);
        printf("\t15. recipient #3    [%s]\n", szRecip3);
        printf("\t16. recipient #4    [%s]\n", szRecip4);
        printf("\t17. recipient #5    [%s]\n", szRecip5);
        printf("\t18. recipient #6    [%s]\n", szRecip6);
        printf("\t19. recipient #7    [%s]\n", szRecip7);
        printf("\t 0. Exit\n");

        if(FAILED(HrDoEnterNumber("SELECTION", TRUE, &ulChoice)))
        {
           continue;
        }

        switch(ulChoice)
        {
        case 1:
            ulInput = 0;
            if(FAILED(HrDoEnterNumber("event type", FALSE, &ulInput)))
            {
                continue;
            }
            nEventType = ulInput;
            break;
        case 2:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("gateway name", szInput)))
            {
                continue;
            }
            strncpy(szGatewayName, szInput, MAX_INPUT_SIZ);
            szGatewayName[MAX_INPUT_SIZ] = 0;
            break;
        case 3:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("partner name", szInput)))
            {
                continue;
            }
            strncpy(szPartnerName, szInput, MAX_INPUT_SIZ);
            szPartnerName[MAX_INPUT_SIZ] = 0;
            break;
        case 4:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("MTS-ID", szInput)))
            {
                continue;
            }
            strncpy(szMtsID, szInput, MAX_INPUT_SIZ);
            szMtsID[MAX_INPUT_SIZ] = 0;
            break;
        case 5:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("Subject MTS-ID", szInput)))
            {
                continue;
            }
            strncpy(szSubjectMtsID, szInput, MAX_INPUT_SIZ);
            szSubjectMtsID[MAX_INPUT_SIZ] = 0;
            break;
        case 6:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("Remote-ID", szInput)))
            {
                continue;
            }
            strncpy(szRemoteID, szInput, MAX_INPUT_SIZ);
            szRemoteID[MAX_INPUT_SIZ] = 0;
            break;
        case 7:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("originator name", szInput)))
            {
                continue;
            }
            strncpy(szOriginatorName, szInput, MAX_INPUT_SIZ);
            szOriginatorName[MAX_INPUT_SIZ] = 0;
            break;
        case 8:
            ulInput = 0;
            if(FAILED(HrDoEnterNumber("priority", FALSE, &ulInput)))
            {
                continue;
            }
            nPriority = ulInput;
            break;
        case 9:
            ulInput = 0;
            if(FAILED(HrDoEnterNumber("length", FALSE, &ulInput)))
            {
                continue;
            }
            nLength = ulInput;
            break;
        case 10:
            ulInput = 0;
            if(FAILED(HrDoEnterNumber("seconds", FALSE, &ulInput)))
            {
                continue;
            }
            nSeconds = ulInput;
            break;
        case 11:
            ulInput = 0;
            if(FAILED(HrDoEnterNumber("cost", FALSE, &ulInput)))
            {
                continue;
            }
            nCost = ulInput;
            break;
        case 12:
            ulInput = 0;
            if(FAILED(HrDoEnterNumber("#recipients", FALSE, &ulInput)))
            {
                continue;
            }
            cRecipients = ulInput;
            break;
        case 13:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip1", szInput)))
            {
                continue;
            }
            strncpy(szRecip1, szInput, MAX_INPUT_SIZ);
            szRecip1[MAX_INPUT_SIZ] = 0;
            break;
        case 14:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip2", szInput)))
            {
                continue;
            }
            strncpy(szRecip2, szInput, MAX_INPUT_SIZ);
            szRecip2[MAX_INPUT_SIZ] = 0;
            break;
        case 15:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip3", szInput)))
            {
                continue;
            }
            strncpy(szRecip3, szInput, MAX_INPUT_SIZ);
            szRecip3[MAX_INPUT_SIZ] = 0;
            break;
        case 16:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip4", szInput)))
            {
                continue;
            }
            strncpy(szRecip4, szInput, MAX_INPUT_SIZ);
            szRecip4[MAX_INPUT_SIZ] = 0;
            break;
        case 17:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip5", szInput)))
            {
                continue;
            }
            strncpy(szRecip5, szInput, MAX_INPUT_SIZ);
            szRecip5[MAX_INPUT_SIZ] = 0;
            break;
        case 18:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip6", szInput)))
            {
                continue;
            }
            strncpy(szRecip6, szInput, MAX_INPUT_SIZ);
            szRecip6[MAX_INPUT_SIZ] = 0;
            break;
        case 19:
            szInput[0] = 0;
            if(FAILED(HrDoEnterString("recip7", szInput)))
            {
                continue;
            }
            strncpy(szRecip7, szInput, MAX_INPUT_SIZ);
            szRecip7[MAX_INPUT_SIZ] = 0;
            break;
        case 0:
            goto cleanup;
        default:
            printf("ERROR: unknown menu selection\n");
            break;
        }
    }

cleanup:

    return;
}

//$--DoRunCommand---------------------------------------------------------------
//  Run a command.
// -----------------------------------------------------------------------------
void DoRunCommand(void)
{
    HRESULT hr = NOERROR;

    printf("running command....\n");

    ZeroMemory(&stEvent, sizeof(SYSTEMTIME));

    GetSystemTime(&stEvent);

    hr = HrTrackWriteLog(
        pvSession,
        nEventType,
        stEvent,
        szGatewayName,
        szPartnerName,
        szMtsID,
        szSubjectMtsID,
        szRemoteID,
        szOriginatorName,
        nPriority,
        nLength,
        nSeconds,
        nCost,
        cRecipients,
        ((cRecipients == 0) ? NULL : ((LPTSTR *)&lpszRecipients)));

    if(FAILED(hr))
    {
        printf("ERROR: tracking write failed\n");

        goto cleanup;
    }

    printf("finished command....\n");

cleanup:

    return;
}

//$--main-----------------------------------------------------------------------
//  Gateway message tracking sample application entry point.
// -----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    HRESULT hr                       = NOERROR;

    DEBUGPUBLIC("main()\n");

    //
    // Initialize MAPI
    //

    hr = MAPIInitialize(NULL);

    if(FAILED(hr))
    {
        printf("ERROR: MAPI initialize failed\n");

        goto cleanup;
    }

    fInitializedMAPI = TRUE;

    //
    // Configure
    //

    hr = HrConfig(argc, argv);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Initialize gateway message tracking
    //

    hr = HrTrackInitLog(
	    szServer,
	    &pvSession);

    if(FAILED(hr))
    {
        printf("ERROR: tracking initialize failed\n");

        goto cleanup;
    }

    lpszRecipients[0] = (LPTSTR)szRecip1;
    lpszRecipients[1] = (LPTSTR)szRecip2;
    lpszRecipients[2] = (LPTSTR)szRecip3;
    lpszRecipients[3] = (LPTSTR)szRecip4;
    lpszRecipients[4] = (LPTSTR)szRecip5;
    lpszRecipients[5] = (LPTSTR)szRecip6;
    lpszRecipients[6] = (LPTSTR)szRecip7;

    printf("\n");

    printf("Processing commands.\n");

    for(;;)
    {
        ULONG ulChoice = 0;

        printf("\nMENU:\n");
        printf("\t 1. Enter command\n");
        printf("\t 2. Run command\n");
        printf("\t 0. Exit\n");

        if(FAILED(HrDoEnterNumber("SELECTION", TRUE, &ulChoice)))
        {
            continue;
        }

        switch(ulChoice)
        {
        case 1:
            DoEnterCommand();
            break;
        case 2:
            DoRunCommand();
            break;
        case 0:
            goto cleanup;
            break;
        default:
            printf("ERROR: unknown menu selection\n");
            break;
        }
    }

cleanup:

    //
    // Uninitialize gateway message tracking
    //

    if(pvSession != NULL)
    {
        hr = HrTrackUninitLog(&pvSession);

        if(FAILED(hr))
        {
            printf("ERROR: tracking uninitialize failed\n");
        }
    }

    if(fInitializedMAPI == TRUE)
    {
        MAPIUninitialize();

        fInitializedMAPI = FALSE;
    }

    // return exit code
    return _nEcFromHr(hr);

}
