// --convdlle.cpp---------------------------------------------------------------
// 
// Defines an entry point to a conversion DLL.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convdlle.chk"

//$--CDllEntryPoint::CDllEntryPoint---------------------------------------------
//
//  DESCRIPTION: CDllEntryPoint class constructor
//
//  INPUT:  none
//
//  RETURNS:    nothing
//
//------------------------------------------------------------------------------
CDllEntryPoint::CDllEntryPoint()
{ 
    DEBUGPRIVATE("CDllEntryPoint::CDllEntryPoint()\n");

    m_nRefs = 1;

    m_pszDllName    = NULL; 
    m_pszEntryPoint = NULL; 
    m_pszGwPoint    = NULL; 
    m_pszOptions    = NULL;
}

//$--CDllEntryPoint::~CDllEntryPoint--------------------------------------------
//
//  DESCRIPTION: CDllEntryPoint class destructor.
//
//  INPUT:  none
//
//  RETURNS:    nothing
//
//------------------------------------------------------------------------------
CDllEntryPoint::~CDllEntryPoint() 
{
    DEBUGPRIVATE("CDllEntryPoint::~CDllEntryPoint()\n");

    // consistency checking
    ASSERTERROR(m_nRefs == 0,"ZERO m_nRefs variable");

    EDKFree();
}

//$--CDllEntryPoint::Release----------------------------------------------------
//
// DESCRIPTION: Decrements CDllEntryPoint instance reference count.  Destroys
//              object when reference count goes to zero.
//
// INPUT:   none
//
// RETURNS: nothing
//
//------------------------------------------------------------------------------
void CDllEntryPoint::Release()
{
    DEBUGPRIVATE("CDllEntryPoint::Release()");

    if(--m_nRefs <= 0)
        delete this;
}

//$--CDllEntryPoint::HrEDKSet------------------------------------------------------
//
//  DESCRIPTION: Initialize a conversion entry point values
//
//  INPUT:  pszDllName  --  Dll name
//          pszEntryPoint   --  entry point function name
//          pszGwPoint  --
//          pszOptions  --  options
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//
//------------------------------------------------------------------------------
HRESULT CDllEntryPoint::HrEDKSet(   // RETURNS: HRESULT
    IN LPCWSTR pszDllName,          // copied
    IN LPCWSTR pszEntryPoint,       // entry point function name
    IN LPCWSTR pszGwPoint,
    IN LPCWSTR pszOptions)          // options
{
    HRESULT hr  =   NOERROR;        // return code

    DEBUGPRIVATE("CDllEntryPoint::HrEDKSet()\n");

    // check input parameters
    hr = CHK_CDllEntryPoint_HrEDKSet(pszDllName, pszEntryPoint, pszGwPoint, pszOptions);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    hr = HrStrWToStrW(pszDllName, &m_pszDllName);

    if ( FAILED(hr) )
    {
        EDKFree();

        goto cleanup;
    } 

    // Remember m_pszEntryPoint is ANSI string

    hr = HrStrWToStrA(pszEntryPoint, &m_pszEntryPoint);

    if ( FAILED(hr) )
    {
        EDKFree();

        goto cleanup;
    }

    hr = HrStrWToStrW(pszGwPoint, &m_pszGwPoint);

    if ( FAILED(hr) )
    {
        EDKFree();

        goto cleanup;
    }

    hr = HrStrWToStrW(pszOptions, &m_pszOptions);

    if ( FAILED(hr) )
    {
        EDKFree();

        goto cleanup;
    }

    ASSERTERROR(m_pszDllName != NULL, "Bad m_pszDllName");
    ASSERTERROR(m_pszEntryPoint != NULL, "Bad m_pszEntryPoint");
    ASSERTERROR(m_pszGwPoint != NULL, "Bad m_pszGwPoint");
    
cleanup:

    RETURN(hr);

}

//$--CDllEntryPoint::EDKFree-------------------------------------------------------
//
// DESCRIPTION: Common dynamic memory free.
//
// INPUT:   none
//
// RETURNS: void
//
//------------------------------------------------------------------------------
void CDllEntryPoint::EDKFree() // RETURNS: void
{
    DEBUGPRIVATE("CDllEntryPoint::EDKFree()\n");

    MAPIFREEBUFFER(m_pszDllName);
    MAPIFREEBUFFER(m_pszEntryPoint);
    MAPIFREEBUFFER(m_pszGwPoint);
    MAPIFREEBUFFER(m_pszOptions);
}

//$--CDllEntryPoint::EDKDump-------------------------------------------------------
//
// DESCRIPTION: dump class contents.
//
// INPUT:   none
//
// RETURNS: void
//
//------------------------------------------------------------------------------
void CDllEntryPoint::EDKDump() // RETURNS: void
{
    // _tprintf(TEXT("  Dll: %ls\n  Ept: %hs\n  Gtw: %ls\n  Opt: %ls\n"),
    //              m_pszDllName, m_pszEntryPoint, m_pszGwPoint, m_pszOptions );
}
