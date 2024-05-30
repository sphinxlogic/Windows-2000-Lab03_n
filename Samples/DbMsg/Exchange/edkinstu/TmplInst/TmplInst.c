// --tmplinst.c-----------------------------------------------------------------
//
//  Address Template installation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

//
// Names of Command Line Arguments
//

#define ARG_SITEDN			"SITEDN"
#define ARG_DISPLAY_NAME    "DISPLAY_NAME"
#define ARG_NAME            "NAME"
#define ARG_TYPE            "TYPE"
#define ARG_SYNTAX          "SYNTAX"
#define ARG_SERVER			"SERVER"
#define ARG_MESSAGE_DT      "MESSAGE_DT"
#define ARG_RECIPIENT_DT    "RECIPIENT_DT"
#define ARG_ADDRESS_DT      "ADDRESS_DT"
#define ARG_LANGUAGE        "LANGUAGE"
#define ARG_DATA16          "DATA16"
#define ARG_DATA32          "DATA32"
#define ARG_FILE            "FILE"
#define ARG_DELETE          "DELETE"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_SITEDN,
    ARG_DISPLAY_NAME,
	ARG_NAME,
	ARG_TYPE,
	ARG_SYNTAX,
	ARG_SERVER,
	ARG_MESSAGE_DT,
	ARG_RECIPIENT_DT,
	ARG_ADDRESS_DT,
	ARG_LANGUAGE,
    ARG_DATA16,
    ARG_DATA32,
    ARG_FILE,
	ARG_DELETE,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char szSiteDN[MAX_PATH+1]                = {0};
