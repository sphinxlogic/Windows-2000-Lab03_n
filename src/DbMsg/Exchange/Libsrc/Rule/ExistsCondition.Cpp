// ----------------------------------------------------------------------------
//	ExistsCondition.cpp : Implementation of CExistsCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "BaseCondition.h"
#include "ExistsCondition.h"

// CExistsCondition
STDMETHODIMP CExistsCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IExistsCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CExistsCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_EXISTS;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CExistsCondition::get_PropertyTag(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lPropTag;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CExistsCondition::put_PropertyTag(long newVal)
{
	m_lPropTag = newVal;
	return NOERROR;
}

HRESULT	CExistsCondition::load(LPSRestriction lpRes)
{
	if(lpRes)
	{
		if(RES_EXIST==lpRes->rt)
		{
			m_lPropTag = lpRes->res.resExist.ulPropTag;
			return NOERROR;
		}
	}
	return E_INVALIDARG;
}

HRESULT	CExistsCondition::pack(LPSRestriction lpRes,LPVOID)
{
	if(lpRes)
	{
		lpRes->rt = RES_EXIST;
		lpRes->res.resExist.ulReserved1 = 0;
		lpRes->res.resExist.ulPropTag = m_lPropTag;
		return NOERROR;
	}
	return E_INVALIDARG;
}

