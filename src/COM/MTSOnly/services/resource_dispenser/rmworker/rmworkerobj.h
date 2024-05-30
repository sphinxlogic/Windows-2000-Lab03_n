
/******************************************************************************\
********************************************************************************
* Filename: RmWorkerObj.h
*
* Description: Declaration of the CRmWorkerObj
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

#include "resource.h"       // main symbols

typedef struct tagFILECPY
{
	 CComBSTR sSource;
	 CComBSTR sDest;
} FILECPY, FAR * LPFILECPY;


//extern ULONG RM_STATUS_BASE = 0x81000000;


typedef struct tagRECOVERY_RECORD
{
	GUID						guidTxn;		// Transaction identifier.
	RECOVERY_STATE				eRecState;		// Recovery state of transaction
	CActionList					*actionList;	// Action list for 
												// transaction.
} RECOVERY_RECORD;

typedef list <FILECPY *> FILECPYLIST;
typedef list <RECOVERY_RECORD *> RECOVERY_LIST;
/////////////////////////////////////////////////////////////////////////////
// CRmWorkerObj
class CRmWorkerObj : 
	public CActionList,
	public CComObjectRoot,
	public IRmWorkerPriv,
	public ITransactionResourceAsync, // DTC Callback	
	public CComCoClass<CRmWorkerObj, &CLSID_CRmWorkerObj>,
	public IRmWorker
{

private:

	ISimpleLog * m_pLog;
	HANDLE m_hFinishedTxEvent;
	CComBSTR m_sRecoverDir;	
	CComBSTR m_sAppName;
	
public:
	HRESULT WriteLog(GUID guidTx, LOG_RM_COMMAND eOp, FILE_OPERATION fOp, BSTR sFromFile, BSTR sToFile);
	HRESULT WriteLog(GUID txID, CAction * pAction);
	HRESULT GetTempFile(TCHAR * pFileName);
	ITransactionEnlistmentAsync	*m_pEnlist;		
	CRmWorkerObj();
	~CRmWorkerObj();

	
DECLARE_REGISTRY_RESOURCEID(IDR_RmWorkerObj)

BEGIN_COM_MAP(CRmWorkerObj)
	COM_INTERFACE_ENTRY(IRmWorker)
	COM_INTERFACE_ENTRY(IRmWorkerPriv)
	COM_INTERFACE_ENTRY(ITransactionResourceAsync)	
END_COM_MAP()

	FILECPYLIST m_lstFiles;	


	STDMETHOD(WaitTxDone)(void);	

// IRmWorker

// misc functions
	STDMETHOD(Init)(IUnknown * pUnkLog, IUnknown * pUnkDtcResMgr, IUnknown *pUnkDtc, BSTR sRecDir);
	STDMETHOD(Recover)(IStorage * pStorage);
	STDMETHOD(Reset)();

// file manipulation
	STDMETHOD(FileCopyTx)(BSTR sFromFile, BSTR sToFile, BOOL bFailIfExists);
	STDMETHOD(FileRenameTx)(BSTR sFromFile, BSTR sToFile);
	STDMETHOD(FileMoveTxt)(BSTR sSource, BSTR sDestination);
	STDMETHOD(FileDeleteTx)(BSTR sFileName);

// list manipulation
	STDMETHOD(AddFile)(BSTR sSource, BSTR sDestination);
	STDMETHOD(CopyListTx)();
	

// DTC related functions
	STDMETHOD(ExportTx)(ULONG cbTranCookie, BYTE *rgbTranCookie);
	STDMETHOD(GetDTCUnknown)(IUnknown ** pUnk);

// Tx related functions	
	STDMETHOD(GetTransactionId)(BSTR * guidTx);
	

public:
// IRmWorkerPriv -- used by CITransactionResourceAsync
	STDMETHOD(PrepareTx) (void);
	STDMETHOD(CommitTx) (void);
	STDMETHOD(AbortTx) (void);	
	STDMETHOD(GetState)(TXSTATE *eState);
	STDMETHOD(SetState)(TXSTATE eState);
	STDMETHOD(CleanupTx) (void);

// ITransactionResourceAsync
	STDMETHODIMP			PrepareRequest(BOOL fRetaining, 
										   DWORD grfRM,
										   BOOL fWantMoniker,
										   BOOL fSinglePhase);
	STDMETHODIMP			CommitRequest(DWORD grfRM, XACTUOW *pNewUOW);
	STDMETHODIMP			AbortRequest(BOID *pboidReason,
										 BOOL fRetaining,
										 XACTUOW *pNewUOW);
	STDMETHODIMP			TMDown(void);

private:


	HRESULT	EnlistTx(void);
	void	 SetStatus (RMSTATUS ermStatus);
	RMSTATUS GetStatus (void);
	
	HRESULT	UndoCopy(TCHAR *sFromFile, TCHAR *sToFile);
	HRESULT	UndoMove(TCHAR *sFromFile, TCHAR *sToFile);
	HRESULT	UndoDelete(TCHAR *sFileName, TCHAR *sTmpFile);
	HRESULT	UndoRename(TCHAR *sFromFile, TCHAR *sToFile);

	// Private methods on the resource manager object.
	RECOVERYRC	RecoverTx (IStream * pStream);			// Restart recovery.
	RECOVERYRC	RecMapTransactions (IStream * pStream);	// Scan log a remap transactions.
	RECOVERY_RECORD *	RecGetTransaction (GUID& guidTxn);
										// Get recovery record for transaction.
	void	RecDiscardTransaction (GUID& guidTxn);
										// Discard transaction recovery record.
	void	RecoverCleanup (void);		// Cleanup recovery data structures.
	HRESULT	RollbackTx (void);			// Undo the current transaction.

	// Private member variables
	RMSTATUS			m_eStatus;		// Status of the last unsuccessful operation.
	TXSTATE				m_eTxState;		// Transaction state.
	IUnknown			*m_punkDTC;		// Pointer to MS DTC IUnknown.
	ITransaction		*m_pITx;		// ITransaction interface pointer.
	IResourceManager	*m_pIResMgr;
	GUID				m_guidTx;		// Global unique id for transaction.
	LONG				m_isoLevel;		// Isolation level of transaction.
	RECOVERY_LIST *m_restartList;	// List of transactions to be restarted.



public:
};
