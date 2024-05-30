// --cfgcode.c------------------------------------------------------------------
//
//  Program to take a .INI file containing property values as input, and create 
//  a file containing packed configuration data as output.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "cfgcode.chk"
#include "cfgcodem.h"
#include <io.h>
#include <sys/stat.h>

//
// Command Line Argument Names
//

#define ARG_PROGRAM_NAME        "CFGCODE"
#define ARG_INPUT_FILE          "InFile"
#define ARG_OUTPUT_FILE         "OutFile"
#define ARG_SECTION             "SECTION"
#define ARG_CONFIG_NAME         "NAME"
#define ARG_HELP1               "?"
#define ARG_HELP2               "HELP"

static char * rgpszArgArray[] =
{
	ARG_PROGRAM_NAME,
	ARG_INPUT_FILE,
	ARG_OUTPUT_FILE,
	ARG_SECTION,
	ARG_CONFIG_NAME,
	ARG_HELP1,
	ARG_HELP2,
};

//
// Command Line Argument Variables
//

static TCHAR    szInputFile[MAX_PATH+1]  = {0};
static TCHAR    szOutputFile[MAX_PATH+1] = {0};
static TCHAR    szSection[MAX_PATH+1]    = {0};
static TCHAR    szConfigName[MAX_PATH+1] = {0};
static BOOL     fPrintHelp               = FALSE;
static BOOL     fPrintUsage              = FALSE;

//
// Function Declarations
//

static VOID PrintUsage(void);

static VOID PrintHelp(void);

static HRESULT HrParseCommandLine(
	IN      int                     argc,
	IN      char *                  argv[]);

static HRESULT HrReadPropsFromINIFile(
	IN      LPTSTR                  pszInputFile,
	IN      LPTSTR                  pszSection,
	OUT     ULONG *                 pcProps,
	OUT     LPSPropValue *  ppProps);

static HRESULT HrParsePropValue(
    IN      LPTSTR                  pszFullLine,
	IN      ULONG                   ulPropTag,
	IN      LPTSTR                  pszValueText,
	IN      LPVOID                  pBaseObject,
	OUT     LPSPropValue            pProp);

static HRESULT HrCreateBinaryDataFile(
	IN      LPTSTR                  pszOutputFile,
	IN      ULONG                   cbData,
	IN      LPBYTE                  pbData);

//
// Functions
//

