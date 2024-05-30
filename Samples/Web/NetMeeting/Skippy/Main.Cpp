//****************************************************************************
//
//  SKIPPY! sample app for Microsoft NetMeeting SDK
//
//  File:       main.cpp
//  Content:    This file contains the application's WinMain and init 
//              functions. GUID.
//
//  Copyright (c) Microsoft Corporation 1997
//  All rights reserved
//
//****************************************************************************

#include "ilstest.h"

#define INC_OLE2
#include <initguid.h>
#include <olectl.h>
#include <ilsguid.h>
#include "appguid.h"

#include "notify.h"


//****************************************************************************
// Global parameters
//****************************************************************************

HINSTANCE          ghInstance = NULL;
LPILS_MAIN         g_pIls = NULL;
IConnectionPoint   *g_pcnp = NULL;
CIlsNotify         *g_pIlsNotify = NULL;
HWND               g_hwndMain = NULL;
CHAR               g_szServer[MAX_PATH];
IIlsServer         *g_pServer = NULL;
IIlsFilter         *g_pProtFilter = NULL;
IIlsFilter         *g_pUserFilter = NULL;
COBLIST            *g_pServerList;
COBLIST            *g_pUserList;
GUID               g_GUID;

#define WM_START   (WM_USER+10)

//****************************************************************************
// Global constant strings
//****************************************************************************

const TCHAR g_szOptions[]   = TEXT("Options");
const TCHAR g_szPosition[]  = TEXT("Placement");
const TCHAR g_szIni[]       = TEXT("skippy.ini");
const TCHAR g_szAppID[]   = TEXT("ms-netmeeting"); // Use this string so NM can see you on the server
const TCHAR g_szProtID[]   = TEXT("h323"); // Default to this protocol ID for now

const TCHAR g_szExe[]       = TEXT("skippy.exe");


//****************************************************************************
// Function prototypes
//****************************************************************************

long CALLBACK App_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//****************************************************************************
//
// HRESULT OnIlsAdviseUnadvise(HWND hwnd, BOOL fAdvise)
//
// This function enables/disables the Ils object's notifications.
//
//****************************************************************************

HRESULT OnIlsAdviseUnadvise(HWND hwnd, BOOL fAdvise)
{
	HRESULT hr;

	if (fAdvise)
	{
		DWORD dwCookie;

		g_pIlsNotify = new CIlsNotify (hwnd);
		hr = g_pcnp->Advise((IUnknown *)g_pIlsNotify, &dwCookie);

		if (hr == S_OK)
		{
			g_pIlsNotify->AddRef();
			g_pIlsNotify->SetCookie(dwCookie);
		};
	}
	else
	{
		hr = g_pcnp->Unadvise(g_pIlsNotify->GetCookie());

		if (hr == S_OK)
		{
			g_pIlsNotify->Release();
			g_pIlsNotify = NULL;
		};
	};
	return hr;
}

//****************************************************************************
//
// void InitConnectableObject(HWND hwnd)
//
// This function initializes the Ils connectable object.
//
//****************************************************************************

void InitConnectableObject(HWND hwnd)
{
	IConnectionPointContainer *pcnpcnt;
	HRESULT hr;

	// Get the ConnectionPointContainer
	//
	hr = g_pIls->QueryInterface(IID_IConnectionPointContainer, (void**)&pcnpcnt);
	if (hr != S_OK)
	{
		ErrorMessage(NULL, TEXT("Cannot query IID_IConnectionPointContainer: returns "),
					hr);
	}
	else
	{
		IEnumConnectionPoints *pEnum;

		// Instead of an easy thing as follows
		// hr = pcnpcnt->FindConnectionPoint(IID_IIlsNotify, &g_pcnp);
		// Let's do the hard thing through enumeration
		//
		hr = pcnpcnt->EnumConnectionPoints(&pEnum);
		if (hr != S_OK)
		{
			ErrorMessage(NULL, TEXT("Cannot enumerate ConnectionPoint: returns "),
						hr);                
		}
		else
		{
			IConnectionPoint *pcnp;
			ULONG            cFetched;

			while(pEnum->Next(1, &pcnp, &cFetched) == S_OK)
			{
				IID riid;

				if ((pcnp->GetConnectionInterface(&riid) == S_OK) &&
					(riid == IID_IIlsNotify))
				{
					g_pcnp = pcnp;
					OnIlsAdviseUnadvise(hwnd, TRUE);
					break;
				};
				pcnp->Release();
			};

			if (g_pcnp == NULL)
			{
				ErrorMessage(NULL, TEXT("Cannot find ConnectionPoint: returns "),
							hr);                
			};

			pEnum->Release();
		};
		pcnpcnt->Release();
	};
}

//****************************************************************************
//
// BOOL InitAppInstance (HINSTANCE hInstance)
//
// This function initializes this instance of the application.
//
//****************************************************************************

