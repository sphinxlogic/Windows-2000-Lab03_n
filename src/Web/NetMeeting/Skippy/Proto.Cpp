//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       proto.cpp
//  Content:    This file contains protocol functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"



//****************************************************************************
//
// int EnumUserProtocols(HWND hwnd, IIlsUser *pu)
//
//
//****************************************************************************

HRESULT EnumUserProtocols(HWND hwnd, IIlsUser *pu)
{
	HRESULT hr = E_FAIL;
	IIlsFilter *pFilter;
	IIlsAttributes *pAttributes = NULL;
	ULONG uReqID;

	// use the global PROT filter, if not defined it will be NULL
	//
	pFilter = g_pProtFilter;

	// The third param is unused and must be NULL
	//
	hr = pu->EnumProtocols(pFilter, pAttributes, NULL, &uReqID);
	
	if (SUCCEEDED(hr))
		MyTextOut(TEXT("IIlsUser::EnumProtocols(%x) pending.\r\n"), uReqID);
	else
		ErrorMessage(hwnd, TEXT("IIlsUser::EnumProtocols fails."), hr);

	return hr;
}


//****************************************************************************
//
// int DisplayProtocol(HWND hwnd, IIlsUser *pu)
//
//
//****************************************************************************
HRESULT DisplayProtocol(HWND hwnd, IIlsUser *pu)
{
	HRESULT hr = E_FAIL;
	IIlsFilter *pFilter;
	IIlsAttributes *pAttributes = NULL;
	ULONG uReqID;
	BSTR bstrProtID;
	char szProtID[MAX_NAME];


	// use the global PROT filter, if not defined it will be NULL
	//
	pFilter = g_pProtFilter;
	pAttributes = NULL;

	// Ask which user to query (need to get a better dialog box)
	//
	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_USERNAME),
			hwnd, (DLGPROC)ProtoNameDlgProc, (LPARAM)szProtID) == IDOK)
	{
		LPTSTR_to_BSTR(&bstrProtID, szProtID);

		// The third param is unused and must be NULL
		//
		hr = pu->GetProtocol(bstrProtID, pAttributes, NULL, &uReqID);
	
		if (SUCCEEDED(hr))
			MyTextOut(TEXT("IIlsUser::GetProtocol(%x) pending.\r\n"), uReqID);
		else
			ErrorMessage(hwnd, TEXT("IIlsUser::GetProtocol fails."), hr);
	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("GetProtocol cancelled.\r\n"));
	}

	return hr;
}



//****************************************************************************
//
// int ProtocolDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog procedure for the protocol dialog box.
//
//****************************************************************************

int ProtocolDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PROTOCOLINFO *ppi;
	
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SetWindowLong (hwnd, DWL_USER, lParam);
			SetFocus (GetDlgItem(hwnd, IDC_PROT_NAME));
			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
				case IDOK:
					ppi = (PPROTOCOLINFO)GetWindowLong(hwnd, DWL_USER);
					SaveProtInfo(hwnd, ppi);
					// FALL THROUGH !!!
					
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
// void SaveProtInfo(HWND hwnd, PPROTOCOLINFO ppi)
//
//****************************************************************************
void SaveProtInfo(HWND hwnd, PPROTOCOLINFO ppi)
{

	TCHAR szTemp[MAX_PATH];
	BOOL fSuccess;

	// retrieve the protocol name
	//
	GetDlgItemText(hwnd, IDC_PROT_NAME, szTemp, MAX_PATH);
	ppi->szProtName = AllocLPTSTR(lstrlen(szTemp) + 1);
	strcpy(ppi->szProtName, szTemp);
	

	// retrieve the mime type
	//
	GetDlgItemText(hwnd, IDC_PROT_MIME, szTemp, MAX_PATH);
	ppi->szProtMime = AllocLPTSTR(lstrlen(szTemp) + 1);
	strcpy(ppi->szProtMime, szTemp);


	// retrieve the protocol port to use
	//
	ppi->uPortNumber = GetDlgItemInt(hwnd, IDC_PROT_PORT, &fSuccess, FALSE);

}



