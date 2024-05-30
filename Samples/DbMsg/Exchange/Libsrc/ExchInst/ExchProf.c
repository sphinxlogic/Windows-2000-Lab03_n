// --exchprof.c-----------------------------------------------------------------
//
// Functions for installing Exchange objects.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"

#include "exchprof.chk"

#define lpszServerPlaceHolder           ((LPSTR)-1)
#define lpszObjectPlaceHolder           ((LPSTR)-2)
#define lpszDisplayNamePlaceHolder      ((LPSTR)-3)
#define lpszProfileVersionPlaceHolder   ((LPSTR)-4)

typedef struct 
{
    LPSTR  lpszSection;
    LPSTR  lpszKey;
    ULONG   ulKey;
    LPSTR  lpszValue;
} SERVICESINIREC;

//$--aGwServicesIni-------------------------------------------------------------
//  Structure defines data to be written into MAPISVC.INF to create gateway
//  service.
// -----------------------------------------------------------------------------
static SERVICESINIREC aGwServicesIni[] =
{
    {"Services",                 "MSEMS_EdkGateway", 0L,                    "Microsoft Exchange Gateway Profile"},

    {"MSEMS_EdkGateway",         NULL,        PR_DISPLAY_NAME,              "Microsoft Exchange Gateway"},
    {"MSEMS_EdkGateway",         "Providers", 0L,                           "MSEMS_DSA_EdkGateway, MSEMS_MDB_EdkGateway, MSEMS_EdkGateway_Public"},
    {"MSEMS_EdkGateway",         "Sections",  0L,                           "MSEMS_EdkGateway_Section"},
    {"MSEMS_EdkGateway",         NULL,        PR_SERVICE_DLL_NAME,          "emsui.dll"},
    {"MSEMS_EdkGateway",         NULL,        PR_SERVICE_ENTRY_NAME,        "EMSCfg"},

    {"MSEMS_EdkGateway_Public",  NULL,        PR_DISPLAY_NAME,              "Public Folders"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_PROVIDER_DISPLAY,          "Microsoft Exchange Message Store"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_RESOURCE_TYPE,             "MAPI_STORE_PROVIDER"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_PROVIDER_DLL_NAME,         "EMSMDB.DLL"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_PROFILE_SERVER,            lpszServerPlaceHolder},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_RESOURCE_FLAGS,            "STATUS_NO_DEFAULT_STORE"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_PROFILE_OPEN_FLAGS,        "06000000"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_PROFILE_TYPE,              "03000000"},
    {"MSEMS_EdkGateway_Public",  NULL,        PR_MDB_PROVIDER,              "78b2fa70aff711cd9bc800aa002fc45a"},

    {"MSEMS_DSA_EdkGateway",     NULL,        PR_DISPLAY_NAME,              "Microsoft Exchange Directory Service"},
    {"MSEMS_DSA_EdkGateway",     NULL,        PR_PROVIDER_DISPLAY,          "Microsoft Exchange Directory Service"},
    {"MSEMS_DSA_EdkGateway",     NULL,        PR_PROVIDER_DLL_NAME,         "emsabp.dll"},
    {"MSEMS_DSA_EdkGateway",     NULL,        PR_RESOURCE_TYPE,             "23000000"},

    {"MSEMS_MDB_EdkGateway",     NULL,        PR_DISPLAY_NAME,              "Private Folders"},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_PROVIDER_DISPLAY,          "Microsoft Exchange Message Store"},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_PROVIDER_DLL_NAME,         "emsmdb.dll"},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_RESOURCE_TYPE,             "21000000"},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_RESOURCE_FLAGS,            "STATUS_PRIMARY_IDENTITY|STATUS_DEFAULT_STORE|STATUS_PRIMARY_STORE"},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_PROFILE_SERVER,            lpszServerPlaceHolder},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_PROFILE_OPEN_FLAGS,        "08000000"},
    {"MSEMS_MDB_EdkGateway",     NULL,        PR_PROFILE_MAILBOX,           lpszObjectPlaceHolder},

    {"MSEMS_EdkGateway_Section", "UID",       0L,                           "13DBB0C8AA05101A9BB000AA002FC45A"}, // pbGlobalProfileSectionGuid
    {"MSEMS_EdkGateway_Section", NULL,        PR_PROFILE_VERSION,           lpszProfileVersionPlaceHolder},
    {"MSEMS_EdkGateway_Section", NULL,        PR_PROFILE_TRANSPORT_FLAGS,   "00000000"},
    {"MSEMS_EdkGateway_Section", NULL,        PR_PROFILE_CONNECT_FLAGS,     "01000000"},
    {"MSEMS_EdkGateway_Section", NULL,        PR_PROFILE_HOME_SERVER,       lpszServerPlaceHolder},
    {"MSEMS_EdkGateway_Section", NULL,        PR_PROFILE_USER,              lpszObjectPlaceHolder},

    {NULL, NULL, 0L, NULL}
};

