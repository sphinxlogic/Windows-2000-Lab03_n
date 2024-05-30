/*
Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.
*/


#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <windows.h>
#include <initguid.h>
#include <iaccess.h>     // IAccessControl
#include "..\ps\ps.h"
// Global variables

// {73A30D75-C27E-11d0-B72A-00AA00C006CF}
DEFINE_GUID(CLSID_PDCObject, 
0x73a30d75, 0xc27e, 0x11d0, 0xb7, 0x2a, 0x0, 0xaa, 0x0, 0xc0, 0x6, 0xcf);


long	g_cComponents;
DWORD   dwRegister;
HANDLE  hevtDone;
HANDLE  hevtGotSink;
HANDLE  hThread;
PSECURITY_DESCRIPTOR psd = NULL;

TCHAR *szAuthnLevels[] = {TEXT("None"),TEXT("Connect"),TEXT("Call"),TEXT("Pkt"),TEXT("Integrity"),TEXT("Privacy")};
TCHAR *szImpLevels[] = {TEXT("Anonymous"),TEXT("Identify"),TEXT("Impersonate"),TEXT("Delegate")};

extern DWORD dwProcessAuthn;
extern DWORD dwProcessImp;
extern DWORD dwProxyAuthn;
extern DWORD dwProxyImp;
extern DWORD dwProcessCaps;
extern DWORD dwProxyCaps;
extern TCHAR szProxyDomain[];
extern TCHAR szProxyUser[];
extern TCHAR szProxyPassword[];
extern TCHAR szClientFile[];
extern TCHAR szAccessPermissions[];

extern BOOL bQuiet;

WCHAR szAppID[] = L"{73A30D75-C27E-11d0-B72A-00AA00C006CF}";
GUID appid;

BOOL GetAccessControl(IAccessControl **p);
BOOL SetSecurityParams ();

// simple class-factory: only knows how to create CSimpleObject instances
class CClassFactory : public IClassFactory 
{
  public:
    // IUnknown
    STDMETHODIMP    QueryInterface (REFIID riid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  { return 1; };
    STDMETHODIMP_(ULONG) Release(void) { return 1; }

    // IClassFactory
    STDMETHODIMP    CreateInstance (LPUNKNOWN punkOuter, REFIID iid, void **ppv);
    STDMETHODIMP    LockServer (BOOL ) { return E_FAIL; };
};

CClassFactory   g_ClassFactory;

// CSimpleObject - implements IMyCustomInterface

class CSimpleObject : public IServer
{
  public:

	  // IUnknown
    STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  { return InterlockedIncrement(&m_cRef); };
    STDMETHODIMP_(ULONG) Release(void) { if (InterlockedDecrement(&m_cRef) == 0) { _tprintf(TEXT("Deleting object\n")); delete this; return 0; } else return m_cRef; }

    // IServer
	STDMETHODIMP    AccessFile(LPCWSTR pszFileName);
    STDMETHODIMP    SetCallBackInterface(IUnknown *p);
    STDMETHODIMP    ImpersonateAndCallback();

    STDMETHODIMP    CallBack(LPCWSTR pszFileName);

    // constructors/destructors
    CSimpleObject()     { m_p = 0; m_cRef = 1; InterlockedIncrement(&g_cComponents);}
    ~CSimpleObject();
	
