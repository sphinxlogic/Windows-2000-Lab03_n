#include <wchar.h>
#include <activeds.h>

HRESULT CheckDomainModeOfObject(IDirectoryObject *pDirObject, BOOL *bIsMixed);
WCHAR * GetDirectoryObjectAttrib(IDirectoryObject *pDirObject,LPWSTR pAttrName);

HRESULT GetDomainMode(IADs *pDomain, BOOL *bIsMixed);


int main(int argc, char* argv[])
{

wprintf(L"This program checks whether the current domain is in mixed or native mode.\n");

//Intialize COM
CoInitialize(NULL);
HRESULT hr = S_OK;
//Get rootDSE and the domain container's DN.
IADs *pObject = NULL;
LPOLESTR szPath = new OLECHAR[MAX_PATH];
VARIANT var;
BOOL bIsMixed;

hr = ADsOpenObject(L"LDAP://rootDSE",
				 NULL,
				 NULL,
				 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
				 IID_IADs,
				 (void**)&pObject);
if (FAILED(hr))
{
   wprintf(L"Not Found. Could not bind to the domain.\n");
   if (pObject)
     pObject->Release();
   return TRUE;
}

hr = pObject->Get(L"defaultNamingContext",&var);
if (SUCCEEDED(hr))
{
	wcscpy(szPath,L"LDAP://"); //For NT 4.0 and Win 9.x, you must add the server name, e.g LDAP://myServer
	wcscat(szPath,var.bstrVal);
	VariantClear(&var);
	if (pObject)
	{
	   pObject->Release();
	   pObject = NULL;
	}
	//Bind to the root of the current domain.
	hr = ADsOpenObject(szPath,
					 NULL,
					 NULL,
					 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
					 IID_IADs,
					 (void**)&pObject);
	if (SUCCEEDED(hr))
	{
		hr = GetDomainMode(pObject, &bIsMixed);
		if (SUCCEEDED(hr))
		{
		    hr = pObject->Get(L"name",&var);
			if (bIsMixed)
			  wprintf(L"Current domain %s is in mixed mode\n", var.bstrVal);
			else
			  wprintf(L"Current domain %s is in native mode\n", var.bstrVal);
		}
		else
			wprintf(L"GetDomainMode failed with hr: %x",hr);
	}
	else
		wprintf(L"Bind to domain failed with hr: %x",hr);
}
VariantClear(&var);
if (pObject)
  pObject->Release();

return TRUE;
}
		







HRESULT GetDomainMode(IADs *pDomain, BOOL *bIsMixed)
{
HRESULT hr = E_FAIL;
VARIANT var;
if (pDomain)
{
	VariantClear(&var);
	//Get the ntMixedDomain attribute
	LPOLESTR szAttribute = L"ntMixedDomain";
	hr = pDomain->Get(szAttribute,&var);
	if (SUCCEEDED(hr))
	{
		//Type should be VT_I4.
		if (var.vt==VT_I4)
		{
			//Zero means native mode.
			if (var.lVal == 0)
				*bIsMixed = FALSE;
			//One means mixed mode.
			else if (var.lVal == 1)
				*bIsMixed = TRUE;
			else
				hr=E_FAIL;
		}
	}
	VariantClear(&var);
}
return hr;

}	

//Given an object, this function finds out if the domain containing the object is in mixed mode.

HRESULT CheckDomainModeOfObject(IDirectoryObject *pDirObject, BOOL *bIsMixed)
{
	HRESULT hr = E_FAIL;
	IADs *pDomain = NULL;
	VARIANT VarTest;
	WCHAR *pFound = NULL;
	int iLen;
	WCHAR *pDomainPath = new WCHAR[MAX_PATH*2];

	//Check whether the domain containing the container is in mixed mode
    WCHAR *pVal = NULL;
    pVal = GetDirectoryObjectAttrib(pDirObject,L"canonicalName");

	if (pVal)
	{
		//Parse the canonical name for the DNS name of the domain
		pFound = wcschr(pVal,'/');
		//Bind to the domain using the dns name, get defaultnamingcontext, 
		if (pFound)
		{
			iLen = pFound - pVal;
			wcscpy(pDomainPath, L"LDAP://");
			wcsncat(pDomainPath, pVal,iLen);
			wcscat(pDomainPath, L"/rootDSE");
			wprintf(L"DNS Name: %s\n", pDomainPath);
			VariantClear(&VarTest);
			hr = ADsOpenObject(pDomainPath,
							NULL,
							NULL,
							ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
							IID_IADs,
							(void**)&pDomain);
			if (SUCCEEDED(hr))
			{
				hr = pDomain->Get(L"defaultNamingContext",&VarTest);
				if (SUCCEEDED(hr))
				{
					wcscpy(pDomainPath, L"LDAP://");
		 			wcsncat(pDomainPath, pVal,iLen);
					wcscat(pDomainPath, L"/");
					wcscat(pDomainPath, VarTest.bstrVal);
					VariantClear(&VarTest);
					if (pDomain)
						pDomain->Release();
					if (SUCCEEDED(hr))
					{
						hr = ADsOpenObject(pDomainPath,
										NULL,
										NULL,
										ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
										IID_IADs,
										(void**)&pDomain);
						if (SUCCEEDED(hr))
						{
							hr = GetDomainMode(pDomain, bIsMixed);
						}
					}
				}
			}
			if (pDomain)
				pDomain->Release();
		}
	}
	return hr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*  
    GetDirectoryObjectAttrib()      -   Returns the value of the attribute named in pAttrName
                                        from the IDirectoryObject passed
    Parameters
    
        IDirectoryObject *pDirObject    - Object from which to retrieve an attribute value
        LPWSTR pAttrName                - Name of attribute to retrieve
*/
WCHAR * GetDirectoryObjectAttrib(IDirectoryObject *pDirObject,LPWSTR pAttrName)
{
    HRESULT   hr;
    ADS_ATTR_INFO   *pAttrInfo=NULL;
    DWORD   dwReturn;
    static WCHAR pwReturn[1024];

    pwReturn[0] = 0l;

    hr = pDirObject->GetObjectAttributes( &pAttrName, 
                                            1, 
                                            &pAttrInfo, 
                                            &dwReturn ); 
    if ( SUCCEEDED(hr) )
    {
        for(DWORD idx=0; idx < dwReturn;idx++, pAttrInfo++ )   
        {
            if ( _wcsicmp(pAttrInfo->pszAttrName,pAttrName) == 0 )       
            {
                wcscpy(pwReturn,pAttrInfo->pADsValues->CaseIgnoreString);
                break;
            }
        }
        FreeADsMem( pAttrInfo );
    }    
    return pwReturn;
}
