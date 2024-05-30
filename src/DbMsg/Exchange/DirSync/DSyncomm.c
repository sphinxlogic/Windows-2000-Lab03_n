// --dsyncomm.c-----------------------------------------------------------------
//
//  This file contains routines that are called by the code in dirsync.c. 
//  The routines in this file do the actual communication with the foreign 
//  system.
//
//  The routines in this file do the directory synchronization by reading and 
//  writing to a file in a format that can be used for directory exchange.
//  However, they were designed in such a way that developers can easily 
//  replace them with their own routines.  So for instance, they could be 
//  rewritten to communicate directly with a foreign mail system's API, or 
//  to make database read/write calls.
//
//
//  This file is linked with dirsync.c, and compiles to a seperate executable 
//  which is run from the command line.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dirsync.h"
#include "dsynmsg.h"
#include "dsyncomm.chk"

//
// Defined Constants
//

// Longest line that can be read from the import file.

#define MAX_IMPORT_LINE                         512

// Equates for size of array of DAPI_ENTRY's created on import, 
// initial allocation and growth amount.

#define DAPI_ARRAY_ALLOCATION_INITIAL           30
#define DAPI_ARRAY_ALLOCATION_GROWTH            20

// Equates for different ways of handling duplicate attributes 
// in HrAddAttributeToList().

#define DUPLICATE_ALLOW         0       // don't check for duplicates (faster)
#define DUPLICATE_DISCARD       1       // discard the duplicate
#define DUPLICATE_REPLACE       2       // replace orig w/ dup in same location
#define DUPLICATE_MULTI_VALUED  3       // make dup multi-valued part of orig
#define DUPLICATE_FAIL          4       // return error on duplicate

//
// Variables Local to the File
//

static FILE *   hExportFile                     = NULL;
static TCHAR    szExportFile[MAX_PATH+1]        = {0};
static BOOL     fDeleteExportFile               = FALSE;

static ULONG    cDAPIArrayElements              = DAPI_ARRAY_ALLOCATION_INITIAL;

static FILE *   hImportFile                     = NULL;
static TCHAR    szImportFile[MAX_PATH+1]        = {0};
static TCHAR    szObjectClass[MAX_PATH+1]       = {0};
static TCHAR    szSourceStamp[MAX_PATH+1]       = {0};
static TCHAR    szBasePoint[MAX_PATH+1]         = {0};
static TCHAR    szContainer[MAX_PATH+1]         = {0};
static TCHAR    szHomeServer[MAX_PATH+1]        = {0};

static CHAR     szImportLine[MAX_IMPORT_LINE]   = {0};
static ULONG    cchImportLine                   = 0;
static BOOL     fImportLineSaved                = FALSE;
static ULONG    nImportLineNumber               = 0;
static CHAR     szTemp1[20]                     = {0};
static CHAR     szRawDN[MAX_IMPORT_LINE]        = {0};

//
// Declarations for Local Routines
//

static HRESULT HrCreateDAPIEntry(
    OUT PDAPI_ENTRY * ppDAPIEntry);

static HRESULT HrReadImportRecordHeader(
    IN      LPTSTR pszBasePoint,
    IN      LPTSTR pszContainer,
    IN OUT  PDAPI_ENTRY pAttributes,
    IN OUT  PDAPI_ENTRY pValues,
    OUT     LPDIR_SYNC_OPERATION peOperation);

static HRESULT HrReadImportDataLines(
    IN OUT  PDAPI_ENTRY pAttributes,
    IN OUT  PDAPI_ENTRY pValues);

static HRESULT HrStripWhiteSpace(
    IN OUT  LPTSTR pszString);

static HRESULT HrSkipToNextRecordHeader(void);

static HRESULT HrReadImportLine(void);

static HRESULT HrAddAttributeToList(
    IN      LPSTR       pszAttribute,
    IN      LPSTR       pszValue,
    IN      ULONG       ulDuplicateAction,
    IN OUT  PDAPI_ENTRY pAttributes,
    IN OUT  PDAPI_ENTRY pValues);

static HRESULT HrExpandDAPIEntry(
    IN OUT  PDAPI_ENTRY pDAPIEntry);



//
// User-Specified Routines
//



