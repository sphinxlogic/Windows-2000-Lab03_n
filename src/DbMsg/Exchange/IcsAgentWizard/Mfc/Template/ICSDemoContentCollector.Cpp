/************************************************************************
*                                                                       *
*   $$Root$$ContentCollector.cpp									*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#include "stdafx.h"
#include "$$Root$$ContentCollector.h"
#include "$$Root$$Synchronizer.h"

C$$Root$$ContentCollector::C$$Root$$ContentCollector()
{
	m_cRef = 1;
	m_lpSynchronizer = NULL;
}

STDMETHODIMP C$$Root$$ContentCollector::QueryInterface(REFIID riid,LPVOID *ppvObj)
{
	HRESULT hResult = S_OK;

	*ppvObj = NULL;

	if (riid == IID_IUnknown)
		*ppvObj = (C$$Root$$ContentCollector *)this;
	else if (riid == __IID_IExchangeImportContentsChanges)
		*ppvObj = (C$$Root$$ContentCollector *)this;
	else
		hResult = E_NOINTERFACE;

	if (*ppvObj != NULL)
		((LPUNKNOWN)*ppvObj)->AddRef();

	return hResult;
}

STDMETHODIMP_(ULONG) C$$Root$$ContentCollector::AddRef()
{
	++m_cRef;
	return m_cRef;
}

STDMETHODIMP_(ULONG) C$$Root$$ContentCollector::Release()
{
	ULONG ulCount = --m_cRef;
	
	if (!ulCount)
	{
		delete this;
	}
	
	return ulCount;
}


STDMETHODIMP C$$Root$$ContentCollector::GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::GetLastError for further details
	// Insert custom code here to take action on this last error

	return S_OK;
}

STDMETHODIMP C$$Root$$ContentCollector::Config(LPSTREAM lpStream, ULONG ulFlags)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::Config for further details
	// Insert custom code here
	
	return S_OK;
}

STDMETHODIMP C$$Root$$ContentCollector::UpdateState(LPSTREAM lpStream)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::UpdateState for further details
	// Insert custom code here

	return S_OK;
}

STDMETHODIMP C$$Root$$ContentCollector::ImportMessageChange(ULONG cpvalChanges, LPSPropValue ppvalChanges, ULONG ulFlags, LPMESSAGE *lppMessage)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::ImportMessageChange for further details
	// Insert custom code here

	return S_OK;
}

STDMETHODIMP C$$Root$$ContentCollector::ImportMessageDeletion(ULONG ulFlags, LPENTRYLIST lpSrcEntryList)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::ImportMessageDeletion for further details
	// Insert custom code here

	return S_OK;
}

STDMETHODIMP C$$Root$$ContentCollector::ImportPerUserReadStateChange(ULONG cElements, LPREADSTATE lpReadState)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::ImportPerUserReadStateChange for further details
	// Insert custom code here

	return S_OK;
}

STDMETHODIMP C$$Root$$ContentCollector::ImportMessageMove(	ULONG cbSourceKeySrcFolder,
		 										BYTE FAR * pbSourceKeySrcFolder,
		 										ULONG cbSourceKeySrcMessage,
		 										BYTE FAR * pbSourceKeySrcMessage,
		 										ULONG cbPCLMessage,
		 										BYTE FAR * pbPCLMessage,
		 										ULONG cbSourceKeyDestMessage,
		 										BYTE FAR * pbSourceKeyDestMessage,
		 										ULONG cbChangeNumDestMessage,
		 										BYTE FAR * pbChangeNumDestMessage)
{
	// C$$Root$$ContentCollector is derived from IExchangeImportContentsChanges
	// Please refer documentation for IExchangeImportContentsChanges::ImportMessageMove for further details
	// Insert custom code here

	return S_OK;
}
