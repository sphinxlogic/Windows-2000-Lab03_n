// --formfact.cpp-------------------------------------------------------------
//
// Implementation of the FRMFAC class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "tool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

#include <ole2.h>
#include <initguid.h>
#include <mapiform.h>
#define INITGUID
#include <initguid.h>
#include <mapix.h>
#include <mapiutil.h>
#include <mapinls.h>

// Tool form clsid.  This must match the configuration file.
DEFINE_GUID(CLSID_MyFormsClsId,  0x861E4010, 0x5030, 0xFEDC, 0x99, 0x12, 0x00, 0x0a, 0x00, 0x38, 0x90, 0x1b);

#include "formdata.h"
#include "form.h"
#include "tooldoc.h"
#include "toolform.h"

/*
 *  F o r m   C l a s s   F a c t o r y
 *
 *  Because we are an exe server, we must implement a class factory
 *  so that other viewers (like Exchange) can learn of our clsid
 *
 */

//$--FRMFAC::FRMFAC-----------------------------------------------------------
//
//  Purpose:
//      Creates a new form factory
//
//----------------------------------------------------------------------------
FRMFAC::FRMFAC()
{
    m_clsid = CLSID_MyFormsClsId;
    m_cRef = 1;
}

//$--FRMFAC::CreateInstance---------------------------------------------------
//
//  Purpose:
//      Creates a new form object of the IPM.Form class.
//
//  Returns:
//      HRESULT         S_OK, or one of the following errors:
//                      CLASS_E_NOAGGREGATION, E_OUTOFMEMORY,
//                      E_NOINTERFACE, E_INVALIDARG.
//----------------------------------------------------------------------------
STDMETHODIMP
FRMFAC::CreateInstance(
            LPUNKNOWN punkOuter,    // Outer object to aggregate with (not supported).
            REFIID riid,            // Desired interface on new form object.
            LPVOID FAR * ppvObject) // Where to put new form object.
{
    FRM *   pfrm = NULL;
    HRESULT hr = NOERROR;

    // ----- Initialize out parameter and check validity of parameters
    if (!ppvObject)
    {
        hr = ResultFromScode(E_INVALIDARG);
        goto Cleanup;
    }
    *ppvObject = NULL;

    if (punkOuter)
    {
        hr = ResultFromScode(CLASS_E_NOAGGREGATION);
        goto Cleanup;
    }

    // ----- Instantiate new form
    TRY
    {
        pfrm = new FRM(m_clsid);
    }
    CATCH(CMemoryException, e)
    {
        hr = ResultFromScode(E_OUTOFMEMORY);
        goto Cleanup;
    }
    END_CATCH

    // ----- Get the desired interface
    hr = pfrm->QueryInterface(riid, ppvObject);

Cleanup:
    if (pfrm)
        ReleaseObj(pfrm);

    return hr;
}

//$--FRMFAC::QueryInterface---------------------------------------------------
//  
//  Purpose:
//      Returns a pointer to the specified interface.
//
//  Returns:
//      HRESULT         Error status.
//----------------------------------------------------------------------------
STDMETHODIMP
FRMFAC::QueryInterface(
            REFIID riid,        // Interface we want.
            LPVOID FAR * ppvObj)// Interface we return.
{
    if (IsEqualIID(riid, IID_IUnknown) || 
        IsEqualIID(riid, IID_IClassFactory))
    {
        *ppvObj = this;
        AddRef();
        return NOERROR;
    }

    *ppvObj = NULL;

    return ResultFromScode(E_NOINTERFACE);
}

//$--FRMFAC::LockServer-------------------------------------------------------
//
//  Purpose:
//      
//  Returns:
//      HRESULT         S_OK always.
//----------------------------------------------------------------------------
STDMETHODIMP
FRMFAC::LockServer(
            BOOL fLock) // Whether to increment or decrement DLL reference count.
{
    return NOERROR;
}

//$--FRMFAC::AddRef-----------------------------------------------------------
//
//  Purpose:
//      Increments reference count on the form class factory.
//
//  Returns:
//      ULONG           New value of reference count.
//----------------------------------------------------------------------------
STDMETHODIMP_(ULONG)
FRMFAC::AddRef(void)
{
    return ++m_cRef;
}

//$--FRMFAC::Release----------------------------------------------------------
//  
//
//  Purpose:
//      Decrements reference count on the form class factory.
//      If count is decremented to zero, the object is freed.
//
//  Returns:
//      ULONG           New value of reference count.
//----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) FRMFAC::Release(void)
{
    if (!(--m_cRef))
    {
        delete this;
        return 0;
    }
    return m_cRef;
}
