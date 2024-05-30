// --newpst.cpp---------------------------------------------------------------
//
// Implementation of the newpst library
//
// Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
//-----------------------------------------------------------------------------

#include "edk.h"
#include "mspst.h"
#include "newpst.chk"

//
// Static storage
//

static BOOL					fProfileCreated =	FALSE;

static LPPROFADMIN			lpProfAdmin     =   NULL;
static LPSERVICEADMIN		lpSvcAdmin      =	NULL;

static MAPIUID				MsgStoreUID     =   {0};

//
// Functions
//

// $--HrCreatePersonalStore----------------------------------------------------------
//
// DESCRIPTION: Create a New PST with properties determined by the input
//				parameters in a temporary profile.  The name and password
//				of the temporary PST are returned to the user.
//
// INPUT:
//
//	[lpszPSTPath]			-- Value for PR_PST_PATH (new PST path).
//	[dwEncryption]			-- Value for PR_PST_ENCRYPTION (TBS).
//	[lpszPSTDisplayName]	-- Value for PR_DISPLAY_NAME (new PST display name).
//	[lpszPSTPassword]		-- Value for PR_PST_PW_SZ_NEW (new PST password,
//							   NULL not accepted).
//
// OUTPUT:
//
//	lppszProfileName		-- Ptr that will be set to point at temporary
//							   profile name on return; this may be used to
//							   establish a MAPI session.
//	lppszProfilePassword	-- Ptr that will be set to point at temporary
//							   profile password on return; this may be used to
//							   establish a MAPI session.
//
// RETURNS:     NOERROR on success,
//              E_INVALIDARG if bad input,
//              E_ACCESSDENIED if can access profile
//  `           E_OUTOFMEMORY if memory problems
//              E_FAIL on general failure.
//
// Notes:		Successive calls to CreateNewPST() should not be made without
//				intervening calls to NewPSTCleanup().  Due to use of internal
//				static storage for objects and profile strings, only one new
//				PST may be created and used at a time.
//
//---------------------------------------------------------------------------

