// --exchinst.c-----------------------------------------------------------------
//
// Functions for installing Exchange objects.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "dapi.h"

#include "exchinst.chk"

//
// Miscellaneous Defines
//

#define MAX_CSV_LINE_SIZ                2048
#define MAX_WORD                        0xFFFF
#define FILE_PREFIX                     "EXCH"
#define NEW_LINE                        "\r\n"

#define EXCHINST_DELIM                  '\t'
#define EXCHINST_QUOTE                  '"'
#define EXCHINST_MV_SEP                 '%'

#define SZ_EXCHINST_DELIM               "\t"
#define SZ_EXCHINST_QUOTE               "\""
#define SZ_EXCHINST_MV_SEP              "%"

#define BEGIN_CSV_LINE(a,b)  lstrcpy(a, b)

#define APPEND_CSV_LINE(a,b)           \
    {                                  \
	lstrcat(a, SZ_EXCHINST_DELIM); \
	lstrcat(a, b);                 \
    }

#define DELETEFILE(_file)                       \
{                                               \
    if((_file) != NULL && (_file)[0] != 0)      \
    {                                           \
	if(! DeleteFile ((_file)))              \
	{                                       \
	    HRESULT _hr = HR_LOG(E_FAIL);       \
	}                                       \
    }                                           \
    (_file)[0] = 0;                             \
}

//
// Attribute Defines
//

#define OBJ_CLASS                       "Obj-Class"
#define MODE                            "Mode"
#define ADDR_SYNTAX                     "Address-Syntax"
#define ADDR_ENTRY_DT                   "Address-Entry-Display-Table"
#define ADDR_TYPE                       "Address-Type"
#define ADMIN_DISPLAY_NAME              "Admin-Display-Name"
#define DISPLAY_NAME                    "Display-Name"
#define COMMON_NAME                     "Common-Name"
#define DELIVERY_MECHANISM              "Delivery-Mechanism"
#define DELIV_EXT_CONT_TYPES            "Deliv-Ext-Cont-Types"
#define EXTENSION_DATA                  "Extension-Data"
#define EXTENSION_NAME                  "Extension-Name"
#define HELP_FILE_NAME                  "Help-File-Name"
#define COMPUTER_NAME                   "Computer-Name"
#define GATEWAY_PROXY                   "Gateway-Proxy"
#define HOME_SERVER                     "Home-Server"
#define FILE_VERSION                    "File-Version"
#define PER_MSG_DDT                     "Per-Msg-Dialog-Display-Table"
#define PER_RECIP_DDT                   "Per-Recip-Dialog-Display-Table"
#define PROXY_GENERATOR_DLL             "Proxy-Generator-DLL"
#define ROUTING_LIST                    "Routing-List"
#define OBJ_DIST_NAME                   "Obj-Dist-Name"
#define ORGANIZATION                    "Organization"
#define ORGANIZATIONAL_UNIT             "Organizational-Unit"
#define CONTAINER                       "Container"
#define HELP_DATA16                     "Help-Data16"
#define HELP_DATA32                     "Help-Data32"
#define OBJ_ADMIN                       "Obj-Admins"
#define SITE_ADDRESSING                 "Site-Addressing"
#define ADMIN_EXTENSION_DLL             "Admin-Extension-Dll"
#define CAN_PRESERVE_DNS                "Can-Preserve-DNs"
#define HEURISTICS                      "Heuristics"
#define CONTAINER_INFO                  "Container-Info"

//
// Attribute Value Defines
//

#define OBJ_CLASS_GW                    "Mail-Gateway"
#define OBJ_CLASS_MB                    "Mailbox-Agent"
#define OBJ_CLASS_SITE                  "Site-Addressing"
#define OBJ_CLASS_ADDR_TYPE             "Addr-Type"
#define OBJ_CLASS_ADDR_TEMPLATE         "Address-Template"
#define OBJ_CLASS_ADMIN_EXTENSION       "Admin-Extension"
#define OBJ_CLASS_COMPUTER              "Computer"
#define OBJ_CLASS_CONTAINER             "Container"

//
// Container Information Defines
//

#define ADDRESS_TEMPLATE_CONTAINER_INFO "256"

//
// Import Mode Defines
//

#define MODE_CREATE                                             "Create"
#define MODE_MODIFY                                             "Modify"
#define MODE_DELETE                                             "Delete"

#define DELIVERY_MECHANISM_GW                   "2"
#define DELIVERY_MECHANISM_MB                   "0"

#define CONTAINER_CONFIGURATION         "/cn=Configuration"
#define CONTAINER_GW                    "/cn=Configuration/cn=Connections"
#define CONTAINER_ADDR_TYPE             "/cn=Configuration/cn=Addressing/cn=Address-Types"
#define CONTAINER_ADDR_TEMPLATE         "/cn=Configuration/cn=Addressing/cn=Address-Templates"
#define CONTAINER_SERVERS               "/cn=Configuration/cn=Servers"
#define CONTAINER_SITE_ADDR             "/cn=Configuration/cn=Site-Addressing"
#define CONTAINER_ADD_INS               "/cn=Configuration/cn=Add-Ins"

#define ACCOUNT_NAME                    "Obj-Users"

//
//  Common macros.
//

#define CREATEKEY(hkParent, pszName, hkOut, dwDisposition) \
    RegCreateKeyEx(hkParent, pszName, 0, "", REG_OPTION_NON_VOLATILE, \
	KEY_ALL_ACCESS, NULL, &hkOut, &dwDisposition)

#define SETSZVALUE(hk, pszName, pszValue) \
    RegSetValueEx(hk, pszName, 0, REG_SZ, pszValue, lstrlen(pszValue)+1)

#define SETMULTISZVALUE(hk, pszName, pszValue) \
    RegSetValueEx(hk, pszName, 0, REG_MULTI_SZ, pszValue, \
	CbMultiSz(pszValue)+sizeof(CHAR))

#define FREEHKEY(hk) \
    if(hk != INVALID_HANDLE_VALUE) \
	RegCloseKey(hk);

static CHAR szExport[]          = "Export";

static CHAR szNull[]            = "(null)";

static CHAR szNullDisplayName[] = "No Display Name!";

//$--CbMultiSz------------------------------------------------------------------
//  Count of bytes in a REG_MULTI_SZ string (not including terminating NULL).
// -----------------------------------------------------------------------------
static DWORD CbMultiSz(                 // RETURNS: count of bytes
    IN LPSTR lpszRegMultiSz)           // REG_MULTI_SZ string
{
    HRESULT hr   = NOERROR;
    DWORD   cch  = 0;
    DWORD   cb   = 0;
    LPSTR  lpsz = NULL;

    DEBUGPRIVATE("CbMultiSz()");

    hr = CHK_HrMultiSz(lpszRegMultiSz);
    if(FAILED(hr))
	return(0);

    if(lpszRegMultiSz == NULL)
    {
	goto cleanup;
    }

    lpsz = lpszRegMultiSz;

    while(*lpsz)
    {
	cch = lstrlen(lpsz);

	cch++;

	cb  += cch * sizeof(CHAR);

	lpsz += cch;
    }

cleanup:

    return(cb);
}

//$--HrGetRegistryValue---------------------------------------------------------
//  Get a registry value - allocating memory to hold it.
// -----------------------------------------------------------------------------
static HRESULT HrGetRegistryValue(  // RETURNS: return code
    IN  HKEY hk,                    // the key.
    IN  LPSTR lpszValue,           // value name in key.
    OUT DWORD * lpType,             // where to put type info.
    OUT DWORD * lpcb,               // where to put byte count info.
    OUT LPVOID * lppData)           // where to put the data.
{
    HRESULT hr   = E_FAIL;
    LONG    lRet = 0;

    DEBUGPRIVATE("HrGetRegistryValue()\n");

    hr = CHK_HrGetRegistryValue(
	hk,
	lpszValue,
	lpType,
	lpcb,
	lppData);
    if(FAILED(hr))
	RETURN(hr);

    *lppData = NULL;

    //
    //  Get its size
    //

    lRet = RegQueryValueEx(
	hk,
	lpszValue,
	NULL,
	lpType,
	NULL,
	lpcb);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Allocate memory for it
    //

    *lppData = (LPVOID)GlobalAlloc(GMEM_FIXED, *lpcb);

    if(*lppData == NULL)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    //
    // Get the current value
    //

    lRet = RegQueryValueEx(hk, lpszValue, NULL, lpType, *lppData, lpcb);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    hr = NOERROR;

cleanup:

    if(FAILED(hr))
    {
	if(lppData != NULL)
	{
	    GLOBALFREE(*lppData);
	}
    }

    RETURN(hr);
}

//$--FCsvGetField---------------------------------------------------------------
// Given a record and a field separator and a field number, this routine 
// will extract the field requested.
//------------------------------------------------------------------------------
static BOOL FCsvGetField(       // RETURNS: TRUE/FALSE
    IN  WORD wLen,              // maximum length of the field to extract
    IN  WORD wFieldNum,         // field number we want from the record
    IN  CHAR cFieldSeparator,  // character to use as a field separator
    IN  CHAR *lpszRecord,      // record to extract the field from
    OUT CHAR *lpszField)       // field we have extracted
{
    HRESULT hr              = NOERROR;
    BOOL    fRet            = FALSE;
    CHAR   *lpszBeginField = lpszField;

    DEBUGPRIVATE("FCsvGetField()");

    hr = CHK_HrCsvGetField(
	wLen,
	wFieldNum,
	cFieldSeparator,
	lpszRecord,
	lpszField);
    if(FAILED(hr))
	return(FALSE);

    while((wFieldNum > 0) && (*lpszRecord != 0))
    {
	// If we found a field separator, increment current field
	if(*lpszRecord == cFieldSeparator)
	{
	    wFieldNum--;
	}
	// If we are at the desired field, copy the current character into it
	else if(wFieldNum == 1 && wLen > 1)
	{
	    *lpszField = *lpszRecord;
	    lpszField++;
	    wLen--;
	}

	lpszRecord++;
    }

    *lpszField = 0;

    // If the requested field # existed, return True,
    // otherwise we ran out of fields - return False

    if(wFieldNum <= 1)
    {
	fRet = TRUE;
    }
    else
    {
	fRet = FALSE;
    }

    return(fRet);
}

//$--FCsvGetRecord--------------------------------------------------------------
// Given a buffer, the buffer's length and a file handle, this
// function fills the buffer with a single line read from the file. 
// The NL & CR are NOT put into the buffer. No unprintable characters are
// placed in the buffer
// -----------------------------------------------------------------------------
BOOL FCsvGetRecord(                 // RETURNS: TRUE/FALSE
    IN  WORD wBufferLen,            // length of the record buffer
    IN  HANDLE hFile,               // file handle to read from
    OUT CHAR *lpszBuffer)          // record we have retrieved
{
    HRESULT hr          = NOERROR;
    DWORD   dwBytesRead = 0;
    BOOL    fReadData   = FALSE;

    DEBUGPRIVATE("FCsvGetRecord()");

    hr = CHK_HrCsvGetRecord(
	wBufferLen,
	hFile,
	lpszBuffer);
    if(FAILED(hr))
	return(FALSE);

    while((ReadFile(hFile, (LPVOID)lpszBuffer, 1, &dwBytesRead, NULL) == TRUE) &&
	  (wBufferLen > 1) && (*lpszBuffer != '\n') && (dwBytesRead > 0))
    {
	fReadData = TRUE;

	// Only store character in buffer if it is printable!

	if((isprint(*lpszBuffer)) || (*lpszBuffer == EXCHINST_DELIM))
	{
	    lpszBuffer++;
	    wBufferLen--;
	}
    }

    // If a given record is too long it is a problem!!!

    if(wBufferLen <= 0)
    {
	fReadData = FALSE;
    }

    *lpszBuffer = 0;

    return(fReadData);
}

//$--HrEDKExportObject----------------------------------------------------------
// This function will export an object from an Exchange server.
// -----------------------------------------------------------------------------
static HRESULT HrEDKExportObject(       // RETURNS: return code
    IN  LPSTR lpszServer,              // server name
    IN  LPSTR lpszBasePoint,           // base point
    IN  DWORD dwControlFlags,           // control flags
    IN  LPSTR *rgpszClasses,           // classes
    IN  LPSTR lpszObjectAttributes,    // list of attributes to export
    OUT LPSTR lpszTempName)            // temporary file name
{
    HRESULT       hr                     = E_FAIL;
    ULONG         cErrors                = 0;
    HANDLE        hTempFile              = INVALID_HANDLE_VALUE;
    CHAR          szTempPath[MAX_PATH+1] = {0};
    DWORD         dwNumberOfBytesWritten = 0;
    BEXPORT_PARMS BExportParms           = {0};
    BOOL          fRet                   = FALSE;

    DEBUGPRIVATE("HrEDKExportObject()");

    hr = CHK_HrEDKExportObject(
	lpszServer,
	lpszBasePoint,
	dwControlFlags,
	rgpszClasses,
	lpszObjectAttributes,
	lpszTempName);
    if(FAILED(hr))
	RETURN(hr);

    // Get temporary directory path

    if(!GetTempPath(MAX_PATH, szTempPath))
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Get temporary file name

    if(!GetTempFileName(szTempPath, FILE_PREFIX, 0, lpszTempName))
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Create the temporary file
    hTempFile = CreateFile(lpszTempName,
	GENERIC_WRITE,
	0,
	(LPSECURITY_ATTRIBUTES)NULL,
	CREATE_ALWAYS,
	FILE_ATTRIBUTE_NORMAL,
	(HANDLE)NULL);

    // Check to see if temporary file was created...

    if(hTempFile == INVALID_HANDLE_VALUE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Write data to the temporary file & close it

    fRet = WriteFile(
	hTempFile,
	lpszObjectAttributes,
	lstrlen(lpszObjectAttributes)*sizeof(CHAR),
	&dwNumberOfBytesWritten,
	NULL);

    if(fRet == FALSE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }


    fRet = WriteFile(
	hTempFile,
	NEW_LINE,
	lstrlen(NEW_LINE)*sizeof(CHAR),
	&dwNumberOfBytesWritten,
	NULL);

    if(fRet == FALSE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    CLOSEHANDLE(hTempFile);

    //
    // Batch Export
    //

    BExportParms.dwDAPISignature = DAPI_SIGNATURE;
    BExportParms.dwFlags         = dwControlFlags | 
				   DAPI_MODIFY_REPLACE_PROPERTIES | 
				   DAPI_SUPPRESS_PROGRESS | 
				   DAPI_SUPPRESS_COMPLETION | 
                   DAPI_SUPPRESS_ARCHIVES | 
                   DAPI_IMPORT_NO_ERR_FILE;
    BExportParms.pszExportFile   = lpszTempName;
    BExportParms.pszBasePoint    = lpszBasePoint;
    BExportParms.pszDSAName      = lpszServer;
    BExportParms.rgpszClasses    = rgpszClasses;
    BExportParms.chColSep        = EXCHINST_DELIM;
    BExportParms.chQuote         = EXCHINST_QUOTE;
    BExportParms.chMVSep         = EXCHINST_MV_SEP;

    cErrors = BatchExport(&BExportParms);

    if(cErrors == 0)
    {
	hr = NOERROR;
    }
    else
    {
	hr = HR_LOG(E_FAIL);
    }
    
cleanup:

    CLOSEHANDLE(hTempFile);

    RETURN(hr);
}

//$--HrEDKImportObject----------------------------------------------------------
// This function will import an object into an Exchange server.
// -----------------------------------------------------------------------------
static HRESULT HrEDKImportObject (      // RETURNS: return code
    IN  LPSTR lpszServer,              // server name
    IN  LPSTR lpszBasePoint,           // base point
    IN  LPSTR lpszObjectAttributes,    // list of attributes to import
    IN  LPSTR lpszAttributeValues)     // list of attributes values to import
{
    HRESULT       hr                     = E_FAIL;
    ULONG         cErrors                = 0;
    HANDLE        hTempFile              = INVALID_HANDLE_VALUE;
    CHAR         szTempName[MAX_PATH+1] = {0};
    CHAR         szTempPath[MAX_PATH+1] = {0};
    DWORD         cBytes                 = 0;
    BIMPORT_PARMS BImportParms           = {0};
    BOOL          fRet                   = FALSE;

    DEBUGPRIVATE("HrEDKImportObject()");

    hr = CHK_HrEDKImportObject(
	lpszServer,
	lpszBasePoint,
	lpszObjectAttributes,
	lpszAttributeValues);
    if(FAILED(hr))
	RETURN(hr);

    // Get temporary directory path

    if(!GetTempPath(MAX_PATH, szTempPath))
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Get temporary file name

    if(!GetTempFileName(szTempPath, FILE_PREFIX, 0, szTempName))
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Create the temporary file

    hTempFile = CreateFile(szTempName,
	GENERIC_WRITE,
	0,
	(LPSECURITY_ATTRIBUTES)NULL,
	CREATE_ALWAYS,
	FILE_ATTRIBUTE_NORMAL,
	(HANDLE)NULL);

    // Check to see if temporary file was created

    if(hTempFile == INVALID_HANDLE_VALUE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Write data to the temporary file & close it

    fRet = WriteFile(
	hTempFile,
	lpszObjectAttributes,
	lstrlen(lpszObjectAttributes)*sizeof(CHAR),
	&cBytes,
	NULL);

    if(fRet == FALSE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    fRet = WriteFile(
	hTempFile,
	NEW_LINE,
	lstrlen(NEW_LINE)*sizeof(CHAR),
	&cBytes,
	NULL);

    if(fRet == FALSE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    fRet = WriteFile(
	hTempFile,
	lpszAttributeValues,
	lstrlen(lpszAttributeValues)*sizeof(CHAR),
	&cBytes,
	NULL);

    if(fRet == FALSE)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    CLOSEHANDLE(hTempFile);

    //
    // Batch Import
    //

    BImportParms.dwDAPISignature = DAPI_SIGNATURE;
    BImportParms.dwFlags         = DAPI_RESTRICT_ACCESS | 
				   DAPI_SUPPRESS_PROGRESS |
                   DAPI_MODIFY_REPLACE_PROPERTIES |
				   DAPI_YES_TO_ALL |
				   DAPI_EVENT_ALL |
				   DAPI_SUPPRESS_COMPLETION | 
                   DAPI_SUPPRESS_ARCHIVES | 
                   DAPI_IMPORT_NO_ERR_FILE;
    BImportParms.pszImportFile   = szTempName;
    BImportParms.pszBasePoint    = lpszBasePoint;
    BImportParms.pszDSAName      = lpszServer;
    BImportParms.chColSep        = EXCHINST_DELIM;
    BImportParms.chQuote         = EXCHINST_QUOTE;
    BImportParms.chMVSep         = EXCHINST_MV_SEP;

    cErrors = BatchImport(&BImportParms);

    if(cErrors == 0)
    {
	hr = NOERROR;
    }
    else
    {
	hr = HR_LOG(E_FAIL);
    }
    
cleanup:

    CLOSEHANDLE(hTempFile);
    DELETEFILE(szTempName);

    RETURN(hr);
}

//$--HrDeleteObject----------------------------------------------------------
//  Deletes an object from an Exchange server
// -----------------------------------------------------------------------------
static HRESULT HrDeleteObject(   // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszBasepoint,        // base point
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszObjClass)         // object class
{
    HRESULT hr                                   = NOERROR;
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues [MAX_CSV_LINE_SIZ] = {0};

    DEBUGPRIVATE("HrDeleteObject()");

    hr = CHK_HrDeleteObject(
	lpszServer,
	lpszBasepoint,
	lpszCommonName,
	lpszObjClass);
    if(FAILED(hr))
	RETURN(hr);

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , lpszObjClass);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_DELETE);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszCommonName);

    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	lpszBasepoint,
	szObjectAttributes,
	szAttributeValues));

    RETURN(hr);
}

