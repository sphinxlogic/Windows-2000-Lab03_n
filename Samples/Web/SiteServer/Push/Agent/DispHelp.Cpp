/****************************************************************************
 ** 
 ** Microsoft Site Server v3.00
 ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
 ** 
 ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
 ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
 ** PURPOSE.
 **
 **
 ** CONTENTS
 **
 ** NOTES
 **
 ****************************************************************************/

#include "stdafx.h"
#include "DispHelp.h"

/*==========================================================================
  %%Function:   operator=
  %%Parameters: LPDISPATCH lp    -- New object to assign to.
  %%Returns:    
  %%Desc:       Adds a reference to hold onto the object.
  ==========================================================================*/
void COleDispatchDriverEx::operator=(LPDISPATCH lp)
{
    SecureInterface(lp);
    lp->AddRef();
    AttachDispatch(lp, TRUE);   // bAutoRelease = TRUE when done
}


/*==========================================================================
  %%Function:   SecureInterface
  %%Parameters: LPUNKNOWN lpIUnk -- Interface to secure.
  %%Returns:    HRESULT          -- If the interface could be secured.
  %%Desc:       Sets the client security information.  This is required 
                for every object that you receive through CoCreateInstance[Ex],
                QueryInterface or through Invoke.  The client needs to set
                the security context and not assume the default security
                setting set through DComCnfg.  For details, search in MSDN for
                CoSetProxyBlanket or go to:
                http://premium.microsoft.com/msdn/library/sdkdoc/comext_47fx.htm
  ==========================================================================*/
HRESULT COleDispatchDriverEx::SecureInterface(LPUNKNOWN lpIUnk)
{
    HRESULT hRes = S_OK;

    if (NULL==lpIUnk)
        return E_INVALIDARG;

    hRes = CoSetProxyBlanket(
            lpIUnk,
            RPC_C_AUTHN_WINNT,
            RPC_C_AUTHZ_NONE,
            NULL,
            RPC_C_AUTHN_LEVEL_PKT,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL,
            0);

    if (hRes == E_NOINTERFACE)  // Ignore if Client has no Security (InProc)
        hRes = S_OK;

    return hRes;
}


/*==========================================================================
  %%Function:   InvokeHelper
  %%Parameters: LPCTSTR pszName         -- Name of method/property
                WORD wType              -- Method/get/put
                VARIANT* pVar           -- Variant to hold the result
                const PBYTE pbParamInfo -- Array of types
                ...                     -- Variable number of args
  %%Returns:    HRESULT
  %%Desc:       Look in COleDispatchDriver::InvokeHelper for details.
                This encapsulates the MFC InvokeHelper and also performs:
                    * Looks up the DispID
                    * Traps any exceptions and translates them into HRESULT
                    * Secures remote interfaces if returned.
  ==========================================================================*/
HRESULT COleDispatchDriverEx::InvokeHelper(
            LPCTSTR pszName, 
            WORD wType,
            VARIANT* pVar, 
            const PBYTE pbParamInfo, 
            ...)
{
    HRESULT hRes = S_OK;
    DISPID dwDispID;

    if (pVar)
        RET_IF_ERR(VariantClear(pVar));

    // Lookup the DispID
    RET_IF_ERR(m_lpDispatch->GetIDsOfNames(
                    IID_NULL, 
                    (LPOLESTR*) &pszName, 
                    1, 
                    LOCALE_SYSTEM_DEFAULT, 
                    &dwDispID));

    va_list argList;
    va_start(argList, pbParamInfo);

    TRY
    {
        // MFC's implementation
        COleDispatchDriver::InvokeHelperV(
                dwDispID, 
                wType, 
                pVar ? VT_VARIANT : VT_EMPTY, 
                pVar, 
                pbParamInfo, 
                argList);
    }
    CATCH(COleDispatchException, e)
    {
        // Display message box for dispatch exceptions.
        hRes = COleException::Process(e);
        e->ReportError(MB_ICONEXCLAMATION | MB_OK);
        e->Delete();
    }
    AND_CATCH_ALL(e)
    {
        // Ignore other exceptions.
        hRes = COleException::Process(e);
        e->Delete();
    }
    END_CATCH_ALL

    va_end(argList);
    
    // Secure if interface is obtained
    if (pVar &&
        (V_VT(pVar) == VT_DISPATCH ||
         V_VT(pVar) == VT_UNKNOWN))
        RET_IF_ERR(SecureInterface(V_UNKNOWN(pVar)));

    return hRes;
}


