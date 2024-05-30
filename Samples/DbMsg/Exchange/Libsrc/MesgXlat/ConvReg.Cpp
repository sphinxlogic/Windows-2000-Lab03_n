// --convreg.cpp----------------------------------------------------------------
// 
// Conversion registry code.
// Locates converters that are stored in DLLs from info stored in the 
// registry.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convreg.chk"

//
//  String constants used to find registry keys.
//
static const LPWSTR pszMAPIConvKey = L"SOFTWARE\\Classes\\MAPI Conversions";

//
//  Conversion KEY values.
//
static const LPWSTR pszClassesKey =  L"Classes";      
static const LPWSTR pszPointKey =    L"Point";
static const LPWSTR pszOptionsKey =  L"Options";

//
// limiting constants.
//
static const int cMaxKeyNameSize = 100;                    // maximum conversion key size.

// Static variables shared by all instances
HKEY CEDKConvReg::ms_hkConversions             = NULL;     // handle to conversion key.
CClassName * CEDKConvReg::ms_pcnClasses        = NULL;     // common cache of conversion info
CDllCache * CEDKConvReg::ms_pDllCache          = NULL;     // common DLL cache

//$--CEDKConvReg::CEDKConvReg------------------------------------------
//
//  DESCRIPTION:     CEDKConvReg class constructor
//
//  INPUT:  none
//
//  RETURNS:    nothing
//
//---------------------------------------------------------------------
CEDKConvReg::CEDKConvReg()
{
    DEBUGPRIVATE("CEDKConvReg::CEDKConvReg()\n");
}

//$--CEDKConvReg::~CEDKConvReg-----------------------------------------
//
//  DESCRIPTION: CEDKConvReg class destructor
//
//  INPUT:   none
//
//  RETURNS:    nothing
//
//---------------------------------------------------------------------
CEDKConvReg::~CEDKConvReg()
{
    DEBUGPRIVATE("CEDKConvReg::~CEDKConvReg()\n");
}

//$--CEDKConvReg::HrEDKInitialize-----------------------------------------
//
//  DESCRIPTION: Perform loading part of Conversion registry initialization.
//
//  INPUT:  none
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_FAIL otherwise
//
//---------------------------------------------------------------------
HRESULT CEDKConvReg::HrEDKInitialize()
{
    HRESULT hr  =   NOERROR;    //  return code
    LONG lRet = ERROR_SUCCESS;  // win32 return code

    DEBUGPRIVATE("CEDKConvReg::HrEDKInitialize()\n");

    //
    //  Skip initialization if it has already been done.
    //
    if(ms_pcnClasses != NULL)    
    {        
        goto cleanup;
    }

    // consistency checking
    ASSERTERROR(ms_hkConversions == NULL,"NULL ms_hkConversions variable");

    // Create the DLL cache.
    ms_pDllCache = new CDllCache;

    if ( ms_pDllCache == NULL )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    //
    //  Open key that contains all conversions.
    //
    lRet = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        pszMAPIConvKey, 
        0,
        KEY_READ,
        &ms_hkConversions);    

    if(lRet != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    //
    //  Parse the contented keys and values.
    //
    hr = HrEDKParseConfiguration();
    
cleanup:

    RETURN(hr);

}

