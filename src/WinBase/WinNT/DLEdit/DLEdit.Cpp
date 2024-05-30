/*-----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 Microsoft Corporation.  All rights reserved.

DLEDIT  -- Drive Letter Assignment Editor

This program demonstrates how to add or remove persistent drive letter
assignments in Windows 2000.  These drive letter assignments persist through
machine reboots.

Platforms:
   This program requires Windows 2000.

Command-line syntax:
   DLEDIT <drive letter> <NT device name>      -- Adds a drive letter
   DLEDIT -r <drive letter>                    -- Removes a drive letter

Command-line examples:

   Say that E: refers to CD-ROM drive, and you want to make F: point to that
   CD-ROM drive instead.  Use the following two commands:

   DLEDIT -r E:\
   DLEDIT F:\ \Device\CdRom0


*******************************************************************************
WARNING: WARNING: WARNING: WARNING: WARNING: WARNING: WARNING: WARNING:

   This program really will change drive letter assignments, and the changes
   persist through reboots.  Do not remove drive letters of your hard disks if
   you don't have this program on a floppy disk or you might not be able to
   access your hard disks again!
*******************************************************************************

-----------------------------------------------------------------------------*/

#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>


#if defined (_DEBUG)
   static void DebugPrint (LPCSTR pszMsg, DWORD dwErr);
   #define DEBUG_PRINT(pszMsg, dwErr) DebugPrint(pszMsg, dwErr)
#else
   #define DEBUG_PRINT(pszMsg, dwErr) NULL
#endif

/* Turn bool to int conversion performance warning. */
#pragma warning (disable : 4800)

void PrintHelp (LPCSTR pszAppName);


