// ComSpy.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f ComSpyps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "ComSpy.h"
#include "..\ComSpyFace\ComSpyCtl.h"
#include "..\ComSpyFace\ComSpyCtl_i.c"
#include "ComSpy_i.c"
#include "SpyCon.h"


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
	OBJECT_ENTRY(CLSID_SpyCon, CSpyCon)
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
			_Module.UpdateRegistryFromResource(IDR_ComSpy, FALSE);
			nRet = _Module.UnregisterServer();
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_ComSpy, TRUE);
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = FindOneOf(lpszToken, szTokens);
	}

	if (bRun)
	{
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
			REGCLS_MULTIPLEUSE);
		_ASSERTE(SUCCEEDED(hRes));

		ISpyCon * pApp;
		CoCreateInstance(CLSID_SpyCon, NULL, CLSCTX_INPROC_SERVER, IID_ISpyCon, (void**)&pApp);
		if (pApp)
		{
			pApp->Run();
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			ULONG ul = pApp -> Release();
			_ASSERTE(ul==0);
		}
		else
			_ASSERTE(0);

		_Module.RevokeClassObjects();
	}

	CoUninitialize();
	return nRet;
}
