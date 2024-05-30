// userprop.cpp : Defines the entry point for the console application.
//

//For the pow function to calculate powers of 2
#include <math.h>
#include <wchar.h>
#include <objbase.h>
#include <activeds.h>

//Make sure you define UNICODE
//Need to define version 5 for Windows 2000
#define _WIN32_WINNT 0x0500
#include <sddl.h>



//Function to use the get_* methods of IADsUser.
HRESULT GetUserPropertyMethods(IADsUser *pUser);

HRESULT FindUserByName(IDirectorySearch *pSearchBase, //Container to search
					   LPOLESTR szFindUser, //Name of user to find.
					   IADs **ppUser); //Return a pointer to the user


void wmain( int argc, wchar_t *argv[ ])
{

//Handle the command line arguments.
LPOLESTR pszBuffer = new OLECHAR[MAX_PATH*2];
if (argv[1] == NULL)
{
	wprintf(L"This program finds a user in the current Window 2000 domain\n");
	wprintf(L"and displays its IADsUser properties.\n");
	wprintf(L"Enter Common Name of the user to find:");
	_getws(pszBuffer);
}
else
   wcscpy(pszBuffer, argv[1]);
//if empty string, exit.
if (0==wcscmp(L"", pszBuffer))
   return;
	
wprintf(L"\nFinding user: %s...\n",pszBuffer);
	
//Intialize COM
CoInitialize(NULL);
HRESULT hr = S_OK;
//Get rootDSE and the domain container's DN.
IADs *pObject = NULL;
IDirectorySearch *pDS = NULL;
LPOLESTR szPath = new OLECHAR[MAX_PATH];
VARIANT var;
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
   return;
}

hr = pObject->Get(L"defaultNamingContext",&var);
if (SUCCEEDED(hr))
{
	wcscpy(szPath,L"LDAP://");
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
					 IID_IDirectorySearch,
					 (void**)&pDS);
	if (SUCCEEDED(hr))
	{
		hr =  FindUserByName(pDS, //Container to search
						   pszBuffer, //Name of user to find.
						   &pObject); //Return a pointer to the user
		if (SUCCEEDED(hr))
		{
			IADsUser *pUser = NULL;
			hr = pObject->QueryInterface( IID_IADsUser, (void**) &pUser );
			if (SUCCEEDED(hr))
			{
			   wprintf (L"----------------------------------------------\n");
			   wprintf (L"--------Call GetUserPropertyMethods-----------\n");
			   hr = GetUserPropertyMethods(pUser);
			   wprintf (L"GetUserPropertyMethods HR: %x\n", hr);
			}
			if (pUser)
				pUser->Release();
		}
		else
		{
            wprintf(L"User \"%s\" not Found.\n",pszBuffer);
			wprintf (L"FindUserByName failed with the following HR: %x\n", hr);
		}
		if (pObject)
			pObject->Release();
	}

	if (pDS)
	   pDS->Release();
}

//Uninitalize COM
CoUninitialize();

	return;
}

