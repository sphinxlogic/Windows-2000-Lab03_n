// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSeGetInfo.c
// DESCRIPTION:   Prints out information about a session
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
   DWORD dwLevel = 10;
   LPSESSION_INFO_10 pBuf = NULL;
   LPTSTR pszServerName = NULL;
   LPTSTR pszUNCClientName = NULL;
   LPTSTR pszUserName = NULL;
   NET_API_STATUS nStatus;

   if (argc == 3)
   {
      pszUNCClientName = argv[1];
      pszUserName = argv[2];
   }
   else if (argc == 4)
   {
      pszServerName = argv[1];
      pszUNCClientName = argv[2];
      pszUserName = argv[3];
   }
   else
   {
      wprintf(L"Usage: %s [\\\\ServerName] \\\\ClientName UserName\n", argv[0]);
      exit(1);
   }

   nStatus = NetSessionGetInfo(pszServerName,
                               pszUNCClientName,
                               pszUserName,
                               dwLevel,
                               (LPBYTE *)&pBuf);

   if (nStatus == NERR_Success)
   {
      if (pBuf != NULL)
      {
         wprintf(L"\n\tClient: %s\n", pBuf->sesi10_cname);
         wprintf(L"\tUser:   %s\n", pBuf->sesi10_username);
         printf("\tActive: %d\n", pBuf->sesi10_time);
         printf("\tIdle:   %d\n", pBuf->sesi10_idle_time);
      }
   }
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   return 0;
}
