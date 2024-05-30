/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    icm.c

Abstract:

    Implementation of the ICM functions

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"
#include "CMMman.h"

#ifdef ICM_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnColorSetup
//
// Routine Description:
//   Displays the color setup dialog UI
//   The color setup dialog is currently limited to one monitor only 
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   int           nMonitor  monitor index
//
// Return Value:
//   none
//

BOOL
BitmapWindow_OnColorSetup(
    PBITMAPWINDOW pWin,
    int           nMonitor
)
{
    USES_BRESULT;
    COLORMATCHSETUP cms;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // fill the COLORMATCHSETUP structure
    
    cms.dwSize    = sizeof(cms);
    cms.dwVersion = COLOR_MATCH_VERSION;

    cms.dwFlags = 0;

    if (pWin->m_bDisableICM) {

        cms.dwFlags |= CMS_DISABLEICM;
    }

    if (pWin->m_bEnableProofing) {

        cms.dwFlags |= CMS_ENABLEPROOFING;
    }

    cms.hwndOwner = pWin->m_hWnd;

    cms.pSourceName = 0;

    if (pWin->m_pDIB && IsV5Header(pWin->m_pDIB)) {

        USES_CONVERSION;

        switch (CastV5Header(pWin->m_pDIB)->bV5CSType) {

        case PROFILE_LINKED:
            cms.pSourceName = A2T((PCSTR) ProfileData(pWin->m_pDIB));
            break;

        case PROFILE_EMBEDDED:
            cms.pSourceName = ResourceString(IDS_EMBEDDED_PROFILE);
            break;
        }
    }

    cms.pDisplayName = pWin->m_Monitor[nMonitor].szName;
    cms.pPrinterName = pWin->m_szPrinterName;

    cms.dwFlags |= CMS_SETRENDERINTENT;
    cms.dwRenderIntent = LCS_TO_ICC(pWin->m_lcsRenderIntent);

    cms.dwFlags |= CMS_SETPROOFINTENT;
    cms.dwProofingIntent = LCS_TO_ICC(pWin->m_lcsProofIntent);

    // if the monitor profile is set in the BITMAPWINDOW structure, 
    // initialize the corresponding field in the COLORMATCHSETUP
    
    if (pWin->m_Monitor[nMonitor].szProfile[0] != '\0') {

        cms.dwFlags |= CMS_SETMONITORPROFILE;
    }

    cms.pMonitorProfile  = pWin->m_Monitor[nMonitor].szProfile;
    cms.ccMonitorProfile = COUNTOF(pWin->m_Monitor[nMonitor].szProfile);

    // if the printer profile is set in the BITMAPWINDOW structure, 
    // initialize the corresponding field in the COLORMATCHSETUP

    if (pWin->m_szPrinterProfile[0] != '\0') {

        cms.dwFlags |= CMS_SETPRINTERPROFILE;
    }

    cms.pPrinterProfile  = pWin->m_szPrinterProfile;
    cms.ccPrinterProfile = COUNTOF(pWin->m_szPrinterProfile);

    // if the target profile is set in the BITMAPWINDOW structure, 
    // initialize the corresponding field in the COLORMATCHSETUP

    if (pWin->m_szTargetProfile[0] != '\0') {

        cms.dwFlags |= CMS_SETTARGETPROFILE;
    }

    cms.pTargetProfile = pWin->m_szTargetProfile;
    cms.ccTargetProfile = COUNTOF(pWin->m_szTargetProfile);

    // we won't use a hook function

    cms.lpfnHook = 0;
    cms.lParam   = 0;

    // we will use the apply callback
    
    cms.dwFlags |= CMS_USEAPPLYCALLBACK;
    cms.lpfnApplyCallback   = ApplyCallbackFunction;
    cms.lParamApplyCallback = (LPARAM) pWin;

    // put up the color matching setup dialog

    if (SetupColorMatching(&cms)) {

        // if the result is success, call the "apply" function to
        // read the changed values

        ApplyCallbackFunction(
            &cms, 
            (LPARAM) pWin
        );

    } else {

        // if the user has pressed cancel, SetupColorMatching will fail 
        // and GetLastError will return ERROR_SUCCESS. If this is the case,
        // exit. If not, display the system error message

        DWORD dwLastError = GetLastError();

        if (dwLastError != ERROR_SUCCESS) {
        
            SYSTEM_ERROR_MESSAGE(dwLastError);
        }
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// ApplyCallbackFunction
//
// Routine Description:
//   Applies the changes in the color setup dialog to the 
//
// Arguments:
//  PCOLORMATCHSETUP pcms  pointer to the COLORMATCHSETUP structure
//  LPARAM lParam          pointer to the BITMAPWINDOW object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
WINAPI 
ApplyCallbackFunction(  
    PCOLORMATCHSETUP pcms,
    LPARAM           lParam
)
{
    USES_BRESULT;
    PBITMAPWINDOW pWin = (PBITMAPWINDOW) lParam;
    int           nMonitor;

    ASSERT(BitmapWindow_AssertValid(pWin));

    ASSERT((pcms->dwFlags & CMS_MONITOROVERFLOW) == 0);
    ASSERT((pcms->dwFlags & CMS_PRINTEROVERFLOW) == 0);
    ASSERT((pcms->dwFlags & CMS_TARGETOVERFLOW) == 0);

    pWin->m_bDisableICM     = pcms->dwFlags & CMS_DISABLEICM;
    pWin->m_bEnableProofing = pcms->dwFlags & CMS_ENABLEPROOFING;

    if (pcms->dwFlags & CMS_SETRENDERINTENT) {
    
        pWin->m_lcsRenderIntent = ICC_TO_LCS(pcms->dwRenderIntent);
    }

    if (pcms->dwFlags & CMS_SETPROOFINTENT) {
    
        pWin->m_lcsProofIntent = ICC_TO_LCS(pcms->dwProofingIntent);
    }

    // If <none> profile is specified, default to sRGB

    if (pWin->m_szPrinterProfile[0] == '\0') {

        _tcscpy(pWin->m_szPrinterProfile, g_szDefaultICMProfile);
    }

    if (pWin->m_szTargetProfile[0] == '\0') {

        _tcscpy(pWin->m_szTargetProfile, g_szDefaultICMProfile);
    }

    // If a DIB is loaded, apply ICM and redraw it

    if (pWin->m_pDIB) {

        for (nMonitor = 0; nMonitor < pWin->m_nNumMonitors; ++nMonitor) {

            if (pWin->m_Monitor[nMonitor].szProfile[0] == '\0') {

                _tcscpy(
                    pWin->m_Monitor[nMonitor].szProfile, 
                    g_szDefaultICMProfile
                );
            }

            CHECK(BitmapWindow_CreateDDB(
                pWin, 
                nMonitor
            ));
        }

        CHECK(InvalidateRect(
            pWin->m_hWnd, 
            0, 
            FALSE
        ));
    }

    BEGIN_CLEANUP;
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_OnCMMManager
//
// Routine Description:
//   Applies the changes in the color setup dialog to the 
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_OnCMMManager(
     PBITMAPWINDOW pWin
)
{
    return DialogBox(  
        g_hInstance,  
        MAKEINTRESOURCE(IDD_CMM_MANAGER_DIALOG),   
        pWin->m_hWnd,
        CMMDialog_DialogProc
    );
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_FillMonitorICMInfo
//
// Routine Description:
//   Fills the default ICM profile for the specified display monitor
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   int           nMonitor  index of the monitor 
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_FillMonitorICMInfo(
     PBITMAPWINDOW pWin,
     int           nMonitor
)
{
    USES_BRESULT;
    HDC hDC = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(hDC = CreateDC(
        pWin->m_Monitor[nMonitor].szName,
        0, 
        0, 
        0
    ));

    if (pWin->m_Monitor[nMonitor].szProfile[0] == '\0') {

        CHECK(GetDefaultICMProfile(
            hDC,
            pWin->m_Monitor[nMonitor].szProfile,
            sizeof(pWin->m_Monitor[nMonitor].szProfile)
        ));
    }

    BEGIN_CLEANUP;
    
    if (hDC) {

        CHECK(DeleteDC(hDC));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_FillPrinterICMInfo
//
// Routine Description:
//   Fills the default ICM profile for the specified printer
//
// Arguments:
//  PBITMAPWINDOW pWin    pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
BitmapWindow_FillPrinterICMInfo(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    HDC        hPrinterDC = 0;
    LPDEVNAMES pDevNames = 0;
    PDEVMODE   pDevMode = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    // get the name of the printer from DevNames struct

    pDevNames = (LPDEVNAMES) GlobalLock(pWin->m_hDevNames);

    if (!pDevNames) {

        pWin->m_szPrinterName[0] = '\0';
        pWin->m_szPrinterProfile[0] = '\0';

    } else {

        // we keep track of one printer only, so we need to know
        // if the printer name has changed or not

        BOOL bDefaultPrinterChanged = _tcscmp(
            pWin->m_szPrinterName, 
            (PTSTR)pDevNames + pDevNames->wDeviceOffset
        );
                
        if (bDefaultPrinterChanged) {

            _tcscpy(
                pWin->m_szPrinterName, 
                (PTSTR)pDevNames + pDevNames->wDeviceOffset
            );
        }

        // if the default printer has changed or if the profile name
        // is not found yet, get the default ICM profile for this 
        // printer

        if (bDefaultPrinterChanged || pWin->m_szPrinterProfile[0] == '\0') {

            CHECK(pDevMode = (PDEVMODE) GlobalLock(pWin->m_hDevMode));

            CHECK(hPrinterDC = CreateDC(
                0, 
                pWin->m_szPrinterName, 
                0, 
                pDevMode
            ));

            CHECK(GetDefaultICMProfile(
                hPrinterDC, 
                pWin->m_szPrinterProfile,
                sizeof(pWin->m_szPrinterProfile)
            ));
        }
    }

    BEGIN_CLEANUP;
    
    if (hPrinterDC) {
        
        CHECK(DeleteDC(hPrinterDC));
    }

    if (pDevNames) {

        GlobalUnlock(pWin->m_hDevNames);
    }

    if (pDevMode) {

        GlobalUnlock(pWin->m_hDevMode);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_FillTwainICMInfo
//
// Routine Description:
//   Fill the ICM information fields in the BITMAPWINDOW struct
//
// Arguments:
//  PBITMAPWINDOW pWin    pointer to the object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
BitmapWindow_FillTwainICMInfo(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;

    PSTI                    pSti = 0;
    PSTI_DEVICE_INFORMATION pdi  = 0;
    DWORD                   dwNumDevices;
    DWORD                   i;
    PWSTR                   pBuffer = (PWSTR) GlobalAlloc(GMEM_FIXED, 1024);

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (g_bSTIFunctionalityPresent) {

        CHECK(StiCreateInstance(
            GetModuleHandle(0),
            STI_VERSION,
            &pSti,
            0
        ) == S_OK);

        CHECK(IStillImage_GetDeviceList(
            pSti, 
            0,
            0,
            &dwNumDevices,
            (PVOID *) &pdi
        ) == S_OK);

        for (i = 0; i < dwNumDevices; ++i) {

            USES_CONVERSION;

            CHECK(GetDeviceValue_ReAlloc(
                pSti, 
                pdi[i].szDeviceInternalName,
                STI_DEVICE_VALUE_TWAIN_NAME,
                (PBYTE *) &pBuffer
            ));

            if (strcmp(W2A(pBuffer), pWin->m_SrcId.ProductName) == 0) {

                CHECK(GetDeviceValue_ReAlloc(
                    pSti, 
                    pdi[i].szDeviceInternalName,
                    STI_DEVICE_VALUE_ICM_PROFILE,
                    (PBYTE *) &pBuffer
                ));

                // Currently STI does not maintain a default profile.
                // We (arbitrarily) select the first returned profile.

                _tcscpy(pWin->m_szScannerProfile, W2T(pBuffer));
            }
        }

    } else {

        DWORD dwSize = sizeof(pWin->m_szScannerProfile);

        pWin->m_szScannerProfile[0] = '\0';

        GetFullColorProfileName(
            g_szDefaultICMProfile,
            pWin->m_szScannerProfile,
            &dwSize
        );
    }

    BEGIN_CLEANUP;

    if (pBuffer) {

        CHECK(GlobalFree(pBuffer) == 0);
    }

    if (pdi) {
    
        CHECK(LocalFree(pdi) == 0);
    }

    if (pSti) {
    
        CHECK(IStillImage_Release(pSti) == S_OK);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// GetDefaultICMProfile
//
// Routine Description:
//   Gets the ICM profile for the given DC
//
// Arguments:
//  HDC   hDC           a DC from which to retrieve the color profile
//  PTSTR pProfileName  the buffer that receives the path name of the profile
//  DWORD dwBufferSize  the size of the buffer
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
GetDefaultICMProfile(
    HDC   hDC,
    PTSTR pProfileName,
    DWORD dwBufferSize
)
{
    BOOL  bResult = TRUE;
    DWORD dwSize;

    // try to get the associated profile name through GetICMProfile

    dwSize = dwBufferSize;

    bResult = GetICMProfile(
        hDC, 
        &dwSize,
        pProfileName
    );

    if (!bResult) {

        // if that fails, try to get the standard profile name

        dwSize = dwBufferSize;

        bResult = GetStandardColorSpaceProfile(
            0, 
            LCS_WINDOWS_COLOR_SPACE, 
            pProfileName, 
            &dwSize
        );

        if (!bResult) {

            // if that also fails, form a profile name using 
            // the color directory name and g_szDefaultICMProfile

            dwSize = dwBufferSize;

            GetFullColorProfileName(
                g_szDefaultICMProfile,
                pProfileName,
                &dwSize
            );

            bResult = TRUE;
        }
    }

    return bResult;
}

//////////////////////////////////////////////////////////////////////////
//
// ModifyDIBColorSpace
//
// Routine Description:
//   This routine links or embeds an ICM profile to a DIB.
//   Converts the DIB header to BITMAPV5HEADER if needed.
//
// Arguments:
//   PBYTE           pOldDIB         original packed DIB
//   DWORD           dwOldOffBits    offset of pixels
//   LPLOGCOLORSPACE plcs            Pointer to the new color space
//   PBYTE           *ppNewDIB       modified packed DIB
//   DWORD           *pdwNewOffBits  offset of pixels
//   
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ModifyDIBColorSpace(
    PBYTE           pOldDIB,
    DWORD           dwOldOffBits,
    LPLOGCOLORSPACE plcs,
    PBYTE           *ppNewDIB,
    DWORD           *pdwNewOffBits
)
{
    USES_BRESULT; 
    USES_CONVERSION; 

    PBYTE           pNewDIB = 0;
    DWORD           dwNewOffBits = 0;
    PBITMAPV5HEADER pDst;
    HANDLE          hFile = INVALID_HANDLE_VALUE;
    PVOID           pProfileData = 0;
    DWORD           dwProfileSize;
    DWORD           dwNumColors;
    DWORD           dwImageSize;

    ASSERT(ppNewDIB && pdwNewOffBits);

    // Process profile data
    
    if (plcs->lcsCSType == PROFILE_EMBEDDED) {

        TCHAR szProfileName[MAX_PATH];
        DWORD dwSize = COUNTOF(szProfileName);

        CHECK(GetFullColorProfileName(
            plcs->lcsFilename,
            szProfileName,
            &dwSize
        ));

        CHECK((hFile = CreateFile(
            szProfileName,
            GENERIC_READ,
            FILE_SHARE_READ,
            0,
            OPEN_EXISTING,
            FILE_FLAG_SEQUENTIAL_SCAN,
            0
        )) != INVALID_HANDLE_VALUE);

        CHECK(dwProfileSize = GetFileSize(hFile, 0));

        CHECK(pProfileData = (PVOID) GlobalAlloc(
            GMEM_FIXED, 
            dwProfileSize
        ));

        CHECK(ReadFile(
            hFile,
            pProfileData,
            dwProfileSize,
            &dwProfileSize,
            0
        ));

    } else if (plcs->lcsCSType == PROFILE_LINKED) {

        pProfileData  = T2A(plcs->lcsFilename);
        dwProfileSize = strlen((PCSTR) pProfileData) + 1;

    } else {

        pProfileData  = 0;
        dwProfileSize = 0;
    }

    // Allocate memory for the new DIB

    dwNumColors = NumColors(pOldDIB);
    dwImageSize = SizeImage(pOldDIB);

    CHECK(pNewDIB = (PBYTE) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        sizeof(BITMAPV5HEADER)
        + dwNumColors * sizeof(RGBQUAD)
        + dwImageSize
        + dwProfileSize
    ));

    dwNewOffBits = sizeof(BITMAPV5HEADER) + dwNumColors * sizeof(RGBQUAD);

    // Copy the header information and the color table

    pDst = CastV5Header(pNewDIB);

    if (IsCoreHeader(pOldDIB)) {

        PBITMAPCOREHEADER pSrc = CastCoreHeader(pOldDIB);
        
        DWORD i;

        RGBTRIPLE *pSrcColorTable = 
            (RGBTRIPLE *) (pOldDIB + HeaderLength(pOldDIB));
        
        RGBQUAD *pDstColorTable = 
            (RGBQUAD *) (pNewDIB + sizeof(BITMAPV5HEADER));

        pDst->bV5Size          = sizeof(BITMAPV5HEADER);
        pDst->bV5Width         = pSrc->bcWidth;
        pDst->bV5Height        = pSrc->bcHeight;
        pDst->bV5Planes        = pSrc->bcPlanes;
        pDst->bV5BitCount      = pSrc->bcBitCount;
        pDst->bV5Compression   = BI_RGB;

        for (i = 0; i < dwNumColors; ++i) {
        
            pDstColorTable[i].rgbRed      = pSrcColorTable[i].rgbtRed;
            pDstColorTable[i].rgbGreen    = pSrcColorTable[i].rgbtGreen;
            pDstColorTable[i].rgbBlue     = pSrcColorTable[i].rgbtBlue;
            pDstColorTable[i].rgbReserved = 0;
        }

    } else {

        DWORD dwHeaderSize = HeaderLength(pOldDIB);

        if (
            IsInfoHeader(pOldDIB) && 
            CastInfoHeader(pOldDIB)->biCompression == BI_BITFIELDS
        ) {

            dwHeaderSize += 3 * sizeof(DWORD);
        }

        CopyMemory(
            pNewDIB,
            pOldDIB,
            dwHeaderSize
        );

        pDst->bV5Size = sizeof(BITMAPV5HEADER);

        CopyMemory(
            ColorTable(pNewDIB),
            ColorTable(pOldDIB),
            dwNumColors * sizeof(RGBQUAD)
        );
    }

    // copy the image data

    CopyMemory(
        pNewDIB + dwNewOffBits,
        pOldDIB + dwOldOffBits,
        dwImageSize
    );

    // fill in the new ICM profile data

    pDst->bV5CSType      = plcs->lcsCSType;
    pDst->bV5Endpoints   = plcs->lcsEndpoints;
    pDst->bV5GammaRed    = plcs->lcsGammaRed;
    pDst->bV5GammaGreen  = plcs->lcsGammaGreen;
    pDst->bV5GammaBlue   = plcs->lcsGammaBlue;
    pDst->bV5Intent      = plcs->lcsIntent;
    pDst->bV5ProfileSize = dwProfileSize;

    if (dwProfileSize != 0) {

        pDst->bV5ProfileData = dwNewOffBits + dwImageSize;

        CopyMemory(
            ProfileData(pDst),
            pProfileData,
            dwProfileSize
        );
    }

    BEGIN_CLEANUP;

    if (hFile != INVALID_HANDLE_VALUE) {

        CHECK(CloseHandle(hFile));

        if (pProfileData) {
        
            CHECK(GlobalFree(pProfileData) == 0);
        }
    }

    if (!BRESULT && pNewDIB) {

        CHECK(GlobalFree(pNewDIB) == 0);
        pNewDIB = 0;
    }

    *ppNewDIB      = pNewDIB;
    *pdwNewOffBits = dwNewOffBits;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// GetColorSpaceFromDIB
//
// Routine Description:
//   Fills a LOGCOLORSPACE structure according to the information in 
//   the DIB header
//
// Arguments:
//  PBYTE           pDIB          pointer to the DIB
//  LPLOGCOLORSPACE plcs          pointer to the output buffer
//  PBOOL pbTemporaryFileCreated  pointer to the "temp file created" flag
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
GetColorSpaceFromDIB(
    PBYTE           pDIB,
    LPLOGCOLORSPACE plcs,
    PBOOL           pbTemporaryFileCreated
)
{
    USES_BRESULT;

    *pbTemporaryFileCreated = FALSE;

    ZeroMemory(plcs, sizeof(LOGCOLORSPACE));

    plcs->lcsSignature  = LCS_SIGNATURE;
    plcs->lcsVersion    = 0x400;
    plcs->lcsSize       = sizeof(LOGCOLORSPACE);

    if (IsV4Header(pDIB)) {

        // this is V4 DIB, grab the fields from the header

        PBITMAPV4HEADER pV4h = CastV4Header(pDIB);

        plcs->lcsCSType     = pV4h->bV4CSType;
        plcs->lcsIntent     = LCS_GM_IMAGES;
        plcs->lcsEndpoints  = pV4h->bV4Endpoints;
        plcs->lcsGammaRed   = pV4h->bV4GammaRed;
        plcs->lcsGammaGreen = pV4h->bV4GammaGreen;
        plcs->lcsGammaBlue  = pV4h->bV4GammaBlue;

    } else if (IsV5Header(pDIB)) {

        // this is V5 DIB, grab the fields from the header

        PBITMAPV5HEADER pV5h = CastV5Header(pDIB);

        plcs->lcsCSType     = pV5h->bV5CSType;
        plcs->lcsIntent     = pV5h->bV5Intent;
        plcs->lcsEndpoints  = pV5h->bV5Endpoints;
        plcs->lcsGammaRed   = pV5h->bV5GammaRed;
        plcs->lcsGammaGreen = pV5h->bV5GammaGreen;
        plcs->lcsGammaBlue  = pV5h->bV5GammaBlue;

        if (pV5h->bV5CSType == PROFILE_LINKED) {

            // if we have a linked profile, copy the profile filename

            USES_CONVERSION;

            _tcsncpy(
                plcs->lcsFilename, 
                A2T((PCSTR) ProfileData(pV5h)), 
                COUNTOF(plcs->lcsFilename)
            );

        } else if (pV5h->bV5CSType == PROFILE_EMBEDDED) {

            // if we have an embedded profile, save it to a temp file, 

            CHECK(SaveEmbeddedProfileToTempFile(
                ProfileData(pV5h),
                pV5h->bV5ProfileSize,
                plcs->lcsFilename
            ));
            
            *pbTemporaryFileCreated = TRUE;
        }
    
    } else {

        // this is not a V4 or V5 DIB, assume the defaults

        plcs->lcsCSType = LCS_WINDOWS_COLOR_SPACE;
        plcs->lcsIntent = LCS_GM_IMAGES;
    }


    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SaveEmbeddedProfileToTempFile
//
// Routine Description:
//   Creates a temporary file and saves the embedded profile into it
//
// Arguments:
//  PVOID pProfileData    pointer to the profile data
//  DWORD dwProfileSize   size of the profile data
//  PTSTR pFileName       pointer to a buffer that will receive the temp filename
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
SaveEmbeddedProfileToTempFile(
    PVOID pProfileData,
    DWORD dwProfileSize,
    PTSTR pFileName
)
{
    USES_BRESULT;
    DWORD  dwNumWritten;
    TCHAR  szTempPath[MAX_PATH];
    HANDLE hFile = INVALID_HANDLE_VALUE;

    // get %TEMP% path

    CHECK(GetTempPath(
        COUNTOF(szTempPath), 
        szTempPath
    ));

    // create a temporary filename in %TEMP%

    CHECK(GetTempFileName(
        szTempPath, 
        _T("ICM"), 
        0, 
        pFileName
    ));

    CHECK((hFile = CreateFile(
        pFileName, 
        GENERIC_WRITE,
        0, 
        0, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_TEMPORARY, 
        0
    )) != INVALID_HANDLE_VALUE);

    // write the profile to the temporary file

    CHECK(WriteFile(
        hFile, 
        pProfileData,
        dwProfileSize,
        &dwNumWritten, 
        0
    ));

    BEGIN_CLEANUP;

    if (hFile != INVALID_HANDLE_VALUE) {
        
        CHECK(CloseHandle(hFile));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// GetFullColorProfileName
//
// Routine Description:
//   Turns the profile name to a fully qualified path name
//
// Arguments:
//   PCTSTR pProfileName   profile name
//   PTSTR  pPathName      the output buffer
//   PDWORD pdwSize        size in charachers of the output buffer
//   
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
GetFullColorProfileName(
    PCTSTR pProfileName,
    PTSTR  pPathName,
    PDWORD pdwSize
)
{
    DWORD dwPathNameLen    = 0;
    DWORD dwProfileNameLen = 0;

    if (!pdwSize) {

        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    // if there is no ':' or '/' or '\' in the filename
    // (i.e. there is no path information), we call GetColorDirectory()
    
    if ( 
        !_tcschr(pProfileName, ':') && 
        !_tcschr(pProfileName, '/') &&
        !_tcschr(pProfileName, '\\') 
    ) {

        DWORD dwSize = *pdwSize * sizeof(TCHAR);

        if (!GetColorDirectory(0, pPathName, &dwSize)) {

            return FALSE;
        }

        dwPathNameLen = _tcslen(pPathName);

        pPathName[dwPathNameLen++] = '\\';
    }

    dwProfileNameLen = _tcslen(pProfileName);

    if (*pdwSize < dwPathNameLen + dwProfileNameLen + 1) {

        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    } 

    *pdwSize = dwPathNameLen + dwProfileNameLen + 1;

    _tcscpy(
        pPathName + dwPathNameLen, 
        pProfileName
    );

    return TRUE;
}

#ifdef ICM_INSIDE_DC

//////////////////////////////////////////////////////////////////////////
//
// CreatePaletteAndDrawDIB_ICM
//
// Routine Description:
//   Sets up the destination DC for the color transformation,
//   prepares the palette and calls DrawDIB
//
// Arguments:
//  PBITMAPWINDOW pWin                pointer to the object  
//  HDC           hDC                 destination DC
//  HPALETTE      *phPalette          pointer to the palette to be created
//  PRECT         pRect               destination rectangle
//  PTSTR         pDestProfileName    name of the destination profile
//                                    or 0 if ICM is to be turned off
//  PTSTR         pTargetProfileName  name of the target profile
//                                    or 0 if proofing is not used
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CreatePaletteAndDrawDIB_ICM(
    HDC           hDC,
    PBYTE         pDIB,
    DWORD         dwOffBits,
    PLOGPALETTE   pLogPal,
    HPALETTE      *phPalette,
    PRECT         pRect,
    PTSTR         pDestProfileName,
    LCSGAMUTMATCH lcsDestIntent,
    PTSTR         pTargetProfileName,
    LCSGAMUTMATCH lcsTargetIntent
)
{
    USES_BRESULT;
    HCURSOR       hPrevCur = 0;
    HDC           hProofDC = 0;
    LOGCOLORSPACE lcs;
    BOOL          bTemporaryFileCreated = FALSE;
    HCOLORSPACE   hColorSpace = 0;
    HCOLORSPACE   hOldColorSpace = 0;
    int           nNumColors;
    RGBQUAD       *pNewColors = 0;
    PALETTEENTRY  *pNewPal = 0;
    int           i;

    BOOL bICMEnabled   = pDestProfileName && pDestProfileName[0] != '\0';
    BOOL bProofEnabled = pTargetProfileName && pTargetProfileName[0] != '\0';

    ASSERT(hDC);
    ASSERT(pDIB);
    ASSERT(pLogPal);
    ASSERT(phPalette);
    ASSERT(pRect);

    // this may be a lengthy operation, display the hourglass

    hPrevCur = SetCursor(LoadCursor(0, IDC_WAIT));

    // create the palette

    CHECK(*phPalette = pLogPal->palNumEntries ? 
        CreatePalette(pLogPal) : 
        CreateHalftonePalette(hDC)
    );

    if (!bICMEnabled) {

        // if we dont't have a destination profile, turn off ICM

        CHECK(SetICMMode(
            hDC, 
            ICM_OFF
        ));

    } else { 

        // Fill a LOGCOLORSPACE according to the information in the DIB
        // If a profile is embedded in the DIB, save it to a temporary file

        CHECK(GetColorSpaceFromDIB(
            pDIB, 
            &lcs,
            &bTemporaryFileCreated
        ));

        if (lcs.lcsFilename[0] != '\0') {
        
            lcs.lcsCSType = LCS_CALIBRATED_RGB;
        }
            
        lcs.lcsIntent = bProofEnabled ? lcsTargetIntent : lcsDestIntent;

        CHECK(hColorSpace = CreateColorSpace(&lcs));

        CHECK(hOldColorSpace = SetColorSpace(
            hDC,
            hColorSpace
        ));

        // set the destination profile

        CHECK(SetICMProfile(
            hDC,
            pDestProfileName
        ));

        // turn on ICM for the destination DC

        CHECK(SetICMMode(
            hDC, 
            ICM_ON
        ));

        if (bProofEnabled) {

            // if we are in proof mode, create another DC, turn on ICM mode
            // for that DC, set the target profile and enable proofing mode

            // for this inside DC ICM case, we can only take lcsTargetIntent 
            // into consideration (through LOGCOLORSPACE). If you want to
            // use lcsDestIntent also, you should use outside DC functions

            CHECK(hProofDC = CreateCompatibleDC(hDC));

            CHECK(SetICMProfile(
                hProofDC,
                pTargetProfileName
            ));
                
            CHECK(SetICMMode(
                hProofDC,
                ICM_ON
            ));

            CHECK(ColorMatchToTarget(
                hDC, 
                hProofDC, 
                CS_ENABLE
            ));
        }

        nNumColors = pLogPal->palNumEntries;

        if (nNumColors) {

            // if we have entries in the palette, color correct them

            CHECK(ColorCorrectPalette(
                hDC,
                *phPalette,
                0,
                nNumColors
            ));

            // Apply this new palette to the bitmap selected into hDC

            CHECK(pNewPal = (PALETTEENTRY *) GlobalAlloc(
                GMEM_FIXED, 
                nNumColors * sizeof(PALETTEENTRY)
            ));

            GetPaletteEntries(
                *phPalette,
                0,
                nNumColors,
                pNewPal
            );

            CHECK(pNewColors = (RGBQUAD *) GlobalAlloc(
                GMEM_FIXED, 
                nNumColors * sizeof(RGBQUAD)
            ));

            for (i = 0; i < nNumColors; ++i) {

                pNewColors[i].rgbRed      = pNewPal[i].peRed;
                pNewColors[i].rgbGreen    = pNewPal[i].peGreen;
                pNewColors[i].rgbBlue     = pNewPal[i].peBlue;
                pNewColors[i].rgbReserved = 0;
            }

            SetDIBColorTable(
                hDC,
                0,
                nNumColors,
                pNewColors
            );
        }
    }

    // copy the transformed DIB to the DIB section

    CHECK(DrawDIB(
        hDC,
        pDIB,
        dwOffBits,
        *phPalette,
        pRect
    ));

    BEGIN_CLEANUP;
    
    if (hProofDC) {

        CHECK(ColorMatchToTarget(
            hDC,
            hProofDC, 
            CS_DELETE_TRANSFORM
        ));

        CHECK(DeleteDC(hProofDC));
    }

    if (hOldColorSpace) {

        CHECK(SetColorSpace(
            hDC,
            hOldColorSpace
        ));
    }

    if (hColorSpace) {

        CHECK(DeleteColorSpace(hColorSpace)); 
    }

    if (bTemporaryFileCreated) {

        CHECK(DeleteFile(lcs.lcsFilename));
    }

    if (pNewColors) {

        CHECK(GlobalFree(pNewColors) == 0);
    }

    if (pNewPal) {

        CHECK(GlobalFree(pNewPal) == 0);
    }

    if (hPrevCur) {
        
        SetCursor(hPrevCur);
    }

    return BRESULT;
}

#endif //ICM_INSIDE_DC

#ifdef ICM_OUTSIDE_DC

//////////////////////////////////////////////////////////////////////////
//
// CreatePaletteAndDrawDIB_ICM
//
// Routine Description:
//   Performs the color transformation outside the DC, prepares the 
//   palette and calls DrawDIB
//
// Arguments:
//  PBITMAPWINDOW pWin                pointer to the object  
//  HDC           hDC                 destination DC
//  HPALETTE      *phPalette          pointer to the palette to be created
//  PRECT         pRect               destination rectangle
//  PTSTR         pDestProfileName    name of the destination profile
//                                    or 0 if ICM is to be turned off
//  PTSTR         pTargetProfileName  name of the target profile
//                                    or 0 if proofing is not used
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CreatePaletteAndDrawDIB_ICM(
    HDC           hDC,
    PBYTE         pDIB,
    DWORD         dwOffBits,
    PLOGPALETTE   pLogPal,
    HPALETTE      *phPalette,
    PRECT         pRect,
    PTSTR         pDestProfileName,
    LCSGAMUTMATCH lcsDestIntent,
    PTSTR         pTargetProfileName,
    LCSGAMUTMATCH lcsTargetIntent
)
{
    USES_BRESULT;
    HCURSOR       hPrevCur = 0;
    PBYTE         pNewDIB = 0;
    PLOGPALETTE   pNewLogPal = 0;
    int           nNumColors;
    RGBQUAD      *pNewColors = 0;
    int           i;

    BOOL bICMEnabled = pDestProfileName && pDestProfileName[0] != '\0';

    ASSERT(hDC);
    ASSERT(pDIB);
    ASSERT(pLogPal);
    ASSERT(phPalette);
    ASSERT(pRect);

    // this may be a lengthy operation, display the hourglass

    hPrevCur = SetCursor(LoadCursor(0, IDC_WAIT));

    if (!bICMEnabled) {

        CHECK(SetICMMode(
            hDC, 
            ICM_OFF
        ));

        pNewDIB    = pDIB;
        pNewLogPal = pLogPal;

    } else { 

        // turn off all color management inside DC

        CHECK(SetICMMode(
            hDC, 
            ICM_DONE_OUTSIDEDC
        ));

        // form the new transformed DIB

        CHECK(ColorTransformDIB(
            pDIB,
            dwOffBits,
            pLogPal,
            &pNewDIB,
            &pNewLogPal,
            pDestProfileName,
            lcsDestIntent,
            pTargetProfileName,
            lcsTargetIntent,
            0
        ));

        nNumColors = pNewLogPal->palNumEntries;

        if (nNumColors) { 
        
            // Apply this new palette to the bitmap selected into hDC

            CHECK(pNewColors = (RGBQUAD *) GlobalAlloc(
                GMEM_FIXED, 
                nNumColors * sizeof(RGBQUAD)
            ));

            for (i = 0; i < nNumColors; ++i) {

                pNewColors[i].rgbRed      = pNewLogPal->palPalEntry[i].peRed;
                pNewColors[i].rgbGreen    = pNewLogPal->palPalEntry[i].peGreen;
                pNewColors[i].rgbBlue     = pNewLogPal->palPalEntry[i].peBlue;
                pNewColors[i].rgbReserved = 0;
            }

            SetDIBColorTable(
                hDC,
                0,
                nNumColors,
                pNewColors
            );
        }
    }

    // create the palette (using the transformed logpalette)

    CHECK(*phPalette = pNewLogPal->palNumEntries ? 
        CreatePalette(pNewLogPal) : 
        CreateHalftonePalette(hDC)
    );

    // copy the transformed DIB to the DIB section

    CHECK(DrawDIB(
        hDC,
        pNewDIB,
        dwOffBits,
        *phPalette,
        pRect
    ));

    BEGIN_CLEANUP;
    
    if (pNewDIB && pNewDIB != pDIB) {

        CHECK(GlobalFree(pNewDIB) == 0);
    }

    if (pNewLogPal && pNewLogPal != pLogPal) {

        CHECK(GlobalFree(pNewLogPal) == 0);
    }

    if (pNewColors) {

        CHECK(GlobalFree(pNewColors) == 0);
    }

    if (hPrevCur) {
        
        SetCursor(hPrevCur);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// ColorTransformDIB
//
// Routine Description:
//  Transforms a DIB using outside DC ICM functions
//
// Arguments:
//  PBITMAPWINDOW pWin                pointer to the object  
//  PBYTE         *ppNewDIB           a double pointer that will receive
//                                    the transformed DIB
//  PLOGPALETTE   *ppNewLogPal        a double pointer that will receive
//                                    the transformed logpalette
//  PTSTR         pDestProfileName    name of the destination profile
//                                    or 0 if ICM is to be turned off
//  LCSGAMUTMATCH lcsDestIntent       intent for the destination
//  PTSTR         pTargetProfileName  name of the target profile
//                                    or 0 if proofing is not used
//  LCSGAMUTMATCH lcsTargetIntent     intent for the target
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ColorTransformDIB(
    PBYTE         pOldDIB,
    DWORD         dwOffBits,
    PLOGPALETTE   pOldLogPal,
    PBYTE         *ppNewDIB,
    PLOGPALETTE   *ppNewLogPal,
    PCTSTR        pDestProfileName,
    LCSGAMUTMATCH lcsDestIntent,
    PCTSTR        pTargetProfileName,
    LCSGAMUTMATCH lcsTargetIntent,
    HWND          hWnd
)
{
    USES_BRESULT;
    PBYTE         pNewDIB = 0;
    PLOGPALETTE   pNewLogPal = 0;
    LOGCOLORSPACE lcs;
    BOOL          bTemporaryFileCreated = FALSE;
    HPROFILE      hDestProfile = 0;
    HPROFILE      hTargetProfile = 0;
    HTRANSFORM    hTransform = 0;
    int           nBitCount;
    int           nNumColors;
    BMFORMAT      bmFormat;

    // First, create the transform

    BOOL bProofEnabled = pTargetProfileName && pTargetProfileName[0] != '\0';

    // Fill a LOGCOLORSPACE according to the information in the DIB
    // If a profile is embedded in the DIB, save it to a temporary file

    CHECK(GetColorSpaceFromDIB(
        pOldDIB, 
        &lcs,
        &bTemporaryFileCreated
    ));

    if (lcs.lcsFilename[0] != '\0') {
    
        lcs.lcsCSType = LCS_CALIBRATED_RGB;
    }
        
    lcs.lcsIntent = bProofEnabled ? lcsTargetIntent : lcsDestIntent;

    // Open the profiles

    CHECK(hDestProfile = OpenColorProfileFromFile(
        pDestProfileName
    ));

    if (bProofEnabled) {

        CHECK(hTargetProfile = OpenColorProfileFromFile(
            pTargetProfileName
        ));
    }

    if (!bProofEnabled || lcsDestIntent == LCS_GM_ABS_COLORIMETRIC) {

        // if we are not in the proof mode, use CreateColorTransform()

        // or we are in the proof mode, and the destination intent is 
        // set to the default, LCS_GM_ABS_COLORIMETRIC, we can still use
        // CreateColorTransform()

        CHECK(hTransform = CreateColorTransform(
            &lcs, 
            hDestProfile, 
            hTargetProfile, 
            BEST_MODE
        ));

    } else {

        // if proofing is enabled and the rendering intent is set to 
        // something other than absolute colorimetric, we need to 
        // create the transform with CreateMultiProfileTransform().

        // The transform first goes to the target profile and then 
        // to the destination profile

        HPROFILE ahProfiles[2];
        DWORD    adwIntents[2];

        ahProfiles[0] = hTargetProfile;
        ahProfiles[1] = hDestProfile;

        adwIntents[0] = LCS_TO_ICC(lcsTargetIntent);
        adwIntents[1] = LCS_TO_ICC(lcsDestIntent);

        CHECK(hTransform = CreateMultiProfileTransform(  
            ahProfiles,
            COUNTOF(ahProfiles),  
            adwIntents,  
            COUNTOF(adwIntents),
            BEST_MODE,
            INDEX_DONT_CARE
        ));
    }

    // Now that the transform is created, transform the actual bits 

    CHECK(pNewDIB = (PBYTE) GlobalDuplicate(pOldDIB));

    nBitCount = BitCount(pOldDIB);

    if (nBitCount > 8) {

        switch (nBitCount) {

        case 16:
            
            // if this is a 16 bit image, we must find out the number
            // of bits allocated to each color component.
            // 
            // By default, 5 bits are used for each component. But
            // in BITMAPINFOHEADER, if the biCompression field shows 
            // BI_BITFIELDS, the bmiColors member contains three 
            // DWORD color masks that specify the red, green, and blue 
            // components of each pixel. This location corresponds to 
            // the bV5RedMask, bV5GreenMask and bV5BlueMask fields in 
            // the V4 and V5 headers, so we can cast the header to a 
            // PBITMAPV5HEADER and read the mask values.
            // 
            // 16 bit images are not supported for BITMAPCOREHEADER, 
            // so we don't consider that case

            if (
                CastV5Header(pOldDIB)->bV5Compression == BI_BITFIELDS &&
                CastV5Header(pOldDIB)->bV5GreenMask   == 0x7E0
            ) {
                
                bmFormat = BM_565RGB;

            } else {
            
                bmFormat = BM_x555RGB;
            }

            break;
        
        case 24:
            bmFormat = BM_RGBTRIPLETS;
            break;

        case 32:
            bmFormat = BM_xRGBQUADS;
            break;
        }

        CHECK(TranslateBitmapBits(
            hTransform,
            pOldDIB + dwOffBits,
            bmFormat,
            abs(ImageW(pOldDIB)), 
            abs(ImageH(pOldDIB)), 
            0,
            pNewDIB + dwOffBits,
            bmFormat,
            0,
            ICMProgressProcCallback,
            (ULONG) hWnd
        ));
    }

    // transform the color table

    nNumColors = NumColors(pOldDIB);

    if (nNumColors > 0) {

        bmFormat = IsCoreHeader(pOldDIB) ? BM_RGBTRIPLETS : BM_xRGBQUADS;

        CHECK(TranslateBitmapBits(
            hTransform,
            ColorTable(pOldDIB),
            bmFormat,
            nNumColors, 
            1,
            0,
            ColorTable(pNewDIB),
            bmFormat,
            0,
            ICMProgressProcCallback,
            (ULONG) hWnd
        ));
    }

    // transform the log palette (notice the BM_xBGRQUADS format)

    CHECK(pNewLogPal = (PLOGPALETTE) GlobalDuplicate(pOldLogPal));

    nNumColors = pOldLogPal->palNumEntries;

    if (nNumColors) { 
    
        CHECK(TranslateBitmapBits(
            hTransform,
            pOldLogPal->palPalEntry,
            BM_xBGRQUADS,
            nNumColors, 
            1,
            0,
            pNewLogPal->palPalEntry,
            BM_xBGRQUADS,
            0,
            ICMProgressProcCallback,
            (ULONG) hWnd
        ));
    }

    BEGIN_CLEANUP;
    
    if (hTransform) {

        CHECK(DeleteColorTransform(hTransform));
    }

    if (hDestProfile) {

        CHECK(CloseColorProfile(hDestProfile));
    }

    if (hTargetProfile) {

        CHECK(CloseColorProfile(hTargetProfile));
    }

    if (bTemporaryFileCreated) {

        CHECK(DeleteFile(lcs.lcsFilename));
    }

    if (!BRESULT && pNewDIB) {
        
        CHECK(GlobalFree(pNewDIB) == 0);
        pNewDIB = 0;
    }

    if (!BRESULT && pNewLogPal) {
        
        CHECK(GlobalFree(pNewLogPal) == 0);
        pNewLogPal = 0;
    }

    *ppNewDIB    = pNewDIB;
    *ppNewLogPal = pNewLogPal;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// ICMProgressProcCallback
//
// Routine Description:
//   Callback function that displays the completion percentage.
//   This function will be called by TranslateBitmapBits during
//   lengthy transformations.
//
// Arguments:
//  ULONG ulMax             the maximum value of the progress counter 
//  ULONG ulCurrent         the current value of the progress counter
//  ULONG ulCallbackData    pointer to our BITMAPWINDOW object
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL 
WINAPI 
ICMProgressProcCallback(  
    ULONG  ulMax,  
    ULONG  ulCurrent,
    LPARAM ulCallbackData
)
{
    USES_BRESULT;
    TCHAR szPercentComplete[80];
    HWND  hWnd = (HWND) ulCallbackData;
    HDC   hDC = 0;

    ASSERT(ulMax);

    if (hWnd) {

        wsprintf(
            szPercentComplete,
            ResourceString(IDS_PERCENT_COMPLETE),
            ulCurrent * 100 / ulMax
        );

        CHECK(hDC = GetDC(hWnd));

        CHECK(TextOut(
            hDC, 
            0,
            0,
            szPercentComplete,
            _tcslen(szPercentComplete)
        ));
    }

    BEGIN_CLEANUP;

    if (hDC) {

        CHECK(ReleaseDC(hWnd, hDC));
    }
    
    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// OpenColorProfileFromFile
//
// Routine Description:
//   Opens a profile file
//
// Arguments:
//   PTSTR pProfileName  name of the profile to open
//
// Return Value:
//   Handle to the open profile / Zero on error
//

HPROFILE
OpenColorProfileFromFile(
    PCTSTR pProfileName
)
{
    USES_BRESULT;
    TCHAR    szPathName[MAX_PATH];
    DWORD    dwSize = COUNTOF(szPathName);
    HPROFILE hProfile = 0;
    PROFILE  profile;
    BOOL     bValid = TRUE;

    CHECK(GetFullColorProfileName(
        pProfileName,
        szPathName,
        &dwSize
    ));

    // open the color profile

    profile.dwType          = PROFILE_FILENAME;
    profile.pProfileData    = (PVOID) szPathName;
    profile.cbDataSize      = (_tcslen(szPathName) + 1) * sizeof(TCHAR);

    CHECK(hProfile = OpenColorProfile(
        &profile, 
        PROFILE_READ, 
        FILE_SHARE_READ, 
        OPEN_EXISTING
    ));

    // check that the profile is valid
        
    CHECK(IsColorProfileValid(
        hProfile, 
        &bValid
    ));

    if (!bValid) {

        CHECK(CloseColorProfile(hProfile));
        hProfile = 0;
        ERROR_MESSAGE(ResourceString(IDS_INVALID_PROFILE));
    }

    BEGIN_CLEANUP;

    return hProfile;
}

#endif //ICM_OUTSIDE_DC

#endif //ICM_ENABLED

