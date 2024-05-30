/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    convert.c

Abstract:

    Implementation of the profile to profile conversion operations

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"
#include "Convert.h"

#ifdef ICM_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// EditColorSpaceDialog_DoModal
//
// Routine Description:
//   Creates the color space editing dialog
//
// Arguments:
//    LPLOGCOLORSPACE plcs         pointer to LOGCOLORSPACE
//    HWND            hWndParent   handle of the parent window
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EditColorSpaceDialog_DoModal(
    LPLOGCOLORSPACE plcs,
    HWND            hWndParent
)
{
    return DialogBoxParam(
        GetModuleHandle(0),
        MAKEINTRESOURCE(IDD_EDITCOLORSPACE_DIALOG),
        hWndParent,
        EditColorSpaceDialog_DialogProc,
        (LPARAM) plcs
    );
}

//////////////////////////////////////////////////////////////////////////
//
// EditColorSpaceDialog_DialogProc
//
// Routine Description:
//   Dialog procedure for the color space editing dialog
//
// Arguments:
//
// Return Value:
//   
//

BOOL
CALLBACK 
EditColorSpaceDialog_DialogProc(  
    HWND   hDlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    LPLOGCOLORSPACE plcs;

	switch (uiMsg) {

	case WM_INITDIALOG:
        plcs = (LPLOGCOLORSPACE) lParam;
        SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR) plcs);
        EditColorSpaceDialog_SetDialogData(hDlg, plcs);
        EditColorSpaceDialog_OnUpdateCSType(hDlg);
        break;

	case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDC_COLOR_SPACE_TYPE:
            if (HIWORD(wParam) == CBN_SELCHANGE) {

                EditColorSpaceDialog_OnUpdateCSType(hDlg);
            }
            break;

        case IDOK:
            plcs = (LPLOGCOLORSPACE) GetWindowLongPtr(hDlg, DWLP_USER);
            EditColorSpaceDialog_GetDialogData(hDlg, plcs);
            return EndDialog(hDlg, IDOK);

        case IDCANCEL:
            return EndDialog(hDlg, IDCANCEL);
        }
        break;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// EditColorSpaceDialog_SetDialogData
