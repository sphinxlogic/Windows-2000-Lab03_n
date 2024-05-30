//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 1999
//
// File:        ce.cpp
//
// Contents:    Cert Server Extension Encoding/Decoding implementation
//
//---------------------------------------------------------------------------

#include "pch.cpp"

#pragma hdrstop

#include <stdio.h>
#include <assert.h>
#include "ce.h"
#include "resource.h"


//+--------------------------------------------------------------------------
// ceDecodeObject -- call CryptDecodeObject, and allocate memory for output
//
//+--------------------------------------------------------------------------

BOOL
ceDecodeObject(
    IN DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN BYTE const *pbEncoded,
    IN DWORD cbEncoded,
    OUT VOID **ppvStructInfo,
    OUT DWORD *pcbStructInfo)
{
    BOOL b;

    *ppvStructInfo = NULL;
    *pcbStructInfo = 0;
    while (TRUE)
    {
	b = CryptDecodeObject(
		    dwEncodingType,
		    lpszStructType,
		    pbEncoded,
		    cbEncoded,
		    0,                  // dwFlags
		    *ppvStructInfo,
		    pcbStructInfo);
	if (b && 0 == *pcbStructInfo)
	{
	    SetLastError(HRESULT_FROM_WIN32(ERROR_INVALID_DATA));
	    b = FALSE;
	}
	if (!b)
	{
	    if (NULL != *ppvStructInfo)
	    {
		HRESULT hr = GetLastError();

		LocalFree(*ppvStructInfo);
		*ppvStructInfo = NULL;
		SetLastError(hr);
	    }
	    break;
	}
	if (NULL != *ppvStructInfo)
	{
	    break;
	}
	*ppvStructInfo = (BYTE *) LocalAlloc(LMEM_FIXED, *pcbStructInfo);
	if (NULL == *ppvStructInfo)
	{
	    b = FALSE;
	    break;
	}
    }
    return(b);
}


BOOL
ceEncodeObject(
    IN DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN VOID const *pvStructInfo,
    OUT BYTE **ppbEncoded,
    OUT DWORD *pcbEncoded)
{
    BOOL b;

    *ppbEncoded = NULL;
    *pcbEncoded = 0;
    while (TRUE)
    {
	b = CryptEncodeObject(
		    dwEncodingType,
		    lpszStructType,
		    const_cast<VOID *>(pvStructInfo),
		    *ppbEncoded,
		    pcbEncoded);
	if (b && 0 == *pcbEncoded)
	{
	    SetLastError(HRESULT_FROM_WIN32(ERROR_INVALID_DATA));
	    b = FALSE;
	}
	if (!b)
	{
	    if (NULL != *ppbEncoded)
	    {
		HRESULT hr = GetLastError();

		LocalFree(*ppbEncoded);
		*ppbEncoded = NULL;
		SetLastError(hr);
	    }
	    break;
	}
	if (NULL != *ppbEncoded)
	{
	    break;
	}
	*ppbEncoded = (BYTE *) LocalAlloc(LMEM_FIXED, *pcbEncoded);
	if (NULL == *ppbEncoded)
	{
	    b = FALSE;
	    break;
	}
    }
    return(b);
}


WCHAR *
ceDuplicateString(
    IN WCHAR const *pwsz)
{
    WCHAR *pwszOut;

    pwszOut = (WCHAR *) LocalAlloc(
				LMEM_FIXED,
				(wcslen(pwsz) + 1) * sizeof(pwsz[0]));
    if (NULL != pwszOut)
    {
	wcscpy(pwszOut, pwsz);
    }
    return(pwszOut);
}


