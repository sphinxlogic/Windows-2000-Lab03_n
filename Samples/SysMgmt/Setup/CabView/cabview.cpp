//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
//
//  CabView.cpp
//
//      Defines WinMain, main window procedure and message handlers.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <shellapi.h>
#include "CabView.h"
#include "Resource.h"

// Global variables
HINSTANCE hAppInstance = NULL;          // Applications HINSTANCE
CHAR szExtractPath[MAX_PATH] = "";      // Destination for extracted files

// Listview columns
LVCOLUMN cols[] = 
{
    {LVCF_FMT | LVCF_WIDTH | LVCF_TEXT, LVCFMT_LEFT, 150, "File", 0, 0},
    {LVCF_FMT | LVCF_WIDTH | LVCF_TEXT, LVCFMT_RIGHT, 75, "Size", 1, 0},
    {LVCF_FMT | LVCF_WIDTH | LVCF_TEXT, LVCFMT_LEFT, 150, "Type", 2, 0},
    {LVCF_FMT | LVCF_WIDTH | LVCF_TEXT, LVCFMT_LEFT, 150, "Modified", 3, 0},
    {0, 0, 0, NULL, 0, 0}
};


//
//  CabView_ListViewSortProc
//
INT CALLBACK CabView_ListViewSortProc (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    LPCABINET_FILE_INFO pcfi1 = (LPCABINET_FILE_INFO) lParam1;
    LPCABINET_FILE_INFO pcfi2 = (LPCABINET_FILE_INFO) lParam2;
    INT nIndex = (INT) lParamSort;

    switch (nIndex)
    {
        case 0:
            // Sort by file name
            return lstrcmpi (pcfi1->szFileName, pcfi2->szFileName);

        case 1:
            // Sort by file size
            if (pcfi1->nFileSize > pcfi2->nFileSize)
                return -1;
            else if (pcfi1->nFileSize < pcfi2->nFileSize)
                return 1;
            return 0;

        case 2:
            // Sort by type name
            return lstrcmpi (pcfi1->szTypeName, pcfi2->szTypeName);

        case 3:
            // Sort by file date/time
            return CompareFileTime (&pcfi1->FileTime, &pcfi2->FileTime);
    }
    return 0;
}


//
//  CabView_OpenCabinet - Enumerates the contents of a CAB file and
//                        inserts the list into the listview
//
BOOL WINAPI CabView_OpenCabinet (HWND hWnd, LPCSTR lpCabinetFile)
{
    LPCABVIEW_INFO pcvi = (LPCABVIEW_INFO) GetWindowLong (hWnd, GWL_USERDATA);
    CHAR szCabinetFile[MAX_PATH] = "";
    CHAR szCabinetDir[MAX_PATH] = "";
    CHAR szNewTitle[MAX_PATH] = "";
    BOOL bResult = FALSE;

    // Clear the current contents of the list view in case it hasn't 
    // been done already'
    ListView_DeleteAllItems (GetDlgItem (hWnd, IDC_CABINET_LIST));
    
    // Get the path and filename for the cabinet file
    lstrcpy (szCabinetDir, lpCabinetFile);
    lstrcpy (szCabinetFile, CabView_PathFindFileName (szCabinetDir));
    CabView_RemoveFileName (szCabinetDir);

    // Turn off the list views redraw while we are adding items
    SendDlgItemMessage (hWnd, IDC_CABINET_LIST, WM_SETREDRAW, FALSE, 0);

    // Enumerate all the files in the cabinet file and add them to the list view
    bResult =  Cabinet_Copy (pcvi->hFdi, szCabinetFile, szCabinetDir, 0, 
                             CabView_CabinetNotifyCallback, 
                             CabView_DecryptCallback, (LPVOID)hWnd);
    if (bResult == TRUE)
    {
        pcvi->bCabinetOpen = TRUE;
        lstrcpy (pcvi->szOpenFile, lpCabinetFile);

        // Update the main window title
        wsprintf (szNewTitle, "Cabinet Viewer - %s", szCabinetFile);
        SetWindowText (hWnd, szNewTitle);

        // Sort the list by filename
        ListView_SortItems (GetDlgItem (hWnd, IDC_CABINET_LIST), CabView_ListViewSortProc, 0);
    }
    else
    {
        MessageBox (hWnd, "An error occurred while opening the cabinet file.", "Cabinet Viewer", MB_OK | MB_ICONEXCLAMATION);
        pcvi->bCabinetOpen = FALSE;
        lstrcpy (pcvi->szOpenFile, "");
        SetWindowText (hWnd, "Cabinet Viewer");
    }

    // Turn redraw back on.
    SendDlgItemMessage (hWnd, IDC_CABINET_LIST, WM_SETREDRAW, TRUE, 0);
    return bResult;
}


