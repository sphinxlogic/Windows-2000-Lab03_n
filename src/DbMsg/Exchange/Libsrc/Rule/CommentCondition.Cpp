// ----------------------------------------------------------------------------
//	CommentCondition.cpp : Implementation of CCommentCondition
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "BaseCondition.h"
#include "PropVal.h"
#include "CommentCondition.h"
#include "util.h"

#pragma warning(disable:4541)

// CCommentCondition
CCommentCondition::CCommentCondition():
	m_propValsCollection(),
	m_pConditionPtr(NULL)
{
}

CCommentCondition::~CCommentCondition()
{
	cleanup();
}

//	ISupportsErrorInfo interface implementation
STDMETHODIMP CCommentCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID *arr[] = 
	{
		&IID_ICommentCondition,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CCommentCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_COMMENT;
		return NOERROR;
	}
	return E_INVALIDARG;
}

//	ICommentCondition interface implementation
STDMETHODIMP CCommentCondition::get_Count(long *pVal)
{
	if(pVal)
	{
		*pVal = m_propValsCollection.size();
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CCommentCondition::get__NewEnum(LPUNKNOWN *pVal)
{
	long				lCount=0;
	HRESULT				hr=NOERROR;
	VARIANT				*varArray=NULL;
	CPropValPtr			*pPropValPtr=NULL;
	CPropValsEnumVar	*pPropValsEnum=NULL;
	CPropValsIterator	propValIter;
	
	if(pVal)
	{
		if(pPropValsEnum=new CPropValsEnumVar)
		{
			if(varArray=new VARIANT[m_propValsCollection.size()])
			{
				for(propValIter=m_propValsCollection.begin(); 
					propValIter!=m_propValsCollection.end(); 
					propValIter++,lCount++)
				{
					if(pPropValPtr=*propValIter)
					{
						VariantInit(&varArray[lCount]);
						varArray[lCount].vt = VT_DISPATCH;
						if(SUCCEEDED(hr=(*pPropValPtr)->QueryInterface(IID_IDispatch,
										(LPVOID*)&(varArray[lCount].pdispVal))))
							continue;
						else
							break;
					}
					else
					{
						hr = E_FAIL;
						break;
					}
				}
				if(SUCCEEDED(hr))
				{
					if(SUCCEEDED(hr=pPropValsEnum->Init(&varArray[0],&varArray[lCount],NULL,AtlFlagTakeOwnership)))
						hr = pPropValsEnum->QueryInterface(IID_IUnknown,(LPVOID FAR*)pVal);
				}
			}
			else
				hr=E_OUTOFMEMORY;
		}
		else
			hr = E_OUTOFMEMORY;
	}
	else
		hr = E_INVALIDARG;
	return hr;
}

STDMETHODIMP CCommentCondition::Item(VARIANT index, LPDISPATCH *ppDispCondition)
{
	long				lIndex=-1;
	long				lCount=1;
	HRESULT				hr=E_INVALIDARG;
	CPropValPtr			*pPropValPtr=NULL;
	CPropValsIterator	propValIter;

	if(ppDispCondition)
	{
		CComVariant		varIndex(index);
		if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
		{
			if(SUCCEEDED(hr=varIndex.Detach(&index)))
			{
				lIndex = index.lVal;
				if((lIndex>0)&&(lIndex<=m_propValsCollection.size()))
				{
					for(propValIter=m_propValsCollection.begin(); 
						propValIter!=m_propValsCollection.end(); 
						propValIter++,lCount++)
					{
						hr = E_FAIL;
						if(lIndex==lCount)
						{
							if(pPropValPtr = *propValIter)
							{
								hr =(*pPropValPtr)->QueryInterface(IID_IDispatch,(LPVOID*)ppDispCondition);
								break;
							}
						}
					}
				}
				else
					hr = E_INVALIDARG;
			}
		}
	}
	return hr;
}

STDMETHODIMP CCommentCondition::get_Condition(LPDISPATCH *ppDispCondition)
{
	HRESULT	hr=E_INVALIDARG;

	if(m_pConditionPtr)
		if(ppDispCondition)
			hr =(*m_pConditionPtr)->QueryInterface(IID_IDispatch,(LPVOID*)ppDispCondition);
	return hr;
}

STDMETHODIMP CCommentCondition::put_Condition(LPDISPATCH lpDispatch)
{
	HRESULT	hr=E_INVALIDARG;
	
	if(lpDispatch)
	{
		if(m_pConditionPtr)
			delete m_pConditionPtr;

		LPCONDITION		lpCond;
		if(SUCCEEDED(hr=lpDispatch->QueryInterface(IID_ICondition,(LPVOID*)&lpCond)))
		{
			if(m_pConditionPtr=new CConditionPtr(lpCond))
				hr = NOERROR;
			else
				hr = E_OUTOFMEMORY;
			lpCond->Release();
		}
	}
	return hr;
}

STDMETHODIMP CCommentCondition::Add(LPDISPATCH pValue)
{
	HRESULT	hr=NOERROR;

	if(pValue)
	{
		LPPROPVAL	lpPropVal;

		if(SUCCEEDED(hr=pValue->QueryInterface(IID_IPropVal,(LPVOID*)&lpPropVal)))
		{
			CPropValPtr	*pPropValPtr;
			if(pPropValPtr=new CPropValPtr(lpPropVal))
				m_propValsCollection.insert(m_propValsCollection.end(),pPropValPtr);
			else
				hr=E_OUTOFMEMORY;
			lpPropVal->Release();
		}
	}
	else
		hr = E_INVALIDARG;
	return hr;
}

STDMETHODIMP CCommentCondition::Delete(VARIANT index)
{
	long		lIndex=0;
	HRESULT		hr=E_INVALIDARG;
	CComVariant	varIndex(index);
	
	if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
	{
		if(SUCCEEDED(hr=varIndex.Detach(&index)))
		{
			lIndex = index.lVal;
			if(lIndex>0&&lIndex<=m_propValsCollection.size())
			{
				CPropValsIterator	propValIter;
				CPropValPtr			*pPropValPtr;
				long				lCount=1;

				for(propValIter=m_propValsCollection.begin(); 
					propValIter!=m_propValsCollection.end(); 
					propValIter++,lCount++)
				{
					hr = E_FAIL;
					if(lIndex==lCount)
					{
						if(pPropValPtr = *propValIter)
						{
							m_propValsCollection.erase(propValIter);
							hr = NOERROR;
							delete pPropValPtr;
							break;
						}
					}
				}
			}
			else
				hr = E_INVALIDARG;
		}
	}
	return hr;
}

void CCommentCondition::cleanup()
{
	if(m_pConditionPtr)
	{
		delete m_pConditionPtr;
		m_pConditionPtr = NULL;
	}
	Clear();
}

HRESULT	CCommentCondition::load(LPSRestriction lpRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		if(RES_COMMENT==lpRes->rt)
		{
			LPCONDITION	lpCondition;
			CBaseCondition		*pCondition;
			SCommentRestriction	*pCommentRes=&lpRes->res.resComment;

			if(pCommentRes->lpRes)
			{
				if(SUCCEEDED(hr=_Module.CreateResInstance(pCommentRes->lpRes->rt,(LPVOID*)&lpCondition)))
				{
					if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
					{
						if(SUCCEEDED(hr=pCondition->load(pCommentRes->lpRes)))
						{
							if(m_pConditionPtr=new CConditionPtr(lpCondition))
							{
								CPropValObject	*pPropValOb;
								CPropValPtr		*pPropValPtr;
								ULONG			lVal;

								for(lVal=0;lVal<pCommentRes->cValues;lVal++)
								{
									if(SUCCEEDED(hr=CPropValObject::CreateInstance(&pPropValOb)))
									{
										if(SUCCEEDED(hr=pPropValOb->load(&pCommentRes->lpProp[lVal])))
										{
											if(pPropValPtr=new CPropValPtr(pPropValOb))
												m_propValsCollection.insert(m_propValsCollection.end(),
														pPropValPtr);
											else
											{
												hr=E_OUTOFMEMORY;
												break;
											}
										}
										else
											break;
									}
									else
										break;
								}
							}
							else
								hr=E_OUTOFMEMORY;
						}
					}
				}
			}
		}
	}
	return hr;
}

HRESULT	CCommentCondition::pack(LPSRestriction lpRes,LPVOID lpObject)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		lpRes->rt = RES_COMMENT;
		lpRes->res.resComment.cValues	= m_propValsCollection.size();
		lpRes->res.resComment.lpRes		= NULL;
		lpRes->res.resComment.lpProp	= NULL;

		if(m_pConditionPtr)
		{
			if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SRestriction),lpObject, 
											 (LPVOID *)&lpRes->res.resComment.lpRes)))
			{
				LPCONDITION	lpCondition;
				if(lpCondition=(*m_pConditionPtr))
				{
					CBaseCondition *pCondition;
					if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
					{		
						if(SUCCEEDED(hr=pCondition->pack(lpRes->res.resComment.lpRes,
										lpObject)))
						{
							if(lpRes->res.resComment.cValues)
							{
								if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SPropValue)*lpRes->res.resComment.cValues,
																 lpObject,(LPVOID*)&lpRes->res.resComment.lpProp)))
								{
									CPropValsIterator	propValIter;
									CPropValPtr			*pPropValPtr;
									LPPROPVAL			lpPropVal;
									CPropVal			*pPropVal;
									long				lVal=0;
								
									for(propValIter =  m_propValsCollection.begin(); 
										propValIter != m_propValsCollection.end(); 
										propValIter ++,lVal++)
									{
										if(pPropValPtr=*propValIter)
										{
											if(lpPropVal=*pPropValPtr)
											{
												if(pPropVal=dynamic_cast<CPropVal*>(lpPropVal))
												{
													if(SUCCEEDED(hr=pPropVal->pack(
														&lpRes->res.resComment.lpProp[lVal],
														lpObject)))
														continue;
													else
														break;
												}
												else
													break;
											}
											else
												hr=E_FAIL;
										}
										else
											hr=E_FAIL;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return hr;
}

STDMETHODIMP CCommentCondition::Clear()
{
	HRESULT				hr=NOERROR;
	CPropValPtr			*pPropValPtr=NULL;
	CPropValsIterator	propValIter;

	for(propValIter=m_propValsCollection.begin(); 
		propValIter!=m_propValsCollection.end(); 
		propValIter++)
	{
		if(pPropValPtr=*propValIter)
			delete pPropValPtr;
		else
		{
			hr = E_FAIL;
			break;
		}
	}
	if(SUCCEEDED(hr))
		m_propValsCollection.clear();
	return hr;
}
