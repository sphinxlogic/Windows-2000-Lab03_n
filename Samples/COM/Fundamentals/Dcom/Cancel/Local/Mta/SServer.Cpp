/*
Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.
*/
#define _WIN32_WINNT  0x0400
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <WindowsX.h>

#include <initguid.h>

HANDLE g_hEventDone;
CRITICAL_SECTION g_cs;

// {37824811-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_MTACancelObject, 0x37824812, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);


typedef struct tagCONSOLEDATA
{
	int x;
	int y;
} CONSOLEDATA;

CONSOLEDATA g_ConsoleData;

// %%Classes: ----------------------------------------------------------------

// simple class-factory: only knows how to create CSimpleObject instances
class CClassFactory : public IClassFactory 
{
  public:
    // IUnknown
    STDMETHODIMP    QueryInterface (REFIID riid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  { return 2; };
    STDMETHODIMP_(ULONG) Release(void) { return 1; }

    // IClassFactory
    STDMETHODIMP    CreateInstance (LPUNKNOWN punkOuter, REFIID iid, void **ppv);
    STDMETHODIMP    LockServer (BOOL fLock) { 
		if (fLock) 
			CoAddRefServerProcess();
		else
		{
			if (!CoReleaseServerProcess())
			{
				SetEvent(g_hEventDone);
			}
		}
		return S_OK;
	}

    CClassFactory()  { }

  private:
    };

class CSimpleObject : public IPersist
{
  public:
    // IUnknown
    STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  {InterlockedIncrement(&m_cRef);return m_cRef;}
    STDMETHODIMP_(ULONG) Release(void) { 
		if (InterlockedDecrement(&m_cRef) == 0) 
		{ delete this; return 0;}
		else
			return m_cRef;
	}

    // IPersist
    STDMETHODIMP    GetClassID(CLSID *pClsID);
	
    // constructors/destructors
    CSimpleObject()     { 
		m_cRef = 1; xy.X = 0; xy.Y = g_ConsoleData.y;
		hConsole = CreateFile(TEXT("CONOUT$"), GENERIC_READ|GENERIC_WRITE, 
			FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == hConsole)
			hConsole = 0;	
		CoAddRefServerProcess();
	}
    ~CSimpleObject()    { if (hConsole) CloseHandle(hConsole);
			if (!CoReleaseServerProcess())
			{
				SetEvent(g_hEventDone);
			}
	}
    STDMETHODIMP    WasteTime(TCHAR *szMessage);

  private:
    LONG        m_cRef;
	COORD       xy;
	HANDLE hConsole;

    };

// %%Globals: ----------------------------------------------------------------

CClassFactory   g_ClassFactory;

// ---------------------------------------------------------------------------
// %%Function: Message
// 
//  Formats and displays a message to the console.
// ---------------------------------------------------------------------------
void
Message(LPTSTR szPrefix, HRESULT hr)
{
    LPTSTR   szMessage;
	TCHAR szDisplay[1000];

    if (hr == S_OK)
        {
		_stprintf(szDisplay, TEXT("%s"), szPrefix);
		MessageBox(0, szDisplay, TEXT("Msg"),MB_SERVICE_NOTIFICATION);    
        return;
        }
 
    if (HRESULT_FACILITY(hr) == FACILITY_WIN32)
        hr = HRESULT_CODE(hr);

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
        (LPTSTR)&szMessage,
        0,
        NULL );

    _stprintf(szDisplay, TEXT("%s: %s(%lx)"), szPrefix, szMessage, hr);
	MessageBox(0, szDisplay, TEXT("Service:Msg"),MB_SERVICE_NOTIFICATION);    
    LocalFree(szMessage);
}  // Message


// ---------------------------------------------------------------------------
// %%Function: CSimpleObject::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSimpleObject::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    *ppv = NULL;
    if (riid == IID_IUnknown || riid == IID_IPersist)
    {
        *ppv =  this;
        ((IUnknown*)*ppv)->AddRef();
        return S_OK;
	}

    return E_NOINTERFACE;
}  // CSimpleObject::QueryInterface

