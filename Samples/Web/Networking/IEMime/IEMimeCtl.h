
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// IEMimeCtl.h : Declaration of the CIEMimeCtl

#ifndef __IEMIMECTL_H_
#define __IEMIMECTL_H_

#include "resource.h"       // main symbols

#include "CPIEMime.h" // Event interface Connection Point
#include "BSCbck.h"   // Bind-status-callback download implementation
// We're using VC5 COM support (_bstr_t and smart pointers)
#include <comdef.h>


/////////////////////////////////////////////////////////////////////////////
// CIEMimeCtl
class ATL_NO_VTABLE CIEMimeCtl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIEMimeCtl,&CLSID_IEMimeCtl>,
	public CComControl<CIEMimeCtl>,
	public IDispatchImpl<IIEMimeCtl, &IID_IIEMimeCtl, &LIBID_IEMIMELib>,
	public IPersistStreamInitImpl<CIEMimeCtl>,
	public IOleControlImpl<CIEMimeCtl>,
	public IOleObjectImpl<CIEMimeCtl>,
	public IOleInPlaceActiveObjectImpl<CIEMimeCtl>,
	public IViewObjectExImpl<CIEMimeCtl>,
	public IConnectionPointContainerImpl<CIEMimeCtl>,
	public IOleInPlaceObjectWindowlessImpl<CIEMimeCtl>,
	public IPersistPropertyBagImpl<CIEMimeCtl>,
	public IPerPropertyBrowsingImpl<CIEMimeCtl>,
	public IObjectSafetyImpl<CIEMimeCtl, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public CProxyDIEMimeEvents<CIEMimeCtl>,
	public IPropertyNotifySinkCP<CIEMimeCtl, CComDynamicUnkArray>,
	public IProvideClassInfo2Impl<&CLSID_IEMimeCtl, &DIID__IEMimeEvents, &LIBID_IEMIMELib>
{
public:
	CIEMimeCtl()
	{
		m_nReadyState = READYSTATE_UNINITIALIZED;
	}

	DWORD  m_dwSafety;

DECLARE_REGISTRY_RESOURCEID(IDR_IEMIMECTL)

BEGIN_COM_MAP(CIEMimeCtl) 
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IIEMimeCtl)
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
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IPersist, IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IPersistPropertyBag)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IID(IID_IProvideClassInfo, IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CIEMimeCtl)
	PROP_ENTRY("URL", 1, CLSID_NULL)
	PROP_ENTRY("Media", 2, CLSID_NULL)
END_PROPERTY_MAP()

BEGIN_CONNECTION_POINT_MAP(CIEMimeCtl)
	CONNECTION_POINT_ENTRY(DIID__IEMimeEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CIEMimeCtl)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IIEMimeCtl