char szDisplayName[MAX_PATH+1]           = {0};
char szTemplateName[MAX_PATH+1]			 = {0};
char szAddressType[MAX_PATH+1]           = {0};
char szAddressSyntax[MAX_PATH+1]         = {0};
char szServer[MAX_PATH+1]				 = {0};
char szMessageDisplayTable[MAX_PATH+1]   = {0};
char szRecipientDisplayTable[MAX_PATH+1] = {0};
char szAddressDisplayTable[MAX_PATH+1]   = {0};
char szLanguage[MAX_PATH+1]              = {0};
char szHelpData16[MAX_PATH+1]            = {0};
char szHelpData32[MAX_PATH+1]            = {0};
char szHelpFileName[MAX_PATH+1]          = {0};
BOOL fDisplayedHelp				         = FALSE;
BOOL fDeleteTemplate                     = FALSE;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: TMPLINST [Flags]\n\n");
	printf("  [Flags]        Enter TMPLINST /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Address Template Installation sample.\n\n");
	printf("USAGE: TMPLINST [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /SITEDN=             Site distinguished name\n");
    printf("  /DISPLAY_NAME        Template display name\n");
	printf("  /NAME=               Template name\n");
	printf("  /TYPE=               Address type\n");
	printf("  /SYNTAX=             Address syntax\n");
	printf("  /SERVER=             Server computer name\n");
	printf("  /ADDRESS_DT=         Address Entry Display Table\n");
	printf("  /LANGUAGE=           Language (e.g. 409) \n");
    printf("  /DATA16=             Help data for 16-bit clients\n");
    printf("  /DATA32=             Help data for 32-bit clients\n");
    printf("  /FILE=               Help file name used by clients\n");
	printf("\n");
	printf("  Optional Flags\n");
	printf("  /MESSAGE_DT=         Per-Message Display Table\n");
	printf("  /RECIPIENT_DT=       Per-Recipient Display Table\n");
	printf("  /DELETE              Delete template\n");
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
				fDeleteTemplate = TRUE;
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

			if (!lstrcmpi(pszArgument,ARG_SITEDN))
			{
				strncpy(szSiteDN, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_DISPLAY_NAME))
			{
				strncpy(szDisplayName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_NAME))
			{
				strncpy(szTemplateName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_SERVER))
			{
				strncpy(szServer, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_TYPE))
			{
				strncpy(szAddressType, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_SYNTAX))
			{
				strncpy(szAddressSyntax, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_MESSAGE_DT))
			{
				strncpy(szMessageDisplayTable, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_RECIPIENT_DT))
			{
				strncpy(szRecipientDisplayTable, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_ADDRESS_DT))
			{
				strncpy(szAddressDisplayTable, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_LANGUAGE))
			{
				strncpy(szLanguage, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_DATA16))
			{
				strncpy(szHelpData16, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_DATA32))
			{
				strncpy(szHelpData32, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_FILE))
			{
				strncpy(szHelpFileName, pszValue, MAX_PATH);
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

            hr = HrGetExchangeStatus(
                szServer,
                &dwService,
                &dwCurrentState);

            if(FAILED(hr))
            {
			    fprintf(stderr, "ERROR: please start Exchange on %s\n",szServer);
			    hr = HR_LOG(E_FAIL);
            }
        }

        if (szTemplateName[0] == 0)
        {
            fprintf(stderr, "ERROR: please specify /%s\n", ARG_NAME);
            hr = HR_LOG(E_FAIL);
        }

	    if (szSiteDN[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SITEDN);
			hr = HR_LOG(E_FAIL);
		}

	    if (szAddressType[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_TYPE);
			hr = HR_LOG(E_FAIL);
		}

	    if (szLanguage[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_LANGUAGE);
			hr = HR_LOG(E_FAIL);
		}

        if(fDeleteTemplate == FALSE)
        {
    	    if (szAddressSyntax[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SYNTAX);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szAddressDisplayTable[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_ADDRESS_DT);
    			hr = HR_LOG(E_FAIL);
    		}
        }
	}

    hrT = HrAdminProgramExists();

    if(FAILED(hrT))
    {
		fprintf(stderr, "ERROR: install the Exchange administrator program\n");
		hr = HR_LOG(E_FAIL);
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
    HRESULT hr      = NOERROR;
    BOOL    fErrMsg = TRUE;

    printf( "\n" );

    //
    // Get parameters from the command-line
    //

    hr = HrConfig(argc, argv);

    if (FAILED(hr))
    {
        fErrMsg = FALSE;
        goto cleanup;
    }

    if(fDeleteTemplate == FALSE)
    {
        hr = HrAddressTemplateExists(
            szServer,
            szSiteDN,
            szTemplateName,
            szAddressType,
            szLanguage);

        if(SUCCEEDED(hr))
        {
            hr = HrRemoveAddressTemplate(
                szServer,
                szSiteDN,
                szTemplateName,
                szAddressType,
                szLanguage);

            if(FAILED(hr))
            {
        		fprintf(stderr,
        		    "ERROR: unable to remove address template %s\n",
        		    szTemplateName);
        		hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        hr = HrInstallAddressTemplate(
            szServer,
            szSiteDN,
            szDisplayName,
            szTemplateName,
            szAddressSyntax,
            szAddressType,
            szMessageDisplayTable,
            szRecipientDisplayTable,
            szAddressDisplayTable,
            szLanguage,
            szHelpData16,
            szHelpData32,
            szHelpFileName);
    }
    else
    {
        hr = HrAddressTemplateExists(
            szServer,
            szSiteDN,
            szTemplateName,
            szAddressType,
            szLanguage);

        if(FAILED(hr))
        {
    		fprintf(stderr,
    		    "ERROR: the address template %s does not exist\n",
    		    szTemplateName);
    		hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrRemoveAddressTemplate(
            szServer,
            szSiteDN,
            szTemplateName,
            szAddressType,
            szLanguage);
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
        if(fDeleteTemplate == FALSE)
        {
		    fprintf(stderr, "Address template created successfully.\n");
        }
        else
        {
		    fprintf(stderr, "Address template deleted successfully.\n");
        }

		hr = NOERROR;
	}

	// Error completion.

	else
	{
        if(fErrMsg == TRUE)
        {
		    fprintf(stderr, "ERROR: error(s) written to NT Event Log.\n");
        }
		hr = HR_LOG(E_FAIL);
	}

    // return exit code
    return _nEcFromHr(hr);
	
}
