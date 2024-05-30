//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCHAT.CPP
//  Content:    INmChannel Routines
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

COBLIST * g_pListChannel = (COBLIST *) NULL;
COBLIST * g_pListChannelNotify = (COBLIST *) NULL;

INmFt * g_pFt = NULL;
INmChannelAppShare * g_pChannelShare = NULL;


//****************************************************************************
//
// HRESULT HookChannel(INmChannel * pChannel)
//
// Hook into notification callback for the channel
// 
//****************************************************************************

HRESULT HookChannel(INmChannel * pChannel)
{
	HRESULT hr;
	CChannelNotify * pNotify;

	ULONG uch;
	pChannel->GetNmch(&uch);
	TRACE_MSG("[%08X] - Channel=[%s] Added", pChannel, GetNmchSz(uch));

	ASSERT(NULL != pChannel);
	pChannel->AddRef();
	AddNode(pChannel, &g_pListChannel);

    pNotify = new CChannelNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(pChannel);
		if (FAILED(hr))
		{
			WARN_MSG("CConfNotify Failed (%s)", GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG("Conference Connection point established successfully");
			AddNode(pNotify, &g_pListChannelNotify);
		}
	}

	if (SUCCEEDED(hr))
	{
		ULONG uch;
		if (SUCCEEDED(pChannel->GetNmch(&uch)))
		{
			switch (uch)
				{
			case NMCH_SHARE:
			{
				if (NULL != g_pChannelShare)
				{
					WARN_MSG("Replacing App Sharing Channel");
					g_pChannelShare->Release();
					g_pChannelShare = NULL;
				}
				hr = pChannel->QueryInterface(IID_INmChannelAppShare, (void **)&g_pChannelShare);
				if (FAILED(hr))
				{
					ERROR_MSG("HookData:Unable to get Data Channel");
				}
				break;
			}
			case NMCH_DATA:
				HookData(pChannel);
				break;
			default:
				break;
				}
		}
	}

	return hr;
}


//****************************************************************************
//
// VOID UnHookChannel(INmChannel * pChannel)
//
//****************************************************************************

VOID UnHookChannel(INmChannel * pChannel)
{
	POSITION pos;
	POSITION posSav;
	IUnknown * pUnk = pChannel;

	ULONG uch;
	pChannel->GetNmch(&uch);
	TRACE_MSG("[%08X] - Channel=[%s] Removed", pChannel, GetNmchSz(uch));

	// Search for the notify object responsible for this channel
	ASSERT(NULL != g_pListChannelNotify);
	for (pos = g_pListChannelNotify->GetHeadPosition(); NULL != pos; )
	{
		posSav = pos;
		CChannelNotify * pNotify = (CChannelNotify *) g_pListChannelNotify->GetNext(pos);
		ASSERT(NULL != pNotify);

		if (S_OK == pChannel->IsSameAs((INmChannel *) pNotify->GetPunk()))
		{
			g_pListChannelNotify->RemoveAt(posSav);
			pNotify->Disconnect();
			pNotify->Release();
			break;
		}
	}

	// Search for the channel in the list
	ASSERT(NULL != g_pListChannel);
	for (pos = g_pListChannel->GetHeadPosition(); NULL != pos; )
	{
		posSav = pos;
		if (S_OK == pChannel->IsSameAs((INmChannel *) g_pListChannel->GetNext(pos)))
		{
			g_pListChannel->RemoveAt(posSav);
			pChannel->Release();
			break;
		}
	}
	
	OBJECT_MSG("Channel connection point removed");
}


//****************************************************************************
//
// VOID UpdateChannelState(INmChannel * pChannel)
//
//****************************************************************************

VOID UpdateChannelState(INmChannel * pChannel)
{
	HRESULT hr;
	ULONG nmch;
	BOOL  fActive;
	ULONG cMember;

	hr = pChannel->GetNmch(&nmch);
	if (FAILED(hr))
	{
		return;
	}
	fActive = S_OK == pChannel->IsActive();
	pChannel->GetMemberCount(&cMember);
	TRACE_MSG("%s channel %08X is %s with %d members", GetNmchSz(nmch), pChannel,
		fActive ? TEXT("Active") : TEXT("Inactive"), cMember);

	switch (nmch)
		{
	case NMCH_DATA:
	{
		INmChannelData * pChannelData;
		hr = pChannel->QueryInterface(IID_INmChannelData, (void **)&pChannelData);
		if (FAILED(hr))
			return;
		if (pChannelData != g_pChannelData)
		{
			WARN_MSG("second data channel?");
		}
		SetMenuCheck(IDM_CHANNEL_DATA, fActive);
		pChannelData->Release();
		break;
	}
	case NMCH_AUDIO:
	case NMCH_VIDEO:
		break;
	case NMCH_SHARE:
	{
		if (fActive)
			break;

		if (NULL == g_pChannelShare)
			break;
		g_pChannelShare->Release();
		g_pChannelShare = NULL;
		break;
	}
		break;
	default:
		break;
		}
}