static SERVICESINIREC aMbServicesIni[] =
{
	{"Services",                 "MSEMS_EdkMbAgent", 0L, "Microsoft Exchange Mailbox Agent Profile"}, 

	{"MSEMS_EdkMbAgent",         NULL,        PR_DISPLAY_NAME,            "Microsoft Exchange Mailbox Agent"}, 
	{"MSEMS_EdkMbAgent",         "Providers", 0L,                         "MSEMS_EdkMbAgent_DSA, MSEMS_EdkMbAgent_MDB, MSEMS_EdkMbAgent_Public, MSEMS_EdkMbAgent_MSX"}, 
	{"MSEMS_EdkMbAgent",         "Sections",  0L,                         "MSEMS_EdkMbAgent_Section"}, 
	{"MSEMS_EdkMbAgent",         NULL,        PR_SERVICE_DLL_NAME,        "emsui.dll"}, 
	{"MSEMS_EdkMbAgent",         NULL,        PR_SERVICE_SUPPORT_FILES,   "emsui.dll,emsabp.dll,emsmdb.dll,emsuix.dll"}, 
	{"MSEMS_EdkMbAgent",         NULL,        PR_SERVICE_ENTRY_NAME,      "EMSCfg"}, 
	{"MSEMS_EdkMbAgent",         NULL,        PR_RESOURCE_FLAGS,          "SERVICE_SINGLE_COPY"}, 

    {"MSEMS_EdkMbAgent_DSA",     NULL,        PR_DISPLAY_NAME,            "Microsoft Exchange Directory Service"},
    {"MSEMS_EdkMbAgent_DSA",     NULL,        PR_PROVIDER_DISPLAY,        "Microsoft Exchange Directory Service"},
    {"MSEMS_EdkMbAgent_DSA",     NULL,        PR_PROFILE_HOME_SERVER,     lpszServerPlaceHolder},
    {"MSEMS_EdkMbAgent_DSA",     NULL,        PR_PROFILE_SERVER,          lpszServerPlaceHolder},
    {"MSEMS_EdkMbAgent_DSA",     NULL,        PR_PROVIDER_DLL_NAME,       "emsabp.dll"},
    {"MSEMS_EdkMbAgent_DSA",     NULL,        PR_RESOURCE_TYPE,           "MAPI_AB_PROVIDER"},

	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_DISPLAY_NAME,            "Private Folders"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_PROVIDER_DISPLAY,        "Microsoft Exchange Message Store"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_PROVIDER_DLL_NAME,       "EMSMDB.DLL"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_RESOURCE_TYPE,           "MAPI_STORE_PROVIDER"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_RESOURCE_FLAGS,          "STATUS_PRIMARY_IDENTITY|STATUS_DEFAULT_STORE|STATUS_PRIMARY_STORE"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_PROFILE_OPEN_FLAGS,      "0C000000"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_PROFILE_TYPE,            "01000000"}, 
	{"MSEMS_EdkMbAgent_MDB",     NULL,        PR_MDB_PROVIDER,            "5494A1C0297F101BA58708002B2A2517"}, 
    {"MSEMS_EdkMbAgent_MDB",     NULL,        PR_PROFILE_SERVER,          lpszServerPlaceHolder},
    {"MSEMS_EdkMbAgent_MDB",     NULL,        PR_PROFILE_MAILBOX,         lpszObjectPlaceHolder},

    {"MSEMS_EdkMbAgent_MSX",     NULL,        PR_DISPLAY_NAME,            "Microsoft Exchange Transport"}, 
    {"MSEMS_EdkMbAgent_MSX",     NULL,        PR_PROVIDER_DISPLAY,        "Microsoft Exchange Transport"}, 
    {"MSEMS_EdkMbAgent_MSX",     NULL,        PR_PROVIDER_DLL_NAME,       "EMSMDB.DLL"}, 
    {"MSEMS_EdkMbAgent_MSX",     NULL,        PR_RESOURCE_TYPE,           "MAPI_TRANSPORT_PROVIDER"}, 
	{"MSEMS_EdkMbAgent_MSX",     NULL,        PR_PROFILE_OPEN_FLAGS,      "00000000"}, 
    {"MSEMS_EdkMbAgent_MSX",     NULL,        PR_PROFILE_SERVER,          lpszServerPlaceHolder},
    {"MSEMS_EdkMbAgent_MSX",     NULL,        PR_PROFILE_MAILBOX,         lpszObjectPlaceHolder},

    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_DISPLAY_NAME,            "Public Folders"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_PROVIDER_DISPLAY,        "Microsoft Exchange Message Store"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_RESOURCE_TYPE,           "MAPI_STORE_PROVIDER"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_PROVIDER_DLL_NAME,       "EMSMDB.DLL"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_PROFILE_SERVER,          lpszServerPlaceHolder},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_RESOURCE_FLAGS,          "STATUS_NO_DEFAULT_STORE"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_PROFILE_OPEN_FLAGS,      "06000000"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_PROFILE_TYPE,            "03000000"},
    {"MSEMS_EdkMbAgent_Public",  NULL,        PR_MDB_PROVIDER,            "78b2fa70aff711cd9bc800aa002fc45a"},

    {"MSEMS_EdkMbAgent_Section", "UID",       0L,                         "13DBB0C8AA05101A9BB000AA002FC45A"}, // pbGlobalProfileSectionGuid
    {"MSEMS_EdkMbAgent_Section", NULL,        PR_PROFILE_VERSION,         lpszProfileVersionPlaceHolder},
    {"MSEMS_EdkMbAgent_Section", NULL,        PR_PROFILE_TRANSPORT_FLAGS, "00000000"},
    {"MSEMS_EdkMbAgent_Section", NULL,        PR_PROFILE_CONNECT_FLAGS,   "03000000"},
    {"MSEMS_EdkMbAgent_Section", NULL,        PR_PROFILE_HOME_SERVER,     lpszServerPlaceHolder},
    {"MSEMS_EdkMbAgent_Section", NULL,        PR_PROFILE_USER,            lpszObjectPlaceHolder},

    {NULL, NULL, 0L, NULL}
};

