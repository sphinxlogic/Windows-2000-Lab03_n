// --gwobjcls.cpp-------------------------------------------------------------
//
// Class source file for the GWCLEAN class object.
//
// Copyright (C) Microsoft Corporation 1986-1996,  All Rights Reserved
//
// ----------------------------------------------------------------------------

#include "edk.h"
#include "mspst.h"

#include "gwstring.h"
#include "gwobjcls.h"
#include "gwevents.h"	// compiled from gwevents.mc
#include "gwobjcls.chk"

// external function declarations
extern VOID DisplayUserMsg(		// RETURNS: VOID
	IN UINT uResID,				// resource string identifier
	 ...);						// additional arguments

extern inline VOID INTERNAL_ERROR(
    IN LPCTSTR str,
    IN const HRESULT hr);

//$--CGWClean::CGWClean----------------------------------------
//
// DESCRIPTION: constructor for CGWClean
//
// INPUT:   none
//
// RETURNS: nothing
//
// -------------------------------------------------------------
CGWClean::CGWClean()        // returns nothing
{
    DEBUGPRIVATE("CGWClean::CGWClean()\n");

    // Initialize data members.
    m_fNewPST           =   FALSE;
    m_fNoMessages       =   FALSE;
    m_lpProfileName     =   NULL;
    m_lpPSTName         =   NULL;
    m_lpFolderName      =   NULL;
    m_lpBeforeDateTime  =   NULL;
    m_lpTempProfilePW   =   NULL;
    m_lpTempProfName    =   NULL;
    m_lpSessGW          =   NULL;
    m_lpSessNew         =   NULL;
    m_lpMDBGateway      =   NULL;
    m_lpMDBNew          =   NULL;
    m_lpFolderFrom      =   NULL;
    m_lpFolderTo        =   NULL;

}

//$--CGWClean::~CGWClean-----------------------------------------------------
//
// DESCRIPTION: CGWClean Destructor
//
// ---------------------------------------------------------------------------

CGWClean::~CGWClean()
{    
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("CGWClean::~CGWClean()\n");

    if ( m_lpMDBGateway )
    {
        // Set the PR_TRANSFER_ENABLED property so that message
        // transfer activity resumes on the gateway.
        hr = HrMAPISetPropBoolean(
                m_lpMDBGateway,         // MAPI object pointer
                PR_TRANSFER_ENABLED,    // property tag
                TRUE);                  // boolean value

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("HrMAPISetPropBoolean()"), hr);
        }
    }

    // clean up after PST creation.  (Removes temporary profile)
    if ( m_fNewPST )
    {
        (VOID)HrCleanupPSTGlobals(m_lpTempProfName);

        // If there were no messages to move, delete the
        // PST created.
        if ( m_fNoMessages )
        {
            (VOID)DeleteFile(m_lpPSTName);
        }
    }

    // Free MAPI buffers
    MAPIFREEBUFFER(m_lpTempProfilePW);
    MAPIFREEBUFFER(m_lpTempProfName);

    // Release MAPI store and folder objects
    ULRELEASE(m_lpMDBGateway);
    ULRELEASE(m_lpMDBNew);
    ULRELEASE(m_lpFolderFrom);
    ULRELEASE(m_lpFolderTo);

    // Logoff any MAPI sessions to which we are logged on.
    if ( m_lpSessGW )
    {
        (VOID)m_lpSessGW->Logoff(0, 0, 0);
    }

    if ( m_lpSessNew )
    {
        (VOID)m_lpSessNew->Logoff(0, 0, 0);
    }

    // Release MAPI session objects if they have not already been released.
    ULRELEASE(m_lpSessGW);
    ULRELEASE(m_lpSessNew);

    // Delete m_lpBeforeDateTime buffer.
    if ( m_lpBeforeDateTime )
    {
        delete m_lpBeforeDateTime;
    }

}   // end CGWClean::~CGWClean();

//$--CGWClean::HrInitialize-------------------------------------------------------
//
// DESCRIPTION: CGWClean initializer.  Creates profile,
//              establishes sessions, opens default stores,
//              opens from and to folders.
//
// INPUT:   lpProfileName   --  gateway profile name
//          lpPSTName  --  new PST name
//          lpFolder    --  gateway folder name
//          lpBeforeDate  --  date/time before which to move messages
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_OUTOFMEMORY if memory problems,
//                      E_FAIL otherwise
//
// ---------------------------------------------------------------------------

HRESULT CGWClean::HrInitialize(
             IN LPTSTR lpProfileName,       // gateway profile name
             IN LPTSTR lpPSTName,           // New PST name
             IN LPTSTR lpFolderName,        // gateway folder name
             IN LPFILETIME lpBeforeTime)    // date/time before which to move messages
{
    HRESULT hr      =   NOERROR;
    ULONG   cbEid   =   0;          // number of bytes in entry identifier
    TCHAR   szErrorCode[16] = {0};

    // Special MAPI buffer base class which frees itself
    // when it goes out of scope.
    LPENTRYID   lpEid   =   NULL;   // entry identifier pointer

    // MAPI session flags
    const ULONG ulFlags =   MAPI_EXPLICIT_PROFILE |
                            MAPI_NEW_SESSION |
                            MAPI_NO_MAIL;

    // new PST PR_DISPLAY_NAME value
    const LPTSTR   lpszDisplayName =   TEXT("Mailbox - GWCLEAN");

    // Separator in folder name.
    const TCHAR     cSeparator  =   TEXT('\\');

    // message database store flags
    const ULONG     ulMDBflags  =   MDB_NO_DIALOG | MDB_WRITE;

    DEBUGPRIVATE("CGWClean::HrInitialize()\n");

    hr = CHK_CGWClean_HrInitialize(lpProfileName, 
                                 lpPSTName, lpFolderName, lpBeforeTime);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Initialize class members
    m_lpProfileName = lpProfileName;
    m_lpPSTName = lpPSTName;
    m_lpFolderName = lpFolderName;

    m_lpBeforeDateTime = new FILETIME;

    if( !TEST_WRITE_PTR( m_lpBeforeDateTime, sizeof(FILETIME)) )
    {
        EventLogMsg( 
        	GWCLEAN_OUTOFMEMORY,
        	0,
        	0);

        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    m_lpBeforeDateTime->dwHighDateTime = lpBeforeTime->dwHighDateTime;
    m_lpBeforeDateTime->dwLowDateTime = lpBeforeTime->dwLowDateTime;

    // Open session to gateway.
    hr = MAPILogonEx(0,   // UI flags,
                m_lpProfileName,    // profile name
                NULL,               // password
                ulFlags,            // MAPI flags
                &m_lpSessGW);

    if ( FAILED(hr) )
    {
        EventLogMsg( 
                GWCLEAN_PROFILEERR, 
				2, m_lpProfileName, _itot( hr, szErrorCode, 16),
                0);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Create the new PST and temporary profile.
    hr = HrCreatePersonalStore(
                        m_lpPSTName,            // fully-pathed PST name
                        PSTF_NO_ENCRYPTION,     // type of encryption
                        (LPTSTR) lpszDisplayName,        // PST PR_DISPLAY_NAME value
                        TEXT(""),               // PST password
                        &m_lpTempProfName,      // temporary profile name
                        &m_lpTempProfilePW);    // temporary profile password

    if ( FAILED(hr) )
    {
        EventLogMsg(
        	GWCLEAN_NEWPSTERR,
			2, m_lpPSTName, _itot( hr, szErrorCode, 16),
            0);

        goto cleanup;
    }

    // Have created a new PST.
    m_fNewPST = TRUE;

    // Log onto the PST's temporary profile
    hr = MAPILogonEx(0,       // UI flags
                m_lpTempProfName,   // temporary profile name
                m_lpTempProfilePW,  // temporary profile password
                ulFlags,            // MAPI flags,
                &m_lpSessNew);

    if ( FAILED(hr) )
    {
        EventLogMsg( 
                GWCLEAN_PROFILEERR, 
				2, m_lpTempProfName, _itot( hr, szErrorCode, 16),
                0);

        hr = HR_LOG(E_FAIL);
    
        goto cleanup;
    }

    // Open gateway's default message store.
    // Find the default MDB message store in the gateway profile.
    hr = HrMAPIFindDefaultMsgStore(m_lpSessGW,    // session pointer
                                 &cbEid,        // count of bytes in entry ID
                                 &lpEid);       // entry id pointer for default store

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrMAPIFindDefaultMsgStore()"), hr);

        goto cleanup;
    }

    // Open the gateway's default message store.
    hr = m_lpSessGW->OpenMsgStore(0,        // window handle
                                  cbEid,    // # of bytes in entry ID
                                  lpEid,    // pointer to entry ID
                                  NULL,     // interface ID pointer
                                  ulMDBflags, // flags
                                  &m_lpMDBGateway);   // output ptr to store

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPISession::OpenMsgStore()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Set the PR_TRANSFER_ENABLED property so that we don't
    // get any activity on the gateway.
    hr = HrMAPISetPropBoolean(
            m_lpMDBGateway,         // MAPI object pointer
            PR_TRANSFER_ENABLED,    // property tag
            FALSE);                 // boolean value

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrMAPISetPropBoolean()"), hr);

        goto cleanup;
    }

    // Free gateway message store entry ID buffer
    MAPIFREEBUFFER(lpEid);

    // Open PST temporary profile's default message store.
    // Find the default MDB message store in the gateway profile
    // first
    hr = HrMAPIFindDefaultMsgStore(m_lpSessNew,   // session pointer
                                 &cbEid,        // count of bytes in entry ID
                                 &lpEid);       // entry id pointer for default store

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("HrMAPIFindDefaultMsgStore()"), hr);

        goto cleanup;
    }

    // Open the gateway's default message store.
    hr = m_lpSessNew->OpenMsgStore(0,       // window handle
                                  cbEid,    // # of bytes in entry ID
                                  lpEid,    // pointer to entry ID
                                  NULL,     // interface ID pointer
                                  ulMDBflags, // flags
                                  &m_lpMDBNew);   // output ptr to store

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPISession::OpenMsgStore()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Open desired folder in gateway.
    hr = HrMAPIOpenFolderEx(
            m_lpMDBGateway,     // message store pointer
            cSeparator,         // folder path separator
            m_lpFolderName,     // folder path
            &m_lpFolderFrom);

    if ( FAILED(hr) )
    {
        EventLogMsg(
        	GWCLEAN_BADFOLDER,
			3,
            m_lpFolderName,
            m_lpProfileName,
            _itot( hr, szErrorCode, 16),
            0);

        goto cleanup;
    }

    // Create GWCLEAN folder in PST.
    hr = HrCreatePSTFolder();

    if ( FAILED(hr) )
    {
        goto cleanup;
    }

    // We are now ready to move messages from the open
    // gateway folder to the open PST folder.
    // We are done with our initialization.

