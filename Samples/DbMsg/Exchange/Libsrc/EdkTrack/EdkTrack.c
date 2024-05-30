// --edktrack.c-----------------------------------------------------------------
// 
//  Module containing gateway tracking functions.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "sadapi.h"

#include "edktrack.chk"

//$--HrTrackInitLog-------------------------------------------------------------
//  This function initializes the gateway event tracking module.
// -----------------------------------------------------------------------------
HRESULT HrTrackInitLog(             // RETURNS: return code
	IN LPSTR lpszComputer,          // name of the remote computer
    OUT PVOID *ppvSession)          // pointer to gateway tracking session
{
    HRESULT      hr        = NOERROR;
    RPC_SC       sc        = ERROR_SUCCESS;
    PRPCBINDINFO lpSession = NULL;

    DEBUGPUBLIC("HrTrackInitLog()");

    hr = CHK_HrTrackInitLog( lpszComputer, ppvSession);
    if(FAILED(hr))
        RETURN(hr);

    *ppvSession = NULL;

    hr = MAPIAllocateBuffer( sizeof(RPCBINDINFO), &lpSession);
    if( FAILED( hr))
        goto cleanup;                                

    ZeroMemory( lpSession, sizeof(RPCBINDINFO));

    __try
    {
	    sc = SAD_ScBindA(lpSession, lpszComputer);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());
        sc = RPC_E_UNEXPECTED;
    }

	if(sc != ERROR_SUCCESS)
	{
        hr = HR_LOG(E_FAIL);    
        goto cleanup;
	}

    *ppvSession = (PVOID)lpSession;

cleanup:
    if( FAILED( hr))
        MAPIFREEBUFFER( lpSession);

    RETURN( hr);
}

//$--HrTrackWriteLog@-------------------------------------------------------
//  This function logs a gateway tracking event.
// ----------------------------------------------------------------------------
HRESULT HrTrackWriteLogW(
    IN PVOID           pvSession,       // gateway tracking session
    IN UINT            nEventType,      // gateway tracking event type
    IN SYSTEMTIME      stEvent,         // time event took place
    IN LPCWSTR         lpszGatewayName, // gateway name
    IN LPCWSTR         lpszPartner,     // pointer to entity name string
    IN LPCWSTR         lpszMTSID,       // pointer to MTS-ID string
    IN LPCWSTR         lpszSubjectMTSID,// pointer to subject MTS-ID string
    IN LPCWSTR         lpszRemoteID,    // pointer to foreign ID string
    IN LPCWSTR         lpszOriginator,  // pointer to originator string
    IN INT             nPriority,       // message priority
    IN INT             nLength,         // message length
    IN INT             nSeconds,        // seconds to process this message
    IN INT             nCost,           // cost of processing this message
    IN INT             cRecipients,     // count of recipients
    IN LPCWSTR        *lppszRecipients) // pointer to recipient pointers
{
    HRESULT     hr                = NOERROR;
    RPC_SC      sc                = ERROR_SUCCESS;
    RPCBINDINFO *lpSession        = NULL;

    RPC_GATEWAY_TRACK_INFORMATION gti = {0};

    DEBUGPUBLIC("HrTrackWriteLogW()");

    hr = CHK_HrTrackWriteLogW(
        pvSession, nEventType, stEvent,
        lpszGatewayName, lpszPartner, lpszMTSID,
        lpszSubjectMTSID, lpszRemoteID, lpszOriginator,
        nPriority, nLength, nSeconds, nCost,
        cRecipients, lppszRecipients);
    if(FAILED(hr))
        RETURN(hr);

    lpSession = (PRPCBINDINFO)pvSession;

    gti.nEventType               = nEventType;

    gti.stEvent.rgwSystemTime[0] = stEvent.wYear;
    gti.stEvent.rgwSystemTime[1] = stEvent.wMonth;
    gti.stEvent.rgwSystemTime[2] = stEvent.wDayOfWeek;
    gti.stEvent.rgwSystemTime[3] = stEvent.wDay;
    gti.stEvent.rgwSystemTime[4] = stEvent.wHour;
    gti.stEvent.rgwSystemTime[5] = stEvent.wMinute;
    gti.stEvent.rgwSystemTime[6] = stEvent.wSecond;
    gti.stEvent.rgwSystemTime[7] = stEvent.wMilliseconds;

    // Strings already WCHAR
    gti.szGatewayName = (LPWSTR)lpszGatewayName;
    gti.szPartner     = (LPWSTR)lpszPartner;
    gti.szMTSID       = (LPWSTR)lpszMTSID;
    gti.szSubjectID   = (LPWSTR)lpszSubjectMTSID;
    gti.szRemoteID    = (LPWSTR)lpszRemoteID;
    gti.szOriginator  = (LPWSTR)lpszOriginator;

    gti.nPriority       = nPriority;
    gti.nLength         = nLength;
    gti.nSeconds        = nSeconds;
    gti.nCost           = nCost;

    __try
    {
        sc = SAD_ScSaveGatewayTrackingData(
            lpSession,
    	    &gti,
    	    cRecipients,
    	    (LPWSTR*)lppszRecipients);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());
        sc = RPC_E_UNEXPECTED;
    }

    if(sc != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

cleanup:
    RETURN(hr);
}

