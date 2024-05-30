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
#include "..\common\debug.h"
#include "..\common\guid.h"

LPTSTR GetNameFromIID (REFIID iid, LPTSTR szInterfaceName)
{
	HKEY hKeyIID;
	TCHAR szKeyIID [255];
	DWORD dwType;
	DWORD dwSize = 255;
	
	OLECHAR szIIDW [255];
	TCHAR szIID[255];
	StringFromGUID2(iid,szIIDW,255);
	
	WideCharToMultiByte(CP_ACP, 0, szIIDW, -1, szIID, 255, NULL, NULL);  

	wsprintf (szKeyIID, TEXT ("Interface\\%s"), szIID);

	RegOpenKeyEx (HKEY_CLASSES_ROOT, 
				  szKeyIID,
				  0, 
				  KEY_ALL_ACCESS, 
				  &hKeyIID);

	RegQueryValueEx (hKeyIID,
				     TEXT (""),
					 NULL,
				     &dwType,
				     (unsigned char *) szInterfaceName,
					 &dwSize);
	RegCloseKey(hKeyIID);

	return szInterfaceName;
}


extern int g_ObjectCount; // Current Object count, so if the count goes to zero, we can shutdown

/****************************************************************************

        FUNCTION: void ApplicationShutDown()

        PURPOSE: to shutdown server when the server has no Objects to service

        COMMENTS:

****************************************************************************/

void ApplicationShutDown()
{
	DebugTrace(TEXT("ApplicationShutDown\r\n"));
	// If we don't have any object to service then let close the server down.
	if(g_ObjectCount ==0)
	{
		// post a WM close method to the main window, to close the application
		PostQuitMessage(0);
	}
}



///////////////////////////////////////////////////////////////////////////
//
// CNumberToText member function
//

/**************************************************************************

   CNumberToText::CNumberToText()

**************************************************************************/

CNumberToText::CNumberToText()
{
	DebugTrace(TEXT("CNumberToText::CNumberToText.\r\n"));
	g_ObjectCount++;
	m_cRefCount = 0;
	m_bstrText[0] = SysAllocString(OLESTR("ZERO"));
	m_bstrText[1] = SysAllocString(OLESTR("ONE"));
	m_bstrText[2] = SysAllocString(OLESTR("TWO"));
	m_bstrText[3] = SysAllocString(OLESTR("THREE"));
	m_bstrText[4] = SysAllocString(OLESTR("FOUR"));
	m_bstrText[5] = SysAllocString(OLESTR("FIVE"));
	m_bstrText[6] = SysAllocString(OLESTR("SIX"));
	m_bstrText[7] = SysAllocString(OLESTR("SEVEN"));
	m_bstrText[8] = SysAllocString(OLESTR("EIGHT"));
	m_bstrText[9] = SysAllocString(OLESTR("NINE"));
	HRESULT hr = E_FAIL;


// There is a chance, that the AddRef/Release getting called during CoGetStdMarshalEx() dance
// To protect from getting deleted during the constructor, We will artificially increment the RefCount.
	m_cRefCount++;

	DebugTrace(TEXT("Before CoGetStdMarshalEx.\r\n"));

	hr = CoGetStdMarshalEx((LPUNKNOWN)(INumberToText *)this, SMEXF_SERVER, (LPUNKNOWN *)&m_pStubUnk);
	DebugTrace(TEXT("After CoGetStdMarshalEx.\r\n"));
	if(FAILED(hr))
	{
		DebugTrace(TEXT("FAILED  CoGetStdMarshalEx %x.\r\n"), hr);
		m_pStubUnk=NULL;
	}
	else
	{
		DebugTrace(TEXT("Before m_pStubUnk->QueryInterface.\r\n"));
		hr = m_pStubUnk->QueryInterface(IID_IMarshal, (LPVOID *)&m_pStubMarshal);
		DebugTrace(TEXT("After m_pStubUnk->QueryInterface.\r\n"));
		if(FAILED(hr))
			m_pStubMarshal=NULL;
		else
		// since we are keeping an interface from Inner object, 
		// we should Call Release on ourself following the rules of Aggregation. 
		// If we don't follow this rule, then Object will have errorneous RefCount, 
			Release();
	}
// Since we had artificially incremented the RefCount, to protect from getting deleted during 
// the constructor. Lets offset that by decrementing the RefCount.
	m_cRefCount--;
}

/**************************************************************************

   CNumberToText::~CNumberToText()

**************************************************************************/

