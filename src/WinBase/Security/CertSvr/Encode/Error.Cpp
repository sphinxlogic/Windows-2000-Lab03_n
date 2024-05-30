//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 1999
//
// File:        error.cpp
//
// Contents:    Cert Server error wrapper routines
//
//---------------------------------------------------------------------------

#include <pch.cpp>

#pragma hdrstop

#include "ce.h"
#include <assert.h>
#include <ntdsbmsg.h>


#define CERTLIB_12BITERRORMASK	0x00000fff
#define CERTLIB_WIN32ERRORMASK	0x0000ffff


//+--------------------------------------------------------------------------
// Jet errors:

#define HRESULT_FROM_JETWARNING(jerr) \
	((STATUS_SEVERITY_WARNING << 30) | (FACILITY_NTDSB << 16) | jerr)

#define HRESULT_FROM_JETERROR(jerr) \
	((STATUS_SEVERITY_ERROR << 30) | (FACILITY_NTDSB << 16) | -jerr)

#define JETERROR_FROM_HRESULT(hr) \
	(-(LONG) (CERTLIB_WIN32ERRORMASK & (hr)))

#define ISJETERROR(hr) \
    ((~CERTLIB_WIN32ERRORMASK & (hr)) == ~CERTLIB_WIN32ERRORMASK)

#define ISJETHRESULT(hr) \
    ((~CERTLIB_WIN32ERRORMASK & (hr)) == ((STATUS_SEVERITY_ERROR << 30) | \
					  (FACILITY_NTDSB << 16)))

#define wszJETERRORPREFIX	L"EDB"


//+--------------------------------------------------------------------------
// Win32 errors:

#define ISWIN32ERROR(hr) \
    ((~CERTLIB_WIN32ERRORMASK & (hr)) == 0)

#define ISWIN32HRESULT(hr) \
    ((~CERTLIB_WIN32ERRORMASK & (hr)) == ((STATUS_SEVERITY_WARNING << 30) | \
					  (FACILITY_WIN32 << 16)))

#define WIN32ERROR_FROM_HRESULT(hr) \
    (CERTLIB_WIN32ERRORMASK & (hr))

#define wszWIN32ERRORPREFIX	L"WIN32"


//+--------------------------------------------------------------------------
// Delayload errors:

#define FACILITY_DELAYLOAD	109
#define DELAYLOAD_FROM_WIN32(hr) \
    ((HRESULT) ((STATUS_SEVERITY_ERROR << 30) | \
		(FACILITY_DELAYLOAD << 16) | \
		(hr)))

#define WIN32ERROR_FROM_DELAYLOAD(hr) \
    (CERTLIB_WIN32ERRORMASK & (hr))

#define ISDELAYLOADHRESULTFACILITY(hr) \
    ((~CERTLIB_WIN32ERRORMASK & (hr)) == ((STATUS_SEVERITY_ERROR << 30) | \
					  (FACILITY_DELAYLOAD << 16)))

// E_DELAYLOAD_MOD_NOT_FOUND	0xc06d007e
#define E_DELAYLOAD_MOD_NOT_FOUND   DELAYLOAD_FROM_WIN32(ERROR_MOD_NOT_FOUND)

// E_DELAYLOAD_PROC_NOT_FOUND	0xc06d007f
#define E_DELAYLOAD_PROC_NOT_FOUND  DELAYLOAD_FROM_WIN32(ERROR_PROC_NOT_FOUND)

#define ISDELAYLOADHRESULT(hr) \
    (E_DELAYLOAD_MOD_NOT_FOUND == (hr) || \
     E_DELAYLOAD_PROC_NOT_FOUND == (hr) || \
     HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND) == (hr) || \
     HRESULT_FROM_WIN32(ERROR_PROC_NOT_FOUND) == (hr))


//+--------------------------------------------------------------------------
// ASN encoding errors:

#define ISOSSERROR(hr) \
    ((~CERTLIB_12BITERRORMASK & (hr)) == CRYPT_E_OSS_ERROR)

#define OSSERROR_FROM_HRESULT(hr) \
    (CERTLIB_12BITERRORMASK & (hr))

#define wszOSSERRORPREFIX	L"ASN"




HRESULT
ceJetHResult(
    IN HRESULT hr)
{
#if DBG_CERTSRV
    HRESULT hrIn = hr;
#endif
    if (S_OK != hr)
    {
        if (SUCCEEDED(hr))
        {
#if 0
	    hr = HRESULT_FROM_JETWARNING(hr);
#else
            if (S_FALSE != hr)
	    {
		ceERRORPRINTLINE("JetHResult: mapping to S_FALSE", hr);
	    }
            assert(S_FALSE == hr);
            hr = S_FALSE;
#endif
        }
        else if (ISJETERROR(hr))
        {
	    hr = HRESULT_FROM_JETERROR(hr);
        }
    }
    assert(S_OK == hr || S_FALSE == hr || FAILED(hr));
    return(hr);
}


HRESULT
ceHExceptionCode(
    IN EXCEPTION_POINTERS const *pep)
{
    HRESULT hr = pep->ExceptionRecord->ExceptionCode;

    return(ceHError(hr));
}


BOOL
ceIsDelayLoadHResult(
    IN HRESULT hr)
{
    return(ISDELAYLOADHRESULT(hr));
}


#define wszCOLONSPACE	L": "

WCHAR const *
ceHResultToStringEx(
    IN OUT WCHAR *awchr,
    IN HRESULT hr,
    IN BOOL fRaw)
{
    HRESULT hrd;
    WCHAR const *pwszType;

    hrd = hr;
    pwszType = L"";
    if (ISJETERROR(hr))
    {
	pwszType = wszJETERRORPREFIX wszCOLONSPACE;
    }
    else if (ISJETHRESULT(hr))
    {
	hrd = JETERROR_FROM_HRESULT(hr);
	pwszType = wszJETERRORPREFIX wszCOLONSPACE;
    }
    else if (ISWIN32HRESULT(hr))
    {
	hrd = WIN32ERROR_FROM_HRESULT(hr);
	pwszType = wszWIN32ERRORPREFIX wszCOLONSPACE;
    }
    else if (ISDELAYLOADHRESULTFACILITY(hr))
    {
	hrd = WIN32ERROR_FROM_DELAYLOAD(hr);
	pwszType = wszWIN32ERRORPREFIX wszCOLONSPACE;
    }
    else if (ISOSSERROR(hr))
    {
	hrd = OSSERROR_FROM_HRESULT(hr);
	pwszType = wszOSSERRORPREFIX wszCOLONSPACE;
    }
    if (fRaw)
    {
	pwszType = L"";
    }

    _snwprintf(
	awchr,
	cwcHRESULTSTRING,
	L"0x%x (%ws%d)",
	hr,
	pwszType,
	hrd);
    return(awchr);
}


WCHAR const *
ceHResultToString(
    IN OUT WCHAR *awchr,
    IN HRESULT hr)
{
    return(ceHResultToStringEx(awchr, hr, FALSE));
}


WCHAR const *
ceHResultToStringRaw(
    IN OUT WCHAR *awchr,
    IN HRESULT hr)
{
    return(ceHResultToStringEx(awchr, hr, TRUE));
}