//$--CEDKConvReg::HrEDKParseConfiguration---------------------------------
//
//  DESCRIPTION: Parse the list of all conversions from the registry conversion keys
//
//  INPUT:  none
//
//  RETURNS:    HRESULT --  NOERROR if no error successful,
//                          EDK_E_END_OF_FILE if syntax error
//                          E_FAIL otherwise
//
//---------------------------------------------------------------------
HRESULT CEDKConvReg::HrEDKParseConfiguration()  // RETURNS: HRESULT
{
    HRESULT hr        = NOERROR;    // return code
    LONG lRet         = 0;
    HKEY hkDll        = NULL;
    HKEY hkEntryPoint = NULL;

    DEBUGPRIVATE("CEDKConvReg::HrEDKParseConfiguration()\n");

    // consistency checking
    ASSERTERROR(ms_hkConversions != NULL,"NULL ms_hkConversions parameter");

    ASSERTERROR(ms_pcnClasses == NULL,"NULL ms_pcnClasses parameter");

    m_bSyntaxError = FALSE;

    //
    // Enumerate all conversion DLLs.  These are sub-keys of hkConversions
    // At the same time, load each DLL found and add to the DLL cache.
    //

    UINT    iDll    =   0;  // DLL index

    for(iDll = 0;;iDll++)
    {
        FILETIME ftDummy                  = {0};
        WCHAR    szDll[cMaxKeyNameSize+1] = {0};
        DWORD    dwDummy                  = cMaxKeyNameSize;

        // DLL loop bounds
        ASSERTERROR(iDll >= 0 && iDll < 1024,"iDll out of bounds");

        //
        //  Get the next key
        //
        lRet = RegEnumKeyExW(
            ms_hkConversions, iDll, szDll, &dwDummy, NULL, NULL, NULL, &ftDummy);

        if(lRet == ERROR_NO_MORE_ITEMS)
            break;

        if(lRet != ERROR_SUCCESS)
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        //
        //  Open the conversion DLL key
        //
        lRet = RegOpenKeyExW(ms_hkConversions, szDll, 0L, KEY_READ, &hkDll);

        if(lRet != ERROR_SUCCESS)
        {
            hr = HR_LOG(E_FAIL);

            goto cleanup;
        }

        // Add the conversion DLL to the global DLL cache. 
        // (This also loads the DLL.)
        hr = ms_pDllCache->HrAdd(
            szDll);     // DLL name to load and add

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        //
        // enumerate all entry point keys contained in the DLL key.
        //
        int iEntryPoint = 0;

        for (iEntryPoint = 0;;iEntryPoint++)
        {
            WCHAR szEntryPoint[cMaxKeyNameSize+1] = {0};

            // Entry point loop bounds
            ASSERTERROR(
                iEntryPoint >= 0 && iEntryPoint < 1024,
                "iEntryPoint out of bounds");
    
            dwDummy = cMaxKeyNameSize;

            lRet = RegEnumKeyExW(
                hkDll, iEntryPoint, szEntryPoint, &dwDummy, NULL, NULL, NULL, &ftDummy);

            if(lRet == ERROR_NO_MORE_ITEMS)
                break;

            if(lRet != ERROR_SUCCESS)
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            //
            //  Open the entry point
            //
            lRet = RegOpenKeyExW(hkDll, szEntryPoint, 0L, KEY_READ, &hkEntryPoint);

            if(lRet != ERROR_SUCCESS)
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            //
            //  Get values and put them in the in-memory structure.
            //
            hr = HrEDKRecordValues(hkEntryPoint, szDll, szEntryPoint);

            if(hr == EDK_E_END_OF_FILE)
            {
                // Error reported by HrEDKRecordValues
                hr = HR_LOG(NOERROR);   // not a critical error
            }

            if(FAILED(hr))
            {
                goto cleanup;
            }


            //
            //  Close entry point key.
            //
            REGCLOSEKEY(hkEntryPoint);
        }

        if(!iEntryPoint)
        {
            EDKSyntaxError(
                szDll,
                NULL,
                NULL,
                NULL,
                NULL);
        }

        //
        //  Close DLL key.
        //
        REGCLOSEKEY(hkDll);
    }

    if(!iDll)
    {
        EDKSyntaxError(
            NULL,
            NULL,
            NULL,
            NULL,
            NULL);
    }

cleanup:

    REGCLOSEKEY(hkDll);
    REGCLOSEKEY(hkEntryPoint);

    if(m_bSyntaxError)
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);
    }

    ASSERTERROR(hkDll == NULL,"NULL hkDll variable");

    ASSERTERROR(hkEntryPoint == NULL,"NULL hkEntryPoint variable");
       
    RETURN(hr);

}

