// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSDiskEnum.c
// DESCRIPTION:   Prints the names of the disk drives
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Mike Liu
// DATE:          5/9/98
//

#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <assert.h>
#include <windows.h> 
#include <lm.h>

int wmain(int argc, wchar_t *argv[])
{
   const int ENTRY_SIZE = 3; // Drive letter, colon, NULL
   LPTSTR pBuf = NULL;
   DWORD dwLevel = 0;
   DWORD dwPrefMaxLen = 0xFFFFFFFF;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }

   if (argc == 2)
      pszServerName = argv[1];

   nStatus = NetServerDiskEnum(pszServerName,
                               dwLevel,
                               (LPBYTE *) &pBuf,
                               dwPrefMaxLen,
                               &dwEntriesRead,
                               &dwTotalEntries,
                               NULL);

   if (nStatus == NERR_Success)
   {
      LPTSTR pTmpBuf;

      if ((pTmpBuf = pBuf) != NULL)
      {
         DWORD i;
         DWORD dwTotalCount = 0;

         for (i = 0; i < dwEntriesRead; i++)
         {
            assert(pTmpBuf != NULL);

            if (pTmpBuf == NULL)
            {
               fprintf(stderr, "An access violation has occurred\n");
               break;
            }

            fwprintf(stdout, L"\tDisk: %S\n", pTmpBuf);

            pTmpBuf += ENTRY_SIZE;
            dwTotalCount++;
         }

         fprintf(stderr, "\nEntries enumerated: %d\n", dwTotalCount);
      }
   }
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   return 0;
}
