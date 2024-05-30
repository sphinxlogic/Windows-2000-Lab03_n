/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    dibview.c

Abstract:
    
    Sample program that demonstrates basic ICM functions

--*/

#include "pch.h"
#include "resource.h"

#include "dibview.h"

#ifdef ICM_ENABLED
#include "SelSource.h"
#include "CMMman.h"
#endif //ICM_ENABLED

#include "check.h"
#include "conv.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"
#include "FFilter.h"

// Global variable to enumerate the image file read filters
FILEFILTERSLIST g_FileFiltersList;

//////////////////////////////////////////////////////////////////////////
//
// _tWinMain
//
// Routine Description:
//   The initial entry point - unicode aware version
//
// Arguments:
//   HINSTANCE hInstance       handle to current instance  
//   HINSTANCE hPrevInstance   handle to previous instance  (= 0 in Win32)
//   PTSTR     pCmdLine        pointer to command line
//   int       nCmdShow        show state of window
//
// Return Value:
//   If it succeeds (terminating after a WM_QUIT message), returns the 
//   exit value contained in that message's wParam parameter. 
//   If it terminates before entering the message loop, it returns zero. 
//

int 
WINAPI 
_tWinMain(  
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PTSTR     pCmdLine,
    int       nCmdShow
)
{
    static USES_BRESULT;
    static HACCEL hAccelTable;
    static MSG msg = { 0 };

    ASSERT(hPrevInstance == 0);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(pCmdLine);

    g_hInstance = hInstance;

    CHECK(DetermineOSVersion());

#ifdef MULTIMON_ENABLED
    
    InitMultiMonitorStubs();

#endif //MULTIMON_ENABLED

#ifdef ICM_ENABLED

    InitICMStubs();

    InitSTIStubs();

#endif //ICM_ENABLED

    InitTwainStubs();

    InitCommonControls();

    CHECK(LoadStringTable());

    CHECK(FileFiltersList_Construct(&g_FileFiltersList));

    CHECK(BitmapWindow_RegisterClass());

    CHECK(hAccelTable = LoadAccelerators(
        hInstance, 
        MAKEINTRESOURCE(IDR_ACCELERATORS)
    ));

    CHECK(ParseCommandLine(nCmdShow));

    while (GetMessage(&msg, 0, 0, 0)) {

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    BEGIN_CLEANUP;

    FileFiltersList_Destruct(&g_FileFiltersList);

    UnloadStringTable();

#ifdef ICM_ENABLED

    FreeICMStubs();

    FreeSTIStubs();

#endif //ICM_ENABLED

    FreeTwainStubs();

    return msg.wParam;
}

//////////////////////////////////////////////////////////////////////////
//
// DetermineOSVersion
//
// Routine Description:
//   Determines the version of Windows we are running on
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
DetermineOSVersion()
{
    USES_BRESULT;

    OSVERSIONINFO vi;
    
    vi.dwOSVersionInfoSize = sizeof(vi);

    CHECK(GetVersionEx(&vi));

    switch (vi.dwPlatformId) {

    case VER_PLATFORM_WIN32s: 
        
        g_OS = OS_WIN32s;
        
        break;

    case VER_PLATFORM_WIN32_WINDOWS: 

        if (vi.dwMajorVersion != 4) {

            return FALSE;
        }
        
        g_OS = vi.dwMinorVersion == 0 ? OS_WIN95 : OS_WIN98;
        
        break;

    case VER_PLATFORM_WIN32_NT: 

        if (vi.dwMajorVersion == 3) {
        
            g_OS = OS_WINNT3;

        } else if (vi.dwMajorVersion == 4) {

            g_OS = OS_WINNT4;

        } else if (vi.dwMajorVersion >= 5) {

            g_OS = OS_WIN2000;
        
        } else {

            return FALSE;
        }
        
        break;
    }

#ifdef UNICODE

    if (g_OS == OS_WIN32s || g_OS == OS_WIN95 || g_OS == OS_WIN98) {

        CHAR szErrorMessage[4098]; 

        LoadStringA(
            g_hInstance,
            IDS_UNICODE_REQUIRED,
            szErrorMessage,
            COUNTOF(szErrorMessage)
        );

        MessageBoxA(
            0,
            szErrorMessage,
            0,
            MB_OK | 
            MB_ICONERROR
        );

        return FALSE;
    }

#endif //UNICODE

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// LoadStringTable
//
// Routine Description:
//   Loads the global string table from the resources
//
// Arguments:
//   none
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
LoadStringTable()
{
    USES_BRESULT;

    // allocate a buffer large enough to hold a maximum allowed 
    // length resource string
    
    TCHAR szBuffer[4098]; 
    int i;

    for (i = IDS_FIRST; i <= IDS_LAST; ++i) {
    
        int nLength = LoadString(
            g_hInstance,
            i,
            szBuffer,
            COUNTOF(szBuffer)
        );

        CHECK(g_pResourceStrings[i - IDS_FIRST] = (PTSTR) GlobalAlloc(
            GMEM_FIXED | GMEM_ZEROINIT, 
            (nLength + 1) * sizeof(TCHAR)
        ));

        if (nLength) {

            // Copy the string to the global table.
            // We use CopyMemory instead of _tcscpy because if this were
            // a MULTI_SZ string, _tcscpy would stop after the first \0

            CopyMemory(
                ResourceString(i),
                szBuffer,
                nLength * sizeof(TCHAR)
            );
        }
    }

    // Set the localizable "unknown error" string. Our SystemErrorMessage() 
    // function will use this string when it cannot find an associated 
    // message string for the LastError

    SetUnknownErrorStr(ResourceString(IDS_UNKNOWN_ERROR));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// UnloadStringTable
//
// Routine Description:
//   Frees the global string table
//
// Arguments:
//   none
//
// Return Value:
//   none
//

VOID
UnloadStringTable()
{
    int i;

    for (i = IDS_FIRST; i <= IDS_LAST; ++i) {
    
        if (ResourceString(i)) {

            GlobalFree(ResourceString(i));
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
// ParseCommandLine
//
// Routine Description:
//   Tries to open the image files given as the command line arguments
//
// Arguments:
//   int nCmdShow   show state of the window(s) to be created
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ParseCommandLine(
    int nCmdShow
)
{
    USES_BRESULT;
    HANDLE          hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fd;
    BOOL            bFound;
    TCHAR           szPathName[MAX_PATH];
    PTSTR           pFileName;
    int             nNumCreated = 0;
    int             i;

    for (i = 1; i < __argc; ++i) {

        // Get a full qualified path name for the next command line argument

        bFound = GetFullPathName(
            __targv[i],
            COUNTOF(szPathName),
            szPathName,
            &pFileName
        );

        bFound = bFound && pFileName != 0;

        // Search for the file. This also takes care of wildcard matching

        hFind = FindFirstFile(szPathName, &fd);
        
        bFound = bFound && hFind != INVALID_HANDLE_VALUE;

        while (bFound) {

            // if a file is found, add the filename to the end of the path

            _tcscpy(pFileName, fd.cFileName);

            // and try to open the file
        
            if (CreateBitmapWindow(nCmdShow, eReadFromFile, szPathName)) {
            
                ++nNumCreated;
            }

            bFound = FindNextFile(hFind, &fd);
        }
    }

    // If no files are given on the command line, or the files
    // cannot be read, open an empty window

    if (nNumCreated == 0) {
        
        CHECK(CreateBitmapWindow(nCmdShow, eOpenEmpty, 0));
    }

    BEGIN_CLEANUP;

    if (hFind != INVALID_HANDLE_VALUE) {

        CHECK(FindClose(hFind));
    }

    return BRESULT;
}

