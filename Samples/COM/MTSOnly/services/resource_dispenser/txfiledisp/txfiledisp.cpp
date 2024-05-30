
/******************************************************************************\
********************************************************************************
* Filename: TxFileDisp.cpp
*
* Description: Implementation of DLL Exports.
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/
#include "stdafx.h"
#include "resource.h"
#include "..\..\..\common\inc\TxFileDisp.h"
#define IID_DEFINED
#define INITGUID
#include "initguid.h"
#include "..\..\..\common\inc\copyfilerm.h"
#include "mtxdm.h"

#include "..\..\..\common\inc\TxFileDisp_i.c"
#include "mtxdm_i.c"
#include "..\..\..\common\inc\copyfilerm_i.c"
#include "txcoord.h"
#include "FileRmPxy.h"
// need to include these to define the GUIDs in this segment
#include "txdtc.h"
#include "xolehlp.h"


#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CRdModule _Module;


LONG CRdModule::Unlock()
{
	return  CComModule::Unlock();
}

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_FileRmPxy, CFileRmPxy)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	lpReserved;
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	HRESULT hRes = PrxDllRegisterServer();
	if (FAILED(hRes))
		return hRes;
#endif
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif
	_Module.UnregisterServer();
#if _WIN32_WINNT >= 0x0400
	UnRegisterTypeLib(LIBID_TXFILEDISPLib, 1, 0, LOCALE_USER_DEFAULT, SYS_WIN32);
#endif
	return S_OK;
}


