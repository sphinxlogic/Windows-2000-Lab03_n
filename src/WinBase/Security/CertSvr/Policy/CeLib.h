//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1995 - 1999
//
//  File:       celib.h
//
//  Contents:   helper functions
//
//--------------------------------------------------------------------------

#ifndef __CELIB_H__
#define __CELIB_H__

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
    IN DWORD dwEncodingType,
    IN LPCSTR lpszStructType,
    IN VOID const *pvStructInfo,
    OUT BYTE **ppbEncoded,
    OUT DWORD *pcbEncoded);

BOOL
ceConvertWszToBstr(
    OUT BSTR *pbstr,
    IN WCHAR const *pwc,
    IN LONG cb);

#endif // __CELIB_H__
