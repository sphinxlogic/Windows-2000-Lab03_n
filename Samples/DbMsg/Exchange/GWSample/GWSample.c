// --gwsample.c-----------------------------------------------------------------
//
//  Sample gateway application.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "gwmain.h"
#include "gwsample.h"
#include "attrname.h"
#include "convcwrp.h"
#include "ipmconv.h"
#include "sgwdata.h"

TCHAR szAppName[]       = TEXT("GWSAMPLE");
TCHAR szWindowTitle[]   = TEXT("Sample Gateway");

// Output/Input file name prefix.
TCHAR szFilePrefix[]    = TEXT("SGW");

#define C_EQU   TEXT("C=")
#define A_EQU   TEXT("A=")
#define P_EQU   TEXT("P=")

static TCHAR szServiceName[MAX_SERVICE_NAME_LENGTH+1] = {0};

static LPTSTR           lpszLocalGDI    = NULL;
static CRITICAL_SECTION csGatewaySeqNo  = {0};
static ULONG            ulGatewaySeqNo  = 0;

static LPMAPISESSION    lpSession       = NULL;
static LPMDB            lpStore         = NULL;
static LPMAPIFOLDER     lpRootFolder    = NULL;
static LPMAPIFOLDER     lpMtsInFolder   = NULL;
static LPMAPIFOLDER     lpMtsOutFolder  = NULL;
static ULONG            cbGalEid        = 0;
static LPENTRYID        lpGalEid        = NULL;

//performance code

LONG    cInThreads           = 0;
ULONG   cInMessages          = 0;

LPTSTR  lpszAddressType      = NULL;

LPTSTR  lpszSysAdminName     = NULL;
LPTSTR  lpszSysAdminAddr     = NULL;

LPTSTR  lpszInDirectory      = NULL;
LPTSTR  lpszInConverter      = NULL;
LPWSTR  lpszInConverterW     = NULL;

BOOL    fInEnabled           = FALSE;

ULONG   cbBufferSize         = 0;
LPBYTE  lpbBuffer            = NULL;
ULONG   cBufferArraySize     = 0;
LPTSTR  *lppszBufferArray    = NULL;

DWORD   dwInSleepInterval    = 0;
DWORD   dwInPollInterval     = 0;

LONG    cOutThreads          = 0;
ULONG   cOutMessages         = 0;

LPTSTR  lpszOutDirectory     = NULL;
LPTSTR  lpszOutConverter     = NULL;
LPWSTR  lpszOutConverterW    = NULL;

BOOL    fOutEnabled          = FALSE;

DWORD   dwOutSleepInterval   = 0;
DWORD   dwOutPollInterval    = 0;

LPTSTR  lpszArchiveDirectory = NULL;

HANDLE  hEventLog            = NULL;

typedef struct _id_item
{
    CRITICAL_SECTION *lpcs;     // only used by list
    LPTSTR           lpszId;
    struct _id_item  *next;
} IDITEM, *LPIDITEM;

static CRITICAL_SECTION csInboundIdList  = {0};
static CRITICAL_SECTION csOutboundIdList = {0};

static IDITEM InboundIdList  = {0};
static IDITEM OutboundIdList = {0};

// Size is because country 2-3, ADMD 0-16, PRMD is 1-16 and LocalId1-32 plus
// size for "/c=/p=/a=/l=". So 3+16+16+32+12+1 = 80.
#define cbMTSIDMax (80)

//$--HrCreateIdItem-------------------------------------------------------------
//  Creates an ID item.
// -----------------------------------------------------------------------------
HRESULT HrCreateIdItem(                 // RETURNS: return code
    IN  LPSTR lpszId,                   // identifier
    OUT LPIDITEM *lppIdItem)            // identifier item
{
	HRESULT  hr       = NOERROR;
    LPIDITEM lpIdItem = NULL;
    ULONG    cBytes   = 0;

    *lppIdItem = NULL;

    cBytes = sizeof(IDITEM);

    hr = MAPIAllocateBuffer(cBytes, (void **)&lpIdItem);

    if(FAILED(hr))
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;                                
    }                                                   

    ZeroMemory(lpIdItem, cBytes);

    cBytes  = cbStrLen(lpszId);

    hr = MAPIAllocateMore(cBytes, lpIdItem, (void **)&lpIdItem->lpszId);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lstrcpy(lpIdItem->lpszId, lpszId);

    *lppIdItem = lpIdItem;

cleanup:

    RETURN(hr);
}

//$--HrDestroyIdItem------------------------------------------------------------
//  Destroys an ID item.
// -----------------------------------------------------------------------------
HRESULT HrDestroyIdItem(                // RETURNS: return code
    IN OUT LPIDITEM *lppIdItem)         // identifier item
{
	HRESULT hr = NOERROR;

    MAPIFREEBUFFER(*lppIdItem);

    RETURN(hr);
}

