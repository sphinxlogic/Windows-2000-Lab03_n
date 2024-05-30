//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       MGRNTFY.H
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#if !defined(AFX_MGRNOTIFY_H__84DE9DA3_26AB_11D1_A79A_00A024AB19AE__INCLUDED_)
#define AFX_MGRNOTIFY_H__84DE9DA3_26AB_11D1_A79A_00A024AB19AE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Conf; // forward declaration


//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

class CMgrNotify : 
	public INmManagerNotify, 
	public RefCount, 
	public CNotify  
{
private:
	CMgrNotify();	// Prevent default construction
	Conf *m_pConf;	// Back pointer to Conf object

public:
	CMgrNotify(Conf *);
	virtual ~CMgrNotify();

	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);

	HRESULT Connect(IUnknown *pUnkOuter);
	HRESULT Disconnect(void);

	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE ConferenceCreated(INmConference *pConference);
	HRESULT STDMETHODCALLTYPE CallCreated(INmCall *pCall);
};

#endif // !defined(AFX_MGRNOTIFY_H__84DE9DA3_26AB_11D1_A79A_00A024AB19AE__INCLUDED_)
