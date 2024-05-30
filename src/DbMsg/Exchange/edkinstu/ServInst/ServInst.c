// --servinst.c-----------------------------------------------------------------
//
//  Service installation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

//
// Run GUIDGEN.EXE to create a GUID to use when installing your company's
// products. This will make it possible for you to find services that you
// have installed.
//

#define PRODUCT_GUID_SAMPLE  TEXT("F90E4AE0-E588-11ce-A2CA-00AA0040E865")

//
// Names of Command Line Arguments
//

#define ARG_SITEDN			"SITEDN"
#define ARG_OBJNAME         "OBJNAME"
#define ARG_OBJTYPE         "OBJTYPE"
#define ARG_SERVICE         "SERVICE"
#define ARG_DISPLAY_NAME    "DISPLAY_NAME"
#define ARG_DEPENDENCIES    "DEPENDENCIES"
#define ARG_EXE             "EXE"
#define ARG_SERVER			"SERVER"
#define ARG_ACCOUNT			"ACCOUNT"
#define ARG_PASSWORD        "PASSWORD"
#define ARG_DELETE          "DELETE"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_SITEDN,
	ARG_OBJNAME,
    ARG_OBJTYPE,
	ARG_SERVICE,
    ARG_DISPLAY_NAME,
    ARG_DEPENDENCIES,
	ARG_EXE,
	ARG_SERVER,
	ARG_ACCOUNT,
	ARG_PASSWORD,
	ARG_DELETE,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char szSiteDN[MAX_PATH+1]               = {0};
char szObjectName[MAX_PATH+1]           = {0};
char szObjectType[MAX_PATH+1]           = {0};
char szServiceName[MAX_PATH+1]          = {0};
char szDisplayName[MAX_PATH+1]          = {0};
char szExeName[MAX_PATH+1]              = {0};
char szServer[MAX_PATH+1]               = {0};
char szAccountName[MAX_PATH+1]          = {0};
char szPassword[MAX_PATH+1]             = {0};
char szObjectGuid[MAX_PATH+1]           = {0};
char szDependencies[MAX_PATH+1]         = {0};
BOOL fDisplayedHelp                     = FALSE;
BOOL fDeleteService                     = FALSE;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: SERVINST [Flags]\n\n");
	printf("  [Flags]        Enter SERVINST /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Service Installation sample.\n\n");
	printf("USAGE: SERVINST [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /SITEDN=             Site distinguished name\n");
	printf("  /OBJNAME=            Object name\n");
	printf("  /OBJTYPE=            Object type (GATEWAY or AGENT)\n");
	printf("  /SERVICE=            Service name\n");
	printf("  /DISPLAY_NAME=       Service display name\n");
    printf("  /DEPENDENCIES=       Service dependencies (separated by '%%')\n");
	printf("  /EXE=                Executable name\n");
	printf("  /SERVER=             Server computer name\n");
	printf("  /ACCOUNT=            Account name\n");
	printf("  /PASSWORD=           Account password\n");
	printf("\n");
	printf("  Optional Flags\n");
	printf("  /DELETE              Delete service\n");
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
				fDeleteService = TRUE;
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

			else if (!lstrcmpi(pszArgument,ARG_OBJNAME))
			{
				strncpy(szObjectName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_OBJTYPE))
			{
				strncpy(szObjectType, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_SERVICE))
			{
				strncpy(szServiceName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_DISPLAY_NAME))
			{
				strncpy(szDisplayName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_DEPENDENCIES))
			{
				strncpy(szDependencies, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_EXE))
			{
				strncpy(szExeName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_SERVER))
			{
				strncpy(szServer, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_ACCOUNT))
			{
				strncpy(szAccountName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_PASSWORD))
			{
				strncpy(szPassword, pszValue, MAX_PATH);
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
	    if (szServiceName[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SERVICE);
			hr = HR_LOG(E_FAIL);
		}

        if(fDeleteService == FALSE)
        {
    	    if (szSiteDN[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SITEDN);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szDisplayName[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_DISPLAY_NAME);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szObjectName[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_OBJNAME);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if(szObjectType[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_OBJTYPE);
    			hr = HR_LOG(E_FAIL);
    		}
            else
            {
                if(!lstrcmpi(szObjectType, "GATEWAY"))
                {
                    strcpy(szObjectGuid, OBJECT_GUID_MAIL_GATEWAY);
                }
                else if(!lstrcmpi(szObjectType, "AGENT"))
                {
                    strcpy(szObjectGuid, OBJECT_GUID_MAILBOX_AGENT);
                }
                else
                {
    			    fprintf(stderr,
    			        "ERROR: please specify a valid /%s\n", ARG_OBJTYPE);
    			    hr = HR_LOG(E_FAIL);
                }
            }

    	    if (szExeName[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_EXE);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szServer[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_SERVER);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szAccountName[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_ACCOUNT);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szPassword[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_PASSWORD);
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
    HRESULT hr      = NOERROR;
    TCHAR   *pch    = NULL;
    BOOL    fErrMsg = TRUE;

    printf( "\n" );

    //
    // Get parameters from the command-line
    //

    ZeroMemory(szDependencies, sizeof(szDependencies));

    hr = HrConfig(argc, argv);

    if (FAILED(hr))
    {
        fErrMsg = FALSE;
        goto cleanup;
    }

    //
    // Convert message classes parameter to REG_MULTI_SZ format.
    //

    szDependencies[sizeof(szDependencies)-1] = 0;
    szDependencies[sizeof(szDependencies)-2] = 0;

    pch = szDependencies;

    while(*pch)
    {
        if(*pch == TEXT('%'))
        {
            *pch = 0;
        }

        pch++;
    }

    if(fDeleteService == FALSE)
    {
        hr = HrInstallService(
            szServer,
            szSiteDN,
            szDisplayName,
            szServiceName,
            szObjectName,
            szObjectGuid,
            PRODUCT_GUID_SAMPLE,
            szExeName,
            szDependencies,
            szAccountName,
            szPassword);
    }
    else
    {
        hr = HrRemoveService(szServiceName);
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
        if(fDeleteService == FALSE)
        {
		    fprintf(stderr, "Service installed successfully.\n");
		    hr = NOERROR;
        }
        else
        {
		    fprintf(stderr, "Service deleted successfully.\n");
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

    // return exit code
    return _nEcFromHr(hr);
	
}