BOOL InitAppInstance (HINSTANCE hInstance)
{
	HRESULT hr;
	LPCLASSFACTORY pcf;
	BOOL    fRet = FALSE;

	// Remember the application instance
	//
	ghInstance = hInstance;

	// Create the main window with a dialog template
	//
	InitCommonControls();
	g_hwndMain = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DLG_APP),
					NULL, (DLGPROC)App_WndProc);

	if (g_hwndMain == NULL)
		return FALSE;

	// Create linked lists for users and servers
	//
	g_pUserList = new COBLIST;
	g_pServerList = new COBLIST;

	// Do the OLE thing
	//
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		ErrorMessage(NULL, TEXT("CoInitialize"), hr);
		return FALSE;
	}

	// Notify the system we want to use the Ils services
	// by creating a Ils object
	//
	hr = CoGetClassObject(CLSID_InternetLocationServices,
							CLSCTX_INPROC_SERVER,
							NULL,
							IID_IClassFactory,
							(void**)&pcf);
	if (FAILED(hr))
	{
		ErrorMessage(NULL, TEXT("CoGetClassObject"), hr);
	}
	else
	{
		// Get the IlsMain object
		//
		hr = pcf->CreateInstance(NULL, IID_IIlsMain, (void**)&g_pIls);
		if (hr != S_OK)
		{
			ErrorMessage(NULL, TEXT("Cannot create a IlsMain object: returns "), hr);
		}
		else
		{
			// Connect to the IlsMain object
			//
			InitConnectableObject(g_hwndMain);

			// Determine how to start the application and
			// start the application
			//
			PostMessage(g_hwndMain, WM_START, 0, 0);
			fRet = TRUE;
		};

		pcf->Release();
	};

	return fRet;
}

//****************************************************************************
//
// void DeinitAppInstance (HINSTANCE hInstance)
//
// This function initializes this instance of the application.
//
//****************************************************************************

void DeinitAppInstance(HINSTANCE hInstance)
{
	// Unregister all the users we created
	UnregisterAllUsers(g_hwndMain);
	
	// Remove the connection points
	//
	if (g_pcnp != NULL)
	{
		OnIlsAdviseUnadvise(g_hwndMain, FALSE);
		g_pcnp->Release();
	};

	// Free the main interface
	//
	if (g_pIls != NULL)
	{
		g_pIls->Uninitialize();
		g_pIls->Release();
	};
	CoUninitialize();

	// clear the user and server lists
	//
	g_pServerList->EmptyList();
	g_pUserList->EmptyList();

	delete g_pUserList;
	delete g_pServerList;

	// Destroy the main window
	DestroyWindow(g_hwndMain);

	return;
}

//****************************************************************************
//
//    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//    PURPOSE: calls initialization function, processes message loop
//
//    COMMENTS:
//
//        Windows recognizes this function by name as the initial entry point 
//        for the program.  This function calls the application initialization 
//        routine, if no other instance of the program is running, and always 
//        calls the instance initialization routine.  It then executes a message 
//        retrieval and dispatch loop that is the top-level control structure 
//        for the remainder of execution.  The loop is terminated when a WM_QUIT 
//        message is received, at which time this function exits the application 
//        instance by returning the value passed by PostQuitMessage(). 
//
//        If this function must abort before entering the message loop, it 
//        returns the conventional value NULL.  
//
//****************************************************************************

int PASCAL WinMain(
HINSTANCE hInstance,        /* current instance     */
HINSTANCE hPrevInstance,    /* previous instance    */
LPSTR     lpCmdLine,        /* command line         */
int       nCmdShow)         /* show-window type (open/icon)  */
{
	MSG     msg;            /* message              */

	if (!InitAppInstance(hInstance)) /* Initialize shared things         */
		return (FALSE);              /* Exits if unable to initialize    */

	/* Acquire and dispatch messages until a WM_QUIT message is received.*/

	while (GetMessage(&msg,    /* message structure                      */
		NULL,                  /* handle of window receiving the message */
		0,                     /* lowest message to examine              */
		0))                    /* highest message to examine             */
	{
		if (!IsDialogMessage(g_hwndMain, &msg))
		{
			TranslateMessage(&msg);    /* Translates virtual key codes       */
			DispatchMessage(&msg);     /* Dispatches message to window       */
		};
	}

	DeinitAppInstance(hInstance);
	return (msg.wParam);       /* Returns the value from PostQuitMessage */
}

//****************************************************************************
//
// void InitializeWindow(HWND hwnd)
//
// This function is called when the main window is initialized.
//
//****************************************************************************

void InitializeWindow(HWND hwnd)
{
	HICON hIcon;
	HMENU hMenu;
	WINDOWPLACEMENT wp;

	// Initialize application icon
	//
	hIcon = LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_APP_ICON));    
	SendMessage(hwnd, WM_SETICON, TRUE, (LPARAM)hIcon);
	SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM)hIcon);

	// Get window placement
	//
	if (GetPrivateProfileStruct(g_szOptions, g_szPosition,
								(LPVOID)&wp, sizeof(wp), g_szIni))
	{
		SetWindowPlacement(hwnd, &wp);
	};

	// Turn on/off the correct menu items
	hMenu = GetMenu(hwnd);
	EnableMenuItem(hMenu, IDM_DESTROYUSER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_DESTROYSERVER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_ENUMUSERS, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_ENUMUSERNAMES, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_REGISTERUSER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_UNREGISTERUSER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_CLONEUSER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_MODIFYUSER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_GETUSERINFO, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_CREATE_PROT, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_DESTROY_PROT, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_DESTROY_PROTFILTER, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(hMenu, IDM_DESTROY_USERFILTER, MF_BYCOMMAND | MF_GRAYED);
	
	return;
}

