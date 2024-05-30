//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       usrinfo.cpp
//  Content:    This file contains the user info dialog functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"
#include "notify.h"
#include "appguid.h"


//****************************************************************************
//
// int NewUserDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog procedure for the user dialog box.
//
//****************************************************************************

int NewUserDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	USERINFO *pUserInfo;

	pUserInfo = (USERINFO *)GetWindowLong(hwnd, DWL_USER);

	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SetWindowLong (hwnd, DWL_USER, lParam);
			pUserInfo = (USERINFO *)lParam;

			SetWindowText(GetDlgItem(hwnd, IDC_UI_FIRSTNAME), pUserInfo->szFirstName);
			SetWindowText(GetDlgItem(hwnd, IDC_UI_LASTNAME),  pUserInfo->szLastName);
			SetWindowText(GetDlgItem(hwnd, IDC_UI_CITY),      pUserInfo->szCity);
			SetWindowText(GetDlgItem(hwnd, IDC_UI_COMMENT),   pUserInfo->szComment);
			SetWindowText(GetDlgItem(hwnd, IDC_UI_IPADD),     pUserInfo->szIPAddress);
			SetWindowText(GetDlgItem(hwnd, IDC_UI_EMAIL),     pUserInfo->szEmailName);
			SetWindowText(GetDlgItem(hwnd, IDC_UI_COUNTRY),   pUserInfo->szCountry);

			// Can't change email or country once set.
			// See if we are creating or modifying
			if(pUserInfo->fModify)
			{
				EnableWindow(GetDlgItem(hwnd, IDC_UI_EMAIL), FALSE);
				EnableWindow(GetDlgItem(hwnd, IDC_UI_COUNTRY), FALSE);
			}

			SetFocus (GetDlgItem(hwnd, IDC_UI_FIRSTNAME));
			break;
		}
		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
				case IDOK:
					SaveUserInfo(hwnd, pUserInfo);

				case IDCANCEL:
					EndDialog(hwnd, GET_WM_COMMAND_ID(wParam, lParam));
					break;
					
				default:
					break;
			};
			break;
		}

		default:
			break;
	};

	return 0;
}

//****************************************************************************
//
// HRESULT NewUserDialog(HWND hwnd)
//
// This function starts the user information dialog box.
//
//****************************************************************************

