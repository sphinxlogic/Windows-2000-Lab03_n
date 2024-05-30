// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NDRemove.c
// DESCRIPTION:   Removes a DFS share.
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
   DWORD res;

   if (argc<4)
      wprintf(L"Syntax: %s \\\\DFS_Server ServerName ShareName\n", argv[0]);
   else
   {
      res = NetDfsRemove(argv[1], argv[2], argv[3]);
      if(res==0)
         printf("Removed junction point\n");
      else
         printf("Error: %u\n", res);
   }
   return;
}