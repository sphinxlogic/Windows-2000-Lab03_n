
/******************************************************************************\
********************************************************************************
* Filename: TxSink.h
*
* Description: Declaration of the CTxSink -- the Tx events
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


#ifndef __TXSINK_H_
#define __TXSINK_H_

#include "resource.h"       // main symbols

class CMtsSpy;
/////////////////////////////////////////////////////////////////////////////
// CTxSink 
class ATL_NO_VTABLE CTxSink : 
	public CMtsSink,
	public IMtsTransactionEvents
{
public:

	CTxSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CTxSink()
	{
		m_pSpy = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TXSINK)
DECLARE_NOT_AGGREGATABLE(CTxSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CTxSink)
	COM_INTERFACE_ENTRY(IMtsTransactionEvents)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

virtual REFIID GetIID(){return IID_IMtsTransactionEvents;}
public:
STDMETHOD (OnTransactionStart)(LONGLONG perfCount, REFGUID guidTx, REFGUID tsid, BOOL fRoot);
STDMETHOD (OnTransactionPrepared)(LONGLONG perfCount, REFGUID guidTx, BOOL fVoteYes);
STDMETHOD (OnTransactionAborted)(LONGLONG perfCount, REFGUID guidTx);

STDMETHODIMP GetSinkType(EventEnum * e){*e = Transaction;return S_OK;}

};

#endif //__TXSINK_H_
