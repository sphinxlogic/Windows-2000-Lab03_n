//-----------------------------------------------------------------------------
//
// File:		HANDLER.h
//
// Copyright:	Copyright (c) 1997-1999 Microsoft Corporation
//
// Contents:	Definition of the CHandler class
//
// Comments:
//
//-----------------------------------------------------------------------------

#if !defined(AFX_HANDLER_H__A1A6B99E_497F_11D1_9217_00C04FBBBFB3__INCLUDED_)
#define AFX_HANDLER_H__A1A6B99E_497F_11D1_9217_00C04FBBBFB3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "adoint.h"
#include "msdfhdl.h"
#include "msdfmap.h"

#define MSDFMAP_PROGID     "MSDFMAP_VC.Handler"
#define MSDFMAP_PROGIDVER  "MSDFMAP_VC.Handler.1"

/////////////////////////////////////////////////////////////////////////////
// CHandler

class CHandler : 
	//public CComDualImpl<IDataFactoryHandler, &IID_IDataFactoryHandler, &LIBID_MSDFMAPLib>, 
	public CComObjectRoot,
	public CComCoClass<CHandler, &CLSID_Handler>,
	public IDataFactoryHandler,
	public ISupportErrorInfo
{
public:
	CHandler();

BEGIN_COM_MAP(CHandler)
	//COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IDataFactoryHandler)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CHandler) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

//DECLARE_REGISTRY_RESOURCEID(IDR_Handler1)
DECLARE_REGISTRY(CLSID_Handler, MSDFMAP_PROGIDVER, MSDFMAP_PROGID, IDS_HANDLER_DESC1, THREADFLAGS_BOTH)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IDataFactoryHandler
	STDMETHODIMP GetRecordset( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ BSTR query,
            /* [out][retval] */ _Recordset **ppRS);
	STDMETHODIMP Reconnect( 
            /* [in] */ BSTR conn,
            /* [in] */ BSTR args,
            /* [in] */ _Recordset *pRS);
	STDMETHODIMP OpenConnection(
			/* [in] */ BSTR conn,
			/* [in] */ BSTR args,
			/* [in] */ long lFlags,  // 1=WriteAccess, 2=ModifyQuery
			/* [in, out] */ BSTR * pQuery,
			/* [out, retval] */ _Connection **ppConnection);

private:
};

#endif // !defined(AFX_HANDLER_H__A1A6B99E_497F_11D1_9217_00C04FBBBFB3__INCLUDED_)
