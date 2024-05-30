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
// Author: S.R.
//         Support Engineer - Internet Client SDK
//         Microsoft Developer Support
//
// AtlBrCon.h : Declaration of the CAtlBrCon
//--------------------------------------------------------------------------

#ifndef __ATLBRCON_H_
#define __ATLBRCON_H_

#include "resource.h"       // main symbols
#include "ExDisp.h"
#include <commctrl.h>
#include <mshtmhst.h>
#include <mshtmdid.h>
#include "AboutBox.h"

/////////////////////////////////////////////////////////////////////////////
// CAtlBrCon
class ATL_NO_VTABLE CAtlBrCon : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlBrCon, &CLSID_AtlBrCon>,
   public CWindowImpl<CAtlBrCon>,
	public IDispatchImpl<IAtlBrCon, &IID_IAtlBrCon, &LIBID_ATLBROWSERLib>,
   public IOleClientSite,
   public IOleInPlaceSite,
   public IDocHostUIHandler,
   public IDocHostShowUI
{
public:
// Construction
   CAtlBrCon();

DECLARE_REGISTRY_RESOURCEID(IDR_ATLBRCON)

// Interface Map
BEGIN_COM_MAP(CAtlBrCon)
	COM_INTERFACE_ENTRY(IAtlBrCon)
   COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IOleClientSite)
	COM_INTERFACE_ENTRY(IOleWindow)
	COM_INTERFACE_ENTRY(IOleInPlaceSite)
	COM_INTERFACE_ENTRY(IDocHostUIHandler)
	COM_INTERFACE_ENTRY(IDocHostShowUI)
END_COM_MAP()

// Message Map
BEGIN_MSG_MAP(CAtlBrCon)
	MESSAGE_HANDLER(WM_CREATE,     OnCreate)
	MESSAGE_HANDLER(WM_NCDESTROY,  OnNCDestroy)
	MESSAGE_HANDLER(WM_SIZE,       OnSize)
	MESSAGE_HANDLER(WM_NOTIFY,     OnNotify)
	MESSAGE_HANDLER(WM_MENUSELECT, OnMenuSelect)
	MESSAGE_HANDLER(WM_KEYDOWN,    OnKeydown)

   // File Menu Commands
   COMMAND_ID_HANDLER(ID_FILE_OPEN,   OnFileOpen)
   COMMAND_ID_HANDLER(ID_FILE_SAVEAS, OnFileSaveAs)
   COMMAND_ID_HANDLER(ID_FILE_CLOSE,  OnFileClose)
   COMMAND_ID_HANDLER(ID_FILE_PRINT,  OnFilePrint)
   COMMAND_ID_HANDLER(ID_FILE_PAGESETUP, OnFilePageSetup)

   // Edit Menu Commands
   COMMAND_ID_HANDLER(ID_EDIT_SELECT_ALL, OnEditSelectAll)
   COMMAND_ID_HANDLER(ID_EDIT_FIND,       OnEditFind)

   // View Menu Commands
   COMMAND_ID_HANDLER(ID_VIEW_REFRESH, OnViewRefresh)
   COMMAND_ID_HANDLER(ID_VIEW_STOP,    OnViewStop)
   COMMAND_ID_HANDLER(ID_VIEW_SOURCE,  OnViewSource)
   COMMAND_ID_HANDLER(ID_VIEW_OPTIONS, OnViewOptions)

   // Go Menu Commands
   COMMAND_ID_HANDLER(ID_GO_BACK,    OnGoBack)
   COMMAND_ID_HANDLER(ID_GO_FORWARD, OnGoForward)
   COMMAND_ID_HANDLER(ID_GO_HOME,    OnGoHome)
   COMMAND_ID_HANDLER(ID_GO_SEARCH,  OnGoSearch)

   // UI Control Menu Commands
   COMMAND_ID_HANDLER(ID_UICONTROL_CTXMENUS,  OnCtxMenus)
   COMMAND_RANGE_HANDLER(ID_UICONTROL_DIALOG, ID_UICONTROL_OPENNEWWIN, OnUIFlag)
   COMMAND_ID_HANDLER(ID_UICONTROL_HELP, OnUIControlHelp)

   // Download Control Menu Commands
   COMMAND_RANGE_HANDLER(ID_DLCTL_DLIMAGES, ID_DLCTL_NO_RUNACTIVEX, OnDLControl)

   // Help Menu Commands
   COMMAND_ID_HANDLER(ID_HELP_ABOUT, OnHelpAbout)
