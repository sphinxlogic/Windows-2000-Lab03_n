/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */
#include <windows.h>
#include <ocidl.h>

#include <iostream.h>

#include "..\Server\debug.h"
#include "..\Server\CUnknown.h"
#include "..\Server\Student.h"


static const GUID UUID_StudentStruct = 
{ 0xd8b3861a, 0x74c6, 0x11d2, { 0xa0, 0xd6, 0x0, 0xc0, 0x4f, 0xb1, 0x7c, 0xdb } };

CHAR_CONVERSION; // A2W, W2A helpers


/*
 * 
 * Uncomment the below define to use early binding which is the typical case. Late binding is mainly used by scripting languages
 *
 */
//#define _VTABLE_



main(int argc, char* argv[])
{
	cout << "Client side of UDT test" << endl;

	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	_ASSERT(SUCCEEDED(hr));

	LPCLASSFACTORY pCF = NULL;
	hr = CoGetClassObject(CLSID_UDT, CLSCTX_SERVER, NULL, IID_IClassFactory, (PVOID*)&pCF);
	_ASSERT(SUCCEEDED(hr) && pCF);

	LPSTUDENT pStudent = NULL;
	hr = pCF->CreateInstance(NULL, IID_IStudent, (PVOID*)&pStudent);
	_ASSERT(SUCCEEDED(hr) && pStudent);
	RELEASEINTERFACE(pCF);


	// Setup UDT to pass to IStudent::Test1()
	StudentStruct student;
	student.name = SysAllocString(L"Joe");
	student.grade = 10;
	student.type = class_Clown;

	// Setup array of UDT's to pass to IStudent::Test2()
	LPTYPEINFO	pTypeInfo = NULL;
   	LPTYPELIB	pTypelib = NULL;
	LPSAFEARRAY psaStudent = NULL;
	SAFEARRAYBOUND rgbounds = { 4, 0 };
	StudentStruct *pStudentStruct = NULL;
	IRecordInfo* pRecInfo = NULL;

	
	// Fetch the IRecordInfo interface describing the UDT
	hr = LoadRegTypeLib(LIBID_Student, 1, 0, GetUserDefaultLCID(), &pTypelib);
	hr = pTypelib->GetTypeInfoOfGuid(UUID_StudentStruct, &pTypeInfo);
	_ASSERT(SUCCEEDED(hr) && pTypeInfo);
    hr = GetRecordInfoFromTypeInfo(pTypeInfo, &pRecInfo);
	_ASSERT(SUCCEEDED(hr) && pRecInfo);
	RELEASEINTERFACE(pTypeInfo);
	RELEASEINTERFACE(pTypelib);

	psaStudent = SafeArrayCreateEx(VT_RECORD, 1, &rgbounds, pRecInfo);
	RELEASEINTERFACE(pRecInfo);
	_ASSERT(psaStudent);
	hr = SafeArrayAccessData(psaStudent, reinterpret_cast<PVOID*>(&pStudentStruct));
	_ASSERT(SUCCEEDED(hr) && pStudentStruct);

	pStudentStruct[0].grade = 3;
	pStudentStruct[0].name = SysAllocString(L"Shaun");
	pStudentStruct[0].type = class_Clown;
	pStudentStruct[1].grade = 8;
	pStudentStruct[1].name = SysAllocString(L"Fred");
	pStudentStruct[1].type = school_Bully;
	pStudentStruct[2].grade = 12;
	pStudentStruct[2].name = SysAllocString(L"Steve");
	pStudentStruct[2].type = teachers_Favorite;
	pStudentStruct[3].grade = 3;
	pStudentStruct[3].name = SysAllocString(L"Linda");
	pStudentStruct[3].type = teachers_Favorite;

	hr = SafeArrayUnaccessData(psaStudent);
	_ASSERT(SUCCEEDED(hr));
	
#if defined(_VTABLE_) 
#pragma message("_VTABLE_ is defined")

/*
 * Demonstrates passing of a single UDT 
 *
 */
	cout << "Using early binding" << endl;

	DEBUGTRACE(_T("Calling Test1() with the following parameter values: Name:[%S] Grade:[%d] StudentType:[%s]"),
		student.name, student.grade, student.type == school_Bully ? "school_Bully" :
	student.type == class_Clown ? "class_Clown" : "teachers_Favorite");

	cout << "Calling Test1() with the following parameter values:" << endl
		 << " Name: " << W2A(student.name)  << endl
		 << " Grade: " << student.grade << endl
		 << " StudentType: "
		 << ((student.type == school_Bully) ? "school_Bully" : (student.type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;

	hr = pStudent->Test1(&student);

	DEBUGTRACE(_T("Test1() returned. with the following parameter values: Name:[%S] Graduate:[%s] Grade:[%d]"),
		student.name, student.graduate ? "True" : "False", student.grade);

	cout << "Test1() returned. with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Graduate: " << (student.graduate ? " Yes" : "No") << endl;

	SysFreeString(student.name);
	student.name = SysAllocString(L"Susan");
	student.grade = 10;
	student.type = class_Clown;
	
	DEBUGTRACE(_T("Calling Test1() with the following parameter values: Name:[%S] Grade:[%d] StudentType:[%s]"),
		student.name, student.grade, student.type == school_Bully ? "school_Bully" :
	student.type == class_Clown ? "class_Clown" : "teachers_Favorite");

	cout << "Calling Test1() with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Grade: " << student.grade << endl
		 << " StudentType: "
		 << ((student.type == school_Bully) ? "school_Bully" : (student.type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;

	hr = pStudent->Test1(&student);

	DEBUGTRACE(_T("Test1() returned. with the following parameter values: Name:[%S] Graduate:[%s] Grade:[%d]"),
		student.name, student.graduate ? "True" : "False", student.grade);

	cout << "Test1() returned. with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Graduate: " << (student.graduate ? " Yes" : "No") << endl;


	SafeArrayAccessData(psaStudent, reinterpret_cast<PVOID*>(&pStudentStruct));	
	cout << "Calling Test2() with the following parameter values:" << endl;
	for (int i = 0; i <= 3; i++)
	{
		 cout << " Name: " << W2A(pStudentStruct[i].name) << endl
		 << " Grade: " << pStudentStruct[i].grade << endl
		 << " StudentType: "
		 << ((pStudentStruct[i].type == school_Bully) ? "school_Bully" : (pStudentStruct[i].type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;
	}
	SafeArrayUnaccessData(psaStudent);

/*
 * Demonstrates passing an array or UDTS's
 *
 */
	hr = pStudent->Test2(psaStudent);
	
	SafeArrayAccessData(psaStudent, reinterpret_cast<PVOID*>(&pStudentStruct));
	cout << "Test2() returned. with the following parameter values:" << endl ;
	for (i = 0; i <= 3; i++)
	{
		 cout << " Name: " << W2A(pStudentStruct[i].name) << endl
		 << " Graduate: " << (pStudentStruct[i].graduate ? " Yes" : "No") << endl;

	}
	SafeArrayUnaccessData(psaStudent);

#else // Late binding
#pragma message("_VTABLE_ is not defined")
	
	cout << "Using late binding" << endl;

	LPDISPATCH pdisp = NULL;
	hr = pStudent->QueryInterface(IID_IDispatch, (PVOID*)&pdisp);
	_ASSERT(SUCCEEDED(hr) && pdisp);
	RELEASEINTERFACE(pStudent);
	
	
	DISPID dispID;
	DISPPARAMS dispParam;
	VARIANT	  vtRecInfo, vtReturn;
	EXCEPINFO exceptInfo;
	UINT Arg;
	LPWSTR method = L"Test1";
	hr = pdisp->GetIDsOfNames(IID_NULL, &method, 1, GetUserDefaultLCID(), &dispID);
	_ASSERT(SUCCEEDED(hr));
	VariantInit(&vtRecInfo); VariantInit(&vtReturn);

	UINT index;

	// Fetch the IRecordInfo interface describing the UDT	
	hr = pdisp->GetTypeInfo(0, GetUserDefaultLCID(), &pTypeInfo);
	_ASSERT(SUCCEEDED(hr) && pTypeInfo);
	hr = pTypeInfo->GetContainingTypeLib(&pTypelib, &index);
	_ASSERT(SUCCEEDED(hr) && pTypelib);
	hr = pTypelib->GetTypeInfoOfGuid(UUID_StudentStruct, &pTypeInfo);
	_ASSERT(SUCCEEDED(hr) && pTypeInfo);
    hr = GetRecordInfoFromTypeInfo(pTypeInfo, &pRecInfo);
	_ASSERT(SUCCEEDED(hr) && pRecInfo);
	RELEASEINTERFACE(pTypeInfo);
	RELEASEINTERFACE(pTypelib);

	// Setup DISPPARAM with a single UDT
	V_VT(&vtRecInfo) = VT_RECORD|VT_BYREF;
	V_RECORDINFO(&vtRecInfo) = pRecInfo;
	V_RECORD(&vtRecInfo) = &student;
	dispParam.cArgs = 1;
	dispParam.cNamedArgs = 0;
	dispParam.rgdispidNamedArgs = NULL;
	dispParam.rgvarg = &vtRecInfo;
	
	
	DEBUGTRACE(_T("Calling Test1() with the following parameter values: Name:[%S] Grade:[%d] StudentType:[%s]"),
		student.name, student.grade, student.type == school_Bully ? "school_Bully" :
	student.type == class_Clown ? "class_Clown" : "teachers_Favorite");


	cout << "Calling Test1() with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Grade: " << student.grade << endl
		 << " StudentType: "
		 << ((student.type == school_Bully) ? "school_Bully" : (student.type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;

/*
 * Demonstrates passing of a single UDT 
 *
 */
	hr = pdisp->Invoke(dispID, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &dispParam, &vtReturn, &exceptInfo, &Arg);
	
	DEBUGTRACE(_T("Test1() returned. with the following parameter values: Name:[%S] Graduate:[%s] Grade:[%d]"),
		student.name, student.graduate ? "True" : "False", student.grade);

	cout << "Test1() returned. with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Graduate: " << (student.graduate ? " Yes" : "No") << endl;

	SysFreeString(student.name);
	student.name = SysAllocString(L"Susan");
	student.grade = 10;
	student.type = class_Clown;
	
	DEBUGTRACE(_T("Calling Test1() with the following parameter values: Name:[%S] Grade:[%d] StudentType:[%s]"),
		student.name, student.grade, student.type == school_Bully ? "school_Bully" :
	student.type == class_Clown ? "class_Clown" : "teachers_Favorite");

	cout << "Calling Test1() with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Grade: " << student.grade << endl
		 << " StudentType: "
		 << ((student.type == school_Bully) ? "school_Bully" : (student.type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;

	hr = pdisp->Invoke(dispID, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &dispParam, &vtReturn, &exceptInfo, &Arg);

	DEBUGTRACE(_T("Test1() returned. with the following parameter values: Name:[%S] Graduate:[%s] Grade:[%d]"),
		student.name, student.graduate ? "True" : "False", student.grade);

	cout << "Test1() returned. with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Graduate: " << (student.graduate ? " Yes" : "No") << endl;

	SysFreeString(student.name);
	student.name = SysAllocString(L"Linda");
	student.grade = 8;
	student.type = teachers_Favorite;
	DEBUGTRACE(_T("Calling Test1() with the following parameter values: Name:[%S] Grade:[%d] StudentType:[%s]"),
		student.name, student.grade, student.type == school_Bully ? "school_Bully" :
	student.type == class_Clown ? "class_Clown" : "teachers_Favorite");


	cout << "Calling Test1() with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Grade: " << student.grade << endl
		 << " StudentType: "
		 << ((student.type == school_Bully) ? "school_Bully" : (student.type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;

	hr = pdisp->Invoke(dispID, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &dispParam, &vtReturn, &exceptInfo, &Arg);

	DEBUGTRACE(_T("Test1() returned. with the following parameter values: Name:[%S] Graduate:[%s] Grade:[%d]"),
		student.name, student.graduate ? "True" : "False", student.grade);

	cout << "Test1() returned. with the following parameter values:" << endl 
		 << " Name: " << W2A(student.name) << endl
		 << " Graduate: " << (student.graduate ? " Yes" : "No") << endl;

	
	// Setup DISPPARAM with an array of UDT's
	VariantInit(&vtRecInfo);
	V_VT(&vtRecInfo) = VT_RECORD|VT_ARRAY;
	V_RECORDINFO(&vtRecInfo) = pRecInfo;
	V_ARRAY(&vtRecInfo) = psaStudent;
	dispParam.cArgs = 1;
	dispParam.cNamedArgs = 0;
	dispParam.rgdispidNamedArgs = NULL;
	dispParam.rgvarg = &vtRecInfo;
	
	psaStudent = V_ARRAY(dispParam.rgvarg);
	SafeArrayAccessData(psaStudent, reinterpret_cast<PVOID*>(&pStudentStruct));	
	cout << "Calling Test2() with the following parameter values:" << endl;
	for (int i = 0; i <= 3; i++)
	{
		 cout << " Name: " << W2A(pStudentStruct[i].name) << endl
		 << " Grade: " << pStudentStruct[i].grade << endl
		 << " StudentType: "
		 << ((pStudentStruct[i].type == school_Bully) ? "school_Bully" : (pStudentStruct[i].type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;
	}
	SafeArrayUnaccessData(psaStudent);

/*
 * Demonstrates passing an array or UDTS's
 *
 */

/* BUGBUG:
 *
 * If you use late binding to pass a safearray of UDT's; any changes made in the method are not reflected back to the client
 * The 
 */
	method = L"Test2";
	hr = pdisp->GetIDsOfNames(IID_NULL, &method, 1, GetUserDefaultLCID(), &dispID);
	_ASSERT(SUCCEEDED(hr));
	hr = pdisp->Invoke(dispID, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &dispParam, &vtReturn, &exceptInfo, &Arg);

	psaStudent = V_ARRAY(dispParam.rgvarg);
	SafeArrayAccessData(psaStudent, reinterpret_cast<PVOID*>(&pStudentStruct));
	cout << "Test2() returned. with the following parameter values:" << endl ;
	for (i = 0; i <= 3; i++)
	{
		 cout << " Name: " << W2A(pStudentStruct[i].name) << endl
		 << " Graduate: " << (pStudentStruct[i].graduate ? " Yes" : "No") << endl;

	}
	SafeArrayUnaccessData(psaStudent);

	RELEASEINTERFACE(pRecInfo);
	RELEASEINTERFACE(pdisp);
#endif // _VTABLE_
	CoUninitialize();
	return 0;
}