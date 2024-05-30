//-------------------------------------------------------------------------------
// (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

// CertSrc.h : Declaration of the CCertSrc

#ifndef __CERTSRC_H_
#define __CERTSRC_H_

#include "certresource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CCertSrc
class ATL_NO_VTABLE CCertSrc : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCertSrc, &CLSID_CertSrc>,
	public CComControl<CCertSrc>,
	public IDispatchImpl<ICertSrc, &IID_ICertSrc, &LIBID_CERTSOURCELib>,
	public IProvideClassInfo2Impl<&CLSID_CertSrc, NULL, &LIBID_CERTSOURCELib>,
	public IPersistStreamInitImpl<CCertSrc>,
	public IPersistStorageImpl<CCertSrc>,
	public IQuickActivateImpl<CCertSrc>,
	public IOleControlImpl<CCertSrc>,
	public IOleObjectImpl<CCertSrc>,
	public IOleInPlaceActiveObjectImpl<CCertSrc>,
	public IViewObjectExImpl<CCertSrc>,
	public IOleInPlaceObjectWindowlessImpl<CCertSrc>,
	public IDataObjectImpl<CCertSrc>,
	public ISpecifyPropertyPagesImpl<CCertSrc>
{
public:
	CCertSrc()
	{
    m_bCertInitialized = 0;
    m_bDNInitialized = 0;
    m_bServerNameInitialized = 0;
    m_bPortInitialized = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CERTSRC)

BEGIN_COM_MAP(CCertSrc)
	COM_INTERFACE_ENTRY(ICertSrc)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CCertSrc)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CCertSrc)
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

// ICertSrc
public:
	STDMETHOD(get_PortNumber)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PortNumber)(/*[in]*/ long newVal);
	STDMETHOD(get_ServerName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ServerName)(/*[in]*/ BSTR newVal);
	STDMETHOD(AddCertToDN)();
	STDMETHOD(get_DN)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DN)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Certificate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Certificate)(/*[in]*/ BSTR newVal);
	HRESULT OnDraw(ATL_DRAWINFO& di);

private:
  CComBSTR        m_bstrCertificate;
  CComBSTR        m_bstrDN;
  CComBSTR        m_bstrServerName;
  CComBSTR        m_bstrName;
  CComBSTR        m_bstrIssuer;
  ULONG           m_ulPort;

  int m_bCertInitialized;
  int m_bDNInitialized;
  int m_bServerNameInitialized;
  int m_bPortInitialized;

};

#endif //__CERTSRC_H_
