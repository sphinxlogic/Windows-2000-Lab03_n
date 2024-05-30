// --ipm_in.cpp--------------------------------------------------------------
//
// API entry points for the ipm_in dynamic link library.
// Converts an 822-style message header to a MAPI message.
// This is the "Inbound IPM Converter".
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "ipmconv.h"
#include "convcls.h"
#include "ipm_in.chk"

// GLOBAL VARIABLES

// Thread local storage slot index. 
// This storage will be used to store the conversion class instance pointer
// for each thread.
static DWORD   dwTlsIndex   =   0xFFFFFFFF;

// external function declarations

// The DLL entry point extern "C" function declaration and
// "C" run-time library initialization extern "C" function declarations.
extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE hInstDll, DWORD fdwReason, 
                                     LPVOID lpvReserved);
extern "C" BOOL WINAPI _CRT_INIT(HINSTANCE hInstDll, DWORD fdwReason, 
                                 LPVOID lpvReserved);

//$--HrCnvQueryCapability---------------------------------------------------------
//
// DESCRIPTION: Determines whether or not a particular conversion can be
//              done.  The only conversion allowed is from
//              an 822 style header to a MAPI message of classes
//              containing ENVELOPE.IPM or
//              REPORT.IPM
//
// INPUT:       pszOptions  --  (not used)
//              pszClass    --  class of message to convert 
//                          (just needs to be a valid class)
//              pContent    --  822-style header stream pointer
//              pEnv    --  conversion environment pointer 
//
// OUTPUT:      pfAmCandidate   --  TRUE if can do conversion, FALSE otherwise
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//
// ---------------------------------------------------------------------------
static HRESULT HrCnvQueryCapability(
        IN LPCWSTR pszOptions,  // conversion options
        IN LPCWSTR pszClass,    // message class to convert
        IN PVOID pContent,      // 822-style header stream pointer (candidate)
        IN PEDKCNVENV pEnv,     // conversion environment pointer
        OUT BOOL * pfAmCandidate)   // TRUE if can convert, FALSE otherwise
{
    HRESULT hr  =   NOERROR;

    DEBUGPRIVATE("HrCnvQueryCapability()\n");

    // check input parameters
    hr = CHK_HrCnvQueryCapability(pszOptions, pszClass,
                                  pContent, pEnv, pfAmCandidate);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    *pfAmCandidate = FALSE;     // initialize output variable

    // Check target message class
    // We can only convert classes which contain ENVELOPE.IPM or
    // REPORT.IPM.
    if ( (wcsstr(pszClass, IPMENVELOPECLASS) == NULL) &&
         (wcsstr(pszClass, IPMREPORTCLASS) == NULL) )
    {
        goto cleanup;
    }

    // We assume that we can parse the input stream.
    *pfAmCandidate = TRUE;

cleanup:

    RETURN(hr);

}

//$--HrAsciitoIPMFormat--------------------------------------------------------
//
// DESCRIPTION: Converts an "822-style" stream input to a MAPI IPM message.
//
// NOTES:   Only one conversion may be performed at
//          a time (per thread). In order to do concurrent conversions,
//          create multiple threads.
//
// INPUT:       lpStream    --  Stream to read from
//              lpwszClass  --  message class
//              fTNEFEncode --  TNEF encoding flag
//              lpAddrType  --  address type
//              lpAddrBook  --  Address book pointer
//              lpEnvelope  --  message to write to
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_FAIL if API function call failure,
//                              E_NOTIMPL if requesting a feature not implemented
//                              or supported,
//                              EDK_E_ALREADY_EXISTS if a conversion is already
//                              in progress,
//
// ---------------------------------------------------------------------------

static HRESULT HrAsciitoIPMFormat(                     
                               IN LPCWSTR lpwszClass,     // message class
                               IN BOOL fTNEFEncode,       // TNEF encoding flag
                               IN LPCTSTR lpAddrType,     // address type
                               IN LPADRBOOK lpAddrBook,   // address book pointer
                               IN LPSTREAM lpStream,      // pointer to stream
                               IN LPMESSAGE lpMessage)    // pointer to MAPI message envelope
{
    HRESULT         hr              =   NOERROR;
    CIPMConvert *   lpCIPMConvert   =   NULL;   // thread-safe conversion class instance pointer
    BOOL            fInitialized    =   FALSE;  // TRUE if conversion instance already in use

    DEBUGPRIVATE("HrAsciitoIPMFormat()\n");

    // Check input parameters.
    hr = CHK_HrAsciitoIPMFormat(lpwszClass, fTNEFEncode, 
                                lpAddrType, lpAddrBook, lpStream, 
                                lpMessage);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    ASSERTERROR(dwTlsIndex != 0xFFFFFFFF, "Bad thread storage index");

    // Retrieve the conversion class instance pointer for this class.
    lpCIPMConvert = (CIPMConvert *) TlsGetValue(dwTlsIndex);

    if ( !lpCIPMConvert )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    // Initialize conversion instance
    hr = lpCIPMConvert->HrInitialize(lpwszClass, fTNEFEncode,
                                     lpAddrType, lpAddrBook, lpMessage,
                                     lpStream);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Go ahead and do conversion.
    hr = lpCIPMConvert->HrConvert();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // Note: The thread-safe conversion class instance is de-initialized
    // at thread or process termination.

cleanup:

    RETURN(hr);

}

