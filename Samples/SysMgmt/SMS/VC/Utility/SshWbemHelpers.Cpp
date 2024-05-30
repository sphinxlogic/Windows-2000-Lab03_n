/////////////////////////////////////////////////////////////////////////////// 
//  SshWbemHelpers.cpp
// 
//  WBEM helper classes - see SshWbemHelpers.h for more information
//
//
//  Copyright (c)1997-99 Microsoft Corporation, All Rights Reserved
///////////////////////////////////////////////////////////////////////////////



#ifdef EXT_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WIN32_LEAN_AND_MEAN
#include <comdef.h>
#include <wbemidl.h>
#include <tchar.h>
#include <SshWbemHelpers.h>

#define REFCOUNT(obj) obj->AddRef()?obj->Release():0xFFFFFFFF



//\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///
//                                                                         //
//   CWbemException                                                        //
//                                                                         //
//\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///

IErrorInfo * CWbemException::GetErrorObject()
{
	IErrorInfo * pEI = NULL;
	GetErrorInfo(0, &pEI);
	return pEI;
}


IErrorInfo * CWbemException::MakeErrorObject(_bstr_t sDescription)
{
	ICreateErrorInfoPtr pcerrinfo;
	HRESULT hr;
	
	hr = CreateErrorInfo(&pcerrinfo);
	
	if(SUCCEEDED(hr))
	{
		pcerrinfo->SetDescription(sDescription);
		pcerrinfo->SetSource(_bstr_t("CWbemException"));
		
		IErrorInfoPtr perrinfo;
		hr = pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID FAR*) &perrinfo);
		
		if(SUCCEEDED(hr))  
		{      
			SetErrorInfo(0, perrinfo);    
		}
	}
	
	return GetErrorObject();
}


void CWbemException::GetWbemStatusObject()
{
	m_pWbemError = new CWbemClassObject();
	
	if(m_pWbemError)
	{
		IErrorInfoPtr pEI = ErrorInfo();
		
		if(pEI)
		{
			pEI->QueryInterface(IID_IWbemClassObject, (void**)&(*m_pWbemError));
			
			if(*m_pWbemError)
			{
				if(!m_pWbemError->GetLong(_bstr_t("StatusCode")))
				{
					m_pWbemError->Put(_bstr_t("StatusCode"),m_hr);
				}
			}
		}
	}
}



CWbemException::CWbemException(HRESULT hr,_bstr_t sDescription) : 
_com_error(hr,GetErrorObject()),
m_sDescription(sDescription),
m_hr(hr)
{
	GetWbemStatusObject();
}



CWbemException::CWbemException(_bstr_t sDescription) : 
_com_error(WBEM_E_FAILED,MakeErrorObject(sDescription)),
m_sDescription(sDescription)
{
	GetWbemStatusObject();
}


CWbemClassObject CWbemException::GetWbemError()
{
	return *m_pWbemError;
}


