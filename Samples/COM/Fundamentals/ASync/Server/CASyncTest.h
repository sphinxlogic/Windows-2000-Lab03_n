/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */


#if !defined(__CAsyncTest__)
#define __CAsyncTest__

#include <objidl.h>
#include "..\proxy\AsyncTest1.h"

class  CServer;
struct ITest;

template<class T, class ISyncFace, class IAsyncFace> class  CAsyncXXX;

class CAsyncTest : public AsyncITest
{
protected:
	CAsyncXXX<CServer, ITest, CAsyncTest>	*m_lpAsyncXXX;		// Back pointer 
	CAsyncTest() {};
	enum  {CallNone, CallDone, CallPending};					// Flags used track call progress
	enum  {Test1, Test2};										// Used by either TimerProc or ThreadProc to designate which 
																// asynchronous method to call
	DWORD m_state;												// State variable that can be set to CallNone/Done/Pending
	HRESULT m_hResult;											// State variable used to hold hresult returned by Begin_XXX
public:
	struct threadParam
	{
		threadParam(DWORD w, CAsyncTest* p, DWORD method, BSTR s) : wait(w), id(0), pA(p), func(method), data(s){}

		DWORD wait; 
		UINT id;
		CAsyncTest* pA; 
		DWORD func;
		BSTR data;
	};
protected:
	CAsyncTest(CAsyncXXX<CServer, ITest, CAsyncTest> *pA);
	virtual ~CAsyncTest();

#if defined(_APARTMENT_)
	static void __stdcall TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
#else
	static void __cdecl ThreadProc(threadParam *pthdParam);
#endif

public:
	bool __stdcall Init();
private:
	// AsyncTest
	virtual HRESULT __stdcall Begin_Test1(BSTR bstr);
	virtual HRESULT __stdcall Finish_Test1(BSTR bstr);
	virtual HRESULT __stdcall Begin_Test2(BSTR bstrIn);
	virtual HRESULT __stdcall Finish_Test2(BSTR *lpbstrOut);
};
#endif // __CAsyncTest__