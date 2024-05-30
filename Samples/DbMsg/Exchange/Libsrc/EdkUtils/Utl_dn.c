// --UTL_CLI.c------------------------------------------------------------------
//
// Utilities for retrieving distinguished names from Exchange server
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#include "edk.h"
#include "utl_dn.chk"

//$--HrGetMailboxDN----------------------------------------------------------
//  Retrieves mailbox distinguished name from the current session object.
//  Example output: /O=Enterprise/OU=Site/CN=Recipients/CN=MailboxName
// -----------------------------------------------------------------------------
HRESULT HrGetMailboxDN(
    IN  LPMAPISESSION lphSession,       // current session
    OUT LPSTR *ppszMailboxDN)           // distinguished name of mailbox.
{
    HRESULT         hr              = NOERROR;
    LPMAPIPROP      lpSessionProps  = NULL; 
    LPSPropValue    lpEmailAddress  = NULL;
    ULONG           cProps          = 0L;

    static SPropTagArray PropEmailAddress = { 1L, { PR_EMAIL_ADDRESS_A}};

    DEBUGPUBLIC( "HrGetMailboxDN()");

    hr = CHK_HrGetMailboxDN( lphSession, ppszMailboxDN);
    if( FAILED( hr))
        RETURN( hr);

    hr = HrOpenSessionObject( lphSession, &lpSessionProps);
    if( FAILED( hr))
        goto cleanup;

    hr = MAPICALL( lpSessionProps)->GetProps( lpSessionProps,
        &PropEmailAddress,
        0L,
        &cProps,
        &lpEmailAddress);
    if( FAILED( hr) || hr == MAPI_W_ERRORS_RETURNED)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    ASSERTERROR( cProps == 1, "Unexpected number of props returned!");
    ASSERTERROR( lpEmailAddress != NULL, "Invalid EmailAddress prop");

    hr = MAPIAllocateBuffer( cbStrLenA( lpEmailAddress->Value.lpszA), (PVOID*)ppszMailboxDN);
    if( FAILED( hr))
    {
        hr = HR_LOG( E_OUTOFMEMORY);
        goto cleanup;
    }

    lstrcpyA( *ppszMailboxDN, lpEmailAddress->Value.lpszA);

cleanup:
    MAPIFREEBUFFER( lpEmailAddress);

    ULRELEASE( lpSessionProps);

    RETURN( hr);
}

//$--HrGetServerDN----------------------------------------------------------
//  Retrieves server distinguished name from the current session object.
//  Example output: /O=Enterprise/OU=Site/CN=Servers/CN=ServerName/CN=NULL
// -----------------------------------------------------------------------------
HRESULT HrGetServerDN(
    IN  LPMAPISESSION lphSession,       // current session
    OUT LPSTR *ppszServerDN)            // distinguished name of server. 
{
    HRESULT         hr              = NOERROR;
    LPMAPIPROP      lpSessionProps  = NULL; 
    LPSPropValue    lpHomeMTA       = NULL;
    ULONG           cbDN            = 0L;
    ULONG           cProps          = 0L;
    LPSTR           lpLastCN        = NULL;

    static SPropTagArray PropHomeMTA = { 1L, { PR_EMS_AB_HOME_MTA_A}};

    DEBUGPUBLIC( "HrGetServerDN()");
																							  
    hr = CHK_HrGetServerDN( lphSession, ppszServerDN);
    if( FAILED( hr))
        RETURN( hr);

    hr = HrOpenSessionObject( lphSession, &lpSessionProps);
    if( FAILED( hr))
        goto cleanup;

    hr = MAPICALL( lpSessionProps)->GetProps( lpSessionProps,
        &PropHomeMTA,
        0L,
        &cProps,
        &lpHomeMTA);
    if( FAILED( hr) || hr == MAPI_W_ERRORS_RETURNED)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    ASSERTERROR( cProps == 1, "Unexpected number of props returned!");
    ASSERTERROR( lpHomeMTA != NULL, "Invalid HomeMTA prop");

    // Search for last "/cn=" and ignore it when copying string
    lpLastCN = strrchr( lpHomeMTA->Value.lpszA, '/');
    if( lpLastCN == NULL ||
        _strnicmp( lpLastCN, "/cn=", 4) != 0)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    cbDN = lpLastCN - lpHomeMTA->Value.lpszA;

    hr = MAPIAllocateBuffer( cbDN + 1, (PVOID*)ppszServerDN);
    if( FAILED( hr))
    {
        hr = HR_LOG( E_OUTOFMEMORY);
        goto cleanup;
    }

    strncpy( *ppszServerDN, lpHomeMTA->Value.lpszA, cbDN);
    (*ppszServerDN)[cbDN] = '\0';

cleanup:
    MAPIFREEBUFFER( lpHomeMTA);

    ULRELEASE( lpSessionProps);

    RETURN( hr);
}