ALT_MSG_MAP(1)  // For subclassed window - m_wndUrlCombo
END_MSG_MAP()

// IAtlBrCon Methods
public:
	STDMETHOD(SayHello)();
	STDMETHOD(GetHwnd)(long* phwnd);
	STDMETHOD(Run)();

protected:
   BOOL  m_bEnableCtxMenus;
   DWORD m_dwDLControl;
   DWORD m_dwCookie;
   DWORD m_dwDocHostUIFlags;
   BOOL  m_bInPlaceActive;
   BOOL  m_bAtlBrowserHelp;
   CContainedWindow m_wndUrlCombo;
   CWindow m_wndStatusBar;
   CWindow m_wndToolBar;
   HMENU m_hMenu;

   CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> m_spWebBrowser;
   CComQIPtr<IOleInPlaceObject, &IID_IOleInPlaceObject> m_spInPlaceObject;
   CComQIPtr<IOleCommandTarget, &IID_IOleCommandTarget> m_spOleCmdTarg;

   LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
   LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL&);
   LRESULT OnNCDestroy(UINT, WPARAM, LPARAM, BOOL&);
   LRESULT OnNotify(UINT, WPARAM, LPARAM lParam, BOOL&);
   LRESULT OnMenuSelect(UINT, WPARAM, LPARAM lParam, BOOL&);
   LRESULT OnKeydown(UINT, WPARAM wParam, LPARAM lParam, BOOL&);

   // Menu Handlers
   LRESULT OnFileClose(WORD, WORD, HWND, BOOL&);
   LRESULT OnFileSaveAs(WORD, WORD, HWND, BOOL&);
   LRESULT OnFileOpen(WORD, WORD, HWND, BOOL&);
   LRESULT OnFilePrint(WORD, WORD, HWND, BOOL&);
   LRESULT OnFilePageSetup(WORD, WORD, HWND, BOOL&);
   LRESULT OnEditFind(WORD, WORD, HWND, BOOL&);
   LRESULT OnEditSelectAll(WORD, WORD, HWND, BOOL&);
   LRESULT OnViewRefresh(WORD, WORD, HWND, BOOL&);
   LRESULT OnViewStop(WORD, WORD, HWND, BOOL&);
   LRESULT OnViewSource(WORD, WORD, HWND, BOOL&);
   LRESULT OnViewOptions(WORD, WORD, HWND, BOOL&);
   LRESULT OnGoBack(WORD, WORD, HWND, BOOL&);
   LRESULT OnGoForward(WORD, WORD, HWND, BOOL&);
   LRESULT OnGoHome(WORD, WORD, HWND, BOOL&);
   LRESULT OnGoSearch(WORD, WORD, HWND, BOOL&);
   LRESULT OnCtxMenus(WORD, WORD, HWND, BOOL&);
   LRESULT OnDLControl(WORD, WORD wID, HWND, BOOL&);
   LRESULT OnUIFlag(WORD, WORD wID, HWND, BOOL&);
   LRESULT OnUIControlHelp(WORD, WORD, HWND, BOOL&);
   LRESULT OnHelpAbout(WORD, WORD, HWND, BOOL&);

	STDMETHOD(Stop)();

private:
   void CreateToolbar();

// IDispatch Methods
private:
   STDMETHOD(Invoke)(DISPID dispidMember,REFIID riid, LCID lcid, WORD wFlags,
                     DISPPARAMS * pdispparams, VARIANT * pvarResult,
                     EXCEPINFO * pexcepinfo, UINT * puArgErr);

