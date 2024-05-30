/*
 * project.hpp - Project C++ header file.
 *
 * (C) Copyright 1996 Microsoft Corporation
 */


#ifndef __PROJECT_HPP__
#define __PROJECT_HPP__


/* System Headers
 *****************/

#define INC_OLE2                // for windows.h
#define CONST_VTABLE            // for objbase.h
#define WIN32_LEAN_AND_MEAN     // for windows.h

#pragma warning(disable:4514)   // "unreferenced inline function" warning

#pragma warning(disable:4201)   // "nameless struct/union" warning

#include <windows.h>

#pragma warning(default:4201)   // "nameless struct/union" warning


/* Project Headers
 ******************/

#include <native.h>
#include <nativcom.h>
#include <javadbg.h>


/* Constants
 ************/

// constants to be used with #pragma data_seg()

#define DATA_SEG_READ_ONLY      ".text"
#define DATA_SEG_PER_INSTANCE   ".data"
#define DATA_SEG_SHARED         ".shared"


#endif  // ! __PROJECT_HPP__

