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
#ifndef _CNUMBER_TO_TEXT_HANDLER_H
#define _CNUMBER_TO_TEXT_HANDLER_H

#include <windows.h>
#include "..\..\NumTxtPS\server.h"


// For more info, on INumberToTextHandler, look at server.h or server.idl
// 
class CNumberToTextHandler : public INumberToText
{
	protected:
		int m_int;
		BSTR m_bstrText[MAX_NUM_SIZE];
		LPUNKNOWN m_pPxyUnk;
		LPUNKNOWN m_pOuterpUnk;
		CRITICAL_SECTION m_csGlobalVar; 
	public:
//		Class Constructor for initialization.
		CNumberToTextHandler(LPUNKNOWN pOuterpUnk);

//		Class destructor for cleanup.
		~CNumberToTextHandler();
   
//		Methods of IUnknown Interface

//		Returns a pointer to a specified interface on a component to which a client
//		currently holds an interface pointer. This function must call IUnknown::AddRef
//		on the pointer it returns. 
		STDMETHOD(QueryInterface)(REFIID iid,void ** ppvObject);

//		The IUnknown::AddRef method increments the reference count for a the calling 
//		interface on an object. It should be called for every new copy of a pointer 
//		to an interface on a given object. 
   		STDMETHOD_(ULONG, AddRef)(void);

//		Decrements the reference count for the calling interface on a object. If the 
//		reference count on the object falls to 0, the object is freed from memory.
		STDMETHOD_(ULONG, Release)(void);

//		Methods of INumberToText Interface
		STDMETHOD(GetText)(int iVal, BSTR *pszString);

};


class CInnerUnknown : public IUnknown
{
	protected:
		long m_cRefCount;
		CNumberToTextHandler *m_pNumToTextHandler;
	public:
//		Class Constructor for initialization.
		CInnerUnknown(LPUNKNOWN pOuterUnk);

//		Class destructor for cleanup.
		~CInnerUnknown();
   
//		Methods of IUnknown Interface

//		Returns a pointer to a specified interface on a component to which a client
//		currently holds an interface pointer. This function must call IUnknown::AddRef
//		on the pointer it returns. 
		STDMETHOD(QueryInterface)(REFIID iid,void ** ppvObject);

//		The IUnknown::AddRef method increments the reference count for a the calling 
//		interface on an object. It should be called for every new copy of a pointer 
//		to an interface on a given object. 
   		STDMETHOD_(ULONG, AddRef)(void);

//		Decrements the reference count for the calling interface on a object. If the 
//		reference count on the object falls to 0, the object is freed from memory.
		STDMETHOD_(ULONG, Release)(void);
};
#endif

