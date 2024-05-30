//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CLISTENER.CPP
//
//-----------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
// Includes
//												   
//////////////////////////////////////////////////////////////////////////////
#include "Headers.h"


//////////////////////////////////////////////////////////////////
// CListener
//
//////////////////////////////////////////////////////////////////
CListener::CListener()
{
	m_cRef = 1;
	m_hrReturn = S_OK;
}

//////////////////////////////////////////////////////////////////
// ~CListener
//
//////////////////////////////////////////////////////////////////
CListener::~CListener() 
{
}

//////////////////////////////////////////////////////////////////
// CListener::SetReturnValue
//
//////////////////////////////////////////////////////////////////
HRESULT CListener::SetReturnValue(HRESULT hrReturn)
{
	m_hrReturn = hrReturn;
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// CListener::GetReturnValue
//
//////////////////////////////////////////////////////////////////
HRESULT CListener::GetReturnValue()
{
	return m_hrReturn;
}

//////////////////////////////////////////////////////////////////
// CListener::Advise
//
//////////////////////////////////////////////////////////////////
HRESULT CListener::Advise(CContainerBase* pCPoint, REFIID riid, DWORD* pdwCookie)
{
	HRESULT hr = S_OK;
	ASSERT(pCPoint);
	IConnectionPoint* pICP = NULL;

	if(pCPoint->m_pIConnectionPointContainer)
	{
		//Obtain the connection point 
		hr = pCPoint->FindConnectionPoint(riid, &pICP);
		if(SUCCEEDED(hr))
		{
			//Delegate
			TESTC(hr = Advise(pICP, pdwCookie));
		}
	}

CLEANUP:
	TRACE_RELEASE(pICP,	L"IConnectionPoint");
	return hr;
}


//////////////////////////////////////////////////////////////////
// CListener::Advise
//
//////////////////////////////////////////////////////////////////
HRESULT CListener::Advise(IConnectionPoint* pIConnectionPoint, DWORD* pdwCookie)
{
	HRESULT hr = S_OK;

	if(pIConnectionPoint)
	{
		//Now we can advise the connection
		//TODO64: Note COM has not changed the Advise output cookie, so we still display it as 0x%08x instead of 0x%p
		XTEST(hr = pIConnectionPoint->Advise((IRowsetNotify*)this, pdwCookie));
		TESTC(TRACE_METHOD(hr, L"IConnectionPoint::Advise(0x%p, &0x%08x)", this, pdwCookie ? *pdwCookie : 0));
	}

CLEANUP:
	return hr;
}


//////////////////////////////////////////////////////////////////
// CListener::Unadvise
//
//////////////////////////////////////////////////////////////////
HRESULT CListener::Unadvise(CContainerBase* pCCPointBase, REFIID riid, DWORD* pdwCookie)
{
	HRESULT hr = S_OK;
	ASSERT(pCCPointBase);
	ASSERT(pdwCookie);
	IConnectionPoint* pICP = NULL;

	if(*pdwCookie && pCCPointBase->m_pIConnectionPointContainer)
	{
		//Obtain the connection point 
		hr = pCCPointBase->FindConnectionPoint(riid, &pICP);
		if(SUCCEEDED(hr))
		{
			//Delegate
			TESTC(hr = Unadvise(pICP, pdwCookie));
		}
	}

CLEANUP:
	TRACE_RELEASE(pICP,	L"IConnectionPoint");
	return hr;
}


//////////////////////////////////////////////////////////////////
// CListener::Unadvise
//
//////////////////////////////////////////////////////////////////
HRESULT CListener::Unadvise(IConnectionPoint* pIConnectionPoint, DWORD* pdwCookie)
{
	HRESULT hr = S_OK;
	ASSERT(pdwCookie);

	if(pIConnectionPoint)
	{
		//Now we can Unadvise the connection
		XTEST(hr = pIConnectionPoint->Unadvise(*pdwCookie));
		TESTC(TRACE_METHOD(hr, L"IConnectionPoint::Unadvise(0x%08x)", *pdwCookie));
		*pdwCookie = 0;
	}

CLEANUP:
	return hr;
}


//////////////////////////////////////////////////////////////////
// CListener::AddRef
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG)	CListener::AddRef()
{
	return ++m_cRef;
}