HRESULT NewUserDialog(HWND hwnd)
{
	HRESULT hr = E_FAIL;
	IIlsUser *pUser;
	USERINFO UserInfo;
	BSTR bstrAppID, bstrUserID;
	USERNODE un;
	PUSERNODE pun;
	
	HMENU hMenu;

	pun = &un;

	// clear the UserInfo structure
	strcpy(UserInfo.szFirstName,"");
	strcpy(UserInfo.szLastName,"");
	strcpy(UserInfo.szEmailName,"");
	strcpy(UserInfo.szCity,"");
	strcpy(UserInfo.szCountry,"");
	strcpy(UserInfo.szComment,"");
	strcpy(UserInfo.szIPAddress,"");

	UserInfo.fModify = FALSE;

	
	// Allow only one dialog at a time
	//
	hMenu = GetMenu(hwnd);
	EnableMenuItem(hMenu, IDM_NEWUSER, MF_BYCOMMAND | MF_GRAYED);

	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_USERINFO),
			hwnd, (DLGPROC)NewUserDlgProc, (LPARAM)&UserInfo) == IDOK)
	{

		if(!MyIsGoodString(UserInfo.szEmailName))
		{
			MyTextOut(TEXT("Email name is empty - no user object created.\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}
		// Convert the necessary strings to BSTRs
		//
		LPTSTR_to_BSTR(&bstrUserID, UserInfo.szEmailName);
		LPTSTR_to_BSTR(&bstrAppID, g_szAppID); // Use "ms-netmeeting" so NM can see this user

		// Create the user object
		hr = g_pIls->CreateUser(bstrUserID, bstrAppID, &pUser);

		if(SUCCEEDED(hr))
		{
			MyTextOut(TEXT("IIls::CreateUser succeeded. %s\r\n"), UserInfo.szEmailName);

			pun->pu = pUser;
			
			// Hookup the notification callback
			OnILSUserAdviseUnadvise(hwnd, pun, TRUE);

			// Set the rest of the user info fields
			// 
			SetUserInfo(hwnd, pun->pu, &UserInfo);

			// Add to the list of users
			NewUserNode(pun);

			if(!g_pUserList->IsEmpty()) // The user list is not empty, enable menu items
			{
				EnableMenuItem(hMenu, IDM_DESTROYUSER, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_CLONEUSER, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_MODIFYUSER, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_CREATE_PROT, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_DESTROY_PROT, MF_BYCOMMAND | MF_ENABLED);
				if(!g_pServerList->IsEmpty())  // only enable Reg/Unreg if there servers in the list
				{
					EnableMenuItem(hMenu, IDM_REGISTERUSER, MF_BYCOMMAND | MF_ENABLED);
					EnableMenuItem(hMenu, IDM_UNREGISTERUSER, MF_BYCOMMAND | MF_ENABLED);
				}
			}

		}
		else
		{
			ErrorMessage(hwnd, TEXT("IIls::CreateUser fails."), hr);
		}

		// Clean up
		SysFreeString(bstrAppID);
		SysFreeString(bstrUserID);

	}
	else
	{
		// User cancelled
		//
		MyTextOut(TEXT("Create User cancelled.\r\n"));

	};

MyExit:

	EnableMenuItem(hMenu, IDM_NEWUSER, MF_BYCOMMAND | MF_ENABLED);
	return hr;
};



//****************************************************************************
//
// HRESULT CloneUserDialog(HWND hwnd)
//
// This function starts the user information dialog box to copy a user.
//
//****************************************************************************

HRESULT CloneUserDialog(HWND hwnd)
{
	HRESULT hr = E_FAIL;
	
	BSTR bstrName;
	USERNODE un;
	PUSERNODE pun;
	char szUserName[MAX_NAME];
	LPTSTR psz;
	POSITION pos;
	USERNODE unClone;
	PUSERNODE punClone;
	HMENU hMenu;

	IIlsUser *pUserClone;

	pun = &un;
	punClone = &unClone;
	
	// Allow only one dialog at a time
	//
	hMenu = GetMenu(hwnd);
	EnableMenuItem(hMenu, IDM_CLONEUSER, MF_BYCOMMAND | MF_GRAYED);

	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
			hwnd, (DLGPROC)UserListDlgProc, (LPARAM)&szUserName) == IDOK)
	{
		if(!MyIsGoodString(szUserName))
		{
			MyTextOut(TEXT("User name is empty.\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}


		// Find the specified user in the list
		pos = g_pUserList->GetHeadPosition();

		while(pos)
		{
			pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);
			
			hr = pun->pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrName);
			BSTR_to_LPTSTR(&psz, bstrName);
			if(strcmp(psz, szUserName) == 0)
			{
				FreeLPTSTR(psz);
				break;
			}
			g_pUserList->GetNext(pos);
			FreeLPTSTR(psz);
		}
		pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);

		// Clone the specified user object
		hr = pun->pu->Clone(&pUserClone);

		if(SUCCEEDED(hr))
		{
			// the user name is in psz and bstrName now
			//
			MyTextOut(TEXT("IIlsUser::Clone succeeded for user %s\r\n"), psz);

			punClone->pu = pUserClone;

			// Hookup the notification callback
			OnILSUserAdviseUnadvise(hwnd, punClone, TRUE);

			// Add to the list of users
			NewUserNode(punClone);

		}
		else
		{
			ErrorMessage(hwnd, TEXT("IIlsUser::CloneUser fails."), hr);
		}
	}
	else
	{
		// User cancelled
		//
		MyTextOut(TEXT("Clone User cancelled.\r\n"));

	};
MyExit:

	EnableMenuItem(hMenu, IDM_CLONEUSER, MF_BYCOMMAND | MF_ENABLED);
	return hr;
};



//****************************************************************************
//
// void NewUserNode (PUSERNODE pUser)
//
// Create a new node and add to the linked list
//****************************************************************************
void NewUserNode(PUSERNODE pUserNode)
{
	PUSERNODE pun;
	
	pun = (PUSERNODE)LocalAlloc(LMEM_FIXED, sizeof(USERNODE));

	pun->pu = pUserNode->pu;
	pun->puNotify = pUserNode->puNotify;
	pun->pProtList = new COBLIST;

	g_pUserList->AddTail( (void *)pun );
}


