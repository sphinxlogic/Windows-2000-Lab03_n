//****************************************************************************
//
//  SKIPPY! sample for Microsoft NetMeeting SDK
//
//  File:       filter.cpp
//  Content:    This file contains filter functions.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"

void UpdateControls(HWND hwnd, BOOL fEnable);
void InitFilterDlg(HWND hwnd, PFILTERINFO pfi);
void GetFilterDlg(HWND hwnd, PFILTERINFO pfi);
void AddUserStrings(HWND hwnd);
void AddProtStrings(HWND hwnd);


//****************************************************************************
//
// HRESULT CreateFilterDialog(HWND hwnd, FILTER_TYPE fType)
//
//****************************************************************************
HRESULT CreateFilterDialog(HWND hwnd, FILTER_USAGE fUsage)
{
	HRESULT hr = E_FAIL;
	IIlsFilter *pf, *pf1, *pf2;
	BSTR bstrName = NULL;	

	FILTERINFO fi;
	PFILTERINFO pfi;
	HMENU hMenu;

	pfi = &fi;
	pfi->fUsage = fUsage;
	pfi->fType = ILS_FILTERTYPE_SIMPLE;

	hMenu = GetMenu(hwnd);

	if(DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_DLG_FILTER),
			hwnd, (DLGPROC)FilterDlgProc, (LPARAM)pfi) == IDOK)
	{

		if(pfi->fType == ILS_FILTERTYPE_SIMPLE)
		{

			if(!MyIsGoodString(pfi->szValue1))
			{
				MyTextOut(TEXT("Filter value is empty - no filter object created\r\n"));
				hr = E_FAIL;
				goto MyExit;
			}

		
			MyTextOut(TEXT("Creating simple filter.\r\n"));

			// Filter type is simple, create one
			hr = g_pIls->CreateFilter(ILS_FILTERTYPE_SIMPLE, pfi->fOp1, &pf);
			
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIls::CreateFilter fails."), hr);
				goto MyExit;
			} 

			// Set the attribute name
			//
			hr = pf->SetStandardAttributeName(pfi->attName1);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::SetStandardAttributeName fails."), hr);
				goto MyExit;
			}

			// Set the attribute value
			LPTSTR_to_BSTR(&bstrName, pfi->szValue1);
			hr = pf->SetAttributeValue(bstrName);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::SetAttributeValue fails."), hr);
				goto MyExit;
			}

			MyTextOut(TEXT("Simple filter created.\r\n"));

		}
		else // ILS_FILTERTYPE_COMPOSITE
		{
			if(!MyIsGoodString(pfi->szValue1) || !MyIsGoodString(pfi->szValue2))
			{
				MyTextOut(TEXT("Filter value is empty - no filter object created\r\n"));
				hr = E_FAIL;
				goto MyExit;
			}

			MyTextOut(TEXT("Creating composite filter.\r\n"));

			// Filter type is composite, create three
			//
			// create first simple
			hr = g_pIls->CreateFilter(ILS_FILTERTYPE_SIMPLE, pfi->fOp1, &pf1);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIls::CreateFilter fails."), hr);
				goto MyExit;
			}
			// Set the first attribute name
			//
			hr = pf1->SetStandardAttributeName(pfi->attName1);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::SetStandardAttributeName fails."), hr);
				goto MyExit;
			}

			// Set the first attribute value
			LPTSTR_to_BSTR(&bstrName, pfi->szValue1);
			hr = pf1->SetAttributeValue(bstrName);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::SetAttributeValue fails."), hr);
				goto MyExit;
			}
			
			// create second simple
			hr = g_pIls->CreateFilter(ILS_FILTERTYPE_SIMPLE, pfi->fOp2, &pf2);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIls::CreateFilter fails."), hr);
				goto MyExit;
			}
			
			// Set the second attribute name
			//
			hr = pf2->SetStandardAttributeName(pfi->attName2);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::SetStandardAttributeName fails."), hr);
				goto MyExit;
			}

			// Set the second attribute value
			LPTSTR_to_BSTR(&bstrName, pfi->szValue2);
			hr = pf2->SetAttributeValue(bstrName);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::SetAttributeValue fails."), hr);
				goto MyExit;
			}


			// Create the composite filter
			hr = g_pIls->CreateFilter(ILS_FILTERTYPE_COMPOSITE, pfi->fOpComp, &pf);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIls::CreateFilter fails."), hr);
				goto MyExit;
			}

			// add filter one
			hr = pf->AddSubFilter(pf1);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::AddSubFilter fails."), hr);
				goto MyExit;
			}

			// add filter two
			hr = pf->AddSubFilter(pf2);
			if(FAILED(hr))
			{
				ErrorMessage(hwnd, TEXT("IIlsFilter::AddSubFilter fails."), hr);
				goto MyExit;
			}

			MyTextOut(TEXT("Composite filter created.\r\n"));

		}

		// Set the global filter pointers
		// destroy existing ones, only allow one at a time
		if(fUsage == USERFILTER)
		{
			if(g_pUserFilter)
				g_pUserFilter->Release();
				
			g_pUserFilter = pf;
			EnableMenuItem(hMenu, IDM_DESTROY_USERFILTER, MF_BYCOMMAND | MF_ENABLED);
		}
		else if(fUsage == PROTFILTER)
		{
			if(g_pProtFilter)
				g_pProtFilter->Release();
				
			g_pProtFilter = pf;
			EnableMenuItem(hMenu, IDM_DESTROY_PROTFILTER, MF_BYCOMMAND | MF_ENABLED);
		}
		else
			ErrorMessage(hwnd, TEXT("filter usage is indeterminate.\r\n"), E_FAIL);

	}
	else
	{
		//User cancelled
		MyTextOut(TEXT("Create Filter cancelled.\r\n"));
	}

