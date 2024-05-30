/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/
#ifndef CLASSFACT_H
#define CLASSFACT_H

#include <windows.h>
#include <ole2.h>


HRESULT RegisterCF(LPSTR lpCmdLine);
HRESULT UnregisterCF();


// dll Main
class CMyClassFactory: public IClassFactory
{
	private:
//		to keep internal count of the object
		ULONG m_cRefCount;
	public:
//		Class Constructor for initialization.
		CMyClassFactory();

//		Class destructor for cleanup.
		virtual ~CMyClassFactory();

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

//		Methods of IClassFactory Interface

//		Creates an uninitialized object. 
		STDMETHOD(CreateInstance)(IUnknown * pUnkOuter, REFIID riid, void ** ppvObject);

//		Called by the client of a class object to keep an open object application in
//		memory, allowing instances to be created more quickly.
		STDMETHOD(LockServer)(BOOL fLock);
};


#endif