  private:
    LONG        m_cRef;
	ICallBack   *m_p;
};



void Message(LPTSTR szPrefix, HRESULT hr)
{
    LPTSTR   szMessage;
	TCHAR szDisplay[1000];

    if (hr == S_OK)
    {
		_tprintf(TEXT("%s\n"), szPrefix);
		//_stprintf(szDisplay, TEXT("%s"), szPrefix);
		//MessageBox(NULL, szDisplay, TEXT("Server:Msg"),0x00200000L);    
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
	
	//_tprintf(TEXT("%s: %s(%lx)"), szPrefix, szMessage, hr);
    _stprintf(szDisplay, TEXT("%s: %s(%lx)"), szPrefix, szMessage, hr);
	MessageBox(NULL, szDisplay, TEXT("Server:Msg"),0x00200000L);    
    LocalFree(szMessage);
}  // Message

CSimpleObject::~CSimpleObject()    
{ 
	if (m_p)
	{
		m_p->Release();
		m_p= 0;
	}							
	if (InterlockedDecrement(&g_cComponents) == 0)
		SetEvent(hevtDone); 
}

STDMETHODIMP CSimpleObject::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    if (riid == IID_IUnknown || riid == IID_IServer)
    {
        *ppv = (IUnknown *) this;
        AddRef();
        return S_OK;
    }
    *ppv = NULL;
    return E_NOINTERFACE;
}  // CSimpleObject::QueryInterface


STDMETHODIMP CSimpleObject::SetCallBackInterface(IUnknown *p)
{
	HRESULT hr;
    Message(TEXT("Server::QI client"), S_OK);
	hr = p->QueryInterface(IID_ICallBack, (void**)&m_p);
	if (FAILED(hr))
	{
        Message(TEXT("Server: QI on client Error"), hr);
		return hr;		
	}
	SetEvent(hevtGotSink);
	return S_OK;
}

STDMETHODIMP CSimpleObject::AccessFile(LPCWSTR pszFileName)
{
	TCHAR szBuf[100];
	HRESULT hr;
	
	DWORD dwAuthnSvc, dwAuthzSvc, dwAuthnLevel, dwCapabilities, dwImpLevel;
	OLECHAR *p;
	void *pv;
#ifndef UNICODE
	char szAnsi[500];
#endif

	//Find out client identity
	hr = CoQueryClientBlanket(&dwAuthnSvc,&dwAuthzSvc, &p, &dwAuthnLevel, 
		&dwImpLevel, (void**)&pv, &dwCapabilities);
	
    if (FAILED(hr))
        {
          Message(TEXT("Server: CoQueryClientBlanket"), hr);
		}
#ifdef UNICODE
	_stprintf(szBuf, TEXT("\nAuthnSvc %x AuthzSvc %x AuthnLevel %s ImpLevel %s client %s"),
		dwAuthnSvc, dwAuthzSvc, szAuthnLevels[dwAuthnLevel-1], szImpLevels[dwImpLevel-1], pv);
#else
	WideCharToMultiByte(0,0,(LPCWSTR)pv,-1,szAnsi, sizeof(szAnsi), NULL, NULL);
	_stprintf(szBuf, TEXT("\nAuthnSvc %x AuthzSvc %x AuthnLevel %s ImpLevel %s client %s"),
		dwAuthnSvc, dwAuthzSvc, szAuthnLevels[dwAuthnLevel-1], szImpLevels[dwImpLevel-1], szAnsi);

#endif

	Message(szBuf,S_OK);
	CoTaskMemFree(p);

	// try to access the file
#ifdef 	UNICODE
	_stprintf(szBuf, TEXT("Server:Trying to open file %s as server"), pszFileName);
	Message(szBuf, S_OK);	
	HANDLE h = CreateFile(pszFileName, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#else
	WideCharToMultiByte(0,0,pszFileName,-1,szAnsi, sizeof(szAnsi), NULL, NULL);
	_stprintf(szBuf, TEXT("Server:Trying to open file %s as server"), szAnsi);
	Message(szBuf, S_OK);	
	HANDLE h = CreateFile(szAnsi, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#endif
	if (h == INVALID_HANDLE_VALUE)
	{
		_stprintf(szBuf, TEXT("Server:Error trying to open file %s as server"), pszFileName);
		Message(szBuf, GetLastError());	
	}
	else
	{
		_stprintf(szBuf, TEXT("Server:Opened file %s as server"), pszFileName);
		Message(szBuf, S_OK);	
		CloseHandle(h);
	}
	
	//impersonate the client
	hr = CoImpersonateClient();
    if (FAILED(hr))
    {
       Message(TEXT("Server: CoImpersonateClient"), hr);
	}
	
	//Now try to access the file
#ifdef 	UNICODE
	_stprintf(szBuf, TEXT("Server:Trying to open file %s as client"), pszFileName);
	Message(szBuf, S_OK);	
	h = CreateFile(pszFileName, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#else
	WideCharToMultiByte(0,0,pszFileName,-1,szAnsi, sizeof(szAnsi), NULL, NULL);
	_stprintf(szBuf, TEXT("Server:Trying to open file %s as client"), szAnsi);
	Message(szBuf, S_OK);	
	h = CreateFile(szAnsi, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#endif
	if (h == INVALID_HANDLE_VALUE)
	{
		_stprintf(szBuf, TEXT("Server:Error trying to open file %s as client"), pszFileName);
		Message(szBuf, GetLastError());	
	}
	else
	{
		_stprintf(szBuf, TEXT("Server:Opened file %s as client"), pszFileName);
		Message(szBuf, S_OK);	
		CloseHandle(h);
	}
	// Go back to original identity
	hr = CoRevertToSelf();
    if (FAILED(hr))
    {
       Message(TEXT("Server: CoRevertToSelf"), hr);
       return hr;
	}
	
	return S_OK;
}

STDMETHODIMP CSimpleObject::ImpersonateAndCallback()
{
	TCHAR szBuf[100];
	HRESULT hr;
#ifndef UNICODE
	WCHAR wszParam[100];
	char szAnsi[500];
#endif
	
	DWORD dwAuthnSvc, dwAuthzSvc, dwAuthnLevel, dwCapabilities, dwImpLevel;
	OLECHAR *p;
	void *pv;

	//Find out client identity
	hr = CoQueryClientBlanket(&dwAuthnSvc,&dwAuthzSvc, &p, &dwAuthnLevel, 
		&dwImpLevel, (void**)&pv, &dwCapabilities);
	
    if (FAILED(hr))
        {
          Message(TEXT("Server: CoQueryClientBlanket"), hr);
		  return hr;
		}
#ifdef UNICODE
	_stprintf(szBuf, TEXT("\nAuthnSvc %x AuthzSvc %x AuthnLevel %s ImpLevel %s client %s"),
		dwAuthnSvc, dwAuthzSvc, szAuthnLevels[dwAuthnLevel-1], szImpLevels[dwImpLevel-1], pv);
#else
	WideCharToMultiByte(0,0,(LPCWSTR)pv,-1,szAnsi, sizeof(szAnsi), NULL, NULL);
	_stprintf(szBuf, TEXT("\nAuthnSvc %x AuthzSvc %x AuthnLevel %s ImpLevel %s client %s"),
		dwAuthnSvc, dwAuthzSvc, szAuthnLevels[dwAuthnLevel-1], szImpLevels[dwImpLevel-1], szAnsi);
#endif

	Message(szBuf,S_OK);
	CoTaskMemFree(p);
	//impersonate the client
	hr = CoImpersonateClient();
    if (FAILED(hr))
    {
      Message(TEXT("Server: CoImpersonateClient"), hr);
	  return hr;
	}
#ifdef UNICODE
	CallBack(szClientFile);
#else
	MultiByteToWideChar(0,0,szClientFile,-1,wszParam, sizeof(wszParam));
	CallBack(wszParam);
#endif
	hr = CoRevertToSelf();
    if (FAILED(hr))
    {
      Message(TEXT("Server: CoRevertToSelf"), hr);
	  return hr;
	}
	return S_OK;	
}

#ifdef UNICODE
SEC_WINNT_AUTH_IDENTITY_W AuthIdentity;
#else
SEC_WINNT_AUTH_IDENTITY_A AuthIdentity;
#endif
 
STDMETHODIMP CSimpleObject::CallBack(LPCWSTR pszFileName)
{
	HRESULT hr=S_OK;
#ifndef UNICODE
	WCHAR wszParam[100];
#endif
	pszFileName; // to get rid of /W4 warnings
	if (m_p)
	{
		ICallBack*    pICallBackCopy; 
		
		for(;;)
		{
			// Make a copy of the proxy and apply proxy security parameters
			
			hr = CoCopyProxy(m_p, (IUnknown**)&pICallBackCopy);
			if (FAILED(hr))
			{
				Message(TEXT("Server: CoCopyProxy Error"), hr);
				break;
			}
#ifdef UNICODE			
			AuthIdentity.User = szProxyUser;
			AuthIdentity.Domain = szProxyDomain;	
			AuthIdentity.Password = szProxyPassword;
			AuthIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

#else
			AuthIdentity.User = (unsigned char*)szProxyUser;
			AuthIdentity.Domain = (unsigned char*)szProxyDomain;	
			AuthIdentity.Password = (unsigned char*)szProxyPassword;
			AuthIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
#endif			
			AuthIdentity.UserLength = lstrlen(szProxyUser);
			AuthIdentity.DomainLength = lstrlen(szProxyDomain);
			AuthIdentity.PasswordLength = lstrlen(szProxyPassword);
			
			//Should we call CSPB at all?
			if (dwProxyAuthn != -1)
			{
				// If yes, use default credentials on the proxy or user specified credentials? 
				if (AuthIdentity.DomainLength == 0 || AuthIdentity.UserLength == 0)
					hr = CoSetProxyBlanket(pICallBackCopy, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
					dwProxyAuthn, dwProxyImp,  NULL, dwProxyCaps);
				else 
					hr = CoSetProxyBlanket(pICallBackCopy, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
					dwProxyAuthn, dwProxyImp,  &AuthIdentity, dwProxyCaps);
				if (FAILED(hr))
				{
					Message(TEXT("Server: CoSetProxyBlanket Error"), hr);
					pICallBackCopy->Release();
					break;
				}
			}
		
			//call method
#ifdef UNICODE
			hr = pICallBackCopy->AccessFile(szClientFile);
#else
			MultiByteToWideChar(0,0,szClientFile,-1,wszParam, sizeof(wszParam));
			hr = pICallBackCopy->AccessFile(wszParam);
#endif
			if (FAILED(hr))
			{
				Message(TEXT("Server: Client callback Error "), hr);
			}		
			pICallBackCopy->Release();
			
			if (bQuiet)
				break;
			_tprintf(TEXT("Call Again(Y/N)?"));
			TCHAR ch = (TCHAR)getche();
			
			// is the object shut down?
			if (WaitForSingleObject(hevtDone, 0)== WAIT_OBJECT_0)
				return S_OK;
			//Re-Initialize proxy security parameters from config file.
			if (ch == 'Y' || ch == 'y')
			{

				if (SetSecurityParams ())
					continue;
				else
					break;
			}
			else
				break;
		}
	}	
	return S_OK;
}

DWORD WINAPI ThreadProc(LPVOID *param)
{
	HRESULT hr;
	// initialize COM for free-threading
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
    {
        Message(TEXT("Server: CoInitializeEx Error"), hr);
        return hr;
    }
	CSimpleObject *p = (CSimpleObject*)param;
	HANDLE h[2];
	DWORD dw;
#ifndef UNICODE
	WCHAR wszParam[100];
#endif
	h[0] = hevtGotSink;
	h[1] = hevtDone;

	//Wait till either the client hooks up the sink or the server is shutting down;
	dw = WaitForMultipleObjects(2, h, FALSE, INFINITE);
	
	if ((dw - WAIT_OBJECT_0) == 0)
	{
		Message(TEXT("Server::Calling client back"), S_OK);
#ifdef UNICODE
		p->CallBack(szClientFile);
#else
		MultiByteToWideChar(0,0,szClientFile,-1,wszParam, sizeof(wszParam));
		p->CallBack(wszParam);
#endif
		
	}
	CoUninitialize();
	return 0;
}

STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, void** ppv)
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

STDMETHODIMP CClassFactory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid, void** ppv)
{
    LPUNKNOWN   punk;
	HRESULT hr;
    *ppv = NULL;

    if (punkOuter != NULL)
        return CLASS_E_NOAGGREGATION;

    // create object
	punk = new CSimpleObject;

    if (punk == NULL)
        return E_OUTOFMEMORY;

    hr = punk->QueryInterface(riid, ppv);
    punk->Release();
	
	// Create a thread to do callback;

	DWORD dw;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)punk, 0, &dw);
	if (!hThread)
	{
		Message(TEXT("Error in CreateThread"), GetLastError());
	}
	return hr;

}  // CClassFactory::CreateInstance


void main()
{
    HRESULT hr;
    DWORD   dwRegister;
	
	// Initialize process security parameters
	if (!SetSecurityParams ())
	{
		Message(TEXT("Error in reading configuration file, using all defaullts for security"), E_FAIL);
	}
    // create the event which is signaled when the last instance is deleted
    hevtDone = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hevtDone == NULL)
    {
        Message(TEXT("Server: CreateEvent Error"), GetLastError());
        exit(-1);
    }
	
