//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
// Author: S.R.
//         Support Engineer - Internet Client SDK
//         Microsoft Developer Support
//
// AtlBrowser.cpp : Implementation of WinMain
//--------------------------------------------------------------------------

// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f AtlBrowserps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "AtlBrowser.h"

#include "AtlBrowser_i.c"
#include "AtlBrCon.h"


LONG CExeModule::Unlock()
{
	LONG l = CComModule::Unlock();
	if (l == 0)
	{
#if _WIN32_WINNT >= 0x0400
		if (CoSuspendClassObjects() == S_OK)
			PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
#else
		PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
#endif
	}
	return l;
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_AtlBrCon, CAtlBrCon)
END_OBJECT_MAP()


LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p++)
				return p1+1;
		}
		p1++;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
	HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
	lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	HRESULT hRes = CoInitialize(NULL);

//  If you are running on NT 4.0 or higher you can use the following call
//	instead to make the EXE free threaded.
//  This means that calls come in on a random RPC thread
//	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	_ASSERTE(SUCCEEDED(hRes));
	_Module.Init(ObjectMap, hInstance);
	_Module.dwThreadID = GetCurrentThreadId();
	TCHAR szTokens[] = _T("-/");

	int nRet = 0;
	BOOL bRun = TRUE;
	LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_AtlBrowser, FALSE);
			nRet = _Module.UnregisterServer();
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_AtlBrowser, TRUE);
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = FindOneOf(lpszToken, szTokens);
	}

	if (bRun)
	{
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
		_ASSERTE(SUCCEEDED(hRes));

      // Create the Atl Browser Container
		CComPtr<IAtlBrCon> pApp;
		CoCreateInstance(CLSID_AtlBrCon, NULL, CLSCTX_INPROC_SERVER, IID_IAtlBrCon,
                       (void**)&pApp);
		if (pApp)
      {
			pApp->Run();

         long hwnd;
         HWND hwndApp;
         pApp->GetHwnd(&hwnd);
         hwndApp = (HWND)hwnd;

		   MSG msg;
		   while (GetMessage(&msg, 0, 0, 0))
         {
            HACCEL hAccel = LoadAccelerators(_Module.GetResourceInstance(),
                                             MAKEINTRESOURCE(IDR_ACCELERATOR));
            _ASSERT(hAccel);
            if (!::TranslateAccelerator(hwndApp, hAccel, &msg))
            {
               // Avoid the beep when in the combo box
               if (msg.wParam != VK_RETURN && msg.wParam != VK_TAB)
                  ::TranslateMessage(&msg);

               //
               // If we get a keydown message, we must get send the message
               // to the container window so that the message can be routed to 
               // the correct window.  This is necessary so that the container
               // window can call TranslateAccelerator on the in-place active
               // object and so that VK_RETURN and VK_TAB messages received from
               // the combobox in the toolbar will be processed correctly.
               // 
               if (msg.message == WM_KEYDOWN)
                  ::SendMessage(hwndApp, msg.message, msg.wParam, msg.lParam);

               ::DispatchMessage(&msg);
            }
         }
      }

		_Module.RevokeClassObjects();
	}

	CoUninitialize();
	return nRet;
}
