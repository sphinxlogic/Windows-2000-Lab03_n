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
*        RasGetCtryInfo.c
*
*        Usage:
*        RasGetCtryInfo > [filename]
*
*        RAS API's used:
*            RasGetCountryInfo
*
*        Created by: Mazahir Poonawala
*        Date: 02/10/98
*/

#include <windows.h>
#include <stdio.h>
#include <ras.h>
#include <raserror.h>


int main(void)
{

    LPRASCTRYINFO lpRasCtryInfo;
    DWORD Size;
    int nRet;

    // The size of the buffer should at least be 256 bytes
    lpRasCtryInfo = (LPRASCTRYINFO) GlobalAlloc(GPTR, 256);
    // Start with country ID = 1
    lpRasCtryInfo->dwCountryID = 1;

    while (lpRasCtryInfo->dwCountryID)
    {

        lpRasCtryInfo->dwSize = sizeof(RASCTRYINFO);
        Size = 256;
        if (nRet = RasGetCountryInfo(lpRasCtryInfo, &Size))
        {
            printf("RasGetCountryInfo failed: Error %d\n", nRet);
            return -1;
        }
        // Print the country name, country code and country ID
        printf("%-30s%6d%6d\n", (LPSTR) lpRasCtryInfo + lpRasCtryInfo->dwCountryNameOffset,
            lpRasCtryInfo->dwCountryCode, lpRasCtryInfo->dwCountryID);
        // Point to the next country on the list
        lpRasCtryInfo->dwCountryID = lpRasCtryInfo->dwNextCountryID;
    }

    GlobalFree(lpRasCtryInfo);
    return 0;
}
