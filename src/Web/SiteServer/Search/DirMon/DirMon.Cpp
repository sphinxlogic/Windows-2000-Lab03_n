//====================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//=====================================================================
//    File System directory monitoring tool.
//    The directory change notifications are sent to the Gatherer 
//    through IGatherNotify interface. The Gatherer asynchronously
//    filters the file and updates the catalog.
//
//  Functions:  MonitorDirectory, SendNotifications
//====================================================================== 

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
#include "gthrntfysdk.h"

#define MAX_NOTIFY_BUF 4096

HRESULT SendNotifications (FILE_NOTIFY_INFORMATION * pFileNotifies, 
                           DWORD dwBytes, 
                           IGatherNotify * pGatherNotify, 
                           LPCWSTR pszDirectory);

HRESULT MonitorDirectory (LPWSTR pszDirectory, 
                          IGatherNotify * pGatherNotify, 
                          DWORD dwNotifyFlags)

//+-----------------------------------------------
//
//    Function:    MonitorDirectory
//
//    Synopsis:     Translates the NTFS directory change notifications to the  
//                  gatherer notifications.
//
//    Returns:    HRESULT
//
//    Arguments:
//    [LPWSTR pszDirectory]             Directory to monitor
//    [IGatherNotify * pGatherNotify]   Pointer to the Gatherer notification 
//                                      interface
//    [DWORD dwNotifyFlags]             Directory change notification flags
//
//+-----------------------------------------------

{
    DWORD dwError;
	BYTE aFileNotify[MAX_NOTIFY_BUF];
    OVERLAPPED ov;
    DWORD dwBytes;
    DWORD dwWait;
    HRESULT hr;

     // Open the directory to monitor 
    HANDLE hDir = CreateFile (
                  pszDirectory,             // Pointer to the file name
                  FILE_LIST_DIRECTORY,      // Access (read-write) mode
                  FILE_SHARE_READ|FILE_SHARE_DELETE,    // Share mode
                  NULL,                     // Security descriptor
                  OPEN_EXISTING,            // How to create
                  FILE_FLAG_BACKUP_SEMANTICS |
                  FILE_FLAG_OVERLAPPED,     // File attributes
                  NULL                      // File with attributes to copy
                  );

    if (INVALID_HANDLE_VALUE == hDir)
    {
        dwError = GetLastError();
        wprintf(L"Error opening Directory %s = %d\n", pszDirectory, dwError);
        return HRESULT_FROM_WIN32 (dwError);
    }

    // Create an event handle to be used in overlapped I/O requests 
    ZeroMemory((PVOID) &ov, sizeof(ov));
    ov.hEvent = CreateEvent (NULL, FALSE, FALSE, NULL);

    // Monitor any changes. 
    wprintf(L"Awaiting changes in \"%s\" directory...\n", pszDirectory);

    // This loop never exits. 
	while (TRUE)
    {
        // Request directory changes 
        if (FALSE == ReadDirectoryChangesW(
                     hDir,            // Handle to directory to monitor 
                     aFileNotify,     // Address of the buffer to receive results 
                     sizeof(aFileNotify),  // Length of lpBuffer 
                     TRUE,            // Monitoring directory/directory tree 
                     dwNotifyFlags,   // Notifications are to monitored 
                     &dwBytes,        // Number of bytes returned 
                     &ov,             // Address of structure for overlapped I/O 
                     NULL             // Address of completion routine 
                     ))
        {
            dwError = GetLastError();
            wprintf(L"Error on ReadDirectoryChangesW = %d\n", dwError);
            return HRESULT_FROM_WIN32 (dwError);
        }

        // Synchronize with directory changes completion 
        dwWait = WaitForSingleObject(ov.hEvent, INFINITE);

        if (dwWait == WAIT_FAILED)
        {
            dwError = GetLastError();
            wprintf(L"Wait Failed %d\n", dwError);
            return HRESULT_FROM_WIN32 (dwError);
        }



        if (dwWait == WAIT_ABANDONED_0) // User cancelled operation 
        {
            return NOERROR;
        }

        // Get the completion result
        if (FALSE == GetOverlappedResult(
                     hDir,          // Handle of file, pipe, or comm. device 
                     &ov,           // Address of overlapped structure 
                     &dwBytes,      // Address of actual bytes count 
                     TRUE           // Wait flag 
                     ))
        {
            dwError = GetLastError();
            wprintf(L"GetOverlappedResult failed %d\n", dwError);
            return HRESULT_FROM_WIN32 (dwError);
        }

        if (0 == dwBytes)
        {
            wprintf(L"Buffer Size of %d Exceeded", sizeof(aFileNotify));
            return E_FAIL;
        }

        // Process notifications 
        if (FAILED(hr = SendNotifications (
                        (FILE_NOTIFY_INFORMATION *) aFileNotify, 
                        dwBytes, 
                        pGatherNotify, 
                        pszDirectory)))
        {
            return hr;
        }
    }

}

