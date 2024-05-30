//
// DOTRACE.OBJ:		The main code for handling a trace commands for the
//					ODBC 3.51 driver manager.
//
// Copyright (c) 1995-1998 by Microsoft Corporation.
// All rights reserved
//


#include "headers.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <share.h>
#include "sql.h"
#include "sqlext.h"
#include "odbcinst.h"

#include "tracecon.h"	
#include "sqlucode.h"
#include <tchar.h>
#include <locale.h>


#define	MAX_HANDLES		200
static	LPTRACESTR	szHandleMap[MAX_HANDLES];
static	FILE	*fhTraceFile= NULL;
static  const wchar_t szTraceFileKey[] = L"TraceFile";
extern  CRITICAL_SECTION g_csWrite;

LPCWSTR	szDefaultFileName=  		L"\\SQL.LOG";
LPCWSTR	szODBC=						L"ODBC";
LPCWSTR	szODBCIni=					L"ODBC.INI";

DWORD	*pdwGlobalTraceVariable;	// global (really global) trace flag

char	*RetToChar(RETCODE	RetCode);
VOID GrabErrors( LPTRACESTR	TraceStr);
BOOL	g_fTrace = FALSE;
BOOL	g_fVS	= FALSE;
BOOL	g_fNoTrace = FALSE;

// Vista variables
DWORD	*pdwGlobalVistaVariable;	// global (really global) vista flag

// Members:
//
//	DoTrace()			Called when entering a traced routine
//	TraceReturn()		Called when exiting a traced routine
//	ProcessTrace()		Prints a trace message to the file or stream

VOID	ProcessTrace(
	LPTRACESTR	TraceStr,
	BOOL		fEntry,
	RETCODE		RetCode);


VOID	HandleArgument(
	LPTRACESTR		TraceStr,
	int				iArg,
	BOOL			fEntry,
	LPSTR			szBuffer,
	DWORD			cbBuffer,
	enum ArgTypes	atArgs);

VOID DisplayString(
	LPSTR	szBuffer,
	DWORD	cbBuffer,
	LPSTR	szData,
	DWORD	cbData);

VOID DisplayStringPtr(
	LPSTR	szBuffer,
	DWORD	cbBuffer,
	LPSTR	szData,
	SDWORD	sdwLen,
	SDWORD	sdwMaxLen,
	BOOL	fUnicode,
	BOOL	fCCH);

VOID	HandleCharData(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	LPTRACESTR	TraceStr,
	DWORD		i,
	BOOL		fEntry,
	BOOL		fUnicode,
	BOOL		fCCH)
;

void GetDefaultId(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	SDWORD		sdwValue,
	const struct tagDFTARRAY  *dftList,
	DWORD		cbDft);

void ExtraInfo(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	LPTRACESTR	TraceStr,
	DWORD		iArg);

void GetPtrValue(
	LPSTR			szBuffer,
	DWORD			cbBuffer,
	SDWORD			sdwAttribute,
	LPVOID			lpvData,
	const struct tagDFTARRAY  *dftList,
	DWORD			cbDft,
	BOOL			fEntry,
	LPTRACESTR		TraceStr,
	DWORD			iArg);

void HandlePtr(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	LPTRACESTR	TraceStr,
	DWORD		iArg,
	BOOL		fEntry);

enum ArgTypes CTypeToAType(
	SWORD	swCType);

enum ArgTypes GatorToAType(
	SDWORD	sdwFlag,
	BOOL	fUnicode);
//
// DoTrace: 	Process a trace request
//
// Parameters:
//		TraceStr:	Structure with information about the function 
//					to trace

VOID	DoTrace(LPTRACESTR	TraceStr)
{

	ProcessTrace(TraceStr,TRUE,0);
	return;
}

//
// TraceReturn:	Process a 'post' trace request
//
// Parameters:
//		TraceStr:	saved trace structure
//

VOID	SQL_API TraceReturn(RETCODE	RetHandle, RETCODE RetCode)
{
	LPTRACESTR	TraceStr = NULL;

	

	if (RetHandle > 0)
		TraceStr = szHandleMap[RetHandle - 1];
			


	if (TraceStr)
	{
		if (!(g_fNoTrace))
		{
			ProcessTrace(TraceStr,FALSE, RetCode);
		}
		free(TraceStr);
		_heapmin();
		szHandleMap[RetHandle - 1] = NULL;
	}

	return;
}

// Moved out here because RISC doesn't like huge stacks
static char	szVistaArgs[8 * 1024]; 

//
// ProcessTrace:	Actually handle a trace message
//
// Parameters:
//		TraceStr:	trace structure
//		fEntry:		TRUE if at function entry

VOID	ProcessTrace(
	LPTRACESTR	TraceStr,
	BOOL		fEntry,
	RETCODE		RetCode)
{
	DWORD	i;
	DWORD	dwStrLen;
	DWORD	dwVistaArgLen = 0;
	char	szBuffer[2000];
	char	szProcName[MAX_PATH];
	BOOL	fTrace = (g_fTrace || pdwGlobalTraceVariable && *pdwGlobalTraceVariable) && TraceStr;


	if (g_fNoTrace)
		return;

	if (!fTrace)
	{
		return;
	}

	_splitpath(GetCommandLine(),NULL,NULL,szProcName,NULL);

	// TODO: semaphores
	
	// tracing 
	if (fTrace && !fhTraceFile)
	{
		(void) TraceOpenLogFile(NULL,NULL,0);
		if (!fhTraceFile)
		{
			fTrace = FALSE;
		}
	}

	if (fTrace)
	{
		EnterCriticalSection(&g_csWrite);
		sprintf(szBuffer,
			"\r\n%-15.15s %x:%x\t%s %s ",
			szProcName,
			GetCurrentProcessId(),
			GetCurrentThreadId(),
			(fEntry) ? "ENTER" : "EXIT ",
			TraceStr->szFuncName);

			if (!(fEntry))
			{
				sprintf(szBuffer + strlen(szBuffer),
						" with return code %d (%s)",
						RetCode,
						RetToChar(RetCode));
			}


			fwrite(szBuffer, strlen(szBuffer),1,fhTraceFile);
			fwrite("\r\n",2,1,fhTraceFile);
	}

	for (i = 0; i < TraceStr->nArgs; i++)
	{
		sprintf(szBuffer,"\t\t%-18.18s ",TraceStr->szArg[i]);
		if (fTrace)
		{
			fwrite(szBuffer,strlen(szBuffer),1,fhTraceFile);
		}


		// only trace output arguments if the return was successful.

		HandleArgument(TraceStr,
						i,
						fEntry || !SQL_SUCCEEDED(RetCode),
						szBuffer,
						sizeof(szBuffer),
						TraceStr->atArg[i]);
		dwStrLen = strlen(szBuffer);

		if (fTrace)
		{
			fwrite(szBuffer,dwStrLen, 1,fhTraceFile);
		}

		
	}

	if (fTrace)
	{
		if (!fEntry) 
		{
			if ((RetCode == SQL_SUCCESS_WITH_INFO) ||
		    	(RetCode == SQL_ERROR))
			{
				GrabErrors(TraceStr);
			}
		}
		fflush(fhTraceFile);
		LeaveCriticalSection(&g_csWrite);
	}

}

