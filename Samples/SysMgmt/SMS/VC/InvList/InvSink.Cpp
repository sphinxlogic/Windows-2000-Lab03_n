// *************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// *************************************************************
// invsink.cpp
// custom implementation of IWbemObjectSink.
// see invlist.cpp for details.
// *************************************************************

#include <comdef.h>
#include "wbemidl.h"
#include "invsink.h"
#include <stdio.h>


// CInvSink Implementation
// ********************************************************


// Constructor
CInvSink::CInvSink(IWbemServices *pIWbemServices, int Querymode) {

	InitializeCriticalSection(&m_cs);
	m_hEvent = CreateEvent(0, FALSE, FALSE, 0);
	m_lRefCount = 1;
	m_lObjCount = 0;
	m_aObjects = NULL;
	m_iQuerymode = Querymode;
	m_pWbemServices = pIWbemServices;
	m_pWbemServices->AddRef();

}

// Destructor
CInvSink::~CInvSink() {
	
	m_pWbemServices->Release();
	CloseHandle(m_hEvent);
	DeleteCriticalSection(&m_cs);
	for( int i = 0; i < m_lObjCount; i++ ) m_aObjects[i]->Release();

	free(m_aObjects);

}

// QueryInterface
HRESULT CInvSink::QueryInterface(REFIID riid, LPVOID *ppvObj) {

	if( riid == IID_IUnknown || riid == IID_IWbemObjectSink ) {
		*ppvObj = this;
	} else {
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return NOERROR;

}

// AddRef
ULONG CInvSink::AddRef() {

	InterlockedIncrement(&m_lRefCount);
	return (ULONG) m_lRefCount;

}

// Release
ULONG CInvSink::Release() {

	if( InterlockedDecrement(&m_lRefCount) <= 0 ) {
		Lock();
		delete this;
		Unlock();
		return 0;
	} else {
		return (ULONG) m_lRefCount;
	}

}

// Indicate
// Indicate is called by a wbem provider to return results.
HRESULT CInvSink::Indicate(LONG lObjectCount, IWbemClassObject **ppObjArray) {

	if( lObjectCount == 0 ) return WBEM_NO_ERROR;

	Lock();

	// Allocate some more space to store the additional objects
	// given to us by the Indicate method.
	m_aObjects = (IWbemClassObject**) realloc(m_aObjects, (m_lObjCount + lObjectCount) * sizeof(IWbemClassObject*));

	for( int i = 0; i < lObjectCount; i++ ) {
		// Store the objects in our m_aObjects array and call AddRef
		// since we'll be using these objects outside of this method
		m_aObjects[m_lObjCount++] = ppObjArray[i];
		ppObjArray[i]->AddRef();
	}

	Unlock();

	return WBEM_NO_ERROR;
	
}

// SetStatus
// SetStatus is called when the query has finished, or to indicate an error condition.
HRESULT CInvSink::SetStatus(LONG lFlags, HRESULT hResult, BSTR strParam, IWbemClassObject *pObjParam) {
	
	// Check to see if an error occurred or no results were returned...
	if( (FAILED(hResult)) || (m_lObjCount == 0) ) {
		switch( m_iQuerymode ) {
		case INVQUERY_OS:
			printf("No OS Inventory Available.\n\n");
			break;
		case INVQUERY_CPU:
			printf("No CPU Inventory Available.\n\n");
			break;
		case INVQUERY_RAM:
			printf("No Memory Inventory Available.\n\n");
			break;
		}
		m_lObjCount = 0;
	}

	// Call SetEvent to tell the object we are finished, this
	// lets the "WaitForSingleObject" fall through. 
	SetEvent(m_hEvent);

	return WBEM_NO_ERROR;

}