HRESULT HrTrackWriteLogA(
    IN PVOID           pvSession,       // gateway tracking session
    IN UINT            nEventType,      // gateway tracking event type
    IN SYSTEMTIME      stEvent,         // time event took place
    IN LPCSTR          lpszGatewayName, // gateway name
    IN LPCSTR          lpszPartner,     // pointer to entity name string
    IN LPCSTR          lpszMTSID,       // pointer to MTS-ID string
    IN LPCSTR          lpszSubjectMTSID,// pointer to subject MTS-ID string
    IN LPCSTR          lpszRemoteID,    // pointer to foreign ID string
    IN LPCSTR          lpszOriginator,  // pointer to originator string
    IN INT             nPriority,       // message priority
    IN INT             nLength,         // message length
    IN INT             nSeconds,        // seconds to process this message
    IN INT             nCost,           // cost of processing this message
    IN INT             cRecipients,     // count of recipients
    IN LPCSTR         *lppszRecipients) // pointer to recipient pointers
{
    HRESULT     hr                = NOERROR;
    RPC_SC      sc                = ERROR_SUCCESS;
    RPCBINDINFO *lpSession        = NULL;
    LPWSTR      *lppszRecipientsW = NULL;

    RPC_GATEWAY_TRACK_INFORMATION gti = {0};

    DEBUGPUBLIC("HrTrackWriteLogA()");

    hr = CHK_HrTrackWriteLogA(
        pvSession, nEventType, stEvent,
        lpszGatewayName, lpszPartner, lpszMTSID,
        lpszSubjectMTSID, lpszRemoteID, lpszOriginator,
        nPriority, nLength, nSeconds, nCost, 
        cRecipients, lppszRecipients);
    if(FAILED(hr))
        RETURN(hr);

    lpSession = (PRPCBINDINFO)pvSession;

    gti.nEventType               = nEventType;

    gti.stEvent.rgwSystemTime[0] = stEvent.wYear;
    gti.stEvent.rgwSystemTime[1] = stEvent.wMonth;
    gti.stEvent.rgwSystemTime[2] = stEvent.wDayOfWeek;
    gti.stEvent.rgwSystemTime[3] = stEvent.wDay;
    gti.stEvent.rgwSystemTime[4] = stEvent.wHour;
    gti.stEvent.rgwSystemTime[5] = stEvent.wMinute;
    gti.stEvent.rgwSystemTime[6] = stEvent.wSecond;
    gti.stEvent.rgwSystemTime[7] = stEvent.wMilliseconds;

    // Convert strings to WCHAR
    hr = HrStrAToStrW( lpszGatewayName, &gti.szGatewayName);
    if(FAILED(hr))
	    goto cleanup;

    hr = HrStrAToStrW( lpszPartner, &gti.szPartner);
    if(FAILED(hr))
	    goto cleanup;

    hr = HrStrAToStrW( lpszMTSID, &gti.szMTSID);
    if(FAILED(hr))
	    goto cleanup;

    hr = HrStrAToStrW( lpszSubjectMTSID, &gti.szSubjectID);
    if(FAILED(hr))
	    goto cleanup;

    hr = HrStrAToStrW( lpszRemoteID, &gti.szRemoteID);
    if(FAILED(hr))
	    goto cleanup;

    hr = HrStrAToStrW( lpszOriginator, &gti.szOriginator);
    if(FAILED(hr))
	    goto cleanup;

    gti.nPriority       = nPriority;
    gti.nLength         = nLength;
    gti.nSeconds        = nSeconds;
    gti.nCost           = nCost;

	if(cRecipients != 0)
	{
        ULONG   cb          = 0L;
        int     iRecipients = 0;

        cb = cRecipients * (sizeof(LPWSTR) + MAX_ALIGN);

	    hr = MAPIAllocateBuffer( 
            cb, (PVOID)&lppszRecipientsW);
        if( FAILED( hr))
            goto cleanup;                                

        ZeroMemory( lppszRecipientsW, cb);

		for(iRecipients = 0; iRecipients < cRecipients; iRecipients++)
		{
			if(lppszRecipients[iRecipients] == NULL)
            {
                hr = HR_LOG(E_FAIL);
    		    goto cleanup;
            }

            hr = HrStrAToStrW(
                lppszRecipients[iRecipients],
                &lppszRecipientsW[iRecipients]);
            if(FAILED(hr))
    		    goto cleanup;
		}
	}

    __try
    {
        sc = SAD_ScSaveGatewayTrackingData(
            lpSession,
    	    &gti,
    	    cRecipients,
    	    lppszRecipientsW);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());
        sc = RPC_E_UNEXPECTED;
    }

    if(sc != ERROR_SUCCESS)
    {
        hr = HR_LOG(E_FAIL);
		goto cleanup;
    }

