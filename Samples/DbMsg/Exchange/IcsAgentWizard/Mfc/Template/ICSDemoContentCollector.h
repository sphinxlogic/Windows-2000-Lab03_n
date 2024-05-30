/************************************************************************
*                                                                       *
*   $$Root$$ContentCollector.h										*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/


#ifndef $$ROOT$$_CONTENT_COLLECTOR_H
#define $$ROOT$$_CONTENT_COLLECTOR_H
#pragma once

#include "stdafx.h"
#include "$$Root$$Util.h"

class C$$Root$$Synchronizer;

class C$$Root$$ContentCollector : public IExchangeImportContentsChanges
{
private:
	ULONG m_cRef;
public:
	
	C$$Root$$ContentCollector();

	virtual STDMETHODIMP_(ULONG) AddRef();
	virtual STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj);
	virtual STDMETHODIMP_(ULONG) Release();

	STDMETHODIMP GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError);
	STDMETHODIMP Config(LPSTREAM lpStream, ULONG ulFlags);
	STDMETHODIMP UpdateState(LPSTREAM lpStream);
	STDMETHODIMP ImportMessageChange(ULONG cpvalChanges, LPSPropValue	ppvalChanges, ULONG ulFlags, LPMESSAGE *lppmessage);
	STDMETHODIMP ImportMessageDeletion(ULONG ulFlags, LPENTRYLIST lpSrcEntryList);
	STDMETHODIMP ImportPerUserReadStateChange(ULONG cElements, LPREADSTATE lpReadState);
	STDMETHODIMP ImportMessageMove(	ULONG cbSourceKeySrcFolder,
		 							BYTE FAR * pbSourceKeySrcFolder,
		 							ULONG cbSourceKeySrcMessage,
		 							BYTE FAR * pbSourceKeySrcMessage,
		 							ULONG cbPCLMessage,
		 							BYTE FAR * pbPCLMessage,
		 							ULONG cbSourceKeyDestMessage,
		 							BYTE FAR * pbSourceKeyDestMessage,
		 							ULONG cbChangeNumDestMessage,
		 							BYTE FAR * pbChangeNumDestMessage);

	C$$Root$$Synchronizer * m_lpSynchronizer;
};

typedef C$$Root$$ContentCollector * LP$$ROOT$$CONTENTCOLLECTOR;


#endif // #ifndef $$ROOT$$_CONTENT_COLLECTOR_H
