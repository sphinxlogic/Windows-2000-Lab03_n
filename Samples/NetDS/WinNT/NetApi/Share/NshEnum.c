// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NShEnum.c
// DESCRIPTION:   Prints information about all SHARES on a computer
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          2/17/98
//

#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <lm.h>

void wmain( int argc, TCHAR *lpszArgv[ ])
{
   PSHARE_INFO_502 BufPtr,p;
   NET_API_STATUS res;
   LPTSTR   lpszServer = NULL;
   DWORD er=0,tr=0,resume=0, i;

   switch(argc)
   {
   case 2:
      lpszServer = lpszArgv[2];
      break;
   default:
      printf("Usage: NetShareEnum <servername>\n");
      return;
   }
   printf("Share:              Local Path:                   Uses:   Descriptor:\n");
   printf("---------------------------------------------------------------------\n");
   do
   {
      res = NetShareEnum (lpszServer, 502, (LPBYTE *) &BufPtr, 0xFFFFFFFF, &er, &tr, &resume);
      if(res == ERROR_SUCCESS || res == ERROR_MORE_DATA)
      {
         p=BufPtr;
         for(i=1;i<=er;i++)
         {
            printf("%-20S%-30S%-8u",p->shi502_netname, p->shi502_path, p->shi502_current_uses);
            if (IsValidSecurityDescriptor(p->shi502_security_descriptor))
               printf("Yes\n");
            else
               printf("No\n");
            p++;
         }
         NetApiBufferFree(BufPtr);
      }
      else 
         printf("Error: %ld\n",res);
   }
   while (res==ERROR_MORE_DATA);
   return;
}
