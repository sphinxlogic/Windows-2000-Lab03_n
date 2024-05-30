// --edkevent.c-----------------------------------------------------------------
//
//  Routines to do event logging for EDK.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include <stdarg.h>
#include "edkevent.chk"


static EDKEVENTCOUNT	sEventCount					= {0};
static HANDLE			hEventSource				= NULL;
static BOOL				fPreviouslyOpenedHandle		= FALSE;


static VOID LogEventCommon(
	IN BOOL fIsUnicode,
	IN DWORD dwEvent,
	IN DWORD cStrings,
	IN va_list pArgList);


//$--HrEventOpenLog----------------------------------------------------------
//  Initialize event logging for the EDK.
// -----------------------------------------------------------------------------
HRESULT HrEventOpenLog(				// RETURNS: HRESULT
	IN LPSTR pszApplicationName,		// name of this application
	IN LPSTR pszExecutableName,		// name of executable
    IN LPSTR pszEventMessageFile,      // name of event message file
    IN LPSTR pszParameterMessageFile,  // name of parameter message file
    IN LPSTR pszCategoryMessageFile,   // name of category message file
	OUT LPHANDLE phEventSourceOut)		// [returns event logging handle]
{
    HRESULT     hr              	= NOERROR;
	DWORD		dwError				= ERROR_SUCCESS;
	CHAR		szKeyName			[MAX_PATH+1] = {0};
	HKEY		hKey				= NULL;
	DWORD		dwDisposition		= 0;
	HMODULE		hinstModule			= NULL;
	CHAR		szExecutableBuffer	[MAX_PATH+1] = {0};
	DWORD		cch					= 0;

    LPSTR      pszMessageFile      = NULL;

	DEBUGPUBLIC("HrEventOpenLog()\n");

	// Check the parameters.

	hr = CHK_HrEventOpenLog(
		pszApplicationName, 
		pszExecutableName, 
        pszEventMessageFile,
        pszParameterMessageFile,
        pszCategoryMessageFile,
		phEventSourceOut);

	if(FAILED(hr))
		RETURN(hr);

	// Make sure the event log isn't already open.

	if (hEventSource != NULL)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Flag that this is not a previously opened handle, and should be closed 
	// when HrEventCloseLog() is called.

	fPreviouslyOpenedHandle = FALSE;

	// If they didn't pass in an executable name then figure out the name 
	// of the executable currently executing and use that.

	if (pszExecutableName == NULL)
	{
		hinstModule = GetModuleHandle(NULL);
		if (hinstModule == NULL)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		cch = GetModuleFileName(
			hinstModule, 
			szExecutableBuffer, 
			sizeof(szExecutableBuffer) - 1);
		if (cch == 0)
		{
			hr = HR_LOG(E_FAIL);
			goto cleanup;
		}

		pszExecutableName = szExecutableBuffer;
	}

	// Create the name of the registry key for this application.

	lstrcpy(szKeyName, 
		"SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\");
	lstrcat(szKeyName, pszApplicationName);

	// Open or create the registry key.  This registry key contains/will 
	// contain values that are required by the Windows NT function 
	// ReportEvent().

	dwError = RegCreateKeyEx(
		HKEY_LOCAL_MACHINE, 
		szKeyName, 
		0, 
		NULL, 
		REG_OPTION_NON_VOLATILE, 
		KEY_ALL_ACCESS, 
		NULL, 
		&hKey, 
		&dwDisposition);
	if (dwError != ERROR_SUCCESS)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Add the message file names to the key.

    if(pszEventMessageFile == NULL)
    {
        pszMessageFile = pszExecutableName;
    }
    else
    {
        pszMessageFile = pszEventMessageFile;
    }

	hr = _HrWriteRegistrySZ(
	    hKey,
	    "EventMessageFile", 
		pszMessageFile);

	if (FAILED(hr))
    {
		goto cleanup;
    }

    if(pszParameterMessageFile == NULL)
    {
        pszMessageFile = "%SystemRoot%\\System32\\kernel32.dll";
    }
    else
    {
        pszMessageFile = pszParameterMessageFile;
    }

	hr = _HrWriteRegistrySZ(
	    hKey,
	    "ParameterMessageFile", 
		pszMessageFile);

	if(FAILED(hr))
    {
		goto cleanup;
    }

    if(pszCategoryMessageFile == NULL)
    {
        pszMessageFile = pszExecutableName;
    }
    else
    {
        pszMessageFile = pszCategoryMessageFile;
    }

	hr = _HrWriteRegistrySZ(
	    hKey,
	    "CategoryMessageFile", 
		pszMessageFile);

	if(FAILED(hr))
    {
		goto cleanup;
    }

	hr = _HrWriteRegistryDWORD(
        hKey,
        "TypesSupported", 
		EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE);

	if(FAILED(hr))
    {
		goto cleanup;
    }

	// Register the event source.

	hEventSource = RegisterEventSource(NULL, pszApplicationName);

	if (hEventSource == NULL)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Reset the event type counters.

	sEventCount.cError = 0;
	sEventCount.cWarning = 0;
	sEventCount.cInformation = 0;

	// Return the handle if they requested it.

	if (phEventSourceOut)
	{
		*phEventSourceOut = hEventSource;
	}

cleanup:
	if (hKey != NULL)
	{
		dwError = RegCloseKey(hKey);

		if (dwError != ERROR_SUCCESS)
		{
			hr = HR_LOG(E_FAIL);
		}

		hKey = NULL;
	}

	RETURN(hr);
}


//$--HrEventUseExisting---------------------------------------------------
//  Initialize event logging for the EDK by connecting to an already open 
//  event log handle.  This allows EventLogMsg() to log events to a handle 
//  that was opened elsewhere.  Calling HrEventCloseLog() after calling 
//  this routine will do internal cleanup but will not close the event log 
//  handle.  One example of where this routine is useful is within a DLL 
//  that is called by EDK code in which event logging has already been 
//  initialized.
// -----------------------------------------------------------------------------
HRESULT HrEventUseExisting(		// RETURNS: HRESULT
	IN HANDLE hExistingEventSource)		// previously opened event log handle
{
	HRESULT hr = NOERROR;

	DEBUGPUBLIC("HrEventUseExisting()\n");

	// Check the parameters.

	hr = CHK_HrEventUseExisting(
		hExistingEventSource);
	if (FAILED(hr))
		RETURN(hr);

	// Make sure the event log isn't already open.

	if (hEventSource != NULL)
	{
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Use the existing event log handle.

	hEventSource = hExistingEventSource;

cleanup:
	RETURN(hr);
}


//$--EventLogMsg----------------------------------------------------------------
//
//  EventLogMsgA -- byte string version
//  EventLogMsgW -- word string version
//
//  Log an event to the event log, and optionally, log the original error(s) 
//  that caused the event.  It has the following parameters:
//
//   DWORD    dwEvent
//   DWORD    cStrings
//  [LPSTR   pszString1]
//  [LPSTR   pszString2]
//  [...................]
//  [LPSTR   pszStringN]
//   DWORD    cErrorCodes
//  [DWORD    dwErrorCode1]
//  [DWORD    dwErrorCode2]
//  [.....................]
//  [DWORD    dwErrorCodeN]
//
//  Each of the above strings and error codes are used as parameters to the 
//  message in the order they appear.  This means that in event messages, 
//  all of the  error message replacement parameters must have higher numbers 
//  than all of the string replacement parameters.  For example:
//
//      EventLogMsg(
//          MYAPP_CANNOT_COPY_FILE, 
//          2, pszSourceFile, pszDestFile, 
//          1, dwError);
//
//  And the message would be defined as:
//
//      MessageId=
//      Severity=Error
//      Facility=Application
//      SymbolicName=MYAPP_CANNOT_COPY_FILE
//      Language=English
//      Cannot copy file from %1 to %2 due to the following error:%n%3.
//      .
//
//  Note: This routine preserves the last error value returned by 
//        GetLastError().
//
// -----------------------------------------------------------------------------

//$--EventLogMsgA---------------------------------------------------------------
//  Byte string version of EventLogMsg().
//
//  IMPORTANT!!! The error code count [and error code list] is REQUIRED after 
//  the text string count [and text string list].  Failure to include the 
//  error code argument(s) may cause unexpected results.
// -----------------------------------------------------------------------------
VOID EventLogMsgA(						// RETURNS: nothing
	IN DWORD dwEvent,					// error code of event to log
	IN DWORD cStrings,					// number of text string parameters
	IN ...								// text string parameters
//	IN DWORD cErrors,					// number of error code parameters
//	IN ...								// error code parameters
)
{
	DWORD   dwSaveLastError	= 0;
	va_list	pArgList        = {0};

	dwSaveLastError = GetLastError();

	va_start(pArgList, cStrings);
	LogEventCommon(FALSE, dwEvent, cStrings, pArgList);
	va_end(pArgList);

	SetLastError(dwSaveLastError);
}

//$--EventLogMsgW---------------------------------------------------------------
//  Word string version of EventLogMsg().
//
//  IMPORTANT!!! The error code count [and error code list] is REQUIRED after 
//  the text string count [and text string list].  Failure to include the 
//  error code argument(s) may cause unexpected results.
// -----------------------------------------------------------------------------
VOID EventLogMsgW(						// RETURNS: nothing
	IN DWORD dwEvent,					// error code of event to log
	IN DWORD cStrings,					// number of text string parameters
	IN ...								// text string parameters
//	IN DWORD cErrors,					// number of error code parameters
//	IN ...								// error code parameters
)
{
	DWORD	dwSaveLastError	= 0;
	va_list	pArgList        = {0};

	dwSaveLastError = GetLastError();

	va_start(pArgList, cStrings);
	LogEventCommon(TRUE, dwEvent, cStrings, pArgList);
	va_end(pArgList);

	SetLastError(dwSaveLastError);
}

// Maximum total number of string and error parameters allowed by EventLogMsg().
#define		_MAX_BUILD_STRINGS			20

// Size of buffer to write error number string into (must be big enough to hold 
// a string of the form: %%<decimal#> in either multi-byte or UNICODE.
#define		_MAX_ERROR_STRING_BYTES		40

//$--LogEventCommon-------------------------------------------------------------
//  Common event logging code for both multi-byte and UNICODE strings.
// -----------------------------------------------------------------------------
static VOID LogEventCommon(				// RETURNS: nothing
	IN BOOL fIsUnicode,					// flag set if text strings are UNICODE
	IN DWORD dwEvent,					// error code of event to log
	IN DWORD cStrings,					// number of text strings that follow
	IN va_list pArgList)				// argument strings/error codes
{
	HRESULT		hr						= NOERROR;
	BOOL		fItWorked				= TRUE;
	DWORD		iArg					= 0;
	DWORD		cBuildStrings			= 0;
	WORD		wEventType				= 0;

	// This array can contain either all LPSTR's or all LPWSTR's.
	LPVOID		rgpvBuildStrings		[_MAX_BUILD_STRINGS] = {NULL};

	// This array will be used to build either WCHAR strings or CHAR strings.
	BYTE		rgrgbBuildErrorStrings	[_MAX_BUILD_STRINGS]
										[_MAX_ERROR_STRING_BYTES] = {0};

	DEBUGPRIVATE("LogEventCommon()\n");

	// Make sure event log is open.

	if (hEventSource == NULL)
	{
		OutputDebugString("Event log is not open in LogEventCommon()\n");
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Get the number of string arguments and make sure it is within limits.

	cBuildStrings = cStrings;

	if (cBuildStrings > _MAX_BUILD_STRINGS)
	{
		OutputDebugString("Too many string parameters in LogEventCommon()\n");
		hr = HR_LOG(E_INVALIDARG);
		goto cleanup;
	}

	// Get the string arguments and make sure they are valid string pointers.

	for (iArg = 0; iArg < cBuildStrings; iArg++)
	{
		BOOL fIsValidString = TRUE;

		if (fIsUnicode)
		{
			rgpvBuildStrings[iArg] = va_arg(pArgList, LPWSTR);
			fIsValidString = TEST_STRINGW_PTR(rgpvBuildStrings[iArg]);
		}
		else
		{
			rgpvBuildStrings[iArg] = va_arg(pArgList, LPSTR);
			fIsValidString = TEST_STRINGA_PTR(rgpvBuildStrings[iArg]);
		}

		if (!fIsValidString)
		{
			OutputDebugString("Invalid string parameter in LogEventCommon()\n");
			hr = HR_LOG(E_INVALIDARG);
			goto cleanup;
		}
	}

	// Get the number of error code arguments and make sure it is within limits.

	cBuildStrings += va_arg(pArgList, DWORD);

	if (cBuildStrings > _MAX_BUILD_STRINGS)
	{
		OutputDebugString("Too many error code parameters in "
			"LogEventCommon()\n");
		hr = HR_LOG(E_INVALIDARG);
		goto cleanup;
	}

	// Get the error code arguments and convert them to strings of the form: 
	// %%<Number>.

	for ( ; iArg < cBuildStrings; iArg++)
	{
		rgpvBuildStrings[iArg] = rgrgbBuildErrorStrings[iArg];

		if (fIsUnicode)
		{
			swprintf(rgpvBuildStrings[iArg], L"%%%%%ld", 
				va_arg(pArgList, DWORD));
		}
		else
		{
			sprintf(rgpvBuildStrings[iArg], "%%%%%ld", 
				va_arg(pArgList, DWORD));
		}
	}

	// Compute the event type for this event.

	switch (dwEvent & 0xC0000000)
	{
		case 0xC0000000:
			wEventType = EVENTLOG_ERROR_TYPE;
			break;
		case 0x80000000:
			wEventType = EVENTLOG_WARNING_TYPE;
			break;
		default:
			wEventType = EVENTLOG_INFORMATION_TYPE;
			break;
	}

	// Log the event.

	if (fIsUnicode)
	{
		fItWorked = ReportEventW(
			hEventSource, 
			wEventType, 
			0, 
			dwEvent, 
			NULL, 
			(WORD)cBuildStrings, 
			0, 
			(LPWSTR *)rgpvBuildStrings, 
			NULL);
	}
	else
	{
		fItWorked = ReportEventA(
			hEventSource, 
			wEventType, 
			0, 
			dwEvent, 
			NULL, 
			(WORD)cBuildStrings, 
			0, 
			(LPSTR *)rgpvBuildStrings, 
			NULL);
	}

	if (!fItWorked)
	{
		OutputDebugString("ReportEvent() failed in LogEventCommon()\n");
		hr = HR_LOG(E_FAIL);
		goto cleanup;
	}

	// Bump up the counter for the right type of event.

	switch (wEventType)
	{
		case EVENTLOG_ERROR_TYPE:
			sEventCount.cError++;
			break;
		case EVENTLOG_WARNING_TYPE:
			sEventCount.cWarning++;
			break;
		case EVENTLOG_INFORMATION_TYPE:
			sEventCount.cInformation++;
			break;
		default:
			OutputDebugString(
				"Cannot increment event type counter for "
				"unknown event type.\n");
			break;
	}

cleanup:
	// If we couldn't log it to the event log, then output a message to the 
	// error log and debug log.

	if (FAILED(hr))
	{
		CHAR szDescription[100] = {0};
		sprintf(szDescription, "Unable to log event 0x%08lx\n", dwEvent);
		OutputDebugString(szDescription);
	}
}


//$--HrEventGetCounts--------------------------------------------------------
//  Returns the number of Error, Warning, and Information events logged (by the 
//  current executable).
// -----------------------------------------------------------------------------
HRESULT HrEventGetCounts(			// RETURNS: HRESULT
	OUT LPEDKEVENTCOUNT lpsEventCount)	// structure to return event counts
{
	HRESULT		hr		= NOERROR;

	DEBUGPUBLIC("HrEventGetCounts(lpsEventCount)\n");

	hr = CHK_HrEventGetCounts(
		lpsEventCount);
	if (FAILED(hr))
		RETURN(hr);

	// Return the values.

	MoveMemory(lpsEventCount, &sEventCount, sizeof(sEventCount));

	RETURN(hr);
}


//$--HrEventCloseLog---------------------------------------------------------
//  Shut down event logging for the EDK.
// -----------------------------------------------------------------------------
HRESULT HrEventCloseLog()			// RETURNS: HRESULT
{
	HRESULT		hr				= NOERROR;
	BOOL		fItWorked		= FALSE;

	DEBUGPUBLIC("HrEventCloseLog()\n");

	if (hEventSource && !fPreviouslyOpenedHandle)
	{
		fItWorked = CloseEventLog(hEventSource);
		if (!fItWorked)
		{
			hr = HR_LOG(E_FAIL);
		}
	}

	hEventSource = NULL;

	RETURN(hr);
}

// $--HrEventGetHandle------------------------------------------------------
//
// DESCRIPTION: Retrieve event handle for this executable.
//
// OUTPUT:  phEventLog   --  event log handle pointer
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// Notes:  
//
// 1) The event handle returned will be NULL if there is
// no open event log.
//
// 2) DLLs may not call this function to retrieve the event handle
// which their parent executable set.  If the parent executable sets
// an event handle, then it must pass the event handle to the DLL.
//
// ----------------------------------------------------------------------------
HRESULT HrEventGetHandle(
        IN HANDLE * phEventLog)       // event log handle pointer
{
    HRESULT hr  =   NOERROR;    

    DEBUGPRIVATE("HrEventGetHandle");
        
    // check input parameters
    hr = CHK_HrEventGetHandle(phEventLog);
    
    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Return current event log handle.  Note that it
    // may be NULL.    
    *phEventLog = hEventSource;

    RETURN(hr);

}
