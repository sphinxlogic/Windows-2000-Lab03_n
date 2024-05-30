
// --ExEvHandler.h--------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __EXEVHANDLER_H_
#define __EXEVHANDLER_H_

#include "resource.h"       // main symbols
#include "stdAfx.h"

#include <mapix.h>
#include <mapidbg.h>
#include <mapiutil.h>
#include "emsabtag.h"
#include "edkmdb.h"

#include "suggest.h"
#include "esconf.h"
#include "exchhndl.h"

/////////////////////////////////////////////////////////////////////////////
// CExEvHandler
class ATL_NO_VTABLE CExEvHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExEvHandler, &CLSID_ExEvHandler>,
	public IExchangeEventHandler,
	public IDispatchImpl<IExEvHandler, &IID_IExEvHandler, &LIBID_SUGGESTLib>
{
public:
	CExEvHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXEVHANDLER)

BEGIN_COM_MAP(CExEvHandler)
	COM_INTERFACE_ENTRY(IExchangeEventHandler)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IExEvHandler
public:
	//IExchangeEventHandler
	STDMETHOD(ExecuteEvent)(LPDISPATCH pSource);
	
	// IEventSource Properties
	HRESULT GetSource(LPMESSAGE* ppMessage);
	HRESULT GetSourceID(BSTR* pstrSourceID);
	HRESULT GetMessageID(BSTR* pstrMessageID);
	HRESULT GetSession(LPMAPISESSION* ppSession);
	HRESULT GetEventType(DWORD* pdwEventType);
	HRESULT GetMaxExecutionTime(DWORD* pdwMaxExecutionTime);
	HRESULT PutResponse(char * lpResponse);

	// Event Information
	HRESULT GetAgentProps(LPSPropValue* ppProps);
	HRESULT SetAgentProps(ULONG cValues, LPSPropValue pProps);
	HRESULT GetTriggerMessage(LPSPropValue pProps,LPMESSAGE* ppMessage);

	// Utility Functions
protected:
	IEventSource* m_pEventSource;
	
	HRESULT CExEvHandler::VariantToMAPIObject(VARIANT var, REFIID iid, void** ppObject);
	HRESULT CExEvHandler::AMObjectToMAPIObject(LPDISPATCH pAMObject, REFIID iid, void** ppObject);
	SBinary CExEvHandler::BSTRToBinary(BSTR str);
};

#endif //__EXEVHANDLER_H_
