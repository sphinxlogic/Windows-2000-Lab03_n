/****************************************************************************
 ** 
 ** Microsoft Site Server v3.00
 ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
 ** 
 ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
 ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
 ** PURPOSE.
 **
 **
 ** CONTENTS
 **     CAgentApp
 **     Entry points for COM server
 **
 ** NOTES
 **     Boot-straps ATL and MFC to initialize COM objects.
 **     The agent property page provider is implemented in ATL.
 **     The agent property page is implemented in MFC.
 ****************************************************************************/

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "Agent.h"
#include "Agent_i.c"
#include "AgentPropPageProvider.h"


class CAgentApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
    virtual int  ExitInstance();
};

CAgentApp  theApp;      // MFC Application
CComModule _Module;     // ATL Application

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_AgentPropPageProvider, CAgentPropPageProvider)
END_OBJECT_MAP()


/*==========================================================================
  %%Function:   InitInstance
  %%Parameters: 
  %%Returns:    BOOL -- Nonzero if initialization is successful; otherwise 0.
  %%Desc:       Registers all objects (MFC + ATL.)
  ==========================================================================*/
BOOL CAgentApp::InitInstance()
{
    COleObjectFactory::RegisterAll();
    _Module.Init(ObjectMap, m_hInstance);
    return CWinApp::InitInstance();
}


/*==========================================================================
  %%Function:   ExitInstance
  %%Parameters: 
  %%Returns:    int -- The application's exit code (0=success)
  %%Desc:       Revokes all objects (MFC + ATL.)
  ==========================================================================*/
int CAgentApp::ExitInstance()
{
    COleObjectFactory::RevokeAll();
    _Module.Term();
    return CWinApp::ExitInstance();
}


/*==========================================================================
  %%Function:   DllCanUnloadNow
  %%Parameters: 
  %%Returns:    
  %%Desc:       Used to determine whether the DLL can be unloaded by OLE.
  ==========================================================================*/
STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? 
           S_OK : S_FALSE;
}


/*==========================================================================
  %%Function:   DllGetClassObject
  %%Parameters: REFCLSID rclsid -- CLSID for the class object
                REFIID riid     -- Reference to the identifier of the 
                                   interface that communicates with the 
                                   class object 
                LPVOID* ppv     -- Indirect pointer to the communicating 
                                   interface
  %%Returns:    HRESULT
  %%Desc:       Returns a class factory to create an object of the requested 
                type.  It first tries to get the object from ATL and then
                MFC in case of failure.
  ==========================================================================*/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    if (FAILED(_Module.GetClassObject(rclsid, riid, ppv)))
        return AfxDllGetClassObject(rclsid, riid, ppv);
    return S_OK;
}


/*==========================================================================
  %%Function:   DllRegisterServer
  %%Parameters: 
  %%Returns:    HRESULT
  %%Desc:       Adds entries to the system registry (MFC + ATL objects.)
  ==========================================================================*/
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    COleObjectFactoryEx::UpdateRegistryAll(TRUE);
    return _Module.RegisterServer(TRUE);
}


/*==========================================================================
  %%Function:   DllUnregisterServer
  %%Parameters: 
  %%Returns:    HRESULT
  %%Desc:       Removes entries from the system registry (MFC + ATL objects.)
  ==========================================================================*/
STDAPI DllUnregisterServer(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    COleObjectFactoryEx::UpdateRegistryAll(FALSE);
    _Module.UnregisterServer();
    return S_OK;
}


