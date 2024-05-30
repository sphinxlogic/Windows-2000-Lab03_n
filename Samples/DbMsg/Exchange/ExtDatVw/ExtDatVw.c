// ExtDatVw.C ------------------------------------------------------------------
// Functions to process the main extension data viewer property sheet.  
// See Admin.H and Admin.C for main handshaking with Exchange Admin.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "retcode.h"
#include "admin.h"
#include "resource.h"
#include "PrValAry.h"

//----------------------------------------------------------------------------
// Some of the global data needed by this module.  See end of file for more.
//----------------------------------------------------------------------------

HWND    hAdminWnd           = NULL; // Handle to parent window.
HWND    hEditExtDataName    = NULL;
HWND    hLBView             = NULL;
HGLOBAL hEditDlgTemplate    = NULL;

BOOL    bExtDataHasChanged  = FALSE;

TCHAR   szAdminTitle[100]   = TEXT( "");    // Title of parent window.
TCHAR   szExtDataName[100]  = TEXT( "");
TCHAR   szSaveChangesMsg[]  = TEXT( "The extension data has been changed but not saved.  "
                                    "Do you wish to save your changes first?\n"
                                    "\n"
                                    "(press 'Yes' button followed by 'Apply' button to save changes)");
WNDPROC EditCtlWndProc      = NULL;

BOOL    bNewExtData         = TRUE;

#define PVA_EXPAND_AMT          10      // Amount to expand the array as it grows.
PropValArray    pvaExtProps     = {0};  // See PrValAry.H for this data structure.
LPSPropValue    lpEditPropVal   = NULL; // Pointer to property to edit.

//----------------------------------------------------------------------------
// Dialog procedure for the edit property dialog implemented in EditDlg.C.
//----------------------------------------------------------------------------

BOOL CALLBACK EditDialogProc( // RETURNS: TRUE if msg was processed.
    IN HWND    hDlg,    // Dialog's window handle.
    IN UINT    wMsg,    // Window message to be processed
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam);  // Window message parameter2

//----------------------------------------------------------------------------
// These integers control the size of the buffer we allocate for the 
// _vsnprintf() function call.  It grows when _vsnprintf() returns an
// error.  The effect is that we remember the largest buffer needed for
// string formating and always start off by allocating that size of buffer.
// This provides a safe string formating method.
//----------------------------------------------------------------------------

static int nLargestBuf = 256;  
static int nGrowSize = 128;

//----------------------------------------------------------------------------
// This performs a safe format with no memory overwrites.
//
// Takes arguments almost like sprintf().  The exception is that the first
// parameter is a pointer to a pointer to a buffer.  We dynamicaly allocate
// the buffer to the largest size we have encountered so far and increase it
// if needed.
//----------------------------------------------------------------------------

HRESULT HrFormat( 
    OUT LPTSTR* lppszBuf, // Ptr to ptr to allocated output buffer.
    IN  LPTSTR  pFmt,     // Ptr to format string.
    ...)                  // Any other parameters needed.
{
    HRESULT hr    = NOERROR;
    va_list pVArg = {0};

    va_start( pVArg, pFmt);

    for( ;;)
    {   // Take a shot at formating the string.
        hr = MAPIAllocateBuffer( nLargestBuf, lppszBuf);
        if( FAILED( hr))
            goto cleanup;

        if( _vsntprintf( *lppszBuf, nLargestBuf, pFmt, pVArg) >= 0)
           break;   // Format was successful.
            
        // Buffer was not big enough so enlarge it.
        nLargestBuf += nGrowSize;
        nGrowSize = (int) (nGrowSize * 3 / 2);
        
        // Free what we are not using so we can reallocate it.
        MAPIFREEBUFFER( *lppszBuf);
    }

cleanup:
    RETURN( hr);
}

// -----------------------------------------------------------------------------
// This formats the property value into a string buffer that you will have to 
// free using MAPIFreeBuffer.
//
// NOTE: A number of the possible property types don't have a conversion at
//       this time.
// -----------------------------------------------------------------------------