/*
WBEM_E_FAILED  = 0x80041001,
WBEM_E_NOT_FOUND  = WBEM_E_FAILED + 1,
WBEM_E_ACCESS_DENIED = WBEM_E_NOT_FOUND + 1,
WBEM_E_PROVIDER_FAILURE = WBEM_E_ACCESS_DENIED + 1,
WBEM_E_TYPE_MISMATCH = WBEM_E_PROVIDER_FAILURE + 1,
WBEM_E_OUT_OF_MEMORY = WBEM_E_TYPE_MISMATCH + 1,
WBEM_E_INVALID_CONTEXT  = WBEM_E_OUT_OF_MEMORY + 1,
WBEM_E_INVALID_PARAMETER   = WBEM_E_INVALID_CONTEXT + 1,
WBEM_E_NOT_AVAILABLE = WBEM_E_INVALID_PARAMETER + 1,
WBEM_E_CRITICAL_ERROR   = WBEM_E_NOT_AVAILABLE + 1,
WBEM_E_INVALID_STREAM   = WBEM_E_CRITICAL_ERROR + 1,
WBEM_E_NOT_SUPPORTED = WBEM_E_INVALID_STREAM + 1,
WBEM_E_INVALID_SUPERCLASS  = WBEM_E_NOT_SUPPORTED + 1,
WBEM_E_INVALID_NAMESPACE   = WBEM_E_INVALID_SUPERCLASS + 1,
WBEM_E_INVALID_OBJECT   = WBEM_E_INVALID_NAMESPACE + 1,
WBEM_E_INVALID_CLASS = WBEM_E_INVALID_OBJECT + 1,
WBEM_E_PROVIDER_NOT_FOUND  = WBEM_E_INVALID_CLASS + 1,
WBEM_E_INVALID_PROVIDER_REGISTRATION   = WBEM_E_PROVIDER_NOT_FOUND + 1,
WBEM_E_PROVIDER_LOAD_FAILURE  = WBEM_E_INVALID_PROVIDER_REGISTRATION + 1,
WBEM_E_INITIALIZATION_FAILURE = WBEM_E_PROVIDER_LOAD_FAILURE + 1,
WBEM_E_TRANSPORT_FAILURE   = WBEM_E_INITIALIZATION_FAILURE + 1,
WBEM_E_INVALID_OPERATION   = WBEM_E_TRANSPORT_FAILURE + 1,
WBEM_E_INVALID_QUERY = WBEM_E_INVALID_OPERATION + 1,
WBEM_E_INVALID_QUERY_TYPE  = WBEM_E_INVALID_QUERY + 1,
WBEM_E_ALREADY_EXISTS   = WBEM_E_INVALID_QUERY_TYPE + 1,
WBEM_E_OVERRIDE_NOT_ALLOWED   = WBEM_E_ALREADY_EXISTS + 1,
WBEM_E_PROPAGATED_QUALIFIER   = WBEM_E_OVERRIDE_NOT_ALLOWED + 1,
WBEM_E_PROPAGATED_PROPERTY = WBEM_E_PROPAGATED_QUALIFIER + 1,
WBEM_E_UNEXPECTED = WBEM_E_PROPAGATED_PROPERTY + 1,
WBEM_E_ILLEGAL_OPERATION   = WBEM_E_UNEXPECTED + 1,
WBEM_E_CANNOT_BE_KEY = WBEM_E_ILLEGAL_OPERATION + 1,
WBEM_E_INCOMPLETE_CLASS = WBEM_E_CANNOT_BE_KEY + 1,
WBEM_E_INVALID_SYNTAX   = WBEM_E_INCOMPLETE_CLASS + 1,
WBEM_E_NONDECORATED_OBJECT = WBEM_E_INVALID_SYNTAX + 1,
WBEM_E_READ_ONLY  = WBEM_E_NONDECORATED_OBJECT + 1,
WBEM_E_PROVIDER_NOT_CAPABLE   = WBEM_E_READ_ONLY + 1,
WBEM_E_CLASS_HAS_CHILDREN  = WBEM_E_PROVIDER_NOT_CAPABLE + 1,
WBEM_E_CLASS_HAS_INSTANCES = WBEM_E_CLASS_HAS_CHILDREN + 1,
WBEM_E_QUERY_NOT_IMPLEMENTED  = WBEM_E_CLASS_HAS_INSTANCES + 1,
WBEM_E_ILLEGAL_NULL  = WBEM_E_QUERY_NOT_IMPLEMENTED + 1,
WBEM_E_INVALID_QUALIFIER_TYPE = WBEM_E_ILLEGAL_NULL + 1,
WBEM_E_INVALID_PROPERTY_TYPE  = WBEM_E_INVALID_QUALIFIER_TYPE + 1,
WBEM_E_VALUE_OUT_OF_RANGE  = WBEM_E_INVALID_PROPERTY_TYPE + 1,
WBEM_E_CANNOT_BE_SINGLETON = WBEM_E_VALUE_OUT_OF_RANGE + 1,
WBEM_E_INVALID_CIM_TYPE = WBEM_E_CANNOT_BE_SINGLETON + 1,
WBEM_E_INVALID_METHOD   = WBEM_E_INVALID_CIM_TYPE + 1,
WBEM_E_INVALID_METHOD_PARAMETERS = WBEM_E_INVALID_METHOD + 1,
WBEM_E_SYSTEM_PROPERTY  = WBEM_E_INVALID_METHOD_PARAMETERS + 1,
WBEM_E_INVALID_PROPERTY = WBEM_E_SYSTEM_PROPERTY + 1,
WBEM_E_CALL_CANCELLED   = WBEM_E_INVALID_PROPERTY + 1,
WBEM_E_SHUTTING_DOWN = WBEM_E_CALL_CANCELLED + 1,
WBEM_E_PROPAGATED_METHOD   = WBEM_E_SHUTTING_DOWN + 1,
WBEM_E_UNSUPPORTED_PARAMETER  = WBEM_E_PROPAGATED_METHOD + 1,
WBEM_E_MISSING_PARAMETER_ID   = WBEM_E_UNSUPPORTED_PARAMETER + 1,
WBEM_E_INVALID_PARAMETER_ID   = WBEM_E_MISSING_PARAMETER_ID + 1,
WBEM_E_NONCONSECUTIVE_PARAMETER_IDS = WBEM_E_INVALID_PARAMETER_ID + 1,
WBEM_E_PARAMETER_ID_ON_RETVAL = WBEM_E_NONCONSECUTIVE_PARAMETER_IDS + 1,
WBEM_E_INVALID_OBJECT_PATH = WBEM_E_PARAMETER_ID_ON_RETVAL + 1,
WBEM_E_OUT_OF_DISK_SPACE   = WBEM_E_INVALID_OBJECT_PATH + 1,
WBEMESS_E_REGISTRATION_TOO_BROAD = 0x80042001,
WBEMESS_E_REGISTRATION_TOO_PRECISE  = WBEMESS_E_REGISTRATION_TOO_BROAD + 1
*/

