/*+==========================================================================
  File:      Order.h
  Summary:   Declaration of COrder class
  Classes:   Declared: COrder
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

#ifndef __ORDER_H_
#define __ORDER_H_

#include "resource.h"       // main symbols

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  ObjectClass: COrder
  Summary:	   Writes an order into the Order Entry table.
			   Sends order to shipping department.
  Interfaces:  IUnknown				Standard COM object feature interface
               IDispatch			Automation interface
	           IOrder				Represents an order
  Aggregation: Not supported
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/  

class ATL_NO_VTABLE COrder : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COrder, &CLSID_Order>,
	public IDispatchImpl<IOrder, &IID_IOrder, &LIBID_QCORDERLib>
{
public:
	COrder() : m_lCustomerId(0), m_lOrderId(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ORDER)
DECLARE_NOT_AGGREGATABLE(COrder)

BEGIN_COM_MAP(COrder)
	COM_INTERFACE_ENTRY(IOrder)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public: // IOrder methods
	STDMETHOD(Process)(long lFlags);
	STDMETHOD(LineItem)(long lItemId, long lQuantity);
	STDMETHOD(put_OrderId)(long lOrderId);
	STDMETHOD(put_CustomerId)(long lCustomerId);

private: // Member data and private helper methods
	long				m_lCustomerId;
	long				m_lOrderId;
	std::vector<long>	m_veclItemId;
	std::vector<long>	m_veclQuantity;

	HRESULT	WriteOrderDB();
	HRESULT	InvokeShip(long lFlags);
	HRESULT	InvokeShipIDispatch(IUnknown * punk, long lFlags);
	HRESULT	InvokeShipVtable(IUnknown * punk, long lFlags);
};

#endif //__ORDER_H_
