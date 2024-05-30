/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    pch.h

Abstract:

    Precompiled Headers

--*/

//
// define Windows version to be at least 5
//

#if      !defined(WINVER) || (WINVER < 0x0500)
#undef   WINVER
#define  WINVER 0x0500
#endif //WINVER

#if      !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0500)
#undef   _WIN32_WINNT
#define  _WIN32_WINNT 0x0500
#endif //_WIN32_WINNT

#if      !defined(_WIN32_WINDOWS) || (_WIN32_WINDOWS < 0x0500)
#undef   _WIN32_WINDOWS
#define  _WIN32_WINDOWS 0x0500
#endif //_WIN32_WINDOWS

#if      !defined(_WIN32_IE) || (_WIN32_IE < 0x0500)
#undef   _WIN32_IE
#define  _WIN32_IE 0x0500
#endif //_WIN32_IE

//
// We will use "C" for COM interfaces
//

#define  CINTERFACE

//
// build settings
//

#if defined(DEBUG) || defined(_DEBUG) || defined(DBG)
#pragma message( "DEBUG build" )
#define DEBUG
#endif

#ifdef UNICODE
#pragma message( "UNICODE enabled" )
#endif //UNICODE

#ifdef MULTIMON_ENABLED
#pragma message( "Multimonitor functionality enabled" )
#endif //MULTIMON_ENABLED

#ifdef ICM_INSIDE_DC
#pragma message( "Inside DC ICM functionality enabled" )
#define ICM_ENABLED 
#endif //ICM_INSIDE_DC

#ifdef ICM_OUTSIDE_DC
#pragma message( "Outside DC ICM functionality enabled" )
#define ICM_ENABLED 
#endif //ICM_OUTSIDE_DC

//
// disable some level 4 compiler warnings
//

#pragma warning(disable: 4057) // 'operator' : 'identifier1' indirection to slightly different base types from 'identifier2'
#pragma warning(disable: 4711) // function 'function' selected for inline expansion
#pragma warning(disable: 4706) // assignment within conditional expression

//
// system header files
//

#include <windows.h>
#include <tchar.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <commctrl.h>
#include <commdlg.h>
#include <icm.h>
#include <sti.h>

#ifndef PCTSTR
#define PCTSTR LPCTSTR
#endif //PCTSTR

#ifndef ASSERT
#define ASSERT assert
#endif //ASSERT

//
// our wrapper header files

//
#ifdef MULTIMON_ENABLED
#include "MMStubs.h"
#endif //MULTIMON_ENABLED

#ifdef ICM_ENABLED 
#include "ICMStubs.h"
#include "STIStubs.h"
#endif //ICM_ENABLED 

#include "TwainStubs.h"

