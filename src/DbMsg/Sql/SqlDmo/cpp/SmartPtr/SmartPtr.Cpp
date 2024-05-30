// **********************************************************************
// Smartptr -	SQL-DMO smartpointer sample application uses
//				the built-in Visual C 5.0 _comp_ptr_t support. 
//				If prefered, adapt to use CComPtr or CComQIPtr
//				(VC 5.0 and later)
//
//				the _com_error calls ->Release automatically when it
//				goes out of scope to clean itself up. 
//				there is no need to call delete or release.
// **********************************************************************

#define STRICT					// Strict type checking.
#define WIN32_LEAN_AND_MEAN		// Do not include the world.
#define INC_OLE2				// Include OLE/COM files

#include <windows.h>
#include <stdio.h>
#include <comdef.h>             // Compiler support for _bstr_t

// The #import statement is locale specific. Change the path to import
// from the locale specific .rll file installed.
#import "c:\mssql7\binn\resources\1033\sqldmo.rll" no_namespace

// **********************************************************************
// Function declarations.
// **********************************************************************
void	vDisplayError(_com_error & pCE);
BOOL	bSetDefaults(_SQLServerPtr & spSQLServer);
BOOL	bConnect(_SQLServerPtr & spSQLServer);
void	vDisconnect(_SQLServerPtr & spSQLServer);
void	vDoQuery(_SQLServerPtr & spSQLServer, LPCTSTR strQuery);
void	vDisplayResults(QueryResultsPtr & spQueryResults);

// **********************************************************************
// Macros.
// **********************************************************************
#define _MAX_COL		25
#define _MAX_COL_FMT    "%-25s "

#define _SERVER			"."     // Local server
#define _USER			"sa"
#define _PWD			""
#define _QUERYSTMT		"SELECT LastName, FirstName, HireDate FROM " \
                        " Northwind.dbo.Employees" 

// **********************************************************************
// main()
// **********************************************************************
void main(void)
{
	printf("\n\nSQL-DMO Smart Pointer Sample\n");


	HRESULT hr;
	if SUCCEEDED(hr = CoInitialize(NULL) )
	{
		// Use the interface appropriate for LPSQLDMOSERVER.
		try
		{
			_SQLServerPtr spSQLServer;

			if (SUCCEEDED(spSQLServer.CreateInstance(__uuidof(SQLServer))))
			{
				try
				{
					if (TRUE == bSetDefaults(spSQLServer))
					{
						vDoQuery(spSQLServer, _QUERYSTMT);
					}

					// Because the spSQLServer was created in main, it
					// will not go out of scope until the end of main.
					//
					// However, this is after the OleUninitilize is called
					// and causes an error.
					//
					// For this special case, call the .Release to
					// clean up the pointer and do the work.
					spSQLServer.Release();
				}
				catch(_com_error pCE)
				{
					vDisplayError(pCE);
					spSQLServer.Release();     //    Free the interface.
				}
			}
			else
			{
				printf("\nUnable to create the SQLServer object.");
			}
		}
		catch(_com_error pCE)
		{
			vDisplayError(pCE);
		}

		CoUninitialize();
	}
	else
	{
		printf("\nCall to CoInitialize failed.");
	}
	
	printf("\n");

}

// **********************************************************************
// vDisplayError
//
// Display error information.
// **********************************************************************
void vDisplayError(_com_error & pCE)
{
	//    Assuming ANSI build at this time.
	printf( "\n%s Error: %ld\r\n"
			"%s\r\n"
            "%s\r\n",
            (char*)pCE.Source(),
                   pCE.Error(),
            (char*)pCE.Description(),
            (char*)pCE.ErrorMessage());
}

