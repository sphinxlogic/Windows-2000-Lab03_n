// --address.c------------------------------------------------------------------
//
//  Find an address given a proxy address.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "_entryid.h"
#include "gwmain.h"
#include "gwsample.h"

//$--HrCreateSearchKey-----------------------------------------------------------
// Create a search key given an address type and an address.
// -----------------------------------------------------------------------------
HRESULT HrCreateSearchKey(              // RETURNS: return code
    IN LPVOID lpObject,                 // pointer to object
    IN LPTSTR lpszAddressType,          // pointer to address type
    IN LPTSTR lpszAddress,              // pointer to address
    OUT LPTSTR *lppszSearchKey)         // pointer to search key
{
    HRESULT hr     = NOERROR;
    SCODE   sc     = 0;
    ULONG   cBytes = 0;

    DEBUGPUBLIC("HrCreateSearchKey()\n");

    *lppszSearchKey = NULL;

    cBytes =
        (lstrlen(lpszAddressType) +
         lstrlen(lpszAddress) + 2) * sizeof(TCHAR);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszSearchKey);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    lstrcpy(*lppszSearchKey, lpszAddressType);
    lstrcat(*lppszSearchKey, TEXT(":"));
    lstrcat(*lppszSearchKey, lpszAddress);
    CharUpperBuff(*lppszSearchKey, cBytes/sizeof(TCHAR));

cleanup:

    return(hr);
}

//$--HrCreateProxyAddress-------------------------------------------------------
// Create proxy address.
// -----------------------------------------------------------------------------
HRESULT HrCreateProxyAddress(               // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,                // pointer to address book
    IN LPVOID     lpObject,                 // pointer to object
    IN BOOL       fMapiRecip,               // MAPI recipient
    IN LPTSTR     lpszDisplayName,          // pointer to display name
    IN LPTSTR     lpszAddressType,          // pointer to address type
    IN LPTSTR     lpszAddress,              // pointer to address
    OUT LPTSTR    *lppszProxyDisplayName,   // proxy display name
    OUT LPTSTR    *lppszProxyAddressType,   // proxy address type
    OUT LPTSTR    *lppszProxyAddress,       // proxy address
    OUT LPTSTR    *lppszProxySearchKey,     // proxy search key
    OUT ULONG     *lpcbProxyEid,            // count of bytes in proxy entry ID
    OUT LPENTRYID *lppProxyEid)             // pointer to proxy entry ID
{
    HRESULT   hr      = NOERROR;
    HRESULT   hrT     = NOERROR;
    SCODE     sc      = 0;

    ULONG     cBytes  = 0;

    ULONG     cbeidT  = 0;
    LPENTRYID lpeidT  = NULL;

    ULONG     ulFlags = 0;

    DEBUGPUBLIC("HrCreateProxyAddress()\n");

    if(lpszDisplayName == NULL)
    {
        hr = HR_LOG(E_INVALIDARG);
        goto cleanup;
    }

    if(lpszAddressType == NULL)
    {
        hr = HR_LOG(E_INVALIDARG);
        goto cleanup;
    }

    if(lpszAddress == NULL)
    {
        hr = HR_LOG(E_INVALIDARG);
        goto cleanup;
    }

    *lppszProxyDisplayName = NULL;
    *lppszProxyAddressType = NULL;
    *lppszProxyAddress     = NULL;
    *lppszProxySearchKey   = NULL;
    *lpcbProxyEid          = 0;
    *lppProxyEid           = NULL;

    //
    // Create proxy address
    //

    cBytes = cbStrLen(lpszAddress);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszProxyAddress);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    CopyMemory(*lppszProxyAddress, lpszAddress, cBytes);

    //
    // Create proxy display name
    //

    cBytes = cbStrLen(lpszDisplayName);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszProxyDisplayName);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    CopyMemory(*lppszProxyDisplayName, lpszDisplayName, cBytes);

    //
    // Create proxy address type
    //

    cBytes = cbStrLen(lpszAddressType);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszProxyAddressType);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    CopyMemory(*lppszProxyAddressType, lpszAddressType, cBytes);

    if(fMapiRecip == TRUE)
    {
        ulFlags = fMapiUnicode;
    }
    else
    {
        ulFlags = fMapiUnicode|MAPI_SEND_NO_RICH_INFO;
    }

    //
    // Create proxy entry ID
    //

    hrT = MAPICALL(lpAdrBook)->CreateOneOff(
        lpAdrBook,
        *lppszProxyDisplayName,
        *lppszProxyAddressType,
        *lppszProxyAddress,
        ulFlags,
        &cbeidT,
        &lpeidT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    sc = MAPIAllocateMore(cbeidT, lpObject, (void **)lppProxyEid);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    *lpcbProxyEid = cbeidT;

    CopyMemory(*lppProxyEid, lpeidT, cbeidT);

    //
    // Create proxy search key
    //

    hr = HrCreateSearchKey(
        lpObject,
        *lppszProxyAddressType,
        *lppszProxyAddress,
        lppszProxySearchKey);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    MAPIFREEBUFFER(lpeidT);

    if(FAILED(hr))
    {
        *lppszProxyDisplayName = NULL;
        *lppszProxyAddressType = NULL;
        *lppszProxyAddress     = NULL;
        *lppszProxySearchKey   = NULL;
        *lpcbProxyEid          = 0;
        *lppProxyEid           = NULL;
    }

    RETURN(hr);
}

//$--HrCreateEmailAddress-------------------------------------------------------
// Create email address.
// -----------------------------------------------------------------------------
HRESULT HrCreateEmailAddress(               // RETURNS: return code
    IN LPADRBOOK  lpAdrBook,                // pointer to address book
    IN LPVOID     lpObject,                 // pointer to object
    IN LPTSTR     lpszDisplayName,          // pointer to display name
    IN LPTSTR     lpszAddressType,          // pointer to address type
    IN LPTSTR     lpszAddress,              // pointer to address
    IN ULONG      cbeid,                    // count of bytes in entry ID
    IN LPENTRYID  lpeid,                    // pointer to entry ID
    OUT LPTSTR    *lppszEmailDisplayName,   // email display name
    OUT LPTSTR    *lppszEmailAddressType,   // email address type
    OUT LPTSTR    *lppszEmailAddress,       // email address
    OUT LPTSTR    *lppszEmailSearchKey,     // email search key
    OUT ULONG     *lpcbEmailEid,            // count of bytes in email entry ID
    OUT LPENTRYID *lppEmailEid)             // pointer to email entry ID
{
    HRESULT   hr     = NOERROR;
    SCODE     sc     = 0;
    ULONG     cBytes = 0;

    DEBUGPUBLIC("HrCreateEmailAddress()\n");

    *lppszEmailDisplayName = NULL;
    *lppszEmailAddressType = NULL;
    *lppszEmailAddress     = NULL;
    *lppszEmailSearchKey   = NULL;
    *lpcbEmailEid          = 0;
    *lppEmailEid           = NULL;

    //
    // Create email address
    //

    cBytes = cbStrLen(lpszAddress);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszEmailAddress);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    CopyMemory(*lppszEmailAddress, lpszAddress, cBytes);

    //
    // Create email display name
    //

    cBytes = cbStrLen(lpszDisplayName);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszEmailDisplayName);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    CopyMemory(*lppszEmailDisplayName, lpszDisplayName, cBytes);

    //
    // Create email address type
    //

    cBytes = cbStrLen(lpszAddressType);

    sc = MAPIAllocateMore(cBytes, lpObject, (void **)lppszEmailAddressType);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    CopyMemory(*lppszEmailAddressType, lpszAddressType, cBytes);

    //
    // Create email entry ID
    //

    sc = MAPIAllocateMore(cbeid, lpObject, (void **)lppEmailEid);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    *lpcbEmailEid = cbeid;

    CopyMemory(*lppEmailEid, lpeid, cbeid);

    //
    // Create email search key
    //

    hr = HrCreateSearchKey(
        lpObject,
        *lppszEmailAddressType,
        *lppszEmailAddress,
        lppszEmailSearchKey);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    if(FAILED(hr))
    {
        *lppszEmailDisplayName = NULL;
        *lppszEmailAddressType = NULL;
        *lppszEmailAddress     = NULL;
        *lppszEmailSearchKey   = NULL;
        *lpcbEmailEid          = 0;
        *lppEmailEid           = NULL;
    }

    return(hr);
}

