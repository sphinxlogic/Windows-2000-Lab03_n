// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NSTransEnum.c
// DESCRIPTION:   Enumerate the transport names managed by
//                the specified server
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
   LPSERVER_TRANSPORT_INFO_0 pBuf = NULL;
   LPSERVER_TRANSPORT_INFO_0 pTmpBuf;
   DWORD dwLevel = 0;
   DWORD dwPrefMaxLen = 256;//0xFFFFFFFF
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwResumeHandle = 0;
   DWORD dwTotalCount = 0;
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

   do
   {
      nStatus = NetServerTransportEnum(pszServerName,
                                       dwLevel,
                                       (LPBYTE *) &pBuf,
                                       dwPrefMaxLen,
                                       &dwEntriesRead,
                                       &dwTotalEntries,
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

               wprintf(L"\tTransport: %s\n", pTmpBuf->svti0_transportname);

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
