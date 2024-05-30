
/******************************************************************************\
********************************************************************************
* Filename: MtsUserEventData.cpp
*
* Description:  Implementation of CMtsUserEventData -- uses a linked list
*				to maintain named-valued pairs
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

#include "stdafx.h"
#include "MtsUserEventObj.h"
#include "MtsUserEventData.h"
#include "mtsevents_i.c"

/////////////////////////////////////////////////////////////////////////////
// CMtsUserEventData
CMtsUserEventData::~CMtsUserEventData()
{

	NameValueList::iterator item;
	CNameValue * pNV;
	for (item = m_list.begin(); item != m_list.end(); ++item)
	{			
							
		pNV = *item;	
		if (pNV)
			delete pNV;
	}

	m_list.clear();

}

STDMETHODIMP CMtsUserEventData::put_DisplayName(BSTR newVal)
{
	m_sDisplayName = newVal;
	return S_OK;
}

STDMETHODIMP CMtsUserEventData::put_GuidEventId(BSTR newVal)
{
	
	m_sEventID = newVal;
	return S_OK;
}

STDMETHODIMP CMtsUserEventData::put_Value(BSTR sKey, VARIANT * newVal)
{
	CNameValue * pNV = new CNameValue(sKey, newVal);
	m_list.push_back(pNV);
	return S_OK;
}


STDMETHODIMP CMtsUserEventData::get_DisplayName(BSTR * sDisplayName)
{
	*sDisplayName = m_sDisplayName.Copy();
	return S_OK;
}
STDMETHODIMP CMtsUserEventData::get_EventID(BSTR * sGuidEventID)
{
	*sGuidEventID = m_sEventID.Copy();
	return S_OK;
}

STDMETHODIMP CMtsUserEventData::get_Count(long * lCount)
{
	*lCount = m_list.size();
	return S_OK;
}

STDMETHODIMP CMtsUserEventData::get_Value(BSTR sKey, VARIANT * pVal)
{
	
	NameValueList::iterator item;
	CNameValue * pNV;
	for (item = m_list.begin(); item != m_list.end(); ++item)
	{			
							
		pNV = *item;	
		if (lstrcmpi(pNV -> m_sName, sKey) == 0)
		{
			VariantInit(pVal);
			pVal -> vt = VT_BSTR;
			pVal -> bstrVal = ::SysAllocString(pNV -> m_sValue.bstrVal);
			break;
		}
		
	}
	
	return S_OK;
}

STDMETHODIMP CMtsUserEventData::get_Names(IUnknown ** pUnk)
{
	long lCount = m_list.size();	
	LPOLESTR *var = new LPOLESTR[lCount];
	int i =0;
	NameValueList::iterator item;
	CNameValue * pNV;
	for (item = m_list.begin(); item != m_list.end(); ++item)
	{			
							
		pNV = *item;			
		var[i]  = pNV->m_sName;
		i++;
	}		

	_ASSERTE(i == lCount);
	typedef CComObject<CComEnum<IEnumString, &IID_IEnumString, LPOLESTR,
		_Copy<LPOLESTR> > > enumvar;
	enumvar* p = new enumvar;
	p->Init(&var[0], &var[i], NULL, AtlFlagCopy);	 // make copies
	delete [] var;
	return p->QueryInterface(IID_IUnknown, (void**)pUnk);	
}
