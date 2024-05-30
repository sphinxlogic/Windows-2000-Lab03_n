
/******************************************************************************\
********************************************************************************
* Filename: CpyImageObj.h
*
* Description: Declaration of the CCpyImageObj
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
// CCpyImageObj
class CCpyImageObj : 
	public CComObjectRoot,
	public CComCoClass<CCpyImageObj, &CLSID_CpyImage>,
	public ISupportErrorInfo,
	public IDispatchImpl<ICpyImage, &IID_ICpyImage, &LIBID_CPYIMAGELib>
{

private:

		IMtsEvents * m_pEvents; // for tracing

public:

BEGIN_COM_MAP(CCpyImageObj)
	COM_INTERFACE_ENTRY(ICpyImage)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()	

	CCpyImageObj()
	{

		HRESULT hr;
		m_pEvents = NULL;

		IMTSLocator * pLocator = NULL;
		hr = CoCreateInstance(CLSID_CoMTSLocator, NULL, CLSCTX_INPROC, IID_IMTSLocator, (void **)&pLocator);
		if (hr == S_OK)
		{
			IUnknown * pUnk = NULL;

			pLocator -> GetEventDispatcher(&pUnk);

			if (pUnk)
			{
				pUnk -> QueryInterface(IID_IMtsEvents, (void **)&m_pEvents);
				pUnk -> Release();
			}
			pLocator -> Release();
		}
	}
	~CCpyImageObj()
	{
	
		if (m_pEvents) m_pEvents -> Release();
	}



DECLARE_REGISTRY_RESOURCEID(IDR_CpyImage)



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICpyImage
public:
	BOOL CreateTable(HSTMT hstmt, BSTR * msg);
	void MtsTrace(BSTR sMsg);
	void MtsTraceObject(BSTR sDisplayName, BSTR sVal);


	STDMETHOD(InsertData)(BSTR sFromFile, BSTR sToFile, 
						   BSTR sDescription, BSTR sMainColor, 
						   BSTR sTheme, BSTR * msg);

		
		STDMETHOD(SetComplete)();
		STDMETHOD(SetAbort)();

		STDMETHOD(Test)(BSTR * msg);
};




	