// TraceOpenLogFile:	Open the log file for a trace
//
// Parameters:
//		lpwszFileName:		file name to open or NULL (UNICODE!)
//		lpwszOutputMsg:		space for output error message
//		cbOutputMsg:		max size of output message
//
// Returns:
//		File handle or NULL
//
// Notes:   If NULL passed in for the file name, looks for the
//			trace file name in the registry.   If none there, it uses
//			\SQL.LOG

RETCODE SQL_API TraceOpenLogFile(
	LPWSTR	szFileName,
	LPWSTR	lpwszOutputMsg,
	DWORD	cbOutputMsg)
{
	WCHAR		szTraceFile[_MAX_PATH + 1];
	char		aszTraceFile[_MAX_PATH];

	if (fhTraceFile)
		return SQL_SUCCESS;

	// Get default entry if no filename specified

	if (!(szFileName))
	{
		SQLGetPrivateProfileStringW(szODBC, 
									szTraceFileKey, 
									szDefaultFileName,
									szTraceFile, 
									sizeof(szTraceFile) / sizeof(WCHAR), 
									szODBCIni);
		
		szFileName = szTraceFile;
	}

	fhTraceFile = _wfsopen(szFileName,L"abc",SH_DENYNO);

	// Maybe we are on the Win95 platform

	if (fhTraceFile == NULL)
	{

		WideCharToMultiByte(CP_ACP,		// XXX Consider: make any cp?
							0,								
							szFileName,
							wcslen(szFileName) + 1,
							aszTraceFile	,
							sizeof(aszTraceFile),
							NULL,
							FALSE);

		fhTraceFile = _fsopen(aszTraceFile,"abc",SH_DENYNO);
		

	}

	if (fhTraceFile == NULL)
	{
		char	szBuffer[1000], szFull[_MAX_PATH];

		_fullpath(szFull,aszTraceFile,sizeof(szFull));

		sprintf(szBuffer,
				"Unable to open ODBC trace file %s: %s\n",
				 szFull,
				 strerror(errno));
		OutputDebugString(szBuffer);

		szBuffer[strlen(szBuffer) - 1] = '\0';

		if (lpwszOutputMsg)
		{
			MultiByteToWideChar(CP_ACP,
								0,
								szBuffer,
								strlen(szBuffer) + 1,
								lpwszOutputMsg,
								cbOutputMsg / sizeof(WCHAR));
		}
		return SQL_ERROR;
	}

	return SQL_SUCCESS;
	
}

//
// TraceCloseLogFile:		Close the log file
//
// Parameters: none
//

RETCODE	SQL_API TraceCloseLogFile()
{
	if (fhTraceFile)
		fclose(fhTraceFile);

	return SQL_SUCCESS;
}

//
// RetToChar: convert a retcode to a character represantation
//
// Parameters:
//		RetCode		Retcode value
//
// Returns:
// 		String mapping to that value

char	*RetToChar(RETCODE	RetCode)
{
	switch (RetCode)
	{
		case	SQL_SUCCESS:		return("SQL_SUCCESS");
		case	SQL_ERROR:			return("SQL_ERROR");
		case	SQL_NO_DATA_FOUND:	return("SQL_NO_DATA_FOUND");
		case	SQL_NEED_DATA:		return("SQL_NEED_DATA");
		case	SQL_INVALID_HANDLE:	return("SQL_INVALID_HANDLE");
		case	SQL_SUCCESS_WITH_INFO:	return("SQL_SUCCESS_WITH_INFO");
		case	SQL_STILL_EXECUTING:	return("SQL_STILL_EXECUTING");
		default:
				return("UNKNOWN SQL RETURN CODE!");
	}
}

//
// GetNextHandle:  get a free trace handle
//


LPTRACESTR	szHandleMap[MAX_HANDLES];

RETCODE	SetNextHandle(LPTRACESTR	lptData)
{
	int	i = 0;

	EnterCriticalSection(&g_csWrite);

	while (i < MAX_HANDLES)
	{
		if (szHandleMap[i] == NULL)
		{
			szHandleMap[i] = lptData;
			LeaveCriticalSection(&g_csWrite);
			return i + 1;
		}
		i++;
	}

	LeaveCriticalSection(&g_csWrite);

	return	0;
}


//
// HandleArgument:	Display an argument
//
// Parameters:
//		TraceStr:	trace structure
//		iArg		Argument to handle
//		szBuffer	Return buffer
// 		cbBuffer	Max buffer size
//		fEntry:		entry to routine (otherwise exit)
//

VOID	HandleArgument(
	LPTRACESTR		TraceStr,
	int				i,
	BOOL			fEntry,
	LPSTR			szBuffer,
	DWORD			cbBuffer,
	enum ArgTypes	atArg)
{
	BOOL		fCCH = FALSE;	// Is unicode CCH argument

