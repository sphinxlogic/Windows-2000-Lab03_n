#include <windows.h>
#include <iostream.h>

#include "DCOMServer.h"
#include "CFactory.h"
#include "Debug.h"



extern "C" 
{
	LPWSTR appSource = CServer::GetProgID();
}
CHAR_CONVERSION; // A2W, W2A helpers

extern int g_cFactoryDataEntries;
extern CFactoryData g_FactoryDataArray[];

typedef enum {EMPTY,REGISTER,UNREGISTER} SERVERFLAGS;
SERVERFLAGS UpdateRegistery(char* argv);

#if 0
ATOM MyRegisterClass(CONST WNDCLASS*);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#endif

char *g_szClassName = "UDT";

HMODULE g_hModule;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,

                     int       nCmdShow)
main(int argc, char* argv[])
{


	cout << "Server side of UDT test" << endl;
	HRESULT hr = CoInitialize(NULL);
	_ASSERT(SUCCEEDED(hr));
 
	if (lpCmdLine && UpdateRegistery(lpCmdLine) == REGISTER)
	{
		hr = CFactory::RegisterAll();
		if (FAILED(hr))
			MessageBox(NULL, "Could not registry app", W2A(CServer::GetProgID()), MB_OK);
		else
			MessageBox(NULL, "application has been registered", W2A(CServer::GetProgID()), MB_OK);
		return TRUE;
	}
	else if(lpCmdLine && UpdateRegistery(lpCmdLine) == UNREGISTER)
	{
		hr = CFactory::UnregisterAll();
		if (FAILED(hr))
			MessageBox(NULL, "Error unregistering app", W2A(CServer::GetProgID()), MB_OK);
		else
			MessageBox(NULL, "application has been unregistered", W2A(CServer::GetProgID()), MB_OK);
		return TRUE;
	}
	
	// Register all ClassFactories
	int i;
	DWORD *dwCookies;
	LPCLASSFACTORY pCF = NULL;;

	dwCookies = new DWORD[g_cFactoryDataEntries];
	DEBUGTRACE(_T("Register all ClassFactories"));
	for (i = 0; i < g_cFactoryDataEntries; i++)
	{
		const CFactoryData* pData = &g_FactoryDataArray[i] ;

		pCF =  new CFactory(pData) ;
		if (pCF == NULL)
		{
			DEBUGTRACE(_T("Error allocating memory for classfactory"));
			return FALSE;
		}
		hr = CoRegisterClassObject(*pData->m_pCLSID,
							  pCF,
							  pData->server == LOCAL ? CLSCTX_LOCAL_SERVER : CLSCTX_SERVER,
							  REGCLS_MULTIPLEUSE|REGCLS_SUSPENDED,
							  &dwCookies[i]);
		_ASSERT(SUCCEEDED(hr));
	}


	if (!hPrevInstance) {
      // Perform instance initialization:
      if (!InitApplication(hInstance)) {
         return (FALSE);
      }
	}

   // Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) {
      return (FALSE);
	}

	
	hr = CoResumeClassObjects();
	_ASSERT(SUCCEEDED(hr));

	DEBUGTRACE(_T("Class Factories have been registered ready to handling in comming"));
	cout << "Class Factories have been registered ready to handling in comming" << endl;

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);


	DEBUGTRACE(_T("Cleaning up and exiting process"));
	for (i = 0; i < g_cFactoryDataEntries; i++)
		CoRevokeClassObject(dwCookies[i]);

	delete [] dwCookies;
	CoUninitialize();
	cout << "End of test" << endl;
	return 0;
}

SERVERFLAGS UpdateRegistery(char* argv)
{
/*(
	char *strtok( char *strToken, const char *strDelimit );
	char *strpbrk( const char *string, const char *strCharSet );
*/
	char *p = strtok(argv, "-/");
	while (p)
	{
		if (stricmp(p, "RegServer")==0)
			return REGISTER;
		else if (stricmp(p, "UnregServer")==0)
			return UNREGISTER;
		p = strtok(NULL, "-/");
	}
	return EMPTY;
}


//
//  FUNCTION: InitApplication(HANDLE)
//
//  PURPOSE: Initializes window data and registers window class
//
//  COMMENTS:
//
//       In this function, we initialize a window class by filling out a data
//       structure of type WNDCLASS and calling either RegisterClass or
//       the internal MyRegisterClass.
//
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    // Fill in window class structure with parameters that describe
    // the main window.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = g_szClassName;

   return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   g_hModule = hInstance; // Store instance handle in our global variable
   char * foo = W2A(CServer::GetProgID());

   hWnd = CreateWindow(g_szClassName, W2A(CServer::GetProgID()), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
      NULL, NULL, hInstance, NULL);

   if (!hWnd) {
      return (FALSE);
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return (TRUE);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  MESSAGES:
//
// WM_COMMAND - process the application menu
// WM_PAINT - Paint the main window
// WM_DESTROY - post a quit message and return
//    WM_DISPLAYCHANGE - message sent to Plug & Play systems when the display changes
//    WM_RBUTTONDOWN - Right mouse click -- put up context menu here if appropriate
//    WM_NCRBUTTONUP - User has clicked the right button on the application's system menu
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

   PAINTSTRUCT ps;
   HDC hdc;

   switch (message) {

      case WM_PAINT:
         hdc = BeginPaint (hWnd, &ps);
         // Add any drawing code here...
         EndPaint (hWnd, &ps);
         break;

      case WM_DESTROY:
         PostQuitMessage(0);
         break;

      default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return (0);
}


