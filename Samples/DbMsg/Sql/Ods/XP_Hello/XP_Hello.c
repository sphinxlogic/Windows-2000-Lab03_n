// This is an example of an extended procedure DLL built with Open Data
// Services. The function within the DLL can be invoked by using the
// extended stored procedures support in SQL Server.
//
// For more information on Open Data Services refer to the Microsoft Open 
// Data Services Programmer's Reference.
//
// xp_hello stored procedure sets an output parameter and sends a result set.
//
// The Transact-SQL script xp_hello.sql installs and exercises the extended
// stored procedure.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <srv.h>
#include <time.h>




// Macros -- return codes
#define XP_NOERROR      0
#define XP_ERROR        1

#define MAX_SERVER_ERROR 20000
#define XP_HELLO_ERROR MAX_SERVER_ERROR+1

void printUsage (SRV_PROC* pSrvProc);
void printError (SRV_PROC *pSrvProc, CHAR* szErrorMsg);


// It is highly recommended that all Microsoft® SQL Server (7.0 
// and greater) extended stored procedure DLLs implement and export 
// __GetXpVersion. For more information see SQL Server 
// Books Online
ULONG __GetXpVersion()

{
    return ODS_VERSION;
}


SRVRETCODE xp_hello
    (
    SRV_PROC* pSrvProc
    )
    {
	char		szText[15] = "Hello World!";
    BYTE        bType;
    long        cbMaxLen;
    long        cbActualLen;
    BOOL        fNull;

#ifdef _DEBUG
    // In a debug build, look up the data type name for assistance.
    DBCHAR*     pdbcDataType;
    int         cbDataType;
#endif


    // Count up the number of input parameters.  There should only be one.
    if (srv_rpcparams(pSrvProc) != 1)
		{
        // Send error message and return
        //
        printUsage (pSrvProc);
        return (XP_ERROR);
		}

	// Use srv_paraminfo to get data type and length information. 
    if (srv_paraminfo(pSrvProc, 1, &bType, &cbMaxLen, &cbActualLen,
        NULL, &fNull) == FAIL)
        {
        printError (pSrvProc, "srv_paraminfo failed...");
 		return (XP_ERROR);    
		}

	// Make sure first parameter is a return (OUTPUT) parameter
	if ((srv_paramstatus(pSrvProc, 1) & SRV_PARAMRETURN) == FAIL)
		{
        printUsage (pSrvProc);
        return (XP_ERROR);    
		}

	// Make sure first parameter is of char or varchar datatype
	if (bType != SRVBIGVARCHAR && bType != SRVBIGCHAR)
		{
        printUsage (pSrvProc);
		return (XP_ERROR);    
		}

    // Make sure first paramter is large enough to hold data
	if (cbMaxLen < (long)strlen(szText))
		{
        printError (pSrvProc, "output param max. length should be bigger");
        return (XP_ERROR);    
		}

    // Describe the results set 
//#define METHOD1
#ifdef METHOD1
    srv_describe(pSrvProc, 1, "Column 1", SRV_NULLTERM, bType,
            cbMaxLen, bType, strlen(szText), szText);
#else
    srv_describe(pSrvProc, 1, "Column 1", SRV_NULLTERM, bType,
            cbMaxLen, bType, 0, NULL);

    // Set the column's length
    if (srv_setcollen(pSrvProc, 1, strlen(szText)) == FAIL)
        {
        printError (pSrvProc, "srv_setcollen failed...");
		return (XP_ERROR);    
		}

    // Set the column's data
    if (srv_setcoldata(pSrvProc, 1, szText) == FAIL)
        {
        printError (pSrvProc, "srv_setcoldata failed...");
		return (XP_ERROR);    
		}

#endif //METHOD1



#ifdef _DEBUG
    // A debugging aid. Get the name of the data type of the parameter.
    pdbcDataType = srv_symbol(SRV_DATATYPE, (int) bType, &cbDataType);
#endif

    
    // Send a row to client
    if (srv_sendrow(pSrvProc) == FAIL)
        {
        printError (pSrvProc, "srv_sendrow failed...");
		return (XP_ERROR);    
		}

	// Set the output parameter
	if (FAIL == srv_paramsetoutput(pSrvProc, 1, szText, strlen(szText), FALSE))
        {
        printError (pSrvProc, "srv_paramsetoutput failed...");
		return (XP_ERROR);    
		}
		

    srv_senddone(pSrvProc, (SRV_DONE_COUNT | SRV_DONE_MORE), 0, 1);

    return (XP_NOERROR);
}

// send XP usage info to client
void printUsage (SRV_PROC *pSrvProc)
{
    // usage: exec xp_hello <@param1 output>
    // Example:
    // declare @txt varchar(33)
    // exec xp_hello @txt OUTPUT
    // select @txt

    srv_sendmsg(pSrvProc, SRV_MSG_ERROR, XP_HELLO_ERROR, SRV_INFO, 1,
            NULL, 0, (DBUSMALLINT) __LINE__, 
            "Usage: exec xp_hello <@param1 output>",
            SRV_NULLTERM);
    srv_senddone(pSrvProc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);

}

// send szErrorMsg to client
void printError (SRV_PROC *pSrvProc, CHAR* szErrorMsg)
{
    srv_sendmsg(pSrvProc, SRV_MSG_ERROR, XP_HELLO_ERROR, SRV_INFO, 1,
            NULL, 0, (DBUSMALLINT) __LINE__, 
            szErrorMsg,
            SRV_NULLTERM);

    srv_senddone(pSrvProc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);

}