//////////////////////////////////////////////////////////////////
// CListener::Release
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG)	CListener::Release()
{
	ASSERT(m_cRef);
	if(--m_cRef)
		return m_cRef;
	
	delete this;
	return 0;
}

//////////////////////////////////////////////////////////////////
// CListener::QueryInterface
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::QueryInterface(REFIID riid, LPVOID* ppv)
{
	if(!ppv)
		return E_INVALIDARG;
	*ppv = NULL;

	if(riid == IID_IUnknown)
		*ppv = (IUnknown*)(IRowsetNotify*)this;
	else if(riid == IID_IRowsetNotify)
		*ppv = (IRowsetNotify*)this;
	else if(riid == IID_IDBAsynchNotify)
		*ppv = (IDBAsynchNotify*)this;
	else if(riid == IID_IRowPositionChange)
		*ppv = (IRowPositionChange*)this;
#ifdef INTERNAL_ONLY
	else if(riid == IID_IDBTraceNotify)
		*ppv = (IDBTraceNotify*)this;
	else if(riid == IID_IPoolNotify)
		*ppv = (IPoolNotify*)this;
#endif //INTERNAL_ONLY
	
	if(*ppv)
	{
		((IUnknown*)*ppv)->AddRef();
		return S_OK;
	}	
	else
	{
		return E_NOINTERFACE;
	}

}


//////////////////////////////////////////////////////////////////
// CListener::OnFieldChange
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnFieldChange
( 
    /* [in] */ IRowset __RPC_FAR* pIRowset,
    /* [in] */ HROW hRow,
    /* [in] */ DBORDINAL cColumns,
    /* [size_is][in] */ DBORDINAL __RPC_FAR rgColumns[  ],
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny
)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IROWSETNOTIFY, m_hrReturn, L"IRowsetNotify", L"OnFieldChange", L"(%s, %s, 0x%p, 0x%p, %lu, 0x%p, %s)", GetReasonName(eReason), GetPhaseName(ePhase), pIRowset, hRow, cColumns, rgColumns, fCantDeny ? L"TRUE" : L"FALSE");
}
        
//////////////////////////////////////////////////////////////////
// CListener::OnRowChange
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnRowChange
( 
    /* [in] */ IRowset __RPC_FAR* pIRowset,
    /* [in] */ DBCOUNTITEM cRows,
    /* [size_is][in] */ const HROW __RPC_FAR rghRows[  ],
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny
)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IROWSETNOTIFY, m_hrReturn, L"IRowsetNotify", L"OnRowChange", L"(%s, %s, 0x%p, %lu, 0x%p, %s)", GetReasonName(eReason), GetPhaseName(ePhase), pIRowset, cRows, rghRows, fCantDeny ? L"TRUE" : L"FALSE");
}
        
//////////////////////////////////////////////////////////////////
// CListener::OnRowsetChange
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnRowsetChange
( 
    /* [in] */ IRowset __RPC_FAR* pIRowset,
    /* [in] */ DBREASON eReason,
    /* [in] */ DBEVENTPHASE ePhase,
    /* [in] */ BOOL fCantDeny)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IROWSETNOTIFY, m_hrReturn, L"IRowsetNotify", L"OnRowsetChange", L"(%s, %s, 0x%p, %s)", GetReasonName(eReason), GetPhaseName(ePhase), pIRowset, fCantDeny ? L"TRUE" : L"FALSE");
}


//////////////////////////////////////////////////////////////////
// CListener::OnLowResource
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnLowResource
(
	DB_DWRESERVE dwReserved
)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IDBASYNCHNOTIFY, m_hrReturn, L"IDBAsynchNotify", L"OnLowResource", L"(0x%p)", dwReserved);
}
        