//$--HrDeleteAddressProps--------------------------------------------------------
// Delete address properties from the message.
// -----------------------------------------------------------------------------
HRESULT HrDeleteAddressProps(           // RETURNS: return code
    IN LPMESSAGE  lpMessage,            // pointer to message
    IN ULONG ulDisplayName,             // display name property tag
    IN ULONG ulAddressType,             // address type property tag
    IN ULONG ulAddress,                 // address property tag
    IN ULONG ulSearchKey,               // search key property tag
    IN ULONG ulEntryId)                 // entry ID property tag
{
    HRESULT hr  = NOERROR;
    HRESULT hrT = NOERROR;
    ULONG   i   = 0;

    SizedSPropTagArray(5, rgPropTags) =
    {
        5,
        {
            PR_NULL,
            PR_NULL,
            PR_NULL,
            PR_NULL,
            PR_NULL,
        }
    };

    DEBUGPUBLIC("HrDeleteAddressProps()\n");

    if(FBadPropTag(ulDisplayName) ||
      (PROP_TYPE(ulDisplayName) == PT_NULL) ||
      (PROP_TYPE(ulDisplayName) == PT_ERROR))
    {
        MODULE_WARNING1("Invalid property type for property tag [%08lx]",ulDisplayName);
    }
    else
    {
        rgPropTags.aulPropTag[i++] = ulDisplayName;
    }

    if(FBadPropTag(ulAddressType) ||
      (PROP_TYPE(ulAddressType) == PT_NULL) ||
      (PROP_TYPE(ulAddressType) == PT_ERROR))
    {
        MODULE_WARNING1("Invalid property type for property tag [%08lx]",ulAddressType);
    }
    else
    {
        rgPropTags.aulPropTag[i++] = ulAddressType;
    }

    if(FBadPropTag(ulAddress) ||
      (PROP_TYPE(ulAddress) == PT_NULL) ||
      (PROP_TYPE(ulAddress) == PT_ERROR))
    {
        MODULE_WARNING1("Invalid property type for property tag [%08lx]",ulAddress);
    }
    else
    {
        rgPropTags.aulPropTag[i++] = ulAddress;
    }

    if(FBadPropTag(ulSearchKey) ||
      (PROP_TYPE(ulSearchKey) == PT_NULL) ||
      (PROP_TYPE(ulSearchKey) == PT_ERROR))
    {
        MODULE_WARNING1("Invalid property type for property tag [%08lx]",ulSearchKey);
    }
    else
    {
        rgPropTags.aulPropTag[i++] = ulSearchKey;
    }

    if(FBadPropTag(ulEntryId) ||
      (PROP_TYPE(ulEntryId) == PT_NULL) ||
      (PROP_TYPE(ulEntryId) == PT_ERROR))
    {
        MODULE_WARNING1("Invalid property type for property tag [%08lx]",ulEntryId);
    }
    else
    {
        rgPropTags.aulPropTag[i++] = ulEntryId;
    }

    //
    // Check if there are any properties left to delete.
    //

    if(i == 0)
    {
        hr = HR_LOG(EDK_E_NOT_FOUND);
        goto cleanup;
    }

    rgPropTags.cValues = i;

    hrT = MAPICALL(lpMessage)->DeleteProps(
        lpMessage,
        (SPropTagArray *)&rgPropTags,
        NULL);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    return(hr);
}

//$--HrDeleteAddressListProperty------------------------------------------------
// Delete a property from an address list given its property tag.
// -----------------------------------------------------------------------------
HRESULT HrDeleteAddressListProperty(    // RETURNS: return code
    IN ULONG ulPropTag,                 // property tag
    IN OUT LPADRLIST lpAdrList)         // pointer to address list
{
    HRESULT      hr      = NOERROR;
    ULONG        i       = 0;
    ULONG        cValues = 0;
    LPSPropValue lpProps = NULL;
    LPSPropValue lpPropT = NULL;

    DEBUGPUBLIC("HrDeleteAddressListProperty()\n");

    for(i = 0; i < lpAdrList->cEntries; i++)
    {
        cValues = lpAdrList->aEntries[i].cValues;
        lpProps = lpAdrList->aEntries[i].rgPropVals;

        lpPropT = LpValFindProp(ulPropTag, cValues, lpProps);

        if(lpPropT != NULL)
        {
            lpPropT->ulPropTag = PR_NULL;
        }
    }

    RETURN(hr);
}

