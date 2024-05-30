//-----------------------------------------------------------------------------
//
// File:		Handler.cpp
//
// Copyright:	Copyright (c) 1997-1999 Microsoft Corporation
//
// Contents:	Implementation of CHandler.
//
// Comments:
//
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include <assert.h>
#include "adoint.h"
#include "adoid.h"
#include "Handler.h"
#include "util.h"


// Directly open an ADO connection instance
static HRESULT DoADOConnect( BSTR bstrConnection, _Connection **ppADOConnection )
{
	assert(bstrConnection != NULL);
	assert(ppADOConnection != NULL);
	HRESULT hr;

	// Create an ADO Connection instance.
	hr = CoCreateInstance(CLSID_CADOConnection, NULL, CLSCTX_ALL,
		__uuidof(_Connection), (LPVOID *)ppADOConnection);
	if (FAILED(hr))
		return hr;
	assert(*ppADOConnection != NULL);

	// Set the cursor location.
	hr = (*ppADOConnection)->put_CursorLocation(adUseClientBatch);
	if (FAILED(hr))
		return hr;

	// Open the connection.
	return (*ppADOConnection)->Open(bstrConnection, NULL, NULL, -1L);
}


// Create and open an ADO Recordset directly from ADO.
static HRESULT GetADORecordset(_Connection *pConn, BSTR bstrQuery, _Recordset **pprs )
{
	assert(pConn != NULL);
	assert(bstrQuery != NULL);
	assert(pprs != NULL);
	VARIANT vConnection, vQuery;
	HRESULT hr;


	// create an ADO recordset
	hr = CoCreateInstance(CLSID_CADORecordset, NULL, CLSCTX_ALL,
		__uuidof(_Recordset), (LPVOID *)pprs);
	if (FAILED(hr))
		return hr;
	assert(*pprs != NULL);

	// Set the cursor location.
	hr = (*pprs)->put_CursorLocation(adUseClientBatch);
	if (FAILED(hr))
		return hr;

	// Setup the variant parameter for Query string
	VariantInit(&vQuery);
	vQuery.vt = VT_BSTR;
	vQuery.bstrVal = bstrQuery;

	// Setup the variant parameter for connection
	VariantInit(&vConnection);
	vConnection.vt = VT_UNKNOWN;
	vConnection.punkVal = pConn;

	// Open the query
	return (*pprs)->Open(
		vQuery,
		vConnection,
		adOpenUnspecified,
		adLockBatchOptimistic,
		adCmdUnspecified);
}


// Reconnect a Recordset to a Connection directly via ADO.
static HRESULT ADOReconnect(
	_Recordset *pADORecordset,
	_Connection *pConn)
{
	assert(pADORecordset != NULL);
	assert(pConn != NULL);

	// Set the new active connection for the recordset
	return pADORecordset->putref_ActiveConnection(pConn);
}


CHandler::CHandler()
{
}


STDMETHODIMP CHandler::GetRecordset( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ BSTR query,
            /* [out, retval] */ _Recordset **ppRS)
{
	HRESULT hr;
	BSTR query2 = SysAllocString(query ? query : L"");

	try
	{
		CUtilComPtr<IErrorInfo> pErrorInfo;

		{
			CUtilComPtr<_Connection> pConn;

			*ppRS = NULL;
			hr = OpenConnection(conn, args, 2, &query2, &pConn);
			if (SUCCEEDED(hr))
				hr = GetADORecordset(pConn, query2, ppRS);

			if (FAILED(hr))
			{
				//Get ADO's error info from OLE, then give it back
				if (GetErrorInfo(0, &pErrorInfo) == S_OK)
					SetErrorInfo(0, pErrorInfo);
				if (*ppRS)
				{
					(*ppRS)->Release();
					*ppRS = NULL;
				}
			}
		}
		if (FAILED(hr))
		{
			//ADO cleared out the error info when the Connect object died. Reset it here.
			SetErrorInfo(0, pErrorInfo);
		}
	}
	catch(HRESULT hrCaught)
	{
		hr = hrCaught;
	}
	catch(...)
	{
		hr = E_FAIL;
	}
	SysFreeString(query2);
	return hr;
}

        
STDMETHODIMP CHandler::Reconnect( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ _Recordset *pRS)
{
	HRESULT hr;

	try
	{
		CUtilComPtr<IErrorInfo> pErrorInfo;

		{
			CUtilComPtr<_Connection> pConn;

			hr = OpenConnection(conn, args, 1, NULL, &pConn);
			if (SUCCEEDED(hr))
				hr = ADOReconnect(pRS, pConn);

			if (FAILED(hr))
			{
				//Get ADO's error info from OLE, then give it back
				if (GetErrorInfo(0, &pErrorInfo) == S_OK)
					SetErrorInfo(0, pErrorInfo);
			}
		}
		if (FAILED(hr))
		{
			//ADO cleared out the error info when the Connect object died. Reset it here.
			SetErrorInfo(0, pErrorInfo);
		}
	}
	catch(HRESULT hrCaught)
	{
		hr = hrCaught;
	}
	catch(...)
	{
		hr = E_FAIL;
	}
	return hr;
}


//
// This function is new for MDAC 2.1
// The 2.1 Data Factory will only call this function for 2.1 clients using "MS Remote".
// The 2.1 Data Factory will still use the other 2 functions for 2.0 clients and for 2.1
//    clients using "DFMode=20".
//
STDMETHODIMP CHandler::OpenConnection( 
			/* [in] */ BSTR conn,
			/* [in] */ BSTR args,
			/* [in] */ long lFlags,  // 1=WriteAccess, 2=ModifyQuery
			/* [in, out] */ BSTR * pQuery,
			/* [out, retval] */ _Connection **ppConnection)
{
	HRESULT hr;

	try
	{
		CUtil util;
		CUtilComPtr<_Connection> pConn;

		*ppConnection = NULL;
		util.SetIniFile(args);
		util.SetConn(conn);
		if (!util.HasReadAccess())
			util.RaiseError(HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED));
		if (lFlags & 1)  // For ReadWrite
		{
			if (!util.HasWriteAccess())
				util.RaiseError(HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED));
		}

		if ((lFlags & 2) && pQuery)
		{
			// For GetRecordset(), etc.
			if (*pQuery)
			{
				util.SetSql(*pQuery);
				SysFreeString(*pQuery);
			}
			else
				util.SetSql(L"");
			*pQuery = SysAllocString(util.GetSql());
		}

		WCHAR *pwsz = util.GetConn();
		CUtilBSTR bstrConn(pwsz);
		hr = DoADOConnect(bstrConn, &pConn);
		if (SUCCEEDED(hr))
			*ppConnection = pConn.Detach();
	}
	catch(HRESULT hrCaught)
	{
		hr = hrCaught;
	}
	catch(...)
	{
		hr = E_FAIL;
	}
	return hr;
}


STDMETHODIMP CHandler::InterfaceSupportsErrorInfo(REFIID riid)
{
	if (IsEqualGUID(riid, IID_IDataFactoryHandler))
		return S_OK;
	return S_FALSE;
}

