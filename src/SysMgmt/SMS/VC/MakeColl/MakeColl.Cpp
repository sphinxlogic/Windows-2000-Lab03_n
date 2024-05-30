// ************************************************************************************************
// Copyright (c)1998-99 Microsoft Corporation, All Rights Reserved
// ************************************************************************************************
// MakeColl - Version 1.0
//
// MakeColl.cpp
//   Generates a new collection using direct rules from a text file of machine names or ip addresses.
// Demonstrates:
//	  The helper classes and defines in SshWbemHelpers.h/.cpp, T_SafeVector.h, and SMSProv.h
//
//   CWbemServices.ConnectServer
//   CWbemServices.GetObject
//   CWbemServices.ExecQuery
//   CWbemServices.ExecMethod
//   CWbemServices.PutInstance
//	  CWbemServices.SetContextValue
//	  CWbemServices.GetMethodSignatures
//	  CWbemServices.CreateInstance
//
//   CWbemClassObject.Put
//   CWbemClassObject.Get
//   CWbemClassObject.SpawnInstance
//
//   Operations with Embedded Objects
//
//   IWbemCallResult->GetResultString
//   IEnumWbemObject->Next
//
// After parsing the command line and connecting, makecoll creates a new instance of SMS_Collection
// (see SMS SDK sample app SWDist for more info on creating new instances)  In order for the
// new collection to be visible to the SMS Admin UI, an accompanying instance of
// SMS_CollectToSubCollect_a must also be created.  Next, the text file is read line by line and
// calls to GetResourceIDForNetbiosName (or GetResourceIDForIPAddress, depending on the command-
// line parameters) return ResourceID's for machine names or IP's.  This is done by executing a 
// query against instances of SMS_R_System.	After a ResourceID has been retrieved, it is stored
// in an instance of SMS_CollectionRuleDirect, which is embedded in the CollectionRule in-parameter of
// of AddMembershipRule: a method of the newly created collection.  RequestRefresh is then called
// to update the collections membership according to the new rules.
// ************************************************************************************************


#include "stdpch.h"
#include <stdio.h>
#include <conio.h>
#include "wbemsec.h"
#include <SshWbemHelpers.h>

#include <T_SafeVector.h>

// the advantage of using the predefined symbols instead of the literal names themselves is that
// a spelling error can be caught at compile time instead of slipping through
// and causing a difficult to locate runtime error
#define _USE_AUTOSYMBOLS  // must be defined before the include
#define _INIT_AUTOSYMBOLS // must be defined before the include in one and only one file
#include <smsprov.h> 	  // include wbem names.

using namespace SMSSDK; // save ourselves some typing by using this namespace 

// functions used in this module
int  Init(CWbemServices& wsServ, IWbemServices** ppwsCache, const _bstr_t& sServer, const _bstr_t& sUser, const _bstr_t& sPassword);
bool PromptUserForPassword(char* szPassword);
bool ParseCommandLine(int argc, WCHAR *argv[]);
int  CreateCollection(CWbemServices& wsServ, const _bstr_t& sCollectionName, _bstr_t& sCollectionPath);
int  CreateCollectToSubCollect(CWbemServices& wsServ, const _bstr_t& sCollectionPath);
int  GetResourceIDForNetbiosName(CWbemServices& wsServ, const _bstr_t& sNetbiosName, long *pnResourceID);
int  GetResourceIDForIPAddress(CWbemServices& wsServ, const _bstr_t& sIPAddress, long *pnResourceID);
int  AddMembershipRuleToVector(CWbemServices& wsServ, CWbemClassObjectSafeVector& vwcoRules, long nResourceID);
int  AddCollectionMembershipRules(CWbemServices& wsServ, const _bstr_t& sCollectionPath, CWbemClassObjectSafeVector& vwcoRules);
int  UpdateCollectionMembership(CWbemServices& wsServ, const _bstr_t& sCollectionPath);
int  ProcessListFile(CWbemServices& wsServ, const _bstr_t& sFilename, const _bstr_t& sCollectionPath);

