// Microsoft Corporation Copyright 1999 
// WBWAB.cpp : Implementation of CWBWAB
#include "stdafx.h"
#include "WBAddrBook.h"
#include "WBWAB.h"
#include <wab.h>
#include <wabapi.h>
#include <exdisp.h>
#include <subsmgr.h>
#include <mshtml.h>
#include <shlobj.h>
#include <wininet.h>
#include <intshcut.h>
 
#include <initguid.h>
// WebBrowser Command Group ID (to do Find, Internet Options, View Source)
#include "WBCmdGroup.h"

/////////////////////////////////////////////////////////////////////////////
// CWBWAB

STDMETHODIMP CWBWAB::get_WebBrowser(LPDISPATCH* ppWebBrowser)
{
   ATLTRACENOTIMPL(_T("CWBWAB::get_WebBrowser"));
}

STDMETHODIMP CWBWAB::putref_WebBrowser(LPDISPATCH pWebBrowser)
{
	m_spWebBrowser = pWebBrowser;
	return S_OK;
}

STDMETHODIMP CWBWAB::get_Offline(VARIANT_BOOL * bOffline)
{
	HRESULT hr = S_FALSE;
    INTERNET_CONNECTED_INFO ci;
	ULONG ci_len = sizeof(ci);

	if (!bOffline)
	{
		hr = E_INVALIDARG;
	}
	else
	{
		memset(&ci, 0, sizeof(ci));
		if (InternetQueryOption(NULL, INTERNET_OPTION_CONNECTED_STATE, &ci, &ci_len))
		{
			hr = S_OK;
			*bOffline = (ci.dwConnectedState != INTERNET_STATE_CONNECTED);
		}
	}
	return hr;
}

STDMETHODIMP CWBWAB::put_Offline(VARIANT_BOOL bOffline)
{
	HRESULT hr = S_FALSE;
    INTERNET_CONNECTED_INFO ci;

    memset(&ci, 0, sizeof(ci));
    if(bOffline) 
	{
        ci.dwConnectedState = INTERNET_STATE_DISCONNECTED_BY_USER;
        ci.dwFlags = ISO_FORCE_DISCONNECTED;
    } 
	else 
	{
        ci.dwConnectedState = INTERNET_STATE_CONNECTED;
    }
    if (InternetSetOption(NULL, INTERNET_OPTION_CONNECTED_STATE, &ci, sizeof(ci)))
	{
		hr = S_OK;
	}
	return hr;
}

STDMETHODIMP CWBWAB::ShowAddressBook(LONG hWnd)
{
	HRESULT hr = S_OK;

	if(!m_hInstWAB)
	{
		// load the WAB DLL path from the registry
		// (sample code similar to "Loading Wab32.dll at Run Time" topic
		// in INetSDK "Internet Explorer Address Book" article)
		const static TCHAR lpszWABRegPathKey[] = TEXT("Software\\Microsoft\\WAB\\DLLPath");
		const static TCHAR lpszWABDll[] = TEXT("WAB32.dll");
		DWORD  dwType = 0;
		TCHAR  szWABDllPath[MAX_PATH] = TEXT("");
		ULONG  cbData = sizeof(szWABDllPath);
		HKEY hKey = NULL;    
		if (ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE,
			lpszWABRegPathKey, 0, KEY_READ, &hKey))
		{
			if (ERROR_SUCCESS == RegQueryValueEx(hKey, TEXT(""), NULL, &dwType, 
				                                 (LPBYTE) szWABDllPath, &cbData))
			{
				// Load the WAB library based on the WAB DLL path
				m_hInstWAB = LoadLibrary(lstrlen(szWABDllPath) ? szWABDllPath : lpszWABDll);
			}
			RegCloseKey(hKey);
		}
	}
	if(m_hInstWAB)
	{
		LPWABOPEN lpfnWABOpen = NULL;
		LPWABOBJECT lpWABObject;
		LPADRBOOK lpAddrBook;

		if (lpfnWABOpen = (LPWABOPEN) GetProcAddress(m_hInstWAB, "WABOpen"))
		{
			hr = lpfnWABOpen(&lpAddrBook, &lpWABObject, NULL, 0);
		}
		if (lpAddrBook)
		{
			ULONG hParentWnd = (ULONG)hWnd;
			ADRPARM addrParm;

			memset(&addrParm, '\0', sizeof(addrParm));
			addrParm.ulFlags = DIALOG_SDI;
			addrParm.lpszCaption = TEXT("My Favorite Browser");
			hr = lpAddrBook->Address(&hParentWnd, &addrParm, NULL);
		}
	}
	return hr;
}

