// --fldmtrc.cpp----------------------------------------------------------------
//
//  Implements the folder metrics code.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "fldmtrc.h"
#include "fldmtrc.chk"

// Class constants
// ---------------
SPropTagArray CFolderMetrics::m_sFolderContentCount     = { 1L, {PR_CONTENT_COUNT } };
SSortOrderSet CFolderMetrics::m_sSortOrderSet           = { 1L, 0, 0, {PR_MESSAGE_DELIVERY_TIME , TABLE_SORT_ASCEND} };
SPropTagArray CFolderMetrics::m_sInFolderSince          = { 1L, {PR_MESSAGE_DELIVERY_TIME } };


//$--CFolderMetrics::CFolderMetrics---------------------------------------------
//  Constructor for Folder Metrics object.
// -----------------------------------------------------------------------------
CFolderMetrics::CFolderMetrics()
{

    DEBUGPUBLIC("CFolderMetrics::CFolderMetrics()\n");

    m_lpFolder = NULL;
    m_lpTable = NULL;
}


//$--CFolderMetrics::~CFolderMetrics--------------------------------------------
//  Destructor for folder Metrics object.
// -----------------------------------------------------------------------------
CFolderMetrics::~CFolderMetrics()
{
    DEBUGPUBLIC("CFolderMetrics::~CFolderMetrics()\n");

    // m_lpFolder isn't freed because we didn't create it.
    // ---------------------------------------------------

    ULRELEASE(m_lpTable);
}


//$--CFolderMetrics::HrReset----------------------------------------------------
//  Resets and assigns the folder metrics object to a particular folder.
// -----------------------------------------------------------------------------
HRESULT CFolderMetrics::HrReset(        // HRESULT
    IN LPMAPIFOLDER lpFolder)           // Object is assigned to this folder.
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("CFolderMetrics::HrReset()\n");

	hr = CHK_CFolderMetrics_HrReset(lpFolder);
	if (FAILED(hr))
		RETURN(hr);

    if (lpFolder == NULL)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    ULRELEASE(m_lpTable);

    // Open content table for lpFolder and set columns for PR_IN_FOLDER_SINCE
    // ----------------------------------------------------------------------
    hr = lpFolder->GetContentsTable(MAPI_DEFERRED_ERRORS, &m_lpTable);

    if (FAILED(hr))
    {
        goto cleanup;
    }

    hr = m_lpTable->SetColumns(&m_sInFolderSince, (ULONG)0);

    if (FAILED(hr))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    m_lpFolder = lpFolder;

cleanup:
    // m_lpFolder isn't freed because we didn't create it.
    // ---------------------------------------------------

    RETURN(hr);
}


