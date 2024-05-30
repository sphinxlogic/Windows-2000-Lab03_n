/*--------------------------------------------------------------------*/
/*
/* ODBCSetupCons - ODBC Setup Console style program that 
/* version checks, copies and installs ODBC32.DLL and a custom
/* ODBC 32bit driver
/*
/* Copyright (c) 1997- 1998 by Microsoft
/*--------------------------------------------------------------------*/

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>
#include <winver.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "install.h"

static char	*DriverName 	="Bogus Driver";
static char *DataSourceName ="My Bogus Datasource";
static char *DriverDLL 		="smpldrv.dll";
static char *RedistPath		="..\\..\\redist32";
static char *DriverPath     ="..\\smpldrv\\ndebug32";		//Note, you must build smpldrv

void main()
{
	char	szRedist[_MAX_PATH], szDriver[_MAX_PATH];

	szRedist[0] = '\0';
	szDriver[0] = '\0';

	printf("Driver path (%s) ?", DriverPath);
	gets(szDriver);
	if (szDriver[0])
		DriverPath=szDriver;

	printf("Redist components path (%s) ?",RedistPath);

	gets(szRedist);
	if (szRedist[0])
		RedistPath=szRedist;



	if( ! Install() )
		printf( "ODBC Install Failed\n" );
	printf( "\nThe End" );
}

/* General error handler for installer functions */

BOOL ProcessErrorMessages( char * func )
{
	WORD	iError = 1;
	DWORD	pfErrorCode;
	char	lpszErrorMsg[301];
	WORD	cbErrorMsgMax = 300;
	WORD	pcbErrorMsg;
	int		rc;
	BOOL	func_rc = FALSE;

	do
	{
		lpszErrorMsg[0] = '\0';
		rc = SQLInstallerError(
			iError,
			& pfErrorCode,
			lpszErrorMsg,
			cbErrorMsgMax,
			& pcbErrorMsg );
		if( rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO )
		{
			printf( "%s in function %s", lpszErrorMsg, func );
			func_rc = TRUE;
		}
		iError++;
	}
	while( rc != SQL_NO_DATA );

	return func_rc;
}

BOOL Install() 
{
	char	szPath[301];
	WORD	cbPathMax = 300;
	WORD	cbPathOut;
	BOOL	rc;
	UINT	uVersionLength = 512;
	char	szExistingVersion[ 300 ];
	char	szNewVersion[ 300 ];
	DWORD	dwUsageCount;

	/* first, retrieve the path the driver should be installed to in szPath*/
	if( SQLInstallDriverManager( szPath, cbPathMax, & cbPathOut ) )
	{
		if(! CheckIfFileExists( szPath,RedistPath))
		{
			fprintf(stderr,"Can't find ODBC SDK in %s\n",RedistPath);
			exit(-10);
		}
		if( CheckIfFileExists( szPath, "odbc32.dll" ) )
		{
			char	szExistingFile[_MAX_PATH], szNewFile[_MAX_PATH];

			sprintf(szExistingFile,"%s\\odbc32.dll",szPath);
			sprintf(szNewFile,"%s\\odbc32.dll",RedistPath);
			
			GetFileVersion( szExistingFile, szExistingVersion, 300 );
			GetFileVersion( szNewFile, szNewVersion, 300 );

			fprintf(stderr,"Existing driver manager version: %s\n",szExistingVersion);
			fprintf(stderr,"SDK driver manager version:      %s\n",  szNewVersion);
			if( strcmp( szNewVersion, szExistingVersion ) > 0 )
			{
				if( ! SQLRemoveDriverManager( & dwUsageCount ) )
				{
					if( ProcessErrorMessages( "SQLGetInstalledDrivers" ) )
						return FALSE;
				}
				else
					CopyODBCCore( szPath );
			}
		}
		else
			CopyODBCCore( szPath );

			/* if not, install the driver */
		rc = InstallMyDriver();

		if( rc )
			/* after the driver is installed create
			the new DSN */
			AddMyDSN();
	}
	else
	{
		ProcessErrorMessages( "SQLInstallDriverManager" );
		return FALSE;
	}

	return TRUE;
}


