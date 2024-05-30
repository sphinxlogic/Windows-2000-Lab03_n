// ----------------------------------------------------------------------------
//	Rule.cpp : Implementation of CRule
//
//	Copyright(C)Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------
#include "stdafx.h"
#include "Rule.h"

#include "ComPtrs.h"
#include "BaseCondition.h"
#include "ActionObj.h"
#include "ActionCollection.h"
#include "RuleObj.h"
#include "util.h"

#pragma warning(disable:4541)

CRule::CRule():
				m_lSequence(0),
				m_lState(ST_ENABLED),
				m_lNameType(PT_TSTRING),
				m_pCondition(NULL),
				m_pActions(NULL),
				m_lpszAProvider(NULL),
				m_lpszTName(NULL),
				m_lLevel(0),
				m_lIndex(0),
				m_lNewIndex(-1),
				m_bReadOnly(FALSE),
				m_lPersist(PERS_EMPTY)
{
	m_liRuleId.LowPart = 0;
	m_liRuleId.HighPart= 0;
}

CRule::~CRule()
{
	cleanup();
}

STDMETHODIMP CRule::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRule,
	};
	for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if(InlineIsEqualGUID(*arr[i],riid))
			return NOERROR;
	}
	return S_FALSE;
}

void CRule::cleanup()
{
	if(m_lpszAProvider)
	{
		delete [] m_lpszAProvider;
		m_lpszAProvider = NULL;
	}
	if(m_lpszTName)
	{
		delete [] m_lpszTName;
		m_lpszTName = NULL;
	}
	if(m_pCondition)
	{
		delete m_pCondition;
		m_pCondition = NULL;
	}
	if(m_pActions)
	{
		delete m_pActions;
		m_pActions = NULL;
	}
}

void CRule::setProvider(LPCSTR lpcStrProv)
{
	if(lpcStrProv)
	{
		if(m_lpszAProvider)
			delete[] m_lpszAProvider;
		if(m_lpszAProvider=new char[lstrlenA(lpcStrProv)+1])
			lstrcpyA(m_lpszAProvider,lpcStrProv);
	}
}

