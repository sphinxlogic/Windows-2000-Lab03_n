/*
 * jdbghlpr.cpp - Main module.
 *
 * (C) Copyright 1996 Microsoft Corporation
 */


/* Headers
 **********/

#include "project.hpp"
#pragma hdrstop


/****************************** Public Functions *****************************/


#pragma warning(disable:4100)	// "unreferenced formal parameter" warning

BOOL APIENTRY DllMain(HINSTANCE hDLL, DWORD dwReason, PVOID pvReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hDLL);
			break;
	}
	
	return(TRUE);
}

#pragma warning(default:4100) 	// "unreferenced formal parameter" warning

DWORD __cdecl RNIGetCompatibleVersion()
{
	return RNIVER;
}
