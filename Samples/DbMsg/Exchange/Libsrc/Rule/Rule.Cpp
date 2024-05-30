// ----------------------------------------------------------------------------
//	Rules.cpp:	Implementation of DLL Exports.
//
//	Note:	Proxy/Stub Information
//			To build a separate proxy/stub DLL, 
//			run nmake -f Rulesps.mk in the project directory.
//
//  Copyright (C) Microsoft Corp. 1986-1998.  All rights reserved.
// ----------------------------------------------------------------------------


#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "Rule.h"

#include "Rule_i.c"
#include "ComPtrs.h"
#include "PropVal.h"
#include "BaseCondition.h"
#include "BitmaskCondition.h"
#include "ComparePropsCondition.h"
#include "ContentCondition.h"
#include "ExistsCondition.h"
#include "PropertyCondition.h"
#include "SizeCondition.h"
#include "CommentCondition.h"
#include "SubCondition.h"
#include "LogicalCondition.h"
#include "ActionObj.h"
#include "ActionCollection.h"
#include "RuleObj.h"
#include "RuleCollection.h"

CEDKRulesComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Rules, CRules)
	OBJECT_ENTRY(CLSID_Rule, CRule)
	OBJECT_ENTRY(CLSID_BitmaskCondition, CBitmaskCondition)
	OBJECT_ENTRY(CLSID_CommentCondition, CCommentCondition)
	OBJECT_ENTRY(CLSID_ComparePropsCondition, CComparePropsCondition)
	OBJECT_ENTRY(CLSID_ContentCondition, CContentCondition)
	OBJECT_ENTRY(CLSID_ExistsCondition, CExistsCondition)
	OBJECT_ENTRY(CLSID_LogicalCondition, CLogicalCondition)
	OBJECT_ENTRY(CLSID_PropertyCondition, CPropertyCondition)
	OBJECT_ENTRY(CLSID_SizeCondition, CSizeCondition)
	OBJECT_ENTRY(CLSID_SubCondition, CSubCondition)
	OBJECT_ENTRY(CLSID_Action, CAction)
	OBJECT_ENTRY(CLSID_PropVal, CPropVal)
END_OBJECT_MAP()

// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}

HRESULT CEDKRulesComModule::CreateResInstance(ULONG rt,LPVOID *ppRes)
{
	HRESULT	hr=E_INVALIDARG;

	if(ppRes)
	{
		switch(rt)
		{
		case RES_AND:
		case RES_OR:
		case RES_NOT:
			hr = CLogicalResObject::CreateInstance((CLogicalResObject**)ppRes);
			break;
		case RES_BITMASK:
			hr = CBitmaskResObject::CreateInstance((CBitmaskResObject**)ppRes);
			break;
		case RES_CONTENT:
			hr = CContentResObject::CreateInstance((CContentResObject**)ppRes);
			break;
		case RES_COMMENT:
			hr = CCommentResObject::CreateInstance((CCommentResObject**)ppRes);
			break;
		case RES_COMPAREPROPS:
			hr = CComparePropsResObject::CreateInstance((CComparePropsResObject**)ppRes);
			break;
		case RES_EXIST:
			hr = CExistsResObject::CreateInstance((CExistsResObject**)ppRes);
			break;
		case RES_PROPERTY:
			hr = CPropertyResObject::CreateInstance((CPropertyResObject**)ppRes);
			break;
		case RES_SIZE:
			hr = CSizeResObject::CreateInstance((CSizeResObject**)ppRes);
			break;
		case RES_SUBRESTRICTION:
			hr = CSubResObject::CreateInstance((CSubResObject**)ppRes);
			break;
		}
	}
	return hr;
}
