// --convengn.cpp---------------------------------------------------------------
// 
// Conversion engine code.  This file defines the CEDKConvEng class which
// defines the top level behavior of the conversion engine.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convengn.chk"

//$--CEDKConvEng::CEDKConvEng----------------------------------------------------
//
//  DESCRIPTION: constructor for CEDKConvEng.  Required because CEDKConvEng has contained
//  objects with CTORs.
//
//  INPUT: none
//
//  RETURNS:    nothing
//
//------------------------------------------------------------------------------
CEDKConvEng::CEDKConvEng()
{
    DEBUGPRIVATE("CEDKConvEng::CEDKConvEng()\n");
}

//$--CEDKConvEng::HrEDKInitialize---------------------------------------------------
//
//  DESCRIPITON: Initialize the conversion engine.
//
//  INPUT:  hEventSource    --  event source handle
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT CEDKConvEng::HrEDKInitialize(   // RETURNS: HRESULT
        IN HANDLE hEventSource)            // event source handle
{
    HRESULT hr  =    NOERROR;

    DEBUGPRIVATE("CEDKConvEng::HrEDKInitialize()\n");

    // check input parameters
    hr = CHK_CEDKConvEng_HrEDKInitialize(hEventSource);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    m_hEventSource = hEventSource;

    hr = m_crRegistry.HrEDKInitialize();

    RETURN(hr);

}

//$--CEDKConvEng::HrEDKConvert------------------------------------------------------
//
//  DESCRIPTION: Search for a suitable conversion.  If a suitable conversion is
//  found, invoke it.
//
//  INPUT:  pEnv    --  environment of the conversion
//          pszContentClass --  class of source to be converted
//          pContentIn  --  source to be converted
//          pContentOut --  converted object
//
//  OUTPUT: 
//          crResult    --  result
//          
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT CEDKConvEng::HrEDKConvert(          // RETURNS:  HRESULT
    IN PEDKCNVENV pEnv,             // environment of the conversion
    IN LPCWSTR pszContentClass,     // class of source to be converted.
    IN PVOID pContentIn,            // source to be converted.
    IN PVOID pContentOut,           // converted object
    OUT EDKCNVRES & crResult)       // result.
{
    HRESULT hr  =   NOERROR;        // return code
    BOOL bFoundAtLeastOneCandidate = FALSE;
    LPCWSTR pszConversionPoint = NULL;  //  conversion point wide string

    DEBUGPRIVATE("CEDKConvEng::HrEDKConvert()\n");

    // check input parameters
    hr = CHK_CEDKConvEng_HrEDKConvert(pEnv, pszContentClass, pContentIn, pContentOut,
                          crResult);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    m_bFoundAtLeastOneAccept = FALSE;
    
    //
    //  Find all candidate converters
    //

    //
    //  start search.
    //

    crResult = GCR_NO_CANDIDATE;

    if(pEnv != NULL)
    {
        pszConversionPoint = pEnv->pszConversionPoint;
    }

    hr = m_crRegistry.HrEDKSearchOpen(pszConversionPoint, pszContentClass, m_pepConverter);

    if( FAILED(hr) )
    {
        goto cleanup;
    }

    while( TRUE )
    {
        // Find next candidate conversion DLL.
        hr = m_crRegistry.HrEDKSearchNext();

        if ( FAILED(hr) )
        {
            // no more candidate DLLs.
            // break;
            break;
        }

        crResult = GCR_CANNOT_CONVERT;

        bFoundAtLeastOneCandidate = TRUE;

        //
        //  Display some debug info.
        //
        #ifdef DEBUG
            // _tprintf( TEXT(" Attempting converter for class %ls\n"), pszContentClass );
            m_pepConverter->EDKDump();
        #endif

        //
        // Attempt the conversion.
        //

        hr = HrEDKAttemptConversion(
            pEnv, 
            pszContentClass,
            pszConversionPoint,
            pContentIn, 
            pContentOut,
            crResult);

        if(FAILED(hr))       // catastrophic error.
        {
            goto cleanup;
        }

        if(crResult == GCR_OK )    // conversion happened.
        {
            goto cleanup;
        }

    }   // end while

    //
    //  Detect and report the case when no candidates found.
    //

    if(!bFoundAtLeastOneCandidate)
    {
        EventLogMsgW(
            MESGXLAT_CNV_NO_CANDIDATE,       // event identfier
            2,                          // # of strings
            pszConversionPoint,         // string 1
            pszContentClass,               
            0);                         // # of error codes
    }

    //
    //  Detect and report the case when candidates found but won't accept.
    //

    if(bFoundAtLeastOneCandidate && !m_bFoundAtLeastOneAccept)
    {
        WCHAR   szRcTmp[(sizeof(HRESULT)+1)*2] = {0};

        swprintf(szRcTmp, L"%08lx", hr);

        EventLogMsgW(
            MESGXLAT_CNV_NO_ACCEPT,  // event identifier
            4,                  // # of strings
            m_pepConverter->pszDllName(),   // string 1
            pszConversionPoint, // string 2
            pszContentClass,
            szRcTmp,
            0);                 // # of error codes
    }

cleanup:

    m_crRegistry.EDKSearchClose();

    if(hr == EDK_E_END_OF_FILE)       // just couldn't find a converter.  Only returned by Find/Next
    {
        crResult = GCR_NO_CANDIDATE;

        hr = HR_LOG(NOERROR);
    }

    RETURN(hr);

}

