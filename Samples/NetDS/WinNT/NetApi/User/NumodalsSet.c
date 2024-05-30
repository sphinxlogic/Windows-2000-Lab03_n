// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NUModalsSet.c
// DESCRIPTION:   Set global information about users and
//                global groups such as password age, length,
//                and history, etc.
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
   DWORD dwLevel = 0;
   USER_MODALS_INFO_0 ui;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   if (argc > 2)
   {
      fwprintf(stderr, L"Usage: %s [\\\\ServerName]\n", argv[0]);
      exit(1);
   }

   if (argc == 2)
      pszServerName = argv[1];

   ui.usrmod0_min_passwd_len = 0;
   ui.usrmod0_max_passwd_age = (86400 * 30);
   ui.usrmod0_min_passwd_age = 0;
   ui.usrmod0_force_logoff = TIMEQ_FOREVER;
   ui.usrmod0_password_hist_len = 0;

   nStatus = NetUserModalsSet(pszServerName,
                              dwLevel,
                              (LPBYTE)&ui,
                              NULL);

   if (nStatus == NERR_Success)
      fwprintf(stderr, L"Modals information set successfully on %s\n", argv[1]);
   else
      fprintf(stderr, "A system error has occurred: %d\n", nStatus);

   return 0;
}
