//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       CONF.H
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


#if !defined(AFX_CONF_H__688DCF62_255F_11D1_A79A_00A024AB19AE__INCLUDED_)
#define AFX_CONF_H__688DCF62_255F_11D1_A79A_00A024AB19AE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define WM_CONNECTING	WM_USER + 1
#define WM_CONNECTED	WM_USER + 2
#define WM_DISCONNECTED WM_USER +3


//****************************************************************************
//
// CLASS Conf
//
//****************************************************************************

class Conf  
{
private:
	CMgrNotify * m_pMgrNotify;
	CCallNotify * m_pCallNotify;
	CConfNotify *m_pConfNotify;
	INmConference * m_pINmConf;
	INmManager * m_pINmMgr;
	INmCall *m_pINmCall;
	HWND m_hWnd;
	BOOL m_bInConnection;

public:
	Conf(HWND);
	virtual ~Conf();

	HRESULT Initialize(void);
	HRESULT Uninitialize(void);
	HRESULT Call(LPSTR);
	HRESULT CallCreated(INmCall *pCall);
	HRESULT ConferenceCreated(INmConference *);
	HRESULT CallRejected();
	HRESULT CallAccepted();
	HRESULT HangUp();
	HRESULT RemoteHungup();
	HRESULT RejectCall();
	HRESULT AcceptCall();
	BOOL InConnection();
};

#endif // !defined(AFX_CONF_H__688DCF62_255F_11D1_A79A_00A024AB19AE__INCLUDED_)