cleanup:

    // Free MAPI buffers
    MAPIFREEBUFFER(lpEid);
    
    RETURN(hr);

}   // end CGWClean::HrInitialize()

//$--CGWClean::HrCreatePSTFolder-----------------------------------------------
//
// DESCRIPTION: Create a new folder in the new PST and
//              open it.
//
// RETURNS:     HRESULT   --  NOERROR if successful
//                            E_FAIL otherwise.
// 
// ---------------------------------------------------------------------------

HRESULT CGWClean::HrCreatePSTFolder()         // RETURNS: HRESULT
{
    HRESULT hr          =   NOERROR;    // MAPI return code
    ULONG   ulObjType   =   0;          // object type

#ifdef USE_MAPIWRAP
    // Special MAPI object base classes which release
    // object when they goe out of scope.
    CMAPIInterface<LPMAPIFOLDER>    lpRootFolder;   // PST root folder
    CMAPIInterface<LPMAPIFOLDER>    lpTopOfStore;   // top of personal folders in PST
#else
    LPMAPIFOLDER    lpRootFolder    =   NULL;   // PST root folder pointer
    LPMAPIFOLDER    lpTopOfStore    =   NULL;   // top of PST personal folders
#endif

    // top of store folder name for PST.
    const LPTSTR   lpszTopOfStoreName  =   TEXT("Top of Personal Folders");

    // Folder to which gateway messages are copied
    const LPTSTR   lpszGWCLEAN =   TEXT("GWCLEAN");

    DEBUGPRIVATE("CGWClean::HrCreatePSTFolder()\n");

    // consistency checks
    ASSERT_IUNKNOWN_PTR( m_lpMDBNew, "Bad m_lpMDBNew");

    // Find the new PST's root folder.
    hr = m_lpMDBNew->OpenEntry(0,     // # of bytes in entry ID
                                  NULL,  // ptr to entry ID
                                  NULL,  // interface ID pointer
                                  MAPI_MODIFY | MAPI_DEFERRED_ERRORS, // flags
                                  &ulObjType,       // object type pointer
                (LPUNKNOWN *) &lpRootFolder);       // output ptr to folder

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMsgStore::OpenEntry()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERTERROR( ulObjType == MAPI_FOLDER, "Bad ulObjType");

    // Create the new PST's Top of Personal Folders folder.
    hr = lpRootFolder->CreateFolder(
                FOLDER_GENERIC,    // folder type
                (LPTSTR) lpszTopOfStoreName,  // folder name
                NULL,        // folder comment
                NULL,        // interface ID pointer
                OPEN_IF_EXISTS | MAPI_DEFERRED_ERRORS,  // flags
                &lpTopOfStore); // new folder pointer

    if ( FAILED(hr) )
    {
        // Check for insufficient disk space.
        if ( hr == MAPI_E_NOT_ENOUGH_DISK )
        {
            EventLogMsg( 
                GWCLEAN_OUTOFDISK,
                0,
                0);

			hr = HR_LOG(E_FAIL);

			goto cleanup;
        }                        

        else
        {
            INTERNAL_ERROR( TEXT("IMAPIFolder::CreateFolder()"), hr);

        	hr = HR_LOG(E_FAIL);
			goto cleanup;
        }
    }	// end if creation of folder failed

    // Create the new PST's GWCLEAN folder (under the Top of Personal Folders folder).
    // All gateway messages will be moved into this folder
    hr = lpTopOfStore->CreateFolder(
                FOLDER_GENERIC,  // folder type
                (LPTSTR) lpszGWCLEAN, // folder name
                NULL,        // folder comment
                NULL,        // interface ID pointer
                OPEN_IF_EXISTS | MAPI_DEFERRED_ERRORS,  // flags
                &m_lpFolderTo); // new folder pointer

    if ( FAILED(hr) )
    {
        // Check for insufficient disk space.
        if ( hr == MAPI_E_NOT_ENOUGH_DISK )
        {
            EventLogMsg( 
                GWCLEAN_OUTOFDISK,
                0,
                0);

			hr = HR_LOG(E_FAIL);

			goto cleanup;
        }

        else
        {
            INTERNAL_ERROR( TEXT("IMAPIFolder::CreateFolder()"), hr);

        	hr = HR_LOG(E_FAIL);
			goto cleanup;
        }
    }		// end if creation of folder fails

cleanup:

    ULRELEASE(lpTopOfStore);
    ULRELEASE(lpRootFolder);

    // Base classes take care of releasing MAPI objects
    // and freeing MAPI memory.

    RETURN(hr);

}

