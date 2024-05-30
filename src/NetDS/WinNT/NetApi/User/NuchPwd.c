// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NUChPwd.c
// DESCRIPTION:   Change user password
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
  
   NET_API_STATUS nStatus;

   if (argc != 5)
   {
      fwprintf(stderr, L"Usage: %s \\\\ServerName UserName OldPassword NewPassword\n", argv[0]);
      exit(1);
   }

   nStatus = NetUserChangePassword(argv[1], argv[2], argv[3], argv[4]);

   if (nStatus == NERR_Success)
      fwprintf(stderr, L"User password has been changed successfully\n");
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
