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
// AtlBrCon.cpp : Implementation of CAtlBrCon
//--------------------------------------------------------------------------
#include "stdafx.h"
#include "AtlBrowser.h"
#include "AtlBrCon.h"
#include "ExDispID.h"
#include "WBCmdGroup.h"
#include "DispIds.h"
#include <strstrea.h>

/////////////////////////////////////////////////////////////////////////////
// CAtlBrCon
CAtlBrCon::CAtlBrCon() :
   m_bEnableCtxMenus(TRUE),
   m_dwDLControl(DLCTL_DLIMAGES|DLCTL_VIDEOS|DLCTL_BGSOUNDS),
   m_dwCookie((DWORD)0),
   m_dwDocHostUIFlags((DWORD)0),
   m_bInPlaceActive(FALSE),
   m_bAtlBrowserHelp(TRUE),
   m_wndUrlCombo(_T("ComboBox"), this, 1)
{
}

LRESULT CAtlBrCon::OnCreate(UINT, WPARAM, LPARAM, BOOL&)
{
   CenterWindow();
   return 0;
}

LRESULT CAtlBrCon::OnMenuSelect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   typedef struct tagSTATUSSTRING
   {
      HMENU hMenu;
      UINT uiString;
   } STATUS_STRING;

   static STATUS_STRING StatusStr[1];

   MenuHelp(uMsg, wParam, lParam, m_hMenu, _Module.GetResourceInstance(),
            m_wndStatusBar, (UINT*)StatusStr);

   bHandled = TRUE;
   return 0;
}

LRESULT CAtlBrCon::OnNCDestroy(UINT /*uMsg*/, WPARAM /*wParam*/,
                               LPARAM /*lParam*/, BOOL& /*lResult*/)
{
   Stop();
   return 0;
}

LRESULT CAtlBrCon::OnKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   if (wParam == VK_RETURN)
   {
      // Stop any previous navigations
      m_spWebBrowser->Stop();

      USES_CONVERSION;
      CComBSTR bstrURL;
      CComVariant vtEmpty;

      m_wndUrlCombo.GetWindowText((BSTR&)bstrURL);

      if (bstrURL)
         m_spWebBrowser->Navigate(bstrURL, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);

      bHandled = TRUE;
      return S_OK;
   }

   MSG msg;
   msg.message = uMsg;
   msg.wParam = wParam;
   msg.lParam = lParam;

   //
   // UIActivate the WebBrowser control when the tab key
   // is pressed so that focus will be changed to the next
   // control in the tabbing order.  If this is not done,
   // the WebBrowser control never gets the focus.
   // 
   if ((uMsg == WM_KEYDOWN || uMsg == WM_KEYUP) && wParam == VK_TAB)
   {
      CComQIPtr<IOleObject, &IID_IOleObject> spOleObject(m_spWebBrowser);

      RECT rect;
      GetClientRect(&rect);
      spOleObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, this, 0, m_hWnd, &rect);
   }

   //
   // Call TranslateAccelerator on the in-place active
   // object so that the accelerator will be passed to the 
   // hosted WebBrowser control.  This also forces tabbing to 
   // work correctly in edit boxes.
   //
   CComQIPtr<IOleInPlaceActiveObject,
             &IID_IOleInPlaceActiveObject> spInPlaceActiveObject(m_spWebBrowser);

   spInPlaceActiveObject->TranslateAccelerator(&msg);

   bHandled = TRUE;

   return S_FALSE;
}

LRESULT CAtlBrCon::OnNotify(UINT, WPARAM wParam, LPARAM lParam, BOOL&)
{
   LPNMHDR pnmh = (LPNMHDR)lParam;

   // Display the tooltip text for the toolbar
   if (pnmh->code == TTN_NEEDTEXT)
   {
      LPSTR pReply;
      LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;

      switch(lpttt->hdr.idFrom)
         {
         case ID_GO_BACK:
            pReply = "Back";
            break;
   
         case ID_GO_FORWARD:
            pReply = "Forward";
            break;

         case ID_VIEW_STOP:
            pReply = "Stop";
            break;

         case ID_VIEW_REFRESH:
            pReply = "Refresh";
            break;

         case ID_GO_HOME:
            pReply = "Home";
            break;

         case ID_GO_SEARCH:
            pReply = "Search";
            break;

         case ID_FILE_PRINT:
            pReply = "Print";
            break;

         case ID_HELP_ABOUT:
            pReply = "About AtlBrowser";
            break;

         default:
            break;
         }
      lstrcpy(lpttt->szText, pReply);
   }

   return 0;
}

