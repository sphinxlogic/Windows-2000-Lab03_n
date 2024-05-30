// -----------------------------------------------------------------------------
// Global.CPP -- Contains global object declarations.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edkafx.h"
#define _GLOBAL_OBJECTS_

// -----------------------------------------------------------------------------
// The purpose of this C++ file is to instantiate global objects in an order that 
// can be depended upon.  
//
// In C++, if you have a global object whose constructor depends upon another 
// object having been constructed, you can run into problems with the randomness
// which the many object modules get linked.
//
// By instantiating all dependant objects in a single source module, construction
// will occur in the order defined.
//
// One way to do this is to instantiate the objects in the header file which they 
// are declared in.  Surround the declarations by #ifdef _GLOBAL_OBJECTS_
// and #endif //_GLOBAL_OBJECTS_.  This will cause them to be defined only once
// in this module (Global.CPP).  Then include those header files below.
//
// Another way would be to include the header file which declare the objects
// needed and to then place the definition directly below the header file.  This
// is not as clean and is not recommended.
// -----------------------------------------------------------------------------

#include "ExAdmin.h"    // This header file must be listed here.
#include "queview.h"
#include "ErrCpp.h"     // This MUST be included so that CHRESULT works.
