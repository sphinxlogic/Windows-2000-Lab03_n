// This is an example of an extended procedure DLL built with Open Data
// Services. The functions within the DLL can be invoked by using the extended
// stored procedures support in SQL Server.  To register the functions 
// and allow all users to use them run the ISQL script XP_DBLIB.SQL.
//
// For further information on Open Data Services refer to the Microsoft Open 
// Data Services Programmer's Reference.
//
// The extended procedure implemented in this DLL is:
//
// XP_GETTABLE_DBLIB -- Used to show the creation of a new connection to SQL
// Server using DBLIB that is bound to the initial client connection; retrieves 
// all rows from the table <szTable>, which is passed as an input parameter				
#define DBNTWIN32
		
#include <windows.h>

#include <sqlfront.h>
#include <sqldb.h>

#include <srv.h>

// Miscellaneous defines
#define XP_NOERROR                      0
#define XP_ERROR                        1
#define MAX_BINDTOKEN                   256

// Defined in odbcss.h.
#ifndef SQL_MAX_SQLSERVERNAME
#define SQL_MAX_SQLSERVERNAME           128
#endif

// Extended procedure error codes
#define REMOTE_FAIL             4002
#define SRV_MAXERROR            50000
#define GETTABLE_ERROR          SRV_MAXERROR + 1
#define GETTABLE_MSG            SRV_MAXERROR + 2

int err_handler();
int msg_handler();

// It is highly recommended that all Microsoft® SQL Server (7.0 
// and greater) extended stored procedure DLLs implement and export 
// __GetXpVersion. For more information see SQL Server 
// Books Online
ULONG __GetXpVersion()

{
    return ODS_VERSION;
}



// XP_GETTABLE_DBLIB
//    Returns the result of the SQL statement
//		select * from <table>
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//    Returns messages and/or a result set to client. 
RETCODE xp_gettable_dblib(srvproc)
SRV_PROC *srvproc;
{
    DBPROCESS*  dbproc;         // DBPROCESS handle for the new connection
    LOGINREC*   loginrec;

    int         bImpersonated;

    // Data from the srvproc.
    DBCHAR      szTable[SQL_MAX_SQLSERVERNAME * 3];
    char        szBindToken[MAX_BINDTOKEN];

    short       nCols;          // Data columns returned     
    int         nCol;           // Index variable            
    DBINT       nRowsFetched;   // Number of rows sent       
    RETCODE     rc;             // Value returned from DB-Library calls      

    // Check number of parameters.
    if ( srv_rpcparams(srvproc) != 1) {
        // Send error message and return.
        srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR,
            SRV_INFO, (DBTINYINT) 0,
            NULL, 0, 0,
            "Error executing extended stored procedure: Invalid number of parameters.",
            SRV_NULLTERM);

        // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
        // result set of an Extended Stored Procedure.
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        return(XP_ERROR);
        }

    // Check parameter for correct type.
    if (srv_paramtype(srvproc, 1) != SRVVARCHAR) {
        // Send error message and return.
        srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR,
            SRV_INFO, (DBTINYINT) 0,
            NULL, 0, 0,
            "Error executing extended stored procedure: Invalid parameter type.",
            SRV_NULLTERM);
        // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
        // result set of an Extended Stored Procedure.
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
        return(XP_ERROR);
        }

    // Terminate parameter string with NULL.
    memcpy(szTable, srv_paramdata(srvproc, 1), srv_paramlen(srvproc, 1));
    szTable[srv_paramlen(srvproc, 1)] = '\0';

    // Get a loginrec and register our error and message handlers.
    loginrec = dblogin();
    dbprocerrhandle(loginrec, (DBERRHANDLE_PROC) err_handler);
    dbprocmsghandle(loginrec, (DBMSGHANDLE_PROC) msg_handler);

    // Check for integrated security.
    if (strcmp(srv_pfield(srvproc, SRV_LSECURE, NULL), "TRUE") == 0) {
        // Client has accessed using some form of integrated security
        // Impersonate client and set DBSETLSECURE flag
        bImpersonated = srv_impersonate_client( srvproc );
        DBSETLSECURE(loginrec);
        }
    else {
        // Set the user name, password, and application name for the remote
        DBSETLUSER( loginrec, srv_pfield(srvproc, SRV_USER, NULL) );
        DBSETLPWD( loginrec, srv_pfield(srvproc, SRV_PWD, NULL) );
        }

    DBSETLAPP (loginrec, "xp_gettable_dblib");

    // Since the servername parameter is set to NULL, the connection will be
    // opened to the local DBMS.
    dbproc = dbopen (loginrec, NULL);

    dbsetuserdata (dbproc, (VOID*) srvproc);

    // Bind to the clients connection for shared transaction space.
    srv_getbindtoken (srvproc, szBindToken);
    dbfcmd (dbproc, "exec sp_bindsession \'%s\'", szBindToken);
    dbsqlexec (dbproc);

    // Execute the SELECT * FROM table.
    dbfcmd (dbproc, "select * from %s ", szTable);
    rc = dbsqlexec(dbproc);

    // Process the results.
    while ((rc = dbresults (dbproc)) != NO_MORE_RESULTS) {
        // How many data columns are in the row?
        nCols = dbnumcols (dbproc);

        // Build the row description for the client return.
        for (nCol = 1; nCol <= nCols; nCol++) {
            // Call srv_describe for each column that will be sent back via ODS
            // to the caller of the extended procedure
            srv_describe (srvproc, nCol, (DBCHAR *)dbcolname (dbproc, nCol), SRV_NULLTERM,
                (DBINT)dbcoltype (dbproc, nCol), dbcollen (dbproc, nCol),
                (DBINT)dbcoltype (dbproc, nCol), dbcollen (dbproc, nCol),
                (BYTE *)NULL);
            }

        nRowsFetched = 0;  // Initialize a counter for the row number.

        while (dbnextrow (dbproc) != NO_MORE_ROWS) {
            // For each data field in the current row, fill the structure that will
            // be sent back to the caller of the extended procedure
            for (nCol = 1; nCol <= nCols; nCol++) {
                srv_setcollen (srvproc, nCol, (short)dbdatlen (dbproc, nCol));
                srv_setcoldata (srvproc, nCol, dbdata(dbproc, nCol));
                }

            // Send the data row back to SQL Server via ODS
            if (srv_sendrow (srvproc) == SUCCEED)
		        nRowsFetched++;                        // Go to the next row. 
            }
        }


    // Send the final done packet for the execution of the command  
    // batch. The previous batch was one that might have returned   
    // rows, so set the DONE status accordingly.                    
    if (nRowsFetched > 0)
        srv_senddone (srvproc, SRV_DONE_COUNT | SRV_DONE_MORE,
            (DBUSMALLINT) 0, nRowsFetched);
    else 
        srv_senddone (srvproc, SRV_DONE_MORE, (DBUSMALLINT) 0, (DBINT) 0);

    // Close the connection to SQL Server. 
    dbclose( dbproc );
    dbfreelogin( loginrec );

    // Revert back to SQL Server's user account
    if( bImpersonated )
        srv_revert_to_self(srvproc);

    return(XP_NOERROR);
}


