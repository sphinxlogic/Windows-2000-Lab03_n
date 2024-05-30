
#include "headers.h"

///// Trace function for SQLAllocConnect /////

RETCODE SQL_API TraceSQLAllocConnect  (HENV arg0,
			 HDBC * arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLALLOCCONNECT;
	lpCallStr->szFuncName="SQLAllocConnect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HDBC *";
	lpCallStr->atArg[1]=TYP_HDBCPTR;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLAllocEnv /////

RETCODE SQL_API TraceSQLAllocEnv  (HENV * arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLALLOCENV;
	lpCallStr->szFuncName="SQLAllocEnv";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV *";
	lpCallStr->atArg[0]=TYP_HENVPTR;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLAllocStmt /////

RETCODE SQL_API TraceSQLAllocStmt  (HDBC arg0,
		 HSTMT * arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLALLOCSTMT;
	lpCallStr->szFuncName="SQLAllocStmt";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HSTMT *";
	lpCallStr->atArg[1]=TYP_HSTMTPTR;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLBindCol /////

RETCODE SQL_API TraceSQLBindCol  (HSTMT arg0,
			UWORD arg1,
			SWORD arg2,
			PTR arg3,
			SDWORD arg4,
			UNALIGNED SDWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLBINDCOL;
	lpCallStr->szFuncName="SQLBindCol";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="PTR";
	lpCallStr->atArg[3]=TYP_PTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SDWORD";
	lpCallStr->atArg[4]=TYP_SDWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SDWORD *";
	lpCallStr->atArg[5]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLCancel /////

RETCODE SQL_API TraceSQLCancel  (HSTMT arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCANCEL;
	lpCallStr->szFuncName="SQLCancel";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColAttributes /////

RETCODE SQL_API TraceSQLColAttributes  (HSTMT arg0,
		 UWORD arg1,
		 UWORD arg2,
		 PTR arg3,
		 SWORD arg4,
		 UNALIGNED SWORD * arg5,
		 UNALIGNED SDWORD * arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLATTRIBUTES;
	lpCallStr->szFuncName="SQLColAttributes";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UWORD";
	lpCallStr->atArg[2]=TYP_UWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="PTR";
	lpCallStr->atArg[3]=TYP_PTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SDWORD *";
	lpCallStr->atArg[6]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLConnect /////

RETCODE SQL_API TraceSQLConnect  (HDBC arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCONNECT;
	lpCallStr->szFuncName="SQLConnect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDescribeCol /////

RETCODE SQL_API TraceSQLDescribeCol  (HSTMT arg0,
		 UWORD arg1,
		 UCHAR * arg2,
		 SWORD arg3,
		 SWORD * arg4,
		 UNALIGNED SWORD * arg5,
		 UNALIGNED UDWORD * arg6,
		 UNALIGNED SWORD * arg7,
		 UNALIGNED SWORD * arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDESCRIBECOL;
	lpCallStr->szFuncName="SQLDescribeCol";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UCHAR *";
	lpCallStr->atArg[2]=TYP_UCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="UDWORD *";
	lpCallStr->atArg[6]=TYP_UDWORDPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD *";
	lpCallStr->atArg[8]=TYP_SWORDPTR;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDisconnect /////

RETCODE SQL_API TraceSQLDisconnect  (HDBC arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDISCONNECT;
	lpCallStr->szFuncName="SQLDisconnect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLError /////

RETCODE SQL_API TraceSQLError  (HENV arg0,
		 HDBC arg1,
		 HSTMT arg2,
		 UCHAR * arg3,
		 UNALIGNED SDWORD * arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UNALIGNED SWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLERROR;
	lpCallStr->szFuncName="SQLError";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HDBC";
	lpCallStr->atArg[1]=TYP_HDBC;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="HSTMT";
	lpCallStr->atArg[2]=TYP_HSTMT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SDWORD *";
	lpCallStr->atArg[4]=TYP_SDWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLExecDirect /////

RETCODE SQL_API TraceSQLExecDirect  (HSTMT arg0,
		 UCHAR * arg1,
		 SDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLEXECDIRECT;
	lpCallStr->szFuncName="SQLExecDirect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLExecute /////

RETCODE SQL_API TraceSQLExecute  (HSTMT arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLEXECUTE;
	lpCallStr->szFuncName="SQLExecute";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLFetch /////

RETCODE SQL_API TraceSQLFetch  (HSTMT arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFETCH;
	lpCallStr->szFuncName="SQLFetch";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLFreeConnect /////

RETCODE SQL_API TraceSQLFreeConnect  (HDBC arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFREECONNECT;
	lpCallStr->szFuncName="SQLFreeConnect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLFreeEnv /////

RETCODE SQL_API TraceSQLFreeEnv  (HENV arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFREEENV;
	lpCallStr->szFuncName="SQLFreeEnv";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLFreeStmt /////

RETCODE SQL_API TraceSQLFreeStmt  (HSTMT arg0,
		 UWORD arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFREESTMT;
	lpCallStr->szFuncName="SQLFreeStmt";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetCursorName /////

RETCODE SQL_API TraceSQLGetCursorName  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UNALIGNED SWORD * arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETCURSORNAME;
	lpCallStr->szFuncName="SQLGetCursorName";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD *";
	lpCallStr->atArg[3]=TYP_SWORDPTR;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLNumResultCols /////

RETCODE SQL_API TraceSQLNumResultCols  (HSTMT arg0,
		 UNALIGNED SWORD * arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLNUMRESULTCOLS;
	lpCallStr->szFuncName="SQLNumResultCols";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SWORD *";
	lpCallStr->atArg[1]=TYP_SWORDPTR;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLPrepare /////

RETCODE SQL_API TraceSQLPrepare  (HSTMT arg0,
		 UCHAR * arg1,
		 SDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPREPARE;
	lpCallStr->szFuncName="SQLPrepare";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLRowCount /////

RETCODE SQL_API TraceSQLRowCount  (HSTMT arg0,
		 UNALIGNED SDWORD * arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLROWCOUNT;
	lpCallStr->szFuncName="SQLRowCount";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SDWORD *";
	lpCallStr->atArg[1]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetCursorName /////

RETCODE SQL_API TraceSQLSetCursorName  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETCURSORNAME;
	lpCallStr->szFuncName="SQLSetCursorName";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetParam /////

RETCODE SQL_API TraceSQLSetParam  (HSTMT arg0,
		 UWORD arg1,
		 SWORD arg2,
		 SWORD arg3,
		 UDWORD arg4,
		 SWORD arg5,
		 PTR arg6,
		 UNALIGNED SDWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETPARAM;
	lpCallStr->szFuncName="SQLSetParam";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="UDWORD";
	lpCallStr->atArg[4]=TYP_UDWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD";
	lpCallStr->atArg[5]=TYP_SWORD;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="PTR";
	lpCallStr->atArg[6]=TYP_PTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SDWORD *";
	lpCallStr->atArg[7]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLTransact /////

RETCODE SQL_API TraceSQLTransact  (HENV arg0,
		 HDBC arg1,
		 UWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLTRANSACT;
	lpCallStr->szFuncName="SQLTransact";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HDBC";
	lpCallStr->atArg[1]=TYP_HDBC;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UWORD";
	lpCallStr->atArg[2]=TYP_UWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColumns /////

RETCODE SQL_API TraceSQLColumns  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLUMNS;
	lpCallStr->szFuncName="SQLColumns";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UCHAR *";
	lpCallStr->atArg[7]=TYP_UCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDriverConnect /////

RETCODE SQL_API TraceSQLDriverConnect  (HDBC arg0,
		 HWND arg1,
		 UCHAR * arg2,
		 SWORD arg3,
		 UCHAR * arg4,
		 SWORD arg5,
		 UNALIGNED SWORD * arg6,
		 UWORD arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDRIVERCONNECT;
	lpCallStr->szFuncName="SQLDriverConnect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HWND";
	lpCallStr->atArg[1]=TYP_HWND;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UCHAR *";
	lpCallStr->atArg[2]=TYP_UCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="UCHAR *";
	lpCallStr->atArg[4]=TYP_UCHARPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD";
	lpCallStr->atArg[5]=TYP_SWORD;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD *";
	lpCallStr->atArg[6]=TYP_SWORDPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UWORD";
	lpCallStr->atArg[7]=TYP_UWORD;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetConnectOption /////

RETCODE SQL_API TraceSQLGetConnectOption  (HDBC arg0,
		 UWORD arg1,
		 PTR arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETCONNECTOPTION;
	lpCallStr->szFuncName="SQLGetConnectOption";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="PTR";
	lpCallStr->atArg[2]=TYP_PTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetData /////

RETCODE SQL_API TraceSQLGetData  (HSTMT arg0,
		 UWORD arg1,
		 SWORD arg2,
		 PTR arg3,
		 SDWORD arg4,
		 UNALIGNED SDWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDATA;
	lpCallStr->szFuncName="SQLGetData";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="PTR";
	lpCallStr->atArg[3]=TYP_PTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SDWORD";
	lpCallStr->atArg[4]=TYP_SDWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SDWORD *";
	lpCallStr->atArg[5]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetFunctions /////

RETCODE SQL_API TraceSQLGetFunctions  (HDBC arg0,
		 UWORD arg1,
		 UWORD  * arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETFUNCTIONS;
	lpCallStr->szFuncName="SQLGetFunctions";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UWORD *";
	lpCallStr->atArg[2]=TYP_UWORDPTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetInfo /////

RETCODE SQL_API TraceSQLGetInfo  (HDBC arg0,
		 UWORD arg1,
		 PTR arg2,
		 SWORD arg3,
		 UNALIGNED SWORD * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETINFO;
	lpCallStr->szFuncName="SQLGetInfo";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="PTR";
	lpCallStr->atArg[2]=TYP_PTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetStmtOption /////

RETCODE SQL_API TraceSQLGetStmtOption  (HSTMT arg0,
		 UWORD arg1,
		 PTR arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETSTMTOPTION;
	lpCallStr->szFuncName="SQLGetStmtOption";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="PTR";
	lpCallStr->atArg[2]=TYP_PTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetTypeInfo /////

RETCODE SQL_API TraceSQLGetTypeInfo  (HSTMT arg0,
		 SWORD arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETTYPEINFO;
	lpCallStr->szFuncName="SQLGetTypeInfo";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SWORD";
	lpCallStr->atArg[1]=TYP_SWORD;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLParamData /////

RETCODE SQL_API TraceSQLParamData  (HSTMT arg0,
		 PTR * arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPARAMDATA;
	lpCallStr->szFuncName="SQLParamData";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="PTR *";
	lpCallStr->atArg[1]=TYP_PTRPTR;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLPutData /////

RETCODE SQL_API TraceSQLPutData  (HSTMT arg0,
		 PTR arg1,
		 SDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPUTDATA;
	lpCallStr->szFuncName="SQLPutData";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="PTR";
	lpCallStr->atArg[1]=TYP_PTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetConnectOption /////

RETCODE SQL_API TraceSQLSetConnectOption  (HDBC arg0,
		 UWORD arg1,
		 UDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETCONNECTOPTION;
	lpCallStr->szFuncName="SQLSetConnectOption";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UDWORD";
	lpCallStr->atArg[2]=TYP_UDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetStmtOption /////

RETCODE SQL_API TraceSQLSetStmtOption  (HSTMT arg0,
		 UWORD arg1,
		 UDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETSTMTOPTION;
	lpCallStr->szFuncName="SQLSetStmtOption";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UDWORD";
	lpCallStr->atArg[2]=TYP_UDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSpecialColumns /////

RETCODE SQL_API TraceSQLSpecialColumns  (HSTMT arg0,
		 UWORD arg1,
		 UCHAR * arg2,
		 SWORD arg3,
		 UCHAR * arg4,
		 SWORD arg5,
		 UCHAR * arg6,
		 SWORD arg7,
		 UWORD arg8,
		 UWORD arg9)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSPECIALCOLUMNS;
	lpCallStr->szFuncName="SQLSpecialColumns";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UCHAR *";
	lpCallStr->atArg[2]=TYP_UCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="UCHAR *";
	lpCallStr->atArg[4]=TYP_UCHARPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD";
	lpCallStr->atArg[5]=TYP_SWORD;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="UCHAR *";
	lpCallStr->atArg[6]=TYP_UCHARPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD";
	lpCallStr->atArg[7]=TYP_SWORD;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="UWORD";
	lpCallStr->atArg[8]=TYP_UWORD;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="UWORD";
	lpCallStr->atArg[9]=TYP_UWORD;
	lpCallStr->nArgs = 10;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLStatistics /////

RETCODE SQL_API TraceSQLStatistics  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UWORD arg7,
		 UWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSTATISTICS;
	lpCallStr->szFuncName="SQLStatistics";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UWORD";
	lpCallStr->atArg[7]=TYP_UWORD;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="UWORD";
	lpCallStr->atArg[8]=TYP_UWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLTables /////

RETCODE SQL_API TraceSQLTables  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLTABLES;
	lpCallStr->szFuncName="SQLTables";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UCHAR *";
	lpCallStr->atArg[7]=TYP_UCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLBrowseConnect /////

RETCODE SQL_API TraceSQLBrowseConnect  (HDBC arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UNALIGNED SWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLBROWSECONNECT;
	lpCallStr->szFuncName="SQLBrowseConnect";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColumnPrivileges /////

RETCODE SQL_API TraceSQLColumnPrivileges  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLUMNPRIVILEGES;
	lpCallStr->szFuncName="SQLColumnPrivileges";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UCHAR *";
	lpCallStr->atArg[7]=TYP_UCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDataSources /////

RETCODE SQL_API TraceSQLDataSources  (HENV arg0,
		 UWORD arg1,
		 UCHAR * arg2,
		 SWORD arg3,
		 SWORD * arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 SWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDATASOURCES;
	lpCallStr->szFuncName="SQLDataSources";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UCHAR *";
	lpCallStr->atArg[2]=TYP_UCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDescribeParam /////

RETCODE SQL_API TraceSQLDescribeParam  (HSTMT arg0,
		 UWORD arg1,
		 UNALIGNED SWORD * arg2,
		 UNALIGNED UDWORD * arg3,
		 UNALIGNED SWORD * arg4,
		 UNALIGNED SWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDESCRIBEPARAM;
	lpCallStr->szFuncName="SQLDescribeParam";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD *";
	lpCallStr->atArg[2]=TYP_SWORDPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UDWORD *";
	lpCallStr->atArg[3]=TYP_UDWORDPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLExtendedFetch /////

RETCODE SQL_API TraceSQLExtendedFetch  (HSTMT arg0,
		 UWORD arg1,
		 SDWORD arg2,
		 UNALIGNED UDWORD * arg3,
		 UNALIGNED UWORD * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLEXTENDEDFETCH;
	lpCallStr->szFuncName="SQLExtendedFetch";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UDWORD *";
	lpCallStr->atArg[3]=TYP_UDWORDPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="UWORD *";
	lpCallStr->atArg[4]=TYP_UWORDPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLForeignKeys /////

RETCODE SQL_API TraceSQLForeignKeys  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UCHAR * arg7,
		 SWORD arg8,
		 UCHAR * arg9,
		 SWORD arg10,
		 UCHAR * arg11,
		 SWORD arg12)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFOREIGNKEYS;
	lpCallStr->szFuncName="SQLForeignKeys";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UCHAR *";
	lpCallStr->atArg[7]=TYP_UCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="UCHAR *";
	lpCallStr->atArg[9]=TYP_UCHARPTR;
	lpCallStr->lpvArg[10] = (LPVOID) arg10;
	lpCallStr->szArg[10]="SWORD";
	lpCallStr->atArg[10]=TYP_SWORD;
	lpCallStr->lpvArg[11] = (LPVOID) arg11;
	lpCallStr->szArg[11]="UCHAR *";
	lpCallStr->atArg[11]=TYP_UCHARPTR;
	lpCallStr->lpvArg[12] = (LPVOID) arg12;
	lpCallStr->szArg[12]="SWORD";
	lpCallStr->atArg[12]=TYP_SWORD;
	lpCallStr->nArgs = 13;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLMoreResults /////

RETCODE SQL_API TraceSQLMoreResults  (HSTMT arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLMORERESULTS;
	lpCallStr->szFuncName="SQLMoreResults";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLNativeSql /////

RETCODE SQL_API TraceSQLNativeSql  (HDBC arg0,
		 UCHAR * arg1,
		 SDWORD arg2,
		 UCHAR * arg3,
		 SDWORD arg4,
		 UNALIGNED SDWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLNATIVESQL;
	lpCallStr->szFuncName="SQLNativeSql";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SDWORD";
	lpCallStr->atArg[4]=TYP_SDWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SDWORD *";
	lpCallStr->atArg[5]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLNumParams /////

RETCODE SQL_API TraceSQLNumParams  (HSTMT arg0,
		 UNALIGNED SWORD * arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLNUMPARAMS;
	lpCallStr->szFuncName="SQLNumParams";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SWORD *";
	lpCallStr->atArg[1]=TYP_SWORDPTR;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLParamOptions /////

RETCODE SQL_API TraceSQLParamOptions  (HSTMT arg0,
		 UDWORD arg1,
		 UNALIGNED UDWORD * arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPARAMOPTIONS;
	lpCallStr->szFuncName="SQLParamOptions";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UDWORD";
	lpCallStr->atArg[1]=TYP_UDWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UDWORD *";
	lpCallStr->atArg[2]=TYP_UDWORDPTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLPrimaryKeys /////

RETCODE SQL_API TraceSQLPrimaryKeys  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPRIMARYKEYS;
	lpCallStr->szFuncName="SQLPrimaryKeys";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLProcedureColumns /////

RETCODE SQL_API TraceSQLProcedureColumns  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 UCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPROCEDURECOLUMNS;
	lpCallStr->szFuncName="SQLProcedureColumns";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UCHAR *";
	lpCallStr->atArg[7]=TYP_UCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLProcedures /////

RETCODE SQL_API TraceSQLProcedures  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPROCEDURES;
	lpCallStr->szFuncName="SQLProcedures";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetPos /////

RETCODE SQL_API TraceSQLSetPos  (HSTMT arg0,
		 UWORD arg1,
		 UWORD arg2,
		 BOOL arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETPOS;
	lpCallStr->szFuncName="SQLSetPos";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UWORD";
	lpCallStr->atArg[2]=TYP_UWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="BOOL";
	lpCallStr->atArg[3]=TYP_BOOL;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetScrollOptions /////

RETCODE SQL_API TraceSQLSetScrollOptions  (HSTMT arg0,
		 UWORD arg1,
		 SDWORD arg2,
		 UWORD arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETSCROLLOPTIONS;
	lpCallStr->szFuncName="SQLSetScrollOptions";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UWORD";
	lpCallStr->atArg[3]=TYP_UWORD;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLTablePrivileges /////

RETCODE SQL_API TraceSQLTablePrivileges  (HSTMT arg0,
		 UCHAR * arg1,
		 SWORD arg2,
		 UCHAR * arg3,
		 SWORD arg4,
		 UCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLTABLEPRIVILEGES;
	lpCallStr->szFuncName="SQLTablePrivileges";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UCHAR *";
	lpCallStr->atArg[1]=TYP_UCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="UCHAR *";
	lpCallStr->atArg[3]=TYP_UCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDrivers /////

RETCODE SQL_API TraceSQLDrivers  (HENV arg0,
		 UWORD arg1,
		 UCHAR * arg2,
		 SWORD arg3,
		 SWORD * arg4,
		 UCHAR * arg5,
		 SWORD arg6,
		 SWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDRIVERS;
	lpCallStr->szFuncName="SQLDrivers";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UCHAR *";
	lpCallStr->atArg[2]=TYP_UCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UCHAR *";
	lpCallStr->atArg[5]=TYP_UCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLBindParameter /////

RETCODE SQL_API TraceSQLBindParameter  (HSTMT arg0,
		 UWORD arg1,
		 SWORD arg2,
		 SWORD arg3,
		 SWORD arg4,
		 UDWORD arg5,
		 SWORD arg6,
		 PTR arg7,
		 SDWORD arg8,
			UNALIGNED SDWORD * arg9)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLBINDPARAMETER;
	lpCallStr->szFuncName="SQLBindParameter";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="UDWORD";
	lpCallStr->atArg[5]=TYP_UDWORD;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="PTR";
	lpCallStr->atArg[7]=TYP_PTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SDWORD";
	lpCallStr->atArg[8]=TYP_SDWORD;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="SDWORD *";
	lpCallStr->atArg[9]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 10;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLAllocHandle /////

RETCODE SQL_API TraceSQLAllocHandle  (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLHANDLE * arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLALLOCHANDLE;
	lpCallStr->szFuncName="SQLAllocHandle";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLHANDLE *";
	lpCallStr->atArg[2]=TYP_SQLHANDLEPTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLBindParam /////

RETCODE SQL_API TraceSQLBindParam  (SQLHSTMT arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLSMALLINT arg3,
		 SQLINTEGER arg4,
		 SQLSMALLINT arg5,
		 SQLPOINTER arg6,
		 UNALIGNED SQLINTEGER * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLBINDPARAM;
	lpCallStr->szFuncName="SQLBindParam";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLSMALLINT";
	lpCallStr->atArg[3]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER";
	lpCallStr->atArg[4]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT";
	lpCallStr->atArg[5]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLPOINTER";
	lpCallStr->atArg[6]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SQLINTEGER *";
	lpCallStr->atArg[7]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLCloseCursor /////

RETCODE SQL_API TraceSQLCloseCursor  (SQLHSTMT arg0)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCLOSECURSOR;
	lpCallStr->szFuncName="SQLCloseCursor";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->nArgs = 1;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColAttribute /////

RETCODE SQL_API TraceSQLColAttribute  (SQLHSTMT arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLPOINTER arg3,
		 SQLSMALLINT arg4,
		 UNALIGNED SQLSMALLINT * arg5,
		 SQLPOINTER arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLATTRIBUTE;
	lpCallStr->szFuncName="SQLColAttribute";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLPOINTER";
	lpCallStr->atArg[3]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLSMALLINT";
	lpCallStr->atArg[4]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT *";
	lpCallStr->atArg[5]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLPOINTER";
	lpCallStr->atArg[6]=TYP_SQLPOINTER;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLCopyDesc /////

RETCODE SQL_API TraceSQLCopyDesc  (SQLHDESC arg0,
		 SQLHDESC arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOPYDESC;
	lpCallStr->szFuncName="SQLCopyDesc";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHDESC";
	lpCallStr->atArg[1]=TYP_SQLHDESC;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLEndTran /////

RETCODE SQL_API TraceSQLEndTran  (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLSMALLINT arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLENDTRAN;
	lpCallStr->szFuncName="SQLEndTran";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLFetchScroll /////

RETCODE SQL_API TraceSQLFetchScroll  (SQLHSTMT arg0,
		 SQLSMALLINT arg1,
		 SQLINTEGER arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFETCHSCROLL;
	lpCallStr->szFuncName="SQLFetchScroll";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLINTEGER";
	lpCallStr->atArg[2]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLFreeHandle /////

RETCODE SQL_API TraceSQLFreeHandle  (SQLSMALLINT arg0,
		 SQLHANDLE arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFREEHANDLE;
	lpCallStr->szFuncName="SQLFreeHandle";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetConnectAttr /////

RETCODE SQL_API TraceSQLGetConnectAttr  (SQLHDBC arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3,
		 UNALIGNED SQLINTEGER * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETCONNECTATTR;
	lpCallStr->szFuncName="SQLGetConnectAttr";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDBC";
	lpCallStr->atArg[0]=TYP_SQLHDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDescField /////

RETCODE SQL_API TraceSQLGetDescField  (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLPOINTER arg3,
		 SQLINTEGER arg4,
		 UNALIGNED SQLINTEGER * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDESCFIELD;
	lpCallStr->szFuncName="SQLGetDescField";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLPOINTER";
	lpCallStr->atArg[3]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER";
	lpCallStr->atArg[4]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLINTEGER *";
	lpCallStr->atArg[5]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDescRec /////

RETCODE SQL_API TraceSQLGetDescRec  (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLCHAR * arg2,
		 SQLSMALLINT arg3,
		 UNALIGNED SQLSMALLINT * arg4,
		 UNALIGNED SQLSMALLINT * arg5,
		 UNALIGNED SQLSMALLINT * arg6,
		 UNALIGNED SQLINTEGER  * arg7,
		 UNALIGNED SQLSMALLINT * arg8,
		 UNALIGNED SQLSMALLINT * arg9,
		 UNALIGNED SQLSMALLINT * arg10)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDESCREC;
	lpCallStr->szFuncName="SQLGetDescRec";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLCHAR *";
	lpCallStr->atArg[2]=TYP_SQLCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLSMALLINT";
	lpCallStr->atArg[3]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLSMALLINT *";
	lpCallStr->atArg[4]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT *";
	lpCallStr->atArg[5]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT *";
	lpCallStr->atArg[6]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SQLINTEGER *";
	lpCallStr->atArg[7]=TYP_SQLINTEGERPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SQLSMALLINT *";
	lpCallStr->atArg[8]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="SQLSMALLINT *";
	lpCallStr->atArg[9]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[10] = (LPVOID) arg10;
	lpCallStr->szArg[10]="SQLSMALLINT *";
	lpCallStr->atArg[10]=TYP_SQLSMALLINTPTR;
	lpCallStr->nArgs = 11;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDiagField /////

RETCODE SQL_API TraceSQLGetDiagField  (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLSMALLINT arg2,
		 SQLSMALLINT arg3,
		 SQLPOINTER arg4,
		 SQLSMALLINT arg5,
		 UNALIGNED SQLSMALLINT * arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDIAGFIELD;
	lpCallStr->szFuncName="SQLGetDiagField";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLSMALLINT";
	lpCallStr->atArg[3]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLPOINTER";
	lpCallStr->atArg[4]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT";
	lpCallStr->atArg[5]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT *";
	lpCallStr->atArg[6]=TYP_SQLSMALLINTPTR;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDiagRec /////

RETCODE SQL_API TraceSQLGetDiagRec  (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLSMALLINT arg2,
		 SQLCHAR * arg3,
		 UNALIGNED SQLINTEGER * arg4,
		 SQLCHAR * arg5,
		 SQLSMALLINT arg6,
		 UNALIGNED SQLSMALLINT * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDIAGREC;
	lpCallStr->szFuncName="SQLGetDiagRec";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLCHAR *";
	lpCallStr->atArg[3]=TYP_SQLCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLCHAR *";
	lpCallStr->atArg[5]=TYP_SQLCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT";
	lpCallStr->atArg[6]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SQLSMALLINT *";
	lpCallStr->atArg[7]=TYP_SQLSMALLINTPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetEnvAttr /////

RETCODE SQL_API TraceSQLGetEnvAttr  (SQLHENV arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3,
		 UNALIGNED SQLINTEGER * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETENVATTR;
	lpCallStr->szFuncName="SQLGetEnvAttr";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHENV";
	lpCallStr->atArg[0]=TYP_SQLHENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetStmtAttr /////

RETCODE SQL_API TraceSQLGetStmtAttr  (SQLHSTMT arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3,
		 UNALIGNED SQLINTEGER * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETSTMTATTR;
	lpCallStr->szFuncName="SQLGetStmtAttr";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetConnectAttr /////

RETCODE SQL_API TraceSQLSetConnectAttr  (SQLHDBC arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETCONNECTATTR;
	lpCallStr->szFuncName="SQLSetConnectAttr";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDBC";
	lpCallStr->atArg[0]=TYP_SQLHDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetDescField /////

RETCODE SQL_API TraceSQLSetDescField  (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLPOINTER arg3,
		 SQLINTEGER arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETDESCFIELD;
	lpCallStr->szFuncName="SQLSetDescField";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLPOINTER";
	lpCallStr->atArg[3]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER";
	lpCallStr->atArg[4]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetDescRec /////

RETCODE SQL_API TraceSQLSetDescRec  (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLSMALLINT arg3,
		 SQLINTEGER arg4,
		 SQLSMALLINT arg5,
		 SQLSMALLINT arg6,
		 SQLPOINTER arg7,
		 UNALIGNED SQLINTEGER * arg8,
		 UNALIGNED SQLINTEGER * arg9)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETDESCREC;
	lpCallStr->szFuncName="SQLSetDescRec";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLSMALLINT";
	lpCallStr->atArg[3]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER";
	lpCallStr->atArg[4]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT";
	lpCallStr->atArg[5]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT";
	lpCallStr->atArg[6]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SQLPOINTER";
	lpCallStr->atArg[7]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SQLINTEGER *";
	lpCallStr->atArg[8]=TYP_SQLINTEGERPTR;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="SQLINTEGER *";
	lpCallStr->atArg[9]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 10;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetEnvAttr /////

RETCODE SQL_API TraceSQLSetEnvAttr  (SQLHENV arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETENVATTR;
	lpCallStr->szFuncName="SQLSetEnvAttr";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHENV";
	lpCallStr->atArg[0]=TYP_SQLHENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetStmtAttr /////

RETCODE SQL_API TraceSQLSetStmtAttr  (SQLHSTMT arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETSTMTATTR;
	lpCallStr->szFuncName="SQLSetStmtAttr";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLAllocHandleStd /////

RETCODE SQL_API TraceSQLAllocHandleStd  (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLHANDLE * arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLALLOCHANDLESTD;
	lpCallStr->szFuncName="SQLAllocHandleStd";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLHANDLE *";
	lpCallStr->atArg[2]=TYP_SQLHANDLEPTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLBulkOperations /////

RETCODE SQL_API TraceSQLBulkOperations  (SQLHSTMT arg0,
			SQLSMALLINT arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLBULKOPERATIONS;
	lpCallStr->szFuncName="SQLBulkOperations";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}
// Generated by makefile (dofuncs.pl), do not modify! // 

///// Trace function for SQLColAttributes /////

RETCODE SQL_API TraceSQLColAttributesW (HSTMT arg0,
		 UWORD arg1,
		 UWORD arg2,
		 PTR arg3,
		 SWORD arg4,
		 UNALIGNED SWORD * arg5,
		 UNALIGNED SDWORD * arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLATTRIBUTES;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLColAttributesW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UWORD";
	lpCallStr->atArg[2]=TYP_UWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="PTR";
	lpCallStr->atArg[3]=TYP_PTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SDWORD *";
	lpCallStr->atArg[6]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLConnect /////

RETCODE SQL_API TraceSQLConnectW (HDBC arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCONNECT;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLConnectW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDescribeCol /////

RETCODE SQL_API TraceSQLDescribeColW (HSTMT arg0,
		 UWORD arg1,
		 WCHAR * arg2,
		 SWORD arg3,
		 SWORD * arg4,
		 UNALIGNED SWORD * arg5,
		 UNALIGNED UDWORD * arg6,
		 UNALIGNED SWORD * arg7,
		 UNALIGNED SWORD * arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDESCRIBECOL;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLDescribeColW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="WCHAR *";
	lpCallStr->atArg[2]=TYP_WCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="UDWORD *";
	lpCallStr->atArg[6]=TYP_UDWORDPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD *";
	lpCallStr->atArg[8]=TYP_SWORDPTR;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLError /////

RETCODE SQL_API TraceSQLErrorW (HENV arg0,
		 HDBC arg1,
		 HSTMT arg2,
		 WCHAR * arg3,
		 UNALIGNED SDWORD * arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 UNALIGNED SWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLERROR;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLErrorW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HDBC";
	lpCallStr->atArg[1]=TYP_HDBC;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="HSTMT";
	lpCallStr->atArg[2]=TYP_HSTMT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SDWORD *";
	lpCallStr->atArg[4]=TYP_SDWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLExecDirect /////

RETCODE SQL_API TraceSQLExecDirectW (HSTMT arg0,
		 WCHAR * arg1,
		 SDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLEXECDIRECT;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLExecDirectW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetCursorName /////

RETCODE SQL_API TraceSQLGetCursorNameW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 UNALIGNED SWORD * arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETCURSORNAME;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetCursorNameW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD *";
	lpCallStr->atArg[3]=TYP_SWORDPTR;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLPrepare /////

RETCODE SQL_API TraceSQLPrepareW (HSTMT arg0,
		 WCHAR * arg1,
		 SDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPREPARE;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLPrepareW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetCursorName /////

RETCODE SQL_API TraceSQLSetCursorNameW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETCURSORNAME;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLSetCursorNameW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColumns /////

RETCODE SQL_API TraceSQLColumnsW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 WCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLUMNS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLColumnsW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="WCHAR *";
	lpCallStr->atArg[7]=TYP_WCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDriverConnect /////

RETCODE SQL_API TraceSQLDriverConnectW (HDBC arg0,
		 HWND arg1,
		 WCHAR * arg2,
		 SWORD arg3,
		 WCHAR * arg4,
		 SWORD arg5,
		 UNALIGNED SWORD * arg6,
		 UWORD arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDRIVERCONNECT;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLDriverConnectW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="HWND";
	lpCallStr->atArg[1]=TYP_HWND;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="WCHAR *";
	lpCallStr->atArg[2]=TYP_WCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="WCHAR *";
	lpCallStr->atArg[4]=TYP_WCHARPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD";
	lpCallStr->atArg[5]=TYP_SWORD;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD *";
	lpCallStr->atArg[6]=TYP_SWORDPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UWORD";
	lpCallStr->atArg[7]=TYP_UWORD;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetConnectOption /////

RETCODE SQL_API TraceSQLGetConnectOptionW (HDBC arg0,
		 UWORD arg1,
		 PTR arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETCONNECTOPTION;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetConnectOptionW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="PTR";
	lpCallStr->atArg[2]=TYP_PTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetInfo /////

RETCODE SQL_API TraceSQLGetInfoW (HDBC arg0,
		 UWORD arg1,
		 PTR arg2,
		 SWORD arg3,
		 UNALIGNED SWORD * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETINFO;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetInfoW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="PTR";
	lpCallStr->atArg[2]=TYP_PTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetTypeInfo /////

RETCODE SQL_API TraceSQLGetTypeInfoW (HSTMT arg0,
		 SWORD arg1)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETTYPEINFO;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetTypeInfoW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SWORD";
	lpCallStr->atArg[1]=TYP_SWORD;
	lpCallStr->nArgs = 2;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetConnectOption /////

RETCODE SQL_API TraceSQLSetConnectOptionW (HDBC arg0,
		 UWORD arg1,
		 UDWORD arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETCONNECTOPTION;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLSetConnectOptionW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="UDWORD";
	lpCallStr->atArg[2]=TYP_UDWORD;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSpecialColumns /////

RETCODE SQL_API TraceSQLSpecialColumnsW (HSTMT arg0,
		 UWORD arg1,
		 WCHAR * arg2,
		 SWORD arg3,
		 WCHAR * arg4,
		 SWORD arg5,
		 WCHAR * arg6,
		 SWORD arg7,
		 UWORD arg8,
		 UWORD arg9)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSPECIALCOLUMNS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLSpecialColumnsW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="WCHAR *";
	lpCallStr->atArg[2]=TYP_WCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="WCHAR *";
	lpCallStr->atArg[4]=TYP_WCHARPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD";
	lpCallStr->atArg[5]=TYP_SWORD;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="WCHAR *";
	lpCallStr->atArg[6]=TYP_WCHARPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD";
	lpCallStr->atArg[7]=TYP_SWORD;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="UWORD";
	lpCallStr->atArg[8]=TYP_UWORD;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="UWORD";
	lpCallStr->atArg[9]=TYP_UWORD;
	lpCallStr->nArgs = 10;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLStatistics /////

RETCODE SQL_API TraceSQLStatisticsW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 UWORD arg7,
		 UWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSTATISTICS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLStatisticsW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="UWORD";
	lpCallStr->atArg[7]=TYP_UWORD;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="UWORD";
	lpCallStr->atArg[8]=TYP_UWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLTables /////

RETCODE SQL_API TraceSQLTablesW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 WCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLTABLES;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLTablesW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="WCHAR *";
	lpCallStr->atArg[7]=TYP_WCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLBrowseConnect /////

RETCODE SQL_API TraceSQLBrowseConnectW (HDBC arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 UNALIGNED SWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLBROWSECONNECT;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLBrowseConnectW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SWORD *";
	lpCallStr->atArg[5]=TYP_SWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColumnPrivileges /////

RETCODE SQL_API TraceSQLColumnPrivilegesW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 WCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLUMNPRIVILEGES;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLColumnPrivilegesW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="WCHAR *";
	lpCallStr->atArg[7]=TYP_WCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDataSources /////

RETCODE SQL_API TraceSQLDataSourcesW (HENV arg0,
		 UWORD arg1,
		 WCHAR * arg2,
		 SWORD arg3,
		 SWORD * arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 SWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDATASOURCES;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLDataSourcesW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="WCHAR *";
	lpCallStr->atArg[2]=TYP_WCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLForeignKeys /////

RETCODE SQL_API TraceSQLForeignKeysW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 WCHAR * arg7,
		 SWORD arg8,
		 WCHAR * arg9,
		 SWORD arg10,
		 WCHAR * arg11,
		 SWORD arg12)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLFOREIGNKEYS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLForeignKeysW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="WCHAR *";
	lpCallStr->atArg[7]=TYP_WCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="WCHAR *";
	lpCallStr->atArg[9]=TYP_WCHARPTR;
	lpCallStr->lpvArg[10] = (LPVOID) arg10;
	lpCallStr->szArg[10]="SWORD";
	lpCallStr->atArg[10]=TYP_SWORD;
	lpCallStr->lpvArg[11] = (LPVOID) arg11;
	lpCallStr->szArg[11]="WCHAR *";
	lpCallStr->atArg[11]=TYP_WCHARPTR;
	lpCallStr->lpvArg[12] = (LPVOID) arg12;
	lpCallStr->szArg[12]="SWORD";
	lpCallStr->atArg[12]=TYP_SWORD;
	lpCallStr->nArgs = 13;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLNativeSql /////

RETCODE SQL_API TraceSQLNativeSqlW (HDBC arg0,
		 WCHAR * arg1,
		 SDWORD arg2,
		 WCHAR * arg3,
		 SDWORD arg4,
		 UNALIGNED SDWORD * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLNATIVESQL;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLNativeSqlW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HDBC";
	lpCallStr->atArg[0]=TYP_HDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SDWORD";
	lpCallStr->atArg[2]=TYP_SDWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SDWORD";
	lpCallStr->atArg[4]=TYP_SDWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SDWORD *";
	lpCallStr->atArg[5]=TYP_SDWORDPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLPrimaryKeys /////

RETCODE SQL_API TraceSQLPrimaryKeysW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPRIMARYKEYS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLPrimaryKeysW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLProcedureColumns /////

RETCODE SQL_API TraceSQLProcedureColumnsW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 WCHAR * arg7,
		 SWORD arg8)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPROCEDURECOLUMNS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLProcedureColumnsW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="WCHAR *";
	lpCallStr->atArg[7]=TYP_WCHARPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SWORD";
	lpCallStr->atArg[8]=TYP_SWORD;
	lpCallStr->nArgs = 9;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLProcedures /////

RETCODE SQL_API TraceSQLProceduresW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLPROCEDURES;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLProceduresW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLTablePrivileges /////

RETCODE SQL_API TraceSQLTablePrivilegesW (HSTMT arg0,
		 WCHAR * arg1,
		 SWORD arg2,
		 WCHAR * arg3,
		 SWORD arg4,
		 WCHAR * arg5,
		 SWORD arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLTABLEPRIVILEGES;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLTablePrivilegesW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HSTMT";
	lpCallStr->atArg[0]=TYP_HSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="WCHAR *";
	lpCallStr->atArg[1]=TYP_WCHARPTR;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SWORD";
	lpCallStr->atArg[2]=TYP_SWORD;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="WCHAR *";
	lpCallStr->atArg[3]=TYP_WCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD";
	lpCallStr->atArg[4]=TYP_SWORD;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLDrivers /////

RETCODE SQL_API TraceSQLDriversW (HENV arg0,
		 UWORD arg1,
		 WCHAR * arg2,
		 SWORD arg3,
		 SWORD * arg4,
		 WCHAR * arg5,
		 SWORD arg6,
		 SWORD * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLDRIVERS;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLDriversW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="HENV";
	lpCallStr->atArg[0]=TYP_HENV;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="UWORD";
	lpCallStr->atArg[1]=TYP_UWORD;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="WCHAR *";
	lpCallStr->atArg[2]=TYP_WCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SWORD";
	lpCallStr->atArg[3]=TYP_SWORD;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SWORD *";
	lpCallStr->atArg[4]=TYP_SWORDPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="WCHAR *";
	lpCallStr->atArg[5]=TYP_WCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SWORD";
	lpCallStr->atArg[6]=TYP_SWORD;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SWORD *";
	lpCallStr->atArg[7]=TYP_SWORDPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLColAttribute /////

RETCODE SQL_API TraceSQLColAttributeW (SQLHSTMT arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLPOINTER arg3,
		 SQLSMALLINT arg4,
		 UNALIGNED SQLSMALLINT * arg5,
		 SQLPOINTER arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLCOLATTRIBUTE;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLColAttributeW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLPOINTER";
	lpCallStr->atArg[3]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLSMALLINT";
	lpCallStr->atArg[4]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT *";
	lpCallStr->atArg[5]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLPOINTER";
	lpCallStr->atArg[6]=TYP_SQLPOINTER;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetConnectAttr /////

RETCODE SQL_API TraceSQLGetConnectAttrW (SQLHDBC arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3,
		 UNALIGNED SQLINTEGER * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETCONNECTATTR;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetConnectAttrW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDBC";
	lpCallStr->atArg[0]=TYP_SQLHDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDescField /////

RETCODE SQL_API TraceSQLGetDescFieldW (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLPOINTER arg3,
		 SQLINTEGER arg4,
		 UNALIGNED SQLINTEGER * arg5)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDESCFIELD;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetDescFieldW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLPOINTER";
	lpCallStr->atArg[3]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER";
	lpCallStr->atArg[4]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLINTEGER *";
	lpCallStr->atArg[5]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 6;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDescRec /////

RETCODE SQL_API TraceSQLGetDescRecW (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLWCHAR * arg2,
		 SQLSMALLINT arg3,
		 UNALIGNED SQLSMALLINT * arg4,
		 UNALIGNED SQLSMALLINT * arg5,
		 UNALIGNED SQLSMALLINT * arg6,
		 UNALIGNED SQLINTEGER  * arg7,
		 UNALIGNED SQLSMALLINT * arg8,
		 UNALIGNED SQLSMALLINT * arg9,
		 UNALIGNED SQLSMALLINT * arg10)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDESCREC;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetDescRecW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLWCHAR *";
	lpCallStr->atArg[2]=TYP_SQLWCHARPTR;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLSMALLINT";
	lpCallStr->atArg[3]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLSMALLINT *";
	lpCallStr->atArg[4]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT *";
	lpCallStr->atArg[5]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT *";
	lpCallStr->atArg[6]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SQLINTEGER *";
	lpCallStr->atArg[7]=TYP_SQLINTEGERPTR;
	lpCallStr->lpvArg[8] = (LPVOID) arg8;
	lpCallStr->szArg[8]="SQLSMALLINT *";
	lpCallStr->atArg[8]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[9] = (LPVOID) arg9;
	lpCallStr->szArg[9]="SQLSMALLINT *";
	lpCallStr->atArg[9]=TYP_SQLSMALLINTPTR;
	lpCallStr->lpvArg[10] = (LPVOID) arg10;
	lpCallStr->szArg[10]="SQLSMALLINT *";
	lpCallStr->atArg[10]=TYP_SQLSMALLINTPTR;
	lpCallStr->nArgs = 11;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDiagField /////

RETCODE SQL_API TraceSQLGetDiagFieldW (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLSMALLINT arg2,
		 SQLSMALLINT arg3,
		 SQLPOINTER arg4,
		 SQLSMALLINT arg5,
		 UNALIGNED SQLSMALLINT * arg6)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDIAGFIELD;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetDiagFieldW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLSMALLINT";
	lpCallStr->atArg[3]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLPOINTER";
	lpCallStr->atArg[4]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLSMALLINT";
	lpCallStr->atArg[5]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT *";
	lpCallStr->atArg[6]=TYP_SQLSMALLINTPTR;
	lpCallStr->nArgs = 7;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetDiagRec /////

RETCODE SQL_API TraceSQLGetDiagRecW (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLSMALLINT arg2,
		 SQLWCHAR * arg3,
		 UNALIGNED SQLINTEGER * arg4,
		 SQLWCHAR * arg5,
		 SQLSMALLINT arg6,
		 UNALIGNED SQLSMALLINT * arg7)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETDIAGREC;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetDiagRecW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLWCHAR *";
	lpCallStr->atArg[3]=TYP_SQLWCHARPTR;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->lpvArg[5] = (LPVOID) arg5;
	lpCallStr->szArg[5]="SQLWCHAR *";
	lpCallStr->atArg[5]=TYP_SQLWCHARPTR;
	lpCallStr->lpvArg[6] = (LPVOID) arg6;
	lpCallStr->szArg[6]="SQLSMALLINT";
	lpCallStr->atArg[6]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[7] = (LPVOID) arg7;
	lpCallStr->szArg[7]="SQLSMALLINT *";
	lpCallStr->atArg[7]=TYP_SQLSMALLINTPTR;
	lpCallStr->nArgs = 8;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLGetStmtAttr /////

RETCODE SQL_API TraceSQLGetStmtAttrW (SQLHSTMT arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3,
		 UNALIGNED SQLINTEGER * arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLGETSTMTATTR;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLGetStmtAttrW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER *";
	lpCallStr->atArg[4]=TYP_SQLINTEGERPTR;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetConnectAttr /////

RETCODE SQL_API TraceSQLSetConnectAttrW (SQLHDBC arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETCONNECTATTR;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLSetConnectAttrW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDBC";
	lpCallStr->atArg[0]=TYP_SQLHDBC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetDescField /////

RETCODE SQL_API TraceSQLSetDescFieldW (SQLHDESC arg0,
		 SQLSMALLINT arg1,
		 SQLSMALLINT arg2,
		 SQLPOINTER arg3,
		 SQLINTEGER arg4)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETDESCFIELD;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLSetDescFieldW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHDESC";
	lpCallStr->atArg[0]=TYP_SQLHDESC;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLSMALLINT";
	lpCallStr->atArg[1]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLSMALLINT";
	lpCallStr->atArg[2]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLPOINTER";
	lpCallStr->atArg[3]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[4] = (LPVOID) arg4;
	lpCallStr->szArg[4]="SQLINTEGER";
	lpCallStr->atArg[4]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 5;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLSetStmtAttr /////

RETCODE SQL_API TraceSQLSetStmtAttrW (SQLHSTMT arg0,
		 SQLINTEGER arg1,
		 SQLPOINTER arg2,
		 SQLINTEGER arg3)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLSETSTMTATTR;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLSetStmtAttrW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLHSTMT";
	lpCallStr->atArg[0]=TYP_SQLHSTMT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLINTEGER";
	lpCallStr->atArg[1]=TYP_SQLINTEGER;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLPOINTER";
	lpCallStr->atArg[2]=TYP_SQLPOINTER;
	lpCallStr->lpvArg[3] = (LPVOID) arg3;
	lpCallStr->szArg[3]="SQLINTEGER";
	lpCallStr->atArg[3]=TYP_SQLINTEGER;
	lpCallStr->nArgs = 4;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}

///// Trace function for SQLAllocHandleStd /////

RETCODE SQL_API TraceSQLAllocHandleStdW (SQLSMALLINT arg0,
		 SQLHANDLE arg1,
		 SQLHANDLE * arg2)
{
	LPTRACESTR	lpCallStr = (LPTRACESTR) malloc(sizeof(TRACESTR));
	if (lpCallStr == NULL)
		return 0;
	memset(lpCallStr,0,sizeof(TRACESTR));
	lpCallStr->dwCallFunc = SQL_API_SQLALLOCHANDLESTD;
	lpCallStr->dwFlags |= TRACESTR_FLAG_UNICODE;
	lpCallStr->szFuncName="SQLAllocHandleStdW";
	lpCallStr->lpvArg[0] = (LPVOID) arg0;
	lpCallStr->szArg[0]="SQLSMALLINT";
	lpCallStr->atArg[0]=TYP_SQLSMALLINT;
	lpCallStr->lpvArg[1] = (LPVOID) arg1;
	lpCallStr->szArg[1]="SQLHANDLE";
	lpCallStr->atArg[1]=TYP_SQLHANDLE;
	lpCallStr->lpvArg[2] = (LPVOID) arg2;
	lpCallStr->szArg[2]="SQLHANDLE *";
	lpCallStr->atArg[2]=TYP_SQLHANDLEPTR;
	lpCallStr->nArgs = 3;
	DoTrace(lpCallStr);
	return((RETCODE)SetNextHandle(lpCallStr));
}
