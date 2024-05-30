/*
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

*/

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <imagehlp.h>

#define MAX_SZ_LEN                     256
#define MEM_5MB                        5 * 1024 * 1024

#if !defined (IMAGE_FILE_LARGE_ADDRESS_AWARE)
#define IMAGE_FILE_LARGE_ADDRESS_AWARE 0x0020   // from winnt.h
#endif


//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
// FUNCTION:     VerifyNTServerEE4SP3 - This function verifies that the
//               current operating system is Windows NT Server Enterprise
//               Edition version 4.0 with Service Pack 3 (or later).
//               See Q132475 "Determining If a Service Pack Has Been Installed"
//               and Q181412 "INFO: Detecting Windows NT Server Enterprise 
//               Edition"
//
// PARAMETERS:   none
//
// RETURN VALUE: TRUE if version is successfully verified
//               FALSE if verification fails
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+

BOOL VerifyNTServerEE4SP3( void ) {
   HKEY           hKey;
   long           lResult;
   char           szProduct[MAX_SZ_LEN];
   DWORD          cbProduct = MAX_SZ_LEN;
   OSVERSIONINFO  osvi;

   // check for NT4 or later
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
   if ( !GetVersionEx( &osvi ) ) {
      printf( "GetVersionEx() failed: Error %d", GetLastError() );
      return FALSE;
   }

   if ( osvi.dwPlatformId != VER_PLATFORM_WIN32_NT 
         || osvi.dwMajorVersion < 4 ) {
      printf( "Failed to verify Windows NT Version 4.0 (or higher)\n" );
      return FALSE;
   } else {
      printf( "Verified Windows NT Version 4.0 (or higher)\n" );
   }

   // if NT4, check for SP3 or later
   if ( osvi.dwMajorVersion == 4 ) {

      lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, 
         "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
         0, KEY_QUERY_VALUE, &hKey );

      if ( lResult != ERROR_SUCCESS ) {
         printf( "RegOpenKey() failed: Error %d\n", lResult );
         return FALSE;
      } else {

         lResult = RegQueryValueEx( hKey, "CSDVersion", NULL, NULL, 
            (LPBYTE) &szProduct, &cbProduct );
         RegCloseKey( hKey );

         if ( lResult != ERROR_SUCCESS ) {
            printf( "RegQueryValueEx() failed: Error %d\n", lResult );
            return FALSE;
         } else {

            if ( _stricmp( szProduct, "service pack 3" ) < 0 ) {
               printf( "Failed to verify Service Pack 3 (or higher)\n" );
               return FALSE;
            } else {
               printf( "Verified Service Pack 3 (or higher)\n" );
            }

         }

      }

   }

   lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, 
      "SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
      0, KEY_QUERY_VALUE, &hKey );

   if ( lResult != ERROR_SUCCESS ) {
      printf( "RegOpenKey() failed: Error %d\n", lResult );
      return FALSE;
   } else {

      // check for NT Server
      cbProduct = MAX_SZ_LEN;
      lResult = RegQueryValueEx( hKey, "ProductType", NULL, NULL, 
         (LPBYTE) &szProduct, &cbProduct );

      if ( lResult != ERROR_SUCCESS ) {
         printf( "RegQueryValueEx() failed: Error %d\n", lResult );
         RegCloseKey( hKey );
         return FALSE;
      } else {

         if ( _stricmp( szProduct, "servernt" ) == 0 ) {
            printf( "Verified Windows NT Server\n" );
         } else {
            printf( "Failed to verify Windows NT Server\n" );
            RegCloseKey( hKey );
            return FALSE;
         }

      }

      // check for enterprise edition
      cbProduct = MAX_SZ_LEN;
      lResult = RegQueryValueEx( hKey, "ProductSuite", NULL, NULL, 
         (LPBYTE) &szProduct, &cbProduct );
      RegCloseKey( hKey );

      if ( ( lResult != ERROR_SUCCESS ) 
            || ( _stricmp( szProduct, "enterprise" ) != 0 ) ) {
         printf( "Failed to verify Enterprise Edition\n" );
         return FALSE;
      } else {
         printf( "Verified Enterprise Edition\n" );
      }

      return TRUE;
   }

}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
// FUNCTION:     VerifyLargeAddressAware - This function verifies that the
//               current executable's image has the characteristic bit set for
//               IMAGE_FILE_LARGE_ADDRESS_AWARE.  It relies on two ImageHelp
//               API's:  MapAndLoad() and UnMapAndLoad().   The executable must
//               be linked with IMAGEHLP.LIB.
//
// PARAMETERS:   none
//
// RETURN VALUE: TRUE if bit is set
//               FALSE otherwise
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+