//$--HrOpenExport---------------------------------------------------------------
//  Function to do whatever initialization needs to be done before exporting 
//  records for directory synchronization.  It should return NOERROR if 
//  the initialization was successful and an error otherwise.  If this function 
//  returns an error then HrWriteExport() and HrCloseExport() will not be 
//  called.
// -----------------------------------------------------------------------------
HRESULT HrOpenExport(                       // RETURNS: HRESULT
    IN LPTSTR pszExportFile)                // file name from /EXPFILE
{
    HRESULT             hr                  = NOERROR;

    DEBUGPUBLIC("HrOpenExport()\n");

    hr = CHK_HrOpenExport(pszExportFile);
    if (FAILED(hr))
        RETURN(hr);

    lstrcpy(szExportFile, pszExportFile);
    fDeleteExportFile = FALSE;

    hExportFile = fopen(szExportFile, "w");
    if (hExportFile == NULL)
    {
        EventLogMsg(
            DIRSYNC_CANNOT_CREATE_EXPORT_FILE, 
            1, szExportFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
    }

    RETURN(hr);
}



//$--HrWriteExport--------------------------------------------------------------
//  Function to export a single record for directory synchronization.  It is 
//  called repeatedly: once for each record to be exported.  If this function 
//  returns an error it will not be called again, and HrCloseExport() will be 
//  called once to clean everything up.
// -----------------------------------------------------------------------------
HRESULT HrWriteExport(                      // RETURNS: HRESULT
    IN PDAPI_ENTRY pEntry,                  // record to export
    IN LPDIR_SYNC_ATTRIBUTE_INFO rgdsAttributeInfo,
                                            // additional information about pEntry
    IN LPTSTR pszDN,                        // distinguished name of this object
    IN DIR_SYNC_OPERATION eOperation)       // type of operation to do with object
{
    HRESULT             hr                  = NOERROR;
    int                 cBytesWritten       = 0;
    DWORD               i                   = 0;
    DWORD               iValueNumber        = 0;
    DWORD               chOperation         = 0;

    DEBUGPUBLIC("HrWriteExport()\n");

    hr = CHK_HrWriteExport(
        pEntry, 
        rgdsAttributeInfo, 
        pszDN, 
        eOperation);
    if (FAILED(hr))
        RETURN(hr);

    // Determine the letter for the operation.

    switch (eOperation)
    {
        case OPERATION_ADD:
            chOperation = 'A';
            break;

        case OPERATION_DELETE:
            chOperation = 'D';
            break;

        case OPERATION_MODIFY:
            chOperation = 'M';
            break;

        default:
            EventLogMsg(
                DIRSYNC_INTERNAL_ERROR, 
                0, 
                0);
            hr = HR_LOG(E_FAIL);
            goto cleanup;
    }

    // Output the first line of the record.

    cBytesWritten = fprintf(hExportFile, "%c %s\n", chOperation, pszDN);
    if (cBytesWritten < 0)
    {
        EventLogMsg(
            DIRSYNC_CANNOT_WRITE_EXPORT_FILE, 
            1, szExportFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    // If the operation is not delete, then output each attribute.

    if (eOperation != OPERATION_DELETE)
    {
        for (i = 0; i < pEntry->unAttributes; i++)
        {
            // Output this attribute only if the user requested it.

            if (rgdsAttributeInfo[i].fRequested)
            {
                ATT_VALUE * pValue = &pEntry->rgEntryValues[i];

                if (pValue->pNextValue == NULL)
                {
                    // Only one instance of this value.

                    cBytesWritten = fprintf(
                        hExportFile, "- %s:%s\n",
                        rgdsAttributeInfo[i].pszName, 
                        pValue->Value.pszValue ? pValue->Value.pszValue : "");
                    if (cBytesWritten < 0)
                    {
                        hr = HR_LOG(E_FAIL);
                        EventLogMsg(
                            DIRSYNC_CANNOT_WRITE_EXPORT_FILE, 
                            1, szExportFile, 
                            1, _doserrno);
                        goto cleanup;
                    }
                }
                else
                {
                    // Multiple instances of this value.

                    for (
                        iValueNumber = 0; 
                        pValue != NULL; 
                        iValueNumber++, pValue = pValue->pNextValue)
                    {
                        cBytesWritten = fprintf(
                            hExportFile, 
                            "- %s[%ld]:%s\n", 
                            rgdsAttributeInfo[i].pszName, 
                            iValueNumber, 
                            pValue->Value.pszValue ? pValue->Value.pszValue : "");
                        if (cBytesWritten < 0)
                        {
                            hr = HR_LOG(E_FAIL);
                            EventLogMsg(
                                DIRSYNC_CANNOT_WRITE_EXPORT_FILE, 
                                1, szExportFile, 
                                1, _doserrno);
                            goto cleanup;
                        }
                    } // endfor
                } // endif (pValue->pNextValue == NULL)
            } // endif (rgdsAttributeInfo[i].fRequested)
        } // endfor
    } // endif (eOperation != OPERATION_DELETE)

    // Put a blank line between records.

    cBytesWritten = fprintf(hExportFile, "\n");
    if (cBytesWritten < 0)
    {
        hr = HR_LOG(E_FAIL);
    }

cleanup:
    // If there was an error then set the flag to tell HrCloseExport() 
    // to delete the file.

    if (FAILED(hr))
    {
        fDeleteExportFile = TRUE;
    }

    RETURN(hr);
}



//$--HrCloseExport--------------------------------------------------------------
//  Function to do whatever cleanup needs to be done after exporting records 
//  for directory synchronization.
// -----------------------------------------------------------------------------
HRESULT HrCloseExport(void)                 // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    DWORD               i                   = 0;

    DEBUGPUBLIC("HrCloseExport()\n");

    // Close the export file.

    if (fclose(hExportFile) == EOF)
    {
        EventLogMsg(
            DIRSYNC_CANNOT_CLOSE_EXPORT_FILE, 
            1, szExportFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
    }

    // If there was an error either on the write or on the close, then delete 
    // the file.

    if (FAILED(hr) || fDeleteExportFile)
    {
        (void) remove(szExportFile);
    }

    RETURN(hr);
}



//$--HrOpenImport---------------------------------------------------------------
//  Function to do whatever initialization needs to be done before importing 
//  records for directory synchronization.  It should return NOERROR if 
//  the initialization was successful and an error otherwise.  If this function 
//  returns an error then HrReadImport() and HrCloseImport() will not be 
//  called.
// -----------------------------------------------------------------------------
HRESULT HrOpenImport(                       // RETURNS: HRESULT
    IN  LPTSTR pszImportFile,               // name of file to import
    IN  LPTSTR pszObjectClass,              // default object class
    IN  LPTSTR pszSourceStamp,              // string for Imported-From attr
    IN  LPTSTR pszBasePoint,                // default base point
    IN  LPTSTR pszContainer,                // default container
    IN  LPTSTR pszHomeServer)               // default home server for new mailbox
{
    HRESULT             hr                  = NOERROR;

    DEBUGPUBLIC("HrOpenImport()\n");

    hr = CHK_HrOpenImport(
        pszImportFile, 
        pszObjectClass, 
        pszSourceStamp, 
        pszBasePoint, 
        pszContainer, 
        pszHomeServer);
    if (FAILED(hr))
        RETURN(hr);

    lstrcpy(szImportFile, pszImportFile);
    lstrcpy(szObjectClass, pszObjectClass);
    lstrcpy(szSourceStamp, pszSourceStamp);
    lstrcpy(szBasePoint, pszBasePoint);
    lstrcpy(szContainer, pszContainer);
    lstrcpy(szHomeServer, pszHomeServer);
    strcpy(szRawDN, "");

    hImportFile = fopen(szImportFile, "r");
    if (hImportFile == NULL)
    {
        EventLogMsg(
            DIRSYNC_CANNOT_OPEN_IMPORT_FILE, 
            1, szImportFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    fImportLineSaved = FALSE;
    nImportLineNumber = 0;

cleanup:
    RETURN(hr);
}



//$--HrReadImport---------------------------------------------------------------
//  Function to import a single record for directory synchronization.  It is 
//  called repeatedly: once for each record to be imported.  If this function 
//  returns an error it will not be called again, and HrCloseImport() will be 
//  called once to clean everything up.
//
//  When there are no more records to import, HrReadImport should return 
//  EDK_E_END_OF_FILE.
// -----------------------------------------------------------------------------
HRESULT HrReadImport(                       // RETURNS: HRESULT
    OUT LPDIR_SYNC_OPERATION peOperation,   // type of operation
    OUT PDAPI_ENTRY *   ppAttributes,       // list of attribute names
    OUT PDAPI_ENTRY *   ppValues)           // list of attribute values
{
    HRESULT             hr                  = NOERROR;
    PDAPI_ENTRY         pAttributes         = NULL;
    PDAPI_ENTRY         pValues             = NULL;
    DIR_SYNC_OPERATION  eOperation          = 0;

    DEBUGPUBLIC("HrReadImport()\n");

    hr = CHK_HrReadImport(
        peOperation, 
        ppAttributes, 
        ppValues);
    if (FAILED(hr))
        RETURN(hr);

    // Loop until we create a valid record or a fatal error.

    while (TRUE)
    {
        // Free any old attribute name and value structures that 
        // may be around from a previous failed attempt.

        MAPIFREEBUFFER(pAttributes);
        MAPIFREEBUFFER(pValues);

        // Create new attribute name and value structures.

        hr = HrCreateDAPIEntry(&pAttributes);
        if (FAILED(hr))
            goto cleanup;

        hr = HrCreateDAPIEntry(&pValues);
        if (FAILED(hr))
            goto cleanup;

        // Add the Obj-Class attribute to the list (this must be first!).

        hr = HrAddAttributeToList(
            OBJ_CLASS, 
            szObjectClass, 
            DUPLICATE_ALLOW, 
            pAttributes, 
            pValues);
        if (FAILED(hr))
            goto cleanup;

        // Read the first line of the record.

        hr = HrReadImportRecordHeader(
            szBasePoint, 
            szContainer, 
            pAttributes, 
            pValues, 
            &eOperation);
        if (FAILED(hr))
        {
            // If it was just a parsing error (i.e. an invalid line) 
            // then skip to the next record header and try again.

            if (hr == EDK_E_PARSE)
            {
                hr = HrSkipToNextRecordHeader();
                if (FAILED(hr))
                    goto cleanup;
                continue;
            }

            goto cleanup;
        }

        // Read the other lines in this record.

        hr = HrReadImportDataLines(pAttributes, pValues);
        if (FAILED(hr))
        {
            // If it was just a parsing error (i.e. an invalid line) 
            // then skip to the next record header and try again.

            if (hr == EDK_E_PARSE)
            {
                hr = HrSkipToNextRecordHeader();
                if (FAILED(hr))
                    goto cleanup;
                continue;
            }

            goto cleanup;
        }

        // Add the Imported-From source stamp.

        hr = HrAddAttributeToList(
            IMPORTED_FROM, 
            szSourceStamp, 
            DUPLICATE_REPLACE, 
            pAttributes, 
            pValues);
        if (FAILED(hr))
            goto cleanup;

        // Succeeded, so exit the loop.

        break;
    }

cleanup:
    if (FAILED(hr))
    {
        MAPIFREEBUFFER(pAttributes);
        MAPIFREEBUFFER(pValues);
    }
    else
    {
        *peOperation = eOperation;
        *ppAttributes = pAttributes;
        *ppValues = pValues;
    }

    RETURN(hr);
}



//$--HrCloseImport--------------------------------------------------------------
//  Function to do whatever cleanup needs to be done after importing records 
//  for directory synchronization.
// -----------------------------------------------------------------------------
HRESULT HrCloseImport(void)                 // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    DWORD               i                   = 0;

    DEBUGPUBLIC("HrCloseImport()\n");

    // Close the import file.

    if (fclose(hImportFile) == EOF)
    {
        EventLogMsg(
            DIRSYNC_CANNOT_CLOSE_IMPORT_FILE, 
            1, szImportFile, 
            1, _doserrno);
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

cleanup:
    RETURN(hr);
}



//
// Local Routines
//



//$--HrCreateDAPIEntry----------------------------------------------------------
//  Create a DAPI_ENTRY structure with an allocated array of ATT_VALUE 
//  structures attached to it.  The number of ATT_VALUE's is determined 
//  by the static variable cDAPIArrayElements.  Initially, the unAttributes 
//  member of the DAPI_ENTRY structure is 0, and this will be incremented 
//  each time one of the elements of the array of ATT_VALUE's is actually 
//  used.
// -----------------------------------------------------------------------------
static HRESULT HrCreateDAPIEntry(           // RETURNS: HRESULT
    OUT PDAPI_ENTRY * ppDAPIEntry)          // DAPI_ENTRY structure created
{
    HRESULT             hr                  = NOERROR;
    PDAPI_ENTRY         pDAPIEntry          = NULL;

    DEBUGPRIVATE("HrCreateDAPIEntry()\n");

    hr = CHK_HrCreateDAPIEntry(
        ppDAPIEntry);
    if (FAILED(hr))
        RETURN(hr);

    hr = MAPIAllocateBuffer(sizeof(DAPI_ENTRY), &pDAPIEntry);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_ERROR, 
            0, 
            1, ERROR_OUTOFMEMORY);
        goto cleanup;
    }
    ZeroMemory(pDAPIEntry, sizeof(DAPI_ENTRY));

    pDAPIEntry->unAttributes = 0;
    pDAPIEntry->ulEvalTag = TEXT_VALUE_ARRAY;

    hr = MAPIAllocateMore(
        cDAPIArrayElements * sizeof(ATT_VALUE), 
        pDAPIEntry, 
        &pDAPIEntry->rgEntryValues);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_ERROR, 
            0, 
            1, ERROR_OUTOFMEMORY);
        goto cleanup;
    }
    ZeroMemory(
        pDAPIEntry->rgEntryValues, 
        cDAPIArrayElements * sizeof(ATT_VALUE));

cleanup:
    if (FAILED(hr))
    {
        MAPIFREEBUFFER(pDAPIEntry);
    }
    else
    {
        *ppDAPIEntry = pDAPIEntry;
    }

    RETURN(hr);
}



//$--HrReadImportRecordHeader---------------------------------------------------
//  Reads the first line of a record from the import file and adds its data 
//  to the attribute name and attribute value arrays.  Also updates the global 
//  variable szRawDN for use in error event logging if there is a parsing error.
//
//  RETURN:         NOERROR =       operation was successful
//                  EDK_E_PARSE =   error but continue parsing at next record
//                  other error =   fatal error that makes it impossible to 
//                                  continue parsing the file
// -----------------------------------------------------------------------------
static HRESULT HrReadImportRecordHeader(    // RETURNS: HRESULT
    IN      LPTSTR pszBasePoint,            // default base point
    IN      LPTSTR pszContainer,            // default container
    IN OUT  PDAPI_ENTRY pAttributes,        // attribute name structure
    IN OUT  PDAPI_ENTRY pValues,            // attribute value structure
    OUT     LPDIR_SYNC_OPERATION peOperation) // operation type
{
    HRESULT             hr                  = NOERROR;
    char                chOperation         = 0;
    int                 cMatch              = 0;
    CHAR                szNormalizedDN[MAX_IMPORT_LINE] = {0};
    DIR_SYNC_OPERATION  eOperation          = 0;

    hr = CHK_HrReadImportRecordHeader(
        pszBasePoint, 
        pszContainer, 
        pAttributes, 
        pValues, 
        peOperation);
    if (FAILED(hr))
        RETURN(hr);

    DEBUGPRIVATE("HrReadImportRecordHeader()\n");

    // Clear the raw DN.

    szRawDN[0] = 0;

    // Get the next line (should be the first line of a record).

    hr = HrReadImportLine();
    if (FAILED(hr))
        goto cleanup;

    // Parse it to get the operation type and the distinguished name.

    cMatch = sscanf(szImportLine, " %c %[^\n]", &chOperation, szRawDN);
    if (cMatch != 2)
    {
        szRawDN[0] = 0;
        EventLogMsg(
            DIRSYNC_INVALID_IMPORT_LINE, 
            4, szImportFile, _itoa(nImportLineNumber,szTemp1,10), szRawDN, 
                szImportLine, 
            0);
        hr = HR_LOG(EDK_E_PARSE);
        goto cleanup;
    }

    switch (toupper(chOperation))
    {
        case 'A':
        case 'a':
            eOperation = OPERATION_ADD;
            break;

        case 'M':
        case 'm':
            eOperation = OPERATION_MODIFY;
            break;

        case 'D':   
        case 'd':   
            eOperation = OPERATION_DELETE;
            break;

        default:
            szRawDN[0] = 0;
            EventLogMsg(
                DIRSYNC_INVALID_IMPORT_LINE, 
                4, szImportFile, _itoa(nImportLineNumber,szTemp1,10), szRawDN, 
                    szImportLine, 
                0);
            hr = HR_LOG(EDK_E_PARSE);
            goto cleanup;
    }

    if (*szRawDN == 0)
    {
        EventLogMsg(
            DIRSYNC_INVALID_IMPORT_LINE, 
            4, szImportFile, _itoa(nImportLineNumber,szTemp1,10), szRawDN, 
                szImportLine, 
            0);
        hr = HR_LOG(EDK_E_PARSE);
        goto cleanup;
    }

    // If the DN starts with "/o" then don't change it.

    if (!_strnicmp(szRawDN, "/o", 2))
    {
        strcpy(szNormalizedDN, szRawDN);
    }

    // Otherwise, normalize the DN (make sure it has /o= /ou= /cn=).

    else
    {
        // Start with "/o=<enterprise>/ou=<site>"...

        strcpy(szNormalizedDN, pszBasePoint);

        // ...[add "/cn=<container>"]...

        if (*pszContainer)
        {
            if (*pszContainer != '/')
            {
                strcat(szNormalizedDN, "/cn=");
            }
            strcat(szNormalizedDN, pszContainer);
        }

        // ...add the DN.

        if (*szRawDN != '/')
        {
            strcat(szNormalizedDN, "/cn=");
        }
        strcat(szNormalizedDN, szRawDN);
    }

    // Add the distinguished name to the list as Common-Name.

    hr = HrAddAttributeToList(
        COMMON_NAME, 
        szNormalizedDN, 
        DUPLICATE_ALLOW, 
        pAttributes, 
        pValues);
    if (FAILED(hr))
        goto cleanup;

    *peOperation = eOperation;

cleanup:
    RETURN(hr);
}



//$--HrReadImportDataLines------------------------------------------------------
//  Read the remaining data lines following the header into the attribute 
//  name and attribute value arrays.
//
//  RETURN:         NOERROR =       operation was successful
//                  EDK_E_PARSE =   error but continue parsing at next record
//                  other error =   fatal error that makes it impossible to 
//                                  continue parsing the file
// -----------------------------------------------------------------------------
static HRESULT HrReadImportDataLines(       // RETURNS: HRESULT
    IN OUT  PDAPI_ENTRY pAttributes,        // list of attribute names
    IN OUT  PDAPI_ENTRY pValues)            // list of attribute values
{
    HRESULT             hr                  = NOERROR;
    int                 cMatch              = 0;
    char                ch                  = 0;
    ULONG               ulDuplicateAction   = DUPLICATE_ALLOW;

    CHAR                szAttributeName[MAX_IMPORT_LINE] = {0};
    CHAR                szAttributeValue[MAX_IMPORT_LINE] = {0};
    CHAR                szCurrentObjectClass[MAX_IMPORT_LINE] = {0};

    DEBUGPRIVATE("HrReadImportDataLines()\n");

    hr = CHK_HrReadImportDataLines(
        pAttributes, 
        pValues);
    if (FAILED(hr))
        RETURN(hr);

    // Make a copy of the current object class.

    strcpy(szCurrentObjectClass, szObjectClass);

    // Loop until end of file or a line that doesn't start with '-'.

    while (TRUE)
    {
        // Reset the action to perform on duplicate attribute names 
        // (default is not to check for duplicates).

        ulDuplicateAction = DUPLICATE_ALLOW;

        // Get a line from the file.

        hr = HrReadImportLine();
        if (hr == EDK_E_END_OF_FILE)
        {
            hr = NOERROR;
            break;
        }
        if (FAILED(hr))
            goto cleanup;

        // If the line doesn't start with '-' then "unget" the line 
        // and we're done.

        cMatch = sscanf(szImportLine, " %c", &ch);
        if (cMatch != 1 || ch != '-')
        {
            fImportLineSaved = TRUE;
            break;
        }

        // Try to match the line to a normal property template.

        cMatch = sscanf(
            szImportLine, 
            " - %[-a-zA-Z] :%[^\n]", 
            szAttributeName, 
            szAttributeValue);

        // If there was only 1 match, then check for the special case 
        // where the attribute value is an empty string.

        if (cMatch == 1)
        {
            cMatch = sscanf(
                szImportLine, 
                " - %[-a-zA-Z] %[^\n]", 
                szAttributeName, 
                szAttributeValue);

            if (cMatch == 2 && !strcmp(szAttributeValue, ":"))
                szAttributeValue[0] = 0;
            else
                cMatch = 1;
        }

        // If that didn't work, try to match it to a multi-valued 
        // property template.

        if (cMatch != 2)
        {
            cMatch = sscanf(
                szImportLine, 
                " - %[-a-zA-Z] [ %*d ] :%[^\n]", 
                szAttributeName, 
                szAttributeValue);

            // If there was only 1 match, then check for the special case 
            // where the attribute value is an empty string.

            if (cMatch == 1)
            {
                cMatch = sscanf(
                    szImportLine, 
                    " - %[-a-zA-Z] [ %*d ] %[^\n]", 
                    szAttributeName, 
                    szAttributeValue);

                if (cMatch == 2 && !strcmp(szAttributeValue, ":"))
                    szAttributeValue[0] = 0;
                else
                    cMatch = 1;
            }

            // If we couldn't match it as either a normal property 
            // template or a multi-valued property template, then 
            // it's an error.

            if (cMatch != 2)
            {
                EventLogMsg(
                    DIRSYNC_INVALID_IMPORT_LINE, 
                    4, szImportFile, _itoa(nImportLineNumber,szTemp1,10), 
                        szRawDN, szImportLine, 
                    0);
                hr = HR_LOG(EDK_E_PARSE);
                goto cleanup;
            }

            ulDuplicateAction = DUPLICATE_MULTI_VALUED;
        }

        // If it's "Obj-Class", then replace the original one and store 
        // away the new value.

        if (!_stricmp(szAttributeName, OBJ_CLASS))
        {
            ulDuplicateAction = DUPLICATE_REPLACE;

            strcpy(szCurrentObjectClass, szAttributeValue);
            hr = HrStripWhiteSpace(szCurrentObjectClass);
            if (FAILED(hr))
                goto cleanup;
        }

        // Otherwise, if it's "Common-Name", then that's an error because they 
        // already specified "Common-Name" in the first line of the record.

        else if (!_stricmp(szAttributeName, COMMON_NAME))
        {
            EventLogMsg(
                DIRSYNC_CANNOT_IMPORT_COMMON_NAME, 
                3, szImportFile, _itoa(nImportLineNumber,szTemp1,10), 
                    szImportLine, 
                0);
            hr = HR_LOG(EDK_E_PARSE);
            goto cleanup;
        }

        // Add the attribute name and value to the list.

        hr = HrAddAttributeToList(
            szAttributeName, 
            szAttributeValue, 
            ulDuplicateAction, 
            pAttributes, 
            pValues);
        if (FAILED(hr))
            goto cleanup;
    }

    // If the object class is "Mailbox" then add the "Home-Server" attribute, 
    // unless the user already specified one.

    if (*szHomeServer && 
        !_stricmp(szCurrentObjectClass, OBJECT_CLASS_MAILBOX))
    {
        hr = HrAddAttributeToList(
            HOME_SERVER, 
            szHomeServer, 
            DUPLICATE_DISCARD, 
            pAttributes, 
            pValues);
        if (FAILED(hr))
            goto cleanup;
    }

cleanup:
    RETURN(hr);
}



//$--HrStripWhiteSpace----------------------------------------------------------
//  Strip white space from a string.
// -----------------------------------------------------------------------------
static HRESULT HrStripWhiteSpace(           // RETURNS: HRESULT
    IN OUT  LPTSTR pszString)               // string to strip white space from
{
    HRESULT             hr                  = NOERROR;
    LPTSTR              pszSrc              = pszString;
    LPTSTR              pszDst              = pszString;

    DEBUGPRIVATE("HrStripWhiteSpace()\n");

    hr = CHK_HrStripWhiteSpace(
        pszString);
    if (FAILED(hr))
        RETURN(hr);

    while (*pszSrc)
    {
        if (isspace(*pszSrc))
            pszSrc++;
        else
            *pszDst++ = *pszSrc++;
    }
    *pszDst = 0;

    RETURN(hr);
}



//$--HrSkipToNextRecordHeader---------------------------------------------------
//  Skip forward in the file to the next line that looks like a record 
//  header (i.e. begins with A|M|D).  After this routine is called, the 
//  next call to HrReadImportLine will return the record header.
//  This is used to resynchronize the input following a parsing error.
// -----------------------------------------------------------------------------
static HRESULT HrSkipToNextRecordHeader(void) // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    int                 ch                  = 0;
    int                 cMatch              = 0;

    DEBUGPRIVATE("HrSkipToNextRecordHeader()\n");

    // Loop to skip lines that aren't record headers.

    do
    {
        hr = HrReadImportLine();
        if (FAILED(hr))
            goto cleanup;

        cMatch = sscanf(szImportLine, " %c", &ch);
        ch = toupper(ch);
    }
    while (cMatch != 1 || (ch != 'A' && ch != 'M' && ch != 'D'));

    // "Unget" the line.

    fImportLineSaved = TRUE;

cleanup:
    RETURN(hr);
}



