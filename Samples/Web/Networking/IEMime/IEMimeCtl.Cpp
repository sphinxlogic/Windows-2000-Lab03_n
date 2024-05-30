
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// IEMimeCtl.cpp : Implementation of CIEMimeCtl
#include "stdafx.h"

#include "IEMime.h"
#include "IEMimeCtl.h"

#include "dispids.h"

/////////////////////////////////////////////////////////////////////////////
// CIEMimeCtl


HRESULT CIEMimeCtl::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;

	HDC hdc  = di.hdcDraw;
	HBRUSH    hOldBrush, hBrush;
    HPEN      hOldPen, hPen;
	hPen = (HPEN)GetStockObject(BLACK_PEN);
    hOldPen = (HPEN)SelectObject(hdc, hPen);
    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SetBkMode(di.hdcDraw,TRANSPARENT);
	SetTextColor(di.hdcDraw,RGB(0,0,255));
	if (!m_bstrCFFormat) // Empty - don't draw text
		return S_OK;

	ATLTRACE(_T("    m_bstrCFFormat=%s\n"),(LPTSTR)m_bstrCFFormat);
	rc.left += 5; // small left margin
	DrawText(di.hdcDraw, m_bstrCFFormat, m_bstrCFFormat.length(), &rc, 	 
		DT_LEFT | DT_WORD_ELLIPSIS | DT_SINGLELINE);

	SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

	return S_OK;
}

STDMETHODIMP CIEMimeCtl::get_URL(BSTR * pVal)
{	
	//*pVal = m_bstrURL.copy();
	*pVal = ::SysAllocString(static_cast<const wchar_t*>(m_bstrURL));

	return S_OK;
}

STDMETHODIMP CIEMimeCtl::put_URL(BSTR newVal)
{	
	m_bstrURL = newVal;

	FireOnChanged(DISPID_URL);

	if (!m_bstrURL) // NULL string
		return S_OK;

	if (READYSTATE_LOADING != m_nReadyState)  // Wait until control is done loading before
		Reload();							  // firing off download

    return S_OK;
}

STDMETHODIMP CIEMimeCtl::get_Media(BSTR * pVal)
{
	//*pVal = m_bstrMedia.copy();
	*pVal = ::SysAllocString(static_cast<const wchar_t*>(m_bstrMedia));

	return S_OK;
}

STDMETHODIMP CIEMimeCtl::put_Media(BSTR newVal)
{	
	m_bstrMedia = newVal;

	FireOnChanged(DISPID_MEDIA);

    return S_OK;
}

STDMETHODIMP CIEMimeCtl::get_Cfformat(BSTR * pVal)
{
	*pVal = m_bstrCFFormat.copy();

	return S_OK;
}

STDMETHODIMP CIEMimeCtl::AboutBox()
{
	// The following is necessary to prepare the frame for showing a modal dialog box
	HRESULT hr;
	OLEINPLACEFRAMEINFO frameInfo;
	RECT rcPos, rcClip;
	CComPtr<IOleInPlaceFrame> spInPlaceFrame;
	CComPtr<IOleInPlaceUIWindow> spInPlaceUIWindow;
	frameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);
	HWND hwndFrame = NULL;

	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->GetWindowContext(&spInPlaceFrame,
			&spInPlaceUIWindow, &rcPos, &rcClip, &frameInfo);
		if (spInPlaceFrame)
		{
			spInPlaceFrame->GetWindow(&hwndFrame);
			hr = spInPlaceFrame->EnableModeless(FALSE);
			if (FAILED(hr))
				return S_OK;  // Failed, but we don't want to send errors back to script
		}
	}
	// -------------------------------------------------------------------------------

    ::MessageBox(hwndFrame, _T("This is My Control"), _T("About iemime"), MB_OK | MB_TASKMODAL);
	
	// Tell frame our modal dialog box has gone away
	if (spInPlaceFrame)
	{
		spInPlaceFrame->EnableModeless(TRUE);
	}
	// --------------------------------------------

	return S_OK;
}