	switch(TraceStr->dwCallFunc)
	{
		case	SQL_API_SQLPREPARE:
		case	SQL_API_SQLGETDESCREC:
		case	SQL_API_SQLEXECDIRECT:
		case	SQL_API_SQLDESCRIBECOL:
		case	SQL_API_SQLDRIVERCONNECT:
		case	SQL_API_SQLCONNECT:
		case	SQL_API_SQLSETDESCREC:
		case	SQL_API_SQLGETDIAGREC:
			fCCH = TRUE;
	}
	switch(atArg)
	{
			case	TYP_HENV:
			case	TYP_HDBC:
			case	TYP_HSTMT:
			case	TYP_HWND:
			case	TYP_SQLHANDLE:
			case	TYP_SQLHDESC:
			case	TYP_SQLHDBC:
			case	TYP_SQLHENV:
			case	TYP_SQLHLOC:
			case	TYP_SQLHSTMT:
				_snprintf(szBuffer,cbBuffer," 0x%08x\r\n",TraceStr->lpvArg[i]);
				return;

			case	TYP_HENVPTR:
			case	TYP_HSTMTPTR:
			case	TYP_SQLHANDLEPTR:
			case	TYP_HDBCPTR:
			{
				CHAR	szTemp[100];

				if ((fEntry) || !(TraceStr->lpvArg[i]))
				{
					_snprintf(szBuffer,cbBuffer," 0x%08x\r\n",TraceStr->lpvArg[i]);
					return;
				}

				if (!(fEntry) && TraceStr->lpvArg[i])
				{
					if (((char *)TraceStr->lpvArg[i] < (char *) 0x1000) ||
						IsBadWritePtr(TraceStr->lpvArg[i],sizeof(UDWORD)))
						sprintf(szTemp,"BADMEM");
					else
						_snprintf(szTemp,cbBuffer," 0x%08x",*(DWORD *)(TraceStr->lpvArg[i]));
				}
				_snprintf(szBuffer,cbBuffer," 0x%08x (%s)\r\n",TraceStr->lpvArg[i],szTemp);
				return;

			}

			case	TYP_PTR:
			case	TYP_PTRPTR:
			case	TYP_SQLPOINTER:
				HandlePtr(szBuffer,cbBuffer,TraceStr,i,fEntry);
				return;

			case	TYP_UNKNOWN:	
				_snprintf(szBuffer,cbBuffer," <unknown type>\r\n");
				break;

			case	TYP_SQLUSMALLINT:
			case	TYP_UWORD:
			{
				_snprintf(szBuffer,cbBuffer,"   %8hu ",(UWORD)(TraceStr->lpvArg[i]));	
				ExtraInfo(szBuffer + strlen(szBuffer),
								  cbBuffer - strlen(szBuffer),
								  TraceStr,
								  i);
				return;
			}

			case	TYP_BOOL:
			case	TYP_SQLSMALLINT: 
			case	TYP_SQLINTEGER:
			case	TYP_SWORD:
			{
				_snprintf(szBuffer,cbBuffer,"   %8hd ",(SWORD)(TraceStr->lpvArg[i]));	
				ExtraInfo(szBuffer + strlen(szBuffer),
								  cbBuffer - strlen(szBuffer),
								  TraceStr,
								  i);
				return;
			}

			case	TYP_UDWORD:
			{
				_snprintf(szBuffer,cbBuffer," %8lu\r\n",(UDWORD)(TraceStr->lpvArg[i]));	
				return;
			}

			case	TYP_SDWORD:
			{
				_snprintf(szBuffer,cbBuffer," %8ld\r\n",(SDWORD)(TraceStr->lpvArg[i]));	
				return;
			}

			case	TYP_SQLINTEGERPTR:
			case	TYP_SDWORDPTR:
			{
				if ((fEntry) || (!(TraceStr->lpvArg[i])))
				{
					_snprintf(szBuffer,cbBuffer," 0x%08x\r\n",TraceStr->lpvArg[i]);
					return;
				}

				if	(IsBadWritePtr(TraceStr->lpvArg[i],sizeof(SDWORD)))
					_snprintf(szBuffer,cbBuffer," 0x%08x (BADMEM)\r\n",TraceStr->lpvArg[i]);
				else
					_snprintf(szBuffer,cbBuffer," 0x%08x (%ld)\r\n",TraceStr->lpvArg[i], *(SDWORD *)(TraceStr->lpvArg[i]));
				return;
			
			}

			case	TYP_SQLSMALLINTPTR:
			case	TYP_SWORDPTR:
			{
				if ((fEntry) || (!(TraceStr->lpvArg[i])))
				{
					_snprintf(szBuffer,cbBuffer," 0x%08x\r\n",TraceStr->lpvArg[i]);
					return;
				}

				if (IsBadWritePtr(TraceStr->lpvArg[i],sizeof(SWORD)))
					_snprintf(szBuffer,cbBuffer," 0x%08x (BADMEM)\r\n",TraceStr->lpvArg[i]);
				else
					_snprintf(szBuffer,cbBuffer," 0x%08x (%d)\r\n",TraceStr->lpvArg[i], *(SWORD *)(TraceStr->lpvArg[i]));
				return;
			}

			case	TYP_UDWORDPTR:
			{
				if ((fEntry) || (!(TraceStr->lpvArg[i])))
				{
					_snprintf(szBuffer,cbBuffer," 0x%08x\r\n",TraceStr->lpvArg[i]);
					return;
				}

				if	(IsBadWritePtr(TraceStr->lpvArg[i],sizeof(UDWORD)))
					_snprintf(szBuffer,cbBuffer," 0x%08x (BADMEM)\r\n",TraceStr->lpvArg[i]);
				else
					_snprintf(szBuffer,cbBuffer," 0x%08x (%lu)\r\n",TraceStr->lpvArg[i], *(SDWORD *)(TraceStr->lpvArg[i]));
				return;
			
			}

			case	TYP_UWORDPTR:
			{
				if ((fEntry) || !(TraceStr->lpvArg[i]))
				{
					_snprintf(szBuffer,cbBuffer," 0x%08x\r\n",TraceStr->lpvArg[i]);
					return;
				}

				if	(IsBadWritePtr(TraceStr->lpvArg[i],sizeof(UWORD)))
					_snprintf(szBuffer,cbBuffer," 0x%08x (BADMEM)\r\n",TraceStr->lpvArg[i]);
				else
					_snprintf(szBuffer,cbBuffer," 0x%08x (%u)\r\n",TraceStr->lpvArg[i], *(SWORD *)(TraceStr->lpvArg[i]));
				return;
			}

			case	TYP_UCHARPTR:
			case	TYP_SQLCHARPTR:
				HandleCharData(szBuffer,cbBuffer,TraceStr,i,fEntry,FALSE,fCCH);
				break;
			case	TYP_WCHARPTR:
			case	TYP_SQLWCHARPTR:
				HandleCharData(szBuffer,cbBuffer,TraceStr,i,fEntry,TRUE,fCCH);
				
				break;
	}

	return;
}


