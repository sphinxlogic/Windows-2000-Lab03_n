// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright  1994-1998  Microsoft Corporation.  All Rights Reserved.
//
// PROGRAM:    CSSAMP
//
// PURPOSE:    Demonstrate and test Uniscribe APIs
//
// PLATFORMS:  Windows 95, 98, NT 4, NT 5.
//


#include "precomp.hxx"

#define GLOBALS_HERE 1
#include "global.h"






////    Initialise
//


void Initialise() {

    InitStyles();
    InitText();
}






////    WinMain - Application entry point and dispatch loop
//
//


int APIENTRY WinMain(
    HINSTANCE   hInst,
    HINSTANCE   hPrevInstance,
    char       *pCmdLine,
    int         nCmdShow) {

    MSG         msg;
    HACCEL      hAccelTable;
    RECT        rc;
    RECT        rcMain;


    g_hInstance = hInst;  // Global hInstance


    Initialise();


    // Create main text window

    g_hTextWnd = CreateTextWindow();


    // Add dialog box on leading side

    g_hSettingsDlg = CreateDialog(
        g_hInstance,
        "Settings",
        g_hTextWnd,
        SettingsDlgProc);


        // Establish positon of text surface relative to the dialog

    GetWindowRect(g_hSettingsDlg, &rc);

    g_iSettingsWidth = rc.right - rc.left;
    g_iSettingsHeight = rc.bottom - rc.top;

    // Establish offset from main window to settings dialog

    GetWindowRect(g_hTextWnd, &rcMain);
    g_iMinWidth = rc.right - rcMain.left;
    g_iMinHeight = rc.bottom - rcMain.top;



    // Size main window to include dialog and text surface

    SetWindowPos(
        g_hTextWnd,
        NULL,
        0,0,
        g_iMinWidth * 29 / 10, g_iMinHeight,
        SWP_NOZORDER | SWP_NOMOVE);

    ShowWindow(g_hTextWnd, SW_SHOWNORMAL);


    InvalidateText();
    UpdateWindow(g_hTextWnd);


    // Main message loop

    if (g_bUnicodeWnd) {

        hAccelTable = LoadAcceleratorsW(g_hInstance, APPNAMEW);

        while (GetMessageW(&msg, (HWND) NULL, 0, 0) > 0) {

            if (g_hSettingsDlg == (HWND) NULL ||
                !IsDialogMessageW(g_hSettingsDlg, &msg) &&
                !TranslateAcceleratorW(g_hTextWnd, hAccelTable, &msg)) {

                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }

    } else {

        hAccelTable = LoadAcceleratorsA(g_hInstance, APPNAMEA);

        while (GetMessageA(&msg, (HWND) NULL, 0, 0) > 0) {

            if (g_hSettingsDlg == (HWND) NULL ||
                !IsDialogMessageA(g_hSettingsDlg, &msg) &&
                !TranslateAcceleratorA(g_hTextWnd, hAccelTable, &msg)) {

                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
    }



    FreeStyles();
    return msg.wParam;


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(pCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
}
