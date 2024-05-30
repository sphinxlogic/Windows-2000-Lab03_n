// This is an example of an extended procedure DLL built with Open Data
// Services. The functions within the DLL can be invoked by using the extended
//      stored procedures support in SQL Server.  To register the functions 
// and allow all users to use them run the ISQL script XP_ODBC.SQL.
//
// For further information on Open Data Services refer to the Microsoft Open 
// Data Services Programmer's Reference.
//
//  The extended procedures implemented in this DLL is:
//
//  XP_GETTABLE_ODBC -- Used to show the creation of a new connection to
//  SQL Server using ODBC that is bound to the initial client connection
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>
#include <srv.h>

// Miscellaneous defines.
#define XP_NOERROR              0
#define XP_ERROR                1

// Extended procedure error codes.
#define SRV_MAXERROR            50000
#define GETTABLE_ERROR          SRV_MAXERROR + 1

#define REMOTE_FAIL             4002

void handle_odbc_err(PSTR szODBCApi,
	SQLRETURN sret,
	DBINT msgnum,
	SQLHANDLE herror,
	SQLSMALLINT htype,
	SRV_PROC* srvproc);

// It is highly recommended that all Microsoft® SQL Server (7.0 
// and greater) extended stored procedure DLLs implement and export 
// __GetXpVersion. For more information see SQL Server 
// Books Online
ULONG __GetXpVersion()

{
    return ODS_VERSION;
}