//$--CEDKConvReg::HrEDKRecordValues---------------------------------------
//
//  DESCRIPTION: We have found an entry point.  Get its details and record them in
//  the in-memory list of classes/entry points.
//
//  INPUT:  hkEntryPoint    --  entry point key
//          pszDll  --  DLL name
//          pszEntryPoint   --  name of DLL's entry point function
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          EDK_E_END_OF_FILE if bad syntax,
//                          E_FAIL otherwise
//
//---------------------------------------------------------------------
HRESULT CEDKConvReg::HrEDKRecordValues(     // RETURN:  HRESULT
                                    //   if a required value is not present
                                    //   SyntaxError() is also called.
    IN HKEY const hkEntryPoint,     // Entry point key that contain details
    IN LPCWSTR pszDll,              // dll containing entry point.
    IN LPCWSTR pszEntryPoint)       // name of entry point in dll.
{
    HRESULT        hr             = NOERROR;    // return code
    PVOID          pClasses       = NULL;
    PVOID          pPoint         = NULL;
    PVOID          pOptions       = NULL;
    DWORD          cbSize         = 0;
    DWORD          nType          = 0;
    LPCWSTR        pszClassName   = NULL;
    CDllEntryPoint *pEntryPoint   = NULL;

    DEBUGPRIVATE("CEDKConvReg::HrEDKRecordValues()\n");

    // check input parameters
    hr = CHK_CEDKConvReg_HrEDKRecordValues(hkEntryPoint, pszDll, 
                                           pszEntryPoint);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    //
    //  Get the key values.
    //

    //
    //  Supported classes.
    //
    hr = HrGetArbSizeValue(hkEntryPoint, pszClassesKey, 
                              pClasses, cbSize, nType);

    if(hr == EDK_E_END_OF_FILE || nType != REG_MULTI_SZ)
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);
    }
    
    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    //  Conversion point.
    //
    hr = HrGetArbSizeValue(hkEntryPoint, pszPointKey, 
                              pPoint, cbSize, nType);

    if(hr == EDK_E_END_OF_FILE || nType != REG_SZ)
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);
    }
    
    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Options.
    //
    hr = HrGetArbSizeValue(hkEntryPoint, pszOptionsKey, 
                              pOptions, cbSize, nType);

    // ignore absent value.
    if(SUCCEEDED(hr) && nType != REG_SZ)
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);

        goto cleanup;
    }
    else
    {
        hr = HR_LOG(NOERROR);
    }

    //
    //  Setup pointer to first class name.
    //
    pszClassName = (LPCWSTR)pClasses;

    ASSERTERROR(pszClassName != NULL, "Bad pszClassName");
    ASSERTERROR(pPoint != NULL, "Bad pPoint");

    if( (*pszClassName == 0) || (*((LPWSTR)pPoint) == 0) )
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);

        goto cleanup;
    }

    //
    //  Create a new entry point.
    //

    pEntryPoint = new CDllEntryPoint;

    if(pEntryPoint == NULL)
    {
        goto cleanup;
    }

    hr = pEntryPoint->HrEDKSet(
        pszDll, (LPCWSTR)pszEntryPoint, (LPCWSTR)pPoint, (LPWSTR)pOptions);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    //
    //  For each class in pClasses
    //

    for(; *pszClassName; pszClassName += lstrlenW(pszClassName)+1)
    {
        //
        //  Make a new class structre
        //

        CClassName * pNewClass = new CClassName;

        if(pNewClass == NULL)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;    
        }    

        hr = pNewClass->HrEDKSet(pszClassName, pEntryPoint);

        if(FAILED(hr))
        {
            delete pNewClass;
            goto cleanup;
        }

        //
        // insert class in list of classes.
        //

        CClassName ** ppcnTmp = &ms_pcnClasses;

        for(;;)
        {
            ASSERTERROR(ppcnTmp != NULL,"NULL ppcnTmp variable");

            if(*ppcnTmp == NULL)
                break;

            ASSERTERROR(*ppcnTmp != NULL,"NULL *ppcnTmp variable");

            if(pNewClass->cNameLength() >= (*ppcnTmp)->cNameLength())
                break;            

            ppcnTmp= &((*ppcnTmp)->m_pcnNext);
        }

        pNewClass->m_pcnNext = *ppcnTmp;

        *ppcnTmp = pNewClass;
    }

