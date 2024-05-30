//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       MAIN.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"


//****************************************************************************
//
// Global Variables
//
//****************************************************************************

HINSTANCE ghInst       = NULL;          // Current Instance
HACCEL    ghAccelTable = NULL;          // Menu accelerators
HMENU     ghMenu       = NULL;          // Main Menu
HWND      ghwndMain    = NULL;          // Main Window

HWND      ghwndSbar    = hwndNil;       // Status bar window
HWND      ghwndTbar    = hwndNil;       // Toolbar window
HWND      ghwndMsg     = hwndNil;       // Message window
HWND      ghwndChat    = hwndNil;       // Chat Edit Control
HWND      ghwndSend    = hwndNil;       // Send Button
HWND      ghwndUList   = hwndNil;       // User List
HWND      ghwndLView   = hwndNil;       // Main List View	
HWND      ghwndEntry   = hwndNil;       // szEntry Edit control
HFONT     ghfontEntry  = hfontNil;      // Font for edit control

PREF      gPref;                        // User preferences
int       gdxWndMin    = 325;           // maximum size of window
int       gdyWndMin    = 250;           // maximum size of window



//****************************************************************************
//
// Main Windows entrypoint
//
//****************************************************************************

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR  lpszCmd, int nCmdShow)
{
	ghInst = hInstance;

	if (FInitApp(lpszCmd, nCmdShow))
	{
		MSG  msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, ghAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

    // Uninitialize OLE
    CoUninitialize();

	return 0;
}