// *******************************************
// Global Variables:
// These will hold the command line parameters
// *******************************************

_bstr_t g_sFilename; 	// text file to read from
_bstr_t g_sCollection;		// name of the collection to create
_bstr_t g_sServer;			// server to connect to

_bstr_t g_sUser;			// userid to connect with
_bstr_t g_sPassword; 	// associated password
bool gbPassAlloced = false;			// was password dynamically allocated?
bool gbIPAddress = false;			// read ip addresses from the file?


// *********************************************
// Init : Connect to specified Server, Sitecode.
// [in] CWbemServices& wsServ - the WBEM services object
// [out] IWbemServices** ppwsCache - the IWbemServices pointer to cache
// [in] const _bstr_t& Server
// [in] const _bstr_t& Sitecode
// [in] const _bstr_t& User
// [in] const _bstr_t& Password
// Returns: int
// 	0 Success
// 	1 CoCreateInstance WbemLocator Failed
// 	2 Specified Server was not found
// 	3 Specified Sitecode was not found
// 	4 Error retrieving NamespacePath
// 	5 Could not connect to NamespacePath
// *********************************************
int Init(CWbemServices& wsServ, IWbemServices** ppwsCache, const _bstr_t& sServer, const _bstr_t& sUser, const _bstr_t& sPassword) 
{
	HRESULT hr;
	_bstr_t sNamespace;
	CWbemClassObject wcoProviderLocation;
	
	// Store \\server\root\sms
	sNamespace = L"\\\\" + sServer + L"\\root\\sms";
	
	try
	{
		// connect to WMI
		
		// To support multithreading, CWbemServices actually stores the WBEM services pointer in an IStream.
		// DCOM, however, requires that an actual interface pointer always be kept around to insure that 
		// the object stays in memory, we put this pointer in ppwsCache
		wsServ.ConnectServer(sNamespace, sUser, sPassword, ppwsCache);
	}
	catch (CWbemException e)
	{
		return 2;
	}
	
	// search for the local provider
	IEnumWbemClassObjectPtr pWbemEnum;
	ULONG ulReturned;
	_bstr_t sQuery;
	
	sQuery = _bstr_t(L"SELECT * FROM ") + CLASS_SMS_ProviderLocation + L" WHERE ";
	sQuery += _bstr_t(SMS_ProviderLocation::PROP_ProviderForLocalSite) + L"=True";
	
	hr = wsServ.ExecQuery(sQuery,&pWbemEnum);
	if (FAILED(hr))
		return 4;
	
	// SetSecurity
	hr = SetInterfaceSecurity(pWbemEnum, NULL, g_sUser, g_sPassword, true);
	if (FAILED(hr))
		return 4;
	
	// Walk through the elements of the enumerator.
	// I'm safely assuming there will only be 1 local provider.
	hr = pWbemEnum->Next(-1, 1, &wcoProviderLocation, &ulReturned);
	if (FAILED(hr) || ulReturned==0 ) 
		return 4;
	
	// Retrieve the value of "NamespacePath".  This will give us the namespace of the true provider location.
	sNamespace = wcoProviderLocation.GetString(SMS_ProviderLocation::PROP_NamespacePath);
	if (!sNamespace)
		return 4;
	
	
	// Finally, connect to the true provider location
	try
	{
		(*ppwsCache)->Release(); // release our cached pointer
		*ppwsCache = NULL;
		wsServ.ConnectServer(sNamespace, sUser, sPassword, ppwsCache);
	}
	catch (CWbemException e)
	{
		return 5;
	}
	
	// set the context
	WCHAR wcComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	
	wcComputerName[0] = L'\0';
	DWORD dwLen = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerNameW(wcComputerName,&dwLen);
	
	wsServ.SetContextValue(CONTEXTVALUE_ApplicationName,"MakeColl Sample App");
	wsServ.SetContextValue(CONTEXTVALUE_MachineName,_bstr_t(wcComputerName));
			
	
	return 0;
}