//$--CGWClean::HrMoveMsgs------------------------------------------------------
//
// DESCRIPTION: Move messages from gateways MTS-OUT folder to PSTs MTS-OUT folder.
//
// RESULT:      HRESULT   --  NOERROR if successful,
//                            EDK_E_NOT_FOUND if no messages to move,
//                            E_FAIL otherwise.
// 
// ---------------------------------------------------------------------------

HRESULT CGWClean::HrMoveMsgs()         // RETURNS: HRESULT 
{
    HRESULT hr  =   NOERROR;        // MAPI return code
    LPMAPITABLE lpContentsTable =   NULL;   // contents table for gateway MTS-OUT folder
    LPENTRYLIST lpEidList   =   NULL;       // list of entry identifiers to move
    LPENTRYLIST lpSearchKeyList =   NULL;   // list of search key identifiers for messages copied
    SizedSPropTagArray(2, SPropEntryIDs);   // property tag array containing only PR_ENTRY_ID and PR_SEARCH_KEY
    SRestriction    sRestriction    =   {0};// Property restriction structure
    SPropValue  sPropValue  =   {0};        // Property value structure
    LPSRowSet   lpMsgRows   =   NULL;       // Row pointer corresponding to a message
    ULONG       ulMsgCount  =   0;          // count of messages moved
    SYSTEMTIME  sSysTime    =   {0};        // local system time structure
    FILETIME    sLocalFileTime  =   {0};    // local file time structure
    TCHAR   szDateTimeString[80]    =   {0};// before date time string
    ULONG   ulCount =   0;                  // loop counter
    ULONG   ulNumBytes  =   0;              // size of entry identifier
    LPBYTE  lpEid   =   NULL;               // entry ID pointer for message
    TCHAR   szErrorCode[16] = {0};          // buffer for error code strings

    DEBUGPRIVATE("CGWCLEAN::HrMoveMsgs()\n");

    // Consistency checking
    ASSERT_IUNKNOWN_PTR( m_lpFolderFrom, "Bad m_lpFolderFrom");
    ASSERT_IUNKNOWN_PTR( m_lpFolderTo, "Bad m_lpFolderTo");

    // Get the contents table for the gateway's MTS-OUT folder.
    hr = m_lpFolderFrom->GetContentsTable(
                MAPI_DEFERRED_ERRORS,  // flags
                &lpContentsTable);  // Contents table pointer

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPIFolder::GetContentsTable()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERTERROR((lpContentsTable != NULL), "Bad lpContentsTable");

    // Get a list of all desired message IDs from the contents table.
    // First, call SetColumns to chose the PR_ENTRY_ID column and
    // PR_SEARCH_KEY columns.  (PR_SEARCH_KEY is the transmittable,
    // unique identifier of the message.)
    SPropEntryIDs.cValues = 2;
    SPropEntryIDs.aulPropTag[0] = PR_ENTRYID;
    SPropEntryIDs.aulPropTag[1] = PR_SEARCH_KEY;

    hr = lpContentsTable->SetColumns((LPSPropTagArray) (&SPropEntryIDs),    // Properties desired
                                     0);            // flags

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPITable::SetColumns()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Make a call here to Restrict to restrict the rows in the table returned
    // to be those where the PR_CREATION_TIME property is less than
    // the desired "before" date.

    ASSERTERROR((m_lpBeforeDateTime != NULL), "Bad m_lpBeforeDateTime");

    sPropValue.ulPropTag    =   PR_CREATION_TIME;
    sPropValue.Value.ft.dwLowDateTime = m_lpBeforeDateTime->dwLowDateTime;
    sPropValue.Value.ft.dwHighDateTime = m_lpBeforeDateTime->dwHighDateTime;

    sRestriction.rt                         = RES_PROPERTY;
    sRestriction.res.resProperty.relop      = RELOP_LT;
    sRestriction.res.resProperty.ulPropTag  = PR_CREATION_TIME;
    sRestriction.res.resProperty.lpProp     = &sPropValue;

    hr = lpContentsTable->Restrict(&sRestriction, 0);

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPITable::Restrict()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Let user know that we are starting the copy.
    // (Convert the FILETIME value to a string for easy
    // display to the user.)
    FileTimeToLocalFileTime(m_lpBeforeDateTime, &sLocalFileTime); // system file time to local file time
    FileTimeToSystemTime(&sLocalFileTime, &sSysTime);  // local file time to local system time
    wsprintf(szDateTimeString, TEXT("%d:%d:%d.%d %d/%d/%d"), sSysTime.wHour,
            sSysTime.wMinute, sSysTime.wSecond, sSysTime.wMilliseconds,
            sSysTime.wMonth, sSysTime.wDay, sSysTime.wYear);

    ASSERT_STRING_PTR( szDateTimeString, "Bad szDateTimeString");

    DisplayUserMsg( 
    	IDS_STARTMOVE, 
        szDateTimeString, 
        m_lpProfileName, 
        m_lpPSTName);

    // Build a list of entry identifiers for the messages which match
    // our criteria.
    while ( TRUE )
    {
        // Free the MAPI structures (SRowSet is special!)
        FREEPROWS(lpMsgRows);

        // Free EDK structures.
        if ( lpEidList )
        {
            HrMAPIDestroyEntryList(&lpEidList);
            lpEidList = NULL;
        }

        if ( lpSearchKeyList )
        {
            HrMAPIDestroyEntryList(&lpSearchKeyList);
            lpSearchKeyList = NULL;
        }

        // Retrieve the row (messages) in the table which meet our
        // selection criteria in EDK_MAX_QUERY_ROWS chunks (1024 at a time).
        hr = lpContentsTable->QueryRows(EDK_MAX_QUERY_ROWS, // count to return
                                        0,                  // flags
                                        &lpMsgRows);        // returned row structure pointer

        switch (hr)
        {
            case MAPI_W_POSITION_CHANGED:
                // Location in table changed by somebody else.
                // Warn the user.
                EventLogMsg( 
                	GWCLEAN_POSCHANGED,
                	0,
                	0);

                hr = HR_LOG(E_FAIL);

                goto cleanup;

            default:
                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("IMAPITable::QueryRows()"), hr);

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                break;

        }   // end switch

        ASSERTERROR((lpMsgRows != NULL), "Bad lpMsgRows");

        // Check to see if any messages to process.
        if ( !lpMsgRows->cRows )
        {
            // If no messages found at all, let user know.
            if ( !ulMsgCount )
            {
                EventLogMsg( 
                	GWCLEAN_NOMSGS,
					1,
                    szDateTimeString,
                    0);

                hr = HR_LOG(EDK_E_NOT_FOUND);

                // Set no messages flag
                m_fNoMessages = TRUE;

                goto cleanup;
            }

            // Otherwise, we are done!
            break;
        }

        // Add message identifiers for messages returned to our list of
        // entry IDs.
        ulMsgCount += lpMsgRows->cRows;  // increment message count
        
        for ( ulCount = 0; ulCount < lpMsgRows->cRows; ulCount++ )
        {
            ASSERTERROR(lpMsgRows->aRow[ulCount].cValues == 2,
                "Bad lpMsgRows->aRow[].cValues");
            ASSERTERROR(lpMsgRows->aRow[ulCount].lpProps[0].ulPropTag == PR_ENTRYID,
                "Bad lpMsgRows->aRows[].lpProps[0].ulPropTag");
            ASSERTERROR(lpMsgRows->aRow[ulCount].lpProps[1].ulPropTag == PR_SEARCH_KEY,
                "Bad lpMsgRows->aRows[].lpProps[1].ulPropTag");

            ulNumBytes = lpMsgRows->aRow[ulCount].lpProps[0].Value.bin.cb;
            lpEid = lpMsgRows->aRow[ulCount].lpProps[0].Value.bin.lpb;

            // Add entry identifier to the entry ID list.
            if ( !lpEidList )
            {
                // Create new entry identifier list.
                hr = HrMAPICreateEntryList(ulNumBytes, (LPENTRYID) lpEid, &lpEidList);                

            	if ( FAILED(hr) )
            	{
                    INTERNAL_ERROR( TEXT("HrMAPICreateEntryList()"), hr);

                	goto cleanup;
            	}
            }
            else
            {
                hr = HrMAPIAppendEntryList(ulNumBytes, (LPENTRYID) lpEid, lpEidList);

            	if ( FAILED(hr) )
            	{
                    INTERNAL_ERROR( TEXT("HrMAPIAppendEntryList()"), hr);

                	goto cleanup;
            	}
            }

            ASSERTERROR((lpEidList != NULL), "Bad lpEidList");

            ulNumBytes = lpMsgRows->aRow[ulCount].lpProps[1].Value.bin.cb;
            lpEid = lpMsgRows->aRow[ulCount].lpProps[1].Value.bin.lpb;

            // Add seach key identifier for search key list.
            if ( !lpSearchKeyList )
            {
                // Create new search key list.
                hr = HrMAPICreateEntryList(ulNumBytes, (LPENTRYID) lpEid, &lpSearchKeyList);                

            	if ( FAILED(hr) )
            	{
                    INTERNAL_ERROR( TEXT("HrMAPICreateEntryList()"), hr);

                	goto cleanup;
            	}
            }
            else
            {
                hr = HrMAPIAppendEntryList(ulNumBytes, (LPENTRYID) lpEid, lpSearchKeyList);

            	if ( FAILED(hr) )
            	{
                    INTERNAL_ERROR( TEXT("HrMAPIAppendEntryList()"), hr);

                	goto cleanup;
            	}
            }

            ASSERTERROR((lpSearchKeyList != NULL), "Bad lpSearchKeyList");

        }   // end for

        ASSERTERROR((lpEidList != NULL), "Bad lpEidList");  // just in case!
        ASSERTERROR((lpSearchKeyList != NULL), "Bad lpSearchKeyList");
        
        // Copy messages from gateway MTS-OUT folder to new PST's MTS-OUT
        // folder.
        hr = m_lpFolderFrom->CopyMessages(lpEidList,  // list of message IDs
                                        &IID_IMAPIFolder,   // interface ID of destination folder
                                        m_lpFolderTo,  // destination folder ptr
                                        0,  // window handle
                                        0,  // progress dialogue handle
                                        MAPI_DECLINE_OK );   // flags

        switch (hr)
        {
            case MAPI_E_DECLINE_COPY:
                // Provider doesn't support CopyMessages function.
                // Warn the user.
                EventLogMsg( 
                	GWCLEAN_NOCOPYMSGS,
                	0,
                	0);

                hr = HR_LOG(E_FAIL);

                goto cleanup;

            case MAPI_E_NOT_ENOUGH_DISK:
                // insufficient disk space.
                EventLogMsg( 
                	GWCLEAN_OUTOFDISK,
                	0,
                	0);

                hr = HR_LOG(E_FAIL);

                goto cleanup;

            case MAPI_W_PARTIAL_COMPLETION:
                // Couldn't copy all messages.
                // Warn the user.
                EventLogMsg( 
                	GWCLEAN_PARTIALCOPY,
                	1, _itot( hr, szErrorCode, 16),
                	0);

                hr = HR_LOG(E_FAIL);
                goto cleanup;

            default:
                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("IMAPIFolder::CopyMessages()"), hr);

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                break;

        }   // end switch

        // Copy the extra gateway message properties not copied via CopyMessages
        // from the old messages to the new messages.
        hr = HrCopyGWMessageProps(lpEidList, lpSearchKeyList);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Now, delete messages moved from gateway MTS-OUT folder to the
        // new PST MTS-OUT folder.
        // Delete copied messages from gateway's MTS-OUT folder.
        hr = m_lpFolderFrom->DeleteMessages(lpEidList,  // entry identifier list
                                              0,          // window handle
                                              0,          // progress dialog
                                              0);         // flags

        switch (hr)
        {
            case MAPI_W_PARTIAL_COMPLETION:

                EventLogMsg( 
                	GWCLEAN_PARTIALDEL,
                	1, _itot( hr, szErrorCode, 16),
                	0);

                hr = HR_LOG(E_FAIL);
                goto cleanup;

            case MAPI_E_HAS_FOLDERS:
            case MAPI_E_SUBMITTED:

                EventLogMsg( 
                	GWCLEAN_PARTIALDEL,
                	1, _itot( hr, szErrorCode, 16),
                	0);

                hr = HR_LOG(E_FAIL);
                goto cleanup;

            default:
                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("IMAPIFolder::DeleteMessages()"), hr);

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                break;

        }   // end switch
    }   // end while messages to copy

    // We have done it!
    // Display a successful completion message and log event.
    EventLogMsg( 
    	GWCLEAN_SUCCESS,
		1, _itot( ulMsgCount, szErrorCode, 10),
		0);

	DisplayUserMsg(
		IDS_SUCCESS,
		ulMsgCount);

