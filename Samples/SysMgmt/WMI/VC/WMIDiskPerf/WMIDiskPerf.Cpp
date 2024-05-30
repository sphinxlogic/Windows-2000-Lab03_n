//***************************************************************************
//
//	Copyright (c) 1997-1999 Microsoft Corporation
//
//	File:  WMIDiskPerf.cpp
//
//	Description:
//		Connects to the WMI server and calls DiskPerfDetails( ) to
//		retrieve partition properties.
//
//	Part of :	WMIDiskPerf
//
//  History:	
//
//***************************************************************************


#include <wbemidl.h>
#include <lmcons.h>
#include <stdio.h>


void			DiskPerfDetails( IWbemServices * pIWbemServices );
BOOL			InitSecurity( void );
DWORD WINAPI	WaitThread( HANDLE hWait );


//==============================================================================
//	main( )
//==============================================================================
int main( int argc, char **argv )
{
	HRESULT	hr;
	DWORD	ThreadId, dwLen = UNCLEN;
	HANDLE	hWait, hThread;
	BSTR	pNamespace;
	TCHAR	szSysName[UNCLEN + 3];

	IWbemLocator	*pIWbemLocator  = NULL;
	IWbemServices	*pIWbemServices = NULL;

	if ( !SUCCEEDED( CoInitialize( NULL ) ) && !InitSecurity( ) ) 
	{
		printf( "COM stuff is hosed!\r\n" );

		return 0;
	}

	// Create an instance of the WbemLocator interface.
	if ( CoCreateInstance( CLSID_WbemLocator,
	                       NULL,
	                       CLSCTX_INPROC_SERVER,
	                       IID_IWbemLocator,
	                       (LPVOID *) &pIWbemLocator ) == S_OK )
	{

		lstrcpy( szSysName, "\\\\" );
		GetComputerName( szSysName + 2, &dwLen );
		pNamespace = SysAllocString( L"root\\WMI" );
		// Display connect message and start wait feedback thread
		printf( "Connecting to %s WMI server at ", szSysName );
		wprintf( L"%s...", pNamespace );

		// make a wait event and kick off wait thread
		hWait = CreateEvent( NULL, TRUE, FALSE, NULL );
		hThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE) WaitThread, hWait, 0, &ThreadId );

		// connect and get the IWbemServices pointer
		hr = pIWbemLocator->ConnectServer( pNamespace,
		                                   NULL,
		                                   NULL,
		                                   0L,
		                                   0L,
		                                   NULL,
		                                   NULL,
		                                   &pIWbemServices );

		// kill wait feedback thread
		SetEvent( hWait );
		// make sure thread is gone
		WaitForSingleObject( hThread, INFINITE );
		CloseHandle( hWait );
		SysFreeString( pNamespace );

		// See what WBEM/WMI says about DiskPerf
		if ( hr == WBEM_NO_ERROR )
		{	
			printf( "\nCool!  Connected with %s\n", szSysName );

			// done with locator object
			pIWbemLocator->Release( ); 

			// Switch the security level to IMPERSONATE so that provider(s)
			// will grant access to system-level objects, and so that
			// CALL authorization will be used.
			CoSetProxyBlanket( pIWbemServices,	// proxy
				RPC_C_AUTHN_WINNT,				// authentication service
				RPC_C_AUTHZ_NONE, 				// authorization service
				NULL,							// server principle name
				RPC_C_AUTHN_LEVEL_CALL,			// authentication level
				RPC_C_IMP_LEVEL_IMPERSONATE,	// impersonation level
				NULL,							// identity of the client
				EOAC_NONE );					// capability flags

			// go enumerate diskperf instances...
			DiskPerfDetails( pIWbemServices );
			pIWbemServices->Release( );
		}
		else
		{	
			printf( "\nBummer, failed to connect with %s, Error: 0x%8lX\n", szSysName, hr );
		}
	}
	else
	{	
		printf( "WMI services not present or unavailable!\n" );
	}

	CoUninitialize( );

	return 0;
}


//==============================================================================
//	WaitThread( HANDLE hWait )
//==============================================================================
DWORD WINAPI WaitThread( HANDLE hWait )
{
	while ( WaitForSingleObject( hWait, 300 ) == WAIT_TIMEOUT )
	{
		printf(".");
	}
	printf("\n");

	return 0;
}


//==============================================================================
//	InitSecurity( void )
//	Initialize COM security for DCOM services.
//==============================================================================
BOOL InitSecurity( void )
{
	// Adjust the security to allow client impersonation.
	HRESULT hres = CoInitializeSecurity
		(NULL, -1, NULL, NULL, 
		RPC_C_AUTHN_LEVEL_NONE, 
		RPC_C_IMP_LEVEL_IMPERSONATE, 
		NULL, 0, 0);

	return SUCCEEDED( hres );
}

