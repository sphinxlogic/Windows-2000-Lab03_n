// ************************************************************************ //
// dmoping.cpp
// 
// purpuse of this tool is to test the ability to instantiate a SQLDMO object
// and connect to the server indicated. Check which version of the server is 
// running and use the appropriate object model based on the SQL Serverversion.
//
// For SQL Server version 7.0 the SQLDMO is used and for SQL Server version 6.x
// the SQLOLE object model is used.
//
// usage dmoping [-S] [-U -P | -E] [-6 | -7] [-V] [-v] [-?]
//		-S server name, defaults to local server
//		-U user name, defaults to sa
//		-P password, defaults to "" (blank)
//		-E integrated security, defaults to FALSE
//		-6 force use of SQLOLE, defaults automatic based on version ping
//		-7 force use of SQLDMO, defaults automatic based on version ping
//		-V verbose mode, defaults to FALSE
//		-? help and usage information
// ************************************************************************ //

#include "dmoping.h"

// ************************************************************************ //
// CDmoPing constructor - set all defaults
// ************************************************************************ //
CDmoPing::CDmoPing()
:	m_pServer(NULL), 
	m_pUser(NULL),
	m_pPassword(NULL),
	m_bIntegratedSec(FALSE),
	m_bVerbose(FALSE),
	m_eSQLVersion(SQLDMOSQLVer_Unknown)
{

}


// ************************************************************************ //
// CDmoPing destructor
// ************************************************************************ //
CDmoPing::~CDmoPing()
{
	if (m_pServer)
	{
		delete [] m_pServer;
		m_pServer = NULL;
	}

	if (m_pUser)
	{
		delete [] m_pUser;
		m_pUser = NULL;
	}

	if (m_pPassword)
	{
		delete [] m_pPassword;
		m_pPassword = NULL;
	}
}

// ************************************************************************ //
// PargeArgs - poor mans command argument parser
// ************************************************************************ //
BOOL CDmoPing::Parse(INT argc, TCHAR* argv[])
{
	int	i = 1;

	while (i < argc)
	{
		if (! IsArgDelimiter(argv[i]) )
		{
			goto Error;
		}

		switch (argv[i][1])
		{
		// server
		case 'S':
			GetArg(i, m_pServer, argc, argv);
			break;

		// login ID
		case 'U':
			GetArg(i, m_pUser, argc, argv);
			break;

		// password.
		case 'P':
			GetArg(i, m_pPassword, argc, argv);
			break;
		
		// integrated security
		case 'E':
			m_bIntegratedSec = TRUE;
			break;

		// force 6.x SQLOLE usage
		case '6':
			m_eSQLVersion = SQLDMOSQLVer_65;
			break;
		
		// force 7.0 SQLDMO
		case '7':
			m_eSQLVersion = SQLDMOSQLVer_70;
			break;

		// version
		case 'v':
			break;

		// verbose mode
		case 'V':
			m_bVerbose = TRUE;
			break;

		case '?':
			goto Usage;

		default:
			goto Error;
		
		}
		i++;
	}

	return(TRUE);

Error:
	_tprintf(TEXT("error dmoping argument (%d) %s\n\n"), i, argv[i] );

Usage:
	_tprintf(TEXT("usage dmoping [-S] [-U -P | -E] [-6 | -7] [-V] [-v] [-?] \n"));
	_tprintf(TEXT("  -S server name, defaults to local server \n"));
	_tprintf(TEXT("  -U user name, defaults to sa \n"));
	_tprintf(TEXT("  -P password, defaults to \"\" (blank) \n"));
	_tprintf(TEXT("  -E integrated security, defaults to FALSE\n"));
	_tprintf(TEXT("  -6 force use of SQLOLE, defaults automatic based on version ping\n"));
	_tprintf(TEXT("  -7 force use of SQLDMO, defaults automatic based on version ping\n"));
	_tprintf(TEXT("  -V verbose mode, defaults to FALSE\n"));
	_tprintf(TEXT("  -? help and usage information\n"));

	return(FALSE);
}

