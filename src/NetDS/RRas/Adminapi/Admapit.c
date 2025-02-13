/******************************************************************************
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved.
*       This sample source code is only intended as a supplement to
*       MprAdmin API usage and is meant to help users with the
*       MprAdmin API calling convention. Use this code at your own risk.
*       Microsoft disclaims any implied warranty. This sample code can
*       be copied and distributed.

******************************************************************************/

/********************************************************************
*  admapit.c -- Sample program demonstrating the use of different
*                     MprAdmin API
*
*  Comments:
*
* This program expects \\Servername  as its arguments.
*
* MprAdminGetErrorString API returns error string. However
* this API may return an Error 87 (Invalid Parameter) for the non
* RAS error codes. This API is designed for only RAS related error codes.
* For more Info. check the documentation. I am using this API for all the
* errors but I print the error codes before calling this API
*
*****************************************************************************/
/***************************************************************************
*  Functions:
*      Init2(void);
*      Init1(void);
*      PrintGetStringError(DWORD dwResult);
*      UserPrivilege(WCHAR *DomainName, WCHAR *UserName);
*      PrintPriv(WCHAR *DomainName, WCHAR *UserName);
*      PrintClearStats(WCHAR * RasSrv, WCHAR *wszPortName);
*      WINAPI RasAdminClearDisc(LPVOID param);
*      IsServiceRunning(WCHAR *RasSrv);
*      Debug_Print_Connection0(RAS_CONNECTION_0 *pRasConnection0);
*      Debug_Print_Connection1(RAS_CONNECTION_1 *pRasConnection1);
*      Debug_Print_RAS_PORT0(RAS_PORT_0 *pRasPort0);
*      Debug_Print_RAS_PORT1(RAS_PORT_1 *pRasPort1);
*      File_Print_Connection0(RAS_CONNECTION_0 *pRasConnection0);
*      File_Print_Connection1(RAS_CONNECTION_1 *pRasConnection1);
*      File_Print_RAS_PORT0(RAS_PORT_0 *pRasPort0);
*      File_Print_RAS_PORT1(RAS_PORT_1 *pRasPort1);
*      ProcPortClearStat(HANDLE hPort);
*      ProcConnectionClearStat(HANDLE hConnection);
*      ProcPortReset(HANDLE hPort);
*      ProcPortDisconnect(HANDLE hPort);
*      ProcConnectionGetInfo(HANDLE hConnection);
*      ProcPortGetInfo(HANDLE hPort);
*****************************************************************************/


#define  sleeptime 10000

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <lm.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <mprapi.h>
#include <memory.h>

#include <tchar.h>

//Function Definitions
VOID Init2(void);
VOID Init1(void);
VOID PrintGetStringError(DWORD dwResult);
VOID UserPrivilege(WCHAR *DomainName, WCHAR *UserName);
VOID PrintPriv(WCHAR *DomainName, WCHAR *UserName);
VOID PrintClearStats(WCHAR * RasSrv, WCHAR *wszPortName);
DWORD WINAPI RasAdminClearDisc(LPVOID param);
INT IsServiceRunning(WCHAR *RasSrv);
VOID Debug_Print_Connection0(RAS_CONNECTION_0 *pRasConnection0);
VOID Debug_Print_Connection1(RAS_CONNECTION_1 *pRasConnection1);
VOID Debug_Print_RAS_PORT0(RAS_PORT_0 *pRasPort0);
VOID Debug_Print_RAS_PORT1(RAS_PORT_1 *pRasPort1);
VOID File_Print_Connection0(RAS_CONNECTION_0 *pRasConnection0);
VOID File_Print_Connection1(RAS_CONNECTION_1 *pRasConnection1);
VOID File_Print_RAS_PORT0(RAS_PORT_0 *pRasPort0);
VOID File_Print_RAS_PORT1(RAS_PORT_1 *pRasPort1);
VOID ProcPortClearStat(HANDLE hPort);
VOID ProcConnectionClearStat(HANDLE hConnection);
VOID ProcPortReset(HANDLE hPort);
VOID ProcPortDisconnect(HANDLE hPort);
VOID ProcConnectionGetInfo(HANDLE hConnection);
VOID ProcPortGetInfo(HANDLE hPort);


// Global Variables
WCHAR*
StrDupWFromA(
    CHAR* psz );


#define Number_Of_Flags 6

HANDLE LogFile  = NULL;
HANDLE cLogFile = NULL;
HANDLE ErrLogFile = NULL;

CHAR buf[120];
WCHAR CallbackNumber[255];
BOOL First_Call = TRUE;
DWORD Status = 0;
DWORD dwResult = 0;
DWORD dwBytesWritten = 0;
CHAR szBuf[120];
BOOL ErrLogInValid = FALSE;
BOOL cErrLogInValid = FALSE;
BOOL LogInValid = TRUE;
BOOL FirstCall = TRUE;
WCHAR szUserAccountServer[UNLEN+1];
PRAS_USER_0 ppRasUser0;
RAS_USER_0 RasUser0;
WCHAR lpszServerName[50];
WCHAR RasSrv[64];
BOOL Quit=FALSE;

RAS_SERVER_HANDLE  phRasServer;


// Function Starts
WCHAR*
StrDupWFromA(
    CHAR* psz )

    /* Returns heap block containing a copy of 0-terminated string 'psz' or
    ** NULL on error or if 'psz' is NULL.  The output string is converted to
    ** UNICODE.  It is caller's responsibility to Free the returned string.
    */
{
   WCHAR* pszNew = NULL;

   if (psz)
   {
      DWORD cb;

      cb = MultiByteToWideChar( CP_ACP, 0, psz, -1, NULL, 0 );

      pszNew = malloc( cb * sizeof(TCHAR) );
      if (!pszNew)
      {
         return NULL;
      }

      cb = MultiByteToWideChar( CP_ACP, 0, psz, -1, pszNew, cb );
      if (cb == 0)
      {
         free( pszNew );
         return NULL;
      }
   }
   return pszNew;
}


//
// Format and write debug information to OutputDebugString
//
ULONG
_cdecl
DbgPrint(
    PCH Format,
    ...
    )
{
   CHAR szbuffer[255];
   WCHAR buffer[255];
   WCHAR *temp = NULL;
   LPINT lpResult=NULL;
   va_list marker;
   va_start (marker,Format);

//#ifdef  _M_ALPHA
//   if (IsTextUnicode( marker.a0, lstrlen(marker.a0),lpResult))
//#else
//   if (IsTextUnicode( marker, lstrlen(marker),lpResult))
//#endif
//   {
      temp = StrDupWFromA(Format);
      wvsprintfW (buffer,temp, marker);
//   }
//   else
//   {
//      wvsprintfA (szbuffer,Format, marker);
//      temp=StrDupWFromA(szbuffer);
//   }
   OutputDebugString (buffer);
   free(temp);
   return TRUE;
}