// from Internet Mail and News INetSDK article...

STDMETHODIMP CWBWAB::ShowClient(LONG hWnd, TCHAR * szClient)
{
	USES_CONVERSION;
	HKEY hKey = NULL;
	DWORD  dwType = 0, cbData;
	HRESULT hr = S_FALSE;
	TCHAR szKeyValue[MAX_PATH];

   CComBSTR bstrClientNameKey(TEXT("SOFTWARE\\Clients"));
   bstrClientNameKey.Append(szClient);

	// get the client name
   if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
#ifdef UNICODE
									 bstrClientNameKey.Copy(), 
#else
                                     OLE2A(bstrClientNameKey),
#endif
                                     0, KEY_READ, &hKey))
   {
		return S_FALSE;
   }

   cbData = MAX_PATH;
	if (ERROR_SUCCESS == RegQueryValueEx(hKey, TEXT(""), NULL, &dwType, 
										(LPBYTE)szKeyValue, &cbData))
	{
		RegCloseKey(hKey);

		// construct keyname for client's shell open command, and get the command string
		CComBSTR bstrOpenCommandKey(bstrClientNameKey);
		bstrOpenCommandKey.Append(TEXT("\\"));
		bstrOpenCommandKey.Append(&szKeyValue[0]);
		bstrOpenCommandKey.Append(TEXT("\\shell\\open\\command"));

	   // get the shell open command string
      if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
#ifdef UNICODE
   										bstrOpenCommandKey.Copy(), 
#else
                                        OLE2A(bstrOpenCommandKey),
#endif
                                        0, KEY_READ, &hKey))
      {
   		return S_FALSE;
      }
      // read the open command string
      cbData = MAX_PATH;
		if (ERROR_SUCCESS == RegQueryValueEx(hKey, TEXT(""), NULL, &dwType, 
														 (LPBYTE)szKeyValue, &cbData))
		{
			// launch the client 
         // isolate the parameters from the pathname
         TCHAR *szParam;
#ifdef UNICODE
         szParam = wcsstr(szKeyValue, TEXT("\" "));
#else
         szParam = strstr(szKeyValue, TEXT("\" "));
#endif
         if (szParam)
         {
            *(++szParam) = TCHAR('\0');
            ++szParam;
         }
         ShellExecute((HWND)hWnd, TEXT("open"), szKeyValue, szParam, TEXT(""), SW_SHOW);
      } 
		RegCloseKey(hKey);
      hr = S_OK;
	}
   return hr;
}

STDMETHODIMP CWBWAB::ShowMail(LONG hWnd)
{
   return ShowClient(hWnd, TEXT("\\Mail"));
}

STDMETHODIMP CWBWAB::ShowNews(LONG hWnd)
{
   return ShowClient(hWnd, TEXT("\\News"));
}

// the following code for properties and find dialog make use of undocumented
// IE4 features that could change in the future. For more info see:
// Article ID: Q175513: Invoke Find, View Source, Options dialogs for WebBrowser 
STDMETHODIMP CWBWAB::ShowWBCmdGroup(int cmdID)
{
   HRESULT hr;
   LPDISPATCH lpDocument;
   
   hr = m_spWebBrowser->get_Document(&lpDocument);
   if (lpDocument)
   {
      CComQIPtr<IOleCommandTarget, &IID_IOleCommandTarget> lpOleCommandTarget(lpDocument);
      lpDocument->Release();
      // Invoke the given command id for the WebBrowser control
      hr = lpOleCommandTarget->Exec(&CGID_IWebBrowser, cmdID, 0, NULL, NULL);
   }
   return hr;
}

STDMETHODIMP CWBWAB::ShowProperties(void)
{
   return ShowWBCmdGroup(CWBCmdGroup.HTMLID_OPTIONS);
}


STDMETHODIMP CWBWAB::ShowFind(void)
{
   return ShowWBCmdGroup(CWBCmdGroup.HTMLID_FIND);
}

STDMETHODIMP CWBWAB::ShowViewSource(void)
{
   return ShowWBCmdGroup(CWBCmdGroup.HTMLID_VIEWSOURCE);
}

typedef UINT (CALLBACK* LPFNORGFAV)(HWND, LPTSTR);

