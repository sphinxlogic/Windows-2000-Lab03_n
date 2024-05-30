// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NDAdd.c
// DESCRIPTION:   Adds a new DFS share. The folder passed as the first argument, 
//                must exist before calling NetDfsAdd.
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
   LPTSTR lpszComment;
   lpszComment = argc < 5 ? NULL : argv[4];
   if (argc<4)
      wprintf(L"Syntax: %s \\\\DFS_Server\\DFS_Share ServerName ShareName [\"Comment\"]\n", argv[0]);
   else
   {
      //To add a second storage to the junction point change
      //the last parameter in the NetDfsAdd function to 0
      res = NetDfsAdd(argv[1], argv[2], argv[3], argv[4], DFS_ADD_VOLUME);
      if(res==0)
         printf("Added junction point\n");
      else
         printf("Error: %u\n", res);
   }
   return;
}