//$--HrEDKObjectExists----------------------------------------------------------
//  Checks if an object exists in the directory.
// -----------------------------------------------------------------------------
static HRESULT HrEDKObjectExists(   // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszBasePoint,        // base point
    IN LPSTR lpszObjClass,         // object class
    IN LPSTR lpszCommonName)       // common name
{
    HRESULT hr                                   = NOERROR;
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues [MAX_CSV_LINE_SIZ] = {0};

    DEBUGPRIVATE("HrEDKObjectExists()");

    hr = CHK_HrEDKObjectExists(
	lpszServer,
	lpszBasePoint,
	lpszCommonName);
    if(FAILED(hr))
	RETURN(hr);

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , lpszObjClass);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_MODIFY);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszCommonName);

    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	lpszBasePoint,
	szObjectAttributes,
	szAttributeValues));

    RETURN(hr);
}

//$--HrEDKEnumAttrib------------------------------------------------------------
//  Enumerates the given attribute.
// -----------------------------------------------------------------------------
static HRESULT HrEDKEnumAttrib(          // RETURNS: return code
    IN  LPSTR lpszRootDN,               // distinguished name of DIT root
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR *rgpszClasses,            // classes
    IN  LPSTR lpszAttribName,           // attribute name
    OUT LPSTR *lppszAttribValues)       // attribute values
{
    HRESULT hr                                   = NOERROR;
    HANDLE  hTempFile                            = INVALID_HANDLE_VALUE;
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCurRecord[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szCurLine[MAX_CSV_LINE_SIZ]          = {0};
    CHAR   szCurField[MAX_PATH+1]               = {0};
    CHAR   szTempName[MAX_PATH+1]               = {0};
    WORD    wAttribField                         = MAX_WORD;
    WORD    wCurrField                           = 0;
    LPSTR  lpsz                                 = NULL;
    LPSTR  lpszCurrAttrib                       = NULL;

    DEBUGPRIVATE("HrEDKEnumAttrib()");

    hr = CHK_HrEDKEnumAttrib(
	lpszRootDN,
	lpszServer,
	rgpszClasses,
	lpszAttribName,
	lppszAttribValues);
    if(FAILED(hr))
	RETURN(hr);

    *lppszAttribValues = NULL;

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    APPEND_CSV_LINE (szObjectAttributes, lpszAttribName);

    hr = HrEDKExportObject(
	lpszServer,
	lpszRootDN,
	DAPI_EXPORT_BASEPOINT_ONLY,
	rgpszClasses,
	szObjectAttributes,
	szTempName);

    if(SUCCEEDED(hr))
    {
	// Open the temporary file
	hTempFile = CreateFile (
	    szTempName,
	    GENERIC_READ,
	    0,
	    (LPSECURITY_ATTRIBUTES)NULL,
	    OPEN_EXISTING,
	    FILE_FLAG_DELETE_ON_CLOSE,
	    (HANDLE)NULL);

	if(hTempFile == INVALID_HANDLE_VALUE)
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	//
	// The first line contains the list of fields - find which field has
	// the attribute we are looking for.
	//

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	for(
	    wCurrField = 1;

	    FCsvGetField(
		MAX_PATH,
		wCurrField,
		EXCHINST_DELIM,
		szCurLine,
		szCurField);

	    wCurrField++)
	{
	    if(strcmp(szCurField, lpszAttribName) == 0) 
	    {
		wAttribField = wCurrField;
		break;
	    }
	}

	// Was the field exported & found above?

	if(wAttribField == MAX_WORD) 
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}


	while( FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine))
	{
	    FCsvGetField(
		MAX_CSV_LINE_SIZ,
		wAttribField,
		EXCHINST_DELIM,
		szCurLine,
		szCurRecord);

	    if( *szCurRecord)
	    {
		lpsz = (LPSTR)GlobalAlloc(
		    GMEM_FIXED,
		    cbStrLen(szCurRecord) + sizeof(CHAR));

		if(lpsz == NULL)
		{
		    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
		    goto cleanup;
		}

		lpszCurrAttrib = lpsz;

		for(
		    wCurrField = 1;

		    FCsvGetField(
			MAX_PATH,
			wCurrField,
			EXCHINST_MV_SEP,
			szCurRecord,
			szCurField);

		    wCurrField++)
		{
		    lstrcpy(lpszCurrAttrib, szCurField);

		    lpszCurrAttrib += cbStrLen(lpszCurrAttrib);
		}

		*lpszCurrAttrib = 0;
		break;  // single record only
	    }
	}
    }

    *lppszAttribValues = lpsz;

cleanup:

    CLOSEHANDLE(hTempFile);

    if(FAILED(hr))
    {
	GLOBALFREE(*lppszAttribValues);
    }

    RETURN(hr);
}

//$--HrEDKEnumDNs---------------------------------------------------------------
//  Enumerates the distinguished name(s).
// -----------------------------------------------------------------------------
static HRESULT HrEDKEnumDNs(             // RETURNS: return code
    IN  LPSTR lpszRootDN,               // distinguished name of DIT root
    IN  LPSTR lpszServer,               // server name
    IN  DWORD  dwControlFlags,           // control flags
    IN  LPSTR *rgpszClasses,            // classes
    OUT LPSTR *lppszDNs)                // distinguished names
{
    HRESULT hr                                   = NOERROR;
    HANDLE  hTempFile                            = INVALID_HANDLE_VALUE;
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCurRecord[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szCurLine[MAX_CSV_LINE_SIZ]          = {0};
    CHAR   szCurField[MAX_PATH+1]               = {0};
    CHAR   szTempName[MAX_PATH+1]               = {0};
    WORD    wAttribField                         = MAX_WORD;
    WORD    wCurrField                           = 0;
    LPSTR  lpsz                                 = NULL;
    ULONG   ulCurrOffset                         = 0;

    DEBUGPRIVATE("HrEDKEnumDNs()");

    hr = CHK_HrEDKEnumDNs(
	lpszRootDN,
	lpszServer,
	dwControlFlags,
	rgpszClasses,
	lppszDNs);
    if(FAILED(hr))
	RETURN(hr);

    *lppszDNs = NULL;

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    APPEND_CSV_LINE (szObjectAttributes, OBJ_DIST_NAME);

    hr = HrEDKExportObject(
	lpszServer,
	lpszRootDN,
	dwControlFlags,
	rgpszClasses,
	szObjectAttributes,
	szTempName);

    if(SUCCEEDED(hr))
    {
	// Open the temporary file
	hTempFile = CreateFile (
	    szTempName,
	    GENERIC_READ,
	    0,
	    (LPSECURITY_ATTRIBUTES)NULL,
	    OPEN_EXISTING,
	    FILE_FLAG_DELETE_ON_CLOSE,
	    (HANDLE)NULL);

	if(hTempFile == INVALID_HANDLE_VALUE)
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	//
	// The first line contains the list of fields - find which field has
	// the attribute we are looking for.
	//

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	for(
	    wCurrField = 1;

	    FCsvGetField(
		MAX_PATH,
		wCurrField,
		EXCHINST_DELIM,
		szCurLine,
		szCurField);

	    wCurrField++)
	{
	    if(strcmp(szCurField, OBJ_DIST_NAME) == 0) 
	    {
		wAttribField = wCurrField;
		break;
	    }
	}

	// Was the field exported & found above?

	if(wAttribField == MAX_WORD) 
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	ulCurrOffset = 0;

	while(FCsvGetRecord (MAX_CSV_LINE_SIZ, hTempFile, szCurLine))
	{
	    FCsvGetField(
		MAX_PATH,
		wAttribField,
		EXCHINST_DELIM,
		szCurLine,
		szCurField);

	    if( *szCurField)
	    {
		if(lpsz == NULL)
		{
		    lpsz = (LPSTR)GlobalAlloc(
			GMEM_FIXED,
			cbStrLen(szCurField) + sizeof(CHAR));
		}
		else
		{
		    lpsz = (LPSTR)GlobalReAlloc(
			lpsz,
			GlobalSize(lpsz) + cbStrLen(szCurField),
			GMEM_MOVEABLE);
		}

		if(lpsz == NULL)
		{
		    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
		    goto cleanup;
		}

		lstrcpy(&lpsz[ulCurrOffset], szCurField);

		ulCurrOffset += cbStrLen(szCurField);

		lpsz[ulCurrOffset] = 0;
	    }
	}
    }
    
    *lppszDNs = lpsz;

cleanup:

    CLOSEHANDLE(hTempFile);

    if(FAILED(hr))
    {
	GLOBALFREE(*lppszDNs);
    }

    RETURN(hr);
}

//$--HrEnumOrganizations-----------------------------------------------------
//  Enumerates the organization name(s).
// -----------------------------------------------------------------------------
HRESULT HrEnumOrganizations(          // RETURNS: return code
    IN  LPSTR lpszRootDN,               // distinguished name of DIT root
    IN  LPSTR lpszServer,               // server name
    OUT LPSTR *lppszOrganizations)      // organizations
{
    HRESULT hr              = NOERROR;
    LPSTR  rgpszClasses[2] = {0};

    DEBUGPUBLIC("HrEnumOrganizations()");

    hr = CHK_HrEnumOrganizations(
	lpszRootDN,
	lpszServer,
	lppszOrganizations);
    if(FAILED(hr))
	RETURN(hr);

    rgpszClasses[0] = ORGANIZATION;
    rgpszClasses[1] = NULL;

    hr = HrEDKEnumDNs(
	lpszRootDN,
	lpszServer,
	DAPI_EXPORT_SUBTREE,
	rgpszClasses,
	lppszOrganizations);

    RETURN(hr);
}

//$--HrEnumSites-------------------------------------------------------------
//  Enumerates the site name(s).
// -----------------------------------------------------------------------------
HRESULT HrEnumSites(                  // RETURNS: return code
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR lpszOrganizationDN,       // distinguished name of organization
    OUT LPSTR *lppszSites)              // sites
{
    HRESULT hr              = NOERROR;
    LPSTR  rgpszClasses[2] = {0};

    DEBUGPUBLIC("HrEnumSites()");

    hr = CHK_HrEnumSites(
	lpszServer,
	lpszOrganizationDN,
	lppszSites);
    if(FAILED(hr))
	RETURN(hr);

    rgpszClasses[0] = ORGANIZATIONAL_UNIT;
    rgpszClasses[1] = NULL;

    hr = HrEDKEnumDNs(
	lpszOrganizationDN,
	lpszServer,
	0,
	rgpszClasses,
	lppszSites);

    RETURN(hr);
}

//$--HrEnumContainers--------------------------------------------------------
//  Enumerates the container name(s).
// -----------------------------------------------------------------------------
HRESULT HrEnumContainers(             // RETURNS: return code
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR lpszSiteDN,               // distinguished name of site
    IN  BOOL   fSubtree,                 // sub-tree?
    OUT LPSTR *lppszContainers)         // containers
{
    HRESULT hr              = NOERROR;
    LPSTR  rgpszClasses[2] = {0};
    DWORD   dwControlFlags  = 0;

    DEBUGPUBLIC("HrEnumContainers()");

    hr = CHK_HrEnumContainers(
	lpszServer,
	lpszSiteDN,
	fSubtree,
	lppszContainers);
    if(FAILED(hr))
	RETURN(hr);

    rgpszClasses[0] = CONTAINER;
    rgpszClasses[1] = NULL;

    if(fSubtree == TRUE)
    {
	dwControlFlags = DAPI_EXPORT_SUBTREE;
    }

    hr = HrEDKEnumDNs(
	lpszSiteDN,
	lpszServer,
	dwControlFlags,
	rgpszClasses,
	lppszContainers);

    RETURN(hr);
}

//$--HrEnumSiteAdmins--------------------------------------------------------
//  Enumerates the administrators for a given site.
// -----------------------------------------------------------------------------
HRESULT HrEnumSiteAdmins(             // RETURNS: return code
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR lpszSiteDN,               // distinguished name of site
    OUT LPSTR *lppszAdmins)             // administrator accounts
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrEnumSiteAdmins()");

    hr = CHK_HrEnumSiteAdmins(
	lpszServer,
	lpszSiteDN,
	lppszAdmins);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrEDKEnumAttrib(
	lpszSiteDN,
	lpszServer,
	NULL,
	OBJ_ADMIN,
	lppszAdmins);

    RETURN(hr);
}

