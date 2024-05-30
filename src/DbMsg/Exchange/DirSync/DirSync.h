// --dirsync.h------------------------------------------------------------------
//
// Header file containing definitions that are used by multiple files of the 
// directory synchronization sample code.
//
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_DIRSYNC_H)
#define _DIRSYNC_H

#include "dapi.h"

//
// Names of DAPI Attributes
//

#define OBJ_CLASS                           "Obj-Class"
#define USN_CHANGED                         "USN-Changed"
#define USN_CREATED                         "USN-Created"
#define IS_DELETED                          "Is-Deleted"
#define OBJ_DIST_NAME                       "Obj-Dist-Name"
#define COMMON_NAME                         "Common-Name"
#define IMPORTED_FROM                       "Imported-From"
#define HOME_SERVER                         "Home-Server"

#define OBJECT_CLASS_REMOTE                 "Remote"
#define OBJECT_CLASS_MAILBOX                "Mailbox"

//
// Defined Types
//

//$--DIR_SYNC_OPERATION---------------------------------------------------------
//  Type of operation to be performed on directory.
// -----------------------------------------------------------------------------
typedef enum _DirSyncOperation {            // (hungarian = e)
    OPERATION_ADD = 0,                      // add a user to the directory
    OPERATION_DELETE,                       // delete a user from the directory
    OPERATION_MODIFY,                       // modify a user in the directory
    OPERATION_LAST                          // all operations are less than this
} DIR_SYNC_OPERATION, *LPDIR_SYNC_OPERATION;

//
// Structures
//

//$--DIR_SYNC_ATTRIBUTE_INFO----------------------------------------------------
//  Holds information about an attribute being passed back from BIMPORT.
//  An array of these structures is passed the the user's fWriteExport() 
//  routine.  Each element of this array corresponds to the element of the 
//  pEntry array element with the same index.
//
//  Note: the boolean variable is stored as a DWORD for alignment purposes.
// -----------------------------------------------------------------------------
typedef struct _DirSyncAttributeInfo {      // (hungarian = ds)
    DWORD   fRequested;                     // TRUE=user requested this attribute
    LPTSTR  pszName;                        // the name of this attribute
} DIR_SYNC_ATTRIBUTE_INFO, *LPDIR_SYNC_ATTRIBUTE_INFO;

//$--REG_VARIABLE---------------------------------------------------------------
//  Structure used to map variables in memory to registry values.
//  This is used by routines which read and write data to the registry.
// -----------------------------------------------------------------------------
typedef struct _RevVariable {               // (hungarian = rv)
    LPTSTR  pszValueName;                   // name of registry value
    DWORD   dwType;                         // type of value (e.g. REG_DWORD)
    DWORD   cbData;                         // in: size of buffer, out: size of data
    LPVOID  pbData;                         // pointer to data buffer
} REG_VARIABLE, *LPREG_VARIABLE;

//
// Function Declarations
//

//$--HrOpenExport---------------------------------------------------------------
//  Function to do whatever initialization needs to be done before exporting 
//  records for directory synchronization.  It should return NOERROR if 
//  the initialization was successful and an error otherwise.  If this function 
//  returns an error then HrWriteExport() and HrCloseExport() will not be 
//  called.
// -----------------------------------------------------------------------------
HRESULT HrOpenExport(                       // RETURNS: HRESULT
    IN LPTSTR pszExportFile);               // file name from /EXPFILE

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
    IN DIR_SYNC_OPERATION eOperation);      // type of operation to do with object

//$--HrCloseExport--------------------------------------------------------------
//  Function to do whatever cleanup needs to be done after exporting records 
//  for directory synchronization.
// -----------------------------------------------------------------------------
HRESULT HrCloseExport(void);                // RETURNS: HRESULT

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
    IN  LPTSTR pszHomeServer);              // default home server for new mailbox

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
    OUT PDAPI_ENTRY * ppAttributes,         // list of attribute names
    OUT PDAPI_ENTRY * ppValues);            // list of attribute values2365


//$--HrCloseImport--------------------------------------------------------------
//  Function to do whatever cleanup needs to be done after importing records 
//  for directory synchronization.
// -----------------------------------------------------------------------------
HRESULT HrCloseImport(void);                // RETURNS: HRESULT

#endif
