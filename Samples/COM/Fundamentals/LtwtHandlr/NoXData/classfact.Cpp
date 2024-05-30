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

#include "ClassFact.h"
#include "..\common\debug.h"
#include "numToText.h"
#include "..\common\guid.h"

void ApplicationShutDown();

int g_cLockCount = 0;



// Class Factory for the creating the Shell Extension object. 
CMyClassFactory::CMyClassFactory()
{
	DebugTrace(TEXT("CMyClassFactory::CMyClassFactory.\r\n"));
//	initialize the reference count to zero
	m_cRefCount = 0;	
}

CMyClassFactory::~CMyClassFactory()
{
	DebugTrace(TEXT("CMyClassFactory::~CMyClassFactory.\r\n"));
//	if the reference is not zero, then the object is being delete too early.
	if(m_cRefCount != 0)
	{
		DebugTrace(TEXT("Object deleted too early.\r\n"));
	}
	ApplicationShutDown();
}

STDMETHODIMP CMyClassFactory::QueryInterface(REFIID iid,void ** ppvObject)
{
	*ppvObject = NULL;
	DebugTrace(TEXT("CMyClassFactory::QueryInterface.\r\n"));
   
   // check if the interfaces requested is IUnknown or IClassFactory, since these are the only 
	// interface supported by our object
	if(IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IClassFactory))
		*ppvObject = (LPVOID)this;

	// return E_NOINTERFACE if you don't support the requested interface
	if(*ppvObject==NULL)
		return E_NOINTERFACE;

	((LPUNKNOWN)*ppvObject)->AddRef();
	return NOERROR;
}

STDMETHODIMP_(ULONG) CMyClassFactory::AddRef()
{
	DebugTrace(TEXT("CMyClassFactory::AddRef.\r\n"));
	m_cRefCount++;
	return m_cRefCount;
}

STDMETHODIMP_(ULONG) CMyClassFactory::Release()
{
	ULONG tempCount;
	DebugTrace(TEXT("CMyClassFactory::Release.\r\n"));
	
	m_cRefCount--;
	tempCount = m_cRefCount;
	// if the reference count of the object is down to zero delete the object
	if(tempCount == 0)
		delete this;
	// return the current reference count of the object
	return tempCount;
}

STDMETHODIMP CMyClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppvObject)
{

   CNumberToText *pNumberToText = NULL;
   HRESULT hr;

   DebugTrace(TEXT("CMyClassFactory::CreateInstance.\r\n"));

   *ppvObject = NULL;
    
   // In our object, we do not support aggregation.
   if(pUnkOuter)
      return CLASS_E_NOAGGREGATION;

   // create a new object of CNumberToText
   pNumberToText = new  CNumberToText;

   // cannot create the object return error.
   if(pNumberToText==NULL)
     return E_OUTOFMEMORY;
   pNumberToText->AddRef();
   // Ask the object for the interface requested.
   hr= pNumberToText->QueryInterface(riid, ppvObject);
   
   pNumberToText->Release();
   return hr;
}

STDMETHODIMP CMyClassFactory::LockServer(BOOL fLock)
{
   DebugTrace(TEXT("CMyClassFactory::LockServer.\r\n"));

   if(fLock)
      g_cLockCount++;
   else
      g_cLockCount--;
   
   return NOERROR;
}


static DWORD g_dwCFMergPS = 0;

HRESULT RegisterCF(LPSTR lpCmdLine)
{
   HRESULT hr = S_OK;
   if (0 == lstrcmpi(lpCmdLine, "-Embedding") || 0 == lstrcmpi(lpCmdLine, "/Embedding"))
   {
	CMyClassFactory *myCF;
	myCF = new CMyClassFactory;
	if(myCF==NULL)
		return E_OUTOFMEMORY;
	hr = CoRegisterClassObject(CLSID_NumToTextNoXData,myCF,CLSCTX_LOCAL_SERVER,REGCLS_MULTIPLEUSE,&g_dwCFMergPS);
   }
	return hr;
}

HRESULT UnregisterCF()
{
	HRESULT hr = S_OK;
	if (0 != g_dwCFMergPS)
	{
		hr = CoRevokeClassObject(g_dwCFMergPS);
	}
	return hr;
}

