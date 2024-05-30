/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    clipboard.c

Abstract:

    Implementation of the clipboard operations

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"
#include "global.h"

#include "BitmapWin.h"

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_PasteFromClipboard
//
// Routine Description:
//   Reads the image (if any) in the Windows clipboard
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_PasteFromClipboard(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    HANDLE hDIB = 0;
    PVOID  pDIB = 0;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(OpenClipboard(pWin->m_hWnd));
    
    // Attempt to read the bitmap data from the clipboard

#ifdef ICM_ENABLED

    if (IsClipboardFormatAvailable(CF_DIBV5)) {

        CHECK(hDIB = GetClipboardData(CF_DIBV5));

    } else 

#endif //ICM_ENABLED

    {
        if (IsClipboardFormatAvailable(CF_DIB)) {

            CHECK(hDIB = GetClipboardData(CF_DIB));

        } else {
            
            ERROR_MESSAGE(ResourceString(IDS_NO_DIB_DATA));
        }
    }

    CHECK(pDIB = (PBYTE) GlobalLock(hDIB));

    if (pWin->m_pDIB) {

        CHECK(GlobalFree(pWin->m_pDIB) == 0);
    }

    CHECK(pWin->m_pDIB = (PBYTE) GlobalDuplicate(pDIB));

    BEGIN_CLEANUP;

    if (pDIB) {

        GlobalUnlock(hDIB);
    }

    CHECK(CloseClipboard());

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_CopyToClipboard
//
// Routine Description:
//   Copies the current image to the Windows clipboard
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_CopyToClipboard(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    HANDLE  hDIBData = 0;
    PBYTE   pDIBData = 0;
    DWORD   dwDIBSize;
    DWORD   dwColorTableSize = 0;
    DWORD   dwProfileDataSize = 0;
    UINT    uClipboardFormat = 0;
    BOOL    bClipboardOpen = FALSE;

    ASSERT(BitmapWindow_AssertValid(pWin));

    ASSERT(pWin->m_pDIB);
        
    // Create a shareable memory region for the copied image

    CHECK(dwDIBSize = GlobalSize(pWin->m_pDIB));

    CHECK(hDIBData = (HANDLE) GlobalAlloc(
        GMEM_MOVEABLE | GMEM_DDESHARE,
        dwDIBSize
    ));

    CHECK(pDIBData = (PBYTE) GlobalLock(hDIBData));

    // First copy the header
    
    CopyMemory(
        pDIBData,
        pWin->m_pDIB,
        HeaderLength(pWin->m_pDIB)
    );

    // Fill in the header dependent data
    
    if (IsCoreHeader(pWin->m_pDIB)) {
    
        PBITMAPCOREHEADER pSrc = CastCoreHeader(pWin->m_pDIB);
        PBITMAPCOREHEADER pDst = CastCoreHeader(pDIBData);

        dwColorTableSize  = sizeof(RGBTRIPLE) * MaxNumColors(pSrc->bcBitCount);
        dwProfileDataSize = 0;
        uClipboardFormat  = CF_DIB;

    } else if (IsInfoHeader(pWin->m_pDIB)) {

        PBITMAPINFOHEADER pSrc = CastInfoHeader(pWin->m_pDIB);
        PBITMAPINFOHEADER pDst = CastInfoHeader(pDIBData);

        dwColorTableSize  = sizeof(RGBQUAD) * pSrc->biClrUsed;
        dwProfileDataSize = 0;
        uClipboardFormat  = CF_DIB;

        if (pSrc->biCompression == BI_BITFIELDS) {
            
            CopyMemory(
                (PBYTE) pDst + HeaderLength(pDst),
                (PBYTE) pSrc + HeaderLength(pSrc),
                3 * sizeof(DWORD)
            );
        }

    } else if (IsV4Header(pWin->m_pDIB)) {

        PBITMAPV4HEADER pSrc = CastV4Header(pWin->m_pDIB);
        PBITMAPV4HEADER pDst = CastV4Header(pDIBData);

        dwColorTableSize  = sizeof(RGBQUAD) * pSrc->bV4ClrUsed;
        dwProfileDataSize = 0;
        uClipboardFormat  = CF_DIB;

        switch (g_OS) {

        case OS_WIN32s:
        case OS_WINNT3:
            pDst->bV4Size = sizeof(BITMAPINFOHEADER);
        }

    } else if (IsV5Header(pWin->m_pDIB)) {

        PBITMAPV5HEADER pSrc  = CastV5Header(pWin->m_pDIB);
        PBITMAPV5HEADER pDst  = CastV5Header(pDIBData);

        dwColorTableSize      = sizeof(RGBQUAD) * pSrc->bV5ClrUsed;

        switch (g_OS) {

        case OS_WIN32s:
        case OS_WINNT3:
            pDst->bV5Size     = sizeof(BITMAPINFOHEADER);
            dwProfileDataSize = 0;
            uClipboardFormat  = CF_DIB;
            break;

        case OS_WIN95:
        case OS_WINNT4:
            pDst->bV5Size     = sizeof(BITMAPV4HEADER);
            dwProfileDataSize = 0;
            uClipboardFormat  = CF_DIB;
            break;
        
        case OS_WIN98:
            dwProfileDataSize = pSrc->bV5ProfileSize;
            uClipboardFormat  = CF_DIB;
            break;

        case OS_WIN2000:
            dwProfileDataSize = pSrc->bV5ProfileSize;
            uClipboardFormat  = CF_DIBV5;
            break;
        }
    }

    // Next, copy the color table
    
    CopyMemory(
        ColorTable(pDIBData),
        ColorTable(pWin->m_pDIB),
        dwColorTableSize
    );

    // Next, copy the bitmap pixel data

    CopyMemory(
        (PBYTE) ColorTable(pDIBData) + dwColorTableSize, 
        pWin->m_pDIB + pWin->m_dwOffBits,
        SizeImage(pWin->m_pDIB)
    );

    // Next, copy the ICM profile (if present)

    if (dwProfileDataSize) {

        CastV5Header(pDIBData)->bV5ProfileData = 
            HeaderLength(pDIBData) 
            + dwColorTableSize 
            + SizeImage(pWin->m_pDIB);

        CopyMemory(
            ProfileData(pDIBData),
            ProfileData(pWin->m_pDIB),
            dwProfileDataSize
        );
    }

    // Send to the clipboard

    CHECK(bClipboardOpen = OpenClipboard(pWin->m_hWnd));

    CHECK(EmptyClipboard());

    CHECK(SetClipboardData(
        uClipboardFormat, 
        hDIBData
    ));

    BEGIN_CLEANUP;

    if (bClipboardOpen) {
    
        CHECK(CloseClipboard());
    }

    if (!BRESULT && hDIBData) {

        CHECK(GlobalFree(hDIBData) == 0);
    }

    return BRESULT;
}
    
