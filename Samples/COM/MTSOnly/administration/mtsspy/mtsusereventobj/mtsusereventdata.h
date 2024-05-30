
/******************************************************************************\
********************************************************************************
* Filename: MtsUserEventData.h
*
* Description: Declaration of the CMtsUserEventDat
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

#ifndef __MTSUSEREVENTDATA_H_
#define __MTSUSEREVENTDATA_H_

#include "resource.h"       // main symbols
#include "mtsevents.h"
class CNameValue
{
public:
	CComBSTR m_sName;
	CComVariant m_sValue;
	CNameValue();
	CNameValue(LPTSTR sName, VARIANT * pVar)
	{
		m_sName = sName;
		m_sValue = *pVar;
	}

};

typedef list<CNameValue *> NameValueList;
/////////////////////////////////////////////////////////////////////////////
// CMtsUserEventData
class ATL_NO_VTABLE CMtsUserEventData : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMtsUserEventData, &CLSID_MtsUserEventData>,
	public IDispatchImpl<IMtsUserEventData, &IID_IMtsUserEventData, &LIBID_MTSUSEREVENTOBJLib>,
	public IDispatchImpl<IMtsEventInfo, &IID_IMtsEventInfo, &LIBID_MTSEVENTSLib>

{

private:

		CComBSTR m_sDisplayName;
		CComBSTR m_sEventID;
		NameValueList m_list;

public:
	CMtsUserEventData()
	{
	}
	~CMtsUserEventData();
DECLARE_REGISTRY_RESOURCEID(IDR_MTSUSEREVENTDATA)

BEGIN_COM_MAP(CMtsUserEventData)
	COM_INTERFACE_ENTRY(IMtsUserEventData)
	COM_INTERFACE_ENTRY2(IDispatch, IMtsEventInfo)
	COM_INTERFACE_ENTRY(IMtsEventInfo)
END_COM_MAP()


	STDMETHOD(get_DisplayName)(BSTR * sDisplayName);
	STDMETHOD(get_EventID)(BSTR * sGuidEventID);
	STDMETHOD(get_Count)(long * lCount);
	STDMETHOD(get_Value)(BSTR sKey, VARIANT * pVal);
	STDMETHOD(get_Names)(IUnknown ** pUnk);
	

// IMtsUserEventData
public:
	STDMETHOD(put_Value)(BSTR sKey, /*[in]*/ VARIANT * newVal);
	STDMETHOD(put_GuidEventId)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_DisplayName)(/*[in]*/ BSTR newVal);
};

#endif //__MTSUSEREVENTDATA_H_
