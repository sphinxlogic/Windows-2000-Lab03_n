// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NWGetInfo.c
// DESCRIPTION:   Prints the configuration information
//                (domain, version, etc.) about the
//                workstation
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
   DWORD dwLevel = 102;
   LPWKSTA_INFO_102 pBuf = NULL;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }

   if (argc == 2)
      pszServerName = argv[1];

   nStatus = NetWkstaGetInfo(pszServerName,
                             dwLevel,
                             (LPBYTE *)&pBuf);

   if (nStatus == NERR_Success)
   {
      printf("\n\tPlatform: %d\n", pBuf->wki102_platform_id);
      wprintf(L"\tName:     %s\n", pBuf->wki102_computername);
      printf("\tVersion:  %d.%d\n", pBuf->wki102_ver_major,
                                  pBuf->wki102_ver_minor);
      wprintf(L"\tDomain:   %s\n", pBuf->wki102_langroup);
      wprintf(L"\tLan Root: %s\n", pBuf->wki102_lanroot);
      wprintf(L"\t# Logged On Users: %d\n", pBuf->wki102_logged_on_users);
   }
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   return 0;
}
