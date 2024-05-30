//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       CNFNTFY.H
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


#if !defined(AFX_CONFNOTIFY_H__C19C97C1_2A15_11D1_A79A_00A024AB19AE__INCLUDED_)
#define AFX_CONFNOTIFY_H__C19C97C1_2A15_11D1_A79A_00A024AB19AE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class Conf; // forward declaration


//****************************************************************************
//
// CLASS CConfNotify
//
//****************************************************************************

class CConfNotify : 
	public INmConferenceNotify, 
	public RefCount, 
	public CNotify
{
private:
	CConfNotify();  // Prevents default construction.
	Conf *m_pConf;	// Back pointer to Conf object
public:
	CConfNotify(Conf *);
	virtual ~CConfNotify();

	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);
	
	HRESULT Connect(IUnknown *pUnkOuter);
	HRESULT Disconnect(void);

	HRESULT STDMETHODCALLTYPE StateChanged(NM_CONFERENCE_STATE uState);
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember);
	HRESULT STDMETHODCALLTYPE ChannelChanged(NM_CHANNEL_NOTIFY uNotify,INmChannel *pChannel);

};

#endif // !defined(AFX_CONFNOTIFY_H__C19C97C1_2A15_11D1_A79A_00A024AB19AE__INCLUDED_)
