/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    icon.c

Abstract:

    Implementation of the window icon drawing

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
// BitmapWindow_CreateIcon
//
// Routine Description:
//   Creates an icon based on the loaded image
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_CreateIcon(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    int     nIconW;
    int     nIconH;
    HDC     hDC = 0;
    HDC     hMemDC = 0;
    HBITMAP hBitmap = 0;
    HBITMAP hOldBitmap = 0;
    PBYTE   pANDMask = 0;
    PBYTE   pXORMask = 0;
    BITMAP  bm;
    RECT    rBitmap;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(nIconW = GetSystemMetrics(SM_CXICON));
    CHECK(nIconH = GetSystemMetrics(SM_CYICON));

    // Create a memory bitmap compatible with the display

    CHECK(hDC = GetDC(pWin->m_hWnd));

    CHECK(hMemDC = CreateCompatibleDC(hDC));

    CHECK(hBitmap = CreateCompatibleBitmap(
        hDC,
        nIconW, 
        nIconH
    ));

    CHECK(hOldBitmap = (HBITMAP) SelectObject(
        hMemDC,
        hBitmap
    ));

    CHECK(PatBlt(
        hMemDC,
        0, 0,
        nIconW, nIconH,
        BLACKNESS
    ));

    // Stretch the DIB to this new memory bitmap

    rBitmap.left   = 0;
    rBitmap.top    = 0;
    rBitmap.right  = nIconW;
    rBitmap.bottom = nIconH;

    CenterBitmap(
        pWin->m_nImageW,
        pWin->m_nImageH,
        &rBitmap,
        TRUE,
        TRUE
    );

    CHECK(DrawDIB(
        hMemDC,
        pWin->m_pDIB,
        pWin->m_dwOffBits,
        0,
        &rBitmap
    ));

    // Extract the bits from the memory bitmap

    CHECK(GetObject(
        hBitmap, 
        sizeof(bm), 
        &bm
    ));

    CHECK(pXORMask = (PBYTE) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        nIconW * nIconH * bm.bmBitsPixel / 8
    ));

    CHECK(GetBitmapBits(
        hBitmap,
        nIconW * nIconH * bm.bmBitsPixel / 8,
        pXORMask
    ));

    // Create the AND mask. 
    // Set the border regions as transparent using this AND mask

    CHECK(pANDMask = (PBYTE) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        nIconW * nIconH / 8
    ));

    // This one is hard coded for 32x32 icons.
    // Todo: extend this to the general case

    if (nIconW == 32) {

        DWORD nBitMask1 = 
            (rBitmap.right < 32 ? ((ULONG) -1 << rBitmap.right) : 0 ) | 
            ~((ULONG) -1 << rBitmap.left);

        DWORD nBitMask = 
            (nBitMask1 & 0xff000000) >> 24 |
            (nBitMask1 & 0x00ff0000) >> 8  |
            (nBitMask1 & 0x0000ff00) << 8  |
            (nBitMask1 & 0x000000ff) << 24;

        int y = 0;

        DWORD *pMask = (DWORD *) pANDMask;

        for (; y < rBitmap.top; ++y) {

            *pMask++ = (DWORD) -1;
        }

        for (; y < rBitmap.bottom; ++y) {
            
            *pMask++ = nBitMask;
        }

        for (; y < nIconH; ++y) {
            
            *pMask++ = (DWORD) -1;
        }
    }

    // and create the icon

    CHECK(pWin->m_hIcon = CreateIcon(
        g_hInstance,
        nIconW, nIconH,
        (BYTE) bm.bmPlanes,
        (BYTE) bm.bmBitsPixel,
        pANDMask,
        pXORMask
    ));

    CHECK(PostMessage(
        pWin->m_hWnd,
        WM_SETICON,
        ICON_BIG,
        (LPARAM) pWin->m_hIcon
    ));

    BEGIN_CLEANUP;

    if (pANDMask) {

        CHECK(GlobalFree(pANDMask) == 0);
    }

    if (pXORMask) {

        CHECK(GlobalFree(pXORMask) == 0);
    }

    if (hOldBitmap) {

        CHECK(SelectObject(hMemDC, hOldBitmap));
    }

    if (hBitmap) {

        CHECK(DeleteObject(hBitmap));
    }

    if (hMemDC) {

        CHECK(DeleteDC(hMemDC));
    }

    if (hDC) {

        CHECK(ReleaseDC(pWin->m_hWnd, hDC));
    }

    return BRESULT;
}