HRESULT FindUserByName(IDirectorySearch *pSearchBase, //Container to search
					   LPOLESTR szFindUser, //Name of user to find.
					   IADs **ppUser) //Return a pointer to the user
{
    HRESULT hrObj = E_FAIL;
    HRESULT hr = E_FAIL;
	if ((!pSearchBase)||(!szFindUser))
		return E_INVALIDARG;
	//Create search filter
	LPOLESTR pszSearchFilter = new OLECHAR[MAX_PATH];
	LPOLESTR szADsPath = new OLECHAR[MAX_PATH];
	wcscpy(pszSearchFilter, L"(&(objectCategory=person)(objectClass=user)(cn=");
	wcscat(pszSearchFilter, szFindUser);
	wcscat(pszSearchFilter,	L"))");
    //Search entire subtree from root.
	ADS_SEARCHPREF_INFO SearchPrefs;
	SearchPrefs.dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
	SearchPrefs.vValue.dwType = ADSTYPE_INTEGER;
	SearchPrefs.vValue.Integer = ADS_SCOPE_SUBTREE;
    DWORD dwNumPrefs = 1;
	// COL for iterations
    ADS_SEARCH_COLUMN col;
    // Handle used for searching
    ADS_SEARCH_HANDLE hSearch;
	// Set the search preference
    hr = pSearchBase->SetSearchPreference( &SearchPrefs, dwNumPrefs);
    if (FAILED(hr))
        return hr;
	// Set attributes to return
	CONST DWORD dwAttrNameSize = 1;
    LPOLESTR pszAttribute[dwAttrNameSize] = {L"ADsPath"};

    // Execute the search
    hr = pSearchBase->ExecuteSearch(pszSearchFilter,
		                          pszAttribute,
								  dwAttrNameSize,
								  &hSearch
								  );
	if (SUCCEEDED(hr))
	{    

    // Call IDirectorySearch::GetNextRow() to retrieve the next row 
    //of data
        while( pSearchBase->GetNextRow( hSearch) != S_ADS_NOMORE_ROWS )
		{
            // loop through the array of passed column names,
            // print the data for each column
            for (DWORD x = 0; x < dwAttrNameSize; x++)
            {
			    // Get the data for this column
                hr = pSearchBase->GetColumn( hSearch, pszAttribute[x], &col );
			    if ( SUCCEEDED(hr) )
			    {
				    // Print the data for the column and free the column
					// Note the attribute we asked for is type CaseIgnoreString.
                    wcscpy(szADsPath, col.pADsValues->CaseIgnoreString); 
					hr = ADsOpenObject(szADsPath,
									 NULL,
									 NULL,
									 ADS_SECURE_AUTHENTICATION, //Use Secure Authentication
									 IID_IADs,
									 (void**)ppUser);
					if (SUCCEEDED(hr))
					{
                       wprintf(L"Found User.\n",szFindUser); 
                       wprintf(L"%s: %s\r\n",pszAttribute[x],col.pADsValues->CaseIgnoreString); 
					   hrObj = S_OK;
					}
				    pSearchBase->FreeColumn( &col );
			    }
			    else
				    hr = E_FAIL;
            }
		}
		// Close the search handle to clean up
        pSearchBase->CloseSearchHandle(hSearch);
	}
	if (FAILED(hrObj))
		hr = hrObj;
    return hr;
}

HRESULT GetUserPropertyMethods(IADsUser *pUser)
{
VARIANT_BOOL bBool;
DATE date;
BSTR bstr;
LONG lProp;
VARIANT var;
HRESULT hr;

  VARIANT *pVar;
  long lLBound, lUBound;
  long cElements;




hr = pUser->get_AccountDisabled(&bBool); 
if (SUCCEEDED(hr))
{
    if (bBool)
      wprintf(L"AccountDisabled: TRUE\n");
    else
      wprintf(L"AccountDisabled: FALSE\n");
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"AccountDisabled property not found.\n");
}

hr = pUser->get_AccountExpirationDate (&date); 
if (SUCCEEDED(hr))
{
//Pack in variant
    var.vt = VT_DATE;
    var.date = date;
    VariantChangeType(&var,&var,VARIANT_NOVALUEPROP,VT_BSTR);
    wprintf(L"AccountExpirationDate: %s\n",var.bstrVal);
    VariantClear(&var);
}
hr = pUser->get_BadLoginAddress (&bstr);
if (SUCCEEDED(hr))
{
      wprintf(L"BadLoginAddress: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"BadLoginAddress property not found.\n");
	else if (hr==E_ADS_PROPERTY_NOT_SUPPORTED)
		//BadLoginAddress is not supported for Windows 2000
		//So don't use this method.
		wprintf(L"BadLoginAddress property is not supported for Windows 2000.\n");
    else
        wprintf(L"BadLoginAddress failed with HR: %x\n", hr);
}
hr = pUser->get_BadLoginCount (&lProp);
if (SUCCEEDED(hr))
{
      wprintf(L"BadLoginCount: %d\n", lProp);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"BadLoginCount property not found.\n");
    else
        wprintf(L"BadLoginCount failed with HR: %x\n", hr);
}
hr = pUser->get_Department (&bstr);
if (SUCCEEDED(hr))
{
      wprintf(L"Department: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Department property not found.\n");
    else
        wprintf(L"Department failed with HR: %x\n", hr);
}