//$--HrCnvConvert---------------------------------------------------------
//
// DESCRIPTION: Converts an 822-style header to a MAPI
//              ENVELOP.IPM or REPORT.IPM message.
//              This function is designed to be called on a per-thread
//              basis.  Each thread can handle one conversion at a time.
//
// INPUT:       pszOptions  --  (not used)
//              pszClass    --  class of message to convert 
//                              (just needs to be a valid class)
//              pContent    --  Stream to read from
//              pContentOut --  MAPI message envelope pointer
//
// OUTPUT:      pcr --  pointer to conversion result enumeration
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if API call failure or syntax error.
//                          E_OUTOFMEMORY if memory problems
//                          E_NOTIMPL if conversion not supported,
//                          EDK_E_ALREADY_EXISTS if busy,
//                          EDK_E_END_OF_FILE if unexpected end-of-file encountered.
//
// ---------------------------------------------------------------------------
static HRESULT HrCnvConvert(
        IN LPCWSTR pszOptions,      // conversion options
        IN LPCWSTR pszClass,        // message class to convert
        IN PVOID pContent,          // stream to convert (candidate)
        IN PVOID pContentOut,       // MAPI message envelope pointer
        IN PEDKCNVENV pEnv,         // conversion environment pointer
        OUT EDKCNVRES * pcr)        // result of conversion
{
    HRESULT         hr          =   NOERROR;
    CONV_OPTIONS *  pConvOpts   =   NULL;   // conversion options structure

    DEBUGPRIVATE("HrCnvConvert()\n");

    // check input parameters
    hr = CHK_HrCnvConvert(pszOptions, pszClass, pContent,
                          pContentOut, pEnv, pcr);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // initialize output parameter
    *pcr = GCR_CONVERSION_FAILED;

    // We can only convert classes which contain ENVELOPE.IPM or
    // REPORT.IPM
    if ( (wcsstr(pszClass, IPMENVELOPECLASS) == NULL) &&
         (wcsstr(pszClass, IPMREPORTCLASS) == NULL) )
    {
        *pcr = GCR_CANNOT_CONVERT;

        goto cleanup;
    }

    // The pGatewayDefined field of the conversion envrironment
    // structure pointer points to a CONV_OPTIONS structure.
    // The CONV_OPTIONS structure contains the TNEF encoding
    // flag and the address book pointer.
    // Note, the CONV_OPTIONS structure was checked for validity
    // in the CHK function.
    pConvOpts = (CONV_OPTIONS *) (pEnv->pGatewayDefined);

    // Let our helper function do the work!
    hr = HrAsciitoIPMFormat(
              pszClass,                     // message class
              pConvOpts->fTnefEncode,       // TNEF encoding flag
              pConvOpts->lpszAddressType,   // address type
              pEnv->lpAB,                   // addres book 
              (LPSTREAM) pContent,          // stream to read from
              (LPMESSAGE) pContentOut);     // MAPI message to write to

    switch (hr)
    {
        case E_NOTIMPL:
            // don't support this conversion type
            *pcr = GCR_CANNOT_CONVERT;

            goto cleanup;

        default:
            if ( FAILED(hr) )
            {
                // conversion failed.
                *pcr = GCR_CONVERSION_FAILED;

                goto cleanup;
            }
    }   // end switch
    
    // if we get to here, then the conversion succeeded.
    *pcr = GCR_OK;
    
cleanup:

    RETURN(hr);        

}

// structure containing pointers to exported functions
static CONVDLLVECT sExportedFuncs =
{
    nDesiredConvDllVersion,  // version number 1
    HrCnvQueryCapability,
    HrCnvConvert
};

