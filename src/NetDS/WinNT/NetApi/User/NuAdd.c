// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NUAdd.c
// DESCRIPTION:   Add a user account
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Mike Liu
// DATE:          5/9/98
//

#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>

int wmain(int argc, wchar_t *argv[])
{
   USER_INFO_1 ui;
   DWORD dwLevel = 1;
   DWORD dwError = 0;
   NET_API_STATUS nStatus;

   if (argc != 3)
   {
      fwprintf(stderr, L"Usage: %s \\\\ServerName UserName\n", argv[0]);
      exit(1);
   }

   ui.usri1_name = argv[2];
   ui.usri1_password = argv[2];
   ui.usri1_priv = USER_PRIV_USER;
   ui.usri1_home_dir = NULL;
   ui.usri1_comment = NULL;
   ui.usri1_flags = UF_SCRIPT;
   ui.usri1_script_path = NULL;

   nStatus = NetUserAdd(argv[1],
                        dwLevel,
                        (LPBYTE)&ui,
                        &dwError);

   if (nStatus == NERR_Success)
      fwprintf(stderr, L"User %s has been successfully added on %s\n",
               argv[2], argv[1]);
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
