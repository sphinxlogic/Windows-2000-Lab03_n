/************************************************************************************/
/*																					*/
/* Module: TPSTART.C																*/
/*																					*/
/* Description:																		*/
/*	Win/NT TP loader for SNA Server.												*/
/*																					*/
/* Copyrigth (C) Microsoft Corporation 1994											*/
/*																					*/
/************************************************************************************/

#define NOSOUND
#define NOATOM
#define NOCLIBBOARD
#define NOMETAFILE
#define NOPROFILER
#define NOKANJI
#define WIN32_LEAN_AND_MEAN

#ifdef i386
#ifndef _X86_
#define	_X86_
#endif
#endif

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "snaver.h"
#include "tpstart.h"

#define REALTOBASED(base,rptr) (DWORD)((DWORD)rptr-(DWORD)base)
#define BASEDTOREAL(base,bptr) (LPVOID)((DWORD)base+(DWORD)bptr)

#ifdef TRACING
VOID WriteTraceLine( LPSTR lpstrFormatString, ... );
VOID BuildHeader( LPSTR lpHeader );

BOOL	bTrace=FALSE;
HFILE	hTraceFile=HFILE_ERROR;
int		iTraceLevel=10;
char	szTraceBuffer[256];
char	szTraceFile[256];
DWORD	dwFileSize=500000;

CRITICAL_SECTION csTraceCritical;
#define TRACE(x,y) if(bTrace && x>iTraceLevel) {\
                     WriteTraceLine y;\
				   };
#else
#define TRACE(x,y)
#endif

LONG APIENTRY MainWndProc( HWND, UINT, UINT, LONG );
int APIENTRY WinMain( HANDLE, HANDLE, LPSTR, int );

BOOL InitTPLoader( HANDLE, int );
BOOL CreateGlobalObjects( VOID );
BOOL DeleteGlobalObjects( VOID );
LPSECURITY_ATTRIBUTES CreateSecurityAttribute( DWORD );
BOOL InitSharedMemory( UCHAR *, BOOL );
DWORD Loader( LPVOID );
VOID ParseCmdLine( LPSTR );

struct {
  ACL       GeneralACL;             /* access control list                   */
  ACCESS_ALLOWED_ACE  GeneralAccessAce;    /* not accessed directly          */
  SID       GeneralAccessSID;       /* SID to allow access by all            */
} GeneralSecurity;

PISID     pGeneralAccessSID;        /* pointer to SID to allow access by all */
SID_IDENTIFIER_AUTHORITY  GeneralSIDAuthority = SECURITY_WORLD_SID_AUTHORITY;
SECURITY_DESCRIPTOR       GeneralSecurityDescriptor;
SECURITY_ATTRIBUTES       GeneralSecurityAttribs =
                          {
                            sizeof(SECURITY_ATTRIBUTES),  /* required value  */
                            &GeneralSecurityDescriptor,
                            FALSE                         /* no inherit      */
                          };
CHAR *lpszAutoTPs="System\\CurrentControlSet\\Services\\Snabase\\Parameters\\TPs";
CHAR *lpszTpParams="\\Parameters";

HANDLE	hInst;
HWND	hMainWnd;
HANDLE  hShrMem, hThread, hMutex, hEvent;
LPVOID	lpShrBase;
DWORD	dwQueueSize=DEFAULT_TPSENTRIES;
BOOL	bNoIcon=FALSE;

/**PROC+**********************************************************************/
/*                                                                           */
/*  FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)                            */
/*                                                                           */
/*  PURPOSE: Calls initialization function, processes message loop           */
/*                                                                           */
/**PROC-**********************************************************************/

int APIENTRY WinMain( HANDLE hInstance,
					  HANDLE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow )
{
	MSG msg;
	msg.wParam = FALSE;

#ifdef TRACING
	ParseCmdLine( lpCmdLine );
#endif
	if( InitTPLoader( hInstance, nCmdShow ) )
	{
		/* TP Loader initialized OK, enter the message loop */
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

    }
	/* Release all allocated resources before terminating */
	DeleteGlobalObjects();

	return( msg.wParam );
}


/**PROC+**********************************************************************/
/*                                                                           */
/*  FUNCTION:  InitTPLoader( HANDLE, int )                                   */
/*                                                                           */
/*  PURPOSE: Initializes window data, registers window class,                */
/*           saves instance handle and creates main window                   */
/*                                                                           */
/**PROC-**********************************************************************/

