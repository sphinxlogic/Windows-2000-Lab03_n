// --dsexport.c-----------------------------------------------------------------
//
//  Directory service export sample.
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
#define ARG_CLASSES 			"CLASSES"
#define ARG_DSA					"DSA"
#define ARG_HELP1				"?"
#define ARG_HELP2				"HELP"
#define ARG_SERVER				"SERVER"
#define ARG_ALL_RECIPIENTS		"ALL_RECIPIENTS"
#define ARG_ONLY_BASEPOINT		"ONLY_BASEPOINT"
#define ARG_DIST_LIST			"DIST_LIST"
#define ARG_MAILBOX				"MAILBOX"
#define ARG_REMOTE_ADDRESS		"REMOTE_ADDRESS"
#define ARG_ALL_CLASSES			"ALL_CLASSES"
#define ARG_HIDDEN				"HIDDEN"
#define ARG_SUBTREE             "SUBTREE"
#define ARG_NO_UI				"NO_UI"

//
// Table of Command Line Switches for _HrExpandCommandLineArgument()
//

static char * rgpszArgArray[] = {
	ARG_FILE,
	ARG_BASEPOINT,
	ARG_CONTAINER,
    ARG_CLASSES,
	ARG_DSA,
	ARG_HELP1,
	ARG_HELP2,
	ARG_SERVER,
	ARG_ALL_RECIPIENTS,
	ARG_ONLY_BASEPOINT,
	ARG_DIST_LIST,
	ARG_MAILBOX,
	ARG_REMOTE_ADDRESS,
    ARG_ALL_CLASSES,
    ARG_HIDDEN,
    ARG_SUBTREE,
	ARG_NO_UI,
};

//
// Variables For Command Line Arguments
//

char    szExportFile[MAX_PATH+1]		= {0};
char    szDsaName[MAX_PATH+1]			= {0};
char    szServerName[MAX_PATH+1]		= {0};
char    szBasePoint[MAX_PATH+1]		    = {0};
char    szParentContainer[MAX_PATH+1]	= {0};
DWORD   ControlFlags					= 0;
ULONG   cClasses                        = 0;
LPSTR*  lppszClasses                    = NULL;

//
// Other Variables
//

BOOL fDisplayedHelp					    = FALSE;
DWORD cLoggedErrors					    = 0;

//
// Function Declarations
//

static HRESULT HrParseCommandLine(
    IN int argc,
    IN char *argv[]);

static VOID ShowUsage(
	void);

static VOID ShowHelp(
	void);

static HRESULT HrDoBatchExport(
	void);

//
// Functions
//

