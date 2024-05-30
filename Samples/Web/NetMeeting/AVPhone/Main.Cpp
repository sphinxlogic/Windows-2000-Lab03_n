//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       MAIN.CPP
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



#include "precomp.h"

//*******************
//GLOBALS
//*******************

#define MAX_SZ 200

HINSTANCE ghInst;

//*******************
//FUNCTION DECLARATIONS
//*******************

BOOL CALLBACK MainDlgProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************************************************************************
//
//    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//    PURPOSE: calls initialization function
//
//    COMMENTS:
//
//        Windows recognizes this function by name as the initial entry point 
//        for the program.  This function calls the application initialization 
//        routine.  
//
//****************************************************************************

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst, LPSTR szCmdLine, INT nCmdShow)
{
	ghInst=hInst;

	CoInitialize(NULL);
	DialogBox(hInst,MAKEINTRESOURCE(IDD_MAIN),NULL,(DLGPROC)MainDlgProc);
	CoUninitialize();
	return 0;

}

//****************************************************************************
//
// BOOL CALLBACK MainDlgProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
//
// This function is called when the Main Dialog initializes.  It sets up 
// the initial interface pointers and updates the dialog accordingly
//
//****************************************************************************


BOOL CALLBACK MainDlgProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static Conf *pConf;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		pConf=new Conf(hWnd);
		if (FAILED(pConf->Initialize()))
		{
			MessageBox(NULL,"NetMeeting may not be installed","Initialization Failure",MB_OK);
			EndDialog(hWnd,0);
			return FALSE;
		}
		return TRUE;
	
	case WM_CLOSE:
		
		// Hangup if in a call
		if (pConf->InConnection())
			pConf->HangUp();

		pConf->Uninitialize();
		delete pConf;
		EndDialog(hWnd,0);
		return TRUE;
	
	case WM_CONNECTING:
	case WM_CONNECTED:

		// Message from Conf object that a user is connected
		SetDlgItemText(hWnd,IDC_CALLHANGUP,"H&ang Up");
		return TRUE;
	
	case WM_DISCONNECTED:

		// Message from Conf object that a user disconnected or rejected call
		SetDlgItemText(hWnd,IDC_CALLHANGUP,"C&all");
		return TRUE;
	
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CALLHANGUP:

				// If not in a call, then call szMachineName, otherwise hang up.
				if (!pConf->InConnection()) 
				{
					char szMachineName[MAX_SZ];
					GetDlgItemText(hWnd,IDC_MACHINENAME,szMachineName,MAX_SZ);
					pConf->Call(szMachineName);
					return TRUE;
				}
				else
				{
					pConf->HangUp();
					return TRUE;
				}

			case ID_FILE_EXIT:
				EndDialog(hWnd,0);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