BOOL InitTPLoader( HANDLE hInstance, int nCmdShow )
{
	WNDCLASS  wc;

	/* Create global objects (shared memory, mutex and event) */
	TRACE(1,("Initializing SNA Server TP Loader"));
	if( !CreateGlobalObjects() )
	{
		return( FALSE );
	}

	wc.style         = CS_DBLCLKS;
	wc.lpfnWndProc   = MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon( hInstance, "TPSTART");
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = TPCLASSNAME;

	if( !RegisterClass( &wc ) )
	{
		return( FALSE );
	}

	hInst = hInstance;
	hMainWnd = CreateWindow( TPCLASSNAME,
							 "SnaTPStart",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 CW_USEDEFAULT,
							 NULL,
							 NULL,
							 hInstance,
							 NULL );

	if( !hMainWnd )
	{
		return (FALSE);
	}

	if( !bNoIcon )
	{
		ShowWindow( hMainWnd, SW_SHOWMINNOACTIVE );
		UpdateWindow( hMainWnd );
	}
	else
	{
		ShowWindow( hMainWnd, SW_HIDE );
	}
	return (TRUE);
}

/**PROC+**********************************************************************/
/*                                                                           */
/*  FUNCTION: MainWndProc(HWND, UINT, UINT, LONG)                            */
/*                                                                           */
/**PROC-**********************************************************************/

LONG APIENTRY MainWndProc( HWND hWnd, UINT message, UINT wParam, LONG lParam)
{
	switch (message)
	{

	case WM_CLOSE:
		{
		char	szCaption[64];
		char	szText[256];

			LoadString( hInst, IDS_WMCLOSE_CAPTION, szCaption, sizeof(szCaption) );
			LoadString( hInst, IDS_WMCLOSE_TEXT, szText, sizeof(szText) );

			switch( MessageBox( hWnd,
								szText,
								szCaption,
								MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2 ) )
			{
			case IDYES:
				DestroyWindow( hWnd );
			}
			return	0;
		}

	case WM_DESTROY:
		TRACE(4,("Got WM_DESTROY Message"));
		PostQuitMessage( 0 );
		break;

	case WM_QUERYOPEN:
		break;

	default:
		return( DefWindowProc( hWnd, message, wParam, lParam ) );
	}
	return (0L);
}


/**PROC+**********************************************************************/
/*                                                                           */
/*  FUNCTION: CreateGlobalObjects( VOID )		                             */
/*                                                                           */
/**PROC-**********************************************************************/

BOOL CreateGlobalObjects()
{
	LPSECURITY_ATTRIBUTES lpSA;
	DWORD dwRet, idThread;

	lpSA = CreateSecurityAttribute( GENERIC_ALL );
	if( lpSA != NULL )
	{
		TRACE(1,("Create security attributes OK, lpSa=%p", lpSA));
		hShrMem = CreateFileMapping( (HANDLE)0xFfFfFfFf, lpSA,
									 (PAGE_READWRITE | SEC_COMMIT), 0,
									 (sizeof(TPSHDR)+dwQueueSize*sizeof(TPSENTRY)),
									 "SnaServer_TpStart_ShrMem" );

		/* Don't make any NT calls before saving the last error code, */
		/* otherwise you loose the CreateFileMapping() error code	  */
		if( hShrMem != NULL )
		{
			dwRet = GetLastError();
			TRACE(4,("Queue Size %d entries", dwQueueSize));

			lpShrBase = MapViewOfFile( hShrMem, FILE_MAP_WRITE, 0, 0, 0 );
			if( lpShrBase != NULL )
			{
				if( dwRet != ERROR_ALREADY_EXISTS )
				{
					TRACE(4,("Created Shared Memory, Base=%p", lpShrBase));

					/* Create a named event and a named mutex */
					hEvent = CreateEvent( lpSA, FALSE, FALSE, "SnaServer_TpStart_Event" );
					hMutex = CreateMutex( lpSA, FALSE, "SnaServer_TpStart_Mutex" );
				}
				else if( ((TPSHDR *)lpShrBase)->bLoaderRunning == FALSE )
				{
					/* Open the event and mutex */
					TRACE(4,("Shared memory already exists, Base=%p", lpShrBase));
					hEvent = OpenEvent( (EVENT_MODIFY_STATE | SYNCHRONIZE), FALSE,
										"SnaServer_TpStart_Event" );
					hMutex = OpenMutex( SYNCHRONIZE, FALSE, "SnaServer_TpStart_Mutex" );
				}
				else // TPSTART already running, exit
				{
					TRACE(9,("SnaTPStart already running, terminating"));
					UnmapViewOfFile( lpShrBase );
					lpShrBase = (LPVOID)0;
					return( FALSE );
				}

				/* Create the loader thread */
				hThread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)Loader,
										(LPVOID)0, 0, &idThread );

				if( hMutex != NULL && hEvent != NULL && hThread != NULL )
				{
					TRACE(4,("Initializing Shared Memory"));
					WaitForSingleObject( hMutex, INFINITE );
					_try {
						InitSharedMemory( lpShrBase, (dwRet == ERROR_ALREADY_EXISTS) );
					}
					_finally {
						ReleaseMutex( hMutex );
					}
					return( TRUE );
				}
				else
				{
					TRACE(9,("Error, hMutex %d, hEvent %d, hThread %d",
							 hMutex, hEvent, hThread));
				}
			}
			else
			{
				TRACE(9,("MapViewOfFile() failed, Error %d", GetLastError()));
			}
		}
		else
		{
			TRACE(9,("CreateFileMapping() failed, Error=%d", GetLastError()));
		}
	}
	return( FALSE );
}