//
// Menu Handlers
//
LRESULT CAtlBrCon::OnFileOpen(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(NULL, OLECMDID_OPEN, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnFileSaveAs(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(NULL, OLECMDID_SAVEAS, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnFilePrint(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(NULL, OLECMDID_PRINT, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnFilePageSetup(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(NULL, OLECMDID_PAGESETUP, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnFileClose(WORD, WORD, HWND, BOOL&)
{
   DestroyWindow();
   return 0;
}

LRESULT CAtlBrCon::OnEditFind(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_FIND, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnEditSelectAll(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(NULL, OLECMDID_SELECTALL, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnViewRefresh(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
      m_spWebBrowser->Refresh();

   return 0;
}

LRESULT CAtlBrCon::OnViewStop(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
      m_spWebBrowser->Stop();

   return 0;
}

LRESULT CAtlBrCon::OnViewSource(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_VIEWSOURCE, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnViewOptions(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spOleCmdTarg);

   m_spOleCmdTarg->Exec(&CGID_IWebBrowserPriv, CWBCmdGroup::HTMLID_OPTIONS, 0, NULL,NULL);

   return 0;
}

LRESULT CAtlBrCon::OnGoBack(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
      m_spWebBrowser->GoBack();

   return 0;
}

LRESULT CAtlBrCon::OnGoForward(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
      m_spWebBrowser->GoForward();

   return 0;
}

LRESULT CAtlBrCon::OnGoHome(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
      m_spWebBrowser->GoHome();

   return 0;
}

LRESULT CAtlBrCon::OnGoSearch(WORD, WORD, HWND, BOOL&)
{
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
      m_spWebBrowser->GoSearch();

   return 0;
}

LRESULT CAtlBrCon::OnCtxMenus(WORD, WORD, HWND, BOOL&)
{
   m_bEnableCtxMenus = !m_bEnableCtxMenus;

   ::CheckMenuItem(m_hMenu, ID_UICONTROL_CTXMENUS, m_bEnableCtxMenus ? MF_CHECKED : MF_UNCHECKED);

   return 0;
}

LRESULT CAtlBrCon::OnUIFlag(WORD, WORD wID, HWND, BOOL&)
{
   // Is the menu item checked or not?
   BOOL bIsChecked = (::GetMenuState(m_hMenu, wID, MF_BYCOMMAND) == MF_CHECKED) ? TRUE : FALSE;
   bIsChecked = !bIsChecked;

   //
   // If the menu item is not checked, add its corresponding UI flag
   // to the DWORD that holds the Download Control constants.
   // To add it, OR it to the current value.  If removing it, XOR it.  
   //
   switch(wID)
   {
   case ID_UICONTROL_DIALOG:
      m_dwDocHostUIFlags = bIsChecked ? (m_dwDocHostUIFlags ^ DOCHOSTUIFLAG_DIALOG)
                                      : (m_dwDocHostUIFlags | DOCHOSTUIFLAG_DIALOG);
      break;

   case ID_UICONTROL_3DBORDER:
      m_dwDocHostUIFlags = bIsChecked ? (m_dwDocHostUIFlags ^ DOCHOSTUIFLAG_NO3DBORDER)
                                      : (m_dwDocHostUIFlags | DOCHOSTUIFLAG_NO3DBORDER);
      break;

   case ID_UICONTROL_SCROLLBARS:
      m_dwDocHostUIFlags = bIsChecked ? (m_dwDocHostUIFlags ^ DOCHOSTUIFLAG_SCROLL_NO)
                                      : (m_dwDocHostUIFlags | DOCHOSTUIFLAG_SCROLL_NO);
      break;

   case ID_UICONTROL_OPENNEWWIN:
      m_dwDocHostUIFlags = bIsChecked ? (m_dwDocHostUIFlags ^ DOCHOSTUIFLAG_OPENNEWWIN)
                                      : (m_dwDocHostUIFlags | DOCHOSTUIFLAG_OPENNEWWIN);
      break;

   default:
      return 0;
   }

   //
   // We must navigate to the current URL so that the 
   // change takes affect.
   //
   CComBSTR bstrURL;
   CComVariant vtEmpty;

   m_spWebBrowser->get_LocationURL(&bstrURL);
   m_spWebBrowser->Navigate(bstrURL, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);

   ::CheckMenuItem(m_hMenu, wID, bIsChecked ? MF_CHECKED : MF_UNCHECKED);
   return 0;
}

LRESULT CAtlBrCon::OnUIControlHelp(WORD, WORD, HWND, BOOL&)
{
   m_bAtlBrowserHelp = !m_bAtlBrowserHelp;
   ::CheckMenuItem(m_hMenu, ID_UICONTROL_HELP, m_bAtlBrowserHelp ? MF_CHECKED : MF_UNCHECKED);

   return 0;
}

LRESULT CAtlBrCon::OnDLControl(WORD, WORD wID, HWND, BOOL&)
{
   // Is the menu item checked or not?
   BOOL bIsChecked = (::GetMenuState(m_hMenu, wID, MF_BYCOMMAND) == MF_CHECKED) ? TRUE : FALSE;
   bIsChecked = !bIsChecked;

   //
   // If the menu item is checked, add its corresponding download
   // control constant to the DWORD that holds the Download Control constants.
   // To add it, OR it to the current value.  If removing it,
   // XOR it if it is not 0.  (XORing something with 0, result
   // in that something.  For example, 128 ^ 0 = 128.
   //
   switch(wID)
   {
   case ID_DLCTL_DLIMAGES:
      m_dwDLControl = bIsChecked ? (m_dwDLControl | DLCTL_DLIMAGES) : (m_dwDLControl ^ DLCTL_DLIMAGES);
      break;

   case ID_DLCTL_VIDEOS:
      m_dwDLControl = bIsChecked ? (m_dwDLControl | DLCTL_VIDEOS) : (m_dwDLControl ^ DLCTL_VIDEOS);
      break;

   case ID_DLCTL_BGSOUNDS:
      m_dwDLControl = bIsChecked ? (m_dwDLControl | DLCTL_BGSOUNDS) : (m_dwDLControl ^ DLCTL_BGSOUNDS);
      break;

   case ID_DLCTL_NO_SCRIPTS:
      m_dwDLControl = bIsChecked ? (m_dwDLControl | DLCTL_NO_SCRIPTS) : (m_dwDLControl ^ DLCTL_NO_SCRIPTS);
      break;

   case ID_DLCTL_NO_JAVA:
      m_dwDLControl = bIsChecked ? (m_dwDLControl | DLCTL_NO_JAVA) : (m_dwDLControl ^ DLCTL_NO_JAVA);
      break;

   case ID_DLCTL_NO_RUNACTIVEX:
      m_dwDLControl = bIsChecked ? (m_dwDLControl | DLCTL_NO_RUNACTIVEXCTLS) : (m_dwDLControl ^ DLCTL_NO_RUNACTIVEXCTLS);
      break;

   default:
      return 0;
   }

   //
   // We must navigate to the current URL so that the ambient
   // property change takes affect.  Refreshing or calling
   // IOleControl::OnAmbientPropertyChange doesn't have any affect.
   //
   CComBSTR bstrURL;
   CComVariant vtEmpty;

   m_spWebBrowser->get_LocationURL(&bstrURL);
   m_spWebBrowser->Navigate(bstrURL, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);

   ::CheckMenuItem(m_hMenu, wID, bIsChecked ? MF_CHECKED : MF_UNCHECKED);
   return 0;
}

LRESULT CAtlBrCon::OnHelpAbout(WORD, WORD, HWND, BOOL&)
{
   CAboutBox dlg(m_hWnd);
   dlg.DoModal();

   return 0;
}

STDMETHODIMP CAtlBrCon::Run()
{
   //
   // Create and show the window
   //
   RECT rcClient = { CW_USEDEFAULT, 0, 0, 0 };
   m_hMenu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_ATLBR_MENU));

   Create(GetDesktopWindow(), rcClient, _T("ATL Browser"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,
          0, (UINT)m_hMenu);
   ShowWindow(SW_SHOWNORMAL);

   //
   // Set the icon for this application
   //
   HICON hIcon = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON));

   SetIcon(hIcon);         // Large icon
   SetIcon(hIcon, FALSE);  // Small icon

   //
   // Create the toolbar
   //
   CreateToolbar();
     
   //
   // Create the status bar
   //
   m_wndStatusBar.Attach(CreateStatusWindow(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CCS_BOTTOM,
                                            "Ready", m_hWnd, 2));
   _ASSERT(m_wndStatusBar);
   
   //
   // Create the WebBrowser control
   //
   CComPtr<IOleObject> spOleObject;
   HRESULT hr = CoCreateInstance(CLSID_WebBrowser, NULL, CLSCTX_INPROC, IID_IOleObject,
                                 (void**)&spOleObject);
   if (hr != S_OK)
   {
      MessageBox(_T("CoCreateInstance failed"));
      return E_FAIL;
   }

   if (spOleObject->SetClientSite(this) != S_OK)
   {
      MessageBox(_T("SetClientSite failed"));
      return E_FAIL;
   }

   // 
   // In-place activate the WebBrower control
   //
   MSG msg;
   GetClientRect(&rcClient);

   hr = spOleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, &msg, this, 0, m_hWnd, &rcClient);
   if (hr != S_OK)
   {
      MessageBox(_T("DoVerb failed"));
      return E_FAIL;
   }

   //
   // Get the pointer to the WebBrowser control.  Note that setting a CComQIPtr
   // equal to a pointer of another type cause CComQIPtr to call QueryInterface.
   //
   m_spWebBrowser = spOleObject;
   _ASSERT(m_spWebBrowser);

   if (!m_spWebBrowser)
      return E_FAIL;

   //
   // Set up the connection to the WebBrowser control to receive events.
   //
   hr = AtlAdvise(m_spWebBrowser, GetUnknown(), DIID_DWebBrowserEvents2, &m_dwCookie);
   if (FAILED(hr))
      ATLTRACE(_T("Failed to Advise\n"));

   //
   // Get the size of the status bar
   //
   RECT rcWindow;
   m_wndStatusBar.GetWindowRect(&rcWindow);

   //
   // Resize the control to accommodate the status bar and toolbar
   //
   rcClient.bottom -= (rcWindow.bottom - rcWindow.top);

   m_wndToolBar.GetWindowRect(&rcWindow);
   rcClient.top += (rcWindow.bottom - rcWindow.top);

   //
   // QI for the in-place object to set the size.
   //
   m_spInPlaceObject = m_spWebBrowser;
   _ASSERT(m_spInPlaceObject);

   if (m_spInPlaceObject)
      m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);

   //
   // QI for the IOleCommandTarget interface that will be used later
   //
   m_spOleCmdTarg = m_spWebBrowser;
   _ASSERT(m_spOleCmdTarg);

   //
   // Go to the user's home page
   //
   m_spWebBrowser->GoHome();

   return S_OK;
}

STDMETHODIMP CAtlBrCon::Stop()
{
   _ASSERT(m_spWebBrowser);

   HRESULT hr = AtlUnadvise(m_spWebBrowser, DIID_DWebBrowserEvents2, m_dwCookie);

   if (FAILED(hr))
      ATLTRACE("Failed to Unadvise\n");

   PostQuitMessage(0);

   return S_OK;
}

LRESULT CAtlBrCon::OnSize(UINT, WPARAM, LPARAM lParam, BOOL&)
{
   RECT rcWindow;

   // Resize the status bar
   if (m_wndStatusBar)
   {
      int cxParent = LOWORD(lParam);
      int cyParent = HIWORD(lParam);
      int x = 0, y, cx, cy;

      // Keep the status bar height the same.
      m_wndStatusBar.GetWindowRect(&rcWindow);
      cy = rcWindow.bottom - rcWindow.top;

      y = cyParent - cy;
      cx = cxParent;
      m_wndStatusBar.MoveWindow(x, y, cx, cy, TRUE);
   }

   // Tell the toolbar to resize itself
   if (m_wndToolBar)
      m_wndToolBar.SendMessage(TB_AUTOSIZE, 0, 0L);

   // Resize the control
   if (m_spWebBrowser && m_bInPlaceActive)
   {
      RECT rcClient;
      GetClientRect(&rcClient);

      // Resize the control to accommodate the status bar and toolbar
      rcClient.bottom -= (rcWindow.bottom - rcWindow.top);

      m_wndToolBar.GetWindowRect(&rcWindow);
      rcClient.top += (rcWindow.bottom - rcWindow.top);

      if (m_spInPlaceObject)
         m_spInPlaceObject->SetObjectRects(&rcClient, &rcClient);
   }

   return 0;
}

//
// IDispatch Methods
//
STDMETHODIMP CAtlBrCon::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
                               DISPPARAMS* pDispParams, VARIANT* pvarResult,
                               EXCEPINFO*  pExcepInfo,  UINT* puArgErr)
{
   USES_CONVERSION;

   switch (dispidMember)
   {
      case DISPID_SAYHELLO:
         SayHello();

      case DISPID_DOCUMENTCOMPLETE:
         ATLTRACE("DISPID_DOCUMENTCOMPLETE\n");
         break;

      case DISPID_DOWNLOADBEGIN:
         // Enable the stop menu item and toolbar button
         EnableMenuItem(m_hMenu, ID_VIEW_STOP, MF_BYCOMMAND|MF_ENABLED);
         m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_VIEW_STOP, MAKELONG(TRUE, 0));

         break;

      case DISPID_NAVIGATECOMPLETE:
         {
            // Set the text of the combobox to the current URL
            CComBSTR bstrURL;

            m_spWebBrowser->get_LocationURL(&bstrURL);
            m_wndUrlCombo.SetWindowText(OLE2T(bstrURL));
         }

         break;

      case DISPID_DOWNLOADCOMPLETE:
         // Disable the stop menu item and toolbar button
         EnableMenuItem(m_hMenu, ID_VIEW_STOP, MF_BYCOMMAND|MF_GRAYED);
         m_wndToolBar.SendMessage(TB_ENABLEBUTTON, ID_VIEW_STOP, MAKELONG(FALSE, 0));

         break;

      //
      // The parameters for this DISPID:
      // [0]: New status bar text - VT_BSTR
      //
      case DISPID_STATUSTEXTCHANGE:
         m_wndStatusBar.SetWindowText(OLE2T(pDispParams->rgvarg[0].bstrVal));
         break;

      //
      // The parameters for this DISPID:
      // [0]: Document title - VT_BSTR
      //
      case DISPID_TITLECHANGE:
         {
            strstream strTitle;

            if (pDispParams->cArgs > 0 && pDispParams->rgvarg[0].vt == VT_BSTR)
            {
               strTitle << OLE2T(pDispParams->rgvarg[0].bstrVal);
               strTitle << " - AtlBrowser";
            }
            else
            {
               strTitle << "AtlBrowser";
            }

            strTitle << ends;
            SetWindowText(strTitle.str());
         }

         break;

      //
      // DISPID for Download Control
      //
      case DISPID_AMBIENT_DLCONTROL:
         {
            CComVariant vtResult(static_cast<long>(m_dwDLControl));
            *pvarResult = vtResult;
         }

         break;

      default:
         return DISP_E_MEMBERNOTFOUND;
   }

   return S_OK;
}

void CAtlBrCon::CreateToolbar()
{
   TBBUTTON tbb[] = 
   {
      // Add separators to make room for the combo box.
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,

      0, ID_GO_BACK,      TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      1, ID_GO_FORWARD,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      2, ID_VIEW_STOP,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      3, ID_VIEW_REFRESH, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      4, ID_GO_HOME,      TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0, 0, 0,
      5, ID_GO_SEARCH,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      6, ID_FILE_PRINT,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
      7, ID_HELP_ABOUT,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
   };

   m_wndToolBar.Attach(CreateToolbarEx(m_hWnd,  WS_CHILD | WS_VISIBLE
                                       | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
                                       ID_TOOLBARWND, 8, _Module.GetResourceInstance(),
                                       IDR_TOOLBAR, tbb,
                                       50, 0, 0, 23, 23, sizeof(TBBUTTON)));
   _ASSERT(m_wndToolBar);

   // Tell the toolbar to resize itself
   m_wndToolBar.SendMessage(TB_AUTOSIZE, 0, 0L);

   // Create the combo box on the toolbar
   RECT rc, rc2;

   // Calculate the coordinates for the combo box.
   m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)0, (LPARAM)(LPRECT)&rc);
   m_wndToolBar.SendMessage(TB_GETITEMRECT, (WPARAM)38, (LPARAM)(LPRECT)&rc2);

   rc.right = rc2.right;
   rc.bottom = 100;
   m_wndUrlCombo.Create(m_wndToolBar, rc, NULL, WS_CHILD|WS_VISIBLE|CBS_DROPDOWN,
                        0, ID_URL_COMBOBOX);
}


STDMETHODIMP CAtlBrCon::GetHwnd(long* phwnd)
{
   *phwnd = (long)m_hWnd;
	return S_OK;
}


// 
// This method is called from script with this command: window.script.SayHello
//
STDMETHODIMP CAtlBrCon::SayHello()
{
   MessageBox(_T("Hey, how's it going?"), _T("AtlBrowser"), MB_OK);
	return S_OK;
}