//
// Init Functions to setup logfiles
//

VOID Init1(void)
{
   //Store port  information in this file
   LogInValid = FALSE;
   LogFile = CreateFile(TEXT("Admin.log"),
                        GENERIC_READ|GENERIC_WRITE,
                        FILE_SHARE_READ,
                        (LPSECURITY_ATTRIBUTES) NULL,
                        CREATE_ALWAYS,
                        0,
                        (HANDLE) NULL);

   if (LogFile== INVALID_HANDLE_VALUE)
   {
      LogInValid = TRUE;
   }

}


VOID Init2(void)
{
   cErrLogInValid = FALSE;
   ErrLogInValid = FALSE;
   //Stores Statistics and port disconnect information in this file
   cLogFile = CreateFile(TEXT("AdminStats.log"),
                         GENERIC_READ|GENERIC_WRITE,
                         FILE_SHARE_READ,
                         (LPSECURITY_ATTRIBUTES) NULL,
                         CREATE_ALWAYS,
                         0,
                         (HANDLE) NULL);
   if (cLogFile== INVALID_HANDLE_VALUE)
   {
      cErrLogInValid = TRUE;
   }

   //Stores user privilege information in this file
   ErrLogFile = CreateFile(TEXT("AdminUser.log"),
                           GENERIC_READ|GENERIC_WRITE,
                           FILE_SHARE_READ,
                           (LPSECURITY_ATTRIBUTES) NULL,
                           CREATE_ALWAYS,
                           0,
                           (HANDLE) NULL);

   if (ErrLogFile== INVALID_HANDLE_VALUE)
   {
      ErrLogInValid = TRUE;
   }

}


//
// Function to print error strings
//
VOID PrintGetStringError(DWORD dwResult)
{
CHAR  szBuf[120];
DWORD dwBytesWritten = 0;

   DbgPrint("ERROR  MprAdminGetErrorString      %d\n",dwResult);
   sprintf(szBuf, "ERROR  MprAdminGetErrorString      %d\n",dwResult);
   WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
}


//
// Function to see if the service running
//
INT IsServiceRunning(WCHAR *RasSrv)
{
DWORD dwResult;
CHAR  szBuf[120];
DWORD dwBytesWritten = 0;

   //Calling MprAdminIsServiceRunning
   // Parameters:
   // IN LPWSTR   * RasSrv
   dwResult = MprAdminIsServiceRunning(RasSrv);
   //printf("Ras server: %s\n", *RasSrv);
   if (dwResult)
   {
      DbgPrint("Ras AND Router Serivce running on the Server\n");
      sprintf(szBuf, "Ras AND Router Serivce running on the Server\n");
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      //Calling MprAdminServerConnect
      // Parameters
      // IN LPWSTR    * RasSrv
      // OUT RAS_SERVER_HANDLE * phRasServer
      dwResult = MprAdminServerConnect(RasSrv, &phRasServer);
      if (dwResult != NO_ERROR)
      {
         DbgPrint("Failed to Connect to Server\n");
	 sprintf(szBuf, "Failed to Connect to Server: ERROR %d\n", dwResult);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
         return 0;
      }
   }
   else
   {
      DbgPrint("Ras AND Router Serivce is NOT running on the Server\n");
      sprintf(szBuf, "Ras AND Router Serivce is NOT running on the Server: ERROR %d\n", dwResult);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      return 0;
   }
   return 1;
}


//
// Function to print user privileges to logfile
//
VOID PrintPriv(WCHAR *DomainName, WCHAR *UserName)
{
DWORD Permission;
DWORD dwBytesWritten = 0;
CHAR  szBuf[120];

     /*********** from mprapi.h ****************************************************/
     //
     // Note: Bit 0 MUST represent NoCallback due to a quirk of the "userparms"
     //       storage method.  When a new LAN Manager user is created, bit 0 of the
     //       userparms field is set to 1 and all other bits are 0.  These bits are
     //       arranged so this "no Dial-In info" state maps to the "default Dial-In
     //       privilege" state.
     //
     // #define RASPRIV_NoCallback        0x01
     // #define RASPRIV_AdminSetCallback  0x02
     // #define RASPRIV_CallerSetCallback 0x04
     // #define RASPRIV_DialinPrivilege   0x08
     //
     // #define RASPRIV_CallbackType (RASPRIV_AdminSetCallback \
     //                             | RASPRIV_CallerSetCallback \
     //                             | RASPRIV_NoCallback)
     /*****************************************************************************/

     sprintf(szBuf,"\nDomainName =  %ws\nUserName = %ws\n",DomainName, UserName);
     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);

     sprintf(szBuf,"ppRasUser0->bfPrivilege = 0x%x\n",ppRasUser0->bfPrivilege);
     WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);

     //
     // display the privilege flags
     //
     if ((ppRasUser0->bfPrivilege) & (RASPRIV_NoCallback))
     {
        sprintf(szBuf, "\t\tRASPRIV_NoCallback        = 0x%x\n", (ppRasUser0->bfPrivilege & (RASPRIV_NoCallback)));
        WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     }
     if ((ppRasUser0->bfPrivilege) & (RASPRIV_AdminSetCallback))
     {
        sprintf(szBuf, "\t\tRASPRIV_AdminSetCallback  = 0x%x\n", (ppRasUser0->bfPrivilege & (RASPRIV_AdminSetCallback)));
        WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     }
     if ((ppRasUser0->bfPrivilege) & (RASPRIV_CallerSetCallback))
     {
        sprintf(szBuf, "\t\tRASPRIV_CallerSetCallback = 0x%x\n", (ppRasUser0->bfPrivilege & (RASPRIV_CallerSetCallback)));
        WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     }
     if ((ppRasUser0->bfPrivilege) & (RASPRIV_DialinPrivilege))
     {
        sprintf(szBuf, "\t\tRASPRIV_DialinPrivilege   = 0x%x\n", (ppRasUser0->bfPrivilege & (RASPRIV_DialinPrivilege)));
        WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
     }
}


