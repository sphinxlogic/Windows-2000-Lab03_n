// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NDGetInfo.c
// DESCRIPTION:   Gets info about a DFS share.
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
   PDFS_INFO_3 pData;
   PDFS_STORAGE_INFO ps;
   DWORD er=0, tr=0, res, j;

   LPTSTR lpszServer, lpszShare;

   lpszShare = argc < 4 ? NULL : argv[3];
   lpszServer = argc < 3 ? NULL : argv[2];
   if (argc<2)
      wprintf(L"Syntax: %s \\\\DFS_Server [ServerName ShareName]\n", argv[0]);
   else
   {
      res = NetDfsGetInfo(argv[1], lpszServer, lpszShare, 3, (LPBYTE *) &pData);
      if(res==0)
      {
         printf("%-30S Storages: %u\nComment: %S\n",pData->EntryPath, pData->NumberOfStorages, pData->Comment);
         ps = pData->Storage;
         for(j=1;j<=pData->NumberOfStorages;j++)
         {
            printf("    %S  ", (ps->State == DFS_STORAGE_STATE_OFFLINE) ? TEXT("Offline"): TEXT("Online "));
            printf("\\\\%S\\%S\n",ps->ServerName,ps->ShareName);
            ps++;
         }
         NetApiBufferFree(pData);
      }
      else
         printf("Error: %u\n", res);
   }
   return;
}