//
//  CabView_InitializeListView - Creates and initializes the listview's
//                               columns and imagelist
//
HWND WINAPI CabView_InitializeListView (HWND hWnd)
{
    HWND hWndList = NULL;
    HIMAGELIST himl = NULL;
    RECT rect = {0};
    SHFILEINFO shfi = {0};

    // Create a list view to show a cabinet's file list
    GetClientRect (hWnd, &rect);
    hWndList = CreateWindowEx (WS_EX_CLIENTEDGE, WC_LISTVIEW, NULL, 
                               WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHAREIMAGELISTS, 
                               0, 0, rect.right, rect.bottom, 
                               hWnd, (HMENU) IDC_CABINET_LIST, 
                               hAppInstance, NULL);
    if (hWndList != NULL)
    {
        // Initialize the column headers
        INT nCol = 0;
        while (cols[nCol].pszText != NULL)
        {
            ListView_InsertColumn (hWndList, nCol, &cols[nCol]);
            nCol++;
        }

        // Create and set the list view's image list by using a copy of the
        // systems image list
        himl = (HIMAGELIST) SHGetFileInfo ("CabView.exe", FILE_ATTRIBUTE_NORMAL, &shfi, 
                                           sizeof (SHFILEINFO), 
                                           SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
        if (himl)
            ListView_SetImageList (hWndList, himl, LVSIL_SMALL);
    }
    return hWndList;
}


//
//  WM_COMMAND(ID_FILE_OPEN) message handler
//
VOID WINAPI CabView_OnFileOpenCabinet (HWND hWnd, INT id, HWND hWndCtrl, UINT nCode)
{
    CHAR szFile[MAX_PATH] = "";
    OPENFILENAME ofn = {0};

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.hInstance = hAppInstance;
    ofn.lpstrFilter = "Cabinet Files\0*.cab\0All Files\0*.*\0\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY;

    if (GetOpenFileName (&ofn) == TRUE)
        CabView_OpenCabinet (hWnd, szFile);
}


//
//  WM_COMMAND(ID_FILE_CLOSE) message handler
//
VOID WINAPI CabView_OnFileCloseCabinet (HWND hWnd, INT id, HWND hWndCtrl, UINT nCode)
{
    LPCABVIEW_INFO pcvi = (LPCABVIEW_INFO) GetWindowLong (hWnd, GWL_USERDATA);
    pcvi->bCabinetOpen = FALSE;
    lstrcpy (pcvi->szOpenFile, "");

    ListView_DeleteAllItems (GetDlgItem (hWnd, IDC_CABINET_LIST));
    SetWindowText (hWnd, "Cabinet Viewer");
}


//
//  WM_COMMAND(ID_FILE_EXTRACT_xxx) message handler
//
VOID WINAPI CabView_OnFileExtractFiles (HWND hWnd, INT id, HWND hWndCtrl, UINT nCode)
{
    LPCABVIEW_INFO pcvi = (LPCABVIEW_INFO) GetWindowLong (hWnd, GWL_USERDATA);
    CabView_GetDestinationPath (hWnd, szExtractPath);

    UINT nItemCount = 0;
    UINT nFlags = LVNI_ALL;
    UINT uMsg = LVM_GETITEMCOUNT;
    INT iListIndex = 0;
    INT iIndex = -1;
    LPSTR *lpFileList = NULL;
    LVITEM item = {0};
    LPCABINET_FILE_INFO pcfi = NULL;
    CHAR szCabinetFile[MAX_PATH] = "";
    CHAR szCabinetDir[MAX_PATH] = "";

    // Get the path and filename for the cabinet file
    lstrcpy (szCabinetDir, pcvi->szOpenFile);
    lstrcpy (szCabinetFile, CabView_PathFindFileName (szCabinetDir));
    CabView_RemoveFileName (szCabinetDir);

    // Build a list of files to be extracted
    if (id == ID_FILE_EXTRACT_SELECTED)
    {
        nFlags = LVNI_SELECTED;
        uMsg = LVM_GETSELECTEDCOUNT;
    }

    nItemCount = (UINT) SendDlgItemMessage (hWnd, IDC_CABINET_LIST, uMsg, 0, 0);
    lpFileList = (LPSTR *) LocalAlloc (LPTR, sizeof(LPSTR) * (nItemCount + 1));
    if (lpFileList == NULL)
        return;

    item.mask = LVIF_PARAM;
    iIndex = -1;
    while ((-1) != (iIndex = ListView_GetNextItem (GetDlgItem (hWnd, IDC_CABINET_LIST), iIndex, nFlags)))
    {
        item.iItem = iIndex;
        ListView_GetItem (GetDlgItem (hWnd, IDC_CABINET_LIST), &item);
        pcfi = (LPCABINET_FILE_INFO) item.lParam;
        lpFileList[iListIndex++] = pcfi->szFileName;
    }
    lpFileList[iListIndex] = NULL;

    CABINET_EXTRACT_INFO cei = {0};
    cei.lpDestinationDir = szExtractPath;
    cei.lpFileList = lpFileList;

    // Extract the requested files from the cabinet file
    Cabinet_Copy (pcvi->hFdi, szCabinetFile, szCabinetDir, 0, 
                  CabView_ExtractNotifyCallback, 
                  CabView_DecryptCallback, (LPVOID)&cei);

    // Release the file list
    LocalFree ((LPVOID) lpFileList);
}


//
//  WM_COMMAND(ID_HELP_ABOUT) message handler
//
VOID WINAPI CabView_OnHelpAbout (HWND hWnd, INT id, HWND hWndCtrl, UINT nCode)
{
    MessageBox (hWnd, "Sample Cabinet Viewer\n\nCopyright 1999 Microsoft Corporation",
                "Cabinet Viewer Sample", MB_OK | MB_ICONINFORMATION);
}

//
//  WM_COMMAND(ID_FILE_EXIT) message handler
//
VOID WINAPI CabView_OnFileExit (HWND hWnd, INT id, HWND hWndCtrl, UINT nCode)
{
    PostMessage (hWnd, WM_CLOSE, 0, 0);
}


//
//  WM_CREATE message handler
//
BOOL WINAPI CabView_OnCreate (HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    LPCABVIEW_INFO pcvi = (LPCABVIEW_INFO) LocalAlloc (LPTR, sizeof(CABVIEW_INFO));
    if (pcvi == NULL)
        return FALSE;

    pcvi->hFdi = Cabinet_Initialize();
    pcvi->bCabinetOpen = FALSE;
    
    SetWindowLong (hWnd, GWL_USERDATA, (LONG) pcvi);

    GetCurrentDirectory (MAX_PATH, szExtractPath);

    HWND hWndList = CabView_InitializeListView (hWnd);
    if (hWndList == NULL)
        return FALSE;
    return TRUE;
}


//
//  WM_CLOSE message handler
//
VOID WINAPI CabView_OnClose (HWND hWnd)
{
    DestroyWindow (hWnd);
}


//
//  WM_DESTROY message handler
//
VOID WINAPI CabView_OnDestroy (HWND hWnd)
{
    LPCABVIEW_INFO pcvi = (LPCABVIEW_INFO) GetWindowLong (hWnd, GWL_USERDATA);
    Cabinet_Uninitialize (pcvi->hFdi);
    LocalFree ((LPVOID) pcvi);
    PostQuitMessage (0);
}


//
//  WM_SIZE message handler
//
VOID WINAPI CabView_OnSize (HWND hWnd, UINT state, INT cx, INT cy)
{
    MoveWindow (GetDlgItem(hWnd, IDC_CABINET_LIST), 0, 0, cx, cy, TRUE);
}


//
//  WM_INITPOPUPMENU message handler
//
VOID WINAPI CabView_OnInitMenuPopup (HWND hWnd, HMENU hMenu, UINT iItem, BOOL fSysMenu)
{
    LPCABVIEW_INFO pcvi = (LPCABVIEW_INFO) GetWindowLong (hWnd, GWL_USERDATA);

    if (iItem == 0)
    {
        // The 'File' menu is being opened. Initially disable all the items,
        // then enable the items we want
        CabView_DisableAllMenuItems (hMenu);

        // 'Open Cabinet' and 'Exit' are always enabled
        EnableMenuItem (hMenu, ID_FILE_OPEN, MF_BYCOMMAND|MF_ENABLED);
        EnableMenuItem (hMenu, ID_FILE_EXIT, MF_BYCOMMAND|MF_ENABLED);

        // Enable 'Close' only if a cabinet is 'opened'
        // Enable 'Extract' only if a cabinet is opened
        // Enable 'Extract | All Files' only if a cabinet is opened
        if (pcvi->bCabinetOpen == TRUE)
        {
            EnableMenuItem (hMenu, ID_FILE_CLOSE, MF_BYCOMMAND|MF_ENABLED);
            EnableMenuItem (hMenu, 2, MF_BYPOSITION|MF_ENABLED);
            EnableMenuItem (GetSubMenu(hMenu, 2), ID_FILE_EXTRACT_ALL, MF_BYCOMMAND|MF_ENABLED);
        }

        // Enable 'Extract Selected Files' only if files(s) are selected
        if (ListView_GetSelectedCount (GetDlgItem (hWnd, IDC_CABINET_LIST)) > 0)
            EnableMenuItem (GetSubMenu(hMenu, 2), ID_FILE_EXTRACT_SELECTED, MF_BYCOMMAND|MF_ENABLED);
    }
}


//
//  WM_NOTIFY message handler
//
LRESULT WINAPI CabView_OnNotify (HWND hWnd, INT idCtrl, LPNMHDR pnmhdr)
{
    LPNMLISTVIEW pnmlv = (LPNMLISTVIEW) pnmhdr;
    NMLVDISPINFO *pnmlvdi = (NMLVDISPINFO *) pnmhdr;
    LPCABINET_FILE_INFO pcfi = NULL;
    SHFILEINFO shfi;
    LVITEM item = {0};
    
    switch (pnmhdr->code)
    {
        case HDN_ITEMCLICK:
        {
            // One of the column headers has been clicked. 
            NMHEADER *pnmh = (NMHEADER *) pnmhdr;

            // Handle left-click only
            if (pnmh->iButton == 0)
            {
                // Sort the list by the column that was clicked
                ListView_SortItems (GetDlgItem (hWnd, IDC_CABINET_LIST), CabView_ListViewSortProc, pnmh->iItem);
            }
            return 0;
        }

        case LVN_DELETEITEM:
            item.mask = LVIF_PARAM;
            item.iItem = pnmlv->iItem;
            ListView_GetItem (pnmhdr->hwndFrom, &item);

            LocalFree ((LPVOID)(LPCABINET_FILE_INFO) item.lParam);
            return 0;

        case LVN_GETDISPINFO:
            item.mask = LVIF_PARAM;
            item.iItem = pnmlvdi->item.iItem;
            ListView_GetItem (pnmhdr->hwndFrom, &item);
            pcfi = (LPCABINET_FILE_INFO) item.lParam;

            switch (pnmlvdi->item.iSubItem)
            {
                case 0:
                    lstrcpyn (pnmlvdi->item.pszText, pcfi->szFileName, pnmlvdi->item.cchTextMax);
                    SHGetFileInfo (pcfi->szFileName, FILE_ATTRIBUTE_NORMAL, &shfi, 
                                   sizeof (SHFILEINFO), 
                                   SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
                    pnmlvdi->item.iImage = shfi.iIcon;
                    return 0;

                case 1:
                    CabView_FormatFileSize (pnmlvdi->item.pszText, pnmlvdi->item.cchTextMax, pcfi->nFileSize);
                    return 0;

                case 2:
                    lstrcpyn (pnmlvdi->item.pszText, pcfi->szTypeName, pnmlvdi->item.cchTextMax);
                    return 0;

                case 3:
                    CabView_FormatFileDateTime (pnmlvdi->item.pszText, pnmlvdi->item.cchTextMax, &pcfi->FileTime);
                    return 0;
            }
    }
    return 0;
}


//
//  WM_COMMAND message handler
//
VOID WINAPI CabView_OnCommand (HWND hWnd, INT id, HWND hWndCtrl, UINT nCode)
{
    switch (id)
    {
        HANDLE_WM_COMMAND_ID (ID_FILE_OPEN, CabView_OnFileOpenCabinet);
        HANDLE_WM_COMMAND_ID (ID_FILE_CLOSE, CabView_OnFileCloseCabinet);
        HANDLE_WM_COMMAND_ID (ID_FILE_EXTRACT_SELECTED, CabView_OnFileExtractFiles);
        HANDLE_WM_COMMAND_ID (ID_FILE_EXTRACT_ALL, CabView_OnFileExtractFiles);
        HANDLE_WM_COMMAND_ID (ID_FILE_EXIT, CabView_OnFileExit);
        HANDLE_WM_COMMAND_ID (ID_HELP_ABOUT, CabView_OnHelpAbout);
    }
}


//
//  CabView_WindowProc
//
LRESULT CALLBACK CabView_WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hWnd, WM_CREATE, CabView_OnCreate);
        HANDLE_MSG(hWnd, WM_CLOSE, CabView_OnClose);
        HANDLE_MSG(hWnd, WM_SIZE, CabView_OnSize);
        HANDLE_MSG(hWnd, WM_INITMENUPOPUP, CabView_OnInitMenuPopup);
        HANDLE_MSG(hWnd, WM_DESTROY, CabView_OnDestroy);
        HANDLE_MSG(hWnd, WM_COMMAND, CabView_OnCommand);
        HANDLE_MSG(hWnd, WM_NOTIFY, CabView_OnNotify);
    }
    return DefWindowProc (hWnd, uMsg, wParam, lParam);
}


//
//  WinMain
//
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    InitCommonControls();

    hAppInstance = hInstance;

    //
    //  Register the application's main window
    //
    WNDCLASS wc = {0};
    wc.style            = 0;
    wc.lpfnWndProc      = CabView_WindowProc;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon (hInstance, MAKEINTRESOURCE (IDI_APPICON));
    wc.hCursor          = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName     = MAKEINTRESOURCE (IDR_MENU1);
    wc.lpszClassName    = WC_CABVIEW;

    if (!RegisterClass (&wc))
        return -1;

    //
    //  Create the main window
    //
    HWND hWndMain = CreateWindowEx (0, WC_CABVIEW, TEXT("Cabinet Viewer"),
                                    WS_OVERLAPPEDWINDOW,
                                    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
                                    NULL, NULL, hInstance, NULL);
    if (!hWndMain)
        return 0;

    //
    //  Update and show the main window
    //
    UpdateWindow (hWndMain);
    ShowWindow (hWndMain, nCmdShow);

    //
    //  Create the application's message loop
    //
    MSG msg;
    while (GetMessage (&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
	return 0;
}

