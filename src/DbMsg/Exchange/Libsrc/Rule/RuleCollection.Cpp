// ----------------------------------------------------------------------------
//	Rules.cpp : Implementation of CRules
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------

#include "stdafx.h"
#include "winerror.h"
#include "initguid.h"
#include "edkguid.h"
#include "mapiguid.h"
#include "mapiutil.h"

#include "Rule.h"
#include "util.h"
#include "ComPtrs.h"
#include "ActionObj.h"
#include "ActionCollection.h"
#include "RuleObj.h"
#include "RuleCollection.h"

const unsigned int	cMaxName =255;
const TCHAR* const	MAPIOBJECT= _T("MAPIOBJECT");

#pragma warning(disable:4541)

// CRules
CRules::CRules():
	m_bMAPIInitialized(FALSE),
	m_pMAPIFolder(NULL),
	m_pExchTbl(NULL),
	m_pMAPITbl(NULL),
	m_rulesCollection(),
	m_DeletedRules()
{
	_Module.m_pDispFolder = NULL;
	_Module.m_pCDOSession	= NULL;
	m_pszAProvider=new char[cMaxName];
	lstrcpyA(m_pszAProvider,"MSExchange.Rules");
}

void CRules::cleanup()
{
	CRuleIterator		ruleIter;
	CRulePtr			*pRulePtr;
	long				lCount=0;

	for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();ruleIter++)
	{
		pRulePtr=*ruleIter;
		delete pRulePtr;
	}
	for(ruleIter=m_DeletedRules.begin();ruleIter!=m_DeletedRules.end();ruleIter++)
	{
		pRulePtr=*ruleIter;
		delete pRulePtr;
	}
	m_rulesCollection.clear();
	m_DeletedRules.clear();

	if(m_pMAPITbl)
		m_pMAPITbl->Release();
	if(m_pExchTbl)
		m_pExchTbl->Release();
	if(m_pMAPIFolder)
		m_pMAPIFolder->Release();
	if(_Module.m_pDispFolder)
		_Module.m_pDispFolder->Release();
	if(_Module.m_pCDOSession)
		_Module.m_pCDOSession->Release();

	m_pMAPITbl=NULL;
	m_pExchTbl=NULL;
	m_pMAPIFolder=NULL;
	_Module.m_pDispFolder=NULL;
	_Module.m_pCDOSession=NULL;
}

CRules::~CRules()
{
	cleanup();
	delete [] m_pszAProvider;
	if(TRUE==m_bMAPIInitialized)
		MAPIUninitialize();
}