//
// Function to get and change User Dialin Privileges.
// It goes through all the Dialin Privileges for a user.
//
VOID UserPrivilege(WCHAR *DomainName, WCHAR *UserName)
{
DWORD Status;
DWORD dwResult;
CHAR  szBuf[120];
DWORD dwBytesWritten = 0;
WCHAR Buf[512];
WCHAR *lpszString;
static BYTE Dialin = 9;
BYTE lpbBuffer;
lpszString = &Buf[0];
ppRasUser0 = &RasUser0;

   // API Called:     MprAdminGetPDCServer
   // Parameters:
   //  IN WCHAR * lpwsDomainName
   //  IN WCHAR * lpwsServerName
   //  OUT WCHAR * lpwsPDCServer


   dwResult = MprAdminGetPDCServer(DomainName, NULL, &szUserAccountServer[0]);

   if (dwResult != NO_ERROR)
   {   
	dwResult = MprAdminGetPDCServer(NULL, RasSrv, &szUserAccountServer[0]);
   };

   if (dwResult == NO_ERROR)
   {
      // API Called:     MprAdminUserGetInfo
      // Parameters:
      // IN WCHAR * lpwsServerName
      // IN WCHAR * lpwsUserName
      // IN DWORD dwLevel
      // OUT LPBYTE *lpbBuffer
      dwResult = MprAdminUserGetInfo(szUserAccountServer, UserName,(DWORD) 0, (LPBYTE) ppRasUser0);
      if (dwResult != NO_ERROR)
      {
         sprintf(szBuf,"ERROR MprAdminUserGetInfo     %d\n",dwResult);
         WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
         sprintf(szBuf,"Parameters in:\n\tlpszServer=%ws\n\tlpszUser=%ws\n\tdwLevel=0,\n\tlpbBuffer)\n",
                        szUserAccountServer, UserName);
         WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);

         dwResult = MprAdminGetErrorString( dwResult, &lpszString);
         if (dwResult == NO_ERROR)
         {
            sprintf(szBuf, "ERROR  MprAdminUserGetInfo: string from MprAdminGetErrorString:  %ws\n",lpszString);
            WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
         }
         else
            PrintGetStringError(dwResult);
      }
      else //MprAdminUserGetInfo returned success
      {
         ppRasUser0->bfPrivilege = (RASPRIV_DialinPrivilege | Dialin  );
	 wcscpy(ppRasUser0->wszPhoneNumber, CallbackNumber);
	 // API Called:     MprAdminUserSetInfo
         // Parameters:
         // IN WCHAR * lpwsServerName
         // IN WCHAR * lpwsUserName
         // IN DWORD dwLevel
         // IN LPBYTE lpbBuffer
         dwResult = MprAdminUserSetInfo(szUserAccountServer, UserName, 0, (LPBYTE)ppRasUser0);
         if (dwResult != NO_ERROR)
         {
            sprintf(szBuf,"ERROR: MprAdminUserSetInfo     %d\n",dwResult);
            WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);

            sprintf(szBuf,"Parameters in:\n\tlpszServer=%ws\n\tlpszUser=%ws\n\tdwLevel=0,\n\tlpbBuffer)\n",
                           szUserAccountServer, UserName);
            WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
            // dump this out to see what privileges were passed in UserSetInfo call
            PrintPriv(szUserAccountServer, UserName);

            dwResult = MprAdminGetErrorString( dwResult, &lpszString);
            if (dwResult == ERROR_SUCCESS)
            {
               sprintf(szBuf, "ERROR  MprAdminUserSetInfo: string from MprAdminGetErrorString:  %ws\n",lpszString);
               WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
            }
            else
               PrintGetStringError(dwResult);
         }
         else
	 {
	    PrintPriv(szUserAccountServer, UserName);
         }
         		
	 
	 //
         // cycle thru these Callback privilege values
         //
	 // Dialin = 9 : No Callback 
	 // Dialin = 10: Admin Sets Callback Number
	 // Dialin = 12: Caller Sets Callback Number
         switch (Dialin)
	 {
		case 9:
			Dialin = 10;
			break;
		case 10:
			Dialin = 12;
			break;
		case 12:
			Dialin = 9;
			break;
		default:
			break;
	 }

	 
      } // end of loop for MprAdminUserGetInfo returning success

   }
   else //MprAdminGetPDCServer returned an error
   {
      DbgPrint("ERROR  MprAdminGetPDCServer     %d\n",dwResult);
      sprintf(szBuf,"ERROR  MprAdminGetPDCServer     %d\n",dwResult);
      WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      sprintf(szBuf,"Parameters in:\n\tlpszDomain=%ws\n\tlpszServer=NULL\n", DomainName);
      WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);

      dwResult = MprAdminGetErrorString(dwResult, &lpszString);
      if (dwResult == NO_ERROR)
      {
         sprintf(szBuf, "ERROR  MprAdminGetPDCServer      %ws\n",lpszString);
         WriteFile(ErrLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }

}  //end UserPrivilege()



//
// dump connection0 struct to debug output
//
VOID Debug_Print_Connection0(RAS_CONNECTION_0 *pRasConnection0)
{
   WCHAR *Interface_Type[] =
   {
   TEXT("ROUTER_IF_TYPE_CLIENT"),
   TEXT("ROUTER_IF_TYPE_HOME_ROUTER"),
   TEXT("ROUTER_IF_TYPE_FULL_ROUTER"),
   TEXT("ROUTER_IF_TYPE_DEDICATED"),
   TEXT("ROUTER_IF_TYPE_INTERNAL"),
   TEXT("ROUTER_IF_TYPE_INTERNAL")
   };

   //dumping pRasConnection0
   DbgPrint("pRasConnection0->hConnection  0x%x\n",pRasConnection0->hConnection);
   DbgPrint("pRasConnection0->hInterface   0x%x\n",pRasConnection0->hInterface);
   DbgPrint("pRasConnection0->dwConnectDuration  %d\n",pRasConnection0->dwConnectDuration);
   DbgPrint("pRasConnection0->dwInterfaceType  %ws\n",Interface_Type[pRasConnection0->dwInterfaceType]);
   DbgPrint("pRasConnection0->dwConnectionFlags  %d\n",pRasConnection0->dwConnectionFlags);
   DbgPrint("pRasConnection0->wszInterfaceName  %ws\n",pRasConnection0->wszInterfaceName);
   DbgPrint("pRasConnection0->wszUserName  %ws\n",pRasConnection0->wszUserName);
   DbgPrint("pRasConnection0->wszLogonDomain  %ws\n",pRasConnection0->wszLogonDomain);
   DbgPrint("pRasConnection0->wszRemoteComputer  %ws\n",pRasConnection0->wszRemoteComputer);

   

    
}


