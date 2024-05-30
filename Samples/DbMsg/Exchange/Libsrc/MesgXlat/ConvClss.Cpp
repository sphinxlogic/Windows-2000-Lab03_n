// --convclss.cpp---------------------------------------------------------------
// 
// Class that represents conversion class name/list info.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "convincl.h"
#include "convclss.chk"

//$--CClassName::CClassName-----------------------------------------------------
//
//  DESCRIPTION: Initialize the conversion registry object constructor.
//
//  INPUT:  none
//
//  RETURNS:    nothing
//
//------------------------------------------------------------------------------
CClassName::CClassName() 
{ 
    DEBUGPRIVATE("CClassName::CClassName()\n");

    m_pszClassName = NULL;
    m_pEntryPoint = NULL;
    m_pcnNext = NULL; 
}

//$--CClassName::~CClassName----------------------------------------------------
//
// DESCRIPTION: CClassName destructor
//
// INPUT:   none
//
// RETURNS: nothing
//
//------------------------------------------------------------------------------
CClassName::~CClassName() 
{
    DEBUGPRIVATE("CClassName::~CClassName()\n");

    if(m_pEntryPoint != NULL)
    {
        m_pEntryPoint->Release();
    }

    MAPIFREEBUFFER(m_pszClassName);
}

//$--CClassName::HrEDKSet----------------------------------------------------------
//
//  DESCRIPTION: Initialize the conversion registry object.
//
//  INPUT:  pszClassName    --  class name
//          pEntryPoint --  entry point information
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT CClassName::HrEDKSet(               // RETURNS: HRESULT
    IN LPCWSTR pszClassName,                // class name.      (Assigned)
    IN CDllEntryPoint * pEntryPoint )       // entry point info (Copied)
                                            //  reference count increased internally.
{
    HRESULT  hr  =   NOERROR;    // return code

    DEBUGPRIVATE("CClassName::HrEDKSet()\n");

    // check input parameters
    hr = CHK_CClassName_HrEDKSet(pszClassName, pEntryPoint);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    m_pEntryPoint = pEntryPoint;

    pEntryPoint->AddRef();

    hr = HrStrWToStrW(pszClassName, &m_pszClassName);

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    ASSERTERROR(m_pszClassName != NULL, "Bad m_pszClassName");

cleanup:

    RETURN(hr);
}

//$--CClassName::EDKDump-----------------------------------------------------------
//
// DESCRIPTION: dump the class contents.
//
// INPUT:   none
//
// RETURNS: void
//
//------------------------------------------------------------------------------
void CClassName::EDKDump() 
{
    DEBUGPRIVATE("CClassName::EDKDump()\n");

    // _tprintf(TEXT(" Class: %ls\n"), m_pszClassName );

    m_pEntryPoint->EDKDump();
}
