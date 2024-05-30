// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NWUSetInfo.c
// DESCRIPTION:   Sets other Windows 9x or Windows NT
//                domains browsed by the workstation
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Mike Liu
// DATE:          5/9/98
//

#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int wmain(int argc, wchar_t *argv[])
{
   DWORD dwLevel = 1101;
   WKSTA_USER_INFO_1101 wui;
   NET_API_STATUS nStatus;

   if (argc != 2)
   {
      fwprintf(stderr, L"Usage: %s OtherDomains\n", argv[0]);
      exit(1);
   }

   wui.wkui1101_oth_domains = argv[1];

   nStatus = NetWkstaUserSetInfo(NULL,
                                 dwLevel,
                                 (LPBYTE)&wui,
                                 NULL);

   if (nStatus == NERR_Success)
      fprintf(stderr, "Workstation user infomation has been changed\n");
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