BOOL
ceConvertWszToSz(
    OUT CHAR **ppsz,
    IN WCHAR const *pwc,
    IN LONG cwc)
{
    BOOL fOk = FALSE;
    LONG cch = 0;

    *ppsz = NULL;
    while (TRUE)
    {
	cch = WideCharToMultiByte(
			GetACP(),
			0,          // dwFlags
			pwc,
			cwc,        // cchWideChar, -1 => null terminated
			*ppsz,
			cch,
			NULL,
			NULL);
	if (0 >= cch)
	{
	    DWORD err;

	    err = GetLastError();
	    ceERRORPRINTLINE("WideCharToMultiByte", err);
	    if (NULL != *ppsz)
	    {
		LocalFree(*ppsz);
		*ppsz = NULL;
	    }
	    break;
	}
	if (NULL != *ppsz)
	{
	    fOk = TRUE;
	    break;
	}
	*ppsz = (CHAR *) LocalAlloc(LMEM_FIXED, cch + 1);
	if (NULL == *ppsz)
	{
	    break;
	}
    }
    return(fOk);
}


BOOL
ceConvertWszToBstr(
    OUT BSTR *pbstr,
    IN WCHAR const *pwc,
    IN LONG cb)
{
    BOOL fOk = FALSE;
    BSTR bstr;

    ceFreeBstr(pbstr);
    do
    {
	bstr = NULL;
	if (NULL != pwc)
	{
	    if (-1 == cb)
	    {
		cb = wcslen(pwc) * sizeof(WCHAR);
	    }
	    bstr = SysAllocStringByteLen((char const *) pwc, cb);
	    if (NULL == bstr)
	    {
		break;
	    }
	}
	*pbstr = bstr;
	fOk = TRUE;
    } while (FALSE);
    return(fOk);
}


BOOL
ceConvertSzToWsz(
    OUT WCHAR **ppwsz,
    IN char const *pch,
    IN LONG cch)
{
    BOOL fOk = FALSE;
    LONG cwc = 0;

    *ppwsz = NULL;
    while (TRUE)
    {
	cwc = MultiByteToWideChar(GetACP(), 0, pch, cch, *ppwsz, cwc);
	if (0 >= cwc)
	{
	    DWORD err;

	    err = GetLastError();
	    ceERRORPRINTLINE("MultiByteToWideChar", err);
	    if (NULL != *ppwsz)
	    {
		LocalFree(*ppwsz);
		*ppwsz = NULL;
	    }
	    break;
	}
	if (NULL != *ppwsz)
	{
	    fOk = TRUE;
	    break;
	}
	*ppwsz = (WCHAR *) LocalAlloc(LMEM_FIXED, (cwc + 1) * sizeof(WCHAR));
	if (NULL == *ppwsz)
	{
	    break;
	}
    }
    return(fOk);
}


BOOL
ceConvertSzToBstr(
    OUT BSTR *pbstr,
    IN CHAR const *pch,
    IN LONG cch)
{
    BOOL fOk = FALSE;
    BSTR bstr = NULL;
    LONG cwc = 0;

    ceFreeBstr(pbstr);
    if (-1 == cch)
    {
	cch = strlen(pch);
    }
    while (TRUE)
    {
	cwc = MultiByteToWideChar(GetACP(), 0, pch, cch, bstr, cwc);
	if (0 >= cwc)
	{
	    //hr = ceHLastError();
	    //printf("MultiByteToWideChar returned %d (%x)\n", hr, hr);
	    break;
	}
	if (NULL != bstr)
	{
	    bstr[cwc] = L'\0';
	    *pbstr = bstr;
	    fOk = TRUE;
	    break;
	}
	bstr = SysAllocStringLen(NULL, cwc);
	if (NULL == bstr)
	{
	    break;
	}
    }
    return(fOk);
}


VOID
ceFreeBstr(
    IN OUT BSTR *pstr)
{
    if (NULL != *pstr)
    {
	SysFreeString(*pstr);
	*pstr = NULL;
    }
}


HRESULT
ceHError(
    IN HRESULT hr)
{
    assert(S_FALSE != hr);

    if (S_OK != hr && S_FALSE != hr && !FAILED(hr))
    {
        hr = HRESULT_FROM_WIN32(hr);
	if (0 == HRESULT_CODE(hr))
	{
	    // A call failed without properly setting an error condition!
	    hr = E_UNEXPECTED;
	}
	assert(FAILED(hr));
    }
    return(hr);
}