//****************************************************************************
//
// void SetUserInfo (HWND hwnd, IlsUser *pUser, USERINFO *pUserInfo)
//
//****************************************************************************
void SetUserInfo(HWND hwnd, IIlsUser *pu, USERINFO *pUserInfo)
{
	HRESULT hr = E_FAIL;
	BSTR bstrFirstName = NULL, bstrLastName = NULL, bstrEmailName = NULL;
	BSTR bstrCity = NULL, bstrCountry = NULL, bstrComment = NULL, bstrIPAddress = NULL;
	GUID *pGUID;
	
	pGUID = (GUID *)&GUID_ILSTest;
	
	// FirstName
	//
	LPTSTR_to_BSTR(&bstrFirstName, pUserInfo->szFirstName);
	hr = pu->SetStandardAttribute(ILS_STDATTR_FIRST_NAME, bstrFirstName);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}
	
	// LastName
	//
	LPTSTR_to_BSTR(&bstrLastName, pUserInfo->szLastName);
	hr = pu->SetStandardAttribute(ILS_STDATTR_LAST_NAME, bstrLastName);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}
	
	// EmailName
	//
	LPTSTR_to_BSTR(&bstrEmailName, pUserInfo->szEmailName);
	hr = pu->SetStandardAttribute(ILS_STDATTR_EMAIL_NAME, bstrEmailName);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}

	// City/State
	//
	LPTSTR_to_BSTR(&bstrCity, pUserInfo->szCity);
	hr = pu->SetStandardAttribute(ILS_STDATTR_CITY_NAME, bstrCity);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}
	
	// Country
	//
	LPTSTR_to_BSTR(&bstrCountry, pUserInfo->szCountry);
	hr = pu->SetStandardAttribute(ILS_STDATTR_COUNTRY_NAME, bstrCountry);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}

	// IP_Address
	//
	LPTSTR_to_BSTR(&bstrIPAddress, pUserInfo->szIPAddress);
	hr = pu->SetStandardAttribute(ILS_STDATTR_IP_ADDRESS, bstrIPAddress);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}
	

	
	// Comment
	//
	LPTSTR_to_BSTR(&bstrComment, pUserInfo->szComment);
	hr = pu->SetStandardAttribute(ILS_STDATTR_COMMENT, bstrComment);

	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::SetStandardAttribute fails."), hr);
		goto MyExit;
	}


	// Make us visible to the rest of the world
	//
	hr = pu->SetVisible(0x01);

	// Set the GUID for the user
	//
	hr = pu->SetGuid(pGUID);

MyExit:
	// Cleanup
	if(bstrFirstName)
		SysFreeString(bstrFirstName);
	if(bstrLastName)
		SysFreeString(bstrLastName);
	if(bstrEmailName)
		SysFreeString(bstrEmailName);
	if(bstrCity)
		SysFreeString(bstrCity);
	if(bstrCountry)
		SysFreeString(bstrCountry);
	if(bstrComment)
		SysFreeString(bstrComment);
	if(bstrIPAddress)
		SysFreeString(bstrIPAddress);

}


//****************************************************************************
//
// void GeUserInfo (HWND hwnd, IlsUser *pUser, USERINFO *pUserInfo)
//
//****************************************************************************
void GetUserInfo(HWND hwnd, IIlsUser *pu, USERINFO *pUserInfo)
{
	HRESULT hr = E_FAIL;
	BSTR bstrName = NULL;
	GUID *pGUID;
	LPTSTR szTemp;
	
	pGUID = (GUID *)&GUID_ILSTest;
	
	// FirstName
	hr = pu->GetStandardAttribute(ILS_STDATTR_FIRST_NAME, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szFirstName, szTemp);

	if(bstrName)
		SysFreeString(bstrName);

	// LastName
	hr = pu->GetStandardAttribute(ILS_STDATTR_LAST_NAME, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szLastName, szTemp);

	if(bstrName)
		SysFreeString(bstrName);

	// EMailName
	hr = pu->GetStandardAttribute(ILS_STDATTR_EMAIL_NAME, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szEmailName, szTemp);

	if(bstrName)
		SysFreeString(bstrName);

	// City
	hr = pu->GetStandardAttribute(ILS_STDATTR_CITY_NAME, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szCity, szTemp);

	if(bstrName)
		SysFreeString(bstrName);

	// Country
	hr = pu->GetStandardAttribute(ILS_STDATTR_COUNTRY_NAME, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szCountry, szTemp);

	if(bstrName)
		SysFreeString(bstrName);

	// IP Address
	hr = pu->GetStandardAttribute(ILS_STDATTR_IP_ADDRESS, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szIPAddress, szTemp);

	if(bstrName)
		SysFreeString(bstrName);

	// Comment
	hr = pu->GetStandardAttribute(ILS_STDATTR_COMMENT, &bstrName);
	if(FAILED(hr))
	{
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);
		goto MyExit;
	}
	BSTR_to_LPTSTR(&szTemp, bstrName);
	strcpy(pUserInfo->szComment, szTemp);

	if(bstrName)
		SysFreeString(bstrName);