BOOL InstallMyDriver()
{
	char 	szDriver[300];
	char 	szPathIn[301];
	char	szPathOut[301];
	WORD	cbPathOutMax = 300;
	WORD	cbPathOut;
	DWORD	dwUsageCount;
	int		x, y;

	/* the correct format of driver keywords are 
		"DriverName\0Driver=xxxxxx.DLL\0Setup=xxxxxx.DLL\0\0" */

	sprintf( szDriver, "Bogus Driver;Driver=%s;Setup=%s;", DriverDLL, DriverDLL );

	for( x = strlen( szDriver ), y = 0 ; y < x ; y++ )
	{
		if( szDriver[ y ] == ';' )
			szDriver[ y ] = '\0';
	}

	/* the szDriver array is filled in before calling SQLInstallDriverEx
	so that SQLInstallDriverEx will return where to install the driver in
	the szPathIn */

	SQLInstallDriverEx(
			szDriver,
			NULL,
			szPathIn,
			cbPathOutMax,
			& cbPathOut,
			ODBC_INSTALL_INQUIRY,
			& dwUsageCount );
 
	/* the correct format of driver keywords are 
		"DriverName\0Driver=c:\winnt\system32\xxxxxx.DLL\0
			Setup=c:\winnt\system32\xxxxxx.DLL\0\0" */

	sprintf( szDriver, 
		"Bogus Driver;Driver=%s\\%s;Setup=%s\\%s;", 
		szPathIn, 
		DriverDLL, 
		szPathIn, 
		DriverDLL );

	for( x = strlen( szDriver ), y = 0 ; y < x ; y++ )
	{
		if( szDriver[ y ] == ';' )
			szDriver[ y ] = '\0';
	}

	if( ! VersionCheckCopyFile( szPathIn, DriverPath, DriverDLL ) )
		if( ProcessErrorMessages( "SQLInstallDriverEx" ) )
			return FALSE;

	/* call SQLInstallDriverEx to install the driver in 
		the registry */
	if( ! SQLInstallDriverEx(
			szDriver,
			szPathIn,
			szPathOut,
			cbPathOutMax,
			& cbPathOut,
			ODBC_INSTALL_COMPLETE,
			& dwUsageCount ) )
		if( ProcessErrorMessages( "SQLInstallDriverEx" ) )
			return FALSE;

	/* call SQLConfigDriver to exercise the driver's setup
	functions - some drivers have their setup routines built in
	and others require a seperate dll */
	if( ! SQLConfigDriver(
		NULL,
		ODBC_CONFIG_DRIVER,
		DriverName,
		"CPTimeout=60\0\0",
		szPathOut,
		cbPathOutMax,
		& cbPathOut ) )
		ProcessErrorMessages( "SQLConfigDriver" );

	return TRUE;
}

BOOL AddMyDSN()
{
	char	*szDriver= DriverName;
	char	szAttributes[400];

	CreateAttributeString( szAttributes );

	/* I choose to remove the DSN if it already existed */
	SQLConfigDataSource( 
			NULL,
			ODBC_REMOVE_SYS_DSN,
			szDriver, 
			szAttributes );

	/* then create a new DSN */
	if( ! SQLConfigDataSource(
			NULL,
			ODBC_ADD_SYS_DSN,
			szDriver,
			szAttributes ) )
		if( ProcessErrorMessages( "SQLConfigDataSource" ) )
			return FALSE;

	return TRUE;
}

/*************************************************************
/	This function builds the keyword pair string required by
/	SQLConfigDataSource
/
/	Since the driver I used in my sample was really the SQL Server
/	driver the string is;
/
/	My Bogus Datasource\0Server=bottles\0Database=\0;UID=sa\0
/		PWD=\0UseProcForPrepare=Yes\0Trusted_Connection=\0AnsiNPW=Yes\0\0
/
/*************************************************************/
void CreateAttributeString( char * pszAttributes )
{
	int		x, y;

	sprintf( pszAttributes, 
		"DSN=%s;Server=bottles;Database=;UID=sa;PWD=;UseProcForPrepare=Yes;Trusted_Connection=;AnsiNPW=Yes;", 
		DataSourceName );

	for( x = strlen( pszAttributes ), y = 0 ; y < x ; y++ )
	{
		if( pszAttributes[ y ] == ';' )
			pszAttributes[ y ] = '\0';
	}
}

void CopyToODBCDir(char *szFile, char *szTargetDir)
{

	VersionCheckCopyFile(szTargetDir,RedistPath,szFile);

}

void CopyODBCCore( char * pszPath )
{
	char	szFromFile[ 200 ];
	char	szToFile[ 200 ];

	sprintf( szFromFile, "%s\\%s", RedistPath,"ds16gt.dll" );
	sprintf( szToFile, "%s\\ds16gt.dll", pszPath );
	CopyFile( szFromFile, szToFile, FALSE );

	CopyToODBCDir("ds16gt.dll",pszPath);
	CopyToODBCDir("odbc16gt.dll",pszPath);
	CopyToODBCDir("odbc32.dll",pszPath);
	CopyToODBCDir("odbc32gt.dll",pszPath);
	CopyToODBCDir("odbccp32.cpl",pszPath);
	CopyToODBCDir("odbccp32.dll",pszPath);
	CopyToODBCDir("odbccr32.dll",pszPath);
	CopyToODBCDir("odbccu32.dll",pszPath);
	CopyToODBCDir("odbcint.dll",pszPath);
	CopyToODBCDir("odbcinst.cnt",pszPath);
	CopyToODBCDir("odbcinst.hlp",pszPath);

}

/* The following functions are not required for ODBC driver and driver
manager installation.  They are for version checking and file copy of
DLL's, and they require NO part of the ODBC API. */