/*
** HandleCharData:		Display a unicode character string
**
** Parameters:
**		szBuffer:	output buffer
**		cbBuffer:	length of output buffer
**		TraceStr:	general trace structure
**		iItem:		item number
**		fEntry:		TRUE if function entry
**		fUnicode:	TRUE if unicode
**		fCCH:		TRUE if unicode/cch
*/
VOID	HandleCharData(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	LPTRACESTR	TraceStr,
	DWORD		i,
	BOOL		fEntry,
	BOOL		fUnicode,
	BOOL		fCCH)
{
	
	BOOL	IsOutput = FALSE, IsStringFunc = FALSE;
	SDWORD	sdwLen = SQL_NTS;
	SDWORD	sdwMaxLen = SQL_NTS;
	SDWORD	iLen;

	
	_snprintf(szBuffer,cbBuffer," 0x%08x ",TraceStr->lpvArg[i]);
	iLen = strlen(szBuffer);
	szBuffer += iLen;
	cbBuffer -= iLen;

	// Determine length

	if (i + 1 < TraceStr->nArgs) 
	{
		switch(TraceStr->atArg[i + 1])
		{
			case	TYP_SWORD:
				sdwLen = (SDWORD) ((SWORD)(TraceStr->lpvArg[i + 1]));
				sdwMaxLen = sdwLen;
				IsStringFunc = TRUE;
				break;
					
			case	TYP_SDWORD:
				sdwLen = (SDWORD)(TraceStr->lpvArg[i + 1]);
				sdwMaxLen = sdwLen;
				IsStringFunc = TRUE;
				break;
		}
	
	
		// Determine if output parameter
		// If so, current "length" is maximum length

		if ((i + 2 < TraceStr->nArgs) && IsStringFunc)
		{
			switch(TraceStr->atArg[i + 2])
			{
				case	TYP_SWORDPTR:
				{
					sdwMaxLen = sdwLen;
					sdwLen = -9999;
					IsOutput = TRUE;
	
					if (!(TraceStr->lpvArg[i + 2]))
						break;

					if (!(IsBadWritePtr(TraceStr->lpvArg[i + 2], sizeof(SWORD))))
						sdwLen = (SDWORD) *((SWORD *)(TraceStr->lpvArg[i + 2]));
					break;
				}

				case	TYP_SQLINTEGERPTR:
				case	TYP_SDWORDPTR:
				{
					sdwMaxLen = sdwLen;
					sdwLen = -9999;

					IsOutput = TRUE;

					if (!(TraceStr->lpvArg[i + 2]))
						break;
					if (!(IsBadWritePtr(TraceStr->lpvArg[i + 2], sizeof(SDWORD))))
						sdwLen = (SDWORD) *((SDWORD *)TraceStr->lpvArg[i + 2]);
					break;
				}
			}
		}
		
	}


	if (!(IsStringFunc))
	{
		_snprintf(szBuffer,cbBuffer,"(NYI) \r\n ");
		return;
	}

	_snprintf(szBuffer,cbBuffer," 0x%08x ",TraceStr->lpvArg[i]);

	// Display input values
	if ((!(IsOutput) || !(fEntry)) && ((sdwLen > 0) || (sdwLen == SQL_NTS)) && ((sdwMaxLen > 0) || (sdwMaxLen == SQL_NTS)))
	{
		_snprintf(szBuffer,cbBuffer,"[%8ld] ",min(sdwMaxLen,sdwLen));

		DisplayStringPtr(szBuffer + strlen(szBuffer),
							 cbBuffer - strlen(szBuffer),
							 TraceStr->lpvArg[i],
							 sdwLen,
							 sdwMaxLen,
							 fUnicode,
							 fCCH);
	} else
	{
		_snprintf(szBuffer,cbBuffer,"\r\n");

	}

	return;
}

//
// DisplayStringPtr: Display unicode string (in ansi)
//
// Parameters:
//		szBuffer:	output buffer
//		cbBuffer:	length
//		szData:		data string
//		sdwLen:		length
//		sdwMaxLen:	max length
//		fUnicode:	is string unicode?
//		fCCH:		is this a unicode CCH?

VOID DisplayStringPtr(
	LPSTR	szBuffer,
	DWORD	cbBuffer,
	LPSTR	szData,
	SDWORD	sdwLen,
	SDWORD	sdwMaxLen,
	BOOL	fUnicode,
	BOOL	fCCH)
{
	LPSTR	szAnsiData = NULL;

	setlocale(LC_ALL,".ACP");

	if (!(szData))
	{
		_snprintf(szBuffer,cbBuffer,"<empty string>\r\n");
		return;

	}
	if (!(sdwLen))
	{
		_snprintf(szBuffer,cbBuffer,"<zero length>\r\n");
		return;
	}


	

	if (sdwLen == SQL_NTS)
	{
		sdwLen = 0;
		// Carefully figure out the length
		if (!(fUnicode))
		{
			while (!(IsBadReadPtr(szData + sdwLen,1)) && *(szData + sdwLen)) 
			{
				sdwLen++;
			}
			if (IsBadReadPtr(szData + sdwLen,1))
			{
				_snprintf(szBuffer,cbBuffer,"<Bad null-terminated string!>\r\n");
				return;
			}
			sdwLen++;		// Include zero byte
		}
		else
		{
			// sdwLen needs to be translated into a wide character offset since
			// *szData is a CHAR -- MDW.  This was a GPF risk.
			while (!(IsBadReadPtr(szData + sdwLen,sizeof(WCHAR)))
					 && *((WCHAR *)(szData + sdwLen))) 
			{
				sdwLen += sizeof(WCHAR);
			}
			if (IsBadReadPtr(szData + sdwLen,sizeof(WCHAR)))
			{
				_snprintf(szBuffer,cbBuffer,"<Bad null-terminated string!>\r\n");
				return;
			}
			sdwLen += sizeof(WCHAR);		// Include zero byte
			sdwLen /= sizeof(WCHAR);		// Now Unicode is CCH rather than CB...
		}

		sdwMaxLen = sdwLen;

	}

	if ((sdwLen < 0) || (sdwMaxLen < 0))
	{
		_snprintf(szBuffer,cbBuffer,"<Invalid string length!>\r\n");
		return;
	}


	if (IsBadReadPtr(szData,min(sdwMaxLen,sdwLen)))
	{
		_snprintf(szBuffer,
					cbBuffer,
					"<Buffer at 0x%08x isn't %d bytes long>\r\n",
					szData,
					min(sdwLen,sdwMaxLen));
		return;
	}

	// Display unicode in ANSI format
	if (fUnicode)
	{
		SDWORD	sdwDiv = fCCH ? 1 : sizeof(WCHAR);

		szAnsiData = malloc(min(sdwLen, sdwMaxLen) + 1);
		if (!(szAnsiData))
		{
			_snprintf(szBuffer,cbBuffer,"Out of memory! \r\n");
			return;
		}

		WideCharToMultiByte(CP_ACP,		// XXX Consider: make any cp?
										0,								
										(LPWSTR)(szData),
										(min(sdwMaxLen,sdwLen) / sdwDiv),
										szAnsiData,
										min(sdwMaxLen,sdwLen),
										NULL,
										FALSE);

		DisplayString(szBuffer, cbBuffer, szAnsiData,
			min(sdwMaxLen/sdwDiv, sdwLen/sdwDiv));
	} else
	{
		DisplayString(szBuffer,cbBuffer,szData,min(sdwMaxLen,sdwLen));
	}

	if (szAnsiData)
		free(szAnsiData);

	return;
}

