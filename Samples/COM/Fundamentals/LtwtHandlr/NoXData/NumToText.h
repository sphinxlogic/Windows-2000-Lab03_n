/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/
#ifndef _CNUMBER_TO_TEXT_H
#define _CNUMBER_TO_TEXT_H

#include <windows.h>
#include "..\NumTxtPS\server.h"


// For more info, on INumberToText, look at server.h or server.idl
// 
class CNumberToText : public INumberToText, public IStdMarshalInfo
{
	protected:
//		to keep internal count of the object
		DWORD m_cRefCount;
		int m_int;
		BSTR m_bstrText[MAX_NUM_SIZE];
	public:
//		Class Constructor for initialization.
		CNumberToText();

//		Class destructor for cleanup.
		~CNumberToText();
   
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

//		Method for IStdMarshalInfo Interface
		STDMETHOD(GetClassForHandler)(DWORD dwDestContext, void * pvDestContext, CLSID * pClsid);
};

#endif

