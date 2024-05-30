/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */
/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/

#include "NumToText.h"
#include "..\..\common\debug.h"
#include "..\..\common\guid.h"



extern long g_ObjectCount; // Current Object count, so if the count goes to zero, we can shutdown


///////////////////////////////////////////////////////////////////////////
//
// CNumberToTextHandler member function
//

/**************************************************************************

   CNumberToTextHandler::CNumberToTextHandler()

**************************************************************************/

CNumberToTextHandler::CNumberToTextHandler(LPUNKNOWN pOuterpUnk)
{
	DebugTrace(TEXT("CNumberToTextHandler::CNumberToTextHandler.\r\n"));

	InitializeCriticalSection(&m_csGlobalVar);	
	m_cbBstrText=0;
	m_bstrText = NULL;
	
	m_pOuterpUnk = pOuterpUnk;

	// At this stage the Proxy manager, connecting to our Handler 
	// and our handler connecting to Proxy 
	// and the Proxy manager connecting to the Proxy is not yet fully established.
	// one should not use the interface pointer returned to us. 
	// namely, QI may not be successfully returned.
	HRESULT hr = E_FAIL;
	hr = CoGetStdMarshalEx(m_pOuterpUnk,SMEXF_HANDLER,&m_pPxyUnk);
	if(FAILED(hr))
		m_pPxyUnk = NULL;
	else
	{
		hr = m_pPxyUnk->QueryInterface(IID_IMarshal, (LPVOID *)&m_pPxyMarshal);
		if(FAILED(hr))
			m_pPxyMarshal = NULL;
		else
			Release();
	}
}

/**************************************************************************

   CNumberToTextHandler::~CNumberToTextHandler()

**************************************************************************/

CNumberToTextHandler::~CNumberToTextHandler()
{
	DebugTrace(TEXT("CNumberToTextHandler::~CNumberToTextHandler.\r\n"));
	EnterCriticalSection(&m_csGlobalVar);
	for(ULONG i=0; i< m_cbBstrText; i++)
	{
		if(m_bstrText[i] != NULL)
			SysFreeString(m_bstrText[i]);
		m_bstrText[i] = NULL;
	}
	if(m_cbBstrText)
		delete m_bstrText;
	m_bstrText =NULL;
	LeaveCriticalSection(&m_csGlobalVar);
	if(m_pPxyUnk)
	{
		m_pPxyUnk->Release();
	}
	if(m_pPxyMarshal)
	{
		AddRef();
		m_pPxyMarshal->Release();
	}
	
	DeleteCriticalSection(&m_csGlobalVar);
}



/**************************************************************************

   CNumberToTextHandler::QueryInterface

**************************************************************************/

STDMETHODIMP CNumberToTextHandler::QueryInterface(REFIID iid,void ** ppvObject)
{
   DebugTrace(TEXT("CNumberToTextHandler::QueryInterface.\r\n"));
   *ppvObject = NULL;
	return m_pOuterpUnk->QueryInterface(iid, ppvObject);
}                                             

