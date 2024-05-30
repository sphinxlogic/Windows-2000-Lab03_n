// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NDEnum.c
// DESCRIPTION:   Enumerates the junction-points & storages of a DFS share. 
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
   PDFS_INFO_3 pData, p;
   PDFS_STORAGE_INFO ps;
   DWORD er=0, tr=0, res, i, j;

   if(argc<2)
      wprintf(L"Syntax: %s \\\\DFS_Server\n", argv[0]);
   else
   {
      res = NetDfsEnum(argv[1], 3, 0xFFFFFFFF, (LPBYTE *) &pData, &er, &tr);
      if(res==0)
      {
         p=pData;
         for(i=1;i<=er;i++)
         {
            printf("%-30S%u\n",p->EntryPath, p->NumberOfStorages);
            ps = p->Storage;
            for(j=1;j<=p->NumberOfStorages;j++)
            {
               printf("    %S  ", (ps->State == DFS_STORAGE_STATE_OFFLINE) ? TEXT("Offline"):TEXT("Online "));
               printf("\\\\%S\\%S\n",ps->ServerName,ps->ShareName);
               ps++;
            }
            p++;
         }
         NetApiBufferFree(pData);
      }
      else
         printf("Error: %u\n", res);
   }
   return;
}