//$--CEDKConvEng::HrEDKAttemptConversion--------------------------------------------
//
//  DESCRIPTION: Attempt a particular conversion.
//
//  INPUT:  pEnv    --  environment of the conversion
//          pszContentClass --  class of source to be converted
//          pszConversionPoint  --  where the conversion happened
//          pContentIn  --  source to be converted
//          pContentOut --  converted object
//
//  OUTPUT: 
//          crResult    --  result
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT CEDKConvEng::HrEDKAttemptConversion(
    IN PEDKCNVENV pEnv,             // environment of the convrsion
    IN LPCWSTR pszContentClass,     // class of source to be converted.
    IN LPCWSTR pszConversionPoint,  // where the conversion happened.
    IN PVOID pContentIn,            // source to be converted.
    IN PVOID pContentOut,           // converted object
    OUT EDKCNVRES & crResult)       // result.
{
    HRESULT hr  =   NOERROR;        // return code
    CEDKConvDll cDll(m_pepConverter, m_hEventSource);   // conversion DLL

    DEBUGPRIVATE("CEDKConvEng::HrEDKAttemptConversion()\n");

    // check input parameters
    hr = CHK_CEDKConvEng_HrEDKAttemptConversion(pEnv, pszContentClass, pszConversionPoint,
                                    pContentIn, pContentOut, crResult);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    //
    //  Make a connection to the DLL.
    //
    hr = cDll.HrEDKLoad();

    if(SUCCEEDED(hr))
    {
        BOOL bAmCandidate = FALSE;

        //
        //  Can this DLL handle the message class?
        //
        hr = cDll.HrEDKQueryCapability(pEnv, pszContentClass, pContentIn, bAmCandidate);

        if(SUCCEEDED(hr) && bAmCandidate)
        {
            m_bFoundAtLeastOneAccept = TRUE;

            //
            //  Yes, try to perform the conversion.
            //

            hr = cDll.HrEDKConvert(
                pEnv, pszContentClass, pContentIn, pContentOut, crResult);

            if(FAILED(hr))
            {
                crResult = GCR_CONVERSION_FAILED;

                //
                //  Report conversion failure
                //

                {
                    WCHAR   szRcTmp[(sizeof(HRESULT)+1)*2] = {0};

                    swprintf(szRcTmp, L"%08lx", hr);

                    EventLogMsgW(
                        MESGXLAT_CNV_CONVERT_FAIL,   // event identifier
                        4,                      // # of strings
                        m_pepConverter->pszDllName(),   // string 1
                        pszConversionPoint,     // string 2
                        pszContentClass,
                        szRcTmp,    
                        0);                     // # of error codes
                }

            }
        }
        else
        {
            if(FAILED(hr))
            {
                //
                //  Report query failure
                //

                {
                    WCHAR   szRcTmp[(sizeof(HRESULT)+1)*2] = {0};

                    swprintf(szRcTmp, L"%08lx", hr);

                    EventLogMsgW(
                        MESGXLAT_CNV_QUERY_FAIL,         // event identifier
                        4,                          // # of strings
                        m_pepConverter->pszDllName(),   // string 1
                        pszConversionPoint,         // string 2
                        pszContentClass,                        
                        szRcTmp,
                        0);                         // # of error codes
                }

            }
        }
    }
    else
    {
        crResult = GCR_CANNOT_LOAD;
    }

    // Don't unload DLL.  The DLL cache takes care of this,
    // when appropriate.

    RETURN(hr);

}


//$--CEDKConvEng::HrEDKUninitialize-------------------------------------------------
//
//  DESCRIPTION: Uninitialize a conversion engine.
//
//  INPUT:  none
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT CEDKConvEng::HrEDKUninitialize()
{
    DEBUGPRIVATE("CEDKConvEng::HrEDKUninitialize()\n");

    RETURN(NOERROR);
}
