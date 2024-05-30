/*

Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.

*/

#include <objbase.h>
#include <initguid.h>
#include "jnatcom.h"
#include "common.h"

extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv) ;
extern "C" STDAPI DllRegisterServer(VOID) ;
extern "C" STDAPI DllUnregisterServer(VOID) ;
extern "C" STDAPI DllCanUnloadNow(void) ;