cleanup:

    // Free EDK structures.
    if ( lpEidList )
    {
        HrMAPIDestroyEntryList(&lpEidList);
    }

    if ( lpSearchKeyList )
    {
        HrMAPIDestroyEntryList(&lpSearchKeyList);
    }

    // Free MAPI structures (SRowSet is special!)
    FREEPROWS(lpMsgRows);

    // Release MAPI objects.
    ULRELEASE(lpContentsTable);

    RETURN(hr);

}   // end CGWClean::MoveMsgs()

//$--CGWClean::HrCopyGWMessageProps--------------------------------------------
//
// DESCRIPTION: Copy the gateway message (envelope) properties not copied by CopyMessages
//              from the gateway messages to the new PST messages.
//              The additional properties copied are determined
//              in HrCreateNewProps().
//
// INPUT:       LPENTRYLIST --  list of entry identifiers of messages copied.
//              LPENTRYLIST --  list of search key identifiers of messages copied.
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------

HRESULT CGWClean::HrCopyGWMessageProps(                   // RETURNS: HRESULT
                        IN LPENTRYLIST lpEidList,       // entry identifiers
                        IN LPENTRYLIST lpSearchKeyList) // search keys
{
    HRESULT hr  =   NOERROR;        // return code
    LPMESSAGE   lpMessage   =   NULL;       // original message pointer (envelope)
    LPMESSAGE   lpNewMessage    =   NULL;   // copied message pointer   (envelope)
    ULONG       ulObjType   =   0;          // MAPI object type
    LPMAPITABLE lpContentsTable =   NULL;   // contents table pointer for new MTS-OUT folder
    SRestriction    sRestriction    =   {0};// Property restriction structure
    SPropValue  sPropValue  =   {0};        // Property value structure
    LPSRowSet   lpMsgRows   =   NULL;       // Row pointer corresponding to a message
    SizedSPropTagArray(2, SPropEntryIDs);   // property tag array containing only PR_ENTRY_ID and PR_SEARCH_KEY
    ULONG   ulLoopCounter   =   0;              // loop counter
    ULONG   ulDupEidSize    =   0;              // duplicate message entry ID size
    LPBYTE  lpDupEid    =   NULL;               // duplicate message's search key
    ULONG   ulTempIndex =   0;                  // temporary index
    BOOL    bDupDone    =   FALSE;              // Duplicate done flag
    LPENTRYLIST lpDoneList  =   NULL;       // duplicates done list

    DEBUGPRIVATE("CGWClean::HrCopyGWMessageProps()\n");

    hr = CHK_CGWClean_HrCopyGWMessageProps(lpEidList, lpSearchKeyList);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // consistency checking
    ASSERT_IUNKNOWN_PTR( m_lpFolderTo, "Bad m_lpFolderTo");
    ASSERT_IUNKNOWN_PTR( m_lpFolderFrom, "Bad m_lpFolderFrom");

    // Get the contents table for the new MTS-OUT folder.
    hr = m_lpFolderTo->GetContentsTable(0,  // flags
                                             &lpContentsTable);  // Contents table pointer

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPFolder::GetContentsTable()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Call SetColumns to chose the PR_ENTRY_ID column and
    // PR_SEARCH_KEY columns for the new table.  (PR_SEARCH_KEY is the transmittable,
    // unique identifier of the message.)
    SPropEntryIDs.cValues = 2;
    SPropEntryIDs.aulPropTag[0] = PR_ENTRYID;
    SPropEntryIDs.aulPropTag[1] = PR_SEARCH_KEY;

    hr = lpContentsTable->SetColumns((LPSPropTagArray) (&SPropEntryIDs),    // Properties desired
                                     0);            // flags

    if ( FAILED(hr) )
    {  
        INTERNAL_ERROR( TEXT("IMAPITable::SetColumns()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // Handle each message in the list    
    for ( ulLoopCounter = 0; ulLoopCounter < lpEidList->cValues; ulLoopCounter++ )
    {    
        // Release the MAPI objects.
        ULRELEASE(lpMessage);

        // Free the MAPI structures (SRowSet is special!)
        FREEPROWS(lpMsgRows);

        // Print out a . for every message to be copied.
        _puttchar(TEXT('.'));

        // Open original message envelope.
        hr = m_lpFolderFrom->OpenEntry(
                            lpEidList->lpbin[ulLoopCounter].cb,  // # of bytes in entry ID
                            (LPENTRYID) (lpEidList->lpbin[ulLoopCounter].lpb),// entry ID pointer
                            &IID_IMessage,  // interface ID pointer
                            0,              // flags
                            &ulObjType,     // object type
                            (LPUNKNOWN FAR *) &lpMessage);    // output pointer to message

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("IMAPIFolder::OpenEntry()"), hr);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        ASSERT_IUNKNOWN_PTR( lpMessage, "Bad lpMessage");
        ASSERTERROR(ulObjType == MAPI_MESSAGE, "Bad ulObjType");

        // Go about finding the corresponding new message

        // Make a call to find the row in the new folder's table 
        // where the PR_SEARCH_KEY property is equal to the 
        // PR_SEARCH_KEY property of the original message.
        sPropValue.ulPropTag    =   PR_SEARCH_KEY;
        sPropValue.Value.bin.cb =   lpSearchKeyList->lpbin[ulLoopCounter].cb;
        sPropValue.Value.bin.lpb =  lpSearchKeyList->lpbin[ulLoopCounter].lpb;

        sRestriction.rt                         = RES_PROPERTY;
        sRestriction.res.resProperty.relop      = RELOP_EQ;
        sRestriction.res.resProperty.ulPropTag  = PR_SEARCH_KEY;
        sRestriction.res.resProperty.lpProp     = &sPropValue;

        hr = lpContentsTable->Restrict(&sRestriction, 0);

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("IMAPITable::Restrict()"), hr);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Retrieve the row(s) from the new table which meet the
        // selection criteria.
        hr = lpContentsTable->QueryRows(lpEidList->cValues, // maximum count to return
                                        0,                  // flags
                                        &lpMsgRows);        // returned row structure pointer

        switch (hr)
        {
            case MAPI_W_POSITION_CHANGED:
                // Location in table changed by somebody else.
                // Warn the user.
                EventLogMsg( 
                	GWCLEAN_POSCHANGED,
                	0,
                	0);

                hr = HR_LOG(E_FAIL);

                goto cleanup;

            default:
                if ( FAILED(hr) )
                {	
                    INTERNAL_ERROR( TEXT("IMAPITable::QueryRows()"), hr);

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                break;

        }   // end switch

        ASSERT_READ_PTR( lpMsgRows, sizeof(SRowSet), "Bad lpMsgRows");

        ASSERTERROR( lpMsgRows->cRows,
            "Bad lpMsgRows->cRows"); // should be at least one match
        ASSERTERROR(lpMsgRows->aRow[0].cValues == 2,
            "Bad lpMsgRows->aRow[0].cValues");
        ASSERTERROR(lpMsgRows->aRow[0].lpProps[0].ulPropTag == PR_ENTRYID,
            "Bad lpMsgRows->aRow[0].lpProps[0].ulPropTag");
        ASSERTERROR(lpMsgRows->aRow[0].lpProps[1].ulPropTag == PR_SEARCH_KEY,
            "Bad lpMsgRows->aRow[0].lpProps[1].ulPropTag");

        // If this message has duplicates, see if we have already
        // handled them before.  If so, continue on to next message
        // in list.
        if ( lpMsgRows->cRows > 1 )
        {
            ulDupEidSize = lpMsgRows->aRow[0].lpProps[1].Value.bin.cb;
            lpDupEid = lpMsgRows->aRow[0].lpProps[1].Value.bin.lpb;

            // if this search key is in the done list, go to the
            // next message.  Otherwise, add it to the done list and
            // handle its duplicates.
            if ( !lpDoneList )
            {
                // Create done list and
                // record this search key in the done list.
                hr = HrMAPICreateEntryList(ulDupEidSize,
                                          (LPENTRYID) lpDupEid,
                                          &lpDoneList);
                
                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("HrMAPICreateEntryList()"), hr);

                    goto cleanup;
                }
            }

            else
            {
                // look for search key in done list.
                for ( ulTempIndex = 0, bDupDone = FALSE; 
                      ulTempIndex < lpDoneList->cValues; ulTempIndex++ )
                {
                    if ( memcmp(lpDupEid, lpDoneList->lpbin[ulTempIndex].lpb, ulDupEidSize) == 0 )
                    {
                        // This duplicate has already been done.
                        bDupDone = TRUE;
                        break;
                    }

                }   // end for

                // If message's duplicates already handled, continue
                if ( bDupDone )
                {
                    continue;   // go do next message
                }

                // Otherwise, add this message's search key to the done list.
                hr = HrMAPIAppendEntryList(ulDupEidSize,
                                          (LPENTRYID) lpDupEid,
                                          lpDoneList);
                
                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("HrMAPIAppendEntryList()"), hr);

                    goto cleanup;
                }

            }   // end if
        }   // end if message has duplicates

        // Handle extra properties for message's duplicates
        ULONG ulDupCount;   // duplicate count
        for (ulDupCount = 0; ulDupCount < lpMsgRows->cRows; ulDupCount++ )
        {        
            // Open corresponding new message envelope.
            hr = m_lpFolderTo->OpenEntry(
                        lpMsgRows->aRow[ulDupCount].lpProps[0].Value.bin.cb,    // # of bytes in entry ID
                        (LPENTRYID) lpMsgRows->aRow[ulDupCount].lpProps[0].Value.bin.lpb,   // entry ID pointer
                        &IID_IMessage,  // interface ID pointer
                        MAPI_MODIFY | MAPI_DEFERRED_ERRORS,    // flags
                        &ulObjType,     // object type
                        (LPUNKNOWN FAR *) &lpNewMessage);    // output pointer to message

            if ( FAILED(hr) )
            {
                INTERNAL_ERROR( TEXT("IMAPIFolder::OpenEntry()"), hr);

                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            ASSERT_IUNKNOWN_PTR( lpNewMessage, "Bad lpNewMessage");
            ASSERTERROR(ulObjType == MAPI_MESSAGE, "Bad ulObjType");

            // If not all properties were copied to the new message
            // by IMAPIFolder::CopyMessages(),
            // create those properties in the new message now.
            hr = HrCreateNewProps(lpMessage, lpNewMessage);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Copy over the properties from the original message (envelope
            // attachment) to the new message (envelope attachment).
            hr = HrCopyGWAttachProps(lpMessage, lpNewMessage);

            if ( FAILED(hr) )
            {
                goto cleanup;
            }

            // Save changes to new message.
            hr = lpNewMessage->SaveChanges(KEEP_OPEN_READWRITE);
        
            if ( FAILED(hr) )
            {
                // check for insufficient disk space
                if ( hr == MAPI_E_NOT_ENOUGH_DISK )
                {
                    EventLogMsg( 
                    	GWCLEAN_OUTOFDISK,
                    	0,
                    	0);

	                hr = HR_LOG(E_FAIL);

    	            goto cleanup;
                }

				else
				{
                    INTERNAL_ERROR( TEXT("IMAPIProp::SaveChanges()"), hr);

					hr = HR_LOG(E_FAIL);
					goto cleanup;
				}
            }	// end if save changes failure

            // Release new message MAPI object.
            ULRELEASE(lpNewMessage);

        }   // end for all duplicates
    }   // end for

    // We are done copying the extra gateway message properties.

cleanup:

    // Release MAPI objects.
    ULRELEASE(lpContentsTable);
    ULRELEASE(lpMessage);
    ULRELEASE(lpNewMessage);

    // SRowSet is special!
    FREEPROWS(lpMsgRows);

    // Free done list
    if ( lpDoneList )
    {
        HrMAPIDestroyEntryList(&lpDoneList);
    }
    
    RETURN(hr);

}   // end CGWClean::CopyGWMessageProps()