HRESULT
ceHLastError(VOID)
{
    return(ceHError(GetLastError()));
}


VOID
ceErrorPrintLine(
    IN char const *pszFile,
    IN DWORD line,
    IN char const *pszMessage,
    IN HRESULT hr)
{
    printf(
	"CertEnc.Dll: Error: %s(%u): %s 0x%x (%d)\n",
	pszFile,
	line,
	pszMessage,
	hr,
	hr);
}


HRESULT
ceDateToGMTFileTime(
    IN DATE const *pDateLocal,
    OUT FILETIME *pftGMT)
{
    SYSTEMTIME stLocal;
    HRESULT hr = S_OK;

    if (!VariantTimeToSystemTime(*pDateLocal, &stLocal))
    {
        hr = E_INVALIDARG;
        ceERRORPRINTLINE("VariantTimeToSystemTime", hr);
        goto error;
    }
    if (!SystemTimeToFileTime(&stLocal, pftGMT))
    {
        hr = ceHLastError();
        ceERRORPRINTLINE("SystemTimeToFileTime", hr);
        goto error;
    }
error:
    return(hr);
}


HRESULT
ceGMTFileTimeToDate(
    IN FILETIME const *pftGMT,
    OUT DATE *pDateLocal)
{
    SYSTEMTIME stLocal;
    HRESULT hr = S_OK;

    if (!FileTimeToSystemTime(pftGMT, &stLocal))
    {
        hr = ceHLastError();
        ceERRORPRINTLINE("FileTimeToSystemTime", hr);
        goto error;
    }
    if (!SystemTimeToVariantTime(&stLocal, pDateLocal))
    {
	hr = HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
        ceERRORPRINTLINE("SystemTimeToVariantTime", hr);
        goto error;
    }
error:
    return(hr);
}


HRESULT
ceVerifyObjId(
    IN WCHAR const *pwszObjId)
{
    HRESULT hr;
    CHAR *pszObjId = NULL;
    DWORD cbEncoded;
    CRYPT_ATTRIBUTE ainfo;

    if (!ceConvertWszToSz(&pszObjId, pwszObjId, -1))
    {
	hr = E_OUTOFMEMORY;
        ceERRORPRINTLINE("ceConvertWszToSz", hr);
        goto error;
    }

    ainfo.pszObjId = pszObjId;
    ainfo.cValue = 0;
    if (!CryptEncodeObject(
		     X509_ASN_ENCODING,
		     PKCS_ATTRIBUTE,
		     &ainfo,
		     NULL,
		     &cbEncoded))
    {
        hr = E_INVALIDARG;
        ceERRORPRINTLINE("invalid Obj Id", hr);
        goto error;
    }
    hr = S_OK;

error:
    if (NULL != pszObjId)
    {
    	LocalFree(pszObjId);
    }
    return(hr);
}


HRESULT
ceVerifyAltNameString(
    IN LONG NameChoice,
    IN WCHAR const *pwszName)
{
    HRESULT hr = S_OK;
    CERT_ALT_NAME_INFO AltName;
    CERT_ALT_NAME_ENTRY Entry;
    char *pszObjectId = NULL;
    DWORD cbEncoded;

    ZeroMemory(&AltName, sizeof(AltName));
    AltName.cAltEntry = 1;
    AltName.rgAltEntry = &Entry;

    ZeroMemory(&Entry, sizeof(Entry));
    Entry.dwAltNameChoice = NameChoice;

    switch (NameChoice)
    {
	case CERT_ALT_NAME_RFC822_NAME:
	    Entry.pwszRfc822Name = const_cast<WCHAR *>(pwszName);
	    break;

	case CERT_ALT_NAME_DNS_NAME:
	    Entry.pwszDNSName = const_cast<WCHAR *>(pwszName);
	    break;

	case CERT_ALT_NAME_URL:
	    Entry.pwszURL = const_cast<WCHAR *>(pwszName);
	    break;

	case CERT_ALT_NAME_REGISTERED_ID:
	    if (!ceConvertWszToSz(&pszObjectId, pwszName, -1))
	    {
		hr = E_OUTOFMEMORY;
		ceERRORPRINTLINE("ceConvertWszToSz", hr);
		goto error;
	    }
	    Entry.pszRegisteredID = pszObjectId;
	    break;

	//case CERT_ALT_NAME_DIRECTORY_NAME:
	//case CERT_ALT_NAME_OTHER_NAME:
	//case CERT_ALT_NAME_X400_ADDRESS:
	//case CERT_ALT_NAME_EDI_PARTY_NAME:
	//case CERT_ALT_NAME_IP_ADDRESS:
	default:
	    hr = E_INVALIDARG;
	    ceERRORPRINTLINE("NameChoice", hr);
	    goto error;
		
    }

    // Encode CERT_ALT_NAME_INFO:

    if (!CryptEncodeObject(
		    X509_ASN_ENCODING,
		    X509_ALTERNATE_NAME,
		    &AltName,
		    NULL,
		    &cbEncoded))
    {
	hr = ceHLastError();
	ceERRORPRINTLINE("ceEncodeObject", hr);
	goto error;
    }

error:
    if (NULL != pszObjectId)
    {
	LocalFree(pszObjectId);
    }
    return(hr);
}


