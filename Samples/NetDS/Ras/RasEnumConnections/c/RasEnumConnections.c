/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 1998 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/*
*		RasEnumConnections.c
*		
*		Usage:
*		RasEnumConnections
*
*		RAS API's used:
*				RasEnumConnections
*
*		Created by:  Mazahir Poonawala
*		Date:		 02/18/98
*		Modified by: Mazahir Poonawala
*		Date:		 03/15/99
*/

#include <windows.h>
#include <stdio.h>
#include <ras.h>
#include <raserror.h>

int main(void)
{
	DWORD		nRet;
	LPRASCONN	lpRasConn;
	LPRASCONN   lpTempRasConn;
	DWORD		lpcb = sizeof(RASCONN);
	DWORD		lpcConnections;
	DWORD		i;
	HRASCONN	hRasConn;

	// Allocate buffer with default value
	lpRasConn = (LPRASCONN) GlobalAlloc(GPTR, sizeof(RASCONN));
	if (lpRasConn == NULL)
	{
		printf("GlobalAlloc failed.\n");
		return -1;
	}
	lpRasConn->dwSize = sizeof(RASCONN);

	nRet = RasEnumConnections(lpRasConn, &lpcb, &lpcConnections);

	switch (nRet) // Check whether RasEnumConnections succeeded
	{
	case ERROR_BUFFER_TOO_SMALL: // Since initial buffer allocation was small.
		GlobalFree(lpRasConn); // Free initial buffer
		// And reassign a new buffer with the value returned in lpcb
		lpRasConn = (LPRASCONN) GlobalAlloc(GPTR, lpcb);
		if (lpRasConn == NULL)
		{
			printf("GlobalAlloc failed.\n");
			return -1;
		}
		
		lpRasConn->dwSize = sizeof(RASCONN);
		// Again call RasEnumConnections
		nRet = RasEnumConnections(lpRasConn, &lpcb, &lpcConnections);
		if (nRet != 0)
		{ // RasEnumConnections failed
			printf("RasEnumConnections failed: Error = %d\n", nRet);
			GlobalFree(lpRasConn);
			return -1;
		}
		else
		{ // RasEnumConnections succeeded. Print the results.
			printf("The following RAS connections are currently active\n\n");
			lpTempRasConn = lpRasConn;
			for (i = 0; i < lpcConnections; i++)
			{
				printf("Size: %d\n", lpTempRasConn->dwSize);
				printf("Entry name: %s\n", lpTempRasConn->szEntryName);
				printf("Device name: %s\n", lpTempRasConn->szDeviceName);
				hRasConn = lpTempRasConn->hrasconn;
				lpTempRasConn++;
			}
		}
		break;
	
	case 0: // RasEnumConnections succeeded with intial buffer allocation.
		printf("The following RAS connections are currently active\n\n");
		lpTempRasConn = lpRasConn;
		for (i = 0; i < lpcConnections; i++)
		{
			printf("Size: %d\n", lpTempRasConn->dwSize);
			printf("Entry name: %s\n", lpTempRasConn->szEntryName);
			printf("Device name: %s\n", lpTempRasConn->szDeviceName);
			hRasConn = lpTempRasConn->hrasconn;
			lpTempRasConn++;
		}
		break;
	
	default: // RasEnumConnections failed with some error.
		printf("RasEnumConnections failed: Error = %d\n", nRet);
		break;
	}

	GlobalFree(lpRasConn);
	return 0;

}