//$--main-----------------------------------------------------------------------
//  Main function that performs file conversion.
// -----------------------------------------------------------------------------
int main(                               // RETURNS: exit code
	IN      int                 argc,   // number of arguments on command line
	IN      char *              argv[]) // array of command line arguments
{
	HRESULT                 hr                      = NOERROR;
	BOOL                    fMAPIInitialized        = FALSE;
	MAPIINIT_0              MapiInit                = { 0 };
	BOOL                    fPrintResult            = FALSE;
	ULONG                   cProps                  = 0;
	LPSPropValue            pProps                  = NULL;
	ULONG                   cbConfigData            = 0;
	LPBYTE                  pbConfigData            = NULL;
	BOOL                    fEventLogOpen           = FALSE;

	DEBUGPUBLIC("main()\n");

	hr = CHK_main(argc, argv);
	if (FAILED(hr))
		return _nEcFromHr(EC_EDK_E_FAIL);

    printf( "\n" );

	// Parse the command line arguments.

	hr = HrParseCommandLine(argc, argv);
	if (FAILED(hr))
		goto cleanup;

	// If they requested a usage message (i.e. no arguments) then 
	// print a usage message and exit.

	if (fPrintUsage)
	{
		PrintUsage();
		goto cleanup;
	}

	// If they requested help then print a help message and exit.

	if (fPrintHelp)
	{
		PrintHelp();
		goto cleanup;
	}

	// Open the event log.

	hr = HrEventOpenLog(
	    TEXT("EDK CFGCODE"), NULL, NULL, NULL, NULL, NULL);

	if (FAILED(hr))
	{
		fprintf(stderr, "ERROR: Can't open event log.\n");
		goto cleanup;
	}
	fEventLogOpen = TRUE;

	// After this point we print the result of the operation and number 
	// of events logged.

	fPrintResult = TRUE;

	// Initialize MAPI.

    MapiInit.ulVersion = MAPI_INIT_VERSION;

    hr = MAPIInitialize(&MapiInit);
    if (FAILED(hr))
	{
		EventLogMsg(
			EDKEVENT_CANNOT_INIT_MAPI, 
			0, 
			0);
	goto cleanup;
	}

	fMAPIInitialized = TRUE;

	// If the input file name is not a full path then add the current 
	// directory to the front of the name.

	if (strchr(szInputFile,':') == NULL && strchr(szInputFile,'\\') == NULL)
	{
		TCHAR szCurrentDir[MAX_PATH+1] = {0};
		ULONG cchCurrentDir = 0;

		cchCurrentDir = GetCurrentDirectory(MAX_PATH, szCurrentDir);
		if (cchCurrentDir == 0)
		{
			EventLogMsg(
				CFGCODE_CANNOT_GET_CURRENT_DIR, 
				0, 
				1, GetLastError());
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		if (
			szCurrentDir[cchCurrentDir - 1] != ':' && 
			szCurrentDir[cchCurrentDir - 1] != '\\')
		{
			strcat(szCurrentDir, "\\");
		}
		strcat(szCurrentDir, szInputFile);
		strcpy(szInputFile, szCurrentDir);
	}

	// Do the operation.

	hr = HrReadPropsFromINIFile(szInputFile, szSection, &cProps, &pProps);
	if (FAILED(hr))
	{
		goto cleanup;
	}

	hr = HrCfgPackData(
		szConfigName, cProps, pProps, &cbConfigData, &pbConfigData);
	if (FAILED(hr))
	{
		EventLogMsg(
			CFGCODE_CANNOT_PACK_CONFIG_INFO, 
			0, 
			0);
		goto cleanup;
	}

	hr = HrCreateBinaryDataFile(szOutputFile, cbConfigData, pbConfigData);
	if (FAILED(hr))
	{
		goto cleanup;
	}

cleanup:
	// Print the results of the operation if we got that far.

	if (fPrintResult)
	{
		if (SUCCEEDED(hr))
		{
			printf("File created.\n");
		}
		else
		{
			HRESULT hrT = NOERROR;
			EDKEVENTCOUNT sEventCount = {0};

			hrT = HrEventGetCounts(&sEventCount);
			if (FAILED(hrT) || 
				(sEventCount.cError == 0 && sEventCount.cWarning == 0))
			{
				fprintf(stderr, "ERROR: operation failed.\n");
			}

			// Print the number of errors logged.

			if (sEventCount.cError == 1)
			{
				fprintf(stderr, 
					"ERROR: 1 error written to NT event log.\n");
			}
			else if (sEventCount.cError > 1)
			{
				fprintf(stderr, 
					"ERROR: %d errors written to NT event log.\n");
			}
				
			// Print the number of warnings logged.

			if (sEventCount.cWarning == 1)
			{
				fprintf(stderr, 
					"WARNING: 1 warning written to NT event log.\n");
			}
			else if (sEventCount.cWarning > 1)
			{
				fprintf(stderr, 
					"WARNING: %d warnings written to NT event log.\n");
			}
		}
	}

	// Free up everything.

	if (fMAPIInitialized)
	{
		MAPIFREEBUFFER(pProps);
		MAPIFREEBUFFER(pbConfigData);
		MAPIUninitialize();
	}

	// Close event logging.

	if (fEventLogOpen)
	{
		(void)HrEventCloseLog();
		fEventLogOpen = FALSE;
	}

    // return exit code
    return _nEcFromHr(hr);

}



//$--PrintUsage-----------------------------------------------------------------
//  Print brief message about how to use this program.
// -----------------------------------------------------------------------------
static VOID PrintUsage(void)                    // RETURNS: nothing
{
	DEBUGPRIVATE("PrintUsage()\n");

	printf("USAGE: CFGCODE InFile OutFile [Flags]\n");
	printf("\n");
	printf("  [Flags]        Enter CFGCODE /? for details\n");
}



//$--PrintHelp------------------------------------------------------------------
//  Print more detailed message about how to use this program.
// -----------------------------------------------------------------------------
static VOID PrintHelp(void)                             // RETURNS: nothing
{
	DEBUGPRIVATE("PrintHelp()\n");

	printf("Utility to create a packed configuration data file from a .INI "
		"file.\n");
	printf("\n");
	printf("USAGE: CFGCODE InFile OutFile [Flags]\n");
	printf("\n");
	printf("  InFile         Input .INI file containing MAPI properties\n");
	printf("  OutFile        Output file to write packed configuration data\n");
	printf("  /SECTION=      Name of the [Section] in the .INI file\n");
	printf("  /NAME=         Configuration name for packed data\n");
	printf("  /HELP or /?    Display help screen\n");
}



//$--HrParseCommandLine---------------------------------------------------------
//  Parse the command line arguments and put their values in the appropriate 
//  variables.
// -----------------------------------------------------------------------------
static HRESULT HrParseCommandLine(              // RETURNS: HRESULT
	IN      int                             argc,                   // number of arguments on command line
	IN      char *                  argv[])                 // array of command line arguments
{
	HRESULT         hr                              = NOERROR;
	HRESULT         hrT                             = NOERROR;
	int                     i                               = 0;
	char *          pszArgument             = NULL;
	char *          pszValue                = NULL;
	int                     cNonFlagArgs    = 0;

	DEBUGPRIVATE("HrParseCommandLine()\n");

	hr = CHK_main(argc, argv);
	if (FAILED(hr))
		RETURN(hr);

	// If there are no flags on the command line then just print usage message.

	if (argc < 2)
	{
		fPrintUsage = TRUE;
		goto cleanup;
	}

	// Do an initial check for /? or /HELP.  If found, don't do any other 
	// parsing.

	for (i = 1; i < argc; i++)
	{
		hrT = _HrExpandCommandLineArgument(
			argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
			&pszArgument, &pszValue);

		if (SUCCEEDED(hrT) && pszArgument && 
			(!_stricmp(pszArgument,ARG_HELP1) || 
			!_stricmp(pszArgument,ARG_HELP2)))
		{
			fPrintHelp = TRUE;
			goto cleanup;
		}
	}

	// Loop through and parse all the command line arguments.

	for (i = 1; i < argc; i++)
	{
		 hr = _HrExpandCommandLineArgument(
			argv[i], rgpszArgArray, ARRAY_CNT(rgpszArgArray), NULL, 
			&pszArgument, &pszValue);
		if (FAILED(hr))
		{
			fprintf(stderr, "ERROR: unable to parse command line flags.\n");
			goto cleanup;
		}

		// Parse non-flag arguments.

		if (pszArgument == NULL && pszValue != NULL)
		{
			switch (++cNonFlagArgs)
			{
				case 1:         // Input File
					STRNCPY(szInputFile, pszValue);
					break;

				case 2:         // Output File
					STRNCPY(szOutputFile, pszValue);
					break;

				default:        // Too many arguments!!!
					fprintf(stderr, "ERROR: unknown argument %s\n", argv[i]);
					hr = HR_LOG(E_FAIL);
			}
		}

		// Parse flag arguments that don't take a value.

		else if (pszArgument != NULL && pszValue == NULL)
		{
			fprintf(stderr, "ERROR: flag /%s requires a value\n", 
				pszArgument);
			hr = HR_LOG(E_FAIL);
		}

		// Parse flag arguments that take a value.

		else if (pszArgument != NULL && pszValue != NULL)
		{
			if (!_stricmp(pszArgument,ARG_SECTION))
			{
				STRNCPY(szSection, pszValue);
			}
			else
			if (!_stricmp(pszArgument,ARG_CONFIG_NAME))
			{
				STRNCPY(szConfigName, pszValue);
			}
			else
			{
				fprintf(stderr, "ERROR: flag /%s does not take a value\n", 
					pszArgument);
				hr = HR_LOG(E_FAIL);
			}
		}

		// Catch unknown flags.

		else
		{
			fprintf(stderr, "ERROR: unknown flag %s\n", argv[i]);
			hr = HR_LOG(E_FAIL);
		}
	}

	// Now make sure that all the flags are valid.

	if (*szInputFile == 0)
	{
		fprintf(stderr, "ERROR: please specify %s\n", ARG_INPUT_FILE);
		hr = HR_LOG(E_FAIL);
	}

	if (*szOutputFile == 0)
	{
		fprintf(stderr, "ERROR: please specify %s\n", ARG_OUTPUT_FILE);
		hr = HR_LOG(E_FAIL);
	}

	if (*szSection == 0)
	{
		fprintf(stderr, "ERROR: please specify /%s\n", ARG_SECTION);
		hr = HR_LOG(E_FAIL);
	}

	if (*szConfigName == 0)
	{
		fprintf(stderr, "ERROR: please specify /%s\n", ARG_CONFIG_NAME);
		hr = HR_LOG(E_FAIL);
	}

cleanup:

	RETURN(hr);
}



//$--HrReadPropsFromINIFile-----------------------------------------------------
//  Read a set of MAPI properties from a .INI file.
//
//  Properties are stored with the property tags as hex values, as follows:
//
//  [Section_Name]
//  <property_tag>=<value>
//  <property_tag>=<value>
//  <property_tag>=<value>
// -----------------------------------------------------------------------------
static HRESULT HrReadPropsFromINIFile(  // RETURNS: HRESULT
	IN      LPTSTR                  pszInputFile,   // name of file to read properties from
	IN      LPTSTR                  pszSection,             // name of section in file
	OUT     ULONG *                 pcProps,                // number of properties read from file
	OUT     LPSPropValue *  ppProps)                // array of properties read from file
{
	HRESULT                 hr                                      = NOERROR;
	LPTSTR                  pszSectionBuffer        = NULL;
	ULONG                   cchSectionBuffer        = 2048;
	ULONG                   cchActualSize           = 0;
	LPTSTR                  psz                                     = NULL;
	LPTSTR                  pszFullLine                     = NULL;
	ULONG                   iProp                           = 0;
	ULONG                   cProps                          = 0;
	LPSPropValue    pProps                          = NULL;
	ULONG                   ulPropTag                       = 0;
	ULONG                   ulError                         = ERROR_SUCCESS;

	DEBUGPRIVATE("HrReadPropsFromINIFile()\n");

	hr = CHK_HrReadPropsFromINIFile(
		pszInputFile, 
		pszSection, 
		pcProps, 
		ppProps);
	if (FAILED(hr))
		RETURN(hr);

	// Read the entire section from the .INI file into the buffer.
	// If the buffer is too small then double its size and keep trying.

	while (TRUE)
	{
		// Get the memory for the buffer to read in the section.

		hr = MAPIAllocateBuffer(cchSectionBuffer, &pszSectionBuffer);
		if (FAILED(hr))
		{
			EventLogMsg(
				EDKEVENT_ERROR, 
				0, 
				1, ERROR_OUTOFMEMORY);
			goto cleanup;
		}
	ZeroMemory(pszSectionBuffer, cchSectionBuffer);

		// Read in the section data.

		SetLastError(ERROR_SUCCESS);
		cchActualSize = GetPrivateProfileSection(
			pszSection, 
			pszSectionBuffer, 
			cchSectionBuffer, 
			pszInputFile);
		ulError = GetLastError();
		if (ulError != ERROR_SUCCESS)
		{
	    if (ulError == ERROR_FILE_NOT_FOUND)
	    {
			EventLogMsg(
				CFGCODE_CANNOT_READ_PROFILE_SECTION_FNF, 
				2, pszSection, pszInputFile, 
				0);
	    }
	    else
	    {
			EventLogMsg(
				CFGCODE_CANNOT_READ_PROFILE_SECTION, 
				2, pszSection, pszInputFile, 
				1, GetLastError());
	    }
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		// If the buffer was big enough then we're done.  If the buffer is 
		// not big enough then the return value is the buffer size minus 
		// two (see GetPrivateProfileSection() documentation).

		if (cchActualSize < (cchSectionBuffer - 2))
			break;

		// Otherwise, add 2K to the buffer size and try again.

		MAPIFREEBUFFER(pszSectionBuffer);

		cchSectionBuffer += 2048;
	}

	// Count the number of properties we've read.

	for (psz = pszSectionBuffer; *psz; psz += (lstrlen(psz) + 1))
	{
		cProps++;
	}

	// Allocate an array of SPropValue's big enough to hold all the properties.

	hr = MAPIAllocateBuffer(cProps * sizeof(SPropValue), &pProps);
	if (FAILED(hr))
	{
		EventLogMsg(
			EDKEVENT_ERROR, 
			0, 
			1, ERROR_OUTOFMEMORY);
		goto cleanup;
	}

	// Read in the data and store it in the allocated array.  We may also need 
	// to allocate other pieces of memory to put the values of data items.

	for (
		psz = pszSectionBuffer, iProp = 0; 
		*psz; 
		psz += (lstrlen(psz) + 1), iProp++)
	{
		ASSERTERROR(iProp < cProps, "iProp >= cProps: array overflow!");

		// Save pointer to original string in case we have to log an error.

		pszFullLine = psz;

		// Get the property tag.

		ulPropTag = strtol(psz, &psz, 16);
	if (psz == pszFullLine)
		{
			EventLogMsg(
				CFGCODE_NO_PROP_TAG, 
				1, pszFullLine, 
				0);
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		// Make sure there's an equal sign.

		if (*psz++ != '=')
		{
			EventLogMsg(
				CFGCODE_PROP_TAG_WITHOUT_EQUALS, 
				1, pszFullLine, 
				0);
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		// Get the value based on the property type.

		hr = HrParsePropValue(pszFullLine, ulPropTag, psz, pProps, &pProps[iProp]);
		if (FAILED(hr))
			goto cleanup;

	} // end for

	// Set the output parameters.

	*pcProps = cProps;
	*ppProps = pProps;

cleanup:
	MAPIFREEBUFFER(pszSectionBuffer);
	if (FAILED(hr))
	{
		MAPIFREEBUFFER(pProps);
	}

	RETURN(hr);
}



//$--HrParsePropValue-----------------------------------------------------------
//  Takes a text version of a property value and fills in an SPropValue 
//  structure.  If memory needs to be allocated, it is allocated using 
//  MAPIAllocateMore() based on the object passed in pBaseObject.
//
//  Valid property value formats for property types are as follows (and do 
//  not include the quotes):
//
//  PT_BINARY   a series of two digit hex numbers separated by spaces
//              (e.g. "01 fe 2a 00 1c")
//
//  PT_BOOLEAN  the value 1 or 0 (1=True, 0=False)
//
//  PT_LONG     a decimal or hex constant (e.g. "127" or "0x0fff0003")
//
//  PT_STRING8  any string of characters (e.g. "This is fun!")
//
//  PT_SYSTIME  a date in the format "yyyy/mm/dd hh:mm:ss" 
//              (e.g. "1995/12/31 23:59:59")
// -----------------------------------------------------------------------------
static HRESULT HrParsePropValue(                // RETURNS: HRESULT
    IN  LPTSTR          pszFullLine,    // the full line (for error logging)
	IN      ULONG                   ulPropTag,              // property tag of this property
	IN      LPTSTR                  pszValueText,   // text of property value to parse
	IN      LPVOID                  pBaseObject,    // base object for MAPIAllocateMore()
	OUT     LPSPropValue    pProp)                  // structure to write results
{
	HRESULT                 hr                              = NOERROR;
	LPTSTR          psz             = NULL;
	LPTSTR          pszPrev         = NULL;

	DEBUGPRIVATE("HrParsePropValue()\n");

	hr = CHK_HrParsePropValue(
	pszFullLine, 
		ulPropTag, 
		pszValueText, 
		pBaseObject, 
		pProp);
	if (FAILED(hr))
		RETURN(hr);

	switch (PROP_TYPE(ulPropTag))
	{
		case PT_BINARY:
		{
			ULONG cb = 0;
			ULONG ib = 0;
			LPBYTE pb = NULL;
			LONG lNumber = 0;

			// Count the bytes and check that all the bytes are valid.

			psz = pszValueText;
			while (*psz)
			{
				if (isspace(*psz))
					psz++;
				else
				{
					pszPrev = psz;
					lNumber = strtol(psz, &psz, 16);
					if (psz == pszPrev || lNumber > 255 || lNumber < 0)
		    {
					hr = HR_LOG(E_FAIL);
					EventLogMsg(
						CFGCODE_ILLEGAL_BINARY_VALUE, 
						1, pszFullLine, 
						0);
					goto cleanup;
		    }
					cb++;
				}
			}

			// Allocate a buffer big enough for the number of bytes.

			hr = MAPIAllocateMore(cb, pBaseObject, &pProp->Value.bin.lpb);
			if (FAILED(hr))
			{
				EventLogMsg(
					EDKEVENT_ERROR, 
					0, 
					1, ERROR_OUTOFMEMORY);
				goto cleanup;
			}
			pProp->Value.bin.cb = cb;

			// Write the bytes into the buffer.

			psz = pszValueText;
			for (ib = 0, pb = pProp->Value.bin.lpb; ib < cb; ib++, pb++)
			{
				*pb = (BYTE)strtol(psz, &psz, 16);
			}

			break;
		}

		case PT_BOOLEAN:
	    psz = pszValueText;

	    while (isspace(*psz))
		psz++;

	    pszPrev = psz;
			pProp->Value.l = strtol(psz, &psz, 0);

	    while (isspace(*psz))
		psz++;

	    if (psz == pszPrev || *psz || 
		(pProp->Value.l != 0 && pProp->Value.l != 1))
	    {
			hr = HR_LOG(E_FAIL);
			EventLogMsg(
				CFGCODE_ILLEGAL_BOOLEAN_VALUE, 
				1, pszFullLine, 
				0);
				goto cleanup;
	    }
			break;

		case PT_LONG:
	    psz = pszValueText;

	    while (isspace(*psz))
		psz++;

	    pszPrev = psz;
			pProp->Value.l = strtol(psz, &psz, 0);

	    while (isspace(*psz))
		psz++;

	    if (psz == pszPrev || *psz)
	    {
			hr = HR_LOG(E_FAIL);
			EventLogMsg(
				CFGCODE_ILLEGAL_LONG_VALUE, 
				1, pszFullLine, 
				0);
				goto cleanup;
	    }
			break;

		case PT_STRING8:
		{
			ULONG cb = strlen(pszValueText) + 1;

			hr = MAPIAllocateMore(cb, pBaseObject, &pProp->Value.lpszA);
			if (FAILED(hr))
			{
			hr = HR_LOG(E_FAIL);
				EventLogMsg(
					EDKEVENT_ERROR, 
					0, 
					1, ERROR_OUTOFMEMORY);
				goto cleanup;
			}
			MoveMemory(pProp->Value.lpszA, pszValueText, cb);
			break;
		}

		case PT_SYSTIME:
		{
			SYSTEMTIME st = {0};
	    CHAR chBogus = 0;
			int lReturn = 0;
			BOOL fItWorked = TRUE;

			lReturn = sscanf(
				pszValueText, 
				" %hd/%hd/%hd %hd:%hd:%hd %c", 
				&st.wYear, 
				&st.wMonth, 
				&st.wDay, 
				&st.wHour, 
				&st.wMinute, 
				&st.wSecond, 
				&chBogus);
			if (lReturn == 0 || lReturn == EOF || chBogus)
			{
				hr = HR_LOG(E_FAIL);
				EventLogMsg(
					CFGCODE_ILLEGAL_SYSTIME_VALUE, 
					1, pszFullLine, 
					0);
				goto cleanup;
			}

			fItWorked = SystemTimeToFileTime(&st, &pProp->Value.ft);
			if (!fItWorked)
			{
				hr = HR_LOG(E_FAIL);
				EventLogMsg(
					CFGCODE_CANNOT_CONVERT_TIME, 
					1, pszFullLine, 
					1, GetLastError());
				goto cleanup;
			}

			break;
		}

		default:
		{
			TCHAR szPropType[9] = {0};

			wsprintf(szPropType, TEXT("%08lx"), PROP_TYPE(ulPropTag));

			hr = HR_LOG(E_NOTIMPL);
			EventLogMsg(
				CFGCODE_UNSUPPORTED_PROPERTY_TYPE, 
				1, pszFullLine, 
				0);
			goto cleanup;
		}
	}

	pProp->ulPropTag = ulPropTag;

cleanup:
	RETURN(hr);
}



//$--HrCreateBinaryDataFile-----------------------------------------------------
//  Create a file and write binary data to it.
// -----------------------------------------------------------------------------
static HRESULT HrCreateBinaryDataFile(  // RETURNS: HRESULT
	IN      LPTSTR                  pszOutputFile,  // name of file to create
	IN      ULONG                   cbData,                 // number of bytes to write to file
	IN      LPBYTE                  pbData)                 // binary data to write to file
{
	HRESULT                 hr                              = NOERROR;
	HANDLE                  hOutputFile             = INVALID_HANDLE_VALUE;
	BOOL                    fItWorked               = TRUE;
	DWORD                   cbBytesWritten  = 0;

	DEBUGPRIVATE("HrCreateBinaryDataFile()\n");

	hr = CHK_HrCreateBinaryDataFile(
		pszOutputFile, 
		cbData, 
		pbData);
	if (FAILED(hr))
		RETURN(hr);

	hOutputFile = CreateFile(
		pszOutputFile,                                  // file name
		GENERIC_WRITE,                                  // open for write
		0,                                                              // no sharing
		NULL,                                                   // default security
		CREATE_ALWAYS,                                  // overwrite existing file
		FILE_ATTRIBUTE_NORMAL,                  // normal file
		NULL);                                                  // no template file
	if (hOutputFile == INVALID_HANDLE_VALUE)
	{
		EventLogMsg(
			CFGCODE_COULD_NOT_CREATE_FILE, 
			1, pszOutputFile, 
			1, GetLastError());
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	fItWorked = WriteFile(
		hOutputFile,                                    // file handle
		pbData,                                                 // buffer to write
		cbData,                                                 // number of bytes to write
		&cbBytesWritten,                                // number of bytes actually written
		NULL);                                                  // no overlapped
	if (!fItWorked || cbBytesWritten != cbData)
	{
		EventLogMsg(
			CFGCODE_COULD_NOT_WRITE_FILE, 
			1, pszOutputFile, 
			1, GetLastError());
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	fItWorked = CloseHandle(hOutputFile);
	if (!fItWorked)
	{
		EventLogMsg(
			CFGCODE_COULD_NOT_CLOSE_FILE, 
			1, pszOutputFile, 
			1, GetLastError());
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}
	hOutputFile = INVALID_HANDLE_VALUE;

cleanup:
	if (FAILED(hr) && hOutputFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hOutputFile);
		DeleteFile(pszOutputFile);
	}

	RETURN(hr);
}
