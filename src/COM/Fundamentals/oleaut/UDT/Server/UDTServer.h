/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */

#if !defined(__CSERVER__)
#define __CSERVER__

#include <windows.h>
#include "CUnknown.h"
#include "Debug.h"
#include "Student.h"

extern "C" const CLSID CLSID_UDT;
extern HMODULE g_hModule;
extern CLSID g_clsid;
extern LPOLESTR g_progID;

class CServer	 : public CUnknown,
		           public ISupportErrorInfo,
//				   public CProvideClassInfo<CMyControl>,
				   public IStudent
{
public:	
	// Creation
	static HRESULT _stdcall CreateInstance(IUnknown* pUnknownOuter,
	                              CUnknown** ppNewComponent) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface(const IID& iid, void** ppv);
	
	// Initialization
 	virtual HRESULT __stdcall Init(const CFactoryData *pData);


	// Notify derived classes that we are releasing.
	virtual void __stdcall FinalRelease();

	// Constructor
	CServer(IUnknown* pUnknownOuter);

	// Destructor
	~CServer();

private:
	// state variables

/*
 *  ITypeInfo, ExceptInfo.......
 * 
 */ 
	LPTYPEINFO m_pTypeInfo;
	EXCEPINFO m_ExcepInfo;

/*
 * IDispatch
 *
 */
	HRESULT __stdcall GetTypeInfoCount(UINT *pctinfo);
	HRESULT __stdcall GetTypeInfo(UINT itinfo, LCID lcid, LPTYPEINFO *pptinfo);
	HRESULT __stdcall GetIDsOfNames(REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgdispID);
	HRESULT __stdcall Invoke(DISPID dispID, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pexcepInfo, UINT *pArgError);

/*
 *
 * Rich Error handling functions
 *
 */
//ISupportErrorInfo interface
	HRESULT __stdcall InterfaceSupportsErrorInfo(REFIID  riid);

/*
 * IServer
 *
 */

	HRESULT __stdcall Test1(LPSTUDENTSTRUCT lpStudent);
	HRESULT __stdcall Test2(LPSAFEARRAY saStudent);


/* 
 * class member functions
 * 
 */
	const LPTYPEINFO GetDefTypeInfo() const {return m_pTypeInfo;}

public:
// accessor functions
	static LPOLESTR GetProgID() {return g_progID;}
	static CLSID GetCLSID() {return g_clsid;}
	static HMODULE GetHInstance() {return g_hModule;}
};

/*
 *
 * Rich Error handling functions
 *
 */
bool __stdcall RaiseException(WORD wException, REFIID guid, LPOLESTR szError, LPOLESTR helpFile, DWORD helpCtx);

#endif // __CSERVER__