/**PROC+**********************************************************************/
/*                                                                           */
/* Name:         CreateSecurityAttribute                                     */
/*                                                                           */
/* Purpose:      Returns address of security attribute to allow access by    */
/*               all. Creates it if necessary.                               */
/*                                                                           */
/* Operation:    Initialize security descriptor                              */
/*                                                                           */
/* Note:         Cannot trace in this routine as it is called during init    */
/*                                                                           */
/**PROC-**********************************************************************/

LPSECURITY_ATTRIBUTES CreateSecurityAttribute( DWORD dwAccessMask )
{
	DWORD rc=0;

	/* Initialize security descriptor */
	if( InitializeSecurityDescriptor( &GeneralSecurityDescriptor,
                                      SECURITY_DESCRIPTOR_REVISION1 ) )
    {
		/* Initialize Access Control List in security descriptor */
		if( InitializeAcl( &GeneralSecurity.GeneralACL,
						   (DWORD)(sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) +
								   sizeof(SID)), ACL_REVISION2 ) )
		{
			/* allocate memory for SID with 1 subauthority */
			if( (pGeneralAccessSID = LocalAlloc( LPTR,
											 GetSidLengthRequired(1))) != NULL )
			{
				/* Initialize the new SID structure (1 subauthority) */
				if( InitializeSid( pGeneralAccessSID,
								   &GeneralSIDAuthority,
								   (BYTE)1 ) )   /* 1 sub authority     */
				{
					/* Get pointer to the subauthority within the SID structure */
					/* and set it to WORLD sub authority (RID)					*/
					*(GetSidSubAuthority(pGeneralAccessSID, 1L)) = SECURITY_WORLD_RID;

					/* Add an ACE to permit the specified access to the world SID */
					if( AddAccessAllowedAce( &GeneralSecurity.GeneralACL,
											 ACL_REVISION2,
											 dwAccessMask,
											 pGeneralAccessSID ) )
					{
						/* Verify that the ACL is OK */
						if( !IsValidAcl(&GeneralSecurity.GeneralACL ) )
						{
							rc = GetLastError();
							return( NULL );
						}

						/* Set the DACL in the security descriptor */
						if( !SetSecurityDescriptorDacl( &GeneralSecurityDescriptor,
														TRUE,
														&GeneralSecurity.GeneralACL,
														FALSE ) )
						{
							rc = GetLastError();
							return( NULL );
						}

						/* Verify that the security descriptor is valid */
						if( !IsValidSecurityDescriptor(&GeneralSecurityDescriptor) )
						{
							rc = GetLastError();
							return( NULL );
						}
						else
						{
							/* Finally return pointer to the security attribute */
							return( &GeneralSecurityAttribs );
						}
					}
				}
			}
		}
	}
	return( NULL );
}

