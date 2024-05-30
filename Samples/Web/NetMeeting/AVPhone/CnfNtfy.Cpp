//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       CNFNTFY.CPP
//  Content:    
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
// CLASS CConfNotify
//
//****************************************************************************


//****************************************************************************
//
// Construction/Destruction
//
//****************************************************************************

CConfNotify::CConfNotify()
{

}

CConfNotify::CConfNotify(Conf *pConf)
{
	m_pConf = pConf;
}

CConfNotify::~CConfNotify()
{

}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

//****************************************************************************
//
// ULONG STDMETHODCALLTYPE CConfNotify::AddRef()
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CConfNotify::AddRef()
{
	return RefCount::AddRef();
}


//****************************************************************************
//
// ULONG STDMETHODCALLTYPE CConfNotify::Release()
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CConfNotify::Release()
{
	return RefCount::Release();
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
{
	*ppvObject = NULL;
	
	if (riid == IID_IUnknown)
		*ppvObject = (PVOID *)this;
	else if (riid == IID_INmConferenceNotify)
		*ppvObject = (PVOID *)this;
	else
		return E_NOINTERFACE;

	AddRef();
	return S_OK;
}


//****************************************************************************
//
// Sink connection methods
//
//****************************************************************************

//****************************************************************************
//
// HRESULT CConfNotify::Connect(IUnknown * pUnkOuter)
//
// Connects to container
//
//****************************************************************************

HRESULT CConfNotify::Connect(IUnknown * pUnkOuter)
{
	return CNotify::Connect(pUnkOuter, IID_INmConferenceNotify, (IUnknown *)this);
}

HRESULT CConfNotify::Disconnect()
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Main sink notification methods
//
//****************************************************************************


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel * pChannel)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel * pChannel)
{
	INmChannelVideo *pVidChannel;
	ULONG uCh;
	IID iid;
	HRESULT hr;

	pChannel->AddRef();


	// When notified that a video channel has been added, display the video window.

	if (uNotify == NM_CHANNEL_ADDED)
		{
			pChannel->GetNmch(&uCh);
			if (uCh==NMCH_VIDEO)
			{
				pChannel->GetInterface(&iid);
				hr = pChannel->QueryInterface(iid,(void **)&pVidChannel);

				if (SUCCEEDED(hr))
				{
					pVidChannel->SetProperty(NM_VIDPROP_IMAGE_PREFERRED_SIZE,NM_VIDEO_SMALL);
					pVidChannel->SetProperty(NM_VIDPROP_WINDOW_AUTO_SIZE,100);
					pVidChannel->SetProperty(NM_VIDPROP_WINDOW_TOP_MOST,1);
					pVidChannel->SetProperty(NM_VIDPROP_WINDOW_VISIBLE,1);
					
					// if video channel is incoming, be sure to not pause by default
					if (pVidChannel->IsIncoming()==S_OK)
						pVidChannel->SetProperty(NM_VIDPROP_PAUSE,0);

					pVidChannel->Release();
				}
			}
		}

	pChannel->Release();

	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember)
//
// This function gets called when a member as changed
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember)
{
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
{
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
{
	// Notify my Conf object that the remote hungup.
	if (uState==NM_CONFERENCE_IDLE)
		m_pConf->RemoteHungup();

	return S_OK;
}
