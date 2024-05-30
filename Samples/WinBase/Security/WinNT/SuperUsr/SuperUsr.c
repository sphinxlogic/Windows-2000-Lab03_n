/*
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.


This code sample requires the following import library:
    advapi32.lib

Note:  This sample does not run on Windows 2000.
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <accctrl.h>
#include <aclapi.h>

#define SD_SIZE (65536 + SECURITY_DESCRIPTOR_MIN_LENGTH)
#define SYSTEM_PID 2

#define PERR(s) fprintf(stderr, "%s(%d) %s : Error %d\n%s\n", \
                   __FILE__, __LINE__, (s), GetLastError(), \
         GetLastErrorText())

BOOL EnableDebugPriv(void);
BOOL ModifySecurity(HANDLE hProc, DWORD dwAccess);
LPSTR GetLastErrorText(void);


void main( int argc, char * argv[] )
{

   HANDLE hProc;
   HANDLE hToken;
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   BOOL                bResult;

   if(!EnableDebugPriv())
   {
      printf("You probably don't have the SE_DEBUG_NAME privilege\n");
      exit(0);
   }

   //
   // PID 2 is always(?) associated with the
   // "system" process which has the context we
   // are after - local system
   //
   if(!(hProc = OpenProcess(
      PROCESS_ALL_ACCESS,
      FALSE,
      SYSTEM_PID)))
   {
      PERR("OpenProcess");
      printf("You are probably not a member of the administrator group\n");
      exit(0);
   }

   //
   // Open the process token with this access
   // so that we can modify the DACL and add
   // TOKEN_DUPLICATE & TOKEN_ASSIGN_PRIMARY
   // rights for this user
   //
   bResult = OpenProcessToken(
      hProc,
      READ_CONTROL|WRITE_DAC,
      &hToken);
   if (bResult == FALSE)
   {
      PERR("OpenProcessToken");
      exit(0);
   }

   if(!ModifySecurity(
      hToken,
      TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_QUERY))
   {
      exit(0);
   }

   CloseHandle(hToken);

   //
   // Close that handle and get a new one with the right
   // privilege level
   //

   bResult = OpenProcessToken(
      hProc,
      TOKEN_QUERY|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY,
      &hToken);
   if (FALSE == bResult)
   {
      PERR("OpenProcessToken");
      exit(0);
   }

   //
   // setup STARTUPINFO structure
   //
   memset( &si, 0, sizeof(STARTUPINFO) );
   si.cb = sizeof(STARTUPINFO);
   si.lpDesktop = "winsta0\\default";

   if( !CreateProcessAsUser(
      hToken,
      NULL,
      "cmd.exe",
      NULL, // default process attributes
      NULL, // default thread attributes
      FALSE, // don't inherit handles
      CREATE_NEW_CONSOLE,
      NULL,  // inherit environment
      NULL,  // same directory
      &si,
      &pi ) )

      PERR( "CreateProcessAsUser" );
   else
      printf( "\"SuperUsr\" mode console started!\n" );

   CloseHandle(hProc);
   CloseHandle(hToken);

}

BOOL EnableDebugPriv(void)
{
   TOKEN_PRIVILEGES tp;
   HANDLE hToken;
   LUID luid;

   if(!OpenProcessToken(
      GetCurrentProcess(),
      TOKEN_ADJUST_PRIVILEGES,
      &hToken ))
   {
      PERR("OpenProcessToken");
      return(FALSE);
   }

   if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
   {
      PERR("LookupPrivilegeValue");
      CloseHandle(hToken);
      return(FALSE);
   }

   tp.PrivilegeCount           = 1;
   tp.Privileges[0].Luid       = luid;
   tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   if(!AdjustTokenPrivileges(
      hToken,
      FALSE,
      &tp,
      sizeof(TOKEN_PRIVILEGES),
      NULL,
      NULL ))
   {
      PERR("AdjustTokenPrivileges");
      CloseHandle(hToken);
      return(FALSE);
   }

   CloseHandle(hToken);

   return(TRUE);

}


BOOL ModifySecurity(HANDLE hProc, DWORD dwAccess)
{
   UCHAR          ucSDbuf[SD_SIZE];
   PSECURITY_DESCRIPTOR pSD=(PSECURITY_DESCRIPTOR)ucSDbuf;
   DWORD          dwSDLengthNeeded;

   PACL           pAcl;
   PACL           pNewAcl;

   EXPLICIT_ACCESS explicitaccess;

   BOOL fDaclPresent,fDaclDefaulted;
   DWORD dwResult;

   UCHAR          ucAbsSDbuf[SD_SIZE];
   PSECURITY_DESCRIPTOR pAbsSD=(PSECURITY_DESCRIPTOR)ucAbsSDbuf;
   DWORD dwSDLength;

#define ACL_SIZE 2048
#define SID_SIZE 1024

   PACL pacl,psacl;
   DWORD dwAclSize=ACL_SIZE, dwSaclSize=ACL_SIZE;
   PSID pSidOwner,pSidPrimary;
   DWORD dwSidOwnLen=SID_SIZE,dwSidPrimLen=SID_SIZE;


   if(!GetKernelObjectSecurity(
      hProc,
      DACL_SECURITY_INFORMATION,
      pSD,
      SD_SIZE,
      &dwSDLengthNeeded))
   {
      PERR("GetKernelObjectSecurity");
      return(FALSE);
   }

   if(!GetSecurityDescriptorDacl(
      pSD,
      &fDaclPresent,
      &pAcl,
      &fDaclDefaulted))
   {
      PERR("GetSecurityDescriptorDacl");
      return(FALSE);
   }


   BuildExplicitAccessWithName(
      &explicitaccess,
      "administrators",
      dwAccess,
      GRANT_ACCESS,
      0 );

   if( dwResult = SetEntriesInAcl(
      1,
      &explicitaccess,
      pAcl,
      &pNewAcl ) )
   {
      SetLastError(dwResult);
      PERR("SetEntriesInAcl");
      return( FALSE );
   }


   pacl = malloc(ACL_SIZE);
   psacl = malloc(ACL_SIZE);
   pSidOwner = malloc(SID_SIZE);
   pSidPrimary = malloc(SID_SIZE);

   dwSDLength = SD_SIZE;

   if(!MakeAbsoluteSD(
      pSD,
      pAbsSD,
      &dwSDLength,
      pacl, &dwAclSize,
      psacl, &dwSaclSize,
      pSidOwner, &dwSidOwnLen,
      pSidPrimary, &dwSidPrimLen))
   {
      PERR("MakeAbsoluteSD");
      return(FALSE);
   }

   if(!SetSecurityDescriptorDacl(
      pAbsSD,
      fDaclPresent,
      pNewAcl,
      fDaclDefaulted))
   {
      PERR("SetSecurityDescriptorDacl");
      return(FALSE);
   }

   if(!SetKernelObjectSecurity(
      hProc,
      DACL_SECURITY_INFORMATION,
      pAbsSD))
   {
      PERR("SetKernelObjectSecurity");
      return(FALSE);
   }

   return (TRUE);
}


LPSTR GetLastErrorText()
{
   #define MAX_MSG_SIZE 256

   static char szMsgBuf[MAX_MSG_SIZE];
   DWORD dwError, dwRes;

   dwError = GetLastError ();

   dwRes = FormatMessage (
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      MAKELANGID (LANG_ENGLISH, SUBLANG_ENGLISH_US),
      szMsgBuf,
      MAX_MSG_SIZE,
      NULL);
   if (0 == dwRes) {
      fprintf(stderr, "FormatMessage failed with %d\n", GetLastError());
      ExitProcess(EXIT_FAILURE);
   }

   return szMsgBuf;
}

