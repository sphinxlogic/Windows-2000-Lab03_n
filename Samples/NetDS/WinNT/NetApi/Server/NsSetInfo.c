// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSSetInfo.c
// DESCRIPTION:   Set the comment information about
//                the specified server
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
   DWORD dwLevel = 1005;
   SERVER_INFO_1005 si;
   NET_API_STATUS nStatus;

   if (argc != 3)
   {
      fwprintf(stderr, L"Usage: %s \\\\ServerName Comment\n", argv[0]);
      exit(1);
   }

   si.sv1005_comment = argv[2];

   nStatus = NetServerSetInfo(argv[1],
                              dwLevel,
                              (LPBYTE)&si,
                              NULL);

   if (nStatus == NERR_Success)
      fwprintf(stderr, L"Comment reset\n", argv[2]);
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
