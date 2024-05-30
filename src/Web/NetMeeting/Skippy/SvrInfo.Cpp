//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       svrinfo.cpp
//  Content:    This file contains the server info dialog functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"
#include "notify.h"

//****************************************************************************
//
// HRESULT NewServerDialog(HWND hwnd)
//
// This function starts the server information dialog box for creating a server.
//
//****************************************************************************
HRESULT NewServerDialog(HWND hwnd)
{
	HRESULT hr = E_FAIL;
	HMENU hMenu;
	BSTR bstrServerName;
	IIlsServer *ps;
	SERVERINFO si;
	PSERVERINFO psi;

	psi = &si;
	
	// Set up the server info structure
	//
	psi->szServerName = NULL;
	psi->szLogonName = NULL;
	psi->szPassword = NULL;
	psi->eam = ILS_AUTH_ANONYMOUS;
	psi->szDomain = NULL;
	psi->szCredential = NULL;
	psi->szBaseDN = NULL;
	psi->dwTimeout = 0;

	// Allow only one dialog at a time
	//
	hMenu = GetMenu(hwnd);
	EnableMenuItem(hMenu, IDM_CREATESERVER, MF_BYCOMMAND | MF_GRAYED);

	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_SERVERNAME),
			hwnd, (DLGPROC)ServerDlgProc, (LPARAM)psi) == IDOK)
	{

		if(!MyIsGoodString(psi->szServerName))
		{
			MyTextOut(TEXT("Server name is empty - no server object created\r\n"));
			hr = E_FAIL;
			goto MyExit;
		}
		
		LPTSTR_to_BSTR(&bstrServerName, psi->szServerName);

		// Create the server object
		hr = g_pIls->CreateServer(bstrServerName, &ps);
		
		if (SUCCEEDED(hr))
		{
			MyTextOut(TEXT("IIls::CreateServer succeeded. %s\r\n"), psi->szServerName);

			// Set the server parameters
			//
			SetServerInfo(hwnd, ps, psi);

			// Add this server to the global list of servers
			//
			NewServerNode(ps, psi->szServerName);


			if(!g_pServerList->IsEmpty()) // Check if any menu items should be enabled
			{
				EnableMenuItem(hMenu, IDM_DESTROYSERVER, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_ENUMUSERS, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_ENUMUSERNAMES, MF_BYCOMMAND | MF_ENABLED);
				EnableMenuItem(hMenu, IDM_GETUSERINFO, MF_BYCOMMAND | MF_ENABLED);
				if(!g_pUserList->IsEmpty())  // only enable Reg/Unreg if are users in the list
				{
					EnableMenuItem(hMenu, IDM_REGISTERUSER, MF_BYCOMMAND | MF_ENABLED);
					EnableMenuItem(hMenu, IDM_UNREGISTERUSER, MF_BYCOMMAND | MF_ENABLED);
				}

			}

		}
		else
		{
			ErrorMessage(hwnd, TEXT("IIls::CreateServer fails."), hr);
		};
		SysFreeString(bstrServerName);
	}
	else
	{
		// User cancelled
		//
		MyTextOut(TEXT("IIls::CreateServer cancelled.\r\n"));

	}

MyExit:

	// Clean up
	if(psi->szServerName != NULL)
		FreeLPTSTR(psi->szServerName);

	if(psi->szLogonName != NULL)
		FreeLPTSTR(psi->szLogonName);

	if(psi->szPassword != NULL)
		FreeLPTSTR(psi->szPassword);

	if(psi->szDomain != NULL)
		FreeLPTSTR(psi->szDomain);

	if(psi->szCredential != NULL)
		FreeLPTSTR(psi->szCredential);

	if(psi->szBaseDN != NULL)
		FreeLPTSTR(psi->szBaseDN);




	EnableMenuItem(hMenu, IDM_CREATESERVER, MF_BYCOMMAND | MF_ENABLED);
	return hr;
}

//****************************************************************************
//
// int ServerDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog procedure for the server prompt dialog box.
//
//****************************************************************************

int ServerDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PSERVERINFO psInfo;
	HWND hwndCombo;
	BOOL fSuccess;
	int iIndex;

	switch (msg)
	{
		case WM_INITDIALOG:
		{
			hwndCombo = GetDlgItem(hwnd, IDC_AUTH_METHOD);

			SetWindowLong (hwnd, DWL_USER, lParam);
			SetFocus(GetDlgItem(hwnd, IDC_SVR_NAME));

			//  set the auth method strings in the list
			//
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"ANONYMOUS");
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"CLEAR_TEXT");
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"NTLM");
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"DPA");
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"MSN");
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"SICILY");
			SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM)"SSPI");

			// set default auth method
			SendMessage(hwndCombo, CB_SETCURSEL, 0, 0);

			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
				{
				TCHAR szTemp[MAX_NAME];
				
				psInfo = (PSERVERINFO)GetWindowLong(hwnd, DWL_USER);
				hwndCombo = GetDlgItem(hwnd, IDC_AUTH_METHOD);

				// clear the server info
				//
				psInfo->szServerName = NULL;
				psInfo->szLogonName = NULL;
				psInfo->szPassword = NULL;
				psInfo->szCredential = NULL;
				psInfo->szDomain = NULL;
				psInfo->szBaseDN = NULL;


				// Get the server name (required)
				//
				if(0 != GetDlgItemText(hwnd, IDC_SVR_NAME, szTemp, MAX_PATH))
				{
					psInfo->szServerName = AllocLPTSTR(lstrlen(szTemp) + 1);
					strcpy(psInfo->szServerName, CharUpper(szTemp));
				}

				// Get the server logon name
				//
				if(0 != GetDlgItemText(hwnd, IDC_LOGON_NAME, szTemp, MAX_PATH))
				{
					psInfo->szLogonName = AllocLPTSTR(lstrlen(szTemp) + 1);
					strcpy(psInfo->szLogonName, szTemp);
				}


				// Get the server password
				//
				if(0 != GetDlgItemText(hwnd, IDC_PASSWORD, szTemp, MAX_PATH))
				{
					psInfo->szPassword = AllocLPTSTR(lstrlen(szTemp) + 1);
					strcpy(psInfo->szPassword, szTemp);
				}


				// Get the server credential to use
				//
				if(0 != GetDlgItemText(hwnd, IDC_AUTH_CRED, szTemp, MAX_PATH))
				{
					psInfo->szCredential = AllocLPTSTR(lstrlen(szTemp) + 1);
					strcpy(psInfo->szCredential, szTemp);
				}

				// Get the domain name use
				//
				if(0 != GetDlgItemText(hwnd, IDC_DOMAIN, szTemp, MAX_PATH))
				{
					psInfo->szDomain = AllocLPTSTR(lstrlen(szTemp) + 1);
					strcpy(psInfo->szDomain, szTemp);
				}


				// Get the Base Distinguished Name use
				//
				if(0 != GetDlgItemText(hwnd, IDC_BASEDN, szTemp, MAX_PATH))
				{
					psInfo->szBaseDN = AllocLPTSTR(lstrlen(szTemp) + 1);
					strcpy(psInfo->szBaseDN, szTemp);
				}

				// Get the server timeout to use
				//
				psInfo->dwTimeout = GetDlgItemInt(hwnd, IDC_TIMEOUT, &fSuccess, FALSE);


				// Get the currently selected authentication method
				//
				iIndex = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
				psInfo->eam = (ILS_ENUM_AUTH_METHOD)iIndex;
				
				// Fall through to end the dialog!!
				}
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
// void NewServerNode (IlsServer *pServer, LPTSTR szName)
//
//****************************************************************************
void NewServerNode(IIlsServer *pServer, LPTSTR szName)
{
	PSERVERNODE psn;

	// Alloc memory for the new node
	//
	psn = (PSERVERNODE)LocalAlloc(LMEM_FIXED, sizeof(SERVERNODE));

	// set the pointers to the new server
	psn->pSrv = pServer;
	strcpy(psn->szName, szName);

	// add to the list
	g_pServerList->AddTail( (void *)psn );

}

//****************************************************************************
//
// HRESULT RemoveServerDialog(HWND hwnd)
//
// This function starts the server information dialog box for 
// destroying a server.
//
//****************************************************************************
HRESULT RemoveServerDialog(HWND hwnd)
{
	HRESULT hr = E_FAIL;
	HMENU hMenu;
	PSERVERNODE psn;
	char szServerName[MAX_NAME];
	POSITION pos;

		
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
			if(strcmp(psn->szName, szServerName) == 0)
				break;
			g_pServerList->GetNext(pos);
		}

		// free server object
		psn->pSrv->Release();
		psn->pSrv = NULL;

		// free server name string
		LocalFree(psn->szName);

		// remove node from list
		g_pServerList->RemoveAt(pos);


		// if the list is now empty, disable the menu item
		if(g_pServerList->IsEmpty())
		{
			hMenu = GetMenu(hwnd);
			EnableMenuItem(hMenu, IDM_DESTROYSERVER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_ENUMUSERS, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_ENUMUSERNAMES, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_REGISTERUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_UNREGISTERUSER, MF_BYCOMMAND | MF_GRAYED);
			EnableMenuItem(hMenu, IDM_GETUSERINFO, MF_BYCOMMAND | MF_GRAYED);
		}

		MyTextOut(TEXT("Server %s removed.\r\n"), szServerName);

	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("Destroy server cancelled.\r\n"));
	}
	