STDMETHODIMP CWBWAB::ShowOrganizeFavorites(LONG hWnd) 
{
   HRESULT hr = S_FALSE;
   HMODULE hMod;

   if (hMod = (HMODULE)LoadLibrary(TEXT("shdocvw.dll")))
   {
      LPFNORGFAV lpfnDoOrganizeFavDlg = (LPFNORGFAV)GetProcAddress(hMod, "DoOrganizeFavDlg");
      if (lpfnDoOrganizeFavDlg)
      {
         TCHAR szPath[MAX_PATH];

         hr = SHGetSpecialFolderPath((HWND)hWnd, szPath, CSIDL_FAVORITES, TRUE);
         if (SUCCEEDED(hr))
            lpfnDoOrganizeFavDlg((HWND)hWnd, szPath);
      }
      FreeLibrary(hMod);
   }
   return hr;
}

STDMETHODIMP CWBWAB::ShowUpdateSubscriptions(void) 
{
   ISubscriptionMgr* pSubscriptionMgr;

   HRESULT hr = CoCreateInstance(CLSID_SubscriptionMgr, NULL, 
                                 CLSCTX_INPROC_SERVER, IID_ISubscriptionMgr, 
                                 (LPVOID*)&pSubscriptionMgr);

   if (SUCCEEDED(hr))
   {
      pSubscriptionMgr->UpdateAll();
      pSubscriptionMgr->Release();
   }
   return hr;
}


/////////////
// helper routines to convert a PIDL into a Variant that Navigate2 will accept
// for more info see Q167834

// macros for walking PIDLs
#define _ILSkip(pidl, cb)       ((LPITEMIDLIST)(((BYTE*)(pidl))+cb))
#define _ILNext(pidl)           _ILSkip(pidl, (pidl)->mkid.cb)

// Get the size of the PIDL by walking the item id list
UINT ILGetSize(LPITEMIDLIST pidl)
{
  UINT cbTotal = 0;
  if (pidl)
  {
     cbTotal += sizeof(pidl->mkid.cb);       // Null terminator
     while (pidl->mkid.cb)
     {
        cbTotal += pidl->mkid.cb;
        pidl = _ILNext(pidl);
     }
  }

  return cbTotal;
}

// Use the shell's IMalloc implementation to free resources
HRESULT SHFree(LPVOID pData)
{
  HRESULT hr;
  LPMALLOC pMalloc = NULL;

  if (SUCCEEDED(hr = SHGetMalloc(&pMalloc)))
  {
     pMalloc->Free((LPVOID)pData);
     pMalloc->Release();
  }

  return hr;
}

// Allocate a SAFEARRAY of cbData size and pack pData into it
LPSAFEARRAY MakeSafeArrayFromData(LPBYTE pData, DWORD cbData)
{
  LPSAFEARRAY psa;

  if (!pData || 0 == cbData)
  {
     return NULL;  // nothing to do
  }

  // create a one-dimensional safe array of BYTEs
  psa = SafeArrayCreateVector(VT_UI1, 0, cbData);

  if (psa) 
  {
     // copy data into the area in safe array reserved for data
     // Note we party directly on the pointer instead of using locking/ 
     // unlocking functions.  Since we just created this and no one
     // else could possibly know about it or be using it, this is OK.
     memcpy(psa->pvData,pData,cbData);
  }

  return psa;
}

// Pack a PIDL into a VARIANT
HRESULT InitVARIANTFromPidl(LPVARIANT pvar, LPITEMIDLIST pidl)
{
  if (!pidl || !pvar)
  {
     return E_POINTER;
  }

  // Get the size of the pidl and allocate a SAFEARRAY of 
  // equivalent size
  UINT cb = ILGetSize(pidl);
  LPSAFEARRAY psa = MakeSafeArrayFromData((LPBYTE)pidl, cb);
  if (!psa) 
  {
     VariantInit(pvar);
     return E_OUTOFMEMORY;
  }

  V_VT(pvar) = VT_ARRAY|VT_UI1;
  V_ARRAY(pvar) = psa;
  return NOERROR;
}

