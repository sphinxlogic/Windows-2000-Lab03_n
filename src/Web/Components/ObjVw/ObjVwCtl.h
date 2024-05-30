 
//=--------------------------------------------------------------------------=
//  (C)  Copyright 1996-1999 Microsoft Corporation. All Rights Reserved.
//=--------------------------------------------------------------------------=
// ObjVwCtl.h : Declaration of the CObjVw

#ifndef __OBJVW_H_
#define __OBJVW_H_

#include "resource.h"       // main symbols
#include <commctrl.h>

// !! The following two #imports need to point to your Windows-System(32) Directory
//    or to a controlled location of MSHTML.TLB and SHDOCVW.DLL
// !! IE4 NOTE: If you're compiling on an IE4 system, you need to point the first
//    #import at mshtml.dll instead of mshtml.tlb.
#pragma warning(disable : 4192) // multiple defines on typical ifaces, okay to
#pragma warning(disable : 4049) // MSHTML is a *big* TLB
#pragma warning(disable : 4146) // unary minus operator in TLB, doesn't always ignore though
#import "c:\winnt\system32\mshtml.tlb" 
#import "c:\winnt\system32\shdocvw.dll" exclude("tagREADYSTATE")

/////////////////////////////////////////////////////////////////////////////
// CObjVw
class ATL_NO_VTABLE CObjVw :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CObjVw,&CLSID_ObjVw>,
	public CComControl<CObjVw>,
	public IDispatchImpl<IObjVw, &IID_IObjVw, &LIBID_OBJVWLib>,
	//public IDispatchImpl<DWebBrowserEvents2, &__uuidof(SHDocVw::DWebBrowserEvents2), &LIBID_OBJVWLib>,
	public IPersistStreamInitImpl<CObjVw>,
	public IOleControlImpl<CObjVw>,
	public IOleObjectImpl<CObjVw>,
	public IOleInPlaceActiveObjectImpl<CObjVw>,
	public IViewObjectExImpl<CObjVw>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CObjVw>,
	public IOleInPlaceObjectWindowlessImpl<CObjVw>,
	public IDispEventImpl<0, CObjVw, &__uuidof(SHDocVw::DWebBrowserEvents2),
						  &LIBID_OBJVWLib, 1, 0>,
	// for backward compatibility with IE3, not really needed
	public IDispEventImpl<1, CObjVw, &__uuidof(SHDocVw::DWebBrowserEvents),
						  &LIBID_OBJVWLib, 1, 0>,
#if _ATL_VER < 0x0300
	public IObjectSafetyImpl<CObjVw>,
#else
	public IObjectSafetyImpl<CObjVw, INTERFACESAFE_FOR_UNTRUSTED_CALLER |
									 INTERFACESAFE_FOR_UNTRUSTED_DATA>
#endif
{
public:
	CContainedWindow m_ctlSysTreeView32;
	SHDocVw::IWebBrowserPtr m_spWebBrowser;
	//REMOVE: DWORD m_dwAdviseCookie;


	CObjVw() :	
		m_ctlSysTreeView32(_T("SysTreeView32"), this, 1)
	{
		m_bWindowOnly = TRUE; 
		//REMOVE: m_dwAdviseCookie = 0;
	}

	void EnumFrames();
	void RecurseWindows(MSHTML::IHTMLDocument2Ptr spDocument, LPVOID pvTreeParent = NULL);
	void GetPageContents(MSHTML::IHTMLDocument2Ptr spDocument, LPVOID pvTreeParent);
	bool GetControlInfo(IUnknownPtr spUnk, LPSTR szClassInfo);

	bool InsertTreeItem(LPTSTR pszItemText, LPVOID pvTreeParent, LPVOID* ppvTree);

DECLARE_REGISTRY_RESOURCEID(IDR_OBJVW)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CObjVw) 
	COM_INTERFACE_ENTRY2(IDispatch, IObjVw)
	COM_INTERFACE_ENTRY_IID(IID_IObjVw, IObjVw)
	//REMOVE: COM_INTERFACE_ENTRY_IID(__uuidof(DWebBrowserEvents2), DWebBrowserEvents2)
	COM_INTERFACE_ENTRY_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CObjVw)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_CONNECTION_POINT_MAP(CObjVw)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CObjVw)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
ALT_MSG_MAP(1)
	// Replace this with message map entries for subclassed SysTreeView32
END_MSG_MAP()

BEGIN_SINK_MAP(CObjVw)
   SINK_ENTRY_EX(0, (__uuidof(DWebBrowserEvents2)), 259, DocumentComplete)
END_SINK_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RECT rc;
		GetWindowRect(&rc);
		rc.right -= rc.left;
		rc.bottom -= rc.top;
		rc.top = rc.left = 0;

		m_ctlSysTreeView32.Create(m_hWnd, rc, _T(""), 
				WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS);

		return 0;
	}
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CObjVw>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlSysTreeView32.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
		return S_OK;
	}

	STDMETHOD(SetClientSite)(IOleClientSite* pClientSite);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IObjVw
public:
	HRESULT OnDraw(ATL_DRAWINFO& di);
	STDMETHOD(Recalc)();

// DWebBrowserEvents2 sinking
public:
	STDMETHOD(DocumentComplete)(IDispatch* pDisp, VARIANT* URL);

};

#endif //__OBJVW_H_
