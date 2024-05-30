/******************************************************************************\
********************************************************************************
* Filename: wmain.cpp
*
* Description: Contains implementation of WinMain and other stuff.
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>
#include <comdef.h>
#include "resource.h"

// Use the VC5 import feature to pull in the typelib; note that we could also use
// the supplied header (mtxadmin.h, mtxadmin_i.c) but this way we get smart COM pointers.
#import ".\mts\mtxadmin.dll"
using namespace MTSAdmin;

// Globals
HINSTANCE g_hInstance;
HWND g_hDlg;
HWND g_hwndStatusMsgEB;
_bstr_t  g_bstrDllPath;
const DWORD MAX_STRING_LEN = 255;


///////////////////////////////////////////////////////////////////
//   Appends a string to the bottom of the display buffer.
void Print(LPTSTR tszMsg)
{
	TCHAR tszBuffer[MAX_STRING_LEN];
	_stprintf(tszBuffer, _T("%s\r\n"), tszMsg);
	SendMessage(g_hwndStatusMsgEB, EM_SETSEL,(WPARAM) -1, (LPARAM) -1) ;
	SendMessage(g_hwndStatusMsgEB, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) tszBuffer) ;
}

///////////////////////////////////////////////////////////////////
//  Clears the contents of the display buffer
void ClearDisplay()
{
	SendMessage(g_hwndStatusMsgEB, EM_SETSEL,(WPARAM) 0, (LPARAM) -1) ;
	SendMessage(g_hwndStatusMsgEB, EM_REPLACESEL, (WPARAM) FALSE, (LPARAM) _T("")) ;
}

///////////////////////////////////////////////////////////////////
//  Prompts the user for a dll to install.
BOOL GetDllPathFromUser()
{
	OPENFILENAME ofn;       // common dialog box structure
	TCHAR tszFile[260];       // buffer for filename
	
	_tcscpy(tszFile, _T(""));

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hDlg;
	ofn.lpstrFile = tszFile;
	ofn.nMaxFile = sizeof(tszFile);
	ofn.lpstrFilter = _T("All\0*.*");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = _T("\\");
	ofn.lpstrTitle = _T("Choose a component dll to install");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;

	// Display the Open dialog box and save filename if they press okay
	if (!GetOpenFileName(&ofn)) 
		return FALSE;
	
	g_bstrDllPath = tszFile;
	return TRUE;
}

///////////////////////////////////////////////////////////////////
//  Installs the file pointed to by g_bstrDllPath into the SDKDemo
//    package, which we assume already exists.
BOOL InstallFileIntoPackage()
{
	_bstr_t bstrT, bstrT2, bstrT3;
	long lPkgCount, lCompCount, i;
	_variant_t varT;
	TCHAR tszBuf[MAX_STRING_LEN];
	try
	{
		ICatalogCollectionPtr pPkgCollection(NULL);
		ICatalogCollectionPtr pCompCollection(NULL);
		IComponentUtilPtr pCompUtil(NULL);
		ICatalogObjectPtr pCatObject(NULL);
		
		// Create instance of the catalog object
		ICatalogPtr pCatalog(__uuidof(Catalog));

		// Needed for COM+ Version
		//bstrT = (LPTSTR)NULL;
		//pCatalog->Connect(bstrT);

		// Get the Packages collection
		bstrT = "Packages";
		pPkgCollection = pCatalog->GetCollection(bstrT);
		
		// Populate it
		pPkgCollection->Populate();

		// Get the "SDK Demo" package
		Print(_T("Getting the ""SDK Demo"" package...."));
		lPkgCount = pPkgCollection->GetCount();
		bstrT2 = "SDK Demo";
		for (i = (lPkgCount-1); i >= 0 ; i--)
		{
			pCatObject = pPkgCollection->GetItem(i);

			bstrT = pCatObject->GetName();
			if (bstrT == bstrT2)
			{
				// Found it
				break;
			}
		}

		// Install the specified file name
		bstrT = "ComponentsInPackage";
		bstrT2 = "";
		bstrT3 = "";

		varT = pCatObject->GetKey();
		
		// Get the "ComponentsInPackage" collection.
		pCompCollection = pPkgCollection->GetCollection(bstrT, varT);
		pCompCollection->Populate();
		pCompUtil = pCompCollection->GetUtilInterface();

		Print(_T("Installing your specified component dll..."));
		pCompUtil->InstallComponent(g_bstrDllPath, bstrT2, bstrT3);

		// Now save, then repopulate the component collection with the just added components
		pCompCollection->SaveChanges();
		pCompCollection->Populate();

		// Now we are going to set the transaction property to "Required" for each component
		// in the  'SDK Demo' package.
		Print(_T("About to set the transaction property for each component..."));
		lCompCount = pCompCollection->GetCount();
		for (i = 0; i < lCompCount; i++)
		{
			pCatObject = pCompCollection->GetItem(i);
			bstrT = "Transaction";
			bstrT2 = "Required";
			varT = bstrT2;
			pCatObject->PutValue(bstrT, varT);
		}
		pCompCollection->SaveChanges();
		pCompCollection->Populate();

		Print(_T("Enumerating each of your components"));
		bstrT = "ProgID";
		for (i = 0; i < lCompCount; i++)
		{
			pCatObject = pCompCollection->GetItem(i);
			varT = pCatObject->GetValue(bstrT);
			bstrT2 = varT;
			_stprintf(tszBuf, _T("  %s"), (char*)bstrT2);
			Print(tszBuf);
		}
	}
	catch (...)
	{
		// pop an error message and return
		return FALSE;
	}
	return TRUE;
} // InstallFileIntoPackage

///////////////////////////////////////////////////////////////////
//  Deletes any and all local packages named "SDK Demo".
BOOL DeleteSDKDemoPackage()
{
	_bstr_t bstrT, bstrT2;
	long    lPkgCount;
	long   i;

	try
	{
		ICatalogCollectionPtr pPkgCollection(NULL);
		ICatalogPtr pCatalog(__uuidof(Catalog));
		ICatalogObjectPtr pCatObject(NULL);

		// Needed for COM+ Version
		//bstrT = (LPTSTR)NULL;
		//pCatalog->Connect(bstrT);

		// Get the Packages collection
		Print(_T("Getting the Packages collection"));
		bstrT = "Packages";
		pPkgCollection = pCatalog->GetCollection(bstrT);
		
		// Populate it
		pPkgCollection->Populate();

		// Loop through all packages in the collection; if we find an
		//   "SDK Demo" package, remove it.
		lPkgCount = pPkgCollection->GetCount();
		bstrT2 = "SDK Demo";

		Print(_T("Searching for the SDK Demo package, if it exists"));
		for (i = (lPkgCount-1); i >= 0 ; i--)
		{
			pCatObject = pPkgCollection->GetItem(i);

			bstrT = pCatObject->GetName();
			if (bstrT == bstrT2)
			{
				Print(_T("Deleting the existing ""SDK Demo"" package now"));
				pPkgCollection->Remove(i);
			}
		}

		// Save any changes we made
		pPkgCollection->SaveChanges();
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////
//  Creates a local package named "SDKDemo"; assumes that a package
//    of this name does not already exist.
BOOL CreateSDKDemoPackage()
{
	_bstr_t bstrT, bstrT2;
	_variant_t varT;

	try
	{
		ICatalogCollectionPtr pPkgCollection(NULL);
		ICatalogPtr pCatalog(__uuidof(Catalog));
		ICatalogObjectPtr pCatObject(NULL);

		// Needed for COM+ Version
		//bstrT = (LPTSTR)NULL;
		//pCatalog->Connect(bstrT);

		// Get the Packages collection
		Print(_T("Getting the Packages collection"));
		bstrT = "Packages";
		pPkgCollection = pCatalog->GetCollection(bstrT);
		
		// Populate it
		pPkgCollection->Populate();

		// Create a new package object
		Print(_T("Adding a new package object"));
		pCatObject = pPkgCollection->Add();
		
		// Set its name property to "SDK Demo"
		Print(_T("Changing its name to ""SDK Demo"""));
		bstrT = "Name";
		bstrT2 = "SDK Demo";
		varT = bstrT2;
		pCatObject->PutValue(bstrT, varT);
	
		// Set its security property to off
		Print(_T("Changing its security setting to off"));
		bstrT = "SecurityEnabled";
		bstrT2 = "N";
		varT = bstrT2;
		pCatObject->PutValue(bstrT, varT);

		// Persist our changes
		pPkgCollection->SaveChanges();
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////
//  
BOOL InstallDllIntoSDKDemoPackage()
{
	BOOL bResult;

	// Delete the SDKDemo package if it exists
	if (!DeleteSDKDemoPackage())
		return FALSE;

	if (!CreateSDKDemoPackage())
		return FALSE;

	bResult = InstallFileIntoPackage();
	if (bResult)
	{
		Print(_T("Installation of your components was successful"));
	}
	else
	{	
		Print(_T("Installation of your components failed"));
	}
	return bResult;
} // InstallDllIntoSDKDemoPackage

///////////////////////////////////////////////////////////////////
//   Command handler from the wndproc.
void InstallDll()
{
	ClearDisplay();

	// First get component dll to install
	if (!GetDllPathFromUser())
		return;

	// Install dll 
	InstallDllIntoSDKDemoPackage();

	// Done
	return;
} // InstallDLL

///////////////////////////////////////////////////////////////////
//
BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	g_hwndStatusMsgEB = GetDlgItem(hwnd,IDC_STATUSMSGBOX);
	g_hDlg = hwnd;
	return TRUE;
}  // Dlg_OnInitDialog

///////////////////////////////////////////////////////////////////
//
BOOL Dlg_OnDestroy(HWND hwnd)
{
	return TRUE;
}  // Dlg_OnDestroy

///////////////////////////////////////////////////////////////////
//
void Dlg_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 1);
}  // Dlg_OnClose

///////////////////////////////////////////////////////////////////
//
void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{	
	switch(id)
	{
	case IDOK:
		break;
	case IDCANCEL:
		break;
	case IDC_INSTALLDLL:
		InstallDll();
		break;
	default:
		break;
	}
	return;
}  // Dlg_OnCommand

///////////////////////////////////////////////////////////////////
//
BOOL CALLBACK Dlg_Proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL fProcessed = TRUE;

	switch(uMsg)
	{
		HANDLE_MSG(hDlg, WM_INITDIALOG, Dlg_OnInitDialog);
		HANDLE_MSG(hDlg, WM_CLOSE, Dlg_OnClose);
		HANDLE_MSG(hDlg, WM_DESTROY, Dlg_OnDestroy);
		HANDLE_MSG(hDlg, WM_COMMAND, Dlg_OnCommand);
	default:
		fProcessed=FALSE;
		break;
	}
	return fProcessed;
}  // Dlg_Proc	

///////////////////////////////////////////////////////////////////
//   Beginning of program execution
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{	
	HRESULT hr;
	int iResult;

	InitCommonControls();
	g_hInstance = hInstance;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return -1;

	iResult = DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, Dlg_Proc);

	CoUninitialize();
	return iResult;
}  // WinMain