//$--HrReadImportLine-----------------------------------------------------------
//  Read a line from the import file into the static variables
//  szImportLine and cchImportLine.  Setting fImportLineSaved == TRUE 
//  acts as an "unget", and causes the current contents of szImportLine 
//  to be used the next time this routine is called.
//
//  HrReadImportLine automatically skips empty lines, or those that begin 
//  with '#', signifying a comment.
//
//  Returns:    NOERROR             = success
//              EDK_E_END_OF_FILE   = end of file
//              E_FAIL              = error
// -----------------------------------------------------------------------------
static HRESULT HrReadImportLine(void)       // RETURNS: HRESULT
{
    HRESULT             hr                  = NOERROR;
    int                 ch                  = 0;
    int                 cMatch              = 0;
    char *              pszResult           = NULL;

    DEBUGPRIVATE("HrReadImportLine()\n");

    // Loop until we get a line we can use.

    do
    {
        // If we have a line saved from last time then just use that one.

        if (fImportLineSaved)
            fImportLineSaved = FALSE;

        // Otherwise read another line from the file.

        else
        {
            pszResult = 
                fgets(szImportLine, sizeof(szImportLine) - 1, hImportFile);
            if (pszResult == NULL)
            {
                if (ferror(hImportFile))
                {
                    EventLogMsg(
                        DIRSYNC_CANNOT_READ_IMPORT_FILE, 
                        1, szImportFile, 
                        1, _doserrno);
                    hr = HR_LOG(E_FAIL);
                }
                else
                {
                    hr = EDK_E_END_OF_FILE;
                }

                goto cleanup;
            }

            // Increment the line number.

            nImportLineNumber++;

            // Strip newline from end of line.

            cchImportLine = strlen(szImportLine);
            if (cchImportLine && szImportLine[cchImportLine - 1] == '\n')
                szImportLine[cchImportLine - 1] = 0;
            else
            {
                EventLogMsg(
                    DIRSYNC_IMPORT_LINE_TOO_LONG, 
                    3, szImportFile, _itoa(nImportLineNumber,szTemp1,10), 
                        szImportLine, 
                    0);
                hr = HR_LOG(E_FAIL);
                goto cleanup;
            }
        }

        // Get the first non-whitespace character in the line so we 
        // can make sure it exists and isn't a comment character ('#')

        cMatch = sscanf(szImportLine, " %c", &ch);
    }
    while (cMatch != 1 || ch == '#');

cleanup:
    RETURN(hr);
}



