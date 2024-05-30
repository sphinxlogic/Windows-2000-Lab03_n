/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */

#include <iostream.h>

#include "UDTServer.h"
#include "CFactory.h"
#include "Registry.h"
#include "Debug.h"
 


extern DWORD g_dwTLS;
extern HANDLE g_CloseEvent;


// errors Application can return via rich error info
const DWORD EXCEPTION_INVALIDPARAM = 1;
const DWORD EXCEPTION_OUTOFMEMORY = 2;


CHAR_CONVERSION; // A2W, W2A helpers


HRESULT __stdcall
CServer::InterfaceSupportsErrorInfo(REFIID  riid)
{
// TODO add code to handle more than one interface
	HRESULT hr;
	riid == IID_IStudent ? hr = S_OK : hr = S_FALSE;
	return hr;
}


bool __stdcall
RaiseException(DWORD dwException, REFIID guid, LPOLESTR szError, LPOLESTR helpFile, DWORD helpCtx)
{
	ICreateErrorInfo *pCreateErrInfo;
	IErrorInfo *pErrorInfo;
	bool fSuccess = false;
	LANGID *plangID = (LANGID*)TlsGetValue(g_dwTLS);
	HRESULT hr = CreateErrorInfo(&pCreateErrInfo);
	if (FAILED(hr))
		return false;

	switch (dwException)
	{
/*
 * setup exception info
 */
		case EXCEPTION_OUTOFMEMORY:
		case EXCEPTION_INVALIDPARAM:
			helpCtx = dwException;		// hackhack
			fSuccess = true;
			break;
	default:
		_ASSERT(0);						// impossible condition
	}


	if (fSuccess)
	{
		pCreateErrInfo->SetGUID(guid);
		pCreateErrInfo->SetHelpFile(helpFile);
		pCreateErrInfo->SetHelpContext(helpCtx);
		pCreateErrInfo->SetDescription(szError);
		pCreateErrInfo->SetSource(CServer::GetProgID());

		hr = pCreateErrInfo->QueryInterface(IID_IErrorInfo, reinterpret_cast<PVOID*>(&pErrorInfo));

		if (SUCCEEDED(hr))
		{
			hr = SetErrorInfo(0, pErrorInfo);
			RELEASEINTERFACE(pErrorInfo);
		}
		else
			fSuccess = false;
	}
	
	RELEASEINTERFACE(pCreateErrInfo);
	return fSuccess;
}

//
// Constructor
//
#pragma warning(disable : 4355)
CServer::CServer(IUnknown* pUnknownOuter): 
	CUnknown(pUnknownOuter, "CServer"),
	m_pTypeInfo(NULL)
{
	DEBUGTRACE(_T("In CServer ctor"));
	ZeroMemory(&m_ExcepInfo, sizeof(EXCEPINFO));
}

//
// Destructor
//
CServer::~CServer()
{
	DEBUGTRACE(_T("In CServer dtor"));
}

void __stdcall 
CServer::FinalRelease()
{
#if !defined(_DLL_SERVER_)		
	if (CoReleaseServerProcess() == 0) // Last reference to server time to cleanup and exit
#if defined(_APARTMENT_)
		PostQuitMessage(0);
#else	// Free Threaded
		SetEvent(g_CloseEvent);
#endif // _APARTMENT_
#endif // _DLL_SERVER_
	return;
}


HRESULT __stdcall 
	CServer::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 
	CHECKPOINTER(ppv);	


	if (iid == IID_IStudent)
	{
		return FinishQI(static_cast<LPSTUDENT>(this), iid, ppv);
	}
	else if (iid == IID_IDispatch)
	{
		return FinishQI(static_cast<LPDISPATCH>(this), iid, ppv);
	}
	else if (iid == IID_ISupportErrorInfo)
	{
		return FinishQI(static_cast<LPSUPPORTERRORINFO>(this), iid, ppv);
	}
#if defined(LATER)
	else if (iid == IID_IProvideClassInfo2)
	{
		return FinishQI(static_cast<LPPROVIDECLASSINFO2>(this), iid, ppv);
	}
	else if (iid == IID_IProvideClassInfo)
	{
		return FinishQI(static_cast<LPPROVIDECLASSINFO>(this), iid, ppv);
	}
#endif
	return CUnknown::NondelegatingQueryInterface(iid, ppv);
}