STDMETHODIMP Busy(HANDLE hConsole, COORD& xy, int nIter)
{
	HRESULT hr = S_OK;
	SetConsoleCursorPosition(hConsole, xy);
	TCHAR *szMessage = TEXT("!!!Call cancelled!!!");
	TCHAR *szBuf[4]={TEXT("|"), TEXT("/"), TEXT("-"), TEXT("\\")};
	for (int i = 0; i < nIter; i++)
	{
		Sleep(5);
		WriteConsole(hConsole, szBuf[0], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szBuf[1], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szBuf[2], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szBuf[3], 1, NULL, NULL);
		SetConsoleCursorPosition(hConsole, xy);
		if (RPC_E_CALL_CANCELED == CoTestCancel())
		{
			hr = RPC_E_CALL_CANCELED;
			WriteConsole(hConsole, szMessage, lstrlen(szMessage), NULL, NULL);
			break;
		}
	}
	return hr;
}
 
STDMETHODIMP
CSimpleObject::WasteTime(TCHAR *szMessage)
{
	if (hConsole)
	{
		SetConsoleCursorPosition(hConsole, xy);
		WriteConsole(hConsole, szMessage, lstrlen(szMessage), NULL, NULL);
		xy.X += 50;
		return Busy(hConsole, xy, 5000);
	}
	return S_OK;
}


STDMETHODIMP
CSimpleObject::GetClassID(CLSID *pClsID)
{
	MessageBeep(0);
	xy.X = 0;
	return WasteTime(TEXT("In Call                               "));
}
 
// ---------------------------------------------------------------------------
// %%Function: CClassFactory::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    if (riid == IID_IClassFactory || riid == IID_IUnknown)
        {
        *ppv = (IClassFactory *) this;
        AddRef();
        return S_OK;
        }
    *ppv = NULL;
    return E_NOINTERFACE;
}  // CClassFactory::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::CreateInstance
// ---------------------------------------------------------------------------

 STDMETHODIMP
CClassFactory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid, void** ppv)
{
	HRESULT hr = S_OK;
    *ppv = NULL;
	CSimpleObject *p;

    if (punkOuter != NULL)
        return CLASS_E_NOAGGREGATION;
	EnterCriticalSection(&g_cs);
	g_ConsoleData.y++;
	p = new CSimpleObject;
	LeaveCriticalSection(&g_cs);
    if (p == NULL)
        return E_OUTOFMEMORY;
	if (RPC_E_CALL_CANCELED == p->WasteTime(TEXT("Creating Object")))
	{
		p->Release();
		return hr;
	}
    hr = p->QueryInterface(riid, ppv);
	p->Release();
	return hr;
}  // CClassFactory::CreateInstance



void main()
{
    HRESULT hr;
    DWORD   dwRegister;

    // create the event which is signaled when the instance is deleted
    g_hEventDone = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (g_hEventDone == NULL)
    {
        Message(TEXT("Server: CreateEvent Error"), GetLastError());
        exit(-1);
    }
	InitializeCriticalSection(&g_cs);
    // initialize COM for free-threading
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
    {
        Message(TEXT("Server: CoInitializeEx Error"), hr);
        exit(-1);
    }
    
	hr = CoInitializeSecurity(
			NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_NONE,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE,
			NULL);
    if (FAILED(hr))
        {
		CoUninitialize();
        Message(TEXT("Client: CoInitializeSecurity Error"), hr);
        exit(hr);
        }
	// register the class-object with OLE
    hr = CoRegisterClassObject(CLSID_MTACancelObject, &g_ClassFactory,
        CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
    
	if (FAILED(hr))
    {
		CoUninitialize();
        Message(TEXT("Server: CoRegisterClassObject Error"), hr);
        exit(-1);
    }
	WaitForSingleObject(g_hEventDone, INFINITE);
	hr = CoRevokeClassObject(dwRegister);
	if (FAILED(hr))
    {
		CoUninitialize();
        Message(TEXT("Server: CoRevokeClassObject Error"), hr);
        exit(-1);
    }
    CoUninitialize();
	CloseHandle(g_hEventDone);
	DeleteCriticalSection(&g_cs);
    _tprintf(TEXT("Server: Done"));
}  // main
