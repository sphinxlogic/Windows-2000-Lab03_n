
/******************************************************************************\
********************************************************************************
* Filename: dispimpl.cpp
*
* Description: main implementation of IDispenserDriver
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
#include "..\..\..\common\inc\TxFileDisp.h"
#include "..\..\..\common\inc\copyfilerm.h"
#include "mtxdm.h"
#include "txcoord.h"
#include "FileRmPxy.h"
#include "txdtc.h"
#include "xolehlp.h"


//
//	called by RDM (Resource Dispenser Manager) when it is time to create
//	a new resource, in this case a connection to the CopyFileRM
//	
STDMETHODIMP CFileRmPxy::CreateResource
(
	/*[in]*/  const RESTYPID ResTypId,	
	/*[out]*/ RESID* pResId, 
	/*[out]*/ TIMEINSECS* pSecsFreeBeforeDestroy
)
{

	ATLTRACE(_T("Creating TxFile Resource\n"));
	CComBSTR sAppName = L"TxFileDispenser";
	long lHandle;
	HRESULT hr;

	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
	{
		_ASSERTE(0);
		return E_UNEXPECTED;
	}
	hr = pRm -> Connect(sAppName.m_str, (long *)&lHandle);
	if (FAILED(hr))
	{
		_ASSERTE(0);
		SafeRelease(pRm);
		return hr;
	}

	*pResId = (RESID)lHandle;
	//
	//	set a 60 second time out
	//
	*pSecsFreeBeforeDestroy = 60; 

	//
	//	save the connection in our set of connections
	//
	m_set.insert(lHandle);

	SafeRelease(pRm);
	return S_OK;
}
//
//	called by RDM (Resource Dispenser Manager) when it is time
//	to rate an already created resource
//
STDMETHODIMP CFileRmPxy::RateResource
(	
	/*[in]*/  const RESTYPID ResTypId,
	/*[in]*/  const RESID ResId,
	/*[in]*/  const BOOL fRequiresTransactionEnlistment,
	/*[out]*/ RESOURCERATING* pRating
)
{
	ATLTRACE(_T("Rating resource\n"));

	// if it is already enlisted on the right transaction, use it
	if (fRequiresTransactionEnlistment == FALSE) 
	{
		*pRating = 100;			
	}
	else
	{
		// not enlisted
		*pRating = 50;
	}
	return S_OK;
}

//
//	called by RDM (Resource Dispenser Manager) when it is time
//	when it is time to enlist a connection on a resource
//
STDMETHODIMP CFileRmPxy::EnlistResource
(
	/*[in]*/  const RESID ResId,
	/*[in]*/  const TRANSID TransId
)
{

	//
	//	there are 3 kinds of resources in the pool:
	//	1. Enlisted resources
	//	2. Un-enlisted resources
	//	3. previously enlisted resources
	//
	//	type (3) resources require Re-enlistment or "Unenlistment" to be used
	//	again.  Dispman asks us to Unenlist a resource by passing in a NULL
	//	TransId
	//	
	//	The CopyFileRm ALWAYS resets the state for the Worker (ie the resource being
	//	dispensed)	to an "uninitialized" state -- and any work on a uninitialized worker object
	//	immediately fails.  so "Unenlistement" is a noop for us (SQL Server, btw, allows work to be done 
	//  with or without a tx, so their implementation is different) 
	//  

	
	if (!TransId)
		return S_OK;


	ATLTRACE(_T("Enlisting Resource\n"));
	ITransaction * pTransaction = (ITransaction *)TransId;

	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;

	HRESULT hr;
	ITransactionExport *pExport;


	pExport = m_mapExport[ResId];
	if (pExport == NULL)
	{
	
		hr = GetExportObject(ResId, pTransaction, &pExport);
		if (FAILED(hr))
		{
			SafeRelease(pRm);
			return hr;
		}

		m_mapExport[ResId] = pExport;
	}

	ULONG						cbTransactionCookie = 0;
	BYTE						*rgbTransactionCookie;
	ULONG						cbUsed;


	// Get transaction cookie
	hr = pExport->Export (pTransaction, &cbTransactionCookie);
	_ASSERTE(hr == S_OK);


	rgbTransactionCookie = (BYTE *) CoTaskMemAlloc (cbTransactionCookie);
	_ASSERTE (0 != rgbTransactionCookie);
	if (0 == rgbTransactionCookie)
	{
		SafeRelease(pRm);
		_ASSERTE(0);
		return E_FAIL;
	} // if

	hr = pExport->GetTransactionCookie (pTransaction, 
										cbTransactionCookie,
										rgbTransactionCookie,
										&cbUsed);
	
	//
	//	ExportTx will also enlist in the Tx
	//
	//
	//	NOTE:  There is a functionaly requirement that makes this call block
	//		   if the connection is not completely finished committing or aborting
	//			the previous transaction
	//
	hr = pRm->ExportTx (ResId, cbUsed, rgbTransactionCookie);

	CoTaskMemFree (rgbTransactionCookie);	
	SafeRelease(pRm);
 	return hr;
	
}