//$--CFolderMetrics::HrGetFolderMetrics-----------------------------------------
//  Determine and return the folder metrics values.
// -----------------------------------------------------------------------------
HRESULT CFolderMetrics::HrGetFolderMetrics( // RETURNS: HRESULT
    IN __int64 liNow,                       // Current time expressed as a file time.
    IN DWORD fMetric,                       // Flag to determine the metric
                                            //  to query. May be an or'ed
                                            //  combination of:
                                            //  FM_CMESSAGES, FM_LONGEST_WAIT
                                            //  FM_TOTAL_WAIT.
    OUT DWORD &cMessages,                   // Receives number of mesages
                                            //  in folder if FM_CMESSAGES
                                            //  is specified. = 0 otherwise.
    OUT __int64 &liLongestWait,             // Receives longest wait
                                            //  expressed as a file time if
                                            //  FM_LONGEST_WAIT specified.
                                            //  = 0 otherwise.
    OUT __int64 &liTotalWait)               // Recieves total wait
                                            //  expresses as a file time if
                                            //  FM_TOTAL_WAIT specified.
                                            // = 0 otherwise.
{
    HRESULT hr       = NOERROR;

    DEBUGPRIVATE("CFolderMetrics::HrGetFolderMetrics()\n");

    // pre-clear all return values
    // ---------------------------
    cMessages = 0;
    liLongestWait = 0;
    liTotalWait   = 0;

	hr = CHK_CFolderMetrics_HrGetFolderMetrics(
    	liNow, 
		fMetric, 
		cMessages, 
		liLongestWait, 
		liTotalWait);
	if (FAILED(hr))
		RETURN(hr);

    // The message count can be generated as a side effect of
    // calculating the FM_TOTAL_WAIT or queried separately as a folder
    // property.  If FM_TOTAL_WAIT is not requested then
    // then query the message count as a less expensive folder property.
    // ----------------------------------------------------------
    if (!(fMetric & FM_TOTAL_WAIT))
    {
        hr = HrGetcMessages(cMessages);

        if (FAILED(hr))
        {
            goto cleanup;
        }
    }


    // Re-sort contents table and go to the start of the table.
    // --------------------------------------------------------
    hr = m_lpTable->SortTable(&m_sSortOrderSet, 0);

    if (FAILED(hr))
    {
        goto cleanup;
    }

    hr = m_lpTable->SeekRow(BOOKMARK_BEGINNING, 0, NULL);

    if (FAILED(hr))
    {
        goto cleanup;
    }

    // If longest wait metric requested, then get longest wait.
    // --------------------------------------------------------
    if (fMetric & FM_LONGEST_WAIT)
    {
        hr = HrGetLongestWait(liNow, liLongestWait);

        if (FAILED(hr))
        {
            goto cleanup;
        }
    }

    // If total wait metric requested, then get total wait.
    // ----------------------------------------------------
    if (fMetric & FM_TOTAL_WAIT)
    {
        hr = HrGetTotalWait(liNow, cMessages, liTotalWait);

        if (FAILED(hr))
        {
            goto cleanup;
        }
    }

cleanup:

    // if they didn't ask for it then don't give it to them.
    // -----------------------------------------------------
    if (!(fMetric & FM_CMESSAGES))
    {
        cMessages     = 0;
    }

    if (!(fMetric & FM_LONGEST_WAIT))
    {
        liLongestWait = 0;
    }

    if (!(fMetric & FM_TOTAL_WAIT))
    {
        liTotalWait = 0;
    }

    RETURN(hr);
}


// -----------------------------------------------------------------------------
//  Private member functions
// -----------------------------------------------------------------------------

//$--CFolderMetrics::HrGetcMessages---------------------------------------------
//  Returns the number of messages in the object folder.
// -----------------------------------------------------------------------------
HRESULT CFolderMetrics::HrGetcMessages( // RETURNS: HRESULT
    OUT DWORD &cMessage)                // Receives number of messages in folder.
{
    HRESULT         hr          = NOERROR;
    DWORD           cValues     = 0;
    LPSPropValue    lpPropValue = NULL;


    DEBUGPRIVATE("CFolderMetrics::HrGetMessages()\n");

	hr = CHK_CFolderMetrics_HrGetcMessages(cMessage);
	if (FAILED(hr))
		RETURN(hr);

    cMessage = 0;

    hr = m_lpFolder->GetProps(
        &m_sFolderContentCount, fMapiUnicode, &cValues, &lpPropValue);

    if (FAILED(hr) || (hr == MAPI_W_ERRORS_RETURNED))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    if ( cValues > 0 )
    {
        cMessage = (DWORD) lpPropValue->Value.l;
    }

cleanup:

    MAPIFREEBUFFER(lpPropValue);

    RETURN(hr);
}


