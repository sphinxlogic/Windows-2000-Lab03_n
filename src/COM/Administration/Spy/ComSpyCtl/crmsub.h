/*+==========================================================================
File:	   CRMsub.h
Summary:   Declaration of CCRMSub class
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

#ifndef __CRMSUB_H__
#define __CRMSUB_H__

#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

class CComSpy;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:   CCRMSub
Summary: CRM Event Subscriber
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class ATL_NO_VTABLE CCRMSub : 
	public CSysLCESub,
	public IComCRMEvents
{
public:

	CCRMSub(CComSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CCRMSub()
	{
		m_pSpy = NULL;
	}

DECLARE_NOT_AGGREGATABLE(CCRMSub)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCRMSub)
	COM_INTERFACE_ENTRY(IComCRMEvents)
	COM_INTERFACE_ENTRY_CHAIN(CSysLCESub)
END_COM_MAP()

STDMETHODIMP GetEventType(EventEnum * e){*e = CRM;return S_OK;}
STDMETHODIMP GetEventClass(LPGUID guid){*guid = CLSID_ComServiceEvents;return S_OK;}
STDMETHODIMP GetInterface(IID* iid){*iid = IID_IComCRMEvents;return S_OK;}


///// IComCRMEvents


	STDMETHOD(OnCRMRecoveryStart)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidApp);

	STDMETHOD(OnCRMRecoveryDone)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidApp);

	STDMETHOD(OnCRMCheckpoint)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidApp);

	STDMETHOD(OnCRMBegin)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID,
				GUID guidActivity,
				GUID guidTx,
				WCHAR szProgIdCompensator[64],			// NOTE: hardcoded
				WCHAR szDescription[64]);				// NOTE: hardcoded

	STDMETHOD(OnCRMPrepare)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMCommit)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMAbort)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMIndoubt)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMDone)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMRelease)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMAnalyze)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID,
				DWORD dwCrmRecordType,
				DWORD dwRecordSize);

	STDMETHOD(OnCRMWrite)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID,
				BOOL bVariants,
				DWORD dwRecordSize);

	STDMETHOD(OnCRMForget)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMForce)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID);

	STDMETHOD(OnCRMDeliver)(
				COMSVCSEVENTINFO * pInfo,
				GUID guidClerkCLSID,
				BOOL bVariants,
				DWORD dwRecordSize);

};
#endif //__CRMSUB_H__