// XP_GETTABLE_ODBC
//    Returns the result of the SQL statement
//              select * from <szTable>
//
// Parameters:
//    srvproc - the handle to the client connection that 
//    got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//    Returns messages and/or a result set to client. 
RETCODE xp_gettable_odbc(srvproc)
SRV_PROC *srvproc;
{

    HENV        henv        = SQL_NULL_HENV;
    HDBC        hdbc        = SQL_NULL_HDBC;
    HSTMT       hstmt       = SQL_NULL_HSTMT;
    SQLRETURN   sret;
    RETCODE     rc;

    char        acBindToken[256];

    // ODBC column attributes.
    TCHAR       acColumnName[MAXNAME];
    SQLINTEGER  cbColData;
    SQLSMALLINT eSQLType;
    SQLINTEGER  iNumAttr;
    SQLSMALLINT cbAttr;                // pointer to storage for descriptor info
    PBYTE*      ppData      = NULL;
    SQLINTEGER* pIndicators = NULL;
    DBINT       rows        = 0L;           // number of rows sent
    PTSTR       szDSN       = _T("local");  // for integrated security to work you need to 
                                            // specify a local server in the ODBC setting
                                            // in the Control Panel in Windows
    int         bImpersonated;

    TCHAR       acUID[MAXNAME];
    TCHAR       acPWD[MAXNAME];

    int         nParams;
    DBINT       paramtype;

    TCHAR       szTable[MAXNAME * 3];   // database.owner.table
    TCHAR       szExec[128 + (MAXNAME * 3)];
    SQLSMALLINT nCols;
    SQLSMALLINT nCol;

    RETCODE     rcXP = XP_ERROR;        // Assume failure until shown otherwise.

    // Get number of parameters.
    nParams = srv_rpcparams(srvproc);   

    // Check number of parameters
    if (nParams != 1) {
	    // Send error message and return
        srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR, SRV_INFO, (DBTINYINT)0,
            NULL, 0, 0, "Error executing extended stored procedure: Invalid Parameter",
            SRV_NULLTERM);

        // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
        // result set of an Extended Stored Procedure.
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        return(XP_ERROR);
        }

    // If parameter is not varchar (should be a table name), send an
    // error and return.
    paramtype = srv_paramtype(srvproc, nParams);
    if (paramtype != SRVVARCHAR) {
        srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR, SRV_INFO, (DBTINYINT)0,
            NULL, 0, 0,
            "Error executing extended stored procedure: Invalid Parameter Type",
            SRV_NULLTERM);

        // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
        // result set of an Extended Stored Procedure.
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        return(XP_ERROR);
        }

    // Terminate parameter string with NULL.
    memcpy(szTable, srv_paramdata(srvproc, 1),
        srv_paramlen(srvproc, 1));
    szTable[srv_paramlen(srvproc, 1)] = '\0';
	
    // Allocate an ODBC environment handle
    sret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
    if (sret != SQL_SUCCESS) {
        handle_odbc_err("SQLAllocHandle:Env",
            sret, 
            (DBINT) REMOTE_FAIL,
            henv,
            SQL_HANDLE_ENV,
            srvproc);
        return(XP_ERROR);
        }
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3,
        SQL_IS_INTEGER);

    // Allocate an ODBC connection handle
    sret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (sret != SQL_SUCCESS) {
        handle_odbc_err("SQLAllocHandle:Dbc",
            sret, 
            (DBINT)REMOTE_FAIL,
            henv, 
            SQL_HANDLE_ENV, 
            srvproc);

        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        return(XP_ERROR);
        }

    // Check for integrated security.
    if (strcmp(srv_pfield(srvproc, SRV_LSECURE, (int *)NULL), "TRUE") == 0) {
        // Client has accessed using some form of integrated security
        // Impersonate client and set SQL_INTEGRATED_SECURITY option
        bImpersonated = srv_impersonate_client(srvproc);

        // Connect to DSN using integrated security
        SQLSetConnectAttr(hdbc, SQL_INTEGRATED_SECURITY, 
            (SQLPOINTER) SQL_IS_ON, SQL_IS_INTEGER);
        _tcscpy(acUID, _T(""));
        _tcscpy(acPWD, _T(""));
        }
    else {
        // Client used standard login. Set the user name and password.
#ifdef UNICODE
        MultiByteToWideChar(CP_ACP, 0, srv_pfield(srvproc, SRV_USER, NULL),
            -1, acUID, MAXNAME);
        MultiByteToWideChar(CP_ACP, 0, srv_pfield(srvproc, SRV_PWD, NULL),
            -1, acPWD, MAXNAME);
#else
        strncpy(acUID, srv_pfield(srvproc, SRV_USER, NULL),
            MAXNAME);
        strncpy(acPWD, srv_pfield(srvproc, SRV_PWD, NULL),
            MAXNAME);
#endif
	    }

    if (!SQL_SUCCEEDED(
        sret = SQLConnect(hdbc, (SQLTCHAR*) szDSN, SQL_NTS, 
        (SQLTCHAR*) acUID, SQL_NTS, (SQLTCHAR*) acPWD, SQL_NTS)
        )) {
        handle_odbc_err("SQLConnect",
            sret, 
            (DBINT)REMOTE_FAIL,
            hdbc, 
            SQL_HANDLE_DBC, 
            srvproc);
        goto SAFE_EXIT;
        } 

    // Process data after successful connection 
    sret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (sret != SQL_SUCCESS) {
        handle_odbc_err("SQLAllocHandle",
            sret, 
            (DBINT)REMOTE_FAIL,
            hdbc, 
            SQL_HANDLE_DBC, 
            srvproc);
        return(XP_ERROR);
        }

    // Get the client session token...
    rc = srv_getbindtoken(srvproc, acBindToken);
    if (rc == FAIL) {
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            GETTABLE_ERROR,
            SRV_INFO,
            (DBTINYINT) 0,
            NULL,
            0,
            0,
            "Error with srv_getbindtoken",
            SRV_NULLTERM);
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        return(XP_ERROR);
        }

    // ...bind it as an ODBC parameter for the stored procedure call...
    _tcscpy(szExec, _T("{call sp_bindsession(?)}"));
    sret = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
        SQL_VARCHAR, 255, 0, acBindToken, 256, NULL);
    if (sret != SQL_SUCCESS) {
        handle_odbc_err("SQLBindParameter",
            sret, 
            (DBINT)REMOTE_FAIL,
            hstmt,
            SQL_HANDLE_STMT,
            srvproc);
        return(XP_ERROR);
        }

    // ...and, using sp_bindsession, bind our session to the client's
    // session so that we share transaction space.
    sret = SQLExecDirect(hstmt, (SQLTCHAR*) szExec, SQL_NTS);
    if (!((sret == SQL_SUCCESS) ||(sret == SQL_SUCCESS_WITH_INFO))) {
        handle_odbc_err("SQLExecDirect",
            sret, 
            (DBINT) GETTABLE_ERROR,
            hstmt,
            SQL_HANDLE_STMT,
            srvproc);
        return(XP_ERROR);
        }
    SQLFreeStmt(hstmt, SQL_RESET_PARAMS);

	// SELECT the result set.
    _tcscpy(szExec, _T("SELECT * FROM  "));
    _tcscat(szExec, szTable);
    sret = SQLExecDirect(hstmt, (SQLTCHAR*) szExec, SQL_NTS);
    if (sret != SQL_SUCCESS) {
        handle_odbc_err("SQLExecDirect",
            sret, 
            (DBINT) GETTABLE_ERROR,
            hstmt,
            SQL_HANDLE_STMT,
            srvproc);
        return(XP_ERROR);
        }

    // Get the number of columns in the ODBC result set.
    SQLNumResultCols(hstmt, &nCols);

    ppData = (PBYTE*) malloc(nCols * sizeof(PBYTE));
    pIndicators = malloc(nCols * sizeof(SQLINTEGER));

    if (ppData == NULL || pIndicators == NULL)
        goto SAFE_EXIT;

    // Build the column description for this results set.
    for (nCol = 0; nCol < nCols; nCol++) {
        // Get the column name, length and data type.
		SQLColAttribute(hstmt, 
			(SQLSMALLINT) (nCol + 1), 
			SQL_DESC_NAME, 
			(SQLTCHAR*) acColumnName,   // returned column name
			MAXNAME,            // max length of rgbDesc buffer
			&cbAttr,            // number of bytes returned in rgbDesc
			&iNumAttr);

		SQLColAttribute(hstmt, 
			(SQLSMALLINT) (nCol + 1), 
			SQL_DESC_OCTET_LENGTH, 
			NULL, 
			0,              
			NULL,           
			&cbColData);     
	
        // Get the column's SQL Server data type, then reset the length
        // of the data retrieved as required.
        SQLColAttribute(hstmt, 
			(SQLSMALLINT) (nCol + 1), 
			SQL_CA_SS_COLUMN_SSTYPE, 
			NULL, 
			0,              
			NULL,           
			&eSQLType);

        // Over-write the column length returned by ODBC with the correct value
		//    to be used by ODS
		switch( eSQLType )  {
			case SQLMONEYN:
			case SQLMONEY:
                cbColData = sizeof(DBMONEY);
                break;

			case SQLDATETIMN:
			case SQLDATETIME:
				cbColData = sizeof(DBDATETIME);
				break;

			case SQLNUMERIC:
			case SQLDECIMAL:
				cbColData = sizeof(DBNUMERIC);
				break;


			case SQLMONEY4:
                cbColData = sizeof(DBMONEY4);
                break;

			case SQLDATETIM4:                       //smalldatetime
				cbColData = sizeof(DBDATETIM4);
				break;
		    }


		// Allocate memory for row data.
        if ((ppData[nCol] = (PBYTE) malloc(cbColData)) == NULL)
            goto SAFE_EXIT;

        memset(ppData[nCol], 0, cbColData);

		// Bind column 
		SQLBindCol(hstmt, 
			(SQLSMALLINT) (nCol + 1), 
			SQL_C_BINARY,           // No data conversion.
			ppData[nCol],           
			cbColData,              
			&(pIndicators[nCol]));
	
		
		// Prepare structure that will be sent via ODS back to
		// the caller of the extended procedure
		srv_describe(srvproc, 
			nCol + 1, 
			acColumnName, 
			SRV_NULLTERM,
			eSQLType,               // Dest data type.
			(DBINT) cbColData,      // Dest data length.
			eSQLType,               // Source data type.
			(DBINT) cbColData,      // Source data length.
			(PBYTE) NULL);
	    }

    // Initialize the row counter
    rows = 0;

    // Get each row of data from ODBC until there are no more rows
    while((sret = SQLFetch(hstmt)) != SQL_NO_DATA_FOUND) {
        if (!SQL_SUCCEEDED(sret)) {
            handle_odbc_err("SQLFetch",
                sret, 
                (DBINT) GETTABLE_ERROR,
                hstmt,
                SQL_HANDLE_STMT,
                srvproc);
            goto SAFE_EXIT;
            }

        // For each data field in the current row, fill the structure
        // that will be sent back to the caller.
        for (nCol = 0; nCol < nCols; nCol++) {
            cbColData = (pIndicators[nCol] == SQL_NULL_DATA ?
                0 : pIndicators[nCol]);
            srv_setcollen(srvproc, nCol+1, (int) cbColData);
            srv_setcoldata(srvproc, nCol+1, ppData[nCol]);
            }

        // Send the data row back to SQL Server via ODS.
        if (srv_sendrow(srvproc) == SUCCEED)
            rows++;
        }

    if (rows > 0)
		srv_senddone(srvproc, SRV_DONE_MORE | SRV_DONE_COUNT, (DBUSMALLINT)0, rows);
	else
		srv_senddone(srvproc, SRV_DONE_MORE, (DBUSMALLINT)0, (DBINT)0);


    // We got here successfully, let the client know.
    rcXP = XP_NOERROR;