// ************************************************************************ //
// GetVersion - uses SQLDMO to determine the SQL Server version 
//				using pSQLServer->PingSQLServerVersion
// ************************************************************************ //
BOOL CDmoPing::GetVersion()
{
	BOOL fRet = FALSE;
	LPSQLDMOSERVER	pSQLServer = NULL; 


	if FAILED(CoCreateInstance(CLSID_SQLDMOServer, NULL, CLSCTX_INPROC_SERVER,
		IID_ISQLDMOServer, (LPVOID*)&pSQLServer))
	{
		return FALSE;
	}

	if SUCCEEDED(pSQLServer->PingSQLServerVersion(&m_eSQLVersion, m_pServer, m_pUser, m_pPassword))
	{
		fRet = TRUE;
	}

	if (pSQLServer)
	{
		pSQLServer->Release();
		pSQLServer = NULL;
	}

	return fRet;
}

// ************************************************************************ //
// Ping - instantiate an SQLOLE or SQLDMO object based on the m_eSQLVersion
//		  connect to the server and retrieve the version information of
//        SQLOLE/SQLDMO and the underlaying database layer DB-Library/ODBC
// ************************************************************************ //
BOOL CDmoPing::Ping()
{
	if (SQLDMOSQLVer_70 == m_eSQLVersion)
	{
		LPSQLDMOSERVER pSQLServer;

		if FAILED(CoCreateInstance(CLSID_SQLDMOServer, NULL, CLSCTX_INPROC_SERVER,
			IID_ISQLDMOServer, (LPVOID*)&pSQLServer))
		{
			DisplayError();
			return(FALSE);
		}

		if (m_bIntegratedSec)
		{
			pSQLServer->SetLoginSecure(TRUE);
		}

		if FAILED(pSQLServer->Connect(m_pServer, m_pUser, m_pPassword) )
		{
			DisplayError();
			delete pSQLServer;
			return(FALSE);
		}

		BSTR strVersion;
		pSQLServer->GetVersionString(&strVersion);
		_tprintf(_T("%s\n"), strVersion);
		SysFreeString(strVersion);

		BSTR strODBCVersion;
		LONG lSQLDMOVersion;
		LONG lSQLDMOVersionMajor;
		LONG lSQLDMOVersionMinor;

		LPSQLDMOAPPLICATION pApplication;
		
		pSQLServer->GetApplication(&pApplication);
		pApplication->GetVersionBuild(&lSQLDMOVersion);
		pApplication->GetVersionMajor(&lSQLDMOVersionMajor);
		pApplication->GetVersionMinor(&lSQLDMOVersionMinor);
		pApplication->GetODBCVersionString(&strODBCVersion);

		_tprintf(_T("SQL-DMO version %d.%d.%d\n"), 
			lSQLDMOVersion, lSQLDMOVersionMajor, lSQLDMOVersionMinor);
		_tprintf(_T("ODBC version %s\n"), strODBCVersion);
		
		SysFreeString(strODBCVersion);

		pSQLServer->DisConnect();
		
		delete pSQLServer;

	}
	else if (SQLDMOSQLVer_65 == m_eSQLVersion || SQLDMOSQLVer_60 == m_eSQLVersion)
	{
		LPSQLOLESERVER pSQLServer;

		if FAILED(CoCreateInstance(CLSID_SQLOLEServer, NULL, CLSCTX_INPROC_SERVER,
			IID_ISQLOLEServer, (LPVOID*)&pSQLServer))
		{
			DisplayError();
			return(FALSE);
		}

		if (m_bIntegratedSec)
		{
			pSQLServer->SetLoginSecure(TRUE);
		}

		if FAILED(pSQLServer->Connect(m_pServer, m_pUser, m_pPassword) )
		{
			DisplayError();
			delete pSQLServer;
			return(FALSE);
		}

		BSTR strVersion;
		pSQLServer->GetVersionString(&strVersion);
		_tprintf(_T("%s\n"), strVersion);
		SysFreeString(strVersion);

		BSTR strDBLibraryVersion;
		LONG lSQLOLEVersion;
		LONG lSQLOLEVersionMajor;
		LONG lSQLOLEVersionMinor;

		LPSQLOLEAPPLICATION pApplication;
		
		pSQLServer->GetApplication(&pApplication);
		pApplication->GetVersionBuild(&lSQLOLEVersion);
		pApplication->GetVersionMajor(&lSQLOLEVersionMajor);
		pApplication->GetVersionMinor(&lSQLOLEVersionMinor);
		pApplication->GetDBLibraryVersionString(&strDBLibraryVersion);

		_tprintf(_T("SQL-OLE version %d.%d.%d\n"), 
			lSQLOLEVersion, lSQLOLEVersionMajor, lSQLOLEVersionMinor);
		_tprintf(_T("DB-Library version %s\n"), strDBLibraryVersion);
		
		SysFreeString(strDBLibraryVersion);

		pSQLServer->DisConnect();
		
		delete pSQLServer;
	}
	else
	{
		// no SQLDMO or SQLOLE version available for this version
		//
		return(FALSE);
	}

	return(TRUE);

}