//$--HrSetGatewayProfileParameters----------------------------------------------
//  Add values to MAPISVC.INF to create profile for the specified gateway.
// -----------------------------------------------------------------------------
static HRESULT HrSetGatewayProfileParameters(   // RETURNS: return code
    IN LPSTR lpszServerName,                   // server name
    IN LPSTR lpszSiteDN,                       // site distinguished name
    IN LPSTR lpszCommonName)                   // common name
{
    HRESULT hr                           = E_FAIL;
    BOOL    fRet                         = FALSE;
    UINT    uiRet                        = 0;
    LPSTR  lpszDN                       = NULL;
    CHAR   szSystemDir[MAX_PATH+1]      = {0};
    CHAR   szServicesIni[MAX_PATH+12]   = {0}; // 12 = space for "MAPISVC.INF"
    UINT    n                            = 0;
    CHAR   szPropNum[10]                = {0};
    LONG    cBytes                       = 0;
    LONG    lRet                         = 0;
    CHAR   szProfileVersion[MAX_PATH+1] = {0};
    WORD    wver[2]                      = {0};
    BYTE    bver[4]                      = {0};

    DEBUGPRIVATE("HrSetGatewayProfileParameters()\n");

    hr = CHK_HrSetGatewayProfileParameters(
        lpszServerName,
        lpszSiteDN,
        lpszCommonName);
    if(FAILED(hr))
        RETURN(hr);

    //
    // Compute profile version
    //

    wver[0] = LOWORD(PROFILE_VERSION);
    wver[1] = HIWORD(PROFILE_VERSION);

    bver[0] = LOBYTE(wver[0]);
    bver[1] = HIBYTE(wver[0]);
    bver[2] = LOBYTE(wver[1]);
    bver[3] = HIBYTE(wver[1]);

    cBytes = _snprintf(
        szProfileVersion,
        MAX_PATH+1,
        "%02x%02x%02x%02x",
        bver[0], bver[1], bver[2], bver[3]);

    if(cBytes < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    //  Compute the DN for use later.
    //

    cBytes = 
        lstrlen(lpszSiteDN) +
        lstrlen(CONTAINER_GW) +
        4 +
        lstrlen(lpszCommonName)
        + 1;

    cBytes *= sizeof(CHAR);
            
    lpszDN = (LPSTR)GlobalAlloc(GMEM_FIXED, cBytes);

    if(lpszDN == NULL)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
        goto cleanup;
    }

    lRet = _snprintf(
        lpszDN,
        cBytes,
        "%s%s/cn=%s",
        lpszSiteDN,
        CONTAINER_GW,
        lpszCommonName);

    if(lRet < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    //  Compute the path to MAPISVC.INF
    //

    uiRet = GetSystemDirectory(szSystemDir, MAX_PATH);

    if(uiRet == 0)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
        goto cleanup;
    }

    sprintf(szServicesIni, "%s\\%s", szSystemDir, "MAPISVC.INF");

    //
    //  Loop through and add items to MAPISVC.INF
    //

    n = 0;

    while(aGwServicesIni[n].lpszSection != NULL)
    {
        LPSTR lpszProp  = aGwServicesIni[n].lpszKey;
        LPSTR lpszValue = aGwServicesIni[n].lpszValue;

        // Switch the property if necessary

        if(lpszProp == NULL)
        {
            sprintf(szPropNum, "%lx", aGwServicesIni[n].ulKey);
            lpszProp = szPropNum;
        }

        // Switch the value if necessary

        if(lpszValue == lpszServerPlaceHolder)
        {
            lpszValue =  lpszServerName;
        }
        else if(lpszValue == lpszObjectPlaceHolder)
        {
            lpszValue = lpszDN;
        }
        else if(lpszValue == lpszDisplayNamePlaceHolder)
        {
            lpszValue = lpszCommonName;
        }
        else if(lpszValue == lpszProfileVersionPlaceHolder)
        {
            lpszValue = szProfileVersion;
        }

        //
        //  Write the item to MAPISVC.INF
        //

        fRet = WritePrivateProfileString(
            aGwServicesIni[n].lpszSection, 
            lpszProp,
            lpszValue,
            szServicesIni);

        if(fRet == FALSE)
        {
            hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
            goto cleanup;
        }

        n++;
    }
    
    // Flush the information

    WritePrivateProfileString(NULL, NULL, NULL, szServicesIni);

    hr = NOERROR;

cleanup:

    GLOBALFREE(lpszDN);

    RETURN(hr);
}

