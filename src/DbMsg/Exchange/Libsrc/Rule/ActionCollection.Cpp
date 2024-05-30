// ----------------------------------------------------------------------------
//	ActionCollection.cpp : Implementation of CActions
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "PropVal.h"
#include "ActionObj.h"
#include "ActionCollection.h"
#include "util.h"

#pragma warning(disable:4541)

CActions::~CActions()
{
	cleanup();
}

void CActions::cleanup()
{
	CActionsIterator	actionIter;
	CActionPtr			*pActionPtr;
	
	for(actionIter = m_actionsCollection.begin(); actionIter != m_actionsCollection.end(); 
		actionIter++)
	{
		pActionPtr = *actionIter;
		delete pActionPtr;
	}
}

STDMETHODIMP CActions::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IActions,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CActions::get__NewEnum(LPUNKNOWN *pVal)
{
	CActionsEnumVar		*pActionsEnum=NULL;
	CActionsIterator	actionIter;
	CActionPtr			*pActionPtr=NULL;
	VARIANT				*varArray=NULL;
	HRESULT				hr=NOERROR;
	long				lCount=0;
	
	if(pVal)
	{
		if(pActionsEnum=new CActionsEnumVar)
		{
			if(varArray=new VARIANT[m_actionsCollection.size()])
			{
				for(actionIter = m_actionsCollection.begin(); actionIter != m_actionsCollection.end(); 
				    actionIter++, lCount++)
				{
					if(pActionPtr=*actionIter)
					{
						VariantInit(&varArray[lCount]);
						varArray[lCount].vt = VT_DISPATCH;
						if(SUCCEEDED(hr=(*pActionPtr)->QueryInterface(IID_IDispatch,(LPVOID*)&(varArray[lCount].pdispVal))))
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
					if(SUCCEEDED(hr=pActionsEnum->Init(&varArray[0],&varArray[lCount],NULL,AtlFlagTakeOwnership)))
						hr=pActionsEnum->QueryInterface(IID_IUnknown,(LPVOID*)pVal);
				}
			}
			else
				hr = E_OUTOFMEMORY;
		}
		else
			hr = E_OUTOFMEMORY;
	}
	else
		hr = E_INVALIDARG;

	if(FAILED(hr))
		if(pActionsEnum)
			delete pActionsEnum;
	return hr;
}

STDMETHODIMP CActions::get_Count(long * pVal)
{
	if(pVal)
	{
		*pVal = m_actionsCollection.size();
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CActions::Item(VARIANT index,LPDISPATCH *pItem)
{
	long				lIndex=0;
	HRESULT				hr=E_INVALIDARG;
	CAction				*pAction=NULL;
	LPAction			lpAction=NULL;
	CActionPtr			*pActionPtr=NULL;
	CActionsIterator	actionIter;

	if(pItem)
	{
		CComVariant		varIndex(index);
		if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
		{
			if(SUCCEEDED(hr=varIndex.Detach(&index)))
			{
				lIndex = index.lVal;
				if((lIndex>0)&&(lIndex<=m_actionsCollection.size()))
				{
					hr = E_FAIL;
					for(actionIter=m_actionsCollection.begin(); 
						actionIter!= m_actionsCollection.end(); 
						actionIter++)
					{
						if(pActionPtr=*actionIter)
						{
							lpAction	=(*pActionPtr);
							if(pAction= dynamic_cast<CAction*>(lpAction))
							{
								if(lIndex==pAction->getIndex())
								{
									hr=lpAction->QueryInterface(IID_IDispatch,(LPVOID*)pItem);
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
					hr = E_INVALIDARG;
			}
		}
	}
	return hr;
}

STDMETHODIMP CActions::Add(VARIANT index,LPDISPATCH pDispAction)
{
	long				lIndex=-1;
	HRESULT				hr=E_INVALIDARG;
	CAction				*pAction=NULL;
	LPAction			lpAction=NULL;
	LPAction			lpAddAction=NULL;
	CActionPtr			*pActionPtr=NULL;
	CActionsIterator	actionIter;

	if(pDispAction)
	{
		if(VT_ERROR==index.vt)
			lIndex = m_actionsCollection.size()+1;
		else
		{
			CComVariant		varIndex(index);
			if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
				if(SUCCEEDED(hr=varIndex.Detach(&index)))
					lIndex = index.lVal;
		}
		if((lIndex>0)&&(lIndex<=(m_actionsCollection.size()+1)))
		{
			if(SUCCEEDED(hr=pDispAction->QueryInterface(IID_IAction,(LPVOID*)&lpAddAction)))
			{
				if(pActionPtr=new CActionPtr(lpAddAction))
				{
					hr = E_FAIL;
					if(pAction=dynamic_cast<CAction*>(lpAddAction))
					{
						pAction->setIndex(lIndex);
						if(lIndex<m_actionsCollection.size())
						{
							for(actionIter=m_actionsCollection.begin(); 
								actionIter!= m_actionsCollection.end(); 
								actionIter++)
							{
								if(pActionPtr=*actionIter)
								{
									lpAction	=(*pActionPtr);
									if(pAction= dynamic_cast<CAction*>(lpAction))
									{
										if(lIndex==pAction->getIndex())
										{
											m_actionsCollection.insert(actionIter,pActionPtr);
											hr = NOERROR;
											break;
										}
									}
									else
										break;
								}
								else
									break;
							}
							if(SUCCEEDED(hr))
								hr = reIndex();
						}
						else
						{
							m_actionsCollection.insert(m_actionsCollection.end(),pActionPtr);
							hr = NOERROR;
						}
					}
				}
				lpAddAction->Release();
			}
		}
		else
			hr = E_INVALIDARG;
	}
	return hr;
}

STDMETHODIMP CActions::Delete(VARIANT index)
{
	long		lIndex=0;
	HRESULT		hr=E_INVALIDARG;
	CComVariant	varIndex(index);
	
	if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
	{
		if(SUCCEEDED(hr=varIndex.Detach(&index)))
		{
			lIndex = index.lVal;
			if(lIndex&&(lIndex<=m_actionsCollection.size())&&(lIndex>=1))
			{
				CActionsIterator	actionIter;
				CActionPtr			*pActionPtr;
				CAction				*pAction;
				LPAction			lpAction;

				for(actionIter=m_actionsCollection.begin(); 
					actionIter!= m_actionsCollection.end(); 
					actionIter++)
				{
					hr = E_FAIL;
					if(pActionPtr=*actionIter)
					{
						lpAction =(*pActionPtr);
						if(pAction=dynamic_cast<CAction*>(lpAction))
						{
							if(pAction->getIndex()==lIndex)
							{
								m_actionsCollection.erase(actionIter);
								delete pActionPtr;
								hr = reIndex();
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
				hr = E_INVALIDARG;
		}
	}
	return hr;
}

HRESULT CActions::reIndex()
{
	long				lIndex=0;
	CAction				*pAction=NULL;
	LPAction			lpAction=NULL;
	CActionPtr			*pActionPtr=NULL;
	CActionsIterator	actionIter;

	for(actionIter = m_actionsCollection.begin(); actionIter != m_actionsCollection.end(); 
		actionIter++, lIndex++)
	{
		if(pActionPtr=*actionIter)
		{
			lpAction =*pActionPtr;
			if(pAction=dynamic_cast<CAction*>(lpAction))
				pAction->setIndex(lIndex);
		}
	}
	return NOERROR;
}

HRESULT CActions::load(LPACTIONS lpActions)
{
	ULONG			ulActIndex= 0;
	HRESULT			hr=NOERROR;
	CActionPtr		*pActionPtr=NULL;
	CActionObject	*pActionOb=NULL;

	if(lpActions)
	{
		if(lpActions->cActions>0 && lpActions->lpAction)
		{
			for(ulActIndex=0;ulActIndex<lpActions->cActions;ulActIndex++)
			{
				if(SUCCEEDED(hr=CActionObject::CreateInstance(&pActionOb)))
				{
					if(SUCCEEDED(hr=pActionOb->load(&lpActions->lpAction[ulActIndex])))
					{
						if(pActionPtr=new CActionPtr(pActionOb))
						{
							pActionOb->setIndex(ulActIndex+1);
							m_actionsCollection.insert(m_actionsCollection.end(),
													   pActionPtr);
						}
						else
						{
							hr = E_FAIL;
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
			hr = E_INVALIDARG;
	}
	else
		hr = E_INVALIDARG;
	return hr;
}

HRESULT CActions::pack(LPACTIONS lpActions,LPVOID lpObject)
{
	long				lCount=0;
	HRESULT				hr=NOERROR;
	CAction				*pAction=NULL;
	LPAction			lpAction=NULL;
	CActionPtr			*pActionPtr=NULL;
	CActionsIterator	actionIter;

	if(lpActions)
	{
		lpActions->ulVersion = EDK_RULES_VERSION;
		lpActions->lpAction = NULL;
		if(lpActions->cActions=m_actionsCollection.size())
		{
			if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(ACTION)*m_actionsCollection.size(), 
											 lpObject,(LPVOID*)&lpActions->lpAction)))
			{
				for(actionIter=m_actionsCollection.begin();actionIter!=m_actionsCollection.end();
					actionIter++,lCount++)
				{
					if(pActionPtr=*actionIter)
					{
						lpAction = *pActionPtr;
						if(pAction= dynamic_cast<CAction*>(lpAction))
						{
							if(SUCCEEDED(hr=pAction->pack(&lpActions->lpAction[lCount], 
											lpObject)))
								continue;
							break;
						}
					}
					else
					{
						hr = E_FAIL;
						break;
					}
				}
			}
		}
		else
			hr = E_INVALIDARG;
	}
	else
		hr = E_INVALIDARG;

	return hr;
}

STDMETHODIMP CActions::Clear()
{
	HRESULT				hr=NOERROR;
	CAction				*pAction=NULL;
	LPAction			lpAction=NULL;
	CActionPtr			*pActionPtr=NULL;
	CActionsIterator	actionIter;

	for(actionIter=m_actionsCollection.begin(); 
		actionIter!= m_actionsCollection.end(); 
		actionIter++)
	{
		if(pActionPtr=*actionIter)
		{
			lpAction =(*pActionPtr);
			if(pAction=dynamic_cast<CAction*>(lpAction))
			{
				delete pActionPtr;
			}
			else
			{
				hr = E_FAIL;
				break;
			}
		}
		else
		{
			hr = E_FAIL;
			break;
		}
	}
	if(SUCCEEDED(hr))
		m_actionsCollection.clear();
	return hr;
}