//$--HrEnumProductServices---------------------------------------------------
//  Enumerates the services for a product.
// -----------------------------------------------------------------------------
HRESULT HrEnumProductServices(        // RETURNS: return code
    IN  LPSTR lpszProductGuid,          // product GUID
    OUT LPSTR *lppszServices,           // service names
    OUT LPSTR *lppszDisplayNames)       // service display names
{
    HRESULT   hr                        = NOERROR;
    LONG      lRet                      = 0;
    HKEY      hkServices                = INVALID_HANDLE_VALUE;
    HKEY      hKey                      = INVALID_HANDLE_VALUE;
    SC_HANDLE schSCManager              = NULL; 
    SC_HANDLE schService                = NULL;
    DWORD     dwType                    = 0;
    DWORD     cbGuid                    = 0;
    LPSTR    lpszGuid                  = NULL;
    DWORD     cbName                    = 0;
    LPSTR    lpszName                  = NULL;

    CHAR     szServiceName[MAX_PATH+1] = {0};
    LPSTR    lpszServices              = NULL;
    LPSTR    lpszDisplayNames          = NULL;
    FILETIME  ftLastWrite               = {0};
    DWORD     dwBufferSize              = 0;
    DWORD     iSubKey                   = 0;
    ULONG     ulServOffset              = 0;
    ULONG     ulDispOffset              = 0;
    CHAR     szSubKey[MAX_PATH+1]      = {0};
    LONG      cBytes                    = 0;

    DEBUGPUBLIC("HrEnumProductServices()");

    hr = CHK_HrEnumProductServices(
	lpszProductGuid,
	lppszServices,
	lppszDisplayNames);
    if(FAILED(hr))
	RETURN(hr);

    *lppszServices = NULL;
    *lppszDisplayNames = NULL;

    //
    //  Connect to service control manager.
    //

    schSCManager = OpenSCManager(
	NULL,                       // machine (NULL == local)
	NULL,                       // database (NULL == default)
	SC_MANAGER_ALL_ACCESS);     // access required

    if(schSCManager == NULL)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    //
    //  Open the services key.
    //

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	"SYSTEM\\CurrentControlSet\\Services", 
	0,
	KEY_ALL_ACCESS,
	&hkServices);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    ulServOffset = 0;
    ulDispOffset = 0;

    for(;;)
    {
	if(lpszGuid != szNull)
	{
	    GLOBALFREE(lpszGuid);
	}

	if(lpszName != szNullDisplayName)
	{
	    GLOBALFREE(lpszName);
	}

	dwBufferSize = MAX_PATH+1;
		
	lRet = RegEnumKeyEx(
	    hkServices,
	    iSubKey,
	    szServiceName,
	    &dwBufferSize,
	    NULL,
	    NULL,
	    NULL,
	    &ftLastWrite);      

	iSubKey++;

	if(lRet == ERROR_NO_MORE_ITEMS)
	{
	    break;
	}

	//
	//  Open the service "Parameters" key.
	//

	cBytes = _snprintf(
	    szSubKey,
	    MAX_PATH+1,
	    "%s\\Parameters",
	    szServiceName);

	if(cBytes < 0)
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	lRet = RegOpenKeyEx(
	    hkServices,
	    szSubKey, 
	    0,
	    KEY_ALL_ACCESS,
	    &hKey);

	if(lRet != ERROR_SUCCESS)
	{
	    continue;
	}

	//
	//  Get the current value.
	//

	hr = HrGetRegistryValue(
	    hKey,
	    "ProductGUID",
	    &dwType,
	    &cbGuid,
	    &lpszGuid);

	FREEHKEY(hKey);

	if(FAILED(hr) || dwType != REG_SZ)
	{
	    continue;
	}

	if(lpszGuid == NULL)
	{
	    lpszGuid = szNull;
	}

	//
	//  Open the service key.
	//

	cBytes = _snprintf(
	    szSubKey,
	    MAX_PATH+1,
	    "%s",
	    szServiceName);

	if(cBytes < 0)
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	lRet = RegOpenKeyEx(
	    hkServices,
	    szSubKey, 
	    0,
	    KEY_ALL_ACCESS,
	    &hKey);

	if(lRet != ERROR_SUCCESS)
	{
	    continue;
	}

	//
	//  Get the current value.
	//

	hr = HrGetRegistryValue(
	    hKey,
	    "DisplayName",
	    &dwType,
	    &cbName,
	    &lpszName);

	FREEHKEY(hKey);

	if(FAILED(hr) || dwType != REG_SZ)
	{
	    lpszName = szNullDisplayName;
	}

	if(lpszName == NULL)
	{
	    lpszName = szNullDisplayName;
	}

	if(!lstrcmpi(lpszProductGuid, lpszGuid))
	{
	    //
	    // Add the service name to the list.
	    //

	    if(lpszServices == NULL)
	    {
		cBytes = cbStrLen(szServiceName) + sizeof(CHAR);

		lpszServices = (LPSTR)GlobalAlloc(
		    GMEM_FIXED,
		    cBytes);
	    }
	    else
	    {
		LPSTR lpszT = NULL;

		cBytes = GlobalSize(lpszServices) +
			 cbStrLen(szServiceName) +
			 sizeof(CHAR);

		lpszT = (LPSTR)GlobalReAlloc(
		    lpszServices,
		    cBytes,
		    GMEM_MOVEABLE);

		if(lpszT != NULL)
		{
		    lpszServices = lpszT;
		}
	    }

	    if(lpszServices == NULL)
	    {
		hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
		goto cleanup;
	    }

	    lstrcpy(&lpszServices[ulServOffset], szServiceName);

	    ulServOffset += lstrlen(szServiceName);
	    lpszServices[ulServOffset] = 0;

	    ulServOffset ++;
	    lpszServices[ulServOffset] = 0;

	    //
	    // Add the service display name to the list.
	    //

	    if(lpszDisplayNames == NULL)
	    {
		cBytes = cbStrLen(lpszName) + sizeof(CHAR);

		lpszDisplayNames = (LPSTR)GlobalAlloc(
		    GMEM_FIXED,
		    cBytes);
	    }
	    else
	    {
		LPSTR lpszT = NULL;

		cBytes = GlobalSize(lpszDisplayNames) +
			 cbStrLen(lpszName) +
			 sizeof(CHAR);

		lpszT = (LPSTR)GlobalReAlloc(
		    lpszDisplayNames,
		    cBytes,
		    GMEM_MOVEABLE);

		if(lpszT != NULL)
		{
		    lpszDisplayNames = lpszT;
		}
	    }

	    if(lpszDisplayNames == NULL)
	    {
		hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
		goto cleanup;
	    }

	    lstrcpy(&lpszDisplayNames[ulDispOffset], lpszName);

	    ulDispOffset += lstrlen(lpszName);
	    lpszDisplayNames[ulDispOffset] = 0;

	    ulDispOffset ++;
	    lpszDisplayNames[ulDispOffset] = 0;
	}

	if(lpszGuid != szNull)
	{
	    GLOBALFREE(lpszGuid);
	}

	if(lpszName != szNullDisplayName)
	{
	    GLOBALFREE(lpszName);
	}
    }

    *lppszServices = lpszServices;
    *lppszDisplayNames = lpszDisplayNames;

    hr = NOERROR;

cleanup:

    FREEHSCM(schService);
    FREEHSCM(schSCManager);

    FREEHKEY(hkServices);
    FREEHKEY(hKey);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    if(lpszGuid != szNull)
    {
	GLOBALFREE(lpszGuid);
    }


    if(lpszName != szNull)
    {
	GLOBALFREE(lpszName);
    }

    if(FAILED(hr))
    {
	GLOBALFREE(*lppszServices);
	GLOBALFREE(*lppszDisplayNames);
    }

    RETURN(hr);
}

//$--HrInstallService--------------------------------------------------------
//  Installs a service associated with an Exchange object.
// -----------------------------------------------------------------------------
HRESULT HrInstallService(            // RETURNS: return code
    IN LPSTR  lpszServer,              // server name
    IN LPSTR  lpszSiteDN,              // distinguished name of site
    IN LPSTR  lpszServiceDisplayName,  // service display name
    IN LPSTR  lpszServiceName,         // service name
    IN LPSTR  lpszCommonName,          // object relative distinguished name
    IN LPSTR  lpszObjectGuid,          // object GUID
    IN LPSTR  lpszProductGuid,         // product GUID
    IN LPSTR  lpszExeName,             // executable name
    IN LPCSTR lpszDependencies,        // dependencies
    IN LPSTR  lpszAccount,             // account
    IN LPSTR  lpszPassword)            // password
{
    HRESULT   hr                 = NOERROR;
    LONG      lRet               = 0;
    HKEY      hkServices         = INVALID_HANDLE_VALUE;
    HKEY      hkObject           = INVALID_HANDLE_VALUE;
    HKEY      hkTmp              = INVALID_HANDLE_VALUE;
    DWORD     dwDisposition      = 0;
    BOOL      bObjectKeyCreated  = FALSE;
    SC_HANDLE schSCManager       = NULL; 
    SC_HANDLE schService         = NULL;

    DEBUGPUBLIC("HrInstallService()");

    hr = CHK_HrInstallService(
	lpszServer,
	lpszSiteDN,
	lpszServiceDisplayName,
	lpszServiceName,
	lpszCommonName,
	lpszObjectGuid,
	lpszProductGuid,
	lpszExeName,
	lpszDependencies,
	lpszAccount,
	lpszPassword);
    if(FAILED(hr))
	RETURN(hr);

    //
    //  Connect to service control manager.
    //

    schSCManager = OpenSCManager(
	NULL,                       // machine (NULL == local)
	NULL,                       // database (NULL == default)
	SC_MANAGER_ALL_ACCESS);     // access required

    if(schSCManager == NULL)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    //
    //  Create the service.
    //

    schService = CreateService(
	schSCManager,               // SCManager database
	lpszServiceName,            // service name
	lpszServiceDisplayName,     // service display name
	SERVICE_ALL_ACCESS,         // desired access
	SERVICE_WIN32_OWN_PROCESS,  // service type
	SERVICE_DEMAND_START,       // start type
	SERVICE_ERROR_NORMAL,       // error control type
	lpszExeName,                // service's binary
	NULL,                       // no load ordering group
	NULL,                       // no tag identifier
	lpszDependencies,           // dependencies
	lpszAccount,                // account
	lpszPassword);              // password

    if(schService == NULL)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    //
    //  Open the services key.
    //

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	"SYSTEM\\CurrentControlSet\\Services", 
	0,
	KEY_ALL_ACCESS,
	&hkServices);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Create the object key.
    //

    lRet = CREATEKEY(hkServices, lpszServiceName, hkObject, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    bObjectKeyCreated = TRUE;

    //
    // Create Parameters key.
    //

    lRet = CREATEKEY(hkObject, "Parameters", hkTmp, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    // Create new values under Parameters key

    lRet = SETSZVALUE(hkTmp, "HomeDSA", lpszServer);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkTmp, "SiteDN", lpszSiteDN);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkTmp, "CommonName", lpszCommonName);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkTmp, "ObjectGUID", lpszObjectGuid);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkTmp, "ProductGUID", lpszProductGuid);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

cleanup:

    FREEHSCM(schService);
    FREEHSCM(schSCManager);

    FREEHKEY(hkServices);
    FREEHKEY(hkObject);
    FREEHKEY(hkTmp);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrGetRegistryString-----------------------------------------------------
//  Get a string value from the registry.
// -----------------------------------------------------------------------------
static HRESULT HrGetRegistryString(  // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    IN  LPSTR  lpszServicePath,        // service path
    IN  LPSTR  lpszValueName,          // registry value name
    IN  DWORD   dwExpectedType,         // expected registry data type
    OUT LPSTR  *lppszString)           // string
{
    HRESULT hr                           = NOERROR;
    LONG    lRet                         = 0;
	DWORD   dwType                       = 0;
	DWORD   cbOrig                       = 0;
	CHAR    szKey[MAX_PATH+1]            = {0};
	HKEY    hKey                         = INVALID_HANDLE_VALUE;

    DEBUGPUBLIC("HrGetRegistryString()");

    hr = CHK_HrGetRegistryString(
	lpszServiceName,
	lpszServicePath,
	lpszValueName,
	dwExpectedType,
	lppszString);
    if(FAILED(hr))
	RETURN(hr);

    //
    //  Open the key.
    //

	lRet = _snprintf(
	    szKey,
	MAX_PATH+1,
	    lpszServicePath,
	    lpszServiceName);

    if(lRet < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	szKey, 
	0,
	KEY_ALL_ACCESS,
	&hKey);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    hr = HrGetRegistryValue(
	hKey, lpszValueName, &dwType, &cbOrig, (LPVOID)lppszString);

    if(FAILED(hr) || dwType != dwExpectedType)
    {
	if(dwType != dwExpectedType)
	    hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

cleanup:

	FREEHKEY(hKey);

    if(FAILED(hr))
    {
	GLOBALFREE(*lppszString);
    }

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrGetServiceServerName--------------------------------------------------
//  Get the Exchange server name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceServerName(      // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszServerName)       // server name
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceServerName()");

    hr = CHK_HrGetServiceServerName(
	lpszServiceName,
	lppszServerName);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	"HomeDSA",
	REG_SZ,
	lppszServerName);

    RETURN(hr);
}

//$--HrGetServiceSiteDN------------------------------------------------------
//  Get the site DN of the Exchange object associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceSiteDN(          // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszSiteDN)           // site distinguished name
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceSiteDN()");

    hr = CHK_HrGetServiceSiteDN(
	lpszServiceName,
	lppszSiteDN);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	"SiteDN",
	REG_SZ,
	lppszSiteDN);

    RETURN(hr);
}

//$--HrGetServiceCommonName--------------------------------------------------
//  Get the common name of the Exchange object associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceCommonName(      // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszCommonName)       // object relative distinguished name
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceCommonName()");

    hr = CHK_HrGetServiceCommonName(
	lpszServiceName,
	lppszCommonName);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	"CommonName",
	REG_SZ,
	lppszCommonName);

    RETURN(hr);
}

//$--HrGetServiceObjectGUID--------------------------------------------------
//  Get the object GUID associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceObjectGUID(      // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszObjectGUID)       // object GUID
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceObjectGUID()");

    hr = CHK_HrGetServiceObjectGUID(
	lpszServiceName,
	lppszObjectGUID);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	"ObjectGUID",
	REG_SZ,
	lppszObjectGUID);

    RETURN(hr);
}

//$--HrGetServiceProductGUID-------------------------------------------------
//  Get the product GUID associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceProductGUID(     // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszProductGUID)      // product GUID
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceProductGUID()");

    hr = CHK_HrGetServiceProductGUID(
	lpszServiceName,
	lppszProductGUID);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters",
	"ProductGUID",
	REG_SZ,
	lppszProductGUID);

    RETURN(hr);
}

//$--HrGetServiceDisplayName-------------------------------------------------
//  Get the display name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceDisplayName(     // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszDisplayName)      // display name
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceDisplayName()");

    hr = CHK_HrGetServiceDisplayName(
	lpszServiceName,
	lppszDisplayName);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s",
	"DisplayName",
	REG_SZ,
	lppszDisplayName);

    RETURN(hr);
}

//$--HrGetServiceExecutableName----------------------------------------------
//  Get the executable name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceExecutableName(  // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszExecutableName)   // executable name
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceExecutableName()");

    hr = CHK_HrGetServiceExecutableName(
	lpszServiceName,
	lppszExecutableName);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s",
	"ImagePath",
	REG_EXPAND_SZ,
	lppszExecutableName);

    RETURN(hr);
}

//$--HrGetServiceAccountName-------------------------------------------------
//  Get the account name associated with the service.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceAccountName(     // RETURNS: return code
    IN  LPSTR  lpszServiceName,        // service name
    OUT LPSTR  *lppszAccountName)      // account name
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrGetServiceAccountName()");

    hr = CHK_HrGetServiceAccountName(
	lpszServiceName,
	lppszAccountName);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrGetRegistryString(
	lpszServiceName,
	"SYSTEM\\CurrentControlSet\\Services\\%s",
	"ObjectName",
	REG_SZ,
	lppszAccountName);

    RETURN(hr);
}

