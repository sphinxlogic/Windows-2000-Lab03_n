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
*		RasDialAsync.c
*		
*		Usage:
*		RasDialAsync
*
*		RAS API's used:
*				RasDial
*				RasHangUp
*				RasGetConnectStatus
*
*		Callback function:
*				RasDialFunc
*
*		Created by:  Mazahir Poonawala
*		Date:		 02/18/98
*		Modified by: Mazahir Poonawala
*		Date:		 03/15/99
*/

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <ras.h>
#include <raserror.h>
#include <string.h>
#include <winbase.h>
#include <time.h>
#include <stdlib.h>

void WINAPI RasDialFunc(UINT unMsg,
                        RASCONNSTATE rasconnstate,
                        DWORD dwError );

HANDLE Event_handle; // Global event handle

// Usage
void Usage(char *progname) 
{
   fprintf(stderr,
   "Usage\n%s \t-e [entry name] -p [phone number] \n\t\t-u [username] -z [password] -d [domain]\n",
   progname);
   exit(0);
}


/* Begin main()... */

int main(int argc, char*argv[])
{
   LPRASDIALPARAMS   lpRasDialParams;   // Structure to store the RasDial parameters
   LPRASCONNSTATUS   lpRasConnStatus;   // Buffer to receive status data
   HRASCONN          hRasConn;          // Handle to RAS connection
   DWORD             nRet;              // Return value from a function
   DWORD             tcLast;            // Final Tick Count value
   int               i;
	

   // Create the event, which indicates completion of RasDial()
   Event_handle = CreateEvent(NULL, FALSE, FALSE, NULL);
   if (!Event_handle)
   {
	   printf("CreateEvent failed: Error = %d", GetLastError());
	   return -1;
   }



   // Initialize the RASDIALPARAMS structure
   lpRasDialParams = (LPRASDIALPARAMS) GlobalAlloc(GPTR, sizeof(RASDIALPARAMS));
   if (lpRasDialParams == NULL)
   {
	   printf("GlobalAlloc failed\n");
	   return -1;
   }

   lpRasDialParams->dwSize =sizeof(RASDIALPARAMS);

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

   // Dial out asynchronously using RasDial()
   printf("Dialing... %s\n", lpRasDialParams->szPhoneNumber);
   hRasConn = NULL;

   nRet = RasDial(NULL, NULL, lpRasDialParams, 0, &RasDialFunc, &hRasConn);
   // Check whether RasDial() succeeded
   if (nRet)
   {
      printf("RasDial failed: Error = %d\n", nRet);
      return -1;
   }

   // Wait for the RasDial() to complete, signaled by the SetEvent()
   nRet = WaitForSingleObject(Event_handle, 50000);
   switch (nRet)
   {
      case WAIT_OBJECT_0:
      // Normal completion or Ras Error encountered
         printf("Will hang up in 5 seconds...\n");
         Sleep(5000);
         printf("Calling RasHangUp...\n");
         nRet = RasHangUp(hRasConn);
         if (nRet != 0)
		 {
            printf("RasHangUp failed: Error = %d\n", nRet);
            return -1;
		 }
			
         lpRasConnStatus = (LPRASCONNSTATUS)GlobalAlloc(GPTR, sizeof(RASCONNSTATUS));
         if (lpRasConnStatus == NULL)
		 {
            printf("GlobalAlloc failed.\n");
            return -1;
		 }
         lpRasConnStatus->dwSize = sizeof(RASCONNSTATUS);
			
         tcLast = GetTickCount() + 10000;

         while( (RasGetConnectStatus(hRasConn,lpRasConnStatus) != ERROR_INVALID_HANDLE) && (tcLast > GetTickCount()))
		 {	
            Sleep(50);      
		 }

         printf("Connection to %s terminated.\n", lpRasDialParams->szPhoneNumber);
         break;
		
      case WAIT_TIMEOUT: // RasDial timed out
         printf("RasDial Timed out...\n");
         printf("Calling RasHangUp...\n");
         RasHangUp(hRasConn);
			
         lpRasConnStatus = (LPRASCONNSTATUS)GlobalAlloc(GPTR, 256);
         if (lpRasConnStatus == NULL)
		 {
            printf("GlobalAlloc failed.\n");
            return -1;
		 }
         lpRasConnStatus->dwSize = sizeof(RASCONNSTATUS);
			
         tcLast = GetTickCount() + 10000;

         while( (RasGetConnectStatus(hRasConn,lpRasConnStatus) != ERROR_INVALID_HANDLE) && (tcLast > GetTickCount()))
		 {	
            Sleep(50);      
		 }

         printf("Connection to %s terminated.\n", lpRasDialParams->szPhoneNumber);
         break;
   }


   CloseHandle(Event_handle);
   GlobalFree(lpRasDialParams);
   GlobalFree(lpRasConnStatus);
   return 0;
}


