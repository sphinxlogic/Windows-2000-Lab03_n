// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NApiBuffer.c
// DESCRIPTION:   Demonstrates how to call all the NetApiBuffer
//                management functions, 
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          5/6/98
//

#define UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>

void PrintError(LPSTR lpszApi, DWORD res);

int main()
{
   PUSER_INFO_10 p;
   DWORD res, dwSize;

   //Call NetApiBufferAllocate
   res = NetApiBufferAllocate(1024, (LPVOID *) &p);
   if(res == NERR_Success)
   {
      printf("NetApiBufferAllocate:   Allocated 1024 bytes.\n");

      //Call NetApiBufferSize
      res = NetApiBufferSize(p, &dwSize);
      if(res == NERR_Success)
      {
         printf("NetApiBufferSize:       Buffer has %u bytes.\n", dwSize);

         //Call NetApiBufferReallocate
         res = NetApiBufferReallocate(p, dwSize * 2, (LPVOID *) &p);   
         if(res == NERR_Success)
            printf("NetApiBufferReallocate: Re-Allocated %u bytes.\n", dwSize * 2);
         else
            PrintError("NetApiBufferReallocate", res);

         //Call NetApiBufferFree
         res = NetApiBufferFree(p);
         if(res == NERR_Success)
            printf("Freed Buffer\n");
         else
            PrintError("NetApiBufferFree", res);
      }
      else
         PrintError("NetApiBufferSize", res);
   }         
   else
      PrintError("NetApiBufferAllocate", res);
   return 0;
}

void PrintError(LPSTR lpszApi, DWORD res)
{
   printf("%s: Error %u\n", lpszApi, res);
   return;
}