//$--HrSetMailboxProfileParameters----------------------------------------------
//  Add values to MAPISVC.INF to create profile for the specified mailbox.
// -----------------------------------------------------------------------------
static HRESULT HrSetMailboxProfileParameters(   // RETURNS: return code
    IN LPSTR lpszServerName,                   // server name
    IN LPSTR lpszSiteDN,                       // site distinguished name
    IN LPSTR lpszCommonName)                   // common name
{
    HRESULT hr                           = E_FAIL;
    BOOL    fRet                         = FALSE;
    UINT    uiRet                        = 0;
    LPSTR  lpszDN                       = NULL;
    CHAR   szSystemDir[MAX_PATH+1]      = {0};
    CHAR   szServicesIni[MAX_PATH+12]   = {0}; // 12 = space for "MAPISVC.INF"
    UINT    n                            = 0;
    CHAR   szPropNum[10]                = {0};
    LONG    cBytes                       = 0;
    LONG    lRet                         = 0;
    CHAR   szProfileVersion[MAX_PATH+1] = {0};
    WORD    wver[2]                      = {0};
    BYTE    bver[4]                      = {0};

    DEBUGPRIVATE("HrSetMailboxProfileParameters()\n");

    hr = CHK_HrSetMailboxProfileParameters(
        lpszServerName,
        lpszSiteDN,
        lpszCommonName);
    if(FAILED(hr))
        RETURN(hr);

    //
    // Compute profile version
    //

    wver[0] = LOWORD(PROFILE_VERSION);
    wver[1] = HIWORD(PROFILE_VERSION);

    bver[0] = LOBYTE(wver[0]);
    bver[1] = HIBYTE(wver[0]);
    bver[2] = LOBYTE(wver[1]);
    bver[3] = HIBYTE(wver[1]);

    cBytes = _snprintf(
        szProfileVersion,
        MAX_PATH+1,
        "%02x%02x%02x%02x",
        bver[0], bver[1], bver[2], bver[3]);

    if(cBytes < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    //  Compute the DN for use later.
    //

    cBytes = 
        lstrlen(lpszSiteDN) +
        lstrlen(lpszCommonName)
        + 1;

    cBytes *= sizeof(CHAR);
            
    lpszDN = (LPSTR)GlobalAlloc(GMEM_FIXED, cBytes);

    if(lpszDN == NULL)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
        goto cleanup;
    }

    lRet = _snprintf(
        lpszDN,
        cBytes,
        "%s%s",
        lpszSiteDN,
        lpszCommonName);

    if(lRet < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    //  Compute the path to MAPISVC.INF
    //

    uiRet = GetSystemDirectory(szSystemDir, MAX_PATH);

    if(uiRet == 0)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
        goto cleanup;
    }

    sprintf(szServicesIni, "%s\\%s", szSystemDir, "MAPISVC.INF");

    //
    //  Loop through and add items to MAPISVC.INF
    //

    n = 0;

    while(aMbServicesIni[n].lpszSection != NULL)
    {
        LPSTR lpszProp  = aMbServicesIni[n].lpszKey;
        LPSTR lpszValue = aMbServicesIni[n].lpszValue;

        // Switch the property if necessary

        if(lpszProp == NULL)
        {
            sprintf(szPropNum, "%lx", aMbServicesIni[n].ulKey);
            lpszProp = szPropNum;
        }

        // Switch the value if necessary

        if(lpszValue == lpszServerPlaceHolder)
        {
            lpszValue =  lpszServerName;
        }
        else if(lpszValue == lpszObjectPlaceHolder)
        {
            lpszValue = lpszDN;
        }
        else if(lpszValue == lpszDisplayNamePlaceHolder)
        {
            lpszValue = lpszCommonName;
        }
        else if(lpszValue == lpszProfileVersionPlaceHolder)
        {
            lpszValue = szProfileVersion;
        }

        //
        //  Write the item to MAPISVC.INF
        //

        fRet = WritePrivateProfileString(
            aMbServicesIni[n].lpszSection, 
            lpszProp,
            lpszValue,
            szServicesIni);

        if(fRet == FALSE)
        {
            hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
            goto cleanup;
        }

        n++;
    }
    
    // Flush the information

    WritePrivateProfileString(NULL, NULL, NULL, szServicesIni);

    hr = NOERROR;

cleanup:

    GLOBALFREE(lpszDN);

    RETURN(hr);
}

