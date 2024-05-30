// --MBLOGON.c------------------------------------------------------------------
//
//  Privileged Access to logon and off of any message store.
//  
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "edkguid.h"
#include "mblogon.chk"

//$--HrMailboxLogon------------------------------------------------------
// Logon to a mailbox.  Before calling this function do the following:
//  1) Create a profile that has Exchange administrator privileges.
//  2) Logon to Exchange using this profile.
//  3) Open the mailbox using the Message Store DN and Mailbox DN.
//
// This version of the function needs the server and mailbox names to be
// in the form of distinguished names.  They would look something like this:
//       /O=<Organization>/OU=<Site>/CN=Servers/CN=<ServerName>/CN=NULL
//       /O=<Organization>/OU=<Site>/CN=<Container>/CN=<MailboxName>
// where items in <brackets> would need to be set to appropriate values
// 
// Note1: The message store DN is nearly identical to the server DN, except
// for the addition of a trailing '/CN=' part.  This part is required although
// its actual value is ignored.
//
// Note2: A NULL lpszMailboxDN indicates the public store should be opened.
// -----------------------------------------------------------------------------

HRESULT HrMailboxLogon(
    IN  LPMAPISESSION   lplhSession,      // MAPI session handle
    IN  LPMDB           lpMDB,            // open message store
    IN  LPSTR           lpszMsgStoreDN,   // desired message store DN
    IN  LPSTR           lpszMailboxDN,    // desired mailbox DN or NULL
    OUT LPMDB           *lppMailboxMDB)   // ptr to mailbox message store ptr
{
    HRESULT                 hr              = NOERROR;
    LPEXCHANGEMANAGESTORE   lpXManageStore  = NULL;
    LPMDB                   lpMailboxMDB    = NULL;
    ULONG                   ulFlags         = 0L;
    ULONG                   cbeid           = 0L;     // count of bytes in entry ID
    LPENTRYID               lpeid           = NULL;   // Entry ID of default store

    DEBUGPUBLIC( "HrMailboxLogon()");

    hr = CHK_HrMailboxLogon(
        lplhSession, lpMDB, lpszMsgStoreDN, lpszMailboxDN, 
        lppMailboxMDB);
    if( FAILED( hr))
        RETURN( hr);

    // Cheap firewall against API abuse
    if( !lplhSession || !lpMDB || !lpszMsgStoreDN)
    {
        hr = HR_LOG( E_INVALIDARG);
        goto cleanup;
    }

    hr = MAPICALL( lpMDB)->QueryInterface( lpMDB,
        (REFIID) &IID_IExchangeManageStore,
        (LPVOID*) &lpXManageStore);
    if( FAILED( hr))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    ASSERTERROR( lpXManageStore != NULL, "NULL lpXManageStore pointer");
            
    // Use NULL MailboxDN for opening the public store
    if( lpszMailboxDN == NULL || !*lpszMailboxDN)
    {
        ulFlags = OPENSTORE_PUBLIC;
    }

    hr = MAPICALL( lpXManageStore)->CreateStoreEntryID( lpXManageStore,
        lpszMsgStoreDN, lpszMailboxDN,
        ulFlags | OPENSTORE_USE_ADMIN_PRIVILEGE | OPENSTORE_TAKE_OWNERSHIP,
        &cbeid, &lpeid);
    if( FAILED( hr))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }
        
    ASSERTERROR( lpeid != NULL, "NULL lpeid pointer");

    hr = MAPICALL( lplhSession)->OpenMsgStore(
        lplhSession, 0, cbeid, lpeid, NULL,
    	MDB_NO_DIALOG |
        MDB_NO_MAIL |       // spooler not notified of our presence
        MDB_TEMPORARY |     // message store not added to MAPI profile
        MAPI_BEST_ACCESS,   // normally WRITE, but allow access to RO store
    	&lpMailboxMDB);
    if( FAILED(hr))
    {
        if( hr == MAPI_E_NOT_FOUND)
            hr = HR_LOG( EDK_E_NOT_FOUND);
        else
            hr = HR_LOG( E_FAIL);
        
        goto cleanup;
    }

    if( hr == MAPI_W_ERRORS_RETURNED)
    {
        ULRELEASE( lpMailboxMDB);

        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    if( lppMailboxMDB)
        *lppMailboxMDB = lpMailboxMDB;

cleanup:    
    MAPIFREEBUFFER( lpeid);
    ULRELEASE( lpXManageStore);
    
    RETURN( hr);
}

//$--HrMailboxLogoff------------------------------------------------------------
//  Logoff of a mailbox.
// -----------------------------------------------------------------------------

HRESULT HrMailboxLogoff(
    IN OUT LPMDB *lppMailboxMDB)          // ptr to mailbox message store ptr
{
    HRESULT hr      = NOERROR;
    ULONG   ulFlags = LOGOFF_NO_WAIT;

    DEBUGPUBLIC( "HrMailboxLogoff()");

    hr = CHK_HrMailboxLogoff( lppMailboxMDB);
    if( FAILED( hr))
        RETURN( hr);

    // Cheap firewall against API abuse
    if( lppMailboxMDB && *lppMailboxMDB)
    {
        hr = MAPICALL( *lppMailboxMDB)->StoreLogoff( *lppMailboxMDB,
            &ulFlags);
        if( FAILED( hr))
            goto cleanup;
    
        ULRELEASE( *lppMailboxMDB);
    }

cleanup:

    RETURN( hr);
}

