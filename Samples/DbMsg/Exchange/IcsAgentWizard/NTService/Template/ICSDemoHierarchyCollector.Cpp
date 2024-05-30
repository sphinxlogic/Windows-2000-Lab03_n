/************************************************************************
*                                                                       *
*   $$Root$$HierarchyCollector.cpp									*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/


#include "stdafx.h"
#include "$$Root$$HierarchyCollector.h"
#include "$$Root$$Synchronizer.h"


C$$Root$$HierarchyCollector::C$$Root$$HierarchyCollector()
{
	m_cRef = 1;
	m_lpSynchronizer = NULL;
}

STDMETHODIMP C$$Root$$HierarchyCollector::QueryInterface(REFIID riid,LPVOID *ppvObj)
{
	HRESULT hResult = S_OK;

	if (ppvObj)
	{
		*ppvObj = NULL;

		if (riid == IID_IUnknown)
			*ppvObj = this;
		else if (riid == __IID_IExchangeImportHierarchyChanges)
			*ppvObj = this;
		else
			hResult = E_NOINTERFACE;

		if (*ppvObj != NULL)
			((LPUNKNOWN)*ppvObj)->AddRef();
	}
	else
	{
		hResult = E_INVALIDARG;
	}

	return hResult;
}

STDMETHODIMP_(ULONG) C$$Root$$HierarchyCollector::AddRef()
{
	++m_cRef;
	return m_cRef;
}

STDMETHODIMP_(ULONG) C$$Root$$HierarchyCollector::Release()
{
	ULONG ulCount = --m_cRef;
	
	if (!ulCount)
	{
		delete this;
	}
	
	return ulCount;
}

STDMETHODIMP C$$Root$$HierarchyCollector::GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError)
{
	// C$$Root$$HierarchyCollector is derived from IExchangeImportHierarchyChanges
	// Please refer documentation for IExchangeImportHierarchyChanges::GetLastError for further details
	// Insert custom code here
	
	return S_OK;
}

STDMETHODIMP C$$Root$$HierarchyCollector::Config(LPSTREAM lpStream, ULONG ulFlags)
{
	// C$$Root$$HierarchyCollector is derived from IExchangeImportHierarchyChanges
	// Please refer documentation for IExchangeImportHierarchyChanges::Config for further details
	// Insert custom code here
	
	return S_OK;
}

STDMETHODIMP C$$Root$$HierarchyCollector::UpdateState(LPSTREAM lpStream)
{
	// C$$Root$$HierarchyCollector is derived from IExchangeImportHierarchyChanges
	// Please refer documentation for IExchangeImportHierarchyChanges::UpdateState for further details
	// Insert custom code here

	return S_OK;
}

STDMETHODIMP C$$Root$$HierarchyCollector::ImportFolderChange(ULONG cValue, LPSPropValue lpPropArray)
{
	// C$$Root$$HierarchyCollector is derived from IExchangeImportHierarchyChanges
	// Please refer documentation for IExchangeImportHierarchyChanges::ImportFolderChange for further details
	// Insert custom code here

	return S_OK;
}


STDMETHODIMP C$$Root$$HierarchyCollector::ImportFolderDeletion(ULONG ulFlags, LPENTRYLIST lpSourceEntryList)
{
	// C$$Root$$HierarchyCollector is derived from IExchangeImportHierarchyChanges
	// Please refer documentation for IExchangeImportHierarchyChanges::ImportFolderDeletion for further details
	// Insert custom code here

	return S_OK;
}