/**************************************************************************

   CNumberToTextHandler::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CNumberToTextHandler::AddRef()
{
   DebugTrace(TEXT("CNumberToTextHandler::AddRef.\r\n"));
   return m_pOuterpUnk->AddRef();
}


/**************************************************************************

   CNumberToTextHandler::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CNumberToTextHandler::Release()
{
	DebugTrace(TEXT("CNumberToTextHandler::Release.\r\n"));
	return m_pOuterpUnk->Release();
}


/**************************************************************************

   CNumberToTextHandler::GetText(int iVal,BSTR *pszString);
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::GetText(int iVal,BSTR *pszString)
{
	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToTextHandler::GetText "));
	DebugTrace(TEXT(" \r\n"));
	EnterCriticalSection(&m_csGlobalVar);
	if((ULONG)iVal >= m_cbBstrText)
	{
		LeaveCriticalSection(&m_csGlobalVar);
		return E_INVALIDARG;
	}
	if(m_bstrText[iVal] != NULL)
	{
		*pszString= SysAllocString(m_bstrText[iVal]);
		LeaveCriticalSection(&m_csGlobalVar);
		return S_OK;
	}
	LeaveCriticalSection(&m_csGlobalVar);
	INumberToText *pNumToText = NULL;
	if(m_pPxyUnk ==NULL)
		return E_FAIL;

	hr = m_pPxyUnk->QueryInterface(IID_INumberToText,(LPVOID *)&pNumToText);
	if(FAILED(hr))
		return hr;
	hr = pNumToText->GetText(iVal,pszString);
	pNumToText->Release();
	if(FAILED(hr))
		return hr;

	EnterCriticalSection(&m_csGlobalVar);
	if((ULONG)iVal >= m_cbBstrText)
	{
		LeaveCriticalSection(&m_csGlobalVar);
		return E_INVALIDARG;
	}

	if(m_bstrText[iVal] == NULL)
		m_bstrText[iVal]= SysAllocString(*pszString);
	LeaveCriticalSection(&m_csGlobalVar);

	return hr;
}

/**************************************************************************

CNumberToTextHandler::GetUnmarshalClass(REFIID riid, void * pv, 
								unsigned long dwDestContext,
								void * pvDestContext, 
								unsigned long mshlflags, 
								LPCLSID pclsid) ;
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::GetUnmarshalClass(REFIID riid, void * pv, unsigned long dwDestContext,
									void * pvDestContext, unsigned long mshlflags, 
									LPCLSID pclsid)
{
	
	HRESULT hr = S_OK;
	
	DebugTrace(TEXT("CNumberToTextHandler::GetUnmarshalClass\r\n "));
	if(!m_pPxyMarshal)
		return E_NOTIMPL;

	hr = m_pPxyMarshal->GetUnmarshalClass(riid, pv, dwDestContext,pvDestContext,
											mshlflags,pclsid);
	return hr;
}

/**************************************************************************

CNumberToTextHandler::GetMarshalSizeMax(REFIID riid, void * pv, 
								unsigned long dwDestContext, 
								void * pvDestContext, 
								unsigned long mshlflags, 
								unsigned long * pSize)
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::GetMarshalSizeMax(REFIID riid, void * pv, unsigned long dwDestContext, 
									void * pvDestContext, unsigned long mshlflags, 
									unsigned long * pSize)
{

	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToTextHandler::GetMarshalSizeMax\r\n "));
	if(!m_pPxyMarshal)
		return E_NOTIMPL;

	hr = m_pPxyMarshal->GetMarshalSizeMax(riid, pv, dwDestContext,pvDestContext,mshlflags,
												pSize);
	if(IsEqualIID(riid, IID_INumberToText))
	{
		*pSize+=sizeof(DWORD);
	}
	return hr;
}

/**************************************************************************

CNumberToTextHandler::MarshalInterface(LPSTREAM pStm, REFIID riid, 
								void * pv,
								unsigned long dwDestContext, 
								LPVOID pvDestContext,
								unsigned long mshlflags)
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::MarshalInterface(LPSTREAM pStm, REFIID riid, void * pv,
									unsigned long dwDestContext, LPVOID pvDestContext,
									unsigned long mshlflags)
{
	HRESULT hr = S_OK;
	

	DebugTrace(TEXT("CNumberToTextHandler::MarshalInterface\r\n "));
	if(!m_pPxyMarshal)
		return E_NOTIMPL;
	hr = m_pPxyMarshal->MarshalInterface(pStm, riid, pv, dwDestContext,pvDestContext,mshlflags);
	
	if(IsEqualIID(riid, IID_INumberToText))
	{
		ULONG cbWritten;
		ULONG data = m_cbBstrText;
		hr = pStm->Write((void const*)&data,sizeof(data),&cbWritten);
	}
	return hr;
}

/**************************************************************************

CNumberToTextHandler::UnmarshalInterface(LPSTREAM pStm, REFIID riid, void * * ppvObj)
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::UnmarshalInterface(LPSTREAM pStm, REFIID riid, 
											   void * * ppvObj)
{
	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToTextHandler::UnmarshalInterface\r\n "));
	if(!m_pPxyMarshal)
		return E_NOTIMPL;
	hr = m_pPxyMarshal->UnmarshalInterface(pStm,riid,ppvObj); 
	if(IsEqualIID(riid, IID_INumberToText))
	{
		ULONG cbRead;
		ULONG ulData = 0;
		
		hr = pStm->Read((void *)&ulData,sizeof(ulData),&cbRead);
		EnterCriticalSection(&m_csGlobalVar);
		if(ulData > 0)
		{
			m_cbBstrText = ulData;
			if(m_bstrText != NULL)
			{	
				for(ULONG i = 0; i< m_cbBstrText;i++)
				{
					SysFreeString(m_bstrText[i]);
				}	
				delete [] m_bstrText;
			}
			m_bstrText = new BSTR[m_cbBstrText];
			for(ULONG i = 0; i< m_cbBstrText;i++)
			{
				m_bstrText[i]=NULL;
			}
		}
		LeaveCriticalSection(&m_csGlobalVar);
	}
	return hr;

}

/**************************************************************************

CNumberToTextHandler::ReleaseMarshalData(LPSTREAM pStm)
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::ReleaseMarshalData(LPSTREAM pStm)
{
	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToTextHandler::ReleaseMarshalData\r\n "));
	if(!m_pPxyMarshal)
		return E_NOTIMPL;

	hr = m_pPxyMarshal->ReleaseMarshalData(pStm);
	return hr;
}

/**************************************************************************

CNumberToTextHandler::DisconnectObject(unsigned long dwReserved)
**************************************************************************/
STDMETHODIMP CNumberToTextHandler::DisconnectObject(unsigned long dwReserved)
{
	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToTextHandler::DisconnectObject\r\n "));
	DebugTrace(TEXT("The above function should not be called\r\n "));
	if(!m_pPxyMarshal)
		return E_NOTIMPL;
	hr = m_pPxyMarshal->DisconnectObject(dwReserved);
	return hr;
}




