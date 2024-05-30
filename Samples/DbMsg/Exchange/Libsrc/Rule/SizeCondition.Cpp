// ----------------------------------------------------------------------------
//	SizeCondition.cpp : Implementation of CSizeCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "BaseCondition.h"
#include "SizeCondition.h"

// CSizeCondition
STDMETHODIMP CSizeCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISizeCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CSizeCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_SIZE;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSizeCondition::get_Operator(RELOP_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_relOperator;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSizeCondition::put_Operator(RELOP_TYPES newVal)
{
	m_relOperator = newVal;
	return NOERROR;
}

STDMETHODIMP CSizeCondition::get_PropertyTag(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lPropTag;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSizeCondition::put_PropertyTag(long newVal)
{
	if( newVal < 0 )
		return E_INVALIDARG;
	m_lPropTag = newVal;
	return NOERROR;
}

STDMETHODIMP CSizeCondition::get_Size(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lSize;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSizeCondition::put_Size(long newVal)
{
	m_lSize = newVal;
	return S_OK;
}

HRESULT	CSizeCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		if(RES_SIZE==lpRes->rt)
		{
			SSizeRestriction	*pSizeRes=&lpRes->res.resSize;
			switch(pSizeRes->relop)
			{
			case RELOP_GE:	m_relOperator = REL_GE;break;
			case RELOP_GT:	m_relOperator = REL_GT;break;
			case RELOP_LE:	m_relOperator = REL_LE;break;
			case RELOP_LT:	m_relOperator = REL_LT;break;
			case RELOP_NE:	m_relOperator = REL_NE;break;
			case RELOP_RE:	m_relOperator = REL_RE;break;
			case RELOP_EQ:	m_relOperator = REL_EQ;break;
			}
			m_lPropTag = pSizeRes->ulPropTag;
			m_lSize = pSizeRes->cb;
			hr = NOERROR;
		}
	}
	return hr;
}

HRESULT	CSizeCondition::pack(LPSRestriction lpRes,LPVOID)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt = RES_SIZE;
		switch( m_relOperator )
		{
		case REL_GE:	lpRes->res.resSize.relop = RELOP_GE;break;
		case REL_GT:	lpRes->res.resSize.relop = RELOP_GT;break;
		case REL_LE:	lpRes->res.resSize.relop = RELOP_LE;break;
		case REL_LT:	lpRes->res.resSize.relop = RELOP_LT;break;
		case REL_NE:	lpRes->res.resSize.relop = RELOP_NE;break;
		case REL_RE:	lpRes->res.resSize.relop = RELOP_RE;break;
		case REL_EQ:	lpRes->res.resSize.relop = RELOP_EQ;break;
		}
		lpRes->res.resSize.ulPropTag = m_lPropTag;
		lpRes->res.resSize.cb = m_lSize;
		hr = NOERROR;
	}
	return hr;
}
