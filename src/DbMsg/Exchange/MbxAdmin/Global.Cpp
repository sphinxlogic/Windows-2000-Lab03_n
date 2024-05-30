//--global.cpp----------------------------------------------------------------
//
// Contains global object declarations.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//---------------------------------------------------------------------------

#include "edkafx.h"
#define _GLOBAL_OBJECTS_

// ---------------------------------------------------------------------------
// The purpose of this C++ file is to instantiate global objects in an order
// that can be depended upon.  
//
// In C++, if you have a global object whose constructor depends upon another 
// object having been constructed, you can run into problems with the
// randomness which the many object modules get linked.
//
// By instantiating all dependant objects in a single source module,
// construction will occur in the order defined.
//
// Declarations are surrounded by #ifdef _GLOBAL_OBJECTS_ and
// #endif //_GLOBAL_OBJECTS_.  This will cause them to be defined only once
// in this module (global.cpp)
// ---------------------------------------------------------------------------

#include "exadmin.h"    // This header file MUST be listed here.
#include "mbxadmin.h"
#include "errcpp.h"     // This MUST be included so that CHRESULT works.
