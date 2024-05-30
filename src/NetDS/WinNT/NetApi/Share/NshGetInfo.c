// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NShGetInfo.c
// DESCRIPTION:   Prints information about a specific SHARE
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
   PSHARE_INFO_502 BufPtr;
   NET_API_STATUS res;
   LPTSTR   lpszServer = NULL, lpszShare;

   switch(argc)
   {
   case 3:
      lpszServer = lpszArgv[2];
   case 2:
      lpszShare = lpszArgv[1];
      break;
   default:
      printf("Usage: NetShareGetInfo sharename <servername>\n");
      return;
   }
   
   if((res = NetShareGetInfo (lpszServer,lpszShare,502,(LPBYTE *) &BufPtr)) == ERROR_SUCCESS)
   {
      printf("%S\t%S\t%u\n",BufPtr->shi502_netname, BufPtr->shi502_path, BufPtr->shi502_current_uses);
      if (IsValidSecurityDescriptor(BufPtr->shi502_security_descriptor))
         printf("It has a valid Security Descriptor.\n");
      else
         printf("It does not have a valid Security Descriptor.\n");
      NetApiBufferFree(BufPtr);
   }
   else 
      printf("Error: %ld\n",res);
   return;
}