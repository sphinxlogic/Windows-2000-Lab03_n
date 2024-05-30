//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       notify.cpp
//  Content:    This file contains notification method implentations.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"
#include "notify.h"

//****************************************************************************
// CIlsNotify::CIlsNotify (HWND hwndInit)
//
//****************************************************************************

CIlsNotify::CIlsNotify (HWND hwndInit) :
			CNotify(hwndInit)
{
	cRef = 0;
	return;
}

//****************************************************************************
// STDMETHODIMP
// CIlsNotify::QueryInterface (REFIID riid, void **ppv)
//
//****************************************************************************

STDMETHODIMP
CIlsNotify::QueryInterface (REFIID riid, void **ppv)
{
	if (riid == IID_IIlsNotify || riid == IID_IUnknown)
	{
		*ppv = (IIlsNotify *) this;
		AddRef();
		return S_OK;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	};
}

//****************************************************************************
// STDMETHODIMP_(ULONG)
// CIlsNotify::AddRef (void)
//
//****************************************************************************

STDMETHODIMP_(ULONG)
CIlsNotify::AddRef (void)
{
	return cRef++;
}

//****************************************************************************
// STDMETHODIMP_(ULONG)
// CIlsNotify::Release (void)
//
//****************************************************************************

STDMETHODIMP_(ULONG)
CIlsNotify::Release (void)
{
	cRef--;

	if (cRef == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return cRef;
	};
}