//
// DisplayString:  display a text string
//
// Parameters:
//
//	szBuffer:	display buffer
//	cbBuffer:	size of buffer
//	szData:		ansi data to display
//	cbData:		length of data

VOID DisplayString(
	LPSTR	szBuffer,
	DWORD	cbBuffer,
	LPSTR	szData,
	DWORD	cbData)
{
	BOOL		fLastWasLeadByte = FALSE;

	if (IsBadReadPtr(szData,cbData))
	{
		_snprintf(szBuffer,cbBuffer,"...<BAD MEMORY after 0x%08x [len=%ld]!>\r\n",szData, cbData);
		return;
	}




	if (cbBuffer)
	{
		*szBuffer++ = '\"';
		cbBuffer--;
	}
		

	while ((cbBuffer > 5) && (cbData > 0))
	{
		if (isprint(*szData) || fLastWasLeadByte || isleadbyte(*szData))
		{
			*szBuffer++ = *szData++;
			cbData--;
			cbBuffer--;
			if (fLastWasLeadByte)
			{
				fLastWasLeadByte = FALSE;
			} else if (isleadbyte(*szData))
			{
				fLastWasLeadByte = TRUE;
			}
		}  else
		{
			sprintf(szBuffer, "\\%2x",*szData++);
			cbData--;
			cbBuffer -= 3;
			szBuffer += 3;
		}
	}

	if (cbBuffer)
	{
		if (cbData)
			_snprintf(szBuffer,cbBuffer,"...\"\r\n");
		else
			_snprintf(szBuffer,cbBuffer,"\"\r\n");

	}

	return;
}

//
// ExtraInfo:	Decode argument values for certain functions
//
// Parameters:
//	szBuffer		output buffer
//	cbBuffer		length of output buffer
//	TraceStr		trace structure
//	iArg			argument we are on

void ExtraInfo(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	LPTRACESTR	TraceStr,
	DWORD		iArg)
{

	switch(TraceStr->dwCallFunc)
	{
		case	SQL_API_SQLGETDATA:
		case	SQL_API_SQLBINDCOL:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfCTypes,
							 NumItems(lpdfCTypes));
				return;
			}
			break;

		case	SQL_API_SQLBINDPARAM:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfCTypes,
							 NumItems(lpdfCTypes));
				return;
			}

			if (iArg == 3)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfSqlTypes,
							 NumItems(lpdfSqlTypes));
				return;
			}

		case	SQL_API_SQLBINDPARAMETER:
			switch (iArg)
			{
				case	2:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (SWORD) TraceStr->lpvArg[iArg],
								 lpdfParamType,
								 NumItems(lpdfParamType));
					return;

				case	3:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (SWORD) TraceStr->lpvArg[iArg],
								 lpdfCTypes,
								 NumItems(lpdfCTypes));
					return;
				case	4:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (SWORD) TraceStr->lpvArg[iArg],
								 lpdfSqlTypes,
								 NumItems(lpdfSqlTypes));
					return;
			}
			break;

		case	SQL_API_SQLCOLATTRIBUTE:
			if (iArg == 2)
			{
				// SQLColAttributes and SQLColAttribute have the same
				// function number
				BOOL fOld = !_tcsicmp(TraceStr->szFuncName, "SQLColAttributes");
 
				GetDefaultId(szBuffer,
					cbBuffer,
					(SWORD) TraceStr->lpvArg[iArg],
					(fOld) ? lpdfDescType : lpdfDescType30,
					(fOld) ? NumItems(lpdfDescType) : NumItems(lpdfDescType30));
				return;
					
			}
			break;


		case	SQL_API_SQLGETENVATTR:
		case	SQL_API_SQLSETENVATTR:

			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
									cbBuffer,
									(UWORD) TraceStr->lpvArg[iArg],
									lpdfSetEnvAttr,
									NumItems(lpdfSetEnvAttr));
				return;
			}

			break;

		case	SQL_API_SQLDATASOURCES:

			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
									cbBuffer,
									(UWORD) TraceStr->lpvArg[iArg],
									lpdfDataSrcs,
									NumItems(lpdfDataSrcs));
				return;
			}

			break;

		case	SQL_API_SQLDRIVERCONNECT:

			if (iArg == 7)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdfDrvrConn,
							NumItems(lpdfDrvrConn));
				return;
			}

			break;

		case	SQL_API_SQLDRIVERS:

			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdfDataSrcs,
							NumItems(lpdfDataSrcs));
				return;
			}

			break;

#ifdef SQL_API_SQLGETLENGTH
		case	SQL_API_SQLGETLENGTH:
		case	SQL_API_SQLGETPOSITION:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdLocfLocatorType,
							NumItems(lpdLocfLocatorType));
				return;
			}
			break;

#endif

		case	SQL_API_SQLFREEHANDLE:
		case	SQL_API_SQLALLOCHANDLE:
		case	SQL_API_SQLENDTRAN:
			if (iArg == 0)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdSQLAllocHandle,
							NumItems(lpdSQLAllocHandle));
				return;
			}
			break;

		case	SQL_API_SQLEXTENDEDFETCH:
		case	SQL_API_SQLFETCHSCROLL:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdfFetchType,
							NumItems(lpdfFetchType));
				return;
			}
			break;

		case	SQL_API_SQLFREESTMT:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdFreeStmtOpt,
							NumItems(lpdFreeStmtOpt));
				return;
			}
			break;
		
		case	SQL_API_SQLGETCONNECTATTR:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							cbBuffer,
							(UWORD) TraceStr->lpvArg[iArg],
							lpdfGetConAtr,
							NumItems(lpdfGetConAtr));
				return;
			}
			break;

		case	SQL_API_SQLGETFUNCTIONS:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdGetFunct,
							 NumItems(lpdGetFunct));
				return;
			}
			break;

		case	SQL_API_SQLGETINFO:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							  cbBuffer,
							  (UWORD) TraceStr->lpvArg[iArg],
							  lpdfInfoType,
							  NumItems(lpdfInfoType));
				return;

			}
			break;


		case	SQL_API_SQLGETSTMTATTR:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdfGetStmtOpt,
							 NumItems(lpdfGetStmtOpt));
				return;
			}
			break;

