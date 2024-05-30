//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CCALL.CPP
//  Content:    INmCall Routines
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"

COBLIST * g_pListCall = (COBLIST *) NULL;
COBLIST * g_pListCallNotify = (COBLIST *) NULL;


//****************************************************************************
//
// INmCall * GetCurrentCall(void)
//
//****************************************************************************

INmCall * GetCurrentCall(void)
{
	if (NULL == g_pListCall)
		return NULL;

	return (INmCall *) g_pListCall->GetTail();
}


//****************************************************************************
//
// HRESULT HookCall(INmCall * pCall)
//
// Hook into notification callback for the call
//
//****************************************************************************

HRESULT HookCall(INmCall * pCall)
{
	HRESULT hr;
	CCallNotify * pNotify;

	ASSERT(NULL != pCall);
	pCall->AddRef();
	AddNode(pCall, &g_pListCall);

    // Connect to the conference object
    pNotify = new CCallNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(pCall);
		if (FAILED(hr))
		{
			ERROR_MSG("CConfNotify Failed (%s)", GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG("Call Connection point established successfully");
			AddNode(pNotify, &g_pListCallNotify);
		}
	}

	return hr;
}


//****************************************************************************
//
// VOID FreeCalls(void)
//
//****************************************************************************

VOID FreeCalls(void)
{
	// Release all notify
	if (NULL != g_pListCallNotify)
	{
		while (!g_pListCallNotify->IsEmpty())
		{
			CCallNotify * pNotify = (CCallNotify *) g_pListCallNotify->RemoveHead();
			ASSERT(NULL != pNotify);
			OBJECT_MSG("[%08X] call notify released", pNotify);
			pNotify->Disconnect();
			pNotify->Release();
		}
	}
	
	if (NULL != g_pListCall)
	{
		while (!g_pListCall->IsEmpty())
		{
			INmCall * pCall = (INmCall *) g_pListCall->RemoveHead();
			ASSERT(NULL != pCall);
			OBJECT_MSG("[%08X] call released", pCall);
			pCall->Release();
		}
	}
}


//****************************************************************************
//
// CLASS CCallNotify
//
//****************************************************************************

CCallNotify::CCallNotify() : RefCount(), CNotify()
{
	OBJECT_MSG("CCallNotify created");
}

CCallNotify::~CCallNotify()
{
	OBJECT_MSG("CCallNotify destroyed");
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CCallNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CCallNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CCallNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	HRESULT hr = S_OK;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG("CCallNotify::QueryInterface(): Returning IUnknown.");
	}
	else if (riid == IID_INmCallNotify)
	{
		*ppvObject = (INmCallNotify *)this;
		OBJECT_MSG("CCallNotify::QueryInterface(): Returning INmCallNotify.");
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG("CCallNotify::QueryInterface(): Called on unknown interface.");
	}

	if (S_OK == hr)
	{
		AddRef();
	}

	return hr;
}



//****************************************************************************
//
// Methods from ICNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmCallNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CCallNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::StateChanged(NM_CALL_STATE uState)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::StateChanged(NM_CALL_STATE uState)
{
	NOTIFY_MSG("CCallNotify::StateChanged uState=%s", GetCallStateSz(uState));
	DumpCallInfo((INmCall *) CNotify::GetPunk());
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::Failed(ULONG uError)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Failed(ULONG uError)
{
	LOG_MSG(RGB(255, 0, 0), "CCallNotify::Failed uError=%08X", uError);
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::Accepted(INmConference * pConference)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Accepted(INmConference * pConference)
{
	NOTIFY_MSG("CCallNotify::Accepted");
	DumpConferenceInfo(pConference);
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::NmUI(CONFN uNotify)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::NmUI(CONFN uNotify)
{
	LOG_MSG(RGB(255, 0, 255), "CCallNotify::NmUI uNotify=%s", GetConfnSz(uNotify));
	return S_OK;
}


//****************************************************************************
//
// VOID DoCallConference(void)
//
//****************************************************************************

VOID DoCallConference(void)
{
	HRESULT hr;
	BSTRING bstrAddr(gPref.pszAddr);
	BSTRING bstrConference(gPref.pszConferenceName);
	BSTRING bstrPassword(gPref.pszPassword);
	INmCall * pCall;
	INmConference * pConference;

	// Validate system
	if (NULL == g_pMgr)
	{
		ERROR_MSG("No conference manager object");
		return;
	}

	pConference = GetCurrentConference();
	if (NULL != pConference)
	{
		WARN_MSG("can't join conferences!");
	}

	hr = g_pMgr->CallConference(&pCall, gPref.nmCallType, gPref.nmAddrType,
		bstrAddr, bstrConference, bstrPassword);

	if (FAILED(hr))
	{
		ERROR_MSG("CallConference failed HResult=%s", GetHrSz(hr));
	}
	else
	{
		ASSERT(pCall == GetCurrentCall());
		pCall->Release();
		TRACE_MSG("CallConference succeeded");
	}
}


//****************************************************************************
//
// VOID DoCallCreate(void)
//
//****************************************************************************

VOID DoCallCreate(void)
{
	HRESULT hr;
	BSTRING bstrAddr(gPref.pszAddr);
	INmCall * pCall;
	INmConference * pConference;

	// Validate system
	if (NULL == g_pMgr)
	{
		ERROR_MSG("No conference manager object");
		return;
	}

	pConference = GetCurrentConference();
	if (NULL == pConference)
	{
		TRACE_MSG("using no conference");
	}

	hr = g_pMgr->CreateCall(&pCall, gPref.nmCallType, gPref.nmAddrType, bstrAddr, pConference);
	if (FAILED(hr))
	{
		ERROR_MSG("CreateCall failed HResult=%s", GetHrSz(hr));
	}
	else
	{
		ASSERT(pCall == GetCurrentCall());
		pCall->Release();
		TRACE_MSG("CreateCall succeeded");
	}
}


//****************************************************************************
//
// VOID DoHandleCall(BOOL fAccept)
//
//****************************************************************************

VOID DoHandleCall(BOOL fAccept)
{
	HRESULT hr;
	INmCall * pCall = GetCurrentCall();

	if (NULL == pCall)
	{
		TRACE_MSG("No call to handle?");
		return;
	}

	if (fAccept)
	{
		hr = pCall->Accept();
	}
	else
	{
		hr = pCall->Reject();
	}

	TRACE_MSG("Call result = %s", GetHrSz(hr));
}


//****************************************************************************
//
// VOID DoCancelCall(void)
//
//****************************************************************************

VOID DoCancelCall(void)
{
	HRESULT hr;
	INmCall * pCall = GetCurrentCall();

	if (NULL == pCall)
	{
		TRACE_MSG("No call to destroy?");
		return;
	}

	hr = pCall->Cancel();
	TRACE_MSG("Call Cancel result = %s", GetHrSz(hr));

	// Free just the single call - watch the notify proc
	FreeCalls();
}