STDMETHODIMP CIEMimeCtl::Reload()
{
	if (!m_bstrURL) // NOOP
		return S_OK;
	else
	{
		m_nReadyState = READYSTATE_INTERACTIVE;
		FireOnChanged(DISPID_READYSTATE);
		CBindStatusCallback2<CIEMimeCtl>::Download(this, OnData, m_bstrURL, m_spClientSite, FALSE);
	}

	return S_OK;
}

HRESULT CIEMimeCtl::PreBindMoniker(CComPtr<IBindCtx> pBindCtx, CComPtr<IMoniker> pMoniker)
{
	HRESULT hr = S_OK;

	if (!(m_bstrMedia)) // No MIME registration of our own, default
		return S_OK;    // will give us an accept-type of "*/*"

	LPSTR rgszTypes[1];
	CLIPFORMAT cfFormats[1];
	cfFormats[0] = CF_NULL;
	
	// Register m_bstrMedia as a media-type. This will either give us
	// the CLIPFORMAT of an existing media-type or create a new one for us.
	rgszTypes[0] = (LPSTR)(m_bstrMedia);
	if (SUCCEEDED(hr))
		hr = RegisterMediaTypes(1, (LPSTR*)&rgszTypes, cfFormats);

	FORMATETC rgfmtetc[1] = 
		{ {CF_NULL, NULL, DVASPECT_CONTENT, -1, TYMED_NULL} };
	IEnumFORMATETC *pMyEtc = NULL;

	// Create and register a FORMATETC enumerator for our (potentially custom)
	// media type. Basically this has the equivalent effect of telling URLMON
	// to use this media type for the HTTP Accept-types header.
	// (this won't come into play for file://)
	rgfmtetc[0].cfFormat = cfFormats[0];
	hr = CreateFormatEnumerator (1, rgfmtetc, &pMyEtc);
	if (SUCCEEDED(hr) && pMyEtc)
	{
		hr = RegisterFormatEnumerator(pBindCtx, pMyEtc, 0);
		_ASSERTE(SUCCEEDED(hr));
	}
	
	return hr;
}

void CIEMimeCtl::OnBindingFailure(HRESULT hr, LPCWSTR szError)
{
	if (NULL != szError && NULL != *szError)
		m_bstrCFFormat = szError;
	else
	{
		// Convert HR to human-readable string
		if (INET_E_NO_VALID_MEDIA == hr)
			m_bstrCFFormat = _T("<Resource at URL does not match Media type>");
		else
			m_bstrCFFormat = _T("<Failed to download>");
	}

	m_nReadyState = READYSTATE_COMPLETE;
	FireOnChanged(DISPID_READYSTATE);
	FireViewChange();

}

//OnData will be used as a callback function by the CBindStatusCallback object.
//OnData will be called periodically with data from the asynchronous transfer
void CIEMimeCtl::OnData(CBindStatusCallback2<CIEMimeCtl>* pbsc, BYTE* pBytes, DWORD dwSize,
			DWORD grfBSCF, FORMATETC *pformatetc, STGMEDIUM *pstgmed)
{
	static TCHAR formatname[MAX_PATH];

	GetClipboardFormatName(pformatetc->cfFormat, formatname, MAX_PATH);
	m_bstrCFFormat = formatname;

	FireOnChanged(DISPID_CFFORMAT);

	if (grfBSCF & BSCF_LASTDATANOTIFICATION)
	{
		Fire_Complete(); // Fire the "Complete" event
		m_nReadyState = READYSTATE_COMPLETE;
		FireOnChanged(DISPID_READYSTATE);
		FireViewChange();
	}

}

// From ATLCTL.H, line 842
STDMETHODIMP CIEMimeCtl::FreezeEvents(BOOL bFreeze)
{
	ATLTRACE(_T("IOleControlImpl::FreezeEvents\n"));
	if (bFreeze)
		m_nFreezeEvents++;
	else
	{
		m_nFreezeEvents--;
		// Modified this so that we wait until container is
		// set before downloading
		if (!m_nFreezeEvents)
		{
			// Let's go!
			Reload();
		}
	}

	return S_OK;
}