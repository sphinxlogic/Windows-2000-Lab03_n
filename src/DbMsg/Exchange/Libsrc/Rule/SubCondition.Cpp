// ----------------------------------------------------------------------------
//	SubCondition.cpp : Implementation of CSubCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "BaseCondition.h"
#include "SubCondition.h"
#include "util.h"

#pragma warning ( disable:4541 )

// CSubCondition
CSubCondition::CSubCondition() :
	m_subObjType(MSG_RECIP),
	m_pConditionPtr(NULL)
{
}

CSubCondition::~CSubCondition()
{
	cleanup();
}

void CSubCondition::cleanup()
{
	if(m_pConditionPtr)
	{
		delete m_pConditionPtr;
		m_pConditionPtr = NULL;
	}
}

//	ICondition interface implementation
STDMETHODIMP CSubCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_SUB;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSubCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISubCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSubCondition::get_Operator(SUBOBJECT_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_subObjType;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSubCondition::put_Operator(SUBOBJECT_TYPES newVal)
{
	m_subObjType = newVal;
	return NOERROR;
}

STDMETHODIMP CSubCondition::get_Condition(LPDISPATCH *pVal)
{
	if(pVal)
	{
		if( m_pConditionPtr)
			return (*m_pConditionPtr)->QueryInterface(IID_IDispatch,(LPVOID*)pVal);
		return E_FAIL;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CSubCondition::put_Condition(LPDISPATCH newVal)
{
	HRESULT	hr=E_INVALIDARG;

	if(newVal)
	{
		LPCONDITION		lpCondition;
		if(SUCCEEDED(hr=newVal->QueryInterface(IID_ICondition,(LPVOID*)&lpCondition)))
		{
			cleanup();
			if(m_pConditionPtr=new CConditionPtr(lpCondition))
				hr = NOERROR;
			lpCondition->Release();
		}
	}
	return hr;
}

HRESULT	CSubCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		SSubRestriction	*pSubRes=&lpRes->res.resSub;

		switch(pSubRes->ulSubObject)
		{
		case PR_MESSAGE_RECIPIENTS:		m_subObjType = MSG_RECIP;break;
		case PR_MESSAGE_ATTACHMENTS:	m_subObjType = MSG_ATTCH;break;
		}

		LPCONDITION	lpCondition;
		if(SUCCEEDED(hr=_Module.CreateResInstance(pSubRes->lpRes->rt,(LPVOID*)&lpCondition)))
		{
			cleanup();
			if(m_pConditionPtr=new CConditionPtr(lpCondition))
			{
				CBaseCondition	*pCondition=NULL;
				if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
				{
					hr = pCondition->load(pSubRes->lpRes);
				}
			}
			else
				hr=E_OUTOFMEMORY;
		}
	}
	return hr;
}

HRESULT	CSubCondition::pack(LPSRestriction lpRes, LPVOID lpObject)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt = RES_SUBRESTRICTION;
		switch(m_subObjType)
		{
		case MSG_RECIP:	lpRes->res.resSub.ulSubObject = PR_MESSAGE_RECIPIENTS;break;
		case MSG_ATTCH:	lpRes->res.resSub.ulSubObject = PR_MESSAGE_ATTACHMENTS;break;
		}

		if(m_pConditionPtr)
		{
			LPCONDITION		lpCondition = (*m_pConditionPtr);
			CBaseCondition	*pCondition = NULL;
	
			if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
			{
				if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SRestriction),lpObject,
											 (LPVOID*)&lpRes->res.resSub.lpRes)))
					hr = pCondition->pack(lpRes->res.resSub.lpRes,lpObject);
			}
		}
	}
	return hr;
}