//$--HrGetExportVector--------------------------------------------------------
//
// DESCRIPTION: Gets pointer to exported functions structure.
//
// INPUT:       dwVersion   --  version requested
//
// OUTPUT:      ppExportVectors --  pointer to export vector structure pointer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//
// ---------------------------------------------------------------------------

HRESULT HrGetExportVector(     // RETURNS: HRESULT
        IN DWORD dwVersion,         // version requested
        OUT PCONVDLLVECT * ppExportVectors)  // pointer to exported functions structure
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPUBLIC("HrGetExportVector()\n");

    // check input parameters
    hr = CHK_HrGetExportVector(dwVersion, ppExportVectors);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // return pointer to exported vectors structure
    *ppExportVectors = &sExportedFuncs;

    RETURN(hr);

}

//$--DllEntryPoint------------------------------------------------------------
//
// DESCRIPTION: 32-bit Windows DLL entry point procedure.  Called on process
//              and thread initialization and deinitialization.
//              Takes care of calling _CRT_INIT to initialize the "C" run-time
//              library.
//
// INPUT:       hInstDll    --  DLL instance handle
//              fdwReason   --  Reason being called flag (PROCESS_ATTACH ...)
//              lpvReserved --  reserved
//
// RETURNS:     TRUE if successful, FALSE otherwise
//
// ---------------------------------------------------------------------------
BOOL WINAPI DllEntryPoint(                // RETURNS: BOOL
            IN HINSTANCE hInstDll,  // DLL instance handle
            IN DWORD fdwReason,     // reason this function is being called
            IN LPVOID lpvReserved)  // reserved (has static and dynamic call values)
{
    BOOL            fResult         =   TRUE;   // FALSE if can't initialize
    CIPMConvert *   lpCIPMConvert   =   NULL;   // Per-thread conversion class instance pointer

    // check to see why we were called.
    switch ( fdwReason )
    {        
        case DLL_PROCESS_ATTACH:
            // Initialize the "C" run-time libarary.
            fResult = _CRT_INIT(hInstDll, fdwReason, lpvReserved);

            if ( !fResult )
            {
                goto cleanup;
            }

            // Get the thread local storage index.
            dwTlsIndex = TlsAlloc();

            if ( dwTlsIndex == 0xFFFFFFFF )
            {
                // general failure
                fResult = FALSE;

                goto cleanup;
            }

            // Initialize a new conversion class.
            lpCIPMConvert = new CIPMConvert();

            if ( !lpCIPMConvert )
            {
                fResult = FALSE;

                goto cleanup;
            }

            // Store the new thread-safe conversion class in the
            // thread local storage slot.
            fResult = TlsSetValue(dwTlsIndex, (LPVOID) lpCIPMConvert);

            break;

        case DLL_THREAD_ATTACH:
            // Initialize the "C" run-time libarary.
            fResult = _CRT_INIT(hInstDll, fdwReason, lpvReserved);

            if ( !fResult )
            {
                goto cleanup;
            }

            // Initialize a new conversion class.
            lpCIPMConvert = new CIPMConvert();

            if ( !lpCIPMConvert )
            {
                fResult = FALSE;

                goto cleanup;
            }

            // Store the new thread-safe conversion class in the
            // thread local storage slot.
            fResult = TlsSetValue(dwTlsIndex, (LPVOID) lpCIPMConvert);

            break;

        case DLL_THREAD_DETACH:
            // Get our thread-local conversion class instance pointer
            lpCIPMConvert = (CIPMConvert *) TlsGetValue(dwTlsIndex);

            if ( lpCIPMConvert )
            {
                // free this conversion class instance.
                delete lpCIPMConvert;
            }

            // de-initialize the "C" run-time libarary.
            fResult = _CRT_INIT(hInstDll, fdwReason, lpvReserved);

            break;

        case DLL_PROCESS_DETACH:
            // Get our thread-local conversion class instance pointer
            lpCIPMConvert = (CIPMConvert *) TlsGetValue(dwTlsIndex);

            if ( lpCIPMConvert )
            {
                // free this conversion class instance.
                delete lpCIPMConvert;
            }

            // Free our thread-local storage index
            (VOID)TlsFree(dwTlsIndex);

            // de-initialize the "C" run-time libarary.
            fResult = _CRT_INIT(hInstDll, fdwReason, lpvReserved);
                        
            break;

        default:            
            // shouldn't happen
            ASSERTERROR(FALSE, "Bad fdwReason");

            fResult = FALSE;

            break;

    }   // end switch

cleanup:

    return fResult;

}