public:
	STDMETHOD(Reload)();
	STDMETHOD(AboutBox)();
	STDMETHOD(get_Cfformat)(/*[out, retval]*/ BSTR *pVal);
	//STDMETHOD(put_Cfformat)(/*[in]*/ BSTR newVal); // PUT not supported
	STDMETHOD(get_Media)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Media)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_URL)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_URL)(/*[in]*/ BSTR newVal); 
	HRESULT OnDraw(ATL_DRAWINFO& di);

	// IOleControl override
	STDMETHOD(FreezeEvents)(BOOL bFreeze);

	// IPersistPropertybag override
	STDMETHOD(Load)(LPPROPERTYBAG pPropBag, LPERRORLOG pErrorLog)
	{
		ATLTRACE(_T("IPersistPropertyBagImpl::Load\n"));
		ATL_PROPMAP_ENTRY* pMap = GetPropertyMap();
		_ASSERTE(pMap != NULL);
		m_nReadyState = READYSTATE_LOADING; 		// ADDED
		FireOnChanged(DISPID_READYSTATE);
		HRESULT hr = IPersistPropertyBag_Load(pPropBag, pErrorLog, pMap);
		m_nReadyState = READYSTATE_COMPLETE;		// ADDED
			// Saying we're complete lets MSHTML proceed. See README.TXT for details.
		FireOnChanged(DISPID_READYSTATE);
		return hr;
	}

	void OnData(CBindStatusCallback2<CIEMimeCtl>* pbsc, BYTE* pBytes, DWORD dwSize,
			DWORD grfBSCF, FORMATETC *pformatetc, STGMEDIUM *pstgmed);

	HRESULT PreBindMoniker(CComPtr<IBindCtx> pBindCtx, CComPtr<IMoniker> pMoniker);

	void OnBindingFailure(HRESULT hr, LPCWSTR szError);

	// IObjectSafetyImpl doesn't support safe-for-persistence naturally.
	// See Microsoft Knowledge Base article Q168371 for more details on the following
	STDMETHOD(GetInterfaceSafetyOptions)(REFIID riid,
										DWORD *pdwSupportedOptions,
										DWORD *pdwEnabledOptions)
	{
	   ATLTRACE(_T("CObjectSafetyImpl::GetInterfaceSafetyOptions\n"));
	   if (!pdwSupportedOptions || !pdwEnabledOptions)
		  return E_FAIL;
	   LPUNKNOWN pUnk;
	   if (_InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE)
		  // Our object doesn't even support this interface.
		  return E_NOINTERFACE;
	   else
	   {
		  // Cleanup after ourselves.
		  pUnk->Release();
		  pUnk = NULL;
	   }
	   if (riid == IID_IDispatch) 
	   {
		  *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		  *pdwEnabledOptions = m_dwSafety &
							   INTERFACESAFE_FOR_UNTRUSTED_CALLER;
		  return S_OK;
		// IEMime only supports persistence via IPersistPropertyBag
	   }
	   else if (riid == IID_IPersistPropertyBag) 
	   {
		  *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
		  *pdwEnabledOptions = m_dwSafety &
							   INTERFACESAFE_FOR_UNTRUSTED_DATA;
		  return S_OK;
	   }
	   else
	   {
		  // No other interfaces in this control are
		  // safe for initializing or scripting.
		  *pdwSupportedOptions = 0;
		  *pdwEnabledOptions = 0;
		  return E_FAIL;
	   }
	}

   STDMETHOD(SetInterfaceSafetyOptions)(REFIID riid,
                                     DWORD dwOptionSetMask,
                                     DWORD dwEnabledOptions)
   {
	   ATLTRACE(_T("CObjectSafetyImpl::SetInterfaceSafetyOptions\n"));
	   if (!dwOptionSetMask && !dwEnabledOptions) return E_FAIL;
	   LPUNKNOWN pUnk;
	   if (_InternalQueryInterface (riid, (void**)&pUnk) == E_NOINTERFACE)
		  // Our object doesn't even support this interface.
		  return E_NOINTERFACE;
	   else
	   {
		  // Cleanup after ourselves.
		  pUnk->Release();
		  pUnk = NULL;
	   }
	   // Store our current safety level to return in
	   // GetInterfaceSafetyOptions
	   m_dwSafety |= dwEnabledOptions & dwOptionSetMask;
	   if ((riid == IID_IDispatch) &&
		   (m_dwSafety & INTERFACESAFE_FOR_UNTRUSTED_CALLER))
		  return S_OK;
	   else if ((riid == IID_IPersistPropertyBag) &&
				 (m_dwSafety & INTERFACESAFE_FOR_UNTRUSTED_DATA))
		  return S_OK;
	   else
		  return E_FAIL;
   }

// ReadyState property - not using CStockPropImpl because we only want this one stock-prop
//                       and we only want it to be read-only
	long m_nReadyState;

	HRESULT STDMETHODCALLTYPE get_ReadyState(long* pnReadyState)
	{
		ATLTRACE(_T("CIEMimeCTL - get_ReadyState - %d\n"),m_nReadyState);

		*pnReadyState = m_nReadyState;
		return S_OK;
	}

public:
	_bstr_t m_bstrURL;
	_bstr_t m_bstrMedia;
	_bstr_t m_bstrCFFormat;
	
};

#endif //__IEMIMECTL_H_
