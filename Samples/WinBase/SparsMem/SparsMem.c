/*
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

*/


#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <process.h>
#include "resource.h"


//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  global declarations and typedefs
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+


typedef struct
{
   BOOL  fUsed;
   DWORD dwPID;
   BYTE  bData[1024];
} CHUNK, *PCHUNK;

typedef struct
{
   DWORD dwcChunksCommitted;
   DWORD dwLastChange;
} CONTROLCHUNK, *PCONTROLCHUNK;

UINT           g_uPageSize     = 0;
UINT_PTR       g_uTimer        = 0;
HANDLE         g_hFileMap      = NULL;
LPVOID         g_lpView        = NULL;
HANDLE         g_hMutex        = NULL;
PCONTROLCHUNK  g_pControlChunk = NULL;


#define MAX_CHUNKS (125000)
PCHUNK g_pSharedData = NULL;



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Dlg_OnInitDialog - mapped to WM_INITDIALOG via message
//                cracker in Dlg_Proc.  This function initializes the dialog
//                box that serves as the user-interface for this sample.
//
//  PARAMETERS:   hwnd - dialog handle
//                hwndFocus - handle of control to receive focus
//                lParam - additional initialization info (zero in this case)
//
//  RETURN VALUE: Zero if the SetFocus function is used to set the focus to
//                one of the controls in the dialog box. Otherwise, nonzero.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
BOOL Dlg_OnInitDialog (HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
   BOOL   g_fOwnerOfFileMap = FALSE;
   LPVOID lpMem;
   DWORD  dwPID;
   CHAR   szPID[33];

   dwPID = GetCurrentProcessId();
   _ltoa(dwPID, szPID, 10);

   // Set dialog icon
   SetClassLongPtr(hwnd, GCLP_HICON,
                (LONG_PTR)LoadIcon( GetWindowInstance(hwnd),
                                 MAKEINTRESOURCE(IDI_SPARSEMEM)) );

   // Update Process ID text control
   SetDlgItemText(hwnd, IDC_TXTPROCESSID, szPID);

   // Create (or obtain a process-relative handle to) the file-mapping object.
   g_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
                                  NULL,
                                  PAGE_READWRITE | SEC_RESERVE,
                                  0,
                                  (MAX_CHUNKS + 1) * g_uPageSize,
                                  "SparseMemorySharedData");

   if (g_hFileMap != NULL)
   {

      // Determine if file-mapping object was created by this process
      g_fOwnerOfFileMap = ( GetLastError() != ERROR_ALREADY_EXISTS );

      // Map a view of the file
      g_lpView = MapViewOfFile(g_hFileMap,
                               FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

      if ( (BYTE *) g_lpView == NULL )
      {
         MessageBox(hwnd, "Couldn't map view of file.",
                    "Error", MB_OK + MB_ICONEXCLAMATION);
         EnableWindow(GetDlgItem(hwnd, IDC_CMDCOMMIT), FALSE);
      }


      if (g_fOwnerOfFileMap)
      {

         // Create mutex to control writing to shared memory
         g_hMutex = CreateMutex(NULL, TRUE, "SparseMemoryMutex");

         if (g_hMutex != NULL)
         {

            // Write control data to first page of shared memory
            lpMem = VirtualAlloc(g_lpView, sizeof(CONTROLCHUNK),
                                 MEM_COMMIT, PAGE_READWRITE);

            if (lpMem != NULL)
            {

               // point g_pControlChunk to the first chunk of shared memory
               g_pControlChunk = ((PCONTROLCHUNK) lpMem);

               // initialize control chunk
               g_pControlChunk->dwcChunksCommitted  = 0;
               g_pControlChunk->dwLastChange        = GetTickCount();

            }
            else
               MessageBox(hwnd, "Could not allocate control chunk.",
                          "Error", MB_OK + MB_ICONEXCLAMATION);

            ReleaseMutex(g_hMutex);

         }
         else
            MessageBox(hwnd, "Mutex could not be created.",
                       "Error", MB_OK + MB_ICONEXCLAMATION);

      }
      else
      {

         g_hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "SparseMemoryMutex");
         if (g_hMutex != NULL)
         {

            // obtain mutex before writing to shared memory
            WaitForSingleObject(g_hMutex, INFINITE);

            // point g_pControlChunk to the first chunk of shared memory
            g_pControlChunk = ((PCONTROLCHUNK) g_lpView);

            ReleaseMutex(g_hMutex);

         }
         else
            MessageBox(hwnd, "Could not open mutex.",
                       "Error", MB_OK + MB_ICONEXCLAMATION);

      }

      // set timer to update the listbox every 1/2 second
      if (g_hMutex != NULL)
      {
         g_uTimer = SetTimer(hwnd, 1, 500, NULL);
         if ( !g_uTimer )
            MessageBox(hwnd, "Could not set update timer.",
                       "Error", MB_OK + MB_ICONEXCLAMATION);
      }

   }
   else
      MessageBox(hwnd, "File-mapping object could not be created.",
                 "Error", MB_OK + MB_ICONEXCLAMATION);

   return (TRUE);
}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Dlg_OnDestroy - mapped to WM_DESTROY via message cracker
//                in Dlg_Proc. This function cleans up any resources allocated
//                in the Dlg_OnInitDlg function above.  It also zeros any
//                chunks of memory used by the process so that they can be
//                re-used by another process.
//
//  PARAMETERS:   hwnd - dialog handle
//
//  RETURN VALUE: none
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
void Dlg_OnDestroy (HWND hwnd)
{
   DWORD dwCount, dwPID;
   PCHUNK pThisChunk;

   if (g_hMutex != NULL)
   {

      // obtain mutex before writing to shared memory
      WaitForSingleObject(g_hMutex, INFINITE);

      // zero any chunks created by this process so they are flagged as unused
      dwPID = GetCurrentProcessId();
      for ( dwCount = 1 ;
          dwCount <= g_pControlChunk->dwcChunksCommitted ;
          dwCount++ )
      {

         pThisChunk = (PCHUNK) ( ( (BYTE *) g_pControlChunk )
                                 + (dwCount * g_uPageSize) );

         if (pThisChunk->dwPID == dwPID)
            ZeroMemory(pThisChunk, sizeof(CHUNK));

      }

      // mark shared memory as changed
      g_pControlChunk->dwLastChange = GetTickCount();

      ReleaseMutex(g_hMutex);

      // close mutex handle
      CloseHandle(g_hMutex);

   }

   // destroy the update timer
   if (g_uTimer)
      KillTimer(hwnd, g_uTimer);

   // unmap the view of the file-mapping object
   if ( (BYTE *) g_lpView != NULL )
      UnmapViewOfFile(g_lpView);

   // close the file-mapping object handle
   if (g_hFileMap != NULL)
      CloseHandle(g_hFileMap);
}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Dlg_OnTimer - mapped to WM_TIMER via message cracker
//                in Dlg_Proc. This function refreshes the listbox which
//                displays the state of the shared memory.  The listbox is
//                only refreshed if the state of the memory has changed.
//
//  PARAMETERS:   hwnd - dialog handle
//                id - timer ID
//
//  RETURN VALUE: none
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
void Dlg_OnTimer (HWND hwnd, UINT id)
{

   HWND lb;
   DWORD dwCount;
   CHAR szNewItem[50];
   PCHUNK pThisChunk;
   static DWORD dwLastUpdate = 0;

   if (id = 1)
   {

      // update the list box if its changed
      if (dwLastUpdate < g_pControlChunk->dwLastChange)
      {

         dwLastUpdate = GetTickCount();

         // rebuild the list of processes
         lb = GetDlgItem(hwnd, IDC_LIST1);
         SendMessage(lb, LB_RESETCONTENT, 0, 0);
         for ( dwCount = 1 ;
             dwCount <= g_pControlChunk->dwcChunksCommitted ;
             dwCount++ )
         {

            pThisChunk = (PCHUNK) ( ( (BYTE *) g_pControlChunk )
                                    + (dwCount * g_uPageSize) );

            if ( pThisChunk->fUsed )
               wsprintf(szNewItem, "Chunk %d used by process %d.", dwCount,
                        pThisChunk->dwPID);
            else
               wsprintf(szNewItem, "Chunk %d no longer in use.", dwCount);

            SendMessage(lb, LB_ADDSTRING, 0, (LPARAM) szNewItem);
         }

      }

   }

}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Cmd_OnCmdCommit - Called when the Commit button is clicked.
//                This function looks for a free chunk of committed memory.
//                If found, the memory is marked as used.  If not found, a new
//                chunk is allocated and marked as used.
//
//  PARAMETERS:   hwnd - dialog handle
//
//  RETURN VALUE: none
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+


