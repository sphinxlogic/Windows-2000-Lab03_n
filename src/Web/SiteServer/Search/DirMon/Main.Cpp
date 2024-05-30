//==========================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//==========================================================================
//
//  File:         main.cpp
//
//  Contents:	  Site Server 3.0 Search SDK
//                File System directory monitoring tool.
//                The directory change notifications are sent to the 
//                Gatherer through the IGatherNotify interface. The Gatherer 
//                asynchronously filters the file and updates the catalog.
//
//  Functions:    main
//
//==========================================================================
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#else if (_WIN32_WINNT < 0x0400)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include <windows.h>
#include <stdio.h>

#include <objbase.h>

#include "gthrntfysdk.h"
#include "gthrntfysdk_i.c"

HRESULT MonitorDirectory(LPWSTR pszDirectory, 
                         IGatherNotify * pGatherNotify, 
                         DWORD dwNotifyFlags);

void Usage(LPCWSTR lpszProgram)
{
   fprintf(stderr, "Usage: %S <FullPath to Directory> [<Server>]\n", lpszProgram);
}

extern "C" int __cdecl wmain (int argc, WCHAR *argv[])
{
    DWORD dwBytes = 0;
    IGatherNotify * pGatherNotify;

	// Parse command-line arguments
    if (argc < 2)
    {
        Usage(argv[0]);
        exit(0);
    }

    int iDir = 1; int iServer = 2;
    for (int i = 1; i < argc; ++i)
    {
        if (*argv[i] == L'-' || *argv[i] == L'/')
        {
            Usage (argv[0]);
            exit(0);
        }
    }

	// Initialize COM 

    HRESULT hr;

    hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
        hr = CoInitializeSecurity(NULL, 
                                  -1, 
                                  NULL, 
                                  NULL,
                                  RPC_C_AUTHN_LEVEL_NONE, 
                                  RPC_C_IMP_LEVEL_DELEGATE, 
                                  NULL, 
                                  EOAC_NONE, 
                                  NULL);
    }

    // If the user does not supply a server on the command line,
	// we'll use the current host's computer name.

    WCHAR wszServer[20];
    wszServer[0] = 0;
    if (iServer < argc)
    {
        lstrcpy(wszServer, argv[iServer]);
    }
    else
    {
        DWORD dwLen = 20;
        GetComputerName(wszServer, &dwLen);
    }

    // Create the notification object 

    COSERVERINFO srvInfo, *psrvInfo = &srvInfo;
    ZeroMemory(&srvInfo, sizeof(COSERVERINFO));
    srvInfo.pwszName = wszServer;

    MULTI_QI qi = {  &IID_IGatherNotify, NULL, S_OK };

    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstanceEx(CLSID_CGatherNotify, 
                                NULL, 
                                CLSCTX_SERVER, 
                                &srvInfo, 
                                1, 
                                &qi);
    }

    if (FAILED(hr))
    {
        fprintf(stderr,"CoCreateInstance failed, returning %8X\n" , hr);
        exit(0);
    }

    pGatherNotify = (IGatherNotify *)qi.pItf;
    
    // Initialize the notification object.
	// The string that is used in the call to Init() must be set as NotificationSource
	// property on one of catalog definitions. The catalog must also be marked as notification
	// type: IBuildCatalog.ProjectType = 0.
	// If the catalog is configured with any start page(s), the	initialization of the
	// notification object will also trigger an incremental crawl.
	// The start page(s) of the project should cover the URL space that the notification
	// source monitors.
	// In case of DirMon sample, the start page is set to the monitored directory.
	// The incremental crawl allows the notification source not to worry about bootstrapping
	// of the catalog, or sending any notifications for changes that occured since the last
	// shutdown of the notification source (Dirmon.exe)
	// The gatherer will be able to enumerate all URLs in the space of the notification source,
	// and get all the changes from the last time the catalog was built, to the time the
	// notification source connects and initializes the notification object.

    BSTR bstrSource = SysAllocString(L"DirmonSource");      // Source name 

    if (FAILED(hr = pGatherNotify->Init(bstrSource)))
    {
        fprintf(stderr, "Error initializing notification object hr = %8X\n", hr);
        exit(0);
    }

    SysFreeString(bstrSource);

	MonitorDirectory(argv[iDir], pGatherNotify, 

                     // Monitor any change to a filename in the directory. 
                     // These changes include creating a file, renaming a file, 
                     // and deleting a file. 

                     FILE_NOTIFY_CHANGE_FILE_NAME    | 

                     // Monitor any change to a directory name in the directory. 
                     // These changes include creating a directory and deleting a 
                     // directory. 

                     FILE_NOTIFY_CHANGE_DIR_NAME     | 

                     // Monitor any change to the size of a file in the directory. 
                     // Windows NT only detects a change in file size when the file
                     // is written to disk. 

                     FILE_NOTIFY_CHANGE_SIZE         | 

                     // Monitor any change to the last write-time of files in the 
                     // directory. Windows NT only detects a change to the last
                     // write-time when the file is written to disk. 

                     FILE_NOTIFY_CHANGE_LAST_WRITE   |

                     // Monitor any change to the creation time of files in the 
                     // directory. 

                     FILE_NOTIFY_CHANGE_CREATION); 

    pGatherNotify->Release();

    return 1;
}
