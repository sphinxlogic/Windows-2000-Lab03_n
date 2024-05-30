
/******************************************************************************\
********************************************************************************
* Filename: irmworkerpriv.cpp
*
* Description:  Contains the "Private" interface that the RM uses to communicate
				with the worker
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
#include "..\..\..\common\inc\RmWorker.h"
#include "txdtc.h"
#include "txcoord.h"
#include "xolehlp.h"
#include "..\..\..\common\inc\simplelog.h"
#include "action.h"
#include "..\..\..\common\inc\copyfilerm.h"
#include "RmWorkerObj.h"




STDMETHODIMP CRmWorkerObj::SetState(TXSTATE eState)
{
	m_eTxState = eState;
	return S_OK;

} // CRmWorkerObj:SetState


STDMETHODIMP CRmWorkerObj::GetState(TXSTATE *eState)
{
	*eState = m_eTxState;
	return S_OK;

} // CRmWorkerObj::GetState()

STDMETHODIMP CRmWorkerObj::CleanupTx(void)
{
	BOOL	fReturn;

	// Set state to initializing new transaction
	SetState (TX_INITIALIZING);

	// Cleanup all interfaces and objects used by transaction
	if (m_pITx)
		m_pITx->Release ();

	m_pITx = NULL;


	fReturn = RemoveAction();
 
	HRESULT hr = WriteLog (m_guidTx, LOG_RM_XACT_END, RM_NONE, 0, 0);
	_ASSERTE(hr == S_OK);
	return S_OK;

} // CRmWorkerObj::CleanupTx()

//
//	if we get a request to enlist on a tx, and we haven't finished
//	the privious tx (usually do to an async abort), then we have
//	to wait until the tx is done
//
STDMETHODIMP CRmWorkerObj::WaitTxDone(void)
{
	_ASSERTE(m_hFinishedTxEvent);
	DWORD		dwWaitRc = 0;
	dwWaitRc = WaitForSingleObject (m_hFinishedTxEvent, INFINITE);
	_ASSERTE (WAIT_FAILED != dwWaitRc);
	return S_OK;

} // CRmWorkerObj::WaitTxDone()


STDMETHODIMP CRmWorkerObj::PrepareTx (void)
{
	BOOL			fRc				= TRUE;
	HRESULT			hRc				= S_OK;
	IPrepareInfo	*pIPrepareInfo	= 0;
	BYTE			*rgbPrepareInfo	= 0;
	ULONG			cbPrepareInfo	= 0;
	TCHAR			rgbSizeBuf[sizeof(ULONG)+1];
	

	hRc = m_pEnlist->QueryInterface (IID_IPrepareInfo,
									 (LPVOID *) &pIPrepareInfo);
	_ASSERTE (S_OK == hRc);
	_ASSERTE (0 != pIPrepareInfo);
	if (S_OK != hRc)
	{
		SetStatus (RM_STATUS_INTERFACE);
		return E_FAIL;
	} // if -- QueryInterface failed
	else
	{
		pIPrepareInfo->GetPrepareInfoSize (&cbPrepareInfo);
		_ASSERTE (0 != cbPrepareInfo);

		// Allocate storage for prepare info
		rgbPrepareInfo = (BYTE *) CoTaskMemAlloc (cbPrepareInfo);
		_ASSERTE (0 != rgbPrepareInfo);
		if (0 == rgbPrepareInfo)
		{
			// Error message -- no memory
			pIPrepareInfo->Release ();
			pIPrepareInfo = 0;

			SetStatus (RM_STATUS_NO_MEMORY);
			return E_FAIL;
		} // if

		memset( (LPVOID) rgbPrepareInfo, '\0', cbPrepareInfo);
		pIPrepareInfo->GetPrepareInfo ( (UCHAR *) rgbPrepareInfo);

		pIPrepareInfo->Release ();
		pIPrepareInfo = 0;

		// CAUTION:  The rgbPrepareInfo byte stream is assumed to be a null terminated
		//			 character string.  If this is not so the log write will fail.
		wsprintf (rgbSizeBuf, L"%ld", cbPrepareInfo);
		HRESULT hr = WriteLog (m_guidTx, LOG_RM_XACT_PREPARE, RM_NONE, (TCHAR *) rgbSizeBuf, (TCHAR *) rgbPrepareInfo);		
		if (hr != S_OK)
		{
			_ASSERTE(0);
			// Error message -- could not write prepare record
			CoTaskMemFree ((LPVOID) rgbPrepareInfo);

			SetStatus (RM_STATUS_LOG_ERROR);
			return E_FAIL;
		} //
	} // if -- QueryInterface succeeded.

	CoTaskMemFree ((LPVOID) rgbPrepareInfo);
	return S_OK;

} // CRmWorkerObj::PrepareTx()



STDMETHODIMP CRmWorkerObj::CommitTx (void)
{
	
	HRESULT hr = WriteLog (m_guidTx, LOG_RM_XACT_COMMIT, RM_NONE, 0, 0);
	if (hr != S_OK)
	{
		_ASSERTE(0);
		SetStatus (RM_STATUS_LOG_ERROR);
		return E_FAIL;
	} // if

//
//	we need to go through the action list to see if we 
//	created any temp files and if we need, we delete them
//

	CleanupAction (TRUE);
	return S_OK;

} // CRmWorkerObj::CommitTx()


STDMETHODIMP CRmWorkerObj::AbortTx (void)
{
	HRESULT	hr = S_OK;

	// Write begin undo record to the log
	hr = WriteLog (m_guidTx, LOG_RM_PRIVATE, RM_UNDO_BEGIN, 0, 0);
	if (hr != S_OK)
	{
		_ASSERTE(0);
		return E_FAIL;
	} // if

	// Undo all action for the current transaction.
	hr = RollbackTx ();
	_ASSERTE (S_OK == hr);
	if (S_OK == hr)
	{
		CleanupAction ();
	} // if
	return hr;

} // CRmWorkerObj::AbortTx()

STDMETHODIMP CRmWorkerObj::GetDTCUnknown(IUnknown ** pUnk)
{
	*pUnk = NULL;
	if (!m_pEnlist)
	{
		_ASSERTE(0);
		return E_UNEXPECTED;
	}
	HRESULT hr = m_pEnlist -> QueryInterface(IID_IUnknown, (void **)pUnk);	
	_ASSERTE(*pUnk);
	return hr;	

}