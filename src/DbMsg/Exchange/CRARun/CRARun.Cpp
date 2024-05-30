//--crarun.cpp----------------------------------------------------------------
//
// implementation of the CExchRuleExt class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include "windows.h"

#include <stdio.h>
#include <MAPIX.H>
#include <MAPIUTIL.H>
#include <MAPIFORM.H>

#include "initguid.h"
#include "exchcli.h"

#include "crarun.h"

CExchRuleExt::CExchRuleExt()
{
}

CExchRuleExt::~CExchRuleExt()
{
}

STDMETHODIMP CExchRuleExt::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    HRESULT hResult = S_OK;

    *ppvObj = NULL;

    if (( IID_IUnknown == riid) || ( IID_IExchangeRuleExt == riid) )
    {
        *ppvObj = (LPUNKNOWN)this;
        AddRef();
    }
    else
        hResult = E_NOINTERFACE;


    return hResult;
}

STDMETHODIMP_(ULONG) CExchRuleExt::AddRef()
{
    ++m_cRef;
    return m_cRef;
}

STDMETHODIMP_(ULONG) CExchRuleExt::Release()
{
	// Use stack parameter, in case we delete ourselves
    ULONG ulCount = --m_cRef;
                         
	if (!ulCount) 
	{ 
		delete this;
	}

	return ulCount;
}

//$--Install------------------------------------------------------------------
// Do we want to run in this context.
// ---------------------------------------------------------------------------
STDMETHODIMP CExchRuleExt::Install (
    LPEXCHANGERULEEXTCALLBACK percb,    // exchange rule callback
    ULONG context)                      // ERCONTEXT_INFO or ERCONTEXT_EXEC
{
    return S_OK;	
}

//$--QueryRelease-------------------------------------------------------------
// This method is reserved for future use.
// ---------------------------------------------------------------------------
STDMETHODIMP CExchRuleExt::QueryRelease()
{
	return S_OK;
}

//$--GetCommand---------------------------------------------------------------
// Display UI and fill out command and display buffers.
// ---------------------------------------------------------------------------
STDMETHODIMP CExchRuleExt::GetCommand (
	LPEXCHANGERULEEXTCALLBACK percb,    // exchange rule callback
	LPTSTR pszCommand,                  // an IN/OUT buffer in which to return
                                        // the encoded command, the buffer may
                                        // be pre-initialized with a previously
                                        // existing command for this provider.
    ULONG cchCommand,                   // length of the buffer given
	LPTSTR pszDisplayName,              // IN/OUT, as the previous buffer,
                                        // but for the display string
    ULONG cchDisplayName)               // length of the buffer given
{
    HRESULT hr;
    HWND hWnd;
    DWORD dwError;
    TCHAR szFileName[_MAX_PATH];
    TCHAR szInitialFileName[_MAX_PATH] = {""};

    if ((NULL == pszCommand) ||
        (NULL == pszDisplayName))
    {
        return MAPI_E_INVALID_PARAMETER;
    }

    sscanf (pszCommand, "launch %s", szInitialFileName);

    hr = percb->GetWindow (&hWnd);

    if (FAILED(hr))
        return hr;
    
    OPENFILENAME ofn;

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = hWnd;
    ofn.hInstance = GetModuleHandle(NULL);
    ofn.lpstrFilter = "Programs\0*.exe;*.bat;*.com\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = szInitialFileName;
    ofn.nMaxFile = _MAX_PATH;
    ofn.lpstrFileTitle = szFileName;
    ofn.nMaxFileTitle = _MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = "Program to Launch";
    ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = "exe";
    ofn.lCustData = 0;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;

    if (!GetOpenFileName (&ofn))
    {
        dwError = CommDlgExtendedError();
        
        if (dwError)
            return S_FALSE;
        
        // else hit Cancel
    }
    else
    {
        if (strlen (ofn.lpstrFile) + sizeof ("launch ") > cchCommand)
        {
            return TYPE_E_BUFFERTOOSMALL;
        }

        if (strlen (ofn.lpstrFile) > cchDisplayName)
        {
            return TYPE_E_BUFFERTOOSMALL;
        }

        sprintf (pszCommand, "launch %s", ofn.lpstrFile);
        strcpy (pszDisplayName, ofn.lpstrFile);
    }

    return S_OK;
}

//$--QueryCommandDisplayName--------------------------------------------------
//  What should the client display in it's display box.
// ---------------------------------------------------------------------------
STDMETHODIMP CExchRuleExt::QueryCommandDisplayName(
	LPEXCHANGERULEEXTCALLBACK percb,    // exchange rule callback
	LPCTSTR pszCommand,                 // command buffer
	LPTSTR pszDisplayName,              // OUT buffer for the display name
    ULONG cchDisplayName)               // size of buffer
{
	TCHAR szFileName[_MAX_PATH];

    if ((NULL == pszCommand) ||
        (NULL == pszDisplayName))
    {
        return MAPI_E_INVALID_PARAMETER;
    }

    sscanf (pszCommand, "launch %s", szFileName);

    if (strlen (szFileName) > cchDisplayName)
    {
        return TYPE_E_BUFFERTOOSMALL;
    }

    strcpy (pszDisplayName, szFileName);

	return S_OK;
}

//$--Command------------------------------------------------------------------
//  Run the command.
// ---------------------------------------------------------------------------
STDMETHODIMP CExchRuleExt::Command(
	LPEXCHANGERULEEXTCALLBACK percb,    // exchange rule callback
	LPCTSTR pszCommand,                 // IN command to run
	ULONG cb, LPENTRYID peid)           // EntryID of the message
{
	HRESULT hr;
    HWND hWnd;
    TCHAR szFileName[_MAX_PATH];

    if ((NULL == pszCommand) ||
        (NULL == peid))
    {
        return MAPI_E_INVALID_PARAMETER;
    }

    sscanf (pszCommand, "launch %s", szFileName);
    
    hr = percb->GetWindow (&hWnd);

    if (FAILED(hr))
        return hr;

    if ((HINSTANCE)32 < ShellExecute (hWnd, NULL, szFileName, NULL, NULL, SW_SHOWNORMAL))
    {
        return S_OK;
    }
    else
    {
        return S_FALSE;
    }
}