bool PromptUserForPassword(char* szPassword) 
{
	char c;
	int i = 0;
	
	printf("Type the password for %wS:", g_sUser);
	
	do 
	{
		c = _getch();
		switch( c ) 
		{
			
		case 8:						// backspace
			if( i-- > 0 ) 
			{
				printf("\b \b");
			}
			break;
			
		case 13: 				// enter
			printf("\n\n");
			szPassword[i] = 0;
			return true;
			
		case 3:						// ctrl-c
		case 27: 				// esc
			printf(" (aborted)\n\n");
			return false;
			
		default: 				// anything else
			printf("*");
			szPassword[i++] = c;
		}
		
	} while( 1 );
}


// **************************************************************************
// ParseCommandLine : Parses the command line.
//
// [in] int argc
// [in] WCHAR *argv[]
// Returns : 
// 	  true  = continue with execution.
// 	  false = stop.  An error was encountered, or the help info was displayed.
// Parsed commands are stored in global variables.
// **************************************************************************
bool ParseCommandLine(int argc, WCHAR *argv[]) 
{
	
	int iArg;	// argument
	int iLoop;	// index
	bool bPassword = false;
	
	char password[255];
	
	for( iLoop = iArg = 1; iLoop < argc; iLoop++ ) 
	{
		if( (*argv[iLoop] != L'-') && (*argv[iLoop] != L'/') ) 
		{
			switch( iArg++ ) 
			{
			case 1:
				// text filename
				g_sFilename = argv[iLoop];
				bPassword = false;
				break;
			case 2:
				// Collection Name
				g_sCollection = argv[iLoop];
				bPassword = false;
				break;
			case 3:
				// Server
				g_sServer = argv[iLoop];
				bPassword = false;
				break;
			default:
				if( bPassword ) 
				{
					g_sPassword = argv[iLoop];
					bPassword = false;
					iArg--;
				} 
				else return false;
			}
		}
		else 
		{
			if( !wcsnicmp(argv[iLoop] + 1, L"U:", 2) ) 
			{
				g_sUser = argv[iLoop] + 3; 			// User name
				bPassword = true;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"I", 1) ) 
			{
				gbIPAddress = true;					// IPAddress Mode
				bPassword = false;
			}
			else if ( !wcsnicmp(argv[iLoop] + 1, L"?", 1) ) return false;	// help
		}
	}
	
	// Check for correct number of real arguments
	if( iArg != 4 ) return false;
	
	// Prompt user for password?
	if( !g_sPassword || g_sPassword != _bstr_t(L"*") ) return true;
	
	// If user did not abort password input...
	if( !PromptUserForPassword(password) ) return false;
	
	g_sPassword = password;
	gbPassAlloced = true;
	
	return true;
}

// ************************************************************************
// CreateCollection : Creates a collection of the specified name.
// [in] CWbemServices& wsServ - the WBEM services object
// [in] const _bstr_t& CollectionName - name of the collection to create
// [out] _bstr_t& CollectionPath - Object path of the newly created collection
// Returns: int
// 	0 success
// 	1 GetObject(SMS_Collection) failed.
// 	2 SpawnInstance failed.
// 	3 Put Name failed.
// 	4 Put OwnedByThisSite failed.
// 	5 PutInstance failed.
// 	6 GetResultString failed.
// 	7 SetInterfaceSecurity failed.
// ************************************************************************
int CreateCollection(CWbemServices& wsServ, const _bstr_t& sCollectionName, _bstr_t& sCollectionPath) 
{
	
	HRESULT hr = 0;
	CWbemClassObject wcoCollInst;
	IWbemCallResultPtr pCallResult;
	BSTR bstrCollectionPath=NULL;
	
	
	// Spawn an instance of SMS_Collection
	wcoCollInst = wsServ.CreateInstance(CLASS_SMS_Collection);
	if( !wcoCollInst )
		return 2;
	
	
	// Store the collection name in the collection class
	hr = wcoCollInst.Put(SMS_Collection::PROP_Name,sCollectionName);
	if( FAILED(hr) )
		return 3;
	
	// Store the OwnedByThisSite variant in the collection
	hr = wcoCollInst.Put(SMS_Collection::PROP_OwnedByThisSite,true);
	if( FAILED(hr) )
		return 4;
	
	// Store the class as a new instance in the repository
	hr = wsServ.PutInstance(wcoCollInst, pCallResult);
	if( FAILED(hr) )
		return 5;
	
	
	// SetSecurity
	if( FAILED( SetInterfaceSecurity(pCallResult, NULL, g_sUser, g_sPassword, true) ) ) 
		return 7;
	
	// Get the Object Path to the new Collection.  (keyhole)
	hr = pCallResult->GetResultString(WBEM_INFINITE, &bstrCollectionPath);
	if( FAILED(hr) )
		return 6;
	
	// Allocate and fill the CollectionPath Out-parameter, grab ownership of BSTR
	sCollectionPath = _bstr_t(bstrCollectionPath,false);
	
	return 0;
}