//$--CFolderMetrics::HrGetLongestWait-------------------------------------------
//  Retrieves duration in the folder of the oldest message.
// -----------------------------------------------------------------------------
HRESULT CFolderMetrics::HrGetLongestWait(   // RETURNS: HRESULT
    IN __int64 liNow,                       // Current Time expressed as a
                                            //   file time.
    OUT __int64 &liLongestWait)             // Receives the longest time that
                                            //   a messages has been in
                                            //   the folder expressed as a
                                            //   file time.
{
    HRESULT hr                  = NOERROR;
    LONG    lRes                = 0;

    LPSRowSet lpRows            = NULL;
    LPSPropValue lpProps        = NULL;
    ULONG ulType                = 0;
    __int64  liInFolderSince	= 0;

    DEBUGPRIVATE("CFolderMetrics::HrGetLongestWait()\n");

	hr = CHK_CFolderMetrics_HrGetLongestWait(liNow, liLongestWait);
	if (FAILED(hr))
		RETURN(hr);

    liLongestWait = 0;

    hr = m_lpTable->QueryRows(1, TBL_NOADVANCE, &lpRows);

    if (FAILED(hr) || (hr == MAPI_W_ERRORS_RETURNED))
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // If no entries, then quit.
    // -------------------------
    if (lpRows->cRows == 0)
    {
        goto cleanup;
    }

    // If number values differs from 1 then quit.
    // ------------------------------------------
    if (lpRows->aRow[0].cValues != 1)
    {
        ASSERTERROR(FALSE,"CFolderMetrics::rcGetLongestWait() Content "
        	"table contains other than 1 Value type.");
        goto cleanup;
    }

    lpProps = lpRows->aRow[0].lpProps;

    ulType = PROP_TYPE(lpProps->ulPropTag);

    if (ulType!= PT_SYSTIME)
    {
        // OK, fake it
        liLongestWait = 0 ;
        goto cleanup ;
    }

    // If time is more recent than now then ignore it.
    // -----------------------------------------------
    liInFolderSince = INT64_FROM_FILETIME(lpProps->Value.ft);

    if (liInFolderSince < liNow)
    {
       liLongestWait = liNow - liInFolderSince;
    }

cleanup:

    FreeProws(lpRows);

    RETURN(hr);
}


//$--HrGetTotalWait-------------------------------------------------------------
//  Returns the sum of all of the waiting periods of each message in the folder.
// -----------------------------------------------------------------------------
HRESULT CFolderMetrics::HrGetTotalWait( // RETURNS: HRESULT
    IN __int64 liNow,                   // Current time expressed as a file time.
    OUT DWORD &cMessages,               // Receives number of messages in file.
    OUT __int64 &liTotalWait)           // Receives total wait of messages in file.
{
    HRESULT hr          = NOERROR;
    LONG  lRes          = 0;

    __int64  liInFolderSince = 0;

    LPSRowSet lpRows = NULL;
    LPSPropValue lpProps = NULL;

    DWORD i             = 0;
    DWORD cRows         = 0;


    DEBUGPRIVATE("CFolderMetrics::HrGetTotalWait()\n");

	hr = CHK_CFolderMetrics_HrGetTotalWait(liNow, cMessages, liTotalWait);
	if (FAILED(hr))
		RETURN(hr);

    liInFolderSince = 0;
    liTotalWait = 0;
    cMessages = 0;

    // Read entries 100 at a time and calculate the total wait
    // from the in folder since time.
    // ---------------------------------------------------------
    do
    {
        hr = m_lpTable->QueryRows(100, 0, &lpRows);

        if (FAILED(hr) || (hr == MAPI_W_ERRORS_RETURNED))
        {
            hr = HR_LOG(E_FAIL);
            goto cleanup;
        }

        cMessages += lpRows->cRows;
        cRows = lpRows->cRows;

        for (i=0; i<cRows; i++)
        {
            // Get the property value from the row.
            // ------------------------------------
            if (lpRows->aRow[i].cValues != 1)
            {
                ASSERTERROR(FALSE,"Content table contains other than 1 "
                	"Value type.");
                goto cleanup;
            }

            lpProps = lpRows->aRow[i].lpProps;
            if (PROP_TYPE(lpProps->ulPropTag) != PT_SYSTIME)
            {
                // ok, fake it.
                continue ;
            }

            // If folder submit time is more recent than
            // now, then don't include this item in average.
            // ----------------------------------------------
            liInFolderSince =  INT64_FROM_FILETIME(lpProps->Value.ft);
            if (liInFolderSince < liNow)
            {
                liTotalWait = liTotalWait + (liNow - liInFolderSince);
            }
        }

        FreeProws(lpRows);
        lpRows = NULL;
    }
    while (cRows != 0); // end of DO {  } WHILE () .

cleanup:

    FreeProws(lpRows);

    RETURN(hr);
}
