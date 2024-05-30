/*
Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <windows.h>
#include <initguid.h>
#include <tchar.h>
#include <conio.h>
#include <iaccess.h>     // IAccessControl
#include "..\ps\ps.h"

// {73A30D75-C27E-11d0-B72A-00AA00C006CF}
DEFINE_GUID(CLSID_PDCObject, 
0x73a30d75, 0xc27e, 0x11d0, 0xb7, 0x2a, 0x0, 0xaa, 0x0, 0xc0, 0x6, 0xcf);

BOOL SetSecurityParams ();
BOOL GetAccessControl(IAccessControl **p);

extern DWORD dwActivationAuthn;
extern DWORD dwActivationImp;
extern DWORD dwProcessAuthn;
extern DWORD dwProcessImp;
extern DWORD dwProxyAuthn;
extern DWORD dwProxyImp;
extern DWORD dwActivationCaps;
extern DWORD dwProcessCaps;
extern DWORD dwProxyCaps;
extern TCHAR szActivationDomain[];
extern TCHAR szActivationUser[];
extern TCHAR szActivationPassword[];
extern TCHAR szProxyDomain[];
extern TCHAR szProxyUser[];
extern TCHAR szProxyPassword[];
extern TCHAR szAccessPermissions[];
extern TCHAR szServerFile[];

TCHAR *szAuthnLevels[] = {TEXT("None"),TEXT("Connect"),TEXT("Call"),TEXT("Pkt"),TEXT("Integrity"),TEXT("Privacy")};
TCHAR *szImpLevels[] = {TEXT("Anonymous"),TEXT("Identify"),TEXT("Impersonate"),TEXT("Delegate")};


class CCallBackObject : public ICallBack
{
  public:

	  // IUnknown
    STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void)  { return InterlockedIncrement(&m_cRef); };
    STDMETHODIMP_(ULONG) Release(void) { if (InterlockedDecrement(&m_cRef) == 0) { delete this; return 0; } return m_cRef; }

    // ICallBackClient
    STDMETHODIMP    AccessFile(LPCWSTR pszFileName);

    // constructors/destructors
    CCallBackObject()     {m_cRef = 0;}
    ~CCallBackObject()    {;}

  private:
    LONG        m_cRef;
	
};

CCallBackObject sink;

STDMETHODIMP CCallBackObject::QueryInterface(REFIID riid, void** ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;
    if (riid == IID_IUnknown || riid == IID_ICallBack)
    {
        *ppv = (IUnknown *) this;
        AddRef();
        return S_OK;
    }
    *ppv = NULL;
    return E_NOINTERFACE;
}  // CSimpleObject::QueryInterface

void Message(LPTSTR szPrefix, HRESULT hr)
{
    LPTSTR   szMessage;
	TCHAR szDisplay[1000];

    if (hr == S_OK)
    {
		_tprintf(TEXT("%s\n"), szPrefix);
		//_stprintf(szDisplay, TEXT("%s"), szPrefix);
		//MessageBox(NULL, szDisplay, TEXT("Client:Msg"),0x00200000L);    
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
	MessageBox(NULL, szDisplay, TEXT("Client:Msg"),0x00200000L);    
    LocalFree(szMessage);
}  // Message

STDMETHODIMP CCallBackObject::AccessFile(LPCWSTR pszFileName)
{
	TCHAR szBuf[100];
	HRESULT hr;
	DWORD dwAuthnSvc, dwAuthzSvc, dwAuthnLevel, dwCapabilities, dwImpLevel;
	OLECHAR *p;
	void *pv;
#ifndef UNICODE
	char szAnsi[100];
#endif

	//Find out client identity
	hr = CoQueryClientBlanket(&dwAuthnSvc,&dwAuthzSvc, &p, &dwAuthnLevel, 
		&dwImpLevel, (void**)&pv, &dwCapabilities);
	
    if (FAILED(hr))
        {
          Message(TEXT("Client: CoQueryClientBlanket"), hr);
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
	_stprintf(szBuf, TEXT("Client:Trying to open file %s as client"), pszFileName);
	Message(szBuf, S_OK);	
	HANDLE h = CreateFile(pszFileName, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#else
	WideCharToMultiByte(0,0,pszFileName,-1,szAnsi, sizeof(szAnsi), NULL, NULL);
	_stprintf(szBuf, TEXT("Client:Trying to open file %s as client"), szAnsi);
	Message(szBuf, S_OK);	
	HANDLE h = CreateFile(szAnsi, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#endif
	if (h == INVALID_HANDLE_VALUE)
	{
		_stprintf(szBuf, TEXT("Client:Error trying to open file %s as client"), pszFileName);
		Message(szBuf, GetLastError());	
	}
	else
	{
		_stprintf(szBuf, TEXT("Client:Opened file %s as client"), pszFileName);
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
	_stprintf(szBuf, TEXT("Server:Trying to open file %s as server"), pszFileName);
	Message(szBuf, S_OK);	
	h = CreateFile(pszFileName, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#else
	WideCharToMultiByte(0,0,pszFileName,-1,szAnsi, sizeof(szAnsi), NULL, NULL);
	_stprintf(szBuf, TEXT("Server:Trying to open file %s as server"), szAnsi);
	Message(szBuf, S_OK);	
	h = CreateFile(szAnsi, GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL); 
#endif
	if (h == INVALID_HANDLE_VALUE)
	{
		_stprintf(szBuf, TEXT("Client:Error trying to open file %s as server"), pszFileName);
		Message(szBuf, GetLastError());	
	}
	else
	{
		_stprintf(szBuf, TEXT("Client:Opened file %s as server"), pszFileName);
		Message(szBuf, S_OK);	
		CloseHandle(h);
	}
	// Go back to original identity
	hr = CoRevertToSelf();
    if (FAILED(hr))
    {
       Message(TEXT("Client: CoRevertToSelf"), hr);
       return hr;
	}
	return S_OK;
}
 


COSERVERINFO csi, *pcsi=NULL;
MULTI_QI    mq;

#ifdef UNICODE
SEC_WINNT_AUTH_IDENTITY_W AuthIdentity;
#else
SEC_WINNT_AUTH_IDENTITY_A AuthIdentity;
#endif

COAUTHINFO AuthInfo;

void main(int argc, CHAR **argv)
{
	HRESULT hr;
    WCHAR wsz [MAX_PATH];
#ifndef UNICODE
	WCHAR wszParam[100];
#endif
	
	// Initialize activation, process and proxy security parameters
	if (!SetSecurityParams ())
	{
		Message(TEXT("Error in reading configuration file, using all defaullts for security"), E_FAIL);
	}
	
	if (argc > 1) // get the server machine name
    {
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, argv[1], -1,
            wsz, MAX_PATH);
        memset(&csi, 0, sizeof(COSERVERINFO));
        csi.pwszName = wsz;
	}
    pcsi = &csi;
	if (dwActivationAuthn == -1)
		pcsi->pAuthInfo = NULL;	
	else
		pcsi->pAuthInfo = &AuthInfo;
	
	// setup activation security parameters
	AuthInfo.dwAuthnSvc = RPC_C_AUTHN_WINNT;
	AuthInfo.dwAuthzSvc = RPC_C_AUTHZ_NONE;
	AuthInfo.pwszServerPrincName = NULL;
	AuthInfo.dwAuthnLevel = dwActivationAuthn;
	AuthInfo.dwImpersonationLevel = dwActivationImp;
	
	// credentials
#ifdef UNICODE
	AuthIdentity.User = szActivationUser;
	AuthIdentity.Domain = szActivationDomain;	
	AuthIdentity.Password = szActivationPassword;
	AuthIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
#else
	AuthIdentity.User = (unsigned char*)szActivationUser;
	AuthIdentity.Domain = (unsigned char*)szActivationDomain;	
	AuthIdentity.Password = (unsigned char*)szActivationPassword;
	AuthIdentity.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
#endif		
	
	AuthIdentity.UserLength = lstrlen(szActivationUser);
	AuthIdentity.DomainLength = lstrlen(szActivationDomain);
	AuthIdentity.PasswordLength = lstrlen(szActivationPassword);
	// Use default credentials on activation?
	if (AuthIdentity.DomainLength == 0 || AuthIdentity.UserLength == 0)
		AuthInfo.pAuthIdentityData = NULL;
	else
		AuthInfo.pAuthIdentityData = (COAUTHIDENTITY*)&AuthIdentity;
	
	AuthInfo.dwCapabilities = dwActivationCaps;
	
	// Use the activation security at all or pick up default?

	
	//initilize COM for for free threading
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        Message(TEXT("Client: CoInitializeEx"), hr);
        exit(hr);
    }
	
	// set up process wide security
	
	// should we call CIS at all or use registry based security?
	if (dwProcessAuthn != -1) 
	{
		void *p = NULL; // Allow everyone
		DWORD dwCapabilities = EOAC_NONE;
		IAccessControl *pIAC;

		// Did the user specify access permssions?
		if (lstrlen(szAccessPermissions))
		{
			if (!GetAccessControl(&pIAC))
				exit(-1);
			p = pIAC;
			dwCapabilities = EOAC_ACCESS_CONTROL;
		}
		
		dwCapabilities |= dwProcessCaps;
		//set process wide security
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
	//create object
	mq.pIID = &IID_IServer;
    mq.pItf = NULL;
    mq.hr = S_OK;
	hr = CoCreateInstanceEx(CLSID_PDCObject, NULL, CLSCTX_SERVER, pcsi, 1, &mq);
	if (FAILED(hr))
	{
		Message(TEXT("Client: CoCreateInstanceEx"), hr);
		CoUninitialize();
		return ;
	}
    else
    {
		IServer*    pIServer = (IServer*)mq.pItf;
		IServer*    pIServerCopy; 
		
		for(;;)
		{
			// Make a copy of the proxy and apply proxy security parameters
			
			hr = CoCopyProxy(pIServer, (IUnknown**)&pIServerCopy);
			if (FAILED(hr))
			{
				Message(TEXT("Client: CoCopyProxy Error"), hr);
				break;
			}
#ifdef UNICODE			
			AuthIdentity.User = szProxyUser;
			AuthIdentity.Domain = szProxyDomain;	
			AuthIdentity.Password = szProxyPassword;
#else
			AuthIdentity.User = (unsigned char*)szProxyUser;
			AuthIdentity.Domain = (unsigned char*)szProxyDomain;	
			AuthIdentity.Password = (unsigned char*)szProxyPassword;
#endif			
			AuthIdentity.UserLength = lstrlen(szProxyUser);
			AuthIdentity.DomainLength = lstrlen(szProxyDomain);
			AuthIdentity.PasswordLength = lstrlen(szProxyPassword);
			//Should we call CSPB at all?
			if (dwProxyAuthn != -1)
			{
				// If yes, use default credentials on the proxy or user specified credentials? 
				if (AuthIdentity.DomainLength == 0 || AuthIdentity.UserLength == 0)
					hr = CoSetProxyBlanket(pIServerCopy, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
					dwProxyAuthn, dwProxyImp,  NULL, dwProxyCaps);
				else 
					hr = CoSetProxyBlanket(pIServerCopy, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, 
					dwProxyAuthn, dwProxyImp,  &AuthIdentity, dwProxyCaps);
			}
			if (FAILED(hr))
			{
				Message(TEXT("Client: CoSetProxyBlanket Error"), hr);
				pIServerCopy->Release();
				break;
			}
		
			//call method
#ifdef UNICODE
			hr = pIServerCopy->AccessFile(szServerFile);
#else
			MultiByteToWideChar(0,0,szServerFile,-1,wszParam, sizeof(wszParam));
			hr = pIServerCopy->AccessFile(wszParam);
#endif
			if (FAILED(hr))
			{
				Message(TEXT("Client: Server Call Error "), hr);
			}		
			pIServerCopy->Release();
			
			
			_tprintf(TEXT("Call Again(Y/N)?"));
			TCHAR ch = (TCHAR)getche();
			
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

		_tprintf(TEXT("Give Server a callback interface pointer(Y/N)?"));
		TCHAR ch = (TCHAR)getche();
		if (ch == 'Y' || ch == 'y')
		{
			// give server an interface pointer for callback
			IUnknown *p;
			sink.QueryInterface(IID_IUnknown, (void**)&p);
			hr = pIServer->SetCallBackInterface(p);
			if (FAILED(hr))
			{
				Message(TEXT("Client: SetCallBackInterface"), hr);
			}
			
			// Now wait for the server to call us. When done, press a key.
			Message(TEXT("Press a key when done...\n\n"), S_OK);
			getche();
		}
		_tprintf(TEXT("Call Server method to impersonate and callback(Y/N)?"));
		ch = (TCHAR)getche();
		if (ch == 'Y' || ch == 'y')
		{
			hr = pIServer->ImpersonateAndCallback();
			if (FAILED(hr))
			{
				Message(TEXT("Client: SetCallBackInterface"), hr);
			}
			// Now wait for the server to call us. When done, press a key.
			Message(TEXT("Press a key when done...\n\n"), S_OK);
			getche();
		}			
		// Shut down the object
		hr = pIServer->Release();
		if (FAILED(hr))
		{
			Message(TEXT("Client: Release Error"), hr);
		}
	}
	CoUninitialize();
	
}  // main

