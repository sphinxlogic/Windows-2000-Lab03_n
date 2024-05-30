// ----------------------------------------------------------------------------
//	LogicalCondition.cpp : Implementation of CLogicalCondition
//
//	Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "BaseCondition.h"
#include "LogicalCondition.h"
#include "util.h"

#pragma warning ( disable:4541 )

// CLogicalCondition
CLogicalCondition::CLogicalCondition() :
	m_logicalOperator(L_AND),
	m_conditionsCollection()
{
}

CLogicalCondition::~CLogicalCondition()
{
	cleanup();
}

STDMETHODIMP CLogicalCondition::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILogicalCondition,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//	ICondition interface implementation
STDMETHODIMP CLogicalCondition::get_Type(CONDITION_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = R_LOGICAL;
		return NOERROR;
	}
	return E_INVALIDARG;
}

void CLogicalCondition::cleanup()
{
	CConditionPtr		*pConditionPtr=NULL;
	CConditionsIterator	conditionsIter;
	
	for ( conditionsIter = m_conditionsCollection.begin(); 
		  conditionsIter != m_conditionsCollection.end(); 
		  conditionsIter++ )
	{
		pConditionPtr = *conditionsIter;
		delete pConditionPtr;
	}
	m_conditionsCollection.clear();
}

STDMETHODIMP CLogicalCondition::get_Operator(LOGICALOP_TYPES *pVal)
{
	if(pVal)
	{
		*pVal = m_logicalOperator;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CLogicalCondition::put_Operator(LOGICALOP_TYPES newVal)
{
	m_logicalOperator = newVal;
	return NOERROR;
}

STDMETHODIMP CLogicalCondition::get_Count(long *pVal)
{
	if(pVal)
	{
		*pVal = m_conditionsCollection.size();
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CLogicalCondition::get__NewEnum(LPUNKNOWN *pVal)
{
	long				lCount=0;
	VARIANT				*varArray=NULL;
	HRESULT				hr=NOERROR;
	CConditionPtr		*pConditionPtr=NULL;
	CConditionsEnumVar	*pConditonsEnum=NULL;
	CConditionsIterator	conditionsIter;
	
	if(pVal)
	{
		if(pConditonsEnum=new CConditionsEnumVar)
		{
			if(varArray=new VARIANT[m_conditionsCollection.size()])
			{
				for(conditionsIter=m_conditionsCollection.begin(); 
					conditionsIter!=m_conditionsCollection.end(); 
					conditionsIter++, lCount++ )
				{
					if(pConditionPtr = *conditionsIter)
					{
						VariantInit( &varArray[lCount] );
						varArray[lCount].vt = VT_DISPATCH;
						if(SUCCEEDED(hr=(*pConditionPtr)->QueryInterface( IID_IDispatch, 
										(LPVOID*)&(varArray[lCount].pdispVal))))
							continue;
						else
							break;
					}
				}
				if(SUCCEEDED(hr))
				{
					if(SUCCEEDED(hr=pConditonsEnum->Init(&varArray[0],&varArray[lCount],NULL,AtlFlagTakeOwnership)))
						hr = pConditonsEnum->QueryInterface(IID_IUnknown,(LPVOID*)pVal);
				}
			}
			else
				hr=E_OUTOFMEMORY;
		}
		else
			hr = E_OUTOFMEMORY;
	}
	else
		hr=E_INVALIDARG;

	if(FAILED(hr))
		if(pConditonsEnum)
			delete pConditonsEnum;
	return hr;
}

STDMETHODIMP CLogicalCondition::Add(LPDISPATCH lpItem)
{
	long				lIndex=m_conditionsCollection.size();
	HRESULT				hr=E_INVALIDARG;
	LPCONDITION			lpCondition=NULL;
	CConditionPtr		*pConditionPtr=NULL;

	if(lpItem)
	{
		if(SUCCEEDED(hr=lpItem->QueryInterface(IID_ICondition,(LPVOID FAR*)&lpCondition)))
		{
			if(pConditionPtr=new CConditionPtr(lpCondition))
			{
				m_conditionsCollection.insert(m_conditionsCollection.end(),pConditionPtr);
				hr = NOERROR;
			}
			else
				hr=E_OUTOFMEMORY;
			lpCondition->Release();
		}
	}
	return hr;
}

STDMETHODIMP CLogicalCondition::Delete(VARIANT index)
{
	long				lIndex;
	long				lCount=1;
	HRESULT				hr=E_INVALIDARG;
	CComVariant			varIndex(index);
	CConditionPtr		*pConditionPtr=NULL;
	CConditionsIterator	conditionsIter;
	
	if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
	{
		if(SUCCEEDED(hr=varIndex.Detach(&index)))
		{
			if(VT_I4==index.vt)
			{
				lIndex = index.lVal;
				if(lIndex>0&&lIndex<=m_conditionsCollection.size())
				{
					for(conditionsIter=m_conditionsCollection.begin(); 
						conditionsIter!=m_conditionsCollection.end(); 
						conditionsIter++, lCount++ )
					{
						hr = E_FAIL;
						if(lCount==lIndex)
						{
							if(pConditionPtr = *conditionsIter)
							{
								m_conditionsCollection.erase(conditionsIter);
								delete pConditionPtr;
								hr=NOERROR;
								break;
							}
						}
					}
				}
				else
					hr =E_INVALIDARG;
			}
		}
	}
	return hr;
}

STDMETHODIMP CLogicalCondition::Item(VARIANT index, LPDISPATCH *pItem)
{
	long				lIndex=-1;
	long				lCount=1;
	HRESULT				hr=E_INVALIDARG;
	CConditionPtr		*pConditionPtr=NULL;
	CConditionsIterator	conditionsIter;

	if(pItem)
	{
		CComVariant		varIndex(index);
		if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
		{
			if(SUCCEEDED(hr=varIndex.Detach(&index)))
			{
				lIndex = index.lVal;
				if(lIndex>0&&lIndex<=m_conditionsCollection.size())
				{
					for(conditionsIter=m_conditionsCollection.begin(); 
						conditionsIter!=m_conditionsCollection.end(); 
						conditionsIter++, lCount++ )
					{
						hr = E_FAIL;
						if(lCount==lIndex)
						{
							if(pConditionPtr = *conditionsIter)
							{
								hr = (*pConditionPtr)->QueryInterface(IID_IDispatch,(LPVOID*)pItem);
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

HRESULT	CLogicalCondition::load(LPSRestriction lpRes)
{
	HRESULT			hr=E_INVALIDARG;
	long			cRes;
	LPSRestriction	lpLogRes=NULL;

	if(lpRes)
	{
		cleanup();

		switch(lpRes->rt)
		{
		case RES_AND:	m_logicalOperator=L_AND;
						cRes = lpRes->res.resAnd.cRes;
						lpLogRes = lpRes->res.resAnd.lpRes;
						hr=NOERROR;
						break;
		case RES_OR:	m_logicalOperator=L_OR;
						cRes = lpRes->res.resOr.cRes;
						lpLogRes=lpRes->res.resOr.lpRes;
						hr=NOERROR;
						break;
		case RES_NOT:	m_logicalOperator=L_NOT;
						cRes=1;
						lpLogRes=lpRes->res.resNot.lpRes;
						hr=NOERROR;
						break;
		}
		if(SUCCEEDED(hr))
		{
			if(lpLogRes)
			{
				LPCONDITION		lpCondition;
				CConditionPtr	*pConditionPtr;
				CBaseCondition	*pCondition;
				long			lCount;

				for(lCount=0;lCount<cRes;lCount++)
				{
					if(SUCCEEDED(hr=_Module.CreateResInstance(lpLogRes[lCount].rt,(LPVOID*)&lpCondition)))
					{
						if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
						{
							if(SUCCEEDED(hr=pCondition->load(&lpLogRes[lCount])))
							{
								if(pConditionPtr = new CConditionPtr(lpCondition))
								{
									m_conditionsCollection.insert(m_conditionsCollection.end(),
													  pConditionPtr);
									continue;
								}
								else
								{
									hr = E_OUTOFMEMORY;
									break;
								}
							}
							else
								break;
						}
						else
							break;
					}
					else
						break;
				}
			}
		}
	}
	return hr;
}

HRESULT	CLogicalCondition::pack(LPSRestriction lpRes,LPVOID lpObject)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpRes)
	{
		long				lCount=0;
		LPCONDITION			lpCondition=NULL;
		CConditionPtr		*pConditionPtr=NULL;
		CBaseCondition		*pCondition=NULL;
		CConditionsIterator	conditionsIter;

		switch( m_logicalOperator )
		{
		case L_AND:
			{
				lpRes->rt = RES_AND;
				if(lpRes->res.resAnd.cRes = m_conditionsCollection.size())
				{
					if(SUCCEEDED(hr=MAPIAllocateMore(lpRes->res.resAnd.cRes*sizeof(SRestriction),
													 lpObject,(LPVOID*)&lpRes->res.resAnd.lpRes)))
					{
						for(conditionsIter = m_conditionsCollection.begin(); 
							conditionsIter != m_conditionsCollection.end(); 
							conditionsIter++, lCount++ )
						{
							if(pConditionPtr = *conditionsIter)
							{
								lpCondition	= *pConditionPtr;
								if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
								{
									if(SUCCEEDED(hr=pCondition->pack(
											&lpRes->res.resAnd.lpRes[lCount],lpObject)))
										continue;
									else
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
			}
			break;
		case L_OR:
			{
				lpRes->rt = RES_OR;
				if(lpRes->res.resOr.cRes = m_conditionsCollection.size())
				{
					if(SUCCEEDED(hr=MAPIAllocateMore(lpRes->res.resOr.cRes*sizeof(SRestriction),
													 lpObject,(LPVOID*)&lpRes->res.resOr.lpRes)))
					{
						for(conditionsIter = m_conditionsCollection.begin(); 
							conditionsIter != m_conditionsCollection.end(); 
							conditionsIter++, lCount++ )
						{
							if(pConditionPtr=*conditionsIter)
							{
								lpCondition = *pConditionPtr;
								if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
								{
									if(SUCCEEDED(hr=pCondition->pack(
											&lpRes->res.resOr.lpRes[lCount],lpObject)))
										continue;
									else
										break;
								}
								else
									break;
							}
							else
								break;
						}
					}
				}
			}
			break;

		case L_NOT:
			{
				lpRes->rt = RES_NOT;
				if(m_conditionsCollection.size())
				{
					if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SRestriction),
												 lpObject,(LPVOID*)&lpRes->res.resNot.lpRes)))
					{
						conditionsIter	= m_conditionsCollection.begin(); 
						if(pConditionPtr = *conditionsIter)
						{
							lpCondition	= (*pConditionPtr);
							if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
								hr = pCondition->pack(lpRes->res.resNot.lpRes,lpObject);
						}
					}
				}
			}
			break;
		}
	}
	return hr;
}

STDMETHODIMP CLogicalCondition::Clear()
{
	HRESULT				hr=NOERROR;
	CConditionPtr		*pConditionPtr=NULL;
	CConditionsIterator	conditionsIter;

	for(conditionsIter=m_conditionsCollection.begin(); 
		conditionsIter!=m_conditionsCollection.end(); 
		conditionsIter++)
	{
		if(pConditionPtr = *conditionsIter)
			delete pConditionPtr;
		else
		{
			hr = E_FAIL;
			break;
		}
	}
	if(SUCCEEDED(hr))
		m_conditionsCollection.clear();
	return hr;
}
