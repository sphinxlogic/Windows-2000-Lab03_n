// --formunk.cpp--------------------------------------------------------------
//
//   Implementation of the FRM IUnknown methods
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "tool.h"

#include "formdata.h"
#include "form.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

//$--FRM::QueryInterface------------------------------------------------------
//
//  Purpose:
//      Returns a pointer to the specified interface.
//
//  Returns:
//      HRESULT             Error status.
// ---------------------------------------------------------------------------
STDMETHODIMP
FRM::QueryInterface(
         REFIID riid,           // Interface wanted.
         LPVOID FAR * ppvObj)   // Interface we return.
{
    HRESULT hr = NOERROR;

    ASSERT(m_cRef > 0);
    if (IsEqualIID(riid, IID_IUnknown))
    {
        AddRef();
        *ppvObj = (IMAPIForm *)this;
    }
    else if (IsEqualIID(riid, IID_IPersistMessage))
    {
        AddRef();
        *ppvObj = (IPersistMessage *)this;
    }
    else if (IsEqualIID(riid, IID_IMAPIForm))
    {
        AddRef();
        *ppvObj = (IMAPIForm *)this;
    }
    else
    {
        hr = ResultFromScode(E_NOINTERFACE);
        *ppvObj = NULL;
    }
  
    return hr;
}


//$--FRM::AddRef--------------------------------------------------------------
//
//  Purpose:
//      Increments reference count on the sample extension.
//
//  Returns:
//      ULONG               New value of reference count.
// ---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) FRM::AddRef(void)
{
    ASSERT(m_cRef > 0);
    return ++m_cRef;
}


//$--FRM::Release-------------------------------------------------------------
//
//  Purpose:
//      Decrements reference count on the sample extension.  If count is
//      decremented to zero, the object is freed.
//
//  Returns:
//      ULONG               New value of reference count.
// ---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) FRM::Release(void)
{
    ASSERT(m_cRef > 0);
    if (!(--m_cRef))
    {
        delete this;
        return 0;
    }
    return m_cRef;
}


