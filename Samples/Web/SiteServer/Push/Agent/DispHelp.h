/****************************************************************************
 ** 
 ** Microsoft Site Server v3.00
 ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.
 ** 
 ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
 ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
 ** PURPOSE.
 **
 **
 ** CONTENTS
 **     COleDispatchDriverEx
 **
 ** NOTES
 **     stdafx.cpp : source file that includes just the standard includes
 **     stdafx.pch will be the pre-compiled header
 **     stdafx.obj will contain the pre-compiled type information
 **
 ****************************************************************************/

#pragma once

class COleDispatchDriverEx : public COleDispatchDriver
{
public:
    void operator=(LPDISPATCH lp);
    HRESULT InvokeHelper(LPCTSTR pszName, WORD wFlags, VARIANT* pVar, const PBYTE pbParamInfo = NULL, ...);

    static HRESULT SecureInterface(LPUNKNOWN lpUnk);
};

HRESULT GetFromVariant(CStringArray& rgstrData, const VARIANT* pVar);
HRESULT PutIntoVariant(VARIANT* pVar, const CStringArray& rgstrData);
