/************************************************************************
*                                                                       *
*   $$Root$$Util.cpp												*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/


#include "StdAfx.h"
#include "$$Root$$Util.h"

//
// Displays debugging information contained in strMessage
void DebugMessage(const string & strMessage)
{
	string dbg = "DEBUG: ";
	dbg += strMessage;
$$IF(PROJTYPE_NTSERVICE)
	ReportICSEvent(dbg.c_str(), EVENTLOG_INFORMATION_TYPE);
$$ELSE
	theTraceBox.Trace(dbg.c_str());
$$ENDIF
}

//
// Displays error information contained in strMessage
void ErrorMessage(const string & strMessage)
{
	string err = "ERROR: ";
	err += strMessage;
$$IF(PROJTYPE_NTSERVICE)
	ReportICSEvent(err.c_str(), EVENTLOG_ERROR_TYPE);
$$ELSE
	theTraceBox.Trace(err.c_str());
$$ENDIF
}

//
// Displays error information contained in strMessage
void FatalErrorMessage(const string & strMessage)
{
	string err = "FATAL ERROR: ";
	err += strMessage;
$$IF(PROJTYPE_NTSERVICE)
	ReportICSEvent(err.c_str(), EVENTLOG_ERROR_TYPE);
$$ELSE
	theTraceBox.Trace(err.c_str());
$$ENDIF
}

//
// Returns a value representing the number of processors
// of the given machine
ULONG GetNumProcessors()
{
	LPCTSTR lpszNumProcessors	= "NUMBER_OF_PROCESSORS";
	LPTSTR lpszBuffer			= new TCHAR[8];
	
	if (NULL == lpszBuffer)
		return 0;

	ULONG ulNumChars = GetEnvironmentVariable(
		lpszNumProcessors,
		lpszBuffer,
		8
		);

	if (ulNumChars == 0)
		return 0;
	else
	{
		int iBase = 10;		
		TCHAR * lpEndChar;
		ULONG ulNumProcessors;
	
		ulNumProcessors = strtoul(
			lpszBuffer, 
			&lpEndChar,
			iBase
			);
		return ulNumProcessors;
	}
}

//
// Displays status information contained in strMessage
void StatusMessage(const string & strMessage)
{
	string status = "STATUS: ";
	status += strMessage;
$$IF(PROJTYPE_NTSERVICE)
	ReportICSEvent(status.c_str(), EVENTLOG_INFORMATION_TYPE);
$$ELSE
	theTraceBox.Trace(status.c_str());
$$ENDIF
}

//
// Displays a warning contained in strMessage
void WarningMessage(const string & strMessage)
{
	string warning = "WARNING: ";
	warning += strMessage;
$$IF(PROJTYPE_NTSERVICE)
	ReportICSEvent(warning.c_str(), EVENTLOG_WARNING_TYPE);
$$ELSE
	theTraceBox.Trace(warning.c_str());
$$ENDIF
}