CNumberToText::~CNumberToText()
{
	DebugTrace(TEXT("CNumberToText::~CNumberToText.\r\n"));
	if(m_cRefCount != 0)
	{
		DebugTrace(TEXT("Object deleted too early.\r\n"));
	}
	
// As we are destructing, and releasing internal objects, we may be getting reentrant in to the Release 
//	and thus Destructor, to avoid that we protect the Destructor with an artifical increment of RefCount;
	m_cRefCount++;

	if(m_pStubMarshal)
	{
		// Following the rules of Aggregation, since we had kept an interface from Inner object, We Should AddRef() ourselves, 
		// and then call release on interface, otherwise, we will cause errorneous RefCount 
		AddRef();
		m_pStubMarshal->Release();
	}

	if(m_pStubUnk)
	{
		// Following the rules of Aggregation, since we had kept an interface from Inner object, We Should AddRef() ourselves, 
		// and then call release on interface, otherwise, we will cause errorneous RefCount 
		AddRef();
		m_pStubUnk->Release();
	}
   //	if the reference is not zero, then the object is being delete too early.
	g_ObjectCount--;
	for(int i = 0; i < MAX_NUM_SIZE; i++)
		SysFreeString(m_bstrText[i]);
// Since we had artificially incremented the RefCount, to protect from getting reentrant during 
// the destructor. Lets offset that by decrementing the RefCount.
	m_cRefCount--;
	ApplicationShutDown();
}

/**************************************************************************

   CNumberToText::QueryInterface

**************************************************************************/

STDMETHODIMP CNumberToText::QueryInterface(REFIID iid,void ** ppvObject)
{
   *ppvObject = NULL;

	TCHAR szInterfaceName[255];
	DebugTrace(TEXT("CNumberToText::QueryInterface %s \r\n"),
							GetNameFromIID(iid,szInterfaceName));
   // check if the interfaces requested is IUnknown or IID_IMergedPS
   // since these are the only interface supported by our object
   if(IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_INumberToText))
		*ppvObject = (INumberToText *)this;

   if(IsEqualIID(iid, IID_IStdMarshalInfo))
	   *ppvObject = (IStdMarshalInfo *)this;

	if(IsEqualIID(iid, IID_IMarshal))
	{
	   *ppvObject = (IMarshal *)this;
	   DebugTrace(TEXT("IID_IMarshal\r\n"));
	}

	if(*ppvObject!=NULL)
	{
		((LPUNKNOWN)*ppvObject)->AddRef();
		return NOERROR;
	}
	// Note: we do not pass any 
	// return E_NOINTERFACE if you don't support the requested interface
	return E_NOINTERFACE;
}                                             

/**************************************************************************

   CNumberToText::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CNumberToText::AddRef()
{
   DebugTrace(TEXT("CNumberToText::AddRef.\r\n"));
   return ++m_cRefCount;
}


/**************************************************************************

   CNumberToText::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CNumberToText::Release()
{
	ULONG tempCount;
	m_cRefCount--;
	DebugTrace(TEXT("CNumberToText::Release. %d\r\n"),m_cRefCount);

	tempCount = m_cRefCount;
   // if the reference count of the object is down to zero delete the object
	if(tempCount == 0)
	{
		delete this;
	}
   // return the current reference count of the object
	return tempCount;
}


/**************************************************************************

   CNumberToText::GetText(int iVal,BSTR *pszString);
**************************************************************************/
STDMETHODIMP CNumberToText::GetText(int iVal,BSTR *pszString)
{
	DebugTrace(TEXT("CNumberToText::GetText "));
	DebugTrace(TEXT(" \r\n"));
	if(iVal >= MAX_NUM_SIZE)
		return E_INVALIDARG;
	*pszString = SysAllocString(m_bstrText[iVal]);
	return S_OK;
}


/**************************************************************************

   CNumberToText::GetClassForHandler(DWORD dwDestContext, void * pvDestContext, CLSID * pClsid);
**************************************************************************/
STDMETHODIMP CNumberToText::GetClassForHandler(DWORD dwDestContext, void * pvDestContext, CLSID * pClsid)
{	
	DebugTrace(TEXT("CNumberToText::GetClassForHandler \r\n "));
	*pClsid= CLSID_INumberToTextHandlerWithXData;
	return S_OK;
}

/**************************************************************************

CNumberToText::GetUnmarshalClass(REFIID riid, void * pv, 
								unsigned long dwDestContext,
								void * pvDestContext, 
								unsigned long mshlflags, 
								LPCLSID pclsid) ;
**************************************************************************/
STDMETHODIMP CNumberToText::GetUnmarshalClass(REFIID riid, void * pv, unsigned long dwDestContext,
									void * pvDestContext, unsigned long mshlflags, 
									LPCLSID pclsid)
{
	
	HRESULT hr = S_OK;
	TCHAR szInterfaceName[255];
	DebugTrace(TEXT("CNumberToText::GetUnmarshalClass %s\r\n"),GetNameFromIID(riid,szInterfaceName));
	if(!m_pStubMarshal)
		return E_NOTIMPL;

	hr = m_pStubMarshal->GetUnmarshalClass(riid, pv, dwDestContext,pvDestContext,
											mshlflags,pclsid);
	DebugTrace(TEXT("GetUnmarshalClass for Stub IMarshal %x\r\n"), hr);
	return hr;
}

