// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NShAdd.c
// DESCRIPTION:   Adds a share to a server
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
   SHARE_INFO_2 p;
   DWORD parm_err = 0;

   if(argc<2)
      printf("Usage: NetShareAdd server\n");
   else
   {
      p.shi2_netname = TEXT("TESTSHARE");    
      p.shi2_type = STYPE_DISKTREE;    
      p.shi2_remark = TEXT("TESTSHARE to test NetShareAdd");
      p.shi2_permissions = 0;    
      p.shi2_max_uses = 4;
      p.shi2_current_uses = 0;    
      p.shi2_path = TEXT("C:\\");
      p.shi2_passwd = NULL;

      res=NetShareAdd(argv[1], 2, (LPBYTE) &p, &parm_err);
      if(res==0)
         printf("Share created.\n");
      else
         printf("Error: %u\tparmerr=%u\n", res, parm_err);
   }
   return;
}