SAFE_EXIT:
	// Free the data buffers.
    if (ppData != NULL)
        {
	    for (nCol = 0; nCol < nCols; nCol++)
		    free(ppData[nCol]);

        free(ppData);
        }
    if (pIndicators != NULL)
        free(pIndicators);
	
	// Free handles.
    if (hstmt != SQL_NULL_HSTMT)
	    SQLFreeStmt(hstmt, SQL_DROP);

    if (hdbc != SQL_NULL_HDBC)
        {
	    SQLDisconnect(hdbc);
	    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        }

    if (henv != SQL_NULL_HENV)
	    SQLFreeEnv(henv);

	// Revert back to SQL Server's user account.
    if( bImpersonated )
	    srv_revert_to_self(srvproc);

	
    return (rcXP);
}


// HANDLE_ODBC_ERR
//  This routine is called to send messages to clients when an ODBC
//  function returns what could be considered an error (e.g., SQL_ERROR,
//  SQL_INVALID_HANDLE).
//
// Parameters:
//  szODBCApi   - The name of the failing function.
//  srODBAPI    - The SQLRETURN of the failing function.
//  msgnum      - The ODS user message code.
//  herror      - The ODBC handle involved in the error.
//  htype       - The ODBC handle type.
//  srvproc     - Contains additional client information.
//
// Returns:
//      none
//
void handle_odbc_err(PSTR szODBCApi,
	SQLRETURN sret,
	DBINT msgnum,
	SQLHANDLE herror,
	SQLSMALLINT htype,
	SRV_PROC* srvproc)
{
    SQLTCHAR    szErrorMsg[SQL_MAX_MESSAGE_LENGTH + 1];
    SQLSMALLINT cbErrorMsg;
    SQLSMALLINT nRec = 1;

    // If sret is SQL_SUCCESS, return without doing anything
    if (sret == SQL_SUCCESS)
        return;

    while (
        SQLGetDiagField(htype, herror, nRec++, SQL_DIAG_MESSAGE_TEXT,
        szErrorMsg, SQL_MAX_MESSAGE_LENGTH, &cbErrorMsg) 
        == SQL_SUCCESS)
        {
        // If sret is SUCCESS_WITH_INFO, send as "message" (severity 
        // <= 10, we use zero), else send to client as "error"
        // (severity > 10, we use 11).
        srv_sendmsg(srvproc, 
            SRV_MSG_INFO, 
            msgnum, 
            (DBTINYINT) (sret == SQL_SUCCESS_WITH_INFO ? 0 : 11),
            (DBTINYINT) 1, 
            NULL, 
            0, 
            0, 
            szErrorMsg,
            SRV_NULLTERM);
        }
}

