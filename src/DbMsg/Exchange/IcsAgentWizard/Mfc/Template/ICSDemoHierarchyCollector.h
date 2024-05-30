/************************************************************************
*                                                                       *
*   $$Root$$HierarchyCollector.h									*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#ifndef $$ROOT$$_HIERARCHY_COLLECTOR_H
#define $$ROOT$$_HIERARCHY_COLLECTOR_H
#pragma once

#include "stdafx.h"
#include "$$Root$$Util.h"

class C$$Root$$Synchronizer;

class C$$Root$$HierarchyCollector : public IExchangeImportHierarchyChanges
{
private:
	ULONG m_cRef;
public:
	
	C$$Root$$Synchronizer * m_lpSynchronizer;

	C$$Root$$HierarchyCollector();

	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP QueryInterface(REFIID riid, LPVOID * ppvObj);
	STDMETHODIMP_(ULONG) Release();

	STDMETHODIMP GetLastError(HRESULT hResult, ULONG ulFlags, LPMAPIERROR FAR * lppMAPIError);
	STDMETHODIMP Config(LPSTREAM lpStream, ULONG ulFlags);
	STDMETHODIMP UpdateState(LPSTREAM lpStream);
	STDMETHODIMP ImportFolderChange(ULONG cValue, LPSPropValue	lpPropArray);
	STDMETHODIMP ImportFolderDeletion(ULONG ulFlags, LPENTRYLIST lpSrcEntryList);
};

typedef C$$Root$$HierarchyCollector * LP$$ROOT$$HIERARCHYCOLLECTOR;

#endif // #ifndef $$ROOT$$_HIERARCHY_COLLECTOR_H