void Cmd_OnCmdCommit ( HWND hwnd )
{

   DWORD  dwNextPage = 0, dwCount;
   PCHUNK pThisChunk, pNewChunk;
   LPVOID lpMem;

   // obtain mutex before writing to shared memory
   WaitForSingleObject(g_hMutex, INFINITE);

   // find the first free page
   for ( dwCount = 1 ;
       dwCount <= g_pControlChunk->dwcChunksCommitted ;
       dwCount++ )
   {

      pThisChunk = (PCHUNK) ( ( (BYTE *) g_pControlChunk )
                              + (dwCount * g_uPageSize) );

      if ( !pThisChunk->fUsed )
      {
         dwNextPage = dwCount;
         lpMem = (VOID *) pThisChunk;
         break;
      }

   }

   // if no free page was found, allocate a new one
   if (dwNextPage == 0)
   {

      dwNextPage = g_pControlChunk->dwcChunksCommitted + 1;

      // commit chunk at next available page boundary
      lpMem = VirtualAlloc((VOID *)(((BYTE *)g_pControlChunk )
                                    + (dwNextPage * g_uPageSize)),
                           sizeof(CHUNK), MEM_COMMIT,
                           PAGE_READWRITE);

      // if successfully committed, increment the committed pages counter
      // in the ControlChunk
      if (lpMem != NULL)
         g_pControlChunk->dwcChunksCommitted++;
      else
         MessageBox(hwnd, "Could not allocate new chunk.",
                    "Error", MB_OK + MB_ICONEXCLAMATION);

   }

   // set pNewChunk to point to the newly allocated chunk of shared memory
   pNewChunk = ((CHUNK *) lpMem);
   pNewChunk->fUsed = TRUE;
   pNewChunk->dwPID = GetCurrentProcessId();

   // store any other relevant data in bData member
   // pNewChunk->bData = ...

   // store time of update in third DWORD of control chunk
   g_pControlChunk->dwLastChange = GetTickCount();

   ReleaseMutex(g_hMutex);
}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Cmd_OnCancel - This function closes the dialog box.
//
//  PARAMETERS:   hwnd - dialog handle
//
//  RETURN VALUE: none
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
void Cmd_OnCancel ( HWND hwnd )
{

   EndDialog(hwnd, IDCANCEL);
}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Dlg_OnCommand - mapped to WM_COMMAND via message cracker
//                in Dlg_Proc. This function handles all command messages by
//                calling more specific functions relating to the control id.
//
//  PARAMETERS:   hwnd - dialog handle
//                id - item, control, or accelerator identifier
//                hwndCtl - handle of control
//                codeNotify - notification code
//
//  RETURN VALUE: none
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
void Dlg_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

   switch (id)
   {
   case IDC_CMDCOMMIT:
      Cmd_OnCmdCommit(hwnd);
      break;

   case IDCANCEL:
      Cmd_OnCancel(hwnd);
      break;

   }
}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     Dlg_Proc - This is the dialog procedure callback function
//                which receives all messages sent to the dialog.  It uses
//                message crackers to forward all such messages to more
//                specific functions.
//
//  PARAMETERS:   hwnd - dialog handle
//                uMsg - message identifier
//                wParam - first message parameter
//                lParam - second message parameter
//
//  RETURN VALUE: Except in response to the WM_INITDIALOG message, the dialog
//                box procedure should return nonzero if it processes the
//                message, and zero if it does not. In response to a
//                WM_INITDIALOG message, the dialog box procedure should return
//                zero if it calls the SetFocus function to set the focus to
//                one of the controls in the dialog box. Otherwise, it should
//                return nonzero.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
LONG_PTR CALLBACK Dlg_Proc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

   switch (uMsg)
   {
   case WM_INITDIALOG:
      return (BOOL) HANDLE_WM_INITDIALOG(hwnd, wParam, lParam,
                                         Dlg_OnInitDialog);

   case WM_COMMAND:
      HANDLE_WM_COMMAND(hwnd, wParam, lParam, Dlg_OnCommand);
      return TRUE;

   case WM_DESTROY:
      HANDLE_WM_DESTROY(hwnd, wParam, lParam, Dlg_OnDestroy);
      return TRUE;

   case WM_TIMER:
      HANDLE_WM_TIMER(hwnd, wParam, lParam, Dlg_OnTimer);
      return TRUE;

   }
   return (FALSE);
}



//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//
//  FUNCTION:     WinMain - Entry point for code execution.
//
//  PARAMETERS:   hinstExe - handle to the current instance of the application
//                hinstPrev - always NULL in 32-bit Windows
//                pszCmdLine - pointer to a null-terminated string specifying
//                   the command line for the application
//                nCmdShow - how the window is to be shown
//
//  RETURN VALUE: Always returns zero.
//
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
int WINAPI WinMain ( HINSTANCE hinstExe, HINSTANCE hinstPrev, LPTSTR pszCmdLine,
                     int nCmdShow )
{
   SYSTEM_INFO SystemInfo;

   // Get the CPU page size
   GetSystemInfo(&SystemInfo);
   g_uPageSize = SystemInfo.dwPageSize;

   DialogBox(hinstExe, MAKEINTRESOURCE(IDD_SPARSEMEM), NULL, Dlg_Proc);
   return (0);
}