cleanup:

    if ( hr == EDK_E_END_OF_FILE )
    {
        // report syntax error to event log
        EDKSyntaxError(
                (LPWSTR) pszDll,
                (LPWSTR) pszEntryPoint,
                (LPWSTR) pClasses,
                (LPWSTR) pOptions,
                (LPWSTR) pPoint);
    }

    MAPIFREEBUFFER(pClasses);
    MAPIFREEBUFFER(pPoint);
    MAPIFREEBUFFER(pOptions);

    if(pEntryPoint != NULL)
    {
        pEntryPoint->Release();
        pEntryPoint = NULL;
    }

    RETURN(hr);
}


//$--CEDKConvReg::HrEDKSearchOpen---------------------------------------------
//
//  DESCRIPTION: Initiate the search for candidate converters.
//  Call HrEDKSearchNext to find subsequent converters.
//  Must call SearchClose after finished, even if errors
//  are returned.  
//
//  INPUT:  pszConversionPoint  --  what conversion point
//          pszContentClass --  what class
//
//  OUTPUT: pep --  hold candidate conversion if found
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT CEDKConvReg::HrEDKSearchOpen(       // returns HRESULT
    IN LPCWSTR pszConversionPoint,          // what conversion point.
    IN LPCWSTR pszContentClass,             // what class
    OUT CDllEntryPoint * &pep)              // holds candidate if found.
{
    HRESULT hr  =   NOERROR;    // return code

    DEBUGPRIVATE("CEDKConvReg::HrEDKSearchOpen()\n");

    // check for bad input
    hr = CHK_CEDKConvReg_HrEDKSearchOpen(pszConversionPoint, 
                                         pszContentClass, pep);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    m_ppep = &pep;
    m_pszConversionPoint = pszConversionPoint;
    m_pszContentClass = pszContentClass;
    m_pcnCurrentClass = ms_pcnClasses;

    RETURN(hr);

}

//$--CEDKConvReg::HrEDKSearchNext-----------------------------------------
//
//  DESCRIPTION: Find the next candidate conversion.  HrEDKSearchOpen must be called 
//  first.  SearchClose must be called after.  EDK_E_END_OF_FILE indicates that
//  no candidates can be found.
//
//  INPUT:  none
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          EDK_E_END_OF_FILE is no candidates found,
//                          E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT CEDKConvReg::HrEDKSearchNext()      // RETURNS: HRESULT
{
    HRESULT             hr      =   NOERROR;    // return code
    CDllEntryPoint *    pdepTmp =   NULL;       // temporary conversion DLL
    HRESULT             hrT     =   NOERROR;    // temporary return code
    BOOL                fFound  =   FALSE;      // TRUE if found DLL

    DEBUGPRIVATE("CEDKConvReg::HrEDKSearchNext()\n");

    //
    //  Search remaining conversions.
    //
    while (m_pcnCurrentClass != NULL)
    {       
        CClassName * pcnTmp = m_pcnCurrentClass;
        m_pcnCurrentClass = m_pcnCurrentClass->m_pcnNext;

        pdepTmp = pcnTmp->pEntryPoint();

        hrT = HrStrstriW(
                    pcnTmp->pszClassName(),     // substring
                    m_pszContentClass);         // message class

        if ( FAILED(hrT) )
        {
            // not a match,
            // continue.
            continue;
        }

        // Class names "match"
        // Check conversion pointer for a match.
        LPWSTR lpszCurPoint = pdepTmp->pszGwPoint();
        if ( lstrcmpiW(m_pszConversionPoint, lpszCurPoint) == 0 )
        {
            //
            // found a match, break;
            //
            fFound = TRUE;

            break;
        }
    }

    // Check to make sure that conversion was found.
    if ( (fFound == FALSE) || (pdepTmp == NULL) )
    {
        hr = HR_LOG(EDK_E_END_OF_FILE);

        goto cleanup;
    }

    *m_ppep = pdepTmp;

cleanup:

    RETURN(hr);

}

