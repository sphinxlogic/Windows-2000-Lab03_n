//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 1999
//
// File:        ce.h
//
// Contents:    Cert Server encode/decode support
//
//---------------------------------------------------------------------------

#define ceERRORPRINTLINE(pszMessage, hr) \
	    ceErrorPrintLine(__FILE__, __LINE__, (pszMessage), (hr))

#define CENCODEMAX	(64 * 1024)

// Bitmap manipulation routines.  Fetch or set a bit, given a base and index.
#define GETBIT(pb, i)	((pb)[(i) / 8] & (1 << ((i) % 8)))
#define SETBIT(pb, i)	((pb)[(i) / 8] |= (1 << ((i) % 8)))
#define CLEARBIT(pb, i)	((pb)[(i) / 8] &= ~(1 << ((i) % 8)))

#define BITSTOBYTES(b)	((int)(((b) + 7) / 8))

// Size of a fixed array:
#define ARRAYSIZE(a)		(sizeof(a)/sizeof((a)[0]))

#define cwcHRESULTSTRING	40


VOID
ceErrorPrintLine(
    IN char const *pszFile,
    IN DWORD line,
    IN char const *pszMessage,
    IN HRESULT hr);

HRESULT
ceHLastError(VOID);

HRESULT
ceHError(
    IN HRESULT hr);

BOOL
ceDecodeObject(
    IN DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN BYTE const *pbEncoded,
    IN DWORD cbEncoded,
    OUT VOID **ppvStructInfo,
    OUT DWORD *pcbStructInfo);

BOOL
ceEncodeObject(
    DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN VOID const *pvStructInfo,
    OUT BYTE **ppbEncoded,
    OUT DWORD *pcbEncoded);

WCHAR *
ceDuplicateString(
    IN WCHAR const *pwsz);

BOOL
ceConvertWszToSz(
    OUT char **ppsz,
    IN WCHAR const *pwc,
    IN LONG cb);

BOOL
ceConvertWszToBstr(
    OUT BSTR *pbstr,
    IN WCHAR const *pwc,
    IN LONG cb);

BOOL
ceConvertSzToWsz(
    OUT WCHAR **ppwsz,
    IN char const *pch,
    IN LONG cch);

BOOL
ceConvertSzToBstr(
    OUT BSTR *pbstr,
    IN CHAR const *pch,
    IN LONG cch);

VOID
ceFreeBstr(
    IN OUT BSTR *pstr);

HRESULT
ceDateToGMTFileTime(
    IN DATE const *pDateLocal,
    OUT FILETIME *pftGMT);

HRESULT
ceGMTFileTimeToDate(
    IN FILETIME const *pftGMT,
    OUT DATE *pDateLocal);

HRESULT
ceVerifyObjId(
    IN WCHAR const *pwszObjId);

HRESULT
ceVerifyAltNameString(
    IN LONG NameChoice,
    IN WCHAR const *pwszName);

HRESULT
ceDispatchSetErrorInfo(
    IN HRESULT hrError,
    IN WCHAR const *pwszDescription,
    OPTIONAL IN WCHAR const *pwszProgId,
    OPTIONAL IN IID const *piid);

WCHAR *
ceGetErrorMessageText(
    IN HRESULT hr,
    IN BOOL fHResultString);

WCHAR const *
ceHResultToString(
    IN OUT WCHAR *awchr,
    IN HRESULT hr);
