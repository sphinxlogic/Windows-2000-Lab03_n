/*+==========================================================================
File:	   ObjPool2Sub.h
Summary:   Declaration and implementation of CObjPool2Sub class
----------------------------------------------------------------------------
This file is part of the Microsoft COM+ Samples.

Copyright (C) 1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
==========================================================================+*/

#ifndef __OBJPOOL2SUB_H__
#define __OBJPOOL2SUB_H__

#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

class CComSpy;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:   CObjPool2Sub
Summary: Object Pool2 Events Subscriber 
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class ATL_NO_VTABLE CObjPool2Sub : 
	public CSysLCESub,
	public IComObjectPoolEvents2
{
public:
	CObjPool2Sub(CComSpy * pSpy)
	{
		m_pSpy = pSpy;
	}

	CObjPool2Sub()
	{
		m_pSpy = NULL;
	}

	DECLARE_NOT_AGGREGATABLE(CObjPool2Sub)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CObjPool2Sub)
		COM_INTERFACE_ENTRY(IComObjectPoolEvents2)
		COM_INTERFACE_ENTRY_CHAIN(CSysLCESub)
	END_COM_MAP()

	STDMETHODIMP GetEventType(EventEnum * e){*e = ObjectPool2;return S_OK;}
	STDMETHODIMP GetEventClass(LPGUID guid){*guid = CLSID_ComServiceEvents;return S_OK;}
	STDMETHODIMP GetInterface(IID* iid){*iid = IID_IComObjectPoolEvents2;return S_OK;}

	STDMETHODIMP OnObjPoolCreateObject(COMSVCSEVENTINFO * pInfo,
									   REFGUID guidClass,
									   DWORD dwObjsCreated,
									   ULONG64 ObjectID)
	{

		m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnObjPoolCreateObject"), GuidToBstr(pInfo->guidApp));
		m_pSpy -> AddParamValueToList(L"guidClass", GuidToBstr( guidClass ));

		WCHAR p1[16];
		wsprintfW(p1, L"%lu", dwObjsCreated);
		m_pSpy -> AddParamValueToList(L"dwObjsCreated", p1);

		WCHAR szObjectID[32];
		wsprintfW(szObjectID, L"0x%08X", ObjectID);
		m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

		IF_AUDIT_DO(OnObjPoolCreateObject)(pInfo->perfCount, GuidToBstr(pInfo->guidApp),							
										GuidToBstr( guidClass ),						
										dwObjsCreated,															
										szObjectID);
		return S_OK;
	}


	STDMETHODIMP  OnObjPoolDestroyObject(COMSVCSEVENTINFO * pInfo,
										 REFGUID guidClass,
										 DWORD dwObjsCreated,
										 ULONG64 ObjectID)
	{
		
		m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnObjPoolDestroyObject"), GuidToBstr(pInfo->guidApp));
		m_pSpy -> AddParamValueToList(L"guidClass", GuidToBstr( guidClass ));

		WCHAR p1[16];
		wsprintfW(p1, L"%lu", dwObjsCreated);
		m_pSpy -> AddParamValueToList(L"dwObjsCreated", p1);

		WCHAR szObjectID[32];
		wsprintfW(szObjectID, L"0x%08X", ObjectID);
		m_pSpy -> AddParamValueToList(L"ObjectID", szObjectID);

		IF_AUDIT_DO(OnObjPoolDestroyObject)(pInfo->perfCount, GuidToBstr(pInfo->guidApp),							
										GuidToBstr( guidClass ),						
										dwObjsCreated,															
										szObjectID);

		return S_OK;
	}

	STDMETHODIMP  OnObjPoolCreateDecision(COMSVCSEVENTINFO * pInfo, 
										  DWORD dwThreadsWaiting,
										  DWORD dwAvail,
										  DWORD dwCreated,
										  DWORD dwMin,
										  DWORD dwMax)
	{
		WCHAR p1[16];
		m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnObjPoolCreateDecision"), GuidToBstr(pInfo->guidApp));
		wsprintfW(p1,  L"%lu", dwThreadsWaiting);
		m_pSpy -> AddParamValueToList(L"dwThreadsWaiting", p1);
		wsprintfW(p1,  L"%lu", dwAvail);
		m_pSpy -> AddParamValueToList(L"dwAvail", p1);
		wsprintfW(p1,  L"lu", dwCreated);
		m_pSpy -> AddParamValueToList(L"dwCreated", p1);
		wsprintfW(p1,  L"lu", dwMin);
		m_pSpy -> AddParamValueToList(L"dwMin", p1);
		wsprintfW(p1,  L"lu", dwMax);
		m_pSpy -> AddParamValueToList(L"dwMax", p1);

		IF_AUDIT_DO(OnObjPoolCreateDecision)(pInfo->perfCount, GuidToBstr(pInfo->guidApp),							
										dwThreadsWaiting,
										dwAvail,
										dwCreated,
										dwMin,
										dwMax);
		return S_OK;
	}


	STDMETHODIMP  OnObjPoolTimeout(COMSVCSEVENTINFO * pInfo,
									 REFGUID guidActivity,
									 REFGUID guidClass,
									 DWORD dwTimeout)
	{
		WCHAR p1[16];
		m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnObjPoolGetFromTx"), GuidToBstr(pInfo->guidApp));
		m_pSpy -> AddParamValueToList(L"guidActivity", GuidToBstr( guidActivity ));
		m_pSpy -> AddParamValueToList(L"guidClass", GuidToBstr( guidClass ));
		wsprintfW(p1,L"0x%08X", dwTimeout);
		m_pSpy -> AddParamValueToList(L"dwTimeout", p1);

		IF_AUDIT_DO(OnObjPoolTimeout)(pInfo->perfCount, GuidToBstr(pInfo->guidApp),							
										GuidToBstr( guidActivity ),
										GuidToBstr( guidClass ),
										dwTimeout);
									
		return S_OK;
	}

	STDMETHODIMP  OnObjPoolCreatePool(COMSVCSEVENTINFO * pInfo,
									  REFGUID guidClass,
									  DWORD dwMin,
									  DWORD dwMax,
									  DWORD dwTimeout)
	{
		WCHAR p1[16];
		m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnObjPoolCreatePool"), GuidToBstr(pInfo->guidApp));
		m_pSpy -> AddParamValueToList(L"guidClass", GuidToBstr( guidClass ));
		wsprintfW(p1,  L"0x%08X", dwMin);
		m_pSpy -> AddParamValueToList(L"dwMin", p1);
		wsprintfW(p1,  L"0x%08X", dwMax);
		m_pSpy -> AddParamValueToList(L"dwMax", p1);
		wsprintfW(p1,L"0x%08X", dwTimeout);
		m_pSpy -> AddParamValueToList(L"dwTimeout", p1);

		IF_AUDIT_DO(OnObjPoolCreatePool)(pInfo->perfCount, GuidToBstr(pInfo->guidApp),															
										GuidToBstr( guidClass ),
										dwMin,
										dwMax,
										dwTimeout);
									

		return S_OK;
	}
};

#endif //__OBJPOOL2SUB_H__
