//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CDATASOURCE.CPP
//
//-----------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////
#include "Headers.h"


/////////////////////////////////////////////////////////////////
// CDataSource::CDataSource
//
/////////////////////////////////////////////////////////////////
CDataSource::CDataSource(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild) 
	: CPropertiesBase(eCDataSource, pCMainWindow, pCMDIChild)
{
	//OLE DB Interfaces
	m_pIDBCreateSession			= NULL;		//DataSource interface
	m_pIPersist					= NULL;		//DataSource interface

	m_pIDBDataSourceAdmin		= NULL;		//DataSource interface
	m_pIDBInfo					= NULL;		//DataSource interface
	m_pIPersistFile				= NULL;		//DataSource interface

	//Services
	m_pIServiceProvider			= NULL;		//Service interface

#ifdef INTERNAL_ONLY
	m_pIGetPool					= NULL;		//Service interface
	m_dwPoolState				= 0;		//Service
#endif //INTERNAL_ONLY
	
	//Properties
	m_bstrDataSource			= NULL;		//DBPROP_DATASOURCENAME
	m_bstrDBMS					= NULL;		//DBPROP_DBMSNAME
	m_bstrDBMSVer				= NULL;		//DBPROP_DBMSVER
	m_bstrProviderName			= NULL;
	m_bstrProviderDesc			= NULL;
	m_lDataSourceType			= DBPROPVAL_DST_TDP;
}

/////////////////////////////////////////////////////////////////
// CDataSource::~CDataSource
//
/////////////////////////////////////////////////////////////////
CDataSource::~CDataSource()
{
	ReleaseObject(0);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CDataSource::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CDataSource::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(IDBCreateSession);
	HANDLE_GETINTERFACE(IPersist);
	HANDLE_GETINTERFACE(IDBDataSourceAdmin);
	HANDLE_GETINTERFACE(IDBInfo);
	HANDLE_GETINTERFACE(IPersistFile);
	HANDLE_GETINTERFACE(IServiceProvider);

#ifdef INTERNAL_ONLY
	HANDLE_GETINTERFACE(IGetPool);
#endif //INTERNAL_ONLY

	//Otherwise delegate
	return CPropertiesBase::GetInterfaceAddress(riid);
}