//
// dump connection1 struct to debug output
//
VOID Debug_Print_Connection1(RAS_CONNECTION_1 *pRasConnection1)
{
    //dumping pRasConnection1
    DbgPrint( "\n\npRasConnection1->hConnection  0x%x\n",pRasConnection1->hConnection);
    DbgPrint( "pRasConnection1->hInterface   0x%x\n",pRasConnection1->hInterface);
    DbgPrint( "pRasConnection1->PppInfo.nbf.dwError %d\n",pRasConnection1->PppInfo.nbf.dwError);
    DbgPrint( "pRasConnection1->PppInfo.nbf.wszWksta %ws\n",pRasConnection1->PppInfo.nbf.wszWksta);
    DbgPrint( "pRasConnection1->PppInfo.ip.dwError %d\n",pRasConnection1->PppInfo.ip.dwError);
    DbgPrint( "pRasConnection1->PppInfo.ip.wszAddress %ws\n",pRasConnection1->PppInfo.ip.wszAddress);
    DbgPrint( "pRasConnection1->PppInfo.ip.wszRemoteAddress %ws\n",pRasConnection1->PppInfo.ip.wszRemoteAddress);
    DbgPrint( "pRasConnection1->PppInfo.ipx.dwError %d\n",pRasConnection1->PppInfo.ipx.dwError);
    DbgPrint( "pRasConnection1->PppInfo.ipx.wszAddress %ws\n",pRasConnection1->PppInfo.ipx.wszAddress);
    DbgPrint( "pRasConnection1->PppInfo.at.dwError  %d\n",pRasConnection1->PppInfo.at.dwError );
    DbgPrint( "pRasConnection1->PppInfo.at.wszAddress %ws\n",pRasConnection1->PppInfo.at.wszAddress);
	
    //connection stats
    DbgPrint( "pRasConnection1->dwBytesXmited=%d\n", pRasConnection1->dwBytesXmited );
    DbgPrint( "pRasConnection1->dwBytesRcved=%d\n", pRasConnection1->dwBytesRcved );
    DbgPrint( "pRasConnection1->dwFramesXmited=%d\n", pRasConnection1->dwFramesXmited );
    DbgPrint( "pRasConnection1->dwFramesRcved=%d\n", pRasConnection1->dwFramesRcved);
    DbgPrint( "pRasConnection1->dwCrcErr=%d\n", pRasConnection1->dwCrcErr);
    DbgPrint( "pRasConnection1->dwTimeoutErr=%d\n", pRasConnection1->dwTimeoutErr);
    DbgPrint( "pRasConnection1->dwAlignmentErr=%d\n", pRasConnection1->dwAlignmentErr);
    DbgPrint( "pRasConnection1->dwHardwareOverrunErr=%d\n", pRasConnection1->dwHardwareOverrunErr);
    DbgPrint( "pRasConnection1->dwFramingErr=%d\n", pRasConnection1->dwFramingErr);
    DbgPrint( "pRasConnection1->dwBufferOverrunErr=%d\n", pRasConnection1->dwBufferOverrunErr);
}



//
// dump port0 struct to debug output
//
VOID Debug_Print_RAS_PORT0(RAS_PORT_0 *pRasPort0)
{
WCHAR *Line_Condition[] =
   {
   TEXT("RAS_PORT_NON_OPERATIONAL"),
   TEXT("RAS_PORT_DISCONNECTED"),
   TEXT("RAS_PORT_CALLING_BACK"),
   TEXT("RAS_PORT_LISTENING"),
   TEXT("RAS_PORT_AUTHENTICATING"),
   TEXT("RAS_PORT_AUTHENTICATED"),
   TEXT("RAS_PORT_INITIALIZING")
   };

WCHAR *Hdw_Error[] =
   {
   TEXT("RAS_HARDWARE_OPERATIONAL"),
   TEXT("RAS_HARDWARE_FAILURE")
   };

   //dumping pRasPort0
   DbgPrint("pRasPort0->hPort  %d\n",pRasPort0->hPort);
   DbgPrint("pRasPort0->hConnection   0x%x\n",pRasPort0->hConnection);
   DbgPrint("pRasPort0->dwPortCondition  %ws\n",Line_Condition[pRasPort0->dwPortCondition-1]);
   DbgPrint("pRasPort0->dwTotalNumberOfCalls  %d\n",pRasPort0->dwTotalNumberOfCalls);
   DbgPrint("pRasPort0->dwConnectDuration  %d\n",pRasPort0->dwConnectDuration);
   DbgPrint("pRasPort0->wszPortName  %ws\n",pRasPort0->wszPortName);
   DbgPrint("pRasPort0->wszMediaName  %ws\n",pRasPort0->wszMediaName);
   DbgPrint("pRasPort0->wszDeviceName  %ws\n",pRasPort0->wszDeviceName);
   DbgPrint("pRasPort0->wszDeviceType  %ws\n",pRasPort0->wszDeviceType);

}



//
// dump port1 struct to debug output
//
VOID Debug_Print_RAS_PORT1(RAS_PORT_1 *pRasPort1)
{
WCHAR *Line_Condition[] =
   {
   TEXT("RAS_PORT_NON_OPERATIONAL"),
   TEXT("RAS_PORT_DISCONNECTED"),
   TEXT("RAS_PORT_CALLING_BACK"),
   TEXT("RAS_PORT_LISTENING"),
   TEXT("RAS_PORT_AUTHENTICATING"),
   TEXT("RAS_PORT_AUTHENTICATED"),
   TEXT("RAS_PORT_INITIALIZING")
   };

WCHAR *Hdw_Error[] =
   {
   TEXT("RAS_HARDWARE_OPERATIONAL"),
   TEXT("RAS_HARDWARE_FAILURE")
   };

   //dumping pRasPort1
   DbgPrint("pRasPort1->hPort  %d\n",pRasPort1->hPort);
   DbgPrint("pRasPort1->hConnection   0x%x\n",pRasPort1->hConnection);
   DbgPrint("pRasPort1->dwHardwareCondition  %ws\n",Hdw_Error[pRasPort1->dwHardwareCondition]);

   //connection stats
   DbgPrint( "pRasPort1->dwLineSpeed=%d\n", pRasPort1->dwLineSpeed );
   DbgPrint( "pRasPort1->dwBytesXmited=%d\n", pRasPort1->dwBytesXmited );
   DbgPrint( "pRasPort1->dwBytesRcved=%d\n", pRasPort1->dwBytesRcved );
   DbgPrint( "pRasPort1->dwFramesXmited=%d\n", pRasPort1->dwFramesXmited );
   DbgPrint( "pRasPort1->dwFramesRcved=%d\n", pRasPort1->dwFramesRcved);
   DbgPrint( "pRasPort1->dwCrcErr=%d\n", pRasPort1->dwCrcErr);
   DbgPrint( "pRasPort1->dwTimeoutErr=%d\n", pRasPort1->dwTimeoutErr);
   DbgPrint( "pRasPort1->dwAlignmentErr=%d\n", pRasPort1->dwAlignmentErr);
   DbgPrint( "pRasPort1->dwHardwareOverrunErr=%d\n", pRasPort1->dwHardwareOverrunErr);
   DbgPrint( "pRasPort1->dwFramingErr=%d\n", pRasPort1->dwFramingErr);
   DbgPrint( "pRasPort1->dwBufferOverrunErr=%d\n", pRasPort1->dwBufferOverrunErr);
}