	// create the event which is signaled when client hooks up a sink
    hevtGotSink = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hevtGotSink == NULL)
    {
        Message(TEXT("Server: CreateEvent Error"), GetLastError());
        exit(-1);
    }
    
	// initialize COM for free-threading
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
    {
        Message(TEXT("Server: CoInitializeEx Error"), hr);
        exit(-1);
    }
	//set process wide security
	
	// should we call CIS at all or use registry based security?
	if (dwProcessAuthn != -1) 
	{
		void *p = NULL; // Allow everyone
		DWORD dwCapabilities = EOAC_NONE;
		IAccessControl *pIAC;

		// appID based?

		if (dwProcessAuthn == -2) 
		{
			hr = CLSIDFromString(szAppID, &appid);
			if (FAILED(hr))
			{
				Message(TEXT("Server: CLSIDFromString Error"), hr);
				exit(-1);
			}
			p = &appid;				
			dwCapabilities |= EOAC_APPID;
		}
		// Did the user specify access permssions?
		else if (lstrlen(szAccessPermissions))
		{
			if (!GetAccessControl(&pIAC))
				exit(-1);
			p = pIAC;
			dwCapabilities |= EOAC_ACCESS_CONTROL;
		}
		dwCapabilities |= dwProcessCaps;

		hr = CoInitializeSecurity(
		    p,
			-1,
			NULL,
			NULL,
			dwProcessAuthn,
			dwProcessImp,
			NULL,
			dwCapabilities,
			NULL);
		if (FAILED(hr))
		{
			Message(TEXT("Client: CoInitializeSecurity Error"), hr);
			exit(hr);
		}
	}