/**PROC+**********************************************************************/
/*                                                                           */
/*  FUNCTION: CreateGlobalObjects( VOID )		                             */
/*                                                                           */
/**PROC-**********************************************************************/

BOOL DeleteGlobalObjects()
{
	TRACE(2,("Deleting all Global Objects"));
	if( hMutex != NULL )
	{
		WaitForSingleObject( hMutex, INFINITE );
	}

	/* Close all open handles that are not NULL */
	_try {
		if( hEvent != NULL )
		{
			CloseHandle( hEvent );
			hEvent = NULL;
			Sleep( 100 );
		}
		if( lpShrBase != NULL )
		{
			((TPSHDR *)lpShrBase)->bLoaderRunning = FALSE;
			UnmapViewOfFile( lpShrBase );
			lpShrBase = (LPVOID)0;
		}
		if( hShrMem != NULL )
		{
			CloseHandle( hShrMem );
			hShrMem = NULL;
		}
	}

	_finally {
		if( hMutex != NULL )
		{
			ReleaseMutex( hMutex );
			CloseHandle( hMutex );
			hMutex = NULL;
		}
	}

	if( pGeneralAccessSID != NULL )
	{
		LocalFree( (HLOCAL)pGeneralAccessSID );
		pGeneralAccessSID = NULL;
	}

#ifdef TRACING
	if( hTraceFile != HFILE_ERROR )
	{
		TRACE(4,("SnaTPStart terminated."));
		_lclose( hTraceFile );
		hTraceFile = HFILE_ERROR;
		DeleteCriticalSection( &csTraceCritical );
		bTrace = FALSE;
	}
#endif

	return( TRUE );
}

/**PROC+**********************************************************************/
/*                                                                           */
/*  FUNCTION: InitSharedMemory( UCHAR *lpBase )		                         */
/*																			 */
/*	NOTES:																	 */
/*	The caller must own the shared memory mutex 							 */
/*                                                                           */
/**PROC-**********************************************************************/

BOOL InitSharedMemory( UCHAR *lpBase, BOOL bExists )
{
	TPSHDR *pHdr = (TPSHDR *)lpBase;
	TPSENTRY *pEntry;
	DWORD i;

	/* First clear the shared memory */
	if( bExists )
	{
		dwQueueSize = pHdr->dwQSize;
		TRACE(8,("Queue Size now %d", dwQueueSize));
	}
	memset( lpBase, '\0', sizeof(TPSHDR)+dwQueueSize*sizeof(TPSENTRY) );
	pHdr->dwQSize = dwQueueSize;

	/* Build the free list with based pointers */
	pEntry = (TPSENTRY *)(pHdr + 1);

	pHdr->bpFreeList = REALTOBASED(lpBase, pEntry);
	for( i = 0; i < dwQueueSize; i++ )
	{
		pEntry->bpNext = REALTOBASED(lpBase,(pEntry+1));
		pEntry++;
	}

	/* Clear the next field in the last entry */ 
	pEntry->bpNext = 0;

	/* No entries in pending list */
	pHdr->bpStartHead = 0;
	pHdr->bpStartTail = 0;

	/* The TP loader is running */
	pHdr->bLoaderRunning = TRUE;
	return(TRUE);
}

/**THREAD+********************************************************************/
/*                                                                           */
/*	NAME: Loader( LPVOID lpVoid )											 */
/*                                                                           */
/*	PURPOSE:																 */
/*		This thread is the thread that does all the work. It waits for the	 */
/*		TP load event to be signaled and then starts the specified program	 */
/*		with CreateProcess().												 */
/*																			 */
/**THREAD+********************************************************************/