MyExit:
	
	return hr;
}

//****************************************************************************
//
// int ServerListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog procedure for the remove server prompt dialog box.
//
//****************************************************************************

int ServerListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PSERVERNODE psn;
	LPTSTR pszTemp;
	POSITION pos;
	HWND hwndList;
	int iIndex;

	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SetWindowLong (hwnd, DWL_USER, lParam);
			hwndList = GetDlgItem(hwnd, IDC_LIST);

			// Walk the list of servers and fill the listbox with names
			pos = g_pServerList->GetHeadPosition();
			SetWindowText(hwnd, "Server List");

			while(pos)
			{
				psn = (PSERVERNODE)g_pServerList->GetFromPosition(pos);
				SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)psn->szName);
				g_pServerList->GetNext(pos);
			}
		
			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
				// return the name of the server chosen
				hwndList = GetDlgItem(hwnd, IDC_LIST);
				pszTemp = (LPTSTR)GetWindowLong(hwnd, DWL_USER);
				iIndex = SendMessage(hwndList, LB_GETCURSEL, 0,0);
				if(iIndex == -1)
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
// int SetServerInfo (HWND hwnd, IIlsServer *ps, PSERVERINFO psi)
//
// set the server options based on the server dialog settings
//
//****************************************************************************
void SetServerInfo(HWND hwnd, IIlsServer *ps, PSERVERINFO psi)
{
	HRESULT hr = E_FAIL;
	BSTR bstrTemp;

	// Auth method
	//
	hr = ps->SetAuthenticationMethod(psi->eam);
	if(SUCCEEDED(hr))
		MyTextOut("IIlsServer::SetAuthentication method succeeded.\r\n");
	else
		ErrorMessage(hwnd, TEXT("IIlsServer::SetAuthenticationMethod fails."), hr);


	// Logon name
	//
	if(psi->szLogonName)
	{
		LPTSTR_to_BSTR(&bstrTemp, psi->szLogonName);
		hr = ps->SetLogonName(bstrTemp);
		SysFreeString(bstrTemp);
		
		if(SUCCEEDED(hr))
			MyTextOut("IIlsServer::SetLogonName, set to %s.\r\n", psi->szLogonName);
		else
			ErrorMessage(hwnd, TEXT("IIlsServer::SetLogonName fails."), hr);

		FreeLPTSTR(psi->szLogonName);
		psi->szLogonName = NULL;

	}
	
	// Password
	//
	if(psi->szPassword)
	{
		LPTSTR_to_BSTR(&bstrTemp, psi->szPassword);
		hr = ps->SetLogonPassword(bstrTemp);
		SysFreeString(bstrTemp);
		
		if(SUCCEEDED(hr))
			MyTextOut("IIlsServer::SetLogonPassword, set to %s.\r\n", psi->szPassword);
		else
			ErrorMessage(hwnd, TEXT("IIlsServer::SetLogonPassword fails."), hr);

		FreeLPTSTR(psi->szPassword);
		psi->szPassword = NULL;

	}

	// Domain
	//
	if(psi->szDomain)
	{
		LPTSTR_to_BSTR(&bstrTemp, psi->szDomain);
		hr = ps->SetDomain(bstrTemp);
		SysFreeString(bstrTemp);
		
		if(SUCCEEDED(hr))
			MyTextOut("IIlsServer::SetDomain method, set to %s.\r\n", psi->szDomain);
		else
			ErrorMessage(hwnd, TEXT("IIlsServer::SetDomain fails."), hr);

		FreeLPTSTR(psi->szDomain);
		psi->szDomain = NULL;

	}

	// BaseDN
	//
	if(psi->szBaseDN)
	{
		LPTSTR_to_BSTR(&bstrTemp, psi->szBaseDN);
		hr = ps->SetBaseDN(bstrTemp);
		SysFreeString(bstrTemp);
		
		if(SUCCEEDED(hr))
			MyTextOut("IIlsServer::SetBaseDN method, set to %s.\r\n", psi->szBaseDN);
		else
			ErrorMessage(hwnd, TEXT("IIlsServer::SetBaseDN fails."), hr);

		FreeLPTSTR(psi->szBaseDN);
		psi->szBaseDN = NULL;

	}

	// Time out
	//
	if(psi->dwTimeout != 0)
	{
		hr = ps->SetTimeout(psi->dwTimeout);
		
		if(SUCCEEDED(hr))
			MyTextOut("IIlsServer::SetTimeout, set to %d seconds.\r\n", psi->dwTimeout);
		else
			ErrorMessage(hwnd, TEXT("IIlsServer::SetTimeout fails."), hr);
	}

}
