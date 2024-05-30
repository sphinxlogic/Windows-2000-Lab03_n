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
*		RasEnumDevices.c
*		
*		Usage:
*		RasEnumDevices
*
*		RAS API's used:
*			RasEnumDevices
*
*		Created by:  Mazahir Poonawala
*		Date:		 02/12/98
*		Modified by: Mazahir Poonawala
*		Date:		 03/15/99
*/

#include <windows.h>
#include <stdio.h>
#include <ras.h>
#include <raserror.h>

int main(void)
{
	DWORD	i;
	DWORD	nRet;
	DWORD	lpcb = 0;
	DWORD	lpcDevices;
	LPRASDEVINFO lpRasDevInfo;
	LPRASDEVINFO lpTempRasDevInfo;

	// To determine the required buffer size, calling RasEnumDevices 
	// with the lpRasDevInfo parameter set to NULL and the variable 
	// pointed to by lpcb set to zero. The function returns the required 
	// buffer size in the variable pointed to by lpcb. 
	nRet = RasEnumDevices(NULL, &lpcb, &lpcDevices);

	if (nRet == ERROR_BUFFER_TOO_SMALL)
	{
		lpRasDevInfo = (LPRASDEVINFO) GlobalAlloc(GPTR, lpcb);
		if (lpRasDevInfo == NULL)
		{
			printf("GlobalAlloc failed.\n");
			return -1;
		}
		lpRasDevInfo->dwSize = sizeof(RASDEVINFO);
	}
	else
	{
		printf("RasEnumDevices failed: Error %d\n", nRet);
		return -1;
	}

	nRet = RasEnumDevices(lpRasDevInfo, &lpcb, &lpcDevices);
	if (nRet != 0)
	{
		printf("RasEnumDevices failed: Error %d\n", nRet);
		return -1;
	}
	else
	{
		printf("The following RAS capable devices were found on this machine:\n\n");
		printf("Device\t\t\tCategory\n\n");
		lpTempRasDevInfo = lpRasDevInfo;
		for (i=0; i < lpcDevices; i++)
		{
			printf("%s\t%s\n",lpTempRasDevInfo->szDeviceName, lpTempRasDevInfo->szDeviceType);
			lpTempRasDevInfo++;
		}
	}

	GlobalFree(lpRasDevInfo);
	return 0;
}