// IDocHostUIHandler Methods
protected:
   STDMETHOD(ShowContextMenu)(DWORD dwID, POINT FAR* ppt, IUnknown FAR* pcmdtReserved,
                              IDispatch FAR* pdispReserved)
   {
      ATLTRACE("IDocHostUIHandler::ShowContextMenu\n");

      if (m_bEnableCtxMenus)
         return S_FALSE;      // Show context menus
      else
         return S_OK;         // Do not show context menus
   }
        
   STDMETHOD(GetHostInfo)(DOCHOSTUIINFO FAR *pInfo)
   {
		ATLTRACE(_T("IDocHostUIHandler::GetHostInfo"));

      pInfo->cbSize  = sizeof(DOCHOSTUIINFO);
      pInfo->dwFlags = m_dwDocHostUIFlags;

      return S_OK;
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
      ATLTRACENOTIMPL(_T("IDocHostUIHandler::TranslateAccelerator\n"));
   }
   
   STDMETHOD(GetOptionKeyPath)(LPOLESTR FAR* pchKey, DWORD dw)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::GetOptionKeyPath"));
   }
   
   STDMETHOD(GetDropTarget)(IDropTarget* pDropTarget, IDropTarget** ppDropTarget)
   {
		ATLTRACENOTIMPL(_T("IDocHostUIHandler::GetDropTarget"));
   }
   
   // 
   // Method called by the WebBrowser control when
   // you call window.external.SayHello from script
   //
   STDMETHOD(GetExternal)(IDispatch** ppDispatch)
   {
		ATLTRACE(_T("IDocHostUIHandler::GetExternal"));

      *ppDispatch = this;
      return S_OK;
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

// IDocHostShowUI Methods
private:
   STDMETHOD(ShowHelp)(HWND hwnd, LPOLESTR pszHelpFile, UINT uCommand, DWORD dwData,
                       POINT ptMouse, IDispatch *pDispatchObjectHit)
   {
		ATLTRACE(_T("IDocHostShowUI::ShowHelp\n"));

      if (m_bAtlBrowserHelp)
      {
         CAboutBox dlg(m_hWnd);
         dlg.DoModal();
         return S_OK;
      }

      return S_FALSE;
   }

   STDMETHOD(ShowMessage)(HWND hwnd, LPOLESTR lpstrText, LPOLESTR lpstrCaption, DWORD dwType,
                          LPOLESTR lpstrHelpFile, DWORD dwHelpContext, LRESULT* plResult)
   {
		ATLTRACE(_T("IDocHostShowUI::ShowMessage\n"));

      USES_CONVERSION;

      //
      // If ShowMessage is called when you have specified no execution of ActiveX 
      // controls and there is an ActiveX control on the page, plResult is NULL
      //
      if (plResult)
         *plResult = ::MessageBox(hwnd, OLE2T(lpstrText), _T("AtlBrowser"), dwType);
      else
         ::MessageBox(hwnd, OLE2T(lpstrText), _T("AtlBrowser"), dwType);

      return S_OK;
   }

// IOleClientSite Methods
private:
   STDMETHOD(SaveObject)(void)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::SaveObject"));
	}

   STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::GetMoniker"));
	}

   STDMETHOD(GetContainer)(IOleContainer **ppContainer)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::GetContainer"));
	}

   STDMETHOD(ShowObject)(void)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::ShowObject"));
	}

   STDMETHOD(OnShowWindow)(BOOL fShow)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::OnShowWindow"));
	}

   STDMETHOD(RequestNewObjectLayout)(void)
	{
		ATLTRACENOTIMPL(_T("IOleClientSite::RequestNewObjectLayout"));
	}


// IOleWindow
private:
   STDMETHOD(GetWindow)(HWND *phwnd)
	{
	   *phwnd = m_hWnd;
      return S_OK;
	}

   STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode)
	{
		ATLTRACENOTIMPL(_T("IOleWindow::CanInPlaceActivate"));
	}

// IOleInPlaceSite
private:
   STDMETHOD(CanInPlaceActivate)(void)
	{
	   return S_OK;
	}

   STDMETHOD(OnInPlaceActivate)(void)
	{
		m_bInPlaceActive = TRUE;
		return S_OK;
	}

   STDMETHOD(OnUIActivate)(void)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::OnUIActivate"));
	}

   STDMETHOD(GetWindowContext)(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc,
	                            LPRECT lprcPosRect, LPRECT lprcClipRect,
                               LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		GetClientRect(lprcPosRect);
		GetClientRect(lprcClipRect);
		return S_OK;
	}

   STDMETHOD(Scroll)(SIZE scrollExtant)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::Scroll"));
	}

   STDMETHOD(OnUIDeactivate)(BOOL fUndoable)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::OnUIDeactivate"));
	}

   STDMETHOD(OnInPlaceDeactivate)( void)
	{
		m_bInPlaceActive = FALSE;
		return S_OK;
	}

   STDMETHOD(DiscardUndoState)( void)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::DiscardUndoState"));
	}

   STDMETHOD(DeactivateAndUndo)( void)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::DeactivateAndUndo"));
	}

   STDMETHOD(OnPosRectChange)(LPCRECT lprcPosRect)
	{
		ATLTRACENOTIMPL(_T("IOleInPlaceSite::OnPosRectChange"));
	}
};

#endif //__ATLBRCON_H_
