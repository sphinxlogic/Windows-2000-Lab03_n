
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// percyctl.h : Declaration of the Cpercyctl

#ifndef __PERCYCTL_H_
#define __PERCYCTL_H_

#include "resource.h"       // main symbols
#include "perhist.h"


/////////////////////////////////////////////////////////////////////////////
// IPersistHistoryImpl

template <class T>
class ATL_NO_VTABLE IPersistHistoryImpl
{
public:
	// IUnknown
	//
	STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject) = 0;
	_ATL_DEBUG_ADDREF_RELEASE_IMPL(IPersistStreamInitImpl)

	// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		ATLTRACE(_T("IPersistStreamInitImpl::GetClassID\n"));
		T* pT = static_cast<T*>(this);
		*pClassID = pT->GetObjectCLSID();
		return S_OK;
	}

	STDMETHOD(LoadHistory)( IStream __RPC_FAR *pStream,
            /* [in] */ IBindCtx __RPC_FAR *pbc)
	{ return S_OK;}
        
	STDMETHOD(SaveHistory)( IStream __RPC_FAR *pStream)
	{ return S_OK;}

	STDMETHOD(SetPositionCookie)( DWORD dwPositioncookie)
	{ return S_OK;}
       
	STDMETHOD(GetPositionCookie)( DWORD dwPositioncookie)
	{ return S_OK;}
        
};



/////////////////////////////////////////////////////////////////////////////
// Cpercyctl
class ATL_NO_VTABLE Cpercyctl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cpercyctl,&CLSID_percyctl>,
	public CComControl<Cpercyctl>,
	public IDispatchImpl<Ipercyctl, &IID_Ipercyctl, &LIBID_PERCYLib>,
	public IPersistStreamInitImpl<Cpercyctl>,
	public IOleControlImpl<Cpercyctl>,
	public IOleObjectImpl<Cpercyctl>,
	public IOleInPlaceActiveObjectImpl<Cpercyctl>,
	public IViewObjectExImpl<Cpercyctl>,
	public IOleInPlaceObjectWindowlessImpl<Cpercyctl>,
	public IObjectSafetyImpl<Cpercyctl, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IPersistHistoryImpl<Cpercyctl>
	{
public:
	CContainedWindow m_ctlEdit;
	
	char m_pstr[20];

	DWORD  m_dwSafety;

	Cpercyctl():m_ctlEdit(_T("Edit"), this, 1)
	{
 	
		m_bWindowOnly = TRUE; 
		m_pstr[0] = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PERCYCTL)

BEGIN_COM_MAP(Cpercyctl) 
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(Ipercyctl)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY_IMPL(IPersistHistory)
END_COM_MAP()

BEGIN_PROPERTY_MAP(Cpercyctl)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(Cpercyctl)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
ALT_MSG_MAP(1)
	// Replace this with message map entries for subclassed Edit
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		m_ctlEdit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER);
		// Set the initial value to whatever was passed to us using IPersistHistory
		::SetWindowText( m_ctlEdit.m_hWnd, (LPCTSTR) m_pstr);
		return 0;
	}
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<Cpercyctl>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlEdit.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IPersistHistory
	STDMETHOD(LoadHistory)( IStream __RPC_FAR *pStream,
            /* [in] */ IBindCtx __RPC_FAR *pbc)
	{ 
		// LoadHistory is called if the browser has anything to  persist ino the control
		// we just put that into our string for later use when the edit control get's initialized
		pStream->Read( m_pstr,19,NULL);
		return S_OK;
	}
        
	STDMETHOD(SaveHistory)( IStream __RPC_FAR *pStream)
	{ 
		// Get the content from the edit control.
		// and write it to the stream supplied
		::GetWindowText(m_ctlEdit.m_hWnd, (LPTSTR) m_pstr, 19);
		pStream->Write( m_pstr,19, NULL);
		return S_OK;
	}

// IObjectSafety so we support IPersistHistory as safe as well.
	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
	{
		ATLTRACE(_T("IObjectSafetyImpl::GetInterfaceSafetyOptions\n"));
		if (pdwSupportedOptions == NULL || pdwEnabledOptions == NULL)
			return E_POINTER;
		HRESULT hr = S_OK;
		if (riid == IID_IDispatch || riid == IID_IPersistHistory)
		{
			*pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
			*pdwEnabledOptions = m_dwSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		}
		else
		{
			*pdwSupportedOptions = 0;
			*pdwEnabledOptions = 0;
			hr = E_NOINTERFACE;
		}
		return hr;
	}
	STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid, DWORD dwOptionSetMask, DWORD dwEnabledOptions)
	{
		ATLTRACE(_T("IObjectSafetyImpl::SetInterfaceSafetyOptions\n"));
		// If we're being asked to set our safe for scripting option then oblige
		if (riid == IID_IDispatch || riid == IID_IPersistHistory)
		{
			// Store our current safety level to return in GetInterfaceSafetyOptions
			m_dwSafety = dwEnabledOptions & dwOptionSetMask;
			return S_OK;
		}
		else

		return E_NOINTERFACE;
	}



// Ipercyctl
public:

	HRESULT OnDraw(ATL_DRAWINFO& di);


};

#endif //__PERCYCTL_H_
