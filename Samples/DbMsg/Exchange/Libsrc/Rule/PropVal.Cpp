// ----------------------------------------------------------------------------
//	PropVal.cpp : Implementation of CPropVal
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "PropVal.h"
#include "util.h"

// CPropVal
CPropVal::~CPropVal()
{
	cleanup();
}

void CPropVal::cleanup()
{
	VariantClear(&m_lVariant);
}

STDMETHODIMP CPropVal::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPropVal,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CPropVal::get_Tag(long *pVal)
{
	if(pVal)
	{
		*pVal = m_ulPropTag;
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CPropVal::put_Tag(long newVal)
{
	m_ulPropTag = newVal;
	return S_OK;
}

STDMETHODIMP CPropVal::get_Value(VARIANT *pVal)
{
	if(pVal)
	{
		VariantClear(pVal);
		return VariantCopy(pVal, &m_lVariant);
	}
	return E_INVALIDARG;
}

STDMETHODIMP CPropVal::put_Value(VARIANT newVal)
{
	HRESULT	hr=E_INVALIDARG;

	VariantClear(&m_lVariant);
	VariantInit(&m_lVariant);
	if(SUCCEEDED(hr=VariantCopy(&m_lVariant, const_cast<VARIANT*>(&newVal))))
	{
		if(m_ulPropTag)
		{
			SPropValue	sPropValtmp;
			sPropValtmp.ulPropTag = m_ulPropTag;
			if(FAILED(hr=ConvertVariantToPropValue(m_lVariant,&sPropValtmp)))
				VariantClear(&m_lVariant);
			ReleasePropVal(&sPropValtmp);
		}
	}
	return hr;
}

HRESULT	CPropVal::load(LPSPropValue lpSPropVal)
{
	if(lpSPropVal)
	{
		m_ulPropTag = lpSPropVal->ulPropTag;
		return ConvertPropValueToVariant(&m_lVariant,lpSPropVal);
	}
	return E_INVALIDARG;
}

HRESULT	CPropVal::pack(LPSPropValue lpSPropVal,LPVOID lpObject)
{
	LPSPropValue	lpPropValtmp=NULL;
	HRESULT			hr=E_OUTOFMEMORY;

	if(lpPropValtmp=new SPropValue)
	{
		lpPropValtmp->ulPropTag = m_ulPropTag;
		lpPropValtmp->dwAlignPad= 0;
		if(SUCCEEDED(hr=ConvertVariantToPropValue(m_lVariant,lpPropValtmp)))
		{
			if(SUCCEEDED(hr=CopyPropVal(lpSPropVal,lpPropValtmp,lpObject)))
				ReleasePropVal(lpPropValtmp);
		}
		delete lpPropValtmp;
	}
	return hr;
}
