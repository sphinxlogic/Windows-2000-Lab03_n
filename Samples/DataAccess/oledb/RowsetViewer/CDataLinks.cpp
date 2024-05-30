//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CDATALINKS.CPP
//
//-----------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////
#include "Headers.h"


/////////////////////////////////////////////////////////////////
// CServiceComp::CServiceComp
//
/////////////////////////////////////////////////////////////////
CServiceComp::CServiceComp(CMainWindow* pCMainWindow) 
	: CBase(eCServiceComp, pCMainWindow, NULL)
{
	//OLE DB Interfaces
	m_pIDataInitialize			= NULL;		//DataLink interface
	
#ifdef INTERNAL_ONLY
	//Services Interfaces
	m_pIPoolMngrInfo			= NULL;		//Services interface
	m_pIUdlCacheMngr			= NULL;		//Services interface
	m_fDisplayPools				= FALSE;	//Services interface
#endif //INTERNAL_ONLY
	
	//Data
	m_pwszInitString			= NULL;
	GetRegEnumValue(HKEY_ROWSETVIEWER, wszRECENTINITSTRING_KEY, 0,	&m_pwszInitString);
}

/////////////////////////////////////////////////////////////////
// CServiceComp::~CServiceComp
//
/////////////////////////////////////////////////////////////////
CServiceComp::~CServiceComp()
{
	ReleaseObject(0);

	//ServiceComponents
	DelRegEntry(HKEY_ROWSETVIEWER, wszRECENTINITSTRING_KEY);
	SetRegEntry(HKEY_ROWSETVIEWER, wszRECENTINITSTRING_KEY,	m_pwszInitString, L"");

	SAFE_FREE(m_pwszInitString);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CServiceComp::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CServiceComp::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(IDataInitialize);
#ifdef INTERNAL_ONLY
	HANDLE_GETINTERFACE(IPoolMngrInfo);
#endif //INTERNAL_ONLY

	//Otherwise delegate
	return CBase::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// CServiceComp::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::AutoRelease()
{
	//OLE DB Interfaces
	RELEASE_INTERFACE(IDataInitialize);

#ifdef INTERNAL_ONLY
	//Unadvise Pooling Listeners
	if(m_pIPoolMngrInfo && m_fDisplayPools)
		m_pIPoolMngrInfo->SetPoolNotify(NULL);

	//Services Interfaces
	RELEASE_INTERFACE(IPoolMngrInfo);
	RELEASE_INTERFACE(IUdlCacheMngr);

	//Release all pools
	ReleasePools();
	m_fDisplayPools = FALSE;
#endif //INTERNAL_ONLY

	//Delegate
	return CBase::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CBase::AutoQI(dwCreateOpts);

	//[MANDATORY]
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(IDataInitialize);

#ifdef INTERNAL_ONLY
		//Services Interfaces
		OBTAIN_INTERFACE(IPoolMngrInfo);
#endif //INTERNAL_ONLY
	}

	//[OPTIONAL]
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::Create
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::Create(CBase* pCSource, DWORD dwCSLCTX, WCHAR* pwszRemoteServer)
{
	HRESULT		hr = S_OK;
	IUnknown*	pIUnknown = NULL;

	//CLSID_MSDAINITIALIZE
	XTESTC(hr = m_pCMainWindow->m_pCRootEnumerator->CreateInstance(NULL, CLSID_MSDAINITIALIZE, dwCSLCTX, IID_IUnknown, &pIUnknown, pwszRemoteServer));

	//Delegate
	TESTC(hr = CBase::CreateObject(pCSource, IID_IUnknown, pIUnknown));

CLEANUP:
	TRACE_RELEASE(pIUnknown, L"IUnknown");
	return hr;
}


////////////////////////////////////////////////////////////////
// CServiceComp::OnDefOperation
//
/////////////////////////////////////////////////////////////////
void	CServiceComp::OnDefOperation() 
{ 
	//Need to bring up the GetDataSource Dialog
	if(m_pIDataInitialize)
		m_pCMainWindow->DisplayDialog(IDD_DATAINIT_GETDATASOURCE, m_pCMainWindow->m_hWnd, CMainWindow::GetDataSourceProc, this);
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::CreateDBInstance
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::CreateDBInstance(REFCLSID clsid, CAggregate* pCAggregate, DWORD dwCLSCTX, REFIID riid, IUnknown** ppIUnknown)
{
	HRESULT	hr			= E_FAIL;

	//CLSID to String (just for display purposes...)
	WCHAR* pwszProgID = GetProgID(clsid);

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDataInitialize)
	{
		//Now Obtain Instance of Provider (with Service Components)
		XTEST(hr = m_pIDataInitialize->CreateDBInstance(clsid, pCAggregate, dwCLSCTX, L"pwszReserved", riid, ppIUnknown));
		TESTC(TRACE_METHOD(hr, L"IDataInitialize::CreateDBInstance(%s, 0x%p, 0x%08x, \"pwszReserved\", %s, &0x%p)", pwszProgID, pCAggregate, dwCLSCTX, GetInterfaceName(riid), ppIUnknown ? *ppIUnknown : NULL));

		//Handle Aggregation
		if(pCAggregate)
			TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));
	}

