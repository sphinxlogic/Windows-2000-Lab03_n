// RootDSE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	IADs    *pRoot=NULL;
    VARIANT varDSRoot;

    HRESULT hr;

	hr = CoInitialize(NULL);
	
	//  Get the name of the schema container for this domain.  
	//  Read the Root DSE from the default DS,  which will be the DS for 
	//  the local domain.  This will get us the name of the schema container,
	//  which is stored in the "schemaNamingContext" operational attribute.


	/////////////////////////////////////////////////////////////////////////////
	// NOTE: If your client is NT 4.0 or Win 9.x without the DS Client, you 
	// must put the server name in front of the LDAP://.  For example
	// ADsGetObject(L"LDAP://myDC/RootDSE")
	// If your client is Windows 2000, you don't need to specify the servername.
	// The locator service in Windows 2000 will automatically locate the best DC for you
	/////////////////////////////////////////////////////////////////////////////////////

    hr = ADsGetObject(L"LDAP://RootDSE",
                      IID_IADs,
                      (void**)&pRoot);

	// Get the Directory Object on the root DSE, to get to the server configuration
	hr = pRoot->Get(L"defaultNamingContext",&varDSRoot);
	printf("\nDS Root :%S\n",varDSRoot.bstrVal);
    
	VariantClear(&varDSRoot);

    if (pRoot)
	{
        pRoot->Release();
	}

    CoUninitialize();


	return 0;
}
