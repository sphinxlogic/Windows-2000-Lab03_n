//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
//         Microsoft Developer Support
//
// WBCustomizerObj.h : Declaration of the CWBCustomizer
//--------------------------------------------------------------------------

#ifndef __WBCUSTOMIZER_H_
#define __WBCUSTOMIZER_H_

#include "resource.h"       // main symbols
#include <ExDisp.h>
#include <mshtmhst.h>
#include "IE4Events.h"

#include <list>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CWBCustomizer
class ATL_NO_VTABLE CWBCustomizer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWBCustomizer, &CLSID_WBCustomizer>,
	public IDispatchImpl<IWBCustomizer, &IID_IWBCustomizer, &LIBID_WBCustomizerLib>,

#if _ATL_VER < 0x0300
   public IObjectSafetyImpl<CWBCustomizer>,
#else
   public IObjectSafetyImpl<CWBCustomizer, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif

   public IDocHostUIHandler
{
public:
	STDMETHOD(EnableAccelerator)(short nKeyCode, short nVirtExtKey, VARIANT_BOOL bState);
	STDMETHOD(get_EnableAllAccelerators)(/*[out, retval]*/ VARIANT_BOOL* pvbEnableAllAccels);
	STDMETHOD(put_EnableAllAccelerators)(/*[in]*/ VARIANT_BOOL vbEnableAllAccels);
	STDMETHOD(get_EnableContextMenus)(/*[out, retval]*/ VARIANT_BOOL* pvbEnableCtxMenus);
	STDMETHOD(put_EnableContextMenus)(/*[in]*/ VARIANT_BOOL vbEnableCtxMenus);
	STDMETHOD(get_WebBrowser)(/*[out, retval]*/ LPDISPATCH* ppWebBrowser);
	STDMETHOD(putref_WebBrowser)(/*[in]*/ LPDISPATCH pWebBrowser);

   CWBCustomizer() :
      m_dwCookie(0),
      m_vbEnableCtxMenus(VARIANT_TRUE),
      m_vbEnableAllAccels(VARIANT_TRUE),
      m_pIE4Events(NULL)
   {
   }

   ~CWBCustomizer()
   {
   }

   void FinalRelease()
   {
      if (m_pIE4Events && m_spWebBrowser)
      {
         //
         // AtlUnadvise causes Release to be called for the event sink.
         // No need to delete m_pIE4Events.  It will delete itself.
         //
         AtlUnadvise(m_spWebBrowser, DIID_DWebBrowserEvents2, m_dwCookie);
      }
   }

   void SetCustomDoc(LPDISPATCH lpDisp);


DECLARE_REGISTRY_RESOURCEID(IDR_WBCUSTOMIZER)

BEGIN_COM_MAP(CWBCustomizer)
	COM_INTERFACE_ENTRY(IWBCustomizer)
	COM_INTERFACE_ENTRY(IDispatch)

#if _ATL_VER < 0x0300
   COM_INTERFACE_ENTRY_IMPL(IObjectSafety)
#else
   COM_INTERFACE_ENTRY(IObjectSafety)
#endif

	COM_INTERFACE_ENTRY(IDocHostUIHandler)
END_COM_MAP()

// Data Members
private:
   CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser;
   DWORD m_dwCookie;

   VARIANT_BOOL m_vbEnableCtxMenus;
   VARIANT_BOOL m_vbEnableAllAccels;

   CIE4Events* m_pIE4Events;

   typedef struct tagACCELERATOR
   {
     short nKeyCode;
     short nVirtExtKey;

   } ACCELERATOR;

   // Linked-list of accelerators
   list<ACCELERATOR> m_disabledAccelerators;

// Utility Methods
private:
   bool AcceleratorDisabled(short nKeyCode);
   list<ACCELERATOR>::iterator FindAccelerator(short nKeyCode, short nVirtExtKey);

////////////////////////////////////////////////////
// Interface Implementation

// IDocHostUIHandler
protected:
   STDMETHOD(ShowContextMenu)(DWORD dwID, POINT FAR* ppt, IUnknown FAR* pcmdtReserved,
                              IDispatch FAR* pdispReserved)
   {
      ATLTRACE("IDocHostUIHandler::ShowContextMenu\n");

      if (m_vbEnableCtxMenus == VARIANT_TRUE)  // Show Context Menu
         return S_FALSE;
      else
         return S_OK;
   }
        
   STDMETHOD(GetHostInfo)(DOCHOSTUIINFO FAR *pInfo)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::GetHostInfo"));
   }
        
   STDMETHOD(ShowUI)(DWORD dwID, IOleInPlaceActiveObject FAR* pActiveObject,
                    IOleCommandTarget FAR* pCommandTarget,
                    IOleInPlaceFrame  FAR* pFrame,
                    IOleInPlaceUIWindow FAR* pDoc)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::ShowUI"));
   }
        
   STDMETHOD(HideUI)(void)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::HideUI"));
   }
        
   STDMETHOD(UpdateUI)(void)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::UpdateUI"));
   }
        
   STDMETHOD(EnableModeless)(BOOL fEnable)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::EnableModeless"));
   }
   
   STDMETHOD(OnDocWindowActivate)(BOOL fActivate)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::OnDocWindowActivate"));
   }
   
   STDMETHOD(OnFrameWindowActivate)(BOOL fActivate)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::OnFrameWindowActivate"));
   }
   
   STDMETHOD(ResizeBorder)(LPCRECT prcBorder, IOleInPlaceUIWindow FAR* pUIWindow,
                           BOOL fRameWindow)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::ResizeBorder"));
   }
   
   STDMETHOD(TranslateAccelerator)(LPMSG lpMsg, const GUID FAR* pguidCmdGroup,
                                   DWORD nCmdID)
   {
      ATLTRACE(_T("IDocHostUIHandler::TranslateAccelerator\n"));

      //
      // If accelerators are turned on, return S_FALSE
      // so that IE4 will perform its default behavior.
      // Check the accelerator to see if it is in the list
      // of accelerators that are turned off.  Return S_OK
      // if the accelerator is in the list.
      if (m_vbEnableAllAccels == VARIANT_TRUE || (GetKeyState(VK_CONTROL) >= 0
         && GetKeyState(VK_SHIFT) >= 0 && GetKeyState(VK_MENU) >= 0))
      {
         // Ignore WM_CHAR.  The wParam for WM_CHAR is 
         // the ASCII code for the character.  We only
         // want virtual key codes.
         if (lpMsg->message != WM_CHAR && AcceleratorDisabled(lpMsg->wParam))
            return S_OK;

         return S_FALSE;
      }

      return S_OK;
   }
   
   STDMETHOD(GetOptionKeyPath)(LPOLESTR FAR* pchKey, DWORD dw)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::GetOptionKeyPath"));
   }
   
   STDMETHOD(GetDropTarget)(IDropTarget* pDropTarget,
                            IDropTarget** ppDropTarget)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::GetDropTarget"));
   }
   
   STDMETHOD(GetExternal)(IDispatch** ppDispatch)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::GetExternal"));
   }
   
   STDMETHOD(TranslateUrl)(DWORD dwTranslate, OLECHAR* pchURLIn,
                           OLECHAR** ppchURLOut)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::TranslateUrl"));
   }
   
   STDMETHOD(FilterDataObject)(IDataObject* pDO, IDataObject** ppDORet)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::FilterDataObject"));
   }

};

#endif //__WBCUSTOMIZER_H_