STDMETHODIMP CRule::get_Sequence(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lSequence;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::get_State(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lState;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::put_State(long newVal)
{
	if(m_bReadOnly)
		return E_ACCESSDENIED;

	m_lState = newVal;
	return NOERROR;
}

STDMETHODIMP CRule::get_Provider(BSTR *pVal)
{
	if(pVal)
	{
		*pVal = SysAllocString((BSTR)_bstr_t(m_lpszAProvider));
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::put_Provider(BSTR newVal)
{
	if(m_bReadOnly)
		return E_ACCESSDENIED;

	if(m_lpszAProvider)
		delete [] m_lpszAProvider;

	_bstr_t		bstrt(newVal);
	LPCSTR		lpcStr =(const char*)bstrt;
	HRESULT		hr=NOERROR;

	if(lpcStr)
	{
		if(m_lpszAProvider = new char[lstrlenA(lpcStr)+1])
			lstrcpyA(m_lpszAProvider, lpcStr);
		else
			hr = E_OUTOFMEMORY;
	}
	else
		hr = E_INVALIDARG;

	return hr;
}

STDMETHODIMP CRule::get_Level(long * pVal)
{
	if(pVal)
	{
		*pVal = m_lLevel;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::put_Level(long newVal)
{
	if(m_bReadOnly)
		return E_ACCESSDENIED;

	m_lLevel = newVal;
	return NOERROR;
}

STDMETHODIMP CRule::get_Name(BSTR *pVal)
{
	if(pVal)
	{
		*pVal = ::SysAllocString((BSTR)_bstr_t(m_lpszTName));
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::put_Name(BSTR newVal)
{
	if(m_bReadOnly)
		return E_ACCESSDENIED;

	_bstr_t		bstrt(newVal);
	LPCTSTR		lpctStr =(LPCTSTR)bstrt;
	HRESULT		hr=NOERROR;

	if(lpctStr)
	{
		if(m_lpszTName)
			delete [] m_lpszTName;
		if(NULL !=(m_lpszTName = new TCHAR[lstrlen(lpctStr)+1]))
			lstrcpy(m_lpszTName,(LPCTSTR)lpctStr); 
		else
			hr = E_OUTOFMEMORY;
	}
	else
		hr = E_INVALIDARG;

	return hr;
}		

STDMETHODIMP CRule::get_Index(long *pVal)
{
	if(pVal)
	{
		*pVal = m_lIndex;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::get_Condition(LPDISPATCH *pVal)
{
	if(pVal)
	{
		*pVal = NULL;
		if(m_pCondition)
			return(*m_pCondition)->QueryInterface(IID_IDispatch,(LPVOID*)pVal);
		else
			return S_OK;	//	fine not to have a condition at all
	}
	else
		return E_INVALIDARG;
}

STDMETHODIMP CRule::put_Condition(LPDISPATCH newVal)
{
	if(m_bReadOnly)
		return E_ACCESSDENIED;

	LPCONDITION		lpCondition=NULL;
	HRESULT			hr=NOERROR;

	if(newVal)
	{
		if(SUCCEEDED(hr=newVal->QueryInterface(IID_ICondition,(LPVOID*)&lpCondition)))
		{
			if(m_pCondition)
				delete m_pCondition;
	
			if(NULL==(m_pCondition = new CConditionPtr(lpCondition)))
				hr = E_OUTOFMEMORY;
			lpCondition->Release();
		}
	}
	return hr;
}

STDMETHODIMP CRule::get_Actions(LPDISPATCH *pVal)
{
	HRESULT	hr=NOERROR;
	if(pVal)
	{
		if(m_pActions)
			hr = (*m_pActions)->QueryInterface(IID_IDispatch,(LPVOID*)pVal);
		else
		{
			CActionsObject	*pActionsOb=NULL;
			if(SUCCEEDED(hr=CActionsObject::CreateInstance(&pActionsOb)))
			{
				if(m_pActions=new CActionsPtr(pActionsOb))
					hr = (*m_pActions)->QueryInterface(IID_IDispatch,(LPVOID*)pVal);
				else
					hr = E_OUTOFMEMORY;
			}
		}
	}
	else
		hr = E_INVALIDARG;
	return hr;
}

STDMETHODIMP CRule::get_NewIndex(long * pVal)
{
	if(pVal)
	{
		*pVal = m_lNewIndex;
		return NOERROR;
	}
	return E_INVALIDARG;
}

STDMETHODIMP CRule::put_NewIndex(long newVal)
{
	m_lNewIndex = newVal;
	return NOERROR;
}

STDMETHODIMP CRule::get_ReadOnly(BOOL * pVal)
{
	if(pVal)
	{
		*pVal = m_bReadOnly;
		return NOERROR;
	}
	return E_INVALIDARG;
}

HRESULT CRule::load(LPSRow lpSRow,ULONG ulIndex)
{
	HRESULT	hr=E_INVALIDARG;

	if(lpSRow)
	{
		m_liRuleId		= lpSRow->lpProps[I_RULE_ID].Value.li;
		m_lSequence		= lpSRow->lpProps[I_RULE_SEQUENCE].Value.l;
		m_lState		= lpSRow->lpProps[I_RULE_STATE].Value.l;
		m_lLevel		= lpSRow->lpProps[I_RULE_LEVEL].Value.l;
		m_lIndex		= ulIndex;

		LPCONDITION		lpCondition=NULL;
		CBaseCondition	*pCondition=NULL;
		CActionsObject	*pActionsOb=NULL;

		cleanup();
		if(m_lpszAProvider = new char[lstrlenA(
							lpSRow->lpProps[I_RULE_PROVIDER].Value.lpszA)+1])
		{
			lstrcpyA(m_lpszAProvider,lpSRow->lpProps[I_RULE_PROVIDER].Value.lpszA);

			if(SUCCEEDED(hr=CActionsObject::CreateInstance(&pActionsOb)))
			{
				if(m_pActions=new CActionsPtr(pActionsOb))
				{
					if(lpSRow->lpProps[I_RULE_ACTIONS].Value.ul)
					{
						if(SUCCEEDED(hr=pActionsOb->load((LPACTIONS)lpSRow->lpProps[I_RULE_ACTIONS].Value.ul)))
						{
							if(PT_ERROR==(m_lNameType=PROP_TYPE(lpSRow->lpProps[I_RULE_NAMEA].ulPropTag)))
								m_lNameType = PROP_TYPE(lpSRow->lpProps[I_RULE_NAMEW].ulPropTag);

							if(PT_STRING8==m_lNameType)
							{
								// this means whatever version of object we are this
								// particular rule has ASCII name
#ifdef UNICODE
								long	srcLen = lstrlenA(lpSRow->lpProps[I_RULE_NAMEA].Value.lpszA);
								if(m_lpszTName = new wchar_t[srcLen+1])
								{
									::MultiByteToWideChar(CP_ACP,0,
														  lpSRow->lpProps[I_RULE_NAMEA].Value.lpszA,-1,
														  m_lpszTName,srcLen+1);
								}
								else
									hr = E_OUTOFMEMORY;
#else
								long	srcLen = lstrlen(lpSRow->lpProps[I_RULE_NAMEA].Value.LPSZ);
								if(m_lpszTName = new TCHAR[srcLen+1])
								{
									lstrcpy(m_lpszTName,lpSRow->lpProps[I_RULE_NAMEA].Value.LPSZ);
								}
								else
									hr = E_OUTOFMEMORY;
#endif
							}
							else if(PT_UNICODE==m_lNameType)
							{
								// this means whatever version of object we are this
								// particular rule has unicode name
#ifdef UNICODE
								long	srcLen = lstrlen(lpSRow->lpProps[I_RULE_NAMEW].Value.LPSZ);
								if(m_lpszTName = new TCHAR[srcLen+1])
								{
									lstrcpy(m_lpszTName,lpSRow->lpProps[I_RULE_NAMEW].Value.LPSZ);
								}
								else
								hr = E_OUTOFMEMORY;
#else
								long	srcLen = lstrlenW(lpSRow->lpProps[I_RULE_NAMEW].Value.lpszW);
								if(m_lpszTName = new char[srcLen+1])
								{
									::WideCharToMultiByte(CP_ACP,0,
														  lpSRow->lpProps[I_RULE_NAMEW].Value.lpszW,-1,
														  m_lpszTName,srcLen+1,NULL,NULL);
								}
								else
									hr = E_OUTOFMEMORY;
#endif
							}
							else
								hr = E_INVALIDARG;
						}
						if(SUCCEEDED(hr))
						{
							if(lpSRow->lpProps[I_RULE_CONDITION].Value.ul)
							{	
								LPSRestriction	lpSRestriction =(LPSRestriction)lpSRow->lpProps[I_RULE_CONDITION].Value.ul;
								if(SUCCEEDED(hr=_Module.CreateResInstance(lpSRestriction->rt,(LPVOID*)&lpCondition)))
								{
									if(m_pCondition=new CConditionPtr(lpCondition))
									{
										if(pCondition=dynamic_cast<CBaseCondition*>(lpCondition))
										{
											hr=pCondition->load(lpSRestriction);
										}
									}
									else
										hr = E_OUTOFMEMORY;
								}
							}
						}
						// not sure if there are no actions, is it a possible sceanrio
						// let us allow it any way, we'll have an empty actions collection
					}
				}
				else
					hr = E_OUTOFMEMORY;
			}
		}
		else
			hr = E_OUTOFMEMORY;
	}
	return hr;
}

HRESULT CRule::pack(LPROWENTRY lpRowEntry, LPVOID lpObject)
{
	long				cRuleProps=0;
	HRESULT				hr=NOERROR;
	CActions			*pActions=NULL;
	LPSPropValue		lpPropVal=NULL;
	CBaseCondition		*pCondition=NULL;

	//	note when we write back to store we write only one property for name
	//	if we are unicode version we write back unicode names, else we write an ASCII
	//	So we need one less property than when we are querying for rules at which time
	//	we try to query for both unicode and ascii strings.

	switch(m_lPersist)
	{
	case PERS_ADD:
		// when adding we are not supposed to populate the RULE_ID property
		// and we would be writing only one RULE_NAME property either ASCII or 
		// unicode so we need only C_RULE_PROPS-2
		cRuleProps = C_RULEPROPS-2;
		break;
	case PERS_MODIFY:
		// when modifying we need to fill in the RULE_ID property properly but
		// we would be writing only one RULE_NAME property either ASCII or 
		// unicode so we need only C_RULE_PROPS-1
		cRuleProps = C_RULEPROPS-1;
		break;
	case PERS_REMOVE:
		// when removing a row just mention the RULE_ID
		cRuleProps = 1;
	}

	if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SPropValue)*cRuleProps,lpObject,
									 (LPVOID*)&(lpRowEntry->rgPropVals))))
    {
		memset(lpRowEntry->rgPropVals,0,sizeof(SPropValue)*cRuleProps);
		lpPropVal = lpRowEntry->rgPropVals;
		lpRowEntry->ulRowFlags = m_lPersist;
		lpRowEntry->cValues = cRuleProps;

		if(PERS_REMOVE==m_lPersist)
		{
			lpPropVal[0].ulPropTag	= 	PR_RULE_ID;
			lpPropVal[0].Value.li	=	m_liRuleId;
			return hr;
		}

		if(m_pActions)
		{
			if(pActions = dynamic_cast<CActions*>(((LPACTIONCOLLECTION)*m_pActions)))
			{
				if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(ACTIONS),lpObject,
								(LPVOID*)&(lpPropVal[I_RULE_ACTIONS].Value.ul))))
				{
					if(SUCCEEDED(hr=pActions->pack((LPACTIONS)lpPropVal[I_RULE_ACTIONS].Value.ul,lpObject)))
					{
						lpPropVal[I_RULE_SEQUENCE].ulPropTag	= 	PR_RULE_SEQUENCE;
						lpPropVal[I_RULE_SEQUENCE].Value.ul		=	m_lSequence;
						lpPropVal[I_RULE_STATE].ulPropTag		=	PR_RULE_STATE;
						lpPropVal[I_RULE_STATE].Value.l			=	m_lState;
						lpPropVal[I_RULE_CONDITION].ulPropTag	=	PR_RULE_CONDITION;
						lpPropVal[I_RULE_ACTIONS].ulPropTag		=	PR_RULE_ACTIONS;
						lpPropVal[I_RULE_LEVEL].ulPropTag		=	PR_RULE_LEVEL;
						lpPropVal[I_RULE_LEVEL].Value.l			=	m_lLevel;

						lpPropVal[I_RULE_PROVIDER].ulPropTag	=	PR_RULE_PROVIDER;
						if(SUCCEEDED(hr=MAPIAllocateMore(lstrlenA(m_lpszAProvider)+1, lpObject, 
														(LPVOID *)&lpPropVal[I_RULE_PROVIDER].Value.lpszA)))
						{
							lstrcpyA(lpPropVal[I_RULE_PROVIDER].Value.lpszA,m_lpszAProvider);
							if((PT_STRING8==m_lNameType)||(PT_UNICODE==m_lNameType))
							{
								if(m_lpszTName)
								{
									lpPropVal[I_RULE_NAME].ulPropTag=PROP_TAG(m_lNameType,PROP_ID(PR_RULE_NAME));
									long	srcLen = lstrlen(m_lpszTName);
									if(PT_STRING8==m_lNameType)
									{
#ifdef UNICODE
										LPSTR	lpStrAName=NULL;
										if(lpStrAName=new char[srcLen+1])
										{
											::WideCharToMultiByte(CP_ACP,0,m_lpszTName,-1,lpStrAName,srcLen+1,NULL,NULL);
											if(SUCCEEDED(hr=MAPIAllocateMore(srcLen+1,lpObject,(LPVOID*)&lpPropVal[I_RULE_NAME].Value.lpszA)))
											{
												m_lNameType = PT_STRING8,
												lstrcpyA(lpPropVal[I_RULE_NAME].Value.lpszA, lpStrAName);
											}
											delete [] lpStrAName;
										}
										else
											hr = E_OUTOFMEMORY;
#else
										if(SUCCEEDED(hr=MAPIAllocateMore((lstrlen(m_lpszTName)+1)*sizeof(TCHAR),lpObject,
																		 (LPVOID*)&lpPropVal[I_RULE_NAME].Value.LPSZ)))
										{
											lstrcpy(lpPropVal[I_RULE_NAME].Value.LPSZ,m_lpszTName);
										}
#endif
									}
									else if(PT_UNICODE==m_lNameType)
									{
#ifdef UNICODE
										if(SUCCEEDED(hr=MAPIAllocateMore((lstrlen(m_lpszTName)+1)*sizeof(TCHAR),lpObject,
																		 (LPVOID*)&lpPropVal[I_RULE_NAME].Value.LPSZ)))
										{
											lstrcpy(lpPropVal[I_RULE_NAME].Value.LPSZ,m_lpszTName);
										}
#else
										LPWSTR	lpStrWName=NULL;
										if(lpStrWName=new wchar_t[srcLen+1])
										{
											::MultiByteToWideChar(CP_ACP,0,m_lpszTName,-1,lpStrWName,srcLen+1);
											if(SUCCEEDED(hr=MAPIAllocateMore((srcLen+1)*sizeof(wchar_t),lpObject,(LPVOID*)&lpPropVal[I_RULE_NAME].Value.lpszW)))
											{
												m_lNameType = PT_UNICODE,
												lstrcpyW(lpPropVal[I_RULE_NAME].Value.lpszW,lpStrWName);
											}
											delete [] lpStrWName;
										}
										else
											hr = E_OUTOFMEMORY;
#endif
									}
								}
							}
							if(SUCCEEDED(hr))
							{
								if(m_pCondition)
								{
									if(pCondition=dynamic_cast<CBaseCondition*>(((LPCONDITION)*m_pCondition)))
									{
										if(SUCCEEDED(hr=MAPIAllocateMore(sizeof(SRestriction),lpObject,
																		 (LPVOID*)&(lpPropVal[I_RULE_CONDITION].Value.ul))))
										{
											hr=pCondition->pack((LPSRestriction)lpPropVal[I_RULE_CONDITION].Value.ul,lpObject);
										}
									}
									else
										hr = E_INVALIDARG;
								}
							}
							if(SUCCEEDED(hr))
							{
								if(PERS_ADD!=m_lPersist)
								{
									lpPropVal[I_RULE_ID].ulPropTag	= 	PR_RULE_ID;
									lpPropVal[I_RULE_ID].Value.li	=	m_liRuleId;
								}
							}
						}
					}
				}
			}
			else
				hr = E_INVALIDARG;
		}
		else
			hr = E_INVALIDARG;
	}
	return hr;
}