DWORD Loader( LPVOID lpVoid )
{
	DWORD dwObject, dwRet;
	HKEY hTpKey=(HKEY)NULL;
	HKEY hKey;
	TPSENTRY *pEntry;
	TPSHDR *pHdr;
	char szPath[512];
	char szCmdLine[1024];
	char szTpParamsKey[64];
	char szYes[8];
	BOOL bWin16;
	DWORD dwLength, dwType, dwCreateFlags;
	STARTUPINFO siStartInfo;
	PROCESS_INFORMATION piProcInfo;

	TRACE(2,("Loader Thread Started"));

	/* Init some locals needed in CreateProcess() */
	memset( &siStartInfo, '\0', sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);

	/* copy the shared memory header address into a local */
	pHdr = (TPSHDR *)lpShrBase;

	/* Loop here until the TP event handle is closed */
	do
	{
		dwObject = WaitForSingleObject( hEvent, INFINITE );

		/* We need to load a new process(es) */
		if( dwObject == WAIT_OBJECT_0 )
		{
			TRACE(2,("WaitForSingleObject() completed OK"));
			/* Loop here until the pending list is empty */
			do
			{
				pEntry = (TPSENTRY *)0;

				/* Lock the shared memory and take the first entry from the */
				/* pending list and update the head and tail if needed.		*/
				if( !WaitForSingleObject( hMutex, INFINITE ) )
				{
					_try {
						if( pHdr->bpStartHead != 0 )
						{
							pEntry = (TPSENTRY *)BASEDTOREAL(lpShrBase,pHdr->bpStartHead);
							pHdr->bpStartHead = pEntry->bpNext;
							if( pHdr->bpStartHead == 0 )
							{
								pHdr->bpStartTail = 0;
							}
						}
					}
					_finally {
						ReleaseMutex( hMutex );
					}
				}

				/* If we got an entry then get the pathname and command 	*/
				/* line parameters from the registry database. The entry    */
				/* contains the KeyName under ..\SnaBase\Parameters\TPs	*/
				TRACE(2,("Got TP Entry %p", pEntry));
				if( pEntry != (TPSENTRY *)0 )
				{
					TRACE(4,("TP Name %s", pEntry->szRegKey));
					/* If we haven't opened the ..\SnaBase\Parameters\TPs */
					/* do it now.											  */
					if( hTpKey == NULL )
					{
						TRACE(4,("Open Registry Key %s", lpszAutoTPs));
						dwRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
											  lpszAutoTPs, 0, KEY_READ, &hTpKey );
					}

					if( hTpKey != NULL )
					{
						/* Open the TP Parameters key */
						strcpy( szTpParamsKey, pEntry->szRegKey );
						strcat( szTpParamsKey, lpszTpParams );
						dwRet = RegOpenKeyEx( hTpKey, szTpParamsKey, 0, KEY_READ, &hKey );
						if( hKey != NULL )
						{
							/* read the pathname and command line args */
							szPath[0] = szCmdLine[0] = '\0';
							dwLength = sizeof(szPath);
							RegQueryValueEx( hKey, "PathName", 0,
											 &dwType, szPath, &dwLength );

							/* The first command line arg is the exe file name */
							strcpy( szCmdLine, szPath );
							strcat( szCmdLine, " " );
							dwLength = sizeof(szCmdLine) - strlen(szCmdLine);
							RegQueryValueEx( hKey, "Parameters", 0,
											 &dwType, szCmdLine+strlen(szCmdLine), &dwLength );

							dwLength = sizeof(szYes);
							bWin16 = FALSE;
							dwCreateFlags = (DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP | NORMAL_PRIORITY_CLASS);

							if( RegQueryValueEx( hKey, "Win16App", 0,
											 	 &dwType, szYes, &dwLength ) == ERROR_SUCCESS )
							{
								if( !stricmp( szYes, "YES" ) )
								{
									TRACE(4,("TP %s is a 16 bit application", pEntry->szRegKey));

									//
									// Set the win16 flag and reset the DETACHED_PROCESS flag
									// in the create flags. If the DETACHED_PROCESS flag is set
									// and the NTVDM is not running the CreateProcess will fail
									// with error 5, ACCESS_DENIED.
									//
									bWin16 = TRUE;
									dwCreateFlags &= ~DETACHED_PROCESS;

									//
									// Check it the 16 bit app needs to be started in its own VDM
									//
									dwLength = sizeof(szYes);
									if( RegQueryValueEx( hKey, "SeparateWoWVDM", 0,
											 	 &dwType, szYes, &dwLength ) == ERROR_SUCCESS )
									{
										if( !stricmp( szYes, "YES" ) )
										{
											dwCreateFlags |= CREATE_SEPARATE_WOW_VDM;
											TRACE(4,("Use separate WOW VDM"));
										}
									}
								}
							}

							/* Create a new process, if it succeeds close the */
							/* process and thread handles 					  */
							/* The path name must be NULL when starting 16 bit apps */
							TRACE(4,("Start Program %s", szPath));
							TRACE(4,("Command Line args %s", szCmdLine));
							if( CreateProcess( (bWin16 ? NULL : szPath), szCmdLine, NULL, NULL, FALSE,
											   dwCreateFlags, NULL, NULL,
											   &siStartInfo, &piProcInfo ) )
							{
								TRACE(4,("Pragram started Ok, Process Id %d", piProcInfo.dwProcessId));
								CloseHandle( piProcInfo.hProcess );
								CloseHandle( piProcInfo.hThread );
							}
							else
							{
								TRACE(9,("CreateProcess() failed, Error %d",GetLastError()));
							}
							RegCloseKey( hKey );
							hKey = 0;
						}
						else
						{
							TRACE(9,("OpenKey %s failed, Error %d", pEntry->szRegKey, dwRet));
						}
					}
					else
					{
						TRACE(9,("OpenKey failed, Error %d", dwRet));
					}

					/* Put the entry back into free list */
					if( !WaitForSingleObject( hMutex, INFINITE ) )
					{
						_try {
							pEntry->bpNext = pHdr->bpFreeList;
							pHdr->bpFreeList = REALTOBASED(lpShrBase,pEntry);
						}
						_finally {
							ReleaseMutex( hMutex );
						}
					}
				}
			} while( pEntry != (TPSENTRY *)0 );
			TRACE(2,("No more TPs to start"));
		}
	} while( dwObject == WAIT_OBJECT_0 );

	/* Wait failed, exit and terminate the process too */
	TRACE(4,("WaitForSingleObject() failed, Error %d", GetLastError()));
	if( hTpKey != NULL )
	{
		RegCloseKey( hTpKey );
		hTpKey = 0;
	}

	PostMessage( hMainWnd, WM_CLOSE, 0, 0 );
	CloseHandle( hThread );
	hThread = 0;

	TRACE(4,("Loader Thread Terminating"));
	return( 0 );
}


