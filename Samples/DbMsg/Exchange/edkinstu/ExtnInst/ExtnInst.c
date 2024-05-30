// --extninst.c-----------------------------------------------------------------
//
//  Admin extension installation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dapi.h"

//
// Names of Command Line Arguments
//

#define ARG_SITEDN			"SITEDN"
#define ARG_DISPLAY_NAME	"DISPLAY_NAME"
#define ARG_MACHINE         "MACHINE"
#define ARG_NAME            "NAME"
#define ARG_SERVER			"SERVER"
#define ARG_EXTDLL          "EXTDLL"
#define ARG_DELETE          "DELETE"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_SITEDN,
	ARG_DISPLAY_NAME,
	ARG_MACHINE,
	ARG_NAME,
	ARG_SERVER,
	ARG_EXTDLL,
    ARG_DELETE,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char   szSiteDN[MAX_PATH+1]             = {0};
char   szDisplayName[MAX_PATH+1]        = {0};
char   szMachineType[MAX_PATH+1]        = {0};
char   szExtensionName[MAX_PATH+1]      = {0};
char   szExtensionDll[MAX_PATH+1]       = {0};
char   szFileName[MAX_PATH+1]           = {0};
char   szServer[MAX_PATH+1]				= {0};
BOOL   fDisplayedHelp					= FALSE;
BOOL   fDeleteExtension                 = FALSE;
LPVOID lpVersionInfo                    = NULL;
DWORD  dwFileVersionMS                  = 0;
DWORD  dwFileVersionLS                  = 0;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: EXTNINST [Flags]\n\n");
	printf("  [Flags]        Enter EXTNINST /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Admin Extension Installation sample.\n\n");
	printf("USAGE: EXTNINST [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /SITEDN=             Admin extension site distinguished name\n");
	printf("  /DISPLAY_NAME=       Admin extension display name\n");
	printf("  /MACHINE=            Admin extension DLL machine type\n");
	printf("  /NAME=               Admin extension name\n");
	printf("  /EXTDLL=             Admin extension DLL (include full path)\n");
	printf("  /SERVER=             Server computer name\n");
	printf("\n");
	printf("  Optional Flags\n");
    printf("  /DELETE              Delete admin extension\n");
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
    HRESULT          hr                 = NOERROR;
    HRESULT          hrT                = NOERROR;
	char *           pszArgument        = NULL;
	char *           pszValue		    = NULL;
    int              i				    = 0;
    UINT             dwBytes            = 0;
    LPVOID           lpBuffer           = 0;
    VS_FIXEDFILEINFO *lpvsFixedFileInfo = {0};

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
				fDeleteExtension = TRUE;
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

			else if (!lstrcmpi(pszArgument,ARG_MACHINE))
			{
				strncpy(szMachineType, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_NAME))
			{
				strncpy(szExtensionName, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_SERVER))
			{				   
				strncpy(szServer, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_EXTDLL))
			{
				strncpy(szExtensionDll, pszValue, MAX_PATH);
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

	    if (szExtensionName[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_NAME);
			hr = HR_LOG(E_FAIL);
		}

	    if (szMachineType[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_MACHINE);
			hr = HR_LOG(E_FAIL);
		}

        if(fDeleteExtension == FALSE)
        {
    	    if (szDisplayName[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_DISPLAY_NAME);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szExtensionDll[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_EXTDLL);
    			hr = HR_LOG(E_FAIL);
    		}
            else
            {
                DWORD dwAttrib = 0;

                dwAttrib = GetFileAttributes(szExtensionDll);

                if(dwAttrib == 0xFFFFFFFF)
                {
        			fprintf(stderr,
        			"ERROR: please specify an existing file for /%s\n",
        			ARG_EXTDLL);

        			hr = HR_LOG(E_FAIL);
                }
            }
        }
	}

    if(SUCCEEDED(hr) && (fDeleteExtension == FALSE))
    {
        //
        // Get extension DLL file name
        //

	    strncpy(szFileName,
	        _GetFileNameFromFullPath((LPTSTR)szExtensionDll), MAX_PATH);

        //
        // Get extension DLL file version
        //

        hr = HrGetFileVersionInfo(
            szExtensionDll,
            &lpVersionInfo);

        if(FAILED(hr))
    	{
    		fprintf(stderr, "ERROR: version unavailable [%08lx] in /%s\n",
                hr,
    		    ARG_EXTDLL);

    		hr = HR_LOG(E_FAIL);
    	}
        else
        {
            BOOL fRet = FALSE;

            fRet = VerQueryValue(lpVersionInfo,
                          TEXT("\\"),
                          &lpBuffer,
                          &dwBytes);

            if(fRet == FALSE)
            {
        		fprintf(stderr, "ERROR: version resource is invalid in /%s\n",
        		    ARG_EXTDLL);

        		hr = HR_LOG(E_FAIL);
            }
            else
            {
                lpvsFixedFileInfo = (VS_FIXEDFILEINFO *)lpBuffer;

                dwFileVersionMS = lpvsFixedFileInfo->dwFileVersionMS;
                dwFileVersionLS = lpvsFixedFileInfo->dwFileVersionLS;
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

    GLOBALFREE(lpVersionInfo);

    RETURN(hr);
}

//$--main-----------------------------------------------------------------------
//  Main function that performs directory import.
// -----------------------------------------------------------------------------
int main(
    IN int argc,
    IN char *argv[])
{
    HRESULT hr                 = NOERROR;
    FILE    *fp                = NULL;
    BOOL    fErrMsg            = TRUE;
    DWORD   dwOldFileVersionMS = 0;
    DWORD   dwOldFileVersionLS = 0;

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

    if(fDeleteExtension == FALSE)
    {
        hr = HrAdminExtensionExists(
            szServer,
            szSiteDN,
            szExtensionName,
            szMachineType);

        if(SUCCEEDED(hr))
        {
            hr = HrGetAdminExtensionVersion(
                szServer,
                szSiteDN,
                szExtensionName,
                szMachineType,
                &dwOldFileVersionMS,
                &dwOldFileVersionLS);

            if(FAILED(hr))
            {
        		fprintf(stderr,
        		    "ERROR: file version is missing in %s admin extension\n",
        		    szExtensionName);
        		hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            if((dwOldFileVersionMS >  dwFileVersionMS) ||
              ((dwOldFileVersionMS == dwFileVersionMS) &&
               (dwOldFileVersionLS >  dwFileVersionLS)))
            {
        		fprintf(stderr,
        		    "WARNING: installing older version of %s admin extension\n",
        		    szExtensionName);
            }

            hr = HrRemoveAdminExtension(
                szServer,
                szSiteDN,
                szExtensionName,
                szMachineType);

            if(FAILED(hr))
            {
        		fprintf(stderr,
        		    "ERROR: unable to remove %s admin extension\n",
        		    szExtensionName);
        		hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        hr = HrInstallAdminExtension(
            szServer,
            szSiteDN,
            szDisplayName,
            szExtensionName,
            dwFileVersionMS,
            dwFileVersionLS,
            szFileName,
            szMachineType);
    }
    else
    {
        hr = HrAdminExtensionExists(
            szServer,
            szSiteDN,
            szExtensionName,
            szMachineType);

        if(FAILED(hr))
        {
    		fprintf(stderr,
    		    "ERROR: the %s admin extension does not exist\n",
    		    szExtensionName);
    		hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrRemoveAdminExtension(
            szServer,
            szSiteDN,
            szExtensionName,
            szMachineType);
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
        if(fDeleteExtension == FALSE)
        {
		    fprintf(stderr, "Admin extension installed successfully.\n");
        }
        else
        {
		    fprintf(stderr, "Admin extension deleted successfully.\n");
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
