// Create.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "activeds.h"


int main(int argc, char* argv[])
{
	HRESULT hr;
	IADsContainer *pCont = NULL;
	IDispatch *pDisp=NULL;

	CoInitialize(NULL);

	///////////////////////////////////////////////////
	// Create a user using IADsContainer::Create
	////////////////////////////////////////////////////
	hr = ADsGetObject( L"WinNT://INDEPENDENCE", IID_IADsContainer, (void**) &pCont );
	if (!SUCCEEDED(hr) )
	{
		return 0;
	}

	IADs *pADs=NULL;
	hr = pCont->Create(L"user", L"AliceW", &pDisp );
	pCont->Release();

	if( !SUCCEEDED(hr) )
	{
		return 0;
	}

	hr = pDisp->QueryInterface( IID_IADs, (void**) &pADs );
	pDisp->Release();

	if ( !SUCCEEDED(hr) )
	{
		return 0;
	}

	pADs->SetInfo(); // Commit

	pADs->Release(); // Release


	
	///////////////////////////////////////////////////////////
	// Use IDirectoryObject to create an object
	////////////////////////////////////////////////////////////
	IDirectoryObject *pDirObject=NULL;
	ADSVALUE   sAMValue;
	ADSVALUE   uPNValue;
	ADSVALUE   classValue;

 
	ADS_ATTR_INFO  attrInfo[] = 
	{  
		{ L"objectClass",   ADS_ATTR_UPDATE, 
			                ADSTYPE_CASE_IGNORE_STRING, &classValue, 1 },
		{L"sAMAccountName", ADS_ATTR_UPDATE, 
                            ADSTYPE_CASE_IGNORE_STRING, &sAMValue, 1},
		{L"userPrincipalName", ADS_ATTR_UPDATE, 
                               ADSTYPE_CASE_IGNORE_STRING, &uPNValue, 1},
	};
	DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
 
	classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	classValue.CaseIgnoreString = L"user";
 
	sAMValue.dwType=ADSTYPE_CASE_IGNORE_STRING;
	sAMValue.CaseIgnoreString = L"mikes";
 
	uPNValue.dwType=ADSTYPE_CASE_IGNORE_STRING;
	uPNValue.CaseIgnoreString = L"mikes@arcadiabay.com";
 
	// Create this user in an organizational unit
	hr = ADsGetObject(L"LDAP://OU=DSys,DC=windows2000,DC=nttest,DC=microsoft,DC=com",
				      IID_IDirectoryObject, (void**) &pDirObject );
 
	if ( SUCCEEDED(hr) )
	{
		hr = pDirObject->CreateDSObject( L"CN=Mike Smith",  attrInfo, 
										 dwAttrs, &pDisp );
		if ( SUCCEEDED(hr) )
		{
			pDisp->Release();
		}
	}
	pDirObject->Release();



	CoUninitialize();
	return 0;
}
