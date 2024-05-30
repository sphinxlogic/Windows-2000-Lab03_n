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
 **     CAgentPropPageProvider
 **
 ** NOTES
 **     Property page PROVIDER implementation for the agent (ATL based.)
 **
 ****************************************************************************/

#include "stdafx.h"
#include "Agent.h"
#include "AgentPropPage.h"
#include "AgentPropPageProvider.h"

#define  AGENT_NAME _T("Sample")


/*==========================================================================
  %%Function:   UpdateRegistry
  %%Parameters: BOOL    -- Determines whether the ATL class's 
                           object factory is to be [un]registered.
  %%Returns:    HRESULT -- Successfully [un]registered
  %%Desc:       DECLARE_REGISTRY_RESOURCEID(IDR_MYCOMAPP)
                This macro expands to:
                    static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
                    {
                        return _Module.UpdateRegistryFromResource(IDR_MYCOMAPP, 
                                                                  bRegister);
                    }
                Enhanced UpdateRegistry function to register the Agent as
                well as do the work done by the macro.
  ==========================================================================*/
HRESULT WINAPI CAgentPropPageProvider::UpdateRegistry(BOOL bRegister)
{
    HRESULT hRes = S_OK;

    CRegKey rootKey;
    RET_IF_WIN32ERR(rootKey.Create(HKEY_LOCAL_MACHINE, AGENTS_KEY));

    if (bRegister)
    {
        CRegKey rk;
        RET_IF_WIN32ERR(rk.Create(rootKey, AGENT_NAME));

        LPOLESTR lpCLSID = NULL;
        RET_IF_ERR(StringFromCLSID(CLSID_AgentPropPageProvider, &lpCLSID));
        CString strCLSID(lpCLSID);
        CoTaskMemFree(lpCLSID);

        RET_IF_WIN32ERR(rk.SetValue(AGENT_NAME,               _T("Display Name")));
        RET_IF_WIN32ERR(rk.SetValue(strCLSID,                 _T("COM Property Sheet")));
        RET_IF_WIN32ERR(rk.SetValue(_T("AgSampleAgent.ASP"),  _T("ASP Property Page")));
        RET_IF_WIN32ERR(rk.SetValue(_T("WizSampleAgent.ASP"), _T("ASP Wizard Page")));
        RET_IF_WIN32ERR(rk.SetValue(_T("SampleAgent.VBS"),    _T("Script Pathname")));
        RET_IF_WIN32ERR(rk.SetValue(_T("VBScript"),           _T("Script Language")));
    }
    else
    {
        // Ignore errors if the key could not be deleted
        rootKey.RecurseDeleteKey(AGENT_NAME);
    }

    // Call the ATL implementation (work done by DECLARE_REGISTRY_RESOURCEID)
    return _Module.UpdateRegistryFromResource(IDR_AGENTPROPPAGEPROVIDER, bRegister);
}


/*==========================================================================
  %%Function:   GetPages
  %%Parameters: CAUUID *pPages  -- The CAUUID structure is a Counted Array 
                                   of UUID or GUID types.
  %%Returns:    HRESULT         -- Success
  %%Desc:       Fills a counted array of GUID values where each GUID 
                specifies the CLSID of each property page that can be 
                displayed in the property sheet for this object. 
  ==========================================================================*/
STDMETHODIMP CAgentPropPageProvider::GetPages(CAUUID *pPages)
{
    GUID *pGUID = NULL;
    pPages->cElems = 0;
    pPages->pElems = NULL;

    // This is freed by the caller
    pGUID = (GUID *) CoTaskMemAlloc(1 * sizeof(GUID));
    if (NULL == pGUID)
        return E_OUTOFMEMORY;

    pGUID[0] = CAgentPropPage::guid;
    
    pPages->cElems = 1;
    pPages->pElems = pGUID;

    return S_OK;
}

