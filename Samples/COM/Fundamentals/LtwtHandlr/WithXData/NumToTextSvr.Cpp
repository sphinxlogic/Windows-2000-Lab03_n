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

        WinMain() - calls initialization function, processes message loop

        COMMENTS:

****************************************************************************/

#include <windows.h>   // required for all Windows applications
#include "classfact.h"
#include "..\common\debug.h"


int g_ObjectCount =0;	// Current Object count, so if the count goes to zero, we can shutdown

char szAppName[] = "NumToTextSvr";   // The name of this application
char szTitle[]   = "NumToTextSvr Sample"; // The title bar text

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
   MSG msg;
      
   /* Perform initializations that apply to a specific instance */
   // Initialize COM/OLE, 
	CoInitialize(NULL);
	DebugTrace(TEXT("InitOle\r\n"));

	// Register the class Factory for the COM object
	if(FAILED(RegisterCF(lpCmdLine)))
		return FALSE;
	DebugTrace(TEXT("RegisterCF\r\n"));

   /* Acquire and dispatch messages until a WM_QUIT message is received. */

  while (GetMessage(&msg, NULL,0, 0))     
  {
      TranslateMessage(&msg);// Translates virtual key codes
      DispatchMessage(&msg); // Dispatches message to window
  }

  // unregister the classfactory for the com object
  UnregisterCF();
  DebugTrace(TEXT("UnregisterCF\r\n"));

  //unintialize COM/OLE
  CoUninitialize();
  DebugTrace(TEXT("UninitOle\r\n"));

  return (msg.wParam); // Returns the value from PostQuitMessage
  lpCmdLine; // This will prevent 'unused formal parameter' warnings
}


