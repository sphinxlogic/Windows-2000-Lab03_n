// --convdllc.cpp--------------------------------------------------------------
//
// Conversion DLL cache source code.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// ----------------------------------------------------------------------------

#include "convincl.h"
#include "convdllc.chk"

//$--CDllCache::CDllCache()----------------------------------------------------
//
// DESCRIPTION: constructor
//
// INPUT: none
//
// RETURNS; nothing
//
//-----------------------------------------------------------------------------
CDllCache::CDllCache()
{
    DEBUGPRIVATE("CDllCache::CDllCache()\n");

    ZeroMemory(m_rgSDllCache, sizeof(m_rgSDllCache));
}

//$--CDllCache::~CDllCache()----------------------------------------------------
//
// DESCRIPTION: destructor
//
// INPUT: none
//
// RETURNS; nothing
//
//-----------------------------------------------------------------------------
CDllCache::~CDllCache()
{
    UINT            iDll    =   0;      // index into DLL cache
    SDllCache *     pDll    =   NULL;   // current DLL pointer

    DEBUGPRIVATE("CDllCache::~CDllCache()\n");

    // Unload any loaded DLLs
    for ( iDll = 0; iDll < nCachedDlls; iDll++ )
    {
        // get current DLL pointer
        pDll = m_rgSDllCache[iDll];

        // See if its valid
        if ( pDll != NULL )
        {
            // unload the DLL
            ASSERTERROR(pDll->hInst != NULL, "Bad pDll->hInst");
            (VOID)FreeLibrary(pDll->hInst);

            // Free the DLL cache entry
            delete pDll;

            pDll = NULL;    // null out pointer
        }

    }   // end for each cached DLL

}

//$--CDllCache::HrAdd----------------------------------------------------------
//
// DESCRIPTION: Loads DLL and adds it to the cache.
//
// INPUT:       lpwszDllName  --  DLL name
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_OUTOFMEMORY if memory problems.
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CDllCache::HrAdd(
        IN LPWSTR lpwszDllName)     // DLL to add
{
    HRESULT         hr          =   NOERROR;
    SDllCache *     pDllCur     =   NULL;   // current cached DLL pointer
    UINT            iDll        =   0;      // index into DLL cache
    BOOL            fLoaded     =   FALSE;  // TRUE if DLL loaded

    DEBUGPRIVATE("CDllCache::HrAdd()\n");

    // check input parameters           
    hr = CHK_CDllCache_HrAdd(lpwszDllName);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Find next empty space in the DLL cache
    for ( iDll = 0; iDll < nCachedDlls; iDll++ )
    {
        pDllCur = m_rgSDllCache[iDll];

        if ( pDllCur == NULL )
        {
            // found an place for this DLL.
            pDllCur = new SDllCache;    // allocate new cache entry

            if ( pDllCur == NULL )
            {
                hr = HR_LOG(E_OUTOFMEMORY);

                goto cleanup;
            }

            // fill in DLL entry information.
            lstrcpyW(pDllCur->lpwszName, lpwszDllName);  // copy DLL name

            // Load DLL
            pDllCur->hInst = LoadLibraryW(lpwszDllName);

            if ( pDllCur->hInst == NULL )
            {
                hr = HR_LOG(E_FAIL);

                goto cleanup;
            }

            // Save DLL entry information in the cache.
            m_rgSDllCache[iDll] = pDllCur;

            fLoaded = TRUE; // DLL is now loaded

            break;

        }   // end if found space

        // Otherwise, make sure that this DLL isn't already loaded.
        else if ( lstrcmpiW(pDllCur->lpwszName, lpwszDllName) == 0 )
        {
            // Dll already here.  
            ASSERTERROR(pDllCur->hInst != NULL, "Bad pDllCur->hInst");

            fLoaded = TRUE;

            // We are done!
            break;
        }
    }   // end for

    // handle case where can't load DLL
    if ( fLoaded == FALSE )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

cleanup:

    RETURN(hr);

}

//$--CDllCache::HrFind------------------------------------------------
//
// DESCRIPTION: Finds instance handle of DLL in cache.
//
// INPUT:       lpwszDllName  --  DLL name
//
// OUTPUT:      phInst  --  pointer to DLL instance handle
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT CDllCache::HrFind(
        IN LPWSTR lpwszDllName,     // DLL to find
        OUT HINSTANCE * phInst)     // pointer to DLL instance handle
{
    HRESULT         hr          =   NOERROR;
    SDllCache *     pDllCur     =   NULL;   // current cached DLL pointer
    UINT            iDll        =   0;      // index into DLL cache
    BOOL            fFound      =   FALSE;  // TRUE if DLL is currently cached

    DEBUGPRIVATE("CDllCache::HrFind()\n");

    // check input parameters           
    hr = CHK_CDllCache_HrFind(lpwszDllName, phInst);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // intialize output parameter
    *phInst = NULL;

    // See if this DLL is already loaded and determine the index
    // of least used DLL in cache
    for ( iDll = 0; iDll < nCachedDlls; iDll++ )
    {
        // get pointer to current DLL.
        pDllCur = m_rgSDllCache[iDll];

        // See if it is a valid pointer
        if ( pDllCur == NULL )
        {
            // No more cached DLLs
            break;
        }

        // See if this DLL is already loaded
        if ( lstrcmpiW(lpwszDllName, pDllCur->lpwszName) == 0 )
        {
            // found DLL
            fFound = TRUE;

            // Succeeded.  
            // Set our output variable
            *phInst = pDllCur->hInst;

            // done
            break;
        }
    }   // end for each DLL in cache

    // See if DLL was found
    if ( fFound == FALSE )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;

    }   // end if DLL not loaded.

cleanup:

    RETURN(hr);

}
