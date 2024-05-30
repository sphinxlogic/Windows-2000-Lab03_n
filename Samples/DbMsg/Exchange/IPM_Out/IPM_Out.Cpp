// --ipm_out.cpp--------------------------------------------------------------
//
// API entry points for the ipm_out dynamic link library.
// Converts MAPI messages to an 822-style header.
// This is the "Outbound IPM Converter" refered to in "Sample Gateway
// Vision, Requirements, Architecture and File Formats".
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include "edk.h"
#include "ipmconv.h"
#include "msgemit.h"
#include "convcls.h"
#include "ipm_out.chk"

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
//              a MAPI message of class ENVELOPE.IPM.NOTE or
//              REPORT.IPM.NOTE to a 822-style header
//              which is written an output stream.
//
// INPUT:       pszOptions  --  (not used)
//              pszClass    --  class of message to convert
//              pContent    --  MAPI message to convert
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
        IN PVOID pContent,      // message to convert (candidate)
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

    // Initialize output variable.
    *pfAmCandidate = FALSE;

    // We can only convert message classes which contain ENVELOPE.IPM
    // or REPORT.IPM
    if ( (wcsstr(pszClass, IPMENVELOPECLASS) == NULL) &&
         (wcsstr(pszClass, IPMREPORTCLASS) == NULL) )
    {
        goto cleanup;
    }

    // If we get to here, we can convert the message
    *pfAmCandidate = TRUE;

cleanup:

    RETURN(hr);

}

//$--HrIPMto822Format--------------------------------------------------------
//
// DESCRIPTION: Converts a MAPI IPM message to a "822-style" stream output
//
// NOTES:   Only one conversion may be performed at
//          a time (per thread). In order to do concurrent conversions,
//          create multiple threads.
//
// INPUT:       lpwszClass  --  message class
//              lpAddrBook  --  address book pointer
//              lpMessage   --  Pointer to MAPI message.
//              bTNEFEncode --  Do TNEF encoding of message attachment flag
//              lpStream    --  Stream to write to
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

static HRESULT HrIPMto822Format(                       
                               IN LPCWSTR lpwszClass,     // message class
                               IN BOOL fTNEFEncode,       // TRUE is should encode attachments
                               IN LPADRBOOK lpAddrBook,   // address book pointer
                               IN LPMESSAGE lpMessage,    // pointer to MAPI message
                               IN LPSTREAM lpStream)      // pointer to stream
{
    HRESULT         hr              =   NOERROR;
    CIPMConvert *   lpCIPMConvert   =   NULL;   // thread-safe conversion class instance pointer
    BOOL            fInitialized    =   FALSE;  // TRUE if conversion instance already in use

    DEBUGPRIVATE("HrIPMto822Format()\n");

    // Check input parameters.
    hr = CHK_HrIPMto822Format(lpwszClass, fTNEFEncode, 
                              lpAddrBook, lpMessage, lpStream);

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
                                     lpAddrBook,
                                     lpMessage, lpStream);

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

}   // end HrIPMto822Format()

//$--HrCnvConvert---------------------------------------------------------
//
// DESCRIPTION: Converts MAPI ENVELOPOE.IPM.* or REPORT.IPM.*
//              to an 822-style header and writes
//              the header to the stream passed in.
//              This function is designed to be called on a per-thread
//              basis.  Each thread can handle one conversion at a time.
//
// INPUT:       pszOptions  --  (not used)
//              pszClass    --  class of message to convert 
//                              (must contain ENVELOPE.IPM or
//                              REPORT.IPM)
//              pContent    --  MAPI message to convert
//              pContentOut --  Stream to write header to
//              pEnv    --  conversion environment pointer
//
// OUTPUT:      pcr --  pointer to conversion result enumeration
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL if API call failure,
//                          E_OUTOFMEMORY if memory problems
//                          E_NOTIMPL if conversion not supported,
//                          EDK_E_ALREADY_EXISTS if busy
//
// ---------------------------------------------------------------------------
static HRESULT HrCnvConvert(        
        IN LPCWSTR pszOptions,  // conversion options
        IN LPCWSTR pszClass,    // message class to convert
        IN PVOID pContent,      // message to convert (candidate)
        IN PVOID pContentOut,   // stream to write 822-style header to
        IN PEDKCNVENV pEnv,     // conversion environment pointer
        OUT EDKCNVRES * pcr)    // result of conversion
{
    HRESULT     hr          =   NOERROR;

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
    // REPORT.IPM.
    if ( (wcsstr(pszClass, IPMENVELOPECLASS) == NULL) &&
         (wcsstr(pszClass, IPMREPORTCLASS) == NULL) )
    {
        *pcr = GCR_CANNOT_CONVERT;

        goto cleanup;
    }

    // Let our helper function do the work!
    hr = HrIPMto822Format(
        pszClass,                   // message class
        ((CONV_OPTIONS *) (pEnv->pGatewayDefined))->fTnefEncode,  // TNEF flag
        pEnv->lpAB,                 // address book pointer
        (LPMESSAGE) pContent,       // message to convert
        (LPSTREAM) pContentOut);    // stream to write to

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

HRESULT HrGetExportVector(     
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

    }   // end switch

cleanup:

    return fResult;

}
