// --iaddr.c--------------------------------------------------------------------
//
//  Find an address given a proxy address.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "gwsample.h"

//$--HrMapGatewayProxyToAddr----------------------------------------------------
// Map all gateway specific email addresses to proxy addresses
// in a given address list.
// -----------------------------------------------------------------------------
HRESULT HrMapGatewayProxyToAddr(        // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPTSTR       lpszAddrType,      // pointer to the address type
    IN OUT LPADRLIST lpAdrList)         // pointer to address list
{
    HRESULT         hr                   = NOERROR;
    SCODE           sc                   = 0;
    ULONG           i                    = 0;
    ULONG           j                    = 0;
    ULONG           cbAddress            = 0;
    ULONG           cProxy               = 0;
    LPSPropValue    lpProps              = NULL;
    LPTSTR          lpszProxyAddress     = NULL;

    LPTSTR          lpszEmailDisplayName = NULL;
    LPTSTR          lpszEmailAddressType = NULL;
    LPTSTR          lpszEmailAddress     = NULL;
    LPTSTR          lpszEmailSearchKey   = NULL;
    ULONG           cbEmailEid           = 0;
    LPENTRYID       lpEmailEid           = NULL;

    DEBUGPUBLIC("HrMapGatewayProxyToAddr()\n");

    for(i = 0; i < lpAdrList->cEntries; i++)
    {
        lpProps = lpAdrList->aEntries[i].rgPropVals;

        if((lpProps[IDISPNAME].ulPropTag == PR_DISPLAY_NAME) &&
           ((lstrcmpi(lpszSysAdminName, lpProps[IDISPNAME].Value.LPSZ) == 0) ||
            (lstrcmpi(TEXT("."), lpProps[IDISPNAME].Value.LPSZ) == 0) ||
            (lstrcmpi(lpszSysAdminAddr, lpProps[IDISPNAME].Value.LPSZ) == 0)))

        {
            lpszEmailDisplayName = NULL;
            lpszEmailAddressType = NULL;
            lpszEmailAddress     = NULL;
            lpszEmailSearchKey   = NULL;
            cbEmailEid           = 0;
            lpEmailEid           = NULL;

            hr = HrCreateProxyAddress(
                lpAdrBook,
                lpProps,
                TRUE,
                SYSTEM_ADMINISTRATOR,
                SYSTEM,
                SYSTEM_ADMINISTRATOR,
                &lpszEmailDisplayName,
                &lpszEmailAddressType,
                &lpszEmailAddress,
                &lpszEmailSearchKey,
                &cbEmailEid,
                &lpEmailEid);

            if(FAILED(hr))
            {
                goto cleanup;
            }

            lpProps[IDISPNAME].ulPropTag      = PR_DISPLAY_NAME;
            lpProps[IDISPNAME].Value.LPSZ     = lpszEmailDisplayName;

            lpProps[IADDRTYPE].ulPropTag      = PR_ADDRTYPE;
            lpProps[IADDRTYPE].Value.LPSZ     = lpszEmailAddressType;

            lpProps[IEMAILADDR].ulPropTag     = PR_EMAIL_ADDRESS;
            lpProps[IEMAILADDR].Value.LPSZ    = lpszEmailAddress;

            lpProps[ISEARCHKEY].ulPropTag = PR_SEARCH_KEY;

            if(lpszEmailSearchKey == NULL)
            {
                lpProps[ISEARCHKEY].Value.bin.cb  = 0;
                lpProps[ISEARCHKEY].Value.bin.lpb = NULL;
            }
            else
            {
                lpProps[ISEARCHKEY].Value.bin.cb  = cbStrLen(lpszEmailSearchKey);
                lpProps[ISEARCHKEY].Value.bin.lpb = lpszEmailSearchKey;
            }

            lpProps[IENTRYID].ulPropTag       = PR_ENTRYID;
            lpProps[IENTRYID].Value.bin.cb    = cbEmailEid;
            lpProps[IENTRYID].Value.bin.lpb   = (LPBYTE)lpEmailEid;
        }
    }

cleanup:

    RETURN(hr);
}

