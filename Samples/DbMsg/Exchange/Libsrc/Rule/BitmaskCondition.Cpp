// ----------------------------------------------------------------------------
//	BitmaskCondition.cpp : Implementation of CBitmaskCondition
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "BaseCondition.h"
#include "BitmaskCondition.h"

//	CBitmaskCondition
CBitmaskCondition::CBitmaskCondition(): 
	m_lValue(0),
	m_bmpOp(B_EQZ),
	m_lPropTag(0)
{
}

//	ISupportsErrorInfo interface implementation
STDMETHODIMP CBitmaskCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBitmaskCondition,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CBitmaskCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_BITMASK;
		return NOERROR;
	}
	return E_INVALIDARG;
}

//	IBitmaskCondtion interface implementation
STDMETHODIMP CBitmaskCondition::get_Operator(BITMAPOP_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_bmpOp;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CBitmaskCondition::put_Operator(BITMAPOP_TYPES newVal)
{
	m_bmpOp = newVal;
	return NOERROR;
}

STDMETHODIMP CBitmaskCondition::get_PropertyTag(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lPropTag;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CBitmaskCondition::put_PropertyTag(long newVal)
{
	m_lPropTag = newVal;
	return NOERROR;
}

STDMETHODIMP CBitmaskCondition::get_Value(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lValue;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CBitmaskCondition::put_Value(long newVal)
{
	if(newVal<0)
		return E_INVALIDARG;
	m_lValue = newVal;
	return S_OK;
}

//	Load internal data from LPSRestriction structure
HRESULT	CBitmaskCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		//	verify if we are loading the proper Restriction structure
		if(RES_BITMASK==lpRes->rt)
		{
			SBitMaskRestriction	*pBitmaskRes=&lpRes->res.resBitMask;
			if(pBitmaskRes)
			{
				m_bmpOp		= pBitmaskRes->relBMR==BMR_EQZ? B_EQZ:B_NEZ;
				m_lPropTag	=(long)pBitmaskRes->ulPropTag;
				m_lValue	=(long)pBitmaskRes->ulMask;
				hr = NOERROR;
			}
		}
	}
	return hr;
}

//	write back state into a LPSRestriction structure
HRESULT	CBitmaskCondition::pack(LPSRestriction lpRes,LPVOID)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt=RES_BITMASK;
		lpRes->res.resBitMask.relBMR	= m_bmpOp==B_EQZ? BMR_EQZ:BMR_NEZ;
		lpRes->res.resBitMask.ulPropTag =(ULONG)m_lPropTag;
		lpRes->res.resBitMask.ulMask	=(ULONG)m_lValue;
		hr=NOERROR;
	}
	return hr;
}
