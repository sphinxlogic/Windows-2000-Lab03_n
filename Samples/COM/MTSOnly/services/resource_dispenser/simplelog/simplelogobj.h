
/******************************************************************************\
********************************************************************************
* Filename: SimpleLogObj.h
*
* Description: Declaration of the CSimpleLogObj
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
/////////////////////////////////////////////////////////////////////////////
// CSimpleLogObj
class CSimpleLogObj : 
	public CComObjectRoot,
	public ISimpleLog, 
	public CComCoClass<CSimpleLogObj, &CLSID_CoSimpleLog>,
	public ISupportErrorInfo
{
private:

		IStorage * m_pStorage;

		TCHAR		*m_pszRecDir;		// Pointer to path name of recorvery directory.

		CComAutoCriticalSection m_CritSec;

		HRESULT ToBase64(LPVOID pv, ULONG cbStart, BSTR* pbstr);
		HRESULT FromBase64(BSTR bstr, BLOB* pblob);

		BOOL m_bInRecovery;

public:
	HRESULT GetStream(IStream **pStream, GUID &guidTx,  BOOL bCreate);
	CSimpleLogObj();
	~CSimpleLogObj();



DECLARE_REGISTRY_RESOURCEID(IDR_SimpleLogObj)

BEGIN_COM_MAP(CSimpleLogObj)
	COM_INTERFACE_ENTRY(ISimpleLog)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISimpleLog	
	STDMETHOD(WriteLog)(GUID guidTx, LOG_RM_COMMAND eOp, BYTE * pByte, long cbBytes);
	STDMETHOD(Init)(BSTR  pszLogFileName);
	STDMETHOD(RecoveryInfo)(IStorage **ppStorage);


public:
	STDMETHOD(GetStream)(GUID guidTx, /*[out]*/ IStream **ppStream);
	STDMETHOD(WriteVariantToLog)(GUID m_guidTx, VARIANT *pVariant);
	STDMETHOD(RemoveTxStream)(GUID guidTx);
	STDMETHOD(WriteStreamToLog)(GUID GuidTx, LOG_RM_COMMAND eOp, IStream * pStream);
};