HRESULT
ceDispatchSetErrorInfo(
    IN HRESULT hrError,
    IN WCHAR const *pwszDescription,
    OPTIONAL IN WCHAR const *pwszProgId,
    OPTIONAL IN IID const *piid)
{
    HRESULT hr;
    ICreateErrorInfo *pCreateErrorInfo = NULL;
    IErrorInfo *pErrorInfo = NULL;
    WCHAR *pwszError = NULL;
    WCHAR *pwszText = NULL;

    assert(FAILED(hrError));
    pwszError = ceGetErrorMessageText(hrError, TRUE);
    if (NULL == pwszError)
    {
	ceERRORPRINTLINE("ceGetErrorMessageText", E_OUTOFMEMORY);
    }
    else
    {
	pwszText = (WCHAR *) LocalAlloc(
	    LMEM_FIXED,
	    (wcslen(pwszDescription) + 1 + wcslen(pwszError) + 1) *
	     sizeof(WCHAR));
	if (NULL == pwszText)
	{
	    ceERRORPRINTLINE("LocalAlloc", E_OUTOFMEMORY);
	}
	else
	{
	    wcscpy(pwszText, pwszDescription);
	    wcscat(pwszText, L" ");
	    wcscpy(pwszText, pwszError);
	}
    }

    hr = CreateErrorInfo(&pCreateErrorInfo);
    if (S_OK != hr)
    {
        ceERRORPRINTLINE("CreateErrorInfo", hr);
        goto error;
    }

    if (NULL != piid)
    {
	hr = pCreateErrorInfo->SetGUID(*piid);
	if (S_OK != hr)
	{
	    ceERRORPRINTLINE("SetGUID", hr);
	}
    }

    hr = pCreateErrorInfo->SetDescription(
		    NULL != pwszText?
			pwszText : const_cast<WCHAR *>(pwszDescription));
    if (S_OK != hr)
    {
	ceERRORPRINTLINE("SetDescription", hr);
    }

    // Set ProgId:

    if (NULL != pwszProgId)
    {
	hr = pCreateErrorInfo->SetSource(const_cast<WCHAR *>(pwszProgId));
	if (S_OK != hr)
	{
	    ceERRORPRINTLINE("SetSource", hr);
	}
    }

    hr = pCreateErrorInfo->QueryInterface(
				    IID_IErrorInfo,
				    (VOID **) &pErrorInfo);
    if (S_OK != hr)
    {
        ceERRORPRINTLINE("QueryInterface", hr);
        goto error;
    }

    SetErrorInfo(0, pErrorInfo);

error:
    if (NULL != pErrorInfo)
    {
	pErrorInfo->Release();
    }
    if (NULL != pCreateErrorInfo)
    {
	pCreateErrorInfo->Release();
    }
    if (NULL != pwszText)
    {
	LocalFree(pwszText);
    }
    if (NULL != pwszError)
    {
	LocalFree(pwszError);
    }
    return(hrError);	// return input error!
}


