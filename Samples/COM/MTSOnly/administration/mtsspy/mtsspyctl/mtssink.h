
/******************************************************************************\
********************************************************************************
* Filename: MtsSink.h
*
* Description: Root object declaration for all sinks.  Does the Advise/Unadvise
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

#ifndef __MTSSINK_H_
#define __MTSSINK_H_

#include "resource.h"       // main symbols

class CMtsSpy;

/////////////////////////////////////////////////////////////////////////////
// CMtsSink
class ATL_NO_VTABLE CMtsSink : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IMtsSink
{
protected:
		IConnectionPointContainer * m_pCPC;
		DWORD m_dwAdviseCookie;
		CComBSTR m_sPackageName;
		IConnectionPoint * m_pConPt;
		BOOL m_bReadyForDelete;
		
public:

	CMtsSpy * m_pSpy;
	void SetSpyObj(CMtsSpy * pSpy)
	{
		m_pSpy = pSpy;
	}

	CMtsSink()
	{
		m_dwAdviseCookie = 0;
		m_pConPt = NULL;
		m_pCPC = NULL;
		m_bReadyForDelete = FALSE;
	}
	~CMtsSink()
	{
		if (m_dwAdviseCookie)
		{
			DAdvise();
			m_dwAdviseCookie = NULL;
		}

		SafeRelease(m_pConPt);
		SafeRelease(m_pCPC);
	}

	
	

DECLARE_REGISTRY_RESOURCEID(IDR_MTSSINK)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CMtsSink)
	COM_INTERFACE_ENTRY(IMtsSink)
END_COM_MAP()

virtual REFIID GetIID() = 0;
// IMtsSink
public:
	STDMETHOD(get_DeleteFlag)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_DeleteFlag)(/*[in]*/ BOOL newVal);
	STDMETHOD(GetSinkType)(EventEnum * e) = 0; // must override
	STDMETHOD(DAdvise)();
	STDMETHOD(Advise)();
	STDMETHOD(Init)(IConnectionPointContainer * pConPt, LPWSTR sPackageName);
};


#endif //__MTSSINK_H_