MyExit:

	// Cleanup
	//
	if(bstrName)
		SysFreeString(bstrName);
		
	return hr;
}


//****************************************************************************
//
// int FilterDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//
// This function is the dialog proc that displays the current user objects
// and returns the chosen item.
//
//****************************************************************************
int FilterDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PFILTERINFO pfi;

	switch (msg)
	{
		case WM_INITDIALOG:
		{
			SetWindowLong (hwnd, DWL_USER, lParam);
			InitFilterDlg(hwnd, (PFILTERINFO)lParam);
			break;
		}

		case WM_COMMAND:
		{
			switch (GET_WM_COMMAND_ID(wParam, lParam))
			{
			case IDOK:
				// return the filter info
				pfi = (FILTERINFO *)GetWindowLong(hwnd, DWL_USER);
				GetFilterDlg(hwnd, pfi);

				// FALL THROUGH !!!
				//
			case IDCANCEL:
				EndDialog(hwnd, GET_WM_COMMAND_ID(wParam, lParam));
				break;

			case IDC_SIMPLE:
			{
				// Turn on/off dialog controls
				//
				UpdateControls(hwnd, FALSE);
				break;
			}
			case IDC_COMPOSITE:
			{
				// Turn on/off dialog controls
				//
				UpdateControls(hwnd, TRUE);
				break;
			}
			
			default:
				break;
			};
			break;
		}

		case WM_ENABLE:
			return 1;
			break;

		default:
			break;
	};

	return 0;
}



//****************************************************************************
//
// int InitFilterDlg (HWND hwnd, PFILTERINFO pfi)
//
//****************************************************************************
void InitFilterDlg(HWND hwnd, PFILTERINFO pfi)
{

	// select the correct radio buttons
	//
	CheckRadioButton( hwnd, IDC_SIMPLE, IDC_COMPOSITE, IDC_SIMPLE);
	CheckRadioButton( hwnd, IDC_OP_EQUAL1, IDC_OP_EXIST1, IDC_OP_EQUAL1);
	CheckRadioButton( hwnd, IDC_OP_EQUAL2, IDC_OP_EXIST2, IDC_OP_EQUAL2);
	CheckRadioButton( hwnd, IDC_AND, IDC_NOT, IDC_AND);

	if(pfi->fUsage == USERFILTER)
	{
		AddUserStrings(GetDlgItem(hwnd, IDC_ATT_LIST1));
		AddUserStrings(GetDlgItem(hwnd, IDC_ATT_LIST2));
	}
	else // PROTFILTER
	{
		AddProtStrings(GetDlgItem(hwnd, IDC_ATT_LIST1));
		AddProtStrings(GetDlgItem(hwnd, IDC_ATT_LIST2));
	}


	// send a message to disable controls
	//
	SendMessage(hwnd, WM_COMMAND, IDC_SIMPLE, 0);
}


//****************************************************************************
//
// int UpdateControls (HWND hwnd, BOOL fEnable)
//
//****************************************************************************
void UpdateControls(HWND hwnd, BOOL fEnable)
{
	EnableWindow(GetDlgItem(hwnd, IDC_COMP_FRAME), fEnable);
	
	EnableWindow(GetDlgItem(hwnd, IDC_AND), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_NOT), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_OR), fEnable);
	
	EnableWindow(GetDlgItem(hwnd, IDC_STD_TXT2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_ATT_LIST2), fEnable);

	EnableWindow(GetDlgItem(hwnd, IDC_ATT_TXT2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_VALUE2), fEnable);

	EnableWindow(GetDlgItem(hwnd, IDC_FIL_OP2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_OP_EQUAL2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_OP_APPROX2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_OP_LESSTHAN2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_OP_GREATERTHAN2), fEnable);
	EnableWindow(GetDlgItem(hwnd, IDC_OP_EXIST2), fEnable);
}

