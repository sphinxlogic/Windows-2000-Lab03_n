// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NUSetGroups.c
// DESCRIPTION:   Sets global group membership information
//                for the specified user
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
   DWORD dwLevel = 0;
   GROUP_USERS_INFO_0 gi;
   NET_API_STATUS nStatus;

   if (argc != 4)
   {
      fwprintf(stderr, L"Usage: %s \\\\ServerName UserName GroupName\n", argv[0]);
      exit(1);
   }

   gi.grui0_name = argv[3];

   nStatus = NetUserSetGroups(argv[1],
                              argv[2],
                              dwLevel,
                              (LPBYTE)&gi,
                              1);

   if (nStatus == NERR_Success)
      fwprintf(stderr, L"Group membership has been successfully for %s\n", argv[2]);
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
