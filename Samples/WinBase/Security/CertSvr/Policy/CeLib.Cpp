//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1995 - 1999
//
//  File:       celib.cpp
//
//  Contents:   helper functions
//
//--------------------------------------------------------------------------

#include "pch.cpp"
#pragma hdrstop

#include "celib.h"


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
		    (VOID *) pvStructInfo,	// BUGBUG const
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


BOOL
ceConvertWszToBstr(
    OUT BSTR *pbstr,
    IN WCHAR const *pwc,
    IN LONG cb)
{
    BOOL fOk = FALSE;
    BSTR bstr;

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
	if (NULL != *pbstr)
	{
	    SysFreeString(*pbstr);
	}
	*pbstr = bstr;
	fOk = TRUE;
    } while (FALSE);
    return(fOk);
}
