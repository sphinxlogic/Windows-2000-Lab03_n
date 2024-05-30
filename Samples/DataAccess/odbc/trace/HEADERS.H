//
// HEADERS.H:	Pre-compiled header file for ODBCTRAC.C.
//
// This is the driver manager's helper dll for implementing tracing of
// the ODBC API.   
//
// Copyright (C) 1995-1998 by Microsoft.   All rights reserved.
//

#define SQL_DESC_BIND_OFFSET		9999		// junk
#define SQL_DESC_UPDATEABLE SQL_DESC_UPDATABLE

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <malloc.h>
#include "trace.h"


#pragma hdrstop