MyExit:

	return;
}




//****************************************************************************
//
// void SaveUserInfo(HWND hwnd, PUSERINFO pUserInfo)
//
// This function saves the changes in the user information.
// to the USERINFO structure
//
//****************************************************************************
void SaveUserInfo(HWND hwnd, PUSERINFO pUserInfo)
{
	HWND    hCtrl;
	TCHAR   szText[MAX_NAME];

	// Get each information field
	//
	hCtrl = GetDlgItem(hwnd, IDC_UI_FIRSTNAME);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szFirstName, szText);

	hCtrl = GetDlgItem(hwnd, IDC_UI_LASTNAME);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szLastName, szText);

	hCtrl = GetDlgItem(hwnd, IDC_UI_EMAIL);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szEmailName, szText);

	hCtrl = GetDlgItem(hwnd, IDC_UI_CITY);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szCity, szText);

	hCtrl = GetDlgItem(hwnd, IDC_UI_COUNTRY);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szCountry, szText);

	hCtrl = GetDlgItem(hwnd, IDC_UI_COMMENT);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szComment, szText);

	hCtrl = GetDlgItem(hwnd, IDC_UI_IPADD);
	Edit_GetText(hCtrl, (LPTSTR)szText, ARRAYSIZE(szText));
	strcpy(pUserInfo->szIPAddress, szText);

}

//****************************************************************************
//
// HRESULT RemoveUserDialog(HWND hwnd)
//
// This function starts the dialog box for 
// destroying a user object.
//
//****************************************************************************
HRESULT RemoveUserDialog(HWND hwnd)
{
	HRESULT hr = E_FAIL;
	HMENU hMenu;
	char szUserName[MAX_NAME];
	char *psz;
	POSITION pos;
	USERNODE *pun;
	BSTR bstrName;
	
	szUserName[0] = NULL;
	
	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
			hwnd, (DLGPROC)UserListDlgProc, (LPARAM)szUserName) == IDOK)
	{
		if(!MyIsGoodString(szUserName))
		{
			MyTextOut(TEXT("User name is empty.\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}

		// match name to usernode
		pos = g_pUserList->GetHeadPosition();

		while(pos)
		{
			pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);
			
			hr = pun->pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrName);
			BSTR_to_LPTSTR(&psz, bstrName);
			if(strcmp(psz, szUserName) == 0)
			{
				FreeLPTSTR(psz);
				break;
			}
			g_pUserList->GetNext(pos);
			FreeLPTSTR(psz);
		}
		
		// Disconnect the notification callbacks
		//
		OnILSUserAdviseUnadvise(hwnd, pun, FALSE);

		// free user object
		pun->pu->Release();
		pun->pu = NULL;

		// free the protocol list
		delete pun->pProtList;
		
		// remove node from list
		g_pUserList->RemoveAt(pos);

		LocalFree(pun);
		pun = NULL;

		// if the list is now empty, disable the menu item
		if(g_pUserList->IsEmpty())
		{
			hMenu = GetMenu(hwnd);
			EnableMenuItem(hMenu, IDM_DESTROYUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_REGISTERUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_UNREGISTERUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_CLONEUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_MODIFYUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_CREATE_PROT, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_DESTROY_PROT, MF_BYCOMMAND | MF_GRAYED);

		}
		MyTextOut(TEXT("User %s removed.\r\n"), szUserName);
	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("Destroy user cancelled.\r\n"));
	}
MyExit:

	return hr;
}

