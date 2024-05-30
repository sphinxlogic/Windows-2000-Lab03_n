
/******************************************************************************\
********************************************************************************
* Filename: TxSink.cpp
*
* Description: Sink for Tx events
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
#include "mtsspyctl.h"
#include "mtsevents.h"
#include "MtsAudit.h"
#include "MTSSpy.h"
#include "MtsSink.h"
#include "packagesink.h"
#include "PackageInfo.h"
#include "TxSink.h"


/////////////////////////////////////////////////////////////////////////////
// CTxSink

STDMETHODIMP CTxSink::OnTransactionStart(LONGLONG perfCount, REFGUID guidTx, REFGUID tsid, BOOL fRoot)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnTransactionStart"), m_sPackageName);

    CComBSTR sGuidTx = GuidToBstr(guidTx);
    CComBSTR sTsid = GuidToBstr(tsid);
	m_pSpy -> AddParamValueToList(L"GuidTx", sGuidTx);	
	m_pSpy -> AddParamValueToList(L"tsid", sTsid);	
	m_pSpy -> AddParamValueToList(L"Is a Root Tx?", fRoot ? L"Yes" : L"No");
	IF_AUDIT_DO(OnTransactionStart)(perfCount,							
									  sGuidTx,						
									  sTsid,
									  fRoot);
									  
	return S_OK;
}

STDMETHODIMP CTxSink::OnTransactionPrepared(LONGLONG perfCount, REFGUID guidTx, BOOL fVoteYes)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnTransactionPrepared"), m_sPackageName);
    CComBSTR sGuidTx = GuidToBstr(guidTx);
    m_pSpy -> AddParamValueToList(L"GuidTx", sGuidTx);
	m_pSpy -> AddParamValueToList(L"Vote",  fVoteYes == TRUE ? L"Yes" : L"No");
	IF_AUDIT_DO(OnTransactionPrepared)(perfCount,							
									  sGuidTx,						
									  fVoteYes);
	return S_OK;
}

STDMETHODIMP CTxSink::OnTransactionAborted(LONGLONG perfCount, REFGUID guidTx)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnTransactionAborted"), m_sPackageName);
    CComBSTR sGuidTx = GuidToBstr(guidTx);
    m_pSpy -> AddParamValueToList(L"GuidTx", sGuidTx);
	IF_AUDIT_DO(OnTransactionAborted)(perfCount, sGuidTx);
	return S_OK;
}

