// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NShCheck.c
// DESCRIPTION:   Checks to see if a specific device is shared on a server
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          2/17/98
//

#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <lm.h>

void wmain( int argc, TCHAR *argv[ ])
{
   NET_API_STATUS res;
   DWORD devType = 0;

   if(argc<3)
      printf("Usage: NetShareCheck server device\n");
   else
   {
      res=NetShareCheck(argv[1], _wcsupr(argv[2]), &devType);
      if(res==0)
         printf("Device is shared as type %u.\n",devType);
      else
         printf("Error: %u\n", res);
   }
   return;
}