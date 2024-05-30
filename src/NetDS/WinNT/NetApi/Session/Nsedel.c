// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSeDel.c
// DESCRIPTION:   Delete a session between a server
//                and a workstation
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
  
   LPTSTR pszServerName = NULL;
   LPTSTR pszClientName = NULL;
   LPTSTR pszUserName = NULL;
   NET_API_STATUS nStatus;

   if (argc > 4)
   {
      wprintf(L"Usage: %s [\\\\ServerName] [\\\\ClientName] [UserName]\n", argv[0]);
      exit(1);
   }

   if (argc >= 2)
      pszServerName = argv[1];

   if (argc >= 3)
      pszClientName = argv[2];

   if (argc == 4)
      pszUserName = argv[3];

   nStatus = NetSessionDel(pszServerName,
                           pszClientName,
                           pszUserName);

   if (nStatus == NERR_Success)
      fprintf(stderr, "The specified session(s) has been successfully deleted\n");
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
