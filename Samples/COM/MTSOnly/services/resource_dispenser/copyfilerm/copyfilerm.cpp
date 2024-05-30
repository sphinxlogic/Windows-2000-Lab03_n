
/******************************************************************************\
********************************************************************************
* Filename: CopyFileRm.cpp
*
* Description: Implementation of WinMain
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

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "txdtc.h"
#define INITGUID
#include "txcoord.h"
#include "xolehlp.h"

#include "..\..\..\common\inc\CopyFileRm.h"
#define IID_DEFINED
#include "..\..\..\common\inc\CopyFileRm_i.c"
#include "..\..\..\common\inc\SimpleLog.h"
#include "..\..\..\common\inc\simplelog_i.c"
#include "..\..\..\common\inc\rmworker.h"
#include "rmoptions.h"
#include "FileRm.h"
#include "rmdlg.h"





LONG CExeModule::Lock()
{
	LONG l = CComModule::Lock();
	if (_Module.m_dlg)
		_Module.m_dlg->SetLockCount(l);

	return l;
}



LONG CExeModule::Unlock()
{
	LONG l = CComModule::Unlock();
	if (_Module.m_dlg)
		_Module.m_dlg->SetLockCount(l);
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
	OBJECT_ENTRY(CLSID_CoFileRm, CFileRm)
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
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
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
			_Module.UpdateRegistryFromResource(IDR_CopyFileRm, FALSE);
			nRet = _Module.UnregisterServer();
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_CopyFileRm, TRUE);
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = FindOneOf(lpszToken, szTokens);
	}

	if (bRun)
	{
		//
		//	to make it easier to demo, I am always going to register the server when
		//	it is launched
		//

		_Module.UpdateRegistryFromResource(IDR_CopyFileRm, TRUE);
		nRet = _Module.RegisterServer(TRUE);
		_ASSERTE(SUCCEEDED(nRet ));
		

		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
		_ASSERTE(SUCCEEDED(hRes));

		if (SUCCEEDED(hRes))
		{

			if (_Module.m_dlg)
					_Module.m_dlg -> SetUsageCount(0);
				MSG msg;
				while (GetMessage(&msg, 0, 0, 0))
					DispatchMessage(&msg);

				_Module.RevokeClassObjects();
			}
		
	}


	CoUninitialize();
	return nRet;
}