// ************************************************************************
// CreateCollectToSubCollect : Creates an instance of CollectToSubCollect
//		Without creating an instance of this class the collection would not be visible in the MMC.
//		Normally it's more straightforward to modify the SMS_CollectToSubCollect table
//    but we already have the path.
//
//	[in] CWbemServices& wsServ - the WBEM services object
// [in] const _bstr_t& CollectionPath - Object Path of the collection just created
// Returns: int
// 	0 success
// 	1 GetObject(SMS_CollectToSubCollect) failed.
// 	2 SpawnInstance failed.
// 	3 Put ParentCollection or SubCollection failed.
// 	4 PutInstance failed.
// ************************************************************************
int CreateCollectToSubCollect(CWbemServices& wsServ, const _bstr_t& sCollectionPath) 
{
	
	HRESULT hr = 0;
	CWbemClassObject wcoAssocInst;
	_bstr_t sRootCollPath;
	
	// Spawn an instance of SMS_CollectToSubCollect_a
	wcoAssocInst = wsServ.CreateInstance(CLASS_SMS_CollectToSubCollect_a);
	if( !wcoAssocInst )
		return 2;
	
	// Store the collection path in the SMS_CollectToSubCollect_a instance
	hr = wcoAssocInst.Put(SMS_CollectToSubCollect_a::PROP_subCollection, sCollectionPath);
	if( FAILED(hr) ) 
		return 3;
	
	// Prepare the root collection path
	sRootCollPath = _bstr_t(CLASS_SMS_Collection) + L"." + SMS_Collection::PROP_CollectionID + L"=\"COLLROOT\"";
	
	// Store the root collection name (CollRoot) in the SMS_CollectToSubCollect_a class
	hr = wcoAssocInst.Put(SMS_CollectToSubCollect_a::PROP_parentCollection, sRootCollPath);
	if( FAILED(hr) ) 
		return 3;
	
	// Store the class as a new instance in the repository - we're attaching our collection to the root collection
	hr = wsServ.PutInstance(wcoAssocInst);
	if( FAILED(hr) )
		return 4;
	
	return 0;
}


// **************************************************************************
// GetResourceIDForNetbiosName : Queries SMS_R_System for the specified name.
// [in] CWbemServices& wsServ - the WBEM services pointer
// [in] const _bstr_t& NetbiosName - the machine name to look up
// [out] long* pnResourceID - the matching resource ID if found
// Returns: int
// 	0 success
// 	1 No such NetbiosName exists.
// 	2 Query failed.
// 	3 ResourceID retrieval failed.
// 	4 SetInterfaceSecurity failed.
// **************************************************************************
int GetResourceIDForNetbiosName(CWbemServices& wsServ, const _bstr_t& sNetbiosName, long *pnResourceID) 
{
	
	HRESULT hr;
	_variant_t vVar;
	ULONG ulReturned;
	IEnumWbemClassObjectPtr pEnum;
	CWbemClassObject wcoResult;
	_bstr_t sQuery;
	
	
	// Build Query string.
	sQuery = _bstr_t(L"SELECT ") + SMS_Resource::PROP_ResourceId + L" FROM " + CLASS_SMS_R_System  + 
		L" WHERE " + SMS_R_System::PROP_NetbiosName + L"=\"" + sNetbiosName + L"\"";
	
	// Execute the query
	hr = wsServ.ExecQuery(sQuery, &pEnum);
	if( FAILED(hr) ) 
		return 2;
	
	// SetSecurity
	if( FAILED( SetInterfaceSecurity(pEnum, NULL, g_sUser, g_sPassword, true) ) ) 
		return 4;
	
	// Walk through the elements of the enumerator.
	// I'm safely assuming there will only be 1 computer with the requested name, if any.
	if( !FAILED(pEnum->Next(-1, 1, &wcoResult, &ulReturned)) && ulReturned ) 
	{
		
		// Result was returned
		
		// Retrieve the resourceid
		*pnResourceID = wcoResult.GetLong(SMS_Resource::PROP_ResourceId);
	}
	else 
	{
		// Enumerator was empty
		return 1;
	}
	
	return 0;
}

