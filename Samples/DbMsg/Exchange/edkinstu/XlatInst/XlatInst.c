// --xlatinst.c-----------------------------------------------------------------
//
//  Message converter installation sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dapi.h"

//
// Names of Command Line Arguments
//

#define ARG_DLL				"DLL"
#define ARG_CLASSES         "CLASSES"
#define ARG_OPTIONS         "OPTIONS"
#define ARG_POINT           "POINT"
#define ARG_DELETE			"DELETE"
#define ARG_HELP1			"?"
#define ARG_HELP2			"HELP"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_DLL,
	ARG_CLASSES,
	ARG_OPTIONS,
	ARG_POINT,
    ARG_DELETE,
	ARG_HELP1,
	ARG_HELP2,
};

#define ARGARRAYSIZE (sizeof(rgpszArgArray)/sizeof(rgpszArgArray[0]))

//
// Variables For Command Line Arguments
//

char szConversionDll[MAX_PATH+1]        = {0};
char szMessageClasses[MAX_PATH+1]       = {0};
char szOptions[MAX_PATH+1]				= {0};
char szPoint[MAX_PATH+1]                = {0};
BOOL fDisplayedHelp						= FALSE;
BOOL fDeleteConverter                   = FALSE;

//
// Functions
//

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: XLATINST [Flags]\n\n");
	printf("  [Flags]        Enter XLATINST /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Message Converter Installation sample.\n\n");
	printf("USAGE: XLATINST [Flags]\n\n");
	printf("  Required Flags\n");
	printf("  /DLL=                Message conversion DLL name (no path)\n");
	printf("  /CLASSES=            Message classes (separated by '%%')\n");
	printf("  /OPTIONS=            Options string\n");
	printf("  /POINT=              Point string\n");
	printf("\n");
	printf("  Optional Flags\n");
    printf("  /DELETE              Delete conversion DLL\n");
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
				fDeleteConverter = TRUE;
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

			if (!lstrcmpi(pszArgument,ARG_DLL))
			{
				strncpy(szConversionDll, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_CLASSES))
			{
				strncpy(szMessageClasses, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_OPTIONS))
			{
				strncpy(szOptions, pszValue, MAX_PATH);
			}

			else if (!lstrcmpi(pszArgument,ARG_POINT))
			{
				strncpy(szPoint, pszValue, MAX_PATH);
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
	    if (szConversionDll[0] == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_DLL);
			hr = HR_LOG(E_FAIL);
		}

        if(fDeleteConverter == FALSE)
        {
    	    if (szMessageClasses[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_CLASSES);
    			hr = HR_LOG(E_FAIL);
    		}

    	    if (szPoint[0] == 0)
    		{
    			fprintf(stderr, "ERROR: please specify /%s\n", ARG_POINT);
    			hr = HR_LOG(E_FAIL);
    		}
        }
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
    TCHAR   *pch    = NULL;
    BOOL    fErrMsg = TRUE;

    printf( "\n" );

    //
    // Get parameters from the command-line
    //

    ZeroMemory(szMessageClasses, sizeof(szMessageClasses));

    hr = HrConfig(argc, argv);

    if (FAILED(hr))
    {
        fErrMsg = FALSE;
        goto cleanup;
    }
                    
    //
    // Convert message classes parameter to REG_MULTI_SZ format.
    //

    szMessageClasses[sizeof(szMessageClasses)-1] = 0;
    szMessageClasses[sizeof(szMessageClasses)-2] = 0;

    pch = szMessageClasses;

    while(*pch)
    {
        if(*pch == TEXT('%'))
        {
            *pch = 0;
        }

        pch++;
    }

    if(fDeleteConverter == FALSE)
    {
        hr = HrInstallMessageConverter(
            szConversionDll,
            szConversionDll,
            szMessageClasses,
            szOptions,
            szPoint);
    }
    else
    {
        hr = HrRemoveMessageConverter(
            szConversionDll);
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
        if(fDeleteConverter == FALSE)
        {
		    fprintf(stderr, "Message converter installed successfully.\n");
        }
        else
        {
		    fprintf(stderr, "Message converter deleted successfully.\n");
        }

		hr = NOERROR;
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
