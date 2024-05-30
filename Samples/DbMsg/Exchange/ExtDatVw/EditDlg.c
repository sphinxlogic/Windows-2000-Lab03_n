// EditDlg.c -------------------------------------------------------------------
// Functions to support a dialog that lets the user select a property type and
// enter a data value for it.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "resource.h"

// -----------------------------------------------------------------------------

#define MAX_DATA_VALUE      600     // Maximum data value we can edit.

// -----------------------------------------------------------------------------
// Global handels to controls used in this module.
// -----------------------------------------------------------------------------

HWND hCboType       = NULL;
HWND hEditDataValue = NULL;

// -----------------------------------------------------------------------------
// Defined in ExtDatVw.C
// -----------------------------------------------------------------------------

extern LPSPropValue lpEditPropVal;  // Pointer to property to edit.
extern HWND         hAdminWnd;      // Handle to parent window.
extern TCHAR        szAdminTitle[]; // Title of parent window.

HRESULT HrFormatPrValue( 
    IN  LPSPropValue lpPropVal, // Ptr to property to format.
    OUT LPTSTR*      lppszBuf); // Ptr to ptr to allocated output buffer.

// -----------------------------------------------------------------------------
// Table to contain property types that we support the editing of.
// -----------------------------------------------------------------------------

typedef struct
{
    LPTSTR  lpsz;
    ULONG   ul;
} PropType;

#define PROP_TBL_ENTRY( PropName)      {TEXT( #PropName), PropName},

// Ordered by frequency of use.
PropType PropTypeArray[] =
{
    PROP_TBL_ENTRY( PT_STRING8)
    PROP_TBL_ENTRY( PT_LONG)
    PROP_TBL_ENTRY( PT_BOOLEAN)
    PROP_TBL_ENTRY( PT_I2)
    PROP_TBL_ENTRY( PT_R4)
    PROP_TBL_ENTRY( PT_DOUBLE)
};

//$--OnInitDialog()-------------------------------------------------------------
// Initialize the dialog.
// -----------------------------------------------------------------------------

static VOID OnInitDialog(
    IN HWND    hDlg)    // Dialog's window handle.
{
    HRESULT hr          = NOERROR;
    LPTSTR  lpszProp    = NULL;
    LPTSTR  lpszValue   = NULL;
    ULONG   iType       = 0;

    // Get the handle of the list box view control.
    hCboType = GetDlgItem( hDlg, IDC_CBO_TYPE);
    if( hCboType == NULL)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }
    
    // Get the handle of the list box view control.
    hEditDataValue = GetDlgItem( hDlg, IDC_EDIT_DATA_VALUE);
    if( hEditDataValue == NULL)
    {
        hr = HR_LOG( E_FAIL);
        goto cleanup;
    }

    // Initialize the combo box with data types that we allow entry on.
    for( iType = 0; iType < ARRAY_CNT( PropTypeArray); iType ++)
        SendMessage( hCboType, CB_ADDSTRING, 0, (LPARAM) PropTypeArray[ iType].lpsz);

    // Do we have initial data?
    if( !lpEditPropVal)
        // No initial data so default to first combo box item.
        SendMessage( hCboType, CB_SETCURSEL, 0, 0); 
    else
    {   // YES, we have initial data so initialize the controls.

        // Find the property type in the PropTypeArray and set combo box index
        // to the same index found in the array.
        // The combo box list is NOT sorted so there will be a one to one
        // correlation between the PropTypeArray and the items in the list.
        for( iType = 0; iType < ARRAY_CNT( PropTypeArray); iType ++)
        {   
            if( PROP_TYPE( lpEditPropVal->ulPropTag) == PropTypeArray[ iType].ul)
                SendMessage( hCboType, CB_SETCURSEL, (WPARAM) iType, 0);
        }
        
        // Format the property value into a string that the user can edit.
        hr = HrFormatPrValue( lpEditPropVal, &lpszProp);
        if( FAILED( hr))
            goto cleanup;

        lpszValue = _tcschr( lpszProp, TEXT( '\t')) + 1;
        if( lpszValue == (LPTSTR) 1)
        {   // This should have found the tab character in the formated string.
            hr = HR_LOG( E_FAIL);
            goto cleanup;
        }

        // Set the text of the edit control to the formated value.
        SetDlgItemText( hDlg, IDC_EDIT_DATA_VALUE, lpszValue);
        
        // This pointer currently points to unfreeable memory.  We will allocate 
        // data and set this to point to it later.  Until then we don't want anyone 
        // freeing data that should not be freed so we MUST set it to NULL to avoid 
        // potential problems later.
        lpEditPropVal = NULL;

        MAPIFREEBUFFER( lpszProp);
    }

cleanup:
    MAPIFREEBUFFER( lpszProp);
}

//$--OnCmdOk()------------------------------------------------------------------
// When the OK button is pressed we allocate a property value structure and save
// the users data in it.
// -----------------------------------------------------------------------------

