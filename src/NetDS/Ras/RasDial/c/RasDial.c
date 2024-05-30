/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1993 - 1998 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/*
*		RasDial.c
*		
*		Usage:
*		RasDial -e [entry name] -p [phone number] -u [username] 
*				-z [password] -d [domain]
*
*		RAS API's used:
*			RasDial
*			RasHangUp
*			RasGetConnectStatus
*			RasGetProjectionInfo
*
*		Created by:  Mazahir Poonawala
*		Date:		 03/05/98
*		Modified by: Mazahir Poonawala
*		Date:		 03/15/99
*/

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <ras.h>
#include <raserror.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Usage
void Usage(char *progname) 
{
   fprintf(stderr,
      "Usage\n%s \t-e [entry name] -p [phone number] \n\t\t-u [username] -z [password] -d [domain]\n",
      progname);
   exit (1);
}


int main(int argc, char **argv) 
{
   LPRASDIALPARAMS      lpRasDialParams;
   HRASCONN             hRasConn;
   LPRASCONNSTATUS      lpRasConnStatus;
   RASPPPIP             *lpProjection;
   int                  i;
   DWORD                nRet;
   DWORD                cb;
   char                 ch;
   DWORD                tcLast;	

   lpRasDialParams = (LPRASDIALPARAMS) GlobalAlloc(GPTR, sizeof(RASDIALPARAMS)); 
   if (lpRasDialParams == NULL)
   {
      printf("GlobalAlloc failed\n");
      return -1;
   }

   lpRasDialParams->dwSize =sizeof(RASDIALPARAMS);
   hRasConn = NULL;

   // Copy command line arguments into the RASDIALPARAMS structure
   if (argc >1) 
   {
      for(i=1;i <argc;i++) 
	  {
         if ( (argv[i][0] == '-') || (argv[i][0] == '/') ) 
		 {
            switch(tolower(argv[i][1])) 
			{
               case 'e': // Entry name
                  lstrcpy(lpRasDialParams->szEntryName, argv[++i]);
                  break;
               case 'p': // Phone number
                  lstrcpy(lpRasDialParams->szPhoneNumber, argv[++i]);
                  break;
               case 'u': // User name
                  lstrcpy(lpRasDialParams->szUserName, argv[++i]);
                  break;
               case 'z': // Password
                  lstrcpy(lpRasDialParams->szPassword, argv[++i]);
                  break;
               case 'd': // Domain name
                  lstrcpy(lpRasDialParams->szDomain, argv[++i]);
                  break;
               default:
                  Usage(argv[0]);
                  break;
			}
		 }
         else
            Usage(argv[0]);
	  }
   }
   else
      Usage(argv[0]);

   printf("Dialing...\n"); 
   // Calling RasDial synchronously
   nRet = RasDial(NULL, NULL, lpRasDialParams, 0, 0L, &hRasConn);
   if (nRet)
   {
      printf("RasDial failed: Error = %d\n", nRet);
      return -1;
   }

   lpRasConnStatus = (LPRASCONNSTATUS)GlobalAlloc(GPTR, sizeof(RASCONNSTATUS));	
   if (lpRasConnStatus == NULL)
   {
      printf("GlobalAlloc failed.\n");
      return -1;
   }
   
   lpRasConnStatus->dwSize = sizeof(RASCONNSTATUS);

   // Checking connection status using RasGetConnectStatus
   nRet = RasGetConnectStatus(hRasConn, lpRasConnStatus);
   if (nRet != ERROR_SUCCESS)
   {
      printf("RasGetConnectStatus failed: Error = %d\n", nRet);
      return -1;
   }
   else
   {
      if (lpRasConnStatus->rasconnstate == RASCS_Connected)
      printf("Connection estabilished using %s\n", lpRasConnStatus->szDeviceName);
   }
	
   lpProjection = (RASPPPIP *) GlobalAlloc(GPTR, sizeof(RASPPPIP));
   if (lpProjection == NULL)
   {
      printf("GlobalAlloc failed.\n");
      return -1;
   }
   lpProjection->dwSize = sizeof(RASPPPIP);
   cb = sizeof(RASPPPIP);
	
   // Getting the Ras client and server IP address using RasGetProjectionInfo
   nRet = RasGetProjectionInfo(hRasConn, RASP_PppIp, lpProjection, &cb);
	
   if (nRet == ERROR_BUFFER_TOO_SMALL)
   {
      GlobalFree(lpProjection);
	
      lpProjection = (RASPPPIP *) GlobalAlloc(GPTR, cb);
      if (lpProjection == NULL)
	  {
         printf("GlobalAlloc failed.\n");
         return -1;
	  }
	
      nRet = RasGetProjectionInfo(hRasConn, RASP_PppIp, lpProjection, &cb);
	
      if (nRet != ERROR_SUCCESS)
	  {
         printf("RasGetProjectionInfo failed: Error %d", nRet);
         return -1;
	  }
      else
	  {
         printf("\nRas Client IP address: %s\n", lpProjection->szIpAddress);
         printf("Ras Server IP address: %s\n\n", lpProjection->szServerIpAddress);
	  }
   }
   else
   {
      if (nRet != ERROR_SUCCESS)
	  {
         printf("RasGetProjectionInfo failed: Error %d", nRet);
		 return -1;
	  }
      else
	  {
         printf("\nRas Client IP address: %s\n", lpProjection->szIpAddress);
		 printf("Ras Server IP address: %s\n\n", lpProjection->szServerIpAddress);
	  }
   }

   printf("Press any key to hang up...\n");
   scanf("%c", &ch);

   // Terminating the connection using RasHangUp
   nRet = RasHangUp(hRasConn);
   if (nRet != ERROR_SUCCESS)
   {
	   printf("RasHangUp failed: Error = %d", nRet);
	   return -1;
   }
   
   tcLast = GetTickCount() + 10000;
   
   while( (RasGetConnectStatus(hRasConn,lpRasConnStatus) != ERROR_INVALID_HANDLE) && (tcLast > GetTickCount()))
   {
	   Sleep(50);
   }

   printf("Hung Up\n");

   GlobalFree(lpProjection);
   GlobalFree(lpRasDialParams);
   GlobalFree(lpRasConnStatus);
   return 0;
}