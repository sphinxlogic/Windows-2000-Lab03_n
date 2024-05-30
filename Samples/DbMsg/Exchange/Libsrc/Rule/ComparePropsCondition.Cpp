// ----------------------------------------------------------------------------
//	ComparePropsCondition.cpp : Implementation of CComparePropsCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "BaseCondition.h"
#include "ComparePropsCondition.h"

// CComparePropsCondition
CComparePropsCondition::CComparePropsCondition() :
	m_lPropTag1(0),
	m_lPropTag2(0),
	m_relOperator(REL_EQ)

{
}

STDMETHODIMP CComparePropsCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IComparePropsCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CComparePropsCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_COMPAREPROPS;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CComparePropsCondition::get_Operator(RELOP_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_relOperator;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CComparePropsCondition::put_Operator(RELOP_TYPES newVal)
{
	m_relOperator = newVal;
	return NOERROR;
}

STDMETHODIMP CComparePropsCondition::get_PropertyTag1(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lPropTag1;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CComparePropsCondition::put_PropertyTag1(long newVal)
{
	m_lPropTag1 = newVal;
	return NOERROR;
}

STDMETHODIMP CComparePropsCondition::get_PropertyTag2(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lPropTag2;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CComparePropsCondition::put_PropertyTag2(long newVal)
{
	m_lPropTag2 = newVal;
	return NOERROR;
}

HRESULT	CComparePropsCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		if(RES_COMPAREPROPS==lpRes->rt)
		{
			SComparePropsRestriction	*pCompPropsRes=&lpRes->res.resCompareProps;
			switch( pCompPropsRes->relop)
			{
				case RELOP_GE:	m_relOperator = REL_GE;break;
				case RELOP_GT:	m_relOperator = REL_GT;break;
				case RELOP_LE:	m_relOperator = REL_LE;break;
				case RELOP_LT:	m_relOperator = REL_LT;break;
				case RELOP_NE:	m_relOperator = REL_NE;break;
				case RELOP_RE:	m_relOperator = REL_RE;break;
				case RELOP_EQ:	m_relOperator = REL_EQ;break;
			}
			m_lPropTag1 = pCompPropsRes->ulPropTag1;
			m_lPropTag2 = pCompPropsRes->ulPropTag2;
			hr=NOERROR;
		}
	}
	return hr;
}

HRESULT	CComparePropsCondition::pack(LPSRestriction lpRes,LPVOID)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt = RES_COMPAREPROPS;
		switch( m_relOperator )
		{
			case REL_GE:	lpRes->res.resCompareProps.relop = RELOP_GE;break;
			case REL_GT:	lpRes->res.resCompareProps.relop = RELOP_GT;break;	
			case REL_LE:	lpRes->res.resCompareProps.relop = RELOP_LE;break;
			case REL_LT:	lpRes->res.resCompareProps.relop = RELOP_LT;break;
			case REL_NE:	lpRes->res.resCompareProps.relop = RELOP_NE;break;
			case REL_RE:	lpRes->res.resCompareProps.relop = RELOP_RE;break;
			case REL_EQ:	lpRes->res.resCompareProps.relop = RELOP_EQ;break;
		}
		lpRes->res.resCompareProps.ulPropTag1 = (ULONG)m_lPropTag1;
		lpRes->res.resCompareProps.ulPropTag2 = (ULONG)m_lPropTag2;
		hr=NOERROR;
	}
	return hr;
}
