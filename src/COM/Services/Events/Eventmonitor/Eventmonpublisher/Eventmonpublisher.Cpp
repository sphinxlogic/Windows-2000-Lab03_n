// EventMonPublisher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "..\include\Adminwrap.h"
#include "EventMonPubdlg.h"


BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

CComModule _Module;
HINSTANCE  g_hInstance =0;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG		msg;
	HWND	hwnd;
	HRESULT hr;
	CPubdlg	pubdlg;
	

	hr = CoInitialize(NULL);
	if FAILED(hr)
		goto exit;

	_Module.Init(NULL,hInstance);

	g_hInstance = hInstance;

	hwnd = pubdlg.Create(NULL, NULL);

	
	while (GetMessage(&msg, 0, 0, 0))
	{
        if (!IsDialogMessage(hwnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}	
	
	_Module.Term();
exit:
	CoUninitialize();
	return 0;
}



 