hr = pUser->get_Description(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"Description: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Description property not found.\n");
    else
        wprintf(L"Description failed with HR: %x\n", hr);
}
hr = pUser->get_Division(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"Division: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Division property not found.\n");
    else
        wprintf(L"Division failed with HR: %x\n", hr);
}

hr = pUser->get_EmailAddress(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"EmailAddress: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"EmailAddress property not found.\n");
    else
        wprintf(L"EmailAddress failed with HR: %x\n", hr);
}

hr = pUser->get_EmployeeID (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"EmployeeID: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"EmployeeID property not found.\n");
    else
        wprintf(L"EmployeeID failed with HR: %x\n", hr);
}
hr = pUser->get_FaxNumber (&var); 
if (SUCCEEDED(hr))
{
	//Fax is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"FaxNumber: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"FaxNumber property not found.\n");
    else
        wprintf(L"FaxNumber failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_FirstName (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"FirstName: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"FirstName property not found.\n");
    else
        wprintf(L"FirstName failed with HR: %x\n", hr);
}
hr = pUser->get_FullName (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"FullName: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"FullName property not found.\n");
    else
        wprintf(L"FullName failed with HR: %x\n", hr);
}
hr = pUser->get_GraceLoginsAllowed (&lProp); 
if (SUCCEEDED(hr))
{
      wprintf(L"GraceLoginsAllowed: %d\n", lProp);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"GraceLoginsAllowed property not found.\n");
	else if (hr==E_ADS_PROPERTY_NOT_SUPPORTED)
		//GraceLoginsAllowed is not supported for Windows 2000
		//So don't use this method.
		wprintf(L"GraceLoginsAllowed property is not supported for Windows 2000.\n");
    else
        wprintf(L"GraceLoginsAllowed failed with HR: %x\n", hr);
}
hr = pUser->get_GraceLoginsRemaining (&lProp); 
if (SUCCEEDED(hr))
{
      wprintf(L"GraceLoginsRemaining: %d\n", lProp);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"GraceLoginsRemaining property not found.\n");
	else if (hr==E_ADS_PROPERTY_NOT_SUPPORTED)
		//GraceLoginsRemaining is not supported for Windows 2000
		//So don't use this method.
		wprintf(L"GraceLoginsRemaining property is not supported for Windows 2000.\n");
    else
        wprintf(L"GraceLoginsRemaining failed with HR: %x\n", hr);
}
hr = pUser->get_HomeDirectory(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"HomeDirectory: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"HomeDirectory property not found.\n");
    else
        wprintf(L"HomeDirectory failed with HR: %x\n", hr);
}
hr = pUser->get_HomePage(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"HomePage: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"HomePage property not found.\n");
    else
        wprintf(L"HomePage failed with HR: %x\n", hr);
}
hr = pUser->get_IsAccountLocked (&bBool); 
if (SUCCEEDED(hr))
{
    if (bBool)
      wprintf(L"IsAccountLocked: TRUE\n");
    else
      wprintf(L"IsAccountLocked: FALSE\n");
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"IsAccountLocked property not found.\n");
    else
        wprintf(L"IsAccountLocked failed with HR: %x\n", hr);
}