//****************************************************************************
//
// int GetFilterDlg(HWND hwnd, PFILTERINFO pfi)
//
// Fill in the FILTERINFO structure
//
//****************************************************************************
void GetFilterDlg(HWND hwnd, PFILTERINFO pfi)
{
	TCHAR szTemp[MAX_NAME];
	HWND hwndCombo;

	// Get standard attribute name for first simple filter
	//
	hwndCombo = GetDlgItem(hwnd, IDC_ATT_LIST1);
	pfi->attName1 = (ILS_STD_ATTR_NAME)(SendMessage(hwndCombo, CB_GETCURSEL, 0, 0) + 1);

	// Get standard attribute value for first simple filter
	//
	GetDlgItemText(hwnd, IDC_VALUE1, szTemp, MAX_NAME);
	pfi->szValue1 = AllocLPTSTR(lstrlen(szTemp) + 1);
	strcpy(pfi->szValue1, szTemp);
	

	// Get standard attribute name for second simple filter
	//
	hwndCombo = GetDlgItem(hwnd, IDC_ATT_LIST2);
	pfi->attName2 = (ILS_STD_ATTR_NAME)(SendMessage(hwnd, CB_GETCURSEL, 0, 0) + 1);

	// Get standard attribute value for second simple filter
	//
	GetDlgItemText(hwnd, IDC_VALUE2, szTemp, MAX_NAME);
	pfi->szValue2 = AllocLPTSTR(lstrlen(szTemp) + 1);
	strcpy(pfi->szValue2, szTemp);


	// some fancy arithmetic to calculate filter operations
	//
	pfi->fOp1 = (ILS_FILTER_OP)((int)ILS_FILTEROP_EQUAL + GetRadioButton(hwnd, IDC_OP_EQUAL1, IDC_OP_EXIST1) - IDC_OP_EQUAL1);
	pfi->fOp2 = (ILS_FILTER_OP)((int)ILS_FILTEROP_EQUAL + GetRadioButton(hwnd, IDC_OP_EQUAL2, IDC_OP_EXIST2) - IDC_OP_EQUAL2);

	pfi->fOpComp = (ILS_FILTER_OP)((int)ILS_FILTEROP_AND + GetRadioButton(hwnd, IDC_AND, IDC_NOT) - IDC_AND);

	pfi->fType = ((GetRadioButton(hwnd, IDC_SIMPLE, IDC_COMPOSITE) == IDC_SIMPLE) ? ILS_FILTERTYPE_SIMPLE : ILS_FILTERTYPE_COMPOSITE);
	
}



//****************************************************************************
//
// void AddUserStrings(HWND hwnd)
//
//****************************************************************************
void AddUserStrings(HWND hwnd)
{
	// Add USER atttibute strings to the combo box
	//
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"USER_ID");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"IP_ADDRESS");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"EMAIL_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"FIRST_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"LAST_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"CITY_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"COUNTRY_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"COMMENT");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"FLAGS");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"APP_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"APP_MIME_TYPE");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"APP_GUID");

	// set default
	SendMessage(hwnd, CB_SETCURSEL, 0, 0);


}


//****************************************************************************
//
// void AddProtStrings(HWND hwnd)
//
//****************************************************************************
void AddProtStrings(HWND hwnd)
{
	// Add PROTOCOL atttibute strings to the combo box
	//
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"PROTOCOL_NAME");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"PROTOCOL_MIME_TYPE");
	SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)"PROTOCOL_PORT");

	// set default
	SendMessage(hwnd, CB_SETCURSEL, 0, 0);


}


//****************************************************************************
//
// void DestroyFilter(HWND hwnd, FILTER_TYPE fType)
//
//  Free the global filters
//
//****************************************************************************
HRESULT DestroyFilter(HWND hwnd, FILTER_USAGE fUsage)
{
	HMENU hMenu;

	hMenu = GetMenu(hwnd);

	if(fUsage == USERFILTER)
	{
		if(g_pUserFilter)
		{
			g_pUserFilter->Release();
			g_pUserFilter = NULL;
			EnableMenuItem(hMenu, IDM_DESTROY_USERFILTER, MF_BYCOMMAND | MF_GRAYED);
			MyTextOut(TEXT("User filter destroyed.\r\n"));
		}
		
	}
	else if(fUsage == PROTFILTER)
	{
		if(g_pProtFilter)
		{
			g_pProtFilter->Release();
			g_pProtFilter = NULL;
			EnableMenuItem(hMenu, IDM_DESTROY_PROTFILTER, MF_BYCOMMAND | MF_GRAYED);
			MyTextOut(TEXT("Protocol filter destroyed.\r\n"));
		}
	}
	else
		ErrorMessage(hwnd, TEXT("DestroyFilter: usage is indeterminate.\r\n"), E_FAIL);

	return S_OK;

}

