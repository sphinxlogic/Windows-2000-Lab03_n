/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    implement.c

Abstract:

    This module is included in the project to force the implementation 
    of the stub functions

--*/


#include "pch.h"

#define  IMPLEMENT_CHECK
#include "check.h"

#ifdef   MULTIMON_ENABLED
#define  IMPLEMENT_MULTIMON_STUBS
#include "MMStubs.h"
#endif //MULTIMON_ENABLED

#ifdef   ICM_ENABLED
#define  IMPLEMENT_ICM_STUBS
#include "ICMStubs.h"
#define  IMPLEMENT_STI_STUBS
#include "STIStubs.h"
#endif //ICM_ENABLED

#define  IMPLEMENT_TWAIN_STUBS
#include "TwainStubs.h"
