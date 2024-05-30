// --profinst.c-----------------------------------------------------------------
//
//  MAPI profile creation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

//
// Names of Command Line Arguments
//

#define ARG_SERVICE         "SERVICE"
#define ARG_NAME			"NAME"
#define ARG_TYPE            "TYPE"
#define ARG_DELETE          "DELETE"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_SERVICE,
	ARG_NAME,
    ARG_TYPE,
    ARG_DELETE,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char szServiceName[MAX_PATH+1]          = {0};
char szProfileName[MAX_PATH+1]          = {0};
char szProfileType[MAX_PATH+1]          = {0};
BOOL fDisplayedHelp                     = FALSE;
BOOL fDeleteProfile                     = FALSE;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: PROFINST [Flags]\n\n");
	printf("  [Flags]        Enter PROFINST /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("MAPI Profile Installation sample.\n\n");
	printf("USAGE: PROFINST [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /SERVICE=            Service name\n");
	printf("  /NAME=               Profile name\n");
	printf("  /TYPE=               Profile type (GATEWAY or AGENT)\n");
	printf("\n");
	printf("  Optional Flags\n");
    printf("  /DELETE              Delete profile\n");
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
			(!lstrcmpi(pszArgument,ARG_HELP1) || 
			!lstrcmpi(pszArgument,ARG_HELP2)))
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
			if (!lstrcmpi(pszArgument,ARG_DELETE))
			{
				fDeleteProfile = TRUE;
			}

			// Other flag (must take a value).

			else
			{
				fprintf(stderr, "ERROR: flag /%s requires a value\n", 
					pszArgument);
				hr = HR_LOG(E_FAIL);
			}
		}

		// Parse flag arguments that take a value.

		else if (pszArgument != NULL && pszValue != NULL)
		{

			if (!lstrcmpi(pszArgument,ARG_SERVICE))
			{
				strncpy(szServiceName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_NAME))
			{
				strncpy(szProfileName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_TYPE))
			{
				strncpy(szProfileType, pszValue, MAX_PATH);
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
	    if ((szServiceName[0] == 0) && (fDeleteProfile == FALSE))
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SERVICE);
			hr = HR_LOG(E_FAIL);
		}

	    if (szProfileName[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_NAME);
			hr = HR_LOG(E_FAIL);
		}

	    if(szProfileType[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_TYPE);
			hr = HR_LOG(E_FAIL);
		}
        else
        {
            if(lstrcmpi(szProfileType, "GATEWAY") &&
               lstrcmpi(szProfileType, "AGENT"))
            {
			    fprintf(stderr, "ERROR: please specify a valid /%s\n", ARG_TYPE);
			    hr = HR_LOG(E_FAIL);
            }
        }
	}

cleanup:

    RETURN(hr);
}

//$--main-----------------------------------------------------------------------
//  Main function.
// -----------------------------------------------------------------------------
int main(
    IN int argc,
    IN char *argv[])
{
    HRESULT    hr         = NOERROR;
	MAPIINIT_0 MapiInit   = { 0 };
    BOOL       IsInitMAPI = FALSE;
    BOOL       fErrMsg    = TRUE;

    printf( "\n" );

    MapiInit.ulVersion = MAPI_INIT_VERSION;

    hr = MAPIInitialize(&MapiInit);

    if(FAILED(hr))
    {
	    fprintf(stderr, "ERROR: MAPI failed to initialize\n");
        fErrMsg = FALSE;
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    IsInitMAPI = TRUE;

    //
    // Get parameters from the command-line
    //

    hr = HrConfig(argc, argv);

    if (FAILED(hr))
    {
        fErrMsg = FALSE;
        goto cleanup;
    }

    if(fDeleteProfile == FALSE)
    {
        if(!lstrcmpi(szProfileType, "GATEWAY"))
        {
            hr = HrCreateGatewayProfile(szServiceName, szProfileName);
        }
        else
        {
            hr = HrCreateMailboxAgentProfile(szServiceName, szProfileName);
        }
    }
    else
    {
        hr = HrRemoveProfile(szProfileName);
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
        if(fDeleteProfile == FALSE)
        {
		    fprintf(stderr, "Profile created successfully.\n");
		    hr = NOERROR;
        }
        else
        {
		    fprintf(stderr, "Profile deleted successfully.\n");
		    hr = NOERROR;
        }
	}

	// Error completion.

	else
	{
        if(fErrMsg == TRUE)
        {
		    fprintf(stderr, "ERROR: an error occurred [%08lx].\n",hr);
        }
		hr = HR_LOG(E_FAIL);
	}

    if(IsInitMAPI == TRUE)
    {
        MAPIUninitialize();
    }

    // return exit code
    return _nEcFromHr(hr);
	
}