cleanup:
    MAPIFREEBUFFER(gti.szGatewayName);
    MAPIFREEBUFFER(gti.szPartner);
    MAPIFREEBUFFER(gti.szMTSID);
    MAPIFREEBUFFER(gti.szSubjectID);
    MAPIFREEBUFFER(gti.szRemoteID);
    MAPIFREEBUFFER(gti.szOriginator);

	if(cRecipients != 0 && lppszRecipientsW != NULL)
	{
        int iRecipients = 0;

		for(iRecipients = 0; iRecipients < cRecipients; iRecipients ++)
            MAPIFREEBUFFER(lppszRecipientsW[iRecipients]);

        MAPIFREEBUFFER(lppszRecipientsW);
	}

    RETURN(hr);
}

//$--HrTrackUninitLog----------------------------------------------------------
//  This function uninitializes the gateway event tracking module.
// ----------------------------------------------------------------------------
HRESULT HrTrackUninitLog(               // RETURNS: return code
    IN OUT PVOID *ppvSession)           // pointer to gateway tracking session
{
    HRESULT      hr        = NOERROR;
    PRPCBINDINFO lpSession = NULL;

    DEBUGPUBLIC("HrTrackUninitLog()");

    hr = CHK_HrTrackUninitLog(
        ppvSession);
    if(FAILED(hr))
        RETURN(hr);

    lpSession = (PRPCBINDINFO)*ppvSession;

    __try
    {
	    SAD_Unbind(lpSession);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());
        hr = HR_LOG(E_FAIL);
    }

    MAPIFREEBUFFER( *ppvSession);

    RETURN(hr);
}