STDMETHODIMP CWBWAB::ShowMyComputer(LONG hWnd) 
{
    HRESULT hr = S_FALSE;
    LPITEMIDLIST pPIDL;

    if (m_spWebBrowser)
    {
        CComVariant vtEmpty;
        CComVariant vtPIDL;
        if (!SHGetSpecialFolderLocation((HWND)hWnd, CSIDL_DRIVES, &pPIDL))
        {
            hr = InitVARIANTFromPidl(&vtPIDL, pPIDL);
            if (hr == NOERROR)
            {
                hr = m_spWebBrowser->Navigate2(&vtPIDL, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
            }
            if (pPIDL)
            {
                SHFree((LPVOID)pPIDL);
            }
        }
    }
    return hr;
}

// Routines to obtain the URL for a shortcut (*.lnk), modified from IEFavMenu sample:
// http://support.microsoft.com/support/kb/articles/q184/7/80.asp
//
// It would be great to do this in J++ or VB. Problem is that the InternetShortcut
// class is not in the shdocvw type library! The others we need are, but since
// we have to do part of the work in C++, might as well do it all
// so can't be used from VB or VJ

//
// Resolves an Internet Shortcut to its URL
//
HRESULT ResolveInternetShortcut(LPCTSTR lpszLinkFile, LPTSTR* lpszURL)
{
   IUniformResourceLocator* pUrlLink = NULL;

   *lpszURL = NULL;  // Assume failure

   HRESULT hr = CoCreateInstance(CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER,
                                 IID_IUniformResourceLocator, (void**)&pUrlLink);

   if (SUCCEEDED(hr))
   {
      IPersistFile* pPersistFile = NULL;

      hr = pUrlLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);
      if (SUCCEEDED(hr))
      {
         // Ensure that the string is Unicode. 
         WORD wsz[MAX_PATH];  
         MultiByteToWideChar(CP_ACP, 0, lpszLinkFile, -1, wsz, MAX_PATH);

         // Load the Internet Shortcut from persistent storage.
         hr = pPersistFile->Load(wsz, STGM_READ);
         if (SUCCEEDED(hr))
            hr = pUrlLink->GetURL(lpszURL);

         pPersistFile->Release();
      }

      pUrlLink->Release();
   }

   return hr;
}  

//
// Resolves a Shell Link to its actual folder location
//
HRESULT ResolveLink(LPCTSTR lpszLinkFile, LPTSTR* lpszURL)
{
   IShellLink* pShellLink = NULL;

   *lpszURL = NULL;   // Assume failure

   HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                                 IID_IShellLink, (void**)&pShellLink); 
   if (SUCCEEDED(hr))
   {
      IPersistFile* pPersistFile = NULL;

      hr = pShellLink->QueryInterface(IID_IPersistFile, (void**)&pPersistFile);
      if (SUCCEEDED(hr))
      {
         // Ensure that the string is Unicode. 
         WORD wsz[MAX_PATH];  
         MultiByteToWideChar(CP_ACP, 0, lpszLinkFile, -1, wsz, MAX_PATH);

         // Load the shortcut.from persistent storage
         hr = pPersistFile->Load(wsz, STGM_READ);
         if (SUCCEEDED(hr))
         {
            WIN32_FIND_DATA wfd;      

            //hr = pShellLink->Resolve(m_hWnd, SLR_NO_UI); 
            hr = pShellLink->Resolve(NULL, SLR_NO_UI); 
            if (hr == NOERROR)
            {
               // Get the path to the link target. 
	   		   *lpszURL = (LPTSTR)malloc(MAX_PATH);  // Must remember to Free later

               hr = pShellLink->GetPath(*lpszURL, MAX_PATH - 1, (WIN32_FIND_DATA*)&wfd, SLGP_UNCPRIORITY);
            }
         }

         pPersistFile->Release();
      }

      pShellLink->Release();
   }

   return hr;
}

STDMETHODIMP CWBWAB::GetURL(VARIANT vPath, LPVARIANT pvURL)
{
	USES_CONVERSION;
	LPTSTR lpszFileName = NULL, lpszURL=NULL;
	SHFILEINFO psfi;
	HRESULT hr = S_FALSE;

    if (!pvURL)
    {
        return E_INVALIDARG;
    }
    VariantClear(pvURL);
	
#ifdef UNICODE
	lpszFileName = V_BSTR(&vPath);
#else
	lpszFileName = OLE2A(V_BSTR(&vPath));
#endif

	SHGetFileInfo(lpszFileName, NULL, &psfi, sizeof(psfi), SHGFI_ATTRIBUTES|SHGFI_TYPENAME);

	if  (!strcmp(psfi.szTypeName, _T("Internet Shortcut")))
	{
	   hr = ResolveInternetShortcut(lpszFileName, &lpszURL);
	}
	else
	{
	   hr = ResolveLink(lpszFileName, &lpszURL);
	}

	CComVariant vTemp(lpszURL);

	if (V_VT(pvURL) & VT_BYREF)
		return VariantCopyInd(pvURL, &vTemp);
	else
		return VariantCopy(pvURL, &vTemp);

	VariantClear(&vTemp);
#ifndef UNICODE
     if (lpszFileName)
        free(lpszFileName);
     if (lpszURL)
        free(lpszURL);
#endif

	return S_OK;
}

