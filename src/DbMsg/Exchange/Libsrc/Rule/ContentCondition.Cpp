// ----------------------------------------------------------------------------
//	ContentCondition.cpp : Implementation of CContentCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "PropVal.h"
#include "BaseCondition.h"
#include "ContentCondition.h"
#include "util.h"

#pragma warning ( disable:4541 )

// CContentCondition
CContentCondition::CContentCondition() : 
		m_pPropValPtr(NULL), 
		m_lPropType(0),
		m_fuzzyTypeOp(LOOSE)

{
}

CContentCondition::~CContentCondition()
{
	cleanup();
}

void CContentCondition::cleanup()
{
	if(m_pPropValPtr)
		delete m_pPropValPtr;
	m_pPropValPtr = NULL;
}

STDMETHODIMP CContentCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IContentCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CContentCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_CONTENT;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CContentCondition::get_Operator(FUZZYLEVEL_TYPES *pVal)
{
	if(pVal)
	{
		*((ULONG*)pVal) = m_fuzzyTypeOp;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CContentCondition::put_Operator(FUZZYLEVEL_TYPES newVal)
{
	m_fuzzyTypeOp = newVal;
	return NOERROR;
}

STDMETHODIMP CContentCondition::get_PropertyType(long *pVal)
{
	if(pVal)
	{
		*pVal  = m_lPropType;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CContentCondition::put_PropertyType(long newVal)
{
	m_lPropType = newVal;
	return NOERROR;
}

STDMETHODIMP CContentCondition::get_Value(LPDISPATCH *pVal)
{
	if(pVal)
		return (*m_pPropValPtr)->QueryInterface( IID_IDispatch,(LPVOID*)pVal);
	return E_INVALIDARG;
}

STDMETHODIMP CContentCondition::put_Value(LPDISPATCH newVal)
{
	LPPROPVAL	lpPropVal=NULL;
	HRESULT		hr=E_INVALIDARG;

	if(newVal)
	{
		if(SUCCEEDED(hr=newVal->QueryInterface(IID_IPropVal,(LPVOID*)&lpPropVal)))
		{
			if(m_pPropValPtr=new CPropValPtr(lpPropVal))
				hr=NOERROR;
			else
				hr=E_OUTOFMEMORY;
			lpPropVal->Release();
		}
	}
	return hr;
}

HRESULT	CContentCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		if(RES_CONTENT==lpRes->rt)
		{
			SContentRestriction	*pContentRes=&lpRes->res.resContent;
			m_fuzzyTypeOp = pContentRes->ulFuzzyLevel;
			m_lPropType = pContentRes->ulPropTag;
		
			if(m_pPropValPtr)
				delete m_pPropValPtr;

			CPropValObject	*pPropValOb;
			if(SUCCEEDED(hr=CPropValObject::CreateInstance(&pPropValOb)))
			{
				if(SUCCEEDED(hr=pPropValOb->load(pContentRes->lpProp)))
				{
					if(m_pPropValPtr = new CPropValPtr(pPropValOb))
						hr = NOERROR;
					else
						hr = E_OUTOFMEMORY;
				}
			}
		}
	}
	return hr;
}

HRESULT	CContentCondition::pack(LPSRestriction lpRes,LPVOID lpObject)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt = RES_CONTENT;
		lpRes->res.resContent.ulFuzzyLevel = m_fuzzyTypeOp;
		lpRes->res.resContent.ulPropTag = m_lPropType;

		if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SPropValue),lpObject, 
								(LPVOID*)&lpRes->res.resContent.lpProp)))
		{
			LPPROPVAL	lpPropVal;
			if(m_pPropValPtr)
			{
				if(lpPropVal=(*m_pPropValPtr))
				{
					CPropVal	*pPropVal;
					if(pPropVal=dynamic_cast<CPropVal*>(lpPropVal))
						hr = pPropVal->pack(lpRes->res.resContent.lpProp,lpObject);
				}
			}
		}
	}
	return hr;
}