//
// dump connection0 struct to logfile
//
VOID File_Print_Connection0(RAS_CONNECTION_0 *pRasConnection0)
{
WCHAR *Interface_Type[] =
   {
   TEXT("ROUTER_IF_TYPE_CLIENT"),
   TEXT("ROUTER_IF_TYPE_HOME_ROUTER"),
   TEXT("ROUTER_IF_TYPE_FULL_ROUTER"),
   TEXT("ROUTER_IF_TYPE_DEDICATED"),
   TEXT("ROUTER_IF_TYPE_INTERNAL"),
   TEXT("ROUTER_IF_TYPE_INTERNAL")
   };

   //dumping pRasConnection0
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"dumping pRasConnection0\n\n");
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->hConnection  0x%x\n",pRasConnection0->hConnection);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->hInterface   0x%x\n",pRasConnection0->hInterface);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->dwConnectDuration  %d\n",pRasConnection0->dwConnectDuration);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->dwInterfaceType  %ws\n",Interface_Type[pRasConnection0->dwInterfaceType]);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->dwConnectionFlags  %d\n",pRasConnection0->dwConnectionFlags);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->wszInterfaceName  %ws\n",pRasConnection0->wszInterfaceName);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->wszUserName  %ws\n",pRasConnection0->wszUserName);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->wszLogonDomain  %ws\n",pRasConnection0->wszLogonDomain);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasConnection0->wszRemoteComputer  %ws\n",pRasConnection0->wszRemoteComputer);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);

}


//
// dump connection1 info to logfile
//
VOID File_Print_Connection1(RAS_CONNECTION_1 *pRasConnection1)
{

   //dumping pRasConnection1
   sprintf(buf,"dumping pRasConnection1\n");
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "\n\npRasConnection1->hConnection  0x%x\n",pRasConnection1->hConnection);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->hInterface   0x%x\n",pRasConnection1->hInterface);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.nbf.dwError %d\n",pRasConnection1->PppInfo.nbf.dwError);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.nbf.wszWksta %ws\n",pRasConnection1->PppInfo.nbf.wszWksta);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.ip.dwError %d\n",pRasConnection1->PppInfo.ip.dwError);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.ip.wszAddress %ws\n",pRasConnection1->PppInfo.ip.wszAddress);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.ip.wszRemoteAddress %ws\n",pRasConnection1->PppInfo.ip.wszRemoteAddress);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.ipx.dwError %d\n",pRasConnection1->PppInfo.ipx.dwError);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.ipx.wszAddress %ws\n",pRasConnection1->PppInfo.ipx.wszAddress);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.at.dwError  %d\n",pRasConnection1->PppInfo.at.dwError );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->PppInfo.at.wszAddress %ws\n",pRasConnection1->PppInfo.at.wszAddress);

   //connection stats
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwBytesXmited=%d\n", pRasConnection1->dwBytesXmited );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwBytesRcved=%d\n", pRasConnection1->dwBytesRcved );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwFramesXmited=%d\n", pRasConnection1->dwFramesXmited );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwFramesRcved=%d\n", pRasConnection1->dwFramesRcved);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwCrcErr=%d\n", pRasConnection1->dwCrcErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwTimeoutErr=%d\n", pRasConnection1->dwTimeoutErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwAlignmentErr=%d\n", pRasConnection1->dwAlignmentErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwHardwareOverrunErr=%d\n", pRasConnection1->dwHardwareOverrunErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwFramingErr=%d\n", pRasConnection1->dwFramingErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasConnection1->dwBufferOverrunErr=%d\n", pRasConnection1->dwBufferOverrunErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
}



//
// dump port0 info to logfile
//
VOID File_Print_RAS_PORT0(RAS_PORT_0 *pRasPort0)
{
WCHAR *Line_Condition[] =
   {
   TEXT("RAS_PORT_NON_OPERATIONAL"),
   TEXT("RAS_PORT_DISCONNECTED"),
   TEXT("RAS_PORT_CALLING_BACK"),
   TEXT("RAS_PORT_LISTENING"),
   TEXT("RAS_PORT_AUTHENTICATING"),
   TEXT("RAS_PORT_AUTHENTICATED"),
   TEXT("RAS_PORT_INITIALIZING")
   };

WCHAR *Hdw_Error[] =
   {
   TEXT("RAS_HARDWARE_OPERATIONAL"),
   TEXT("RAS_HARDWARE_FAILURE")
   };

   //dumping pRasPort0 to a file
   sprintf(buf,"dumping pRasPort0 to file\n");
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->hPort  %d\n",pRasPort0->hPort);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->hConnection   0x%x\n",pRasPort0->hConnection);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->dwPortCondition  %ws\n",Line_Condition[pRasPort0->dwPortCondition-1]);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->dwTotalNumberOfCalls  %d\n",pRasPort0->dwTotalNumberOfCalls);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->dwConnectDuration  %d\n",pRasPort0->dwConnectDuration);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->wszPortName  %ws\n",pRasPort0->wszPortName);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->wszMediaName  %ws\n",pRasPort0->wszMediaName);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->wszDeviceName  %ws\n",pRasPort0->wszDeviceName);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort0->wszDeviceType  %ws\n",pRasPort0->wszDeviceType);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);

}