HRESULT HrCreatePersonalStore(                 // RETURNS HRESULT
	IN	LPSTR	lpszPSTPath,            // new PST fully-pathed name
	IN	DWORD	dwEncryption,           // encryption level
	IN	LPSTR	lpszPSTDisplayName,     // PR_DISPLAY_NAME value
	IN	LPSTR	lpszPSTPassword,        // new PST password
	OUT	LPSTR *	lppszProfileName,       // temporary profile name
	OUT	LPSTR *	lppszProfilePassword    // temporary profile password
	)
{
	HRESULT			hr          =           NOERROR;
	LPSPropValue	aPropVals   =			NULL;
	LPSRowSet		lpRows      =			NULL;
	LPMAPITABLE		lpTable     =			NULL;
    const UINT      cbProfile   =           14;     // # chars in temporary profile name
    const UINT      cbPassword  =           1;      // # char in temporary password      

    DEBUGPUBLIC("HrCreatePersonalStore()\n");

    // Check input values
    hr = CHK_HrCreatePersonalStore(lpszPSTPath, dwEncryption, lpszPSTDisplayName,
                            lpszPSTPassword, lppszProfileName,
                            lppszProfilePassword);
                                
    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

	// Make sure we have not previously called CreateNewPST() without
	// an intervening NewPSTCleanup() call.  When this occurs, we just
	// return E_FAIL and do no cleanup, thus leaving the 
	// previous profile and PST in place.

	if (lpProfAdmin != NULL)
	{
		hr = HR_LOG(E_FAIL);

        goto cleanup;
	}

	// Get a profile administration object.

	hr = MAPIAdminProfiles(0, &lpProfAdmin);

	if (FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);

		goto cleanup;
    }

    // Allocate memory for temporary profile and password.
	// Create the temporary profile.
    hr = MAPIAllocateBuffer(cbPassword * sizeof(CHAR),   // one character password
                            (PVOID *) lppszProfilePassword);  // pointer to string pointer

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    hr = MAPIAllocateBuffer(cbProfile * sizeof(CHAR),
                            (PVOID *) lppszProfileName);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_OUTOFMEMORY);

        goto cleanup;
    }

    ASSERTERROR(!IsBadWritePtr(lppszProfileName, sizeof(LPSTR)),
                "Bad lppszProfileName");
    ASSERTERROR(!IsBadWritePtr(lppszProfilePassword, sizeof(LPSTR)),
                "Bad lppszProfilePassword");

	{
		int		i;

		**lppszProfilePassword = '\0';  // no password

		for (i = 0; (i < 1000) && (!fProfileCreated); i++)
		{
			sprintf(*lppszProfileName, "PstLoadTmp%03.3u", i);

			hr = lpProfAdmin->CreateProfile(*lppszProfileName,
											*lppszProfilePassword,
											0,
											0);

            switch (hr) 
            {                
               case MAPI_E_NO_ACCESS:   // name collision

                hr = HR_LOG(E_ACCESSDENIED);

                break;

               default:
                if ( FAILED(hr) )
                {
                    hr = HR_LOG(E_FAIL);

                    goto cleanup;
                }

                fProfileCreated = TRUE;
                
            }   // end switch   
		}   // end for

		if (i == 1000)
        {
			goto cleanup;	// MAPI_E_NO_ACCESS will be returned.
        }
	}

	// Get a service administration object.

	hr = lpProfAdmin->AdminServices(*lppszProfileName,
									*lppszProfilePassword,
									0,
									0,
									&lpSvcAdmin);
	if (FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        
		goto cleanup;
    }

	// Add the MS Personal Information Store service to the temporary profile.
	// This will also happen to be set as the default store.

	hr = lpSvcAdmin->CreateMsgService("MSPST MS",
									  "", // UI not used, so not needed.
									  0,
									  0);

	if (FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);

		goto cleanup;
    }

	// Configure the MS Personal Information Store per NewPST entries.

	{
		ULONG			cValues =   0;
		LPSPropValue	lpProp  =   NULL;

    	hr = lpSvcAdmin->GetMsgServiceTable(0, &lpTable);

		if (FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);

			goto cleanup;
        }

		// We don't need to worry about checking all the columns; there should
		// only be one since we just created the profile and added one service.

    	hr = lpTable->QueryRows(1, 0, &lpRows);

    	if (FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            
			goto cleanup;
        }

    	if (lpRows == NULL)
		{
			hr = HR_LOG(E_FAIL);	// highly unlikely.

			goto cleanup;
		}

    	cValues =	lpRows->aRow[0].cValues;
    	lpProp =	lpRows->aRow[0].lpProps;

    	while (cValues)
    	{
        	if (lpProp->ulPropTag == PR_SERVICE_UID)
			{
				MsgStoreUID = *((LPMAPIUID)lpProp->Value.bin.lpb);
				break;
			}

        	lpProp++;
			cValues--;
    	}

		if (cValues == 0)
		{
			hr = HR_LOG(E_FAIL);	// highly unlikely.

			goto cleanup;
		}

		cValues = 6;

		hr = MAPIAllocateBuffer(cValues * sizeof(SPropValue),
								(LPVOID *)&aPropVals);

        if ( FAILED(hr) )
        {
            hr = HR_LOG(E_OUTOFMEMORY);

			goto cleanup;
		}

		aPropVals[0].ulPropTag =	PR_DISPLAY_NAME;
		aPropVals[0].Value.lpszA =	lpszPSTDisplayName;

		aPropVals[1].ulPropTag =	PR_PST_PATH;
		aPropVals[1].Value.lpszA =	lpszPSTPath;;

		aPropVals[2].ulPropTag =	PR_PST_REMEMBER_PW;
		aPropVals[2].Value.b =		TRUE;

		aPropVals[3].ulPropTag =	PR_PST_ENCRYPTION;
		aPropVals[3].Value.l =		dwEncryption;

		aPropVals[4].ulPropTag =	PR_PST_PW_SZ_NEW;
		aPropVals[4].Value.lpszA =	lpszPSTPassword;

		aPropVals[5].ulPropTag =	PR_PST_PW_SZ_OLD;
		aPropVals[5].Value.lpszA =	*lppszProfilePassword;

		hr = lpSvcAdmin->ConfigureMsgService(&MsgStoreUID,
											 0,
											 0,
											 cValues,
											 aPropVals);
		if (FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            
			goto cleanup;
        }
	}

cleanup:

    FREEPROWS(lpRows);

	ULRELEASE(lpTable);

    MAPIFREEBUFFER(aPropVals);

	// This makes it an "all or none" call.

	if ( FAILED(hr) )
    {
        if ( lppszProfileName )
        {
            // remove temporary profile and 
            // release administration service.
		    HrCleanupPSTGlobals(*lppszProfileName);

            MAPIFREEBUFFER(*lppszProfileName);
        }

        if ( lppszProfilePassword )
        {
            MAPIFREEBUFFER(*lppszProfilePassword);
        }
    }   // end if failure

	RETURN(hr);
}


// $--HrCleanupPSTGlobals-----------------------------------------------------------
//
// DESCRIPTION: Release objects involved in creation of a new PST.
//
// INPUT:       temporary profile name
//
// RETURNS:     NOERROR on success,
//              E_FAIL if error.
//
// Notes:		This should be called after Logoff() and Release() are called
//				for the LPSESSION and before MAPIUninitialize() is called.
//---------------------------------------------------------------------------

HRESULT HrCleanupPSTGlobals(         // RETURNS: HRESULT
        IN LPSTR lpszProfileName)   // temporary profile name
{
	HRESULT		hr  =   NOERROR;    // return code

    DEBUGPUBLIC("HrCleanupPSTGlobals()\n");

    // check input parameters
    hr = CHK_HrCleanupPSTGlobals(lpszProfileName);

    if ( FAILED(hr) )
    {
        RETURN(hr);
    }

    ULRELEASE(lpSvcAdmin);

	if (fProfileCreated)
    {
		hr = lpProfAdmin->DeleteProfile(lpszProfileName, 0);
    }

	ULRELEASE(lpProfAdmin);

	lpSvcAdmin =		NULL;
	fProfileCreated =	FALSE;
	lpProfAdmin =		NULL;

	RETURN(hr);
}