// Alloc and return error message string

WCHAR *
ceGetErrorMessageText(
    IN HRESULT hr,
    IN BOOL fHResultString)
{
    static WCHAR s_wszUknownDefault[] = L"Error %ws %ws";
    WCHAR *pwszRet = NULL;
    WCHAR *pwszMsgT;
    WCHAR const *pwszUnknown;
    WCHAR wszUnknown[10 * ARRAYSIZE(s_wszUknownDefault)];
    WCHAR wszUnexpected[512];
    WCHAR awchr[cwcHRESULTSTRING];
    DWORD cwc;
    DWORD cwcUnexpected = 0;
    HMODULE hMod = NULL;

    wszUnexpected[0] = L'\0';
    if (E_UNEXPECTED == hr)
    {
	cwcUnexpected = LoadString(
		    NULL,
		    IDS_E_UNEXPECTED,	// L"Unexpected method call sequence."
		    wszUnknown,
		    ARRAYSIZE(wszUnknown));
    }
    cwc = FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
		    FORMAT_MESSAGE_FROM_SYSTEM |
		    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                hr,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                (WCHAR *) &pwszRet,    
                0,    
                NULL);
    if (0 == cwc)
    {
	hMod = LoadLibrary(L"ntdsbmsg.dll");
	if (NULL != hMod)
	{
	    cwc = FormatMessage(
		    FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_HMODULE |
			FORMAT_MESSAGE_IGNORE_INSERTS,
		    hMod,
		    hr,
		    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
		    (WCHAR *) &pwszRet,    
		    0,    
		    NULL);
	}
    }
    if (0 == cwc)
    {
	// couldn't find error, _snwprintf it instead

	cwc = LoadString(
		    NULL,
		    IDS_UNKNOWN_ERROR_CODE,	// L"Error %ws %ws"
		    wszUnknown,
		    ARRAYSIZE(wszUnknown));
	if (0 == cwc)
	{
	    pwszUnknown = s_wszUknownDefault;
	}
	else
	{
	    pwszUnknown = wszUnknown;
	}
	cwc = wcslen(pwszUnknown) + cwcUnexpected + ARRAYSIZE(awchr) + 1;
        pwszRet = (WCHAR *) LocalAlloc(LMEM_FIXED, cwc * sizeof(WCHAR));
	if (NULL == pwszRet)
	{
	    ceERRORPRINTLINE("LocalAlloc", E_OUTOFMEMORY);
	    goto error;
	}
        _snwprintf(
		pwszRet,
		cwc,
		pwszUnknown,
		wszUnexpected,
		ceHResultToString(awchr, hr));
    }
    else
    {
        // strip trailing \r\n

        cwc = wcslen(pwszRet);

        if (2 <= cwc &&
	    L'\r' == pwszRet[cwc - 2] &&
	    L'\n' == pwszRet[cwc - 1])
	{
            pwszRet[cwc - 2] = L'\0';
	}
	awchr[0] = L'\0';
	if (fHResultString)
	{
	    ceHResultToString(awchr, hr);
	}
	if (fHResultString || 0 != cwcUnexpected)
	{
	    cwc = wcslen(pwszRet) + 1 + cwcUnexpected + 1 + wcslen(awchr) + 1;
	    pwszMsgT = (WCHAR *) LocalAlloc(LMEM_FIXED, cwc * sizeof(WCHAR));
	    if (NULL == pwszMsgT)
	    {
		ceERRORPRINTLINE("LocalAlloc", E_OUTOFMEMORY);
		goto error;
	    }
	    _snwprintf(
		    pwszMsgT,
		    cwc,
		    L"%ws %ws %ws",
		    pwszRet,
		    wszUnexpected,
		    awchr);
	    LocalFree(pwszRet);
	    pwszRet = pwszMsgT;
	}
    }

error:
    if (NULL != hMod)
    {
	FreeLibrary(hMod);
    }
    return(pwszRet);
}
