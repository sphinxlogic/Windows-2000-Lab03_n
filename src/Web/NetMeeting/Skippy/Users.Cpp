//*************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       users.cpp
//  Content:    This file contains user object manipulation functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"
#include "notify.h"

//****************************************************************************
//
// HRESULT EnumUsers(HWND hwnd, BOOL fShort)
//
// This function starts the user information display dialogs
//
//****************************************************************************

HRESULT EnumUsers(HWND hwnd, BOOL fShort)
{
	HRESULT hr = E_FAIL;
	ULONG uReqID;
	IIlsFilter *pFilter;
	SERVERNODE *pNode;
	POSITION pos;

	// Use the global USER filter
	pFilter = g_pUserFilter;

	if(g_pServerList->IsEmpty())
		MyTextOut(TEXT("No server objects defined.\r\n"));
	else
	{

		// Do the enumerations for all server objects 
		//
		pos = g_pServerList->GetHeadPosition();

		while(pos)
		{
			pNode = (PSERVERNODE)g_pServerList->GetFromPosition(pos);
		
			if (fShort) // we are only interested in user names
			{
				hr = g_pIls->EnumUserNames(pNode->pSrv, pFilter, NULL, &uReqID);

				if (SUCCEEDED(hr))
				{
					MyTextOut(TEXT("IIls::EnumUserNames(%x) pending for server %s.\r\n"),
							uReqID, pNode->szName);
				}
				else
				{
					ErrorMessage(hwnd, TEXT("IIls::EnumUserNames fails."), hr);
				}
			}
			else // retrieve the entire user object
			{
				// set up the attributes object here so the 
				// desired extended attributes get returned.
				IIlsAttributes *pAttrib = NULL;
				hr = GetNMAttributesObject(g_pIls, &pAttrib);

				if (SUCCEEDED(hr))
				{

					hr = g_pIls->EnumUsers(pNode->pSrv, pFilter, pAttrib, NULL, &uReqID);

					if (SUCCEEDED(hr))
					{
						MyTextOut(TEXT("IIls::EnumUsers(%x) pending for server %s.\r\n"), uReqID, pNode->szName);
					}
					else
					{
						ErrorMessage(hwnd, TEXT("IIls::EnumUsers fails."), hr);
					}
				}
			}
			g_pServerList->GetNext(pos);
		}
	}
	return hr;
};

//****************************************************************************
//
// HRESULT RegisterUser(HWND hwnd, IIlsUser *pu, IIlsServer *ps, LPTSTR szServerName)
//
// This function registers a specific user on all servers
//
//****************************************************************************

HRESULT RegisterUser(HWND hwnd, IIlsUser *pu, IIlsServer *ps, LPTSTR szServerName)
{
	HRESULT hr = E_FAIL;
	ULONG uReqID;
	LPTSTR szUserName;
	BSTR bstrUserName;


	// Get the user ID
	//
	hr = pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrUserName);

	if(SUCCEEDED(hr))
		BSTR_to_LPTSTR(&szUserName, bstrUserName);
	else
		strcpy(szUserName, TEXT("<unknown>"));

	// Register the user
	//
	hr = pu->Register(ps, &uReqID);

	if (SUCCEEDED(hr))
	{
		MyTextOut(TEXT("IIlsUser::Register(%x) pending for user %s on server %s.\r\n"),
				uReqID, szUserName, szServerName);
	}
	else
		ErrorMessage(hwnd, TEXT("IIlsUser::Register fails."), hr);

	return hr;
};


//****************************************************************************
//
// HRESULT UnregisterUser(HWND hwnd, IIlsUser *pu, BOOL fSilent)
//
// This function registers a specific user on all servers
//
//****************************************************************************

HRESULT UnregisterUser(HWND hwnd, IIlsUser *pu, BOOL fSilent)
{
	HRESULT hr = E_FAIL;
	ULONG uReqID;
	LPTSTR szUserName;
	BSTR bstrUserName;


	// Get the user ID
	//
	hr = pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrUserName);

	if(SUCCEEDED(hr))
		BSTR_to_LPTSTR(&szUserName, bstrUserName);
	else
		strcpy(szUserName, TEXT("<unknown>"));

	// Unregister the user
	//
	hr = pu->Unregister(&uReqID);

	if (SUCCEEDED(hr))
	{
		MyTextOut(TEXT("IIlsUser::Unregister(%x) pending for user %s.\r\n"),
				uReqID, szUserName);
	}
	else
	{
		if(!fSilent) // Do we really want error messages?
			ErrorMessage(hwnd, TEXT("IIlsUser::Unregister fails."), hr);
	}

	return hr;
};