BOOL GetFileVersion( char * pFilePath, char * pVersion, UINT uMaxVersionLen )
{
	DWORD	dwHandle = 0;
	DWORD	dwVersionInfoSize;
	DWORD	dwError;
	PVOID	pFileInfo;
	PBYTE	pVersionInfo;
	PDWORD	pTranslation = NULL;
	UINT	uLength = 0;
	char	szString[512] = "";
	LPSTR	szVersionStr;

	dwVersionInfoSize = GetFileVersionInfoSize(
		pFilePath,	/* pointer to filename string */
		& dwHandle );	/* pointer to variable to receive zero */
	if( ! dwVersionInfoSize )
	{
		dwError = GetLastError();
		return FALSE;
	}

	pFileInfo = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwVersionInfoSize );
	pVersionInfo = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, dwVersionInfoSize );

	if( ! GetFileVersionInfo( pFilePath,	/* pointer to filename string */
		( DWORD ) dwHandle,	/* ignored */
		dwVersionInfoSize,	/* size of buffer */
		pFileInfo ) ) 	/* pointer to buffer to receive file-version info.*/
	{
		dwError = GetLastError();
		HeapFree( GetProcessHeap(), 0, pFileInfo );
		HeapFree( GetProcessHeap(), 0, pVersionInfo );
		return FALSE;
	}

	if( ! VerQueryValue( pFileInfo,	/* address of buffer for version resource */
		TEXT( "\\VarFileInfo\\Translation" ), /* address of value to retrieve */
		& pTranslation,	/* address of buffer for version pointer */
		& uLength )	/* address of version-value length buffer */
		)
	{
		dwError = GetLastError();
		HeapFree( GetProcessHeap(), 0, pFileInfo );
		HeapFree( GetProcessHeap(), 0, pVersionInfo );
		return FALSE;
	}
	
	wsprintf( szString, "\\StringFileInfo\\%04x%04x\\FileVersion",
		LOWORD( ( DWORD ) * pTranslation, ), HIWORD( ( DWORD ) * pTranslation ) );

	if( ! VerQueryValue( pFileInfo,	/* address of buffer for version resource */
		szString, 					/* Key that indicates the value we want to retrieve*/
		( PVOID * ) & szVersionStr,	/* address of buffer for version pointer */
		& uLength )					/* address of version-value length buffer */
		)
	{
		dwError = GetLastError();
		HeapFree( GetProcessHeap(), 0, pFileInfo );
		HeapFree( GetProcessHeap(), 0, pVersionInfo );
		return FALSE;
	}

	if( lstrlen( szVersionStr) >= ( int ) uMaxVersionLen )
		lstrcpyn( pVersion, szVersionStr, uMaxVersionLen - 1 );
	else
		lstrcpy( pVersion, szVersionStr);

	HeapFree( GetProcessHeap(), 0, pFileInfo );
	HeapFree( GetProcessHeap(), 0, pVersionInfo );

	return TRUE;
}

BOOL CheckIfFileExists( char * szFilePath, char * szFileName )
{
	DWORD	nBufferLength = 300;
	char	szBuffer[300];
	LPTSTR	lpFilePart;
	DWORD	rt;

	rt= SearchPath(
		szFilePath,	// address of search path 
		szFileName,	// address of filename 
		NULL, //LPCTSTR lpExtension,	// address of extension 
		nBufferLength,	// size, in characters, of buffer 
		szBuffer,	// address of buffer for found filename 
		& lpFilePart ); 	// address of pointer to file component 

	return rt;
}

/*********************************************************************
/	szOldPath is the "to path"
/	szNewPath is the "from path"
/	szFileName is the name of the file in the from path
/*********************************************************************/
BOOL VersionCheckCopyFile( char * szOldPath, char * szNewPath, char * szFileName )
{
	char	szOldFile[512];
	char	szNewFile[512];
	char	szOldFileVersion[ 512 ];
	char	szNewFileVersion[ 512 ];
	UINT	uVersionLength = 512;
	int		rt;

	sprintf( szOldFile, "%s\\%s", szOldPath, szFileName );
	sprintf( szNewFile, "%s\\%s", szNewPath, szFileName);

	if( CheckIfFileExists( szOldPath, szFileName ) )
	{

		if( GetFileVersion( szOldFile, szOldFileVersion, uVersionLength ) )
		{
			sprintf( szNewFile, "%s\\%s", szNewPath, szFileName );

			if( GetFileVersion( szNewFile, szNewFileVersion, uVersionLength ) )
			{
				rt = strcmp( szOldFileVersion, szNewFileVersion );
				if( rt < 0 )
				{
					fprintf(stderr,"Updating    file %14.14s\n",szFileName);
					if (!CopyFile( szNewFile, szOldFile, FALSE ))
					{
						fprintf(stderr,"Unable to copy %s from %s\n",szNewFile,szOldFile);
						exit(-10);
					}
				} else 
				{
					fprintf(stderr,
							"Not copying file %14.14s, it is up-to-date %s\n",
							szFileName,
							szOldFileVersion);
							
				}

				return TRUE;
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	else
	{
		fprintf(stderr,"Copying new file %14.14s\n", szFileName);
		if (!CopyFile( szNewFile, szOldFile, FALSE ))
		{
			fprintf(stderr,"Unable to copy %s to %s\n",szOldFile, szNewFile);
			exit(-10);
		}
	}
	return TRUE;
}