_bstr_t CWbemException::GetWbemErrorText(HRESULT hr)
{
	_bstr_t sRet;
	
	switch (hr)
	{
	case WBEM_NO_ERROR : sRet = "WBEM_NO_ERROR"; break;
		
		// Non-error status codes.
		// =======================
		
	case WBEM_S_NO_MORE_DATA : sRet = "WBEM_S_NO_MORE_DATA "; break;
	case WBEM_S_ALREADY_EXISTS : sRet = "WBEM_S_ALREADY_EXISTS"; break;
	case WBEM_S_RESET_TO_DEFAULT: sRet = "WBEM_S_RESET_TO_DEFAULT"; break;
		
		// Errors.
		// =======
		
	case WBEM_E_FAILED : sRet = "WBEM_E_FAILED"; break;
	case WBEM_E_NOT_FOUND: sRet = "WBEM_E_NOT_FOUND"; break;
	case WBEM_E_ACCESS_DENIED: sRet = "WBEM_E_ACCESS_DENIED"; break;
	case WBEM_E_PROVIDER_FAILURE: sRet = "WBEM_E_PROVIDER_FAILURE"; break;
	case WBEM_E_TYPE_MISMATCH: sRet = "WBEM_E_TYPE_MISMATCH"; break;
	case WBEM_E_OUT_OF_MEMORY: sRet = "WBEM_E_OUT_OF_MEMORY"; break;
	case WBEM_E_INVALID_CONTEXT: sRet = "WBEM_E_INVALID_CONTEXT"; break;
	case WBEM_E_INVALID_PARAMETER: sRet = "WBEM_E_INVALID_PARAMETER"; break;
	case WBEM_E_NOT_AVAILABLE: sRet = "WBEM_E_NOT_AVAILABLE"; break;
	case WBEM_E_CRITICAL_ERROR: sRet = "WBEM_E_CRITICAL_ERROR"; break;
	case WBEM_E_INVALID_STREAM: sRet = "WBEM_E_INVALID_STREAM"; break;
	case WBEM_E_NOT_SUPPORTED: sRet = "WBEM_E_NOT_SUPPORTED"; break;
	case WBEM_E_INVALID_SUPERCLASS: sRet = "WBEM_E_INVALID_SUPERCLASS"; break;
	case WBEM_E_INVALID_NAMESPACE: sRet = "WBEM_E_INVALID_NAMESPACE"; break;
	case WBEM_E_INVALID_OBJECT: sRet = "WBEM_E_INVALID_OBJECT"; break;
	case WBEM_E_INVALID_CLASS: sRet = "WBEM_E_INVALID_CLASS"; break;
	case WBEM_E_PROVIDER_NOT_FOUND: sRet = "WBEM_E_PROVIDER_NOT_FOUND"; break;
	case WBEM_E_INVALID_PROVIDER_REGISTRATION: sRet = "WBEM_E_INVALID_PROVIDER_REGISTRATION"; break;
	case WBEM_E_PROVIDER_LOAD_FAILURE: sRet = "WBEM_E_PROVIDER_LOAD_FAILURE"; break;
	case WBEM_E_INITIALIZATION_FAILURE: sRet = "WBEM_E_INITIALIZATION_FAILURE"; break;
	case WBEM_E_TRANSPORT_FAILURE: sRet = "WBEM_E_TRANSPORT_FAILURE"; break;
	case WBEM_E_INVALID_OPERATION: sRet = "WBEM_E_INVALID_OPERATION"; break;
	case WBEM_E_INVALID_QUERY: sRet = "WBEM_E_INVALID_QUERY"; break;
	case WBEM_E_INVALID_QUERY_TYPE: sRet = "WBEM_E_INVALID_QUERY_TYPE"; break;
	case WBEM_E_ALREADY_EXISTS: sRet = "WBEM_E_ALREADY_EXISTS"; break;
	case WBEM_E_OVERRIDE_NOT_ALLOWED: sRet = "WBEM_E_OVERRIDE_NOT_ALLOWED"; break;
	case WBEM_E_PROPAGATED_QUALIFIER: sRet = "WBEM_E_PROPAGATED_QUALIFIER"; break;
	case WBEM_E_UNEXPECTED: sRet = "WBEM_E_UNEXPECTED"; break;
	case WBEM_E_ILLEGAL_OPERATION: sRet = "WBEM_E_ILLEGAL_OPERATION"; break;
	case WBEM_E_CANNOT_BE_KEY: sRet = "WBEM_E_CANNOT_BE_KEY"; break;
	case WBEM_E_INCOMPLETE_CLASS: sRet = "WBEM_E_INCOMPLETE_CLASS"; break;
	case WBEM_E_INVALID_CIM_TYPE: sRet = "WBEM_E_INVALID_CIM_TYPE"; break;
	case WBEM_E_NONDECORATED_OBJECT: sRet = "WBEM_E_NONDECORATED_OBJECT"; break;
	case WBEM_E_READ_ONLY: sRet = "WBEM_E_READ_ONLY"; break;
	case WBEM_E_PROVIDER_NOT_CAPABLE: sRet = "WBEM_E_PROVIDER_NOT_CAPABLE"; break;
	case WBEM_E_CLASS_HAS_CHILDREN: sRet = "WBEM_E_CLASS_HAS_CHILDREN"; break;
	case WBEM_E_CLASS_HAS_INSTANCES: sRet = "WBEM_E_CLASS_HAS_INSTANCES"; break;
	case WBEM_E_QUERY_NOT_IMPLEMENTED: sRet = "WBEM_E_QUERY_NOT_IMPLEMENTED"; break;
	case WBEM_E_ILLEGAL_NULL: sRet = "WBEM_E_ILLEGAL_NULL"; break;
	case WBEM_E_INVALID_QUALIFIER_TYPE: sRet = "WBEM_E_INVALID_QUALIFIER_TYPE"; break;
	case WBEM_E_INVALID_PROPERTY_TYPE: sRet = "WBEM_E_INVALID_PROPERTY_TYPE"; break;
	case WBEM_E_VALUE_OUT_OF_RANGE: sRet = "WBEM_E_VALUE_OUT_OF_RANGE"; break;
	case WBEM_E_CANNOT_BE_SINGLETON: sRet = "WBEM_E_CANNOT_BE_SINGLETON"; break;
	case WBEMESS_E_REGISTRATION_TOO_BROAD: sRet = "WBEMESS_E_REGISTRATION_TOO_BROAD"; break;
	case WBEMESS_E_REGISTRATION_TOO_PRECISE: sRet = "WBEMESS_E_REGISTRATION_TOO_PRECISE"; break;
		
	case WBEM_E_INVALID_METHOD: sRet = "WBEM_E_INVALID_METHOD"; break;
	case WBEM_E_INVALID_METHOD_PARAMETERS: sRet = "WBEM_E_INVALID_METHOD_PARAMETERS"; break;
	case WBEM_E_SYSTEM_PROPERTY: sRet = "WBEM_E_SYSTEM_PROPERTY"; break;
	case WBEM_E_INVALID_PROPERTY: sRet = "WBEM_E_INVALID_PROPERTY"; break;
	case WBEM_E_CALL_CANCELLED: sRet = "WBEM_E_CALL_CANCELLED"; break;
	case WBEM_E_SHUTTING_DOWN: sRet = "WBEM_E_SHUTTING_DOWN"; break;
	case WBEM_E_PROPAGATED_METHOD: sRet = "WBEM_E_PROPAGATED_METHOD"; break;
	case WBEM_E_UNSUPPORTED_PARAMETER: sRet = "WBEM_E_UNSUPPORTED_PARAMETER"; break;
	case WBEM_E_MISSING_PARAMETER_ID: sRet = "WBEM_E_MISSING_PARAMETER_ID"; break;
	case WBEM_E_INVALID_PARAMETER_ID: sRet = "WBEM_E_INVALID_PARAMETER_ID"; break;
	case WBEM_E_NONCONSECUTIVE_PARAMETER_IDS: sRet = "WBEM_E_NONCONSECUTIVE_PARAMETER_IDS"; break;
	case WBEM_E_PARAMETER_ID_ON_RETVAL: sRet = "WBEM_E_PARAMETER_ID_ON_RETVAL"; break;
	case WBEM_E_INVALID_OBJECT_PATH: sRet = "WBEM_E_INVALID_OBJECT_PATH"; break;
	case WBEM_E_OUT_OF_DISK_SPACE: sRet = "WBEM_E_OUT_OF_DISK_SPACE"; break;
		
		
	default:
		{
			LPVOID  lpMsgBuf;      
			
			::FormatMessage
				( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,                       
				NULL,
				hr,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,                       0,
				NULL 
				);      
			
			TCHAR szTemp[100];
			wsprintf(szTemp, _T("0x%08X : "), hr);
			sRet += szTemp;
			sRet += (LPTSTR)lpMsgBuf;
			
			// Free the buffer.      
			::LocalFree( lpMsgBuf );
		}
	}
	
	return sRet;
}




