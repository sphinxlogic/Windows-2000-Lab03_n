// CheckSFP.cpp : Tool for Windows 2000 to check for System File Protection
//

#include "stdafx.h"

TCHAR *g_wszPath;

bool ProcessCmdLine(int argc, wchar_t* argv[]);
void PrintUsage(void);

extern "C" 
int wmain(int argc, wchar_t* argv[])
{
	WIN32_FIND_DATA findData;
	DWORD			dwVersion;

	// Get the Windows version - only run on win2000 or greater
	dwVersion = GetVersion();
 
	// High order bit = NT, low order byte = version major
	if ((dwVersion > 0x80000000) ||
		((DWORD)(LOBYTE(LOWORD(dwVersion))) < 5))
	{
		printf("CheckSFP requires Windows 2000 or greater.\n");
		// Return an error code
		return -1;
	}

	if (ProcessCmdLine(argc, argv) == FALSE)
	{
		return -1;
	}

	// Be sure this file exists
	if (FindFirstFile(g_wszPath, &findData) == INVALID_HANDLE_VALUE)
	{
		wprintf(TEXT("The file: '%s' could not be found.\n"), g_wszPath);
		// Return an error code
		return -1;
	}
	
	// Call system API to see if file is protected
	if (SfcIsFileProtected(NULL, g_wszPath) == 0)
	{
		wprintf(TEXT("The file: '%s' is not protected.\n"), g_wszPath);
		return 0;
	}
	else
	{
		wprintf(TEXT("The file: '%s' is protected.\n"), g_wszPath);
		return 1;
	}
}

bool ProcessCmdLine(int argc, wchar_t* argv[])
{
	if (argc != 2) 
	{
		// No args, or too many args - show usage
		PrintUsage();
		return FALSE;
	}

	if (argv[1][1] == '?')
	{
		// User asked for help - show usage
		PrintUsage();
		return FALSE;
	}

	// Set search path to first arg
	g_wszPath = argv[1];

	return TRUE;
}

void PrintUsage(void)
{
	wprintf(TEXT("USAGE: CheckSFP [Path to file] [/?] \n"));
}
