// ----------------------------------------------------------------------------
//	PropertyCondition.cpp : Implementation of CPropertyCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "PropVal.h"
#include "BaseCondition.h"
#include "PropertyCondition.h"
#include "util.h"

#pragma warning ( disable:4541 )

// CPropertyCondition
CPropertyCondition::CPropertyCondition() :
	m_pPropValPtr(NULL),
	m_lPropTag(0),
	m_relOperator(REL_EQ)

{
}

CPropertyCondition::~CPropertyCondition()
{
	if(m_pPropValPtr)
		delete m_pPropValPtr;
}

STDMETHODIMP CPropertyCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPropertyCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CPropertyCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_PROPERTY;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CPropertyCondition::get_Operator(RELOP_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_relOperator;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CPropertyCondition::put_Operator(RELOP_TYPES newVal)
{
	m_relOperator = newVal;
	return NOERROR;
}

STDMETHODIMP CPropertyCondition::get_PropertyTag(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lPropTag;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CPropertyCondition::put_PropertyTag(long newVal)
{
	HRESULT		hr=E_INVALIDARG;

	if(m_pPropValPtr)
	{
		LPPROPVAL	lpPropVal=*m_pPropValPtr;
		CPropVal	*pPropVal=NULL;
		
		if(pPropVal= dynamic_cast<CPropVal*>(lpPropVal))
		{
			long	lPropTag;
			if(SUCCEEDED(hr=pPropVal->get_Tag(&lPropTag)))
			{
				if(PROP_TYPE(lPropTag)!=PROP_TYPE(newVal))
					hr = E_INVALIDARG;
				else
				{
					m_lPropTag = newVal;
					hr = NOERROR;
				}
			}
		}
	}
	else
	{
		m_lPropTag = newVal;
		hr = NOERROR;
	}
	return hr;
}

STDMETHODIMP CPropertyCondition::get_Value(LPDISPATCH *pVal)
{
	if(pVal)
		return (*m_pPropValPtr)->QueryInterface(IID_IDispatch,(LPVOID*)pVal);
	return E_INVALIDARG;
}

STDMETHODIMP CPropertyCondition::put_Value(LPDISPATCH newVal)
{
	LPPROPVAL	lpPropVal=NULL;
	HRESULT		hr=E_INVALIDARG;

	if(newVal)
	{
		if(SUCCEEDED(hr=newVal->QueryInterface(IID_IPropVal,(LPVOID*)&lpPropVal)))
		{
			if(m_pPropValPtr)
			{
				delete m_pPropValPtr;
				m_pPropValPtr = NULL;
			}
			if(m_pPropValPtr=new CPropValPtr(lpPropVal))
			{
				CPropVal	*pPropVal;
				if(pPropVal= dynamic_cast<CPropVal*>(lpPropVal))
				{
					long	lPropTag;
					if(SUCCEEDED(hr=pPropVal->get_Tag(&lPropTag)))
					{
						if(m_lPropTag)
						{
							if(PROP_TYPE(m_lPropTag)!=PROP_TYPE(lPropTag))
							{
								hr = E_FAIL;
								delete m_pPropValPtr;
								m_pPropValPtr = NULL;
							}
							else
								hr = NOERROR;
						}
					}
				}
			}
			else
				hr=E_OUTOFMEMORY;
			lpPropVal->Release();
		}
	}
	return hr;
}

HRESULT	CPropertyCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		if(RES_PROPERTY==lpRes->rt)
		{
			SPropertyRestriction	*pPropRes=&lpRes->res.resProperty;

			switch(pPropRes->relop)
			{
				case RELOP_GE:	m_relOperator = REL_GE;break;
				case RELOP_GT:	m_relOperator = REL_GT;break;
				case RELOP_LE:	m_relOperator = REL_LE;break;
				case RELOP_LT:	m_relOperator = REL_LT;break;
				case RELOP_NE:	m_relOperator = REL_NE;break;
				case RELOP_RE:	m_relOperator = REL_RE;break;
				case RELOP_EQ:	m_relOperator = REL_EQ;break;
			}
			m_lPropTag = pPropRes->ulPropTag;

			CPropValObject	*pPropValOb=NULL;
			if(SUCCEEDED(hr=CPropValObject::CreateInstance(&pPropValOb)))
			{
				if(SUCCEEDED(hr=pPropValOb->load(pPropRes->lpProp)))
				{
					if(m_pPropValPtr)
					{
						delete m_pPropValPtr;
						m_pPropValPtr = NULL;
					}
					if(m_pPropValPtr=new CPropValPtr(pPropValOb))
						hr=NOERROR;
					else
						hr=E_OUTOFMEMORY;
				}
			}
		}
	}
	return hr;
}

HRESULT	CPropertyCondition::pack(LPSRestriction lpRes,LPVOID lpObject)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt = RES_PROPERTY;
		switch( m_relOperator )
		{
		case REL_GE:	lpRes->res.resProperty.relop = RELOP_GE;break;
		case REL_GT:	lpRes->res.resProperty.relop = RELOP_GT;break;
		case REL_LE:	lpRes->res.resProperty.relop = RELOP_LE;break;
		case REL_LT:	lpRes->res.resProperty.relop = RELOP_LT;break;
		case REL_NE:	lpRes->res.resProperty.relop = RELOP_NE;break;
		case REL_RE:	lpRes->res.resProperty.relop = RELOP_RE;break;
		case REL_EQ:	lpRes->res.resProperty.relop = RELOP_EQ;break;
		}

		lpRes->res.resProperty.ulPropTag = m_lPropTag;
		if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SPropValue),lpObject,
										 (LPVOID*)&lpRes->res.resProperty.lpProp)))
		{
			if(m_pPropValPtr)
			{
				LPPROPVAL	lpPropVal = (*m_pPropValPtr);
				CPropVal	*pPropVal = NULL;
				if(pPropVal= dynamic_cast<CPropVal*>(lpPropVal))
				{
					long	lPropTag;
					if(SUCCEEDED(hr=pPropVal->get_Tag(&lPropTag)))
					{
						if(m_lPropTag)
						{
							if(PROP_TYPE(m_lPropTag)!=PROP_TYPE(lPropTag))
							{
								hr = E_FAIL;
								delete m_pPropValPtr;
								m_pPropValPtr = NULL;
							}
							else
								hr = NOERROR;
						}
					}
					if(SUCCEEDED(hr))
						hr = pPropVal->pack(lpRes->res.resProperty.lpProp,lpObject);
				}
			}
			else
				hr = E_INVALIDARG;
		}
	}
	return hr;
}