//\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///
//                                                                         //
//   CWbemServices                                                         //
//                                                                         //
//\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///

CWbemServices::CWbemServices(IWbemContext * _pContext)
{
	InitializeCriticalSection(&m_cs);
	m_pCtx              = _pContext;
	m_pServicesStream   = NULL;
}



CWbemServices::CWbemServices(const CWbemServices& _p)
{
	m_pServicesStream   = NULL;
	InitializeCriticalSection(&m_cs);
	
	IWbemServicesPtr pServices;
	
	if(const_cast<CWbemServices&>(_p).GetInterfacePtr(pServices))
	{
		CommonInit(pServices);
	}
	
	m_pCtx                  = _p.m_pCtx;
}



CWbemServices::CWbemServices(const IWbemServicesPtr& _in)
{
	m_pServicesStream   = NULL;
	InitializeCriticalSection(&m_cs);
	CommonInit(const_cast<IWbemServicesPtr&>(_in));
}



CWbemServices::CWbemServices(IWbemServices *_in,IWbemContext * _pContext)
{
	InitializeCriticalSection(&m_cs);
	m_pCtx = _pContext;
	m_pServicesStream   = NULL;
	
	IWbemServicesPtr pServices = _in;
	CommonInit(pServices);
}



CWbemServices::CWbemServices(const IUnknownPtr& _in)
{
	IWbemServicesPtr pServices = _in;
	
	InitializeCriticalSection(&m_cs);
	
	CommonInit(pServices);
}