#ifdef SQL_API_SQLLOCATEDUPDATE

		case	SQL_API_SQLLOCATEDUPDATE:
		case	SQL_API_SQLGETSUBSTRING:
			if ((iArg == 1) || (iArg == 5))
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 (iArg == 1)?  lpdLocfLocatorType : 
										   lpdLocfSrcTargType,
							 (iArg == 1) ? NumItems(lpdLocfLocatorType) :
										   NumItems(lpdLocfSrcTargType));
				return;
			}
			break;

#endif
		case	SQL_API_SQLGETTYPEINFO:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfSqlTypes,
							 NumItems(lpdfSqlTypes));
				return;
			}
			break;

#ifdef SQL_API_SQLLOCATOR

		case	SQL_API_SQLLOCATOR:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdLocfOperation,
							 NumItems(lpdLocfOperation));
				return;
			}
			break;
#endif


		case	SQL_API_SQLSETCONNECTATTR:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfSetConAtr,
							 NumItems(lpdfSetConAtr));
				return;
			}
			break;

		case	SQL_API_SQLSETCONNECTOPTION:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfSetConOpt,
							 NumItems(lpdfSetConOpt));

				return;
			}
			break;


		case	SQL_API_SQLSETDESCFIELD:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdSetDescFields,
							 NumItems(lpdSetDescFields));
				return;
			}
			break;


		case	SQL_API_SQLSETDESCREC:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SWORD) TraceStr->lpvArg[iArg],
							 lpdfCTypes,
							 NumItems(lpdfCTypes));
				return;
			}

			break;

	
		case	SQL_API_SQLSETPOS:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdfSetPos,
							 NumItems(lpdfSetPos));
				return;
			} 
			if (iArg == 3)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdfLock,
							 NumItems(lpdfLock));
				return;
			}
			break;

		case	SQL_API_SQLSETSCROLLOPTIONS:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdConcurrency,
							 NumItems(lpdConcurrency));
				return;
			}
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SDWORD) TraceStr->lpvArg[iArg],
							 lpdCursorType,
							 NumItems(lpdCursorType));
				return;
			}
			break;


		case	SQL_API_SQLSETSTMTATTR:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SDWORD) TraceStr->lpvArg[iArg],
							 lpdfSetStmtAtr,
							 NumItems(lpdfSetStmtAtr));
				return;
			}
			break;

		case	SQL_API_SQLSETSTMTOPTION:
			if (iArg == 1)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (SDWORD) TraceStr->lpvArg[iArg],
							 lpdfSetStmtOpt,
							 NumItems(lpdfSetStmtOpt));
				return;
			}
			break;

		case	SQL_API_SQLSPECIALCOLUMNS:
			switch (iArg)
			{
				case	1:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (UWORD) TraceStr->lpvArg[iArg],
								 lpdfColType,
								 NumItems(lpdfColType));
					return;
				case	8:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (UWORD) TraceStr->lpvArg[iArg],
								 lpdfScope,
								 NumItems(lpdfScope));
					return;
				case	9:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (UWORD) TraceStr->lpvArg[iArg],
								 lpdfNullable,
								 NumItems(lpdfNullable));
					return;
			}
			break;

		case	SQL_API_SQLSTATISTICS:
			switch (iArg)
			{
				case	7:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (UWORD) TraceStr->lpvArg[iArg],
								 lpdfUnique,
								 NumItems(lpdfUnique));
					return;
				case	8:
					GetDefaultId(szBuffer,
								 cbBuffer,
								 (UWORD) TraceStr->lpvArg[iArg],
								 lpdfAccuracy,
								 NumItems(lpdfAccuracy));
					return;
			}
			break;

		case	SQL_API_SQLTRANSACT:
			if (iArg == 2)
			{
				GetDefaultId(szBuffer,
							 cbBuffer,
							 (UWORD) TraceStr->lpvArg[iArg],
							 lpdTransactType,
							 NumItems(lpdTransactType));
				return;
			}
			break;


	}
	_snprintf(szBuffer,cbBuffer,"\r\n");

	return;

}

//
// GetDefaultId:	Get the default id for a value
//
// Parameters:
//
//	szBuffer:	buffer
//	cbBuffer:	length of buffer
//	dftList:	list to search
//	cbDft:		size of list

void GetDefaultId(
	LPSTR			szBuffer,
	DWORD			cbBuffer,
	SDWORD			sdwValue,
	const struct tagDFTARRAY  *dftList,
	DWORD			cbDft)

{
	DWORD		iCount;

	for (iCount = 0; iCount < cbDft; iCount++)
	{
		if (dftList[iCount].fOpt == sdwValue)
		{
			_snprintf(szBuffer,cbBuffer,"<%s>\r\n",dftList[iCount].szOpt);
			return;
		}
	}

	_snprintf(szBuffer,cbBuffer,"<unknown>\r\n");
	return;
}

//
// HandlePtr: handle PTR data type 
//
// Parameters:
//	szBuffer		output buffer
//	cbBuffer		length of output buffer
//	TraceStr		trace structure
//	iArg			argument we are on

