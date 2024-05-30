//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
// Factory.cpp : Implementation of CFactory
#include "stdafx.h"
#include "AtlBehave.h"
#include "Factory.h"

/////////////////////////////////////////////////////////////////////////////
// CFactory
	STDMETHODIMP
CFactory::FindBehavior(
	BSTR pchNameSpace,
	BSTR pchTagName,
	IElementBehaviorSite* pUnkArg,
	IElementBehavior** ppBehavior)
{
HRESULT					hr;
CComObject<CBehavior>*	pBehavior;

	// Create a behavior object
	hr = CComObject<CBehavior>::CreateInstance( &pBehavior );
	if ( SUCCEEDED(hr) )
		return pBehavior->QueryInterface( __uuidof(IElementBehavior), (void**)ppBehavior );
	else
		return hr;
}