//****************************************************************************
//
// int UserListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog proc that displays the current user objects
// and returns the chosen item.
//
//****************************************************************************
int UserListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	USERNODE *pun;
	LPTSTR pszTemp;
	POSITION pos;
	HWND hwndList;
	char *psz;
	int iIndex;
	HRESULT hr = E_FAIL;
	BSTR bstrName;



	switch (msg)
	{
		case WM_INITDIALOG:
		{
			hwndList = GetDlgItem(hwnd, IDC_LIST);
			SetWindowLong (hwnd, DWL_USER, lParam);

			// Walk the list of servers and fill the listbox with names
			pos = g_pUserList->GetHeadPosition();
			SetWindowText(hwnd, "User List");


			while(pos)
			{
				pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);
				hr = pun->pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrName);
				BSTR_to_LPTSTR(&psz, bstrName);
				SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)psz);
				g_pUserList->GetNext(pos);
				FreeLPTSTR(psz);
			}

			SetFocus(GetDlgItem(hwnd, IDC_LIST));		
			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
				hwndList = GetDlgItem(hwnd, IDC_LIST);

				// return the name of the user chosen 
				pszTemp = (LPTSTR)GetWindowLong(hwnd, DWL_USER);
				iIndex = SendMessage(hwndList, LB_GETCURSEL, 0,0);
				if(iIndex == -1) // default to the first item in the list if none selected
					iIndex = 0;
				iIndex = SendMessage(hwndList, LB_GETTEXT, iIndex, (LPARAM)pszTemp);

				// Fall through to end the dialog!!
				
			case IDCANCEL:
				EndDialog(hwnd, GET_WM_COMMAND_ID(wParam, lParam));
				break;

			default:
				break;
			};
			break;
		}

		default:
			break;
	};

	return 0;
}


//****************************************************************************
//
// HRESULT RegisterUserDialog(HWND hwnd, BOOL fRegister)
//
// This function starts the dialog box for 
// registering or unregistering a user object on a server.
//
//****************************************************************************
HRESULT RegUnregUserDialog(HWND hwnd, BOOL fRegister)
{
	HRESULT hr = E_FAIL;
	char szUserName[MAX_NAME];
	char szServerName[MAX_NAME];
	char *psz;
	POSITION pos;
	BSTR bstrName;
	PUSERNODE pun;
	PSERVERNODE psn;
	
	// Ask which user to reg/unreg
	//
	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
			hwnd, (DLGPROC)UserListDlgProc, (LPARAM)szUserName) == IDOK)
	{
	
		if(!MyIsGoodString(szUserName))
		{
			MyTextOut(TEXT("User name is empty.\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}


		// match name to usernode
		pos = g_pUserList->GetHeadPosition();

		while(pos)
		{
			pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);
			
			hr = pun->pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrName);
			BSTR_to_LPTSTR(&psz, bstrName);
			if(strcmp(psz, szUserName) == 0)
			{
				FreeLPTSTR(psz);
				break;
			}
			g_pUserList->GetNext(pos);
			FreeLPTSTR(psz);
		}

		if(fRegister)
		{
			// Got the user, now ask which server to use
			//
			if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
					hwnd, (DLGPROC)ServerListDlgProc, (LPARAM)szServerName) == IDOK)
			{

			if(!MyIsGoodString(szServerName))
			{
				MyTextOut(TEXT("Server name is empty.\r\n"));
				hr = E_FAIL;
				goto MyExit;
			}

				// match name to servernode
				pos = g_pServerList->GetHeadPosition();

				while(pos)
				{
					psn = (PSERVERNODE)g_pServerList->GetFromPosition(pos);
					if(strcmp(psn->szName, (LPCTSTR)szServerName) == 0)
						break;
					g_pServerList->GetNext(pos);
				}
			}

			RegisterUser(hwnd, pun->pu, psn->pSrv, psn->szName);
		}
		else
		{
			UnregisterUser(hwnd, pun->pu, FALSE);
		}

	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("Reg/Unreg cancelled.\r\n"));
	}

MyExit:
	
	return hr;
}