///////////////////////////////////////////////////////////////////////////
//
// CInnerUnknown member function
//

/**************************************************************************

   CInnerUnknown::CInnerUnknown()

**************************************************************************/

CInnerUnknown::CInnerUnknown(LPUNKNOWN pOuterUnk)
{
	InterlockedIncrement(&g_ObjectCount);
	DebugTrace(TEXT("CInnerUnknown::CInnerUnknown.\r\n"));
	if(pOuterUnk==NULL)
		pOuterUnk = this;
	m_cRefCount = 0;
	m_pNumToTextHandler = new CNumberToTextHandler(pOuterUnk);
}

/**************************************************************************

   CInnerUnknown::~CInnerUnknown()

**************************************************************************/

CInnerUnknown::~CInnerUnknown()
{
	DebugTrace(TEXT("CInnerUnknown::~CInnerUnknown.\r\n"));

   //	if the reference is not zero, then the object is being delete too early.
	if(m_cRefCount != 0)
	{
		DebugTrace(TEXT("Object deleted too early.\r\n"));
	}
	delete m_pNumToTextHandler;
	InterlockedDecrement(&g_ObjectCount);
}

/**************************************************************************

   CNumberToTextHandler::QueryInterface

**************************************************************************/

STDMETHODIMP CInnerUnknown::QueryInterface(REFIID iid,void ** ppvObject)
{
   DebugTrace(TEXT("CInnerUnknown::QueryInterface.\r\n"));
   *ppvObject = NULL;

   // check if the interfaces requested is IUnknown or IID_INumberToText
   // since these are the only interface supported by our object
   if(IsEqualIID(iid, IID_IUnknown))
		*ppvObject = (IUnknown *)this;	   

   if(IsEqualIID(iid, IID_INumberToText))
		*ppvObject = (INumberToText *)m_pNumToTextHandler;
   
	if(IsEqualIID(iid, IID_IMarshal))
		*ppvObject = (IMarshal *)m_pNumToTextHandler;


	if(*ppvObject!=NULL)
	{
		((LPUNKNOWN)*ppvObject)->AddRef();
		return NOERROR;
	}

   	// return E_NOINTERFACE if you don't support the requested interface
	return E_NOINTERFACE;
}                                             

/**************************************************************************

   CInnerUnknown::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CInnerUnknown::AddRef()
{
   DebugTrace(TEXT("CInnerUnknown::AddRef.\r\n"));
   return InterlockedIncrement(&m_cRefCount);
}


/**************************************************************************

   CInnerUnknown::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CInnerUnknown::Release()
{
	ULONG tempCount;
	DebugTrace(TEXT("CInnerUnknown::Release.\r\n"));

	if((tempCount = InterlockedDecrement(&m_cRefCount))==0)
	{
		delete this;
	}
   // return the current reference count of the object
	return tempCount;
}
