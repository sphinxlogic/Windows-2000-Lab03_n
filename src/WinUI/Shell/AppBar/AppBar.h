// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1999  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   	appbar.h
//
//  PURPOSE:   	Contains prototypes and constants for appbar.c.
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//


//////////////////////////////////////////////////////////////////////////////
// Constants and Enumerations

#define CX_DEFWIDTH 	80
#define CY_DEFHEIGHT 	60

#define IDT_AUTOHIDE 	1
#define IDT_AUTOUNHIDE 	2

#define APPBAR_TOP		0
#define APPBAR_BOTTOM	1
#define APPBAR_LEFT		2
#define APPBAR_RIGHT	3


//////////////////////////////////////////////////////////////////////////////
// Types

typedef struct tagOPTIONS
{
	BOOL fAutoHide;
	BOOL fOnTop;
	BOOL fHiding;
	UINT uSide;
	DWORD cxWidth;
	DWORD cyHeight;
	RECT rcEdges[4];
} OPTIONS, *POPTIONS;


//////////////////////////////////////////////////////////////////////////////
// Global Variables

extern BOOL g_fAppRegistered;
extern RECT g_rcAppBar;				   // BUGBUG: Get rid of this!


//////////////////////////////////////////////////////////////////////////////
// Prototypes

void AppBar_Size(HWND);
void AppBar_QueryPos(HWND, LPRECT);
void AppBar_QuerySetPos(UINT, LPRECT, PAPPBARDATA, BOOL);
void AppBar_Callback(HWND, UINT, WPARAM, LPARAM);
void AppBar_PosChanged(PAPPBARDATA);
BOOL AppBar_SetAutoHide(HWND hwnd, BOOL fHide);
BOOL AppBar_UnRegister(HWND hwnd);
BOOL AppBar_Register(HWND hwnd);
BOOL AppBar_SetSide(HWND hwnd, UINT uSide);
void AppBar_SetAlwaysOnTop(HWND hwnd, BOOL fOnTop);
void AppBar_Hide(HWND hwnd);
void AppBar_UnHide(HWND hwnd);
void AppBar_SetAutoHideTimer(HWND hwnd);
void AppBar_SetAutoUnhideTimer(HWND hwnd);
POPTIONS GetAppbarData(HWND);                                  


