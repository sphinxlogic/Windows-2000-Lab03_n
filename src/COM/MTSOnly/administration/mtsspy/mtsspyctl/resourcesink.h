
/******************************************************************************\
********************************************************************************
* Filename: ResourceSink.h
*
* Description: defininition of sink for resource events.
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

#ifndef __RESOURCESINK_H_
#define __RESOURCESINK_H_

#include "resource.h"       // main symbols

class CMtsSpy;

/////////////////////////////////////////////////////////////////////////////
// CResourceSink
class ATL_NO_VTABLE CResourceSink : 
	public CMtsSink, 
	public IMtsResourceEvents

{
public:
	CResourceSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CResourceSink()
	{
		m_pSpy = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RESOURCESINK)
DECLARE_NOT_AGGREGATABLE(CResourceSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CResourceSink)
	COM_INTERFACE_ENTRY(IMtsResourceEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

	virtual REFIID GetIID(){return IID_IMtsResourceEvents;}
// IResourceSink
public:
    STDMETHOD(OnResourceCreate)(LONGLONG perfCount, REFGUID guidActivity, MTS_OBJID ObjectID, LPCOLESTR pszType,MTS_RESID resId);
	STDMETHOD(OnResourceAllocate)(LONGLONG perfCount, REFGUID guidActivity, MTS_OBJID ObjectID, LPCOLESTR pszType,MTS_RESID resId);	
	STDMETHOD(OnResourceRecycle)(LONGLONG perfCount, MTS_OBJID ObjectID, LPCOLESTR pszType,MTS_RESID resId);
	STDMETHOD(OnResourceDestroy)(LONGLONG perfCount, MTS_OBJID ObjectID, LPCOLESTR pszType,MTS_RESID resId);

	STDMETHODIMP GetSinkType(EventEnum * e){*e = Resource;return S_OK;}


};

#endif //__RESOURCESINK_H_
