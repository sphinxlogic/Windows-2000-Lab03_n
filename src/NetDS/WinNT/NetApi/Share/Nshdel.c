// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NShDel.c
// DESCRIPTION:   Deletes a share for a specific share on a server
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          2/17/98
//

#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <lm.h>

void wmain( int argc, TCHAR *argv[ ])
{
   NET_API_STATUS res;

	if(argc<3)
		printf("Usage: NetShareDel server share\n");
	else
	{
		res=NetShareDel(argv[1], argv[2], 0);
		if(res==0)
			printf("Share Removed.\n");
		else
			printf("Error: %u\n", res);
	}
	return;
}