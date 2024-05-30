// Admin.C ---------------------------------------------------------------------
// Functions to support Exchange Admin Configuration Extension Dialogs for C 
// programs.  This does the majority of the handshaking necessary.
// (See ExAdmin.CPP for C++ support)
//
// This module is intended to be a generic MAIN source file for creating an 
// Exchange Administration DLL.  You could take this file and include it in your
// project as starting place for your DLL.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "retcode.h"
#include "admin.h"
#include "admin.chk"

HINSTANCE hDLLInst  = NULL;
BOOL      bReadOnly = FALSE;     // The mode is read only if TRUE.

ADMIN_AdministratorFunction* pAdminFunctions;  // Admin functions available to you.
ADMIN_ObjectInfo*            pAdminObjectInfo; // Admin server name and other useful DNs.

extern BOOL __stdcall _CRT_INIT( HINSTANCE, DWORD, LPVOID);

//$--LibMain--------------------------------------------------------------------
// Eported Function. Called when DLL is first loaded. 
// -----------------------------------------------------------------------------

BOOL APIENTRY LibMain(        // Returns TRUE if DLL has been initialized.
    IN HINSTANCE   hinstDLL,  // Handle to this DLL instance
    IN DWORD       dwReason,  // Reason DLL is being initialized.
    IN LPVOID      lpContext) // Context (not used) 
{
    // Set global instance variable.
    hDLLInst = hinstDLL;

    // Initialize the C Run Time DLL.
    if( dwReason == DLL_PROCESS_ATTACH || dwReason == DLL_THREAD_ATTACH )
    {
        if( _CRT_INIT( hinstDLL, dwReason, lpContext) == FALSE)
        {
            HR_LOG( E_FAIL);
            return( FALSE);
        }
    }

    return( TRUE);
}

//$--bInitSheet()---------------------------------------------------------------
// This function initializes the property sheet info and returns it to admin.
// 
// Since this piece of code is written to be a generic MAIN source file for
// creating an Exchange Administration DLL we use global data defined outside
// of this module to contain the information about the property sheet dialogs.
// You will need to make sure your code contains the following two globals:
//
//  1) ADMIN_SheetInfo rgSheetInfo[]                Array of info about your 
//                                                  property sheets.
//
//  2) int cSheetInfo = ARRAY_CNT( rgSheetInfo);    The count of property sheets
//                                                  in the array.
// -----------------------------------------------------------------------------

BOOL PASCAL bInitSheet(                 // RETURNS: TRUE if initialization OK
    IN  ADMIN_ObjectInfo* poi,          // Computer name & DN.
    IN  ULONG             fFlags,       // Tells us if it is read only or not.               
    OUT ADMIN_SheetInfo** ppSheetInfo,  // Property sheet description array
    OUT UINT*             pcsi,         // Number of property sheets
    OUT VOID**            ppNotUsed)    // Local data
{
    int              iSheet     = 0;

    DEBUGPUBLIC( "bInitSheet()\n");
    if( FAILED( CHK_bInitSheet( poi, fFlags, ppSheetInfo, pcsi, ppNotUsed)))
        return( FALSE);

    // Remember these for later usage.
    pAdminObjectInfo = poi;
    bReadOnly = (fFlags & fxfReadOnly) > 0;

    // Initialize Admin property sheet info array.
    for( iSheet = 0; iSheet < cSheetInfo; iSheet++)
    {   // Update each array item with info we know about.
        rgSheetInfo[ iSheet].hInstance = hDLLInst;
        rgSheetInfo[ iSheet].langid = MAKELANGID(LANG_ENGLISH,SUBLANG_NEUTRAL);
    }

    // Set return values.
    *pcsi = cSheetInfo;
    *ppSheetInfo = rgSheetInfo;
    *ppNotUsed = NULL;

    return( TRUE);
}

//$--DeinitSheet()--------------------------------------------------------------
// Admin calls this when the property sheet dialog box is about to be removed.
// -----------------------------------------------------------------------------

void PASCAL DeinitSheet(
    IN VOID* pNotUsed)           // Extension data. 
{
    DeinitSheet1();
}

//$--bInstallExtension()--------------------------------------------------------
// -----------------------------------------------------------------------------

BOOL PASCAL bInstallExtension(ADMIN_ObjectInfo * poi)
{
    return(TRUE);
}

//$--bDeinstallExtension()------------------------------------------------------
// -----------------------------------------------------------------------------

BOOL PASCAL bDeinstallExtension(ADMIN_ObjectInfo * poi)
{
    return(TRUE);
}


//$--bShowPage()----------------------------------------------------------------
// This is called once per standard property sheet.  Not at all for our property
// sheets.  If you want to disable some or all of the standard property sheets 
// then return FALSE for those default property sheets.
// -----------------------------------------------------------------------------

BOOL PASCAL bShowPage( UINT iddAdminPage)
{
    BOOL bRet = TRUE;   // Show the standard property sheet.
    return( bRet);
}

//$--iStartPage()---------------------------------------------------------------
// This function is called once durring initialization.  Return -1 to cause the 
// first standard property sheet to be displayed.  Or return the index of one of 
// our property sheets to have it come up first.
// -----------------------------------------------------------------------------

INT PASCAL iStartPage( void)
{
    int i = -1; // Default to the first standard property sheet.
    return( i);
}

//$--ADMIN_Initialize()---------------------------------------------------------
// Exported function. This is the first function called by admin after the DLL 
// has been initialized.
// -----------------------------------------------------------------------------