void HandlePtr(
	LPSTR		szBuffer,
	DWORD		cbBuffer,
	LPTRACESTR	TraceStr,
	DWORD		iArg,
	BOOL		fEntry)
{

	switch(TraceStr->dwCallFunc)
	{
		case	SQL_API_SQLGETENVATTR:
		case	SQL_API_SQLSETENVATTR:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
									cbBuffer,
									(DWORD) TraceStr->lpvArg[1],
									TraceStr->lpvArg[iArg],
									lpdfSetEnvAttr,
									NumItems(lpdfSetEnvAttr),
									fEntry,
									TraceStr,
									iArg);
				return;
			}

			break;

		case	SQL_API_SQLCOLATTRIBUTE:

			if (iArg == 6)
			{
				GetPtrValue(szBuffer,
								cbBuffer,
								(DWORD) TraceStr->lpvArg[2],
								TraceStr->lpvArg[iArg],
								lpdfDescType,
								NumItems(lpdfDescType),
								fEntry,
								TraceStr,
								iArg);
				return;
			}

			break;

		case	SQL_API_SQLGETCONNECTATTR:

			if (iArg == 4)
			{
				GetPtrValue(szBuffer,
								cbBuffer,
								(UWORD) TraceStr->lpvArg[1],
								TraceStr->lpvArg[iArg],
								lpdfGetConAtr,
								NumItems(lpdfGetConAtr),
								fEntry,
								TraceStr,
								iArg);
				return;
			}
			break;

		case	SQL_API_SQLGETDATA:
			if (iArg == 3)
			{
				HandleArgument(TraceStr,
								iArg,
								fEntry,
								szBuffer,
								cbBuffer,
								CTypeToAType((SWORD) TraceStr->lpvArg[2]));
				return;
			}
			break;

		case	SQL_API_SQLGETINFO:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
								cbBuffer,
								(UWORD) TraceStr->lpvArg[1],
								TraceStr->lpvArg[iArg],
								lpdfInfoType,
								NumItems(lpdfInfoType),
								fEntry,
								TraceStr,
								iArg);
				return;
			}
			break;

		case	SQL_API_SQLGETSTMTATTR:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
								cbBuffer,
								(UWORD) TraceStr->lpvArg[1],
								TraceStr->lpvArg[iArg],
								lpdfGetStmtOpt,
								NumItems(lpdfGetStmtOpt),
								fEntry,
								TraceStr,
								iArg);
				return;
			}
			break;

		case	SQL_API_SQLSETCONNECTATTR:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
							cbBuffer,
							(SWORD) TraceStr->lpvArg[1],
							TraceStr->lpvArg[iArg],
							lpdfSetConAtr,
							NumItems(lpdfSetConAtr),
							fEntry,
							TraceStr,
							iArg);
				return;
			}
			break;

		case	SQL_API_SQLSETCONNECTOPTION:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
							cbBuffer,
							(SWORD) TraceStr->lpvArg[1],
							TraceStr->lpvArg[iArg],
							lpdfSetConOpt,
							NumItems(lpdfSetConOpt),
							fEntry,
							TraceStr,
							iArg);
				return;
			}
			break;

		case	SQL_API_SQLSETDESCFIELD:

			if (iArg == 3)
			{
				GetPtrValue(szBuffer,
							cbBuffer,
							(SWORD) TraceStr->lpvArg[2],
							TraceStr->lpvArg[iArg],
							lpdSetDescFields,
							NumItems(lpdSetDescFields),
							fEntry,
							TraceStr,
							iArg);
				return;
			}
			break;
		
		case	SQL_API_SQLSETSTMTATTR:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
							cbBuffer,
							(SWORD) TraceStr->lpvArg[1],
							TraceStr->lpvArg[iArg],
							lpdfSetStmtAtr,
							NumItems(lpdfSetStmtAtr),
							fEntry,
							TraceStr,
							iArg);
				return;
			}
			break;

		case	SQL_API_SQLSETSTMTOPTION:

			if (iArg == 2)
			{
				GetPtrValue(szBuffer,
							cbBuffer,
							(SWORD) TraceStr->lpvArg[1],
							TraceStr->lpvArg[iArg],
							lpdfSetStmtOpt,
							NumItems(lpdfSetStmtOpt),
							fEntry,
							TraceStr,
							iArg);
				return;
			}
			break;
		

	}

	_snprintf(szBuffer,cbBuffer,"0x%08x\r\n", TraceStr->lpvArg[iArg]);
	return;

}
//
// GetPtrValue:	Get the value of a pointer that varies according
//				to some argument (like SQLGetEnvAttr arg 3)
//
// Parameters:
//
//	szBuffer:		buffer
//	cbBuffer:		length of buffer
//  sdwAtribute:	attribute value 
//  lpvData:		address of data
//	dftList:		list to search
//	cbDft:			size of list
//	fEntry:			is this the entry point or exit?

void GetPtrValue(
	LPSTR			szBuffer,
	DWORD			cbBuffer,
	SDWORD			sdwAttribute,
	LPVOID			lpvData,
	const struct tagDFTARRAY  *dftList,
	DWORD			cbDft,
	BOOL			fEntry,
	LPTRACESTR		TraceStr,
	DWORD			iArg)

{
	DWORD			iCount;
	enum ArgTypes	AtThis;

	for (iCount = 0; iCount < cbDft; iCount++)
	{
		if (dftList[iCount].fOpt == sdwAttribute)
		{
			AtThis = GatorToAType(dftList[iCount].uValInfo, (TraceStr->dwFlags & TRACESTR_FLAG_UNICODE));
			switch (AtThis)
			{
				case TYP_UDWORD:
					AtThis = TYP_UDWORDPTR;
					break;
				case TYP_UWORD:
					AtThis = TYP_UWORDPTR;
					break;
			}
			HandleArgument(TraceStr,iArg,fEntry,szBuffer,cbBuffer,AtThis);
			return;
		}
	}

	_snprintf(szBuffer,cbBuffer," [Unknown attribute %ld]\r\n",sdwAttribute);
	return;
}

//
// CTypeToAType:  convert a SQL_C_xxx type to an enum
//
// Parameters:
//	swCType
// returns: enum

enum ArgTypes CTypeToAType(
	SWORD	swCType)
{
	switch (swCType)
	{
		default:
			return TYP_UNKNOWN;	

		case SQL_C_USHORT:
			return TYP_UWORD;

		case SQL_C_SLONG:
			return TYP_SDWORD;

		case SQL_C_ULONG:
			return TYP_UDWORD;

		case SQL_C_BIT:
			return TYP_BOOL;

		case SQL_C_TINYINT:
		case SQL_C_SSHORT:
			return TYP_SQLSMALLINT;


		case SQL_C_CHAR:
			return TYP_SQLCHARPTR;


		case SQL_C_WCHAR:
			return TYP_WCHARPTR;
	}
}



//
// GatorToAtype: convert gators odd flags into a type enum
//
// Parameters:
//	swCType
// returns: enum

