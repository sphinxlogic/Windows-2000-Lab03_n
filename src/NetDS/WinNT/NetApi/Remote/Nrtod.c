// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NRTOD.c
// DESCRIPTION:   Prints a remote server's data and time
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
   LPTIME_OF_DAY_INFO pBuf = NULL;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }

   if (argc == 2)
      pszServerName = argv[1];

   nStatus = NetRemoteTOD(pszServerName,
                          (LPBYTE *)&pBuf);

   if (nStatus == NERR_Success)
   {
      if (pBuf != NULL)
      {
         fprintf(stderr, "\nThe current date is: %d/%d/%d\n",
                 pBuf->tod_month, pBuf->tod_day, pBuf->tod_year);
         fprintf(stderr, "The current time is: %d:%d:%d\n",
                 pBuf->tod_hours, pBuf->tod_mins, pBuf->tod_secs);
      }
   }
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   return 0;
}