//$--HrLookupIdItem-------------------------------------------------------------
//  Looks up an ID item.
// -----------------------------------------------------------------------------
HRESULT HrLookupIdItem(                 // RETURNS: return code
    IN LPIDITEM lpIdList,               // identifier item list
    IN LPTSTR lpszId,                   // identifier
    IN OUT LPIDITEM *lppIdItem)         // identifier item
{
	HRESULT  hr       = EDK_E_NOT_FOUND;
    HRESULT  hrT      = NOERROR;
    LPIDITEM lpIdItem = NULL;

    __try
    {
        *lppIdItem = NULL;

        lpIdItem = lpIdList->next;
    
        while(lpIdItem != NULL)
        {
            if(!lstrcmpi(lpIdItem->lpszId, lpszId))
            {
                //
                // Found identifier in ID list
                //

                *lppIdItem = lpIdItem;

                hr = NOERROR;
                goto cleanup;
            }

            lpIdItem = lpIdItem->next;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

cleanup:

    RETURN(hr);
}

//$--HrAddIdItem----------------------------------------------------------------
//  Adds an ID item to a list.
// -----------------------------------------------------------------------------
HRESULT HrAddIdItem(                    // RETURNS: return code
    IN LPIDITEM lpIdList,               // identifier item list
    IN LPTSTR lpszId,                   // identifier
    IN OUT LPIDITEM *lppIdItem)         // identifier item
{
	HRESULT  hr       = EDK_E_NOT_FOUND;
    HRESULT  hrT      = NOERROR;
    LPIDITEM lpIdItem = NULL;

    EnterCriticalSection(lpIdList->lpcs);

    hr = HrLookupIdItem(lpIdList, lpszId, &lpIdItem);

    if(hr != EDK_E_NOT_FOUND)
    {
        hr = HR_LOG(EDK_E_ALREADY_EXISTS);
        goto cleanup;
    }

    __try
    {
        *lppIdItem = NULL;

        hr = HrCreateIdItem(
            lpszId,
            &lpIdItem);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        lpIdItem->next = lpIdList->next;

        lpIdList->next = lpIdItem;

        *lppIdItem = lpIdItem;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

cleanup:

    LeaveCriticalSection(lpIdList->lpcs);

    RETURN(hr);
}

//$--HrRemoveIdItem-------------------------------------------------------------
//  Removes an ID item from a list.
// -----------------------------------------------------------------------------
HRESULT HrRemoveIdItem(                 // RETURNS: return code
    IN LPIDITEM lpIdList,               // identifier item list
    IN LPIDITEM lpIdItem)               // identifier item
{
	HRESULT  hr           = EDK_E_NOT_FOUND;
    HRESULT  hrT          = NOERROR;
    LPIDITEM lpPrevIdItem = NULL;
    LPIDITEM lpCurrIdItem = NULL;

    EnterCriticalSection(lpIdList->lpcs);

    __try
    {
        lpCurrIdItem = lpIdList->next;
    
        while(lpCurrIdItem != NULL)
        {
            if(lpCurrIdItem == lpIdItem)
            {
                //
                // Found identifier item in ID list
                //

                if(lpIdList->next == lpIdItem)
                {
                    // item found at head of list
                    lpIdList->next = lpIdItem->next;
                }
                else
                {
                    lpPrevIdItem->next = lpIdItem->next;
                }

                hr = NOERROR;
                goto cleanup;
            }

            lpPrevIdItem = lpCurrIdItem;
            lpCurrIdItem = lpCurrIdItem->next;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

cleanup:

    hrT = HrDestroyIdItem(&lpIdItem);

    if(FAILED(hr))
    {
        hrT = HR_LOG(E_FAIL);
    }

    LeaveCriticalSection(lpIdList->lpcs);

    RETURN(hr);
}

//$--HrEmptyIdList--------------------------------------------------------------
//  Empty an ID list.
// -----------------------------------------------------------------------------
HRESULT HrEmptyIdList(                  // RETURNS: return code
    IN LPIDITEM lpIdList)               // identifier item list
{
	HRESULT  hr       = NOERROR;
    HRESULT  hrT      = NOERROR;
    LPIDITEM lpIdItem = NULL;

    EnterCriticalSection(lpIdList->lpcs);

    __try
    {
        lpIdItem = lpIdList->next;
    
        while(lpIdItem != NULL)
        {
            lpIdList->next = lpIdItem->next;

            MAPIFREEBUFFER(lpIdItem);

            lpIdItem = lpIdList->next;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    LeaveCriticalSection(lpIdList->lpcs);

    RETURN(hr);
}

//$--HrCreateMtsId--------------------------------------------------------------
//  Returns the newly created stringized MTS identifier. It takes in a site
//  MTS identifier string that contains the country, ADMD and PRMD code and
//  creates the local identifier to create a new MTS identifier.
// -----------------------------------------------------------------------------
HRESULT HrCreateMtsId(                  // RETURNS: return code
    IN  LPSTR lpszSiteMtsId,            // site MTS identifier
    IN  LPSTR lpszGatewayName,          // gateway name
    IN  ULONG ulSeqNo,                  // sequence number
    OUT LPSTR lpszMTSID)                // MTS identifier
{
	HRESULT    hr                     = NOERROR;
    SYSTEMTIME st                     = {0};
	CHAR       rgchUTC[cbMTSIDMax]    = {0};
	ULONG      cbMTName               = 0;
	LPSTR      lpszMTName[cbMTSIDMax] = {0};
	ULONG      cbSeqNo                = 0;
	CHAR       rgchSeqNo[9]           = {0};

	// Get the current time and make it a UTCTime string
    GetSystemTime(&st);
    sprintf(rgchUTC, "%04u%02u%02u%02u%02u%02uZ",
        st.wYear,
        st.wMonth,
        st.wDay,
        st.wHour,
        st.wMinute,
        st.wSecond);

	// format the ulSeqNo into a string and get's length
	sprintf((LPSTR)rgchSeqNo, "%08lx", ulSeqNo);
	cbSeqNo = strlen(rgchSeqNo);

	// find out how much of the gateway name can be put into the local identifer
	cbMTName = 32 - cbSeqNo - strlen(rgchUTC) - 2;

	lstrcpy((LPSTR)lpszMTName, lpszGatewayName);

	if(cbMTName < (ULONG)lstrlen((LPSTR)lpszMTName))
    {
		lpszMTName[cbMTName] = 0;
	}

    //			
	// Format of local identifier is:
	//     "Gateway Name-stringized UTC Time-stringized ulSeqNo"
	// NOTE: DO NOT CHANGE Delimiter to "/".
    //

	sprintf(
	    lpszMTSID,
	    "%s;L=%s-%s-%s",
	    lpszSiteMtsId,
	    lpszMTName,
	    rgchUTC,
	    rgchSeqNo);	

	RETURN(hr);
}

//$--DumpPropProblems-----------------------------------------------------------
//  Dumps property problems to the debug log.
//------------------------------------------------------------------------------
VOID DumpPropProblems(                  // RETURNS: nothing
    IN LPSTR lpszFile,                  // source file name
    IN ULONG ulLine,                    // source line number
    IN LPSPropProblemArray lpProblems)  // property problems
{
    ULONG i = 0;

    DEBUGPUBLIC("DumpPropProblems()\n");

    if(lpProblems == NULL)
    {
        goto cleanup;
    }

#ifdef DEBUG
    for(i = 0; i < lpProblems->cProblem; i++)
    {
        _Assert("PROBLEM", lpszFile, ulLine, D_WARNING, 0, "%lu\t%08lx\t%08lx\n",
            lpProblems->aProblem[i].ulIndex,
            lpProblems->aProblem[i].ulPropTag,
            lpProblems->aProblem[i].scode);
    }
#endif

cleanup:

    return;
}

#ifdef DEBUG
#define DUMPPROPPROBLEMS(_prob) DumpPropProblems(__FILE__,__LINE__,(_prob))
#else
#define DUMPPROPPROBLEMS(_prob) ((void)0)
#endif

//$--HrCreateEnterpriseGDI------------------------------------------------------
//  Create the enterprise GDI from the input string.
// -----------------------------------------------------------------------------
HRESULT HrCreateEnterpriseGDI(          // RETURNS: return code
    IN LPTSTR lpsz,                     // pointer to input string
    IN LPTSTR lpszEOT,                  // pointer to separator character(s)
    OUT LPTSTR *lppszGDI)               // pointer to enterprise GDI
{
    HRESULT hr          = NOERROR;
    SCODE   sc          = 0;
    ULONG   cBytes      = 0;
    ULONG   cArraySize  = 0;
    LPTSTR  *lppszArray = NULL;
    LPTSTR  lpszCountry = NULL;
    LPTSTR  lpszAdmd    = NULL;
    LPTSTR  lpszPrmd    = NULL;
    ULONG   i           = 0;

    DEBUGPUBLIC("HrCreateEnterpriseGDI()\n");

    *lppszGDI = NULL;

    hr = HrStrTokAll(
        lpsz,
        lpszEOT,
        &cArraySize,
        &lppszArray);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    for(i = 0; i < cArraySize; i++)
    {
        if(lppszArray[i] == NULL)
        {
            ;
        }
        else if(!_tcsnicmp(lppszArray[i], C_EQU, lstrlen(C_EQU)))
        {
            lpszCountry = lppszArray[i];
        }
        else if(!_tcsnicmp(lppszArray[i], A_EQU, lstrlen(A_EQU)))
        {
            lpszAdmd = lppszArray[i];
        }
        else if(!_tcsnicmp(lppszArray[i], P_EQU, lstrlen(P_EQU)))
        {
            lpszPrmd = lppszArray[i];
        }
    }

    if(lpszCountry == NULL)
    {
        lpszCountry = TEXT("C=;");
    }

    if(lpszAdmd == NULL)
    {
        lpszAdmd = TEXT("A=;");
    }

    if(lpszPrmd == NULL)
    {
        lpszPrmd = TEXT("P=;");
    }

    cBytes = (lstrlen(TEXT(";;;")) +
              lstrlen(lpszCountry) +
              lstrlen(lpszAdmd) +
              lstrlen(lpszPrmd) + 1) * sizeof(TCHAR);

    sc = MAPIAllocateBuffer(cBytes, (void **)lppszGDI);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    lstrcpy(*lppszGDI, lpszCountry);
    lstrcat(*lppszGDI, TEXT(";"));
    lstrcat(*lppszGDI, lpszAdmd);
    lstrcat(*lppszGDI, TEXT(";"));
    lstrcat(*lppszGDI, lpszPrmd);
    lstrcat(*lppszGDI, TEXT(";"));

    CharUpperBuff(*lppszGDI, cBytes/sizeof(TCHAR));

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszGDI);
    }

    MAPIFREEBUFFER(lppszArray);

    RETURN(hr);
}

//$--HrGetMtsIdEnterpriseGDI----------------------------------------------------
//  Get the enterprise GDI from the MTS-ID (or SUBJECT-MTS-ID).
// -----------------------------------------------------------------------------
HRESULT HrGetMtsIdEnterpriseGDI(        // RETURNS: return code
    IN LPMESSAGE lpMessage,             // pointer to message
    IN ULONG ulPropTag,                 // MTS-ID property tag
    OUT LPTSTR *lppszGDI)               // pointer to enterprise GDI
{
    HRESULT hr          = NOERROR;
    ULONG   cBytes      = 0;
    LPTSTR  lpszMtsId   = NULL;

    DEBUGPUBLIC("HrGetMtsIdEnterpriseGDI()\n");

    *lppszGDI = NULL;

    hr = HrMAPIGetPropBinary(
        (LPMAPIPROP)lpMessage,
        ulPropTag,
        &cBytes,
        (LPVOID *)&lpszMtsId);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = HrCreateEnterpriseGDI(
        lpszMtsId,
        TEXT("/;"),
        lppszGDI);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszGDI);
    }

    MAPIFREEBUFFER(lpszMtsId);

    RETURN(hr);
}

//$--HrGetTraceEnterpriseGDI----------------------------------------------------
//  Get the enterprise GDI from the external trace information.
// -----------------------------------------------------------------------------
HRESULT HrGetTraceEnterpriseGDI(        // RETURNS: return code
    IN LPMESSAGE lpMessage,             // pointer to message
    IN ULONG ulPropTag,                 // external trace info property tag
    OUT LPTSTR *lppszGDI)               // pointer to enterprise GDI
{
    HRESULT      hr           = NOERROR;
    SCODE        sc           = 0;
    ULONG        cBytes       = 0;
    LPTRACEINFO  lpTraceInfo  = NULL;
    LPTRACEENTRY lpTraceEntry = NULL;
    FILETIME     ft           = {0};
    LPTSTR       lpszT        = NULL;
    LPTSTR       lpszCountry  = NULL;
    LPTSTR       lpszAdmd     = NULL;
    LPTSTR       lpszPrmd     = NULL;
    ULONG        i            = 0;

    DEBUGPUBLIC("HrGetTraceEnterpriseGDI()\n");

    *lppszGDI = NULL;

    hr = HrMAPIGetPropBinary(
        (LPMAPIPROP)lpMessage,
        ulPropTag,
        &cBytes,
        (LPVOID *)&lpTraceInfo);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = HrTraceGotoFirstEntry(
        lpTraceInfo,
        &i,
        &lpTraceEntry);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrTraceOpenEntry(
        lpTraceEntry,
        &i,
        &ft,
        &ft,
        &lpszAdmd,
        &lpszCountry,
        &lpszPrmd,
        &lpszT,
        &lpszT,
        &lpszT);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(lpszCountry == NULL)
    {
        lpszCountry = TEXT("C=;");
    }

    if(lpszAdmd == NULL)
    {
        lpszAdmd = TEXT("A=;");
    }

    if(lpszPrmd == NULL)
    {
        lpszPrmd = TEXT("P=;");
    }

    cBytes = (lstrlen(TEXT("C=;A=;P=;")) +
              lstrlen(lpszCountry) +
              lstrlen(lpszAdmd) +
              lstrlen(lpszPrmd) + 1) * sizeof(TCHAR);

    sc = MAPIAllocateBuffer(cBytes, (void **)lppszGDI);

    if(FAILED(sc))
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    lstrcpy(*lppszGDI, C_EQU);
    lstrcat(*lppszGDI, lpszCountry);
    lstrcat(*lppszGDI, TEXT(";A="));
    lstrcat(*lppszGDI, lpszAdmd);
    lstrcat(*lppszGDI, TEXT(";P="));
    lstrcat(*lppszGDI, lpszPrmd);
    lstrcat(*lppszGDI, TEXT(";"));

    CharUpperBuff(*lppszGDI, cBytes/sizeof(TCHAR));

cleanup:

    if(FAILED(hr))
    {
        MAPIFREEBUFFER(*lppszGDI);
    }

    MAPIFREEBUFFER(lpTraceInfo);

    RETURN(hr);
}

//$--HrFixUpRecipientNumbers----------------------------------------------------
//  Fix up recipient numbers.
// -----------------------------------------------------------------------------
static HRESULT HrFixUpRecipientNumbers( // RETURNS: return code
    IN OUT LPADRLIST lpEnvelopeAdrList, // pointer to envelope address list
    IN OUT LPADRLIST lpMessageAdrList)  // pointer to message address list
{
    HRESULT      hr                = NOERROR;
    HRESULT      hrT               = NOERROR;
    SCODE        sc                = 0;
    ULONG        cb                = 0;

    ULONG*       rgulOrigRecipNums = NULL;

    LPSPropValue lpPropT           = NULL;

    ULONG        i                 = 0;
    ULONG        j                 = 0;

    ULONG        cValues           = 0;
    LPSPropValue lpProps           = NULL;

    DEBUGPRIVATE("HrFixUpRecipientNumbers()\n");

    if( (!((lpMessageAdrList == NULL) || (lpMessageAdrList->cEntries == 0))) &&
        (!((lpEnvelopeAdrList == NULL) || (lpEnvelopeAdrList->cEntries == 0))))
    {
        cb = lpMessageAdrList->cEntries * (sizeof(ULONG) + MAX_ALIGN);

        sc = MAPIAllocateBuffer(cb, (void **)&rgulOrigRecipNums);

        if(FAILED(sc))
        {
            hr = HR_LOG(E_OUTOFMEMORY);
            goto cleanup;
        }

        for(i = 0; i < lpMessageAdrList->cEntries; i++)
        {
            rgulOrigRecipNums[i] = 0;

            cValues = lpMessageAdrList->aEntries[i].cValues;
            lpProps = lpMessageAdrList->aEntries[i].rgPropVals;

            if(lpProps != NULL)
            {
                lpPropT = LpValFindProp(PR_RECIPIENT_NUMBER, cValues, lpProps);

                if(lpPropT == NULL)
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                rgulOrigRecipNums[i] = lpPropT->Value.ul;

                lpPropT->ulPropTag = 
                    PROP_TAG(PT_ERROR, PROP_ID(lpPropT->ulPropTag));
            }
        }

        for(i = 0; i < lpEnvelopeAdrList->cEntries; i++)
        {
            cValues = lpEnvelopeAdrList->aEntries[i].cValues;
            lpProps = lpEnvelopeAdrList->aEntries[i].rgPropVals;

            if(lpProps != NULL)
            {
                lpPropT = LpValFindProp(PR_RECIPIENT_NUMBER, cValues, lpProps);

                if(lpPropT == NULL)
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                for(j = 0; j < lpMessageAdrList->cEntries; j++)
                {
                    if(rgulOrigRecipNums[j] == lpPropT->Value.ul)
                    {
                        lpPropT->Value.ul = j+1;
                    }
                }
            }
        }

        //
        // Clear recipient numbers for message address list.
        //

        hr = HrDeleteAddressListProperty(
            PR_RECIPIENT_NUMBER,
            (LPADRLIST)lpMessageAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    //
    // Clear row IDs for envelope address list.
    //

    if(!((lpEnvelopeAdrList == NULL) || (lpEnvelopeAdrList->cEntries == 0)))
    {
        hr = HrDeleteAddressListProperty(
            PR_ROWID,
            (LPADRLIST)lpEnvelopeAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    //
    // Clear row IDs for message address list.
    //

    if(!((lpMessageAdrList == NULL) || (lpMessageAdrList->cEntries == 0)))
    {
        hr = HrDeleteAddressListProperty(
            PR_ROWID,
            (LPADRLIST)lpMessageAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

cleanup:

    MAPIFREEBUFFER(rgulOrigRecipNums);

    RETURN(hr);
}

//$--HrDeleteSenderProps--------------------------------------------------------
// Delete sender properties from the message.
// -----------------------------------------------------------------------------
HRESULT HrDeleteSenderProps(            // RETURNS: return code
    IN LPMESSAGE  lpMessage)            // pointer to message
{
    HRESULT hr  = NOERROR;
    HRESULT hrT = NOERROR;

    LPSPropProblemArray lpProblems = NULL;

    SizedSPropTagArray(10, rgPropTags) =
    {
        10,
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
        }
    };

    DEBUGPUBLIC("HrDeleteSenderProps()\n");

    hrT = MAPICALL(lpMessage)->DeleteProps(
        lpMessage,
        (SPropTagArray *)&rgPropTags,
        &lpProblems);

    if(FAILED(hrT))
    {
        lpProblems = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    DUMPPROPPROBLEMS(lpProblems);

cleanup:

    MAPIFREEBUFFER(lpProblems);

    RETURN(hr);
}

//$--HrDeleteMtsIdProps---------------------------------------------------------
// Delete MTS-ID properties from the message.
// -----------------------------------------------------------------------------
HRESULT HrDeleteMtsIdProps(             // RETURNS: return code
    IN LPMESSAGE  lpMessage)            // pointer to message
{
    HRESULT hr = NOERROR;

    LPSPropProblemArray lpProblems = NULL;

    SizedSPropTagArray(1, rgPropTags) =
    {
        1,
        {
            PR_MTS_ID,
        }
    };

    DEBUGPUBLIC("HrDeleteMtsIdProps()\n");

    hr = MAPICALL(lpMessage)->DeleteProps(
        lpMessage,
        (SPropTagArray *)&rgPropTags,
        &lpProblems);

    if(FAILED(hr))
    {
        lpProblems = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    DUMPPROPPROBLEMS(lpProblems);

cleanup:

    MAPIFREEBUFFER(lpProblems);

    RETURN(hr);
}

//$--HrDeleteTraceProps---------------------------------------------------------
// Delete trace properties from the message.
// -----------------------------------------------------------------------------
HRESULT HrDeleteTraceProps(                  // RETURNS: return code
    IN LPMESSAGE  lpMessage)            // pointer to message
{
    HRESULT hr  = NOERROR;

    LPSPropProblemArray lpProblems = NULL;

    SizedSPropTagArray(1, rgPropTags) =
    {
        1,
        {
            PR_TRACE_INFO,
        }
    };

    DEBUGPUBLIC("HrDeleteTraceProps()\n");

    hr = MAPICALL(lpMessage)->DeleteProps(
        lpMessage,
        (SPropTagArray *)&rgPropTags,
        &lpProblems);

    if(FAILED(hr))
    {
        lpProblems = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    DUMPPROPPROBLEMS(lpProblems);

cleanup:

    MAPIFREEBUFFER(lpProblems);

    RETURN(hr);
}

//$--HrNonDeliverAllRecipList---------------------------------------------------
//  Create a recipient list to non-deliver all recipients.
// -----------------------------------------------------------------------------
HRESULT HrNonDeliverAllRecipList(       // RETURNS: return code
    IN LPMESSAGE lpMessage,             // message
    IN LPADRLIST *lppAdrList)           // address list
{
    HRESULT      hr            = NOERROR;
    HRESULT      hrT           = NOERROR;
    LPSRowSet    lpRows        = NULL;
    LPADRLIST    lpAdrList     = NULL;
    LPADRLIST    lpAllAdrList  = NULL;
    LPMAPITABLE  lpTable       = NULL;

    LPSPropValue lpPropT       = NULL;

    ULONG        cFailedValues = 0;
    LPSPropValue lpFailedProps = NULL;

    ULONG        i             = 0;

    DEBUGPUBLIC("HrNonDeliverAllRecipList()");

    *lppAdrList = NULL;

    //
    // Get the recipient table for the message
    //

    hr = MAPICALL(lpMessage)->GetRecipientTable(
        lpMessage,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hr))
    {
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
        goto cleanup;
    }

    lpAdrList = (LPADRLIST)lpRows;

    hr = HrNDRCreateFailedRecipList(
        &lpAllAdrList);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    for(i = 0; i < lpAdrList->cEntries; i++)
    {
        hr = HrNDRGetFailedRecipList(
            &lpAdrList->aEntries[i],
            0,
            NULL,
            &cFailedValues,
            &lpFailedProps);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        lpPropT = LpValFindProp(PR_RECIPIENT_NUMBER, cFailedValues, lpFailedProps);

        if(lpPropT != NULL)
        {
            lpPropT->Value.ul = (i+1);
        }

        hr = HrNDRAddToFailedRecipList(
            cFailedValues,
            lpFailedProps,
            &lpAllAdrList);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        MAPIFREEBUFFER(lpFailedProps);
    }   // end for

    *lppAdrList  = lpAllAdrList;
    lpAllAdrList = NULL;

cleanup:

    MAPIFREEBUFFER(lpFailedProps);

    FREEPADRLIST(lpAdrList);        // also frees lpRows

    FREEPADRLIST(lpAllAdrList);

    ULRELEASE(lpTable);

    if(FAILED(hr))
    {
        FREEPADRLIST(lpAllAdrList);
        *lppAdrList = NULL;
    }

    RETURN(hr);
}

//$--HrCreateNonDeliveryReport--------------------------------------------------
//  Create a non-delivery report.
// -----------------------------------------------------------------------------
HRESULT HrCreateNonDeliveryReport(          // RETURNS: return code
    IN BOOL fCreateMtsId,                   // create MTS identifier
    IN LPADRBOOK lpAdrBook,                 // pointer to address book
    IN LPMAPIFOLDER lpFolder,               // pointer to folder
    IN LPMESSAGE lpMessage,                 // pointer to message
    IN LPADRLIST lpAdrList,                 // pointer to address list
    OUT LPMESSAGE *lppReport)               // pointer to report
{
    HRESULT      hr                   = NOERROR;
    LPMESSAGE    lpReport             = NULL;
    ULONG        cBytes               = 0;
    ULONG        cValues              = 0;
    LPSPropValue lpProps              = NULL;

    LPTSTR       lpszEmailDisplayName = NULL;
    LPTSTR       lpszEmailAddressType = NULL;
    LPTSTR       lpszEmailAddress     = NULL;
    LPTSTR       lpszEmailSearchKey   = NULL;
    ULONG        cbEmailEid           = 0;
    LPENTRYID    lpEmailEid           = NULL;

	LPSPropProblemArray lpProblems    = NULL;

    CHAR         szGatewayName[MAX_SERVICE_NAME_LENGTH+1] = {0};

    ULONG        ulMtsIdSeqNo          = 0;
    CHAR         rgchMTSID[cbMTSIDMax] = {0};

    DEBUGPUBLIC("HrCreateNonDeliveryReport()\n");

    *lppReport = NULL;

    if(fCreateMtsId == TRUE)
    {
        EnterCriticalSection(&csGatewaySeqNo);
        ulMtsIdSeqNo = ++ulGatewaySeqNo;
        LeaveCriticalSection(&csGatewaySeqNo);

        //
        // Get gateway service name.
        //

        hr = HrServiceGetName(
            szGatewayName);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        hr = HrCreateMtsId(
            lpszLocalGDI,
            szGatewayName,
            ulMtsIdSeqNo,
            rgchMTSID);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }

    hr = HrNDRGetFailedProps(
        lpMessage,
        &cValues,
        &lpProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrNDRCreate(
        lpAdrBook,
        lpFolder,
        lpMessage,
        lpAdrList,
        cValues,
        lpProps,
        &lpReport);

    MAPIFREEBUFFER(lpProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cBytes = CbNewSPropValue(6);

    hr = MAPIAllocateBuffer(cBytes, (void **)&lpProps);

    if(FAILED(hr))
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;                                
    }                                                   

    ZeroMemory(lpProps, cBytes);

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

    lpProps[0].ulPropTag         = PR_SENDER_NAME;
    lpProps[0].Value.LPSZ        = lpszEmailDisplayName;

    lpProps[1].ulPropTag         = PR_SENDER_ADDRTYPE;
    lpProps[1].Value.LPSZ        = lpszEmailAddressType;

    lpProps[2].ulPropTag         = PR_SENDER_EMAIL_ADDRESS;
    lpProps[2].Value.LPSZ        = lpszEmailAddress;

    lpProps[3].ulPropTag         = PR_SENDER_SEARCH_KEY;

    if(lpszEmailSearchKey == NULL)
    {
        lpProps[3].Value.bin.cb  = 0;
        lpProps[3].Value.bin.lpb = NULL;
    }
    else
    {
        lpProps[3].Value.bin.cb  = cbStrLen(lpszEmailSearchKey);
        lpProps[3].Value.bin.lpb = lpszEmailSearchKey;
    }

    lpProps[4].ulPropTag         = PR_SENDER_ENTRYID;
    lpProps[4].Value.bin.cb      = cbEmailEid;
    lpProps[4].Value.bin.lpb     = (LPBYTE)lpEmailEid;

    lpProps[5].ulPropTag         = PR_MTS_ID;
    lpProps[5].Value.bin.cb      = cbStrLen(rgchMTSID);
    lpProps[5].Value.bin.lpb     = (LPBYTE)rgchMTSID;

    if(fCreateMtsId == TRUE)
    {
        cValues = 6;
    }
    else
    {
        cValues = 5;
    }

    hr = MAPICALL(lpReport)->SetProps(
        lpReport,
        cValues,
        lpProps,
        &lpProblems);

    if(FAILED(hr))
    {
        lpProblems = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    DUMPPROPPROBLEMS(lpProblems);
    MAPIFREEBUFFER(lpProblems);

    // Save changes just made to report envelope
    hr = MAPICALL(lpReport)->SaveChanges(
        lpReport,
        KEEP_OPEN_READWRITE);

    if ( FAILED(hr) )
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    *lppReport = lpReport;

cleanup:

    MAPIFREEBUFFER(lpProps);

    MAPIFREEBUFFER(lpProblems);

    RETURN(hr);
}

//$--HrImportMessage------------------------------------------------------------
//  Process an IPM/IPN in MTS-IN.
// -----------------------------------------------------------------------------
HRESULT HrImportMessage(                // RETURNS: return code
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN LPABCONT lpGalABCont,            // pointer to GAL
    IN BOOL fIgnoreRespValue,           // ignore  responsibility value
    IN BOOL fSendNDR,                   // TRUE if NDRs should be generated
    IN DWORD dwStartProcessingTime,     // start processing time
    IN OUT LPMESSAGE lpEnvelope)        // pointer to envelope
{
    HRESULT             hr                     = NOERROR;
    HRESULT             hrT                    = NOERROR;

    LPMESSAGE           lpMessage              = NULL;
    LPATTACH            lpAttach               = NULL;

    ULONG               cEnvelopeValues        = 0;
    LPSPropValue        lpEnvelopeProps        = NULL;
    ULONG               cMessageValues         = 0;
    LPSPropValue        lpMessageProps         = NULL;

    LPADRLIST           lpOriginalEnvelopeAdrList = NULL;
    LPADRLIST           lpOriginalMessageAdrList  = NULL;

    LPADRLIST           lpEnvelopeAdrList      = NULL;
    LPADRLIST           lpMessageAdrList       = NULL;

    LPADRLIST           lpEnvelope_NDR_AdrList = NULL;
    LPADRLIST           lpMessage_NDR_AdrList  = NULL;

    DWORD               dwEndProcessingTime    = 0;
    DWORD               dwTotalProcessingTime  = 0;
    DWORD               dwSleepProcessingTime  = 0;

    ULONG               cEnvelopeMesgAddr         = 0;
    ULONG               cEnvelopeReplyAddr        = 0;
    ULONG               cEnvelopeRecipAddr        = 0;
    LPADRLIST           lpEnvelopeAllAdrList      = NULL;
    LPADRLIST           lpMappedEnvelopeAdrList   = NULL;

    ULONG               cMessageMesgAddr          = 0;
    ULONG               cMessageReplyAddr         = 0;
    ULONG               cMessageRecipAddr         = 0;
    LPADRLIST           lpMessageAllAdrList       = NULL;
    LPADRLIST           lpMappedMessageAdrList    = NULL;

    BOOL                HasContent                = TRUE;

	LPSPropProblemArray lpProblems                = NULL;

    DEBUGPUBLIC("HrImportMessage()\n");

    // Get the attachment in the envelope
    hrT = MAPICALL(lpEnvelope)->OpenAttach(
        lpEnvelope,
        0,
        NULL,
        MAPI_MODIFY,
        &lpAttach);

    if((FAILED(hrT)) && (hrT != MAPI_E_NOT_FOUND))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(hrT == MAPI_E_NOT_FOUND)
    {
        //
        // Message does not have an attachment.
        //

        HasContent = FALSE;
        lpAttach   = NULL;
    }

    if(HasContent == TRUE)
    {
        // Open a message interface on the attachment
        hrT = MAPICALL(lpAttach)->OpenProperty(
            lpAttach,
            PR_ATTACH_DATA_OBJ,
            (LPIID)&IID_IMessage,
            0,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            (LPUNKNOWN *)&lpMessage);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

//------------------------------------------------------------------------------

    //
    // Map envelope addresses
    //

    hr = HrExpandMessageAddressList(
        lpEnvelope,
        &cEnvelopeMesgAddr,
        &cEnvelopeReplyAddr,
        &cEnvelopeRecipAddr,
        &lpOriginalEnvelopeAdrList,
        &lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMapAddrToProxy(
        lpAdrBook,
        lpszAddressType,
        lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMapGatewayProxyToAddr(
        lpAdrBook,
        lpszAddressType,
        lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMapProxyToAddr(
        lpAdrBook,
        lpGalABCont,
        lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrCollapseMessageAddressList(
        lpEnvelope,
        cEnvelopeMesgAddr,
        cEnvelopeReplyAddr,
        cEnvelopeRecipAddr,
        lpEnvelopeAllAdrList,
        &cEnvelopeValues,
        &lpEnvelopeProps,
        &lpMappedEnvelopeAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    FREEPADRLIST(lpEnvelopeAllAdrList);

    //
    // TNEF encode is setting the value of PR_RESPONSIBILITY to FALSE
    // for each recipient entry.
    //

    {
        ULONG        i       = 0;
        LPSPropValue lpPropT = NULL;

        for(i = 0; i < lpOriginalEnvelopeAdrList->cEntries; i++)
        {
            lpPropT = LpValFindProp(
                PR_RESPONSIBILITY,
                lpOriginalEnvelopeAdrList->aEntries[i].cValues,
                lpOriginalEnvelopeAdrList->aEntries[i].rgPropVals);

            if(lpPropT != NULL)
            {
                lpPropT->Value.b = TRUE;
            }
        }

        for(i = 0; i < lpMappedEnvelopeAdrList->cEntries; i++)
        {
            lpPropT = LpValFindProp(
                PR_RESPONSIBILITY,
                lpMappedEnvelopeAdrList->aEntries[i].cValues,
                lpMappedEnvelopeAdrList->aEntries[i].rgPropVals);

            if(lpPropT != NULL)
            {
                lpPropT->Value.b = TRUE;
            }
        }
    }

    if(HasContent == TRUE)
    {
        //
        // Map message addresses
        //

        hr = HrExpandMessageAddressList(
            lpMessage,
            &cMessageMesgAddr,
            &cMessageReplyAddr,
            &cMessageRecipAddr,
            &lpOriginalMessageAdrList,
            &lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMapAddrToProxy(
            lpAdrBook,
            lpszAddressType,
            lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMapGatewayProxyToAddr(
            lpAdrBook,
            lpszAddressType,
            lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMapProxyToAddr(
            lpAdrBook,
            lpGalABCont,
            lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrCollapseMessageAddressList(
            lpMessage,
            cMessageMesgAddr,
            cMessageReplyAddr,
            cMessageRecipAddr,
            lpMessageAllAdrList,
            &cMessageValues,
            &lpMessageProps,
            &lpMappedMessageAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        FREEPADRLIST(lpMessageAllAdrList);
    }

//------------------------------------------------------------------------------

    hr = HrMapRecipProxyToAddr(
        lpAdrBook,
        TRUE,
        fIgnoreRespValue,
        lpGalABCont,
        lpszAddressType,
        lpOriginalEnvelopeAdrList,
        lpMappedEnvelopeAdrList,
        NULL,
        NULL,
        lpEnvelope,
        &lpEnvelopeAdrList,
        &lpEnvelope_NDR_AdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        hr = HrMapRecipProxyToAddr(
            lpAdrBook,
            FALSE,
            fIgnoreRespValue,
            lpGalABCont,
            lpszAddressType,
            lpOriginalMessageAdrList,
            lpMappedMessageAdrList,
            lpEnvelopeAdrList,
            lpEnvelope_NDR_AdrList,
            lpMessage,
            &lpMessageAdrList,
            &lpMessage_NDR_AdrList);

        FREEPADRLIST(lpOriginalMessageAdrList);

        FREEPADRLIST(lpMessage_NDR_AdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    // Non-deliver any recipients that could not be mapped.

    if((lpEnvelope_NDR_AdrList != NULL) &&
       (lpEnvelope_NDR_AdrList->cEntries != 0) &&
       (fSendNDR == TRUE))
    {
        LPMESSAGE lpReportEnvelope = NULL;

        //
        // Clear row IDs for envelope NDR address list.
        //

        hr = HrDeleteAddressListProperty(
            PR_ROWID,
            (LPADRLIST)lpEnvelope_NDR_AdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        //
        // Create a non delivery report in MTS-OUT
        //

        hr = HrCreateNonDeliveryReport(
            TRUE,
            lpAdrBook,
            lpMtsOutFolder,
            lpMessage,
            lpEnvelope_NDR_AdrList,
            &lpReportEnvelope);

        if(FAILED(hr))
        {
            ;
        }
        else
        {
            HANDLE hNewMailEvent = GetGWNewMailEvent();

            if((hNewMailEvent != NULL) && (!SetEvent(hNewMailEvent)))
            {
                hr = HR_LOG(E_FAIL);
            }
        }

        ULRELEASE(lpReportEnvelope);
    }

    FREEPADRLIST(lpEnvelope_NDR_AdrList);

    if((lpEnvelopeAdrList == NULL) || (lpEnvelopeAdrList->cEntries == 0))
    {
        FREEPADRLIST(lpEnvelopeAdrList);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        if((lpMessageAdrList == NULL) || (lpMessageAdrList->cEntries == 0))
        {
            FREEPADRLIST(lpMessageAdrList);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

//------------------------------------------------------------------------------

    // Fix up recipient numbers
    hr = HrFixUpRecipientNumbers(lpEnvelopeAdrList, lpMessageAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

//------------------------------------------------------------------------------

    hrT = MAPICALL(lpEnvelope)->SetProps(
        lpEnvelope,
        cEnvelopeValues,
        lpEnvelopeProps,
        &lpProblems);

    if(FAILED(hrT))
    {
        lpProblems = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    DUMPPROPPROBLEMS(lpProblems);
    MAPIFREEBUFFER(lpProblems);

    hr = HrMAPISetPropBoolean(
        (LPMAPIPROP)lpEnvelope,
        PR_DELETE_AFTER_SUBMIT,
        TRUE);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        hrT = MAPICALL(lpMessage)->SetProps(
            lpMessage,
            cMessageValues,
            lpMessageProps,
            &lpProblems);

        if(FAILED(hrT))
        {
            lpProblems = NULL;

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        DUMPPROPPROBLEMS(lpProblems);
        MAPIFREEBUFFER(lpProblems);
    }

//------------------------------------------------------------------------------

    // Set envelope recipients
    hrT = MAPICALL(lpEnvelope)->ModifyRecipients(
        lpEnvelope,
        0,
        lpEnvelopeAdrList);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        // Set message recipients
        hrT = MAPICALL(lpMessage)->ModifyRecipients(
            lpMessage,
            0,
            lpMessageAdrList);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

//------------------------------------------------------------------------------

    if(HasContent == TRUE)
    {
        // Save changes to the message
        hrT = MAPICALL(lpMessage)->SaveChanges(
            lpMessage,
            MAPI_DEFERRED_ERRORS|KEEP_OPEN_READWRITE);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Save changes to attachment object
        hrT = MAPICALL(lpAttach)->SaveChanges(
            lpAttach,
            MAPI_DEFERRED_ERRORS|KEEP_OPEN_READWRITE);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        ULRELEASE(lpMessage);

        ULRELEASE(lpAttach);
    }

    //----------------------------------------------------------------------
    dwEndProcessingTime     = GetTickCount();

    dwTotalProcessingTime   = dwEndProcessingTime - dwStartProcessingTime;

    dwSleepProcessingTime   =
        ((dwTotalProcessingTime < dwInSleepInterval) ?
         (dwInSleepInterval - dwTotalProcessingTime) : 0);

    if(dwSleepProcessingTime > 0)
    {
        Sleep(dwSleepProcessingTime);
    }
    //----------------------------------------------------------------------

    // Submit message
    hrT = MAPICALL(lpEnvelope)->SubmitMessage(lpEnvelope, FORCE_SUBMIT);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    MAPIFREEBUFFER(lpProblems);

    FREEPADRLIST(lpEnvelopeAdrList);

    FREEPADRLIST(lpMessageAdrList);

    FREEPADRLIST(lpEnvelope_NDR_AdrList);

    FREEPADRLIST(lpMessage_NDR_AdrList);

    FREEPADRLIST(lpOriginalEnvelopeAdrList);
    FREEPADRLIST(lpOriginalMessageAdrList);

    FREEPADRLIST(lpEnvelopeAllAdrList);
    FREEPADRLIST(lpMessageAllAdrList);

    FREEPADRLIST(lpMappedEnvelopeAdrList);
    FREEPADRLIST(lpMappedMessageAdrList);

    MAPIFREEBUFFER(lpEnvelopeProps);
    MAPIFREEBUFFER(lpMessageProps);

    ULRELEASE(lpMessage);

    ULRELEASE(lpAttach);

    RETURN(hr);
}

//$--HrCheckExternalTraceInformation--------------------------------------------
// Process messages in MTS-IN.
// -----------------------------------------------------------------------------
HRESULT HrCheckExternalTraceInformation(    // RETURNS: return code
    IN LPMESSAGE lpEnvelope)                // pointer to envelope
{
    HRESULT hr           = NOERROR;
    LPTSTR  lpszMtsIdGDI = NULL;
    LPTSTR  lpszTraceGDI = NULL;

    DEBUGPUBLIC("HrCheckExternalTraceInformation()\n");

    hr = HrGetMtsIdEnterpriseGDI(
        lpEnvelope,
        PR_MTS_ID,
        &lpszMtsIdGDI);

    if((FAILED(hr)) && (hr != MAPI_E_NOT_FOUND))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrGetTraceEnterpriseGDI(
        lpEnvelope,
        PR_TRACE_INFO,
        &lpszTraceGDI);

    if((FAILED(hr)) && (hr != MAPI_E_NOT_FOUND))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if((lpszMtsIdGDI == NULL) && (lpszTraceGDI == NULL))
    {
        // consistent
    }
    else if((lpszMtsIdGDI == NULL) || (lpszTraceGDI == NULL))
    {
        // warning
        MODULE_ERROR("**** Inconsistent external trace ****");

        if((lpszTraceGDI != NULL) &&
           (lstrcmpi(lpszTraceGDI, lpszLocalGDI) == 0))
    	{
            // delete MTS-ID
            hr = HrDeleteMtsIdProps(
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
    	}
        else if((lpszMtsIdGDI != NULL) &&
                (lstrcmpi(lpszMtsIdGDI, lpszLocalGDI) == 0))
        {
            // delete trace
            hr = HrDeleteTraceProps(
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
    	}
    	else
    	{
            // delete trace
            hr = HrDeleteTraceProps(
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            // delete MTS-ID
            hr = HrDeleteMtsIdProps(
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
    	}
    }
    else
    {
        if(lstrcmpi(lpszMtsIdGDI, lpszTraceGDI) != 0)
    	{
            // warning
            MODULE_ERROR("**** Inconsistent external trace ****");

            if(lstrcmpi(lpszTraceGDI, lpszLocalGDI) == 0)
    		{
                // delete MTS-ID
                hr = HrDeleteMtsIdProps(
                    lpEnvelope);

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
    		}
            else if(lstrcmpi(lpszMtsIdGDI, lpszLocalGDI) == 0)
    		{
                // delete trace
                hr = HrDeleteTraceProps(
                    lpEnvelope);

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
    		}
    		else
    		{
                // delete trace
                hr = HrDeleteTraceProps(
                    lpEnvelope);

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }

                // delete MTS-ID
                hr = HrDeleteMtsIdProps(
                    lpEnvelope);

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
    		}
    	}
    	else
    	{
            // consistent
    	}
    }

cleanup:

    hr = NOERROR;

    MAPIFREEBUFFER(lpszMtsIdGDI);

    MAPIFREEBUFFER(lpszTraceGDI);

    RETURN(hr);
}

//$--HrNonDeliverMtsInMessage---------------------------------------------------
//  Non-deliver a message in MTS-IN.
// -----------------------------------------------------------------------------
HRESULT HrNonDeliverMtsInMessage(       // RETURNS: zero
    IN LPTSTR lpszMessageClass,         // message class
    IN LPMESSAGE lpEnvelope)            // envelope
{
    HRESULT   hr               = NOERROR;
    LPADRBOOK lpAdrBook        = NULL;
    LPMESSAGE lpMessage        = NULL;
    LPMESSAGE lpSubjectMessage = NULL;
    LPMESSAGE lpReportEnvelope = NULL;
    LPADRLIST lpReportAdrList  = NULL;
    LPATTACH  lpAttach         = NULL;
    BOOL      HasContent       = TRUE;

    DEBUGPUBLIC("HrNonDeliverMtsInMessage()\n");

    lpAdrBook   = GetAdrBookPtr();

    MODULE_ERROR1(
        "**** [IN ] Unknown message class [%s] ****",
        ((lpszMessageClass == NULL) ? "(null)" : lpszMessageClass));

    hr = HrNonDeliverAllRecipList(
        lpEnvelope,
        &lpReportAdrList);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Get the attachment in the envelope
    hr = MAPICALL(lpEnvelope)->OpenAttach(
        lpEnvelope,
        0,
        NULL,
        MAPI_MODIFY,
        &lpAttach);

    if((FAILED(hr)) && (hr != MAPI_E_NOT_FOUND))
    {
        goto cleanup;
    }

    if(hr == MAPI_E_NOT_FOUND)
    {
        //
        // Message does not have an attachment.
        //

        HasContent = FALSE;
        lpAttach   = NULL;
    }

    lpSubjectMessage = NULL;

    if(HasContent == TRUE)
    {
        // Open a message interface on the attachment
        hr = MAPICALL(lpAttach)->OpenProperty(
            lpAttach,
            PR_ATTACH_DATA_OBJ,
            (LPIID)&IID_IMessage,
            0,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            (LPUNKNOWN *)&lpMessage);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        lpSubjectMessage = lpMessage;
    }
    else
    {
        lpSubjectMessage = lpEnvelope;
    }

    //
    // Create a non delivery report in MTS-OUT
    //

    if(lpSubjectMessage != NULL)
    {
        hr = HrCreateNonDeliveryReport(
            TRUE,
            lpAdrBook,
            lpMtsOutFolder,
            lpSubjectMessage,
            lpReportAdrList,
            &lpReportEnvelope);

        if(FAILED(hr))
        {
            ;
        }
        else
        {
            HANDLE hNewMailEvent = GetGWNewMailEvent();

            if((hNewMailEvent != NULL) && (!SetEvent(hNewMailEvent)))
            {
                hr = HR_LOG(E_FAIL);
            }
        }
    }

cleanup:

    ULRELEASE(lpReportEnvelope);

    ULRELEASE(lpMessage);

    FREEPADRLIST(lpReportAdrList);

    RETURN(hr);
}

//$--ProcessMtsIn---------------------------------------------------------------
//  Process messages in MTS-IN.
// -----------------------------------------------------------------------------
DWORD ProcessMtsIn(                     // RETURNS: zero
    IN LPVOID lpParameter)              // parameter
{
    HRESULT             hr                       = NOERROR;
    HRESULT             hrT                      = NOERROR;
    ULONG               i                        = 0;
    ULONG               cRows                    = 0;

    LPMESSAGE           lpEnvelope               = NULL;

    ULONG               cbMessageClass           = 0;
    LPTSTR              lpszMessageClass         = NULL;

    LPSTREAM            lpStream                 = NULL;
    TCHAR               rgchFileName[MAX_PATH+1] = {0};

    DWORD               dwStartProcessingTime    = 0;

    LPADRBOOK           lpAdrBook                = NULL;
    LPABCONT            lpGalABCont              = NULL;
    ULONG               ulObjType                = 0;

	SPropTagArray       sptExcludeNone           = {0};
	LPSTnefProblemArray lptpa                    = NULL;

	LPWIN32_FIND_DATA   rgFindData               = NULL;
	LPWIN32_FIND_DATA   lpFindData               = NULL;

    EDKCNVRES           crRes                    = GCR_OK;

    //
    //  Declare an environment for the conversion.
    //

    EDKCNVENV envTmp =
    { 
        1,
        lpszInConverterW,
        (LHANDLE)NULL,
        NULL,
        NULL,
        NULL
    };

    CONV_OPTIONS sConvOptions = 
    {
        FALSE,              // attach TNEF encapsulation
        NULL                // address type
    };

    const LPCWSTR pszMessageClassW = L"ENVELOPE.IPM";

    PVOID           pvConvInstance              = NULL;

    LPIDITEM        lpIdItem                    = NULL;

    DEBUGPUBLIC("ProcessMtsIn()\n");

    //performance code

    // Initialize conversion engine instance data.
    hr = HrConvInitInstance(hEventLog, &pvConvInstance);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cRows       = GetGWFindDataSize(lpParameter);

    rgFindData  = GetGWFindData(lpParameter);

    lpAdrBook   = GetAdrBookPtr();

    lpGalABCont = GetGWGAL();


    for(i = 0; i < cRows; i++)
    {
        dwStartProcessingTime = GetTickCount();

//------------------------------------------------------------------------------
    	// Build file name of incoming message

        lpFindData = &rgFindData[i];

    	lstrcpy(rgchFileName, lpszInDirectory);
    	lstrcat(rgchFileName, lpFindData->cFileName);

    //------------------------------------------------------------------------------

        // Adding file to the "being processed" list!
        // Prevents another thread from processing this file.
        hr = HrAddIdItem(&InboundIdList, rgchFileName, &lpIdItem);

        if(hr == EDK_E_ALREADY_EXISTS)
        {
            //
            // Don't process this message. It is already being processed
            // by another thread.
            //

            continue;
        }

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------

        // Open a buffered stream on the input file.
    	hrT = OpenStreamOnFile(
    	    MAPIAllocateBuffer,
    	    MAPIFreeBuffer,
    		STGM_READ | STGM_SHARE_EXCLUSIVE,		// stream interface flags
    		rgchFileName,
    		NULL,
    		&lpStream);

    	if(FAILED(hrT))
    	{
            // Temporarily can't access this file.  
            // We MUST remove it from the being processed list, since
            // this thread added it, but now can't continue to process it.
  			goto SKIP;
    	}

        lpEnvelope = NULL;

        hrT = MAPICALL(lpMtsInFolder)->CreateMessage(
            lpMtsInFolder,
            NULL,
            MAPI_DEFERRED_ERRORS,
            &lpEnvelope);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

//------------------------------------------------------------------------------

        // Initialize the conversion environment structure

        sConvOptions.lpszAddressType = lpszAddressType;

        envTmp.lphSession      = (LHANDLE)lpSession;
        envTmp.lpAB            = lpAdrBook;
        envTmp.pGatewayDefined = &sConvOptions;

        //
        //  Perform the conversion.
        //

        hr = HrConvConvert(
            pvConvInstance,         // conversion instance pointer
            &envTmp,                // environment structure pointer
            pszMessageClassW,       // dummy message class
            lpStream,               // stream to read from
            lpEnvelope,             // message to convert to
            &crRes);                // result pointer

        if(FAILED(hr) || crRes != GCR_OK)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

//------------------------------------------------------------------------------

        // Get the message class

        MAPIFREEBUFFER(lpszMessageClass);

        cbMessageClass = 0;
        lpszMessageClass = NULL;

        hr = HrMAPIGetPropString(
            (LPMAPIPROP)lpEnvelope,
            PR_MESSAGE_CLASS,
            &cbMessageClass,
            (void **)&lpszMessageClass);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MODULE_WARNING1(
            "**** [IN ] Processing message of class [%s] ****",
            ((lpszMessageClass == NULL) ? "(null)" : lpszMessageClass));

        //
        // Check for inconsistencies in MTS-ID & external trace information.
        //

        hr = HrCheckExternalTraceInformation(lpEnvelope);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Process the message

        if(_tcsstr(lpszMessageClass, TEXT("ENVELOPE.IPM")) != NULL)
        {
            hr = HrMAPISetPropBoolean(
                (LPMAPIPROP)lpEnvelope,
                PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED,
                TRUE);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrMAPISetPropBoolean(
                (LPMAPIPROP)lpEnvelope,
                PR_NON_RECEIPT_NOTIFICATION_REQUESTED,
                TRUE);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrImportMessage(
                lpAdrBook,
                lpGalABCont,
                FALSE,
                TRUE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".NDR")) != NULL))
        {
            hr = HrMAPISetPropBoolean(
                (LPMAPIPROP)lpEnvelope,
                PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED,
                TRUE);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrDeleteSenderProps(
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrImportMessage(
                lpAdrBook,
                lpGalABCont,
                TRUE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".DR")) != NULL))
        {
            hr = HrMAPISetPropBoolean(
                (LPMAPIPROP)lpEnvelope,
                PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED,
                TRUE);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrDeleteSenderProps(
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrImportMessage(
                lpAdrBook,
                lpGalABCont,
                TRUE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".IPNNRN")) != NULL))
        {
            hr = HrMAPISetPropBoolean(
                (LPMAPIPROP)lpEnvelope,
                PR_NON_RECEIPT_NOTIFICATION_REQUESTED,
                TRUE);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrImportMessage(
                lpAdrBook,
                lpGalABCont,
                FALSE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".IPNRN")) != NULL))
        {
            hr = HrMAPISetPropBoolean(
                (LPMAPIPROP)lpEnvelope,
                PR_READ_RECEIPT_REQUESTED,
                TRUE);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrImportMessage(
                lpAdrBook,
                lpGalABCont,
                FALSE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else
        {
            hr = HrNonDeliverMtsInMessage(
                lpszMessageClass,
                lpEnvelope);

            if(FAILED(hr))
            {
                ; // failed to non-deliver message
            }
        }

        if(FAILED(hr))
        {
            MODULE_ERROR1(
                "**** [IN ] Error while processing message of class [%s] ****",
                ((lpszMessageClass == NULL) ? "(null)" : lpszMessageClass));

            //
            // This message will be moved to the archive directory.
            //

            ULRELEASE(lpStream);
            MAPIFREEBUFFER(lpszMessageClass);
            ULRELEASE(lpEnvelope);
            continue;
        }

        ULRELEASE(lpStream);

        MAPIFREEBUFFER(lpszMessageClass);

        ULRELEASE(lpEnvelope);

        //performance code

        if(!DeleteFile(rgchFileName))
        {
            hr = HR_LOG(E_FAIL);
        }

    //------------------------------------------------------------------------------

SKIP:   // can't process this file now, so remove it from the "being processed" list.

        hr = HrRemoveIdItem(&InboundIdList, lpIdItem);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------
    }

cleanup:

    ULRELEASE(lpStream);

    MAPIFREEBUFFER(lpszMessageClass);

    ULRELEASE(lpEnvelope);

    if(pvConvInstance != NULL)
    {
        // De-initialize conversion engine instance data.
        (VOID)HrConvUninitInstance(pvConvInstance);
        pvConvInstance = NULL;
    }

    return(0);
}

//$--HrExportMessage------------------------------------------------------------
// Process an IPM/IPN in MTS-OUT.
// -----------------------------------------------------------------------------
HRESULT HrExportMessage(                // RETURNS: return code
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN BOOL fIgnoreRespValue,           // ignore  responsibility value
    IN BOOL fSendNDR,                   // TRUE if NDRs should be generated
    IN DWORD dwStartProcessingTime,     // start processing time
    IN OUT LPMESSAGE lpEnvelope)        // pointer to envelope
{
    HRESULT             hr                        = NOERROR;
    HRESULT             hrT                       = NOERROR;

    LPMESSAGE           lpMessage                 = NULL;
    LPATTACH            lpAttach                  = NULL;

    ULONG               cEnvelopeValues           = 0;
    LPSPropValue        lpEnvelopeProps           = NULL;
    ULONG               cMessageValues            = 0;
    LPSPropValue        lpMessageProps            = NULL;

    LPADRLIST           lpOriginalEnvelopeAdrList = NULL;
    LPADRLIST           lpOriginalMessageAdrList  = NULL;

    LPADRLIST           lpEnvelopeAdrList         = NULL;
    LPADRLIST           lpMessageAdrList          = NULL;

    LPADRLIST           lpEnvelope_NDR_AdrList    = NULL;
    LPADRLIST           lpMessage_NDR_AdrList     = NULL;

    DWORD               dwEndProcessingTime       = 0;
    DWORD               dwTotalProcessingTime     = 0;
    DWORD               dwSleepProcessingTime     = 0;

    ULONG               cbeid                     = 0;
    LPENTRYID           lpeid                     = NULL;

    ULONG               cEnvelopeMesgAddr         = 0;
    ULONG               cEnvelopeReplyAddr        = 0;
    ULONG               cEnvelopeRecipAddr        = 0;
    LPADRLIST           lpEnvelopeAllAdrList      = NULL;
    LPADRLIST           lpMappedEnvelopeAdrList   = NULL;

    ULONG               cMessageMesgAddr          = 0;
    ULONG               cMessageReplyAddr         = 0;
    ULONG               cMessageRecipAddr         = 0;
    LPADRLIST           lpMessageAllAdrList       = NULL;
    LPADRLIST           lpMappedMessageAdrList    = NULL;

    BOOL                HasContent                = TRUE;

    LPSPropProblemArray lpProblems                = NULL;

    DEBUGPUBLIC("HrExportMessage()\n");

    // Get the attachment in the envelope
    hrT = MAPICALL(lpEnvelope)->OpenAttach(
        lpEnvelope,
        0,
        NULL,
        MAPI_MODIFY,
        &lpAttach);

    if((FAILED(hrT)) && (hrT != MAPI_E_NOT_FOUND))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(hrT == MAPI_E_NOT_FOUND)
    {
        //
        // Message does not have an attachment.
        //

        HasContent = FALSE;
        lpAttach   = NULL;
    }

    if(HasContent == TRUE)
    {
        // Open a message interface on the attachment
        hrT = MAPICALL(lpAttach)->OpenProperty(
            lpAttach,
            PR_ATTACH_DATA_OBJ,
            (LPIID)&IID_IMessage,
            0,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            (LPUNKNOWN *)&lpMessage);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

//------------------------------------------------------------------------------

    //
    // Map envelope addresses
    //

    hr = HrExpandMessageAddressList(
        lpEnvelope,
        &cEnvelopeMesgAddr,
        &cEnvelopeReplyAddr,
        &cEnvelopeRecipAddr,
        &lpOriginalEnvelopeAdrList,
        &lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMapAddrToProxy(
        lpAdrBook,
        lpszAddressType,
        lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrMapGatewayAddrToProxy(
        lpAdrBook,
        lpszAddressType,
        lpEnvelopeAllAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrCollapseMessageAddressList(
        lpEnvelope,
        cEnvelopeMesgAddr,
        cEnvelopeReplyAddr,
        cEnvelopeRecipAddr,
        lpEnvelopeAllAdrList,
        &cEnvelopeValues,
        &lpEnvelopeProps,
        &lpMappedEnvelopeAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    FREEPADRLIST(lpEnvelopeAllAdrList);

    if(HasContent == TRUE)
    {
        //
        // Map message addresses
        //

        hr = HrExpandMessageAddressList(
            lpMessage,
            &cMessageMesgAddr,
            &cMessageReplyAddr,
            &cMessageRecipAddr,
            &lpOriginalMessageAdrList,
            &lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMapAddrToProxy(
            lpAdrBook,
            lpszAddressType,
            lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMapGatewayAddrToProxy(
            lpAdrBook,
            lpszAddressType,
            lpMessageAllAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrCollapseMessageAddressList(
            lpMessage,
            cMessageMesgAddr,
            cMessageReplyAddr,
            cMessageRecipAddr,
            lpMessageAllAdrList,
            &cMessageValues,
            &lpMessageProps,
            &lpMappedMessageAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        FREEPADRLIST(lpMessageAllAdrList);
    }

//------------------------------------------------------------------------------

    hr = HrMapRecipAddrToProxy(
        lpAdrBook,
        TRUE,
        fIgnoreRespValue,
        lpszAddressType,
        NULL,
        lpOriginalEnvelopeAdrList,
        lpMappedEnvelopeAdrList,
        NULL,
        NULL,
        lpEnvelope,
        &lpEnvelopeAdrList,
        &lpEnvelope_NDR_AdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        hr = HrMapRecipAddrToProxy(
            lpAdrBook,
            FALSE,
            fIgnoreRespValue,
            lpszAddressType,
            lpOriginalEnvelopeAdrList,
            lpOriginalMessageAdrList,
            lpMappedMessageAdrList,
            lpEnvelopeAdrList,
            lpEnvelope_NDR_AdrList,
            lpMessage,
            &lpMessageAdrList,
            &lpMessage_NDR_AdrList);

        FREEPADRLIST(lpOriginalEnvelopeAdrList);

        FREEPADRLIST(lpOriginalMessageAdrList);

        FREEPADRLIST(lpMessage_NDR_AdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    // Non-deliver any recipients that could not be mapped.

    if((lpEnvelope_NDR_AdrList != NULL) &&
       (lpEnvelope_NDR_AdrList->cEntries != 0) &&
       (fSendNDR == TRUE))
    {
        LPMESSAGE lpReportEnvelope = NULL;

        //
        // Clear row IDs for envelope NDR address list.
        //

        hr = HrDeleteAddressListProperty(
            PR_ROWID,
            (LPADRLIST)lpEnvelope_NDR_AdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        //
        // Create a non delivery report in MTS-IN
        //

        hr = HrCreateNonDeliveryReport(
            FALSE,
            lpAdrBook,
            lpMtsInFolder,
            lpMessage,
            lpEnvelope_NDR_AdrList,
            &lpReportEnvelope);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        hr = HrMAPISetPropBoolean(
            (LPMAPIPROP)lpReportEnvelope,
            PR_DELETE_AFTER_SUBMIT,
            TRUE);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);

            ULRELEASE(lpReportEnvelope);

            goto cleanup;
        }

        // Submit message
        hrT = MAPICALL(lpReportEnvelope)->SubmitMessage(lpReportEnvelope, FORCE_SUBMIT);

        if(FAILED(hrT))
        {
            hrT = HR_LOG(hrT);
        }

        ULRELEASE(lpReportEnvelope);
    }

    FREEPADRLIST(lpEnvelope_NDR_AdrList);

    if((lpEnvelopeAdrList == NULL) || (lpEnvelopeAdrList->cEntries == 0))
    {
        FREEPADRLIST(lpEnvelopeAdrList);

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        if((lpMessageAdrList == NULL) || (lpMessageAdrList->cEntries == 0))
        {
            FREEPADRLIST(lpMessageAdrList);

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

//------------------------------------------------------------------------------

    // Fix up recipient numbers
    hr = HrFixUpRecipientNumbers(lpEnvelopeAdrList, lpMessageAdrList);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

//------------------------------------------------------------------------------

    hrT = MAPICALL(lpEnvelope)->SetProps(
        lpEnvelope,
        cEnvelopeValues,
        lpEnvelopeProps,
        &lpProblems);

    if(FAILED(hrT))
    {
        lpProblems = NULL;

        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    DUMPPROPPROBLEMS(lpProblems);
    MAPIFREEBUFFER(lpProblems);

    if(HasContent == TRUE)
    {
        hrT = MAPICALL(lpMessage)->SetProps(
            lpMessage,
            cMessageValues,
            lpMessageProps,
            &lpProblems);

        if(FAILED(hrT))
        {
            lpProblems = NULL;

            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        DUMPPROPPROBLEMS(lpProblems);
        MAPIFREEBUFFER(lpProblems);
    }

//------------------------------------------------------------------------------

    // Set envelope recipients
    hrT = MAPICALL(lpEnvelope)->ModifyRecipients(
        lpEnvelope,
        0,
        lpEnvelopeAdrList);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(HasContent == TRUE)
    {
        // Set message recipients
        hrT = MAPICALL(lpMessage)->ModifyRecipients(
            lpMessage,
            0,
            lpMessageAdrList);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

//------------------------------------------------------------------------------

    if(HasContent == TRUE)
    {
        // Save changes to the message
        hrT = MAPICALL(lpMessage)->SaveChanges(
            lpMessage,
            MAPI_DEFERRED_ERRORS|FORCE_SAVE);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Save changes to attachment object
        hrT = MAPICALL(lpAttach)->SaveChanges(
            lpAttach,
            MAPI_DEFERRED_ERRORS|FORCE_SAVE);

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        ULRELEASE(lpMessage);

        ULRELEASE(lpAttach);
    }

    // Save changes to the envelope
    hrT = MAPICALL(lpEnvelope)->SaveChanges(
        lpEnvelope,
        MAPI_DEFERRED_ERRORS|KEEP_OPEN_READWRITE);

    if(FAILED(hrT))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //----------------------------------------------------------------------
    dwEndProcessingTime     = GetTickCount();

    dwTotalProcessingTime   = dwEndProcessingTime - dwStartProcessingTime;

    dwSleepProcessingTime   =
        ((dwTotalProcessingTime < dwOutSleepInterval) ?
         (dwOutSleepInterval - dwTotalProcessingTime) : 0);

    if(dwSleepProcessingTime > 0)
    {
        Sleep(dwSleepProcessingTime);
    }
    //----------------------------------------------------------------------

cleanup:

    MAPIFREEBUFFER(lpProblems);

    MAPIFREEBUFFER(lpeid);

    FREEPADRLIST(lpOriginalEnvelopeAdrList);

    FREEPADRLIST(lpOriginalMessageAdrList);

    FREEPADRLIST(lpEnvelopeAdrList);

    FREEPADRLIST(lpMessageAdrList);

    FREEPADRLIST(lpEnvelope_NDR_AdrList);

    FREEPADRLIST(lpMessage_NDR_AdrList);

    FREEPADRLIST(lpEnvelopeAllAdrList);

    FREEPADRLIST(lpMessageAllAdrList);

    FREEPADRLIST(lpMappedEnvelopeAdrList);
    FREEPADRLIST(lpMappedMessageAdrList);

    MAPIFREEBUFFER(lpEnvelopeProps);
    MAPIFREEBUFFER(lpMessageProps);

    ULRELEASE(lpMessage);

    ULRELEASE(lpAttach);

    RETURN(hr);
}

//$--HrConvertMtsOut------------------------------------------------------------
//  Convert a message in MTS-OUT.
// -----------------------------------------------------------------------------
HRESULT HrConvertMtsOut(                // RETURNS: return code
    IN PVOID     pvConvInstance,        // converter instance
    IN LPADRBOOK lpAdrBook,             // pointer to address book
    IN LPTSTR    lpszMessageClass,      // message class
    IN LPMESSAGE lpMessage)             // message
{
    HRESULT      hr                          = NOERROR;
    HRESULT      hrT                         = NOERROR;
    LPSRowSet    lpRows                      = NULL;
    LPADRLIST    lpAdrList                   = NULL;
    LPMAPITABLE  lpTable                     = NULL;
    BOOL         fFileCreated                = FALSE;   // TRUE if output file created

    ULONG        cValues                     = 0;
    LPSPropValue lpProps                     = NULL;
    LPSPropValue lpPropT                     = NULL;

    BOOL         IsMapiRecip                 = 0;
    LPTSTR       lpszAddress                 = NULL;

    LPADRLIST    lpMapiAdrList               = NULL;
    LPADRLIST    lpNonMapiAdrList            = NULL;

    ULONG        i                           = 0;

    LPSTREAM     lpStream                    = NULL;
    TCHAR        rgchOutFileName[MAX_PATH+1] = {0};

    EDKCNVRES    crRes                       = GCR_OK;

    //
    //  Declare an environment for the conversion.
    //

    EDKCNVENV envTmp =
    { 
        1,
        lpszOutConverterW,
        (LHANDLE)NULL,
        NULL,
        NULL,
        NULL
    };

    CONV_OPTIONS sConvOptions = 
    {
        FALSE,              // attach TNEF encapsulation
        NULL                // address type
    };

    ULONG  cbMessageClass                    = 0;
    LPWSTR lpszMessageClassW                 = NULL;

    ULONG  iMapi                             = 0;
    ULONG  iNonMapi                          = 0;

    SizedSPropTagArray(1, rgPropTags) =
    {
        1,
        {
            PR_REPORT_DESTINATION_ENTRYID,
        }
    };

	// stream interface flags
	const ULONG	ulFlags	=	STGM_CREATE | STGM_READWRITE | 
						  	SOF_UNIQUEFILENAME | STGM_SHARE_EXCLUSIVE;

    DEBUGPUBLIC("HrConvertMtsOut()\n");

    if(_tcsstr(lpszMessageClass, TEXT("ENVELOPE.IPM")) != NULL)
    {
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
        // Divide recipient list into MAPI and non-MAPI recipients
        //

        lpAdrList = (LPADRLIST)lpRows;

        hr = HrMAPICreateSizedAddressList(
            lpAdrList->cEntries,
            &lpMapiAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        hr = HrMAPICreateSizedAddressList(
            lpAdrList->cEntries,
            &lpNonMapiAdrList);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        for(i = 0; i < lpAdrList->cEntries; i++)
        {
            cValues = lpAdrList->aEntries[i].cValues;
            lpProps = lpAdrList->aEntries[i].rgPropVals;

            lpPropT = LpValFindProp(PR_SEND_RICH_INFO, cValues, lpProps);

            if(lpPropT != NULL)
            {
                IsMapiRecip = lpPropT->Value.b;
            }
            else
            {
                IsMapiRecip = FALSE;
            }

            if(IsMapiRecip == TRUE)
            {
                hr = HrMAPISetAddressList(
                    iMapi,
                    cValues,
                    lpProps,
                    lpMapiAdrList);

                iMapi++;

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
            }
            else
            {
                hr = HrMAPISetAddressList(
                    iNonMapi,
                    cValues,
                    lpProps,
                    lpNonMapiAdrList);

                iNonMapi++;

                if(FAILED(hr))
                {
                    hr = HR_LOG(E_FAIL);
                    goto cleanup;
                }
            }
        }   // end for
        
        //
        // Convert message for MAPI recipients
        //

        if(iMapi > 0)
        {
            // Set envelope recipients
            hrT = MAPICALL(lpMessage)->ModifyRecipients(
                lpMessage,
                0,
                lpMapiAdrList);

            if(FAILED(hrT))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hrT = MAPICALL(lpMessage)->SaveChanges(
                lpMessage,
                KEEP_OPEN_READWRITE);

            if(FAILED(hrT))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

    //------------------------------------------------------------------------------

        	lstrcpy(rgchOutFileName, lpszOutDirectory);

            // Open a buffered stream on our SGW*.TMP output file.
        	hrT = OpenStreamOnFile(
        	    MAPIAllocateBuffer,
        	    MAPIFreeBuffer,
        		ulFlags,				// stream interface flags
        		rgchOutFileName,
        		szFilePrefix,
        		&lpStream);

        	if(FAILED(hrT))
        	{
                hr = HR_LOG(E_FAIL);
                goto cleanup;
        	}

            fFileCreated = TRUE;    // output file has been created

        //------------------------------------------------------------------------------

            // Get the message class

            MAPIFREEBUFFER(lpszMessageClassW);

            cbMessageClass = 0;
            lpszMessageClassW = NULL;

            hr = HrMAPIGetPropString(
                (LPMAPIPROP)lpMessage,
                PR_MESSAGE_CLASS_W,
                &cbMessageClass,
                (void **)&lpszMessageClassW);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            // Initialize the conversion environment structure

            sConvOptions.fTnefEncode     = TRUE;
            sConvOptions.lpszAddressType = lpszAddressType;

            envTmp.lphSession      = (LHANDLE)lpSession;
            envTmp.lpAB            = lpAdrBook;
            envTmp.pGatewayDefined = &sConvOptions;

            //
            //  Perform the conversion.
            //

            hr = HrConvConvert(
                pvConvInstance,         // conversion instance pointer
                &envTmp,                // environment structure pointer
                lpszMessageClassW,      // message class
                lpMessage,              // message to convert from
                lpStream,               // stream to read to
                &crRes);                // result pointer

            if(FAILED(hr) || crRes != GCR_OK)
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

        //------------------------------------------------------------------------------

            ULRELEASE(lpStream);

            //
            // Finished processing message
            //

            {
                BOOL fT = FALSE;

                fT = SetFileAttributes(rgchOutFileName, FILE_ATTRIBUTE_NORMAL);

                if(fT == FALSE)
                {
                    hrT = HR_LOG(E_FAIL);
                }
            }
        }   // end if MAPI recipients

        //
        // Convert message for non-MAPI recipients
        //

        if(iNonMapi > 0)
        {
            // Set envelope recipients
            hrT = MAPICALL(lpMessage)->ModifyRecipients(
                lpMessage,
                0,
                lpNonMapiAdrList);

            if(FAILED(hrT))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hrT = MAPICALL(lpMessage)->SaveChanges(
                lpMessage,
                KEEP_OPEN_READWRITE);

            if(FAILED(hrT))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

    //------------------------------------------------------------------------------

        	lstrcpy(rgchOutFileName, lpszOutDirectory);

        	hrT = OpenStreamOnFile(
        	    MAPIAllocateBuffer,
        	    MAPIFreeBuffer,
        		STGM_CREATE | STGM_READWRITE | SOF_UNIQUEFILENAME,
        		rgchOutFileName,
        		szFilePrefix,
        		&lpStream);

        	if(FAILED(hrT))
        	{
                hr = HR_LOG(E_FAIL);
                goto cleanup;
        	}

            fFileCreated = TRUE;    // output file has been created

        //------------------------------------------------------------------------------

            // Get the message class

            MAPIFREEBUFFER(lpszMessageClassW);

            cbMessageClass = 0;
            lpszMessageClassW = NULL;

            hr = HrMAPIGetPropString(
                (LPMAPIPROP)lpMessage,
                PR_MESSAGE_CLASS_W,
                &cbMessageClass,
                (void **)&lpszMessageClassW);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            // Initialize the conversion environment structure

            sConvOptions.fTnefEncode     = FALSE;
            sConvOptions.lpszAddressType = lpszAddressType;

            envTmp.lphSession      = (LHANDLE)lpSession;
            envTmp.lpAB            = lpAdrBook;
            envTmp.pGatewayDefined = &sConvOptions;

            //
            //  Perform the conversion.
            //

            hr = HrConvConvert(
                pvConvInstance,         // conversion instance pointer
                &envTmp,                // environment structure pointer
                lpszMessageClassW,      // message class
                lpMessage,              // message to convert from
                lpStream,               // stream to read to
                &crRes);                // result pointer

            if(FAILED(hr) || crRes != GCR_OK)
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

        //------------------------------------------------------------------------------

            ULRELEASE(lpStream);

            //
            // Finished processing message
            //

            {
                BOOL fT = FALSE;

                fT = SetFileAttributes(rgchOutFileName, FILE_ATTRIBUTE_NORMAL);

                if(fT == FALSE)
                {
                    hrT = HR_LOG(E_FAIL);
                }
            }
        }   // end if non-MAPI recipients
    }   // end if Interpersonal message

    else if(_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL)
    {
        //
        // Determine if the report/notification recipient is a MAPI
        // or a non-MAPI recipient.
        //

        if((_tcsstr(lpszMessageClass, TEXT(".NDR")) != NULL) ||
           (_tcsstr(lpszMessageClass, TEXT(".DR")) != NULL))
        {
            //
            // Get destination of non-delivery/delivery report.
            //

            hr = MAPICALL(lpMessage)->GetProps(
                lpMessage,
                (SPropTagArray *)&rgPropTags,
                fMapiUnicode,
                &cValues,
                &lpProps);

            if(FAILED(hr))
            {
                lpProps = NULL;

                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }

            hr = HrGWResolveProxy(
                lpAdrBook,
                lpProps->Value.bin.cb,
                (LPENTRYID)lpProps->Value.bin.lpb,
                lpszAddressType,
                &IsMapiRecip,
                &lpszAddress);

            MAPIFREEBUFFER(lpProps);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }
        else if((_tcsstr(lpszMessageClass, TEXT(".IPNNRN")) != NULL) ||
                (_tcsstr(lpszMessageClass, TEXT(".IPNRN")) != NULL))
        {
            //
            // Get the recipient table for the non-read/read notification.
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

            lpAdrList = (LPADRLIST)lpRows;
            cValues   = lpAdrList->aEntries[i].cValues;
            lpProps   = lpAdrList->aEntries[i].rgPropVals;

            lpPropT = LpValFindProp(PR_SEND_RICH_INFO, cValues, lpProps);

            if(lpPropT != NULL)
            {
                IsMapiRecip = lpPropT->Value.b;
            }
            else
            {
                IsMapiRecip = FALSE;
            }

            FREEPADRLIST(lpAdrList);
        }
        else
        {
            IsMapiRecip = FALSE;
        }

    //------------------------------------------------------------------------------

    	lstrcpy(rgchOutFileName, lpszOutDirectory);

    	hrT = OpenStreamOnFile(
    	    MAPIAllocateBuffer,
    	    MAPIFreeBuffer,
    		STGM_CREATE | STGM_READWRITE | SOF_UNIQUEFILENAME,
    		rgchOutFileName,
    		szFilePrefix,
    		&lpStream);

    	if(FAILED(hrT))
    	{
            hr = HR_LOG(E_FAIL);
            goto cleanup;
    	}

        fFileCreated = TRUE;    // output file has been created

    //------------------------------------------------------------------------------

        // Get the message class

        MAPIFREEBUFFER(lpszMessageClassW);

        cbMessageClass = 0;
        lpszMessageClassW = NULL;

        hr = HrMAPIGetPropString(
            (LPMAPIPROP)lpMessage,
            PR_MESSAGE_CLASS_W,
            &cbMessageClass,
            (void **)&lpszMessageClassW);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        // Initialize the conversion environment structure

        sConvOptions.fTnefEncode     = IsMapiRecip;
        sConvOptions.lpszAddressType = lpszAddressType;

        envTmp.lphSession            = (LHANDLE)lpSession;
        envTmp.lpAB                  = lpAdrBook;
        envTmp.pGatewayDefined       = &sConvOptions;

        //
        //  Perform the conversion.
        //

        hr = HrConvConvert(
            pvConvInstance,         // conversion instance pointer
            &envTmp,                // environment structure pointer
            lpszMessageClassW,      // message class
            lpMessage,              // message to convert from
            lpStream,               // stream to read to
            &crRes);                // result pointer

        if(FAILED(hr) || crRes != GCR_OK)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------

        ULRELEASE(lpStream);

        //
        // Finished processing message
        //

        {
            BOOL fT = FALSE;

            fT = SetFileAttributes(rgchOutFileName, FILE_ATTRIBUTE_NORMAL);

            if(fT == FALSE)
            {
                hrT = HR_LOG(E_FAIL);
            }
        }
    }   // end if report

    else
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:

    if ( FAILED(hr) )
    {
        // delete the output file created, if any.
        if ( fFileCreated == TRUE )
        {
            // Must release the stream first!
            ULRELEASE(lpStream);

            (VOID)DeleteFile(rgchOutFileName);
        }
    }

    MAPIFREEBUFFER(lpszAddress);
    MAPIFREEBUFFER(lpszMessageClassW);

    FREEPADRLIST(lpAdrList);        // also frees lpRows

    FREEPADRLIST(lpMapiAdrList);

    FREEPADRLIST(lpNonMapiAdrList);

    ULRELEASE(lpStream);

    ULRELEASE(lpTable);

    RETURN(hr);
}

//$--HrNonDeliverMtsOutMessage--------------------------------------------------
//  Non-deliver a message in MTS-OUT.
// -----------------------------------------------------------------------------
HRESULT HrNonDeliverMtsOutMessage(      // RETURNS: zero
    IN LPTSTR lpszMessageClass,         // message class
    IN LPMESSAGE lpEnvelope)            // envelope
{
    HRESULT   hr               = NOERROR;
    LPADRBOOK lpAdrBook        = NULL;
    LPMESSAGE lpMessage        = NULL;
    LPMESSAGE lpSubjectMessage = NULL;
    LPMESSAGE lpReportEnvelope = NULL;
    LPADRLIST lpReportAdrList  = NULL;
    LPATTACH  lpAttach         = NULL;
    BOOL      HasContent       = TRUE;

    DEBUGPUBLIC("HrNonDeliverMtsOutMessage()\n");

    lpAdrBook   = GetAdrBookPtr();

    MODULE_ERROR1(
        "**** [IN ] Unknown message class [%s] ****",
        ((lpszMessageClass == NULL) ? "(null)" : lpszMessageClass));

    hr = HrNonDeliverAllRecipList(
        lpEnvelope,
        &lpReportAdrList);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    // Get the attachment in the envelope
    hr = MAPICALL(lpEnvelope)->OpenAttach(
        lpEnvelope,
        0,
        NULL,
        MAPI_MODIFY,
        &lpAttach);

    if((FAILED(hr)) && (hr != MAPI_E_NOT_FOUND))
    {
        goto cleanup;
    }

    if(hr == MAPI_E_NOT_FOUND)
    {
        //
        // Message does not have an attachment.
        //

        HasContent = FALSE;
        lpAttach   = NULL;
    }

    lpSubjectMessage = NULL;

    if(HasContent == TRUE)
    {
        // Open a message interface on the attachment
        hr = MAPICALL(lpAttach)->OpenProperty(
            lpAttach,
            PR_ATTACH_DATA_OBJ,
            (LPIID)&IID_IMessage,
            0,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            (LPUNKNOWN *)&lpMessage);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        lpSubjectMessage = lpMessage;
    }
    else
    {
        lpSubjectMessage = lpEnvelope;
    }

    //
    // Create a non delivery report in MTS-IN
    //

    if(lpSubjectMessage != NULL)
    {
        hr = HrCreateNonDeliveryReport(
            FALSE,
            lpAdrBook,
            lpMtsInFolder,
            lpSubjectMessage,
            lpReportAdrList,
            &lpReportEnvelope);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        hr = HrMAPISetPropBoolean(
            (LPMAPIPROP)lpReportEnvelope,
            PR_DELETE_AFTER_SUBMIT,
            TRUE);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        // Submit message
        hr = MAPICALL(lpReportEnvelope)->SubmitMessage(lpReportEnvelope, FORCE_SUBMIT);

        if(FAILED(hr))
        {
            ;
        }
    }

cleanup:

    ULRELEASE(lpReportEnvelope);

    ULRELEASE(lpMessage);

    FREEPADRLIST(lpReportAdrList);

    RETURN(hr);
}

//$--ProcessMtsOut--------------------------------------------------------------
//  Process messages in MTS-OUT.
// -----------------------------------------------------------------------------
DWORD ProcessMtsOut(                    // RETURNS: zero
    IN LPVOID lpParameter)              // parameter
{
    HRESULT         hr                          = NOERROR;
    HRESULT         hrT                         = NOERROR;
    SCODE           sc                          = 0;
    ULONG           cbeid                       = 0;
    LPENTRYID       lpeid                       = NULL;
    ULONG           ulObjType                   = 0;
    ULONG           ulPropTag                   = 0;
    ULONG           cValues                     = 0;
    ULONG           i                           = 0;
    ULONG           j                           = 0;
    ULONG           cRows                       = 0;

    LPMESSAGE       lpEnvelope                  = NULL;

    ULONG           cbMessageClass              = 0;
    LPTSTR          lpszMessageClass            = NULL;

    LPSPropValue    lpProps                     = NULL;

	LPSPropTagArray lpPropTagArray              = NULL;

    ULONG           cValuesT                    = 0;
    LPSPropValue    lpPropsT                    = NULL;

    DWORD           dwStartProcessingTime       = 0;

    LPADRBOOK       lpAdrBook                   = NULL;

    ULONG           cbMsgEid                    = 0;
    LPENTRYID       lpMsgEid                    = NULL;

    SizedSPropTagArray(1, rgRecipPropTag) =
    {
        1,
        {
            PR_MESSAGE_RECIPIENTS
        }
    };

    SizedSPropTagArray(1, rgRecordKeyPropTag) =
    {
        1,
        {
            PR_RECORD_KEY
        }
    };

    ULONG           cBytes                      = 0;
    LPTSTR          lpszRecordKey               = 0;

    PVOID           pvConvInstance              = NULL;

    LPIDITEM        lpIdItem                    = NULL;

    DEBUGPUBLIC("ProcessMtsOut()\n");

    //performance code

    // Initialize conversion engine instance data.
    hr = HrConvInitInstance(hEventLog, &pvConvInstance);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    cRows       = GetGWSRowSet(lpParameter)->cRows;

    lpAdrBook   = GetAdrBookPtr();


    for(i = 0; i < cRows; i++)
    {
        dwStartProcessingTime = GetTickCount();

        cValues = GetGWSRowSet(lpParameter)->aRow[i].cValues;

        lpProps = GetGWSRowSet(lpParameter)->aRow[i].lpProps;

        cbeid = lpProps[0].Value.bin.cb;
        lpeid = (LPENTRYID)lpProps[0].Value.bin.lpb;

        cbMsgEid = cbeid;
        lpMsgEid = lpeid;

        cValues = 0;
        lpProps = NULL;

        // Get the message in the MTS-OUT folder
        hrT = MAPICALL(lpMtsOutFolder)->OpenEntry(
            lpMtsOutFolder,
            cbeid,
            lpeid,
            NULL,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            &ulObjType,
            (LPUNKNOWN FAR *)&lpEnvelope);

        cbeid = 0;
        lpeid = NULL;

        if(FAILED(hrT))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if(ulObjType != MAPI_MESSAGE)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------
        // Get the message ID

        MAPIFREEBUFFER(lpPropsT);
        MAPIFREEBUFFER(lpszRecordKey);

        cValuesT = 0;
        lpPropsT = NULL;

        hr = MAPICALL(lpEnvelope)->GetProps(
            lpEnvelope,
            (LPSPropTagArray)&rgRecordKeyPropTag,
    		fMapiUnicode,
    		&cValuesT,
    		&lpPropsT);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        if(lpPropsT[0].ulPropTag != PR_RECORD_KEY)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if(lpPropsT[0].Value.bin.cb == 0)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if(lpPropsT[0].Value.bin.lpb == NULL)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        cBytes = (lpPropsT[0].Value.bin.cb + sizeof(TCHAR)) * (2 * sizeof(TCHAR));

        hr = MAPIAllocateBuffer(cBytes, (void **)&lpszRecordKey);

        if(FAILED(hr))
        {                                                   
            goto cleanup;                                
        }                                                   

        HexFromBin(lpPropsT[0].Value.bin.lpb, lpPropsT[0].Value.bin.cb, lpszRecordKey);

        MAPIFREEBUFFER(lpPropsT);

        hr = HrAddIdItem(
            &OutboundIdList,
            lpszRecordKey,
            &lpIdItem);

        if(hr == EDK_E_ALREADY_EXISTS)
        {
            //
            // Skip this message. It is already being processed
            // by another thread.
            //

            MAPIFREEBUFFER(lpPropsT);
            MAPIFREEBUFFER(lpszRecordKey);
            ULRELEASE(lpEnvelope);
            continue;
        }

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------
        // Get the message class

        MAPIFREEBUFFER(lpszMessageClass);

        cbMessageClass = 0;
        lpszMessageClass = NULL;

        hr = HrMAPIGetPropString(
            (LPMAPIPROP)lpEnvelope,
            PR_MESSAGE_CLASS,
            &cbMessageClass,
            (void **)&lpszMessageClass);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        MODULE_WARNING1(
            "**** [OUT] Processing message of class [%s] ****",
            ((lpszMessageClass == NULL) ? "(null)" : lpszMessageClass));

        if(_tcsstr(lpszMessageClass, TEXT("ENVELOPE.IPM")) != NULL)
        {
            hr = HrExportMessage(
                lpAdrBook,
                FALSE,
                TRUE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".NDR")) != NULL))
        {
            hr = HrExportMessage(
                lpAdrBook,
                TRUE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".DR")) != NULL))
        {
            hr = HrExportMessage(
                lpAdrBook,
                TRUE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".IPNNRN")) != NULL))
        {
            hr = HrExportMessage(
                lpAdrBook,
                FALSE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else if((_tcsstr(lpszMessageClass, TEXT("REPORT.IPM")) != NULL) &&
                (_tcsstr(lpszMessageClass, TEXT(".IPNRN")) != NULL))
        {
            hr = HrExportMessage(
                lpAdrBook,
                FALSE,
                FALSE,
                dwStartProcessingTime,
                lpEnvelope);
        }
        else
        {
            hr = HrNonDeliverMtsOutMessage(
                lpszMessageClass,
                lpEnvelope);

            if(FAILED(hr))
            {
                ; // failed to non-deliver message
            }
        }

        if(FAILED(hr))
        {
            MODULE_ERROR1(
                "**** [OUT] Error while processing message of class [%s] ****",
                ((lpszMessageClass == NULL) ? "(null)" : lpszMessageClass));

            //
            // This message will be moved to the archive folder.
            //

            MAPIFREEBUFFER(lpszMessageClass);
            MAPIFREEBUFFER(lpPropsT);
            MAPIFREEBUFFER(lpszRecordKey);
            ULRELEASE(lpEnvelope);
            continue;
        }

    //------------------------------------------------------------------------------
        else
        {
            hr = HrConvertMtsOut(
                pvConvInstance,
                lpAdrBook,
                lpszMessageClass,
                lpEnvelope);

            if(FAILED(hr))
            {
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }
    //------------------------------------------------------------------------------

        ULRELEASE(lpEnvelope);

        //performance code

        hr = HrMAPIDeleteMessage(
            lpMtsOutFolder,
            cbMsgEid,
            lpMsgEid);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------

        hr = HrRemoveIdItem(&OutboundIdList, lpIdItem);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------

    }

cleanup:

    MAPIFREEBUFFER(lpPropsT);

    MAPIFREEBUFFER(lpszRecordKey);

    MAPIFREEBUFFER(lpszMessageClass);

    ULRELEASE(lpEnvelope);

    if(pvConvInstance != NULL)
    {
        // De-initialize conversion engine instance data.
        (VOID)HrConvUninitInstance(pvConvInstance);
        pvConvInstance = NULL;
    }

    return(0);
}

// $--AppendSlash----------------------------------------------------------
//  This function will append a backslash to a pathname if one does not
//  already exist.
// ------------------------------------------------------------------------
void AppendSlash (                  // RETURNS:  Nothing
    IN OUT LPTSTR sz1)              // pathname
{
    LPTSTR sz2 = sz1;

    while (*sz2)                    //  Loop through each char until '\0'
    {
        sz1 = sz2;
        sz2 = CharNext(sz1);
    }

    //  Check there were no CharNext errors, then add a '\' if not there.
    if (sz2 != sz1 + 1 || *sz1 != TEXT('\\'))
    {
        *sz2++ = TEXT('\\');
        *sz2 = TEXT('\0');
    }
}

//$--GWMain---------------------------------------------------------------------
//  Start threads.
// -----------------------------------------------------------------------------
void GWMain(
    void)
{
    HRESULT      hrT                 = NOERROR;
    HRESULT      hr                  = NOERROR;

    EDK_SERVICE_CONTROL_T sc = 0;

    LPMAPIPROP   lpCurrentObject     = NULL;
    ULONG        ulExtensionDataTag  = 0;
    ULONG        cValues             = 0;
    LPSPropValue lpProps             = NULL;
    LPSBinary    lpBlobArray         = NULL;
    ULONG        cBlobArray          = 0;
    ULONG        i                   = 0;
    LPBYTE       lpbBlob             = NULL;
    ULONG        cbBlob              = 0;
    LPSPropValue lpUnpackedProps     = NULL;
    ULONG        cUnpackedProps      = 0;
    LPTSTR       lpszUnpackedName    = NULL;
    LPTSTR       lpszDir             = NULL;
    ULONG        cBytes              = 0;
    LPTSTR       lpsz                = NULL;

	SizedSPropTagArray(1, rgPropTags) =
	{
		1,
		{
			0,
        }
    };

    DEBUGPUBLIC("GWMain()\n");

    //--------------------------------------------------------------------------

    //
    // Get a pointer to the current object
    //

	hr = HrOpenSessionObject(
	    lpSession, 
        &lpCurrentObject);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Convert our MAPI Name ID to a property tag
    //
    hr = HrCfgPropertyTagFromNameId(
        lpCurrentObject,
        NM_EXTENSION_DATA,
        &ulExtensionDataTag);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Now get the properties we want from the site object
    //

    rgPropTags.aulPropTag[0] =
        PROP_TAG(MV_FLAG|PT_BINARY, PROP_ID(ulExtensionDataTag));
    
    hr = MAPICALL(lpCurrentObject)->GetProps(
        lpCurrentObject,
        (LPSPropTagArray)&rgPropTags,
		fMapiUnicode,
		&cValues,
		&lpProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if(PROP_TYPE(lpProps[0].ulPropTag) == PT_ERROR)
    {
        hr = HR_LOG(E_FAIL);

        goto cleanup;
    }

    lpBlobArray = lpProps->Value.MVbin.lpbin;
    cBlobArray  = lpProps->Value.MVbin.cValues;

    for(i = 0; i < cBlobArray; i++)
    {
        if (!lstrcmpW(SGWBLOBNAMEW, (LPWSTR)lpBlobArray[i].lpb))
        {
            lpbBlob = lpBlobArray[i].lpb;
            cbBlob  = lpBlobArray[i].cb;
        }
    }

    hr = HrCfgUnpackData(
        cbBlob, 
        lpbBlob, 
        &lpszUnpackedName, 
        &cUnpackedProps, 
        &lpUnpackedProps);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //--------------------------------------------------------------------------

    if(cUnpackedProps < 17)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;

    }

    lpszAddressType     = lpUnpackedProps[IDX_ADDR_TYPE].Value.LPSZ;

    lpszSysAdminName    = lpUnpackedProps[IDX_DISP_NAME].Value.LPSZ;

    lpszSysAdminAddr    = lpUnpackedProps[IDX_EMAIL_ADDR].Value.LPSZ;

    cInThreads          = lpUnpackedProps[IDX_EDIT_THREADS_IN].Value.ul;

    cInMessages         = lpUnpackedProps[IDX_EDIT_MSGS_IN].Value.ul;

    dwInSleepInterval   = lpUnpackedProps[IDX_EDIT_SLEEP_IN].Value.ul;

    lpszInDirectory     = lpUnpackedProps[IDX_DIR_IN].Value.LPSZ;

    dwInPollInterval    = lpUnpackedProps[IDX_EDIT_POLLING_IN].Value.ul;

    lpszInConverter     = lpUnpackedProps[IDX_CONVERTER_IN].Value.LPSZ;

    fInEnabled          = lpUnpackedProps[IDX_CHECK_IN_BOUND].Value.b;

    cOutThreads         = lpUnpackedProps[IDX_EDIT_THREADS_OUT].Value.ul;

    cOutMessages        = lpUnpackedProps[IDX_EDIT_MSGS_OUT].Value.ul;

    dwOutSleepInterval  = lpUnpackedProps[IDX_EDIT_SLEEP_OUT].Value.ul;

    lpszOutDirectory    = lpUnpackedProps[IDX_DIR_OUT].Value.LPSZ;

    dwOutPollInterval   = lpUnpackedProps[IDX_EDIT_POLLING_OUT].Value.ul;

    lpszOutConverter    = lpUnpackedProps[IDX_CONVERTER_OUT].Value.LPSZ;

    fOutEnabled         = lpUnpackedProps[IDX_CHECK_OUT_BOUND].Value.b;

    hr = HrStrToStrW(lpszInConverter, &lpszInConverterW);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrStrToStrW(lpszOutConverter, &lpszOutConverterW);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    //
    // Add trailing slash to inbound directory.
    //

    cBytes  = cbStrLen(lpszInDirectory) + sizeof(TCHAR);
    lpszDir = NULL;

    hr = MAPIAllocateMore(cBytes, lpUnpackedProps, (void **)&lpszDir);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lstrcpy(lpszDir, lpszInDirectory);
    AppendSlash(lpszDir);
    lpszInDirectory = lpszDir;

    //
    // Add trailing slash to outbound directory.
    //

    cBytes  = cbStrLen(lpszOutDirectory) + sizeof(TCHAR);
    lpszDir = NULL;

    hr = MAPIAllocateMore(cBytes, lpUnpackedProps, (void **)&lpszDir);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lstrcpy(lpszDir, lpszOutDirectory);
    AppendSlash(lpszDir);
    lpszOutDirectory = lpszDir;

    //
    // Add trailing slash to archive directory.
    //

    cBytes  = cbStrLen(lpszOutDirectory) +
              cbStrLen(TEXT("\\ARCHIVE")) +
              sizeof(TCHAR);

    lpszDir = NULL;

    hr = MAPIAllocateBuffer(cBytes, (void **)&lpszDir);

    if(FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    lstrcpy(lpszDir, lpszOutDirectory);
    AppendSlash(lpszDir);
    lpszArchiveDirectory = lpszDir;

    lpsz =  lpszArchiveDirectory;
    lpsz += lstrlen(lpszArchiveDirectory);
    lpsz --;
    *lpsz = 0;

    while(lpsz != lpszArchiveDirectory)
    {
        if((*lpsz == TEXT('\\')) || (*lpsz == TEXT(':')))
        {
            if(*lpsz == TEXT(':'))
                lpsz++;
            lstrcpy(lpsz, "\\ARCHIVE\\");
            break;
        }

        lpsz--;
    }

    //--------------------------------------------------------------------------

    if(fInEnabled == TRUE)
    {
        hr = HrGWStartNewFileHandler(
            dwInSleepInterval,
            dwInPollInterval,
            cInMessages,
            cInThreads,
            lpszAddressType,
            TEXT("SGW*.TMP"),
            lpszInDirectory,
            (LPTHREAD_START_ROUTINE)ProcessMtsIn);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
    else
    {
        MODULE_WARNING("**** [IN] Processing not enabled ****");
    }

    //--------------------------------------------------------------------------

    if(fOutEnabled == TRUE)
    {
        hr = HrGWStartNewMailHandler(
            dwOutSleepInterval,
            dwOutPollInterval,
            cOutMessages,
            cOutThreads,
            lpszAddressType,
            lpszOutDirectory,
            (LPTHREAD_START_ROUTINE)ProcessMtsOut);

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }
    else
    {
        MODULE_WARNING("**** [OUT] Processing not enabled ****");
    }

cleanup:

    if(FAILED(hr))
    {
        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    MAPIFREEBUFFER(lpProps);

    MAPIFREEBUFFER(lpszUnpackedName);

    ULRELEASE(lpCurrentObject);

    //
    // Wait for a request for the gateway to stop.
    //

    hr = HR_LOG(HrServiceWaitForStop(INFINITE, &sc));

    MAPIFREEBUFFER(lpszInConverterW);

    MAPIFREEBUFFER(lpszOutConverterW);

    MAPIFREEBUFFER(lpUnpackedProps);

    //
    // IMPORTANT: Return from this function only if the gateway is ready to stop.
    //

    return;
}

//$--HrGWLogon------------------------------------------------------------------
//  Logon to the gateway.
// -----------------------------------------------------------------------------
HRESULT HrGWLogon(                      // RETURNS: return code
    void)                               // no arguments
{
    HRESULT      hr                  = NOERROR;
    SCODE        sc                  = 0;
    BOOL         fStatus             = TRUE;
    LPTSTR       lpszT               = NULL;
    LPMAPIPROP   lpSiteAddressing    = NULL;
    ULONG        ulGatewayProxyTag   = 0;
    ULONG        cValues             = 0;
    LPSPropValue lpProps             = NULL;
    ULONG        i                   = 0;

	SizedSPropTagArray(1, rgPropTags) =
	{
		1,
		{
			0,
        }
    };

    DEBUGPUBLIC("HrGWLogon()\n");

    InitializeCriticalSection(&csGatewaySeqNo);
    InitializeCriticalSection(&csInboundIdList);
    InitializeCriticalSection(&csOutboundIdList);

    InboundIdList.lpcs  = &csInboundIdList;
    OutboundIdList.lpcs = &csOutboundIdList;

    lpSession       = GetGWSession();
    lpStore         = GetGWDefaultStore();
    lpRootFolder    = GetGWRootFolder();
    lpMtsInFolder   = GetGWMtsInFolder();
    lpMtsOutFolder  = GetGWMtsOutFolder();
    cbGalEid        = GetGWGALEntryIdSize();
    lpGalEid        = GetGWGALEntryId();

    //
    // Get a pointer to the site addressing object

	hr = HrOpenSiteContainerAddressing(
	    lpSession, 
        &lpSiteAddressing);

    if(FAILED(hr))
    {
        fStatus = FALSE;
        goto cleanup;
    }

    //
    // Convert our MAPI Name ID to a property tag
    //
    hr = HrCfgPropertyTagFromNameId(
        lpSiteAddressing,
        NM_GATEWAY_PROXY,
        &ulGatewayProxyTag);

    if(FAILED(hr))
    {
        fStatus = FALSE;
        goto cleanup;
    }

    //
    // Now get the properties we want from the site object
    //

    rgPropTags.aulPropTag[0] = ulGatewayProxyTag;
    
    hr = MAPICALL(lpSiteAddressing)->GetProps(
        lpSiteAddressing,
        (LPSPropTagArray)&rgPropTags,
		fMapiUnicode,
		&cValues,
		&lpProps);

    if(FAILED(hr))
    {
        fStatus = FALSE;
        goto cleanup;
    }

    if(PROP_TYPE(lpProps[0].ulPropTag) == PT_ERROR)
    {
        hr = HR_LOG(E_FAIL);

        fStatus = FALSE;
        goto cleanup;
    }

    if(lpProps[0].Value.MVSZ.cValues == 0)
    {
        hr = HR_LOG(E_FAIL);

        fStatus = FALSE;
        goto cleanup;
    }

    for(i = 0; i < (lpProps[0].Value.MVSZ.cValues); i++)
    {
        if(!_tcsnicmp(
            lpProps[0].Value.MVSZ.LPPSZ[i],
            TEXT("X400:"),
            lstrlen(TEXT("X400:"))))
        {
            break;
        }
    }

    sc = MAPIAllocateBuffer(
        cbStrLen(lpProps[0].Value.MVSZ.LPPSZ[i]),
        (void **)&lpszT);

    if(FAILED(sc))                           
    {                                                   
        hr = HR_LOG(E_OUTOFMEMORY);                                 
        goto cleanup;                                
    }                    
    
    lstrcpy(lpszT, lpProps[0].Value.MVSZ.LPPSZ[i]);

    //
    // Create the local enterprise GDI.
    //

    hr = HrCreateEnterpriseGDI(
        lpszT,
        TEXT(":;"),
        &lpszLocalGDI);

    if(FAILED(hr))
    {
        fStatus = FALSE;
        goto cleanup;
    }

    // Open an event log for this application.
    hr = HrEventOpenLog(
        szAppName,          // application name
        NULL,               // executable name (will be computed)
        TEXT("EDKMSG.DLL"), // event message file
        NULL,               // parameter message file (will be computed)
        NULL,               // category message file (will be computed)
        &hEventLog);        // event source handle

    if ( FAILED(hr) || (hEventLog == NULL) )
    {
        goto cleanup;
    }

    // Initialize global conversion engine data.
    hr = HrConvInitGlobals();

    if ( FAILED(hr) )
    {
        fStatus = FALSE;
        goto cleanup;
    }

cleanup:

    ULRELEASE(lpSiteAddressing);

    MAPIFREEBUFFER(lpProps);

    MAPIFREEBUFFER(lpszT);

    if(fStatus == FALSE)
    {
        //
        // Gateway logon failed.
        //

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    RETURN(hr);
}

//$--HrArchiveMtsOut------------------------------------------------------------
//  Archive messages in MTS-OUT which could not be delivered.
// -----------------------------------------------------------------------------
HRESULT HrArchiveMtsOut(                // RETURNS: zero
    VOID)                               // parameter
{
    HRESULT         hr                          = NOERROR;
    ULONG           cbeid                       = 0;
    LPENTRYID       lpeid                       = NULL;
    ULONG           ulObjType                   = 0;
    ULONG           ulPropTag                   = 0;
    ULONG           cValues                     = 0;
    ULONG           i                           = 0;
    ULONG           cRows                       = 0;

    LPMAPIFOLDER    lpArchiveFolder             = NULL;
    LPMAPITABLE     lpTable                     = NULL;

    LPMESSAGE       lpEnvelope                  = NULL;

    LPSPropValue    lpProps                     = NULL;

	LPSPropTagArray lpPropTagArray              = NULL;

    ULONG           cValuesT                    = 0;
    LPSPropValue    lpPropsT                    = NULL;

    ULONG           cbMsgEid                    = 0;
    LPENTRYID       lpMsgEid                    = NULL;

    LPSRowSet       lpRows                      = NULL;

    SizedSPropTagArray(1, rgRecordKeyPropTag) =
    {
        1,
        {
            PR_RECORD_KEY
        }
    };

    ULONG           cBytes                      = 0;
    LPTSTR          lpszRecordKey               = 0;

    LPIDITEM        lpIdItem                    = NULL;

    SizedSPropTagArray(1, rgPropTag) =
    {
        1,
        {
            PR_ENTRYID
        }
    };

    DEBUGPUBLIC("HrArchiveMtsOut()\n");

    //
    // Find and open the MTS-OUT archive folder.
    //

    hr = HrMAPIFindFolder(
        GetGWRootFolder(),
        TEXT("ARCHIVE"),
        &cbeid,
        &lpeid);

    if(FAILED(hr))
    {                                                   
        hr = MAPICALL(lpRootFolder)->CreateFolder(
            lpRootFolder,
            FOLDER_GENERIC,
            TEXT("ARCHIVE"),
            NULL,
            NULL,
            MAPI_DEFERRED_ERRORS,
            &lpArchiveFolder);

        if(FAILED(hr))
        {
            goto cleanup;
        }
    }
    else
    {
        // Open the archive folder in the root folder
        hr = MAPICALL(lpRootFolder)->OpenEntry(
            lpRootFolder,
            cbeid,
            lpeid,
            NULL,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            &ulObjType,
            (LPUNKNOWN FAR *) &lpArchiveFolder);

        MAPIFREEBUFFER(lpeid);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        if(ulObjType != MAPI_FOLDER)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }
    }

    //
    // Get the contents table for the MTS-OUT
    //

    hr = MAPICALL(lpMtsOutFolder)->GetContentsTable(
        lpMtsOutFolder,
        MAPI_DEFERRED_ERRORS,
        &lpTable);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    hr = MAPICALL(lpTable)->SetColumns(
        lpTable,
        (LPSPropTagArray)&rgPropTag,
        TBL_BATCH);

    if(FAILED(hr))
    {
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

    ULRELEASE(lpTable);

    if(FAILED(hr))
    {
        goto cleanup;
    }

    cRows = lpRows->cRows;

    for(i = 0; i < cRows; i++)
    {
        cValues = lpRows->aRow[i].cValues;

        lpProps = lpRows->aRow[i].lpProps;

        cbeid = lpProps[0].Value.bin.cb;
        lpeid = (LPENTRYID)lpProps[0].Value.bin.lpb;

        cbMsgEid = cbeid;
        lpMsgEid = lpeid;

        cValues = 0;
        lpProps = NULL;

        // Get the message in the MTS-OUT folder
        hr = MAPICALL(lpMtsOutFolder)->OpenEntry(
            lpMtsOutFolder,
            cbeid,
            lpeid,
            NULL,
            MAPI_DEFERRED_ERRORS|MAPI_MODIFY,
            &ulObjType,
            (LPUNKNOWN FAR *)&lpEnvelope);

        cbeid = 0;
        lpeid = NULL;

        if(FAILED(hr))
        {
            goto cleanup;
        }

        if(ulObjType != MAPI_MESSAGE)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------

        // Get the message ID

        MAPIFREEBUFFER(lpPropsT);
        MAPIFREEBUFFER(lpszRecordKey);

        cValuesT = 0;
        lpPropsT = NULL;

        hr = MAPICALL(lpEnvelope)->GetProps(
            lpEnvelope,
            (LPSPropTagArray)&rgRecordKeyPropTag,
    		fMapiUnicode,
    		&cValuesT,
    		&lpPropsT);

        if(FAILED(hr))
        {
            goto cleanup;
        }

        if(lpPropsT[0].ulPropTag != PR_RECORD_KEY)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if(lpPropsT[0].Value.bin.cb == 0)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        if(lpPropsT[0].Value.bin.lpb == NULL)
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        cBytes = (lpPropsT[0].Value.bin.cb + sizeof(TCHAR)) * (2 * sizeof(TCHAR));

        hr = MAPIAllocateBuffer(cBytes, (void **)&lpszRecordKey);

        if(FAILED(hr))
        {                                                   
            goto cleanup;                                
        }                                                   

        HexFromBin(lpPropsT[0].Value.bin.lpb, lpPropsT[0].Value.bin.cb, lpszRecordKey);

        MAPIFREEBUFFER(lpPropsT);

        hr = HrLookupIdItem(
            &OutboundIdList,
            lpszRecordKey,
            &lpIdItem);

        if(hr == EDK_E_NOT_FOUND)
        {
            //
            // Skip this message. It is a new message.
            //

            MAPIFREEBUFFER(lpszRecordKey);
            MAPIFREEBUFFER(lpPropsT);
            ULRELEASE(lpEnvelope);
            continue;
        }

        if(FAILED(hr))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

    //------------------------------------------------------------------------------

        MAPIFREEBUFFER(lpszRecordKey);
        MAPIFREEBUFFER(lpPropsT);
        ULRELEASE(lpEnvelope);

    //------------------------------------------------------------------------------

        hr = HrMAPIMoveMessage(
            lpMtsOutFolder,
            lpArchiveFolder,
            cbMsgEid,
            lpMsgEid);

        if(FAILED(hr))
        {
            ; // create an entry in the debug log
        }
    }

cleanup:

    FREEPROWS(lpRows);

    MAPIFREEBUFFER(lpPropsT);

    MAPIFREEBUFFER(lpszRecordKey);

    ULRELEASE(lpEnvelope);

    ULRELEASE(lpArchiveFolder);

    ULRELEASE(lpTable);

    RETURN(hr);
}

//$--HrArchiveMtsIn-------------------------------------------------------------
//  Archive messages in MTS-IN which could not be delivered.
// -----------------------------------------------------------------------------
HRESULT HrArchiveMtsIn(                 // RETURNS: return code
    VOID)                               // no arguments
{
	HRESULT  hr                       = NOERROR;
    HRESULT  hrT                      = NOERROR;
    LPIDITEM lpIdItem                 = NULL;
    BOOL     fRet                     = FALSE;
    TCHAR    rgchFileName[MAX_PATH+1] = {0};
    TCHAR    rgchPathName[MAX_PATH+1] = {0};
    LPTSTR   lpszPath                 = NULL;
    LPIDITEM lpIdList                 = NULL;

    //
    // Find and open the MTS-IN archive directory.
    //

    lstrcpy(rgchPathName, lpszArchiveDirectory);

    fRet = CreateDirectory(rgchPathName, NULL);

    if(fRet == FALSE)
    {
        hr = HR_LOG(E_FAIL);
    }

    lpszPath = rgchPathName;

    lpIdList = &InboundIdList;

    EnterCriticalSection(lpIdList->lpcs);

    __try
    {
        lpIdItem = lpIdList->next;
    
        while(lpIdItem != NULL)
        {
            lpIdList->next = lpIdItem->next;

            rgchFileName[0] = 0;

	        fRet = GetTempFileName32(lpszPath, TEXT("BAK"), 0, (LPTSTR)rgchFileName);

            if(fRet == FALSE)
	        {
		        hr = HR_LOG(E_FAIL);
	        }
            else
            {
                fRet = MoveFileEx(
                    lpIdItem->lpszId,
                    (LPTSTR)rgchFileName,
                    MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING);

                if(fRet == FALSE)
                {
                    hr = HR_LOG(E_FAIL);
                }
            }

            lpIdItem = lpIdList->next;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());

        hr = HR_LOG(E_FAIL);

        MODULE_WARNING("**** Stopping gateway ****");

        SetServiceExitCode( ERROR_INTERNAL_ERROR, NOERROR);

        ServiceStop();
    }

    LeaveCriticalSection(lpIdList->lpcs);

    RETURN(hr);
}

//$--HrGWLogoff-----------------------------------------------------------------
//  Logoff of the gateway.
// -----------------------------------------------------------------------------
HRESULT HrGWLogoff(                     // RETURNS: return code
    void)                               // no arguments
{
    HRESULT hr  = NOERROR;
    HRESULT hrT = NOERROR;

    DEBUGPUBLIC("HrGWLogoff()\n");

    // De-initialize conversion engine global data.
    ConvUninitGlobals();

    // Close the event log.
    (VOID)HrEventCloseLog();
    hEventLog = NULL;

    MAPIFREEBUFFER(lpbBuffer);

    MAPIFREEBUFFER(lppszBufferArray);

    MAPIFREEBUFFER(lpszLocalGDI);

    //
    // Archive messages which could not be delivered.
    //

    hrT = HR_LOG(HrArchiveMtsIn());

    hrT = HR_LOG(HrArchiveMtsOut());


    hrT = HR_LOG(HrEmptyIdList(&InboundIdList));

    hrT = HR_LOG(HrEmptyIdList(&OutboundIdList));

    DeleteCriticalSection(&csGatewaySeqNo);
    DeleteCriticalSection(&csInboundIdList);
    DeleteCriticalSection(&csOutboundIdList);

    MAPIFREEBUFFER(lpszArchiveDirectory);

    RETURN(hr);
}
