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
// IE4Events.cpp : Implementation of the CIE4Events
//--------------------------------------------------------------------------

#include "stdafx.h"
#include <ExDispID.h>
#include "IE4Events.h"
#include "WBCustomizer.h"
#include "WBCustomizerObj.h"

STDMETHODIMP CIE4Events::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
                                DISPPARAMS* pDispParams, VARIANT* pvarResult,
                                EXCEPINFO*  pExcepInfo,  UINT* puArgErr)
{
   if (!pDispParams)
      return E_INVALIDARG;

   switch (dispidMember)
   {
      //
      // The parameters for this DISPID are as follows:
      // [0]: URL to navigate to - VT_BYREF|VT_VARIANT
      // [1]: An object that evaluates to the top-level or frame
      //      WebBrowser object corresponding to the event. 
      case DISPID_NAVIGATECOMPLETE2:
         _ASSERT(m_pParent);

         //
         // The IDocHostUIHandler association must be set
         // up every time we navigate to a new page.
         //
         if (pDispParams->cArgs >= 2 && pDispParams->rgvarg[1].vt == VT_DISPATCH)
            m_pParent->SetCustomDoc(pDispParams->rgvarg[1].pdispVal);
         else
            return E_INVALIDARG;

         break;

      default:
         break;
   }

   return S_OK;
}