//$--main-----------------------------------------------------------------------
//  Main function that performs directory export.
// -----------------------------------------------------------------------------
int main(								// RETURNS: exit code
	IN int argc,						// number of arguments on command line
	IN char *argv[])					// array of command line arguments
{
    HRESULT hr		    = NOERROR;
    BOOL    IsMAPIInit  = FALSE;

	DEBUGPUBLIC("main()\n");

    printf( "\n" );

    hr = MAPIInitialize(NULL);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    IsMAPIInit = TRUE;

    // Get export parameters from the command line.

    hr = HrParseCommandLine(argc, argv);
    if (FAILED(hr))
    {
        goto cleanup;
    }

    // Do batch export

    hr = HrDoBatchExport();
    if (FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    if(IsMAPIInit == TRUE)
    {
        MAPIUninitialize();
    }

	// Successful completion.

	if (fDisplayedHelp)
	{
		hr = NOERROR;
	}
	else if (SUCCEEDED(hr))
	{
		fprintf(stderr, "Export operation completed successfully.\n");
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

    MAPIFREEBUFFER(lppszClasses);

	return _nEcFromHr(hr);
}

//$--HrParseCommandLine---------------------------------------------------------
//  Read export configuration from command line.
// -----------------------------------------------------------------------------
static HRESULT HrParseCommandLine(		// RETURNS: HRESULT
    IN int argc,						// number of arguments on command line
    IN char *argv[])					// array of command line arguments
{
    HRESULT		hr				= NOERROR;
    HRESULT		hrT				= NOERROR;
	char *		pszArgument		= NULL;
	char *		pszValue		= NULL;
    int			i				= 0;
    LPTSTR      lpszSep         = "%\0";

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

		if (pszArgument != NULL && pszValue == NULL)
		{
			// ALL_RECIPIENTS

			if (!_stricmp(pszArgument,ARG_ALL_RECIPIENTS))
			{
				ControlFlags |= DAPI_EXPORT_RECIPIENTS;
			}

			// ONLY_BASEPOINT

			else if (!_stricmp(pszArgument,ARG_ONLY_BASEPOINT))
			{
				ControlFlags |= DAPI_EXPORT_BASEPOINT_ONLY;
			}

			// DIST_LIST

			else if (!_stricmp(pszArgument,ARG_DIST_LIST))
			{
				ControlFlags |= DAPI_EXPORT_DIST_LIST;
			}

			// MAILBOX

			else if (!_stricmp(pszArgument,ARG_MAILBOX))
			{
				ControlFlags |= DAPI_EXPORT_MAILBOX;
			}

			// REMOTE_ADDRESS

			else if (!_stricmp(pszArgument,ARG_REMOTE_ADDRESS))
			{
				ControlFlags |= DAPI_EXPORT_CUSTOM;
			}

			// ALL_CLASSES

			else if (!_stricmp(pszArgument,ARG_ALL_CLASSES))
			{
				ControlFlags |= DAPI_EXPORT_ALL_CLASSES;
			}

			// HIDDEN

			else if (!_stricmp(pszArgument,ARG_HIDDEN))
			{
				ControlFlags |= DAPI_EXPORT_HIDDEN;
			}

			// SUBTREE

			else if (!_stricmp(pszArgument,ARG_SUBTREE))
			{
				ControlFlags |= DAPI_EXPORT_SUBTREE;
			}
			
			// Suppress all the UI, needed for batch processing

			else if (!_stricmp(pszArgument,ARG_NO_UI))
			{
				ControlFlags |= DAPI_YES_TO_ALL |
								DAPI_SUPPRESS_COMPLETION |
								DAPI_SUPPRESS_PROGRESS;
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
			if (!_stricmp(pszArgument,ARG_DSA))
			{
				strncpy(szDsaName, pszValue, MAX_PATH);
                szDsaName[MAX_PATH] = 0;
			}
			else if (!_stricmp(pszArgument,ARG_SERVER))
			{
				strncpy(szServerName, pszValue, MAX_PATH);
                szServerName[MAX_PATH] = 0;
			}
			else if (!_stricmp(pszArgument,ARG_FILE))
			{
				strncpy(szExportFile, pszValue, MAX_PATH);
                szExportFile[MAX_PATH] = 0;
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
			else if (!_stricmp(pszArgument,ARG_CLASSES))
			{

                hr = HrStrTokAll(
                    pszValue,
                    lpszSep,
                    &cClasses,
                    &lppszClasses);

                if(FAILED(hr))
                {
    				fprintf(stderr, "ERROR: syntax error in /%s\n", 
    					pszArgument);
                    goto cleanup;
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
		if (*szDsaName == 0)
		{
			fprintf(stderr, "ERROR: please specify /%s\n", ARG_DSA);
			hr = HR_LOG(E_FAIL);
		}
		if (*szExportFile == 0)
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

    printf("USAGE: DSEXPORT [Flags]\n\n");
	printf("  [Flags]        Enter DSEXPORT /? for details\n");

	fDisplayedHelp = TRUE;
}

//$--ShowHelp-------------------------------------------------------------------
//  Show help information.
// -----------------------------------------------------------------------------
static VOID ShowHelp(void)				// RETURNS: nothing
{
	DEBUGPRIVATE("ShowHelp()\n");

	printf("Directory Service Export sample.\n\n");
	printf("USAGE: DSEXPORT [Flags]\n\n");
	printf("  /FILE=               Name of export file\n");
	printf("  /SERVER=             Exchange server name\n");
	printf("  /DSA=                Directory Service Agent name\n");
	printf("  /BASEPOINT=          DN of Directory basepoint object\n");
	printf("  /CONTAINER=          RDN of Directory container beneath "
		"BASEPOINT\n");
	printf("  /CLASSES=            Object classes (separated by '%%')\n");
	printf("  /HELP or /?          Display help screen\n");
	printf("  /ONLY_BASEPOINT      Export only the BASEPOINT object\n");
	printf("  /ALL_RECIPIENTS      Export all recipients\n");
	printf("  /DIST_LIST           Export distribution list recipients\n");
	printf("  /MAILBOX             Export mailbox recipients\n");
	printf("  /REMOTE_ADDRESS      Export remote address recipients\n");
	printf("  /ALL_CLASSES         Export all classes\n");
	printf("  /HIDDEN              Export hidden objects of the selected "
	    "classes\n");
	printf("  /SUBTREE             Export subtree\n");
	printf("  /NO_UI               Suppress all User Interfaces\n");

	fDisplayedHelp = TRUE;
}

//$--DoBatchExport--------------------------------------------------------------
//  Do batch export of directory objects.
// -----------------------------------------------------------------------------
static HRESULT HrDoBatchExport(void)	// RETURNS: HRESULT
{
	HRESULT         hr              = NOERROR;
	BEXPORT_PARMS 	BexportParms    = {0};
	LPBEXPORT_PARMS lpBexportParms  = {0};

	DEBUGPRIVATE("HrDoBatchExport()\n");

	lpBexportParms = &BexportParms;
	lpBexportParms->dwDAPISignature = DAPI_SIGNATURE;
	lpBexportParms->dwFlags = ControlFlags | 
							  DAPI_EVENT_ALL;
	lpBexportParms->pszExportFile = szExportFile;
	lpBexportParms->pszBasePoint = szBasePoint;

    if (*szParentContainer)
    {
	    lpBexportParms->pszContainer = szParentContainer;
    }

    if (*szDsaName)
    {
	    lpBexportParms->pszDSAName = szDsaName;
    }

    if (*szServerName)
    {
	    lpBexportParms->pszHomeServer = szServerName;
    }

    if(lppszClasses != NULL)
    {
	    lpBexportParms->rgpszClasses = lppszClasses;
    }

	lpBexportParms->chColSep = DAPI_DEFAULT_DELIM;
	lpBexportParms->chQuote = DAPI_DEFAULT_QUOTE;
	lpBexportParms->chMVSep = DAPI_DEFAULT_MV_SEP;

	cLoggedErrors = BatchExport(lpBexportParms);
	if (cLoggedErrors)
	{
		hr = HR_LOG(E_FAIL);
	}

    RETURN(hr);
}