// **********************************************************************
// bSetDefaults
//
// Accepts the current address so the RefCount does not need to be 
// touched. There is no reason to increment it on entry and then 
// decrement it on exit, just to be doing it.
// **********************************************************************
BOOL bSetDefaults(_SQLServerPtr & spSQLServer)
{
	BOOL bRC = FALSE;

    printf("\nSetting SQL Server object properties.");

    try
	{
		spSQLServer->PutLoginTimeout(10);
        spSQLServer->PutApplicationName("SmartPointers");
        spSQLServer->PutHostName("Test");
        spSQLServer->PutNetPacketSize(1024);

        bRC = TRUE;
	}
    catch(_com_error pCE)
	{
		vDisplayError(pCE);
	}
    return bRC;
}


// **********************************************************************
// bConnect
//
// Connect to the SQL Server.
// **********************************************************************
BOOL bConnect(_SQLServerPtr & spSQLServer)
{
	BOOL bRC = FALSE;

	printf("\nAttempting to connect to %s as %s", _SERVER, _USER);

    try
	{
		spSQLServer->Connect(_SERVER, _USER, _PWD);

		bRC = TRUE;
	}
	catch(_com_error pCE)
	{
		vDisplayError(pCE);
	}
	return bRC;
}


// **********************************************************************
// vDisconnect
//
// Disconnect from the SQL Server.
// **********************************************************************
void vDisconnect(_SQLServerPtr & spSQLServer)
{
    printf("\nDisconnecting from %s", _SERVER);

	try
	{
		spSQLServer->Close();
	}
	catch(_com_error pCE)
	{
		vDisplayError(pCE);
	}
}

// **********************************************************************
// vDoQuery
//
// Execute query capturing generated result sets in a QueryResults
// object.
// **********************************************************************
void vDoQuery(_SQLServerPtr & spSQLServer, LPCTSTR strQuery)
{
	QueryResultsPtr spQueryResults;

	if (TRUE == bConnect(spSQLServer))
	{
		printf("\nExecuting %s\n", strQuery);

		try
		{
			spQueryResults = spSQLServer->ExecuteWithResults(strQuery);

			vDisplayResults(spQueryResults);
		}
		catch(_com_error pCE)
		{
			vDisplayError(pCE);
		}

        vDisconnect(spSQLServer);

	}
}

// **********************************************************************
// vDisplayResults
//
// Print result set(s) information and contents.
// **********************************************************************
void vDisplayResults(QueryResultsPtr & spQueryResults)
{
	long	lMaxColLen = 0;
    char    strDisplayData[_MAX_COL +1] = "";
    _bstr_t bstrColName;
    _bstr_t bstrRowInfo;

    try
	{
		// Loop through the results sets.
		for (long lSet = 1; lSet <= spQueryResults->GetResultSets(); lSet++)
		{
			spQueryResults->PutCurrentResultSet(lSet);
			printf("\n >>> Result set #%ld\n", lSet);

			// Print the column headers.
			for (long lCols = 1; lCols <= spQueryResults->GetColumns(); lCols++)
			{
				// You do not need to call SysFreeString when using the smart
                // BSTR pointer (_bstr_t). The copy operator of the _bstr_t
                // performs a free on any prior value and then handles the
                // new data, preventing a memory leak when used in this loop.
				//
				// For complete details, see the definition of the _bstr_t
                // copy coperator in COMUTIL.H.
				bstrColName = spQueryResults->GetColumnName(lCols);

				// Assuming ANSI build for sample so casting as char*.
				strncpy(strDisplayData, (char *)bstrColName, _MAX_COL);
				printf(_MAX_COL_FMT, strDisplayData);
			}
			
			printf("\n");

			// Display the data.
			for (long lRows = 1; lRows <= spQueryResults->GetRows(); lRows++)
			{
				for (long lCols = 1; lCols <= spQueryResults->GetColumns(); lCols++)
				{
					bstrRowInfo = spQueryResults->GetColumnString(lRows, lCols);

					strncpy(strDisplayData, (char *)bstrRowInfo, _MAX_COL);
					printf(_MAX_COL_FMT, strDisplayData);
				}
				// End of row.
				printf("\n");
			}

            printf("\nRows processed (%ld)", spQueryResults->GetRows());
		
		} // End of FOR loop processing a result set.
	}
	catch(_com_error pCE)
	{
		vDisplayError(pCE);
	}
}