//****************************************************************************
//
// HRESULT GetUserInfoDialog(HWND hwnd)
//
// This function displays user information for all users
//
//****************************************************************************
HRESULT GetUserInfoDialog(HWND hwnd)
{
	ULONG uReqID;
	BOOL fCancel = FALSE;
	HRESULT hr = E_FAIL;
	char szUserID[MAX_NAME];
	char szServerName[MAX_NAME];
	POSITION pos;
	PSERVERNODE psn;
	BSTR bstrUserID = NULL, bstrAppID = NULL, bstrProtID = NULL;

	// Ask which user to query
	//
	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_USERNAME),
			hwnd, (DLGPROC)UserNameDlgProc, (LPARAM)szUserID) == IDOK)
	{

		if(!MyIsGoodString(szUserID))
		{
			MyTextOut(TEXT("User ID is empty.\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}

		LPTSTR_to_BSTR(&bstrUserID, (LPCTSTR)szUserID);
		
		// Got the user, now ask which server to use
		//
		if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
				hwnd, (DLGPROC)ServerListDlgProc, (LPARAM)szServerName) == IDOK)
		{

			if(!MyIsGoodString(szServerName))
			{
				MyTextOut(TEXT("Server name is empty.\r\n"));
				hr = E_FAIL;
				goto MyExit;
			}

			// match name to servernode
			pos = g_pServerList->GetHeadPosition();

			while(pos)
			{
				psn = (PSERVERNODE)g_pServerList->GetFromPosition(pos);
				if(strcmp(psn->szName, (LPCTSTR)szServerName) == 0)
					break;
				g_pServerList->GetNext(pos);
			}
		

			LPTSTR_to_BSTR(&bstrProtID, g_szProtID); // TODO - allow user to specify protocol ID here

			LPTSTR_to_BSTR(&bstrAppID, g_szAppID); // Use "ms-netmeeting"

			// set up the attributes object here so the 
			// desired extended attributes get returned.
			IIlsAttributes *pAttrib = NULL;
			hr = GetNMAttributesObject(g_pIls, &pAttrib);

			hr = g_pIls->GetUser(psn->pSrv, bstrUserID, bstrAppID, bstrProtID, pAttrib, NULL, &uReqID);

			if (SUCCEEDED(hr))
			{
				MyTextOut(TEXT("IIlsMain::GetUser(%x) pending for user %s on server %s.\r\n"),
					uReqID, szUserID, szServerName);
			}
			else
				ErrorMessage(hwnd, TEXT("IIlsMain::GetUser fails."), hr);

		}
		else
		{
			//User cancelled
			MyTextOut(TEXT("Server List cancelled.\r\n"));
		}
	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("Get User cancelled.\r\n"));
	}

MyExit:
	// Cleanup
	//
	if(bstrUserID)
		SysFreeString(bstrUserID);
	if(bstrAppID)
		SysFreeString(bstrAppID);
	if(bstrProtID)
		SysFreeString(bstrProtID);
		
	return hr;
}



//****************************************************************************
//
// int UserNameDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog proc that displays the current user objects
// and returns the chosen item.
//
//****************************************************************************
int UserNameDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LPTSTR pszTemp;
	HRESULT hr = E_FAIL;


	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SetWindowLong (hwnd, DWL_USER, lParam);
			SetFocus(GetDlgItem(hwnd, IDC_USER_NAME));
			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
				// return the name of the user chosen 
				pszTemp = (LPTSTR)GetWindowLong(hwnd, DWL_USER);
				GetDlgItemText(hwnd, IDC_USER_NAME, pszTemp, MAX_NAME);

				// Fall through to end the dialog!!
				
			case IDCANCEL:
				EndDialog(hwnd, GET_WM_COMMAND_ID(wParam, lParam));
				break;

			default:
				break;
			};
			break;
		}

		default:
			break;
	};

	return 0;
}


//****************************************************************************
//
// HRESULT DisplayIlsUserDialog(HWND hwnd, IIlsUser *pu)
//
// This function displays user information for all users
//
//****************************************************************************
HRESULT DisplayIlsUserDialog(HWND hwnd, IIlsUser *pu)
{

	HRESULT hr = E_FAIL;

	// Display the specified user details
	//
	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_ILSUSER),
			hwnd, (DLGPROC)UserDlgProc, (LPARAM)pu) != IDOK)
	{
		//User cancelled
		MyTextOut(TEXT("Get User cancelled.\r\n"));
	}
	
	return hr;
}



//****************************************************************************
//
// int UserDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog proc that displays the current user objects
// and returns the chosen item.
//
//****************************************************************************
int UserDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IIlsUser *pu;

	switch (msg)
	{
		case WM_INITDIALOG:
		{
			pu = (IIlsUser *)lParam;
			SetWindowLong (hwnd, DWL_USER, lParam);
			InitIlsUser(hwnd, pu);
			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
			case IDCANCEL:
				EndDialog(hwnd, GET_WM_COMMAND_ID(wParam, lParam));
				break;

			case IDC_UU_PROT:  // Display the protocols in the main window
			{
				IIlsUser *pu;

				pu = (IIlsUser *)GetWindowLong(hwnd, DWL_USER);
				EnumUserProtocols(hwnd, pu);
				break;
			}
			case IDC_UU_EXATTR:  // display the extended attributes in the main window
			{
				IIlsUser *pu;

				pu = (IIlsUser *)GetWindowLong(hwnd, DWL_USER);
				EnumUserExAttributes(hwnd, pu);
				break;
			}

			case IDC_UU_GETPROT:  // Display the protocol information in the main window
			{
				IIlsUser *pu;

				pu = (IIlsUser *)GetWindowLong(hwnd, DWL_USER);
				DisplayProtocol(hwnd, pu);
				break;
			}


			case WM_IT_ENUM_NAMES_RESULT:
				DisplayIlsNames(hwnd, (IEnumIlsNames *)lParam, "protocols");
				break;

			default:
				break;
			};
			break;
		}

		default:
			break;
	};

	return 0;
}