/*
	LPUNKNOWN punk;
	DWORD dwUnused;

	// Register the proxy/stub classes, so we avoid separate
	// registration for the P/S DLL
	hr = DllGetClassObject(IID_IServer, IID_IUnknown, (void **)&punk);
    if (FAILED(hr))
	{
		Message(TEXT("DllGetClassObject Error"), hr);
        exit(hr);
	}
	hr = CoRegisterClassObject(IID_IServer, punk,
        CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &dwUnused);
    if (FAILED(hr))
	{
		Message(TEXT("CoRegisterClassObject Error"), hr);
        exit(hr);
	}
	hr = CoRegisterPSClsid(IID_IServer, IID_IServer);
    if (FAILED(hr))
	{
		Message(TEXT("CoRegisterPSClsid Error"), hr);
        exit(hr);
	}
	hr = DllGetClassObject(IID_ICallBack, IID_IUnknown, (void **)&punk);
    if (FAILED(hr))
	{
		Message(TEXT("DllGetClassObject Error"), hr);
        exit(hr);
	}
	hr = CoRegisterClassObject(IID_ICallBack, punk,
        CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &dwUnused);
    if (FAILED(hr))
	{
		Message(TEXT("CoRegisterClassObject Error"), hr);
        exit(hr);
	}
	hr = CoRegisterPSClsid(IID_ICallBack, IID_ICallBack);
    if (FAILED(hr))
	{
		Message(TEXT("CoRegisterPSClsid Error"), hr);
        exit(hr);
	}
   
*/
	// register the class-object with COM
    hr = CoRegisterClassObject(CLSID_PDCObject, &g_ClassFactory,
        CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
 	if (FAILED(hr))
    {
        Message(TEXT("Server: CoRegisterClassObject Error"), hr);
        exit(hr);
    }
	
	
	// Wait till the object instance is deleted
	Message(TEXT("Server Waiting"), S_OK);
	WaitForSingleObject(hevtDone, INFINITE);
	
	//Cleanup
	
	// Make sure that our worker thread exited as well
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hevtGotSink);
    CloseHandle(hevtDone);
	CoRevokeClassObject(dwRegister);
    CoUninitialize();
 }  // main