// **************************************************************************
// GetResourceIDForIPAddress : Queries SMS_R_System for the specified address.
// [in] CWbemServices& wsServ - the WBEM services object
// [in] const _bstr_t& IPAddress - string containing IP address to look up
// [out] long* pnResourceID - the matching resource ID if found
// Returns: int
// 	0 success
// 	1 No such IPAddress was found.
// 	2 Query failed.
// 	3 ResourceID retrieval failed.
// 	4 SetInterfaceSecurity failed.
// **************************************************************************
int GetResourceIDForIPAddress(CWbemServices& wsServ, const _bstr_t& sIPAddress, long *pnResourceID) 
{
	
	HRESULT hr;
	ULONG ulReturned;
	IEnumWbemClassObjectPtr pEnum;
	CWbemClassObject wcoResult;
	_bstr_t sQuery;
	
	// Build Query string.
	sQuery = _bstr_t(L"SELECT ") + SMS_Resource::PROP_ResourceId + L" FROM " + CLASS_SMS_R_System + 
		L" WHERE " + SMS_R_System::PROP_IPAddresses + L"=\"" + sIPAddress + L"\"";
	
	// Execute the query
	hr = wsServ.ExecQuery(sQuery,  &pEnum);
	if( FAILED(hr) ) 
		return 2;
	
	// SetSecurity
	if( FAILED( SetInterfaceSecurity(pEnum, NULL, g_sUser, g_sPassword, true) ) ) 
		return 4;
	
	// Walk through the elements of the enumerator.
	// I'm safely assuming there will only be 1 computer with the requested address, if any.
	if( !FAILED(pEnum->Next(-1, 1, &wcoResult, &ulReturned)) && ulReturned )
	{
		
		// Result was returned
		
		// Retrieve the resourceid
		*pnResourceID = wcoResult.GetLong(SMS_Resource::PROP_ResourceId);
		
	}	
	else
	{
		// Enumerator was empty
		return 1;
	}
	
	
	return 0;
}

// **************************************************************************
//  AddMembershipRuleToVector - Adds a membership rule object to the end of the
// 									  supplied vector
//		[in] CWbemServices& wsServ - WBEM services object
// 	[in, out] CWbemClassObjectSafeVector& vwcoRules - our vector of rule objects
// 	[in] long nResourceID - id of resource to add as a direct rule
// Returns: int
// 	0 success
// 	4 get collectionrule class failed
// 	5 error storing resourceclassname
// 	6 error storing rulename
// 	7 error storing resourceid
// ********************************************************************
int AddMembershipRuleToVector(CWbemServices& wsServ, CWbemClassObjectSafeVector& vwcoRules, long nResourceID)
{
	HRESULT hr;
	CWbemClassObject wcoRule;
	_bstr_t sRulename;
	
	
	wcoRule = wsServ.CreateInstance(CLASS_SMS_CollectionRuleDirect);
	if( !wcoRule )
		return 4;
	
	// Store the resource class name (sms_r_system) 
	hr = wcoRule.Put(SMS_CollectionRuleDirect::PROP_ResourceClassName, _bstr_t(CLASS_SMS_R_System));
	if( FAILED(hr) ) 
		return 5;
	
	//  build a RuleName
	sRulename = L"MakeColl Resource=" + _bstr_t(_variant_t(nResourceID));
	
	// Store the rulename
	hr = wcoRule.Put(SMS_CollectionRule::PROP_RuleName, sRulename);
	if( FAILED(hr) ) 
		return 6;
	
	// Store ResourceID
	hr = wcoRule.Put(SMS_CollectionRuleDirect::PROP_ResourceID, nResourceID);
	if( FAILED(hr) ) 
		return 7;
	
	vwcoRules.push_back(wcoRule);
	
	return 0;
}

