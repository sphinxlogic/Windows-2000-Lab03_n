// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************

// CInvSink interface.
// *************************************************************


#define INVQUERY_OS 1
#define INVQUERY_CPU 2
#define INVQUERY_RAM 3

class CInvSink : public IWbemObjectSink
{
	LONG m_lRefCount;					// Reference count

	IWbemServices *m_pWbemServices;		// IWbemServices for this object to use.
	int m_iQuerymode;					// Query OS, CPU, or RAM?

	HANDLE m_hEvent;					// Event Handle
	CRITICAL_SECTION m_cs;				// Critical section

	// Critical Section methods
	void Lock() { EnterCriticalSection(&m_cs); }
	void Unlock() { LeaveCriticalSection(&m_cs); }

public:

	IWbemClassObject **m_aObjects;		// Object array
	long m_lObjCount;					// Object count

	// Constructor, Destructor
	CInvSink(IWbemServices *pIWbemServices, int Querymode);
	~CInvSink();

	// IUnknown
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	// IWbemObjectSink
	HRESULT __stdcall Indicate(LONG lObjectCount, IWbemClassObject **ppObjArray);
	HRESULT __stdcall SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject *pObjParam);

	// Wait method
	DWORD Wait() { return WaitForSingleObject(m_hEvent, INFINITE); }

};