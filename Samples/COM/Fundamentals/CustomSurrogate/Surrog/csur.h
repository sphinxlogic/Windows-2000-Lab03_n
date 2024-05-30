// Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.
//
//    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//    PARTICULAR PURPOSE.

#include <stack>
#include "cfwrap.h"

class CSurrogate : public ISurrogate
{
	// data structure to store all the class factory wrappers and revoke them
	// when FreeSurrogate() is called.  
	std::stack<CClassFactoryWrapper*> m_stkClassFactories;

public:
	CSurrogate () {};
	virtual ~CSurrogate() {};

	// IUnknown
    STDMETHOD (QueryInterface)(REFIID iid, LPVOID* ppv);
    STDMETHOD_(ULONG,AddRef)();
    STDMETHOD_(ULONG,Release)();

	// ISurrogate
	STDMETHOD(LoadDllServer)(REFCLSID rclsid);
	STDMETHOD(FreeSurrogate)();
};





