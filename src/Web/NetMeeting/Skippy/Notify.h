//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       notify.h
//  Content:    This file contains common notification sink objects.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#ifndef __NOTIFY_H__
#define __NOTIFY_H__

// Common notification sink object
//
class CNotify
{
private:
	HWND    hwnd;
	DWORD   dwCookie;

public:
	CNotify (HWND hwnd) {this->hwnd = hwnd; dwCookie = 0xFFFFFFFF; return;}

	void                    SetCookie (DWORD dwCookie)  {this->dwCookie = dwCookie; return;}
	STDMETHODIMP_(DWORD)    GetCookie (void)            {return dwCookie;}
	HWND                    GetWindow(void)             {return hwnd;}
};

//****************************************************************************
// Ils notification sink object
//
//****************************************************************************
class CIlsNotify : public CNotify,
				public IIlsNotify
{
private:
	UINT    cRef;

public:
	CIlsNotify (HWND hwndInit);

	// IUnknown
	STDMETHODIMP            QueryInterface (REFIID iid, void **ppv);
	STDMETHODIMP_(ULONG)    AddRef (void);
	STDMETHODIMP_(ULONG)    Release (void);

	// IIlsNotify
	STDMETHODIMP GetUserResult(ULONG uReqID, IIlsUser *pUser, HRESULT hResult);
	STDMETHODIMP EnumUserNamesResult(ULONG uReqID, IEnumIlsNames *pEnumUserName,
									HRESULT hResult);
	STDMETHODIMP EnumUsersResult(ULONG uReqID, IEnumIlsUsers *pEnumUser,
								HRESULT hResult);
};


//****************************************************************************
// IlsProtocol notification sink object
//
//****************************************************************************
class CIlsProtocolNotify : public CNotify,
							public IIlsProtocolNotify
{
private:
	UINT    cRef;

public:
	CIlsProtocolNotify (HWND hwndInit);

	// IUnknown
	STDMETHODIMP            QueryInterface (REFIID iid, void **ppv);
	STDMETHODIMP_(ULONG)    AddRef (void);
	STDMETHODIMP_(ULONG)    Release (void);

	// IIlsLocalAppProtocolNotify
	STDMETHODIMP UpdateResult(ULONG uReqID, HRESULT hResult);
};

//****************************************************************************
// IlsUser notification sink object
//
//****************************************************************************
class CIlsUserNotify : public CNotify,
					public IIlsUserNotify
{
private:
	UINT    cRef;

public:
	CIlsUserNotify (HWND hwndInit);

	// IUnknown
	STDMETHODIMP            QueryInterface (REFIID iid, void **ppv);
	STDMETHODIMP_(ULONG)    AddRef (void);
	STDMETHODIMP_(ULONG)    Release (void);

	// IIlsUserNotify
	STDMETHODIMP StateChanged(ULONG fPrimary, BSTR bstrServerName);
	STDMETHODIMP RegisterResult(ULONG uReqID, HRESULT hResult);
	STDMETHODIMP UpdateResult(ULONG uReqID, HRESULT hResult);
	STDMETHODIMP ProtocolChangeResult(ULONG uReqID, HRESULT hResult);
	STDMETHODIMP EnumProtocolsResult(ULONG uReqID, IEnumIlsNames *pEnum,
									HRESULT hResult);
	STDMETHODIMP GetProtocolResult(ULONG uReqID, IIlsProtocol *pProtocol,
									HRESULT hResult);
};



#endif //__NOTIFY_H__