CLEANUP:
	SAFE_FREE(pwszProgID);
	return hr;
}


/////////////////////////////////////////////////////////////////
// CServiceComp::GetDataSource
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::GetDataSource(CAggregate* pCAggregate, DWORD dwCLSCTX, WCHAR* pwszInitString, REFIID riid, IUnknown** ppIUnknown)
{
	HRESULT	hr			= E_FAIL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDataInitialize)
	{
		//GetDataSource based upoon the InitString
		XTEST(hr = m_pIDataInitialize->GetDataSource(pCAggregate, dwCLSCTX, pwszInitString, riid, ppIUnknown));
		TESTC(TRACE_METHOD(hr, L"IDataInitialize::GetDataSource(0x%p, 0x%08x, \"%s\", %s, &0x%p)", pCAggregate, m_pCMainWindow->GetOptions()->m_dwCLSCTX, pwszInitString, GetInterfaceName(riid), ppIUnknown ? *ppIUnknown : NULL));

		//Handle Aggregation
		if(pCAggregate)
			TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));
	}

CLEANUP:
	return hr;
}

	
/////////////////////////////////////////////////////////////////
// CServiceComp::GetInitString
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::GetInitString(IUnknown* pIUnknown, boolean fIncludePassword, WCHAR** ppwszInitString)
{
	HRESULT	hr				= E_FAIL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDataInitialize)
	{
		//GetInitializationString
		XTEST(hr = m_pIDataInitialize->GetInitializationString(pIUnknown, fIncludePassword, ppwszInitString));
		TESTC(TRACE_METHOD(hr, L"IDataInitialize::GetInitializationString(0x%p, %s, &\"%s\")", pIUnknown, fIncludePassword ? L"True" : L"False", ppwszInitString ? *ppwszInitString : NULL));
	}

CLEANUP:
	return hr;
}



/////////////////////////////////////////////////////////////////
// CServiceComp::SaveInitString
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::SaveInitString(WCHAR* pwszFileName, WCHAR* pwszInitString, DWORD dwCreateOpts)
{
	HRESULT	hr			= E_FAIL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDataInitialize)
	{
		//WriteStringToStorage
		XTEST(hr = m_pIDataInitialize->WriteStringToStorage(pwszFileName, pwszInitString, dwCreateOpts));
		TESTC(TRACE_METHOD(hr, L"IDataInitialize::WriteStringToStorage(\"%s\", \"%s\", 0x%08x)", pwszFileName, pwszInitString, dwCreateOpts));
	}

CLEANUP:
	return hr;
}

	
/////////////////////////////////////////////////////////////////
// CServiceComp::LoadInitString
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::LoadInitString(WCHAR* pwszFileName, WCHAR** ppwszInitString)
{
	HRESULT	hr				= E_FAIL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDataInitialize)
	{
		//LoadStringFromStorage
		XTEST(hr = m_pIDataInitialize->LoadStringFromStorage(pwszFileName, ppwszInitString));
		TESTC(TRACE_METHOD(hr, L"IDataInitialize::LoadStringFromStorage(\"%s\", &\"%s\")", pwszFileName, ppwszInitString ? *ppwszInitString : NULL));
	}

CLEANUP:
	return hr;
}



