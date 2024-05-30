// --convregh.cpp---------------------------------------------------------------
// 
// Class that represents conversion class name/list info.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convregh.chk"

//$--HrGetArbSizeValue---------------------------------------------------------
//
//  DESCRIPTION: Allocate sufficient memory to read a value from the the registry 
//  and read it.  
//
//  INPUT:  hk  --  key that contains value
//          lpszValueName   --  name of value
//       
//  OUTPUT: pValue  --  pointer to key's value
//          cbSize  --  size of value (including null)
//          nType   --  type of value
//
//  RETURNS:    HRESULT -   NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          EDK_E_END_OF_FILE if key not found,
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT HrGetArbSizeValue(       // RETURNS: HRESULT
    IN HKEY hk,                 // key that contains the value
    IN LPWSTR lpszValueName,    // name of the value
    OUT PVOID & pValue,         // pointer to its value
    OUT DWORD & cbSize,         // how big is it (including trailing null(s)
    OUT DWORD & nType)          // what type
{
    HRESULT hr  =   NOERROR;    // return code
    LONG lRet = 0;

    DEBUGPRIVATE("HrGetArbSizeValue()\n");

    // check input parameters
    hr = CHK_HrGetArbSizeValue(hk, lpszValueName, pValue, cbSize, nType);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    pValue = NULL;

    lRet = RegQueryValueExW(hk, lpszValueName, NULL, &nType, NULL, &cbSize);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);

        goto cleanup;
    }

    hr = MAPIAllocateBuffer(
                cbSize,     // # of bytes
                &pValue);   // output buffer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    lRet = RegQueryValueExW(hk, lpszValueName, NULL, &nType, (PBYTE)pValue, &cbSize);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    if( FAILED(hr) )
    {
        MAPIFREEBUFFER(pValue);
    }

    RETURN(hr);

}

//$--HrStrstriW-------------------------------------------------------
//
// DESCRIPTION: determines whether one string is a sub-string of another.
// Not case sensitive.
//
// INPUT:   pszSubString   --  the sub-string to check for
//          pszString   --  the string
//
// RETURNS: HRESULT --  NOERROR if string contains the sub-string.
//                      E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT HrStrstriW(           
    IN LPCWSTR pszSubString,    // the candidate substring
    IN LPCWSTR pszString)       // the string.
{
    HRESULT hr          =   NOERROR;    // return code
    LPWSTR  pszStringT  =   NULL;       // string copy
    LPWSTR  pszSubStrT  =   NULL;       // substring copy

    DEBUGPRIVATE("HrStrstriW()\n");
    
    // DON'T check input parameters, as null strings are allowed.
    if((pszString == NULL) && (pszSubString == NULL))
    {
        goto cleanup;
    }

    if((pszString == NULL) && (pszSubString != NULL))
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    if((pszString != NULL) && (pszSubString == NULL))
    {
        goto cleanup;
    }

    // upper-case the strings so that our comparison will be
    // case-insensitive.  Duplicate the strings first, however.
    hr = HrStrWToStrW(
                pszString,          // input string
                &pszStringT);       // output string pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    hr = HrStrWToStrW(
                pszSubString,       // input string
                &pszSubStrT);       // output string pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    pszStringT = _wcsupr(pszStringT);
    pszSubStrT = _wcsupr(pszSubStrT);

    if ( (pszSubStrT == NULL) || (pszStringT == NULL) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    if ( wcsstr(pszStringT, pszSubStrT) == NULL )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // substring exists in string

cleanup:

    // free MAPI buffers
    MAPIFREEBUFFER(pszStringT);
    MAPIFREEBUFFER(pszSubStrT);

    RETURN(hr);
        
}