//****************************************************************************
//
// void InitIlsUser(HWND hwnd, IIlsUser *pu)
// 
// Retrieve the standard attributes and display them in a dialog.
//
//****************************************************************************
void InitIlsUser(HWND hwnd, IIlsUser *pu)
{

	LPTSTR szID, szFirstName, szLastName, szEmailName, szCityName, szCountryName;
	LPTSTR szComment, szAppID, szAppMimeType, szIPAdd;
	TCHAR szVisible[MAX_NAME];
	TCHAR szGuid[MAX_NAME];
	HRESULT hr = E_FAIL;
	BSTR bstrTemp;
	TCHAR szText[512];
	DWORD fVisible;
	GUID guid;

	pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrTemp);
	BSTR_to_LPTSTR(&szID, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_IP_ADDRESS, &bstrTemp);
	BSTR_to_LPTSTR(&szIPAdd, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_EMAIL_NAME, &bstrTemp);
	BSTR_to_LPTSTR(&szEmailName, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_FIRST_NAME, &bstrTemp);
	BSTR_to_LPTSTR(&szFirstName, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_LAST_NAME, &bstrTemp);
	BSTR_to_LPTSTR(&szLastName, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_CITY_NAME, &bstrTemp);
	BSTR_to_LPTSTR(&szCityName, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_COUNTRY_NAME, &bstrTemp);
	BSTR_to_LPTSTR(&szCountryName, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_COMMENT, &bstrTemp);
	BSTR_to_LPTSTR(&szComment, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_APP_NAME, &bstrTemp);
	BSTR_to_LPTSTR(&szAppID, bstrTemp);
	SysFreeString(bstrTemp);
	
	pu->GetStandardAttribute(ILS_STDATTR_APP_MIME_TYPE, &bstrTemp);
	BSTR_to_LPTSTR(&szAppMimeType, bstrTemp);
	SysFreeString(bstrTemp);

	// English interpretation of Visibile flags
	hr = pu->GetVisible(&fVisible);
	if(SUCCEEDED(hr))
		strcpy(szVisible, (fVisible == 0x01 ? TEXT("visible") : TEXT("hidden")));
	else
		strcpy(szVisible, TEXT("ERROR"));
	
	hr = pu->GetGuid(&guid);
	if(SUCCEEDED(hr))
		StringFromGuid(guid, szGuid);
	else
		strcpy(szGuid, TEXT("ERROR"));

	wsprintf(szText, 
		TEXT("ID:\t\t%s\nFirst:\t\t%s\nLast:\t\t%s\nE-mail:\t\t%s\nCity:\t\t%s\nCountry:\t\t%s\nComment:\t%s\nIP:\t\t%s\nAppID:\t\t%s\nMime Type:\t%s\nVisibility:\t\t%s\nGUID:\t%s"),
		szID, szFirstName, szLastName, szEmailName, szCityName, szCountryName, 
		szComment, szIPAdd, szAppID, szAppMimeType, szVisible, szGuid);

	SetDlgItemText(hwnd, IDC_UU_INFO, szText);
	
	FreeLPTSTR(szID);
	FreeLPTSTR(szIPAdd);
	FreeLPTSTR(szEmailName);
	FreeLPTSTR(szFirstName);
	FreeLPTSTR(szLastName);
	FreeLPTSTR(szCityName);
	FreeLPTSTR(szCountryName);
	FreeLPTSTR(szComment);
	FreeLPTSTR(szAppID);
	FreeLPTSTR(szAppMimeType);

}


//****************************************************************************
//
// HRESULT UnregisterAllUsers(HWND hwnd)
//
// This function removes all our users from the servers
//
//****************************************************************************

void UnregisterAllUsers(HWND hwnd)
{
	POSITION pos;
	PUSERNODE pun;

	// Walk the list of users
	pos = g_pUserList->GetHeadPosition();

	while(pos)
	{
		pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);
		UnregisterUser(hwnd, pun->pu, TRUE);

		g_pUserList->GetNext(pos);
	}
	return;
};



