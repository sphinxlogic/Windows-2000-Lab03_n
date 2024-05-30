
//=--------------------------------------------------------------------------=
//  (C) Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// Button.h : Declaration of the CButton

#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "resource.h"       // main symbols
#include <mshtml.h>


/////////////////////////////////////////////////////////////////////////////
// CButton
class ATL_NO_VTABLE CButton : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CButton, &CLSID_Button>,
	public CComControl<CButton>,
	public IDispatchImpl<IButton, &IID_IButton, &LIBID_COLBTNLib>,
	public IProvideClassInfo2Impl<&CLSID_Button, NULL, &LIBID_COLBTNLib>,
	public IPersistStreamInitImpl<CButton>,
	public IPersistStorageImpl<CButton>,
	public IQuickActivateImpl<CButton>,
	public IOleControlImpl<CButton>,
	public IOleObjectImpl<CButton>,
	public IOleInPlaceActiveObjectImpl<CButton>,
	public IViewObjectExImpl<CButton>,
	public IOleInPlaceObjectWindowlessImpl<CButton>,
	public IDataObjectImpl<CButton>,
	public ISpecifyPropertyPagesImpl<CButton>
{
public:
	CContainedWindow m_ctlButton;
	

	CButton() :	
		m_ctlButton(_T("Button"), this, 1)
	{
 	
		m_bWindowOnly = TRUE; 
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BUTTON)

BEGIN_COM_MAP(CButton)
	COM_INTERFACE_ENTRY(IButton)
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

BEGIN_PROPERTY_MAP(CButton)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CButton)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
ALT_MSG_MAP(1)
 	MESSAGE_HANDLER( WM_LBUTTONUP, OnClick)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;
		m_ctlButton.Create(m_hWnd, rc );
		::SendMessage(m_ctlButton.m_hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)"Pink" );

		return 0;
	}
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CButton>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlButton.m_hWnd, NULL, 0,
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

	LRESULT OnClick(UINT, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HRESULT hr = E_FAIL;
		// Get the document
		CComPtr<IOleContainer> spContainer;
		m_spClientSite->GetContainer(&spContainer);
		CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> spDoc(spContainer);
		if (spDoc)
			hr = spDoc->put_bgColor( CComVariant(CComBSTR(_T("pink") ) ) );
		m_ctlButton.DefWindowProc(WM_LBUTTONUP, wParam, lParam);
		return 0;
	}	

// IButton
public:
	HRESULT OnDraw(ATL_DRAWINFO& di);

};

#endif //__BUTTON_H_
