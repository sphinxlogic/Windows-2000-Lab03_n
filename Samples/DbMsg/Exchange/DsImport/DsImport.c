// --dsimport.c-----------------------------------------------------------------
//
//  Directory service import sample.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dapi.h"

//
// Names of Command Line Arguments
//

#define ARG_FILE				"FILE"
#define ARG_BASEPOINT			"BASEPOINT"
#define ARG_CONTAINER			"CONTAINER"
#define ARG_DSA					"DSA"
#define ARG_HELP1				"?"
#define ARG_HELP2				"HELP"
#define ARG_NO_UI				"NO_UI"


//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_FILE,
	ARG_BASEPOINT,
	ARG_CONTAINER,
	ARG_DSA,
	ARG_HELP1,
	ARG_HELP2,
	ARG_NO_UI,
};

//
// Variables For Command Line Arguments
//

char szDsaName[MAX_PATH+1]			= {0};
char szBasePoint[MAX_PATH+1]		= {0};
char szParentContainer[MAX_PATH+1]	= {0};
char szImportFile[MAX_PATH+1]		= {0};

DWORD   ControlFlags				= 0;

//
// Other Variables
//

BOOL fDisplayedHelp					= FALSE;
DWORD cLoggedErrors					= 0;

//
// Function Declarations
//

static HRESULT HrParseCommandLine(
    int argc,
    char *argv[]);

static VOID ShowUsage(
	void);

static VOID ShowHelp(
	void);

static HRESULT HrDoBatchImport(
	void);

//
// Functions
//

//$--main-----------------------------------------------------------------------
//  Main function that performs directory import.
// -----------------------------------------------------------------------------
int main(								// RETURNS: exit code
	int argc,							// number of arguments on command line
	char *argv[])						// array of command line arguments
{
    HRESULT		hr		= NOERROR;

	DEBUGPUBLIC("main()\n");

    printf( "\n" );

    // Get import parameters from the command line.

    hr = HrParseCommandLine(argc, argv);
    if (FAILED(hr))
    {
        goto cleanup;
    }

    // Do batch import

    hr = HrDoBatchImport();
    if (FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
		fprintf(stderr, "Import operation completed successfully.\n");
	}

	// Error completion.

	else if (cLoggedErrors == 1)
	{
		fprintf(stderr, "ERROR: 1 error written to NT Event Log.\n");
	}
	else if (cLoggedErrors > 1)
	{
		fprintf(stderr, "ERROR: %d errors written to NT Event Log.\n", 
			cLoggedErrors);
	}

	return _nEcFromHr(hr);
}

//$--HrParseCommandLine---------------------------------------------------------
//  Read import configuration from command line.
// -----------------------------------------------------------------------------
static HRESULT HrParseCommandLine(		// RETURNS: HRESULT
    int argc,							// number of arguments on command line
    char *argv[])						// array of command line arguments
{
    HRESULT		hr				= NOERROR;
    HRESULT		hrT				= NOERROR;
	char *		pszArgument		= NULL;
	char *		pszValue		= NULL;
    int			i				= 0;

	DEBUGPRIVATE("HrParseCommandLine()\n");

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
			argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
			&pszArgument, &pszValue);

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
			argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
			&pszArgument, &pszValue);

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

			if (!_stricmp(pszArgument,ARG_NO_UI))
			{
				ControlFlags |= DAPI_YES_TO_ALL |
								DAPI_SUPPRESS_COMPLETION |
								DAPI_SUPPRESS_PROGRESS;
			}
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
			if (!_stricmp(pszArgument,ARG_DSA))
			{
				strncpy(szDsaName, pszValue, MAX_PATH);
                szDsaName[MAX_PATH] = 0;
			}
			else if (!_stricmp(pszArgument,ARG_FILE))
			{
				strncpy(szImportFile, pszValue, MAX_PATH);
                szImportFile[MAX_PATH] = 0;
			}
			else if (!_stricmp(pszArgument,ARG_BASEPOINT))
			{
				strncpy(szBasePoint, pszValue, MAX_PATH);
                szBasePoint[MAX_PATH] = 0;
			}
			else if (!_stricmp(pszArgument,ARG_CONTAINER))
			{
				strncpy(szParentContainer, pszValue, MAX_PATH);
                szParentContainer[MAX_PATH] = 0;
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
		if (*szDsaName == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_DSA);
			hr = HR_LOG(E_FAIL);
		}
		if (*szImportFile == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_FILE);
			hr = HR_LOG(E_FAIL);
		}
	}

cleanup:
    RETURN(hr);
}

//$--ShowUsage------------------------------------------------------------------
//  Show usage information.
// -----------------------------------------------------------------------------
static VOID ShowUsage(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowUsage()\n");

    printf("USAGE: DSIMPORT [Flags]\n\n");
	printf("  [Flags]        Enter DSIMPORT /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Directory Service Import sample.\n\n");
	printf("USAGE: DSIMPORT [Flags]\n\n");
	printf("  /FILE=               Name of import file\n");
	printf("  /DSA=                Directory Service Agent name\n");
	printf("  /BASEPOINT=          DN of Directory basepoint object\n");
	printf("  /CONTAINER=          RDN of Directory container beneath "
		"BASEPOINT\n");
	printf("  /HELP or /?          Display help screen\n");
	printf("  /NO_UI               Suppress all User Interfaces\n");

	fDisplayedHelp = TRUE;
}

//$--HrDoBatchImport------------------------------------------------------------
//  Do batch import of directory objects.
// -----------------------------------------------------------------------------
static HRESULT HrDoBatchImport(void)	// RETURNS: HRESULT
{
	HRESULT         hr              = NOERROR;
	BIMPORT_PARMS 	BimportParms    = {0};
	LPBIMPORT_PARMS lpBimportParms  = &BimportParms;

	DEBUGPRIVATE("HrDoBatchImport()\n");

	lpBimportParms->dwDAPISignature 	= DAPI_SIGNATURE;
	lpBimportParms->dwFlags    	        = ControlFlags |
										  DAPI_RESTRICT_ACCESS |
										  DAPI_EVENT_ALL;

	lpBimportParms->pszImportFile 		= szImportFile;
	lpBimportParms->pszBasePoint 		= szBasePoint;
	lpBimportParms->pszContainer 	    = szParentContainer;
	lpBimportParms->pszNTDomain			= NULL;

    if(*szDsaName)
    {
	    lpBimportParms->pszDSAName 		= szDsaName;
    }

	lpBimportParms->chColSep 			= DAPI_DEFAULT_DELIM;
	lpBimportParms->chQuote 			= DAPI_DEFAULT_QUOTE;
	lpBimportParms->chMVSep 			= DAPI_DEFAULT_MV_SEP;

	cLoggedErrors = BatchImport(lpBimportParms);
	if (cLoggedErrors)
	{
		hr = HR_LOG(E_FAIL);
	}

    RETURN(hr);
}
