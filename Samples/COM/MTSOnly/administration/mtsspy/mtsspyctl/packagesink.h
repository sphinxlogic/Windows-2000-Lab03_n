
/******************************************************************************\
********************************************************************************
* Filename: PackageSink.h
*
* Description:  Sink for package events
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


// PackageSink.h : Declaration of the CPackageSink

#ifndef __PACKAGE_H__
#define __PACKAGE_H__

#include "stdafx.h"
#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

class CMtsSpy;

/////////////////////////////////////////////////////////////////////////////
// CPackageSink 
class ATL_NO_VTABLE CPackageSink : 
	public CMtsSink,
	public IMtsPackageEvents
{
private:
	BOOL m_bShowPackageEvents;

public:
	CPackageSink()
	{
		m_pSpy = NULL;
	}
	CPackageSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	void SetShowEvent(BOOL bShow)
	{
		m_bShowPackageEvents = bShow;
	}

	BOOL GetShowEvent()
	{
		return m_bShowPackageEvents;
	}

DECLARE_NOT_AGGREGATABLE(CPackageSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CPackageSink)
	COM_INTERFACE_ENTRY(IMtsPackageEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()



virtual REFIID GetIID(){return IID_IMtsPackageEvents;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = Package;return S_OK;}

//
//  we can never get this event as currently implemented in mtsevents.dll
//	because the runtime using this event to start the event infrastructure,
//	so no sink can be established until _after_ this event is fired.
//
STDMETHODIMP OnPackageActivation(LONGLONG perfCount, REFGUID guidPackage, LPCOLESTR sPackageName)
{
    return S_OK;
}

//
//	when the package shuts down, all of the sinks must be shut down as well
//
STDMETHODIMP OnPackageShutdown(LONGLONG perfCount, REFGUID guidPackage, LPCOLESTR sPackageName)
{
	if (m_bShowPackageEvents)
	{
		if (m_pSpy)
		{
            CComBSTR sGuidPackage = GuidToBstr(guidPackage);
			m_pSpy -> AddEventToList(perfCount, _TEXT("OnPackageShutdown"), m_sPackageName);	
			m_pSpy -> AddParamValueToList(L"guidPackage", sGuidPackage);
		}
	}



	_ASSERTE(m_pSpy);
	if (m_pSpy)
	{ 
		CComBSTR sGuidPackage = GuidToBstr(guidPackage);
		IF_AUDIT_DO(OnPackageShutdown)(perfCount, sGuidPackage, sPackageName);
		m_pSpy -> ShutdownPackage(sPackageName);
	}
	return S_OK;
}
};

#endif //__PACKAGE_H__