HRESULT HrFormatPrValue( 
    IN  LPSPropValue lpPropVal, // Ptr to property to format.
    OUT LPTSTR*      lppszBuf)  // Ptr to ptr to allocated output buffer.
{
    HRESULT     hr      = NOERROR;
    int         ii      = 0;
    unsigned    ui      = 0;
    double      dbl     = 0;
    LPTSTR      lpszBuf = NULL;
    LPBYTE      pByte   = NULL;    
    SYSTEMTIME  st      = {0};
    __UPV       upv     = lpPropVal->Value;

    switch( PROP_TYPE( lpPropVal->ulPropTag))
    {
        case PT_I2:
            ii = upv.i; // Convert short unsigned to regular unsigned.
            hr = HrFormat( lppszBuf, "PT_I2\t%d", ii);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_LONG:
            hr = HrFormat( lppszBuf, "PT_LONG\t%ld", upv.ul);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_R4:
            dbl = upv.flt;
            hr = HrFormat( lppszBuf, "PT_R4\t%g", dbl);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_DOUBLE:
            hr = HrFormat( lppszBuf, "PT_DOUBLE\t%g", upv.dbl);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_BOOLEAN:
            if( upv.b)
                hr = HrFormat( lppszBuf, "PT_BOOLEAN\tTRUE");
            else
                hr = HrFormat( lppszBuf, "PT_BOOLEAN\tFALSE");
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_SYSTIME:
            if( FileTimeToSystemTime( &upv.ft, &st))
                hr = HrFormat( lppszBuf, "PT_SYSTIME\t%.2d:%.2d:%.2d %.2d/%.2d/%.2d",
                    st.wHour, st.wMinute, st.wSecond,
                    st.wMonth, st.wDay, st.wYear);
            else
                hr = HrFormat( lppszBuf, "PT_SYSTIME\tError %lu converting file time to system time.", GetLastError());
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_STRING8:
            hr = HrFormat( lppszBuf, "PT_STRING8\t%s", upv.lpszA);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_BINARY:
            // Format the count and a place holder for up to 400 hex digits.
            hr = HrFormat( lppszBuf, "PT_BINARY\tCB:%d 0x%-400s", upv.bin.cb, TEXT( "PlaceHolder"));
            
            // Make sure we don't format more than 200 bytes (400 hex digits).
            if( upv.bin.cb > 200)
                ii = 200;
            else
                ii = upv.bin.cb;

            // Find "PlaceHolder" to set the starting point for formating.
            lpszBuf = _tcsstr( *lppszBuf, TEXT("PlaceHolder"));
            
            // Ptr to first byte in binary data to format.
            pByte = upv.bin.lpb;
            
            // Loop to format into hex digits.
            while( ii)
            {   // Format a single byte into a hex value and add to sRetVal.
                ui = *pByte;
                sprintf( lpszBuf, "%.2x", ui);
                
                // Next byte.
                lpszBuf += 2;
                pByte ++;
                ii --;
            }
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_ERROR:
        {
            hr = HrFormat( lppszBuf, "PT_ERROR\tError %.8lx", upv.err);
            break;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        default: 
            hr = HrFormat( lppszBuf, "PT_%d\thas no conversion at this time.", PROP_TYPE( lpPropVal->ulPropTag));
            break;
    }

    RETURN( hr);
}

//$--OnRefreshBtnClick()--------------------------------------------------------
// This is called when the refresh button is clicked or the extension data name 
// edit control loses focus.  We need to verify that the user has saved changes
// before we refresh.
// -----------------------------------------------------------------------------

static VOID OnRefreshBtnClick(
    IN HWND    hDlg)    // Dialog's window handle.
{
    HRESULT         hr          = NOERROR;
    ULONG           cExtProps   = 0;      // Count of ext data properties. 
    ULONG           iProp       = 0;      // Index to a single property.
    int             iSaveChanges= 0;      
    LPTSTR          lpszProp    = NULL;   // Formated property type and value for display.
    LPSPropValue    lpExtProps  = NULL;   // Ptr to extension data properties.

    // If extension data has changed make sure user wants to loose their changes.
    if( bExtDataHasChanged)
    {
        iSaveChanges = MessageBox( hDlg, szSaveChangesMsg, szAdminTitle, MB_YESNO);
        if( iSaveChanges == IDYES)
            return; // Cancel the REFRESH so user can press the apply button.
    }

    // At this point we know that data has been saved if it had been altered.

    // Get the extension data name from the edit control.
    GetDlgItemText( hDlg, IDC_EDIT_EXT_DATA_NAME, szExtDataName, sizeof( szExtDataName));

    // Return if extension data name has not been supplied.
    if( szExtDataName[0] == TEXT( '\0'))
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Free old property value array.
    PVA_Destroy( &pvaExtProps);

    // Clear the contents of the listbox.
    SendMessage( hLBView, LB_RESETCONTENT, 0, 0);

    // Apply could be enabled so use this flag to tell us 
    // not to save anything unless it really changes later.
    bExtDataHasChanged = FALSE;

    // Load the extension data as a property value array.  Ignore any
    // errors since they are expected.
    hr = HrLoadExtData( hDlg, szExtDataName, &cExtProps, &lpExtProps);   
    bNewExtData = FAILED( hr); // We expect this to fail if creating new extension data.

    // Initialize the property value array structure.
    hr = PVA_HrInit( &pvaExtProps, PVA_EXPAND_AMT, cExtProps, lpExtProps);
    if( FAILED( hr))
        goto cleanup;

    // Loop to display the property values.
    for( iProp = 0; iProp < cExtProps; iProp++)
    {
        hr = HrFormatPrValue( lpExtProps + iProp, &lpszProp);
        if( FAILED( hr))
            goto cleanup;

        SendMessage( hLBView, LB_ADDSTRING, 0, (LPARAM) lpszProp);
        MAPIFREEBUFFER( lpszProp);
    }
        
    // Leave a line at end of list for inserting at end.
    SendMessage( hLBView, LB_ADDSTRING, 0, (LPARAM) TEXT( "*** end ***"));

cleanup:
    if( FAILED( hr))
        SendMessage( hLBView, LB_RESETCONTENT, 0, 0); // Clear the contents of the listbox.

    return;
}

//$--OnWmKillFocus()------------------------------------------------------------
// Handles the kill focus for the extension data name edit control.  We need
// to refresh the list box if the user changed the extension data name.
// -----------------------------------------------------------------------------

static void OnWmKillFocus(
    IN HWND    hWnd,    // Window handle of edit control.
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam)  // Window message parameter2
{
    HWND hDlg = NULL;

    // If the extension data name has not change there is no need to refresh.
    if( szExtDataName[0] != TEXT('\0'))
        return; 

    // Get the parent dialog handle.
    hDlg = GetParent( hWnd);

    // Refresh the list box.
    OnRefreshBtnClick( hDlg);
}

//$--EditWindowProc()-----------------------------------------------------------
// Window procedure for the edit control.
// -----------------------------------------------------------------------------

BOOL CALLBACK EditWindowProc( // RETURNS: TRUE if msg was processed.
    IN HWND    hWnd,    // Window handle.
    IN UINT    wMsg,    // Window message to be processed
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam)  // Window message parameter2
{
    switch( wMsg)
    {
        case WM_KILLFOCUS:
            OnWmKillFocus( hWnd, wParam, lParam);
            // Intentionaly drop through to also do the default processing.

        default:
            return( CallWindowProc( EditCtlWndProc, hWnd, wMsg, wParam, lParam));
    }
}

// -----------------------------------------------------------------------------
// Initialize the dialog.
// -----------------------------------------------------------------------------

static VOID OnInitDialog(
    IN HWND    hDlg)    // Dialog's window handle.
{
    int nTabStops[] = {60};    // Array of tab stops.

    // Get the parent window handle.
    hAdminWnd = GetParent( hDlg);

    // Get the parent window title so we can use it in message boxes.
    GetWindowText( hAdminWnd, szAdminTitle, sizeof(szAdminTitle));
    
    // Tell admin where to find our ICON and TITLE controls so it can display
    // the standard picture and text.
    pAdminFunctions->pfnSetIcon( hDlg, IDC_ADMINICON);
    pAdminFunctions->pfnSetTitle( hDlg, IDC_TITLE);

    // Get the handle of the extension data name edit control.
    hEditExtDataName = GetDlgItem( hDlg, IDC_EDIT_EXT_DATA_NAME);
    if( hEditExtDataName == NULL)
    {
        HR_LOG( E_FAIL);
        return;
    }

    // Subclass the window procedure to capture the kill focus message.
    EditCtlWndProc = (WNDPROC) SetWindowLong( hEditExtDataName, GWL_WNDPROC, (LONG) EditWindowProc);

    // Get the handle of the list box view control.
    hLBView = GetDlgItem( hDlg, IDC_LB_VIEW);
    if( hLBView == NULL)
    {
        HR_LOG( E_FAIL);
        return; // Can't use goto since handle is invalid.
    }

    // Gives us an arbitrarly large amount of room to scroll horizontaly.
    SendMessage( hLBView, LB_SETHORIZONTALEXTENT, 4000, 0);

    // Set the tab stops.
    SendMessage( hLBView, LB_SETTABSTOPS, ARRAY_CNT( nTabStops), (LPARAM) ((int*) nTabStops));
}

//$--OnExtDataNameChange()------------------------------------------------------
// When the extension data name is changed this function is called.  We need to
// make sure the user has saved changes that may have been made to previous data.
// -----------------------------------------------------------------------------

static VOID OnExtDataNameChange(
    IN HWND    hDlg)    // Dialog's window handle.
{
    static BOOL bRecurse = FALSE;   // Used to avoid recursion 
    int iSaveChanges = 0;
    
    if( !bExtDataHasChanged)
        goto cleanup;

    if( bRecurse)
        goto cleanup;
    bRecurse = TRUE;

    iSaveChanges = MessageBox( hDlg, szSaveChangesMsg, szAdminTitle, MB_YESNO);
    if( iSaveChanges == IDYES)
    {   // This causes recursion.
        SetDlgItemText( hDlg, IDC_EDIT_EXT_DATA_NAME, szExtDataName);
        goto cleanup;
    }

    // Indicates the extension data to view has changed.
    szExtDataName[0] = TEXT( '\0');

    // Indicates the extension data has not changed.
    bExtDataHasChanged = FALSE;

cleanup:    
    bRecurse = FALSE;
}

//$--HrEditValue()--------------------------------------------------------------
// Supports editing of a property value when either the New or Modify button is 
// pressed.
// -----------------------------------------------------------------------------

static HRESULT HrEditValue(
    IN HWND hDlg,  // Dialog's window handle.
    IN BOOL bAdd)  // TRUE if adding a new one.
{
    HRESULT hr       = NOERROR;
    int     iRet     = 0;
    ULONG   ulCurSel = SendMessage( hLBView, LB_GETCURSEL, 0, 0);
    LPTSTR  lpszProp = NULL;   // Formated property type and value for display.
    
    if( ulCurSel == LB_ERR)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Don't let them modify the last item in the list which is only a place holder.
    if( !bAdd && ulCurSel == pvaExtProps.cTotal)
        goto cleanup;

    // Is this the first time we tried to edit data?
    if( !hEditDlgTemplate)
    {   // YES, so load and initialize the dialog template.
        hr = HrLoadDialogTemplate( IDD_EDIT, &hEditDlgTemplate);
        if( FAILED( hr))
            goto cleanup;
    }

    // Make data to edit available.
    if( bAdd)
        lpEditPropVal = NULL;
    else    
        lpEditPropVal = pvaExtProps.lpPropVal + ulCurSel;

    // Bring up the dialog to create the data.
    iRet = DialogBoxIndirect( hDLLInst, hEditDlgTemplate, hDlg, EditDialogProc);
    if( iRet == IDOK)
    {   // The user has wants to save his/her changes.
        if( !lpEditPropVal)
        {
            hr = HR_LOG( E_FAIL);
            goto cleanup;
        }
        
        // Insert or modify the array.
        if( bAdd)
            hr = PVA_HrInsert( &pvaExtProps, ulCurSel, lpEditPropVal);
        else
            hr = PVA_HrModify( &pvaExtProps, ulCurSel, lpEditPropVal);
        if( FAILED( hr))
            goto cleanup;

        // Format the edited data for display in the list box.
        hr = HrFormatPrValue( lpEditPropVal, &lpszProp);
        if( FAILED( hr))
            goto cleanup;

        // If modifying an existing one delete it and then reinsert it.
        if( !bAdd)
            SendMessage( hLBView, LB_DELETESTRING, ulCurSel, 0);

        // Insert modified data and set the selection to it.
        SendMessage( hLBView, LB_INSERTSTRING, ulCurSel, (LPARAM) lpszProp);
        if( bAdd)
            ulCurSel ++;
        SendMessage( hLBView, LB_SETCURSEL, ulCurSel, 0);

        // Free the formated data string.
        MAPIFREEBUFFER( lpszProp);
        
        pAdminFunctions->pfnInfoHasChanged( hDlg);
        bExtDataHasChanged = TRUE;
    }
    else if( iRet != IDCANCEL)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

cleanup:
    RETURN( hr);
}

//$--OnDeleteBtnClick()---------------------------------------------------------
// Delete a single property value from the array and list box.
// -----------------------------------------------------------------------------

static VOID OnDeleteBtnClick(
    IN HWND    hDlg)    // Dialog's window handle.
{
    HRESULT hr;
    ULONG   ulCurSel = SendMessage( hLBView, LB_GETCURSEL, 0, 0);
    
    if( ulCurSel == LB_ERR)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Don't let them delete the last item in the list which is only a place holder.
    if( ulCurSel == pvaExtProps.cTotal)
        goto cleanup;   

    // Delete the selected item from the array.
    hr = PVA_HrDelete( &pvaExtProps, ulCurSel);
    if( FAILED( hr))
        goto cleanup;

    // Delete the item for the list box and set the selection to the item below it.
    SendMessage( hLBView, LB_DELETESTRING, ulCurSel, 0);
    SendMessage( hLBView, LB_SETCURSEL, ulCurSel, 0);

    pAdminFunctions->pfnInfoHasChanged( hDlg);
    bExtDataHasChanged = TRUE;

cleanup:;
}

//$--OnWmCommand()--------------------------------------------------------------
// Processes a command sent to the dialog box. In this case, commands are sent 
// to a dialog box by the controls when the control values have changed or when
// a button is pressed.
// -----------------------------------------------------------------------------

static BOOL OnWmCommand(
    IN HWND    hDlg,    // Dialog's window handle.
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam)  // Window message parameter2
{
    HRESULT hr       = NOERROR;
    WORD wNotifyCode = HIWORD( wParam);     // Notification code
    WORD wID         = LOWORD( wParam);     // Id of control
     
    // Has an edit control changed or a button been clicked?
    if( wNotifyCode == EN_CHANGE || wNotifyCode == BN_CLICKED)
    {   // YES, so process the change or click.
        switch( wID)
        {
            case IDC_EDIT_EXT_DATA_NAME:
                OnExtDataNameChange( hDlg);
                return( TRUE);

            case IDC_BTN_REFRESH:
                OnRefreshBtnClick( hDlg);
                return( TRUE);

            case IDC_BTN_ADD:
                hr = HrEditValue( hDlg, TRUE);
                if( FAILED( hr));
                return( TRUE);

            case IDC_BTN_MODIFY:
                hr = HrEditValue( hDlg, FALSE);
                if( FAILED( hr));
                return( TRUE);

            case IDC_BTN_DELETE:
                OnDeleteBtnClick( hDlg);
                return( TRUE);

            default:
                return( FALSE);
        }
    }
}

//$--DialogProc() --------------------------------------------------------------
// Dialog procedure for the property sheet.
// -----------------------------------------------------------------------------

BOOL CALLBACK DialogProc( // RETURNS: TRUE if msg was processed.
    IN HWND    hDlg,    // Dialog's window handle.
    IN UINT    wMsg,    // Window message to be processed
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam)  // Window message parameter2
{
    switch( wMsg)
    {
        case WM_INITDIALOG:
            OnInitDialog( hDlg);
            return( TRUE);

        case WM_COMMAND:
            return( OnWmCommand( hDlg, wParam, lParam));

        case WM_CHILDACTIVATE:
            if( !bNewExtData)
                OnRefreshBtnClick( hDlg);
            return( TRUE);

        default:
            return( FALSE);
    }
}

//$--bSaveData()----------------------------------------------------------------
// Called by Exchange Admin when the property sheet page loses focus.  This is
// where all data needs to be saved so that other property sheets can have 
// access to it.  Exchange Admin will not commit the data to permanant media
// until the OK or APPLY button has been pressed.
// -----------------------------------------------------------------------------

BOOL PASCAL bSaveData(   // Returns: TRUE if successful.
    IN VOID* pNotUsed,       // Extension data for all sheets
    IN HWND  hDlg)           // Window handle of the property sheet.
{
    HRESULT hr   = NOERROR;
    BOOL    bRet = TRUE;

    DEBUGPUBLIC( "bSaveData()\n");
    //if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        //return( FALSE);

    // If our internal flag tells us that the data has not changed then don't save it.
    if( !bExtDataHasChanged)
        goto cleanup;
            
    // Packs the property value array and passes it to Exchange Admin for storage.
    hr = HrSaveExtData( hDlg, szExtDataName, pvaExtProps.cTotal, 
                        pvaExtProps.lpPropVal, bNewExtData);
    if( FAILED( hr))
    {
        bRet = FALSE;
        goto cleanup;
    }

    // The data is not new anymore.
    bNewExtData = FALSE;

    // Indicates the extension data has not changed.
    bExtDataHasChanged = FALSE;

    // Clear the extension data name (in memory) so it will refresh 
    // when we come back to form.  The name will still be on the form
    // so we can read it again later.
    szExtDataName[0] = TEXT( '\0');

cleanup:
    return( bRet);
}

//$--bCommitData()--------------------------------------------------------------
// This function is called by Exchange Admin when the user presses either the 
// OK or the APPLY buttons.  We do not save data here.  We do that in the 
// bSaveData() function.  Exchange Admin will commit the data to the data store
// if we return TRUE.
//
// Possible uses of this function are to allow you to display a message telling
// the user to restart an application or to save data to another location 
// besides the Exchange Admin managed data store.
// -----------------------------------------------------------------------------

BOOL PASCAL bCommitData(            // Returns:  TRUE if successful.
    IN VOID* pNotUsed,       // Extension data.
    IN HWND  hDlg)                  // Handle of the property sheet to be committed.
{
    DEBUGPUBLIC( "bCommitData()\n");
    //if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        //return( FALSE);

    return( TRUE);
}

//$--bHasHelp()-----------------------------------------------------------------
// Called by Exchange Admin to find out if we support help.
// -----------------------------------------------------------------------------

BOOL PASCAL bHasHelp(               // RETURNS: true if help is available.
    IN VOID* pNotUsed,       // Ext dll managed data area.
    IN HWND  hDlg)                  // Window handle of the property sheet.
{
    DEBUGPUBLIC( "bHasHelp()\n");
    //if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        //return( FALSE);

    return( FALSE);
}

//$--DoHelp()-------------------------------------------------------------------
// Called by Exchange Admin to displays help for the user.
// -----------------------------------------------------------------------------

VOID PASCAL DoHelp(
    IN VOID* pNotUsed,       // Ext dll managed data area.
    IN HWND  hDlg)           // Window handle of the property sheet.
{
    DEBUGPUBLIC( "DoHelp()\n");
    //if( FAILED( CHK_HrGeneral( pNotUsed, hDlg)))
        //return;
}

//$--DeinitSheet1()-------------------------------------------------------------
// This function will be called by the DeinitSheet() function in Admin.C.  If
// you were to implement more than one property sheet this function would need
// to call a DeinitSheet2() function for the next sheet and so on for each 
// additional sheet.
// -----------------------------------------------------------------------------

VOID DeinitSheet1()
{
    // Destroy the property value array.
    PVA_Destroy( &pvaExtProps);
    
    // If we loaded a dialog template we need to free it.
    if( hEditDlgTemplate)
        pAdminFunctions->pfnFreeDialogResource( (LPBYTE*) &hEditDlgTemplate);

    // Call other dialog's DeinitSheet functions here.
}

// =============================================================================
// Globals needed by Admin.C to perform the handshaking with Exchange Admin.
// =============================================================================

// -----------------------------------------------------------------------------
// These are pointers to the functions that Exchange Admin will want to access.
// -----------------------------------------------------------------------------

ADMIN_ExtensionFunction extensionFunctions =
{
    ADMIN_ExtensionAPIVersion,
    bInstallExtension,      // Found in Admin.C
    bDeinstallExtension,    // Found in Admin.C
    bInitSheet,             // Found in Admin.C
    bShowPage,              // Found in Admin.C
    iStartPage,             // Found in Admin.C
    bHasHelp,
    DoHelp,
    bSaveData,
    bCommitData,
    DeinitSheet             // Found in Admin.C
};

// -----------------------------------------------------------------------------
// This array contains a list of info for one property sheet.  If you were 
// writing a DLL that had more than one sheet you would need to provide a list 
// of information for each sheet.
// -----------------------------------------------------------------------------

ADMIN_SheetInfo rgSheetInfo[] =
{
    {   // List of info for a single property sheet.
        0,                   // Place holder for instance handle.
        IDD_EXT_DATA_VIEWER, // Resource ID of Dialog
        &DialogProc,         // DLGPROC      lpfnDlgProc;
        IDS_EXT_DATA_VIEWER, // Resource ID of name to place on tag.
        0,                   // LPARAM that will be passed to DlgProc on WM_INITDIALOG.
        0,                   // Place holder for language ID of dialog to be loaded.
    },
    // {More property sheet info could be added here.}
};

// Count of property sheets that we implement. (needed by admin.c)
int cSheetInfo = ARRAY_CNT( rgSheetInfo);

// -----------------------------------------------------------------------------