//$--HrCreateGatewayProfile--------------------------------------------------
//  Creates a gateway profile.
// -----------------------------------------------------------------------------
HRESULT HrCreateGatewayProfile(          // RETURNS: return code
	IN LPSTR lpszServiceName,              // service name
	IN LPSTR lpszProfileName)              // profile name
{
    HRESULT        hr             = E_FAIL;
    LPPROFADMIN    lpProfAdmin    = NULL;
    LPSERVICEADMIN lpServiceAdmin = NULL;

    BOOL    fRet                         = FALSE;
    UINT    uRet                         = 0;
    CHAR   szSystemDir[MAX_PATH+1]      = {0};
    CHAR   szServicesIni[MAX_PATH+12+1] = {0}; // 12 = space for "MAPISVC.INF"

	LONG    lRet                         = 0;
	LPSTR  lpszServer                   = NULL;
	LPSTR  lpszSiteDN                   = NULL;
	LPSTR  lpszObjectGuid               = NULL;
    LPSTR  lpszCommonName               = NULL;
	DWORD   dwType                       = 0;
	DWORD   cbOrig                       = 0;
	CHAR    szParametersKey[MAX_PATH+1]  = {0};
	HKEY    hkParameters                 = INVALID_HANDLE_VALUE;

    DEBUGPUBLIC("HrCreateGatewayProfile()\n");

    hr = CHK_HrCreateGatewayProfile(
    	lpszServiceName,
    	lpszProfileName);
    if(FAILED(hr))
        RETURN(hr);

    //
    //  Open the parameters key.
    //

	lRet = _snprintf(
	    szParametersKey,
        MAX_PATH+1,
	    "SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	    lpszServiceName);

    if(lRet < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lRet = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        szParametersKey, 
        0,
        KEY_READ,
        &hkParameters);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
        goto cleanup;
    }

    //
    //  Get the profile parameters
    //

    hr = HrGetRegistryValue(
        hkParameters, "HomeDSA", &dwType, &cbOrig, (LPVOID) &lpszServer);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetRegistryValue(
        hkParameters, "SiteDN", &dwType, &cbOrig, (LPVOID) &lpszSiteDN);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetRegistryValue(
        hkParameters, "ObjectGUID", &dwType, &cbOrig, (LPVOID) &lpszObjectGuid);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if((lpszObjectGuid == NULL) ||
       (lstrcmpi(lpszObjectGuid, OBJECT_GUID_MAIL_GATEWAY)))
    {
        //
        // The object is the directory is not a gateway.
        //

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetRegistryValue(
        hkParameters, "CommonName", &dwType, &cbOrig, (LPVOID) &lpszCommonName);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Connect to Profile Admin interface.
    //

    hr = MAPIAdminProfiles(0, &lpProfAdmin);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    ASSERTERROR(lpProfAdmin != NULL, "NULL lpPropAdmin variable");

    //
    //  Create a profile for the gateway.
    //

    hr = MAPICALL(lpProfAdmin)->CreateProfile(
        lpProfAdmin,
        lpszProfileName,
        NULL,
        0,
        fMapiUnicode);

    if(FAILED(hr))
    {
        // Did it fail because a profile of this name already exists?

        hr = HrMAPIProfileExists(lpProfAdmin, lpszProfileName);

        if(hr != E_ACCESSDENIED)
        {
            hr = HR_LOG(E_FAIL);
        }
        else
        {
            hr = HR_LOG(hr);
        }

        goto cleanup;
    }        

    //
    // Fix MAPISVC.INF to contain the information we want to add to the profile
    //

    hr = HrSetGatewayProfileParameters(
        lpszServer,
        lpszSiteDN,
        lpszCommonName);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Add profile section from MAPISVC.INF
    //

    hr = MAPICALL(lpProfAdmin)->AdminServices(
        lpProfAdmin,
        lpszProfileName,
        "", 
        0,
        0,
        &lpServiceAdmin);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    ASSERTERROR(lpServiceAdmin != NULL, "NULL lpServiceAdmin variable");

    hr = MAPICALL(lpServiceAdmin)->CreateMsgService(
        lpServiceAdmin,
        "MSEMS_EdkGateway",
        "Exchange Access for EDK Gateways",
        0,
        0);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    //  Compute the path to MAPISVC.INF
    //

    uRet = GetSystemDirectory(szSystemDir, MAX_PATH);

    if(uRet == 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    sprintf(szServicesIni, "%s\\%s", szSystemDir, "MAPISVC.INF");

    //
    //  Remove service entry from MAPISVC.INF
    //

    fRet = WritePrivateProfileString(
        TEXT("Services"), 
        TEXT("MSEMS_EdkGateway"),
        NULL,
        szServicesIni);

    if(fRet == FALSE)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
        goto cleanup;
    }

    hr = NOERROR;

cleanup:

	GLOBALFREE(lpszServer);
	GLOBALFREE(lpszSiteDN);
	GLOBALFREE(lpszObjectGuid);
    GLOBALFREE(lpszCommonName);

	FREEHKEY(hkParameters);

    ULRELEASE(lpServiceAdmin);
    ULRELEASE(lpProfAdmin);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrCreateMailboxAgentProfile---------------------------------------------
//  Creates a mailbox agent profile.
// -----------------------------------------------------------------------------
HRESULT HrCreateMailboxAgentProfile(     // RETURNS: return code
	IN LPSTR lpszServiceName,              // service name
	IN LPSTR lpszProfileName)              // profile name
{
    HRESULT        hr             = E_FAIL;
    LPPROFADMIN    lpProfAdmin    = NULL;
    LPSERVICEADMIN lpServiceAdmin = NULL;

    BOOL    fRet                         = FALSE;
    UINT    uRet                         = 0;
    CHAR   szSystemDir[MAX_PATH+1]      = {0};
    CHAR   szServicesIni[MAX_PATH+12+1] = {0}; // 12 = space for "MAPISVC.INF"

	LONG    lRet                         = 0;
	LPSTR  lpszServer                   = NULL;
	LPSTR  lpszSiteDN                   = NULL;
	LPSTR  lpszObjectGuid               = NULL;
    LPSTR  lpszCommonName               = NULL;
	DWORD   dwType                       = 0;
	DWORD   cbOrig                       = 0;
	CHAR    szParametersKey[MAX_PATH]    = {0};
	HKEY    hkParameters                 = INVALID_HANDLE_VALUE;

    DEBUGPUBLIC("HrCreateMailboxAgentProfile()\n");

    hr = CHK_HrCreateMailboxAgentProfile(
    	lpszServiceName,
    	lpszProfileName);
    if(FAILED(hr))
        RETURN(hr);

    //
    //  Open the parameters key.
    //

	lRet = _snprintf(
	    szParametersKey,
        MAX_PATH+1,
	    "SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	    lpszServiceName);

    if(lRet < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lRet = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        szParametersKey, 
        0,
        KEY_READ,
        &hkParameters);

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
        goto cleanup;
    }

    //
    //  Get the profile parameters
    //

    hr = HrGetRegistryValue(
        hkParameters, "HomeDSA", &dwType, &cbOrig, (LPVOID) &lpszServer);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetRegistryValue(
        hkParameters, "SiteDN", &dwType, &cbOrig, (LPVOID) &lpszSiteDN);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetRegistryValue(
        hkParameters, "ObjectGUID", &dwType, &cbOrig, (LPVOID) &lpszObjectGuid);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if((lpszObjectGuid == NULL) ||
       (lstrcmpi(lpszObjectGuid, OBJECT_GUID_MAILBOX_AGENT)))
    {
        //
        // The object is the directory is not a mailbox agent.
        //

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetRegistryValue(
        hkParameters, "CommonName", &dwType, &cbOrig, (LPVOID) &lpszCommonName);

    if(FAILED(hr) || dwType != REG_SZ)
    {
        if(dwType != REG_SZ)
            hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Connect to Profile Admin interface.
    //

    hr = MAPIAdminProfiles(0, &lpProfAdmin);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    ASSERTERROR(lpProfAdmin != NULL, "NULL lpPropAdmin variable");

    //
    //  Create a profile for the gateway.
    //

    hr = MAPICALL(lpProfAdmin)->CreateProfile(
        lpProfAdmin,
        lpszProfileName,
        NULL,
        0,
        fMapiUnicode);

    if(FAILED(hr))
    {
        // Did it fail because a profile of this name already exists?

        hr = HrMAPIProfileExists(lpProfAdmin, lpszProfileName);

        if(hr != E_ACCESSDENIED)
        {
            hr = HR_LOG(E_FAIL);
        }
        else
        {
            hr = HR_LOG(hr);
        }

        goto cleanup;
    }        

    //
    // Fix MAPISVC.INF to contain the stuff we want to add to the profile
    //

    hr = HrSetMailboxProfileParameters(
        lpszServer,
        lpszSiteDN,
        lpszCommonName);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Add profile section from MAPISVC.INF
    //

    hr = MAPICALL(lpProfAdmin)->AdminServices(
        lpProfAdmin,
        lpszProfileName,
        "", 
        0,
        0,
        &lpServiceAdmin);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    ASSERTERROR(lpServiceAdmin != NULL, "NULL lpServiceAdmin variable");

    hr = MAPICALL(lpServiceAdmin)->CreateMsgService(
        lpServiceAdmin,
        "MSEMS_EdkMbAgent",
        "Exchange Access for EDK Mailbox Agents",
        0,
        0);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    //  Compute the path to MAPISVC.INF
    //

    uRet = GetSystemDirectory(szSystemDir, MAX_PATH);

    if(uRet == 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    sprintf(szServicesIni, "%s\\%s", szSystemDir, "MAPISVC.INF");

    //
    //  Remove service entry from MAPISVC.INF
    //

    fRet = WritePrivateProfileString(
        TEXT("Services"), 
        TEXT("MSEMS_EdkMbAgent"),
        NULL,
        szServicesIni);

    if(fRet == FALSE)
    {
        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
        goto cleanup;
    }

    hr = NOERROR;

cleanup:

	GLOBALFREE(lpszServer);
	GLOBALFREE(lpszSiteDN);
	GLOBALFREE(lpszObjectGuid);
    GLOBALFREE(lpszCommonName);

	FREEHKEY(hkParameters);

    ULRELEASE(lpServiceAdmin);
    ULRELEASE(lpProfAdmin);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrRemoveProfile---------------------------------------------------------
//  Removes a profile.
//------------------------------------------------------------------------------
HRESULT HrRemoveProfile(                 // RETURNS: return code
    LPSTR lpszProfileName)                 // profile name
{
    HRESULT     hr          = NOERROR;
    LPPROFADMIN lpProfAdmin = NULL;

    DEBUGPUBLIC("HrRemoveProfile()\n");

    hr = CHK_HrRemoveProfile(
        lpszProfileName);
    if(FAILED(hr))
        RETURN(hr);

    //
    // Connect to Profile Admin interface.
    //

    hr = MAPIAdminProfiles(0, &lpProfAdmin);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    ASSERTERROR(lpProfAdmin != NULL, "NULL lpPropAdmin variable");

    //
    //  Delete a MAPI profile
    //

    hr = MAPICALL(lpProfAdmin)->DeleteProfile(lpProfAdmin, lpszProfileName, 0);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    ULRELEASE(lpProfAdmin);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrMAPIProfileExists---------------------------------------------------------
//  Checks for an existing profile.
// -----------------------------------------------------------------------------
HRESULT HrMAPIProfileExists(             // RETURNS: return code
    IN LPPROFADMIN lpProfAdmin,         // profile admin object
    IN LPSTR      lpszProfileName)     // profile name
{
    HRESULT      hr      = NOERROR;
    HRESULT      hrT     = 0;
    LPMAPITABLE  lpTable = NULL;
    LPSRowSet    lpRows  = NULL;
    LPSPropValue lpProp  = NULL;
    ULONG        i       = 0;
    ULONG        cRows   = 0;

    SizedSPropTagArray(1, rgPropTag) = 
    {
        1,
        {
            PR_DISPLAY_NAME_A
        }
    };

    DEBUGPUBLIC("HrMAPIProfileExists()\n");

    hr = CHK_HrMAPIProfileExists(
        lpProfAdmin,
        lpszProfileName);
    if(FAILED(hr))
        RETURN(hr);

    // Get a table of existing profiles

    hr = MAPICALL(lpProfAdmin)->GetProfileTable(
        lpProfAdmin,
        0,
        &lpTable);

    if(FAILED(hr))
    {
        goto cleanup;
    }
   
	hr = HrQueryAllRows(
	    lpTable,
		(LPSPropTagArray)&rgPropTag,
		NULL,
		NULL,
		0,
		&lpRows);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    cRows = lpRows->cRows;

    // If table is empty then profile doesn't exist

    if (cRows == 0)
    {
        hr = NOERROR;
        goto cleanup;
    }

    // Search rows for the folder in question

    for(i = 0; i < cRows; i++)
    {
        ASSERTERROR(
            lpRows->aRow[i].cValues > 0,
            "Profile row is empty of properties.");

        lpProp = lpRows->aRow[i].lpProps;

        ASSERTERROR(
            lpProp[0].ulPropTag == PR_DISPLAY_NAME_A,
            "Profile row does not contain display name");

        if(lstrcmpiA(lpProp[0].Value.lpszA, lpszProfileName) == 0)
        {
            hr = E_ACCESSDENIED;
            goto cleanup;
        }
    }
    
cleanup:
    
    FREEPROWS(lpRows);

    ULRELEASE(lpTable);

    RETURN(hr);
}
