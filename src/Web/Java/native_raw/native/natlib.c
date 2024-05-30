
/*

Copyright (c) 1996-1997  Microsoft Corporation

*/

#include <windows.h>
#include <native.h>
#include "JMain.h"
#include "JFoo.h"
#include "JThread1.h"
#include "JThread2.h"

////////////////////////////////////////////////////////////////////////////////
//
//	RNIGetCompatibleVersion
//
//	Called by the virtual machine to determine what level of RNI compatibility
//	this DLL offers.
//
////
DWORD __cdecl RNIGetCompatibleVersion()
{
	return RNIVER;
}

////////////////////////////////////////////////////////////////////////////////
//
//	JMain_Square()
//
//	returns the square of its parameter;  simple callout from java to
//	native code to perform this operation.
//
////
__declspec(dllexport) long __cdecl JMain_Square(struct HJMain *pThis, long lVal)
{
	return lVal * lVal ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	JMain_DoubleInstanceVar()
//
//	executes a java-implemented method to retrieve the value of an
//	instance variable;  returns twice the retrieved value.
//
////
__declspec(dllexport) void __cdecl JMain_DoubleInstanceVar(struct HJMain *pThis)
{
	long lVal ;

	lVal = execute_java_dynamic_method(0, (HObject*) pThis, "GetiVar1", "()I") ;

	pThis->iVar1 = lVal << 1 ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	Jmain_showMemberArray()
//
//	executes a class method which returns a private member array of
//	ints (java); loops through and displays the array members.
//
////
__declspec(dllexport) void __cdecl JMain_showMemberArray(struct HJMain *pThis)
{
	ClassArrayOfInt *paiVar1 ;
	long	*plVar2 ;
	int	cIndex ;

	// get a pointer to an instance array of int, and display it.
	paiVar1 = (ClassArrayOfInt *) execute_java_dynamic_method(0, (HObject *) pThis, "GetiCVar2", "()[I") ;
	plVar2 = paiVar1->body ;

	for (cIndex = 0; cIndex < paiVar1->length; cIndex++)
	{
		printf("%5d", *plVar2++) ;
	}
	printf("\n") ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	JMain_Various()
//
//	finds JFoo class; executes a static method in that class
//
////
__declspec(dllexport) void __cdecl JMain_Various(struct HJMain *pThis)
{
	_int64 i64Val = 10 ;
	ClassClass *pcls = FindClass(NULL, "JFoo", TRUE) ;

	if (pcls)
	{
		// and exec the static method
		execute_java_static_method(NULL, pcls, "StaticMethod", "(J)V", i64Val) ;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	w32CreateEvent()
//
//	wrapper for win32 API CreateEvent()
//
////
__declspec(dllexport) long __cdecl JMain_w32CreateEvent(struct HJMain *pThis, long bInit)
{
	BOOL	bInitialState ;
	HANDLE	hEvent ;

	// determine if initial state is signaled or non-signaled.
	if (bInit)
	{
		bInitialState = TRUE ;
	}
	else
	{
		bInitialState = FALSE ;
	}

	// create Event object and return handle
	return (long) CreateEvent(NULL, FALSE, bInitialState, NULL) ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	w32PulseEvent()
//
//	wrapper for win32 API PulseEvent()
//
////
__declspec(dllexport) void __cdecl JThread1_w32PulseEvent(struct HJThread1 *pThis,long hEvent)
{
	PulseEvent((HANDLE) hEvent) ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	w32CloseHandle()
//
//	wrapper for win32 API CloseHandle()
//
////
__declspec(dllexport) long __cdecl JThread2_w32CloseHandle(struct HJThread2 *pThis, long hObject)
{
	return (long) CloseHandle((HANDLE) hObject) ;
}

////////////////////////////////////////////////////////////////////////////////
//
//	GCSafeNative()
//
//	method demonstrates GC safe way of performing GC-sensitive operations
//	in native code.
//
////
__declspec(dllexport) void __cdecl JThread2_GCSafeNative(struct HJThread2 *pThis, long hEvent)
{
	struct
	{
		HJFoo *pJFoo1, *pJFoo2 ;
	} gcSafe ;				// struct holds out pointers to JObjects
	GCFrame gcf ;

	// GCFramePush() creates storage for GC-sensitive data (JObjects in this case)
	GCFramePush(&gcf, &gcSafe, sizeof(gcSafe)) ;

	// set our member variables to point to two JObjects
	gcSafe.pJFoo1 = (HJFoo *) execute_java_constructor(0, "JFoo", 0, "(I)", 10) ;
	gcSafe.pJFoo2 = (HJFoo *) execute_java_constructor(0, "JFoo", 0, "()") ;

	// call GCEnable() - we don't know how long we might be blocked
	GCEnable() ;

	// block
	WaitForSingleObject((HANDLE) hEvent, INFINITE) ;

	// display instance variable values for above-created JObjects.
	printf("gcSafe.pJFoo1->m_iVal = %d\tgcSafe.pJFoo2->m_iVal = %d\n", gcSafe.pJFoo1->m_iVal, gcSafe.pJFoo2->m_iVal) ;

	// disable GC and pop our storage
	GCDisable() ;
	GCFramePop(&gcf) ;
}
