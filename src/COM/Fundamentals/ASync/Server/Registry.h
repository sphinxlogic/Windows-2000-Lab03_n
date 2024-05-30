/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */

#ifndef __Registry_H__
#define __Registry_H__
//
// Registry.h
//   - Helper functions registering and unregistering a component.
//

// This function will register a component in the Registry.
// The component calls this function from its DllRegisterServer function.

// Forward reference
struct CFactoryData;

HRESULT RegisterServer(HMODULE hModule,            // DLL module handle
					   CFactoryData& classData);
// This function will unregister a component.  Components
// call this function from their DllUnregisterServer function.

HRESULT UnregisterServer(HMODULE hModule,            // DLL module handle
					   CFactoryData& classData);

// Helper function to register the typelib
HRESULT RegisterLibrary(HMODULE hModule, const GUID& pLibIID, LPCSTR szPath = NULL);

// Helper functions to register/unregistry custom proxy
HRESULT RegisterProxy(HMODULE hModule, LPCSTR szPath = NULL);
HRESULT UnRegisterProxy(HMODULE hModule, LPCSTR szPath = NULL);
#endif