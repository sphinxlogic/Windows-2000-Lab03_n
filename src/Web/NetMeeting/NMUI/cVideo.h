//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CVIDEO.H
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


typedef VOID (* PFNSTATECHANGE)(NM_VIDEO_STATE, DWORD);
typedef VOID (* PFNPROPERTYCHANGE)(DWORD, DWORD);

class CVideoNotify : public RefCount, public CNotify, public INmChannelVideoNotify
{
private:
    PFNSTATECHANGE m_pfnStateChange;
    PFNPROPERTYCHANGE m_pfnPropertyChange;
    DWORD m_dwParam;

public:
	CVideoNotify(PFNSTATECHANGE pfnStateChange, PFNPROPERTYCHANGE pfnPropertyChange, DWORD dwParam);
	~CVideoNotify();

	// INmChannelVideoNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember);
    HRESULT STDMETHODCALLTYPE StateChanged(NM_VIDEO_STATE uState);
    HRESULT STDMETHODCALLTYPE PropertyChanged(DWORD dwReserved);

	// ICNotify methods
	HRESULT STDMETHODCALLTYPE Connect (IUnknown *pUnk);
	HRESULT STDMETHODCALLTYPE Disconnect(void);

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObj);
};

// Global Routines
HRESULT HookVideo(INmChannel * pChannel, CVideoNotify * pNotify);
VOID UnhookVideo(CVideoNotify * pNotify);