////////////////////////////////////////////////////////////////
// CDataSource::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::AutoRelease()
{
	//DataSource interfaces
	RELEASE_INTERFACE(IDBCreateSession);
	RELEASE_INTERFACE(IPersist);

	RELEASE_INTERFACE(IDBDataSourceAdmin);
	RELEASE_INTERFACE(IDBInfo);
	RELEASE_INTERFACE(IPersistFile);

	//Services
	RELEASE_INTERFACE(IServiceProvider);

#ifdef INTERNAL_ONLY
	RELEASE_INTERFACE(IGetPool);
	m_dwPoolState = 0;
#endif //INTERNAL_ONLY

	//Extra interfaces

	//Properties
	SAFE_BSTRFREE(m_bstrDataSource);
	SAFE_BSTRFREE(m_bstrDBMS);
	SAFE_BSTRFREE(m_bstrDBMSVer);
	SAFE_BSTRFREE(m_bstrProviderName);
	SAFE_BSTRFREE(m_bstrProviderDesc);

	//Delegate
	return CPropertiesBase::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataSource::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CPropertiesBase::AutoQI(dwCreateOpts);

	//[MANDATORY]
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(IDBCreateSession);
		OBTAIN_INTERFACE(IPersist);
#ifdef INTERNAL_ONLY
		OBTAIN_INTERFACE(IGetPool);
#endif //INTERNAL_ONLY
	}

	//AutoQI
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
		OBTAIN_INTERFACE(IDBDataSourceAdmin);
		OBTAIN_INTERFACE(IDBInfo);
		OBTAIN_INTERFACE(IPersistFile);

		//Services
		OBTAIN_INTERFACE(IServiceProvider);
	}

	//Are we intialized yet...
	if(m_pIDBProperties && (IsInitialized() || m_pIDBCreateSession))
	{
		//DBPROP_DATASOURCENAME
		GetProperty(IID_IDBProperties, m_pIDBProperties, DBPROP_DATASOURCENAME,			DBPROPSET_DATASOURCEINFO, DBTYPE_BSTR, &m_bstrDataSource);
		//DBPROP_DBMSNAME
		GetProperty(IID_IDBProperties, m_pIDBProperties, DBPROP_DBMSNAME,				DBPROPSET_DATASOURCEINFO, DBTYPE_BSTR, &m_bstrDBMS);
		//DBPROP_DBMSVER
		GetProperty(IID_IDBProperties, m_pIDBProperties, DBPROP_DBMSVER,				DBPROPSET_DATASOURCEINFO, DBTYPE_BSTR, &m_bstrDBMSVer);
		//DBPROP_PROVIDERFILENAME
		GetProperty(IID_IDBProperties, m_pIDBProperties, DBPROP_PROVIDERFILENAME,		DBPROPSET_DATASOURCEINFO, DBTYPE_BSTR, &m_bstrProviderName);
		//DBPROP_PROVIDERFRIENDLYNAME
		GetProperty(IID_IDBProperties, m_pIDBProperties, DBPROP_PROVIDERFRIENDLYNAME,	DBPROPSET_DATASOURCEINFO, DBTYPE_BSTR, &m_bstrProviderDesc);
		//DBPROP_DATASOURCE_TYPE
		GetProperty(IID_IDBProperties, m_pIDBProperties, DBPROP_DATASOURCE_TYPE,		DBPROPSET_DATASOURCEINFO, DBTYPE_I4,   &m_lDataSourceType);

		//Only set "Default" properties, if requested by the user
		if(GetOptions()->m_dwRowsetOpts & ROWSET_SETDEFAULTPROPS)
		{
			//Kagera has a problem with OPTIONAL properties, still treating
			//them as SETIFCHEAP and lets you know the NOTSET ones...
			//Instead of always getting DB_S_ERRORSOCCURRED just special case until fixed
			DBPROPOPTIONS dwPropOptions = DBPROPOPTIONS_OPTIONAL;
			if(m_bstrProviderName && wcscmp(m_bstrProviderName, L"MSDASQL.DLL")==0)
				dwPropOptions = DBPROPOPTIONS_REQUIRED;

			if(m_pCMDIChild)
			{
				CPropSets* pCPropSets = &m_pCMDIChild->m_CDefPropSets;

				//We want to provide Scrolling Capabilites to the user (if supported)
				if(IsSettableProperty(m_pIDBProperties, DBPROP_CANSCROLLBACKWARDS, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_CANSCROLLBACKWARDS, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);
				if(IsSettableProperty(m_pIDBProperties, DBPROP_CANFETCHBACKWARDS, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_CANFETCHBACKWARDS, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);

				//Allow the user to change data (if supported)
				if(IsSettableProperty(m_pIDBProperties, DBPROP_IRowsetChange, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_IRowsetChange, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);
				if(IsSettableProperty(m_pIDBProperties, DBPROP_UPDATABILITY, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_UPDATABILITY, DBPROPSET_ROWSET, DBTYPE_I4, (void*)(DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE), dwPropOptions);
				
				//The table may contain BLOBs, and the Provider may require random positioning
				if(IsSettableProperty(m_pIDBProperties, DBPROP_ACCESSORDER, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_ACCESSORDER, DBPROPSET_ROWSET, DBTYPE_I4, (void*)DBPROPVAL_AO_RANDOM, dwPropOptions);
				
				//Notifications are very useful debugging info (if supported)
				if(IsSettableProperty(m_pIDBProperties, DBPROP_IConnectionPointContainer, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_IConnectionPointContainer, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);

				//DBPROP_ISequentialStream 
				if(GetOptions()->m_dwAccessorOpts & ACCESSOR_BLOB_ISEQSTREAM &&
					IsSettableProperty(m_pIDBProperties, DBPROP_ISequentialStream, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_ISequentialStream, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);
				//DBPROP_ILockBytes 
				if(GetOptions()->m_dwAccessorOpts & ACCESSOR_BLOB_ILOCKBYTES &&
					IsSettableProperty(m_pIDBProperties, DBPROP_ILockBytes, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_ILockBytes, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);
				//DBPROP_IStorage
				if(GetOptions()->m_dwAccessorOpts & ACCESSOR_BLOB_ISTORAGE &&
					IsSettableProperty(m_pIDBProperties, DBPROP_IStorage, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_IStorage, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);
				//DBPROP_IStream
				if(GetOptions()->m_dwAccessorOpts & ACCESSOR_BLOB_ISTREAM &&
					IsSettableProperty(m_pIDBProperties, DBPROP_IStream, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_IStream, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, dwPropOptions);

				//DBPROP_UNIQUEROWS
				//If the user has requested to display Hidden Columns then we need to set UniqueRows
				//Since hidden columns are only returned if UniqueRows==TRUE...
				if(GetOptions()->m_dwRowsetOpts & ROWSET_HIDDENCOLUMNS &&
					IsSettableProperty(m_pIDBProperties, DBPROP_UNIQUEROWS, DBPROPSET_ROWSET))
					pCPropSets->SetProperty(DBPROP_UNIQUEROWS, DBPROPSET_ROWSET, DBTYPE_BOOL, (void*)VARIANT_TRUE, DBPROPOPTIONS_REQUIRED/*DBPROPOPTIONS_OPTIONAL*/);
			}
		}

#ifdef INTERNAL_ONLY
		//PoolInfo...
		if(m_pIGetPool)
		{
			//IGetPool::GetState
			GetPoolState(&m_dwPoolState);
		}
#endif //INTERNAL_ONLY
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CDataSource::GetObjectDesc
//
/////////////////////////////////////////////////////////////////////////////
WCHAR* CDataSource::GetObjectDesc()
{
	if(!m_pwszObjectDesc && m_pIPersist)
	{
		CLSID clsid;
		GetClassID(&clsid, &m_pwszObjectDesc);
	}

	return m_pwszObjectDesc;
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataSource::CreateSession
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::CreateSession(CAggregate* pCAggregate, REFIID riid, IUnknown** ppIUnknown)
{
	HRESULT				hr = S_OK;
	
	if(m_pIDBCreateSession)
	{
		//CreateSession
		TEST(hr = m_pIDBCreateSession->CreateSession(pCAggregate, riid, ppIUnknown));
		TESTC(TRACE_METHOD(hr, L"IDBCreateSession::CreateSession(0x%p, %s, &0x%p)", pCAggregate, GetInterfaceName(riid), ppIUnknown ? *ppIUnknown : NULL));

		//Handle Aggregation
		if(pCAggregate)
			TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));
	}

CLEANUP:
	return hr;
}



/////////////////////////////////////////////////////////////////
// HRESULT CDataSource::AdminCreateDataSource
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::AdminCreateDataSource(CAggregate* pCAggregate, ULONG cPropSets, DBPROPSET* rgPropSets, REFIID riid, IUnknown** ppIUnknown)
{
	HRESULT	hr = S_OK;
	DWORD dwCreateOpts = GetOptions()->m_dwCreateOpts;

	if(m_pIDBDataSourceAdmin)
	{
		//IDBDataSourceAdmin::CreateDataSource
		XTEST(hr = m_pIDBDataSourceAdmin->CreateDataSource(cPropSets, rgPropSets, pCAggregate, riid, ppIUnknown));
		TRACE_METHOD(hr, L"IDBDataSourceAdmin::CreateDataSource(%d, 0x%p, 0x%p, %s, &0x%p)", cPropSets, rgPropSets, pCAggregate, GetInterfaceName(riid), ppIUnknown ? *ppIUnknown : NULL);

		//Display any property errors...
		TESTC(hr = DisplayPropErrors(hr, cPropSets, rgPropSets));

		//Handle Aggregation
		if(pCAggregate)
			pCAggregate->HandleAggregation(riid, ppIUnknown);
		
		//We are now Initialized
		m_fInitialized = TRUE;

		//Obtain all interfaces, now that we are initialized
		TESTC(hr = AutoQI(dwCreateOpts));
	}
	
CLEANUP:
	return hr;
}


////////////////////////////////////////////////////////////////
// CDataSource::GetClassID
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::GetClassID(CLSID* pclsid, WCHAR** ppwszProgID)
{
	HRESULT hr = S_OK;
	WCHAR* pwszProgID = NULL;

	if(!m_pIPersist)
		return E_FAIL;

	//IPersist::GetClassID
	XTEST(hr = m_pIPersist->GetClassID(pclsid));

	//Obtain ProgID
	if(pclsid)
		pwszProgID = GetProgID(*pclsid);
	TESTC(TRACE_METHOD(hr, L"IPersist::GetClassID(%s)", pwszProgID));
	
CLEANUP:
	if(ppwszProgID)
		*ppwszProgID = pwszProgID;
	else
		SAFE_FREE(pwszProgID);
	return hr;
}


#ifdef INTERNAL_ONLY
////////////////////////////////////////////////////////////////
// CDataSource::GetPool
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::GetPool(IPoolInfo** ppIPoolInfo)
{
	HRESULT hr = S_OK;

	if(m_pIGetPool)
	{
		//IGetPool::GetPool
		XTEST(hr = m_pIGetPool->GetPool(ppIPoolInfo));
		TESTC(TRACE_METHOD(hr, L"IGetPool::GetPool(&0x%p)", ppIPoolInfo ? *ppIPoolInfo : NULL));
	}
	
CLEANUP:
	return hr;
}


////////////////////////////////////////////////////////////////
// CDataSource::GetPoolState
//
/////////////////////////////////////////////////////////////////
HRESULT CDataSource::GetPoolState(DWORD* pdwPoolState)
{
	HRESULT hr = S_OK;

	if(m_pIGetPool)
	{
		//IGetPool::GetState
		XTEST(hr = m_pIGetPool->GetState(pdwPoolState));
		TESTC(TRACE_METHOD(hr, L"IGetPool::GetState(&0x%08x)", pdwPoolState ? *pdwPoolState : 0));
	}
	
CLEANUP:
	return hr;
}
#endif //INTERNAL_ONLY