//$--HrSetUlongPropertyValue----------------------------------------------------
// Set a ULONG property value.
// -----------------------------------------------------------------------------
HRESULT HrSetUlongPropertyValue(        // RETURNS: return code
    IN BOOL  fOverwrite,                // overwrite value if it exists
    IN ULONG ulPropTag,                 // property tag
    IN ULONG ulValue,                   // property value
    IN ULONG cValues,                   // count of property values
    IN LPSPropValue lpProps,            // pointer to property values
    OUT ULONG* lpcValues,               // new count of property values
    OUT LPSPropValue* lppProps)         // new pointer to property values
{
    HRESULT      hr           = NOERROR;
    LPSPropValue lpPropT      = NULL;
    SPropValue   PropValue[1] = {0};

    DEBUGPUBLIC("HrSetUlongPropertyValue()\n");

    if(PROP_TYPE(ulPropTag) != PT_LONG)
    {
        RETURN(HR_LOG(E_INVALIDARG));
    }

    *lpcValues = 0;
    *lppProps  = NULL;

    lpPropT = LpValFindProp(ulPropTag, cValues, lpProps);

    if(lpPropT == NULL)
    {
        PropValue[0].ulPropTag = ulPropTag;
        PropValue[0].Value.ul  = ulValue;

        hr = HrMAPIAppendSPropValues(
            cValues,
            lpProps,
            1,
            PropValue,
            lpcValues,
            lppProps);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
    else
    {
        SCODE sc = 0;

        sc = ScDupPropset(
            cValues,
            lpProps,
    		MAPIAllocateBuffer,
    		lppProps);

        if(FAILED(sc))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        *lpcValues = cValues;

        if(fOverwrite == TRUE)
        {
            lpPropT = LpValFindProp(ulPropTag, *lpcValues, *lppProps);

            if(lpPropT != NULL)
            {
                lpPropT->ulPropTag = ulPropTag;
                lpPropT->Value.ul  = ulValue;
            }
        }
    }

cleanup:

    RETURN(hr);
}

//$--HrExpandMessageAddressList-------------------------------------------------
// Expand a list of addresses on the message.
// -----------------------------------------------------------------------------
HRESULT HrExpandMessageAddressList(     // RETURNS: return code
    IN LPMESSAGE  lpMessage,            // pointer to message
    OUT ULONG*    lpcMesgAddr,          // count of message addresses
    OUT ULONG*    lpcReplyAddr,         // count of reply recipient addresses
    OUT ULONG*    lpcRecipAddr,         // count of recipient addresses
    OUT LPADRLIST *lppRecipList,        // pointer to recipient address list
    OUT LPADRLIST *lppAdrList)          // pointer to address list
{
    HRESULT      hr                   = NOERROR;
    HRESULT      hrT                  = NOERROR;
    ULONG        i                    = 0;
    ULONG        cValues              = 0;
    LPSPropValue lpProps              = NULL;
    LPSPropValue lpPropT              = NULL;
    LPSRowSet    lpRows               = 0;

    LPMAPITABLE  lpTable              = NULL;

    SPropValue   rgProps[3]           = {0};

    ULONG        cEntries             = 0;

    ULONG        cAddr                = 0;

    ULONG        cMesgAddr            = 0;
    ULONG        cRecipAddr           = 0;
    ULONG        cReplyAddr           = 0;

#define IREPORTDEST 10

#define CADDREID    14

    SizedSPropTagArray(CADDREID, rgPropTags) =
    {
        CADDREID,
        {
            PR_SENDER_ENTRYID,
            PR_SENT_REPRESENTING_ENTRYID,
            PR_ORIGINAL_SENDER_ENTRYID,
            PR_ORIGINAL_SENT_REPRESENTING_ENTRYID,
            PR_RECEIVED_BY_ENTRYID,
            PR_RCVD_REPRESENTING_ENTRYID,
            PR_ORIGINAL_AUTHOR_ENTRYID,
            PR_REPORT_ENTRYID,
            PR_READ_RECEIPT_ENTRYID,
            PR_ORIGINATOR_ENTRYID,
            PR_REPORT_DESTINATION_ENTRYID,
            PR_CREATOR_ENTRYID,
            PR_LAST_MODIFIER_ENTRYID,
            //PR_ORIGINALLY_INTENDED_RECIP_ENTRYID,
            PR_REPLY_RECIPIENT_ENTRIES,
        }
    };

    DEBUGPUBLIC("HrExpandMessageAddressList()\n");

    *lpcMesgAddr  = 0;
    *lpcReplyAddr = 0;
    *lpcRecipAddr = 0;
    *lppRecipList = NULL;
    *lppAdrList   = NULL;

    //
    // Get message addresses
    //

    hrT = MAPICALL(lpMessage)->GetProps(
        lpMessage,
        (SPropTagArray *)&rgPropTags,
        fMapiUnicode,
        &cValues,
        &lpProps);

    if(FAILED(hrT))
    {
        lpProps = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Get the recipient table for the message
    //

    hrT = MAPICALL(lpMessage)->GetRecipientTable(
        lpMessage,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

	//
	//  Query all the rows
	//

	hr = HrQueryAllRows(
	    lpTable,
		NULL,
		NULL,
		NULL,
		0,
		&lpRows);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Calculate the total number of addresses
    //

    if(lpProps[CADDREID-1].ulPropTag == PR_REPLY_RECIPIENT_ENTRIES)
    {
        cReplyAddr = lpProps[CADDREID-1].Value.MVbin.cValues;
    }
    else
    {
        cReplyAddr = 0;
    }

    cEntries = cValues - 1 + lpRows->cRows + cReplyAddr;

    for(i = 0; i < lpRows->cRows; i++)
    {
        lpPropT = LpValFindProp(
            PR_ORIGINAL_ENTRYID,
            lpRows->aRow[i].cValues,
            lpRows->aRow[i].lpProps);

        if((lpPropT != NULL) && (lpPropT->ulPropTag == PR_ORIGINAL_ENTRYID))
        {
            cEntries++;
        }
    }

    //
    // Create an ADRLIST
    //

    hr = HrMAPICreateSizedAddressList(
        cEntries,
        lppAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cAddr = 0;

    //
    // Add message addresses to the address list
    //

    cMesgAddr = --cValues;

    for(i = 0; i < cMesgAddr; i++, cAddr++)
    {
        if(PROP_TYPE(lpProps[i].ulPropTag) == PT_ERROR)
        {
            rgProps[0].ulPropTag     = PR_NULL;
            rgProps[0].Value.err     = MAPI_E_NOT_FOUND;
        }
        else
        {
            rgProps[0].ulPropTag     = PR_ENTRYID;
            rgProps[0].Value.bin.cb  = lpProps[i].Value.bin.cb;
            rgProps[0].Value.bin.lpb = lpProps[i].Value.bin.lpb;
        }

        rgProps[1].ulPropTag     = PR_RECIPIENT_TYPE;
        rgProps[1].Value.ul      = MAPI_TO;

        hr = HrMAPISetAddressList(
            cAddr,
            2,
            rgProps,
            *lppAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    //
    // Add reply recipient addresses to the address list
    //

    for(i = 0; i < cReplyAddr; i++, cAddr++)
    {
        rgProps[0].ulPropTag     = PR_ENTRYID;
        rgProps[0].Value.bin.cb  = lpProps[CADDREID-1].Value.MVbin.lpbin[i].cb;
        rgProps[0].Value.bin.lpb = lpProps[CADDREID-1].Value.MVbin.lpbin[i].lpb;
        rgProps[1].ulPropTag     = PR_RECIPIENT_TYPE;
        rgProps[1].Value.ul      = MAPI_TO;

        hr = HrMAPISetAddressList(
            cAddr,
            2,
            rgProps,
            *lppAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    //
    // Add recipient addresses to the address list
    //

    cRecipAddr = lpRows->cRows;

    for(i = 0; i < cRecipAddr; i++, cAddr++)
    {
        hr = HrMAPISetAddressList(
            cAddr,
            lpRows->aRow[i].cValues,
            lpRows->aRow[i].lpProps,
            *lppAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    for(i = 0; i < cRecipAddr; i++)
    {
        lpPropT = LpValFindProp(
            PR_ORIGINAL_ENTRYID,
            lpRows->aRow[i].cValues,
            lpRows->aRow[i].lpProps);

        if((lpPropT != NULL) && (lpPropT->ulPropTag == PR_ORIGINAL_ENTRYID))
        {
            rgProps[0].ulPropTag     = PR_ENTRYID;
            rgProps[0].Value.bin.cb  = lpPropT->Value.bin.cb;
            rgProps[0].Value.bin.lpb = lpPropT->Value.bin.lpb;
            rgProps[1].ulPropTag     = PR_RECIPIENT_NUMBER;
            rgProps[1].Value.ul      = i;
            rgProps[2].ulPropTag     = PR_RECIPIENT_TYPE;
            rgProps[2].Value.ul      = MAPI_TO;

            hr = HrMAPISetAddressList(
                cAddr,
                3,
                rgProps,
                *lppAdrList);

            cAddr++;

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }
    }

    *lpcMesgAddr  = cMesgAddr;
    *lpcReplyAddr = cReplyAddr;
    *lpcRecipAddr = cRecipAddr;

    *lppRecipList = (LPADRLIST)lpRows;

cleanup:

    if(FAILED(hr))
    {
        *lpcMesgAddr  = 0;
        *lpcReplyAddr = 0;
        *lpcRecipAddr = 0;

        FREEPADRLIST(*lppRecipList);
    }

    // Free MAPI buffers
    MAPIFREEBUFFER(lpProps);

    // Release MAPI objects
    ULRELEASE(lpTable);

    RETURN(hr);

#undef IREPORTDEST
}

//$--HrCheckForType-------------------------------------------------------------
//  Check if the passed in string has the requested address type. If so, return
//  the address value, otherwise fail.
// -----------------------------------------------------------------------------
static HRESULT HrCheckForType(  // RETURNS: return code
    IN  LPUNKNOWN lpObject,     // pointer to object
    IN  LPTSTR lpszAddrType,    // pointer to address type
    IN  LPTSTR lpszProxy,       // pointer to proxy address
    OUT LPTSTR * lppszAddress)  // pointer to address pointer
{
    HRESULT hr              = EDK_E_NOT_FOUND;
    int     rc              = 0;
    LPTSTR  lpszProxyAddr   = NULL;
    ULONG   cbAddress       = 0;
    SCODE   sc              = 0;
    ULONG   cchProxy        = 0;
    ULONG   cchProxyType    = 0;

    DEBUGPUBLIC("HrCheckForType()\n");

    //
	// Initialize output parameter
    //

	*lppszAddress = NULL;

    //
    // Find the ':' separator.
    //

    cchProxy = lstrlen(lpszProxy);

    for(
        cchProxyType = 0;
        (lpszProxy[cchProxyType] != 0) && (lpszProxy[cchProxyType] != TEXT(':'));
        cchProxyType++);

    if((cchProxyType == 0) || (cchProxyType >= cchProxy))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Does the address type match?
    //

    rc = CompareString(
        GetSystemDefaultLCID(),
        NORM_IGNORECASE|NORM_IGNORENONSPACE|SORT_STRINGSORT,
        lpszAddrType, -1,
        lpszProxy, cchProxyType);
        
    if(rc == 2)
    {   
        //
        // Specified address type found    
        //

        lpszProxyAddr = lpszProxy + cchProxyType + 1;

        cbAddress = cbStrLen(lpszProxyAddr);

        //
        // Make a buffer to hold it.
        //

        sc = MAPIAllocateMore(cbAddress, lpObject, (void **)lppszAddress);

        if(FAILED(sc))
        {
            hr = HR_LOG(E_OUTOFMEMORY);
            goto cleanup;
        }
        else
        {
            CopyMemory(*lppszAddress, lpszProxyAddr, cbAddress);

            hr = NOERROR;
        }
    }
    else if(rc == 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }
    else
    {
        hr = EDK_E_NOT_FOUND;
    }

cleanup:

    RETURN(hr);
}

//$--HrMapAddrToProxy-----------------------------------------------------------
// Map all email addresses to proxy addresses in a given address list.
// -----------------------------------------------------------------------------
HRESULT HrMapAddrToProxy(               // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPTSTR       lpszAddrType,      // pointer to the address type
    IN OUT LPADRLIST lpAdrList)         // pointer to address list
{
    HRESULT      hr                    = NOERROR;
    SCODE        sc                    = 0;
    ULONG        i                     = 0;
    ULONG        j                     = 0;
    ULONG        cbAddress             = 0;
    ULONG        cProxy                = 0;
    LPSPropValue lpProps               = NULL;
    LPSPropValue lpPropT               = NULL;

    LPTSTR       lpszProxyDisplayName  = NULL;
    LPTSTR       lpszProxyAddressType  = NULL;
    LPTSTR       lpszProxyAddress      = NULL;

    LPTSTR       lpszEmailDisplayName  = NULL;
    LPTSTR       lpszEmailAddressType  = NULL;
    LPTSTR       lpszEmailAddress      = NULL;
    LPTSTR       lpszEmailSearchKey    = NULL;
    ULONG        cbEmailEid            = 0;
    LPENTRYID    lpEmailEid            = NULL;

    SPropValue   prop[MIN_CRECIPPROPS] = {0};

    SizedSPropTagArray(MIN_CRECIPPROPS, rgPropTags) =
    {
        MIN_CRECIPPROPS, 
        {
            PR_DISPLAY_NAME,
            PR_ADDRTYPE,
            PR_EMAIL_ADDRESS,
            PR_SEARCH_KEY,
            PR_ENTRYID,
            PR_SEND_RICH_INFO,
            PR_RESPONSIBILITY,
            PR_RECIPIENT_NUMBER,
            PR_ORIGINAL_DISPLAY_NAME,
            PR_ORIGINAL_ENTRYID,
            PR_EMS_AB_PROXY_ADDRESSES
        }
    };

    DEBUGPUBLIC("HrMapAddrToProxy()\n");

    //
    // NOTE: PrepareRecips() will not create a value for PR_SEARCH_KEY. This is
    // why the following code has to check for PR_ADDRTYPE and PR_EMAIL_ADDRESS
    // and create a search key where possible.
    //

    hr = MAPICALL(lpAdrBook)->PrepareRecips(
        lpAdrBook,
        0,
        (LPSPropTagArray)&rgPropTags,
        lpAdrList);

    if(HR_FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0; i < lpAdrList->cEntries; i++)
    {
        lpProps = lpAdrList->aEntries[i].rgPropVals;

        lpPropT = LpValFindProp(
            PR_ENTRYID,
            lpAdrList->aEntries[i].cValues,
            lpProps);

        //
        // Check if this is a valid recipient entry.
        //

        if((lpAdrList->aEntries[i].cValues < MIN_CRECIPPROPS) ||
           (lpPropT == NULL) ||
           (PROP_TYPE(lpPropT->ulPropTag) == PT_ERROR))
        {
            //
            // Add an empty recipient entry.
            //

            MODULE_WARNING1("**** Adding an empty recipient entry [%lu] ****", i);

            prop[0].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_DISPLAY_NAME));
            prop[0].Value.err = MAPI_E_NOT_FOUND;
            prop[1].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_ADDRTYPE));
            prop[1].Value.err = MAPI_E_NOT_FOUND;
            prop[2].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_EMAIL_ADDRESS));
            prop[2].Value.err = MAPI_E_NOT_FOUND;
            prop[3].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_SEARCH_KEY));
            prop[3].Value.err = MAPI_E_NOT_FOUND;
            prop[4].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_SEND_RICH_INFO));
            prop[4].Value.err = MAPI_E_NOT_FOUND;
            prop[5].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_ENTRYID));
            prop[5].Value.err = MAPI_E_NOT_FOUND;
            prop[6].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_RESPONSIBILITY));
            prop[6].Value.err = MAPI_E_NOT_FOUND;
            prop[7].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_RECIPIENT_NUMBER));
            prop[7].Value.err = MAPI_E_NOT_FOUND;
            prop[8].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_ORIGINAL_DISPLAY_NAME));
            prop[8].Value.err = MAPI_E_NOT_FOUND;
            prop[9].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_ORIGINAL_ENTRYID));
            prop[9].Value.err = MAPI_E_NOT_FOUND;
            prop[10].ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_EMS_AB_PROXY_ADDRESSES));
            prop[10].Value.err = MAPI_E_NOT_FOUND;

            hr = HrMAPISetAddressList(
                i,
                MIN_CRECIPPROPS,
                prop,
                lpAdrList);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            lpProps = lpAdrList->aEntries[i].rgPropVals;
        }

        // If the PR_RECIPIENT_NUMBER property is not set, default the value
        // to 1

        if((PROP_TYPE(lpProps[IRECIPNUM].ulPropTag) == PT_ERROR) &&
           (PROP_ID(lpProps[IRECIPNUM].ulPropTag) == PROP_ID(PR_RECIPIENT_NUMBER)))
        {
            lpProps[IRECIPNUM].ulPropTag = PR_RECIPIENT_NUMBER;
            lpProps[IRECIPNUM].Value.ul  = 1;
        }

        // If the PR_SEND_RICH_INFO property is not set, default the value
        // to FALSE

        if((PROP_TYPE(lpProps[IMAPIRECIP].ulPropTag) == PT_ERROR) &&
           (PROP_ID(lpProps[IMAPIRECIP].ulPropTag) == PROP_ID(PR_SEND_RICH_INFO)))
        {
            lpProps[IMAPIRECIP].ulPropTag = PR_SEND_RICH_INFO;
            lpProps[IMAPIRECIP].Value.b   = FALSE;
        }

        // If the PR_RESPONSIBILITY property is not set, default the value
        // to FALSE

        if((PROP_TYPE(lpProps[IRESP].ulPropTag) == PT_ERROR) &&
           (PROP_ID(lpProps[IRESP].ulPropTag) == PROP_ID(PR_RESPONSIBILITY)))
        {
            lpProps[IRESP].ulPropTag = PR_RESPONSIBILITY;
            lpProps[IRESP].Value.b   = FALSE;
        }

        lpszProxyDisplayName = NULL;
        lpszProxyAddressType = NULL;
        lpszProxyAddress     = NULL;

        // If the given address type matches the PR_ADDRTYPE value,
        // return the PR_EMAIL_ADDRESS value
    
        if((lpProps[IADDRTYPE].ulPropTag == PR_ADDRTYPE) &&
           (lpProps[IEMAILADDR].ulPropTag == PR_EMAIL_ADDRESS) &&
           (lstrcmpi(lpProps[IADDRTYPE].Value.LPSZ, lpszAddrType) == 0))
        {
            lpszProxyAddressType = lpProps[IADDRTYPE].Value.LPSZ;
            lpszProxyAddress = lpProps[IEMAILADDR].Value.LPSZ;
        }

        //
        // Search for a PR_EMS_AB_PROXY_ADDRESSES of the given type if present.
        //

        else if(lpProps[IPROXYADDR].ulPropTag == PR_EMS_AB_PROXY_ADDRESSES)
        {
            BOOL IsFound = FALSE;

            //
            // Count of proxy addresses
            //

            cProxy = lpAdrList->aEntries[i].rgPropVals[IPROXYADDR].Value.MVSZ.cValues;

            IsFound = FALSE;

            for(j = 0; j < cProxy; j++)
            {
                hr = HrCheckForType(
                    (LPUNKNOWN)lpProps,
                    lpszAddrType, 
                    lpProps[IPROXYADDR].Value.MVSZ.LPPSZ[j],
                    &lpszProxyAddress);

                if(hr == EDK_E_NOT_FOUND)
                {
                    continue;
                }
                else if(FAILED(hr))
                {
                    goto cleanup;
                }
                else
                {
                    IsFound = TRUE;
                    break;
                }
            }

            if(IsFound == FALSE)
            {
                MODULE_WARNING("A proxy address was not found!");

                if(lpProps[IADDRTYPE].ulPropTag == PR_ADDRTYPE)
                {
                    lpszProxyAddressType = lpProps[IADDRTYPE].Value.LPSZ;
                }

                if(lpProps[IEMAILADDR].ulPropTag == PR_EMAIL_ADDRESS)
                {
                    lpszProxyAddress = lpProps[IEMAILADDR].Value.LPSZ;
                }
            }
            else
            {
                lpszProxyAddressType = lpszAddrType;
            }
        }
        else
        {
            if(lpProps[IADDRTYPE].ulPropTag == PR_ADDRTYPE)
            {
                lpszProxyAddressType = lpProps[IADDRTYPE].Value.LPSZ;
            }

            if(lpProps[IEMAILADDR].ulPropTag == PR_EMAIL_ADDRESS)
            {
                lpszProxyAddress = lpProps[IEMAILADDR].Value.LPSZ;
            }
        }

        //
        // Update proxy display name
        //

        if((lpProps[IDISPNAME].ulPropTag != PR_DISPLAY_NAME) ||
           (lpProps[IDISPNAME].Value.LPSZ == NULL) ||
           (lstrlen(lpProps[IDISPNAME].Value.LPSZ) == 0))
        {
            if(lpszProxyAddress != NULL)
            {
                lpszProxyDisplayName = lpszProxyAddress;
            }
            else
            {
                lpszProxyDisplayName = NULL;
            }
        }
        else
        {
            lpszProxyDisplayName = lpProps[IDISPNAME].Value.LPSZ;
        }

        //
        // Create a proxy address
        //

        if((lpszProxyDisplayName != NULL) &&
           (lpszProxyAddressType != NULL) &&
           (lpszProxyAddress != NULL))
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
                lpProps[IMAPIRECIP].Value.b,
                lpszProxyDisplayName,
                lpszProxyAddressType,
                lpszProxyAddress,
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

            lpProps[IDISPNAME].ulPropTag    = PR_DISPLAY_NAME;
            lpProps[IDISPNAME].Value.LPSZ   = lpszEmailDisplayName;

            lpProps[IADDRTYPE].ulPropTag    = PR_ADDRTYPE;
            lpProps[IADDRTYPE].Value.LPSZ   = lpszEmailAddressType;

            lpProps[IEMAILADDR].ulPropTag   = PR_EMAIL_ADDRESS;
            lpProps[IEMAILADDR].Value.LPSZ  = lpszEmailAddress;

            lpProps[ISEARCHKEY].ulPropTag   = PR_SEARCH_KEY;

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

            lpProps[IENTRYID].ulPropTag     = PR_ENTRYID;
            lpProps[IENTRYID].Value.bin.cb  = cbEmailEid;
            lpProps[IENTRYID].Value.bin.lpb = (LPBYTE)lpEmailEid;
        }
        else
        {
            MODULE_WARNING("Unable to create a proxy address!");
        }
    }