//
// dump port1 info to logfile
//
VOID File_Print_RAS_PORT1(RAS_PORT_1 *pRasPort1)
{
WCHAR *Line_Condition[] =
   {
   TEXT("RAS_PORT_NON_OPERATIONAL"),
   TEXT("RAS_PORT_DISCONNECTED"),
   TEXT("RAS_PORT_CALLING_BACK"),
   TEXT("RAS_PORT_LISTENING"),
   TEXT("RAS_PORT_AUTHENTICATING"),
   TEXT("RAS_PORT_AUTHENTICATED"),
   TEXT("RAS_PORT_INITIALIZING")
   };

WCHAR *Hdw_Error[] =
   {
   TEXT("RAS_HARDWARE_OPERATIONAL"),
   TEXT("RAS_HARDWARE_FAILURE")
   };


   //dumping pRasPort1
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"\n dumping pRasPort1\n");
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort1->hPort  %d\n",pRasPort1->hPort);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort1->hConnection   0x%x\n",pRasPort1->hConnection);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf,"pRasPort1->dwHardwareCondition  %ws\n",Hdw_Error[pRasPort1->dwHardwareCondition]);

   //connection stats
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwLineSpeed=%d\n", pRasPort1->dwLineSpeed );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwBytesXmited=%d\n", pRasPort1->dwBytesXmited );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwBytesRcved=%d\n", pRasPort1->dwBytesRcved );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwFramesXmited=%d\n", pRasPort1->dwFramesXmited );
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwFramesRcved=%d\n", pRasPort1->dwFramesRcved);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwCrcErr=%d\n", pRasPort1->dwCrcErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwTimeoutErr=%d\n", pRasPort1->dwTimeoutErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwAlignmentErr=%d\n", pRasPort1->dwAlignmentErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwHardwareOverrunErr=%d\n", pRasPort1->dwHardwareOverrunErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwFramingErr=%d\n", pRasPort1->dwFramingErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);
   sprintf(buf, "pRasPort1->dwBufferOverrunErr=%d\n", pRasPort1->dwBufferOverrunErr);
   WriteFile(cLogFile, (LPSTR)buf, strlen(buf), &dwBytesWritten, NULL);

}