//$--CGWClean::HrCopyGWMessageProps----------------------------------------------------
//
// DESCRIPTION: Recursively copy the gateway message & attachment (message) 
//              properties not copied by CopyMessages
//              from the gateway messages to the new PST messages.
//              The additional properties copied are
//              determined in HrCreateNewProps().
//
// INPUT:       LPMESSAGE --  Original message pointer
//              LPMESSAGE --  New message pointer
//
// RESULT:      HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------

HRESULT CGWClean::HrCopyGWAttachProps(              // RETURNS: HRESULT
                        IN LPMESSAGE lpParent,      // original message pointer
                        IN LPMESSAGE lpNewParent)   // new message pointer
{
    HRESULT hr  =   NOERROR;    // return code
    LPMAPITABLE lpAttachTable   =   NULL;   // Original message's attachment table
    LPMAPITABLE lpNewAttachTable    =   NULL;   // new message's attachment table
    LPMESSAGE   lpMessage   =   NULL;       // Original message (envelope attachment)
    LPMESSAGE   lpNewMessage    =   NULL;   // New message (envelope attachment)
    ULONG   ulCount =   0;                  // count
    LPSRowSet   lpRows  =   NULL;           // old message QueryRows return
    LPSRowSet   lpNewRows   =   NULL;       // new message QueryRows return
    ULONG   ulAttachNum =   0;              // old message attachment index
    ULONG   ulNewAttachNum  =   0;          // new message attachment index
    LPATTACH    lpAttachment    =   NULL;   // Original attachment
    LPATTACH    lpNewAttachment =   NULL;   // new attachment
    ULONG       ulLoopCounter   =   0;      // loop counter
    LPBYTE  lpSearchKey =   NULL;           // old search key
    LPBYTE  lpSearchKeyNew  =   NULL;       // new search key
    ULONG   ulCountNew  =   0;
    BOOL    bFound  =   FALSE;              // True if find corresponding attachment
    ULONG   ulLoopCount2    =   0;          // inner loop counter

    SizedSPropTagArray(1, sPropAttachNum)   =   // PR_ATTACH_NUM property tag array
    {
        1,  // number of properties
        {
            PR_ATTACH_NUM   // property tag
        }
    };

    DEBUGPRIVATE("CGWClean::HrCopyGWAttachProps()\n");

    hr = CHK_CGWClean_HrCopyGWAttachProps(lpParent, lpNewParent);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Open the message's attachments table.
    hr = lpParent->GetAttachmentTable(0, &lpAttachTable);

    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMessage::GetAttachmentTable()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = lpNewParent->GetAttachmentTable(0, &lpNewAttachTable);
    
    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMessage::GetAttachmentTable()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
        
    ASSERT_IUNKNOWN_PTR( lpAttachTable, "Bad lpAttachTable");
    ASSERT_IUNKNOWN_PTR( lpNewAttachTable, "Bad lpNewAttachTable");

    // Retrieve all the attachments for this message.  This function is now
    // called recursively to handle all message attachments.
    hr = HrQueryAllRows(
            lpAttachTable,  // original attachment table
            (LPSPropTagArray) &sPropAttachNum,  // only want PR_ATTACH_NUM columns
            NULL,           // restriction pointer
            NULL,           // sort order set pointer
            0,              // maximum rows--defaults to all
            &lpRows);

    switch (hr)
    {
        case MAPI_W_POSITION_CHANGED:
            // Location in table changed by somebody else.
            // Warn the user.
            EventLogMsg( 
            	GWCLEAN_POSCHANGED,
            	0,
            	0);

            hr = HR_LOG(E_FAIL);

            goto cleanup; 

        default:
            if ( FAILED(hr) )
            {
                INTERNAL_ERROR( TEXT("HrQueryAllRows()"), hr);

                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            break;

    }   // end switch()

    ASSERT_READ_PTR( lpRows, sizeof(SRowSet), "Bad lpRows");
    
    // If there are no attachments for this message,
    // we are done.  Return!
    if ( !(lpRows->cRows) )
    {
        goto cleanup;
    }

    // Get all the attachments for the new envelope.
    hr = HrQueryAllRows(
            lpNewAttachTable,   // new message attachment table
            (LPSPropTagArray) &sPropAttachNum,  // only want PR_ATTACH_NUM columns
            NULL,               // restriction pointer
            NULL,               // sort order set pointer
            0,                  // maximum rows--defaults to all
            &lpNewRows);

    switch (hr)
    {
        case MAPI_W_POSITION_CHANGED:
            // Location in table changed by somebody else.
            // Warn the user.
            EventLogMsg( 
                GWCLEAN_POSCHANGED,
            	0,
            	0);

            hr = HR_LOG(E_FAIL);

            goto cleanup; 

        default:
            if ( FAILED(hr) )
            {
                INTERNAL_ERROR( TEXT("HrQueryAllRows()"), hr);

                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

        break;

    }   // end switch()

    ASSERT_READ_PTR( lpNewRows, sizeof(SRowSet), "Bad lpNewRows");
    ASSERTERROR(lpNewRows->cRows == lpRows->cRows, "Bad lpNewRows count");

    // Handle each attachment
    for ( ulLoopCounter = 0; ulLoopCounter < lpRows->cRows; ulLoopCounter++ )
    {
        // Release MAPI objects
        ULRELEASE(lpMessage);
        ULRELEASE(lpAttachment);

        // Get entry identifier information for attachment.
        ulAttachNum = lpRows->aRow[ulLoopCounter].lpProps[0].Value.ul;

        // Open the attachment specified by the entry identifier.
        hr = lpParent->OpenAttach(
                                    ulAttachNum, 
                                    0, 
                                    MAPI_DEFERRED_ERRORS,   // reduces RPCs
                                    &lpAttachment);

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("IMessage::OpenAttach()"), hr);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        ASSERT_IUNKNOWN_PTR( lpAttachment, "Bad lpAttachment");

        // Try to open the attachment as a message.
        hr = lpAttachment->OpenProperty(PR_ATTACH_DATA_OBJ,
                                    &IID_IMessage,  // interface identifier
                                    0,
                                    MAPI_DEFERRED_ERRORS,  // reduces RPCs
                                    (LPUNKNOWN FAR *) &lpMessage);

        switch (hr)
        {
            case MAPI_E_INTERFACE_NOT_SUPPORTED:
            case MAPI_E_NOT_FOUND:
                // The attachment is not a message. 
                // Try the next attachment.
                hr = HR_LOG(NOERROR);   // This isn't a failure!

                continue;   // go to next attachment

            default:

                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("IMAPIProp::OpenProperty()"), hr);

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                break;
        }   // end switch

        ASSERT_IUNKNOWN_PTR( lpMessage, "Bad lpMessage");

        // Find the new attachment corresponding to the old attachment.
        for ( ulLoopCount2 = 0; ulLoopCount2 < lpRows->cRows; ulLoopCount2++ )
        {
            // Free MAPI structures
            MAPIFREEBUFFER(lpSearchKey);
            MAPIFREEBUFFER(lpSearchKeyNew);

            // Release MAPI objects
            ULRELEASE(lpNewAttachment);
            ULRELEASE(lpNewMessage);

            // Get entry identifier information for new message attachment.
            ulNewAttachNum = lpNewRows->aRow[ulLoopCount2].lpProps[0].Value.ul;

            // Open the attachment specified by the new entry identifier.
            hr = lpNewParent->OpenAttach(
                                    ulNewAttachNum, 
                                    0, 
                                    MAPI_MODIFY | MAPI_DEFERRED_ERRORS, 
                                    &lpNewAttachment);

            if ( FAILED(hr) )
            {
                INTERNAL_ERROR( TEXT("IMessage::OpenAttach()"),  hr);

                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            ASSERT_IUNKNOWN_PTR( lpNewAttachment, "Bad lpNewAttachment");

            // Open the new attachment as a message
            hr = lpNewAttachment->OpenProperty(PR_ATTACH_DATA_OBJ,
                                       &IID_IMessage,
                                       0,
                                       MAPI_MODIFY | MAPI_DEFERRED_ERRORS,
                                       (LPUNKNOWN FAR *) &lpNewMessage);

            switch (hr)
            {
                case MAPI_E_INTERFACE_NOT_SUPPORTED:
                case MAPI_E_NOT_FOUND:
                    // Not this attachment! (not an error)                
                    hr = HR_LOG(NOERROR);

                    // Try the next attachment
                    continue;                

                default:
                
                    if ( FAILED(hr) )
                    {  
                        INTERNAL_ERROR( TEXT("IMAPIProp::OpenProperty()"), hr);

                        hr = HR_LOG(E_FAIL);
                        goto cleanup;
                    }

                    break;

            }   // end switch

            ASSERT_IUNKNOWN_PTR( lpNewMessage, "Bad lpNewMessage");

            // Compare search key of new message to search key of
            // old message.  If not the same, try next new attachment
            // in table.
            hr = HrMAPIGetPropBinary(
                            (LPMAPIPROP) lpNewMessage,
                            PR_SEARCH_KEY,
                            &ulCountNew,
                            (LPVOID FAR *) &lpSearchKeyNew);

            if ( FAILED(hr) )
            {
                INTERNAL_ERROR( TEXT("HrMAPIGetPropBinary()"), hr);

                goto cleanup;
            }

            hr = HrMAPIGetPropBinary(
                            (LPMAPIPROP) lpMessage,
                            PR_SEARCH_KEY,
                            &ulCount,
                            (LPVOID FAR *) &lpSearchKey);

            if ( FAILED(hr) )
            {
                INTERNAL_ERROR( TEXT("HrMAPIGetPropBinary()"), hr);

                goto cleanup;
            }

            ASSERTERROR(ulCount == ulCountNew, "Bad ulCount");

            // manually compare search keys. (PR_SEARCH_KEY is comparable)
            bFound = FALSE;
            if ( memcmp(lpSearchKey, lpSearchKeyNew, ulCount) == 0 )
            {
                // Found correct new attachment.
                bFound = TRUE;
                break;
            }

        }   // end for

        // Make sure we found the corresponding attachment.
        if ( !bFound )
        {
            INTERNAL_ERROR( TEXT("HrCopyGWAttachProps()"),  E_FAIL);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Create and copy all properties in new attachment which aren't
        // in the old attachment.
        hr = HrCreateNewProps(lpMessage, lpNewMessage);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Call this function recursively to handle all attached messages.
        hr = HrCopyGWAttachProps(lpMessage, lpNewMessage);

        if ( FAILED(hr) )
        {
            goto cleanup;
        }

        // Save changes to the new message.
        hr = lpNewMessage->SaveChanges(KEEP_OPEN_READWRITE);
        
        if ( FAILED(hr) )
        {
            // check for insufficient disk space
            if ( hr == MAPI_E_NOT_ENOUGH_DISK )
            {
                EventLogMsg( 
                	GWCLEAN_OUTOFDISK,
                	0,
                	0);

				hr = HR_LOG(E_FAIL);

				goto cleanup;
            }

			else
			{
                INTERNAL_ERROR( TEXT("IMAPIProp::SaveChanges()"), hr);

            	hr = HR_LOG(E_FAIL);
            	goto cleanup;
			}
        }	// end if save changes failure

        // Save changes to the new attachment
        hr = lpNewAttachment->SaveChanges(KEEP_OPEN_READWRITE);
        
        if ( FAILED(hr) )
        {
            // check for insufficient disk space
            if ( hr == MAPI_E_NOT_ENOUGH_DISK )
            {
                EventLogMsg( 
                	GWCLEAN_OUTOFDISK,
                	0,
                	0);

				hr = HR_LOG(E_FAIL);

				goto cleanup;
            }

			else
			{
                INTERNAL_ERROR( TEXT("IMAPIProp::SaveChanges()"), hr);

            	hr = HR_LOG(E_FAIL);
            	goto cleanup;
			}
        }
    }   // end for

cleanup:

    // Release the MAPI objects
    ULRELEASE(lpAttachTable);
    ULRELEASE(lpNewAttachTable);
    ULRELEASE(lpMessage);
    ULRELEASE(lpNewMessage);
    ULRELEASE(lpAttachment);
    ULRELEASE(lpNewAttachment);

    // Free  MAPI structures.  (SRowSet is special!)
    FREEPROWS(lpRows);
    FREEPROWS(lpNewRows);

    MAPIFREEBUFFER(lpSearchKey);
    MAPIFREEBUFFER(lpSearchKeyNew);

    RETURN(hr);

}   // end CGWClean::CopyGWAttachProps()

//$--CGWClean::HrCreateNewProps----------------------------------------------------
//
// DESCRIPTION: Determine which properties didn't get copied
//              to the new message by CopyMessages(), and then
//              create and set those properties on the new message.
//
// INPUT:       LPMESSAGE --  Original message pointer
//              LPMESSAGE --  New message pointer
//
// RESULT:      HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------

HRESULT CGWClean::HrCreateNewProps(   // RETURNS: HRESULT
    IN LPMESSAGE lpMessage,         // source message
    IN LPMESSAGE lpNewMessage)                // destination message
{
    const   INT iMaxSize    =   124;    // maximum number of properties to create
    HRESULT hr  =   NOERROR;    // return code
    ULONG   ulCount =   0;      // # props for original message
    ULONG   ulNewCount  =   0;  // # props for new message
    LPSPropValue    lpsPropValues   =   NULL;   // original message properties and values
    LPSPropValue    lpsPropNewValues    =   NULL;   // new message properties and values
    ULONG   ulLoopCount =   0;  // loop counter
    ULONG   ulLoopCount2    =   0;  // second loop counter
    ULONG   ulOrigProp  =   0;  // original message property tag
    BOOL    bFound  =   FALSE;  // TRUE if property is found in new message
    MAPINAMEID  rgNamedMsgProps[iMaxSize] =   {0}; // array of named property structures for "extra" message properties
    LPMAPINAMEID    lpNamedMsgProps[iMaxSize] =   {0};    // array of pointers to MAPINAMEID structures
    ULONG   ulCreated   =   0;  // number of named properties created in new message
    SPropValue  lpsCreatedPropValues[iMaxSize]   =   {0};    // values of created properties
    LPSPropTagArray lpsNewPropTags  =   NULL;   // new named property tags
    WCHAR   lpPropNames[iMaxSize][80]  =   {0};    // named property array
    LPCWSTR lpBaseName  =   L"GWMSGPROP";   // base name for named property
    LPSPropProblemArray    lpsPropProblems =   NULL;   // for SetProps call
    WCHAR   lpTempString[10]    =   {0};        // temporary string for _itow

    DEBUGPRIVATE("CGWClean::HrCreateNewProps()\n");

    // check input parameters
    hr = CHK_CGWClean_HrCreateNewProps(lpMessage, lpNewMessage);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    // Get all properties for the original message
    hr = lpMessage->GetProps(NULL,  // get all properties
                                 0,     // flags
                                 &ulCount,  // number of properties
                                 &lpsPropValues);   // property value array pointer

    if ( hr == MAPI_W_ERRORS_RETURNED )
    {
        // May not have enough memory to get PR_BODY, PR_RTF_COMPRESSED
        // and PR_ATTACH_DATA_BIN properties if they are very large.
        // This is not really an error.  
        // CopyMessages will copy over all properties that it can.
        // Then, we are only interested in copying over properties which
        // exist in old object but not in the new.
        hr = HR_LOG(NOERROR);
    }

    if ( FAILED(hr) )
    {	
        INTERNAL_ERROR( TEXT("IMAPIProp::GetProps()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERT_READ_PTR( lpsPropValues, sizeof(SPropValue), "Bad lpsPropValues");

   // Get all properties from the new messsage.
   hr = lpNewMessage->GetProps(NULL,  // get all properties
                                 0,     // flags
                                 &ulNewCount,  // number of properties
                                 &lpsPropNewValues);   // property value array pointer

    if ( hr == MAPI_W_ERRORS_RETURNED )
    {
        // May not have enough memory to get PR_BODY, PR_RTF_COMPRESSED
        // and PR_ATTACH_DATA_BIN properties if they are very large.
        // This is not really an error.  
        // CopyMessages will copy over all properties that it can.
        // Then, we are only interested in copying over properties which
        // exist in old object but not in the new.
        hr = HR_LOG(NOERROR);
    }
   
    if ( FAILED(hr) )
    {
        INTERNAL_ERROR( TEXT("IMAPIProp::GetProps()"), hr);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ASSERT_READ_PTR( lpsPropNewValues, sizeof(SPropValue), "Bad lpsPropNewValues");
    
    // If the number of properties in both messages is the same,
    // then we are done.  Otherwise, we need to create all properties
    // in the new message which are in the original message, but which
    // are not currently in the new message.
    if ( ulCount != ulNewCount )
    {
        for ( ulLoopCount = 0; ulLoopCount < ulCount; ulLoopCount++ )
        {
            // Get next original message property
            ulOrigProp = lpsPropValues[ulLoopCount].ulPropTag;

            bFound = FALSE; // initialize found flag

            // Search for original property in the new message.
            for ( ulLoopCount2 = 0; ulLoopCount2 < ulNewCount; ulLoopCount2++ )
            {
                if ( PROP_ID(lpsPropNewValues[ulLoopCount2].ulPropTag) ==
                     PROP_ID(ulOrigProp) )
                {
                    // We found it.  Done with this property check
                    bFound = TRUE;
                    break;
                }    
            }   // end for

            // If we didn't find the property in the new message,
            // create it now.
            if ( !bFound )
            {
                // Create a named property in the new message for the
                // original property in the old message
                // (Set up structures here.  Create when all found.)
                ASSERTERROR(ulCreated < iMaxSize, "Bad ulCreated");

                rgNamedMsgProps[ulCreated].lpguid = (LPGUID) &PS_PUBLIC_STRINGS;
                rgNamedMsgProps[ulCreated].ulKind = MNID_STRING;

                // Named property will be GWMSGPROP# where # is an integer
                // starting at 0.
                lstrcpyW(lpPropNames[ulCreated], lpBaseName);
                lstrcatW(lpPropNames[ulCreated], _itow(ulCreated, lpTempString, 10));
                rgNamedMsgProps[ulCreated].Kind.lpwstrName = lpPropNames[ulCreated];

                lpNamedMsgProps[ulCreated] = &(rgNamedMsgProps[ulCreated]);

                // Set up the value for the created property and the property tag type.
                lpsCreatedPropValues[ulCreated].Value = lpsPropValues[ulLoopCount].Value;
                lpsCreatedPropValues[ulCreated].ulPropTag = lpsPropValues[ulLoopCount].ulPropTag;

                // increment count of named message properties created
                ulCreated++;

            }   // end if not found
        }   // end for

        // Create the needed named properties
        hr = lpNewMessage->GetIDsFromNames(ulCreated,    // # of names
                                           (LPMAPINAMEID FAR *) lpNamedMsgProps,// array of names
                                           MAPI_CREATE,     // flags
                                           &lpsNewPropTags);// address of property tags

        switch ( hr )
        {
            case MAPI_W_ERRORS_RETURNED:
                INTERNAL_ERROR( TEXT("IMAPIProp::GetIDsFromNames()"), hr);

                hr = HR_LOG(E_FAIL);
                goto cleanup;

            case MAPI_E_NOT_ENOUGH_DISK:
                // insufficient disk space
                EventLogMsg( 
                	GWCLEAN_OUTOFDISK,
                	0,
                	0);

                hr = HR_LOG(E_FAIL);

                goto cleanup;

            default:
                if ( FAILED(hr) )
                {
                    INTERNAL_ERROR( TEXT("IMAPIProp::GetIDsFromNames()"), hr);

                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                break;
            
        }   // end switch

        // Keep the original property type, but replace the
        // proptery ID with the new named property ID.
        for ( ulLoopCount2 = 0; ulLoopCount2 < ulCreated; ulLoopCount2++ )
        {
            lpsCreatedPropValues[ulLoopCount2].ulPropTag = PROP_TAG(
               PROP_TYPE(lpsCreatedPropValues[ulLoopCount2].ulPropTag),
               PROP_ID(lpsNewPropTags->aulPropTag[ulLoopCount2]));

        }   // end for

        // Set the values of the new named properties
        hr = lpNewMessage->SetProps(ulCreated, // number of properties
                                    lpsCreatedPropValues,  // Property tags and values
                                    &lpsPropProblems);    // problem structure

        if ( FAILED(hr) )
        {
            INTERNAL_ERROR( TEXT("IMAPIProp::SetProps()"), hr);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }   // end if some properties not already copied over
    
cleanup:

    // free MAPI buffers
    MAPIFREEBUFFER(lpsPropValues);
    MAPIFREEBUFFER(lpsPropNewValues);
    MAPIFREEBUFFER(lpsNewPropTags);
    MAPIFREEBUFFER(lpsPropProblems);

    // Release MAPI and OLE objects

    RETURN(hr);

}

/*
 * EOF
 */
