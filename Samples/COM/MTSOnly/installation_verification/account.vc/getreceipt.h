// Filename: GetReceipt.h
//
// Description: Declaration of GetReceipt
//
// This file is provided as part of the Microsoft Transaction Server Samples
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 Microsoft Corporation, All rights reserved

#if !defined(AFX_GETRECEIPT_H__A81260B3_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
#define AFX_GETRECEIPT_H__A81260B3_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetReceipt

class CGetReceipt : 
	public CComDualImpl<IGetReceipt, &IID_IGetReceipt, &LIBID_ACCOUNT>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CGetReceipt,&CLSID_CGetReceipt>
{
public:
	CGetReceipt() {}
BEGIN_COM_MAP(CGetReceipt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IGetReceipt)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CGetReceipt) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_GetReceipt)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGetReceipt
public:
	STDMETHOD (GetNextReceipt) (OUT long* plReceiptNo);
};

#endif // !defined(AFX_GETRECEIPT_H__A81260B3_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