BOOL VerifyLargeAddressAware( void ) {
   
   int            iSize;
   char           szFilename[MAX_SZ_LEN];
   LOADED_IMAGE   li;
   BOOL           bSuccess;

   iSize = GetModuleFileName( NULL, (CHAR *) &szFilename, MAX_SZ_LEN );
   
   if ( iSize == 0 ) {
      printf( "GetModuleFileName() failed: Error %d\n", GetLastError() );
      return FALSE;
   } else {
      
      bSuccess = MapAndLoad( szFilename, NULL, &li, FALSE, TRUE );

      if ( !bSuccess ) {
         printf( "MapAndLoad() failed: Error %d\n", GetLastError() );
         return FALSE;
      } else {

         bSuccess = ( li.Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE );
         if ( bSuccess ) {
            printf( "Verified large address aware bit\n" );
         } else {
            printf( "Failed to verify large address aware bit\n" );
         }

         UnMapAndLoad( &li );

         return bSuccess;
      }

   }

}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
// FUNCTION:     Verify3GBBootupSwitch - This function verifies that the 
//               system was booted with the /3GB switch by looking at the size
//               of virtual memory returned from GlobalMemoryStatus()
//               Note that if the exe is not large address aware then GMS
//               will report 2gb.
//
// PARAMETERS:   none
//
// RETURN VALUE: TRUE if greater than 2GB virtual memory
//               FALSE otherwise
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+

BOOL Verify3GBBootupSwitch ( void ) {

   MEMORYSTATUS   ms;

   ms.dwLength = sizeof(ms);
   GlobalMemoryStatus( &ms );
   if ( ms.dwTotalVirtual < 0x80000000 ) {
      printf( "Failed to verify /3GB bootup switch\n" );
      return FALSE;
   } else {
      printf( "Verified /3GB bootup switch\n" );
      return TRUE;
   }

}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
// FUNCTION:     main - Entry point for code execution.
//
//               This function first verifies that the proper operating system
//               is in use. It then makes sure the EXE's image header contains 
//               the IMAGE_FILE_LARGE_ADDRESS_AWARE bit. Next it verifies that
//               NT was booted with the /3GB switch. If all of the above
//               checks pass, it attempts to allocate a 5MB block of memory
//               above the 2 GB limit.
//
// PARAMETERS:   none
//
// RETURN VALUE: none
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+

void main( void ) {

   VOID *         lpMem = NULL;

   if ( !VerifyNTServerEE4SP3() ) {
      printf( "4GT is only supported on Windows NT Server Enterprise %s\n",
         "Edition version 4.0\nwith Service Pack 3 (or later)" );
      goto Exit;
   }

   if ( !VerifyLargeAddressAware() ) {
      printf( "This executable must be linked with %s\n",
         "the /LARGEADDRESSAWARE switch (see Q171793)" );
      goto Exit;
   }

   if ( !Verify3GBBootupSwitch() ) {
      printf( "NT must be booted with the /3GB switch (see Q170756)\n" );
      goto Exit;
   }

   // allocate memory above 2 GB
   lpMem = VirtualAlloc( LongToHandle( 0x88000000), MEM_5MB, 
      MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE );

   if ( lpMem == NULL ) {
      printf( "Failed to allocate a block above 2GB.  Error %d",
         GetLastError() );
      goto Exit;
   } else {
      printf( "A 5MB block was successfully allocated at 0x%p\n", lpMem );
      VirtualFree( lpMem, 0, MEM_RELEASE );
   }

Exit:
   printf( "\nPress any key to exit\n" );
   while(!kbhit()) {
      Sleep(100);
   }

}