//////////////////////////////////////////////////////////////////
// CListener::OnProgress
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnProgress
		( 
            HCHAPTER		hChapter,
            DBASYNCHOP		eOperation,
            DBCOUNTITEM		ulProgress,
            DBCOUNTITEM		ulProgressMax,
            DBASYNCHPHASE	eAsynchPhase,
            LPOLESTR		pwszStatusText
		)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IDBASYNCHNOTIFY, m_hrReturn, L"IDBAsynchNotify", L"OnProgress", L"(0x%p, %s, %lu, %lu, %s, %s)", hChapter, GetAsynchReason(eOperation), ulProgress, ulProgressMax, GetAsynchPhase(eAsynchPhase), pwszStatusText);
}
        
//////////////////////////////////////////////////////////////////
// CListener::OnStop
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnStop
		( 
            HCHAPTER hChapter,
            ULONG    ulOperation,
           	HRESULT  hrStatus,
            LPOLESTR pwszStatusText
		)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IDBASYNCHNOTIFY, m_hrReturn, L"IDBAsynchNotify", L"OnStop", L"(0x%p, %s, %S, %s)", hChapter, GetAsynchReason(ulOperation), GetErrorName(hrStatus), pwszStatusText);
}


//////////////////////////////////////////////////////////////////
// CListener::OnRowPositionChange
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnRowPositionChange(
		DBREASON		eReason,
		DBEVENTPHASE	ePhase,
		BOOL			fCantDeny)
{
	//Output Notification
	return TRACE_NOTIFICATION(NOTIFY_IROWPOSITIONCHANGE, m_hrReturn, L"IRowPositionChange", L"OnRowPositionChange", L"(%s, %s, %s)", GetReasonName(eReason), GetPhaseName(ePhase), fCantDeny ? L"TRUE" : L"FALSE");
}


#ifdef INTERNAL_ONLY
//////////////////////////////////////////////////////////////////
// CListener::OnPackageReady
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::OnPackageReady
(
	DBLENGTH cbPackageDataLen, 
	BYTE* pPackageData
)
{
	//Output Notification
	return CTrace::TraceReceiver(cbPackageDataLen, pPackageData);
}


//////////////////////////////////////////////////////////////////
// CListener::SendNotification
//
//////////////////////////////////////////////////////////////////
STDMETHODIMP CListener::SendNotification
(
		IPoolInfo*			pPoolInfo,
		SPNOTIFICATION_TYPE	eType
)
{
	const static WIDENAMEMAP rgNotifyTypes[] = 
	{
		VALUE_WCHAR(EID_CREATERES),
		VALUE_WCHAR(EID_RELEASERES),
		VALUE_WCHAR(EID_DESTROYRES),
		VALUE_WCHAR(EID_ENLISTRES),
		VALUE_WCHAR(EID_RESETRES),
		VALUE_WCHAR(EID_RATERES),
		VALUE_WCHAR(EID_DRAWRES),
	};

	//Output Notification
	HRESULT hr = TRACE_NOTIFICATION(NOTIFY_IPOOLNOTIFY, m_hrReturn, L"IPoolNotify", L"SendNotification", L"(%p, %s)", pPoolInfo, GetBitMapName(eType, NUMELE(rgNotifyTypes), rgNotifyTypes));

	switch(eType)
	{
		case EID_CREATERES:
		case EID_RELEASERES:
		case EID_DESTROYRES:
		case EID_DRAWRES:
		{
			//We should refresh the pools display, since something has changed since last time...
			CMainWindow* pCMainWindow = (CMainWindow*)CAppLite::m_pCMainWindow;
			if(pCMainWindow && pCMainWindow->m_pCServiceComp)
				pCMainWindow->m_pCServiceComp->RefreshPools();
			break;
		}
	};

	return hr;
}
#endif //INTERNAL_ONLY