/**PROC+**********************************************************************/
/*                                                                           */
/* NAME: VOID ParseCmdLine( LPSTR lpCmdLine )								 */
/*                                                                           */
/* Parses the command line parameters. Following two parameters are 		 */
/* supported in the non-trace version.										 */
/*                                                                           */
/* /QSIZE=<number>	- Size of the pending queue, MIN=16,MAX=256,DEFAULT=64	 */
/* /HIDE			- Hides the icon, DEFAULT=Show Icon						 */
/*					  (If you kill a "hidden" tpstart you can't restart a 	 */
/*					   new copy before you stop the snabase)				 */ 
/* 																			 */
/* The trace version supports the following additional parameters:			 */
/* /TRACE			- Enables tracing, DEFAULT=no tracing					 */
/* /FILE=<filename>	- Trace file name, DEFAULT=none (tracing disabled)		 */
/* /FSIZE=<number>	- Max size of the trace file, MIN=10000,MAX=0xFFFFFFFF,  */
/*					  DEFAULT=500K. When the trace file grows to the max it	 */
/*					  is renamed to <filename.bak>.							 */
/* /LEVEL=<number>	- Trace level, smaller numbers mean more detailed 		 */
/*					  tracing, MIN=0,MAX=10,DEFAULT=10 (no tracing)			 */
/**PROC+**********************************************************************/

