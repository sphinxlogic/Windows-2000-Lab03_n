// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NCEnum.c
// DESCRIPTION:   Lists all the connections to a specific share on a server or 
//                all the connections between two computers
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          3/12/98
//

#define UNICODE      //Unicode required for all 32-Bit LANMAN API Calls
#include <windows.h>
#include <lm.h>
#include <stdio.h>

void wmain(int argc, wchar_t *argv[ ])
{
   DWORD res, i, er = 0, tr = 0, resume = 0;
   PCONNECTION_INFO_1 p,b;
   LPTSTR lpszServer = NULL, lpszShare = NULL;

   if(argc<2)
      wprintf(L"Syntax: %s [ServerName] ShareName | \\\\ComputerName\n", argv[0]);
   else
   {
      if(argc>2)
         lpszServer=argv[1];     //Server is not the default local machine
      lpszShare=argv[argc - 1];  //ShareName is always the last argument

      res=NetConnectionEnum(lpszServer, lpszShare, 1, (LPBYTE *) &p, 0xFFFFFFFF, &er, &tr, &resume);

      if(res == 0)//if no error occured
      {
         if(er>0)    //if there were any results, print them out
         {
            b=p;
            for(i=0;i<er;i++)
            {
               printf("%S\t%S\n", b->coni1_username,b->coni1_netname);
               b++;
            }
            NetApiBufferFree(p);
         }
         else        //otherwise print a message depending on whether the qualifier
         {           // parameter was a computer (\\ComputerName) or a share (ShareName)
            if(lpszShare[0]=='\\')  
               printf("No connection to %S from %S\n", 
                  (lpszServer == NULL)?TEXT("LocalMachine"):lpszServer, lpszShare);
            else                       
               printf("No one connected to %S\\%S\n",
                  (lpszServer == NULL)?TEXT("\\\\LocalMachine"):lpszServer,lpszShare);
         }        
      }
      else        //otherwise print the error
         printf("Error: %d\n",res);
   }
   return;
}