// ********************************************************************
// AddCollectionMembershipRules : Adds a membership rule to a collection
// [in] CWbemServices& wsServ - the WBEM services object
// [in] const _bstr_t& CollectionPath - path of collection to add rules to
// [in] CWbemClassObjectSafeVector& vwcoRules - vector of rule objects to add
// Returns: int
// 	0 success
// 	1 get sms_collection failed
// 	3 spawninstance on in-parameter failed
// 	2 get in-parameter class failed
// 	8 error storing embedded object in the imparam
// 	9 method failed
// ********************************************************************
int AddCollectionMembershipRules(CWbemServices& wsServ, const _bstr_t& sCollectionPath, CWbemClassObjectSafeVector& vwcoRules) 
{
	
	HRESULT hr;
	CWbemClassObject wcoInparamClass;
	CWbemClassObject wcoOutparamClass;
	CWbemClassObject wcoInparam;
	CWbemClassObject wcoOutparam;
	
	// Gather all the classes we will need to call AddMembershipRules
	hr = wsServ.GetMethodSignatures(CLASS_SMS_Collection,SMS_Collection::METHOD_AddMembershipRules,wcoInparamClass,wcoOutparamClass);
	
	if( FAILED(hr) )
		return 2;
	
	wcoInparam = wcoInparamClass.SpawnInstance();
	if( !wcoInparam ) 
		return 3;
	
	hr = wcoInparam.Put(SMS_Collection::AddMembershipRules::In::PARAM_collectionRules, vwcoRules.GetVariant());
	if( FAILED(hr) )
		return 8;
	
	// And finally...  Execute the AddMembershipRules (wcoOutparam is NULL since we don't want it)
	hr = wsServ.ExecMethod(sCollectionPath, SMS_Collection::METHOD_AddMembershipRules, wcoInparam, wcoOutparam);
	if( FAILED(hr) )
		return 9;
	
	return 0;
}

// ********************************************************************
// UpdateCollectionMembership : marks a collection for reevaluation
// [in] CWbemServices wsServ - WBEM services object
// [in] const _bstr_t& CollectionPath - path of the collection to update
// Returns: int
// 	0 success
// 	1 get sms_collection failed
// 	3 spawninstance on in-parameter failed
// 	2 get in-parameter class failed
// 	8 error storing value in the imparam
// 	9 method failed
// ********************************************************************
int UpdateCollectionMembership(CWbemServices& wsServ, const _bstr_t& sCollectionPath) 
{
	
	HRESULT hr;
	CWbemClassObject wcoInparamClass;
	CWbemClassObject wcoOutparamClass;
	CWbemClassObject wcoInparam;
	CWbemClassObject wcoOutparam;
	
	// Gather all the classes we will need to call RequestRefresh
	hr = wsServ.GetMethodSignatures(CLASS_SMS_Collection,SMS_Collection::METHOD_RequestRefresh,wcoInparamClass,wcoOutparamClass);
	
	if( FAILED(hr) )
		return 2;
	
	wcoInparam = wcoInparamClass.SpawnInstance();
	if( !wcoInparam ) 
		return 3;
	
	
	hr = wcoInparam.Put(SMS_Collection::RequestRefresh::In::PARAM_includesubcollections, false);
	if( FAILED(hr) )
		return 8;
	
	// And finally...  Execute the RequestRefresh (wcoOutparam is NULL since we don't want it)
	hr = wsServ.ExecMethod(sCollectionPath, SMS_Collection::METHOD_RequestRefresh, wcoInparam, wcoOutparam);
	if( FAILED(hr) )
		return 9;
	
	return 0;
}