//$--HrRemoveService---------------------------------------------------------
//  Removes a service.
// -----------------------------------------------------------------------------
HRESULT HrRemoveService(             // RETURNS: return code
    IN LPCSTR lpszServiceName)         // service name
{
    HRESULT   hr           = NOERROR;
    SC_HANDLE schService   = NULL;
    SC_HANDLE schSCManager = NULL;
    BOOL      fStatus      = FALSE;

    DEBUGPUBLIC("HrRemoveService()\n");

    hr = CHK_HrRemoveService(
	lpszServiceName);
    if(FAILED(hr))
	RETURN(hr);

    schSCManager = OpenSCManager(
	NULL,
	NULL,
	SC_MANAGER_ALL_ACCESS);

    if(schSCManager == NULL)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    schService = OpenService(schSCManager, lpszServiceName, SERVICE_ALL_ACCESS);

    if(schService == NULL) 
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    fStatus = DeleteService(schService);

    if(fStatus == FALSE) 
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }
    
cleanup:

    FREEHSCM(schService);
    FREEHSCM(schSCManager);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrNameContained------------------------------------------------------------
// Determine if the name is in the list.
// -----------------------------------------------------------------------------
static HRESULT HrNameContained( // RETURNS: return code
    IN LPSTR lpszName,         // name to find
    IN LPSTR lpszList,         // list to search
    IN DWORD cbListLen)         // max length to search
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("HrNameContained()\n");

    hr = CHK_HrNameContained(
	lpszName,
	lpszList,
	cbListLen);
    if(FAILED(hr))
	RETURN(hr);

    hr = EDK_E_NOT_FOUND;

    while(*lpszList)
    {
	// does it match?
	if(!lstrcmpi(lpszName, lpszList))
	{
	    hr = NOERROR;
	    break;
	}

	// go to next element   
	lpszList += sizeof(CHAR)*(1+lstrlen(lpszList));
    }

    RETURN(hr);
}

//$--HrEDKAddServiceToLinkage---------------------------------------------------
//  Add service name to the export value in the key.
// -----------------------------------------------------------------------------
static HRESULT HrEDKAddServiceToLinkage(// RETURNS: return code
    IN HKEY hkLinkage,                  // key containing export list.
    IN LPSTR lpszServiceName)          // service name.
{
    HRESULT hr            = E_FAIL;
    HRESULT hrT           = NOERROR;
    LONG    lRet          = 0;
    DWORD   dwType        = 0;
    DWORD   cbOrig        = 0;
    DWORD   cbServiceName = 0;
    LPBYTE  lpOrig        = NULL;
    LPBYTE  lpRes         = NULL;

    DEBUGPRIVATE("HrEDKAddServiceToLinkage()\n");

    hr = CHK_HrEDKAddServiceToLinkage(
	hkLinkage,
	lpszServiceName);
    if(FAILED(hr))
	RETURN(hr);

    //
    // How big is the current value?
    //

    hrT = HrGetRegistryValue(hkLinkage, szExport, &dwType, &cbOrig, &lpOrig);

    if(SUCCEEDED(hrT))
    {
	ASSERTERROR(lpOrig != NULL, "NULL lpOrig variable");

	// If the name is already there, don't add it again.

	// has value, make sure it is the right type.
	if(dwType != REG_MULTI_SZ)
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	hrT = HrNameContained(lpszServiceName, (LPSTR)lpOrig, cbOrig);

	if(SUCCEEDED(hrT))
	{
	    hr = NOERROR;
	    goto cleanup;
	}
    }
    else
    {
	// Assume that there is no initial value, so leave space
	// for a double-null terminator.
	cbOrig = 1;
    }

    // Allocate space for the result.

    cbServiceName = cbStrLen(lpszServiceName);

    lpRes = GlobalAlloc(GMEM_FIXED, cbServiceName + cbOrig);

    if(lpRes == NULL)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // put out new name in and put in extra null in case orig value was empty
    lstrcpy(lpRes, lpszServiceName);

    // put in the rest of the name if it exists
    if(lpOrig != NULL)
    {
	CopyMemory(((LPSTR)lpRes)+cbServiceName, lpOrig, cbOrig);
    }
    else
    {
	*((LPSTR)(lpRes+cbServiceName)) = 0;
    }

    // Now, write the result.
    lRet = RegSetValueEx(
	hkLinkage,
	szExport,
	0, 
	REG_MULTI_SZ,
	lpRes,
	cbServiceName + cbOrig);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = NOERROR;

cleanup:

    GLOBALFREE(lpOrig);
    GLOBALFREE(lpRes);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrInstallServicePerfMon-------------------------------------------------
//  Installs service performance monitoring.
// -----------------------------------------------------------------------------
HRESULT HrInstallServicePerfMon(         // RETURNS: return code
    IN LPSTR lpszServiceName,              // service name
    IN LPSTR lpszClassName,                // class name
    IN LPSTR lpszLibraryName,              // library name
    IN LPSTR lpszLibraryOpenFunction,      // open function
    IN LPSTR lpszLibraryCollectFunction,   // collect function
    IN LPSTR lpszLibraryCloseFunction)     // close function
{
    HRESULT hr             = E_FAIL;
    LONG    lRet           = 0;

    HKEY    hkServices     = INVALID_HANDLE_VALUE;

    HKEY    hkServiceClass = INVALID_HANDLE_VALUE;
    HKEY    hkLinkage      = INVALID_HANDLE_VALUE;
    HKEY    hkPerformance  = INVALID_HANDLE_VALUE;

    HKEY    hkServiceName  = INVALID_HANDLE_VALUE;
    HKEY    hkLinkage2     = INVALID_HANDLE_VALUE;
    HKEY    hkParameters   = INVALID_HANDLE_VALUE;

    DWORD   dwDisposition  = 0;

    DEBUGPUBLIC("HrInstallServicePerfMon()\n");

    hr = CHK_HrInstallServicePerfMon(
	lpszServiceName,
	lpszClassName,
	lpszLibraryName,
	lpszLibraryOpenFunction,
	lpszLibraryCollectFunction,
	lpszLibraryCloseFunction);
    if(FAILED(hr))
	RETURN(hr);

    //
    //  Open the general services key.
    //

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	"SYSTEM\\CurrentControlSet\\Services", 
	0,
	KEY_ALL_ACCESS,
	&hkServices);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the class key.
    //
    lRet = CREATEKEY(hkServices, lpszClassName, hkServiceClass, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the linkage key
    //
    lRet = CREATEKEY(hkServiceClass, "Linkage", hkLinkage, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the performance key
    //
    lRet = CREATEKEY(hkServiceClass, "Performance", hkPerformance, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    // setup performance data.
    //
    lRet = SETSZVALUE(hkPerformance, "Library", lpszLibraryName);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkPerformance, "Open", lpszLibraryOpenFunction);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkPerformance, "Collect", lpszLibraryCollectFunction);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    lRet = SETSZVALUE(hkPerformance, "Close", lpszLibraryCloseFunction);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    // Link the service name into the Export list.
    //

    hr = HrEDKAddServiceToLinkage(hkLinkage, lpszServiceName);

    if(FAILED(hr))
    {
	goto cleanup;
    }

    //
    //  Open or create the service key.
    //

    lRet = CREATEKEY(hkServices, lpszServiceName, hkServiceName, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the linkage key
    //

    lRet = CREATEKEY(hkServiceName, "Linkage", hkLinkage2, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the performance key
    //

    lRet = CREATEKEY(hkServiceName, "Parameters", hkParameters, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    // Setup parameters data
    //

    lRet = SETSZVALUE(hkParameters, "ObjectClass", lpszClassName);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

cleanup:

    FREEHKEY(hkLinkage);
    FREEHKEY(hkPerformance);
    FREEHKEY(hkServiceClass);

    FREEHKEY(hkLinkage2);
    FREEHKEY(hkParameters);
    FREEHKEY(hkServiceName);

    FREEHKEY(hkServices);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

// $--HrDeleteContainedKeysInternal---------------------------------------------
//  recursive delete keys.  Is passed in lpszwName for storage.
// -----------------------------------------------------------------------------
static HRESULT HrDeleteContainedKeysInternal(   // RETURNS: return code
    IN HKEY hKey,                               // registry key handle
    IN LPWSTR lpszwName)                        // temporary storage
{
#define cchName 255
    HRESULT hr           = NOERROR;
    DWORD   dwEnumResult = !ERROR_NO_MORE_ITEMS;
    HKEY    hSubKey      = NULL;

    DEBUGPRIVATE("HrDeleteContainedKeysInternal()\n");

    hr = CHK_HrDeleteContainedKeysInternal(
	hKey,
	lpszwName);
    if(FAILED(hr))
	RETURN(hr);

    //
    // Enumerate each sub key and delete it recursively. Temporary memory
    // for the sub-key name is allocated and freed before and after the 
    // recursive call but not during to prevent a recursive storage
    // build up.
    //

    do 
    {
	DWORD    dwResult = 0;
	DWORD    cbSubKey = cchName;
	FILETIME ftDummy  = {0};

	//
	// Get the name of the next remaining sub-key.
	//

	dwEnumResult = RegEnumKeyExW(
	    hKey, 0, lpszwName, &cbSubKey, NULL, NULL, NULL, &ftDummy);

	if(dwEnumResult == ERROR_SUCCESS)
	{
	    //
	    // Convert the name of the sub-key into an open handle. 
	    // Dispose of the name.
	    //

	    dwResult = RegOpenKeyExW(
		hKey, lpszwName, 0, KEY_ALL_ACCESS, &hSubKey);

	    if(dwResult == ERROR_SUCCESS)
	    {
		//
		// Recursively call delete with this sub-key handle.
		//

		hr = HrDeleteContainedKeysInternal(hSubKey, lpszwName);

		if(FAILED(hr))
		{
		    goto cleanup;
		}

		FREEHKEY(hSubKey);                  

		//
		// Get the name of the sub-key again
		//

		cbSubKey = cchName;

		dwEnumResult = RegEnumKeyExW(
		    hKey, 0, lpszwName, &cbSubKey, NULL, NULL, NULL, &ftDummy);

		if(dwEnumResult != ERROR_SUCCESS)
		{
		    hr = HR_LOG(HRESULT_FROM_WIN32(dwEnumResult));
		    goto cleanup;    
		}

		dwResult = RegDeleteKeyW(hKey, lpszwName);

		if(dwResult != ERROR_SUCCESS)
		{
		    hr = HR_LOG(HRESULT_FROM_WIN32(dwResult));
		    goto cleanup;    
		}
	    }
	    else
	    {
		hr = HR_LOG(HRESULT_FROM_WIN32(dwResult));
		goto cleanup;    
	    }

	    FREEHKEY(hSubKey);                  
	}
	else if(dwEnumResult != ERROR_NO_MORE_ITEMS)
	{
	    hr = HR_LOG(HRESULT_FROM_WIN32(dwEnumResult));
	    goto cleanup;    
	}
    } while (dwEnumResult != ERROR_NO_MORE_ITEMS); // do

cleanup:

    FREEHKEY(hSubKey);

    RETURN(hr);
}

//$--HrDeleteContainedKeys------------------------------------------------------
//  The recursive component of delete key. Each invocation of this function
//  will enumerate the subkeys of a key and delete them one by one
//  recursively.
// -----------------------------------------------------------------------------
static HRESULT HrDeleteContainedKeys(       // RETURNS: return code
    IN HKEY hKey)                           // registry key handle
{
    HRESULT hr                = NOERROR;
    WCHAR   rgchName[cchName] = {0};

    DEBUGPRIVATE("HrDeleteContainedKeys()");

    hr = CHK_HrDeleteContainedKeys(
	hKey);
    if(FAILED(hr))
	RETURN(hr);

    hr = HrDeleteContainedKeysInternal(hKey, rgchName);

    RETURN(hr);

#undef  cchName
}

//$--HrRemoveRegistry-----------------------------------------------------------
//  Remove the registry for the service.
// -----------------------------------------------------------------------------
HRESULT HrRemoveRegistry(              // RETURNS: nothing
    IN LPCSTR lpszServiceName)         // service name
{
    HRESULT hr         = NOERROR;
    LONG    lRet       = 0;
    HKEY    hkServices = INVALID_HANDLE_VALUE;
    HKEY    hkSvc      = INVALID_HANDLE_VALUE;

    DEBUGPUBLIC("HrRemoveRegistry()");

    hr = CHK_HrEDKRemoveRegistry(
	lpszServiceName);
    if(FAILED(hr))
	RETURN(hr);

    //
    //  Open the services key.
    //

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	"SYSTEM\\CurrentControlSet\\Services", 
	0,
	KEY_ALL_ACCESS,
	&hkServices);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open the service key.
    //

    lRet = RegOpenKeyEx(
	hkServices,
	lpszServiceName,
	0,
	KEY_ALL_ACCESS,
	&hkSvc);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    hr = HrDeleteContainedKeys(hkSvc);

    if(FAILED(hr))
    {
	goto cleanup;
    }

    lRet = RegDeleteKey(hkServices, lpszServiceName);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

cleanup:

    FREEHKEY(hkSvc);
    FREEHKEY(hkServices);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrRemoveName---------------------------------------------------------------
//  Remove the service name from the export list and signal if we're now empty
// -----------------------------------------------------------------------------
static HRESULT HrRemoveName(        // RETURNS: return code
    IN HKEY hkLinkage,              // key containing export
    IN LPSTR lpszServiceName,      // service name
    OUT BOOL * pfEmpty)             // flag to indicate its empty.
{
    LONG    lRet     = 0;
    HRESULT hr       = E_FAIL;
    HRESULT hrT      = NOERROR;
    BOOL    fChanged = FALSE;
    BOOL    fEmpty   = TRUE;
    DWORD   dwType   = 0;
    DWORD   cbOrig   = 0;
    LPVOID  pOrig    = NULL;
    LPVOID  pNew     = NULL;
    DWORD   cbNew    = 0;
    LPSTR  lpszOrig  = NULL;
    LPSTR  lpszNew   = NULL;

    DEBUGPRIVATE("HrRemoveName()\n");

    hr = CHK_HrRemoveName(
	hkLinkage,
	lpszServiceName,
	pfEmpty);
    if(FAILED(hr))
	RETURN(hr);

    //
    //  Get the current value.
    //

    hrT = HrGetRegistryValue(hkLinkage, szExport, &dwType, &cbOrig, &pOrig);

    if(FAILED(hrT) || dwType != REG_MULTI_SZ)
    {
	if(dwType != REG_MULTI_SZ)
	    hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    //
    //  Allocate a buffer big enough to hold a copy.
    //

    pNew = GlobalAlloc(GMEM_FIXED, cbOrig);

    if(pNew == NULL)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    lpszOrig = (LPSTR)pOrig;
    lpszNew = (LPSTR)pNew;

    //
    //  Loop through the source.
    //

    while(*lpszOrig)
    {
	int cchNameLen = strlen(lpszOrig) + 1;  

	if(!_strcmpi(lpszOrig, lpszServiceName))
	{
	    // found an instance.
	    fChanged = TRUE;
	}
	else
	{
	    lstrcpy(lpszNew, lpszOrig);

	    lpszNew += cchNameLen;
	    cbNew += sizeof(CHAR) * cchNameLen;

	    fEmpty = FALSE;
	}

	lpszOrig += cchNameLen;
    }

    //
    // Add final NULL
    //

    *lpszNew = 0;
    cbNew += sizeof(CHAR);

    if(fChanged)
    {
	//
	//  If it has changed, write it back.
	//

	lRet = RegSetValueEx(hkLinkage, szExport, 0, REG_MULTI_SZ, pNew, cbNew);

	if(lRet != ERROR_SUCCESS)
	{
	    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	    goto cleanup;
	}
    }

    hr = NOERROR;

    *pfEmpty = fEmpty;

cleanup:

    GLOBALFREE(pOrig);
    GLOBALFREE(pNew);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrRemoveServicePerfMon--------------------------------------------------
//  Removes service performance monitoring.
// -----------------------------------------------------------------------------
HRESULT HrRemoveServicePerfMon(          // RETURNS: return code
    IN  LPSTR lpszServiceName,             // service name
    IN  LPSTR lpszClassName,               // class name
    OUT BOOL   *lpfUnloadCounters)          // unload counters?
{
    HRESULT hr             = E_FAIL;
    LONG    lRet           = 0;
    BOOL    bEmpty         = FALSE;
    HKEY    hkServices     = INVALID_HANDLE_VALUE;
    HKEY    hkServiceClass = INVALID_HANDLE_VALUE;
    HKEY    hkLinkage      = INVALID_HANDLE_VALUE;
    DWORD   dwDisposition  = 0;

    DEBUGPUBLIC("HrRemoveServicePerfMon()\n");

    hr = CHK_HrRemoveServicePerfMon(
	lpszServiceName,
	lpszClassName,
	lpfUnloadCounters);
    if(FAILED(hr))
	RETURN(hr);

    *lpfUnloadCounters = FALSE;

    //
    //  Open the general services key.
    //

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	"SYSTEM\\CurrentControlSet\\Services", 
	0,
	KEY_ALL_ACCESS,
	&hkServices);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the class key.
    //

    lRet = CREATEKEY(hkServices, lpszClassName, hkServiceClass, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open or create the linkage key
    //

    lRet = CREATEKEY(hkServiceClass, "Linkage", hkLinkage, dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Remove the name.
    //

    hr = HrRemoveName(hkLinkage, lpszServiceName, &bEmpty);

    if(FAILED(hr))
    {
	goto cleanup;
    }

cleanup:

    FREEHKEY(hkLinkage);

    if(SUCCEEDED(hr) && bEmpty)
    {
	*lpfUnloadCounters = TRUE;
    }

    FREEHKEY(hkServiceClass);
    FREEHKEY(hkServices);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrInstallGateway--------------------------------------------------------
// Installs a gateway into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallGateway(        // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszDisplayName,      // display name
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszExtensionName,    // admin extension name
    IN LPSTR lpszExtensionData,    // extension data file
    IN LPSTR lpszAddressType,      // address type handled by this gateway
    IN LPSTR lpszAccountName,      // account name
    IN BOOL   fCanPreserveDNs)      // can this gateway preserve DNs?
{
    HRESULT hr                                          = NOERROR;
    CHAR   szTmpBuf[MAX_CSV_LINE_SIZ]                  = {0};
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]               = {0};
    CHAR   szHomeServer[MAX_CSV_LINE_SIZ]              = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]         = {0};
    CHAR   lpszComputerName[MAX_COMPUTERNAME_LENGTH+1] = {0};
    DWORD   cbComputerName                              = MAX_COMPUTERNAME_LENGTH+1;
    INT     cBytes                                      = 0;

    DEBUGPUBLIC("HrInstallGateway()");

    hr = CHK_HrInstallGateway(
	lpszServer,
	lpszSiteDN,
	lpszDisplayName,
	lpszCommonName,
	lpszExtensionName,
	lpszExtensionData,
	lpszAddressType,
	lpszAccountName,
	fCanPreserveDNs);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_GW);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szHomeServer,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s",
	lpszSiteDN,
	CONTAINER_SERVERS,
	lpszServer);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_GW);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_CREATE);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszCommonName);

    APPEND_CSV_LINE (szObjectAttributes, ADMIN_DISPLAY_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszDisplayName);
    
    APPEND_CSV_LINE (szObjectAttributes, DELIVERY_MECHANISM);
    APPEND_CSV_LINE (szAttributeValues , DELIVERY_MECHANISM_GW);
    
    APPEND_CSV_LINE (szObjectAttributes, DELIV_EXT_CONT_TYPES);
    APPEND_CSV_LINE (szAttributeValues , "2A864886F7140501");

    if((lpszExtensionData != NULL) && (lstrlen(lpszExtensionData) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, EXTENSION_DATA);
	sprintf(szTmpBuf, "=%s", lpszExtensionData);
	APPEND_CSV_LINE (szAttributeValues , szTmpBuf); 
    }

    if((lpszExtensionName != NULL) && (lstrlen(lpszExtensionName) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, EXTENSION_NAME);
	APPEND_CSV_LINE (szAttributeValues , lpszExtensionName);
    }

    APPEND_CSV_LINE (szObjectAttributes, COMPUTER_NAME);
    GetComputerName((LPSTR)lpszComputerName, &cbComputerName);
    APPEND_CSV_LINE (szAttributeValues , lpszComputerName); 
    
    APPEND_CSV_LINE (szObjectAttributes, HOME_SERVER);

    APPEND_CSV_LINE (szAttributeValues , szHomeServer); 
    
    APPEND_CSV_LINE (szObjectAttributes, ROUTING_LIST);
    sprintf(szTmpBuf, "%s:*;1", lpszAddressType);
    APPEND_CSV_LINE (szAttributeValues , szTmpBuf); 
    
    if((lpszAccountName != NULL) && (lstrlen(lpszAccountName) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, ACCOUNT_NAME);
	APPEND_CSV_LINE (szAttributeValues , lpszAccountName);
    }

    if(fCanPreserveDNs == TRUE)
    {
	APPEND_CSV_LINE (szObjectAttributes, CAN_PRESERVE_DNS);
	sprintf(szTmpBuf, "1");
	APPEND_CSV_LINE (szAttributeValues , szTmpBuf);
    }
    else
    {
	APPEND_CSV_LINE (szObjectAttributes, CAN_PRESERVE_DNS);
	sprintf(szTmpBuf, "0");
	APPEND_CSV_LINE (szAttributeValues , szTmpBuf);
    }

    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	szBasePoint,
	szObjectAttributes,
	szAttributeValues));

