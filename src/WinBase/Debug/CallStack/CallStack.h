/*----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.


CallStack.H

This file implements the function prototype of LogStackWalk()
helper function that can be used to obtain stack trace.
----------------------------------------------------------------------------*/

#ifndef __CALLSTACK_H__
#define __CALLSTACK_H__

#include <windows.h>

#ifdef __cplusplus
extern "C"
{
#endif

    DWORD LogStackWalk(LPEXCEPTION_POINTERS exceptionInfo);

#ifdef __cplusplus
}
#endif

#endif // __CALLSTACK_H__
