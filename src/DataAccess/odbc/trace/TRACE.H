//
// TRACE.H 
//
// Definitions for the ODBC trace dll.
//
// Copyright (c) 1995 - 1998 by Microsoft Corporation.
// All rights reserved.

#ifndef __TRACEH
#define	__TRACEH

#define MAX_ARGS	20

// Include here just so you can compile if you don't happen to
// have the ODBC 3.51 headers in your path.
#ifndef TRACE_VS_EVENT_ON
#define TRACE_ON 1
#define TRACE_VS_EVENT_ON 2
#endif

// Argument type enum

enum	 ArgTypes
{

 	TYP_UNKNOWN,	
	TYP_HENV,
	TYP_HDBCPTR,
	TYP_HENVPTR,
	TYP_HDBC,
	TYP_HSTMTPTR,
	TYP_HSTMT,
	TYP_UWORD,
	TYP_SWORD,
	TYP_PTR,
	TYP_SDWORD,
	TYP_SDWORDPTR,
	TYP_SWORDPTR,
	TYP_UCHARPTR,
	TYP_UDWORDPTR,
	TYP_UDWORD,
	TYP_HWND,
	TYP_UWORDPTR,
	TYP_PTRPTR,
	TYP_BOOL,
	TYP_SQLSMALLINT,
	TYP_SQLHANDLE,
	TYP_SQLHANDLEPTR,
	TYP_SQLHSTMT,
	TYP_SQLINTEGER,
	TYP_SQLPOINTER,
	TYP_SQLINTEGERPTR,
	TYP_SQLSMALLINTPTR,
	TYP_SQLHDESC,
	TYP_SQLHDBC,
	TYP_SQLCHARPTR,
	TYP_SQLHENV,
	TYP_SQLHLOC,
	TYP_SQLUSMALLINT,
	TYP_WCHARPTR,
	TYP_SQLWCHARPTR
};


#define TRACESTR_FLAG_UNICODE	0x00000001L
#define TRACESTR_FLAG_VISTA		0x00000002L

typedef struct tagTRACESTR {
	DWORD			dwCallFunc;			// ODBC ID of function
	DWORD			nArgs;				// How many arguments
	LPVOID			lpvArg[MAX_ARGS];	// Arguments
	enum ArgTypes	atArg[MAX_ARGS];	// Argument type 
	LPCSTR			szArg[MAX_ARGS];	// Printable name
	DWORD			dwFlags;			// flags
	LPCSTR			szFuncName;			// Printable function name
} * LPTRACESTR, TRACESTR;

VOID	DoTrace(LPTRACESTR);
RETCODE	SetNextHandle(LPTRACESTR	lptData);
#endif
