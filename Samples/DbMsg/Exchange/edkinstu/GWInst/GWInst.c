// --gwinst.c-------------------------------------------------------------------
//
//  Gateway installation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dapi.h"
#include "sadapi.h"

//
// Names of Command Line Arguments
//

#define ARG_ENTERPRISE		"ENTERPRISE"
#define ARG_SITEDN          "SITEDN"
#define ARG_DISPLAY_NAME	"DISPLAY_NAME"
#define ARG_NAME            "NAME"
#define ARG_ADDRTYPE		"ADDRTYPE"
#define ARG_EXTNAME         "EXTNAME"
#define ARG_EXTDATA         "EXTDATA"
#define ARG_SERVER			"SERVER"
#define ARG_ACCOUNT			"ACCOUNT_NAME"
#define ARG_PRESERVE_DNS    "PRESERVE_DNS"
#define ARG_DELETE			"DELETE"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_SITEDN,
    ARG_DISPLAY_NAME,
	ARG_NAME,
	ARG_ADDRTYPE,
	ARG_EXTNAME,
	ARG_EXTDATA,
	ARG_SERVER,
	ARG_ACCOUNT,
    ARG_PRESERVE_DNS,
    ARG_DELETE,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char szSiteDN[MAX_PATH+1]               = {0};
char szDisplayName[MAX_PATH+1]          = {0};
char szGatewayName[MAX_PATH+1]          = {0};
char szExtensionName[MAX_PATH+1]        = {0};
char szExtensionData[MAX_PATH+1]        = {0};
char szServer[MAX_PATH+1]               = {0};
char szAccountName[MAX_PATH+1]          = {0};
char szAddressType[MAX_PATH+1]          = {0};
BOOL fCanPreserveDNs                    = FALSE;
BOOL fDisplayedHelp                     = FALSE;
BOOL fDeleteGateway                     = FALSE;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: GWINST [Flags]\n\n");
	printf("  [Flags]        Enter GWINST /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Gateway Installation sample.\n\n");
	printf("USAGE: GWINST [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /SITEDN=             Gateway site distinguished name\n");
	printf("  /DISPLAY_NAME=       Gateway display name\n");
	printf("  /NAME=               Gateway name\n");
	printf("  /ADDRTYPE=           Address type\n");
	printf("  /SERVER=             Server computer name\n");
	printf("\n");
	printf("  Optional Flags\n");
	printf("  /EXTNAME=            Extension name\n");
	printf("  /EXTDATA=            Extension data absolute path & file name\n");
	printf("                       (Use CFGCODE to create this file.)\n");
	printf("  /ACCOUNT=            Account name\n");
    printf("  /PRESERVE_DNS=       Can this gateway preserve DNs? (yes/no)\n");
    printf("  /DELETE              Delete gateway\n");
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
				fDeleteGateway = TRUE;
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
				strncpy(szGatewayName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_ADDRTYPE))
			{
				strncpy(szAddressType, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_EXTNAME))
			{
				strncpy(szExtensionName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_EXTDATA))
			{
				strncpy(szExtensionData, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_SERVER))
			{				   
				strncpy(szServer, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_ACCOUNT))
			{
				strncpy(szAccountName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_PRESERVE_DNS))
			{
			    if (!lstrcmpi(pszValue,TEXT("YES")))
                {
                    fCanPreserveDNs = TRUE;
                }
                else if (!lstrcmpi(pszValue,TEXT("NO")))
                {
                    fCanPreserveDNs = FALSE;
                }
                else
                {
    				fprintf(stderr, "ERROR: enter \"YES\" or \"NO\" for flag /%s\n", 
    					pszArgument);
    				hr = HR_LOG(E_FAIL);
                }
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

	    if (szSiteDN[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SITEDN);
			hr = HR_LOG(E_FAIL);
		}

	    if (szGatewayName[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_NAME);
			hr = HR_LOG(E_FAIL);
		}

        if(fDeleteGateway == FALSE)
        {
	        if (szDisplayName[0] == 0)
		    {
			    fprintf(stderr, "ERROR: please specify /%s\n", ARG_DISPLAY_NAME);
			    hr = HR_LOG(E_FAIL);
		    }

            if (szAddressType[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_ADDRTYPE);
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
//  Main function that performs directory import.
// -----------------------------------------------------------------------------
int main(
    IN int argc,
    IN char *argv[])
{
    HRESULT hr      = NOERROR;
    FILE    *fp     = NULL;
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

    if(fDeleteGateway == FALSE)
    {
        //
        // Set gateway bit
        //

        hr = HrSetGatewayBit(
            szServer,
            szSiteDN,
            szServer);

        if(FAILED(hr))
        {
        	fprintf(stderr,
        		"ERROR: unable to set gateway bit\n");
        	hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrGatewayExists(
            szServer,
            szSiteDN,
            szGatewayName);

        if(SUCCEEDED(hr))
        {
            hr = HrRemoveGateway(
                szServer,
                szSiteDN,
                szGatewayName);

            if(FAILED(hr))
            {
        		fprintf(stderr,
        		    "ERROR: unable to remove gateway %s\n",
        		    szGatewayName);
        		hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        hr = HrInstallGateway(
            szServer,
            szSiteDN,
            szDisplayName,
            szGatewayName,
            szExtensionName,
            szExtensionData,
            szAddressType,
            szAccountName,
            fCanPreserveDNs);

		//
		// Rebuild gateway address routing table (GWART).
		//

        if(SUCCEEDED(hr))
        {
		    (void)SAD_ScRunRID(szServer);
        }
    }
    else
    {
        hr = HrGatewayExists(
            szServer,
            szSiteDN,
            szGatewayName);

        if(FAILED(hr))
        {
    		fprintf(stderr,
    		    "ERROR: the gateway %s does not exist\n",
    		    szGatewayName);
    		hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrRemoveGateway(
            szServer,
            szSiteDN,
            szGatewayName);
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
        if(fDeleteGateway == FALSE)
        {
		    fprintf(stderr, "Gateway installed successfully.\n");
        }
        else
        {
		    fprintf(stderr, "Gateway deleted successfully.\n");
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