static VOID OnCmdOk(
    IN HWND    hDlg)    // Dialog's window handle.
{
    HRESULT hr                           = 0;
    TCHAR   szDataValue[ MAX_DATA_VALUE] = {TEXT( '\0')};// Buffer for intermediate data.
    int     iType                        = 0;
    ULONG   ulPropType                   = 0;
    LPBYTE  lpbData                      = NULL;

    // Validate that the combo field has a selection.
    iType = SendMessage( hCboType, CB_GETCURSEL, 0, 0);
    if( iType == CB_ERR)
    {
        MessageBox( hAdminWnd, "You must select a data type.", szAdminTitle, MB_OK);
        SetFocus( hCboType);
        goto cleanup;
    }
    
    // Set the true MAPI property type from combo box selection.
    ulPropType = PropTypeArray[ iType].ul;

    // Get the data value entered by the user.
    GetDlgItemText( hDlg, IDC_EDIT_DATA_VALUE, szDataValue, sizeof( szDataValue));

    // Allocate a buffer to handle the biggest property we will need to deal with.
    hr = MAPIAllocateBuffer( sizeof( SPropValue) + MAX_DATA_VALUE, &lpEditPropVal);
    if( FAILED( hr))
        goto cleanup;

    // Set pointer to buffer of extra data.
    lpbData = ((LPBYTE) lpEditPropVal) + sizeof( SPropValue);

    // Set the property tag.  Using 1 for the ID keeps it from being 
    // considered invalid by some of the MAPI routines.
    lpEditPropVal->ulPropTag = PROP_TAG( ulPropType, 1);

    switch( ulPropType)
    {
        case PT_I2:
            lpEditPropVal->Value.i = (int) _ttol( szDataValue);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_LONG:
            lpEditPropVal->Value.l = _ttol( szDataValue);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_R4:
            lpEditPropVal->Value.flt = (float) atof( szDataValue);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_DOUBLE:
            lpEditPropVal->Value.dbl = atof( szDataValue);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_BOOLEAN:
            if( _tcsicmp( szDataValue, TEXT( "TRUE")) == 0)
            {
                lpEditPropVal->Value.b = TRUE;
                break;
            }
            else if( _tcsicmp( szDataValue, TEXT( "FALSE")) == 0)
            {
                lpEditPropVal->Value.b = FALSE;
                break;
            }
            
            MessageBox( hAdminWnd, "You must enter either TRUE or FALSE.", szAdminTitle, MB_OK);
            SetFocus( hEditDataValue);
            goto cleanup;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        case PT_STRING8:
            lpEditPropVal->Value.LPSZ = lpbData;
            lstrcpy( lpbData, szDataValue);
            break;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        default: 
            MessageBox( hAdminWnd, "Unknown property type.", szAdminTitle, MB_OK);
            SetFocus( hEditDataValue);
            goto cleanup;
    }
    
    // Normal termination.
    EndDialog( hDlg, IDOK);
    return;

cleanup:
    MAPIFREEBUFFER( lpEditPropVal);
}

//$--OnWmCommand()--------------------------------------------------------------
// Processes a command sent to the dialog box. In this case, commands are sent 
// to dialog box by the controls when the control values have changed or when
// a button is pressed.
// -----------------------------------------------------------------------------

static VOID OnWmCommand(
    IN HWND    hDlg,    // Dialog's window handle.
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam)  // Window message parameter2
{
    WORD wNotifyCode = HIWORD( wParam);     // Notification code
    WORD wID         = LOWORD( wParam);     // Id of control
     
    // Has an edit control changed or a button been clicked?
    if( wNotifyCode == EN_CHANGE || wNotifyCode == BN_CLICKED)
    {   // YES, so process the change or click.
        switch( wID)
        {
            case IDOK:
                OnCmdOk( hDlg);
                return;

            case IDCANCEL:
                EndDialog( hDlg, IDCANCEL);
                return;

            default:
                return;        
        }
    }
}

//$--EditDialogProc()-----------------------------------------------------------
// Dialog procedure for this dialog.
// -----------------------------------------------------------------------------

BOOL CALLBACK EditDialogProc( // RETURNS: TRUE if msg was processed.
    IN HWND    hDlg,    // Dialog's window handle.
    IN UINT    wMsg,    // Window message to be processed
    IN WPARAM  wParam,  // Window message parameter1
    IN LPARAM  lParam)  // Window message parameter2
{
    WORD wNotifyCode = HIWORD( wParam);     // Notification code
    WORD wID         = LOWORD( wParam);     // Id of control

    switch( wMsg)
    {
        case WM_INITDIALOG:
            OnInitDialog( hDlg);
            return( TRUE);

        case WM_COMMAND:
            OnWmCommand( hDlg, wParam, lParam);
            return( TRUE);

        default:
            return( FALSE);
    }
}

// -----------------------------------------------------------------------------