//****************************************************************************
// STDMETHODIMP
// CIlsNotify::GetUserResult(ULONG uReqID, IIlsUser *pUser, HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsNotify::GetUserResult(ULONG uReqID, IIlsUser *pUser,
						HRESULT hResult)
{
	MyTextOut (TEXT("IIlsNotify::GetUserResult(%x) returns %x. [%s]\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	
	if (SUCCEEDED(hResult))
	{
		pUser->AddRef();
		PostMessage(GetWindow(), WM_IT_RESOLVE_USER_RESULT, 0, (LPARAM)pUser);
	};
	return S_OK;
}


//****************************************************************************
// STDMETHODIMP
// CIlsNotify::EnumUserNamesResult(ULONG uReqID, IEnumIlsNames *pEnumUserName,
//                                 HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsNotify::EnumUserNamesResult(ULONG uReqID, IEnumIlsNames *pEnumUserName,
								HRESULT hResult)
{
	MyTextOut (TEXT("IIlsNotify::EnumUserNamesResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	
	if (hResult == NOERROR)
	{
		pEnumUserName->AddRef();
		PostMessage(GetWindow(), WM_IT_ENUM_NAMES_RESULT, 0, (LPARAM)pEnumUserName);
	};
	return S_OK;
}


//****************************************************************************
// STDMETHODIMP
// CIlsNotify::EnumUsersResult(ULONG uReqID, IEnumIlsUsers *pEnumUser,
//                             HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsNotify::EnumUsersResult(ULONG uReqID, IEnumIlsUsers *pEnumUser,
							HRESULT hResult)
{
	MyTextOut (TEXT("IIlsNotify::EnumUsersResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	
	if (hResult == NOERROR)
	{
		pEnumUser->AddRef();
		PostMessage(GetWindow(), WM_IT_ENUM_USERS_RESULT, 0, (LPARAM)pEnumUser);
	};
	return S_OK;
}



//****************************************************************************
// CIlsUserNotify::CIlsUserNotify (HWND hwndInit)
//
//****************************************************************************

CIlsUserNotify::CIlsUserNotify (HWND hwndInit) :
				CNotify(hwndInit)
{
	cRef = 0;
	return;
}

//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::QueryInterface (REFIID riid, void **ppv)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::QueryInterface (REFIID riid, void **ppv)
{
	if (riid == IID_IIlsUserNotify || riid == IID_IUnknown)
	{
		*ppv = (IIlsUserNotify *) this;
		AddRef();
		return S_OK;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	};
}

//****************************************************************************
// STDMETHODIMP_(ULONG)
// CIlsUserNotify::AddRef (void)
//
//****************************************************************************

STDMETHODIMP_(ULONG)
CIlsUserNotify::AddRef (void)
{
	return cRef++;
}

//****************************************************************************
// STDMETHODIMP_(ULONG)
// CIlsUserNotify::Release (void)
//
//****************************************************************************

STDMETHODIMP_(ULONG)
CIlsUserNotify::Release (void)
{
	cRef--;

	if (cRef == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return cRef;
	};
}


//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::StateChanged(ULONG fPrimary, BSTR bstrServerName)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::StateChanged(ULONG fPrimary, BSTR bstrServerName)
{
	MyTextOut (TEXT("IIlsUserNotify::StateChanged returns %x on server %s.\r\n"),
			fPrimary, bstrServerName);
	
	return S_OK;
}



//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::RegisterResult(ULONG uReqID, HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::RegisterResult(ULONG uReqID, HRESULT hResult)
{
	MyTextOut (TEXT("IIlsUserNotify::RegisterResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	return S_OK;
}




//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::UpdateResult(ULONG uReqID, HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::UpdateResult(ULONG uReqID, HRESULT hResult)
{
	MyTextOut (TEXT("IIlsUserNotify::UpdateResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	return S_OK;
}


//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::ProtocolChangeResult(ULONG uReqID, HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::ProtocolChangeResult(ULONG uReqID, HRESULT hResult)
{
	MyTextOut (TEXT("IIlsUserNotify::ProtocolChangeResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	return S_OK;
}



//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::EnumProtocolsResult(ULONG uReqID,
//                                    IEnumIlsNames *pEnumProtocol,
//                                    HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::EnumProtocolsResult(ULONG uReqID,
								IEnumIlsNames *pEnumProtocol,
								HRESULT hResult)
{
	MyTextOut (TEXT("IIlsUserNotify::EnumProtocolsResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	
	if (hResult == NOERROR)
	{
		pEnumProtocol->AddRef();
		PostMessage(GetWindow(), WM_IT_ENUM_NAMES_RESULT, 0, (LPARAM)pEnumProtocol);
	};
	return S_OK;
}

//****************************************************************************
// STDMETHODIMP
// CIlsUserNotify::GetProtocolResult(ULONG uReqID, IIlsProtocol *pProt,
//                                  HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsUserNotify::GetProtocolResult(ULONG uReqID, IIlsProtocol *pProt,
								HRESULT hResult)
{
	MyTextOut (TEXT("IIlsUserNotify::GetProtocolResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	
	if (SUCCEEDED(hResult))
	{
		pProt->AddRef();
		PostMessage(GetWindow(), WM_IT_RESOLVE_PROT_RESULT, 0, (LPARAM)pProt);
	};
	return S_OK;
}






//****************************************************************************
// CIlsProtocolNotify::CIlsProtocolNotify (HWND hwndInit)
//
//****************************************************************************

CIlsProtocolNotify::CIlsProtocolNotify (HWND hwndInit) :
				CNotify(hwndInit)
{
	cRef = 0;
	return;
}

//****************************************************************************
// STDMETHODIMP
// CIlsProtocolNotify::QueryInterface (REFIID riid, void **ppv)
//
//****************************************************************************

STDMETHODIMP
CIlsProtocolNotify::QueryInterface (REFIID riid, void **ppv)
{
	if (riid == IID_IIlsProtocolNotify || riid == IID_IUnknown)
	{
		*ppv = (IIlsProtocolNotify *) this;
		AddRef();
		return S_OK;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	};
}

//****************************************************************************
// STDMETHODIMP_(ULONG)
// CIlsProtocolNotify::AddRef (void)
//
//****************************************************************************

STDMETHODIMP_(ULONG)
CIlsProtocolNotify::AddRef (void)
{
	return cRef++;
}

//****************************************************************************
// STDMETHODIMP_(ULONG)
// CIlsProtocolNotify::Release (void)
//
//****************************************************************************

STDMETHODIMP_(ULONG)
CIlsProtocolNotify::Release (void)
{
	cRef--;

	if (cRef == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return cRef;
	};
}



//****************************************************************************
// STDMETHODIMP
// CIlsProtocolNotify::UpdateResult(ULONG uReqID, HRESULT hResult)
//
//****************************************************************************

STDMETHODIMP
CIlsProtocolNotify::UpdateResult(ULONG uReqID, HRESULT hResult)
{
	MyTextOut (TEXT("IIlsProtocolNotify::UpdateResult(%x) returns %x [%s].\r\n"),
			uReqID, hResult, GetErrorString(hResult) );
	return S_OK;
}


