
/******************************************************************************\
********************************************************************************
* Filename: FileRm.h
*
* Description: Declaration of the CFileRm
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

#ifndef __FILERM_H_
#define __FILERM_H_

#include "resource.h"       // main symbols
#include <set>
interface IResourceManager;

extern long glWorkers;  // a global count of the number of workers connected to...
using namespace std;

typedef set<long> WorkerSet;

/////////////////////////////////////////////////////////////////////////////
// CFileRm
class ATL_NO_VTABLE CFileRm : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFileRm, &CLSID_CoFileRm>,
	public IFileRm
{

private: 

	BYTE *m_rgbTmAddr;
	ULONG m_cbTmAddr;
	
	IResourceManager	*m_pIResMgr;	// Resource manager interface.	
	ISimpleLog			*m_pLog;		// log interface
	IUnknown			*m_punkDTC;		// DTC

	BOOL m_bTMDown;
	WorkerSet m_setWorkers;
	CRmOptions m_options;

public:
	BOOL IsTMDown(){return m_bTMDown;}
	void SetTMDown(BOOL bDown){m_bTMDown = bDown;}

	HRESULT TmUp();
	HRESULT GetMyTmWhereAbouts();
	ISimpleLog * GetLog(BOOL bAddRef = FALSE)
	{
		if (m_pLog)
		{
			if (bAddRef) m_pLog -> AddRef();
		}

		return m_pLog;

	}
	IResourceManager * GetIResourceManager(BOOL bAddRef = FALSE)
	{
		if (m_pIResMgr)
		{
			if (bAddRef) m_pIResMgr -> AddRef();
		}
		return m_pIResMgr;

	}
	IUnknown * GetDTCUnknown(BOOL bAddRef = FALSE)
	{
		if (m_punkDTC)
		{
			if (bAddRef) m_punkDTC -> AddRef();		
		}
		return m_punkDTC;
	}



	HRESULT OpenLog();
	HRESULT Recover();
	HRESULT InitializeRm();

	CFileRm()
	{
		m_cbTmAddr = 0;
		m_rgbTmAddr = NULL;
		m_punkDTC = NULL;
		m_pIResMgr = NULL;
		m_bTMDown = FALSE;

	}
	

	IRmWorker * GetWorker(long lHandle)
	{
		_ASSERTE(lHandle);
		IRmWorker * pWorker  = NULL;		
		pWorker = (IRmWorker *)(*m_setWorkers.find(lHandle));
		return pWorker;

		//return (IRmWorker *)lHandle;		
	}	

	~CFileRm()
	{
		WorkerSet::iterator item = m_setWorkers.begin();
		IUnknown * pUnk;
		while (item != m_setWorkers.end())
		{
			pUnk = (IUnknown *)(*item); // get the value
			SafeRelease(pUnk);
			item++;
		}
		m_setWorkers.clear();

		if (m_cbTmAddr)
			delete m_rgbTmAddr;
	}

	DECLARE_CLASSFACTORY_SINGLETON(CFileRm);
	DECLARE_PROTECT_FINAL_CONSTRUCT();
	DECLARE_REGISTRY_RESOURCEID(IDR_FILERM)
	DECLARE_NOT_AGGREGATABLE(CFileRm)

BEGIN_COM_MAP(CFileRm)
	COM_INTERFACE_ENTRY(IFileRm)	
END_COM_MAP()

	HRESULT FinalConstruct();
// IFileRm

	STDMETHOD(GetTmWhereabouts)(long lConHandle, BYTE **rgbTmAddr, ULONG *pcbTmAddr);
	STDMETHOD(ExportTx)(long lConHandle, ULONG cbTranCookie, BYTE *rgbTranCookie);
	STDMETHOD(Connect)(BSTR sAppName, long * ulConnHandle);
	STDMETHOD(Disconnect)(long ulConnHandle);
	STDMETHOD(FileCopyTx)(long lConHandle, BSTR sSource, BSTR sDestination, BOOL bFailIfExists);
	STDMETHOD(FileRenameTx)(long lConHandle, BSTR sSource, BSTR sDestination);
	STDMETHOD(AddFile)(long lConHandle, BSTR sSource, BSTR sDestination);
	STDMETHOD(CopyListTx)(long lConHandle);
	STDMETHOD(FileMoveTxt)(long lConHandle, BSTR sSource, BSTR sDestination);
	STDMETHOD(FileDeleteTx)(long lConHandle, BSTR sFileName);
	STDMETHOD(ResetConnection)(long lConHandle);
	
// IFileRm
public:
	STDMETHOD(TMDown)();
	HRESULT FinalRelease();
	
	
};

#endif //__FILERM_H_
