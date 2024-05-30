// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NDSetInfo.c
// DESCRIPTION:   Sets the Comment on a DFS junction-point
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          2/18/98
//

#define UNICODE
#include <windows.h>
#include <lm.h>
#include <lmdfs.h>
#include <stdio.h>

void wmain(int argc, wchar_t *argv[ ])
{
   DFS_INFO_100 dfsData;
   DWORD res;

   if (argc<2)
      wprintf(L"Syntax: %s \\\\DFS_Server\\DFS_Share [\"Comment\"]\n", argv[0]);
   else
   {
      dfsData.Comment = argc < 3 ? NULL : argv[2];
      res=NetDfsSetInfo(argv[1], NULL, NULL, 100, (LPBYTE) &dfsData);
      if(res == 0)
         printf("Comment set.\n");
      else
         printf("Error: %u", res);
   }
   return;
}
