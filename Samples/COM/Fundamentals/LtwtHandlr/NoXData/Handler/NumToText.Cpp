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
	for(int i=0; i< MAX_NUM_SIZE; i++)
	{
		m_bstrText[i] = NULL;
	}
	m_pPxyUnk = NULL;
	m_pOuterpUnk = pOuterpUnk;
	if(FAILED(CoGetStdMarshalEx(m_pOuterpUnk,SMEXF_HANDLER,&m_pPxyUnk)))
		m_pPxyUnk = NULL;

}

/**************************************************************************

   CNumberToTextHandler::~CNumberToTextHandler()

**************************************************************************/

CNumberToTextHandler::~CNumberToTextHandler()
{
	DebugTrace(TEXT("CNumberToTextHandler::~CNumberToTextHandler.\r\n"));

	for(int i=0; i< MAX_NUM_SIZE; i++)
	{
		if(m_bstrText[i] != NULL)
			SysFreeString(m_bstrText[i]);
	}
	if(m_pPxyUnk)
		m_pPxyUnk->Release();
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
	if(iVal >= MAX_NUM_SIZE)
		return E_INVALIDARG;

	EnterCriticalSection(&m_csGlobalVar);
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
	if(m_bstrText[iVal] == NULL)
		m_bstrText[iVal]= SysAllocString(*pszString);
	LeaveCriticalSection(&m_csGlobalVar);
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
	DebugTrace(TEXT("CInnerUnknown::CInnerUnknown.\r\n"));
	InterlockedIncrement(&g_ObjectCount);
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
   
   	// return E_NOINTERFACE if you don't support the requested interface
	if(*ppvObject==NULL)
		return E_NOINTERFACE;

	((LPUNKNOWN)*ppvObject)->AddRef();
	return NOERROR;
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