// Callback function RasDialFunc()
void WINAPI RasDialFunc(UINT unMsg, 
                        RASCONNSTATE rasconnstate, 
                        DWORD dwError )
{
   char szRasString[256]; // Buffer for storing the error string

   if ( dwError )  // Error occurred
   {
      RasGetErrorString( (UINT)dwError, szRasString, 256 );
      printf("Error: %d - %s\n",dwError, szRasString);
      SetEvent(Event_handle);
      return;
   }

   // Map each of the states of RasDial() and display on the screen
   // the next state that RasDial() is entering
   switch (rasconnstate)
   {
      case RASCS_OpenPort:
            printf ("RASCS_OpenPort = %d\n", rasconnstate);
            printf ("Opening port...\n");
			break;
        case RASCS_PortOpened:
            printf ("RASCS_PortOpened = %d\n", rasconnstate);
            printf ("Port opened.\n");
        	break;
        case RASCS_ConnectDevice: 
            printf ("RASCS_ConnectDevice = %d\n", rasconnstate);
            printf ("Connecting device...\n");
           break;
        case RASCS_DeviceConnected: 
            printf ("RASCS_DeviceConnected = %d\n", rasconnstate);
            printf ("Device connected.\n");
            break;
        case RASCS_AllDevicesConnected:
            printf ("RASCS_AllDevicesConnected = %d\n", rasconnstate);
            printf ("All devices connected.\n");
            break;
        case RASCS_Authenticate: 
            printf ("RASCS_Authenticate = %d\n", rasconnstate);
            printf ("Authenticating...\n");
            break;
        case RASCS_AuthNotify:
            printf ("RASCS_AuthNotify = %d\n", rasconnstate);
            printf ("Authentication notify.\n");
            break;
        case RASCS_AuthRetry: 
            printf ("RASCS_AuthRetry = %d\n", rasconnstate);
            printf ("Retrying authentication...\n");
            break;
        case RASCS_AuthCallback:
            printf ("RASCS_AuthCallback = %d\n", rasconnstate);
            printf ("Authentication callback...\n");
            break;
        case RASCS_AuthChangePassword: 
            printf ("RASCS_AuthChangePassword = %d\n", rasconnstate);
            printf ("Change password...\n");
            break;
        case RASCS_AuthProject: 
            printf ("RASCS_AuthProject = %d\n", rasconnstate);
            printf ("Projection phase started...\n");
            break;
        case RASCS_AuthLinkSpeed: 
            printf ("RASCS_AuthLinkSpeed = %d\n", rasconnstate);
            printf ("Negoting speed...\n");
            break;
        case RASCS_AuthAck: 
            printf ("RASCS_AuthAck = %d\n", rasconnstate);
            printf ("Authentication acknowledge...\n");
            break;
        case RASCS_ReAuthenticate: 
            printf ("RASCS_ReAuthenticate = %d\n", rasconnstate);
            printf ("Retrying Authentication...\n");
            break;
        case RASCS_Authenticated: 
            printf ("RASCS_Authenticated = %d\n", rasconnstate);
            printf ("Authentication complete.\n");
            break;
        case RASCS_PrepareForCallback: 
            printf ("RASCS_PrepareForCallback = %d\n", rasconnstate);
            printf ("Preparing for callback...\n");
            break;
        case RASCS_WaitForModemReset: 
            printf ("RASCS_WaitForModemReset = %d\n", rasconnstate);
            printf ("Waiting for modem reset...\n");
            break;
        case RASCS_WaitForCallback:
            printf ("RASCS_WaitForCallback = %d\n", rasconnstate);
            printf ("Waiting for callback...\n");
            break;
        case RASCS_Projected:  
            printf ("RASCS_Projected = %d\n", rasconnstate);
            printf ("Projection completed.\n");
            break;
    #if (WINVER >= 0x400) 
        case RASCS_StartAuthentication:    // Windows 95 only 
            printf ("RASCS_StartAuthentication = %d\n", rasconnstate);
            printf ("Starting authentication...\n");

            break;
        case RASCS_CallbackComplete:       // Windows 95 only 
            printf ("RASCS_CallbackComplete = %d\n", rasconnstate);
            printf ("Callback complete.\n");
            break;
        case RASCS_LogonNetwork:           // Windows 95 only 
            printf ("RASCS_LogonNetwork = %d\n", rasconnstate);
            printf ("Login to the network.\n");
            break;
    #endif 
        case RASCS_SubEntryConnected:
            printf ("RASCS_SubEntryConnected = %d\n", rasconnstate);
            printf ("Subentry connected.\n");
            break;
        case RASCS_SubEntryDisconnected:
            printf ("RASCS_SubEntryDisconnected = %d\n", rasconnstate);
            printf ("Subentry disconnected.\n");
            break;
		//PAUSED STATES:
		case RASCS_Interactive:
            printf ("RASCS_Interactive = %d\n", rasconnstate);
            printf ("In Paused state: Interactive mode.\n");
            break;
		case RASCS_RetryAuthentication:
            printf ("RASCS_RetryAuthentication = %d\n", rasconnstate);
            printf ("In Paused state: Retry Authentication...\n");
            break;
		case RASCS_CallbackSetByCaller:
            printf ("RASCS_CallbackSetByCaller = %d\n", rasconnstate);
            printf ("In Paused state: Callback set by Caller.\n");
            break;
		case RASCS_PasswordExpired:
            printf ("RASCS_PasswordExpired = %d\n", rasconnstate);
            printf ("In Paused state: Password has expired...\n");
            break;
 
        case RASCS_Connected: // = RASCS_DONE: 
            printf ("RASCS_Connected = %d\n", rasconnstate);
            printf ("Connection completed.\n");
			SetEvent(Event_handle);
            break;
        case RASCS_Disconnected: 
            printf ("RASCS_Disconnected = %d\n", rasconnstate);
            printf ("Disconnecting...\n");
            break;
		default:
			printf ("Unknown Status = %d\n", rasconnstate);
			printf ("What are you going to do about it?\n");
			break;
   }
} 