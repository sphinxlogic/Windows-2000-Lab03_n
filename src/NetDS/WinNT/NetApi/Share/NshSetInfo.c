// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NShSetInfo.c
// DESCRIPTION:   Sets the remark for a specific share on a server
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
   SHARE_INFO_1004 p;
   NET_API_STATUS res;
   DWORD parm_err = 0;

   if(argc<4)
      printf("Usage: SetInfo server share \"remark\"\n");
   else
   {
      p.shi1004_remark=argv[3];
      res=NetShareSetInfo(argv[1], argv[2], 1004, (LPBYTE)&p, &parm_err);
      if(res==0)
         printf("Remark set.\n");
      else
         printf("Error: %u\tparmerr=%u\n", res, parm_err);
   }
   return;
}