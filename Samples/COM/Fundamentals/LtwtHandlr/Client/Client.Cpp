/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/

/****************************************************************************

        PROGRAM: NumToTextSvr.cpp

        PURPOSE: Generic template for Windows applications

        FUNCTIONS:

        WinMain() - calls initialization function, 

        COMMENTS:

****************************************************************************/

#include <windows.h>   // required for all Windows applications
#include "..\NumTxtPS\server.h"
#include "..\common\Debug.h"
#include "..\common\Guid.h"



char szAppName[] = "Client";   // The name of this application
char szTitle[]   = "Client to NumToTextSvr Sample"; // The title bar text

/****************************************************************************

        FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

        PURPOSE: calls initialization function, processes message loop

        COMMENTS:

                Windows recognizes this function by name as the initial entry point
                for the program.  This function calls the application initialization
                routine, if no other instance of the program is running, and always
                calls the instance initialization routine.  It then executes a message
                retrieval and dispatch loop that is the top-level control structure
                for the remainder of execution.  The loop is terminated when a WM_QUIT
                message is received, at which time this function exits the application
                instance by returning the value passed by PostQuitMessage().

                If this function must abort before entering the message loop, it
                returns the conventional value NULL.

****************************************************************************/
int CALLBACK WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{
	/* Perform initializations that apply to a specific instance */
	// Initialize COM/OLE, 
	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	DebugTrace(TEXT("Client: InitOle\r\n"));
	INumberToText *pINumToText =NULL;
	HRESULT hr = S_OK;
	// Create the component, and get INumToText interface
#ifdef WITHXDATA	
	hr = CoCreateInstance(CLSID_NumToTextWithXData,NULL,CLSCTX_SERVER,IID_INumberToText,(LPVOID *)&pINumToText);
#else
	hr = CoCreateInstance(CLSID_NumToTextNoXData,NULL,CLSCTX_SERVER,IID_INumberToText,(LPVOID *)&pINumToText);
#endif 
	if(SUCCEEDED(hr))
	{
		BSTR pText;

		DebugTrace(TEXT("Client: GetText 1 \r\n"));
		hr = pINumToText->GetText(1,&pText);
		if(SUCCEEDED(hr))
		{
			OutputDebugStringW(pText);
			DebugTrace(TEXT(" \r\n"));
			SysFreeString(pText);
		}

		DebugTrace(TEXT("Client: GetText 2 \r\n"));
		hr = pINumToText->GetText(2,&pText);
		if(SUCCEEDED(hr))
		{
			OutputDebugStringW(pText);
			DebugTrace(TEXT(" \r\n"));
			SysFreeString(pText);
		}

		DebugTrace(TEXT("Client: GetText 1 \r\n "));
		hr = pINumToText->GetText(1,&pText);
		if(SUCCEEDED(hr))
		{
			OutputDebugStringW(pText);
			DebugTrace(TEXT(" \r\n"));
			SysFreeString(pText);
		}
		pINumToText->Release();

	}
	else
	{
		DebugTrace(TEXT("Client: CCI Failed %x\r\n"),hr);
	}
	MessageBox(NULL, "Test to See if Server shutsdown", "Messagebox", MB_OK);
	//unintialize COM/OLE
	CoUninitialize();
	DebugTrace(TEXT("Client: UninitOle\r\n"));

	return 0;
}