//****************************************************************************
//
// void CreateProtocolDialog(HWND hwnd)
//
//****************************************************************************
void CreateProtocolDialog(HWND hwnd)
{
	PROTOCOLINFO ProtInfo;
	PROTOCOLINFO *pProtInfo = &ProtInfo;
	HRESULT hr;
	BSTR bstrName, bstrMIME;
	IIlsProtocol *pp;
	ULONG uReqID;
	char szUserName[MAX_NAME];
	PUSERNODE pun;
	POSITION pos;
	LPTSTR psz;


	pProtInfo->szProtName = NULL;
	pProtInfo->szProtMime = NULL;
	pProtInfo->uPortNumber = 0;

	
	// Prompt for the user 
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
		//
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

		// Got the right user, get the protocol details...
		//
		if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_PROTOCOL),
			hwnd, (DLGPROC)ProtocolDlgProc, (LPARAM)pProtInfo) == IDOK)
		{

			if(!MyIsGoodString(pProtInfo->szProtName))
			{
				MyTextOut(TEXT("Protocol name is emtpy - no protocol object created.\r\n"));
				hr = E_FAIL;
				goto MyExit;
			}
			

			// Create the protocol for the user
			//
			LPTSTR_to_BSTR(&bstrName, pProtInfo->szProtName);
			LPTSTR_to_BSTR(&bstrMIME, pProtInfo->szProtMime);
			
			hr = pun->pu->CreateProtocol(bstrName, pProtInfo->uPortNumber, bstrMIME, &pp);

			SysFreeString(bstrName);
			SysFreeString(bstrMIME);
			
			if(SUCCEEDED(hr))
				MyTextOut(TEXT("IIlsUser::CreateProtocol succeeded.\r\n"));
			else
			{
				ErrorMessage(hwnd, TEXT("IIlsUser::CreateProtocol fails."), hr);
				goto MyExit;
			}

			// Add the protocol to the user
			//
			hr = pun->pu->AddProtocol(pp, &uReqID);
			if (SUCCEEDED(hr))
			{
				ILS_STATE pState;
				
				// Adding is sync if the user is not yet registered
				//
				hr = pun->pu->GetState(&pState);
				if(pState == ILS_REGISTERED)
					MyTextOut(TEXT("IIlsUser::AddProtocol(%x) pending.\r\n"), uReqID);
				else if (pState == ILS_UNREGISTERED)
					MyTextOut(TEXT("IIlsUser::AddProtocol returns %s.\r\n"), GetErrorString(hr));
				else
					MyTextOut(TEXT("Hmm.. not sure of user's state on the server.\r\n"));

				// Add this protocol to the list for this user
				// TODO - should really post a message in the callback and handle it in the
				// main wndproc.
				pun->pProtList->AddTail(pp);
			}
			else
				ErrorMessage(hwnd, TEXT("IIlsMain::AddProtocol fails."), hr);
			
		}
		else
		{
			//  User cancelled
			MyTextOut(TEXT("Create Protocol cancelled.\r\n"));
		}
	}
	else
	{
		//  User cancelled
		MyTextOut(TEXT("User list cancelled.\r\n"));
	}
	
	if(pProtInfo->szProtName != NULL)
		FreeLPTSTR(pProtInfo->szProtName);
	if(pProtInfo->szProtMime != NULL)
		FreeLPTSTR(pProtInfo->szProtMime);


	
MyExit:
	return;
}

//****************************************************************************
//
// void DestroyProtocolDialog(HWND hwnd)
//
//****************************************************************************
void DestroyProtocolDialog(HWND hwnd)
{
	PROTOCOLINFO ProtInfo;
	PROTOCOLINFO *pProtInfo = &ProtInfo;
	HRESULT hr;
	BSTR bstrName;
	char szUserName[MAX_NAME];
	PUSERNODE pun;
	POSITION pos;
	LPTSTR psz;

	ENUMPROTINFO epi;
	PENUMPROTINFO pepi = &epi;

	
	// Prompt for the user 
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

		// Got the right user, Enum the protocols...
		//
		pepi->pun = pun;
		
		if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_LIST),
			hwnd, (DLGPROC)ProtoListDlgProc, (LPARAM)pepi) == IDOK)
		{
			// Everything is done in the ProtoListDlgProc function
		}
		else
		{
			//User cancelled
			MyTextOut(TEXT("Destroy Protocol cancelled.\r\n"));
			
		}
	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("User list cancelled.\r\n"));
	}
MyExit:
	return;
}