//
//	called by RDM (Resource Dispenser Manager) when it is time
//	to reset the resouce -- ie it is being returned to the inactive
//	pool.  you should generally clean up connection specific state
//	here.
//
STDMETHODIMP CFileRmPxy::ResetResource
(
	/*[in]*/  const RESID ResId
)
{
	ATLTRACE(_T("Resetting resource\n"));
	HRESULT hr = E_FAIL;	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;
	hr = pRm -> ResetConnection((long)ResId);
	SafeRelease(pRm);
	_ASSERTE(hr == S_OK);

	//
	//	if you return S_FALSE, then the resource
	//	is destroyed emmediately
	//
	return hr;
}
//
//	called by RDM (Resource Dispenser Manager) when it is time
//	to destroy the resource
//
STDMETHODIMP CFileRmPxy::DestroyResource 
(
	/*[in]*/  const RESID ResId
)
{	

	ATLTRACE(_T("Destroying a resource\n"));
	HRESULT hr = E_FAIL;	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;

	hr = pRm -> Disconnect((long )ResId);
	ULONG ulRefcount  = pRm -> Release();
	pRm = NULL;

	ITransactionExport			*pExport;
	pExport = m_mapExport[ResId];
	int nElements = m_mapExport.erase(ResId);
	_ASSERTE(nElements == 1);
	SafeRelease(pExport);
	
	// remove it from our set
	m_set.erase(ResId);
	_ASSERTE(hr == S_OK);
	return hr;
}

STDMETHODIMP CFileRmPxy::DestroyResourceS
(
	/*[in]*/  constSRESID ResId
)
{
	return E_NOTIMPL;
}

