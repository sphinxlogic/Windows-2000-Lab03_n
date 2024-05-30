#include "stdafx.h"
#include "..\ComSpyFace\ComSpyCtl.h"
#include <comsvcs.h>
#include "SysLCESub.h"
#include "..\ComSpyFace\ComSpyAudit.h"

#include "ComSpy.h"
#include "securitysub.h"



//-------------------------------------------------------------
//-Copy from methodsub
HRESULT CMethodSub::GetClsidOfTypeLib2 (IID * piid, UUID * puuidClsid)
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
HRESULT CMethodSub::GetMethodName (REFIID riid, int iMeth, _TCHAR** ppszMethodName)
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