/*-----------------------------------------------------------------------------
main( argc, argv )

Parameters
   argc
      Count of the command-line arguments
   argv
      Array of pointers to the individual command-line arguments

This function is the main program.  It parses the command-line arguments and
performs the work of either removing a drive letter or adding a new one.
-----------------------------------------------------------------------------*/
void main (int argc, char **argv)
{
   char * pszDriveLetter,
        * pszNTDevice,
        * pszOptions;

   char szUniqueVolumeName[MAX_PATH];
   char szDriveLetterAndSlash[4];
   char szDriveLetter[3];

   bool  fRemoveDriveLetter;
   bool  fResult;

   /*
      Command-line parsing.
         1) Validate number of arguments
         2) Determine whether user wants to remove or add a drive letter
         3) Deal with user passing in drive letters with or without a trailing
            backslash
   */
   if (argc != 3)
   {
      PrintHelp(argv[0]);
      return;
   }

   /*
      Use the command line to see if user wants to add or remove the drive
      letter.  Do this by looking for the -r option.
   */
   fRemoveDriveLetter = !lstrcmpi (argv[1], "-r");

   if (fRemoveDriveLetter)
   {
      /*
         User wants to remove the drive letter.  Command line should be:
            dl -r <drive letter>
      */
      pszOptions       = argv[1];
      pszDriveLetter   = argv[2];
      pszNTDevice      = NULL;
   }
   else
   {
      /*
         User wants to add a drive letter.  Command line should be:
            dl <drive letter> <NT device name>
      */
      pszOptions       = NULL;
      pszDriveLetter   = argv[1];
      pszNTDevice      = argv[2];
   }


   /*
      GetVolumeNameForVolumeMountPoint, SetVolumeMountPoint, and
      DeleteVolumeMountPoint require drive letters to have a trailing backslash.
      However, DefineDosDevice requires that the trailing backslash be absent.
      So, we'll use:

          szDriveLetterAndSlash     for the mount point APIs
          szDriveLetter             for DefineDosDevice

      This way, we can accept command lines that use the following forms for
      drive letters without writing back to the original command-line arg:
          a:
          a:\
   */
   szDriveLetter[0] = pszDriveLetter[0];
   szDriveLetter[1] = ':';
   szDriveLetter[2] = '\0';

   szDriveLetterAndSlash[0] = pszDriveLetter[0];
   szDriveLetterAndSlash[1] = ':';
   szDriveLetterAndSlash[2] = '\\';
   szDriveLetterAndSlash[3] = '\0';


   /*
      Now add or remove the drive letter.
   */
   if (fRemoveDriveLetter)
   {
      fResult = DeleteVolumeMountPoint (szDriveLetterAndSlash);

      if (!fResult)
         printf("error %lu: couldn't remove %s\n",
                GetLastError(), szDriveLetterAndSlash);
   }
   else
   {
      /*
         To add a drive letter that persists through reboots, we have to use
         SetVolumeMountPoint.  This requires the unique volume name of the
         NT device to which the new drive letter will refer. To get the unique
         volume name we use GetVolumeNameForVolumeMountPoint; it requires the
         drive letter to already exist.  So, we first have to define the drive
         letter as a symbolic link to the NT device name.  Once we have the
         unique volume name that the new drive letter will point to, we must
         delete the symbolic link because the Mount Manager allows only one
         reference to a device at a time (the new one to be added).
      */
      fResult = DefineDosDevice (DDD_RAW_TARGET_PATH, szDriveLetter,
                                 pszNTDevice);

      if (fResult)
      {
         /*
            If GetVolumeNameForVolumeMountPoint fails, then SetVolumeMountPoint
            below will also fail.  We can't bail out because we must call
            DefineDosDevice to remove the temporary symbolic link.  So, we'll
            just set szUniqueVolume to a known empty string.
         */
         if (!GetVolumeNameForVolumeMountPoint (szDriveLetterAndSlash,
                                                szUniqueVolumeName,
                                                MAX_PATH))
         {
            DEBUG_PRINT("GetVolumeNameForVolumeMountPoint failed",
                        GetLastError());
            szUniqueVolumeName[0] = '\0';
         }

         fResult = DefineDosDevice (DDD_RAW_TARGET_PATH|DDD_REMOVE_DEFINITION|
                                    DDD_EXACT_MATCH_ON_REMOVE, szDriveLetter,
                                    pszNTDevice);

         if (!fResult)
            DEBUG_PRINT("DefineDosDevice to remove drive letter failed",
                        GetLastError());

         fResult = SetVolumeMountPoint (szDriveLetterAndSlash,
                                        szUniqueVolumeName);

         if (!fResult)
            printf ("error %lu: could not add %s\n",
                    GetLastError(), szDriveLetterAndSlash);
      }
   }
}


/*-----------------------------------------------------------------------------
PrintHelp( pszAppName )

Parameters
   pszAppName
      The name of the executable.  Used in displaying the help for this app.

Prints the command-line usage help.
-----------------------------------------------------------------------------*/
void PrintHelp (LPCSTR pszAppName)
{
   printf("Adds or removes a drive letter assignment to an NT device\n\n");
   printf("usage: %s <Drive Letter> <NT device name>   add a drive letter\n",
          pszAppName);
   printf("       %s -r <Drive Letter>                 remove a drive letter\n\n",
          pszAppName);
   printf("example: %s e:\\ \\Device\\CdRom0\n", pszAppName);
   printf("         %s -r e:\\\n", pszAppName);
}


#if defined (_DEBUG)
/*-----------------------------------------------------------------------------
DebugPrint( pszMsg, dwErr )

Parameters
   pszMsg
      The string to be printed to STDOUT
   dwErr
      The error code; usually obtained from GetLastError.  If dwErr is zero,
      then no error code is added to the error string.  If dwErr is non-zero,
      then the error code will be printed in the error string.
-----------------------------------------------------------------------------*/
void DebugPrint (LPCSTR pszMsg, DWORD dwErr)
{
   if (dwErr)
      printf("%s: %lu\n", pszMsg, dwErr);
   else
      printf("%s\n", pszMsg);
}
#endif

