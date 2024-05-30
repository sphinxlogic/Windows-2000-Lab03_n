/*
** init.c - This module contains the DLL initialization functions
**
**  Copyright (c) 1997 - 1998 By Microsoft Corp.
*/

#include "headers.h"

DWORD	*pdwGlobalTraceVariable;
DWORD	*pdwGlobalVistaVariable;
HANDLE	g_hOdbcDM;

CRITICAL_SECTION	g_csWrite;

/* libmain() - Std DLL entry point, called from libentry.asm */
BOOL  WINAPI DllMain(HANDLE hInst,
					DWORD ul_reason_being_called,
					LPVOID lpReserved)
{
    switch (ul_reason_being_called) 
	{
		case DLL_PROCESS_ATTACH:

			// We do not need the thread attach/detach calls
		 	
			DisableThreadLibraryCalls(hInst);
			g_hOdbcDM = LoadLibraryA("odbc32.dll");
			if (g_hOdbcDM)
			{
				pdwGlobalTraceVariable = (DWORD *) GetProcAddress(g_hOdbcDM, "ODBCSharedTraceFlag");
				pdwGlobalVistaVariable = (DWORD *) GetProcAddress(g_hOdbcDM, "ODBCSharedVSFlag");
			}
			InitializeCriticalSection(&g_csWrite);
			break;

    	case DLL_PROCESS_DETACH:
			FreeLibrary(g_hOdbcDM);
			break;

	/* no need for these cases
    	case DLL_THREAD_ATTACH:
    	case DLL_THREAD_DETACH:
	*/
		default:
			break;

	} /* switch */

    return 1;
    UNREFERENCED_PARAMETER(lpReserved);
}

