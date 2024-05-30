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
#include "..\common\debug.h"
#include "..\common\guid.h"



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

}

/**************************************************************************

   CNumberToText::~CNumberToText()

**************************************************************************/

CNumberToText::~CNumberToText()
{
	DebugTrace(TEXT("CNumberToText::~CNumberToText.\r\n"));

   //	if the reference is not zero, then the object is being delete too early.
	if(m_cRefCount != 0)
	{
		DebugTrace(TEXT("Object deleted too early.\r\n"));
	}
	g_ObjectCount--;
	for(int i = 0; i < MAX_NUM_SIZE; i++)
		SysFreeString(m_bstrText[i]);
	ApplicationShutDown();
}

/**************************************************************************

   CNumberToText::QueryInterface

**************************************************************************/

STDMETHODIMP CNumberToText::QueryInterface(REFIID iid,void ** ppvObject)
{
   DebugTrace(TEXT("CNumberToText::QueryInterface.\r\n"));
   *ppvObject = NULL;

   // check if the interfaces requested is IUnknown or IID_IMergedPS
   // since these are the only interface supported by our object
   if(IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_INumberToText))
		*ppvObject = (INumberToText *)this;

   if(IsEqualIID(iid, IID_IStdMarshalInfo))
	   *ppvObject = (IStdMarshalInfo *)this;

   	// return E_NOINTERFACE if you don't support the requested interface
	if(*ppvObject==NULL)
		return E_NOINTERFACE;

	((LPUNKNOWN)*ppvObject)->AddRef();
	return NOERROR;
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
	DebugTrace(TEXT("CNumberToText::Release.\r\n"));
	
	m_cRefCount--;
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
	DebugTrace(TEXT("CNumberToText::GetClassForHandler\r\n "));
	*pClsid= CLSID_INumberToTextHandlerNoXData;
	return S_OK;
}

