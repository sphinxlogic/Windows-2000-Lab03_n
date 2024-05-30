// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NWGetInfo.c
// DESCRIPTION:   Sets the session time out information
//                on the workstation
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
   WKSTA_INFO_1018 wi;
   DWORD dwLevel = 1018;
   NET_API_STATUS nStatus;

   if (argc != 3)
   {
      fwprintf(stderr, L"Usage: %s \\\\ServerName SessionTimeOut\n", argv[0]);
      exit(1);
   }

   wi.wki1018_sess_timeout = _wtoi(argv[2]);

   nStatus = NetWkstaSetInfo(argv[1],
                             dwLevel,
                             (LPBYTE)&wi,
                             NULL);

   if (nStatus == NERR_Success)
      fwprintf(stderr, L"Workstation information reset\n", argv[2]);
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