/////////////////////////////////////////////////////////////////
// CServiceComp::ConnectFromFile
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::ConnectFromFile(WCHAR* pwszSelectedFile)
{
	HRESULT hr = S_OK;
	WCHAR* pwszInitString = NULL;
	IUnknown* pIUnknown = NULL;

	//No-op
	if(pwszSelectedFile == NULL)
		return E_FAIL;

	//Load the saved InitString from the SelectedFile
	TESTC(hr = LoadInitString(pwszSelectedFile, &pwszInitString));

	//Delegate - Now that we have the InitString
	TESTC(hr = GetDataSource(NULL, GetOptions()->m_dwCLSCTX, pwszInitString, IID_IUnknown, &pIUnknown));

	//Update the Saved Files (now that successfuly connected)
	m_pCMainWindow->m_pCFullConnect->AddRecentFile(pwszSelectedFile);

	//Handle the returned object...
	//NOTE: Can pontentially return other object types: (ie: CREATE_DETERMINE_TYPE)
	if(!m_pCMainWindow->HandleObjectType(this, pIUnknown, IID_IUnknown, eCDataSource, 0, NULL, CREATE_NEWWINDOW | CREATE_DETERMINE_TYPE | GetOptions()->m_dwCreateOpts))
		TESTC(hr = E_FAIL);
	
CLEANUP:
	SAFE_RELEASE(pIUnknown);
	SAFE_FREE(pwszInitString);
	return hr;
}


#ifdef INTERNAL_ONLY
/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::EnumPools
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::EnumPools()
{
	HRESULT				hr = S_OK;

	ULONG iPool,cPools = 0;
	IPoolInfo** rgpIPoolInfo = NULL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	//Advise Pooling Listeners
	//NOTE: We do this here only if the user wishes to see pool info (and only the first time)
	if(m_pIPoolMngrInfo && !m_fDisplayPools)
	{
		m_pCMainWindow->GetOptions()->m_dwNotifyOpts |= NOTIFY_IPOOLNOTIFY;
		m_pIPoolMngrInfo->SetPoolNotify((IPoolNotify*)m_pCMainWindow->m_pCListener);
	}

	//The user wishes to see pool updates...
	m_fDisplayPools = TRUE;

	if(m_pIPoolMngrInfo)
	{

		//IPoolMngrInfo::EnumPools
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolMngrInfo->EnumPools(&cPools, &rgpIPoolInfo));
		TESTC(TRACE_METHOD(hr, L"    IPoolMngrInfo::EnumPools(&%d, &0x%p)", cPools, rgpIPoolInfo));

		//Release all existing pools...
		ReleasePools();

		//For every pool obtained display it...
		for(iPool=0; iPool<cPools; iPool++)
		{
			IPoolInfo* pIPoolInfo = rgpIPoolInfo[iPool];
			ASSERT(pIPoolInfo);
			
			CPoolInfo* pCPoolInfo = new CPoolInfo(m_pCMainWindow, NULL);
			if(pCPoolInfo)
			{
				//Create this object...
				TESTC(hr = pCPoolInfo->CreateObject(this, IID_IPoolInfo, pIPoolInfo));

				//Now refresh this pool...
				TESTC(hr = pCPoolInfo->DisplayObject());
			
				//Add this item to our list of pools...
				m_listCPoolInfo.AddTail(pCPoolInfo);
			}
				
			//Release the pool interface
			SAFE_RELEASE(pIPoolInfo);
		}
	}

CLEANUP:
	SAFE_FREE(rgpIPoolInfo);
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::RefreshPools
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::RefreshPools()
{
	if(m_fDisplayPools)
		return EnumPools();

	return S_OK;
}