//
//	called by the framework during the IClassFactory::CreateInstance()
//	method...this is a good place to initialize because the object is
//	fully created, and you can propagate an error code back to the user
//
HRESULT CFileRmPxy::FinalConstruct()
{
	HRESULT hr;

	hr = GetDispenserManager(&m_pDispMan);
	if (SUCCEEDED(hr))
	{

		// we are running under MTS
		IDispenserDriver * pDriver;
		hr = GetUnknown()->QueryInterface(IID_IDispenserDriver, (void **)&pDriver);
		_ASSERTE(hr == S_OK);
		hr = m_pDispMan -> RegisterDispenser(pDriver, L"TxFileDispenser", &m_pHolder);		
		_ASSERTE(hr == S_OK);
		//
		//	WATCH OUT HERE!!!!!!!!
		//	
		//	there is a bug in MTS 1.x that was found post ship where the pDriver isn't 
		//	properly AddRef()'d.  In a future version of MTS, we will have a new 
		//	RegisterDispenser() API (e.g. something like RegisterDispenser2()
		//	that will do this correctly.  In the meantime, treat
		//	this as a "moved" reference, and do not release the pDriver pointer!
		//	(all future versions of RegisterDispenser() will behave this way for
		//	backward compatiblity)
		
	}
	//
	// get a connection to the RM -- the RM is a singleton object, so we will always get the same
	// pointer back from CoCreateInstance
	//
	hr = CoCreateInstance(CLSID_CoFileRm, NULL, CLSCTX_LOCAL_SERVER, IID_IFileRm , (void **)&m_pRm);	
	if (FAILED(hr))
	{
		_ASSERTE(0);
		return hr;
	}

	//
	//	NT SP3 has added support for the "Global Interface Table"
	//	which we use to get a proxy valid on any thread (see the WIN32
	//	SDK docs for more info)
	//
	m_dwRmPtrCookie = 0;
	hr = CoCreateInstance(CLSID_StdGlobalInterfaceTable,
                                NULL,
                                CLSCTX_INPROC_SERVER,
                                IID_IGlobalInterfaceTable,
                                (void **)&m_pGIT);
	_ASSERT(SUCCEEDED(hr));
	if (m_pGIT)
    {
        // register our interface and get a cookie
		hr = m_pGIT->RegisterInterfaceInGlobal(m_pRm, IID_IFileRm, &m_dwRmPtrCookie);
		_ASSERT(SUCCEEDED(hr));
    }
	
	//
	//	aggregate in the free threaded marshaler
	//	this is ABSOLUTELY CRITICAL to do in a resource dispenser!
	//	if we take a thread switch because we switched apartments, 
	//	we will loose the object context and the resource dispenser 
	//	manager will think that there is no	transaction, 
	//	and EnlistResource() will not be called.
	//
	//	NOTE:	you should mark all resource dispensers as "Both" in the registy
	//			(see the FileRmPxy.rgs files)
	//

	hr = CoCreateFreeThreadedMarshaler(GetUnknown(), &m_pFreeThreadedMarshaler);
	_ASSERTE(hr == S_OK);

	return hr;
}
//
//	this is called by the framework when my reference count is going from 1 to 0
//
void CFileRmPxy::FinalRelease()
{

	ATLTRACE(_T("\nCFileRmPxy::FinalRelease()\n"));
	HRESULT hr;
	if (m_pGIT && m_dwRmPtrCookie)
	{		
		hr =m_pGIT->RevokeInterfaceFromGlobal(m_dwRmPtrCookie);
		if (FAILED(hr))
		{			
			USES_CONVERSION;
			char * szFile = __FILE__;			
			ATLTRACE(_T("RevokeInterfaceFromGlobal() failed on line %ld of file %s.\n\nError Code %lx"), __LINE__, A2W(szFile) , hr);
		}
		SafeRelease(m_pGIT);
		m_dwRmPtrCookie = 0;
	}
	m_dwRmPtrCookie = 0;	
	SafeRelease(m_pDispMan);
	SafeRelease(m_pHolder);
	SafeRelease(m_pRm);
	SafeRelease(m_pFreeThreadedMarshaler);

}
//
//	GetFileRmPointer:
//
//	use the Global Interface Table to get a proxy valid on any thread
//
IFileRm * CFileRmPxy::GetFileRmPointer()
{

	IFileRm * pRm =NULL;
	HRESULT hr;
	hr = m_pGIT->GetInterfaceFromGlobal(m_dwRmPtrCookie, IID_IFileRm, (void **)&pRm);	
	_ASSERTE(pRm);
	return pRm;

}
//
//	helper function to get an ITransactionExport pointer
//
HRESULT CFileRmPxy::GetExportObject(long ResId, ITransaction * pTransaction, ITransactionExport **ppExport)
{
	*ppExport = NULL;

	
	ULONG						cbWhereabouts = 0;
	BYTE						*rgbWhereabouts = NULL;
	HRESULT						hr;
	ITransactionExportFactory	*pTxExpFac;
	IGetDispenser				*pIDispenser;

	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;

	//
	//	GetTmWhereabouts finds the PHYSICAL location of the RM..if you know that
	//	you will only ever be connecting to one RM, you can get the Whereabouts ONCE
	//	and store it to be used with multiple connections.
	//
	//	here we actually get it each time, in order to show the generalized process
	//

	hr = pRm->GetTmWhereabouts (ResId, &rgbWhereabouts, &cbWhereabouts);
	if (S_OK != hr)
	{
		SafeRelease(pRm);
		_ASSERTE(hr == S_OK);
		return hr;
	} // if

	hr = pTransaction->QueryInterface (IID_IGetDispenser, (LPVOID *) &pIDispenser);
	if (S_OK != hr)
	{		
		SafeRelease(pRm);
		_ASSERTE(0);
		return hr;
	} // if

	hr = pIDispenser->GetDispenser (IID_ITransactionExportFactory, 
									 (LPVOID *) &pTxExpFac );
	SafeRelease(pIDispenser);
	if (S_OK != hr)
	{
		_ASSERTE(0);
		SafeRelease(pRm);
		return hr;
	} // if

	
	hr = pTxExpFac->Create (cbWhereabouts, rgbWhereabouts, ppExport);
	SafeRelease(pTxExpFac);		
	if (S_OK != hr)
	{			
		SafeRelease(pRm);
		_ASSERTE(0);
		return hr;	
	} // if

	CoTaskMemFree (rgbWhereabouts);		
	SafeRelease(pRm);
	return hr;

}