//$-HrAddAttributeToList--------------------------------------------------------
//  Adds an attribute name and value to the attribute name and attribute 
//  value arrays.
// -----------------------------------------------------------------------------
static HRESULT HrAddAttributeToList(        // RETURNS: HRESULT
    IN      LPSTR       pszAttribute,       // name of attribute to add
    IN      LPSTR       pszValue,           // value of attribute to add
    IN      ULONG       ulDuplicateAction,  // action if property already in list
    IN OUT  PDAPI_ENTRY pAttributes,        // list of attribute names
    IN OUT  PDAPI_ENTRY pValues)            // list of attribute values
{
    HRESULT             hr                  = NOERROR;
    BOOL                fIsDuplicate        = FALSE;
    int                 iDuplicate          = 0;
    PATT_VALUE          pavAttribute        = NULL;
    PATT_VALUE          pavValue            = NULL;

    DEBUGPRIVATE("HrAddAttributeToList()\n");

    hr = CHK_HrAddAttributeToList(
        pszAttribute, 
        pszValue, 
        ulDuplicateAction, 
        pAttributes, 
        pValues);
    if (FAILED(hr))
        RETURN(hr);

    // Check for duplicate attributes unless they are allowed.

    if (ulDuplicateAction != DUPLICATE_ALLOW)
    {
        // Search backwards because duplicate names for multi-valued 
        // attributes are likely to be grouped together in the file.

        for (
            iDuplicate = pAttributes->unAttributes - 1; 
            iDuplicate >= 0; 
            iDuplicate--)
        {
            if (!_stricmp(
                pAttributes->rgEntryValues[iDuplicate].Value.pszA, 
                pszAttribute))
            {
                fIsDuplicate = TRUE;
                break;
            }
        }
    }

    // Handle duplicates here.

    if (fIsDuplicate)
    {
        switch (ulDuplicateAction)
        {
            // Discard duplicate -- don't change anything.

            case DUPLICATE_DISCARD:
                pavAttribute = NULL;
                pavValue = NULL;
                break;

            // Replace duplicate -- no need to re-create the name but 
            // overwrite the present value in the array.

            case DUPLICATE_REPLACE:
                pavAttribute = NULL;
                pavValue = &pValues->rgEntryValues[iDuplicate];
                break;

            // Make duplicate multi-valued part of original -- no need 
            // to re-create the name but allocate a new value structure 
            // and link it into the original.

            case DUPLICATE_MULTI_VALUED:
                pavAttribute = NULL;
                hr = MAPIAllocateMore(
                    sizeof(ATT_VALUE), 
                    pValues, 
                    &pavValue);
                if (FAILED(hr))
                {
                    EventLogMsg(
                        DIRSYNC_ERROR, 
                        0, 
                        1, ERROR_OUTOFMEMORY);
                    goto cleanup;
                }

                pavValue->pNextValue = 
                    pValues->rgEntryValues[iDuplicate].pNextValue;
                pValues->rgEntryValues[iDuplicate].pNextValue = pavValue;
                break;

            // Fail on duplicates -- error.

            case DUPLICATE_FAIL:
                EventLogMsg(
                    DIRSYNC_DUPLICATE_IMPORT_ATTRIBUTE, 
                    3, pszAttribute, szImportFile, 
                        _itoa(nImportLineNumber,szTemp1,10), szImportLine, 
                    0);
                hr = HR_LOG(E_FAIL);
                goto cleanup;

            // Invalid parameter.

            default:
                EventLogMsg(
                    DIRSYNC_INTERNAL_ERROR, 
                    0, 
                    0);
                hr = HR_LOG(E_FAIL);
                goto cleanup;
        }
    }

    // Handle non-duplicates here.

    else
    {
        // Not a duplicate -- add both name and value to the end of 
        // their respective arrays.

        // If we've run out of space in the arrays then expand them.

        if (pAttributes->unAttributes >= cDAPIArrayElements)
        {
            cDAPIArrayElements += DAPI_ARRAY_ALLOCATION_GROWTH;

            hr = HrExpandDAPIEntry(pAttributes);
            if (FAILED(hr))
                goto cleanup;

            hr = HrExpandDAPIEntry(pValues);
            if (FAILED(hr))
                goto cleanup;
        }

        pavAttribute = &pAttributes->rgEntryValues[pAttributes->unAttributes++];
        pavValue = &pValues->rgEntryValues[pValues->unAttributes++];
    }

    // Fill in the attribute name structure.

    if (pavAttribute)
    {
        ZeroMemory(pavAttribute, sizeof(ATT_VALUE));
        pavAttribute->DapiType = DAPI_STRING8;
        pavAttribute->size = strlen(pszAttribute);
        hr = MAPIAllocateMore(
            pavAttribute->size + 1, 
            pAttributes, 
            &pavAttribute->Value.pszA);
        if (FAILED(hr))
        {
            EventLogMsg(
                DIRSYNC_ERROR, 
                0, 
                1, ERROR_OUTOFMEMORY);
            goto cleanup;
        }
        strcpy(pavAttribute->Value.pszA, pszAttribute);
    }

    // Fill in the attribute value structure.

    if (pavValue)
    {
        ZeroMemory(pavValue, sizeof(ATT_VALUE));
        pavValue->DapiType = DAPI_STRING8;
        pavValue->size = strlen(pszValue);
        hr = MAPIAllocateMore(
            pavValue->size + 1, 
            pValues, 
            &pavValue->Value.pszA);
        if (FAILED(hr))
        {
            EventLogMsg(
                DIRSYNC_ERROR, 
                0, 
                1, ERROR_OUTOFMEMORY);
            goto cleanup;
        }
        strcpy(pavValue->Value.pszA, pszValue);
    }

cleanup:
    RETURN(hr);
}