//
// Routine Description:
//   Initializes dialog controls according to the values in LOGCOLORSPACE
//
// Arguments:
//    HWND            hDlg    handle to the dialog
//    LPLOGCOLORSPACE plcc    pointer to LOGCOLORSPACE
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EditColorSpaceDialog_SetDialogData(
    HWND            hDlg,
    LPLOGCOLORSPACE plcs
)
{
    USES_BRESULT;

    HWND      hColorSpaceType;
    HWND      hIntent;
    HWND      hProfileName;
    HWND      hEndPointRX;
    HWND      hEndPointRY;
    HWND      hEndPointRZ;
    HWND      hEndPointGX;
    HWND      hEndPointGY;
    HWND      hEndPointGZ;
    HWND      hEndPointBX;
    HWND      hEndPointBY;
    HWND      hEndPointBZ;
    HWND      hGammaR;
    HWND      hGammaG;
    HWND      hGammaB;
    int       nSelectedCSType;
    int       nSelectedIntent;
    PBYTE     pBuffer = 0;

    // 
	
    CHECK(hColorSpaceType = GetDlgItem(hDlg, IDC_COLOR_SPACE_TYPE));
    
    CHECK(hIntent         = GetDlgItem(hDlg, IDC_INTENT));
    
    CHECK(hProfileName    = GetDlgItem(hDlg, IDC_PROFILE_NAME));

    CHECK(hEndPointRX     = GetDlgItem(hDlg, IDC_ENDPOINT_R_X));
    CHECK(hEndPointRY     = GetDlgItem(hDlg, IDC_ENDPOINT_R_Y));
    CHECK(hEndPointRZ     = GetDlgItem(hDlg, IDC_ENDPOINT_R_Z));

    CHECK(hEndPointGX     = GetDlgItem(hDlg, IDC_ENDPOINT_G_X));
    CHECK(hEndPointGY     = GetDlgItem(hDlg, IDC_ENDPOINT_G_Y));
    CHECK(hEndPointGZ     = GetDlgItem(hDlg, IDC_ENDPOINT_G_Z));

    CHECK(hEndPointBX     = GetDlgItem(hDlg, IDC_ENDPOINT_B_X));
    CHECK(hEndPointBY     = GetDlgItem(hDlg, IDC_ENDPOINT_B_Y));
    CHECK(hEndPointBZ     = GetDlgItem(hDlg, IDC_ENDPOINT_B_Z));

    CHECK(hGammaR         = GetDlgItem(hDlg, IDC_GAMMA_R));
    CHECK(hGammaG         = GetDlgItem(hDlg, IDC_GAMMA_G));
    CHECK(hGammaB         = GetDlgItem(hDlg, IDC_GAMMA_B));

    // fill CSType

    CHECK(ComboBox_ResetContent(hColorSpaceType));

    CHECK(ComboBox_InsertString(
        hColorSpaceType,
        0, 
        ResourceString(IDS_CALIBRATED_RGB)
    ));

    CHECK(ComboBox_InsertString(
        hColorSpaceType,
        1, 
        ResourceString(IDS_SRGB)
    ));

    CHECK(ComboBox_InsertString(
        hColorSpaceType,
        2, 
        ResourceString(IDS_WINDOWS_COLOR_SPACE)
    ));

    CHECK(ComboBox_InsertString(
        hColorSpaceType,
        3, 
        ResourceString(IDS_LINKED_PROFILE)
    ));

    CHECK(ComboBox_InsertString(
        hColorSpaceType,
        4, 
        ResourceString(IDS_EMBEDDED_PROFILE)
    ));

    switch (plcs->lcsCSType) {
    
    case LCS_CALIBRATED_RGB:      nSelectedCSType = 0; break;
    case LCS_sRGB:                nSelectedCSType = 1; break;
    case LCS_WINDOWS_COLOR_SPACE: nSelectedCSType = 2; break; 
    case PROFILE_LINKED:          nSelectedCSType = 3; break;
    case PROFILE_EMBEDDED:        nSelectedCSType = 4; break;
    default: ASSERT(0);
    }

    CHECK(ComboBox_SetCurSel(
        hColorSpaceType, 
        nSelectedCSType
    ));

    
    // fill Intent

    CHECK(ComboBox_ResetContent(hIntent));

    CHECK(ComboBox_InsertString(
        hIntent, 
        0, 
        LCS_TO_TEXT(LCS_GM_IMAGES)
    ));

    CHECK(ComboBox_InsertString(
        hIntent, 
        1, 
        LCS_TO_TEXT(LCS_GM_GRAPHICS)
    ));

    CHECK(ComboBox_InsertString(
        hIntent, 
        2, 
        LCS_TO_TEXT(LCS_GM_BUSINESS)
    ));

    CHECK(ComboBox_InsertString(
        hIntent, 
        3, 
        LCS_TO_TEXT(LCS_GM_ABS_COLORIMETRIC)
    ));

    switch (plcs->lcsIntent) {
    
    case LCS_GM_IMAGES:            nSelectedIntent = 0; break;
    case LCS_GM_GRAPHICS:          nSelectedIntent = 1; break;
    case LCS_GM_BUSINESS:          nSelectedIntent = 2; break; 
    case LCS_GM_ABS_COLORIMETRIC:  nSelectedIntent = 3; break;
    default: ASSERT(0);
    }

    CHECK(ComboBox_SetCurSel(
        hIntent, 
        nSelectedIntent
    ));

    
    // fill profile

    CHECK(ComboBox_ResetContent(hProfileName));

    CHECK(ComboBox_AddString(
        hProfileName, 
        _T("")          // insert the empty string (no profile)
    ));

    if (plcs->lcsFilename[0] != '\0') {

        // insert the profile associated with the image

        CHECK(ComboBox_AddString(
            hProfileName, 
            plcs->lcsFilename
        ));
    }

    if (g_bICMFunctionalityPresent) {

        // insert the other profiles in the system

        ENUMTYPE  et = { 0 };
        PCTSTR    pProfileNameString;

        et.dwSize    = sizeof(et);
        et.dwVersion = ENUM_TYPE_VERSION;

        pBuffer = (PBYTE) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, 1024);

        CHECK(EnumColorProfiles_ReAlloc(&et, &pBuffer));
    
        for (
            pProfileNameString = (PCTSTR) pBuffer;
            *pProfileNameString;
            pProfileNameString += _tcslen(pProfileNameString) + 1
        ) {

            if (_tcscmp(plcs->lcsFilename, pProfileNameString) != 0) {

                CHECK(ComboBox_AddString(
                    hProfileName, 
                    pProfileNameString
                ));
            }
        }
    }

    CHECK(ComboBox_SetCurSel(
        hProfileName, 
        ComboBox_FindString(hProfileName, -1, plcs->lcsFilename)
    ));
    
    // set endpoints

    CHECK(SetFloat(
        hEndPointRX, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzRed.ciexyzX)
    ));

    CHECK(SetFloat(
        hEndPointRY, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzRed.ciexyzY)
    ));

    CHECK(SetFloat(
        hEndPointRZ, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzRed.ciexyzZ)
    ));

    CHECK(SetFloat(
        hEndPointGX, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzGreen.ciexyzX)
    ));

    CHECK(SetFloat(
        hEndPointGY, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzGreen.ciexyzY)
    ));

    CHECK(SetFloat(
        hEndPointGZ, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzGreen.ciexyzZ)
    ));

    CHECK(SetFloat(
        hEndPointBX, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzBlue.ciexyzX)
    ));

    CHECK(SetFloat(
        hEndPointBY, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzBlue.ciexyzY)
    ));

    CHECK(SetFloat(
        hEndPointBZ, 
        FXPT2DOT30_TO_FLPT(plcs->lcsEndpoints.ciexyzBlue.ciexyzZ)
    ));

    // set gamma

    CHECK(SetFloat(
        hGammaR, 
        FXPT16DOT16_TO_FLPT(plcs->lcsGammaRed)
    ));

    CHECK(SetFloat(
        hGammaG, 
        FXPT16DOT16_TO_FLPT(plcs->lcsGammaGreen)
    ));

    CHECK(SetFloat(
        hGammaB, 
        FXPT16DOT16_TO_FLPT(plcs->lcsGammaBlue)
    ));

    BEGIN_CLEANUP;

    if (pBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EditColorSpaceDialog_GetDialogData
//
// Routine Description:
//   Reads the data from dialog controls into the LOGCOLORSPACE
//
// Arguments:
//    HWND            hDlg    handle to the dialog
//    LPLOGCOLORSPACE plcc    pointer to LOGCOLORSPACE
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EditColorSpaceDialog_GetDialogData(
    HWND            hDlg,
    LPLOGCOLORSPACE plcs
)
{
    USES_BRESULT;

    HWND      hColorSpaceType;
    HWND      hIntent;
    HWND      hProfileName;
    HWND      hEndPointRX;
    HWND      hEndPointRY;
    HWND      hEndPointRZ;
    HWND      hEndPointGX;
    HWND      hEndPointGY;
    HWND      hEndPointGZ;
    HWND      hEndPointBX;
    HWND      hEndPointBY;
    HWND      hEndPointBZ;
    HWND      hGammaR;
    HWND      hGammaG;
    HWND      hGammaB;

    // 
	
    CHECK(hColorSpaceType = GetDlgItem(hDlg, IDC_COLOR_SPACE_TYPE));
    
    CHECK(hIntent         = GetDlgItem(hDlg, IDC_INTENT));
    
    CHECK(hProfileName    = GetDlgItem(hDlg, IDC_PROFILE_NAME));

    CHECK(hEndPointRX     = GetDlgItem(hDlg, IDC_ENDPOINT_R_X));
    CHECK(hEndPointRY     = GetDlgItem(hDlg, IDC_ENDPOINT_R_Y));
    CHECK(hEndPointRZ     = GetDlgItem(hDlg, IDC_ENDPOINT_R_Z));

    CHECK(hEndPointGX     = GetDlgItem(hDlg, IDC_ENDPOINT_G_X));
    CHECK(hEndPointGY     = GetDlgItem(hDlg, IDC_ENDPOINT_G_Y));
    CHECK(hEndPointGZ     = GetDlgItem(hDlg, IDC_ENDPOINT_G_Z));

    CHECK(hEndPointBX     = GetDlgItem(hDlg, IDC_ENDPOINT_B_X));
    CHECK(hEndPointBY     = GetDlgItem(hDlg, IDC_ENDPOINT_B_Y));
    CHECK(hEndPointBZ     = GetDlgItem(hDlg, IDC_ENDPOINT_B_Z));

    CHECK(hGammaR         = GetDlgItem(hDlg, IDC_GAMMA_R));
    CHECK(hGammaG         = GetDlgItem(hDlg, IDC_GAMMA_G));
    CHECK(hGammaB         = GetDlgItem(hDlg, IDC_GAMMA_B));

    // read color space type

    switch (ComboBox_GetCurSel(hColorSpaceType)) {
    
    case 0: plcs->lcsCSType = LCS_CALIBRATED_RGB;      break;
    case 1: plcs->lcsCSType = LCS_sRGB;                break;
    case 2: plcs->lcsCSType = LCS_WINDOWS_COLOR_SPACE; break; 
    case 3: plcs->lcsCSType = PROFILE_LINKED;          break;
    case 4: plcs->lcsCSType = PROFILE_EMBEDDED;        break;
    default: ASSERT(0);
    }

    // read intent

    switch (ComboBox_GetCurSel(hIntent)) {
    
    case 0: plcs->lcsIntent = LCS_GM_IMAGES;           break;
    case 1: plcs->lcsIntent = LCS_GM_GRAPHICS;         break;
    case 2: plcs->lcsIntent = LCS_GM_BUSINESS;         break; 
    case 3: plcs->lcsIntent = LCS_GM_ABS_COLORIMETRIC; break;
    default: ASSERT(0);
    }

    // read profile name

    CHECK(ComboBox_GetLBText(
        hProfileName, 
        ComboBox_GetCurSel(hProfileName), 
        plcs->lcsFilename
    ));

    // read endpoint values

    plcs->lcsEndpoints.ciexyzRed.ciexyzX = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointRX));

    plcs->lcsEndpoints.ciexyzRed.ciexyzY = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointRY));

    plcs->lcsEndpoints.ciexyzRed.ciexyzZ = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointRZ));

    plcs->lcsEndpoints.ciexyzGreen.ciexyzX = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointGX));

    plcs->lcsEndpoints.ciexyzGreen.ciexyzY = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointGY));

    plcs->lcsEndpoints.ciexyzGreen.ciexyzZ = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointGZ));

    plcs->lcsEndpoints.ciexyzBlue.ciexyzX = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointBX));

    plcs->lcsEndpoints.ciexyzBlue.ciexyzY = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointBY));

    plcs->lcsEndpoints.ciexyzBlue.ciexyzZ = 
        FLPT_TO_FXPT2DOT30(GetFloat(hEndPointBZ));

    // read gamma values

    plcs->lcsGammaRed = FLPT_TO_FXPT16DOT16(GetFloat(hGammaR));
    
    plcs->lcsGammaGreen = FLPT_TO_FXPT16DOT16(GetFloat(hGammaG));
    
    plcs->lcsGammaBlue = FLPT_TO_FXPT16DOT16(GetFloat(hGammaB));

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// EditColorSpaceDialog_OnUpdateCSType
//
// Routine Description:
//   Updates the enabled / disabled states of the controls accourding 
//   to the selected color space type
//
// Arguments:
//    HWND            hDlg    handle to the dialog
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
EditColorSpaceDialog_OnUpdateCSType(
    HWND            hDlg
)
{
    USES_BRESULT;

    HWND      hColorSpaceType;
    HWND      hIntent;
    HWND      hProfileName;
    HWND      hEndPointRX;
    HWND      hEndPointRY;
    HWND      hEndPointRZ;
    HWND      hEndPointGX;
    HWND      hEndPointGY;
    HWND      hEndPointGZ;
    HWND      hEndPointBX;
    HWND      hEndPointBY;
    HWND      hEndPointBZ;
    HWND      hGammaR;
    HWND      hGammaG;
    HWND      hGammaB;

    // 
	
    CHECK(hColorSpaceType = GetDlgItem(hDlg, IDC_COLOR_SPACE_TYPE));
    
    CHECK(hIntent         = GetDlgItem(hDlg, IDC_INTENT));
    
    CHECK(hProfileName    = GetDlgItem(hDlg, IDC_PROFILE_NAME));

    CHECK(hEndPointRX     = GetDlgItem(hDlg, IDC_ENDPOINT_R_X));
    CHECK(hEndPointRY     = GetDlgItem(hDlg, IDC_ENDPOINT_R_Y));
    CHECK(hEndPointRZ     = GetDlgItem(hDlg, IDC_ENDPOINT_R_Z));

    CHECK(hEndPointGX     = GetDlgItem(hDlg, IDC_ENDPOINT_G_X));
    CHECK(hEndPointGY     = GetDlgItem(hDlg, IDC_ENDPOINT_G_Y));
    CHECK(hEndPointGZ     = GetDlgItem(hDlg, IDC_ENDPOINT_G_Z));

    CHECK(hEndPointBX     = GetDlgItem(hDlg, IDC_ENDPOINT_B_X));
    CHECK(hEndPointBY     = GetDlgItem(hDlg, IDC_ENDPOINT_B_Y));
    CHECK(hEndPointBZ     = GetDlgItem(hDlg, IDC_ENDPOINT_B_Z));

    CHECK(hGammaR         = GetDlgItem(hDlg, IDC_GAMMA_R));
    CHECK(hGammaG         = GetDlgItem(hDlg, IDC_GAMMA_G));
    CHECK(hGammaB         = GetDlgItem(hDlg, IDC_GAMMA_B));

    // read color space type

    switch (ComboBox_GetCurSel(hColorSpaceType)) {
    
    case 0: // LCS_CALIBRATED_RGB
        EnableWindow(hProfileName, FALSE);
        EnableWindow(hEndPointRX, TRUE);
        EnableWindow(hEndPointRY, TRUE);
        EnableWindow(hEndPointRZ, TRUE);
        EnableWindow(hEndPointGX, TRUE);
        EnableWindow(hEndPointGY, TRUE);
        EnableWindow(hEndPointGZ, TRUE);
        EnableWindow(hEndPointBX, TRUE);
        EnableWindow(hEndPointBY, TRUE);
        EnableWindow(hEndPointBZ, TRUE);
        EnableWindow(hGammaR, TRUE);
        EnableWindow(hGammaG, TRUE);
        EnableWindow(hGammaB, TRUE);
        break;

    case 1: // LCS_sRGB
    case 2: // LCS_WINDOWS_COLOR_SPACE
        EnableWindow(hProfileName, FALSE);
        EnableWindow(hEndPointRX, FALSE);
        EnableWindow(hEndPointRY, FALSE);
        EnableWindow(hEndPointRZ, FALSE);
        EnableWindow(hEndPointGX, FALSE);
        EnableWindow(hEndPointGY, FALSE);
        EnableWindow(hEndPointGZ, FALSE);
        EnableWindow(hEndPointBX, FALSE);
        EnableWindow(hEndPointBY, FALSE);
        EnableWindow(hEndPointBZ, FALSE);
        EnableWindow(hGammaR, FALSE);
        EnableWindow(hGammaG, FALSE);
        EnableWindow(hGammaB, FALSE);
        break;

    case 3: // PROFILE_LINKED
    case 4: // PROFILE_EMBEDDED
        EnableWindow(hProfileName, TRUE);
        EnableWindow(hEndPointRX, FALSE);
        EnableWindow(hEndPointRY, FALSE);
        EnableWindow(hEndPointRZ, FALSE);
        EnableWindow(hEndPointGX, FALSE);
        EnableWindow(hEndPointGY, FALSE);
        EnableWindow(hEndPointGZ, FALSE);
        EnableWindow(hEndPointBX, FALSE);
        EnableWindow(hEndPointBY, FALSE);
        EnableWindow(hEndPointBZ, FALSE);
        EnableWindow(hGammaR, FALSE);
        EnableWindow(hGammaG, FALSE);
        EnableWindow(hGammaB, FALSE);
        break;

    default: ASSERT(0);
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_EditColorSpace
//
// Routine Description:
//   Edits the color space of the currently loaded DIB
//
// Arguments:
//    PBITMAPWINDOW pWin   pointer to the structure
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_EditColorSpace(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    LOGCOLORSPACE lcs;
    BOOL          bTemporaryFileCreated = FALSE;
    TCHAR         szTemporaryFileName[MAX_PATH];
    PBYTE         pNewDIB = 0;
    DWORD         dwNewOffBits = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // get the source profile name

    CHECK(GetColorSpaceFromDIB(
        pWin->m_pDIB, 
        &lcs,
        &bTemporaryFileCreated
    ));

    if (bTemporaryFileCreated) {

        _tcscpy(szTemporaryFileName, lcs.lcsFilename);
        _tcscpy(lcs.lcsFilename, ResourceString(IDS_EMBEDDED_PROFILE));
    }

    if (EditColorSpaceDialog_DoModal(&lcs, pWin->m_hWnd) == IDOK) {

        if (_tcscmp(lcs.lcsFilename, 
            ResourceString(IDS_EMBEDDED_PROFILE)) == 0) {

            _tcscpy(lcs.lcsFilename, szTemporaryFileName);
        }

        CHECK(ModifyDIBColorSpace(
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            &lcs,
            &pNewDIB,
            &dwNewOffBits
        ));

        CHECK(GlobalFree(pWin->m_pDIB) == 0);

        pWin->m_pDIB      = pNewDIB;
        pWin->m_dwOffBits = dwNewOffBits;
        pNewDIB           = 0;

        CHECK(BitmapWindow_OpenDocument(
            pWin,
            eAttachToDIB,
            pWin->m_szFileName
        ));
    }

    BEGIN_CLEANUP;

    if (bTemporaryFileCreated) {

        CHECK(DeleteFile(szTemporaryFileName));
    }

    if (pNewDIB) {

        CHECK(GlobalFree(pNewDIB) == 0);
    }

    return BRESULT;
}

#endif //ICM_ENABLED


#ifdef ICM_OUTSIDE_DC

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_TransformDIB
//
// Routine Description:
//   Transforms the currently loaded DIB into a new color space
//
// Arguments:
//    PBITMAPWINDOW pWin   pointer to the structure
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_TransformDIB(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    LOGCOLORSPACE lcs = { 0 };
    BOOL          bTemporaryFileCreated = FALSE;
    PBYTE         pProfileMemoryBuffer = 0;
    PBYTE         pNewDIB = 0;
    DWORD         dwNewOffBits = 0;
    PLOGPALETTE   pNewLogPal = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    lcs.lcsSignature = LCS_SIGNATURE;
    lcs.lcsVersion   = 0x400;
    lcs.lcsSize      = sizeof(lcs);
    lcs.lcsCSType    = LCS_WINDOWS_COLOR_SPACE;
    lcs.lcsIntent    = LCS_GM_IMAGES;

    if (EditColorSpaceDialog_DoModal(&lcs, pWin->m_hWnd) == IDOK) {

        if (lcs.lcsFilename[0] == '\0') {

            switch (lcs.lcsCSType) {

            case LCS_sRGB:
            case LCS_WINDOWS_COLOR_SPACE:
                _tcscpy(lcs.lcsFilename, g_szDefaultICMProfile);
                break;

            case LCS_CALIBRATED_RGB:

                CHECK(CreateProfileFromLogColorSpace(
                    &lcs,
                    &pProfileMemoryBuffer
                ));

                CHECK(SaveEmbeddedProfileToTempFile(
                    pProfileMemoryBuffer,
                    GlobalSize(pProfileMemoryBuffer),
                    lcs.lcsFilename
                ));

                bTemporaryFileCreated = TRUE;

                break;

            default:
                ASSERT(0);
            }
        }

        CHECK(ColorTransformDIB(
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &pNewDIB,
            &pNewLogPal,
            lcs.lcsFilename,
            lcs.lcsIntent,
            0,
            0,
            pWin->m_hWnd
        ));

        CHECK(GlobalFree(pWin->m_pDIB) == 0);

        pWin->m_pDIB      = pNewDIB;
        pNewDIB           = 0;

        CHECK(ModifyDIBColorSpace(
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            &lcs,
            &pNewDIB,
            &dwNewOffBits
        ));

        CHECK(GlobalFree(pWin->m_pDIB) == 0);

        pWin->m_pDIB      = pNewDIB;
        pWin->m_dwOffBits = dwNewOffBits;
        pNewDIB           = 0;

        CHECK(BitmapWindow_OpenDocument(
            pWin,
            eAttachToDIB,
            pWin->m_szFileName
        ));
    }

    BEGIN_CLEANUP;

    if (bTemporaryFileCreated) {

        CHECK(DeleteFile(lcs.lcsFilename));
    }

    if (pProfileMemoryBuffer) {

        CHECK(GlobalFree(pProfileMemoryBuffer) == 0);
    }

    if (pNewDIB) {

        CHECK(GlobalFree(pNewDIB) == 0);
    }

    if (pNewLogPal) {

        CHECK(GlobalFree(pNewLogPal) == 0);
    }

    return BRESULT;
}



//////////////////////////////////////////////////////////////////////////
//
// ProfileToProfileDialog_DoModal
//
// Routine Description:
//   Creates the profile to profile transformation dialog
//
// Arguments:
//    PPROFILETOPROFILEDIALOG pDlg         pointer to the struct
//    HWND                    hWndParent   handle of the parent window
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ProfileToProfileDialog_DoModal(
    PPROFILETOPROFILEDIALOG pDlg,
    HWND					hWndParent
)
{
    return DialogBoxParam(
        GetModuleHandle(0),
        MAKEINTRESOURCE(IDD_PROFILE_TO_PROFILE_DIALOG),
        hWndParent,
        ProfileToProfileDialog_DialogProc,
        (LPARAM) pDlg
    );
}

//////////////////////////////////////////////////////////////////////////
//
// ProfileToProfileDialog_DoModal
//
// Routine Description:
//   Dialog procedure for the profile to profile transformation dialog
//
// Arguments:
//
// Return Value:
//

BOOL
CALLBACK 
ProfileToProfileDialog_DialogProc(  
    HWND   hDlg,
    UINT   uiMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    PPROFILETOPROFILEDIALOG pDlg;

	switch (uiMsg) {

	case WM_INITDIALOG:
        pDlg = (PPROFILETOPROFILEDIALOG) lParam;
        SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR) pDlg);
        ProfileToProfileDialog_SetDialogData(hDlg, pDlg);
        break;

	case WM_COMMAND:
        switch (LOWORD(wParam)) {

        case IDOK:
            pDlg = (PPROFILETOPROFILEDIALOG) GetWindowLongPtr(hDlg, DWLP_USER);
            ProfileToProfileDialog_GetDialogData(hDlg, pDlg);
            return EndDialog(hDlg, IDOK);

        case IDCANCEL:
            return EndDialog(hDlg, IDCANCEL);
        }
        break;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
// ProfileToProfileDialog_SetDialogData
//
// Routine Description:
//   Initializes dialog controls according to the values in the struct
//
// Arguments:
//    HWND                    hDlg    handle to the dialog
//    PPROFILETOPROFILEDIALOG pDlg    pointer to the struct
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ProfileToProfileDialog_SetDialogData(
    HWND                    hDlg,
    PPROFILETOPROFILEDIALOG pDlg
)
{
    USES_BRESULT;

    HWND   hSourceProfile;
    HWND   hDestinationProfile;
    HWND   hIntent;
    int    nSelectedIntent;
    PBYTE  pBuffer = 0;

    // 
	
    CHECK(hSourceProfile      = GetDlgItem(hDlg, IDC_SOURCE_PROFILE));
    CHECK(hDestinationProfile = GetDlgItem(hDlg, IDC_DESTINATION_PROFILE));
    CHECK(hIntent             = GetDlgItem(hDlg, IDC_INTENT));

    // fill profiles

    CHECK(ComboBox_ResetContent(hSourceProfile));

    if (pDlg->m_lcsSrc.lcsFilename[0] != '\0') {

        // insert the profile associated with the image

        CHECK(ComboBox_AddString(
            hSourceProfile, 
            pDlg->m_lcsSrc.lcsFilename
        ));
    }

    if (g_bICMFunctionalityPresent) {

        // insert the other profiles in the system

        ENUMTYPE  et = { 0 };
        PCTSTR    pProfileNameString;

        et.dwSize    = sizeof(et);
        et.dwVersion = ENUM_TYPE_VERSION;

        pBuffer = (PBYTE) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, 1024);

        CHECK(EnumColorProfiles_ReAlloc(&et, &pBuffer));
    
        for (
            pProfileNameString = (PCTSTR) pBuffer;
            *pProfileNameString;
            pProfileNameString += _tcslen(pProfileNameString) + 1
        ) {

            if (_tcscmp(pDlg->m_lcsSrc.lcsFilename, pProfileNameString) != 0) {

                CHECK(ComboBox_AddString(
                    hSourceProfile, 
                    pProfileNameString
                ));

                CHECK(ComboBox_AddString(
                    hDestinationProfile, 
                    pProfileNameString
                ));
            }
        }
    }

    CHECK(ComboBox_SetCurSel(
        hSourceProfile, 
        ComboBox_FindString(hSourceProfile, -1, pDlg->m_lcsSrc.lcsFilename)
    ));   

    // fill Intent

    CHECK(ComboBox_ResetContent(hIntent));

    CHECK(ComboBox_InsertString(
        hIntent, 
        0, 
        LCS_TO_TEXT(LCS_GM_IMAGES)
    ));

    CHECK(ComboBox_InsertString(
        hIntent, 
        1, 
        LCS_TO_TEXT(LCS_GM_GRAPHICS)
    ));

    CHECK(ComboBox_InsertString(
        hIntent, 
        2, 
        LCS_TO_TEXT(LCS_GM_BUSINESS)
    ));

    CHECK(ComboBox_InsertString(
        hIntent, 
        3, 
        LCS_TO_TEXT(LCS_GM_ABS_COLORIMETRIC)
    ));

    switch (pDlg->m_lcsSrc.lcsIntent) {
    
    case LCS_GM_IMAGES:            nSelectedIntent = 0; break;
    case LCS_GM_GRAPHICS:          nSelectedIntent = 1; break;
    case LCS_GM_BUSINESS:          nSelectedIntent = 2; break; 
    case LCS_GM_ABS_COLORIMETRIC:  nSelectedIntent = 3; break;
    default: ASSERT(0);
    }

    CHECK(ComboBox_SetCurSel(
        hIntent, 
        nSelectedIntent
    ));

    BEGIN_CLEANUP;

    if (pBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// ProfileToProfileDialog_GetDialogData
//
// Routine Description:
//   Reads the data from dialog controls into the struct
//
// Arguments:
//    HWND                    hDlg    handle to the dialog
//    PPROFILETOPROFILEDIALOG pDlg    pointer to the struct
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ProfileToProfileDialog_GetDialogData(
    HWND                    hDlg,
    PPROFILETOPROFILEDIALOG pDlg
)
{
    USES_BRESULT;

    HWND      hSourceProfile;
    HWND      hDestinationProfile;
    HWND      hIntent;

    // 
	
    CHECK(hSourceProfile      = GetDlgItem(hDlg, IDC_SOURCE_PROFILE));
    CHECK(hDestinationProfile = GetDlgItem(hDlg, IDC_DESTINATION_PROFILE));
    CHECK(hIntent             = GetDlgItem(hDlg, IDC_INTENT));
    
    // read profile names

    pDlg->m_lcsSrc.lcsCSType = PROFILE_LINKED;

    CHECK(ComboBox_GetLBText(
        hSourceProfile, 
        ComboBox_GetCurSel(hSourceProfile), 
        pDlg->m_lcsSrc.lcsFilename
    ));

    pDlg->m_lcsDst.lcsCSType = PROFILE_LINKED;

    CHECK(ComboBox_GetLBText(
        hDestinationProfile, 
        ComboBox_GetCurSel(hDestinationProfile), 
        pDlg->m_lcsDst.lcsFilename
    ));

    // read intent

    pDlg->m_lcsSrc.lcsIntent = LCS_GM_ABS_COLORIMETRIC;

    switch (ComboBox_GetCurSel(hIntent)) {
    
    case 0: pDlg->m_lcsDst.lcsIntent = LCS_GM_IMAGES;           break;
    case 1: pDlg->m_lcsDst.lcsIntent = LCS_GM_GRAPHICS;         break;
    case 2: pDlg->m_lcsDst.lcsIntent = LCS_GM_BUSINESS;         break; 
    case 3: pDlg->m_lcsDst.lcsIntent = LCS_GM_ABS_COLORIMETRIC; break;
    default: ASSERT(0);
    }

    // read CMM

    BEGIN_CLEANUP;

    return BRESULT;
}


//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_TransformDIB
//
// Routine Description:
//   Transforms the currently loaded DIB from one profile to another
//
// Arguments:
//    PBITMAPWINDOW pWin   pointer to the structure
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_ProfileToProfile(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    PROFILETOPROFILEDIALOG Dlg;
    BOOL          bTemporaryFileCreated = FALSE;
    TCHAR         szTemporaryFileName[MAX_PATH];
    PBYTE         pProfileMemoryBuffer = 0;
    PBYTE         pNewDIB = 0;
    DWORD         dwNewOffBits = 0;
    PLOGPALETTE   pNewLogPal = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(GetColorSpaceFromDIB(
        pWin->m_pDIB, 
        &Dlg.m_lcsSrc,
        &bTemporaryFileCreated
    ));

    if (Dlg.m_lcsSrc.lcsFilename[0] == '\0') {

        switch (Dlg.m_lcsSrc.lcsCSType) {

        case LCS_sRGB:
        case LCS_WINDOWS_COLOR_SPACE:
            _tcscpy(Dlg.m_lcsSrc.lcsFilename, g_szDefaultICMProfile);
            break;

        case LCS_CALIBRATED_RGB:

            CHECK(CreateProfileFromLogColorSpace(
                &Dlg.m_lcsSrc,
                &pProfileMemoryBuffer
            ));

            CHECK(SaveEmbeddedProfileToTempFile(
                pProfileMemoryBuffer,
                GlobalSize(pProfileMemoryBuffer),
                Dlg.m_lcsSrc.lcsFilename
            ));

            bTemporaryFileCreated = TRUE;

            break;

        default:
            ASSERT(0);
        }
    }

    if (bTemporaryFileCreated) {

        _tcscpy(szTemporaryFileName, Dlg.m_lcsSrc.lcsFilename);
        _tcscpy(Dlg.m_lcsSrc.lcsFilename, ResourceString(IDS_EMBEDDED_PROFILE));
    }

    if (ProfileToProfileDialog_DoModal(&Dlg, pWin->m_hWnd) == IDOK) {

        // set source color space

        if (_tcscmp(Dlg.m_lcsSrc.lcsFilename, 
            ResourceString(IDS_EMBEDDED_PROFILE)) != 0) {

            CHECK(ModifyDIBColorSpace(
                pWin->m_pDIB,
                pWin->m_dwOffBits,
                &Dlg.m_lcsSrc,
                &pNewDIB,
                &dwNewOffBits
            ));

            CHECK(GlobalFree(pWin->m_pDIB) == 0);

            pWin->m_pDIB      = pNewDIB;
            pWin->m_dwOffBits = dwNewOffBits;
            pNewDIB           = 0;
        }

        // transform the bits

        CHECK(ColorTransformDIB(
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &pNewDIB,
            &pNewLogPal,
            Dlg.m_lcsDst.lcsFilename,
            Dlg.m_lcsDst.lcsIntent,
            0,
            0,
            pWin->m_hWnd
        ));

        CHECK(GlobalFree(pWin->m_pDIB) == 0);

        pWin->m_pDIB      = pNewDIB;
        pNewDIB           = 0;

        // set the new source color space

        CHECK(ModifyDIBColorSpace(
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            &Dlg.m_lcsDst,
            &pNewDIB,
            &dwNewOffBits
        ));

        CHECK(GlobalFree(pWin->m_pDIB) == 0);

        pWin->m_pDIB      = pNewDIB;
        pWin->m_dwOffBits = dwNewOffBits;
        pNewDIB           = 0;

        // reflect changes

        CHECK(BitmapWindow_OpenDocument(
            pWin,
            eAttachToDIB,
            pWin->m_szFileName
        ));
    }

    BEGIN_CLEANUP;

    if (bTemporaryFileCreated) {

        CHECK(DeleteFile(szTemporaryFileName));
    }

    if (pProfileMemoryBuffer) {

        CHECK(GlobalFree(pProfileMemoryBuffer) == 0);
    }

    if (pNewDIB) {

        CHECK(GlobalFree(pNewDIB) == 0);
    }

    if (pNewLogPal) {

        CHECK(GlobalFree(pNewLogPal) == 0);
    }

    return BRESULT;
}


#endif //ICM_OUTSIDE_DC