//$--CEDKConvReg::EDKSearchClose------------------------------------------
//
//  DESCRIPTION: must be called after HrEDKSearchOpen.
//
//  INPUT:  none
//
//  RETURNS:    void
//
//---------------------------------------------------------------------
void CEDKConvReg::EDKSearchClose() // RETURNS: void
{
    DEBUGPRIVATE("CEDKConvReg::EDKSearchClose()\n");

}

//$--CEDKConvReg::EDKFree-------------------------------------------------
//
//  DESCRIPTION: internal routine to free conversion structure.
//
//  INPUT:  none
//
//  RETURNS:    void
//
//---------------------------------------------------------------------
void CEDKConvReg::EDKFree()    // RETURNS: void
{
    DEBUGPRIVATE("CEDKConvReg::EDKFree()\n");

    CClassName * pcnTmp = ms_pcnClasses;

    while (pcnTmp != NULL) 
    {
        CClassName * pcnNext = pcnTmp->m_pcnNext;

        delete pcnTmp;

        pcnTmp = pcnNext;
    }
    ms_pcnClasses = NULL;

    REGCLOSEKEY(ms_hkConversions);

    // delete the DLL cache.  (This also unloads the DLLs previously
    // loaded.
    delete ms_pDllCache;

    ms_pDllCache = NULL;

}


//$--CEDKConvReg::EDKDumpMappings-----------------------------------------
//
//  DESCRIPTION: debug routine to display mappings.
//
//  INPUT:  none
//
//  RETURNS:    void
//
//---------------------------------------------------------------------
void CEDKConvReg::EDKDumpMappings()     // RETURNS void
{
    DEBUGPRIVATE("CEDKConvReg::EDKDumpMappings()\n");

    CClassName * pcnTmp = ms_pcnClasses;

    // incompatabile with WINWRAP _tprintf(TEXT("Dump of mappings...\n"));
    while (pcnTmp != NULL) 
    {
        pcnTmp->EDKDump();

        pcnTmp = pcnTmp->m_pcnNext;
    }
    
}

//$--CEDKConvReg::EDKSyntaxError------------------------------------------
//
//  DESCRIPTION: debug routine called whenever a syntax error is detected.
//
//  INPUT:      pszDll  --  DLL key name
//              pszEntryPoint   -- entry point name
//              pszClass    --  message class key name
//              pszOptions  --  conversion options key name
//              pszPoint    --  conversion point key name
//
//  RETURNS:    VOID
//
//---------------------------------------------------------------------
VOID CEDKConvReg::EDKSyntaxError(         // RETURNS: VOID
        IN LPWSTR   pszDll,     // DLL name
        IN LPWSTR   pszEntryPoint,  // entry point name
        IN LPWSTR   pszClass,   // message class
        IN LPWSTR   pszOptions, // conversion options
        IN LPWSTR   pszPoint)   // conversion point
{
    LPWSTR  lpszBlank   =   L"";    // blank string

    LPWSTR  lpszDllName =   lpszBlank;   // conversion DLL name
    LPWSTR  lpszEntry   =   lpszBlank;   // entry point name
    LPWSTR  lpszPoint   =   lpszBlank;   // conversion point
    LPWSTR  lpszClass   =   lpszBlank;   // message class
    LPWSTR  lpszOptions =   lpszBlank;   // options

    DEBUGPRIVATE("CEDKConvReg::EDKSyntaxError()\n");

    // No check function for this routine.  It is an event
    // logging routine and all parameters may be NULL.

    m_bSyntaxError = TRUE;

    if ( pszDll != NULL )
    {
        lpszDllName = pszDll;
    }

    if ( pszEntryPoint != NULL )
    {
        lpszEntry = pszEntryPoint;
    }

    if ( pszPoint != NULL )
    {
        lpszPoint = pszPoint;
    }

    if ( pszClass != NULL )
    {
        lpszClass = pszClass;
    }

    if ( pszOptions != NULL )
    {
        lpszOptions = pszOptions;
    }

    // Log event to the event log.
    EventLogMsgW(
            MESGXLAT_CNV_BAD_SYNTAX,    // event identfier
            5,                          // # of strings
            lpszDllName,                // string 1
            lpszEntry,
            lpszClass,               
            lpszOptions,
            lpszPoint,         
            0);                         // # of error codes

}