STDMETHODIMP CRules::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[]=
	{
		&IID_IRules,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CRules::get_Folder(LPDISPATCH *pVal)
{
	return _Module.m_pDispFolder->QueryInterface(IID_IDispatch,(LPVOID*)pVal);
}

STDMETHODIMP CRules::put_Folder(LPDISPATCH newVal)
{
	VARIANT			lVarResult;
	HRESULT			hr=E_INVALIDARG;
	LPSRowSet		lpRowSet=NULL;

	if(newVal)
	{
		if(FALSE==m_bMAPIInitialized)
		{
			if(SUCCEEDED(hr=MAPIInitialize(NULL)))
				m_bMAPIInitialized = TRUE;
		}
		cleanup();
		_Module.m_pDispFolder=newVal;
		_Module.m_pDispFolder->AddRef();
	
		if(SUCCEEDED(hr=::PropertyInvoke(_Module.m_pDispFolder,DISPATCH_PROPERTYGET,MAPIOBJECT,&lVarResult)))
		{
			if(SUCCEEDED(hr=VariantToMAPIObject(lVarResult,IID_IMAPIFolder,
								(LPVOID*)&m_pMAPIFolder)))
			{
				if(SUCCEEDED(hr=getRulesTable()))
				{
					if(SUCCEEDED(hr=getRowSet(&lpRowSet)))
					{
						if(SUCCEEDED(hr=::PropertyInvoke(_Module.m_pDispFolder,DISPATCH_PROPERTYGET,_T("Session"),&lVarResult)))
						{
							if(VT_DISPATCH==lVarResult.vt)
							{
								if(SUCCEEDED(hr=lVarResult.pdispVal->QueryInterface(IID_IDispatch,(LPVOID*)&_Module.m_pCDOSession)))
								{
									hr=load(lpRowSet);
								}
								VariantClear(&lVarResult);
							}
						}
					}
				}
			}
		}
	}

	FreeProws(lpRowSet);
	if(FAILED(hr))
		cleanup();

	return hr;
}

HRESULT CRules::getRulesTable()
{
	HRESULT		hr=NOERROR;

	// Open the RULE table property on the folder.  The returned table
	// pointer may be used to get a MAPI table for reading and it can
	// also be used to modify the rules table.  If there is no rules table,
	// this call will fail with E_NOINTERFACE.
    if(SUCCEEDED(hr=m_pMAPIFolder->OpenProperty(
										PR_RULES_TABLE,
										(LPGUID)&IID_IExchangeModifyTable,
										0,
										MAPI_DEFERRED_ERRORS,
										(LPUNKNOWN*)&m_pExchTbl 
										)))
	{
		//	Open a MAPI table on the RULE table property.  This table can be
		//	read to determine what the rules table looks like.
		hr=m_pExchTbl->GetTable(0,&m_pMAPITbl);
	}
	return hr;
}

HRESULT CRules::getRowSet(LPSRowSet *lppRows)
{
	HRESULT		hr		= NOERROR;
	ULONG		ulRow	= 0;
	ULONG		ulNum	= 0;
	ULONG		ulDenom	= EDK_MAX_QUERY_ROWS;

	SizedSPropTagArray(C_RULEPROPS,rgPropTag)=
	{
		C_RULEPROPS,
    	{
    		PR_RULE_SEQUENCE,
    		PR_RULE_STATE,
    		PR_RULE_CONDITION,
    		PR_RULE_ACTIONS,
    		PR_RULE_PROVIDER,
			PR_RULE_NAMEA,
			PR_RULE_LEVEL,
			PR_RULE_ID,
			PR_RULE_NAMEW
		}
	};
	if(SUCCEEDED(hr=m_pMAPITbl->SetColumns((LPSPropTagArray)&rgPropTag,0)))
		if(SUCCEEDED(hr=m_pMAPITbl->SeekRow(BOOKMARK_BEGINNING,0,NULL)))
			hr=HrQueryAllRows(m_pMAPITbl,NULL,NULL,NULL,EDK_MAX_QUERY_ROWS,lppRows);
	return hr;
}

HRESULT CRules::load(LPSRowSet lpRows)
{
	long				cOurProviderRules=0;
	long				cOtherProviderRules=0;
	ULONG				lRowCount=0;
	ULONG				ulRow  =0;
	BOOL				sortReqd=TRUE;
	HRESULT				hr = E_INVALIDARG;
	LPSSortOrderSet		lpSortOrderSet=NULL;
	
	if(lpRows)
	{
		// Check to be sure that table is not bigger than EDK_MAX_QUERY_ROWS.
		// We do this by checking whether or not the cursor is positioned at
		// the end of the table.
		if(lpRows->cRows == EDK_MAX_QUERY_ROWS)
		{
			ULONG	ulNumerator =	0;
			ULONG	ulDenominator =	0;

			if(SUCCEEDED(hr=m_pMAPITbl->QueryPosition(&ulRow,&ulNumerator,
										&ulDenominator)))
			{
				// SeekRowApprox()doc states that if ulNumerator == ulDenominator,you
				// are at the end of the table,of course
				if(ulNumerator!=ulDenominator)
					hr = NOERROR;
			}
		}
	
		// check if the rows are sorted in the order of sequence 
		// that way we need not do any sorting as we assign indices for the 
		// rules in the order of the sequence
		if(SUCCEEDED(hr=m_pMAPITbl->QuerySortOrder(&lpSortOrderSet)))
		{
			for(ulRow=0;ulRow < lpSortOrderSet->cSorts;ulRow++)
			{
				if((PR_RULE_SEQUENCE	== lpSortOrderSet->aSort[ulRow].ulPropTag)&&
					(TABLE_SORT_ASCEND== lpSortOrderSet->aSort[ulRow].ulOrder))
				{
					sortReqd=FALSE;
					break;
				}
			}
		}
	}

	if(SUCCEEDED(hr))
	{
		if(TRUE == sortReqd)
			return MAPI_E_NO_SUPPORT;
	}
	else
		return hr;

	// as of now we are not going to sort LPSRowSet array in the order
	// of PR_RULE_SEQUENCE,As observed the rowset is already
	// sorted in that order. In future if the sort is not done,we may have
	// to implement a sorting function here
	// rules table does not support SortTable function


	LPSRow				lpSRow=NULL;
	CRuleObject			*pRuleOb=NULL;
	CRulePtr			*pRulePtr=NULL;

	// we now assume rules are all sorted in sequence order
	for(lRowCount=0;lRowCount<lpRows->cRows;lRowCount++)
	{
		lpSRow	=(&lpRows->aRow[lRowCount]);

		if( lpSRow->cValues < C_RULEPROPS										||
			lpSRow->lpProps[I_RULE_ID].ulPropTag		!=  PR_RULE_ID			||
			lpSRow->lpProps[I_RULE_SEQUENCE].ulPropTag	!=	PR_RULE_SEQUENCE	||
			lpSRow->lpProps[I_RULE_STATE].ulPropTag		!=	PR_RULE_STATE		||
			lpSRow->lpProps[I_RULE_CONDITION].ulPropTag	!=	PR_RULE_CONDITION	||
			lpSRow->lpProps[I_RULE_ACTIONS].ulPropTag	!=	PR_RULE_ACTIONS		||
			lpSRow->lpProps[I_RULE_PROVIDER].ulPropTag	!=	PR_RULE_PROVIDER	||
			lpSRow->lpProps[I_RULE_PROVIDER].Value.lpszA==	NULL				||
			lpSRow->lpProps[I_RULE_LEVEL].ulPropTag		!=	PR_RULE_LEVEL		||
			!(
			lpSRow->lpProps[I_RULE_NAMEA].ulPropTag	==  PR_RULE_NAMEA			||
			lpSRow->lpProps[I_RULE_NAMEW].ulPropTag	==	PR_RULE_NAMEW )
		  )
		{
			hr=E_INVALIDARG;
			break;
		}
		// before we create a new rule object,we have to see if this rule
		// is of our provider,if not we would'nt be modifiying it and we have to set
		// the rule to be read only 

		if(SUCCEEDED(hr=CRuleObject::CreateInstance(&pRuleOb)))
		{
			if(SUCCEEDED(hr=pRuleOb->load(lpSRow,lRowCount+1)))
			{
				// create a new smart pointer to this object
				if(pRulePtr=new CRulePtr(pRuleOb))
				{
					if(0==lstrcmpA(m_pszAProvider,lpSRow->lpProps[I_RULE_PROVIDER].Value.lpszA))
					{
						pRuleOb->setPersistence(PERS_MODIFY);
						pRuleOb->setReadWrite();
					}
					else
						pRuleOb->setReadOnly();
					// insert the smart pointer at the end of the list
					m_rulesCollection.insert(m_rulesCollection.end(),pRulePtr);
				}
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
	return hr;
}

STDMETHODIMP CRules::Add(VARIANT index,LPDISPATCH pDispRule)
{
	CRulePtr		*pRulePtr=NULL;
	CRule			*pRule=NULL;
	LPRULE			lpRule=NULL;
	LPRULE			lpAddRule=NULL;
	HRESULT			hr=E_INVALIDARG;
	long			lIndex=-1;
	long			lPrevSequence=0;
	long			lCurSequence=0;

	if(pDispRule)
	{
		// first get the index integer value
		if(VT_ERROR==index.vt)
		{
			lIndex = m_rulesCollection.size()+1;
		}
		else
		{
			CComVariant		varIndex(index);
			if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
				if(SUCCEEDED(hr=varIndex.Detach(&index)))
					lIndex = index.lVal;
		}
		// if it is greater than the existing rules or less than 1 it is invalid
		if((lIndex>0)&&(lIndex<=(m_rulesCollection.size()+1)))
		{
			// first get a pointer to rule interface from the disp interface
			if(SUCCEEDED(hr=pDispRule->QueryInterface(IID_IRule,(LPVOID*)&lpAddRule)))
			{
				// allocate a new smart pointer
				if(pRulePtr=new CRulePtr(lpAddRule))
				{
					if(pRule=dynamic_cast<CRule*>(lpAddRule))
					{
						// set the index to the given index
						pRule->setIndex(lIndex);
						pRule->setReadWrite();
						pRule->setProvider(m_pszAProvider);
						pRule->setPersistence(PERS_ADD);

						if(lIndex<=m_rulesCollection.size())
						{
							// this is an insertion
							// the thing I have to check is
							// .	see if there is enough gap in the sequence nos at this point
							//		that is rule[lIndex].sequenceNo>1 + rule[lIndex-1].sequenceNo
							//		in which case I could just assign the rule[lIndex-1].sequenceNo+1
							//		to this new rule,indices are however pseudo values
	
							CRuleIterator	ruleIter;
							CRulePtr		*pPrevPtr=NULL;
							CRulePtr		*pCurPtr=NULL;
							long			ruleIndex;

							for(ruleIter=m_rulesCollection.begin();
								ruleIter != m_rulesCollection.end();ruleIter++)
							{
								if(pCurPtr=*ruleIter)
								{
									if(SUCCEEDED(hr=(*pCurPtr)->get_Index(&ruleIndex)))
									{
										if(lIndex==ruleIndex)
										{
											// this is the point of insertion
											if(pPrevPtr)
											{
												if(SUCCEEDED(hr=(*pPrevPtr)->get_Sequence(
																&lPrevSequence)))
												{
													if(SUCCEEDED(hr=(*pCurPtr)->get_Sequence(&lCurSequence)))
													{
														if(lCurSequence<=lPrevSequence+1)
														{
															pRule->setSequence(lPrevSequence+1);
															m_rulesCollection.insert(ruleIter,pRulePtr);

															if(SUCCEEDED(hr=reSequence()))
															{
																hr=reIndex();
																break;
															}
														}
														else 
														{
															pRule->setSequence(lPrevSequence+1);
															m_rulesCollection.insert(ruleIter,pRulePtr);
															hr=reIndex();
															break;
														}
														break;
													}
													break;
												}
												break;
											}
											else if(SUCCEEDED(hr=(*pCurPtr)->get_Sequence(&lCurSequence)))
											{
												if(lCurSequence>=1)
												{
													pRule->setSequence(lCurSequence-1);
													m_rulesCollection.insert(m_rulesCollection.begin(),pRulePtr);
													hr = reIndex();
													break;
												}
												else
												{
													pRule->setSequence(lCurSequence);
													m_rulesCollection.insert(m_rulesCollection.begin(),pRulePtr);
													if(SUCCEEDED(hr = reIndex()))
														hr = reSequence();
													break;
												}
											}
											else 
											{
												pRule->setSequence(0);
												m_rulesCollection.insert(m_rulesCollection.begin(),pRulePtr);
												if(SUCCEEDED(hr=reSequence()))
													hr=reIndex();
												break;
											}
										}
									}
								}
								pPrevPtr=pCurPtr;
							}
						}
						else
						{
							// insert at the end of the collection,always succeds
							if(m_rulesCollection.size())
							{
								CRulePtr	*pEndPtr=m_rulesCollection.back();
								if(pEndPtr)
								{
									lpRule=*pEndPtr;
									hr=lpRule->get_Sequence(&lCurSequence);
								}
							}
							else
							{
								lCurSequence = 0;
								hr = NOERROR;
							}
							if(SUCCEEDED(hr))
							{
								pRule->setSequence(lCurSequence + 1);
								m_rulesCollection.insert(m_rulesCollection.end(),pRulePtr);
							}
						}
					}
					else
						hr=E_FAIL;
				}
				else
					hr = E_OUTOFMEMORY;
				lpAddRule->Release();
			}
			else
				hr=E_FAIL;
		}
		else
			hr = E_INVALIDARG;
	}
	if(FAILED(hr))
		if(pRulePtr)
			delete pRulePtr;
	return hr;
}

STDMETHODIMP CRules::Delete(VARIANT index)
{
	long			lIndex;
	HRESULT			hr=NOERROR;
	CComVariant		varIndex(index);

	if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
	{
		if(SUCCEEDED(hr=varIndex.Detach(&index)))
		{
			lIndex = index.lVal;
			if((lIndex<=m_rulesCollection.size())&&(lIndex>=1))
			{
				CRuleIterator	ruleIter;
				CRulePtr		*pRulePtr;
				LPRULE			lpRule;
				CRule			*pRule;
				BOOL			bReadOnly;
				long			ruleIndex;

				for(ruleIter=m_rulesCollection.begin();ruleIter != m_rulesCollection.end();
					ruleIter++)
				{
					pRulePtr=*ruleIter;
					if(NULL!=pRulePtr)
					{
						if(SUCCEEDED(hr=(*pRulePtr)->get_Index(&ruleIndex)))
						{
							if(ruleIndex==lIndex)
							{
								if(SUCCEEDED(hr =(*pRulePtr)->get_ReadOnly(&bReadOnly)))
								{
									if(bReadOnly)
									{
										// cannot delete other providers' rules
										hr =E_ACCESSDENIED;
										break;
									}
									else
									{
										m_rulesCollection.erase(ruleIter);
										lpRule	= *pRulePtr;
										if(pRule=dynamic_cast<CRule*>(lpRule))
										{
											LARGE_INTEGER	lID=pRule->getRuleID();
											if((lID.LowPart==0)&&(lID.HighPart==0))
												delete pRulePtr;
											else
											{
												m_DeletedRules.insert(m_DeletedRules.end(),pRulePtr);
												pRule->setPersistence(PERS_REMOVE);
											}
										}
										hr=reIndex();
										break;
									}
								}
							}
						}
						else
							break;
					}
					else 
					{
						hr=E_FAIL;
						break;
					}
				}
			}
			else
				hr=E_INVALIDARG;
		}
	}

	return hr;
}

STDMETHODIMP CRules::Item(VARIANT index,LPDISPATCH *pItem)
{
	long				lIndex=-1;
	HRESULT				hr=E_INVALIDARG;

	if(pItem)
	{
		CComVariant		varIndex(index);
		if(SUCCEEDED(hr=varIndex.ChangeType(VT_I4)))
		{
			if(SUCCEEDED(hr=varIndex.Detach(&index)))
			{
				lIndex = index.lVal;
				if((lIndex<=m_rulesCollection.size())&&(lIndex>=1))
				{
					CRuleIterator	ruleIter;
					CRulePtr		*pRulePtr;
					long			ruleIndex;

					for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();
						ruleIter++)
					{
						pRulePtr=*ruleIter;
						if(NULL!=pRulePtr)
						{
							if(SUCCEEDED(hr=(*pRulePtr)->get_Index(&ruleIndex)))
							{
								if(ruleIndex==lIndex)
								{
									hr =(*pRulePtr)->QueryInterface(IID_IDispatch,(LPVOID*)pItem);
									break;
								}
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
				}
				else
					hr = E_INVALIDARG;
			}
			else
				hr = E_INVALIDARG;
		}
	}
	return hr;
}

STDMETHODIMP CRules::get_Count(long *pVal)
{
	if(pVal)
	{
		*pVal=m_rulesCollection.size();
		return S_OK;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRules::get__NewEnum(LPUNKNOWN *pVal)
{
	CRuleIterator	ruleIter;
	CRulePtr		*pRulePtr=NULL;
	CRuleEnumVar	*pRuleEnum=NULL;
	VARIANT			*varArray=NULL;
	HRESULT			hr=NOERROR;
	long			lCount=0;

	if(pVal)
	{
		if(pRuleEnum=new CRuleEnumVar)
		{
			if(varArray=new VARIANT[m_rulesCollection.size()])
			{
				for(ruleIter=m_rulesCollection.begin();ruleIter != m_rulesCollection.end();
					ruleIter++,lCount++)
				{
					pRulePtr =*ruleIter;
					if(NULL != pRulePtr)
					{
						VariantInit(&varArray[lCount]);
						varArray[lCount].vt=VT_DISPATCH;
						if(SUCCEEDED(hr =(*pRulePtr)->QueryInterface(IID_IDispatch,
									(LPVOID *)&(varArray[lCount].pdispVal))))
							continue;
						else
							break;
					}
					else
					{
						hr=E_FAIL;
						break;
					}
				}
				if(SUCCEEDED(hr))
				{
					if(SUCCEEDED(hr=pRuleEnum->Init(&varArray[0],&varArray[lCount],NULL,AtlFlagTakeOwnership)))
						hr=pRuleEnum->QueryInterface(IID_IUnknown,(LPVOID*)pVal);
				}
			}
			else
				hr = E_OUTOFMEMORY;

		}
		else
			hr=E_OUTOFMEMORY;
	}
	else
		hr = E_INVALIDARG;
	
	if(FAILED(hr))
		if(pRuleEnum)
			delete pRuleEnum;
	return hr;
}

HRESULT CRules::reSequence()
{
	CRuleIterator	ruleIter;
	CRulePtr		*pRulePtr=NULL;
	CRule			*pRule=NULL;
	LPRULE			lpRule=NULL;
	HRESULT			hr=NOERROR;
	long			lLastSequenceNo=-1;
	long			lSequenceNo=0;
	long			lCount=1;

	for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();
		ruleIter++,lCount++)
	{
		pRulePtr	=*ruleIter;
		if(NULL != pRulePtr)
		{
			lpRule	= *pRulePtr;
			if(pRule=dynamic_cast<CRule*>(lpRule))
			{
				if(SUCCEEDED(hr=pRule->get_Sequence(&lSequenceNo)))
				{
					if(lLastSequenceNo>=lSequenceNo)
					{
						pRule->setSequence(lSequenceNo=lLastSequenceNo+1);
						if(PERS_EMPTY==pRule->getPersistence())
						{
							LARGE_INTEGER	lID=pRule->getRuleID();
							if((lID.LowPart==0)&&(lID.HighPart==0))
							{
								if(pRule->getPersistence()!=PERS_ADD)
								{
									hr = E_FAIL;
									break;
								}
							}
							else
								pRule->setPersistence(PERS_MODIFY);
						}
					}
					lLastSequenceNo = lSequenceNo;
				}
			}
		}
	}
	return hr;
}

HRESULT	CRules::reIndex()
{
	CRuleIterator	ruleIter;
	CRulePtr		*pRulePtr=NULL;
	CRule			*pRule=NULL;
	LPRULE			lpRule=NULL;
	HRESULT			hr=NOERROR;
	long			lCount=1;

	for(ruleIter=m_rulesCollection.begin();ruleIter != m_rulesCollection.end();
		ruleIter++,lCount++)
	{
		pRulePtr	=*ruleIter;
		if(NULL!=pRulePtr)
		{
			lpRule= *pRulePtr;
			if(pRule=dynamic_cast<CRule*>(lpRule))
			{
				pRule->setIndex(lCount);
				continue;
			}
		}
		else
		{
			hr=E_FAIL;
			break;
		}
	}
	return hr;
}
		
STDMETHODIMP CRules::UpdateIndices()
{
	CRuleIterator	ruleIter;
	CRulePtr		*pRulePtr=NULL;
	CRule			*pRule=NULL;
	LPRULE			lpRule=NULL;
	HRESULT			hr=NOERROR;
	long			lCount=0;
	long			lIndex=0;
	long			lSum=0;
	long			lLastSequenceNo=0;
	long			lSequenceNo=0;

	lSum=0;
	for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();ruleIter++,lCount++)
	{
		pRulePtr	=*ruleIter;
		if(pRulePtr)
		{
			lpRule	= *pRulePtr;
			if(pRule=dynamic_cast<CRule*>(lpRule))
			{
				if(SUCCEEDED(hr=pRule->get_NewIndex(&lIndex)))
				{
					if(lIndex>=0)
						pRule->setIndex(lIndex);
				}
				else
					break;

				if(SUCCEEDED(hr=pRule->get_Index(&lIndex)))
				{
					lSum += lIndex;
					continue;
				}
				else
					break;
			}
		}
		else
		{
			hr=E_FAIL;
			break;
		}
	}
	if(SUCCEEDED(hr))
	{
		if(lSum==((m_rulesCollection.size()*(m_rulesCollection.size()+1))/2))
		{
			CRuleList		tmpCollection;
			CRuleIterator	tmpruleIter;

			lCount = 1;
			for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();ruleIter++,lCount++)
			{
				for(tmpruleIter=m_rulesCollection.begin();tmpruleIter!=m_rulesCollection.end();tmpruleIter++)
				{
					pRulePtr	=*tmpruleIter;
					if(pRulePtr)
					{
						lpRule	= *pRulePtr;
						if(pRule=dynamic_cast<CRule*>(lpRule))
						{
							if(SUCCEEDED(hr=pRule->get_Index(&lIndex)))
							{
								if(lIndex==lCount)
								{
									tmpCollection.insert(tmpCollection.end(),pRulePtr);
									break;
								}
							}
						}
					}
				}
			}
			if(m_rulesCollection.size()==tmpCollection.size())
			{
				m_rulesCollection.clear();
				for(ruleIter=tmpCollection.begin();ruleIter!=tmpCollection.end();ruleIter++)
				{
					pRulePtr	=*ruleIter;
					m_rulesCollection.insert(m_rulesCollection.end(),pRulePtr);
				}
				reSequence();
			}
			else
				hr = E_FAIL;
		}
		else
			hr=E_FAIL;	// there are duplicate indices
	}
	return hr;
}

STDMETHODIMP CRules::Update()
{
	CRuleIterator	ruleIter;
	CRulePtr		*pRulePtr=NULL;
	CRule			*pRule=NULL;
	LPRULE			lpRule=NULL;
	LPROWLIST		lpRowList =	NULL;
	HRESULT			hr=NOERROR;
	long			lNewRows=0;
	long			lItems=0;
	long			lCount=0;

	if(SUCCEEDED(hr=reSequence()))
	{
		lNewRows = m_rulesCollection.size();
		for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();ruleIter++)
		{
			pRulePtr= *ruleIter;
			lpRule	= *pRulePtr;

			if(pRule=dynamic_cast<CRule*>(lpRule))
			{
				// for PERS_EMPTY
				if(PERS_EMPTY==pRule->getPersistence())
					continue;
				lItems++;
			}
		}
		if(lItems += m_DeletedRules.size())
		{
			if(SUCCEEDED(hr=MAPIAllocateBuffer(sizeof(ROWLIST)+(lItems-MAPI_DIM)*sizeof(ROWENTRY),(LPVOID*)&lpRowList)))
			{
				lpRowList->cEntries=lItems;

				for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();ruleIter++)
				{
					pRulePtr= *ruleIter;
					lpRule	= *pRulePtr;

					if(pRule=dynamic_cast<CRule*>(lpRule))
					{
						if(PERS_EMPTY!=pRule->getPersistence())
						{
							if(SUCCEEDED(hr=pRule->pack((LPROWENTRY)&lpRowList->aEntries[lCount++],lpRowList)))
								continue;
							else
							{
								hr = E_FAIL;
								break;
							}
						}
					}
					else
					{
						hr = E_FAIL;
						break;
					}
				}
				if(SUCCEEDED(hr))
				{
					for(ruleIter=m_DeletedRules.begin();ruleIter!=m_DeletedRules.end();ruleIter++)
					{
						pRulePtr= *ruleIter;
						lpRule	= *pRulePtr;

						if(pRule=dynamic_cast<CRule*>(lpRule))
						{
							if(SUCCEEDED(hr=pRule->pack((LPROWENTRY)&lpRowList->aEntries[lCount++],lpRowList)))
								continue;
							else
							{
								hr = E_FAIL;
								break;
							}
						}
					}
					if(SUCCEEDED(hr))
						hr=m_pExchTbl->ModifyTable(0,lpRowList);
				}
			}
			else
				hr = E_OUTOFMEMORY;
		}
	}
	MAPIFreeBuffer(lpRowList);
	if(SUCCEEDED(hr))
	{
		for(ruleIter=m_DeletedRules.begin();ruleIter!=m_DeletedRules.end();ruleIter++)
		{
			pRulePtr= *ruleIter;
			delete pRulePtr;
		}
		m_DeletedRules.clear();
		for(ruleIter=m_rulesCollection.begin();ruleIter!=m_rulesCollection.end();ruleIter++)
		{
			pRulePtr= *ruleIter;
			delete pRulePtr;
		}
		m_rulesCollection.clear();
		
		LPSRowSet		lpRowSet=NULL;
		
		if(m_pMAPITbl)
			m_pMAPITbl->Release();
		if(m_pExchTbl)
			m_pExchTbl->Release();

		if(SUCCEEDED(hr=getRulesTable()))
			if(SUCCEEDED(hr=getRowSet(&lpRowSet)))
				hr = load(lpRowSet);
		FreeProws(lpRowSet);

		if(lNewRows!=m_rulesCollection.size())
			hr = E_FAIL;
	}
	return hr;
}

STDMETHODIMP CRules::Clear()
{
	HRESULT			hr=NOERROR;
	CRuleIterator	ruleIter;
	CRulePtr		*pRulePtr=NULL;
	CRule			*pRule=NULL;
	LPRULE			lpRule=NULL;

	for(ruleIter=m_rulesCollection.begin();ruleIter != m_rulesCollection.end();ruleIter++)
	{
		if(pRulePtr=*ruleIter)
		{
			lpRule	= *pRulePtr;
			if(pRule=dynamic_cast<CRule*>(lpRule))
			{
				LARGE_INTEGER	lID=pRule->getRuleID();

				if((lID.LowPart==0)&&(lID.HighPart==0))
					delete pRulePtr;
				else
				{
					m_DeletedRules.insert(m_DeletedRules.end(),pRulePtr);
					pRule->setPersistence(PERS_REMOVE);
				}
			}
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
		m_rulesCollection.clear();
	return hr;
}