//
// Function to clear port statistics.
//
VOID ProcPortClearStat(HANDLE hPort)
{
DWORD dwBytesWritten = 0;
CHAR szBuf[120];
CHAR buf[120];
WCHAR Buf[512];
WCHAR *lpszString;
lpszString = &Buf[0];

   // API Called:     MprAdminPortClearStats
   // Parameters:
   // IN RAS_SERVER_HANDLE phRasServer
   // IN HANDLE  hPort
   Status = MprAdminPortClearStats(phRasServer, hPort);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminPortClearStats   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString(Status,&lpszString);
      if (dwResult == ERROR_SUCCESS)
      {
         DbgPrint("ERROR  MprAdminPortClearStats      %ws\n",lpszString);
         sprintf(szBuf, "ERROR  MprAdminPortClearStats      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      DbgPrint("\n\nMprAdminPortClearStats Called From ProcPortClearStat, Now dumping structs \n");
      sprintf(szBuf, "\n\nMprAdminPortClearStats Called From ProcPortClearStat, Now dumping structs\n");
      WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      ProcPortGetInfo(hPort);
   }

}



//
// Function to clear connection statistics.
//
VOID ProcConnectionClearStat(HANDLE hConnection)
{
DWORD dwBytesWritten = 0;
CHAR szBuf[120];
CHAR buf[120];
WCHAR Buf[512];
WCHAR *lpszString;
lpszString = &Buf[0];

   // API Called:     MprAdminConnectionClearStats
   // Parameters:
   // IN RAS_SERVER_HANDLE  phRasServer
   // IN HANDLE  hConnection
   Status = MprAdminConnectionClearStats(phRasServer, hConnection);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminConnectionClearStats   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString(Status, &lpszString);
      if (dwResult == ERROR_SUCCESS)
      {
         DbgPrint("ERROR  MprAdminConnectionClearStats      %ws\n",lpszString);
         sprintf(szBuf, "ERROR  MprAdminConnectionClearStats      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      DbgPrint("\n\nMprAdminConnectionClearStats Called From ProcConnectionClearStat, Now dumping structs \n");
      sprintf(szBuf, "\n\nMprAdminConnectionClearStats Called From ProcConnectionClearStat, Now dumping structs\n");
      WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      ProcConnectionGetInfo(hConnection);
   }
}


//
// Function to reset port.
//
VOID ProcPortReset(HANDLE hPort)
{
DWORD dwBytesWritten = 0;
CHAR szBuf[120];
CHAR buf[120];
WCHAR Buf[512];
WCHAR *lpszString;
lpszString = &Buf[0];

   // API Called:     MprAdminPortReset
   // Parameters:
   // IN RAS_SERVER_HANDLE  phRasServer
   // IN HANDLE  hPort
   Status = MprAdminPortReset(phRasServer, hPort);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminPortReset   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString(Status, &lpszString);
      if (dwResult == ERROR_SUCCESS)
      {
         DbgPrint("ERROR  MprAdminPortReset      %ws\n",lpszString);
         sprintf(szBuf, "ERROR  MprAdminPortReset      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      DbgPrint("\n\nMprAdminPortReset Called From ProcPortReset, Now dumping structs \n");
      sprintf(szBuf, "\n\nMprAdminPortReset Called From ProcPortReset, Now dumping structs\n");
      WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      ProcPortGetInfo(hPort);
   }
}


//
// Function to disconnect port.
//
VOID ProcPortDisconnect(HANDLE hPort)
{
DWORD dwBytesWritten = 0;
CHAR szBuf[120];
CHAR buf[120];
WCHAR Buf[512];
WCHAR *lpszString;
lpszString = &Buf[0];

   // API Called:     MprAdminPortDisconnect
   // Parameters:
   // IN RAS_SERVER_HANDLE  phRasServer
   // IN HANDLE  hPort
   Status = MprAdminPortDisconnect(phRasServer, hPort);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminPortDisconnect   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString( Status, &lpszString);
      if (dwResult == ERROR_SUCCESS)
      {
         DbgPrint("ERROR  MprAdminPortDisconnect      %ws\n",lpszString);
         sprintf(szBuf, "ERROR  MprAdminPortDisconnect      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
}



//
// Function to reset port statistics
//
DWORD WINAPI RasAdminClearDisc(LPVOID param)
{
CHAR option= ' ';
WORD i = 0;
INT  k = 0;

   while (!Quit)
   {
      // If the user hits q or Q then this will exit gracefully.
      // It may take some time to exit though.
      printf("Type Q to Quit\n");
      do
      {
         option=_getch();
         option =toupper(option);
         printf("%c\n",option);
      } while (((option) != 'q')&& ((option) != 'Q'));

      if (option == 'Q')
      {
         Quit = TRUE;
      }
   }
   return(0);
}

VOID ProcConnectionGetInfo(HANDLE hConnection)
{
RAS_CONNECTION_0 *pRasConnection0;
RAS_CONNECTION_1 *pRasConnection1;
LPBYTE lplpbBuffer;
DWORD dwBytesWritten = 0;
CHAR  szBuf[120];
WCHAR *lpszString;
WCHAR Buf[512];
lpszString = &Buf[0];

   // API Called: MprAdminConnectionGetInfo
   // Parameters:
   // IN  RAS_SERVER_HANDLE phRasServer
   // IN DWORD    dwLevel
   // IN HANDLE   hConnection
   // OUT LPBYTE * lplpbBuffer
   Status = MprAdminConnectionGetInfo(phRasServer,0,hConnection,&lplpbBuffer);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminConnectionGetInfo   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString( Status, &lpszString);
      if (dwResult == NO_ERROR)
      {
         sprintf(szBuf,"ERROR  MprAdminConnectionGetInfo      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      pRasConnection0 = (RAS_CONNECTION_0 *) lplpbBuffer;
      sprintf(szBuf, "\n\nDumping RpRasConnection0::Called from ProcConnectionGetinfo:->MprAdminConnectionGetInfo\n");
              WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      File_Print_Connection0(pRasConnection0);
      DbgPrint("\n\nDumping RpRasConnection0::Called from ProcConnectionGetinfo:->MprAdminConnectionGetInfo\n");
      Debug_Print_Connection0(pRasConnection0);
      MprAdminBufferFree(pRasConnection0);
   }

   Status = MprAdminConnectionGetInfo(phRasServer,1,hConnection,&lplpbBuffer);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminConnectionGetInfo   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString( Status, &lpszString);
      if (dwResult == NO_ERROR)
      {
         sprintf(szBuf,"ERROR  MprAdminConnectionGetInfo      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      pRasConnection1 = (RAS_CONNECTION_1 *) lplpbBuffer;
      sprintf(szBuf, "\n\nDumping RpRasConnection1::Called from ProcConnectionGetinfo:->MprAdminConnectionGetInfo\n");
      WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      File_Print_Connection1(pRasConnection1);
      DbgPrint("\n\nDumping RpRasConnection1::Called from ProcConnectionGetinfo:->MprAdminConnectionGetInfo\n");
      Debug_Print_Connection1(pRasConnection1);
      MprAdminBufferFree(pRasConnection1);
   }
}


//
// get port info
//
VOID ProcPortGetInfo(HANDLE hPort)
{
RAS_PORT_0 *pRasPort0;
RAS_PORT_1 *pRasPort1;
LPBYTE lplpbBuffer;
DWORD dwBytesWritten = 0;
CHAR  szBuf[120];
WCHAR *lpszString;
WCHAR Buf[512];
lpszString = &Buf[0];

   // API Called: MprAdminPortGetInfo
   // Parameters:
   // IN  RAS_SERVER_HANDLE phRasServer
   // IN DWORD    dwLevel
   // IN HANDLE   hPort
   // OUT LPBYTE * lplpbBuffer
   Status = MprAdminPortGetInfo(phRasServer,0,hPort,&lplpbBuffer);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminPortGetInfo   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString( Status, &lpszString);
      if (dwResult == NO_ERROR)
      {
         sprintf(szBuf,"ERROR  MprAdminPortGetInfo      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      pRasPort0 = (RAS_PORT_0 *) lplpbBuffer;
      sprintf(szBuf, "\n\nDumping RpRasPort0::Called from ProcPortGetInfo:-> MprAdminPortGetInfo\n");
      WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      File_Print_RAS_PORT0(pRasPort0);
      DbgPrint("\n\nDumping RpRasPort0::Called from ProcPortGetInfo:->MprAdminPortGetInfo\n");
      Debug_Print_RAS_PORT0(pRasPort0);
      MprAdminBufferFree(pRasPort0);
   }

   Status = MprAdminPortGetInfo(phRasServer,1,hPort,&lplpbBuffer);
   if (Status != NO_ERROR)
   {
      sprintf(szBuf, "ERROR MprAdminPortGetInfo   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString( Status, &lpszString);
      if (dwResult == NO_ERROR)
      {
         sprintf(szBuf,"ERROR  MprAdminPortGetInfo      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else
   {
      pRasPort1 = (RAS_PORT_1 *) lplpbBuffer;
      sprintf(szBuf, "\n\nDumping pRasPort1::Called from ProcPortGetInfo:->MprAdminPortGetInfo\n");
      WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      File_Print_RAS_PORT1(pRasPort1);
      DbgPrint("\n\nDumping RpRasConnection1::Called from ProcPortGetInfo:->MprAdminPortGetInfo\n");
      Debug_Print_RAS_PORT1(pRasPort1);
      MprAdminBufferFree(pRasPort1);
   }
}


/*************************************************************************/
/***************** Start Main ********************************************/
/*************************************************************************/

void _cdecl main(int argc, char **argv)
{
INT LoopPriv = 0;
INT Error = 0;
CHAR szBuf[120];
DWORD dwBytesWritten = 0;
DWORD Dialin = 1;
WORD Entries;
WORD i = 0;
DWORD id = 0;
WCHAR *lpszString;
WCHAR Buf[512];
HANDLE ConnectDiscThread;
LPBYTE lplpbBuffer;
DWORD dwPrefMaxLen;
DWORD lpdwEntriesRead = 0;
DWORD lpdwTotalEntries = 0;
LPDWORD lpdwResumeHandle=NULL;
RAS_CONNECTION_0 *pRasConnection0;
RAS_CONNECTION_1 *pRasConnection1;
LPBYTE plplpbBuffer;
DWORD plpdwPrefMaxLen = 0;
DWORD plpdwEntriesRead = 0;
DWORD plpdwTotalEntries = 0;
DWORD plpdwResumeHandle = 0;
RAS_PORT_0 *pRasPort0;
HANDLE hConnection = 0;
lpszString = &Buf[0];

 if (argc > 1)
 {
    mbstowcs(RasSrv, argv[1], 32) ;
 }
 Init1();
 Init2();
 Error=IsServiceRunning(RasSrv);
 if (!Error)
 {
    printf ("Ras Server is not started on the system");
    exit(0);
 }
 printf("Please specify the Client's phone number or IP address\n");
 scanf("%ws", CallbackNumber);
 ConnectDiscThread = CreateThread (NULL,
                                  0,
                                  &RasAdminClearDisc,
                                  (LPVOID) id,
                                  0,
                                  &id);
 while (!Quit)
 {
 // API Called:     MprAdminConnectionEnum
 // Parameters:
 //  IN RAS_SERVER_HANDLE phRasServer
 //  IN DWORD dwLevel
 //  OUT LPBYTE * lplpbBuffer    (RAS_CONNECTION_0 array)
 //  IN DWORD dwPrefMaxLen
 //  OUT LPDWORD lpdwEntriesRead
 //  OUT LPDWORD lpdwdTotalEntries
 //  IN  LPDWORD lpdwResumeHandle  OPTIONAL

 // Free up lplpbBuffer by calling MprAdminFreeBuffer API

   lpdwEntriesRead = 0;

   Status = MprAdminConnectionEnum(phRasServer,(DWORD) 0,&lplpbBuffer,(DWORD)-1,
                                   &lpdwEntriesRead,&lpdwTotalEntries,lpdwResumeHandle);
   if (Status != NO_ERROR)  //error
   {  
      sprintf(szBuf, "ERROR MprAdminConnectionEnum   %d\n",Status);
      WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      dwResult = MprAdminGetErrorString( Status, &lpszString);
      if (dwResult == NO_ERROR)
      {
         sprintf(szBuf,"ERROR  MprAdminConnectionEnum      %ws\n",lpszString);
         WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
      }
      else
         PrintGetStringError(dwResult);
   }
   else  //no error
   {  
      if (lpdwEntriesRead == lpdwTotalEntries)
      {
         pRasConnection0 = (RAS_CONNECTION_0 *) lplpbBuffer;
         for (i=0; i < (DWORD)lpdwTotalEntries;i++)
         {
            sprintf(szBuf, "\n\nDumping RpRasConnection0::Called from MprAdminConnectionEnum\n");
            WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
            File_Print_Connection0(&pRasConnection0[i]);
            DbgPrint("\n\nDumping RpRasConnection0::Called from MprAdminConnectionEnum\n");
            Debug_Print_Connection0(&pRasConnection0[i]);
            ProcConnectionGetInfo(pRasConnection0[i].hConnection);
            // pass hConnection = handle from MprAdminConnectionEnum
            hConnection = pRasConnection0[i].hConnection;
            //alternatively, could pass hConnection = INVALID_HANDLE_VALUE;
            Sleep (500);
            // A good idea is to call UserPrivilege outside the loop. It doesn't really
            // make sense to go through the privilege change for every iteration.
            // However, this code is just intended to demonstrate the usage.
            if (lpdwEntriesRead > 0)
	    {
		UserPrivilege(pRasConnection0[i].wszLogonDomain,pRasConnection0[i].wszUserName);
	    }
            ProcConnectionClearStat(pRasConnection0[i].hConnection);
            // API Called:     MprAdminPortEnum
            // Parameters:
            //  IN RAS_SERVER_HANDLE phRasServer
            //  IN DWORD pdwLevel
            //  HANDLE hConnection
            //  OUT LPBYTE * plplpbBuffer    (RAS_PORT_0 array)
            //  IN DWORD pdwPrefMaxLen
            //  OUT LPDWORD plpdwEntriesRead
            //  OUT LPDWORD plpdwdTotalEntries
            //  IN  LPDWORD plpdwResumeHandle  OPTIONAL

            // Free up lplpbBuffer by calling MprAdminFreeBuffer API
            Status = MprAdminPortEnum(phRasServer,(DWORD) 0,hConnection, &plplpbBuffer,
                        (DWORD) -1, &plpdwEntriesRead, &plpdwTotalEntries, &plpdwResumeHandle);
            if (Status != NO_ERROR)
            {
               sprintf(szBuf, "ERROR MprAdminPortEnum   %d\n",Status);
               WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
               dwResult = MprAdminGetErrorString( Status, &lpszString);
               if (dwResult == NO_ERROR)
               {
                  sprintf(szBuf,"ERROR  MprAdminPortEnum      %ws\n",lpszString);
                  WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
               }
               else
                  PrintGetStringError(dwResult);
            }
            else
            {
               if (plpdwEntriesRead == plpdwTotalEntries)
               {
                  pRasPort0 = (RAS_PORT_0 *) plplpbBuffer;
                  for (i=0; i < (DWORD)plpdwTotalEntries;i++)
                  {
                     sprintf(szBuf, "\n\nDumping pRasPort0::Called from MprAdminPortEnum\n");
                     WriteFile(cLogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);
                     File_Print_RAS_PORT0(&pRasPort0[i]);
                     DbgPrint("\n\nDumping RpRasPort0::Called from MprAdminPortEnum\n");
                     Debug_Print_RAS_PORT0(&pRasPort0[i]);
                     ProcPortGetInfo(pRasPort0[i].hPort);
                     Sleep (500);
                     ProcPortClearStat(pRasPort0[i].hPort);
                     Sleep (500);
                     ProcPortReset(pRasPort0[i].hPort);
                     Sleep (500);
                     ProcPortDisconnect(pRasPort0[i].hPort);
                  }
               }
               MprAdminBufferFree(pRasPort0);
            }
         }
      }
      MprAdminBufferFree(pRasConnection0);
   }

   CloseHandle(LogFile);
   Sleep(sleeptime);
   Init1();

 } //end of loop: while (!Quit)


 WaitForSingleObject(ConnectDiscThread,INFINITE);


 //Calling MprAdminServerDisconnect (type VOID, returns nothing)
 // Parameters
 // IN RAS_SERVER_HANDLE * phRasServer
 MprAdminServerDisconnect(phRasServer);
 DbgPrint("info: called MprAdminServerDisconnect(hRasServer=0x%x)\n", phRasServer);
 sprintf(szBuf, "info: called MprAdminServerDisconnect(hRasServer=0x%x)\n", phRasServer);
 WriteFile(LogFile, (LPSTR)szBuf, strlen(szBuf), &dwBytesWritten, NULL);

 //
 // close logfiles
 //
 CloseHandle(LogFile);
 CloseHandle(cLogFile);
 CloseHandle(ErrLogFile);


} // Main End