VOID ParseCmdLine( LPSTR lpCmdLine )
{
	LPSTR lpParamX;
#ifdef TRACING
	LPSTR lpTraceFile, lpStr;
	OFSTRUCT of;
	char ch;
#endif

	lpParamX = strchr( lpCmdLine, '/' );
	while( lpParamX != NULL )
	{
		if( !strnicmp( lpParamX, "/QSIZE", 6 ) )
		{
			dwQueueSize = (DWORD)atoi( lpParamX+7 );
			if( dwQueueSize < MIN_TPSENTRIES )
			{
				dwQueueSize = MIN_TPSENTRIES;
			}
			else if( dwQueueSize > MAX_TPSENTRIES )
			{
				dwQueueSize = MAX_TPSENTRIES;
			}
		}
		else if( !strnicmp( lpParamX, "/HIDE", 5 ) )
		{
			bNoIcon = TRUE;
		}
#ifdef TRACING
		else if( !strnicmp( lpParamX, "/TRACE", 6 ) )
		{
			bTrace = TRUE;
			InitializeCriticalSection( &csTraceCritical );
		}
		else if( !strnicmp( lpParamX, "/FILE", 5 ) )
		{
			lpTraceFile = strchr( lpParamX, '=' );
			if( lpTraceFile != NULL )
			{
				lpTraceFile++;
				lpStr = lpTraceFile;
				while( *lpStr > ' ' ) lpStr++;
				ch = *lpStr;
				*lpStr = '\0';
				hTraceFile = OpenFile( lpTraceFile, &of, (OF_CREATE | OF_WRITE) );
				strcpy( szTraceFile, lpTraceFile );
				*lpStr = ch;
			}
		}
		else if( !strnicmp( lpParamX, "/LEVEL", 6 ) )
		{
			iTraceLevel = atoi( lpParamX+7 );
			if( iTraceLevel < 0 )
			{
				iTraceLevel = 0;
			}
			else if( iTraceLevel > 10 )
			{
				iTraceLevel = 10;
			}
		}
		else if( !strnicmp( lpParamX, "/FSIZE", 6 ) )
		{
			dwFileSize = (DWORD)atoi( lpParamX+7 );
			if( dwFileSize < 10000 )
			{
				dwFileSize = 10000;
			}
		}
#endif
		lpParamX = strchr( lpParamX+1, '/' );
	}

#ifdef TRACING
	if( bTrace && hTraceFile == HFILE_ERROR )
	{
		bTrace = FALSE;
		DeleteCriticalSection( &csTraceCritical );
	}
	if( !bTrace && hTraceFile != HFILE_ERROR )
	{
		_lclose( hTraceFile );
		hTraceFile = HFILE_ERROR;
	}
	TRACE(9,(">-----------------------------------------------------<"));
#endif
}


#ifdef TRACING
VOID WriteTraceLine( LPSTR lpstrFormatString, ... )
{
	va_list vaArgs;
	char szHeader[64];
	static DWORD dwCurrentSize=0;
	OFSTRUCT of;
	int iLen;
	LPSTR lpDot;

	va_start(vaArgs,lpstrFormatString);
    if( lpstrFormatString != NULL && hTraceFile != HFILE_ERROR )
	{
		EnterCriticalSection( &csTraceCritical );

		memset( szHeader, 0, sizeof(szHeader) );
		BuildHeader( szHeader );

		/* use _vsnprintf() to format the parameters (see Microsoft C/C++ */
		/* on-line docs for _vsnprintf documentation)					  */
		_vsnprintf( szTraceBuffer, sizeof(szTraceBuffer), lpstrFormatString, vaArgs );
		strcat( szTraceBuffer, "\n" );

		iLen = strlen(szHeader);
		_lwrite( hTraceFile, szHeader, iLen );
		dwCurrentSize += iLen;

		iLen = strlen(szTraceBuffer);
		_lwrite( hTraceFile, szTraceBuffer, iLen );
		dwCurrentSize += iLen;

		if( dwCurrentSize > dwFileSize )
		{
			_lclose( hTraceFile );
			strcpy( szTraceBuffer, szTraceFile );
			lpDot = strchr( szTraceBuffer, '.' );
			if( lpDot != NULL )
			{
				strcpy( lpDot+1, "bak" );
			}
			else
			{
				strcat( szTraceBuffer, ".bak" );
			}
			MoveFileEx( szTraceFile, szTraceBuffer, MOVEFILE_REPLACE_EXISTING );
			hTraceFile = OpenFile( szTraceFile, &of, (OF_CREATE | OF_WRITE) );
			dwCurrentSize = 0;
		}
		LeaveCriticalSection( &csTraceCritical );
	}
	va_end(vaArgs);
}

VOID BuildHeader( LPSTR lpHeader )
{
	DWORD dwThread;
	time_t t;
	char *lpTime;

	*lpHeader = '|';
	time( &t );
	lpTime = ctime( &t );
	strncpy( lpHeader+1, lpTime+4, 15 );
	strcat( lpHeader, "|" );

	dwThread = GetCurrentThreadId();
	wsprintf( lpHeader+strlen(lpHeader), "%04X", dwThread );
	strcat( lpHeader, "|  " );
}
#endif