cleanup:

    RETURN(hr);
}

//$--HrRemoveGateway---------------------------------------------------------
//  Removes a gateway from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveGateway(         // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName)       // common name
{
    HRESULT hr                            = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                        = 0;

    DEBUGPUBLIC("HrRemoveGateway()");

    hr = CHK_HrRemoveGateway(
	lpszServer,
	lpszSiteDN,
	lpszCommonName);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_GW);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }
    
    hr = HR_LOG(HrDeleteObject(
	lpszServer,
	szBasePoint,
	lpszCommonName,
	OBJ_CLASS_GW));

cleanup:

    RETURN(hr);
}

//$--HrGatewayExists---------------------------------------------------------
//  Checks if a gateway exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrGatewayExists(         // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName)       // common name
{
    HRESULT hr                            = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                        = 0;

    DEBUGPUBLIC("HrGatewayExists()");

    hr = CHK_HrGatewayExists(
	lpszServer,
	lpszSiteDN,
	lpszCommonName);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_GW);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKObjectExists(
	lpszServer,
	szBasePoint,
	OBJ_CLASS_GW,
	lpszCommonName);

    if(FAILED(hr))
    {
	goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrInstallMailboxAgent---------------------------------------------------
//  Installs a mailbox agent into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallMailboxAgent(   // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszDisplayName,      // display name
    IN LPSTR lpszRDN,              // relative distinguished name
    IN LPSTR lpszExtensionName,    // admin extension name
    IN LPSTR lpszExtensionData,    // extension data file
    IN LPSTR lpszAccountName)      // account name
{
    HRESULT hr                                           = NOERROR;
    CHAR   szTempBuffer[MAX_CSV_LINE_SIZ]               = {0};
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]                = {0};
    CHAR   szHomeServer[MAX_CSV_LINE_SIZ]               = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ]         = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]          = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ]               = {0};
    CHAR   lpszComputerName[MAX_COMPUTERNAME_LENGTH+1]  = {0};
    DWORD   cbComputerName                               = MAX_COMPUTERNAME_LENGTH+1;
    INT     cBytes                                       = 0;
    LPSTR  lpsz                                         = NULL;
    LPSTR  lpszT                                        = NULL;
    LPSTR  lpszCommonName                               = NULL;
    BOOL    IsFound                                      = FALSE;

    DEBUGPUBLIC("HrInstallMailboxAgent()");

    hr = CHK_HrInstallMailboxAgent(
	lpszServer,
	lpszSiteDN,
	lpszDisplayName,
	lpszRDN,
	lpszExtensionName,
	lpszExtensionData,
	lpszAccountName);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szHomeServer,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s",
	lpszSiteDN,
	CONTAINER_SERVERS,
	lpszServer);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    IsFound = FALSE;

    lpsz = lpszRDN + lstrlen(lpszRDN);

    while(lpsz != lpszRDN)
    {
	lpsz--;

	if(*lpsz == '/')
	{
	    IsFound = TRUE;
	    break;
	}
    }

    if(IsFound == FALSE)
    {
	hr = HR_LOG(E_INVALIDARG);
	goto cleanup;
    }

    lpszCommonName = lpsz + sizeof("cn=");

    lstrcpy(szCommonName, lpszCommonName);

    lstrcpy(szBasePoint, lpszSiteDN);
    lstrcpyn(szBasePoint + lstrlen(szBasePoint), lpszRDN, lpsz - lpszRDN + 1);


    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_MB);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_CREATE);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , szCommonName);

    APPEND_CSV_LINE (szObjectAttributes, DISPLAY_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszDisplayName);
    
    APPEND_CSV_LINE (szObjectAttributes, DELIVERY_MECHANISM);
    APPEND_CSV_LINE (szAttributeValues , DELIVERY_MECHANISM_MB);
    
    APPEND_CSV_LINE (szObjectAttributes, DELIV_EXT_CONT_TYPES);
    APPEND_CSV_LINE (szAttributeValues , "2A864886F7140501");

    if((lpszExtensionData != NULL) && (lstrlen(lpszExtensionData) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, EXTENSION_DATA);
	sprintf(szTempBuffer, "=%s", lpszExtensionData);
	APPEND_CSV_LINE (szAttributeValues , szTempBuffer); 
    }

    if((lpszExtensionName != NULL) && (lstrlen(lpszExtensionName) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, EXTENSION_NAME);
	APPEND_CSV_LINE (szAttributeValues , lpszExtensionName);
    }
	
    APPEND_CSV_LINE (szObjectAttributes, COMPUTER_NAME);
    GetComputerName((LPSTR)lpszComputerName, &cbComputerName);
    APPEND_CSV_LINE (szAttributeValues , lpszComputerName); 

    if((lpszAccountName != NULL) && (lstrlen(lpszAccountName) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, ACCOUNT_NAME);
	APPEND_CSV_LINE (szAttributeValues , lpszAccountName);
    }
    
    APPEND_CSV_LINE (szObjectAttributes, HOME_SERVER);

    APPEND_CSV_LINE (szAttributeValues , szHomeServer);
    
    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	szBasePoint,
	szObjectAttributes,
	szAttributeValues));

cleanup:

    RETURN(hr);
}

//$--HrRemoveMailboxAgent----------------------------------------------------
// Removes a mailbox agent from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveMailboxAgent(    // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszRDN)              // relative distinguished name
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ] = {0};
    LPSTR  lpsz                           = NULL;
    LPSTR  lpszT                          = NULL;
    LPSTR  lpszCommonName                 = NULL;
    BOOL    IsFound                        = FALSE;

    DEBUGPUBLIC("HrRemoveMailboxAgent()");

    hr = CHK_HrRemoveMailboxAgent(
	lpszServer,
	lpszSiteDN,
	lpszRDN);
    if(FAILED(hr))
	RETURN(hr);

    IsFound = FALSE;

    lpsz = lpszRDN + lstrlenA(lpszRDN);

    while(lpsz != lpszRDN)
    {
	lpsz--;

	if(*lpsz == '/')
	{
	    IsFound = TRUE;
	    break;
	}
    }

    if(IsFound == FALSE)
    {
	hr = HR_LOG(E_INVALIDARG);
	goto cleanup;
    }

    lpszCommonName = lpsz + sizeof("cn=");

    lstrcpy(szCommonName, lpszCommonName);

    lstrcpy(szBasePoint, lpszSiteDN);
    lstrcpyn(szBasePoint + lstrlen(szBasePoint), lpszRDN, lpsz - lpszRDN + 1);
    
    hr = HR_LOG(HrDeleteObject(
	lpszServer,
	szBasePoint,
	szCommonName,
	OBJ_CLASS_MB));

cleanup:

    RETURN(hr);
}

//$--HrMailboxAgentExists----------------------------------------------------
//  Checks if a mailbox agent exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrMailboxAgentExists(    // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszRDN)              // relative distinguished name
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ] = {0};
    LPSTR  lpsz                           = NULL;
    LPSTR  lpszT                          = NULL;
    LPSTR  lpszCommonName                 = NULL;
    BOOL    IsFound                        = FALSE;

    DEBUGPUBLIC("HrMailboxAgentExists()");

    hr = CHK_HrMailboxAgentExists(
	lpszServer,
	lpszSiteDN,
	lpszRDN);
    if(FAILED(hr))
	RETURN(hr);

    IsFound = FALSE;

    lpsz = lpszRDN + lstrlen(lpszRDN);

    while(lpsz != lpszRDN)
    {
	lpsz--;

	if(*lpsz == '/')
	{
	    IsFound = TRUE;
	    break;
	}
    }

    if(IsFound == FALSE)
    {
	hr = HR_LOG(E_INVALIDARG);
	goto cleanup;
    }

    lpszCommonName = lpsz + sizeof("cn=");

    lstrcpy(szCommonName, lpszCommonName);

    lstrcpy(szBasePoint, lpszSiteDN);
    lstrcpyn(szBasePoint + lstrlen(szBasePoint), lpszRDN, lpsz - lpszRDN + 1);

    hr = HrEDKObjectExists(
	lpszServer,
	szBasePoint,
	OBJ_CLASS_MB,
	szCommonName);

    if(FAILED(hr))
    {
	goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrInstallAddressType----------------------------------------------------
//  Installs an address type object into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallAddressType(    // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszDisplayName,      // display name
    IN LPSTR lpszCommonName,       // common name
    IN DWORD  dwFileVersionMS,      // high-order 32 bits of file version number
    IN DWORD  dwFileVersionLS,      // low-order 32 bits of file version number
    IN LPSTR lpszProxyGenDLL,      // proxy generator DLL file name
    IN LPSTR lpszMachineType)      // machine type (e.g. "i386")
{
    HRESULT hr                                   = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ]       = {0};
    CHAR   szFileVersion[MAX_CSV_LINE_SIZ]      = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues [MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                               = 0;
    WORD    wver[4]                              = {0};
    BYTE    bver[8]                              = {0};

    DEBUGPUBLIC("HrInstallAddressType()");

    hr = CHK_HrInstallAddressType(
	lpszServer,
	lpszSiteDN,
	lpszDisplayName,
	lpszCommonName,
	dwFileVersionMS,
	dwFileVersionLS,
	lpszProxyGenDLL,
	lpszMachineType);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_ADDR_TYPE);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szCommonName,
	MAX_CSV_LINE_SIZ,
	"%s:%s",
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    wver[0] = LOWORD(dwFileVersionLS);
    wver[1] = HIWORD(dwFileVersionLS);
    wver[2] = LOWORD(dwFileVersionMS);
    wver[3] = HIWORD(dwFileVersionMS);

    bver[0] = LOBYTE(wver[0]);
    bver[1] = HIBYTE(wver[0]);
    bver[2] = LOBYTE(wver[1]);
    bver[3] = HIBYTE(wver[1]);
    bver[4] = LOBYTE(wver[2]);
    bver[5] = HIBYTE(wver[2]);
    bver[6] = LOBYTE(wver[3]);
    bver[7] = HIBYTE(wver[3]);

    cBytes = _snprintf(
	szFileVersion,
	MAX_CSV_LINE_SIZ,
	"%02x%02x%02x%02x%02x%02x%02x%02x",
	bver[0], bver[1], bver[2], bver[3],
	bver[4], bver[5], bver[6], bver[7]);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_ADDR_TYPE);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_CREATE);
    
    APPEND_CSV_LINE (szObjectAttributes, ADMIN_DISPLAY_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszDisplayName);
    
    APPEND_CSV_LINE (szObjectAttributes, ADDR_TYPE);
    APPEND_CSV_LINE (szAttributeValues , lpszCommonName);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);

    APPEND_CSV_LINE (szAttributeValues , szCommonName);

    APPEND_CSV_LINE (szObjectAttributes, PROXY_GENERATOR_DLL);
    APPEND_CSV_LINE (szAttributeValues , lpszProxyGenDLL);
    
    APPEND_CSV_LINE (szObjectAttributes, FILE_VERSION);
    APPEND_CSV_LINE (szAttributeValues , szFileVersion);
    
    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	szBasePoint,
	szObjectAttributes,
	szAttributeValues));

