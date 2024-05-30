// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NQDInfo.c
// DESCRIPTION:   Return all global groups
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          1/27/98
//

#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <lm.h>

void main( int argc, char *argv[ ] )
{
   PNET_DISPLAY_GROUP pBuff, p;
   DWORD res, dwRec, i = 0;
   TCHAR szServer[255]=TEXT("");  //Actually you can pass a NULL or an Empty string to get
                           //the local information

   if(argc > 1)   //see if there was a server name passed
      MultiByteToWideChar(CP_ACP, 0, argv[1], -1, szServer, 255); //convert it to Unicode

   do
   {  // Make the request. I told it to break the returned data into 25 byte chunks
      // just to demonstrate how to make the request over and over again.
      res = NetQueryDisplayInformation(szServer, 3, i, 1000, 25, &dwRec, &pBuff);
      if((res==ERROR_SUCCESS) || (res==ERROR_MORE_DATA))
      {
         p = pBuff;
         for(;dwRec>0;dwRec--)
         {
            printf("Name:      %S\n"
                  "Comment:   %S\n"
                  "Group ID:  %u\n"
                  "Attributs: %u\n"
                  "--------------------------------\n",
                  p->grpi3_name,
                  p->grpi3_comment,
                  p->grpi3_group_id,
                  p->grpi3_attributes);
            i = p->grpi3_next_index;  //if there is more then set the index
            p++;
         }
         NetApiBufferFree(pBuff);
      }
      else
         printf("Error: %u\n", res);
   } while (res==ERROR_MORE_DATA);
   return;
}