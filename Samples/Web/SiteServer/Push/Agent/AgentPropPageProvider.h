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
 **
 ** NOTES
 **
 ****************************************************************************/

#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAgentPropPageProvider
class ATL_NO_VTABLE CAgentPropPageProvider : 
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CAgentPropPageProvider, &CLSID_AgentPropPageProvider>,
    public IDispatchImpl<IAgentPropPageProvider, &IID_IAgentPropPageProvider, &LIBID_AGENTLib>,
    public ISpecifyPropertyPages
{
public:
    CAgentPropPageProvider()
    {
    }

    // DECLARE_REGISTRY_RESOURCEID(IDR_AGENTPROPPAGEPROVIDER)
    static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

BEGIN_COM_MAP(CAgentPropPageProvider)
    COM_INTERFACE_ENTRY(IAgentPropPageProvider)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
END_COM_MAP()

// IAgentPropPageProvider
public:

// ISpecifyPropertyPages
public:
    STDMETHODIMP GetPages(CAUUID *);
};