CWbemServices::CWbemServices(IUnknown * _in)
{
	IWbemServicesPtr pServices = _in;
	
	m_pServicesStream   = NULL;
	
	InitializeCriticalSection(&m_cs);
	
	CommonInit(pServices);
}


CWbemServices::~CWbemServices()
{
	//    HRESULT hr;
	EnterCriticalSection(&m_cs);
	
	if(m_pServicesStream)
	{
		//IWbemServicesPtr pServices;
		//hr = CoGetInterfaceAndReleaseStream(m_pServicesStream,IID_IWbemServices,(void**)&pServices);
		m_pServicesStream->Release();
		m_pServicesStream = NULL;
	}
	
	LeaveCriticalSection(&m_cs);
	
	DeleteCriticalSection(&m_cs);
}


CWbemServices&  CWbemServices::operator=(IWbemServices *_p)
{
	EnterCriticalSection(&m_cs);
	m_pCtx = NULL;
	
	IWbemServicesPtr pServices = _p;
	
	CommonInit(pServices);
	
	LeaveCriticalSection(&m_cs);
	
   return *this;
}


CWbemServices& CWbemServices::operator=(IUnknown * _p)
{
	EnterCriticalSection(&m_cs);
	
	IWbemServicesPtr pServices = _p;
	
	m_pCtx = NULL;
	
	CommonInit(pServices);
	
	LeaveCriticalSection(&m_cs);
	
   return *this;
}