//$--HrExpandDAPIEntry----------------------------------------------------------
//  Re-allocates a DAPI_ENTRY structure with a larger array.
// -----------------------------------------------------------------------------
static HRESULT HrExpandDAPIEntry(           // RETURNS: HRESULT
    IN OUT  PDAPI_ENTRY pDAPIEntry)         // DAPI_ENTRY structure
{
    HRESULT             hr                  = NOERROR;
    PATT_VALUE          pavNewBuffer        = NULL;

    DEBUGPRIVATE("HrExpandDAPIEntry()\n");

    hr = CHK_HrExpandDAPIEntry(
        pDAPIEntry);
    if (FAILED(hr))
        RETURN(hr);

    // Allocate the new (bigger) buffer.

    hr = MAPIAllocateMore(
        cDAPIArrayElements * sizeof(ATT_VALUE), 
        pDAPIEntry, 
        &pavNewBuffer);
    if (FAILED(hr))
    {
        EventLogMsg(
            DIRSYNC_ERROR, 
            0, 
            1, ERROR_OUTOFMEMORY);
        goto cleanup;
    }
    ZeroMemory(
        pavNewBuffer, 
        cDAPIArrayElements * sizeof(ATT_VALUE));

    // Copy the old buffer to the new one.

    CopyMemory(
        pavNewBuffer, 
        pDAPIEntry->rgEntryValues, 
        pDAPIEntry->unAttributes * sizeof(ATT_VALUE));

    // Point the header to the new buffer.  (It's OK to leave the 
    // old one dangling--it was allocated with MAPIAllocateMore, 
    // and will be freed along with the header).

    pDAPIEntry->rgEntryValues = pavNewBuffer;

cleanup:
    RETURN(hr);
}
