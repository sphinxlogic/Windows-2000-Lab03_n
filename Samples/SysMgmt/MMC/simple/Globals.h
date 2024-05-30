//==============================================================;
//
//	This source code is only intended as a supplement to existing Microsoft documentation. 
//
//	Use of this code is NOT supported.  
//
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
//
//    Microsoft Premier Support for Developers
//
//==============================================================;

#include <tchar.h>

#define IDM_BUTTON1    0x100
#define IDM_BUTTON2    0x101

extern HINSTANCE g_hinst;
extern ULONG g_uObjects;

#define OBJECT_CREATED InterlockedIncrement((long *)&g_uObjects);
#define OBJECT_DESTROYED InterlockedDecrement((long *)&g_uObjects);