CWbemServices& CWbemServices::operator=(IUnknownPtr& _p)
{
	EnterCriticalSection(&m_cs);
	
	IWbemServicesPtr pServices = _p;
	
	m_pCtx = NULL;
	
	CommonInit(pServices);
	
	LeaveCriticalSection(&m_cs);
	
   return *this;
}


CWbemServices& CWbemServices::operator=(const CWbemServices& _p)
{
	EnterCriticalSection(&m_cs);
	
	IWbemServicesPtr pServices;
	
	if(const_cast<CWbemServices&>(_p).GetInterfacePtr(pServices))
	{
		CommonInit(pServices);
	}
	
	m_pCtx              = _p.m_pCtx;
	
	LeaveCriticalSection(&m_cs);
	
   return *this;
}



bool CWbemServices::GetInterfacePtr(IWbemServicesPtr& pServices,bool bThrowException)
{
	bool bRet = false;
	
	EnterCriticalSection(&m_cs);
	
	if(m_pServicesStream)
	{
		HRESULT hr;
		
		if(m_pUnkCache)
		{
			pServices = m_pUnkCache;    
		}
		else
		{
			hr = CoGetInterfaceAndReleaseStream(m_pServicesStream,IID_IWbemServices,(void**)&pServices);
         m_pServicesStream = NULL;
			
			if( FAILED(hr) )
			{
				if(bThrowException)
				{
					LeaveCriticalSection(&m_cs);
					throw CWbemException(hr,"Error Retreiving Marshalled Services Pointer!");
				}
				else
				{
					bRet = false;
				}
			}
			else
			{
				bRet = true;
			}
			
			m_pUnkCache = pServices;
			
			hr = CoMarshalInterThreadInterfaceInStream(IID_IWbemServices,pServices,&m_pServicesStream);
			
			m_pUnkCache = NULL;
		}
		
		if( FAILED(hr) && bRet )
		{
			if(bThrowException)
			{
				LeaveCriticalSection(&m_cs);
				throw CWbemException(hr,"Error Marshalling Services Pointer!");
			}
			else
			{
				bRet = false;
			}
		}
	}
	else
	{
		if(bThrowException)
		{
			LeaveCriticalSection(&m_cs);
			throw CWbemException("Invalid Services Pointer!");
		}
	}
	
	LeaveCriticalSection(&m_cs);
	
	if(!bRet && bThrowException)
	{
		throw CWbemException("NULL Services Pointer!");
	}
	
	return bRet;
}



void CWbemServices::CommonInit(IWbemServicesPtr& pServ)
{
   EnterCriticalSection(&m_cs);
	
   if (m_pServicesStream) 
   {
      m_pServicesStream->Release();
		
      m_pServicesStream = NULL;
   }
	
	if(pServ)
	{
		
		HRESULT hr;
		hr = CoMarshalInterThreadInterfaceInStream(IID_IWbemServices,pServ,&m_pServicesStream);
		
		if(FAILED(hr))
		{
         LeaveCriticalSection(&m_cs);
			throw CWbemException(hr,"Unable to marshal Services Pointer.");
		}
	}
	else
	{
      LeaveCriticalSection(&m_cs);
		throw CWbemException("Invalid (NULL) Services Pointer!");
	}
	
   LeaveCriticalSection(&m_cs);
}


