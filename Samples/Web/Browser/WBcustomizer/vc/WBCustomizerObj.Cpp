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
//
// WBCustomizerObj.cpp : Implementation of CWBCustomizer
//--------------------------------------------------------------------------
#include "stdafx.h"
#include "WBCustomizer.h"
#include "WBCustomizerObj.h"
#include <ExDispID.h>

/////////////////////////////////////////////////////////////////////////////
// CWBCustomizer

void CWBCustomizer::SetCustomDoc(LPDISPATCH lpDisp)
{
   _ASSERT(lpDisp);
   _ASSERT(m_spWebBrowser);

   if (lpDisp)
   {
      m_spWebBrowser = lpDisp;

      if (m_spWebBrowser)
      {
         CComPtr<IDispatch> spDoc;
         m_spWebBrowser->get_Document(&spDoc);

         if (spDoc)
         {
            CComQIPtr<ICustomDoc, &IID_ICustomDoc> spCustomDoc(spDoc);
            if (spCustomDoc)
               spCustomDoc->SetUIHandler(this);
         }
      }
   }
}

STDMETHODIMP CWBCustomizer::get_WebBrowser(LPDISPATCH* ppWebBrowser)
{
   ATLTRACENOTIMPL(_T("CWBCustomizer::get_WebBrowser"));
}

STDMETHODIMP CWBCustomizer::putref_WebBrowser(LPDISPATCH pWebBrowser)
{
   // Unadvise the event sink, if there was a
   // previous reference to the WebBrowser control,
   if (m_spWebBrowser)
      AtlUnadvise(m_spWebBrowser, DIID_DWebBrowserEvents2, m_dwCookie);

   m_spWebBrowser = pWebBrowser;
   _ASSERT(m_spWebBrowser);

   if (m_spWebBrowser)
   {
      //
      // We are using the primary dispatch here for the event sink.  
      // This is done for simplicity.  Typically, you would use a 
      // separate class for the event sink.
      //
      m_pIE4Events = new CComObject<CIE4Events>;
      _ASSERT(m_pIE4Events);

      if (!m_pIE4Events)
         return E_FAIL;

      m_pIE4Events->Init(this);

      HRESULT hr = AtlAdvise(m_spWebBrowser, m_pIE4Events->GetUnknown(), DIID_DWebBrowserEvents2, &m_dwCookie);
      if (FAILED(hr))
      {
         ATLTRACE(_T("Failed to Advise\n"));
         return E_FAIL;
      }
   }

	return S_OK;
}

STDMETHODIMP CWBCustomizer::get_EnableContextMenus(VARIANT_BOOL* pvbEnableCtxMenus)
{
   *pvbEnableCtxMenus = m_vbEnableCtxMenus;
	return S_OK;
}

STDMETHODIMP CWBCustomizer::put_EnableContextMenus(VARIANT_BOOL vbEnableCtxMenus)
{
   m_vbEnableCtxMenus = vbEnableCtxMenus;
	return S_OK;
}

STDMETHODIMP CWBCustomizer::get_EnableAllAccelerators(VARIANT_BOOL* pvbEnableAllAccels)
{
   *pvbEnableAllAccels = m_vbEnableAllAccels;
	return S_OK;
}

STDMETHODIMP CWBCustomizer::put_EnableAllAccelerators(VARIANT_BOOL vbEnableAllAccels)
{
   m_vbEnableAllAccels = vbEnableAllAccels;
	return S_OK;
}

STDMETHODIMP CWBCustomizer::EnableAccelerator(short nKeyCode, short nVirtExtKey, VARIANT_BOOL bState)
{
   static unsigned int curpos = 0;

   list<ACCELERATOR>::iterator it = FindAccelerator(nKeyCode, nVirtExtKey);

   if (bState)  // Turn on accelerator
   {
      // If the key code exists in the accelerator array, remove it.
      if (it != m_disabledAccelerators.end())
         m_disabledAccelerators.erase(it);
   }
   else
   {
      // Only add the accelerator if it doesn't already exist.
      if (it == m_disabledAccelerators.end())
      {
         ACCELERATOR newAccel;
         newAccel.nKeyCode = nKeyCode;
         newAccel.nVirtExtKey = nVirtExtKey;

         m_disabledAccelerators.push_front(newAccel);
      }
   }

   return S_OK;
}

bool CWBCustomizer::AcceleratorDisabled(short nKeyCode)
{
   short nVirtExtKey = 0;

   //
   // Get the virtual key that is pressed in
   // order to pass it to FindAccelerator.
   //
   if (GetKeyState(VK_CONTROL) < 0)
      nVirtExtKey = VK_CONTROL;
   else if (GetKeyState(VK_MENU) < 0)
      nVirtExtKey = VK_MENU;
   else if (GetKeyState(VK_SHIFT) < 0)
      nVirtExtKey = VK_SHIFT;

   list<ACCELERATOR>::iterator it = FindAccelerator(nKeyCode, nVirtExtKey);
   if (it != m_disabledAccelerators.end())
   {
      //
      // The accelerator is disabled if it is not found in the list
      // or if no virtual key is present for the accelerator in the
      // list and the Ctrl, Alt, or Shift keys are not pressed.
      // Or the virtual key is present and that virtual key is pressed 
      //
      if ((!it->nVirtExtKey && GetKeyState(VK_CONTROL) >= 0
           && GetKeyState(VK_MENU) >= 0 && GetKeyState(VK_SHIFT) >= 0)
        || GetKeyState(it->nVirtExtKey) < 0)
      {
         return true;
      }
   }

   return false;
}

list<CWBCustomizer::ACCELERATOR>::iterator
CWBCustomizer::FindAccelerator(short nKeyCode, short nVirtExtKey)
{
   list<ACCELERATOR>::iterator it;

   // Search the list for the accelerator
   for (it = m_disabledAccelerators.begin(); it != m_disabledAccelerators.end(); ++it)
   {
      //
      // If the key code is found in the list, check to see
      // if the virtual key code matches the one passed in to this function.
      //
      if (it->nKeyCode == nKeyCode && it->nVirtExtKey == nVirtExtKey)
         break;
   }

   return it;
}
