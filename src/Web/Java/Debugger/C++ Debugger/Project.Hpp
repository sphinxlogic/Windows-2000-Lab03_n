/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

   project.hpp

Abstract:

   Project C++ header file.

--*/


#ifndef __PROJECT_HPP__
#define __PROJECT_HPP__


/* System Headers
 *****************/

#define INC_OLE2                 // for windows.h
#define WIN32_LEAN_AND_MEAN      // for windows.h
#define CONST_VTABLE             // for objbase.h

#include <windows.h>


/* Constants
 ************/

//
// Constants to be used with #pragma data_seg().
//

#define DATA_SEG_READ_ONLY    	".text"
#define DATA_SEG_PER_INSTANCE		".data"


#endif	/* ! __PROJECT_HPP__ */

