// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSeEnum.c
// DESCRIPTION:   Enumeration all current sessions
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
   LPSESSION_INFO_10 pBuf = NULL;
   LPSESSION_INFO_10 pTmpBuf;
   DWORD dwLevel = 10;
   DWORD dwPrefMaxLen = 0xFFFFFFFF;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwResumeHandle = 0;
   DWORD i;
   DWORD dwTotalCount = 0;
   LPTSTR pszServerName = NULL;
   LPTSTR pszClientName = NULL;
   LPTSTR pszUserName = NULL;
   NET_API_STATUS nStatus;

   if (argc > 4)
   {
      wprintf(L"Usage: %s [\\\\ServerName] [\\\\ClientName] [UserName]\n", argv[0]);
      exit(1);
   }

   if (argc >= 2)
      pszServerName = argv[1];

   if (argc >= 3)
      pszClientName = argv[2];

   if (argc == 4)
      pszUserName = argv[3];

   do
   {
      nStatus = NetSessionEnum(pszServerName,
                               pszClientName,
                               pszUserName,
                               dwLevel,
                               (LPBYTE*)&pBuf,
                               dwPrefMaxLen,
                               &dwEntriesRead,
                               &dwTotalEntries,
                               &dwResumeHandle);

      if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
      {
         if ((pTmpBuf = pBuf) != NULL)
         {
            for (i = 0; (i < dwEntriesRead); i++)
            {
               assert(pTmpBuf != NULL);

               if (pTmpBuf == NULL)
               {
                  fprintf(stderr, "An access violation has occurred\n");
                  break;
               }

               wprintf(L"\n\tClient: %s\n", pTmpBuf->sesi10_cname);
               wprintf(L"\tUser:   %s\n", pTmpBuf->sesi10_username);
               printf("\tActive: %d\n", pTmpBuf->sesi10_time);
               printf("\tIdle:   %d\n", pTmpBuf->sesi10_idle_time);

               pTmpBuf++;
               dwTotalCount++;
            }
         }
      }
      else
         fprintf(stderr, "A system error has occurred: %d\n", nStatus);

      if (pBuf != NULL)
      {
         NetApiBufferFree(pBuf);
         pBuf = NULL;
      }
   }
   while (nStatus == ERROR_MORE_DATA);

   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

   fprintf(stderr, "\nTotal of %d entries enumerated\n", dwTotalCount);

   return 0;
}
