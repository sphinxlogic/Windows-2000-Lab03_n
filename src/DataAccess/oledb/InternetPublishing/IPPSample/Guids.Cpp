/*------------------------------------------------------------------------------
	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
	ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
	TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

	guids.cpp

	All the code for the sample.

------------------------------------------------------------------------------*/
// By default, the oledb.h file declares all of its constants as extern.
// By defining "DBINITCONSTANTS" before including it, the values will be
// supplied so that the linker will not complain about unresolved externals.
// We need to do this once and exactly once -- everywhere else we include
// the file should not have DBINITCONSTANTS defined.
#define OLEDBVER 0x0250

#include "stdafx.h"

#define DBINITCONSTANTS
#include <oledb.h>

#define INITGUID
#include <initguid.h>
#include <msdaipp.h>
