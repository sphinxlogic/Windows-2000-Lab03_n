/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */
/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include "classfact.h"
#include "..\..\common\debug.h"
#include "..\..\common\guid.h"


HINSTANCE   g_hInst;	//	Instance handle of the dll

long g_ObjectCount =0;	//	to keep count of object of the dll. This is needed to find if the dll can be 
						//	unloaded or not.

ULONG g_cLockCount; //	Keep track if the Class Factory is locked or not
/****************************************************************************

        FUNCTION: BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)

        PURPOSE: Dll entry point

        COMMENTS:

****************************************************************************/
extern "C" 
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			DebugTrace(TEXT("DLL_PROCESS_ATTACH.\r\n"));
			// initialize object count to zero
			g_ObjectCount = 0;
			// initialize Class factory Lock Count to zero
			g_cLockCount = 0;
			g_hInst = hInstance;
			break;
		default:
			break;
	}
	return TRUE;
}                                 


/****************************************************************************

        FUNCTION: STDAPI DllGetClassObject( REFCLSID rclsid, REFIID riid, LPVOID *ppReturn)

        PURPOSE: This function is need for all COM Inproc Server, This the entry point, 
				 when Client does a CoCreateInstance or CoGetClassObject

        COMMENTS:

****************************************************************************/
STDAPI DllGetClassObject( REFCLSID rclsid, REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	DebugTrace(TEXT("DllGetClassObject.\r\n"));

	//	if we don't support this classid, return the proper error code
	if(!IsEqualCLSID(rclsid, CLSID_INumberToTextHandlerWithXData))
		return CLASS_E_CLASSNOTAVAILABLE;

	//	Check if class factory supports this interface. 
	if(!IsEqualIID(riid, IID_IUnknown) &&
		!IsEqualIID(riid, IID_IClassFactory))
		return E_NOINTERFACE;
   
	//	create a CClassFactory object and check it for validity
	CMyClassFactory *pClassFactory;
	pClassFactory = new CMyClassFactory;
	if(pClassFactory==NULL)
		return E_OUTOFMEMORY;

	//	Add ref since we create a new object.
	pClassFactory->AddRef();
	*ppReturn = (LPVOID) pClassFactory;

	return NOERROR;
}

/****************************************************************************

        FUNCTION: STDAPI DllCanUnloadNow(void)

        PURPOSE: This function is called by COM, to see if this dll can be unloaded or not.

        COMMENTS:

****************************************************************************/
STDAPI DllCanUnloadNow(void)
{
//	return true if the Object count is zero and locked count is zero
	return (g_ObjectCount == 0 && g_cLockCount == 0) ? S_OK : S_FALSE;
}


