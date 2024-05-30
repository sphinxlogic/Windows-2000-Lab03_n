//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       CALLNTFY.H
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


#if !defined(AFX_CALLNOTIFY_H__21170B81_2878_11D1_A79A_00A024AB19AE__INCLUDED_)
#define AFX_CALLNOTIFY_H__21170B81_2878_11D1_A79A_00A024AB19AE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//****************************************************************************
//
// CLASS CCallNotify
//
//****************************************************************************

class CCallNotify : 
	public INmCallNotify, 
	public RefCount, 
	public CNotify 
{
private:
	Conf *m_pConf; // Back pointer to Conf object
	CCallNotify(); // prevent default construction
public:
	CCallNotify(Conf *);
	virtual ~CCallNotify();
	
	// from IUnknown
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);

	// Sink connection methods
	HRESULT Connect(IUnknown *pUnkOuter);
	HRESULT Disconnect(void);
	
	// Main sink notification methods
	HRESULT STDMETHODCALLTYPE StateChanged( NM_CALL_STATE uState);
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE Failed(ULONG uError);
	HRESULT STDMETHODCALLTYPE Accepted(INmConference *pConference);
};

#endif // !defined(AFX_CALLNOTIFY_H__21170B81_2878_11D1_A79A_00A024AB19AE__INCLUDED_)
