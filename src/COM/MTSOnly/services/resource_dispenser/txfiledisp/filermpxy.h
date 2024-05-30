
/******************************************************************************\
********************************************************************************
* Filename: FileRmPxy.h
*
* Description:
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
// FileRmPxy.h : Declaration of the CFileRmPxy

#include "resource.h"       // main symbols
interface IFileRm;
interface ITransaction;
interface IDispenserDriver;

#include <map>
#include <set>
#include <list>
using namespace std;


interface IFileRm;

// 
//	setup a map of DWORDs to ITransactionExport * objects for 
//	mapping the DTC whereabouts to connections for enlisting on tx's
//

typedef map<DWORD, ITransactionExport *> ExportObjMap;


//
//	a set of connection handles -- if the ASP shutsdown, we should free the connections
//
typedef set<long> ConnectionSet;


#define SafeRelease(pUnk) {if (pUnk){pUnk -> Release();pUnk = NULL; }}

/////////////////////////////////////////////////////////////////////////////
// CFileRmPxy
class CFileRmPxy : 
	public IDispenserDriver, 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFileRmPxy, &CLSID_FileRmPxy>,
	public IDispatchImpl<IFileRmPxy, &IID_IFileRmPxy, &LIBID_TXFILEDISPLib>

{

private: 
// Resource Dispenser stuff
	IGlobalInterfaceTable *m_pGIT;
	DWORD m_dwRmPtrCookie;
	IHolder * m_pHolder;
	IDispenserManager * m_pDispMan;
	CComAutoCriticalSection m_critsec;
	
// a map of Connection handles to export objects
	ExportObjMap m_mapExport;

//	critical sections for STL collections
	CComAutoCriticalSection m_csCol;
	

	BOOL m_bConfirm;
	IFileRm * m_pRm;
#ifdef _DEBUG
	void ShowMessage();
#endif
	IFileRm * GetFileRmPointer();
	ConnectionSet m_set;
	IUnknown * m_pFreeThreadedMarshaler;

public:
//
// this resource dispenser must be a singleton object so that
// there is a unique IHolder which maintains the list of 
// resources to be pooled
//
DECLARE_CLASSFACTORY_SINGLETON(CFileRmPxy);
DECLARE_PROTECT_FINAL_CONSTRUCT();


	
	CFileRmPxy();
	~CFileRmPxy();

	HRESULT FinalConstruct();
	void FinalRelease();
	HRESULT GetExportObject(long ResID, ITransaction * pTransaction, ITransactionExport **ppExport);

DECLARE_REGISTRY_RESOURCEID(IDR_FileRmPxy)

BEGIN_COM_MAP(CFileRmPxy)
	COM_INTERFACE_ENTRY(IFileRmPxy)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDispenserDriver)	
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pFreeThreadedMarshaler)
END_COM_MAP()

public:

	
// IFileRmPxy
	STDMETHOD(AddFile)(long hConnection, BSTR sSource, BSTR sDestination);
	STDMETHOD(CopyFilesInCopyList)(long hConnection);
	STDMETHOD(CopyDirTx)(long hConnection, BSTR sSource, BSTR sDestination);
	STDMETHOD(CopyFileTx)(long hConnection,BSTR sSource,BSTR sDestination,BOOL bFailIfExists);
	STDMETHOD(MoveFileTx)(long hConnection,BSTR sSource,BSTR sDestination);
	STDMETHOD(DeleteFileTx)(long hConnection,BSTR sFileName);


	
//connection management
	STDMETHOD(Connect)(long *hConnection);
	STDMETHOD(Disconnect)(long hConnection);
	
// IDispenserDriver
	STDMETHOD(CreateResource)(/*[in]*/  const RESTYPID ResTypId,	
							      /*[out]*/ RESID* pResId, 
							      /*[out]*/ TIMEINSECS* pSecsFreeBeforeDestroy);

	STDMETHOD(RateResource)(/*[in]*/  const RESTYPID ResTypId,
							/*[in]*/  const RESID ResId,
							/*[in]*/  const BOOL fRequiresTransactionEnlistment,
							/*[out]*/ RESOURCERATING* pRating);

	STDMETHOD(EnlistResource)(/*[in]*/  const RESID ResId,/*[in]*/  const TRANSID TransId);
	STDMETHOD(ResetResource)(/*[in]*/  const RESID ResId);
	STDMETHOD(DestroyResource)(/*[in]*/  const RESID ResId);	// numeric resource id
	STDMETHOD(DestroyResourceS)(/*[in]*/  constSRESID ResId);	// string resource id


	

};