//$--HrMapRecipProxyToAddr------------------------------------------------------
// Map recipient proxy addresses to addresses.
// -----------------------------------------------------------------------------
HRESULT HrMapRecipProxyToAddr(          // RETURNS: return code
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN BOOL fDefaultRespValue,          // default responsibility value
    IN BOOL fIgnoreRespValue,           // ignore  responsibility value
    IN LPABCONT lpGalABCont,            // pointer to GAL container
    IN LPTSTR lpszAddrType,             // pointer to address type
    IN LPADRLIST lpOriginalAdrList,     // pointer to unmodified address list
    IN LPADRLIST lpMappedAdrList,       // pointer to unmodified address list
    IN OUT LPADRLIST lpEnvelopeAdrList, // pointer to envelope address list
    IN OUT LPADRLIST lpEnvelopeNDRAdrList,// pointer to envelope NDR address list
    IN OUT LPMESSAGE lpMessage,         // pointer to message
    OUT LPADRLIST *lppAdrList,          // pointer to address list
    OUT LPADRLIST *lppNDRAdrList)       // pointer to NDR address list
{
    HRESULT         hrT                  = NOERROR;
    HRESULT         hr                   = NOERROR;
    SCODE           sc                   = 0;
    LPMAPITABLE     lpTable              = NULL;

    ULONG           cbeid                = 0;
    LPENTRYID       lpeid                = NULL;

    ULONG           cRows                = 0;
    LPSRowSet       lpRows               = 0;

    LPSPropTagArray lpPropTagArray       = NULL;

    ULONG           nName                = 0;
    ULONG           nAddrType            = 0;
    ULONG           nAddress             = 0;
    ULONG           nEntryId             = 0;
    ULONG           nSearchKey           = 0;
    ULONG           nRecipStat           = 0;

    ULONG           i                    = 0;
    ULONG           iAck                 = 0;
    ULONG           iNak                 = 0;

    ULONG           cValues              = 0;
    LPSPropValue    lpProps              = NULL;

    LPSPropValue    lpEnvelopeProps      = NULL;
    LPSPropValue    lpMessageProps       = NULL;

    ULONG           cbSearchKey          = 0;
    LPTSTR          lpszSearchKey        = NULL;

    BOOL            fRespTrue            = FALSE;

    FILETIME        ftReportTime         = {0};

    LPSPropValue    lpPropT              = NULL;

    ULONG           cNewProps            = 0;
    LPSPropValue    lpNewProps           = NULL;

    ULONG           cMapValues           = 0;
    LPSPropValue    lpMapProps           = NULL;

    BOOL            fEnv                 = FALSE;

    DEBUGPUBLIC("HrMapRecipProxyToAddr()\n");

    *lppAdrList    = NULL;
    *lppNDRAdrList = NULL;

    //
    // Get the current time.
    //

    GetSystemTimeAsFileTime( &ftReportTime);

    nName      = IDISPNAME;
    nAddrType  = IADDRTYPE;
    nAddress   = IEMAILADDR;
    nEntryId   = IENTRYID;
    nSearchKey = ISEARCHKEY;
    nRecipStat = IRECIPSTAT;

    cRows  = lpOriginalAdrList->cEntries;
    lpRows = (LPSRowSet)lpOriginalAdrList;

    if(lpRows == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(lpEnvelopeAdrList != NULL)
    {
        //
        // Clear recipient numbers if this is not an envelope address list.
        //

        hr = HrDeleteAddressListProperty(
            PR_RECIPIENT_NUMBER,
            (LPADRLIST)lpRows);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    hr = HrMAPICreateSizedAddressList(
        cRows,
        lppAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPICreateSizedAddressList(
        cRows,
        lppNDRAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0; i < cRows; i++)
    {
        //
        // Preserve original recipient number for original recipient entry
        //

        cValues = lpRows->aRow[i].cValues;
        lpProps = lpRows->aRow[i].lpProps;

        cNewProps  = 0;
        lpNewProps = NULL;

        hr = HrSetUlongPropertyValue(
            FALSE,
            PR_RECIPIENT_NUMBER,
            (i+1),
            cValues,
            lpProps,
            &cNewProps,
            &lpNewProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MAPIFREEBUFFER(lpProps);

        lpRows->aRow[i].cValues = cNewProps;
        lpRows->aRow[i].lpProps = lpNewProps;

        cNewProps  = 0;
        lpNewProps = NULL;

        cValues = 0;
        lpProps = NULL;

        //
        // Preserve original recipient number for mapped recipient entry
        //

        cValues = lpMappedAdrList->aEntries[i].cValues;
        lpProps = lpMappedAdrList->aEntries[i].rgPropVals;

        cNewProps  = 0;
        lpNewProps = NULL;

        hr = HrSetUlongPropertyValue(
            FALSE,
            PR_RECIPIENT_NUMBER,
            (i+1),
            cValues,
            lpProps,
            &cNewProps,
            &lpNewProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MAPIFREEBUFFER(lpProps);

        lpMappedAdrList->aEntries[i].cValues = cNewProps;
        lpMappedAdrList->aEntries[i].rgPropVals = lpNewProps;

        cNewProps  = 0;
        lpNewProps = NULL;

        cValues = 0;
        lpProps = NULL;

        //
        // Preserve original row number for original recipient entry
        //

        cValues = lpRows->aRow[i].cValues;
        lpProps = lpRows->aRow[i].lpProps;

        cNewProps  = 0;
        lpNewProps = NULL;

        hr = HrSetUlongPropertyValue(
            TRUE,
            PR_ROWID,
            i,
            cValues,
            lpProps,
            &cNewProps,
            &lpNewProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MAPIFREEBUFFER(lpProps);

        lpRows->aRow[i].cValues = cNewProps;
        lpRows->aRow[i].lpProps = lpNewProps;

        cNewProps  = 0;
        lpNewProps = NULL;

        cValues = 0;
        lpProps = NULL;

        //
        // Preserve original row number for mapped recipient entry
        //

        cValues = lpMappedAdrList->aEntries[i].cValues;
        lpProps = lpMappedAdrList->aEntries[i].rgPropVals;

        cNewProps  = 0;
        lpNewProps = NULL;

        hr = HrSetUlongPropertyValue(
            TRUE,
            PR_ROWID,
            i,
            cValues,
            lpProps,
            &cNewProps,
            &lpNewProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MAPIFREEBUFFER(lpProps);

        lpMappedAdrList->aEntries[i].cValues = cNewProps;
        lpMappedAdrList->aEntries[i].rgPropVals = lpNewProps;

        cNewProps  = 0;
        lpNewProps = NULL;

        cValues = 0;
        lpProps = NULL;

        //
        // Mapped recipient entry (read-only)
        //

        cMapValues = lpMappedAdrList->aEntries[i].cValues;
        lpMapProps = lpMappedAdrList->aEntries[i].rgPropVals;

        //
        // Find the email address associated with a proxy address,
        //

        //
        // Get the recipient responsibility
        //

        lpPropT = LpValFindProp(PR_RESPONSIBILITY, cMapValues, lpMapProps);

        if(lpPropT == NULL)
        {
            fRespTrue = fDefaultRespValue;
        }
        else
        {
            fRespTrue = lpPropT->Value.b;
        }

        if(fIgnoreRespValue == TRUE)
        {
            fRespTrue = FALSE;
        }

        //
        // NOTE: If the recipient address type is the same as the email
        // address type then the address was mapped.
        //

        if((lpMapProps[IADDRTYPE].ulPropTag != PR_ADDRTYPE) ||
           (lpMapProps[IADDRTYPE].Value.LPSZ == NULL))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
        else
        {
            if( (lstrcmpi(lpMapProps[IADDRTYPE].Value.LPSZ,
                         TEXT(EXCHANGE_ADDRTYPE)) != 0) &&
                (fRespTrue == TRUE) )
            {
                MODULE_WARNING("email address was not found");

                if(lpMapProps[IRECIPSTAT].Value.ul != NOERROR)
                {
                    //
                    // Non-deliver recipient
                    //

                    hr = HrNonDeliverRecipient(
                        MAPI_REASON_TRANSFER_IMPOSSIBLE,
                        (ULONG)MAPI_DIAG_OR_NAME_AMBIGUOUS,
                        &ftReportTime,
                        (ULONG)-1,
                        iNak,
                        cMapValues,
                        lpMapProps,
                        *lppNDRAdrList);

                    if(FAILED(hr))
                    {
                        goto cleanup;
                    }

                    iNak++;
                }
                else
                {
                    goto skip;
                }
            }
            else
            {
skip:
                hr = HrMAPISetAddressList(
                    iAck,
                    cMapValues,
                    lpMapProps,
                    *lppAdrList);

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                iAck++;
            }
        }
    }

    (*lppAdrList)->cEntries    = iAck;
    (*lppNDRAdrList)->cEntries = iNak;

cleanup:

    if(FAILED(hr))
    {
        if(*lppAdrList != NULL)
        {
            FREEPADRLIST(*lppAdrList);
        }

        if(*lppNDRAdrList != NULL)
        {
            FREEPADRLIST(*lppNDRAdrList);
        }

    }

    MAPIFREEBUFFER(lpNewProps);
            
    RETURN(hr);
}
