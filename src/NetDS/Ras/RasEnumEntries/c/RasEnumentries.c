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
*		RasEnumEntries.c
*		
*		Usage:
*		RasEnumEntry
*
*		RAS API's used:
*			RasEnumEntries
*
*		Created by:  Mazahir Poonawala
*		Date:		 02/11/98
*		Modified by: Mazahir Poonawala
*		Date:		 03/15/99
*/

#include <windows.h>
#include <stdio.h>
#include <ras.h>
#include <raserror.h>

int main()
{
	LPRASENTRYNAME lpRasEntryName;
	LPRASENTRYNAME lpTempRasEntryName;
	DWORD cb = sizeof (RASENTRYNAME);
	DWORD cEntries = 0;
	int nRet;
	DWORD i;

	
	lpRasEntryName = (LPRASENTRYNAME)GlobalAlloc(GPTR, sizeof(RASENTRYNAME));
	if (lpRasEntryName == NULL)
	{
		printf("GlobalAlloc failed.\n");
		return -1;
	}
	lpRasEntryName->dwSize = sizeof(RASENTRYNAME);

	// Getting the size required for the RASENTRYNAME buffer

	nRet = RasEnumEntries(NULL, NULL, lpRasEntryName, &cb, &cEntries);

	switch (nRet)
	{
	case ERROR_BUFFER_TOO_SMALL:
		GlobalFree(lpRasEntryName);
		
		lpRasEntryName = (LPRASENTRYNAME)GlobalAlloc(GPTR, cb);
		if (lpRasEntryName == NULL)
		{
			printf("GlobalAlloc failed.\n");
			return -1;
		}
		lpRasEntryName->dwSize = sizeof(RASENTRYNAME);
		
		// Calling RasEnumEntries to enumerate the phonebook entries	
		nRet = RasEnumEntries(NULL, NULL, lpRasEntryName, &cb, &cEntries);
		
		if (nRet != ERROR_SUCCESS)
		{
			printf("RasEnumEntries failed: Error %d\n", nRet);
			GlobalFree(lpRasEntryName);
			return -1;
		}
		else
		{
			printf("Phone book entries in the default phonebook:\n\n");
			lpTempRasEntryName = lpRasEntryName;
			for(i=0;i < cEntries;i++)
			{
				printf("%s\n",lpTempRasEntryName->szEntryName);
				lpTempRasEntryName++;
			}
		}
		break;
	
	case 0:
		printf("Phone book entries in the default phonebook:\n\n");
		lpTempRasEntryName = lpRasEntryName;
		for(i=0;i < cEntries;i++)
		{
			printf("%s\n",lpTempRasEntryName->szEntryName);
			lpTempRasEntryName++;
		}
		break;
	
	default:
		printf("RasEnumEntries failed: Error = %d\n", nRet);
		GlobalFree(lpRasEntryName);
		return -1;
	}
	
	
	GlobalFree(lpRasEntryName);
	return 0;
}