void CWbemServices::ConnectServer(_bstr_t sNetworkResource, IWbemServices **_WbemServicesCache)
{
	IWbemLocatorPtr pLocator;
	HRESULT         hr;
	
   *_WbemServicesCache = NULL;
	
	// Get a pointer locator and use it to get a pointer to WbemServices!
	hr = pLocator.CreateInstance(CLSID_WbemLocator);
	
	if(SUCCEEDED(hr))
	{    
		IWbemServicesPtr pServices;
		
		hr = pLocator->ConnectServer
			(
			sNetworkResource,               // Network
			NULL,                           // User
			NULL,                           // Password
			NULL,                           // Locale
			0,                              // Security Flags
			NULL,                           // Authority
			NULL,                           // Context
			&pServices                      // Namespace
			);
		
		if(SUCCEEDED(hr))
		{
			CommonInit(pServices);
         *_WbemServicesCache = pServices.Detach();
		}
		else
		{
			throw CWbemException(hr,"Connect Server failed.");
		}
	}
	else
	{
		throw CWbemException("Unable to create instance of IWbemLocator.");
	}
}


void CWbemServices::ConnectServer
(
 _bstr_t sNetworkResource,
 _bstr_t sUser,
 _bstr_t sPassword,
 IWbemServices **_WbemServicesCache,
 long    lSecurityFlags
 )
{
	IWbemLocatorPtr pLocator;
	HRESULT         hr;
	
   *_WbemServicesCache = NULL;
	
	// Get a pointer locator and use it to get a pointer to WbemServices!
	hr = pLocator.CreateInstance(CLSID_WbemLocator);
	
	if(SUCCEEDED(hr))
	{    
		IWbemServicesPtr pServices;
		
		hr = pLocator->ConnectServer
			(
			sNetworkResource,               // Network
			sUser,                          // User
			sPassword,                      // Password
			NULL,                           // Locale
			lSecurityFlags,                 // Security Flags
			NULL,                           // Authority
			NULL,                           // Context
			&pServices                      // Namespace
			);
		
		if(SUCCEEDED(hr))
		{
			CommonInit(pServices);
         *_WbemServicesCache = pServices.Detach();
		}
		else
		{
			throw CWbemException(hr,"Connect Server failed.");
		}
	}
	else
	{
		throw CWbemException("Unable to create instance of IWbemLocator.");
	}
}



CWbemClassObject CWbemServices::GetObject
(
 _bstr_t                 _sName,
 IWbemCallResultPtr&     _cr,
 bool                    _bThrowOnError
 )
{
	CWbemClassObject coRet;
	
	IWbemServicesPtr pServices;
	GetInterfacePtr(pServices);
	HRESULT hr = pServices->GetObject(_sName,0,m_pCtx,&coRet,&_cr);
	
	if(_bThrowOnError && FAILED(hr))
	{
		_bstr_t sMessage = "Error retrieving object";
		sMessage += _sName;
		
		throw CWbemException(hr,sMessage);
	}
	
	return coRet;
}



HRESULT CWbemServices::SetContextValue(_bstr_t sName,_variant_t value)
{
	HRESULT hr = S_OK;
	
	if(!bool(m_pCtx))
	{
		hr = m_pCtx.CreateInstance(CLSID_WbemContext);
	}
	
	if( SUCCEEDED(hr) )
	{
		hr = m_pCtx->SetValue(sName,0,&value);
	}
	
	return hr;
}



HRESULT CWbemServices::SetContext(IWbemContext * pWbemContext)
{
	HRESULT hr = S_OK;
	
	m_pCtx = pWbemContext;
	
	return hr;
}


HRESULT CWbemServices::GetContextValue(_bstr_t sName,_variant_t& value)
{
	HRESULT hr = S_OK;
	
	if(m_pCtx)
	{
		hr = m_pCtx->GetValue(sName,0,&value);
	}
	else
	{
		hr = E_FAIL;
	}
	
	return hr;
}


HRESULT CWbemServices::DeleteContextValue(_bstr_t sName)
{
	HRESULT hr = S_OK;
	
	if(m_pCtx)
	{
		hr = m_pCtx->DeleteValue(sName,0);
	}
	else
	{
		hr = E_FAIL;
	}
	
	return hr;
}



HRESULT CWbemServices::DeleteAllContextValues()
{
	HRESULT hr = S_OK;
	
	if(m_pCtx)
	{
		hr = m_pCtx->DeleteAll();
	}
	else
	{
		hr = E_FAIL;
	}
	
	return hr;
}


