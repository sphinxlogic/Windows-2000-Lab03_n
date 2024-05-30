/*
Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.
*/

#include <windows.h>
#include "natcom.h"
#include <iostream.h>
#include <olectl.h>
#include <stdio.h>

// globals

ULONG	g_cObject = 0 ;
HANDLE	g_hDllMain ;

////////////////////////////////////////////////////////////////////////////////
//
//	ObjectCreated()
//
//	increments ref count of objects which reference this .DLL
//
////
VOID ObjectCreated(VOID)
{
    InterlockedIncrement( (LONG*)&g_cObject ) ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	ObjectDestroyed()
//
//	decrements ref count of objects which reference this .dll
//
////
VOID ObjectDestroyed(VOID)
{
    InterlockedDecrement( (LONG*)&g_cObject ) ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	CNatCom
//
//	contains our COM object
//
////
class CNatCom : public IUnknown
{
	////////////////////////////////////////////////////////////////////////
	//
	//	CImpINatCom
	//
	//	implements the INatCom interface.  IUnknown delegates to
	//	controlling unknown (CNatCom if not aggregated).
	//
	////
	class CImpINatCom : public INatCom
	{
		friend class CNatCom ;

		// PUBLIC ------------------------------------------------------

		public :

		////////////////////////////////////////////////////////////////
		//
		//
		//	CImpINatCom()
		//
		//	constructor;  Initialize member variables.
		//
		////
		CImpINatCom()
		{
			m_cRef = 0 ;
			m_pNatCom = NULL ;
			m_punkCCW = NULL ;
		}

		////////////////////////////////////////////////////////////////
		//
		//	~CImpINatCom()
		//
		//	destructor; release CCW if we have one.
		//
		////
		~CImpINatCom()
		{
			if (m_punkCCW)
			{
				m_punkCCW->Release() ;
			}
		}

		////////////////////////////////////////////////////////////////
		//
		//	QueryInterface()
		//
		//	delegating QI.
		//
		////
		HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
		{
			return m_pUnkOuter->QueryInterface(riid,ppv) ;
		}

		////////////////////////////////////////////////////////////////
		//
		//	AddRef()
		//
		////
		ULONG __stdcall AddRef(void)
		{
			return m_pUnkOuter->AddRef() ;
		}

		////////////////////////////////////////////////////////////////
		//
		//	Release()
		//
		//	delegating Release
		//
		////
		ULONG __stdcall Release(void)
		{
			return m_pUnkOuter->Release() ;
		}

		////////////////////////////////////////////////////////////////
		//
		//	MultParam()
		//
		//	multiplies the two passed arguments and returns the
		//	value back in lVal.
		//
		//	parameters:
		//		lMult	multiplier
		//		lVal	returns value we are multiplied by
		//
		////
		HRESULT __stdcall MultParam(long lMult, long *lVal)
		{
			*lVal = *lVal * lMult ;

			return S_OK ;
		}

		////////////////////////////////////////////////////////////////
		//
		//	Square()
		//
		//	squares lVal, returning the result back in lResult.
		//
		//	parameters:
		//		lVal		value to be squared
		//		lResult 	return value = lVal squared
		//
		////
		HRESULT __stdcall Square(long lVal, long *lResult)
		{
			*lResult = lVal * lVal ;

			return S_OK ;
		}

		////////////////////////////////////////////////////////////////
		//
		//	GetClass()
		//
		//	CoCreates a java-implemented object (CCW); returns the
		//	pointer into the v-table to the callee; exercises one
		//	method in the ccw.
		//
		//	parameters:
		//		pjNatCom	pointer to our CCW.
		//
		////
		HRESULT __stdcall GetClass(jINatCom **pjNatCom)
		{
			HRESULT hr ;

			if (FAILED(hr = CoCreateInstance(CLSID_jCNatCom, NULL, CLSCTX_SERVER, IID_IUnknown, (void **)&m_punkCCW)))
			{
				return hr ;
			}

			if (FAILED(hr = m_punkCCW->QueryInterface(IID_jINatCom, (void **)&m_pNatCom)))
			{
				m_punkCCW->Release() ;		// IID_IUnknown
				m_punkCCW = NULL ;

				return hr ;
			}

			// per the rules of COM we leave the refcount at 2, since
			//  we're passing the pointer back to the caller.  Caller
			//  must Release() the object.

			// set member variable
			*pjNatCom = m_pNatCom ;

			// invoke java-implemented method
			m_pNatCom->ccwHelloWorld() ;

			return S_OK ;
		}

		////////////////////////////////////////////////////////////////

		private :

		ULONG		m_cRef ;		// ref count
		IUnknown	*m_pUnkOuter ;		// controlling unknown
		jINatCom	*m_pNatCom ;		// ccw interface pointer
		IUnknown	*m_punkCCW ;		// IUnknown of our CCW
	} ;

	CImpINatCom m_CImpINatCom ;

	// PUBLIC --------------------------------------------------------------

	public :

	////////////////////////////////////////////////////////////////////////
	//
	//	CNatCom()
	//
	//	constructor;  initializes variables, including those of
	//	CImpINatCom to point to controlling unknown.
	//
	////
	CNatCom(IUnknown *punkOuter)
	{
		ObjectCreated() ;

		m_cRef = 0 ;

		// if this is non-null, we're being aggregated
		if (punkOuter)
		{
			m_pUnkOuter = punkOuter ;
			m_CImpINatCom.m_pUnkOuter = punkOuter ;
		}
		else
		{
			m_pUnkOuter = this ;
			m_CImpINatCom.m_pUnkOuter = this ;
		}
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	~CNatCom()
	//
	//	destructor.
	//
	////
	~CNatCom()
	{
		ObjectDestroyed() ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	QueryInterface()
	//
	//	non-delegating QI
	//
	////
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		*ppv = NULL ;
        
		if (riid == IID_IUnknown)
		{
			*ppv = this ;
		}

		if (riid == IID_INatCom)
		{
			*ppv = &m_CImpINatCom ;
		}

		if (*ppv == NULL)
		{
			return E_NOINTERFACE ;
		}

		((IUnknown *) *ppv)->AddRef() ;
	        
		return NOERROR ;
	}
        
	////////////////////////////////////////////////////////////////////////
	//
	//	AddRef()
	//
	//	non-delegating AddRef()
	//
	////
	ULONG __stdcall AddRef(void)
	{
		InterlockedIncrement( (LONG*)&m_cRef ) ;

		return m_cRef ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	Release()
	//
	//	non-delegating Release
	//
	////
	ULONG __stdcall Release(void)
	{
		if (!InterlockedDecrement( (LONG*)&m_cRef ))
		{
			delete this ;
			return 0 ;
		}
	        
		return m_cRef ;
	}

	// PRIVATE -------------------------------------------------------------

	private :

	ULONG		m_cRef ;		// ref count
	IUnknown	*m_pUnkOuter ;		// controlling unknown
} ;

// CLASS FACTORY --------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//
//	CNatComCF
//
//	class factory for CNatCom
//
////
class CNatComCF : public IClassFactory
{
	public :

	////////////////////////////////////////////////////////////////////////
	//
	//	CNatComCF()
	//
	//	constructor
	//
	////
	CNatComCF()
	{
		m_cRef = 0 ;
	}

	///////////////////////////////////////////////////////////////////////
	//
	//	CreateInstance()
	//
	//	IClassFactory CreateInstance() method implementation
	//
	////
	HRESULT __stdcall CreateInstance(IUnknown *punkOuter, REFIID riid, void **ppv)
	{
		CNatCom *cmg ;
		HRESULT hr ;

		*ppv = NULL ;

		if ((punkOuter) && (riid != IID_IUnknown))
		{
			return CLASS_E_NOAGGREGATION ;
		}

		cmg = new CNatCom(punkOuter) ;

		hr = cmg->QueryInterface(riid, ppv) ;

		if (FAILED(hr))
		{
			delete cmg ;
			return hr ;
		}

		return S_OK ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	QueryInterface()
	//
	//	IUnknown QueryInterface() method implementation
	//
	////
	HRESULT __stdcall QueryInterface(REFIID iid, void **ppv)
	{
		*ppv = NULL ;

		if (iid == IID_IUnknown || iid == IID_IClassFactory)
			*ppv = this ;
		else
			return E_NOINTERFACE ;

		AddRef() ;

		return S_OK ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	AddRef()
	//
	//	IUnknown AddRef() method implementation
	//
	////
	ULONG __stdcall AddRef(void)
	{
		return ++m_cRef ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	Release()
	//
	//	IUnknown Release() method implementation
	//
	////
	ULONG __stdcall Release(void)
	{
		if (--m_cRef == 0)
		{
			delete this ;
			return 0 ;
		}
        
		return m_cRef ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	LockServer()
	//
	//	IClassFactory LockServer() method implementation
	//
	////
	HRESULT __stdcall LockServer(BOOL bLock)
	{
		bLock ? ObjectCreated() : ObjectDestroyed() ;

		return S_OK ;
	}


	// PRIVATE -------------------------------------------------------------

	private :

	ULONG	m_cRef ;		// refcount
} ;

////////////////////////////////////////////////////////////////////////////////
//
//	DllMain()
//
//	entry point
//
////
BOOL WINAPI DllMain(HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	  case DLL_PROCESS_ATTACH :
		g_hDllMain = hDLLInst ;
	}

	return TRUE ;
}

// -----------------------------------------------------------------------------

TCHAR achSampleDesc[]		= "CNatCom";
TCHAR achInprocServer32[]	= "InprocServer32";
TCHAR achSampleProgID[] 	= "CNatCom";
TCHAR achProgID[]		= "CNatCom";
TCHAR achThreadingModel[]	= "ThreadingModel";
TCHAR achFree[] 		= "Both";

#define GUIDSTR_MAX	(1+ 8 + 1 + 4 + 1 + 4 + 1 + 4 + 1 + 12 + 1 + 1)
static const CHAR szDigits[]	= "0123456789ABCDEF";
static const BYTE GuidMap[]	= { 3, 2, 1, 0, '-', 5, 4, '-', 7, 6, '-',
				    8, 9, '-', 10, 11, 12, 13, 14, 15 };

////////////////////////////////////////////////////////////////////////////////
//
//	GUID2StringA()
//
//	converts GUID to string form
//
////
VOID GUID2StringA(REFGUID rguid, LPSTR lpsz)
{
	int	i;
	LPSTR	p = lpsz;

	const BYTE * pBytes = (const BYTE *) &rguid;

	*p++ = '{';

	for (i = 0; i < sizeof(GuidMap); i++)
	{
		if (GuidMap[i] == '-')
		{
			*p++ = '-';
		}
		else
		{
			*p++ = szDigits[ (pBytes[GuidMap[i]] & 0xF0) >> 4 ];
			*p++ = szDigits[ (pBytes[GuidMap[i]] & 0x0F) ];
		}
	}

	*p++ = '}';
	*p   = '\0';
}

////////////////////////////////////////////////////////////////////////////////
//
//	NTCompatibleRegDeleteKey()
//
//	checks that registry key does not have any subkeys prior to deletion
//
////
LONG NTCompatibleRegDeleteKey(HKEY hKey, LPCTSTR szSubKey)
{
	TCHAR achName[MAX_PATH+1];
	HKEY  hSubkey;

	if (ERROR_SUCCESS != RegOpenKey(hKey, szSubKey, &hSubkey))
		return REGDB_E_INVALIDVALUE;

	if (ERROR_SUCCESS == RegEnumKey(hSubkey, 0, achName, sizeof(achName)/sizeof(TCHAR)))
	{
		RegCloseKey(hSubkey);
		// There's still one subkey: fail the call.
		return REGDB_E_INVALIDVALUE;
	}

	RegCloseKey(hSubkey);
	return RegDeleteKey(hKey, szSubKey);
}

////////////////////////////////////////////////////////////////////////////////
//
//	DllRegisterServer()
//
//	registers this COM server via the registry.
//
////
STDAPI DllRegisterServer(VOID)
{
	HKEY	hKey  = NULL;
	HKEY	hKey2  = NULL;
	HKEY	hKey3  = NULL;
	DWORD	result;
	HRESULT hr = SELFREG_E_CLASS;
	CHAR	achCLSID[GUIDSTR_MAX];
	CHAR	achLIBID[GUIDSTR_MAX] ;
	TCHAR	achModulePathName[MAX_PATH];
	TCHAR	achCurrentDirectory[MAX_PATH] ;

	// CLSID

	GUID2StringA(CLSID_CNatCom, achCLSID) ;

	// If we fail in the middle, the state of the registry entries
	// is indeterminate (as per Ole specs.)

	// Create HKEY_CLASSES_ROOT\progid\CLSID
	result = RegCreateKey(HKEY_CLASSES_ROOT, achSampleProgID, &hKey);
	if (result != ERROR_SUCCESS) goto lExit;

	result = RegSetValue(hKey, NULL, REG_SZ, achSampleDesc, lstrlen(achSampleDesc));
	if (result != ERROR_SUCCESS) goto lExit;

	result = RegCreateKey(hKey, TEXT("CLSID"), &hKey2);
	if (result != ERROR_SUCCESS) goto lExit;

	result = RegSetValue(hKey2, NULL, REG_SZ, achCLSID, GUIDSTR_MAX-1);
	if (result != ERROR_SUCCESS) goto lExit;

	RegCloseKey(hKey);
	RegCloseKey(hKey2);
	hKey = NULL;
	hKey2 = NULL;

	// Create HKEY_CLASSES_ROOT\CLSID\...

	// create CLSID key
	result = RegCreateKey(HKEY_CLASSES_ROOT, TEXT("CLSID"), &hKey);
	if (result != ERROR_SUCCESS) goto lExit ;

	// create CLSID/GUID key
	result = RegCreateKey(hKey, achCLSID, &hKey2);
	if (result != ERROR_SUCCESS) goto lExit ;

	// put in sample description value into CLSID\GUID key
	result = RegSetValue(hKey2, NULL, REG_SZ, achSampleDesc, lstrlen(achSampleDesc));
	if (result != ERROR_SUCCESS) goto lExit ;

	// get our path ..
	result = GetModuleFileName(g_hDllMain, achModulePathName, sizeof(achModulePathName)/sizeof(TCHAR));
	if (result == 0) goto lExit ;

	// create subkey under CLSID\GUID
	result = RegCreateKey(hKey2, achInprocServer32, &hKey3);
	if (result != ERROR_SUCCESS) goto lExit ;

	// set key value to the path obtained above
	result = RegSetValue(hKey3, NULL, REG_SZ, achModulePathName, lstrlen(achModulePathName));
	if (result != ERROR_SUCCESS) goto lExit ;

	// both
	result = RegSetValueEx(hKey3, achThreadingModel, 0, REG_SZ, (BYTE*)achFree, sizeof(achFree));
	if (result != ERROR_SUCCESS) goto lExit;

	RegCloseKey(hKey3);
	hKey3 = NULL;

	// PROGID

	result = RegCreateKey(hKey2, achProgID, &hKey3);
	if (result != ERROR_SUCCESS) goto lExit;

	result = RegSetValue(hKey3, NULL, REG_SZ, achSampleProgID, lstrlen(achSampleProgID));
	if (result != ERROR_SUCCESS) goto lExit;

	RegCloseKey(hKey3);
	hKey3 = NULL;


	hr = S_OK ;

 lExit :

	// close up
	if (hKey) RegCloseKey(hKey);
	if (hKey2) RegCloseKey(hKey2);
	if (hKey3) RegCloseKey(hKey3);

	return hr ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	DllUnregisterServer()
//
//	removes our registry entries (entered via DllRegisterServer())
//
////
STDAPI DllUnregisterServer(VOID)
{
	HKEY	hKey  = NULL;
	HKEY	hKey2 = NULL;
	DWORD	result;
	HRESULT hr = SELFREG_E_CLASS;
	CHAR	achCLSID[GUIDSTR_MAX];
	CHAR	achLIBID[GUIDSTR_MAX];

	// If we fail in the middle, the state of the registry entries
	// is indeterminate (as per Ole specs.)
	GUID2StringA(CLSID_CNatCom, achCLSID);

	result = RegOpenKey(HKEY_CLASSES_ROOT, achSampleProgID, &hKey);
	if (result == ERROR_SUCCESS)
	{
		NTCompatibleRegDeleteKey(hKey, TEXT("CLSID"));
		RegCloseKey(hKey);
		hKey = NULL;
		NTCompatibleRegDeleteKey(HKEY_CLASSES_ROOT, achSampleProgID);
	}

	result = RegOpenKey(HKEY_CLASSES_ROOT, TEXT("CLSID"), &hKey);
	result = RegOpenKey(hKey, achCLSID, &hKey2);

	if (result == ERROR_SUCCESS)
	{
		NTCompatibleRegDeleteKey(hKey2, achInprocServer32);
		NTCompatibleRegDeleteKey(hKey2, achProgID);
		RegCloseKey(hKey2);
		hKey2 = NULL;
		NTCompatibleRegDeleteKey(hKey, achCLSID);
	}

	// If this fails, it means somebody else added a subkey to this tree.
	// We're not allowed to touch it so ignore the failure.

	RegCloseKey(hKey);
	hKey = NULL;

	hr = S_OK;

	return hr;
}


////////////////////////////////////////////////////////////////////////////////
//
//	DllGetClassObject()
//
//	COM entry point
//
////
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, VOID **ppv)
{
	HRESULT 		hr ;
	class CNatComCF *	pcf;

	*ppv = NULL ;

	if (rclsid != CLSID_CNatCom)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	pcf = new CNatComCF() ;

	if (!pcf)
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	hr = pcf->QueryInterface(riid, ppv) ;

	if (FAILED(hr))
	{
		delete pcf ;
		return hr ;
	}

	return S_OK ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	DllCanUnloadNow()
//
//	returns refcount of objects which are using this .dll
//
////
STDAPI DllCanUnloadNow()
{
	return g_cObject ;
}
