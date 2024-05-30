/////////////////////////////////////////////////////////////////////////////// 
//  stdpch.h
//
///////////////////////////////////////////////////////////////////////////////

#pragma once // More efficient method for the guard macros!
#define WIN32_LEAN_AND_MEAN
#define _WIN32_DCOM

#pragma warning( disable : 4018 ) // '<' : signed/unsigned mismatch
#pragma warning( disable : 4786 ) // identifier was truncated to 'number' characters in the debug information
#pragma warning( disable : 4355 ) // 'this' : used in base member initializer list
#pragma warning( disable : 4503 ) // decorated name length exceeded, name was truncated

// STL
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <vector>

// ATL
#include <atlbase.h>

// COM helper classes
#include <comdef.h>

// WBEM
#include <wbemidl.h>

#define EXTASSERT(param) if(!(param)) { printf("%s Assert in wbem helpers\n",__FILE__); printf("...line %d",__LINE__); }

#pragma warning( disable : 4018 ) // '<' : signed/unsigned mismatch


