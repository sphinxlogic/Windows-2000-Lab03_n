//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CVIDEO.CPP
//  Content:    Video Channel Routines
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


//****************************************************************************
//
// CLASS CVideoNotify
//
//****************************************************************************

CVideoNotify::CVideoNotify(PFNSTATECHANGE pfnStateChange, PFNPROPERTYCHANGE pfnPropertyChange, DWORD dwParam) : RefCount(), CNotify()
{
	OBJECT_MSG("CVideoNotify created");

	m_pfnStateChange = pfnStateChange;
	m_pfnPropertyChange = pfnPropertyChange;
	m_dwParam = dwParam;
}

CVideoNotify::~CVideoNotify()
{
	OBJECT_MSG("CDataNotify destroyed");
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CVideoNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CVideoNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CVideoNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	HRESULT hr = S_OK;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG("CVideoNotify::QueryInterface(): Returning IUnknown.");
	}
	else if (riid == IID_INmChannelVideoNotify)
	{
		*ppvObject = (INmChannelVideoNotify *)this;
		OBJECT_MSG("CVideoNotify::QueryInterface(): Returning INmChannelVideoNotify.");
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG("CVideoNotify::QueryInterface(): Called on unknown interface.");
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

HRESULT STDMETHODCALLTYPE CVideoNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelVideoNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CVideoNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from INmChannelNotify
//
//****************************************************************************
HRESULT STDMETHODCALLTYPE CVideoNotify::NmUI(CONFN uNotify)
{
	NOTIFY_MSG("CVideoNotify::NmUI uNotify=%08X, pChannel=%08X", uNotify, CNotify::GetPunk());
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CVideoNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	NOTIFY_MSG("CVideoNotify::MemberChanged uNotify=%08X, pMember=%08X, pChannel=%08X", uNotify, pMember, CNotify::GetPunk());

	PUSER pUser = PUserFromINmMember(pMember);
	if (NULL != pUser)
	{
		UpdateUserChannel(pUser, (INmChannel *) (CNotify::GetPunk()), uNotify);
	}

	return S_OK;
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CVideoNotify::StateChanged(NM_VIDEO_STATE uState)
{
	NOTIFY_MSG("CVideoNotify::StateChanged uState=%08X, pChannel=%08X", uState, CNotify::GetPunk());
	if (NULL != m_pfnStateChange)
	{
		m_pfnStateChange(uState, m_dwParam);
	}
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CVideoNotify::PropertyChanged(DWORD dwReserved)
{
	NOTIFY_MSG("CVideoNotify::PropertyChanged dwReserved=%08X, pChannel=%08X", dwReserved, CNotify::GetPunk());
	if (NULL != m_pfnPropertyChange)
	{
		m_pfnPropertyChange(dwReserved, m_dwParam);
	}
	return S_OK;
}