//****************************************************************************
//
// VOID FreeChannels(void)
//
//****************************************************************************

VOID FreeChannels(void)
{
	// Release all notify
	if (NULL != g_pListChannelNotify)
	{
		while (!g_pListChannelNotify->IsEmpty())
		{
			CChannelNotify * pNotify = (CChannelNotify *) g_pListChannelNotify->RemoveHead();
			ASSERT(NULL != pNotify);
			OBJECT_MSG("[%08X] channel notify released", pNotify);
			pNotify->Disconnect();
			pNotify->Release();
		}
	}
	
	if (NULL != g_pListChannel)
	{
		while (!g_pListChannel->IsEmpty())
		{
			INmChannel * pChannel = (INmChannel *) g_pListChannel->RemoveHead();
			ASSERT(NULL != pChannel);
			OBJECT_MSG("[%08X] channel released", pChannel);
			pChannel->Release();
		}
	}
}


//****************************************************************************
//
// CLASS CChannelNotify
//
//****************************************************************************

CChannelNotify::CChannelNotify() : RefCount(), CNotify()
{
	OBJECT_MSG("CChannelNotify created");
}

CChannelNotify::~CChannelNotify()
{
	OBJECT_MSG("CChannelNotify destroyed");
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CChannelNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CChannelNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CChannelNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	HRESULT hr = S_OK;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG("CChannelNotify::QueryInterface(): Returning IUnknown.");
	}
	else if (riid == IID_INmChannelNotify)
	{
		*ppvObject = (INmChannelNotify *)this;
		OBJECT_MSG("CChannelNotify::QueryInterface(): Returning INmChannelNotify.");
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG("CChannelNotify::QueryInterface(): Called on unknown interface.");
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

HRESULT STDMETHODCALLTYPE CChannelNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CChannelNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CChannelNotify::NmUI(CONFN uNotify)
{
	NOTIFY_MSG("CChannelNotify::NmUI uNotify=%08X, pChannel=%08X", uNotify, CNotify::GetPunk());
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CChannelNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	NOTIFY_MSG("CChannelNotify::MemberChanged uNotify=%d pMember=%08X, pChannel=%08X", uNotify, pMember, CNotify::GetPunk());

	PUSER pUser = PUserFromINmMember(pMember);
	if (NULL != pUser)
	{
		UpdateUserChannel(pUser, (INmChannel *) (CNotify::GetPunk()), uNotify);
	}

	return S_OK;
}


//****************************************************************************
//
// VOID SendFile(INmMember * pMember)
//
//****************************************************************************

VOID SendFile(INmMember * pMember)
{
	PUSER pUser = PUserLocal();
	if (NULL == pUser)
	{
		return;
	}

	if (NULL == pUser->m_pChannelFt)
	{
		return;
	}

	INmFt * pFt;
	BSTRING bstrFileName(gPref.pszFileName);
	HRESULT hr = pUser->m_pChannelFt->SendFile(&pFt, pMember, bstrFileName, 0);
	if (SUCCEEDED(hr))
	{
		FreeFt();
		g_pFt = pFt;
	}
}


//****************************************************************************
//
// VOID DoFtCancel(void)
//
//****************************************************************************

VOID DoFtCancel(void)
{
	if (NULL == g_pFt)
		return;

	HRESULT hr = g_pFt->Cancel();
}


//****************************************************************************
//
// VOID FreeFt(void)
//
//****************************************************************************

VOID FreeFt(void)
{
	if (NULL != g_pFt)
	{
		g_pFt->Release();
		g_pFt = NULL;
	}
}


//****************************************************************************
//
// VOID FreeAs(void)
//
//****************************************************************************

VOID FreeAs(void)
{
	if (NULL != g_pChannelShare)
	{
		g_pChannelShare->Release();
		g_pChannelShare = NULL;
	}
}