VOID PASCAL ADMIN_Initialize(
    IN  ADMIN_AdministratorConnections* pAdminConnections,  // Global Administrator Connections
    IN  ADMIN_AdministratorFunction*    pAdminFuncs,        // Global admin function
    OUT ADMIN_ExtensionFunction**       ppExtensionFunction)// Global Extension function
{
    DEBUGPUBLIC( "ADMIN_Initialize()\n");
    if( FAILED( CHK_ADMIN_Initialize( pAdminConnections, pAdminFuncs, ppExtensionFunction)))
        return;

    // We need to keep a global copy of admin's function pointers.
    pAdminFunctions = pAdminFuncs;

    // Tell admin where it can find the rest of our functions that it needs.
    *ppExtensionFunction = &extensionFunctions;  
}

// -----------------------------------------------------------------------------


// =============================================================================
// Miscelaneous support functions.  The above functions are required by admin.,
// the functions listed below are not.
// =============================================================================


//$--HrLoadExtData()------------------------------------------------------------
// Loads the extension data from Exchange Admin into an array of property values.
// -----------------------------------------------------------------------------

HRESULT HrLoadExtData(
    IN  HWND            hDlg,            // Handle of property sheet dialog.
    IN  LPTSTR          lpszExtDataName, // Name of extension data to retrieve.
    OUT ULONG*          lpcExtProps,     // Ptr to receive count of ext data properties. 
    OUT LPSPropValue*   lppExtProps)     // Ptr to ptr to extension data properties.
{
    HRESULT     hr               = NOERROR;
    RC          rc               = RC_SUCCESS;
    UINT        cTemp            = 0;
    ULONG       cRawExtData      = 0;    // Count of raw extension data blob.
    LPBYTE      lpbRawExtData    = NULL; // Ptr to raw extension data blob.
    LPWSTR      lpwszExtDataName = NULL; // Ptr to mapi allocated WIDE extension data name.

    //hr = CHK_HrLoadExtData( lpszExtDataName, lpcExtProps, lppExtProps);  
    //if( FAILED( hr))
        //RETURN( hr);

    // Make sure the property count starts at zero.
    *lpcExtProps = 0;

    // Convert extension data name string to a wide string 
    // which is required by Exchange Admin.
    hr = HrStrToStrW( lpszExtDataName, &lpwszExtDataName);
    if( FAILED( hr))
        goto cleanup;

    // Ask Exchange Admin the size of the buffer needed to hold the data.
    rc = pAdminFunctions->pfnGetObjectDataSize( hDlg, lpwszExtDataName, &cTemp);
    if( RC_FAILED( rc))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }
    
    // Convert UINT to a ULONG.
    cRawExtData = cTemp;

    // Allocate a buffer to hold the extension data returned from Exchange Admin.
    hr = MAPIAllocateBuffer( cRawExtData, (LPVOID*) &lpbRawExtData);
    if( FAILED( hr))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Get the extension data from Exchange Admin.
    rc = pAdminFunctions->pfnGetObjectData( hDlg, lpwszExtDataName, lpbRawExtData, cRawExtData);
    if( RC_FAILED(rc))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Unpack the Exchange Admin data into a MAPI style property value array.
    hr = HrCfgUnpackData( cRawExtData, lpbRawExtData, NULL, lpcExtProps, lppExtProps);
    if( FAILED( hr))
        goto cleanup;

cleanup:
    MAPIFREEBUFFER( lpwszExtDataName);
    MAPIFREEBUFFER( lpbRawExtData);

    RETURN( hr);
}

// -----------------------------------------------------------------------------
// Saves the extension data into an Exchange Admin buffer.  Admin will not 
// commit this data until the user presses the Apply or OK button.  However the
// changed data is then available to other property sheets.
// -----------------------------------------------------------------------------

HRESULT HrSaveExtData(
    IN  HWND            hDlg,            // Handle of property sheet dialog.
    IN  LPTSTR          lpszExtDataName, // Name of extension data to save.
    IN  ULONG           cExtProps,       // Count of ext data properties. 
    IN  LPSPropValue    lpExtProps,      // Ptr to extension data properties.
    IN  BOOL            bNew)            // Indicates the blob is new.
{
    HRESULT hr          = NOERROR;
    RC      rc          = RC_SUCCESS;
    ULONG   cExtData    = 0;
    LPBYTE  lpbExtData  = NULL;

    // Validate the data to save.
    if( cExtProps != 0 && !TEST_READ_PTR( lpExtProps, sizeof( SPropValue) * cExtProps))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Pack the configuration data from a MAPI style property value array 
    // into a format that Exchange Admin will be able to save.
    hr = HrCfgPackData( lpszExtDataName, cExtProps, lpExtProps, &cExtData, &lpbExtData);
    if( FAILED( hr))
        goto cleanup;
        
    // Set the extension data using Exchange Admin.
    rc = pAdminFunctions->pfnSetObjectData( hDlg, lpbExtData, cExtData, bNew);
    if( RC_FAILED(rc))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

cleanup:
    MAPIFREEBUFFER( lpbExtData);
    RETURN( hr);
}

//$--HrLoadDialogTemplate()-----------------------------------------------------
// Use this function to create child dialog box templates.  It will ensure that 
// the correct language and fonts are used.  
//
// To display the dialog use DialogBoxIndirect() which is a Windows SDK 
// function.
// -----------------------------------------------------------------------------

HRESULT HrLoadDialogTemplate(
    IN  UINT     iddDialog,     // Resource ID of dialog.
    OUT HGLOBAL* phDlgTemplate) // Ptr to var to store handle in.
{
    HRESULT hr = NOERROR;

    if( !pAdminFunctions->pfnLoadDialogResource( hDLLInst, iddDialog, 
            LANGIDFROMLCID(pAdminObjectInfo->lcid), (LPBYTE*) phDlgTemplate))
        hr = HR_LOG( E_FAIL);    

    RETURN( hr);
}

// -----------------------------------------------------------------------------
