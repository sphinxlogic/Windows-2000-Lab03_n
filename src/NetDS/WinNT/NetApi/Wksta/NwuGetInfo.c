// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NWUGetInfo.c
// DESCRIPTION:   Get infomation about the specified user
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          2/17/98
//
// NOTES: Much of the code below is just parsing the UserName and ServerName
//        to look up.  The sample allows you to pass as arguments a Username,
//			 a ServerName, both or neither.
//
//			 If you pass neither then it will lookup the currently logged on user
//        If you pass no server name it will look through the local user database
//			 If you pass both it will look either in domain or the server you specify
//

#define UNICODE

#include <windows.h>
#include <lm.h>
#include <stdio.h>

int wmain(int argc, wchar_t *argv[])
{

   int res;
   PUSER_INFO_3 pInfo = NULL;
   PWKSTA_USER_INFO_1 pWkstaUser = NULL;

   LPTSTR pszUser = NULL, pszServer = NULL, pszDC = NULL;
   
   if((argc > 1) && (wcscmp(argv[1],TEXT("/?"))==0))
   {
      printf("Usage: Nugi [username [domainname | \\\\servername]]\n");
      return 0;
   }

   if(argc < 2)
   {
      if(res = NetWkstaUserGetInfo(NULL, 1, (LPBYTE *) &pWkstaUser))
      {
         printf("Could not find a local user name.  Error %D\n", res);
         return(res);
      }
      else
      {
         pszUser = pWkstaUser->wkui1_username;
         pszServer = pWkstaUser->wkui1_logon_server;
      }
   }
   else
      pszUser = argv[1];

   if(argc < 3)
      pszServer = NULL;
   else
   {
      if (argv[2][1] == '\\')
         pszServer = argv[2];
      else
      {
         if(res = NetGetDCName(NULL, argv[2], (LPBYTE *) &pszDC))
         {
            printf("Could not find a domain named %S\n",argv[2]);
            return(res);
         }
         else
            pszServer = pszDC;
      }
   }

   res = NetUserGetInfo (pszServer, pszUser, 3,(LPBYTE *) &pInfo);
   if(res)
      printf("NetUserGetInfo(%S, %S, 3, 0x%p) returned %d.\n", pszServer, pszUser, &pInfo, res);
   else
   {
      printf("%S reported that\nUser Name: %S\nhas logged on: %u times.\n",
         pszServer,
         pInfo->usri3_name, 
         pInfo->usri3_num_logons);
      NetApiBufferFree(pInfo);
   }
   if(pWkstaUser)
      NetApiBufferFree(pWkstaUser);
   if(pszDC)
      NetApiBufferFree(pszDC);

   return 0;
}