cleanup:

    RETURN(hr);
}

//$--HrRemoveAddressType-----------------------------------------------------
//  Removes an address type from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAddressType(     // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszMachineType)      // machine type (e.g. "i386")
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrRemoveAddressType()");

    hr = CHK_HrRemoveAddressType(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszMachineType);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_ADDR_TYPE);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szCommonName,
	MAX_CSV_LINE_SIZ,
	"%s:%s",
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }
    
    hr = HR_LOG(HrDeleteObject(
	lpszServer,
	szBasePoint,
	szCommonName,
	OBJ_CLASS_ADDR_TYPE));

cleanup:

    RETURN(hr);
}

//$--HrAddressTypeExists-----------------------------------------------------
//  Checks if an address type exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrAddressTypeExists(     // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszMachineType)      // machine type (e.g. "i386")
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrAddressTypeExists()");

    hr = CHK_HrAddressTypeExists(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszMachineType);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_ADDR_TYPE);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szCommonName,
	MAX_CSV_LINE_SIZ,
	"%s:%s",
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKObjectExists(
	lpszServer,
	szBasePoint,
	OBJ_CLASS_ADDR_TYPE,
	szCommonName);

    if(FAILED(hr))
    {
	goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrGetAddressTypeVersion-------------------------------------------------
//  Get the version of an address type object in a given site.
// -----------------------------------------------------------------------------
HRESULT HrGetAddressTypeVersion( // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszMachineType,      // machine type (e.g. "i386")
    OUT DWORD *lpdwFileVersionMS,   // high-order 32 bits of file version
    OUT DWORD *lpdwFileVersionLS)   // low-order 32 bits of file version
{
    HRESULT hr                                   = NOERROR;
    HANDLE  hTempFile                            = INVALID_HANDLE_VALUE;
    INT     cBytes                               = 0;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCurVersionRecord[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szCurLine[MAX_CSV_LINE_SIZ]          = {0};
    CHAR   szFileVersionMS[2*sizeof(DWORD)+3]   = {0};
    CHAR   szFileVersionLS[2*sizeof(DWORD)+3]   = {0};
    CHAR   szCurField[MAX_PATH]                 = {0};
    CHAR   szTempName[MAX_PATH]                 = {0};
    WORD    wVersionField                        = MAX_WORD;
    WORD    wCurField                            = 0;
    LPSTR  endptr                               = NULL;

    DEBUGPUBLIC("HrGetAddressTypeVersion()");

    hr = CHK_HrGetAddressTypeVersion(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszMachineType,
	lpdwFileVersionMS,
	lpdwFileVersionLS);
    if(FAILED(hr))
	RETURN(hr);

    *lpdwFileVersionMS = 0;
    *lpdwFileVersionLS = 0;

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    APPEND_CSV_LINE (szObjectAttributes, FILE_VERSION);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s:%s",
	lpszSiteDN,
	CONTAINER_ADDR_TYPE,
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKExportObject(
	lpszServer,
	szBasePoint,
	DAPI_EXPORT_BASEPOINT_ONLY,
	NULL,
	szObjectAttributes,
	szTempName);

    if(SUCCEEDED(hr))
    {
	hTempFile = CreateFile(
	    szTempName,
	    GENERIC_READ,
	    0,
	    (LPSECURITY_ATTRIBUTES)NULL,
	    OPEN_EXISTING,
	    FILE_FLAG_DELETE_ON_CLOSE,
	    (HANDLE)NULL);

	if(hTempFile == INVALID_HANDLE_VALUE)
	{
	    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	    goto cleanup;
	}

	//
	// The first line contains the list of fields - find which field has
	// the file version.
	//

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	for(
	    wCurField = 1;

	    FCsvGetField(
		MAX_PATH,
		wCurField,
		EXCHINST_DELIM,
		szCurLine,
		szCurField);

	    wCurField++)
	{
	    if(lstrcmp(szCurField, FILE_VERSION) == 0) 
	    {
		wVersionField = wCurField;
		break;
	    }
	}

	// Was the file version field exported & found above?

	if(wVersionField == MAX_WORD) 
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	FCsvGetField(
	    MAX_CSV_LINE_SIZ,
	    wVersionField,
	    EXCHINST_DELIM,
	    szCurLine,
	    szCurVersionRecord);

	szFileVersionMS[ 0] = '0';
	szFileVersionMS[ 1] = 'x';
	szFileVersionMS[ 2] = szCurVersionRecord[16];
	szFileVersionMS[ 3] = szCurVersionRecord[17];
	szFileVersionMS[ 4] = szCurVersionRecord[14];
	szFileVersionMS[ 5] = szCurVersionRecord[15];
	szFileVersionMS[ 6] = szCurVersionRecord[12];
	szFileVersionMS[ 7] = szCurVersionRecord[13];
	szFileVersionMS[ 8] = szCurVersionRecord[10];
	szFileVersionMS[ 9] = szCurVersionRecord[11];
	szFileVersionMS[10] = 0;

	szFileVersionLS[ 0] = '0';
	szFileVersionLS[ 1] = 'x';
	szFileVersionLS[ 2] = szCurVersionRecord[ 8];
	szFileVersionLS[ 3] = szCurVersionRecord[ 9];
	szFileVersionLS[ 4] = szCurVersionRecord[ 6];
	szFileVersionLS[ 5] = szCurVersionRecord[ 7];
	szFileVersionLS[ 6] = szCurVersionRecord[ 4];
	szFileVersionLS[ 7] = szCurVersionRecord[ 5];
	szFileVersionLS[ 8] = szCurVersionRecord[ 2];
	szFileVersionLS[ 9] = szCurVersionRecord[ 3];
	szFileVersionLS[10] = 0;

	*lpdwFileVersionMS = _tcstoul(szFileVersionMS, &endptr, 16);
	*lpdwFileVersionLS = _tcstoul(szFileVersionLS, &endptr, 16);
    }

cleanup:

    CLOSEHANDLE(hTempFile);

    RETURN(hr);
}

//$--HrInstallAddressTemplate------------------------------------------------
//  Installs an address template into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallAddressTemplate( // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszAddressSyntax,     // address syntax generator file
    IN LPSTR lpszAddressType,       // address type supported by this template
    IN LPSTR lpszPerMessageDDT,     // per-message dialog file
    IN LPSTR lpszPerRecipientDDT,   // per-recipient dialog file
    IN LPSTR lpszAddressEntryDDT,   // address entry dialog file
    IN LPSTR lpszLanguage,          // language supported by this template
    IN LPSTR lpszHelpData16,        // help data for 16-bit clients
    IN LPSTR lpszHelpData32,        // help data for 32-bit clients
    IN LPSTR lpszHelpFile)          // client help file name
{
    HRESULT hr                                   = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ]       = {0};
    CHAR   szTempBuffer[MAX_CSV_LINE_SIZ]       = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues [MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                               = 0;

    DEBUGPUBLIC("HrInstallAddressTemplate()");

    hr = CHK_HrInstallAddressTemplate(
	lpszServer,
	lpszSiteDN,
	lpszDisplayName,
	lpszCommonName,
	lpszAddressSyntax,
	lpszAddressType,
	lpszPerMessageDDT,
	lpszPerRecipientDDT,
	lpszAddressEntryDDT,
	lpszLanguage,
	lpszHelpData16,
	lpszHelpData32,
	lpszHelpFile);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s",
	lpszSiteDN,
	CONTAINER_ADDR_TEMPLATE,
	lpszLanguage);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_ADDR_TEMPLATE);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_CREATE);
    
    APPEND_CSV_LINE (szObjectAttributes, ADMIN_DISPLAY_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszDisplayName);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszCommonName);

    APPEND_CSV_LINE (szObjectAttributes, ADDR_SYNTAX);
    sprintf(szTempBuffer, "=%s", lpszAddressSyntax);   
    APPEND_CSV_LINE (szAttributeValues , szTempBuffer);
    
    APPEND_CSV_LINE (szObjectAttributes, ADDR_TYPE);
    APPEND_CSV_LINE (szAttributeValues , lpszAddressType);
    
    if((lpszPerMessageDDT != NULL) && (lstrlen(lpszPerMessageDDT) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, PER_MSG_DDT);
	sprintf(szTempBuffer, "=%s", lpszPerMessageDDT);    
	APPEND_CSV_LINE (szAttributeValues , szTempBuffer);
    }

    if((lpszPerRecipientDDT != NULL) && (lstrlen(lpszPerRecipientDDT) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, PER_RECIP_DDT);
	sprintf(szTempBuffer, "=%s", lpszPerRecipientDDT);  
	APPEND_CSV_LINE (szAttributeValues , szTempBuffer);
    }
	
    APPEND_CSV_LINE (szObjectAttributes, ADDR_ENTRY_DT);
    sprintf(szTempBuffer, "=%s", lpszAddressEntryDDT);
    APPEND_CSV_LINE (szAttributeValues , szTempBuffer);

    if((lpszHelpData16 != NULL) && (lstrlen(lpszHelpData16) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, HELP_DATA16);
	sprintf(szTempBuffer, "=%s", lpszHelpData16);    
	APPEND_CSV_LINE (szAttributeValues , szTempBuffer);
    }

    if((lpszHelpData32 != NULL) && (lstrlen(lpszHelpData32) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, HELP_DATA32);
	sprintf(szTempBuffer, "=%s", lpszHelpData32);
	APPEND_CSV_LINE (szAttributeValues , szTempBuffer);
    }

    if((lpszHelpFile != NULL) && (lstrlen(lpszHelpFile) > 0))
    {
	APPEND_CSV_LINE (szObjectAttributes, HELP_FILE_NAME);
	APPEND_CSV_LINE (szAttributeValues , lpszHelpFile);
    }

    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	szBasePoint,
	szObjectAttributes,
	szAttributeValues));

cleanup:

    RETURN(hr);
}

//$--HrRemoveAddressTemplate-------------------------------------------------
//  Removes an address template from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAddressTemplate(  // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszAddressType,       // address type supported by this template
    IN LPSTR lpszLanguage)          // language supported by this template
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrRemoveAddressTemplate()");

    hr = CHK_HrRemoveAddressTemplate(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszAddressType,
	lpszLanguage);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s",
	lpszSiteDN,
	CONTAINER_ADDR_TEMPLATE,
	lpszLanguage);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HR_LOG(HrDeleteObject(
	lpszServer,
	szBasePoint,
	lpszCommonName,
	OBJ_CLASS_ADDR_TEMPLATE));

cleanup:

    RETURN(hr);
}

//$--HrAddressTemplateExists-------------------------------------------------
//  Checks if an address template exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrAddressTemplateExists(  // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszAddressType,       // address type supported by this template
    IN LPSTR lpszLanguage)          // language supported by this template
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrAddressTemplateExists()");

    hr = CHK_HrAddressTemplateExists(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszAddressType,
	lpszLanguage);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s",
	lpszSiteDN,
	CONTAINER_ADDR_TEMPLATE,
	lpszLanguage);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKObjectExists(
	lpszServer,
	szBasePoint,
	OBJ_CLASS_ADDR_TEMPLATE,
	lpszCommonName);

    if(FAILED(hr))
    {
	goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrInstallAdminExtension-------------------------------------------------
//  Installs an admin extension object into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallAdminExtension( // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszDisplayName,      // display name
    IN LPSTR lpszCommonName,       // common name
    IN DWORD  dwFileVersionMS,      // high-order 32 bits of file version number
    IN DWORD  dwFileVersionLS,      // low-order 32 bits of file version number
    IN LPSTR lpszExtensionDLL,     // admin extension DLL file name
    IN LPSTR lpszMachineType)      // machine type (e.g. "i386")
{
    HRESULT hr                                   = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ]       = {0};
    CHAR   szFileVersion[MAX_CSV_LINE_SIZ]      = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues [MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                               = 0;
    WORD    wver[4]                              = {0};
    BYTE    bver[8]                              = {0};

    DEBUGPUBLIC("HrInstallAdminExtension()");

    hr = CHK_HrInstallAdminExtension(
	lpszServer,
	lpszSiteDN,
	lpszDisplayName,
	lpszCommonName,
	dwFileVersionMS,
	dwFileVersionLS,
	lpszExtensionDLL,
	lpszMachineType);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_ADD_INS);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szCommonName,
	MAX_CSV_LINE_SIZ,
	"%s:%s",
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    wver[0] = LOWORD(dwFileVersionLS);
    wver[1] = HIWORD(dwFileVersionLS);
    wver[2] = LOWORD(dwFileVersionMS);
    wver[3] = HIWORD(dwFileVersionMS);

    bver[0] = LOBYTE(wver[0]);
    bver[1] = HIBYTE(wver[0]);
    bver[2] = LOBYTE(wver[1]);
    bver[3] = HIBYTE(wver[1]);
    bver[4] = LOBYTE(wver[2]);
    bver[5] = HIBYTE(wver[2]);
    bver[6] = LOBYTE(wver[3]);
    bver[7] = HIBYTE(wver[3]);

    cBytes = _snprintf(
	szFileVersion,
	MAX_CSV_LINE_SIZ,
	"%02x%02x%02x%02x%02x%02x%02x%02x",
	bver[0], bver[1], bver[2], bver[3],
	bver[4], bver[5], bver[6], bver[7]);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_ADMIN_EXTENSION);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_CREATE);
    
    APPEND_CSV_LINE (szObjectAttributes, ADMIN_DISPLAY_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszDisplayName);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , szCommonName);

    APPEND_CSV_LINE (szObjectAttributes, ADMIN_EXTENSION_DLL);
    APPEND_CSV_LINE (szAttributeValues , lpszExtensionDLL);
    
    APPEND_CSV_LINE (szObjectAttributes, FILE_VERSION);
    APPEND_CSV_LINE (szAttributeValues , szFileVersion);
    
    hr = HR_LOG(HrEDKImportObject(
	lpszServer,
	szBasePoint,
	szObjectAttributes,
	szAttributeValues));

cleanup:

    RETURN(hr);
}

//$--HrRemoveAdminExtension--------------------------------------------------
//  Removes an admin extension from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAdminExtension(  // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszMachineType)      // machine type (e.g. "i386")
{
    HRESULT hr                             = 0;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrRemoveAdminExtension()");

    hr = CHK_HrRemoveAdminExtension(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszMachineType);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_ADD_INS);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szCommonName,
	MAX_CSV_LINE_SIZ,
	"%s:%s",
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }
    
    hr = HR_LOG(HrDeleteObject(
	lpszServer,
	szBasePoint,
	szCommonName,
	OBJ_CLASS_ADMIN_EXTENSION));

cleanup:

    RETURN(hr);
}