int err_handler(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS	*dbproc;
int			severity;
int			dberr;
int			oserr;
char		*dberrstr;
char		*oserrstr;
{
    SRV_PROC*       srvproc = (SRV_PROC*) dbgetuserdata(dbproc);

    if (srvproc == NULL)
        return 0;

    srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT) GETTABLE_MSG,
        (DBTINYINT)severity, (DBTINYINT)0, NULL, 0, 0, dberrstr,
        SRV_NULLTERM);

    if ((dbproc == NULL) || (DBDEAD(dbproc)))
        return(INT_EXIT);

    return(INT_CANCEL);
}


int msg_handler(dbproc, msgno, msgstate, severity, msgtext)
DBPROCESS	*dbproc;
DBINT		msgno;
int			msgstate;
int			severity;
char		*msgtext;
{
    SRV_PROC*       srvproc = (SRV_PROC*) dbgetuserdata(dbproc);

    if (srvproc == NULL)
        return 0;

    if (severity < 10) {    
        // If informational message....
        srv_sendmsg(srvproc, SRV_MSG_INFO, msgno, (DBTINYINT)severity,
            (DBTINYINT)msgstate, NULL, 0, 0, (DBCHAR *)msgtext, SRV_NULLTERM);
        return(0);
        }

    // Trap login fail message
    if (msgno == REMOTE_FAIL) {
        // Send a message to the client that
        // the remote connection failed.
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)msgno, (DBTINYINT)severity,
            (DBTINYINT)msgstate, NULL, 0, 0,
            "Login to remote DBMS failed (dbopen).", SRV_NULLTERM);
        return(0);
        }

     // Must be an error message....
    srv_sendmsg(srvproc, SRV_MSG_ERROR, msgno, (DBTINYINT)severity,
        (DBTINYINT)msgstate, NULL, 0, 0, (DBCHAR *)msgtext, SRV_NULLTERM);

    return(0);
}



