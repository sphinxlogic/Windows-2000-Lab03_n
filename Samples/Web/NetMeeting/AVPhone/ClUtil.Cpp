//****************************************************************************
//  Module:     AVPHONE.EXE     
//  File:       CLUTIL.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-1997
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"


//****************************************************************************
//
// CLASS RefCount
//
//****************************************************************************

//****************************************************************************
//
// Constructor
//
//****************************************************************************

RefCount::RefCount(void)
{
	m_cRef = 1;
}

//****************************************************************************
//
// Destructor
//
//****************************************************************************

RefCount::~RefCount(void)
{
}


//****************************************************************************
//
// ULONG STDMETHODCALLTYPE RefCount::AddRef(void)
//
//****************************************************************************

ULONG STDMETHODCALLTYPE RefCount::AddRef(void)
{
   ASSERT(m_cRef >= 0);

   InterlockedIncrement(&m_cRef);

   return (ULONG) m_cRef;
}


//****************************************************************************
//
// ULONG STDMETHODCALLTYPE RefCount::Release(void)
//
//****************************************************************************

ULONG STDMETHODCALLTYPE RefCount::Release(void)
{
	if (0 == InterlockedDecrement(&m_cRef))
	{
		delete this;
		return 0;
	}

	ASSERT(m_cRef > 0);
	return (ULONG) m_cRef;
}


//****************************************************************************
//
// CLASS CNotify
//
//****************************************************************************

//****************************************************************************
//
// Constructor
//
//****************************************************************************

CNotify::CNotify() :
	m_pcnpcnt(NULL),
    m_pcnp(NULL),
    m_dwCookie(0),
    m_pUnk(NULL)
{
}


//****************************************************************************
//
// destructor
//
//****************************************************************************

CNotify::~CNotify()
{
	Disconnect(); // Make sure we're disconnected
}


//****************************************************************************
//
// HRESULT CNotify::Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN)
//
// Connects the sink to the container
//
//****************************************************************************

HRESULT CNotify::Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN)
{
	HRESULT hr;

	ASSERT(0 == m_dwCookie);

	// Get the connection container
	hr = pUnk->QueryInterface(IID_IConnectionPointContainer, (void **)&m_pcnpcnt);
	if (SUCCEEDED(hr))
	{
		// Find an appropriate connection point
		hr = m_pcnpcnt->FindConnectionPoint(riid, &m_pcnp);
		if (SUCCEEDED(hr))
		{
			ASSERT(NULL != m_pcnp);
			// Connect the sink object
			hr = m_pcnp->Advise((IUnknown *)pUnkN, &m_dwCookie);
		}
	}

	if (FAILED(hr))
	{
		m_dwCookie = 0;
	}
	else
	{
    	m_pUnk = pUnk; // keep around for caller
    }

	return hr;
}


//****************************************************************************
//
// HRESULT CNotify::Disconnect (void)
//
// Disconnects the sink from the container
//
//****************************************************************************

HRESULT CNotify::Disconnect (void)
{
    if (0 != m_dwCookie)
    {

        // Disconnect the sink object
        m_pcnp->Unadvise(m_dwCookie);
        m_dwCookie = 0;

        m_pcnp->Release();
        m_pcnp = NULL;

        m_pcnpcnt->Release();
        m_pcnpcnt = NULL;

        m_pUnk = NULL;
    }

    return S_OK;
}


//****************************************************************************
//
// CLASS BSTRING
//
//****************************************************************************

//****************************************************************************
//
// Constructor
//
//****************************************************************************

// We don't support construction from an ANSI string in the Unicode build.
#if !defined(UNICODE)

BSTRING::BSTRING(LPCSTR lpcString)
{
	m_bstr = NULL;

	// Compute the length of the required BSTR, including the null
	int cWC =  MultiByteToWideChar(CP_ACP, 0, lpcString, -1, NULL, 0);
	if (cWC <= 0)
		return;

	// Allocate the BSTR, including the null
	m_bstr = SysAllocStringLen(NULL, cWC - 1); // SysAllocStringLen adds another 1

	ASSERT(NULL != m_bstr);
	if (NULL == m_bstr)
	{
		return;
	}

	// Copy the string
	MultiByteToWideChar(CP_ACP, 0, lpcString, -1, (LPWSTR) m_bstr, cWC);

	// Verify that the string is null terminated
	ASSERT(0 == m_bstr[cWC - 1]);
}

#endif // !defined(UNICODE)


//****************************************************************************
//
// CLASS BTSTR
//
//****************************************************************************

//****************************************************************************
//
// Constructor
//
//****************************************************************************

BTSTR::BTSTR(BSTR bstr)
{
	m_psz = PszFromBstr(bstr);
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

BTSTR::~BTSTR()
{
	if (NULL != m_psz)
		LocalFree(m_psz);
}

//****************************************************************************
//
// LPTSTR PszFromBstr(BSTR bstr)
//
// Converts a BSTR to a LPSTR
//
//****************************************************************************

LPTSTR PszFromBstr(BSTR bstr)
{
	if (NULL == bstr)
		return NULL;
	int cch =  WideCharToMultiByte(CP_ACP, 0, (LPWSTR)bstr, -1, NULL, 0, NULL, NULL);
	if (cch <= 0)
		return NULL;

	LPTSTR psz = (char *)LocalAlloc(LPTR,cch);
	if (NULL == psz)
		return NULL;

	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)bstr, -1, psz, cch+1, NULL, NULL);
	return psz;
}

