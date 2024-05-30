// --convcwrp.cpp---------------------------------------------------------------
// 
// C callable code that wraps the conversion engine class.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convcwrp.chk"

// Globals

// global conversion DLL registry information cache pointer
CEDKConvReg *  pCConvReg   =   NULL;     

//$--HrConvInitGlobals-------------------------------------------------
//
// DESCRIPTION: Called once by the gateway to initalize common data areas.
//
// INPUT:   none
//
// RETURNS: HRESULT --  NOERROR if successful
//                      E_OUTOFMEMORY if memory problems
//
//---------------------------------------------------------------------
HRESULT HrConvInitGlobals() 
{  
    HRESULT hr  =   NOERROR;

    DEBUGPUBLIC("HrConvInitGlobals()\n");

    // Create a global conversion DLL registry information cache.
    pCConvReg = new CEDKConvReg();

    if ( pCConvReg == NULL )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    // Initialize the registry information cache.
    hr = pCConvReg->HrEDKInitialize();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);

}

//$--ConvUninitGlobals-------------------------------------------------
//
// DESCRIPTION: Called once by the gateway to de-initalize common data areas.
//
// INPUT:   none
//
// RETURNS: VOID
//
//---------------------------------------------------------------------
VOID ConvUninitGlobals() 
{
    DEBUGPUBLIC("ConvUninitGlobals()\n");

    // Delete the global registry information cache.
    if ( pCConvReg )
    {
        // First, delete its common members (the DLL cache
        // and the list of class names).
        pCConvReg->EDKFree();

        // Now, delete the registry informtion cache itself.
        delete pCConvReg;
    }

    pCConvReg = NULL;

    return;

}

//$--HrConvInitInstance-----------------------------------------------
//
//  DESCRIPTION: Called to create a new instance of the conversion engine.  Each
//  instance of the conversion engine is single-threaded.  Multiple
//  instances can be used in separate threads.
//
//  INPUT:  hEventSource    --  event source handle
//
//  OUTPUT:  ppvConvInst --  conversion engine instance
//
//  RETURNS:    HRESULT --  NOERROR if no error,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if failure
//
//---------------------------------------------------------------------
HRESULT HrConvInitInstance(       
    IN HANDLE hEventSource,         // event source handle
    OUT PVOID * ppvConvInst)        // new conversion engine instance
{
    HRESULT hr = NOERROR;           // return code
    CEDKConvEng * pceTmp = NULL;    // Temporary conversion engine pointer

    DEBUGPUBLIC("HrConvInitInstance()\n");

    // check input parameters
    hr = CHK_HrConvInitInstance(hEventSource, ppvConvInst);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    //
    //  Make a new instance.
    //

    pceTmp = new CEDKConvEng;

    if(pceTmp == NULL)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    //
    //  Pass back the new instance.
    //

    (*(CEDKConvEng**)ppvConvInst) = pceTmp;

    //
    //  Attempt to initialize
    //

    hr = pceTmp->HrEDKInitialize(hEventSource);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

cleanup:

    if(FAILED(hr))
    {
        if(pceTmp != NULL)
        {
            delete pceTmp;
            pceTmp = NULL;
        }
    }

    RETURN(hr);
}

//$--HrConvUninitInstance----------------------------------------------
//
// DESCRIPTION: Called to dispose of a previously allocated conversion engine.
//
// INPUT:   pvConvInst  --  conversion engine instance to free.
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT HrConvUninitInstance(     
    IN PVOID pvConvInst)                    // handle to instance to free.
{
    HRESULT hr  =   NOERROR;            // return code
    CEDKConvEng * pceTmp    =   NULL;   // temporary conversion engine pointer

    DEBUGPUBLIC("HrConvUninitInstance()\n");

    // check input parameters
    hr = CHK_HrConvUninitInstance(pvConvInst);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    pceTmp = (CEDKConvEng *) pvConvInst;

    delete pceTmp;

    RETURN(hr);
}

//$--HrConvConvert----------------------------------------------------
//
// DESCRIPTION: called to initiate a conversion.
//
// INPUT:   pvConvInst  --  conversion engine instance
//          pEnv    --  conversion environment
//          pszContentClass --  class of source
//          pContentIn  --  source to be converted
//          pContentOut --  converted object
// 
// OUTPUT:  
//          pcrResult   --  result
//
// RETURNS: HRESULT --  NOERROR if no error,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT HrConvConvert(           
    IN PVOID pvConvInst,            // handle to instance of engine.
    IN PEDKCNVENV pEnv,             // environment of the convrsion
    IN LPCWSTR pszContentClass,     // class of source to be converted.
    IN PVOID pContentIn,            // source to be converted.
    IN PVOID pContentOut,           // converted object
    OUT EDKCNVRES *pcrResult)       // result.
{
    HRESULT hr  =   NOERROR;    // return code
    CEDKConvEng * pceTmp    =   NULL;   // temporary conversion engine pointer

    DEBUGPUBLIC("HrConvConvert()\n");

    // check input parameters
    hr = CHK_HrConvConvert(pvConvInst, pEnv, pszContentClass, pContentIn,
                              pContentOut, pcrResult);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    pceTmp = (CEDKConvEng *) pvConvInst;

    hr = pceTmp->HrEDKConvert(pEnv, pszContentClass, pContentIn, pContentOut,
                              *pcrResult);

    RETURN(hr);

}