// ********************************************************************
// ProcessListFile : 
// [in] CWbemServices& wsServ - WBEM services object
// [in] const _bstr_t& Filename - path and file name of file to process
// [in] const _bstr_t& CollectionPath - path of the collection to add members to
// Returns: int
// 	0 success
// 	1 failed to open the file.
// ********************************************************************
int ProcessListFile(CWbemServices& wsServ, const _bstr_t& sFilename, const _bstr_t& sCollectionPath) 
{
	FILE *fListfile;
	ULONG ulCount = 0;
	ULONG ulSuccess = 0;
	WCHAR pwszLine[256];
	WCHAR *pwszNewline;
	long nResourceID;
	HRESULT hr;
	int result;
	CWbemClassObjectSafeVector vwcoRules;
	
	
	// open the file
	fListfile = _wfopen(sFilename, L"r");
	
	if( !fListfile ) 
	{
		printf("\n-- File %wS does not exist, Deleting the collection...",sFilename);
		hr = wsServ.DeleteInstance(sCollectionPath);
		if( FAILED(hr) ) 
			printf("error.\nERROR: Collection couldn't not be deleted.\n");
		else 
			printf("Done.\n");	
		return 1;
	}
	
	// Read the file
	while( !feof(fListfile)) 
	{
		
		// Get a line from the file
		if( fgetws(pwszLine, 255, fListfile) ) 
		{
			
			ulCount++;
			
			// Strip newline if necessary
			if( (pwszNewline = wcschr(pwszLine, L'\n')) ) 
				*pwszNewline = L'\0';
			
			// Call the appropriate GetResourceID function
			if( gbIPAddress ) 
				result = GetResourceIDForIPAddress(wsServ, _bstr_t(pwszLine), &nResourceID);
			else 
				result = GetResourceIDForNetbiosName(wsServ, _bstr_t(pwszLine), &nResourceID);
			
			switch( result ) 
			{
			case 0:
				switch( AddMembershipRuleToVector(wsServ, vwcoRules, nResourceID) ) 
				{
				case 0:
					ulSuccess++;
					break;
				case 9:
					printf("%ls caused AddMembershipRule to fail.\n", pwszLine);
					break;
				default:
					break;
				}
				break;
				default:
					printf("%ls was skipped.  It may not have a matching entry in SMS_R_System.\n", pwszLine);
			}
		}
		
	}
	
	if (ulSuccess)
		result = AddCollectionMembershipRules(wsServ,sCollectionPath,vwcoRules);
	
	if( ulSuccess && result==0 )
	{
		UpdateCollectionMembership(wsServ,sCollectionPath); // mark collection for update
		printf("\n-- %d of %d entries were successfully processed --\n", ulSuccess, ulCount);
	}
	else 
	{
		printf("\n-- Add membership rules failed, deleting the collection...");
		hr = wsServ.DeleteInstance(sCollectionPath);
		if( FAILED(hr) ) 
			printf("error.\nERROR: Collection couldn't not be deleted.\n");
		else
			printf("Done.\n");
	}
	
	fclose(fListfile);
	
	return 0;
	
}

