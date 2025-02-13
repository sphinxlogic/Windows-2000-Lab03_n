// Copyright 1992 - 1998 Microsoft Corporation, All rights reserved.
//
//    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//    PARTICULAR PURPOSE.

class CClassFactoryWrapper : public IClassFactory, public IMarshal
{
	LONG m_cRef;
	CLSID m_clsid;
	DWORD m_dwReg;
public:
	CClassFactoryWrapper(REFCLSID rclsid);
	virtual ~CClassFactoryWrapper();
	
	// IUnknown
    STDMETHOD (QueryInterface)(REFIID iid, LPVOID* ppv);
    STDMETHOD_(ULONG,AddRef)();
    STDMETHOD_(ULONG,Release)();

    // IClassFactory
    STDMETHOD (CreateInstance)(IUnknown* pUnkOuter, REFIID iid, void** ppv);
    STDMETHOD (LockServer)(BOOL fLock);

    // IMarshal
    STDMETHOD (GetUnmarshalClass)(REFIID riid, void *pv, DWORD dwDestContext,
								void *pvDestContext, DWORD mshlflags, CLSID *pCid);
    STDMETHOD (GetMarshalSizeMax)(REFIID riid, void *pv, DWORD dwDestContext,
								void *pvDestContext, DWORD mshlflags, DWORD *pSize);
    STDMETHOD (MarshalInterface)(IStream *pStm, REFIID riid, void *pv,
								DWORD dwDestContext, void *pvDestContext, DWORD mshlflags);
    STDMETHOD (UnmarshalInterface)(IStream *pStm,REFIID riid,void **ppv);
    STDMETHOD (ReleaseMarshalData)(IStream *pStm);
    STDMETHOD (DisconnectObject)(DWORD dwReserved);

	friend class CSurrogate;
};