//****************************************************************************
//
// HRESULT OnILSUserAdviseUnadvise(HWND hwnd, PILSUSER pIlsUser, BOOL fAdvise)
//
// This function enables/disables the user object notifications.
//
//****************************************************************************

HRESULT OnILSUserAdviseUnadvise(HWND hwnd, PUSERNODE pUserNode, BOOL fAdvise)
{
	IConnectionPointContainer *pcnpcnt;
	HRESULT hr;

	// Get the ConnectionPointContainer
	//
	hr = pUserNode->pu->QueryInterface(IID_IConnectionPointContainer,
							(void**)&pcnpcnt);
	if (FAILED(hr))
	{
		ErrorMessage(NULL, TEXT("Cannot query IID_IConnectionPointContainer: returns "),
					hr);
	}
	else
	{
		IConnectionPoint *pcnp;

		// Instead of an easy thing as follows
		// Let's do the hard thing through enumeration
		//
		hr = pcnpcnt->FindConnectionPoint(IID_IIlsUserNotify, &pcnp);

		if (hr != S_OK)
		{
			ErrorMessage(NULL, TEXT("Cannot find ConnectionPoint: returns "),
						hr);                
		}
		else
		{
			CIlsUserNotify *pun;

			if (fAdvise)
			{
				DWORD dwCookie;

				pun = new CIlsUserNotify (hwnd);
				hr = pcnp->Advise((IUnknown *)pun, &dwCookie);

				if (hr == S_OK)
				{
					MyTextOut(TEXT("User Advise succeeded.\r\n"));
					pun->AddRef();
					pun->SetCookie(dwCookie);
					pUserNode->puNotify = pun;
				};
			}
			else
			{
				pun = pUserNode->puNotify;

				if (pun != NULL)
				{
					hr = pcnp->Unadvise(pun->GetCookie());

					if (hr == S_OK)
					{
						MyTextOut(TEXT("User Unadvise succeeded.\r\n"));
						pun->Release();
						pUserNode->puNotify = NULL;
					};
				};
			};
			pcnp->Release();
		};
		pcnpcnt->Release();
	};
	return hr;
}

//****************************************************************************
//
// int DisplayIlsUserInfo(HWND hwnd, IIlsUser *pu)
//
// Displays the "easy" attributes for a user.
// for a more detailed look, use "Get User Info"
//****************************************************************************

int DisplayIlsUserInfo(HWND hwnd, IIlsUser *pu)
{
	HRESULT hr = E_FAIL;

	MyTextOut(" ======================== \r\n");

	// The standard attributes...
	DisplayStdAtt(pu, ILS_STDATTR_IP_ADDRESS,   "IP address  ", USER);
	DisplayStdAtt(pu, ILS_STDATTR_EMAIL_NAME,   "Email name  ", USER);
	DisplayStdAtt(pu, ILS_STDATTR_FIRST_NAME,   "First name  ", USER);
	DisplayStdAtt(pu, ILS_STDATTR_LAST_NAME,    "Last name  ",  USER);
	DisplayStdAtt(pu, ILS_STDATTR_CITY_NAME,    "City name  ",  USER);
	DisplayStdAtt(pu, ILS_STDATTR_COUNTRY_NAME, "Ctry name ",   USER);
	DisplayStdAtt(pu, ILS_STDATTR_COMMENT,      "Comment  ",    USER);
	DisplayStdAtt(pu, ILS_STDATTR_APP_NAME,     "App name  ",   USER);
	DisplayStdAtt(pu, ILS_STDATTR_APP_MIME_TYPE,"App Mime  ",   USER);

	MyTextOut(" ---------------------- \r\n");

	// The extended attributes...
	DisplayExtAtt(pu, NM_RESTRICTION,"User type  ",   USER);
	DisplayExtAtt(pu, NM_IN_A_CALL,"In a call  ",    USER);
	DisplayExtAtt(pu, NM_SEND_AUDIO,"Video capable  ",   USER);
	DisplayExtAtt(pu, NM_SEND_VIDEO,"Audio capable  ",   USER);

	MyTextOut(" ======================== \r\n");

  return 1;
}

//****************************************************************************
//
// HRESULT DisplayIlsUsers(HWND hwnd, IEnumIlsUsers *pEnum)
//
// This function displays user information for all users
//
//****************************************************************************

HRESULT DisplayIlsUsers(HWND hwnd, IEnumIlsUsers *pEnum)
{
	IIlsUser *pu;
	BOOL fCancel = FALSE;

	// For each user name...
	//
	while (!fCancel && (pEnum->Next(1, &pu, NULL) == NOERROR))
	{
		fCancel = (DisplayIlsUserInfo(hwnd, pu) == IDCANCEL);
		pu->Release();
	};
	pEnum->Release();

	return NOERROR;
}



