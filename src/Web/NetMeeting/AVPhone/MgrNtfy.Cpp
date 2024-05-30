//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       MGRNTFY.CPP
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
// CLASS CMgrNotify
//
//****************************************************************************

//****************************************************************************
//
// Construction/Destruction
//
//****************************************************************************

CMgrNotify::CMgrNotify()
{

}

CMgrNotify::CMgrNotify(Conf * pConf)
{
	m_pConf = pConf;
}

CMgrNotify::~CMgrNotify()
{

}

//****************************************************************************
//
// Methods from IUknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CMgrNotify::AddRef()
{
	return RefCount::AddRef();
}

ULONG STDMETHODCALLTYPE CMgrNotify::Release()
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CMgrNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
{
	*ppvObject = NULL;
	
	if (riid == IID_IUnknown)
		*ppvObject = (PVOID *)this;
	else if (riid == IID_INmManagerNotify)
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

HRESULT CMgrNotify::Connect(IUnknown * pUnkOuter)
{
	return CNotify::Connect(pUnkOuter, IID_INmManagerNotify, (IUnknown *)this);
}

HRESULT CMgrNotify::Disconnect()
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Main sink notification methods
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::CallCreated(INmCall * pCall)
{
	// Notify my Conf object that a Call object was created
	m_pConf->CallCreated(pCall);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMgrNotify::ConferenceCreated(INmConference * pConference)
{
	// Notify my Conf object that a Conference object was created
	m_pConf->ConferenceCreated(pConference); 
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMgrNotify::NmUI(CONFN uNotify)
{
	return S_OK;
}