///////////////////////////////////////////////////////////
//
// Creation function used by CFactory
//
HRESULT CServer::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent) 
{
	*ppNewComponent = new CServer(pUnknownOuter) ;
	DEBUGTRACE(_T("In CServer::CreateInstance\n")) ;
	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// Initialize the component and create the contained component.
//


HRESULT __stdcall
CServer::Init(const CFactoryData *pData)
{
#if !defined(_DLL_SERVER_)		
	CoAddRefServerProcess();
#endif // _DLL_SERVER_

	HRESULT hr;
	// Load typeinfo
	if (NULL == m_pTypeInfo)
	{
		LPTYPELIB pTypeLib;
		OLECHAR m_FileName[MAX_PATH];


		DWORD Major = HIWORD(pData->m_LibVersion);
		DWORD Minor = LOWORD(pData->m_LibVersion);
		LCID  lcid = pData->m_lcid;
		hr = LoadRegTypeLib(LIBID_Student, HIWORD(pData->m_LibVersion), LOWORD(pData->m_LibVersion), pData->m_lcid, &pTypeLib);
/* 
 * First try and load the typelibrary from the DLL's resources
 */
		if (FAILED(hr))
		{
			char FileName[MAX_PATH];
			GetModuleFileName(GetHInstance(), FileName, sizeof(FileName));
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, FileName, sizeof(FileName), m_FileName, sizeof(m_FileName));
			DEBUGTRACE(_T("LoadRegTypeLib failed, loading typelib from filename [%S]\n"), m_FileName);
			hr = LoadTypeLibEx(m_FileName, REGKIND_REGISTER, &pTypeLib);
/*
 * If that fails then resort to loading the typelibrary as a seperate file
 * this will only look for a typelibrary with the same name as the application
 */
			if (FAILED(hr))
			{
				LPOLESTR p = wcsrchr(m_FileName, '.');
				*p = NULL;
				wcscat(m_FileName, L".tlb");
				DEBUGTRACE(_T("LoadRegTypeLib failed, loading typelib from filename [%S]\n"), m_FileName);
				hr = LoadTypeLibEx(m_FileName, REGKIND_REGISTER, &pTypeLib);
				if (FAILED(hr))
				{
					DEBUGTRACE(_T("LoadTypeLib failed bombing out [%X]\n"), hr);
					goto Error;
				}
			}
		}
		hr = pTypeLib->GetTypeInfoOfGuid(IID_IStudent, &m_pTypeInfo);
		if FAILED(hr)
		{
			DEBUGTRACE(_T("GetTypeInfoOfGuid failed [%X]\n"), hr);
			goto Error;
		}
		RELEASEINTERFACE(pTypeLib);
	}
	return S_OK;
Error:
	return E_FAIL;
}

 
/*
 * Interface IDispatch implementation
 *
 */

HRESULT __stdcall
CServer::GetTypeInfoCount(UINT *pctinfo)
{
	DEBUGTRACE(_T("In CServer::GetTypeInfoCount\n"));
	CHECKPOINTER(pctinfo);

	*pctinfo = 1;
	return NOERROR;
}


HRESULT __stdcall
CServer::GetTypeInfo( UINT itinfo, LCID lcid, LPTYPEINFO *pptinfo)
{
	DEBUGTRACE(_T("In CServer::GetTypeInfo\n"));
	CHECKPOINTER(pptinfo);

	if ( 0 != itinfo)
	{
		*pptinfo = NULL;
		return DISP_E_BADINDEX;
	}

	if (LOCALE_SYSTEM_DEFAULT == lcid || 0 == lcid)
		lcid = GetSystemDefaultLCID();
	else if (LOCALE_USER_DEFAULT == lcid)
		lcid = GetUserDefaultLCID();

	switch(PRIMARYLANGID(lcid))
	{
		case LANG_ENGLISH:
		case LANG_NEUTRAL:
			*pptinfo = GetDefTypeInfo(); //currently only one typeinfo supported
			break;
		default:
			*pptinfo = NULL;
			return DISP_E_UNKNOWNLCID;
	}

	(*pptinfo)->AddRef();
	return NOERROR;
}