/*==========================================================================
  %%Function:   GetFromVariant
  %%Parameters: CStringArray& rgstrData -- String Array that will be filled
                                           with the elements in the variant.
                VARIANT* pVar           -- Variant holding safe array of 
                                           variants of type BSTR
  %%Returns:    HRESULT
  %%Desc:       Fills in a CStringArray from the variant
  ==========================================================================*/
HRESULT GetFromVariant(CStringArray& rgstrData, const VARIANT* pVar)
{
    HRESULT hRes = S_OK;

    if (V_VT(pVar) != (VT_ARRAY | VT_VARIANT))
        return DISP_E_TYPEMISMATCH;

    long nLow  = 0;
    long nHigh = 0;
    SAFEARRAY *psa = V_ARRAY(pVar);
    if (1 != SafeArrayGetDim(psa))
        return DISP_E_BADINDEX;

    SafeArrayGetLBound(psa, 1, &nLow);
    SafeArrayGetUBound(psa, 1, &nHigh);
    SafeArrayLock(psa);

    VARIANT *pvarTemp = NULL;
    SafeArrayAccessData(psa, (LPVOID*) &pvarTemp);

    rgstrData.RemoveAll();
    for (int nItem=0, nMax=nHigh-nLow + 1; nItem < nMax; nItem++)
    {
        VARIANT *pVar = pvarTemp + nItem;
        if (V_VT(pVar)!=VT_BSTR)
            return DISP_E_TYPEMISMATCH;

        rgstrData.Add( V_BSTR(pVar) );
    }

    SafeArrayUnaccessData(psa);
    SafeArrayUnlock(psa);

    return hRes;
}


/*==========================================================================
  %%Function:   PutIntoVariant
  %%Parameters: VARIANT* pVar           -- Variant to hold resultant data
                CStringArray& rgstrData -- String Array containing data to
                                           be put into the variant.
  %%Returns:    HRESULT
  %%Desc:       Walks an array of strings and prepares a variant as a 
                safearray of variants of type BSTR (vbscript friendly.)
  ==========================================================================*/
HRESULT PutIntoVariant(VARIANT* pVar, const CStringArray& rgstrData)
{
    HRESULT hRes = S_OK;

    VariantClear(pVar);

    // construct the new safearray
    SAFEARRAYBOUND rgsabound;
    rgsabound.lLbound = 0;
    rgsabound.cElements = rgstrData.GetSize();

    V_VT(pVar)    = VT_ARRAY | VT_VARIANT;
    V_ARRAY(pVar) = SafeArrayCreate(VT_VARIANT, 1, &rgsabound);

    VARIANT *pvarTemp = NULL;
    SAFEARRAY *psa = V_ARRAY(pVar);
    SafeArrayLock(psa);
    SafeArrayAccessData(psa, (LPVOID*) &pvarTemp);

    // add the data into the safearray
    for (int nItem=0, nMax=rgstrData.GetSize(); nItem < nMax; nItem++)
    {
        VARIANT *pVar = pvarTemp + nItem;
        V_VT(pVar)   = VT_BSTR;
        V_BSTR(pVar) = SysAllocString(rgstrData[nItem]);
        
        if (V_BSTR(pVar) == NULL && !rgstrData[nItem].IsEmpty())
        {
            hRes = E_OUTOFMEMORY;
            break;
        }
    }

    SafeArrayUnaccessData(psa);
    SafeArrayUnlock(psa);

    return hRes;
}


