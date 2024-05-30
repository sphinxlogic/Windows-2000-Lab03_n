
/******************************************************************************\
********************************************************************************
* Filename: UserSink.h
*
* Description: Declaration of the CUserSink -- for user defined events
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
#ifndef __USERSINK_H__
#define __USERSINK_H__

#include "resource.h"       // main symbols

class CMtsSpy;
/////////////////////////////////////////////////////////////////////////////
// CUserSink 
class ATL_NO_VTABLE CUserSink : 
	public CMtsSink,
	public IMtsUserEvent
{
public:

	CUserSink(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CUserSink()
	{
		m_pSpy = NULL;
	}

DECLARE_NOT_AGGREGATABLE(CUserSink)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CUserSink)
	COM_INTERFACE_ENTRY(IMtsUserEvent)
	COM_INTERFACE_ENTRY_CHAIN(CMtsSink)
END_COM_MAP()

virtual REFIID GetIID(){return IID_IMtsUserEvent;}
STDMETHODIMP GetSinkType(EventEnum * e){*e = User;return S_OK;}

STDMETHODIMP OnUserEvent(LONGLONG perfCount, VARIANT * var)
{
	if (var -> vt == VT_BSTR)
	{
		m_pSpy -> AddEventToList(perfCount, _TEXT("OnUserEvent"), m_sPackageName);
		m_pSpy -> AddParamValueToList(L"String Value",  var->bstrVal);	
	}
	else if (var -> vt == VT_UNKNOWN)
	{
		IMtsEventInfo * pInfo = NULL;
		var -> punkVal -> QueryInterface(IID_IMtsEventInfo, (void **)&pInfo);
		if (pInfo)
		{
			CComBSTR s;
			pInfo -> get_DisplayName(&s.m_str);
			m_pSpy -> AddEventToList(perfCount, s.m_str, m_sPackageName);	

			long lCount;
			pInfo -> get_Count(&lCount);
			if (lCount)
			{
				VARIANT var;
				LPOLESTR * pKeys = new LPOLESTR[lCount+1];
				IUnknown * pUnk = NULL;
				pInfo -> get_Names(&pUnk);
				_ASSERTE(pUnk);
				IEnumString * pEnum;
				pUnk -> QueryInterface(IID_IEnumString, (void **)&pEnum);
				_ASSERTE(pEnum);
				pUnk -> Release();
				ULONG lFetched;
				pEnum -> Next(lCount, pKeys, &lFetched);
				pEnum -> Release();				
				_ASSERTE(lFetched == lCount);
				int i;
				for (i=0; i<lFetched; i++)
				{
					s = pKeys[i];
					pInfo -> get_Value(s, &var);
					if (var.vt == VT_BSTR)
					{
						m_pSpy -> AddParamValueToList(pKeys[i],  var.bstrVal);	
						VariantClear(&var);
					}
				}
				for (i=0;i<lCount;i++)
					CoTaskMemFree(pKeys[i]);

				delete pKeys;
			}
			pInfo -> Release();
		}
	}
	else
		m_pSpy -> AddEventToList(perfCount, _TEXT("OnUserEvent"), m_sPackageName);
	return S_OK;
}

};

#endif //__USERSINK_H__