/**************************************************************************

CNumberToText::GetMarshalSizeMax(REFIID riid, void * pv, 
								unsigned long dwDestContext, 
								void * pvDestContext, 
								unsigned long mshlflags, 
								unsigned long * pSize)
**************************************************************************/
STDMETHODIMP CNumberToText::GetMarshalSizeMax(REFIID riid, void * pv, unsigned long dwDestContext, 
									void * pvDestContext, unsigned long mshlflags, 
									unsigned long * pSize)
{
	HRESULT hr = S_OK;
	TCHAR szInterfaceName[255];
	DebugTrace(TEXT("CNumberToText::GetMarshalSizeMax %s\r\n"),GetNameFromIID(riid,szInterfaceName));
	if(!m_pStubMarshal)
		return E_NOTIMPL;
	hr = m_pStubMarshal->GetMarshalSizeMax(riid, pv, dwDestContext,pvDestContext,mshlflags,
												pSize);
	if(IsEqualIID(riid, IID_INumberToText))
	{
		DebugTrace(TEXT("Before GetMarshalSizeMax Stub IMarshal %d %x\r\n"), *pSize, hr);
		*pSize+=sizeof(ULONG);
		DebugTrace(TEXT("GetMarshalSizeMax Stub IMarshal %d\r\n"), *pSize);
	}
	return hr;
}

/**************************************************************************

CNumberToText::MarshalInterface(LPSTREAM pStm, REFIID riid, 
								void * pv,
								unsigned long dwDestContext, 
								LPVOID pvDestContext,
								unsigned long mshlflags)
**************************************************************************/
STDMETHODIMP CNumberToText::MarshalInterface(LPSTREAM pStm, REFIID riid, void * pv,
									unsigned long dwDestContext, LPVOID pvDestContext,
									unsigned long mshlflags)
{
	HRESULT hr = S_OK;
	

	TCHAR szInterfaceName[255];
	DebugTrace(TEXT("CNumberToText::MarshalInterface %s\r\n"),GetNameFromIID(riid,szInterfaceName));
	if(!m_pStubMarshal)
		return E_NOTIMPL;
	hr = m_pStubMarshal->MarshalInterface(pStm, riid, pv, dwDestContext,pvDestContext,mshlflags);

	DebugTrace(TEXT("MarshalInterface Stub IMarshal %x\r\n"), hr);
	if(IsEqualIID(riid, IID_INumberToText))
	{
		DebugTrace(TEXT(" %s MarshalInterface Stub IMarshal %x\r\n"),szInterfaceName, hr);
		ULONG cbWritten;
		ULONG data = MAX_NUM_SIZE;
		hr = pStm->Write((void const*)&data,sizeof(data),&cbWritten);
		DebugTrace(TEXT("MarshalInterface Stub IMarshal %d %d %x\r\n"),
					data,cbWritten, hr);
	}

	return hr;
}

/**************************************************************************

CNumberToText::UnmarshalInterface(LPSTREAM pStm, REFIID riid, void * * ppvObj)
**************************************************************************/
STDMETHODIMP CNumberToText::UnmarshalInterface(LPSTREAM pStm, REFIID riid, 
											   void * * ppvObj)
{
	HRESULT hr = S_OK;
	TCHAR szInterfaceName[255];
	DebugTrace(TEXT("CNumberToText::UnmarshalInterface %s\r\n"),GetNameFromIID(riid,szInterfaceName));
	if(!m_pStubMarshal)
		return E_NOTIMPL;
	hr = m_pStubMarshal->UnmarshalInterface(pStm,riid,ppvObj); 

	if(IsEqualIID(riid, IID_INumberToText))
	{
		ULONG cbRead;
		ULONG data = 0;
		hr = pStm->Read((void *)&data,sizeof(data),&cbRead);
	}
	return hr;
}

/**************************************************************************

CNumberToText::ReleaseMarshalData(LPSTREAM pStm)
**************************************************************************/
STDMETHODIMP CNumberToText::ReleaseMarshalData(LPSTREAM pStm)
{
	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToText::ReleaseMarshalData\r\n"));
	if(!m_pStubMarshal)
		return E_NOTIMPL;
	hr = m_pStubMarshal->ReleaseMarshalData(pStm);

	return hr;
}

/**************************************************************************

CNumberToText::DisconnectObject(unsigned long dwReserved)
**************************************************************************/
STDMETHODIMP CNumberToText::DisconnectObject(unsigned long dwReserved)
{
	HRESULT hr = S_OK;
	DebugTrace(TEXT("CNumberToText::DisconnectObject\r\n"));
	if(!m_pStubMarshal)
		return E_NOTIMPL;
	hr = m_pStubMarshal->DisconnectObject(dwReserved);
	return hr;
}