HRESULT CWbemServices::GetContext(IWbemContext ** ppWbemContext)
{
	HRESULT hr = E_FAIL;
	
	if(m_pCtx)
	{
		m_pCtx->AddRef();
		*ppWbemContext = m_pCtx;
		hr = S_OK;
	}
	
	return hr;
}




//\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///
//                                                                         //
//   CWbemClassObject                                                      //
//                                                                         //
//\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///\\///

// global object count of active WBEM object encapsulated by this class
// helpful for debugging
DWORD CWbemClassObject::s_dwObjectCount = 0;


CWbemClassObject::CWbemClassObject(const CWbemClassObject&  _in):
m_pWbemObject(_in.m_pWbemObject) 
{
	s_dwObjectCount++;
}


CWbemClassObject::CWbemClassObject(IWbemClassObject * const _in):
m_pWbemObject(_in) 
{
	s_dwObjectCount++;
}



CWbemClassObject::CWbemClassObject(IWbemClassObjectPtr& _in) :
m_pWbemObject(_in)
{
	s_dwObjectCount++;
}



CWbemClassObject::CWbemClassObject(IUnknown * _in):
m_pWbemObject(_in) 
{
	s_dwObjectCount++;
}

CWbemClassObject::CWbemClassObject(IUnknownPtr& _in):
m_pWbemObject(_in) 
{
	s_dwObjectCount++;
}



CWbemClassObject::CWbemClassObject():
m_pWbemObject() 
{
	s_dwObjectCount++;
}



CWbemClassObject::~CWbemClassObject()
{
	s_dwObjectCount--;
}




unsigned long CWbemClassObject::GetObjectSize()
{
	unsigned long ulRet = 0;
	
	IMarshalPtr pTest = (IUnknown*)m_pWbemObject;
	
	if(pTest)
	{
		pTest->GetMarshalSizeMax(IID_IWbemClassObject,(IUnknown*)m_pWbemObject,MSHCTX_LOCAL,NULL,MSHLFLAGS_NORMAL,&ulRet);
	}
	
	return ulRet;
}



_bstr_t CWbemClassObject::GetString(const _bstr_t& _Name)
{
	HRESULT hr;
	_variant_t v1;
	hr = Get(_Name, v1);
   if(v1.vt == VT_NULL)
   {
      return "";
   }
   return v1;
}



_int64 CWbemClassObject::GetI64(const _bstr_t& _Name)
{
	HRESULT hr;
	_variant_t v1;
   _bstr_t str;
	
	hr = Get(_Name, v1);
   if(v1.vt == VT_NULL)
   {
      return 0;
   }
   str = (_bstr_t) v1;
   return _atoi64(str);
}



long CWbemClassObject::GetLong(const _bstr_t& _Name)
{
	HRESULT hr;
	_variant_t v1;
	hr = Get(_Name,v1);
   if(v1.vt == VT_NULL)
   {
      return 0;
   }
	return v1;
}


bool CWbemClassObject::GetBool(const _bstr_t& _Name)
{
   HRESULT hr;
   _variant_t v1;
   hr = Get (_Name, v1);
   if(v1.vt == VT_NULL)
   {
      return false;
   }
   return v1;
}


_bstr_t CWbemClassObject::GetCIMTYPE(const _bstr_t& _Name)
{
	IWbemQualifierSetPtr pQualifierSet;
	_bstr_t              sRet;
	
	if(m_pWbemObject->GetPropertyQualifierSet(_Name, &pQualifierSet) == S_OK)
	{
		_variant_t vt;
		
		if(pQualifierSet->Get(_bstr_t("CIMTYPE"), 0, &vt, NULL) == S_OK)
		{
			sRet = vt;
		}
	}
	
	return sRet;
}



CWbemClassObject CWbemClassObject::GetEmbeddedObject(const _bstr_t& _Name)
{
	CWbemClassObject    coRet;
	HRESULT             hr;
	
	_variant_t v1;
	
	hr = Get(_Name,v1);
	
	if(hr == S_OK)
	{
		if(v1.vt == VT_UNKNOWN)
		{              
			coRet = (IWbemClassObject*) v1.punkVal;
		}
	}
	
	return coRet;
}