// ************************************************************************ //
// main
// ************************************************************************ //
INT	_tmain(INT argc, TCHAR** argv, TCHAR** envp)
{
	int	iExitStatus = 1;	// assume failure.

	try
	{
		// Initialize COM
		//
		if FAILED(CoInitialize (NULL))
		{
			return (iExitStatus);
		}

		CDmoPing* pPing = new CDmoPing();

		if (FALSE == pPing->Parse(argc, argv) )
		{
			return (iExitStatus);
		}

		if (SQLDMOSQLVer_Unknown == pPing->GetSQLVersion() )
		{
			pPing->GetVersion();
		}

		pPing->Ping();

		delete pPing;
			
		CoUninitialize();
		
		iExitStatus = 0;	// Success
	}
	catch(...)
	{
		_tprintf(TEXT("error dmoping unhandled exception (%d)\n"), GetLastError() );
	}

	return (iExitStatus);
}

// **********************************************************************
// display error information
// **********************************************************************
VOID DisplayError()
{
	LPERRORINFO	pErrorInfo = NULL;
	BSTR		strDescription, strSource;

	GetErrorInfo(0,&pErrorInfo);

	pErrorInfo->GetDescription(&strDescription);
	pErrorInfo->GetSource(&strSource);

	_tprintf(TEXT("Error: %s\n"),strSource);
	_tprintf(TEXT("%s\n"),strDescription);

	pErrorInfo->Release();
	
	SysFreeString(strDescription);
	SysFreeString(strSource);
	
	return;
}

// **********************************************************************
// IsArgDelimiter - determine if the first character is a delimiter
// **********************************************************************
BOOL IsArgDelimiter(LPTSTR lpArg)
{
	if (lpArg[0] == '/' || lpArg[0] == '-')
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}


// **********************************************************************
// GetArg - return command line argument in string buffer
// **********************************************************************
BOOL GetArg(INT& i, LPTSTR& lpValue, INT argc, TCHAR* argv[])
{
	LPTSTR lpStr = lpValue;

	if (argv[i][2] == '\0')
	{
		// still in range
		if ((i + 1) < argc) 
		{
			// next starts with Arg Delimiter, so this value is NULL
			if (IsArgDelimiter(argv[i + 1]) )
			{
				lpStr = NULL;
			}
			// use the next Arg as the value
			else
			{
				size_t nSize = _tcslen(argv[i + 1]);
				if (lpStr)
				{
					delete [] lpStr;
				}
				lpStr = new TCHAR[nSize + sizeof(TCHAR)];
				_tcscpy(lpStr, argv[i + 1]);
				i++;
			}
		}
		else
		{
			lpStr = NULL;
		}
	}
	else
	{
		size_t nSize = _tcslen(argv[i]) - 2;
		if (lpStr)
		{
			delete [] lpStr;
		}
		lpStr = new TCHAR[nSize + sizeof(TCHAR)];
		_tcscpy(lpStr, argv[i] + 2);
	}

	lpValue = lpStr;

	return(TRUE);
}
