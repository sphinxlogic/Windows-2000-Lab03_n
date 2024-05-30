// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSEnum.c
// DESCRIPTION:   List all the visible servers in a domain
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
   LPSERVER_INFO_101 pBuf = NULL;
   LPSERVER_INFO_101 pTmpBuf;
   DWORD dwLevel = 101;
   DWORD dwPrefMaxLen = 0xFFFFFFFF;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwTotalCount = 0;
   DWORD dwServerType = SV_TYPE_SERVER;
   DWORD dwResumeHandle = 0;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;
   DWORD i;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }

   if (argc == 2)
      pszServerName = argv[1];

   nStatus = NetServerEnum(pszServerName,
                           dwLevel,
                           (LPBYTE *) &pBuf,
                           dwPrefMaxLen,
                           &dwEntriesRead,
                           &dwTotalEntries,
                           dwServerType,
                           NULL,
                           &dwResumeHandle);

   if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
   {
      if ((pTmpBuf = pBuf) != NULL)
      {
         for (i = 0; i < dwEntriesRead; i++)
         {
            assert(pTmpBuf != NULL);

            if (pTmpBuf == NULL)
            {
               fprintf(stderr, "An access violation has occurred\n");
               break;
            }

            printf("\tPlatform: %d\n", pTmpBuf->sv101_platform_id);
            wprintf(L"\tName:     %s\n", pTmpBuf->sv101_name);
            printf("\tVersion:  %d.%d\n",
                   pTmpBuf->sv101_version_major,
                   pTmpBuf->sv101_version_minor);
            printf("\tType:     %d", pTmpBuf->sv101_type);

            // Let's check to see if it is a DC
            if (pTmpBuf->sv101_type & SV_TYPE_DOMAIN_CTRL)
               wprintf(L" (PDC)");
            else if (pTmpBuf->sv101_type & SV_TYPE_DOMAIN_BAKCTRL)
               wprintf(L" (BDC)");
            
            printf("\n");

            wprintf(L"\tComment:  %s\n\n", pTmpBuf->sv101_comment);

            pTmpBuf++;
            dwTotalCount++;
         }

         if (nStatus == ERROR_MORE_DATA)
         {
            fprintf(stderr, "\nMore entries available!!!\n");
            fprintf(stderr, "Total entries: %d", dwTotalEntries);
         }

         printf("\nEntries enumerated: %d\n", dwTotalCount);
      }
   }
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   return 0;
}
