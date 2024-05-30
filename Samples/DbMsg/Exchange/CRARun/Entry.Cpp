//--entry.cpp-----------------------------------------------------------------
//
// Exchange entry function
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "windows.h"

#include <MAPIX.H>
#include <MAPIUTIL.H>
#include <MAPIFORM.H>

#include "exchcli.h"

#include "crarun.h"

//$--ExchEntryPoint-----------------------------------------------------------
//
//	Parameters - none
//
//	Purpose
//	The entry point called by Exchange.
//
//	Return Value
//	Pointer to Exchange Extension (IExchRuleExt) interface
//
//	Comments
//	Exchange Client calls this for each context entry.  
// ---------------------------------------------------------------------------
extern "C"
LPEXCHANGERULEEXT CALLBACK ExchEntryPoint(void)
{
	return new CExchRuleExt;
};
