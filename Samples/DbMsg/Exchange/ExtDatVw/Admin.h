// Admin.h ---------------------------------------------------------------------
// Functions to support Exchange Admin Configuration Extension Dialogs for C 
// programs.  This does the majority of the handshaking necessary.
// (See ExAdmin.H for C++ support)
//
// This module is intended to be a generic MAIN source file for creating an 
// Exchange Administration DLL.  You could take this file and include it in your
// project as starting place for your DLL.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __ADMIN_H__
#define __ADMIN_H__

#include "adminext.h"

// -----------------------------------------------------------------------------
// Functions that are required or used by Exchange Admin.
// -----------------------------------------------------------------------------

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

BOOL PASCAL bInitSheet(                 // RETURNS: TRUE if initialization OK
    IN  ADMIN_ObjectInfo* poi,          // Computer name & DN.
    IN  ULONG             fFlags,       // Tells us if it is read only or not.               
    OUT ADMIN_SheetInfo** ppSheetInfo,  // Property sheet description array
    OUT UINT*             pcsi,         // Number of property sheets
    OUT VOID**            ppNotUsed);   // Local data

// Admin calls this when the property sheet dialog box is about to be removed.
void PASCAL DeinitSheet(
    IN VOID* pNotUsed);          // Extension data. 

BOOL PASCAL bInstallExtension(ADMIN_ObjectInfo * poi);
BOOL PASCAL bDeinstallExtension(ADMIN_ObjectInfo * poi);

// This is called once per standard property sheet.  Not at all for our property
// sheets.  If you want to disable some or all of the standard property sheets 
// then return FALSE for those default property sheets.
BOOL PASCAL bShowPage( UINT iddAdminPage);

// This function is called once durring initialization.  Return -1 to cause the 
// first standard property sheet to be displayed.  Or return the index of one of 
// our property sheets to have it come up first.
INT PASCAL iStartPage( void);

// Exported function. This is the first function called by admin after the DLL 
// has been initialized.
VOID PASCAL ADMIN_Initialize(
    IN  ADMIN_AdministratorConnections* pAdminConnections,  // Global Administrator Connections
    IN  ADMIN_AdministratorFunction*    pAdminFuncs,        // Global admin function
    OUT ADMIN_ExtensionFunction**       ppExtensionFunction);// Global Extension function

// -----------------------------------------------------------------------------
// Miscelaneous support functions that are not required by Exchange Admin.
// -----------------------------------------------------------------------------

// Loads the extension data from Exchange Admin into an array of property values.
HRESULT HrLoadExtData(
    IN  HWND            hDlg,            // Handle of property sheet dialog.
    IN  LPTSTR          lpszExtDataName, // Name of extension data to retrieve.
    OUT ULONG*          lpcExtProps,     // Ptr to receive count of ext data properties. 
    OUT LPSPropValue*   lppExtProps);    // Ptr to ptr to extension data properties.

// Saves the extension data into an Exchange Admin buffer.  Admin will not 
// commit this data until the user presses the Apply or OK button.  However the
// changed data is then available to other property sheets.
HRESULT HrSaveExtData(
    IN  HWND            hDlg,            // Handle of property sheet dialog.
    IN  LPTSTR          lpszExtDataName, // Name of extension data to save.
    IN  ULONG           cExtProps,       // Count of ext data properties. 
    IN  LPSPropValue    lpExtProps,      // Ptr to extension data properties.
    IN  BOOL            bNew);           // Indicates the blob is new.

// Use this function to create child dialog box templates.  It will ensure that 
// the correct language and fonts are used.  
//
// To display the dialog use DialogBoxIndirect() which is a Windows SDK 
// function.
HRESULT HrLoadDialogTemplate(
    IN  UINT     iddDialog,     // Resource ID of dialog.
    OUT HGLOBAL* phDlgTemplate);// Ptr to var to store handle in.

// -----------------------------------------------------------------------------
// Global data declared in Admin.C
// -----------------------------------------------------------------------------

extern HINSTANCE hDLLInst;
extern BOOL      bReadOnly;     // The mode is read only if TRUE.

extern ADMIN_AdministratorFunction* pAdminFunctions;  // Admin functions available to you.
extern ADMIN_ObjectInfo*            pAdminObjectInfo; // Admin server name and other useful DNs.

// -----------------------------------------------------------------------------
// Globals and external functions that must be defined in the dialog code that 
// you write.  (See ExtDatVw.C as an example.)
// -----------------------------------------------------------------------------

// This is a list of functions that Exchange Admin will call.  You will need to
// fill this list with the address of your functions as well as some of the 
// functions contained in Admin.C.  
extern ADMIN_ExtensionFunction extensionFunctions;

// You will need to provide the resource ID of your dialogs, the address of your 
// dialog processing functions, and the resource ID of the string to place on 
// the property sheet tag.
extern ADMIN_SheetInfo rgSheetInfo[];
extern int cSheetInfo;  // Set to ARRAY_CNT( rgSheetInfo)

// External function to deinitialize first property sheet.  It should call the deinit
// for the second property sheet if there is one, and so on.
//
// You will need to implement this function in your code!
void DeinitSheet1(); 

// -----------------------------------------------------------------------------
#endif // __ADMIN_H__