cleanup:

    RETURN(hr);
}

//$--HrCollapseMessageAddressList-----------------------------------------------
// Collapse a list of addresses on the message.
// -----------------------------------------------------------------------------
HRESULT HrCollapseMessageAddressList(   // RETURNS: return code
    IN LPMESSAGE     lpMessage,         // pointer to message
    IN ULONG         cMesgAddr,         // count of message addresses
    IN ULONG         cReplyAddr,        // count of reply recipient addresses
    IN ULONG         cRecipAddr,        // count of recipient addresses
    IN LPADRLIST     lpAdrList,         // message address list
    OUT ULONG        *lpcValues,        // count of message address properties
    OUT LPSPropValue *lppProps,         // message address properties
    OUT LPADRLIST    *lppAdrList)       // recipient address list
{
    HRESULT      hr            = NOERROR;
    SCODE        sc            = 0;
    LPSPropValue lpMesgProps   = NULL;
    LPTSTR       *lppDispNames = NULL;
    SBinary      *lppEntryIDs  = NULL;
    ULONG        cBytes        = 0;
    ULONG        i             = 0;
    ULONG        j             = 0;
    ULONG        cOrigAddr     = 0;
    LPADRLIST    lpRecipList   = 0;

    ULONG        cValues       = 0;
    LPSPropValue lpProps       = NULL;

#define CMESGPROPS 70

    SizedSPropTagArray(CMESGPROPS, rgPropTags) =
    {
        CMESGPROPS,
        {
            PR_SENDER_NAME,
            PR_SENDER_ADDRTYPE,
            PR_SENDER_EMAIL_ADDRESS,
            PR_SENDER_SEARCH_KEY,
            PR_SENDER_ENTRYID,
            PR_SENT_REPRESENTING_NAME,
            PR_SENT_REPRESENTING_ADDRTYPE,
            PR_SENT_REPRESENTING_EMAIL_ADDRESS,
            PR_SENT_REPRESENTING_SEARCH_KEY,
            PR_SENT_REPRESENTING_ENTRYID,
            PR_ORIGINAL_SENDER_NAME,
            PR_ORIGINAL_SENDER_ADDRTYPE,
            PR_ORIGINAL_SENDER_EMAIL_ADDRESS,
            PR_ORIGINAL_SENDER_SEARCH_KEY,
            PR_ORIGINAL_SENDER_ENTRYID,
            PR_ORIGINAL_SENT_REPRESENTING_NAME,
            PR_ORIGINAL_SENT_REPRESENTING_ADDRTYPE,
            PR_ORIGINAL_SENT_REPRESENTING_EMAIL_ADDRESS,
            PR_ORIGINAL_SENT_REPRESENTING_SEARCH_KEY,
            PR_ORIGINAL_SENT_REPRESENTING_ENTRYID,
            PR_RECEIVED_BY_NAME,
            PR_NULL,//PR_RECEIVED_BY_ADDRTYPE,
            PR_NULL,//PR_RECEIVED_BY_EMAIL_ADDRESS,
            PR_RECEIVED_BY_SEARCH_KEY,
            PR_RECEIVED_BY_ENTRYID,
            PR_RCVD_REPRESENTING_NAME,
            PR_NULL,//PR_RCVD_REPRESENTING_ADDRTYPE,
            PR_NULL,//PR_RCVD_REPRESENTING_EMAIL_ADDRESS,
            PR_RCVD_REPRESENTING_SEARCH_KEY,
            PR_RCVD_REPRESENTING_ENTRYID,
            PR_ORIGINAL_AUTHOR_NAME,
            PR_ORIGINAL_AUTHOR_ADDRTYPE,
            PR_ORIGINAL_AUTHOR_EMAIL_ADDRESS,
            PR_ORIGINAL_AUTHOR_SEARCH_KEY,
            PR_ORIGINAL_AUTHOR_ENTRYID,
            PR_REPORT_NAME,
            PR_NULL,//PR_REPORT_ADDRTYPE,
            PR_NULL,//PR_REPORT_EMAIL_ADDRESS,
            PR_REPORT_SEARCH_KEY,
            PR_REPORT_ENTRYID,
            PR_NULL,//PR_READ_RECEIPT_NAME,
            PR_NULL,//PR_READ_RECEIPT_ADDRTYPE,
            PR_NULL,//PR_READ_RECEIPT_EMAIL_ADDRESS,
            PR_READ_RECEIPT_SEARCH_KEY,
            PR_READ_RECEIPT_ENTRYID,
            PR_ORIGINATOR_NAME,
            PR_ORIGINATOR_ADDRTYPE,
            PR_ORIGINATOR_ADDR,//PR_ORIGINATOR_EMAIL_ADDRESS,
            PR_NULL,//PR_ORIGINATOR_SEARCH_KEY,
            PR_ORIGINATOR_ENTRYID,
            PR_REPORT_DESTINATION_NAME,
            PR_NULL,//PR_REPORT_DESTINATION_ADDRTYPE,
            PR_NULL,//PR_REPORT_DESTINATION_EMAIL_ADDRESS,
            PR_NULL,//PR_REPORT_DESTINATION_SEARCH_KEY,
            PR_REPORT_DESTINATION_ENTRYID,
            PR_CREATOR_NAME,
            PR_NULL,//PR_CREATOR_ADDRTYPE,
            PR_NULL,//PR_CREATOR_EMAIL_ADDRESS,
            PR_NULL,//PR_CREATOR_SEARCH_KEY,
            PR_CREATOR_ENTRYID,
            PR_LAST_MODIFIER_NAME,
            PR_NULL,//PR_LAST_MODIFIER_ADDRTYPE,
            PR_NULL,//PR_LAST_MODIFIER_EMAIL_ADDRESS,
            PR_NULL,//PR_LAST_MODIFIER_SEARCH_KEY,
            PR_LAST_MODIFIER_ENTRYID,
            //PR_ORIGINALLY_INTENDED_RECIPIENT_NAME,
            //PR_ORIGINALLY_INTENDED_RECIP_ADDRTYPE,
            //PR_ORIGINALLY_INTENDED_RECIP_EMAIL_ADDRESS,
            //PR_NULL,//PR_ORIGINALLY_INTENDED_RECIP_SEARCH_KEY,
            //PR_ORIGINALLY_INTENDED_RECIP_ENTRYID,
            PR_REPLY_RECIPIENT_NAMES,
            PR_NULL,//PR_REPLY_RECIPIENT_ADDRTYPE,
            PR_NULL,//PR_REPLY_RECIPIENT_EMAIL_ADDRESS,
            PR_NULL,//PR_REPLY_RECIPIENT_SEARCH_KEY,
            PR_REPLY_RECIPIENT_ENTRIES,
        }
    };

    DEBUGPUBLIC("HrCollapseMessageAddressList()\n");

    if(cMesgAddr != (CMESGPROPS/5-1))
    {
        hr = HR_LOG(E_INVALIDARG);                                 
        goto cleanup;                                
    }

    if((cMesgAddr + cReplyAddr + cRecipAddr) > lpAdrList->cEntries)
    {
        hr = HR_LOG(E_INVALIDARG);                                 
        goto cleanup;                                
    }

    cOrigAddr = lpAdrList->cEntries - (cMesgAddr + cReplyAddr + cRecipAddr);

    cBytes = CbNewSPropValue(CMESGPROPS);

    sc = MAPIAllocateBuffer(cBytes, (void **)&lpMesgProps);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;                                
    }                                                   

    ZeroMemory(lpMesgProps, cBytes);

    //
    // Copy message address properties
    //

    for(i = 0; i < (CMESGPROPS/5-1); i++)
    {
        if(PROP_ID(lpAdrList->aEntries[i].rgPropVals[IDISPNAME].ulPropTag) !=
           PROP_ID(PR_DISPLAY_NAME))
        {
            hr = HR_LOG(E_FAIL);                                 
            goto cleanup;                                
        }

        if(rgPropTags.aulPropTag[i*5+IDISPNAME] != PR_NULL)
        {
            lpMesgProps[i*5+IDISPNAME].ulPropTag =
                PROP_TAG(
                    PROP_TYPE(lpAdrList->aEntries[i].rgPropVals[IDISPNAME].ulPropTag),
                    PROP_ID(rgPropTags.aulPropTag[i*5+IDISPNAME]));
        }
        else
        {
            lpMesgProps[i*5+IDISPNAME].ulPropTag = PR_NULL;
        }

        lpMesgProps[i*5+IDISPNAME].Value.LPSZ =
            lpAdrList->aEntries[i].rgPropVals[IDISPNAME].Value.LPSZ;

        if(rgPropTags.aulPropTag[i*5+IADDRTYPE] != PR_NULL)
        {
            lpMesgProps[i*5+IADDRTYPE].ulPropTag =
                PROP_TAG(
                    PROP_TYPE(lpAdrList->aEntries[i].rgPropVals[IADDRTYPE].ulPropTag),
                    PROP_ID(rgPropTags.aulPropTag[i*5+IADDRTYPE]));
        }
        else
        {
            lpMesgProps[i*5+IADDRTYPE].ulPropTag = PR_NULL;
        }

        lpMesgProps[i*5+IADDRTYPE].Value.LPSZ =
            lpAdrList->aEntries[i].rgPropVals[IADDRTYPE].Value.LPSZ;

        if(rgPropTags.aulPropTag[i*5+IEMAILADDR] != PR_NULL)
        {
            lpMesgProps[i*5+IEMAILADDR].ulPropTag =
                PROP_TAG(
                    PROP_TYPE(lpAdrList->aEntries[i].rgPropVals[IEMAILADDR].ulPropTag),
                    PROP_ID(rgPropTags.aulPropTag[i*5+IEMAILADDR]));
        }
        else
        {
            lpMesgProps[i*5+IEMAILADDR].ulPropTag = PR_NULL;
        }

        lpMesgProps[i*5+IEMAILADDR].Value.LPSZ =
            lpAdrList->aEntries[i].rgPropVals[IEMAILADDR].Value.LPSZ;

        if(rgPropTags.aulPropTag[i*5+ISEARCHKEY] != PR_NULL)
        {
            lpMesgProps[i*5+ISEARCHKEY].ulPropTag =
                PROP_TAG(
                    PROP_TYPE(lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].ulPropTag),
                    PROP_ID(rgPropTags.aulPropTag[i*5+ISEARCHKEY]));
        }
        else
        {
            lpMesgProps[i*5+ISEARCHKEY].ulPropTag = PR_NULL;
        }

        lpMesgProps[i*5+ISEARCHKEY].Value.bin.cb =
            lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.cb;
        lpMesgProps[i*5+ISEARCHKEY].Value.bin.lpb =
            lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.lpb;

        if(rgPropTags.aulPropTag[i*5+IENTRYID] != PR_NULL)
        {
            lpMesgProps[i*5+IENTRYID].ulPropTag =
                PROP_TAG(
                    PROP_TYPE(lpAdrList->aEntries[i].rgPropVals[IENTRYID].ulPropTag),
                    PROP_ID(rgPropTags.aulPropTag[i*5+IENTRYID]));
        }
        else
        {
            lpMesgProps[i*5+IENTRYID].ulPropTag = PR_NULL;
        }

        lpMesgProps[i*5+IENTRYID].Value.bin.cb =
            lpAdrList->aEntries[i].rgPropVals[IENTRYID].Value.bin.cb;
        lpMesgProps[i*5+IENTRYID].Value.bin.lpb =
            lpAdrList->aEntries[i].rgPropVals[IENTRYID].Value.bin.lpb;
    }

    //
    // Copy reply recipient properties
    //

    if(cReplyAddr > 0)
    {
        //
        // Copy reply recipient names
        //

        cBytes = cReplyAddr*(sizeof(LPTSTR)+MAX_ALIGN);

        sc = MAPIAllocateBuffer(cBytes, (void **)&lppDispNames);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;                                
        }                                                   

        ZeroMemory(lppDispNames, cBytes);

        for(i = 0, j = cMesgAddr; i < cReplyAddr; i++, j++)
        {
            lppDispNames[i] =
                lpAdrList->aEntries[j].rgPropVals[IDISPNAME].Value.LPSZ;
        }

        //
        // Copy reply recipient entry IDs
        //

        cBytes = cReplyAddr*(sizeof(SBinary)+MAX_ALIGN);

        sc = MAPIAllocateBuffer(cBytes, (void **)&lppEntryIDs);

        if(FAILED(sc))                           
        {                                                   
            hr = HR_LOG(E_OUTOFMEMORY);                                 
            goto cleanup;                                
        }                                                   

        ZeroMemory(lppDispNames, cBytes);

        for(i = 0, j = cMesgAddr; i < cReplyAddr; i++, j++)
        {
            lppEntryIDs[i].cb =
                lpAdrList->aEntries[j].rgPropVals[IENTRYID].Value.bin.cb;

            lppEntryIDs[i].lpb =
                lpAdrList->aEntries[j].rgPropVals[IENTRYID].Value.bin.lpb;
        }

        lpMesgProps[CMESGPROPS-5].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-5];
        lpMesgProps[CMESGPROPS-5].Value.MVSZ.cValues = cReplyAddr;
        lpMesgProps[CMESGPROPS-5].Value.MVSZ.LPPSZ   = lppDispNames;

        lpMesgProps[CMESGPROPS-4].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-4];
        lpMesgProps[CMESGPROPS-3].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-3];
        lpMesgProps[CMESGPROPS-2].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-2];

        lpMesgProps[CMESGPROPS-1].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-1];
        lpMesgProps[CMESGPROPS-1].Value.MVbin.cValues = cReplyAddr;
        lpMesgProps[CMESGPROPS-1].Value.MVbin.lpbin   = lppEntryIDs;
    }
    else
    {
        lpMesgProps[CMESGPROPS-5].ulPropTag =
            PROP_TAG(PT_ERROR,PROP_ID(rgPropTags.aulPropTag[CMESGPROPS-5]));
        lpMesgProps[CMESGPROPS-5].Value.err = MAPI_E_NOT_FOUND;

        lpMesgProps[CMESGPROPS-4].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-4];
        lpMesgProps[CMESGPROPS-3].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-3];
        lpMesgProps[CMESGPROPS-2].ulPropTag = rgPropTags.aulPropTag[CMESGPROPS-2];

        lpMesgProps[CMESGPROPS-1].ulPropTag =
            PROP_TAG(PT_ERROR,PROP_ID(rgPropTags.aulPropTag[CMESGPROPS-1]));
        lpMesgProps[CMESGPROPS-1].Value.err = MAPI_E_NOT_FOUND;
    }

    //
    // Duplicate message properties
    //

    cValues = CMESGPROPS;
    lpProps = NULL;

    sc = ScDupPropset(
        cValues,
        lpMesgProps,
		MAPIAllocateBuffer,
		&lpProps);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Copy recipient address list
    //

    hr = HrMAPICreateSizedAddressList(
        cRecipAddr,
        &lpRecipList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0, j = (cMesgAddr + cReplyAddr); i < cRecipAddr; i++, j++)
    {
        lpRecipList->aEntries[i] = lpAdrList->aEntries[j];
    }

    //
    // Copy original recipient information
    //

    for(i = (cMesgAddr + cReplyAddr + cRecipAddr); i < lpAdrList->cEntries; i++)
    {
        j = lpAdrList->aEntries[i].rgPropVals[IRECIPNUM].Value.ul;


        lpRecipList->aEntries[j].rgPropVals[IORIGDISP] =
            lpAdrList->aEntries[i].rgPropVals[IDISPNAME];
        lpRecipList->aEntries[j].rgPropVals[IORIGDISP].ulPropTag  =
            PR_ORIGINAL_DISPLAY_NAME;

        lpRecipList->aEntries[j].rgPropVals[IORIGENTRY] =
            lpAdrList->aEntries[i].rgPropVals[IENTRYID];
        lpRecipList->aEntries[j].rgPropVals[IORIGENTRY].ulPropTag =
            PR_ORIGINAL_ENTRYID;
    }

    //
    // Duplicate updated address list
    //

    hr = HrMAPICreateSizedAddressList(
        lpRecipList->cEntries,
        lppAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0; i < lpRecipList->cEntries; i++)
    {
        if(lpRecipList->aEntries[i].cValues < MIN_CRECIPPROPS)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        //
        // Unregistered named properties cannot be set on the recipient list.
        //
                    
        lpRecipList->aEntries[i].rgPropVals[IPROXYADDR].ulPropTag = PR_NULL;
        lpRecipList->aEntries[i].rgPropVals[IPROXYADDR].Value.ul  = 0;


        hr = HrMAPISetAddressList(
            i,
            lpRecipList->aEntries[i].cValues,
            lpRecipList->aEntries[i].rgPropVals,
            *lppAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
        
    *lpcValues  = cValues;
    *lppProps   = lpProps;

cleanup:

    if(FAILED(hr))
    {
        *lpcValues = 0;

        if(lppProps != NULL)
        {
            MAPIFREEBUFFER(*lppProps);
        }

        if(lppAdrList != NULL)
        {
            FREEPADRLIST(*lppAdrList);
        }
    }

    MAPIFREEBUFFER(lpMesgProps);

    MAPIFREEBUFFER(lppDispNames);

    MAPIFREEBUFFER(lppEntryIDs);

    MAPIFREEBUFFER(lpRecipList);

    RETURN(hr);
}

//$--HrMapProxyToAddr-----------------------------------------------------------
// Map all proxy addresses to email addresses in a given address list. Always
// call HrMapAddrToProxy() before calling this function.
// -----------------------------------------------------------------------------
HRESULT HrMapProxyToAddr(               // RETURNS: return code
    IN  LPADRBOOK    lpAdrBook,         // pointer to address book
    IN  LPABCONT     lpGalABCont,       // pointer to GAL container
    IN OUT LPADRLIST lpAdrList)         // pointer to address list
{
    HRESULT         hr                   = NOERROR;
    HRESULT         hrT                  = NOERROR;
    SCODE           sc                   = 0;
    ULONG           i                    = 0;

    SPropValue      prop[2]              = {0};
    LPFlagList      lpFlagList           = NULL;
    LPADRLIST       lpRecipList          = NULL;

    LPTSTR          lpszEmailDisplayName = NULL;
    LPTSTR          lpszEmailAddressType = NULL;
    LPTSTR          lpszEmailAddress     = NULL;
    LPTSTR          lpszEmailSearchKey   = NULL;
    ULONG           cbEmailEid           = 0;
    LPENTRYID       lpEmailEid           = NULL;

    SizedSPropTagArray(MIN_CRECIPPROPS, rgPropTags) =
    {
        MIN_CRECIPPROPS, 
        {
            PR_DISPLAY_NAME,
            PR_ADDRTYPE,
            PR_EMAIL_ADDRESS,
            PR_SEARCH_KEY,
            PR_ENTRYID,
            PR_SEND_RICH_INFO,
            PR_RESPONSIBILITY,
            PR_RECIPIENT_NUMBER,
            PR_ORIGINAL_DISPLAY_NAME,
            PR_ORIGINAL_ENTRYID,
            PR_RECIPSTAT
        }
    };

    DEBUGPUBLIC("HrMapProxyToAddr()\n");

    sc = MAPIAllocateBuffer( CbNewFlagList(lpAdrList->cEntries), (LPVOID*)&lpFlagList);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    lpFlagList->cFlags = lpAdrList->cEntries;

    for(i = 0; i < lpAdrList->cEntries; i++)
    {
        lpFlagList->ulFlag[i] = MAPI_UNRESOLVED;
    }

    hr = HrMAPICreateSizedAddressList(lpAdrList->cEntries, &lpRecipList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0; i < lpAdrList->cEntries; i++)
    {
        if((lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].ulPropTag != PR_SEARCH_KEY) ||
           (lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.cb == 0) ||
           (lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.lpb == NULL))
        {
            prop[0].ulPropTag  = PR_DISPLAY_NAME;
            prop[0].Value.LPSZ = TEXT("UNKNOWN:UNKNOWN");
        }
        else
        {
            prop[0].ulPropTag  = PR_DISPLAY_NAME;
            prop[0].Value.LPSZ =
                (LPTSTR)lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.lpb;
        }

        prop[1].ulPropTag = PR_RECIPIENT_TYPE;
        prop[1].Value.ul = MAPI_TO;

        hr = HrMAPISetAddressList(
            i,
            2,
            prop,
            lpRecipList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    hr = MAPICALL(lpGalABCont)->ResolveNames(
        lpGalABCont,
        (LPSPropTagArray)&rgPropTags,
        EMS_AB_ADDRESS_LOOKUP,
        lpRecipList,
        lpFlagList);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    for(i = 0; i < lpRecipList->cEntries; i++)
    {
        if(lpFlagList->ulFlag[i] != MAPI_RESOLVED)
        {
            if(lpFlagList->ulFlag[i] == MAPI_AMBIGUOUS)
            {
                hrT = MAPI_E_AMBIGUOUS_RECIP;
            }
            else
            {
                hrT = NOERROR; // MAPI_E_NOT_FOUND
            }
        }
        else
        {
            //
            // Update recipient entry only if an email address was found
            //

            lpszEmailDisplayName = NULL;
            lpszEmailAddressType = NULL;
            lpszEmailAddress     = NULL;
            lpszEmailSearchKey   = NULL;
            cbEmailEid           = 0;
            lpEmailEid           = NULL;            

            hr = HrCreateEmailAddress(
                lpAdrBook,
                lpAdrList->aEntries[i].rgPropVals,
                lpRecipList->aEntries[i].rgPropVals[IDISPNAME].Value.LPSZ,
                lpRecipList->aEntries[i].rgPropVals[IADDRTYPE].Value.LPSZ,
                lpRecipList->aEntries[i].rgPropVals[IEMAILADDR].Value.LPSZ,
                lpRecipList->aEntries[i].rgPropVals[IENTRYID].Value.bin.cb,
                (LPENTRYID)lpRecipList->aEntries[i].rgPropVals[IENTRYID].Value.bin.lpb,
                &lpszEmailDisplayName,
                &lpszEmailAddressType,
                &lpszEmailAddress,
                &lpszEmailSearchKey,
                &cbEmailEid,
                &lpEmailEid);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            lpAdrList->aEntries[i].rgPropVals[IDISPNAME].Value.LPSZ  =
                lpszEmailDisplayName;
            lpAdrList->aEntries[i].rgPropVals[IADDRTYPE].Value.LPSZ  =
                lpszEmailAddressType;
            lpAdrList->aEntries[i].rgPropVals[IEMAILADDR].Value.LPSZ =
                lpszEmailAddress;
            
            if(lpszEmailSearchKey == NULL)
            {
                lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.cb = 0;
            }
            else
            {
                lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.cb =
                    cbStrLen(lpszEmailSearchKey);
            }

            lpAdrList->aEntries[i].rgPropVals[ISEARCHKEY].Value.bin.lpb =
                (LPBYTE)lpszEmailSearchKey;
            lpAdrList->aEntries[i].rgPropVals[IENTRYID].Value.bin.cb  =
                cbEmailEid;
            lpAdrList->aEntries[i].rgPropVals[IENTRYID].Value.bin.lpb =
                (LPBYTE)lpEmailEid;

            hrT = NOERROR;
        }

        //
        // Add recipient status to recipient entry in address list
        //

        lpAdrList->aEntries[i].rgPropVals[IRECIPSTAT].ulPropTag =
            PR_RECIPSTAT;
        lpAdrList->aEntries[i].rgPropVals[IRECIPSTAT].Value.ul = hrT;
    }

cleanup:

    MAPIFREEBUFFER(lpFlagList);

    FREEPADRLIST(lpRecipList);

    RETURN(hr);
}

//$--HrNonDeliverRecipient------------------------------------------------------
// Non-deliver a recipient.
// -----------------------------------------------------------------------------
HRESULT HrNonDeliverRecipient(          // RETURNS: return code
    IN ULONG ulReasonCode,              // NDR reason code
    IN ULONG ulDiagnosticCode,          // NDR diagnostic code
    IN LPFILETIME lpftReportTime,       // report time
    IN ULONG ulRecipientNumber,         // recipient number
    IN ULONG ulOffset,                  // offset in NDR address list
    IN ULONG cValues,                   // count of property values
    IN LPSPropValue lpProps,            // pointer to property values
    IN OUT LPADRLIST lpAdrList)         // pointer to NDR address list
{
    HRESULT      hr              = NOERROR;
    ULONG        i               = 0;
    ULONG        j               = 0;
    ULONG        ulExtraProps[4] = {0};
    LPSPropValue lpExtraProps[4] = {NULL};
    SPropValue   ExtraProps[5]   = {0};
    ULONG        cNewValues      = 0;
    LPSPropValue lpNewProps      = NULL;
    LPSPropValue lpPropT         = NULL;

    DEBUGPUBLIC("HrNonDeliverRecipient()\n");

    lpPropT = LpValFindProp(PR_NDR_REASON_CODE, cValues, lpProps);

    if(lpPropT != NULL)
    {
        ulExtraProps[j  ]  = lpPropT->ulPropTag;
        lpExtraProps[j++]  = lpPropT;
        lpPropT->ulPropTag = PR_NULL;
    }

    ExtraProps[i].ulPropTag = PR_NDR_REASON_CODE;
    ExtraProps[i].Value.ul  = ulReasonCode;
    i++;

    lpPropT = LpValFindProp(PR_NDR_DIAG_CODE, cValues, lpProps);

    if(lpPropT != NULL)
    {
        ulExtraProps[j  ]  = lpPropT->ulPropTag;
        lpExtraProps[j++]  = lpPropT;
        lpPropT->ulPropTag = PR_NULL;
    }

    ExtraProps[i].ulPropTag = PR_NDR_DIAG_CODE;
    ExtraProps[i].Value.ul  = ulDiagnosticCode;
    i++;

    lpPropT = LpValFindProp(PR_REPORT_TIME, cValues, lpProps);

    if(lpPropT != NULL)
    {
        ulExtraProps[j  ]  = lpPropT->ulPropTag;
        lpExtraProps[j++]  = lpPropT;
        lpPropT->ulPropTag = PR_NULL;
    }

    ExtraProps[i].ulPropTag = PR_REPORT_TIME;
    ExtraProps[i].Value.ft  = *lpftReportTime;
    i++;

    lpPropT = LpValFindProp(PR_REPORT_TEXT, cValues, lpProps);

    if(lpPropT != NULL)
    {
        ulExtraProps[j  ]  = lpPropT->ulPropTag;
        lpExtraProps[j++]  = lpPropT;
        lpPropT->ulPropTag = PR_NULL;
    }

    ExtraProps[i].ulPropTag  = PR_REPORT_TEXT;
    ExtraProps[i].Value.LPSZ = TEXT("");
    i++;

    lpPropT = LpValFindProp(PR_RECIPIENT_NUMBER, cValues, lpProps);

    if(lpPropT == NULL)
    {
        ExtraProps[i].ulPropTag = PR_RECIPIENT_NUMBER;
        ExtraProps[i].Value.ul  = ulRecipientNumber;
        i++;
    }

    hr = HrMAPIAppendSPropValues(
        cValues,
        lpProps,
        i,
        ExtraProps,
        &cNewValues,
        &lpNewProps);

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(lpNewProps);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMAPISetAddressList(
        ulOffset,
        cNewValues,
        lpNewProps,
        lpAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    MAPIFREEBUFFER(lpNewProps);

    for(i = 0; i < j; i++)
    {
        lpPropT = lpExtraProps[i];
        lpPropT->ulPropTag = ulExtraProps[i];
    }

    RETURN(hr);
}