//****************************************************************************
//
// void TerminateWindow(HWND hwnd)
//
// This function is called when the main window is terminated.
//
//****************************************************************************

void TerminateWindow(HWND hwnd)
{
	WINDOWPLACEMENT wp;

	// Remember the last position
	//
	wp.length = sizeof(wp);
	if (GetWindowPlacement(hwnd, &wp))
	{
		WritePrivateProfileStruct(g_szOptions, g_szPosition,
								(LPVOID)&wp, sizeof(wp), g_szIni);
	};
	PostQuitMessage(0);
	return;
}

//****************************************************************************
//
// long CALLBACK App_WndProc(HWND hwnd, UINT message,
//                           WPARAM wParam, LPARAM lParam)
//
// This function is the main window procedure.
//
//****************************************************************************

long CALLBACK App_WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int iCommand;

	switch (message)
	{
		case WM_INITDIALOG:
			InitializeWindow(hwnd);
			break;

		case WM_CLOSE:
			TerminateWindow(hwnd);
			break;

		case WM_START:
		{
			HRESULT hr;

			// Initialize the Ils object
			//
			hr = g_pIls->Initialize();
			if (FAILED(hr))
				ErrorMessage(NULL, TEXT("IIls::Initialize returns"), hr);
		}

		case WM_COMMAND:
		{
			// Process the menu selections
			//
			iCommand = GET_WM_COMMAND_ID(wParam, lParam);

			switch (iCommand)
			{
				case IDM_EXIT:
					TerminateWindow(hwnd);
					break;
				
				case IDM_NEWUSER:
					NewUserDialog(hwnd);
					break;

				case IDM_MODIFYUSER:
					ModifyUserDialog(hwnd);
					break;

				case IDM_CLONEUSER:
					CloneUserDialog(hwnd);
					break;

				case IDM_DESTROYUSER:
					RemoveUserDialog(hwnd);
					break;

				case IDM_CREATESERVER:
					NewServerDialog(hwnd);
					break;

				case IDM_DESTROYSERVER:
					RemoveServerDialog(hwnd);
					break;

				case IDM_ENUMUSERS:
					EnumUsers(hwnd, FALSE);
					break;

				case IDM_ENUMUSERNAMES:
					EnumUsers(hwnd, TRUE);
					break;

				case IDM_REGISTERUSER:
					RegUnregUserDialog(hwnd, TRUE);
					break;

				case IDM_UNREGISTERUSER:
					RegUnregUserDialog(hwnd, FALSE);
					break;

				case IDM_GETUSERINFO:
					GetUserInfoDialog(hwnd);
					break;

				case IDM_USER_FILTER:
					CreateFilterDialog(hwnd, USERFILTER);
					break;
					
				case IDM_PROTOCOL_FILTER:
					CreateFilterDialog(hwnd, PROTFILTER);
					break;

				case IDM_DESTROY_USERFILTER:
					DestroyFilter(hwnd, USERFILTER);
					break;

				case IDM_DESTROY_PROTFILTER:
					DestroyFilter(hwnd, PROTFILTER);
					break;

				case IDM_CREATE_PROT:
					CreateProtocolDialog(hwnd);
					break;

				case IDM_DESTROY_PROT:
					DestroyProtocolDialog(hwnd);
					break;

				case IDM_ABOUT:
					DisplayAboutBox(hwnd);
					break;

				default:
					break;
			};
			break;
		};

		// Handle messages posted from the callbacks
		//
		case WM_IT_ENUM_NAMES_RESULT:
			DisplayIlsNames(hwnd, (IEnumIlsNames *)lParam, "names");
			break;

		case WM_IT_ENUM_USERS_RESULT:
			DisplayIlsUsers(hwnd, (IEnumIlsUsers *)lParam);
			break;

		case WM_IT_RESOLVE_PROT_RESULT:
			DisplayProtocolInfo(hwnd, (IIlsProtocol *)lParam);
			break;

		case WM_IT_RESOLVE_USER_RESULT:
			{
			USERNODE un;
			PUSERNODE pun = &un;
			IIlsUser *pUser = (IIlsUser *)lParam;
			
			pun->pu = pUser;
			
			// Hookup the notification callback
			OnILSUserAdviseUnadvise(hwnd, pun, TRUE);

			// Display the information dialog
			DisplayIlsUserDialog(hwnd, pUser);

			// Remove the callback
			OnILSUserAdviseUnadvise(hwnd, pun, FALSE);

			// release the user object.
			pUser->Release();

            }
			break;

		default:
			break;
	}

	return 0L;
}

