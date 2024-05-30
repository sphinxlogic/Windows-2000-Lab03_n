/*
 * process.cpp - Native methods.
 *
 * (C) Copyright 1996 Microsoft Corporation
 */


/* Headers
 **********/

#include "project.hpp"
#pragma hdrstop

#include "DebuggeeProcess.h"


/****************************** Public Functions *****************************/


BOOL JavaStringToANSIString(Hjava_lang_String *phjsCommandLine, PSTR *ppszANSI)
{
	int ncchLen;

	// (+ 1) for null terminator.
    ncchLen = javaStringLength(phjsCommandLine) + 1;

    *ppszANSI = (PSTR)LocalAlloc(0, ncchLen);

	if (*ppszANSI)
        javaString2CString(phjsCommandLine, *ppszANSI, ncchLen);

    return(*ppszANSI != NULL);
}


/***************************** Exported Functions ****************************/


/* A debugger requires a way to get the process ID of its debuggee process. */

void __cdecl DebuggeeProcess_CreateSuspendedProcess(HDebuggeeProcess *hdp, Hjava_lang_String *phjsCommandLine)
{
    PSTR pszCommandLine;

    hdp->m_nMainThreadHandle = 0;
    hdp->m_nProcessID = 0;

	if (JavaStringToANSIString(phjsCommandLine, &pszCommandLine))
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
	
        if (CreateProcess(NULL, pszCommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi))
		{
			hdp->m_nMainThreadHandle = (int)(pi.hThread);
			hdp->m_nProcessID = pi.dwProcessId;

            CloseHandle(pi.hProcess);
		}
		else
			SignalError(0, "java/io/IOException", "CreateProcess");

		LocalFree(pszCommandLine);
        pszCommandLine = NULL;
	}
	else
		SignalError(0, JAVAPKG "OutOfMemoryError", 0);

    return;
}


void __cdecl DebuggeeProcess_ResumeProcess(HDebuggeeProcess *hdp)
{
    if (hdp->m_nMainThreadHandle != NULL)
	{
        if (ResumeThread((HANDLE)(hdp->m_nMainThreadHandle)) == 0xffffffff)
			SignalError(0, "java/io/IOException", "ResumeThread");

		CloseHandle((HANDLE)(hdp->m_nMainThreadHandle));
        hdp->m_nMainThreadHandle = 0;
	}

	return;
}