// ****************************************
// wmain : Using wmain to get WCHAR argv's.
// ****************************************
extern "C" void wmain(int argc, WCHAR *argv[]) 
{
	
	if( ParseCommandLine(argc, argv) ) 
	{
		
		printf("Connecting...");
		
		// Initialize COM
		CoInitializeEx(NULL,COINIT_MULTITHREADED); 
		InitializeSecurity(true);
		
		try
		{
			IWbemServicesPtr pwsCache; 
			CWbemServices wsServ;
			
			int rval = Init(wsServ, &pwsCache, g_sServer, g_sUser, g_sPassword);
			
			// Call Init
			switch( rval ) 
			{
			case 0:
				printf("Done.\n");
				break;
			case 1:
				printf("\nERROR: CoCreateInstance WbemLocator Failed.\n");
				return;
			case 2:
				printf("\nERROR: Could not connect to the specified server.\n");
				return;
			case 3:
				printf("\nERROR: Specified Sitecode was invalid.\n");
				return;
			case 4:
				printf("\nERROR: Could not retrieve the Namespace Path.\n");
				return;
			case 5:
				printf("\nERROR: Could not connect to the provider location.\n");
				return;
			}
			
			printf("Creating Collection...");
			
			_bstr_t sCollectionPath;		// CreateCollection will return the object path of the new collection here.
			
			// Call CreateCollection
			rval = CreateCollection(wsServ, g_sCollection, sCollectionPath);
			
			switch( rval ) 
			{
			case 0:
				printf("Object path: %ls\n", (WCHAR*)sCollectionPath);
				break;
			case 1:
				printf("\nERROR: Could not GetObject SMS_Collection.  Do you have permission?\n");
				return;
			case 2:
				printf("\nERROR: Could not spawn new instance.\n");
				return;
			case 3:
				printf("\nERROR: Could not store the collection name.\n");
				return;
			case 4:
				printf("\nERROR: Could not set the \"Owned By This Site\" flag.\n");
				return;
			case 5:
				printf("\nERROR: Could not store new collection in the repository.\n");
				printf("You probably do not have permission to create collections.\n");
				return;
			case 6:
				printf("\nERROR: Could not retrieve the object path to the new collection.\n");
				return;
			case 7:
				printf("\nERROR: Could not retrieve the object path to the new collection.\n");
				printf("Note:  This was caused by a security malfunction, try -u:DOMAIN\\USER\n");
				return;
			}
			
			printf("Creating CollectToSubCollect...");
			
			
			// Call CreateCollectToSubCollect
			rval = CreateCollectToSubCollect(wsServ, sCollectionPath);
			
			switch( rval ) 
			{
			case 0:
				printf("Done.\n\n");
				break;
			case 1:
				printf("\nERROR: Could not GetObject SMS_CollectToSubCollect_a.  Do you have permission?\n");
				return;
			case 2:
				printf("\nERROR: Could not spawn new instance.\n");
				return;
			case 3:
				printf("\nERROR: Could not store the ParentCollection or Subcollection name.\n");
				return;
			case 4:
				printf("\nERROR: Could not store new SMS_CollectToSubCollect_a in the repository.\n");
				return;
			case 5:
				printf("\nERROR: Could not retrieve the object path to the new SMS_CollectToSubCollect_a.\n");
				return;
			}
			
			printf("Adding collection members...\n");
			
			rval = ProcessListFile(wsServ, g_sFilename, sCollectionPath);
			
			if( rval ) 
				printf("ERROR: Couldn't find file: %ls\n", (WCHAR*)g_sFilename);
			
		}
		catch (CWbemException e)
		{
			printf("WMI Exception: %ls\n",(WCHAR*)e.GetDescription());
		}
		catch (_com_error e)
		{
			printf("COM Exception: %ls\n",(WCHAR*)e.Description());
		}
		
		CoUninitialize();
	}
	else 
	{
		printf(
			"MakeColl -- Make Collection generates a new collection\n"
			"using a text file list of machine names or ip addresses.\n"
			"----------------------------------------------------------\n"
			"The input file should be a simple, newline delimited list of\n"
			"Netbios Machine Names, or IP Addresses.\n\n"
			"Usage:  MakeColl <filename> <collection> <server>\n"
			"                 [-I] [-U:<user> [<password> | *]]\n"
			"Where:\n"
			"    filename   : text file list of machine names or ip addresses.\n"
			"    collection : the created collection will have this name.\n"
			"    server     : sms site server machine name.\n"
			"    user       : userid for connection\n"
			"    password   : password for userid\n"
			"    -I         : read IP Addresses from the file, rather than\n"
			"                 machine names.\n\n"
			);
	}
}
