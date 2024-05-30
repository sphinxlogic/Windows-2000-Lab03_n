
/******************************************************************************\
********************************************************************************
* Filename: MethodSink.cpp
*
* Description:  Sink for Method events
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/
#include "stdafx.h"
#include "mtsspyctl.h"
#include "mtsevents.h"
#include "MtsSink.h"
#include "MtsAudit.h"
#include "MTSSpy.h"
#include "packagesink.h"
#include "PackageInfo.h"
#include "methodsink.h"

extern LONGLONG PerformanceFrequency;

STDMETHODIMP  CMethodSink::OnMethodCall(LONGLONG perfCount, MTS_OBJID oid,REFCLSID guidCid, REFIID guidRid, ULONG iMeth)
{
	TimeStack * pStack = m_map[oid];
	if (!pStack)
	{
		pStack = new TimeStack;
		m_map[oid] = pStack;
	}
	_ASSERTE(pStack);
	pStack -> push_front(perfCount);

	m_pSpy -> AddEventToList(perfCount, _TEXT("OnMethodCall"), m_sPackageName);
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", oid);
	m_pSpy -> AddParamValueToList(L"ObjectID", id);

    CComBSTR sCid = GuidToBstr(guidCid);
    CComBSTR sIid = GuidToBstr(guidRid);

	m_pSpy -> AddParamValueToList(L"CLSID", sCid);	
	m_pSpy -> AddParamValueToList(L"riid", sIid);

	TCHAR * pszGuidName = NULL;
	HRESULT hr;
	hr = GetMethodName(guidRid, iMeth, &pszGuidName) ;
    if(hr == S_OK) 
	{ 
		m_pSpy -> AddParamValueToList(L"Method Name", pszGuidName);
	}
	else
	{
		pszGuidName = new _TCHAR[8] ; 
		wsprintf(pszGuidName, _T("%X"), iMeth) ; 
		m_pSpy -> AddParamValueToList(L"v-table index", pszGuidName);
	}
   	IF_AUDIT_DO(OnMethodCall)(perfCount,							
							  oid,						
							  sCid,						
							  sIid,			
							  pszGuidName);



    delete pszGuidName ;
    pszGuidName = NULL ;
	return S_OK;
}

STDMETHODIMP  CMethodSink::OnMethodReturn(LONGLONG perfCount, 
										  MTS_OBJID oid,
										  REFCLSID guidCid, 
										  REFIID guidRid, 
										  ULONG iMeth, 
										  HRESULT hrRet)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnMethodReturn"), m_sPackageName);
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", oid);
	m_pSpy -> AddParamValueToList(L"ObjectID", id);

    CComBSTR sCid = GuidToBstr(guidCid);
    CComBSTR sIid = GuidToBstr(guidRid);

	m_pSpy -> AddParamValueToList(L"CLSID", sCid);
	m_pSpy -> AddParamValueToList(L"riid", sIid);

	TCHAR      * pszGuidName   =   NULL ;
	HRESULT hr;
	hr = GetMethodName(guidRid, iMeth, &pszGuidName) ;
    if(hr != S_OK) 
	{ 
		pszGuidName = new _TCHAR[8] ; 
		wsprintf(pszGuidName, _T("%X"), iMeth) ; 
		m_pSpy -> AddParamValueToList(L"v-table index", pszGuidName);
	}
	else
	{
		m_pSpy -> AddParamValueToList(L"Method Name", pszGuidName);
	}
    
   	IF_AUDIT_DO(OnMethodReturn)(perfCount,							
								  oid,						
								  sCid,						
								  sIid,			
								  pszGuidName,
								  hrRet);


    delete pszGuidName ;
    pszGuidName = NULL ;


	wsprintf(id, L"0x%08X", hrRet);
    m_pSpy -> AddParamValueToList(L"Return Value", id);

	TCHAR sTime[16];
	TimeStack * pStack = m_map[oid];
	LONGLONG oldTime  = pStack -> front();
	pStack -> pop_front();
	_ASSERTE(oldTime);

    DWORD timeDiff = (DWORD)((1000*(perfCount-oldTime))/PerformanceFrequency);
	wsprintf(sTime, _T("%d"), timeDiff);

	m_pSpy -> AddParamValueToList(L"Call time (ms)", sTime);
	if (pStack -> empty())
	{
		delete pStack;
		m_map.erase(oid);
	}
	return S_OK;
}

STDMETHODIMP  CMethodSink::OnMethodException(LONGLONG perfCount, MTS_OBJID oid,REFCLSID guidCid, REFIID guidRid, ULONG iMeth)
{
	m_pSpy -> AddEventToList(perfCount, _TEXT("OnInstanceException"), m_sPackageName);
	
	WCHAR id[16];
	wsprintfW(id,L"0x%08X", oid);
	m_pSpy -> AddParamValueToList(L"ObjectID", id);

    CComBSTR sCid = GuidToBstr(guidCid);
    CComBSTR sIid = GuidToBstr(guidRid);

	m_pSpy -> AddParamValueToList(L"CLSID", sCid);
	m_pSpy -> AddParamValueToList(L"riid", sIid);

	TCHAR      * pszGuidName   =   NULL ;
	HRESULT hr;
	hr = GetMethodName(guidRid, iMeth, &pszGuidName) ;
    if(hr != S_OK) { pszGuidName = new _TCHAR[64] ; lstrcpy(pszGuidName, L"Unknown (no TypeLibrary)") ; }
    m_pSpy -> AddParamValueToList(L"Method Name", pszGuidName);

   	IF_AUDIT_DO(OnMethodException)(perfCount,							
								  oid,						
								  sCid,						
								  sIid,			
								  pszGuidName);


    delete pszGuidName ;
    pszGuidName = NULL ;
	return S_OK;
}

STDMETHODIMP  CMethodSink::Advise()
{
	if (m_dwAdviseCookie)
		return E_FAIL;

	_ASSERTE(m_pCPC);
	HRESULT hr;
	hr = m_pCPC -> FindConnectionPoint(GetIID(), &m_pConPt);
	if (hr == S_OK)
	{
		hr = m_pConPt -> Advise((IUnknown *)(IMtsMethodEvents *)this, &m_dwAdviseCookie);						
		_ASSERTE(hr == S_OK);
	}

	return hr;
}

HRESULT CMethodSink::GetClsidOfTypeLib2 (IID * piid, UUID * puuidClsid)
{
	WCHAR		*	pszBuffIID				= 0x0;
	HRESULT			hr						= S_OK;
	WCHAR			rgBufferIid [40];
	WCHAR			szBufferClsid[40];
	RPC_STATUS		RpcStatus;
	WCHAR			rgBufferKey [256];
	long			lRetVal;
	HKEY			hkey;
	long			lcbszClsidBuff			= 40 * sizeof(WCHAR) ;
	
	//-------------------------------------------------------------------------
	//Convert the iid to it's string form
	RpcStatus = UuidToString ( piid, &pszBuffIID);


	lstrcpy (rgBufferIid, pszBuffIID);
	RpcStringFree (&pszBuffIID);


	//-------------------------------------------------------------------------
	//Create the Registry key to do the lookup with
	lstrcpy (rgBufferKey, L"Interface\\{");
	lstrcat (rgBufferKey, rgBufferIid);
	lstrcat (rgBufferKey, L"}\\TypeLib");

	//UNDONE -- gaganc Perhaps should handle the \interface\<iid1>\forward\<iid2|
	//case also.

	//-------------------------------------------------------------------------
	//Open the appropriate registry key
	//HKEY_CLASSES_ROOT\Interface\{<...interface iid ...>}\Typelib

	lRetVal = RegOpenKey	(
								HKEY_CLASSES_ROOT,
								rgBufferKey,
								&hkey								
							);

	if (lRetVal != ERROR_SUCCESS)
	{
		return E_FAIL;
	}



	//-------------------------------------------------------------------------
	//Obain the clsid from the open key
	lRetVal = RegQueryValueEx	(
									hkey,
									NULL,
									NULL,
									NULL,
									(unsigned char *)szBufferClsid,
									(unsigned long *)&lcbszClsidBuff
								);
	
	
    if(lRetVal != ERROR_SUCCESS)
    {
        RegCloseKey(hkey) ;
        return E_FAIL ;
    }


	//-------------------------------------------------------------------------
	//Get rid of the braces in the begining and the end.

	//Remove the trailing brace
	szBufferClsid[37] = '\0';

	//convert the string form of the clsid to a binary form. Plus 1 will 
	//remove the first brace.
	lRetVal = UuidFromString ((szBufferClsid + 1), puuidClsid);

    if(lRetVal != ERROR_SUCCESS)
    {
        RegCloseKey(hkey) ;
        return E_UNEXPECTED ;
    }        

	//-------------------------------------------------------------------------
	//Prepare to return

	lRetVal = RegCloseKey (hkey);

	return hr;
} //end GetClsidOfTypeLib


//----------------------------------------------------------------------------
// Function:	GetMethodName (INTERNAL FUNCTION)
// Description:	Takes an IID and a method index returns the corresponding 
//              method name.
//           
// Exceptions:	n/a
// Process:		
// Notes:		ppszMethodName should be freed by the client using standard
//				C++ delete.  If hr != S_OK, ppszMethodName will be set to
//				NULL.
//----------------------------------------------------------------------------
HRESULT CMethodSink::GetMethodName (REFIID riid, int iMeth, _TCHAR** ppszMethodName)
{
	BOOL			fRet		= FALSE;
	HRESULT			hr;
	UUID			uuidClsid;
	LCID			lcid		= 0x0;
	ITypeLib	*	pITypeLib	= 0x0;
	ITypeInfo	*	pITypeInfo	= 0x0;
    FUNCDESC    *   pFuncDesc   = 0x0;
    _TCHAR      *   pszMethod   = 0x0;
    BSTR            bstrName ;
    UINT            lcNames     = 0 ;

    IID * piid = (IID *) &riid;

	//Obtain the clsid of the typelib for this interface
	hr = GetClsidOfTypeLib2 (piid, &uuidClsid);

	if (hr != S_OK) goto errExit ;

	//-------------------------------------------------------------------------
	//Obtain the ITypeLib interface on the typelib
	hr = LoadRegTypeLib (
							uuidClsid,		//CLSID
							1,				//Major version number
							0,				//Minor version number
							0,			//the locale id
							&pITypeLib
						);

	// if the default system lcid (0) doesn't work, we try
	// LCID 9 (standard english) and if that doesn't work, we failfast
	if(FAILED(hr))
	{
		hr = LoadRegTypeLib (uuidClsid,	1,0,9,&pITypeLib);
	}


    if(FAILED(hr)) goto errExit ;

	hr = pITypeLib->GetTypeInfoOfGuid (*piid, &pITypeInfo);

    if(FAILED(hr)) goto errExit ;

	hr = pITypeInfo->GetFuncDesc(iMeth, &pFuncDesc) ;

    if(FAILED(hr)) goto errExit ;

    hr = pITypeInfo->GetNames(pFuncDesc->memid, &bstrName, 1, &lcNames) ;

    if(FAILED(hr)) goto errExit ;

    pszMethod = new _TCHAR[lstrlen(bstrName)+1] ;

    if(! pszMethod)
    {
        hr = E_OUTOFMEMORY ;
        goto errExit ;
    }

    lstrcpy(pszMethod, bstrName) ;

    SysFreeString(bstrName) ;
    
errExit:    	
    
    if (pFuncDesc)
	{
		pITypeInfo->ReleaseFuncDesc(pFuncDesc) ;
	}


	if (pITypeInfo)
	{
		pITypeInfo->Release();
	}

    if (pITypeLib)
    {
        pITypeLib->Release() ;
    }

    *ppszMethodName = pszMethod ;

    return hr ;
} 

/* ----------------------------------------------------------------------------
 @func Description
 
 Usage:<nl>
----------------------------------------------------------------------------- */