hr = pUser->get_Languages(&var); 
if (SUCCEEDED(hr))
{
      wprintf(L"Languages (%d):\n", var.vt);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Languages property not found.\n");
	else if (hr==E_ADS_PROPERTY_NOT_SUPPORTED)
		//Languages is not supported for Windows 2000
		//So don't use this method.
		wprintf(L"Languages property is not supported for Windows 2000.\n");
     else
        wprintf(L"Languages failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_LastFailedLogin (&date);
if (SUCCEEDED(hr))
{
//Pack in variant
    var.vt = VT_DATE;
    var.date = date;
    VariantChangeType(&var,&var,VARIANT_NOVALUEPROP,VT_BSTR);
    wprintf(L"LastFailedLogin: %s\n",var.bstrVal);
    VariantClear(&var);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LastFailedLogin property not found.\n");
    else
        wprintf(L"LastFailedLogin failed with HR: %x\n", hr);
}

hr = pUser->get_LastLogin (&date);
if (SUCCEEDED(hr))
{
//Pack in variant
    var.vt = VT_DATE;
    var.date = date;
    VariantChangeType(&var,&var,VARIANT_NOVALUEPROP,VT_BSTR);
    wprintf(L"LastLogin: %s\n",var.bstrVal);
    VariantClear(&var);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LastLogin property not found.\n");
    else
        wprintf(L"LastLogin failed with HR: %x\n", hr);
}

hr = pUser->get_LastLogoff (&date);
if (SUCCEEDED(hr))
{
//Pack in variant
    var.vt = VT_DATE;
    var.date = date;
    VariantChangeType(&var,&var,VARIANT_NOVALUEPROP,VT_BSTR);
    wprintf(L"LastLogoff: %s\n",var.bstrVal);
    VariantClear(&var);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LastLogoff property not found.\n");
    else
        wprintf(L"LastLogoff failed with HR: %x\n", hr);
}
hr = pUser->get_LastName (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"LastName: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LastName property not found.\n");
    else
        wprintf(L"LastName failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_LoginHours (&var); 
if (SUCCEEDED(hr))
{
  wprintf(L"LoginHours:\n");
  //For Octet String
  void HUGEP *pArray;
  ULONG dwSLBound;
  ULONG dwSUBound;
  if (var.vt==(VT_UI1|VT_ARRAY))
  {
		hr = SafeArrayGetLBound( V_ARRAY(&var),
								  1,
								  (long FAR *) &dwSLBound );
		hr = SafeArrayGetUBound( V_ARRAY(&var),
								  1,
								  (long FAR *) &dwSUBound );
		if (SUCCEEDED(hr))
		{
			hr = SafeArrayAccessData( V_ARRAY(&var),
									  &pArray );
		}

	   //21 byte array representing 8 hour blocks for each day.
	   //First byte is 16:00-23:59 on saturday.
	   //Second byte is 0:00-07:59 on sunday,
	   //Third byte is 8:00-15:59 on sunday,
	   //and so on up to 8:00-15:59 on saturday.
	   PBYTE pLogonHours = (PBYTE)pArray;
	   LPOLESTR szDay = new OLECHAR[MAX_PATH];
	   LPOLESTR szTime = new OLECHAR[MAX_PATH];
	   int base = 2;
	   //8 bits in a byte.
	   DWORD iBitMax = 8;
	   DWORD dVal, j;
	   int iTotalBytes = 21;
	   int iOffset;
   	   for (int k = 1; k <= iTotalBytes; k++)
	   {
			if (k!=iTotalBytes)
			  iOffset = k;
			else
			  iOffset = 0;
			//Get the block of time during the day.
			switch (k-1)
			{
			case 0:
			case 1:
			case 2:
			  wcscpy(szDay, L"Sunday");
			  break;
			case 3:
			case 4:
			case 5:
			  wcscpy(szDay, L"Monday");
			  break;
			case 6:
			case 7:
			case 8:
			  wcscpy(szDay, L"Tuesday");
			  break;
			case 9:
			case 10:
			case 11:
			  wcscpy(szDay, L"Wednesday");
			  break;
			case 12:
			case 13:
			case 14:
			  wcscpy(szDay, L"Thursday");
			  break;
			case 15:
			case 16:
			case 17:
			  wcscpy(szDay, L"Friday");
			  break;
			case 18:
			case 19:
			case 20:
			  wcscpy(szDay, L"Saturday");
			  break;
			}
		  
			switch (k-1)
			{
			case 0:
			case 3:
			case 6:
			case 9:
			case 12:
			case 15:
			case 18:
			   for (j = 0; j < iBitMax; j++)
			   {
				   dVal = pow(base, j);
				   if ((pLogonHours[iOffset] & dVal)==dVal)
				   {
					  switch (j)
					  {
						case 0:
						  wcscpy(szTime, L"00:00-59");
						  break;
						case 1:
						  wcscpy(szTime, L"01:00-59");
						  break;
						case 2:
						  wcscpy(szTime, L"02:00-59");
						  break;
						case 3:
						  wcscpy(szTime, L"03:00-59");
						  break;
						case 4:
						  wcscpy(szTime, L"04:00-59");
						  break;
						case 5:
						  wcscpy(szTime, L"05:00-59");
						  break;
						case 6:
						  wcscpy(szTime, L"06:00-59");
						  break;
						case 7:
						  wcscpy(szTime, L"07:00-59");
						  break;
					  }
			  		  wprintf(L"   %s %s\n",szDay,szTime);
				   }
			   }
			   break;
			case 1:
			case 4:
			case 7:
			case 10:
			case 13:
			case 16:
			case 19:
			   for (j = 0; j < iBitMax; j++)
			   {
				   dVal = pow(base, j);
				   if ((pLogonHours[iOffset] & dVal)==dVal)
				   {
					  switch (j)
					  {
						case 0:
						  wcscpy(szTime, L"08:00-59");
						  break;
						case 1:
						  wcscpy(szTime, L"09:00-59");
						  break;
						case 2:
						  wcscpy(szTime, L"10:00-59");
						  break;
						case 3:
						  wcscpy(szTime, L"11:00-59");
						  break;
						case 4:
						  wcscpy(szTime, L"12:00-59");
						  break;
						case 5:
						  wcscpy(szTime, L"13:00-59");
						  break;
						case 6:
						  wcscpy(szTime, L"14:00-59");
						  break;
						case 7:
						  wcscpy(szTime, L"15:00-59");
						  break;
					  }
			  		  wprintf(L"   %s %s\n",szDay,szTime);
				   }
			   }
			   break;
			case 2:
			case 5:
			case 8:
			case 11:
			case 14:
			case 17:
			case 20:
			   for (j = 0; j < iBitMax; j++)
			   {
				   dVal = pow(base, j);
				   if ((pLogonHours[iOffset] & dVal)==dVal)
				   {
					  switch (j)
					  {
						case 0:
						  wcscpy(szTime, L"16:00-59");
						  break;
						case 1:
						  wcscpy(szTime, L"17:00-59");
						  break;
						case 2:
						  wcscpy(szTime, L"18:00-59");
						  break;
						case 3:
						  wcscpy(szTime, L"19:00-59");
						  break;
						case 4:
						  wcscpy(szTime, L"20:00-59");
						  break;
						case 5:
						  wcscpy(szTime, L"21:00-59");
						  break;
						case 6:
						  wcscpy(szTime, L"22:00-59");
						  break;
						case 7:
						  wcscpy(szTime, L"23:00-59");
						  break;
					  }
			  		  wprintf(L"   %s %s\n",szDay,szTime);
				   }
			   }
			   break;
		  }
		}
								
	   //Decrement the access count for the array.
		SafeArrayUnaccessData( V_ARRAY(&var) );
        VariantClear(&var);
	}

}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LoginHours property not found.\n");
    else
        wprintf(L"LoginHours failed with HR: %x\n", hr);
}
VariantClear(&var);

hr = pUser->get_LoginScript(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"LoginScript: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LoginScript property not found.\n");
    else
        wprintf(L"LoginScript failed with HR: %x\n", hr);
}
hr = pUser->get_LoginWorkstations (&var); 
if (SUCCEEDED(hr))
{
  wprintf(L"LoginWorkstations: ");
  //Should be safe array containing variants of type BSTR.
  if (var.vt==(VT_VARIANT|VT_ARRAY))
  {
	   hr = SafeArrayAccessData((SAFEARRAY*)(var.pparray), (void HUGEP* FAR*)&pVar);
	   //One dimensional array. Get the bounds for the array.
 	   hr = SafeArrayGetLBound((SAFEARRAY*)(var.pparray), 1, &lLBound);
	   hr = SafeArrayGetUBound((SAFEARRAY*)(var.pparray), 1, &lUBound);
	   //Get the count of elements
	   cElements = lUBound-lLBound + 1;
	   //Get the elements of the array
	   if (SUCCEEDED(hr))
	   {
			for (int i = 0; i < cElements; i++ ) 
			{
			  switch (pVar[i].vt)
			  {
			  case VT_BSTR:
				  wprintf(L"%s ",pVar[i].bstrVal);
				  break;
			  default:
				  wprintf(L"Unhandled Variant type for property value array: %d\n",pVar[i].vt);
				  break;
			  }
			}
	   }
	   wprintf(L"\n");

	   //Decrement the access count for the array.
	   SafeArrayUnaccessData((SAFEARRAY*)(var.pparray));
  }
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"LoginWorkstations property not found.\n");
    else
        wprintf(L"LoginWorkstations failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_Manager (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"Manager: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Manager property not found.\n");
    else
        wprintf(L"Manager failed with HR: %x\n", hr);
}
hr = pUser->get_MaxLogins (&lProp); 
if (SUCCEEDED(hr))
{
      wprintf(L"MaxLogins: %d\n", lProp);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"MaxLogins property not found.\n");
	else if (hr==E_ADS_PROPERTY_NOT_SUPPORTED)
		//MaxLogins is not supported for Windows 2000
		//So don't use this method.
		wprintf(L"MaxLogins property is not supported for Windows 2000.\n");
     else
        wprintf(L"MaxLogins failed with HR: %x\n", hr);
}
hr = pUser->get_MaxStorage (&lProp); 
if (SUCCEEDED(hr))
{
      wprintf(L"MaxStorage: %d\n", lProp);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"MaxStorage property not found.\n");
    else
        wprintf(L"MaxStorage failed with HR: %x\n", hr);
}
hr = pUser->get_NamePrefix (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"NamePrefix: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"NamePrefix property not found.\n");
    else
        wprintf(L"NamePrefix failed with HR: %x\n", hr);
}
hr = pUser->get_NameSuffix (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"NameSuffix: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"NameSuffix property not found.\n");
    else
        wprintf(L"NameSuffix failed with HR: %x\n", hr);
}
hr = pUser->get_OfficeLocations (&var); 
if (SUCCEEDED(hr))
{
    //OfficeLocations is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"OfficeLocations: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"OfficeLocations property not found.\n");
    else
        wprintf(L"OfficeLocations failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_OtherName (&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"OtherName: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"OtherName property not found.\n");
    else
        wprintf(L"OtherName failed with HR: %x\n", hr);
}
hr = pUser->get_PasswordExpirationDate (&date); 
if (SUCCEEDED(hr))
{
//Pack in variant
    var.vt = VT_DATE;
    var.date = date;
    VariantChangeType(&var,&var,VARIANT_NOVALUEPROP,VT_BSTR);
    wprintf(L"PasswordExpirationDate: %s\n",var.bstrVal);
    VariantClear(&var);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"PasswordExpirationDate property not found.\n");
    else
        wprintf(L"PasswordExpirationDate failed with HR: %x\n", hr);
}
hr = pUser->get_PasswordLastChanged (&date);
if (SUCCEEDED(hr))
{
//Pack in variant
    var.vt = VT_DATE;
    var.date = date;
    VariantChangeType(&var,&var,VARIANT_NOVALUEPROP,VT_BSTR);
    wprintf(L"PasswordLastChanged: %s\n",var.bstrVal);
    VariantClear(&var);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"PasswordLastChanged property not found.\n");
    else
        wprintf(L"PasswordLastChanged failed with HR: %x\n", hr);
}
hr = pUser->get_PasswordMinimumLength (&lProp); 
if (SUCCEEDED(hr))
{
      wprintf(L"PasswordMinimumLength: %d\n", lProp);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"PasswordMinimumLength property not found.\n");
    else
        wprintf(L"PasswordMinimumLength failed with HR: %x\n", hr);
}
hr = pUser->get_PasswordRequired (&bBool); 
if (SUCCEEDED(hr))
{
    if (bBool)
      wprintf(L"PasswordRequired: TRUE\n");
    else
      wprintf(L"PasswordRequired: FALSE\n");
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"PasswordRequired property not found.\n");
    else
        wprintf(L"PasswordRequired failed with HR: %x\n", hr);
}
hr = pUser->get_Picture (&var); 
if (SUCCEEDED(hr))
{
      wprintf(L"Picture (%d):\n", var.vt);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Picture property not found.\n");
    else
        wprintf(L"Picture failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_PostalAddresses (&var); 
if (SUCCEEDED(hr))
{
    //PostalAddresses is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"PostalAddresses: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"PostalAddresses property not found.\n");
    else
        wprintf(L"PostalAddresses failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_PostalCodes (&var); 
if (SUCCEEDED(hr))
{
    //PostalCodes is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"PostalCodes: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"PostalCodes property not found.\n");
    else
        wprintf(L"PostalCodes failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_Profile(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"Profile: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Profile property not found.\n");
    else
        wprintf(L"Profile failed with HR: %x\n", hr);
}

hr = pUser->get_RequireUniquePassword(&bBool);
if (SUCCEEDED(hr))
{
    if (bBool)
      wprintf(L"RequireUniquePassword: TRUE\n");
    else
      wprintf(L"RequireUniquePassword: FALSE\n");
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"RequireUniquePassword property not found.\n");
    else
        wprintf(L"RequireUniquePassword failed with HR: %x\n", hr);
}
hr = pUser->get_SeeAlso (&var); 
if (SUCCEEDED(hr))
{
    //SeeAlso is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"SeeAlso: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"SeeAlso property not found.\n");
    else
        wprintf(L"SeeAlso failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_TelephoneHome (&var); 
if (SUCCEEDED(hr))
{
    //TelephoneHome is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"TelephoneHome: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"TelephoneHome property not found.\n");
    else
        wprintf(L"TelephoneHome failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_TelephoneMobile (&var); 
if (SUCCEEDED(hr))
{
    //TelephoneMobile is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"TelephoneMobile: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"TelephoneMobile property not found.\n");
    else
        wprintf(L"TelephoneMobile failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_TelephoneNumber (&var); 
if (SUCCEEDED(hr))
{
    //TelephoneNumber is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"TelephoneNumber: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"TelephoneNumber property not found.\n");
    else
        wprintf(L"TelephoneNumber failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_TelephonePager (&var); 
if (SUCCEEDED(hr))
{
    //TelephonePager is a bstrVal
	if (var.vt==VT_BSTR)
      wprintf(L"TelephonePager: %s\n", var.bstrVal);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"TelephonePager property not found.\n");
    else
        wprintf(L"TelephonePager failed with HR: %x\n", hr);
}
VariantClear(&var);
hr = pUser->get_Title(&bstr); 
if (SUCCEEDED(hr))
{
      wprintf(L"Title: %s\n", bstr);
      SysFreeString(bstr);
}
else
{
	if (hr==E_ADS_PROPERTY_NOT_FOUND)
		wprintf(L"Title property not found.\n");
    else
        wprintf(L"Title failed with HR: %x\n", hr);
}

return hr;

}