HRESULT __stdcall
CServer::GetIDsOfNames(
   REFIID riid, OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgdispID)
{
	LPTYPEINFO ptinfo;
	DEBUGTRACE(_T("In CServer::GetIDsOfNames\n"));
	CHECKPOINTER(rgdispID);

	if (IID_NULL != riid)
	{
		*rgdispID = DISPID_UNKNOWN;
		return DISP_E_UNKNOWNINTERFACE;
	}

	if (LOCALE_SYSTEM_DEFAULT == lcid || 0 == lcid)
		lcid = GetSystemDefaultLCID();
	else if (LOCALE_USER_DEFAULT == lcid)
		lcid = GetUserDefaultLCID();

	switch(PRIMARYLANGID(lcid))
	{
		case LANG_ENGLISH:
		case LANG_NEUTRAL:
			ptinfo = GetDefTypeInfo();
			break;
		default:
			*rgdispID = DISPID_UNKNOWN;
			return DISP_E_UNKNOWNLCID;
	}
	
	return DispGetIDsOfNames(ptinfo, rgszNames, cNames, rgdispID);
}



HRESULT __stdcall
CServer::Invoke(
	DISPID dispID, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS *pDispParams, VARIANT *pvarResult, 
	EXCEPINFO *pexcepInfo, UINT *pArgError)
{
	HRESULT hr;
	LANGID langID = PRIMARYLANGID(lcid);

	DEBUGTRACE(_T("In CServer::Invoke\n"));
	
	if (IID_NULL != riid)
		return DISP_E_UNKNOWNINTERFACE;

	SetErrorInfo(0, NULL);

	TlsSetValue(g_dwTLS, &langID);
	hr = DispInvoke(static_cast<LPDISPATCH>(this), 
		    GetDefTypeInfo(), dispID, wFlags, pDispParams,
			pvarResult, pexcepInfo, pArgError);

	return hr;
}


/*
 * IStudent
 *
 */
HRESULT __stdcall 
CServer::Test1(LPSTUDENTSTRUCT lpStudent)
{
	DEBUGTRACE(_T("In CServer::Test1. Structure has the following values: Name: [%S] Grade: [%d] Type: [%s] Graduate: [%s]"),
		lpStudent->name, lpStudent->grade, lpStudent->type == school_Bully ? "school_Bully" :
	lpStudent->type == class_Clown ? "class_Clown" : "teachers_Favorite", lpStudent->graduate ? "True" : "False");

	cout << "In structure has the following values:" << endl
		 << "Name: " << W2A(lpStudent->name) << endl
		 << " Grade: " << lpStudent->grade << endl
		 << " StudentType: "
		 << ((lpStudent->type == school_Bully) ? "school_Bully" : (lpStudent->type == class_Clown) ? "class_Clown" : "teachers_Favorite")
		 << endl;

	switch (lpStudent->type)
	{
	case class_Clown:
		lpStudent->graduate = lpStudent->grade <=5 ? TRUE : FALSE;
		break;
	case school_Bully:
		lpStudent->graduate = FALSE;
		break;
	case teachers_Favorite:
		lpStudent->graduate = TRUE;
		break;
	}
	
	if (lstrcmpW(L"Joe", lpStudent->name)==0)
		// we don't like Joe
		lpStudent->graduate = FALSE;

	if (lpStudent->graduate)
		lpStudent->grade++;

	DEBUGTRACE(_T("[%S] has [%s] and is in [%d] grade"), 
		lpStudent->name, lpStudent->graduate ? "graduated" : "not graduated", lpStudent->grade);

	cout << "After processing structure the values are now:" << endl 
		 << " Name: " << W2A(lpStudent->name) << endl
		 << " Graduate: " << (lpStudent->graduate ? " Yes" : "No") << endl;

	return S_OK;
}


HRESULT __stdcall 
CServer::Test2(LPSAFEARRAY saStudent)
{
	CHAR_CONVERSION;
	LPSTUDENTSTRUCT aStudentStruct;

	cout << "In CServer::Test2" << endl;

	HRESULT hr = SafeArrayAccessData(saStudent, (PVOID*)&aStudentStruct);
	_ASSERT(SUCCEEDED(hr));
	UINT dim, lastElem;
	dim	= SafeArrayGetDim(saStudent);
	SafeArrayGetUBound(saStudent, dim, reinterpret_cast<long*>(&lastElem));
	_ASSERT(dim == 1); // Only support 1 dimension

	for (UINT i = 0; i <= lastElem; i++)
	// call Test1() to do the work
		_ASSERT(SUCCEEDED(Test1(&aStudentStruct[i])));

	hr = SafeArrayUnaccessData(saStudent);
	_ASSERT(SUCCEEDED(hr));

	cout << "Leaving CServer::Test2" << endl;

	return S_OK;
}