// --convdll.cpp----------------------------------------------------------------
// 
// Conversion DLL code.
// Handles loading, unloading and using conversion DLLs.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convdll.chk"

// external declarations
extern CEDKConvReg *  pCConvReg;        // global conversion registry information pointer


//$--CEDKConvDll::CEDKConvDll---------------------------------------------------
//
// DESCRIPTION: CEDKConvDLL class constructor
//
// INPUT:   pep --  CDllEntryPoint class instance
//                  hEventSource    --  event source handle
//
// RETURNS: nothing
//
//------------------------------------------------------------------------------
CEDKConvDll::CEDKConvDll(
    IN CDllEntryPoint * pep,
    IN HANDLE hEventSource)
{
    DEBUGPRIVATE("CEDKConvDll::CEDKConvDll()\n");

    // check input parameters
    CHK_CEDKConvDll_CEDKConvDll(pep, hEventSource);

    m_pepEntry = pep;
    m_hEventSource = hEventSource;

    // initialize other class data members
    m_hDll = NULL;
    m_pDllVector = NULL;

}

//$--CEDKConvDll::~CEDKConvDll--------------------------------------------------
//
// DESCRIPTION: CEDKConvDLL class destructor
// 
// INPUT:   none
//
// RETURNS: nothing
//
//------------------------------------------------------------------------------
CEDKConvDll::~CEDKConvDll()
{
    DEBUGPRIVATE("CEDKConvDLL::~CEDKConvDLL()\n");

    m_pepEntry = NULL;
}

//$--CEDKConvDll::HrEDKLoad--------------------------------------------------------
//
//  DESCRIPTION: Load the specified DLL, find the entry point and invoke the
//  initialization method.  If this method fails, it frees the
//  DLL and entry point.  If this method succeeds, rcUnLoad must
//  be called to release the library.
//
//  INPUT:  none
//
//  RETURNS:    HRESULT --  NOERROR if no error,
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT CEDKConvDll::HrEDKLoad()        // RETURNS:  HRESULT
{
    HRESULT         hr      =   NOERROR;    // return code
    PCONVDLLENTRYFN pfnTmp  =   NULL;       // DLL entry point
    
    DEBUGPRIVATE("CEDKConvDLL::HrEDKLoad()\n");

    // consistency checking
    ASSERTERROR(m_pepEntry != NULL, "NULL m_pepEntry parameter.");
    ASSERTERROR(pCConvReg != NULL, "NULL pCConvReg");

    //
    //  Find the library in our cache
    //
    hr = pCConvReg->HrGetDllHandle(
        m_pepEntry->pszDllName(),   // DLL name
        &m_hDll);                   // DLL instance pointer

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    ASSERTERROR(m_hDll != NULL, "Bad m_hDll");

    //
    //  Find the entry point.
    //
    pfnTmp = (PCONVDLLENTRYFN)GetProcAddress(
            m_hDll, 
            m_pepEntry->pszEntryPoint());

    if(pfnTmp != NULL)
    {
        //
        //  Get the vector table.
        //
        hr = pfnTmp(nDesiredConvDllVersion, &m_pDllVector);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }
    }

    else
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    if( FAILED(hr) )
    {
        m_pDllVector = NULL;
        m_hDll = NULL;            
    }

    RETURN(hr);
}

//$--CEDKConvDll::HrEDKUnLoad------------------------------------------------------
//
//  DESCRIPTION: Invoke the DLL cleanup method and release the library.
//
//  INPUT:  none
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise
//
//------------------------------------------------------------------------------
HRESULT CEDKConvDll::HrEDKUnLoad()
{
    HRESULT hr  =   NOERROR;        // return code

    DEBUGPRIVATE("CEDKConvDLL::HrEDKUnLoad()\n");

    // consistency checking
    ASSERTERROR(m_pDllVector != NULL,"NULL m_pDllVector parameter");

    ASSERTERROR(m_hDll != NULL,"NULL m_hDll parameter");

    //
    //  Free the library.
    //

    FreeLibrary(m_hDll);

    m_pDllVector = NULL;
    m_hDll = NULL;

    RETURN(hr);

}

//$--CEDKConvDll::HrEDKQueryCapability---------------------------------------------
//
//  DESCRIPTION: Invoke the query capability method of the dll.
//
//  INPUT:  pEnv    --  environment for conversion
//          pszContentClass --  class to be converted
//          pConent --  pointer to the content
//
//  OUTPUT: fAmCandidate    --  TRUE if can be converted, FALSE otherwise.
//
//  RETURNS:    HRESULT --  NOERROR if overall function call succeeds,
//                          E_INVALIDARG if bad input
//
//------------------------------------------------------------------------------
HRESULT CEDKConvDll::HrEDKQueryCapability(  // RETURN - HRESULT
    IN PEDKCNVENV pEnv,             // environment for conversion.
    IN LPCWSTR pszContentClass,     // class to be converted.
    IN PVOID pContent,              // pointer to the content.
    OUT BOOL &fAmCandidate)         // result of the conversion.
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("CEDKConvDLL::HrEDKQueryCapability()\n");

    // check input parameters
    hr = CHK_CEDKConvDll_HrEDKQueryCapability(pEnv, pszContentClass, pContent,
                                  fAmCandidate);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // consistency checking
    ASSERTERROR(m_pDllVector != NULL,"NULL m_pDllVector parameter");

    ASSERTERROR(m_hDll != NULL,"NULL m_hDll parameter");

    hr = m_pDllVector->pfnCnvQueryCapability(
            m_pepEntry->pszOptions(), 
            pszContentClass,
            pContent,
            pEnv,
            &fAmCandidate);


    RETURN(hr);

}

//$--CEDKConvDll::HrEDKConvert-----------------------------------------------------
//
//  DESCRIPTION: Invoke the converter.
//
//  INPUT:  pEnv    --  environment
//          lpszContentClass    --  class of content to convert
//          pContentIn  --  source
//          pContentOut --  target of conversion
//          
//  OUTPUT: 
//          crResult    --  result of conversion
//
//  RETURNS:    HRESULT --  NOERROR if overall call succeeds,
//                          E_INVALIDARG if bad input.
//
//------------------------------------------------------------------------------
HRESULT CEDKConvDll::HrEDKConvert(  // RETURNS: HRESULT
    IN PEDKCNVENV pEnv,             // environment
    IN LPCWSTR lpszContentClass,    // class of content to convert.
    IN PVOID pContentIn,            // source.
    IN PVOID pContentOut,           // target of conversion
    OUT EDKCNVRES & crResult)       // result of conversion
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("CEDKConvDLL::HrEDKConvert()\n");

    // check input parameters
    hr = CHK_CEDKConvDll_HrEDKConvert(pEnv, lpszContentClass, pContentIn, pContentOut,
                          crResult);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // consistency checking
    ASSERTERROR(m_pDllVector != NULL,"NULL m_pDllVector parameter");

    ASSERTERROR(m_hDll != NULL,"NULL m_hDll parameter");

    hr = m_pDllVector->pfnCnvConvert(
            m_pepEntry->pszOptions(), 
            lpszContentClass,
            pContentIn,
            pContentOut,
            pEnv,
            &crResult);

    RETURN(hr);

}
