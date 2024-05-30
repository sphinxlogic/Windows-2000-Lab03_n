//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright (C) 1995-1999 Microsoft Corporation
//
// @doc 
//
// @module TEMPLATE.CPP | Template source file for all test modules.
//

#include "modstandard.hpp"
#define  DBINITCONSTANTS	// Must be defined to initialize constants in OLEDB.H
#define  INITGUID
#include "template.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Module Values
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// {{ TCW_MODULE_GLOBALS *
DECLARE_MODULE_CLSID = { 0x17dff980, 0x64a3, 0x11ce, { 0xb1, 0x24, 0x00, 0xaa, 0x00, 0x57, 0x59, 0x9e }};
DECLARE_MODULE_NAME("Enter your module name here");
DECLARE_MODULE_OWNER("Enter your email name here");
DECLARE_MODULE_DESCRIP("Enter module description here");
DECLARE_MODULE_VERSION(795921705);
// }}


//--------------------------------------------------------------------
// @func Module level initialization routine
//
// @rdesc Success or Failure
// 		@flag  TRUE  | Successful initialization
//		@flag  FALSE | Initialization problems
//
BOOL ModuleInit(CThisTestModule * pThisTestModule)
{
	return TRUE;
}	
  
//--------------------------------------------------------------------
// @func Module level termination routine
//
// @rdesc Success or Failure
// 		@flag  TRUE  | Successful initialization
//		@flag  FALSE | Initialization problems
//
BOOL ModuleTerminate(CThisTestModule * pThisTestModule)
{
	return TRUE;
}	



// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Test Case Section
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// }} END_DECLARE_TEST_CASES()

// {{ TCW_TESTMODULE(ThisModule)
TEST_MODULE(0, ThisModule, gwszModuleDescrip)
END_TEST_MODULE()
// }}




