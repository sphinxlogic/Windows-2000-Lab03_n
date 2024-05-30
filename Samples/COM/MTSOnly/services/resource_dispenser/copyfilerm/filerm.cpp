
/******************************************************************************\
********************************************************************************
* Filename: FileRm.cpp
*
* Description: Implementation of CFileRm
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
#include "txdtc.h"
#include "txcoord.h"
#include "xolehlp.h"
#include "..\..\..\common\inc\CopyFileRm.h"
#include "..\..\..\common\inc\rmworker.h"
#include "..\..\..\common\inc\simplelog.h"
#include "rmoptions.h"
#include "FileRm.h"
#include "rmdlg.h"
#define IID_DEFINED
#include "..\..\..\common\inc\rmworker_i.c"

#include "rmsink.h"
#include "RmOptionsDlg.h"

#define CHECK_TM_DOWN() {	if (IsTMDown())	{		if (InitializeRm() == S_OK)			TmUp();		else 			return	XACT_E_TMNOTAVAILABLE; 	}}

//
//	a worker thread function to check if the TM comes back up
//

DWORD WINAPI TMDownWorkerThread( LPVOID pData);


//
//	Normally if you want to have multiple instances of an RM, you would log a guid 
//	for each RM instance and reuse it for recovery
//

static GUID CopyFileRmGuid = 
	{ 0xf3ffa31a, 0x860a, 0x11d0, { 0xb1, 0x71, 0x0, 0xaa, 0x0, 0xba, 0x32, 0x58 } };


long glWorkers = 0;

STDMETHODIMP CFileRm::Connect(BSTR sAppName, long * ulConnHandle)
{
	
	CHECK_TM_DOWN();

	HRESULT hr; 
	IRmWorker * pWorker = NULL;
	hr = CoCreateInstance(CLSID_CRmWorkerObj, NULL, CLSCTX_SERVER, IID_IRmWorker , (void **)&pWorker);
	if (FAILED(hr))
	{
		_ASSERTE(0);
		return hr;
	}
	hr = pWorker -> Init((IUnknown *)m_pLog, (IUnknown *)m_pIResMgr, (IUnknown *)m_punkDTC, m_options.GetRecDir());
	if (FAILED(hr))
	{
		_ASSERTE(0);
		pWorker -> Release();
		return hr;
	}

	InterlockedIncrement(&glWorkers);
	if (_Module.m_dlg)
		_Module.m_dlg->SetUsageCount(glWorkers);

	*ulConnHandle = (long) pWorker;
	m_setWorkers.insert(*ulConnHandle);
	return S_OK;
}
//
//	Disconnect() works even if the TM is down, so we
//	don't use the GetWorker() method
//
STDMETHODIMP CFileRm::Disconnect(long ulConnHandle)
{
	
	IRmWorker * pWorker  = NULL;
	pWorker = (IRmWorker *)(*m_setWorkers.find(ulConnHandle));	
	if (!pWorker)
	{
		return E_FAIL;
	}
	ULONG lRef = pWorker -> Release();
	pWorker = NULL;	
	InterlockedDecrement(&glWorkers);
	if (_Module.m_dlg)
		_Module.m_dlg->SetUsageCount(glWorkers);

	int nEraseCount = m_setWorkers.erase(ulConnHandle);
	_ASSERTE(nEraseCount == 1);
	return S_OK;
}
//
//	the whereabouts is the same for every worker, and is fixed for every instance
//	of the RM
//
STDMETHODIMP CFileRm::GetTmWhereabouts(long lConHandle, BYTE **rgbTmAddr, ULONG *pcbTmAddr)
{
	
	//
	//	NOTE:  this is handle independent!
	//
	
	CHECK_TM_DOWN();
	HRESULT hr = S_OK;
	if (!m_cbTmAddr)
	{
		
		hr = GetMyTmWhereAbouts();
		if (FAILED(hr))
			return hr;
	}

	*pcbTmAddr = m_cbTmAddr;
	*rgbTmAddr = (BYTE *) CoTaskMemAlloc (m_cbTmAddr);
	memcpy(*rgbTmAddr, m_rgbTmAddr, m_cbTmAddr);
	return hr;
}
STDMETHODIMP CFileRm::ExportTx(long lConHandle, ULONG cbTranCookie, BYTE *rgbTranCookie)
{
	
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}
	HRESULT hr = pWorker ->ExportTx(cbTranCookie, rgbTranCookie);	
	return  hr;
}

STDMETHODIMP CFileRm::FileCopyTx(long lConHandle, BSTR sSource, BSTR sDestination, BOOL bFailIfExists)
{
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	HRESULT hr =pWorker -> FileCopyTx(sSource, sDestination, bFailIfExists);		
	return hr;
}

STDMETHODIMP CFileRm::FileRenameTx(long lConHandle, BSTR sSource, BSTR sDestination)
{
			
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	HRESULT hr =pWorker -> FileRenameTx(sSource, sDestination);		
	return hr;
}

STDMETHODIMP CFileRm::AddFile(long lConHandle, BSTR sSource, BSTR sDestination)
{
	
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	HRESULT hr =pWorker -> AddFile(sSource, sDestination);
	return  hr;	
}

STDMETHODIMP CFileRm::CopyListTx(long lConHandle)
{
	
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	HRESULT hr =  pWorker -> CopyListTx();
	return  hr;	
}



STDMETHODIMP CFileRm::FileMoveTxt(long lConHandle, BSTR sSource, BSTR sDestination)
{
	
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	HRESULT hr =  pWorker -> FileMoveTxt(sSource, sDestination);	
	return  hr;	
}

STDMETHODIMP CFileRm::FileDeleteTx(long lConHandle, BSTR sFileName)
{
	
	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	HRESULT hr =  pWorker -> FileDeleteTx(sFileName);	
	return  hr;	

}


STDMETHODIMP CFileRm::ResetConnection(long lConHandle)
{

	CHECK_TM_DOWN();
	IRmWorker * pWorker = GetWorker(lConHandle);
	if (!pWorker)
	{
		return E_INVALIDARG;
	}

	return pWorker -> Reset();
	
}
//
//	FinalConstruct()
//
//
HRESULT CFileRm::FinalConstruct()
{
	HRESULT hRes;
	hRes = OpenLog();
	if (hRes == S_OK)
	{
		hRes = InitializeRm();
		{
			if (hRes == S_OK)
				hRes = Recover();
		}
	}
	return hRes;
}


//
// Perform any required recovery.
//
HRESULT CFileRm::Recover()
{
	Lock();
	IStorage * pStorage = NULL;
	long lCount = 0;
	HRESULT hr;
	hr = m_pLog -> RecoveryInfo(&pStorage);
	if (FAILED(hr))
	{	
		Unlock();
		return hr;
	}

	IRmWorker * pWorker = NULL;
	hr = CoCreateInstance(CLSID_CRmWorkerObj, NULL, CLSCTX_SERVER, IID_IRmWorker , (void **)&pWorker);
	if (FAILED(hr))
	{
		Unlock();
		return hr;
	}

	BSTR sRecDir = m_options.GetRecDir();
	_ASSERTE(sRecDir);
	hr = pWorker -> Init(m_pLog, m_pIResMgr, m_punkDTC, sRecDir);
	if (FAILED(hr))
	{
		Unlock();
		return hr;
	}
	hr = pWorker -> Recover(pStorage);
	Unlock();
	SafeRelease(pWorker);	
	return hr;
}


HRESULT CFileRm::InitializeRm()
{
	HRESULT					hr = E_FAIL;
	IResourceManagerFactory	*pIRmFactory	= NULL;
	
	//
	// we make have a call to this originating from the Resource Dispenser
	// and while we are in the call, the worker thread wakes up and calls it again
	//

	Lock(); 

	if (m_punkDTC)	
	{
		Unlock();
		return S_OK;	// while we were Locked, somebody successfully finished
	}

	//
	// Establish contact with the MS DTC transaction manager.  
	// 
	
	
	hr = DtcGetTransactionManager (NULL,
									NULL,
									IID_IUnknown,
									0,
									0,
									0,
									(LPVOID *) &m_punkDTC);
	if (S_OK != hr)
	{
		
		Unlock();
		return hr;

	} 

	//
	//	if I wan't caching the IUnknown * of DTC, I could ask for this
	//	interface directly from the DtcGetTransactionManager API, and 
	//	avoid the QI
	//
	hr = m_punkDTC->QueryInterface(IID_IResourceManagerFactory,
								    (LPVOID *) &pIRmFactory);
	
	_ASSERTE(hr == S_OK); // this can never fail


	CComObject<CResourceManagerSink> * pSink = NULL;
	hr = CComObject<CResourceManagerSink>::CreateInstance(&pSink);

	pSink -> SetRm((IFileRm *)this);

	IResourceManagerSink * pISink = NULL;
	pSink -> QueryInterface(IID_IResourceManagerSink, (void **)&pISink);
	_ASSERTE(pISink);

	// Create instance of the resource manager interface.
	hr = pIRmFactory->Create (&CopyFileRmGuid, 
							   "CopyFileRm", 
							   pISink, 
							   &m_pIResMgr );
	//
	//	DTC owns the reference (and lifetime) to the IResourceManagerSink interface
	//

	SafeRelease(pSink);

	if (FAILED(hr))
	{
		SafeRelease(m_punkDTC);		

	}
	
	SafeRelease(pIRmFactory);
	
	Unlock();
	return hr;	



}


HRESULT CFileRm::OpenLog()
{


	_Module.m_dlg = new CRmDlg(&m_options);
	_ASSERTE(_Module.m_dlg);
	HWND hWnd = _Module.m_dlg -> Create(NULL);
	_Module.m_dlg->ShowWindow(SW_SHOWNORMAL);
	_Module.m_dlg->SetUsageCount(1);
	_ASSERTE(hWnd);

	m_pLog = NULL;
	HRESULT hr; 
	hr = CoCreateInstance(CLSID_CoSimpleLog, NULL, CLSCTX_SERVER, IID_ISimpleLog , (void **)&m_pLog);
	if (FAILED(hr))
	{
		return hr;
	}
	
	CComBSTR sFileName = m_options.GetLogDir();
	_ASSERTE(sFileName.m_str);
	sFileName += L"FileRmLog";
	hr = m_pLog -> Init(sFileName);
	if (FAILED(hr))
		return hr;

	return hr;
}

HRESULT CFileRm::FinalRelease()
{
	SafeRelease(m_punkDTC);
	SafeRelease(m_pIResMgr);
	return S_OK;
}
//
//	the resource Manager's TM goes down
//
//	we need to 
//	1. set a global variarable so we won't except any new connections
//	2. free all RmWorkers (make sure they have a TMDown() event already
//	3. start a worker thread and ping DTC until it comes up
//	4. when DTC comes back up, do recovery and then accept new connections
//
//	NOTE:  You should NEVER block a DTC thread!	
//
STDMETHODIMP CFileRm::TMDown()
{
	
	
	m_bTMDown = TRUE;
	WorkerSet::iterator item = m_setWorkers.begin();
	IRmWorker * pWorker;
	while (item != m_setWorkers.end())
	{
		pWorker = (IRmWorker *)(*item); // get the value
		//
		//	if the Worker object was enlisted in DTC, then we
		//	are GUARANTEED that they will have gotten the TMDown()
		//	before the RM gets the TMDown(), but I want to make sure
		//	that all Workers get the TMDown, not just the enlisted ones.
		//	my implementation of TMDown() doesn't care if it is called 
		//	twice, so rather than check the state and call TMDown on the
		//	ones that haven't gotten it yet, I'll call it for all workers
		//
		
		if (pWorker)
			pWorker -> TMDown(); 
		else
			m_setWorkers.erase(item++);

		item++;
	}
	if (m_cbTmAddr)
	{
		delete m_rgbTmAddr;
		m_cbTmAddr = 0;
	}

	SafeRelease(m_punkDTC);
	SafeRelease(m_pIResMgr);
	SafeRelease(m_pLog);
	
	DWORD dwThreadID;
	HANDLE hThread;
	hThread = CreateThread(NULL, 0, TMDownWorkerThread, (LPVOID)this, NULL, &dwThreadID);
	return S_OK;
}

//
//	Worker Thread that waits for the RM to come back up
//	
DWORD WINAPI TMDownWorkerThread( LPVOID pData)
{
	
	
	CFileRm * pRm = (CFileRm *)pData;
	BOOL bGo= TRUE;
	DWORD dwSleepTime = 1000 * 10; 

	
	while (bGo)
	{

		if (pRm -> InitializeRm() == S_OK)
			bGo = FALSE;

		Sleep(dwSleepTime);

	}


	HRESULT hRes;
	hRes = pRm -> TmUp();
	return hRes;

}
//
//	called after the TM goes down -- resets everything to a good state
//
//
HRESULT CFileRm::TmUp()
{


	HRESULT hRes;
	hRes = OpenLog();
	if (SUCCEEDED(hRes))
	{
		hRes = Recover();	
	}
	if (SUCCEEDED(hRes))
	{
		_ASSERTE(GetLog());
		_ASSERTE(GetIResourceManager());
		_ASSERTE(GetDTCUnknown());

		SetTMDown(FALSE);
		WorkerSet::iterator item = m_setWorkers.begin();
		IRmWorker * pWorker;
		while (item != m_setWorkers.end())
		{
			pWorker = (IRmWorker *)(*item); // get the value
			hRes = pWorker -> Init((IUnknown *)GetLog(), (IUnknown *)GetIResourceManager(), GetDTCUnknown(), m_options.GetRecDir());
			_ASSERTE(hRes == S_OK);//this really can't fail...
			item++;
		}

	}

	hRes = GetMyTmWhereAbouts();	
	
	return hRes;

}


HRESULT CFileRm::GetMyTmWhereAbouts()
{

	_ASSERTE(GetLog());
	_ASSERTE(GetIResourceManager());
	_ASSERTE(GetDTCUnknown());
	ULONG	cbUsed = 0;

	ITransactionImportWhereabouts	*pITxWhere = 0;

	// Ensure that the resource manager is initializing

	// Get a pointer to the ITransactionWhereabouts interface.
	HRESULT hRc = m_punkDTC->QueryInterface (IID_ITransactionImportWhereabouts,
									 (LPVOID *) &pITxWhere);
	_ASSERTE (S_OK == hRc);
	if (S_OK != hRc)
	{
		pITxWhere = 0;		
		return hRc;
	} // if

	// Get the size of the whereabouts blob for the TM
	pITxWhere->GetWhereaboutsSize (&m_cbTmAddr);
	m_rgbTmAddr = new BYTE[m_cbTmAddr];
	// Get the whereabouts blob
	hRc = pITxWhere->GetWhereabouts (m_cbTmAddr, m_rgbTmAddr, &cbUsed);
	SafeRelease(pITxWhere);	
	return hRc;
}