#define CaseAction(x, y)    case x: dwNotify = y; break

 HRESULT SendNotifications(FILE_NOTIFY_INFORMATION * pFileNotifies, DWORD dwBytes, IGatherNotify * pGatherNotify, LPCWSTR pszDirectory)

//+-----------------------------------------------
//
//    Function:    SendNotifications
//
//    Synopsis:    Parses the file notification buffer and sends gatherer 
//                 notifications for each file
//
//    Returns:    HRESULT 
//
//    Arguments:
//    [FILE_NOTIFY_INFORMATION * pFileNotifies]	Buffer returned by the directory 
//                                              change notification
//    [DWORD dwBytes]                           Buffer size
//    [IGatherNotify * pGatherNotify]           Pointer to the gatherer  
//                                              notification interface
//    [LPCWSTR pszDirectory]                    Directory being monitored
//
//+-----------------------------------------------
{
    WCHAR wszFileName[MAX_PATH];
    DWORD dwNotify = 0;

    // Copy the directory in the buffer that is sent to the gatherer. 
    // The gatherer expects a full path specification for each file or URL 

    lstrcpy(wszFileName, pszDirectory);
    int fileNameIndex = lstrlen(wszFileName);
    if(fileNameIndex && wszFileName[fileNameIndex - 1] != L'\\')
    {
        wszFileName[fileNameIndex] = L'\\';
        ++fileNameIndex;
        wszFileName[fileNameIndex] = 0;
    }

    FILE_NOTIFY_INFORMATION * pFNotify = pFileNotifies;
    
    // Parse the directory change notification buffer 
    for (ULONG iCount = 0; 
            pFNotify && iCount < dwBytes; )
    {
        // Set the dwNotify flag to values that the gatherer understands 

        switch (pFNotify->Action)
        {
            // The file was added to the directory 
            CaseAction(FILE_ACTION_ADDED, GTHR_CA_ADD); 

            // The file was removed from the directory 
            CaseAction(FILE_ACTION_REMOVED, GTHR_CA_DELETE); 

            // The file was modified. This can be a change in the time stamp or 
            // a change in attribute 
            CaseAction(FILE_ACTION_MODIFIED, GTHR_CA_MODIFY); 

            default:
                dwNotify = 0;
        }

        // If we've got a notifcation we are interested in 
        if (dwNotify)
        {
            // Append the file name to the directory name
            wszFileName[fileNameIndex] = 0;
            CopyMemory(wszFileName + fileNameIndex, 
                       pFNotify->FileName, 
                       pFNotify->FileNameLength);

            // The dual interface wants a BSTR
            BSTR bstrFileName = SysAllocStringLen(wszFileName, 
			                                      fileNameIndex + 
												  pFNotify->FileNameLength/2);

            // Send gatherer notification
            pGatherNotify->OnDataChange (
                           dwNotify,       // The type of change 
                           bstrFileName,   // Physical address 
                           NULL); 

            SysFreeString(bstrFileName);
        }

        // Increment the pointer in the directory change notification buffer 
        iCount += pFNotify->NextEntryOffset;

        if (pFNotify->NextEntryOffset == 0)
        {
            pFNotify = 0;
        }
        else
        {
            pFNotify += pFNotify->NextEntryOffset;
        }
    }

    return NOERROR;
}