//****************************************************************************
//
// HRESULT ModifyUserDialog(HWND hwnd)
//
// This function starts the user information modify dialog box.
//
//****************************************************************************

HRESULT ModifyUserDialog(HWND hwnd)
{
	HRESULT hr = E_FAIL;
	USERINFO UserInfo;
	BSTR bstrName = NULL;
	LPTSTR psz = NULL;
	char szUserName[MAX_NAME];
	USERNODE un;
	PUSERNODE pun;
	POSITION pos;
	ULONG uReqID;
	HMENU hMenu;

	pun = &un;
	
	// Allow only one dialog at a time
	//
	hMenu = GetMenu(hwnd);
	EnableMenuItem(hMenu, IDM_NEWUSER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_MODIFYUSER, MF_BYCOMMAND | MF_GRAYED);

	// Ask which user to query
	//
	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
			hwnd, (DLGPROC)UserListDlgProc, (LPARAM)&szUserName) == IDOK)
	{

		// Check the user name
		if(!MyIsGoodString(szUserName))
		{
			MyTextOut(TEXT("User Name is invalid.\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}

		// Find the specified user in the list
		pos = g_pUserList->GetHeadPosition();

		while(pos)
		{
			pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);
			
			hr = pun->pu->GetStandardAttribute(ILS_STDATTR_USER_ID, &bstrName);
			BSTR_to_LPTSTR(&psz, bstrName);
			if(strcmp(psz, szUserName) == 0)
			{
				FreeLPTSTR(psz);
				break;
			}
			g_pUserList->GetNext(pos);
			FreeLPTSTR(psz);
		}
		pun = (PUSERNODE)g_pUserList->GetFromPosition(pos);

		// Get the user info stuff here...
		GetUserInfo(hwnd, pun->pu, &UserInfo);

		// Mark this for modification
		UserInfo.fModify = TRUE;
	
		// Show the user info dialog box and allow the user make changes
		if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_USERINFO),
				hwnd, (DLGPROC)NewUserDlgProc, (LPARAM)&UserInfo) == IDOK)
		{
			// For now we assume that if they've pressed OK, they actually changed something

			// Can't change EMAIL_NAME or COUNTRY_NAME -- see SDK documentation
			//
			//ChangeAttribute(pun->pu, ILS_STDATTR_EMAIL_NAME,   UserInfo.szEmailName);
			//ChangeAttribute(pun->pu, ILS_STDATTR_COUNTRY_NAME, UserInfo.szCountry);
			
			ChangeAttribute(pun->pu, ILS_STDATTR_FIRST_NAME,   UserInfo.szFirstName);
			ChangeAttribute(pun->pu, ILS_STDATTR_LAST_NAME,    UserInfo.szLastName);
			ChangeAttribute(pun->pu, ILS_STDATTR_CITY_NAME,    UserInfo.szCity);
			ChangeAttribute(pun->pu, ILS_STDATTR_COMMENT,      UserInfo.szComment);
			ChangeAttribute(pun->pu, ILS_STDATTR_IP_ADDRESS,   UserInfo.szIPAddress);

			// Now we've got the local user changed, write it to the server
			hr = pun->pu->Update(&uReqID);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsUser::Update fails."), hr);
				goto MyExit;
			}
		}
		else
		{
			// User cancelled
			//
			MyTextOut(TEXT("Modify User cancelled.\r\n"));
		};
	}
MyExit:
	EnableMenuItem(hMenu, IDM_NEWUSER, MF_BYCOMMAND | MF_ENABLED);
	EnableMenuItem(hMenu, IDM_MODIFYUSER, MF_BYCOMMAND | MF_ENABLED);
	return hr;
};



//****************************************************************************
//
// HRESULT ChangeAttribute(ILS_STD_ATTR_NAME attr, LPTSTR psz)
//
// This function removes all our users from the servers
//
//****************************************************************************
HRESULT ChangeAttribute(IIlsUser *pu, ILS_STD_ATTR_NAME attr, LPTSTR psz)
{
	BSTR bstr;
	HRESULT hr = E_FAIL;
	
	if(MyIsGoodString(psz))
	{
		LPTSTR_to_BSTR(&bstr, psz);
		hr = pu->SetStandardAttribute(attr, bstr);

		if(SUCCEEDED(hr))
			SysFreeString(bstr);
	}

	return hr;
}