enum ArgTypes GatorToAType(
	SDWORD	sdwFlag,
	BOOL	fUnicode)
{

	if (sdwFlag & PRM_STR)
		return (fUnicode)? TYP_SQLWCHARPTR : TYP_SQLCHARPTR;


	if (sdwFlag & PRM_16BIT)
		return TYP_UWORD;
	
	if ((sdwFlag & PRM_32MSK) || (sdwFlag & PRM_32HDL))
		return TYP_HENV;		// Forces hex output

	if (sdwFlag & PRM_32BIT)
		return TYP_UDWORD;

	return TYP_HENV;
}

// Returns the trace API version

DWORD	SQL_API TraceVersion()
{
	return	TRACE_VERSION;
}



void GrabErrors( LPTRACESTR	TraceStr)
{
	LPVOID		lpvHandle = TraceStr->lpvArg[0];
	SQLSMALLINT	cRec = 0;
	RETCODE		RetCode;
	char		szMessage[2000], szState[100];
	char		szBuffer[4000];
	SQLINTEGER	NativeError;
	SQLSMALLINT	hType;

	switch (TraceStr->dwCallFunc)
	{
		default:
				return;

		case	SQL_API_SQLALLOCCONNECT         :
		case	SQL_API_SQLFREEENV         :
		case	SQL_API_SQLGETENVATTR   :
		case	SQL_API_SQLSETENVATTR     :
			hType = SQL_HANDLE_ENV;
			break;


		case	SQL_API_SQLALLOCSTMT            :
		case	SQL_API_SQLCONNECT              :
		case	SQL_API_SQLDATASOURCES     :
		case	SQL_API_SQLDISCONNECT           :
		case	SQL_API_SQLFREECONNECT:
		case	SQL_API_SQLGETCONNECTATTR   :
		case	SQL_API_SQLGETCONNECTOPTION  :
		case	SQL_API_SQLSETCONNECTATTR  :
		case	SQL_API_SQLSETCONNECTOPTION  :
		case	SQL_API_SQLDRIVERCONNECT	:
		case	SQL_API_SQLDRIVERS          :
		case	SQL_API_SQLNATIVESQL:
		case	SQL_API_SQLGETINFO      :
		case	SQL_API_SQLBROWSECONNECT       :
			hType = SQL_HANDLE_DBC;
			break;

		case	SQL_API_SQLTRANSACT            :
			if (TraceStr->lpvArg[0])
			{
				hType = SQL_HANDLE_ENV;
				lpvHandle = TraceStr->lpvArg[0];
			} else 
			{
				hType = SQL_HANDLE_DBC;
				lpvHandle = TraceStr->lpvArg[1];
			}
	
			break;

		case	SQL_API_SQLGETDESCFIELD   :
		case	SQL_API_SQLGETDESCREC      :
		case	SQL_API_SQLCOPYDESC        :
		case	SQL_API_SQLSETDESCFIELD     :
		case	SQL_API_SQLSETDESCREC      :
			hType = SQL_HANDLE_DESC;
			break;

		case	SQL_API_SQLBINDCOL              :
		case	SQL_API_SQLBINDPARAM         :
		case	SQL_API_SQLCANCEL               :
		case	SQL_API_SQLCLOSECURSOR      :
		case	SQL_API_SQLCOLATTRIBUTE         :
		case	SQL_API_SQLCOLUMNS         :
		case	SQL_API_SQLDESCRIBECOL          :
		case	SQL_API_SQLENDTRAN        :
		case	SQL_API_SQLEXECDIRECT    :
		case	SQL_API_SQLEXECUTE       :
		case	SQL_API_SQLFETCH        :
		case	SQL_API_SQLFETCHSCROLL :
		case	SQL_API_SQLFREESTMT        :
		case	SQL_API_SQLGETCURSORNAME    :
		case	SQL_API_SQLGETDATA         :
		case	SQL_API_SQLGETFUNCTIONS  :
		case	SQL_API_SQLGETSTMTATTR :
		case	SQL_API_SQLGETSTMTOPTION     :
		case	SQL_API_SQLGETTYPEINFO      :
		case	SQL_API_SQLNUMRESULTCOLS   :
		case	SQL_API_SQLPARAMDATA      :
		case	SQL_API_SQLPREPARE       :
		case	SQL_API_SQLPUTDATA      :
		case	SQL_API_SQLROWCOUNT    :
		case	SQL_API_SQLSETCURSORNAME    :
		case	SQL_API_SQLSETPARAM      :
		case	SQL_API_SQLSETSTMTATTR     :
		case	SQL_API_SQLSETSTMTOPTION   :
		case	SQL_API_SQLSPECIALCOLUMNS      :
		case	SQL_API_SQLSTATISTICS          :
		case	SQL_API_SQLTABLES              :
		case	SQL_API_SQLBULKOPERATIONS	:
		case	SQL_API_SQLBINDPARAMETER    :
		case	SQL_API_SQLCOLUMNPRIVILEGES :
		case	SQL_API_SQLDESCRIBEPARAM    :
		case	SQL_API_SQLEXTENDEDFETCH    :
		case	SQL_API_SQLFOREIGNKEYS      :
		case	SQL_API_SQLMORERESULTS      :
		case	SQL_API_SQLNUMPARAMS        :
		case	SQL_API_SQLPARAMOPTIONS     :
		case	SQL_API_SQLPRIMARYKEYS      :
		case	SQL_API_SQLPROCEDURECOLUMNS :
		case	SQL_API_SQLPROCEDURES       :
		case	SQL_API_SQLSETPOS           :
		case	SQL_API_SQLSETSCROLLOPTIONS :
		case	SQL_API_SQLTABLEPRIVILEGES  :
			hType = SQL_HANDLE_STMT;
			break;
	}

	do {
		g_fNoTrace = TRUE;
		RetCode = SQLGetDiagRec(hType,
								lpvHandle,
								++cRec,
								szState,
								&NativeError,
								szMessage,
								(SQLSMALLINT) sizeof(szMessage),
								(SQLSMALLINT *) NULL);
	
		g_fNoTrace = FALSE;
		if (RetCode == SQL_SUCCESS)
		{
			sprintf(szBuffer,
					"\r\n\t\tDIAG [%s] %s (%d) \r\n",
					szState,
					szMessage,
					NativeError);
			fwrite(szBuffer, strlen(szBuffer),1,fhTraceFile);
		}

	} while (RetCode == SQL_SUCCESS);

	return;
}
					
		

RETCODE SQL_API TraceVSControl(DWORD dwControl)
{
	g_fTrace = dwControl & TRACE_ON;
	g_fVS = dwControl & TRACE_VS_EVENT_ON;
	return SQL_SUCCESS;
}
												