/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::ReleasePools
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::ReleasePools()
{
	HRESULT				hr = S_OK;

	while(!m_listCPoolInfo.IsEmpty())
	{
		CPoolInfo* pCPoolInfo = m_listCPoolInfo.RemoveHead();
		SAFE_RELEASE(pCPoolInfo);
	}


//CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::GetStringInfoFromFileName
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::GetStringInfoFromFileName(WCHAR* pwszFileName, WCHAR** ppwszInitString, DWORD* pdwTickCount)
{
	HRESULT hr = S_OK;
	WCHAR* pwszInitString = NULL;
	DWORD dwTickCount = 0;

	if(m_pIUdlCacheMngr)
	{
		//IUdlCacheMngr::GetStringInfoFromFileName
		//NOTE: Internal interface (indent)
		hr = m_pIUdlCacheMngr->GetStringInfoFromFileName(pwszFileName, &pwszInitString, &dwTickCount);
		TRACE_METHOD(hr, L"    IUdlCacheMngr::GetStringInfoFromFileName(\"%s\", \"%s\", &0x%08x)", pwszFileName, pwszInitString, dwTickCount);
	}

	//Output Params
	if(ppwszInitString)
		*ppwszInitString = pwszInitString;
	else
		SAFE_FREE(pwszInitString);
	if(pdwTickCount)
		*pdwTickCount = dwTickCount;
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::SetUdlGlobalTickCount
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::SetUdlGlobalTickCount(DWORD dwTickCount)
{
	HRESULT hr = S_OK;

	if(m_pIUdlCacheMngr)
	{
		//IUdlCacheMngr::SetUdlGlobalTickCount
		//NOTE: Internal interface (indent)
		hr = m_pIUdlCacheMngr->SetUdlGlobalTickCount(dwTickCount);
		TRACE_METHOD(hr, L"    IUdlCacheMngr::SetUdlGlobalTickCount(0x%08x)", dwTickCount);
	}

	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::GetUdlGlobalTickCount
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::GetUdlGlobalTickCount(DWORD* pdwTickCount)
{
	HRESULT hr = S_OK;

	if(m_pIUdlCacheMngr)
	{
		//IUdlCacheMngr::GetUdlGlobalTickCount
		//NOTE: Internal interface (indent)
		hr = m_pIUdlCacheMngr->GetUdlGlobalTickCount(pdwTickCount);
		TRACE_METHOD(hr, L"    IUdlCacheMngr::GetUdlGlobalTickCount(&0x%08x)", pdwTickCount ? *pdwTickCount : NULL);
	}

	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::SetUdlCacheSize
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::SetUdlCacheSize(DWORD dwCacheSize)
{
	HRESULT hr = S_OK;

	if(m_pIUdlCacheMngr)
	{
		//IUdlCacheMngr::SetUdlCacheSize
		//NOTE: Internal interface (indent)
		hr = m_pIUdlCacheMngr->SetUdlCacheSize(dwCacheSize);
		TRACE_METHOD(hr, L"    IUdlCacheMngr::SetUdlCacheSize(0x%08x)", dwCacheSize);
	}

	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CServiceComp::GetCurrentUdlCacheSize
//
/////////////////////////////////////////////////////////////////
HRESULT CServiceComp::GetCurrentUdlCacheSize(DWORD* pdwCacheSize)
{
	HRESULT hr = S_OK;

	if(m_pIUdlCacheMngr)
	{
		//IUdlCacheMngr::GetCurrentUdlCacheSize
		//NOTE: Internal interface (indent)
		hr = m_pIUdlCacheMngr->GetCurrentUdlCacheSize(pdwCacheSize);
		TRACE_METHOD(hr, L"    IUdlCacheMngr::GetCurrentUdlCacheSize(&0x%08x)", pdwCacheSize ? *pdwCacheSize : NULL);
	}

	return hr;
}


#endif //INTERNAL_ONLY



/////////////////////////////////////////////////////////////////
// CDataLinks::CDataLinks
//
/////////////////////////////////////////////////////////////////
CDataLinks::CDataLinks(CMainWindow* pCMainWindow) 
	: CBase(eCDataLinks, pCMainWindow, NULL)
{
	//OLE DB Interfaces
	m_pIDBPromptInitialize		= NULL;		//DataLink interface
	
	//Data
}

/////////////////////////////////////////////////////////////////
// CDataLinks::~CDataLinks
//
/////////////////////////////////////////////////////////////////
CDataLinks::~CDataLinks()
{
	ReleaseObject(0);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CDataLinks::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CDataLinks::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(IDBPromptInitialize);

	//Otherwise delegate
	return CBase::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// CDataLinks::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CDataLinks::AutoRelease()
{
	//OLE DB Interfaces
	RELEASE_INTERFACE(IDBPromptInitialize);

	//Delegate
	return CBase::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataLinks::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CDataLinks::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CBase::AutoQI(dwCreateOpts);

	//[MANDATORY]
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(IDBPromptInitialize);
	}

	//[OPTIONAL]
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
	}

	return S_OK;
}


/////////////////////////////////////////////////////////////////
// HRESULT CDataLinks::Create
//
/////////////////////////////////////////////////////////////////
HRESULT CDataLinks::Create(CBase* pCSource, DWORD dwCSLCTX, WCHAR* pwszRemoteServer)
{
	HRESULT		hr = S_OK;
	IUnknown*	pIUnknown = NULL;

	//CLSID_MSDAINITIALIZE
	XTESTC(hr = m_pCMainWindow->m_pCRootEnumerator->CreateInstance(NULL, CLSID_DataLinks, dwCSLCTX, IID_IUnknown, &pIUnknown, pwszRemoteServer));

	//Delegate
	TESTC(hr = CBase::CreateObject(pCSource, IID_IUnknown, pIUnknown));

CLEANUP:
	TRACE_RELEASE(pIUnknown, L"IUnknown");
	return hr;
}


////////////////////////////////////////////////////////////////
// CDataLinks::OnDefOperation
//
/////////////////////////////////////////////////////////////////
void	CDataLinks::OnDefOperation() 
{ 
	//PromptDataSource dialog
	IUnknown* pIUnknown = NULL;
			
	//Just display the PromptDataSource dialog directly (common case)
	if(SUCCEEDED(PromptDataSource(NULL, m_pCMainWindow->m_hWnd, DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, IID_IDBInitialize, &pIUnknown)))
	{
		//Handle the returned object...
		//NOTE: Can pontentially return other object types: (ie: CREATE_DETERMINE_TYPE)
		m_pCMainWindow->HandleObjectType(this, pIUnknown, IID_IDBInitialize, eCDataSource, 0, NULL, CREATE_NEWWINDOW | CREATE_DETERMINE_TYPE | m_pCMainWindow->GetOptions()->m_dwCreateOpts);
	}

	SAFE_RELEASE(pIUnknown);
}


/////////////////////////////////////////////////////////////////
// CDataLinks::PromptDataSource
//
/////////////////////////////////////////////////////////////////
HRESULT CDataLinks::PromptDataSource(CAggregate* pCAggregate, HWND hWndParent, DBPROMPTOPTIONS dwPromptOptions, ULONG cTypeFilters, DBSOURCETYPE* rgTypeFilters, WCHAR* pwszProvFilter, REFIID riid, IUnknown** ppDataSource)
{
	HRESULT	hr			= E_FAIL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDBPromptInitialize)
	{
		//IDBPromptInitialize::PromptDataSource
		//NOTE: Expect S_OK or DB_E_CANCELED, since canceling the dialog always returns DB_E_CANCELED
		XTEST_(hr = m_pIDBPromptInitialize->PromptDataSource(pCAggregate, hWndParent, dwPromptOptions, cTypeFilters, rgTypeFilters, pwszProvFilter, riid, ppDataSource),DB_E_CANCELED);
		TESTC(TRACE_METHOD(hr, L"IDBPromptInitialize::PromptDataSource(0x%p, 0x%p, 0x%08x, %d, 0x%p, \"%s\", %s, &0x%p)", pCAggregate, hWndParent, dwPromptOptions, cTypeFilters, rgTypeFilters, pwszProvFilter, GetInterfaceName(riid), ppDataSource ? *ppDataSource : NULL));

		//Handle Aggregation
		if(pCAggregate)
			TESTC(hr = pCAggregate->HandleAggregation(riid, ppDataSource));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// CDataLinks::PromptFileName
//
/////////////////////////////////////////////////////////////////
HRESULT CDataLinks::PromptFileName(HWND hWndParent, DBPROMPTOPTIONS dwPromptOptions, WCHAR* pwszDirectory, WCHAR* pwszFileName, WCHAR** ppwszSelectedFile)
{
	HRESULT	hr			= E_FAIL;

	//Defferred Creation
	if(!m_pIUnknown)
		TESTC(hr = Create(NULL));

	if(m_pIDBPromptInitialize)
	{
		//IDBPromptInitalize::PromptFileName
		//NOTE: Expect S_OK or DB_E_CANCELED, since canceling the dialog always returns DB_E_CANCELED
		XTEST_(hr = m_pIDBPromptInitialize->PromptFileName
					(
					hWndParent,							// hWndParent
					dwPromptOptions,					// dwPromptOptions
            		pwszDirectory,						// pwszInitialDirectory
            		pwszFileName,						// pwszInitialFile
            		ppwszSelectedFile					// pwszSelectedFile
					), DB_E_CANCELED);
		TESTC(TRACE_METHOD(hr, L"IDBPromptInitialize::PromptFileName(0x%p, 0x%08x, \"%s\", \"%s\", &\"%s\")", hWndParent, dwPromptOptions, pwszDirectory, pwszFileName, ppwszSelectedFile ? *ppwszSelectedFile : NULL));
	}

CLEANUP:
	return hr;
}



#ifdef INTERNAL_ONLY
/////////////////////////////////////////////////////////////////
// CPoolInfo::CPoolInfo
//
/////////////////////////////////////////////////////////////////
CPoolInfo::CPoolInfo(CMainWindow* pCMainWindow, CMDIChild* pCMDIChild) 
	: CBase(eCPoolInfo, pCMainWindow, pCMDIChild)
{
	//Services Interfaces
	m_pIPoolInfo			= NULL;		//Services interface

	//Data
	m_pwszPoolID			= NULL;
	m_pwszPrototype			= NULL;
}

/////////////////////////////////////////////////////////////////
// CPoolInfo::~CPoolInfo
//
/////////////////////////////////////////////////////////////////
CPoolInfo::~CPoolInfo()
{
	//Make sure the TreeItem is gone for good, (along with everything under it...)
	if(m_hTreeItem && m_pCMainWindow->m_pCMDIObjects->m_pCObjTree->m_hWnd)
		m_pCMainWindow->m_pCMDIObjects->m_pCObjTree->DeleteItem(m_hTreeItem);
	m_hTreeItem = NULL;

	ReleaseObject(0);
}


/////////////////////////////////////////////////////////////////
// IUnknown** CPoolInfo::GetInterfaceAddress
//
/////////////////////////////////////////////////////////////////
IUnknown** CPoolInfo::GetInterfaceAddress(REFIID riid)
{
	HANDLE_GETINTERFACE(IPoolInfo);

	//Otherwise delegate
	return CBase::GetInterfaceAddress(riid);
}


/////////////////////////////////////////////////////////////////
// CPoolInfo::AutoRelease
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::AutoRelease()
{
	//Services Interfaces
	RELEASE_INTERFACE(IPoolInfo);

	SAFE_FREE(m_pwszPoolID);
	SAFE_FREE(m_pwszPrototype);

	//Delegate
	return CBase::AutoRelease();
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::AutoQI
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::AutoQI(DWORD dwCreateOpts)
{
	//Delegate First so we have base interfaces
	CBase::AutoQI(dwCreateOpts);

	//[MANDATORY]
	if(dwCreateOpts & CREATE_QI_MANDATORY)
	{
		OBTAIN_INTERFACE(IPoolInfo);
	}

	//[OPTIONAL]
	if(dwCreateOpts & CREATE_QI_OPTIONAL)
	{
	}

	//Obtain the PoolID if available...
	GetPoolID(&m_pwszPoolID);

	//NOTE: Request a prototype without returning a datasource...
	//(For this special case ppIUnknown==NULL)
	GetPrototype(&m_pwszPrototype, IID_IUnknown, NULL);
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CPoolInfo::GetObjectDesc
//
/////////////////////////////////////////////////////////////////////////////
WCHAR* CPoolInfo::GetObjectDesc()
{
	return m_pwszPoolID;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::DisplayObject
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::DisplayObject()
{
	HRESULT hr = S_OK;
	CObjTree* pCObjTree = m_pCMainWindow->m_pCMDIObjects->m_pCObjTree;
	if(!m_hTreeItem || !pCObjTree || !pCObjTree->m_hWnd)
		return E_FAIL;
	
	//First remove all children...
	HTREEITEM hChildItem = pCObjTree->GetChildItem(m_hTreeItem);
	while(hChildItem)
	{
		pCObjTree->DeleteItem(hChildItem);
		hChildItem = pCObjTree->GetChildItem(m_hTreeItem);
	}

	//Now display all "InUse" and "Idle" elements of the pool...
	if(m_pIPoolInfo)
	{
		DWORD i,dwInUse=0;
		DWORD dwIdle=0;

		//Now obtain all the elements within this pool...
		TESTC(hr = GetCount(&dwInUse, &dwIdle));
		//Lets be realistic!
		ASSERT(dwInUse <= 1000 && dwIdle <= 1000);
		
		//Display all the "InUse" Elements in the pool...
		for(i=0; i<dwInUse; i++)
			pCObjTree->InsertItem(m_hTreeItem, NULL, L"InUse", NULL/*lParam*/, IMAGE_DATASOURCE, IMAGE_DATASOURCE);

		//Display all the "Idle" Elements in the pool...
		for(i=0; i<dwIdle; i++)
			pCObjTree->InsertItem(m_hTreeItem, NULL, L"Idle", NULL/*lParam*/, IMAGE_DRAWNPOOL, IMAGE_DRAWNPOOL);

		//Automatically Expand the Tree...
		pCObjTree->Expand(m_hTreeItem);
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::GetPoolID
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::GetPoolID(WCHAR** ppwszPoolID)
{
	//DataLink interfaces
	HRESULT hr = S_OK;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::GetPoolID
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->GetPoolID(ppwszPoolID));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::GetPoolID(&\"%s\")", ppwszPoolID ? *ppwszPoolID : NULL));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::GetPrototype
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::GetPrototype(WCHAR** ppwszPrototype, REFIID riid, IUnknown** ppDataSource)
{
	//DataLink interfaces
	HRESULT hr = S_OK;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::GetPrototype
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->GetPrototype(ppwszPrototype, riid, (void**)ppDataSource));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::GetPrototype(\"%s\", %s, &0x%p)", ppwszPrototype ? *ppwszPrototype : NULL, GetInterfaceName(riid), ppDataSource ? *ppDataSource : NULL));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::GetCount
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::GetCount(DWORD* pdwInUse, DWORD* pdwIdle)
{
	//DataLink interfaces
	HRESULT hr = S_OK;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::GetCount
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->GetCount(pdwInUse, pdwIdle));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::GetCount(&%d, &%d)", pdwInUse ? *pdwInUse : 0, pdwIdle ? *pdwIdle : 0));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::GetPoolTimeOut
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::GetPoolTimeOut(DWORD* pdwTimeOut)
{
	//DataLink interfaces
	HRESULT hr = S_OK;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::GetPoolTimeOut
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->GetPoolTimeOut(pdwTimeOut));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::GetPoolTimeOut(&%d)", pdwTimeOut ? *pdwTimeOut : 0));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::SetPoolTimeOut
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::SetPoolTimeOut(DWORD dwTimeOut)
{
	//DataLink interfaces
	HRESULT hr = S_OK;
	DWORD dwPrevTimeOut = 0;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::SetPoolTimeOut
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->SetPoolTimeOut(dwTimeOut, &dwPrevTimeOut));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::SetPoolTimeOut(%d, &%d)", dwTimeOut, dwPrevTimeOut));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::GetRetryTimeOut
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::GetRetryTimeOut(DWORD* pdwTimeOut)
{
	//DataLink interfaces
	HRESULT hr = S_OK;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::GetRetryTimeOut
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->GetRetryTimeOut(pdwTimeOut));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::GetRetryTimeOut(&%d)", pdwTimeOut ? *pdwTimeOut : 0));
	}

CLEANUP:
	return hr;
}


/////////////////////////////////////////////////////////////////
// HRESULT CPoolInfo::SetRetryTimeOut
//
/////////////////////////////////////////////////////////////////
HRESULT CPoolInfo::SetRetryTimeOut(DWORD dwTimeOut)
{
	//DataLink interfaces
	HRESULT hr = S_OK;
	DWORD dwPrevTimeOut = 0;

	if(m_pIPoolInfo)
	{
		//IPoolInfo::SetRetryTimeOut
		//NOTE: Internal interface (indent)
		XTEST(hr = m_pIPoolInfo->SetRetryTimeOut(dwTimeOut, &dwPrevTimeOut));
		TESTC(TRACE_METHOD(hr, L"    IPoolInfo::SetRetryTimeOut(%d, &%d)", dwTimeOut, dwPrevTimeOut));
	}

CLEANUP:
	return hr;
}
#endif //INTERNAL_ONLY