//****************************************************************************
//
// int ProtoListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog proc that displays the protocols for the 
// current user objects and returns the chosen item.
//
//****************************************************************************
int ProtoListDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hwndList;
	int iIndex;
	HRESULT hr = E_FAIL;
	ULONG uReqID;
	PENUMPROTINFO pepi;
	BSTR bstrName;
	LPTSTR szName;
	POSITION pos;
	IIlsProtocol *pp;

	pp = NULL;
	
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			hwndList = GetDlgItem(hwnd, IDC_LIST);

			pepi = (ENUMPROTINFO *)lParam;

			SetWindowLong (hwnd, DWL_USER, lParam);
			SetWindowText(hwnd, "Protocol List");

			// walk the list of Protocols and add the names to the list box
			pos = pepi->pun->pProtList->GetHeadPosition();
			
			while(pos)
			{
				pp = (IIlsProtocol *)pepi->pun->pProtList->GetFromPosition(pos);
				
				hr = pp->GetStandardAttribute(ILS_STDATTR_PROTOCOL_NAME, &bstrName);
				BSTR_to_LPTSTR(&szName, bstrName);
				SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)szName);
				pepi->pun->pProtList->GetNext(pos);
				FreeLPTSTR(szName);
			}

			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
			{
				TCHAR szTemp[256];
				hwndList = GetDlgItem(hwnd, IDC_LIST);

				// return the name of the user chosen 
				pepi = (ENUMPROTINFO *)GetWindowLong(hwnd, DWL_USER);
				iIndex = SendMessage(hwndList, LB_GETCURSEL, 0,0);
				if(iIndex = -1) 
					iIndex = 0;
				iIndex = SendMessage(hwndList, LB_GETTEXT, iIndex, (LPARAM)szTemp);

				// walk the list of protocols until we find the one selected
				pos = pepi->pun->pProtList->GetHeadPosition();

				while(pos)
				{
					pp = (IIlsProtocol *)pepi->pun->pProtList->GetFromPosition(pos);
			
					hr = pp->GetStandardAttribute(ILS_STDATTR_PROTOCOL_NAME, &bstrName);
					BSTR_to_LPTSTR(&szName, bstrName);
					if(strcmp(szName, szTemp) == 0)
					{
						// TODO - really should post a message in the callback and 
						// handle this in the main wndproc.
						FreeLPTSTR(szName);
						pepi->pun->pProtList->RemoveAt(pos);
						break;
					}
					pepi->pun->pProtList->GetNext(pos);
					FreeLPTSTR(szName);
				}

				hr = pepi->pun->pu->RemoveProtocol(pp, &uReqID);

				if(SUCCEEDED(hr))
				{
					ILS_STATE pState;

					// Removing is sync if the user is not yet registered
					//
					hr = pepi->pun->pu->GetState(&pState);
					if(pState == ILS_REGISTERED)
						MyTextOut(TEXT("IIlsUser::RemoveProtocol(%x) pending.\r\n"), uReqID);
					else if (pState == ILS_UNREGISTERED)
						MyTextOut(TEXT("IIlsUser::RemoveProtocol returns %s.\r\n"), GetErrorString(hr));
					else
						MyTextOut(TEXT("Hmm.. not sure of user's state on the server.\r\n"));  // TODO - better error handling here.
				}
				else
				{
					ErrorMessage(hwnd, TEXT("RemoveProtocol failed"), hr);
				}
				


			}

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
// int DisplayProtocolInfo(HWND hwnd, IIlsProtocol *pp)
//
//
//****************************************************************************
HRESULT DisplayProtocolInfo(HWND hwnd, IIlsProtocol *pp)
{
	HRESULT hr = E_FAIL;
	BSTR bstrTemp = NULL;
	LPTSTR szTemp;
	BOOL pValue;

	MyTextOut(" ---------------\r\n");

	// Print out the protocol information 
	//
	hr = pp->IsWritable(&pValue);
	if (SUCCEEDED(hr))
	{
		if(pValue)
			MyTextOut("Protocol is writable.\r\n");
		else
			MyTextOut("Protocol is read only.\r\n");
	}
	else
	{
		ErrorMessage(hwnd, TEXT("IIlsProtocol::IsWritable fails."), hr);
	}

		
	
	hr = pp->GetStandardAttribute(ILS_STDATTR_PROTOCOL_NAME, &bstrTemp);
	if (SUCCEEDED(hr))
	{
		BSTR_to_LPTSTR(&szTemp, bstrTemp);
		MyTextOut("Protocol name is %s.\r\n", szTemp);
		SysFreeString(bstrTemp);
	}
	else
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);

	hr = pp->GetStandardAttribute(ILS_STDATTR_PROTOCOL_MIME_TYPE, &bstrTemp);
	if (SUCCEEDED(hr))
	{
		BSTR_to_LPTSTR(&szTemp, bstrTemp);
		MyTextOut("Mime Type is %s.\r\n", szTemp);
		SysFreeString(bstrTemp);
	}
	else
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);

	hr = pp->GetStandardAttribute(ILS_STDATTR_PROTOCOL_PORT, &bstrTemp);
	if (SUCCEEDED(hr))
	{
		BSTR_to_LPTSTR(&szTemp, bstrTemp);
		MyTextOut("Port is %s.\r\n", szTemp);
		SysFreeString(bstrTemp);
	}
	else
		ErrorMessage(hwnd, TEXT("IIlsUser::GetStandardAttribute fails."), hr);

	MyTextOut(" ---------------\r\n");

	return hr;
}






//****************************************************************************
//
// int ProtoNameDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog proc that prompts the user for a protocol name
//
//****************************************************************************
int ProtoNameDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LPTSTR pszTemp;
	HRESULT hr = E_FAIL;


	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SetWindowLong (hwnd, DWL_USER, lParam);
			SetFocus(GetDlgItem(hwnd, IDC_USER_NAME));
			SetWindowText(hwnd, "Protocol name");

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