//$--HrAdminExtensionExists--------------------------------------------------
//  Checks if an admin extension exists on a given site.
// -----------------------------------------------------------------------------
HRESULT HrAdminExtensionExists(  // RETURNS: return code
    IN LPSTR lpszServer,           // server name
    IN LPSTR lpszSiteDN,           // distinguished name of site
    IN LPSTR lpszCommonName,       // common name
    IN LPSTR lpszMachineType)      // machine type (e.g. "i386")
{
    HRESULT hr                             = NOERROR;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCommonName[MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrAdminExtensionExists()");

    hr = CHK_HrAdminExtensionExists(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszMachineType);
    if(FAILED(hr))
	RETURN(hr);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_ADD_INS);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cBytes = _snprintf(
	szCommonName,
	MAX_CSV_LINE_SIZ,
	"%s:%s",
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKObjectExists(
	lpszServer,
	szBasePoint,
	OBJ_CLASS_ADMIN_EXTENSION,
	szCommonName);

    if(FAILED(hr))
    {
	goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrGetAdminExtensionVersion----------------------------------------------
//  Get the version of an admin extension object in a given site.
// -----------------------------------------------------------------------------
HRESULT HrGetAdminExtensionVersion(  // RETURNS: return code
    IN LPSTR lpszServer,               // server name
    IN LPSTR lpszSiteDN,               // distinguished name of site
    IN LPSTR lpszCommonName,           // common name
    IN LPSTR lpszMachineType,          // machine type (e.g. "i386")
    OUT DWORD *lpdwFileVersionMS,       // high-order 32 bits of file version
    OUT DWORD *lpdwFileVersionLS)       // low-order 32 bits of file version
{
    HRESULT hr                                   = NOERROR;
    HANDLE  hTempFile                            = INVALID_HANDLE_VALUE;
    INT     cBytes                               = 0;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCurVersionRecord[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szCurLine[MAX_CSV_LINE_SIZ]          = {0};
    CHAR   szFileVersionMS[2*sizeof(DWORD)+3]   = {0};
    CHAR   szFileVersionLS[2*sizeof(DWORD)+3]   = {0};
    CHAR   szCurField[MAX_PATH]                 = {0};
    CHAR   szTempName[MAX_PATH]                 = {0};
    WORD    wVersionField                        = MAX_WORD;
    WORD    wCurField                            = 0;
    LPSTR  endptr                               = NULL;

    DEBUGPUBLIC("HrGetAdminExtensionVersion()");

    hr = CHK_HrGetAdminExtensionVersion(
	lpszServer,
	lpszSiteDN,
	lpszCommonName,
	lpszMachineType,
	lpdwFileVersionMS,
	lpdwFileVersionLS);
    if(FAILED(hr))
	RETURN(hr);

    *lpdwFileVersionMS = 0;
    *lpdwFileVersionLS = 0;

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    APPEND_CSV_LINE (szObjectAttributes, FILE_VERSION);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s/cn=%s:%s",
	lpszSiteDN,
	CONTAINER_ADD_INS,
	lpszCommonName,
	lpszMachineType);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKExportObject(
	lpszServer,
	szBasePoint,
	DAPI_EXPORT_BASEPOINT_ONLY,
	NULL,
	szObjectAttributes,
	szTempName);

    if(SUCCEEDED(hr))
    {
	hTempFile = CreateFile(
	    szTempName,
	    GENERIC_READ,
	    0,
	    (LPSECURITY_ATTRIBUTES)NULL,
	    OPEN_EXISTING,
	    FILE_FLAG_DELETE_ON_CLOSE,
	    (HANDLE)NULL);

	if(hTempFile == INVALID_HANDLE_VALUE)
	{
	    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	    goto cleanup;
	}

	//
	// The first line contains the list of fields - find which field has
	// the file version.
	//

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	for(
	    wCurField = 1;

	    FCsvGetField(
		MAX_PATH,
		wCurField,
		EXCHINST_DELIM,
		szCurLine,
		szCurField);

	    wCurField++)
	{
	    if(lstrcmp(szCurField, FILE_VERSION) == 0) 
	    {
		wVersionField = wCurField;
		break;
	    }
	}

	// Was the file version field exported & found above?

	if(wVersionField == MAX_WORD) 
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	FCsvGetField(
	    MAX_CSV_LINE_SIZ,
	    wVersionField,
	    EXCHINST_DELIM,
	    szCurLine,
	    szCurVersionRecord);

	szFileVersionMS[ 0] = '0';
	szFileVersionMS[ 1] = 'x';
	szFileVersionMS[ 2] = szCurVersionRecord[16];
	szFileVersionMS[ 3] = szCurVersionRecord[17];
	szFileVersionMS[ 4] = szCurVersionRecord[14];
	szFileVersionMS[ 5] = szCurVersionRecord[15];
	szFileVersionMS[ 6] = szCurVersionRecord[12];
	szFileVersionMS[ 7] = szCurVersionRecord[13];
	szFileVersionMS[ 8] = szCurVersionRecord[10];
	szFileVersionMS[ 9] = szCurVersionRecord[11];
	szFileVersionMS[10] = 0;

	szFileVersionLS[ 0] = '0';
	szFileVersionLS[ 1] = 'x';
	szFileVersionLS[ 2] = szCurVersionRecord[ 8];
	szFileVersionLS[ 3] = szCurVersionRecord[ 9];
	szFileVersionLS[ 4] = szCurVersionRecord[ 6];
	szFileVersionLS[ 5] = szCurVersionRecord[ 7];
	szFileVersionLS[ 6] = szCurVersionRecord[ 4];
	szFileVersionLS[ 7] = szCurVersionRecord[ 5];
	szFileVersionLS[ 8] = szCurVersionRecord[ 2];
	szFileVersionLS[ 9] = szCurVersionRecord[ 3];
	szFileVersionLS[10] = 0;

	*lpdwFileVersionMS = _tcstoul(szFileVersionMS, &endptr, 16);
	*lpdwFileVersionLS = _tcstoul(szFileVersionLS, &endptr, 16);
    }

cleanup:

    CLOSEHANDLE(hTempFile);

    RETURN(hr);
}

//$--HrInstallContainer---------------------------------------------------------
//  Installs a container in the directory.
// -----------------------------------------------------------------------------
HRESULT HrInstallContainer(         // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszBasePoint,         // base point
    IN LPSTR lpszCommonName,        // common name
    IN LPSTR lpszDisplayName,       // display name
    IN LPSTR lpszContainerInfo)     // container information
{
    HRESULT hr                                   = NOERROR;
    CHAR    szTempBuffer[MAX_CSV_LINE_SIZ]       = {0};
    CHAR    szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR    szAttributeValues [MAX_CSV_LINE_SIZ] = {0};
    INT     cBytes                               = 0;

    DEBUGPUBLIC("HrInstallContainer()");

    hr = CHK_HrInstallContainer(
        lpszServer,
        lpszBasePoint,
        lpszCommonName,
        lpszDisplayName,
        lpszContainerInfo);
    if(FAILED(hr))
        RETURN(hr);

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_CONTAINER);

    APPEND_CSV_LINE (szObjectAttributes, MODE);
    APPEND_CSV_LINE (szAttributeValues , MODE_CREATE);
    
    APPEND_CSV_LINE (szObjectAttributes, ADMIN_DISPLAY_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszDisplayName);
    
    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
    APPEND_CSV_LINE (szAttributeValues , lpszCommonName);

    APPEND_CSV_LINE (szObjectAttributes, CONTAINER_INFO);
    APPEND_CSV_LINE (szAttributeValues , lpszContainerInfo);

    hr = HR_LOG(HrEDKImportObject(
        lpszServer,
        lpszBasePoint,
        szObjectAttributes,
        szAttributeValues));

    RETURN(hr);
}

//$--HrRemoveContainer----------------------------------------------------------
//  Removes a container from the directory.
// -----------------------------------------------------------------------------
HRESULT HrRemoveContainer(          // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszBasePoint,         // base point
    IN LPSTR lpszCommonName)        // common name
{
    HRESULT hr                             = NOERROR;
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrRemoveContainer()");

    hr = CHK_HrRemoveContainer(
        lpszServer,
        lpszBasePoint,
        lpszCommonName);
    if(FAILED(hr))
        RETURN(hr);

    hr = HR_LOG(HrDeleteObject(
        lpszServer,
        lpszBasePoint,
        lpszCommonName,
        OBJ_CLASS_CONTAINER));

    RETURN(hr);
}

//$--HrContainerExists----------------------------------------------------------
//  Checks if a container exists in the directory.
// -----------------------------------------------------------------------------
HRESULT HrContainerExists(          // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszBasePoint,         // base point
    IN LPSTR lpszCommonName)        // common name
{
    HRESULT hr                             = NOERROR;
    INT     cBytes                         = 0;

    DEBUGPUBLIC("HrContainerExists()");

    hr = CHK_HrContainerExists(
        lpszServer,
        lpszBasePoint,
        lpszCommonName);
    if(FAILED(hr))
        RETURN(hr);

    hr = HrEDKObjectExists(
        lpszServer,
        lpszBasePoint,
        OBJ_CLASS_CONTAINER,
        lpszCommonName);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrInstallAddressTemplateContainer------------------------------------------
//  Installs an address template container in the directory.
// -----------------------------------------------------------------------------
HRESULT HrInstallAddressTemplateContainer(  // RETURNS: return code
    IN LPSTR lpszServer,                    // server name
    IN LPSTR lpszSiteDN,                    // site distinguished name
    IN LPSTR lpszLanguage,                  // language supported by container
    IN LPSTR lpszDisplayName)               // display name
{
    HRESULT hr                             = NOERROR;
    INT     cBytes                         = 0;
    CHAR    szBasePoint[MAX_CSV_LINE_SIZ]  = {0};

    DEBUGPUBLIC("HrInstallAddressTemplateContainer()");

    hr = CHK_HrInstallAddressTemplateContainer(
        lpszServer,
        lpszSiteDN,
        lpszLanguage,
        lpszDisplayName);
    if(FAILED(hr))
        RETURN(hr);

    cBytes = _snprintf(
        szBasePoint,
        MAX_CSV_LINE_SIZ,
        "%s%s",
        lpszSiteDN,
        CONTAINER_ADDR_TEMPLATE);

    if(cBytes < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrInstallContainer(
        lpszServer,
        szBasePoint,
        lpszLanguage,
        lpszDisplayName,
        ADDRESS_TEMPLATE_CONTAINER_INFO);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrRemoveAddressTemplateContainer-------------------------------------------
//  Removes an address template container from the directory.
// -----------------------------------------------------------------------------
HRESULT HrRemoveAddressTemplateContainer(   // RETURNS: return code
    IN LPSTR lpszServer,                    // server name
    IN LPSTR lpszSiteDN,                    // site distinguished name
    IN LPSTR lpszLanguage)                  // language supported by container
{
    HRESULT hr                             = NOERROR;
    INT     cBytes                         = 0;
    CHAR    szBasePoint[MAX_CSV_LINE_SIZ]  = {0};

    DEBUGPUBLIC("HrRemoveAddressTemplateContainer()");

    hr = CHK_HrRemoveAddressTemplateContainer(
        lpszServer,
        lpszSiteDN,
        lpszLanguage);
    if(FAILED(hr))
        RETURN(hr);

    cBytes = _snprintf(
        szBasePoint,
        MAX_CSV_LINE_SIZ,
        "%s%s",
        lpszSiteDN,
        CONTAINER_ADDR_TEMPLATE);

    if(cBytes < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrRemoveContainer(
        lpszServer,
        szBasePoint,
        lpszLanguage);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrAddressTemplateContainerExists-------------------------------------------
//  Checks if an address template container exists in the directory.
// -----------------------------------------------------------------------------
HRESULT HrAddressTemplateContainerExists(   // RETURNS: return code
    IN LPSTR lpszServer,                    // server name
    IN LPSTR lpszSiteDN,                    // site distinguished name
    IN LPSTR lpszLanguage)                  // language supported by container
{
    HRESULT hr                             = NOERROR;
    INT     cBytes                         = 0;
    CHAR    szBasePoint[MAX_CSV_LINE_SIZ]  = {0};

    DEBUGPUBLIC("HrAddressTemplateContainerExists()");

    hr = CHK_HrAddressTemplateContainerExists(
        lpszServer,
        lpszSiteDN,
        lpszLanguage);
    if(FAILED(hr))
        RETURN(hr);

    cBytes = _snprintf(
        szBasePoint,
        MAX_CSV_LINE_SIZ,
        "%s%s",
        lpszSiteDN,
        CONTAINER_ADDR_TEMPLATE);

    if(cBytes < 0)
    {
        hr = HR_LOG(E_FAIL);
        goto cleanup;
    }

    hr = HrContainerExists(
        lpszServer,
        szBasePoint,
        lpszLanguage);

    if(FAILED(hr))
    {
        goto cleanup;
    }

cleanup:

    RETURN(hr);
}

//$--HrAddDelGatewayProxy-------------------------------------------------------
// This function will add/delete our gateway proxy to/from the given site.
// -----------------------------------------------------------------------------
static HRESULT HrAddDelGatewayProxy(    // RETURNS: return code
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR lpszSiteDN,               // site distinguished name
    IN  LPSTR lpszOurProxyString,       // proxy string for our gateway
    IN  BOOL  fAddProxy)                // If TRUE we will add proxy
{
    HRESULT hr                                   = NOERROR;
    HANDLE  hTempFile                            = INVALID_HANDLE_VALUE;
    INT     cBytes                               = 0;
    CHAR   szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR   szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR   szAttributeValues[MAX_CSV_LINE_SIZ]  = {0};
    CHAR   szCurProxyRecord[MAX_CSV_LINE_SIZ]   = {0};
    CHAR   szNewProxyRecord[MAX_CSV_LINE_SIZ]   = {0};
    CHAR   szCurProxyString[MAX_CSV_LINE_SIZ]   = {0};
    CHAR   szCurLine[MAX_CSV_LINE_SIZ]          = {0};
    CHAR   szCurField[MAX_PATH]                 = {0};
    CHAR   szTempName[MAX_PATH]                 = {0};
    CHAR   szTmpBuf[MAX_CSV_LINE_SIZ]           = {0};
    WORD    wGatewayProxyField                   = MAX_WORD;
    WORD    wCurField                            = 0;
    BOOL    fOurProxyExist                       = FALSE;
    DWORD   cchOurProxyString                    = 0;

    hr = CHK_HrAddDelGatewayProxy(
	lpszServer,
	lpszSiteDN,
	lpszOurProxyString,
	fAddProxy);
    if(FAILED(hr))
	RETURN(hr);

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    APPEND_CSV_LINE (szObjectAttributes, GATEWAY_PROXY);

    cBytes = _snprintf(
	szBasePoint,
	MAX_CSV_LINE_SIZ,
	"%s%s",
	lpszSiteDN,
	CONTAINER_SITE_ADDR);

    if(cBytes < 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    hr = HrEDKExportObject(
	lpszServer,
	szBasePoint,
	DAPI_EXPORT_BASEPOINT_ONLY,
	NULL,
	szObjectAttributes,
	szTempName);

    if(SUCCEEDED(hr))
    {
	hTempFile = CreateFile(
	    szTempName,
	    GENERIC_READ,
	    0,
	    (LPSECURITY_ATTRIBUTES)NULL,
	    OPEN_EXISTING,
	    FILE_FLAG_DELETE_ON_CLOSE,
	    (HANDLE)NULL);

	if(hTempFile == INVALID_HANDLE_VALUE)
	{
	    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	    goto cleanup;
	}

	//
	// The first line contains the list of fields - find which field has
	// the gateway proxy.
	//

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	for(
	    wCurField = 1;

	    FCsvGetField(
		MAX_PATH,
		wCurField,
		EXCHINST_DELIM,
		szCurLine,
		szCurField);

	    wCurField++)
	{
	    if(strcmp(szCurField, GATEWAY_PROXY) == 0) 
	    {
		wGatewayProxyField = wCurField;
		break;
	    }
	}

	// Was the gateway proxy field exported & found above?

	if(wGatewayProxyField == MAX_WORD) 
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	cchOurProxyString = lstrlen(lpszOurProxyString);

	//
	// Get the current Proxy record and Add or Delete it as specified
	// (Add only if it doesnt exist)
	// (e.g. Proxy record: SMTP:@site.ent.com%MS:site/ent%EDK:@site.ent.com)
	//

	FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	FCsvGetField(
	    MAX_CSV_LINE_SIZ,
	    wGatewayProxyField,
	    EXCHINST_DELIM,
	    szCurLine,
	    szCurProxyRecord);

	for(
	    wCurField = 1;

	    FCsvGetField(
		MAX_PATH,
		wCurField,
		EXCHINST_MV_SEP,
		szCurProxyRecord,
		szCurProxyString);

	    wCurField++)
	{
	    if(_strnicmp(
		szCurProxyString, lpszOurProxyString, cchOurProxyString) == 0)
	    {
		fOurProxyExist = TRUE;

		if(fAddProxy)
		{
		    if(lstrlen(szNewProxyRecord) != 0)
			lstrcat(szNewProxyRecord, SZ_EXCHINST_MV_SEP);
		    lstrcat(szNewProxyRecord, szCurProxyString);
		}
	    }
	    else 
	    {
		if(lstrlen(szNewProxyRecord) != 0)
		    lstrcat(szNewProxyRecord, SZ_EXCHINST_MV_SEP);
		lstrcat(szNewProxyRecord, szCurProxyString);
	    }
	}

	if(fOurProxyExist == FALSE)
	{
	    if(fAddProxy)
	    {
		if(lstrlen(szNewProxyRecord) != 0)
		    lstrcat(szNewProxyRecord, SZ_EXCHINST_MV_SEP);
		lstrcat(szNewProxyRecord, lpszOurProxyString);
	    }
	    else
	    {
		hr = HR_LOG(EDK_E_NOT_FOUND);
		goto cleanup;
	    }
	}

	// Build line to perform the modification.

	BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
	BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_SITE);

	APPEND_CSV_LINE (szObjectAttributes, MODE);
	APPEND_CSV_LINE (szAttributeValues , MODE_MODIFY);

	APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
	APPEND_CSV_LINE (szAttributeValues , SITE_ADDRESSING);
    
	APPEND_CSV_LINE (szObjectAttributes, GATEWAY_PROXY);
	APPEND_CSV_LINE (szAttributeValues , szNewProxyRecord);

	cBytes = _snprintf(
	    szBasePoint,
	    MAX_CSV_LINE_SIZ,
	    "%s%s",
	    lpszSiteDN,
	    CONTAINER_CONFIGURATION);

	if(cBytes < 0)
	{
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
	}

	hr = HR_LOG(HrEDKImportObject(
	    lpszServer,
	    szBasePoint,
	    szObjectAttributes,
	    szAttributeValues));
    }

cleanup:

    CLOSEHANDLE(hTempFile);

    RETURN(hr);
}

//$--HrInstallGatewayProxy---------------------------------------------------
//  Installs a gateway proxy into a given site.
// -----------------------------------------------------------------------------
HRESULT HrInstallGatewayProxy(    // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszProxy)             // gateway proxy
{
    HRESULT hr = NOERROR;

    DEBUGPUBLIC("HrInstallGatewayProxy()");

    hr = CHK_HrInstallGatewayProxy(
	lpszServer,
	lpszSiteDN,
	lpszProxy);
    if(FAILED(hr))
	RETURN(hr);

    RETURN(HrAddDelGatewayProxy(
	lpszServer,
	lpszSiteDN,
	lpszProxy,
	TRUE));
}

//$--HrRemoveGatewayProxy----------------------------------------------------
//  Removes a gateway proxy from a given site.
// -----------------------------------------------------------------------------
HRESULT HrRemoveGatewayProxy(     // RETURNS: return code
    IN LPSTR lpszServer,            // server name
    IN LPSTR lpszSiteDN,            // distinguished name of site
    IN LPSTR lpszProxy)             // gateway proxy
{
    RETURN(HrAddDelGatewayProxy(
	lpszServer,
	lpszSiteDN,
	lpszProxy,
	FALSE));
}

//$--FHasAdminPrivs----------------------------------------------------------------
//  Returns TRUE if the current user is an administrator.
// -----------------------------------------------------------------------------
BOOL FHasAdminPrivs(                    // RETURNS: TRUE/FALSE
    void)                            // no arguments
{
    BOOL                     fRet               = TRUE;
    HANDLE                   hProcess           = INVALID_HANDLE_VALUE;
    HANDLE                   hAccessToken       = INVALID_HANDLE_VALUE;
    UCHAR                    InfoBuffer[1024]   = {0};
    PTOKEN_GROUPS            ptgGroups          = (PTOKEN_GROUPS)InfoBuffer;
    DWORD                    dwInfoBufferSize   = 0;
    PSID                     psidAdministrators = NULL;
    SID_IDENTIFIER_AUTHORITY siaNtAuthority     = SECURITY_NT_AUTHORITY;
    UINT                     x                  = 0;

    hProcess = GetCurrentProcess();

    if(!OpenProcessToken(hProcess,TOKEN_READ,&hAccessToken))
	return(FALSE);

    if(!GetTokenInformation(
	hAccessToken,TokenGroups, InfoBuffer, 1024, &dwInfoBufferSize))
	return(FALSE);

    fRet = AllocateAndInitializeSid(
	&siaNtAuthority,
	2,
	SECURITY_BUILTIN_DOMAIN_RID,
	DOMAIN_ALIAS_RID_ADMINS,
	0,
	0,
	0,
	0,
	0,
	0,
	&psidAdministrators);

    if (!fRet)
    {
	return(FALSE);
    }

    for(x = 0; x < ptgGroups->GroupCount; x++)
    {
	if(EqualSid(psidAdministrators, ptgGroups->Groups[x].Sid))
	{
	    FreeSid(psidAdministrators);
	    return(TRUE);
	}
    }

    FreeSid(psidAdministrators);

    return(FALSE);
}

//$--HrInstallMessageConverter-----------------------------------------------
// Installs a message conversion DLL.
// -----------------------------------------------------------------------------
HRESULT HrInstallMessageConverter(   // RETURNS: return code
    IN LPSTR lpszConverter,            // converter name
    IN LPSTR lpszDllName,              // name of conversion DLL
    IN LPSTR lpszMessageClasses,       // message classes
    IN LPSTR lpszOptions,              // options string
    IN LPSTR lpszPoint)                // conversion point
{
    HRESULT hr                 = NOERROR;
    LONG    lRet               = 0;
    HKEY    hkClasses          = INVALID_HANDLE_VALUE;
    HKEY    hkObject           = INVALID_HANDLE_VALUE;
    HKEY    hkTmp              = INVALID_HANDLE_VALUE;
    DWORD   dwDisposition      = 0;

    DEBUGPUBLIC("HrInstallMessageConverter()\n");

    hr = CHK_HrInstallMessageConverter(
	lpszConverter,
	lpszDllName,
	lpszMessageClasses,
	lpszOptions,
	lpszPoint);
    if(FAILED(hr))
	RETURN(hr);

    lRet = RegCreateKeyEx(
	HKEY_LOCAL_MACHINE,
	"Software\\Classes\\MAPI Conversions",
	0,
	"",
	REG_OPTION_NON_VOLATILE,
	KEY_ALL_ACCESS,
	NULL,
	&hkClasses,
	&dwDisposition);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    //
    //  Create the object key.
    //

    lRet = CREATEKEY(hkClasses, lpszDllName, hkObject, dwDisposition);

    if((lRet != ERROR_SUCCESS) && (lRet != ERROR_ALREADY_EXISTS))
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    //
    // Create GetTrivialVector key.
    //

    lRet = CREATEKEY(hkObject, "GetTrivialVector", hkTmp, dwDisposition);

    if((lRet != ERROR_SUCCESS) && (lRet != ERROR_ALREADY_EXISTS))
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    // Create new values under GetTrivialVector key

    lRet = SETMULTISZVALUE(hkTmp, "Classes", lpszMessageClasses);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

    if(lpszOptions != NULL)
    {
	lRet = SETSZVALUE(hkTmp, "Options", lpszOptions);

	if(lRet != ERROR_SUCCESS)
	{
	    hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	    goto cleanup;
	}
    }

    lRet = SETSZVALUE(hkTmp, "Point", lpszPoint);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

cleanup:

    FREEHKEY(hkClasses);
    FREEHKEY(hkObject);
    FREEHKEY(hkTmp);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrRemoveMessageConverter-----------------------------------------------
//  Delete a message conversion DLL.
// ----------------------------------------------------------------------------
HRESULT HrRemoveMessageConverter(    // RETURNS: return code
    IN LPCSTR lpszConverter)           // converter name
{
    HRESULT hr         = NOERROR;
    LONG    lRet       = 0;
    HKEY    hkClasses  = INVALID_HANDLE_VALUE;
    HKEY    hkObject   = INVALID_HANDLE_VALUE;

    DEBUGPUBLIC("HrRemoveMessageConverter()\n");

    hr = CHK_HrRemoveMessageConverter(
	lpszConverter);
    if(FAILED(hr))
	RETURN(hr);

    //
    //  Open the services key.
    //

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	TEXT("Software\\Classes\\MAPI Conversions"), 
	0,
	KEY_ALL_ACCESS,
	&hkClasses);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    //
    //  Open the conversion key.
    //

    lRet = RegOpenKeyEx(
	hkClasses,
	lpszConverter,
	0,
	KEY_ALL_ACCESS,
	&hkObject);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    (void)HrDeleteContainedKeys(hkObject);

    lRet = RegDeleteKey(hkClasses, lpszConverter);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

cleanup:

    FREEHKEY(hkObject);
    FREEHKEY(hkClasses);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrAdminProgramExists---------------------------------------------------
//  Check if the admin program has been installed on the local computer.
// ----------------------------------------------------------------------------
HRESULT HrAdminProgramExists(        // RETURNS: return code
    void)                               // nothing
{
    HRESULT hr                     = NOERROR;
    LONG    lRet                   = 0;
    HKEY    hKey                   = INVALID_HANDLE_VALUE;
    DWORD   dwType                 = 0;
    DWORD   cBytes                 = 0;
    LPSTR  lpszAdminDest          = NULL;
    CHAR   szFileName[MAX_PATH+1] = {0};
    ULONG   cch                    = 0;
    DWORD   dwAttrib               = 0;

    DEBUGPUBLIC("HrAdminProgramExists()\n");

    lRet = RegOpenKeyEx(
	HKEY_LOCAL_MACHINE,
	TEXT("Software\\Microsoft\\Exchange\\Setup"), 
	0,
	KEY_ALL_ACCESS,
	&hKey);

    if(lRet != ERROR_SUCCESS)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(lRet));
	goto cleanup;
    }

    hr = HrGetRegistryValue(
	hKey, "AdminDest", &dwType, &cBytes, (LPVOID) &lpszAdminDest);

    if(FAILED(hr) || dwType != REG_SZ)
    {
	if(dwType != REG_SZ)
	    hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    if(lpszAdminDest == NULL)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    cch = lstrlen(lpszAdminDest);

    if(cch == 0)
    {
	hr = HR_LOG(E_FAIL);
	goto cleanup;
    }

    lstrcpy(szFileName, lpszAdminDest);

    if(szFileName[cch-1] != '\\')
    {
	lstrcatA(szFileName, "\\");
    }

    lstrcatA(szFileName, "ADMIN.EXE");

    dwAttrib = GetFileAttributes(szFileName);

    if(dwAttrib == 0xFFFFFFFF)
    {
	hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	goto cleanup;
    }

cleanup:

	GLOBALFREE(lpszAdminDest);
    FREEHKEY(hKey);

    RegFlushKey(HKEY_LOCAL_MACHINE);
    RegFlushKey(HKEY_CURRENT_USER);

    RETURN(hr);
}

//$--HrSetGatewayBit------------------------------------------------------------
//  This function will set the gateway bit on a given server.
// -----------------------------------------------------------------------------
HRESULT HrSetGatewayBit(                // RETURNS: return code
    IN  LPSTR lpszServer,               // server name
    IN  LPSTR lpszSiteDN,               // site distinguished name
    IN  LPSTR lpszServerName)           // server name
{
    HRESULT hr                                   = NOERROR;
    HANDLE  hTempFile                            = INVALID_HANDLE_VALUE;
    INT     cBytes                               = 0;
    CHAR    szBasePoint[MAX_CSV_LINE_SIZ]        = {0};
    CHAR    szObjectAttributes[MAX_CSV_LINE_SIZ] = {0};
    CHAR    szAttributeValues[MAX_CSV_LINE_SIZ]  = {0};
    CHAR    szCurHeuristicRecord[MAX_CSV_LINE_SIZ] = {0};
    CHAR    szNewHeuristicRecord[MAX_CSV_LINE_SIZ] = {0};
    CHAR    szCurLine[MAX_CSV_LINE_SIZ]          = {0};
    CHAR    szCurField[MAX_PATH]                 = {0};
    CHAR    szTempName[MAX_PATH]                 = {0};
    CHAR    szTmpBuf[MAX_CSV_LINE_SIZ]           = {0};
    WORD    wHeuristicField                      = MAX_WORD;
    WORD    wCurField                            = 0;
    ULONG   ulHeuristic                          = 0;

    hr = CHK_HrSetGatewayBit(
	    lpszServer,
	    lpszSiteDN,
	    lpszServerName);
    if(FAILED(hr))
	    RETURN(hr);

    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
    APPEND_CSV_LINE (szObjectAttributes, HEURISTICS);

    cBytes = _snprintf(
	    szBasePoint,
	    MAX_CSV_LINE_SIZ,
	    "%s%s/cn=%s",
	    lpszSiteDN,
	    CONTAINER_SERVERS,
        lpszServerName);

    if(cBytes < 0)
    {
	    hr = HR_LOG(E_FAIL);
	    goto cleanup;
    }

    hr = HrEDKExportObject(
	    lpszServer,
	    szBasePoint,
	    DAPI_EXPORT_BASEPOINT_ONLY,
	    NULL,
	    szObjectAttributes,
	    szTempName);

    if(SUCCEEDED(hr))
    {
	    hTempFile = CreateFile(
	        szTempName,
	        GENERIC_READ,
	        0,
	        (LPSECURITY_ATTRIBUTES)NULL,
	        OPEN_EXISTING,
	        FILE_FLAG_DELETE_ON_CLOSE,
	        (HANDLE)NULL);

	    if(hTempFile == INVALID_HANDLE_VALUE)
	    {
	        hr = HR_LOG(HRESULT_FROM_WIN32(GetLastError()));
	        goto cleanup;
	    }

	    //
	    // The first line contains the list of fields - find which field has
	    // the heuristic.
	    //

	    FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	    for(
	        wCurField = 1;

	        FCsvGetField(
		    MAX_PATH,
		    wCurField,
		    EXCHINST_DELIM,
		    szCurLine,
		    szCurField);

	        wCurField++)
	    {
	        if(strcmp(szCurField, HEURISTICS) == 0) 
	        {
		        wHeuristicField = wCurField;
		        break;
	        }
	    }

	    // Was the heuristic field exported & found above?

	    if(wHeuristicField == MAX_WORD) 
	    {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
	    }

	    //
	    // Get the current value of the heuristic attribute.
	    //

	    FCsvGetRecord(MAX_CSV_LINE_SIZ, hTempFile, szCurLine);

	    FCsvGetField(
	        MAX_CSV_LINE_SIZ,
	        wHeuristicField,
	        EXCHINST_DELIM,
	        szCurLine,
	        szCurHeuristicRecord);

        //
        // Set the gateway bit.
        //

        ulHeuristic  = atol(szCurHeuristicRecord);

        ulHeuristic |= 2;

        cBytes = _snprintf(
	        szNewHeuristicRecord,
	        MAX_CSV_LINE_SIZ,
	        "%lu",
            ulHeuristic);

        if(cBytes < 0)
        {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
        }

	    // Build line to perform the modification.

	    BEGIN_CSV_LINE  (szObjectAttributes, OBJ_CLASS);
	    BEGIN_CSV_LINE  (szAttributeValues , OBJ_CLASS_COMPUTER);

	    APPEND_CSV_LINE (szObjectAttributes, MODE);
	    APPEND_CSV_LINE (szAttributeValues , MODE_MODIFY);

	    APPEND_CSV_LINE (szObjectAttributes, COMMON_NAME);
	    APPEND_CSV_LINE (szAttributeValues , lpszServerName);
    
	    APPEND_CSV_LINE (szObjectAttributes, HEURISTICS);
	    APPEND_CSV_LINE (szAttributeValues , szNewHeuristicRecord);

        cBytes = _snprintf(
	        szBasePoint,
	        MAX_CSV_LINE_SIZ,
	        "%s%s",
	        lpszSiteDN,
	        CONTAINER_SERVERS);

        if(cBytes < 0)
        {
	        hr = HR_LOG(E_FAIL);
	        goto cleanup;
        }

	    hr = HR_LOG(HrEDKImportObject(
	        lpszServer,
	        szBasePoint,
	        szObjectAttributes,
	        szAttributeValues));
    }

cleanup:

    CLOSEHANDLE(hTempFile);

    RETURN(hr);
}

#include "exchprof.c"
