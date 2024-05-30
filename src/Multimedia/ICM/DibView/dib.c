/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    dib.c

Abstract:

    Implementation of the bitmap manipulation functions

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
// BitmapWindow_ProcessHeader
//
// Routine Description:
//   Initializes internal BITMAPWINDOW fields according to the 
//   information from the bitmap header.
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_ProcessHeader(
    PBITMAPWINDOW pWin
)
{
    USES_BRESULT;
    DWORD i;

    ASSERT(BitmapWindow_AssertValid(pWin));

    if (IsCoreHeader(pWin->m_pDIB)) {

        DWORD nNumPalEntries;
        PBITMAPCOREHEADER pbmch = CastCoreHeader(pWin->m_pDIB);
        RGBTRIPLE *pColorTable = (RGBTRIPLE *) ColorTable(pbmch);

        pWin->m_nImageW = pbmch->bcWidth;
        pWin->m_nImageH = pbmch->bcHeight;

        // If the offset of the bitmap bits from the beginning of the header
        // is not set, determine its value and store it

        nNumPalEntries = MaxNumColors(pbmch->bcBitCount);

        if (!pWin->m_dwOffBits) {

            pWin->m_dwOffBits = 
                pbmch->bcSize + sizeof(RGBTRIPLE) * nNumPalEntries;
        }

        // Extract the palette information
 
        CHECK(pWin->m_pLogPal = (PLOGPALETTE) GlobalAlloc(
            GMEM_FIXED, 
            sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * (nNumPalEntries - 1)
        ));

        pWin->m_pLogPal->palVersion    = 0x300;
        pWin->m_pLogPal->palNumEntries = (WORD) nNumPalEntries;
        
        for (i = 0; i < nNumPalEntries; ++i) {
        
            pWin->m_pLogPal->palPalEntry[i].peRed   = pColorTable[i].rgbtRed;
            pWin->m_pLogPal->palPalEntry[i].peGreen = pColorTable[i].rgbtGreen;
            pWin->m_pLogPal->palPalEntry[i].peBlue  = pColorTable[i].rgbtBlue;
            pWin->m_pLogPal->palPalEntry[i].peFlags = 0;
        }

    } else {

        PBITMAPINFOHEADER pbmih = CastInfoHeader(pWin->m_pDIB);

        RGBQUAD *pColorTable = (RGBQUAD *) ColorTable(pbmih);

        pWin->m_nImageW = pbmih->biWidth;
        pWin->m_nImageH = abs(pbmih->biHeight);
        
        // If image size is not set in the header, fix it

        if (pbmih->biSizeImage == 0) {

            pbmih->biSizeImage = SizeImage(pbmih);
        }

        // If the number of entries in the color table is not set, fix it

        if (pbmih->biClrUsed == 0) {
                
            pbmih->biClrUsed = MaxNumColors(pbmih->biBitCount);
        }

        // If the offset of the bitmap bits from the start of the DIB data
        // is not given, find it

        if (!pWin->m_dwOffBits) {

            // Start with the header

            pWin->m_dwOffBits = pbmih->biSize;

            // If this is a 16 or 32 bit bitmap and BI_BITFIELDS is used, 
            // bmiColors member contains three DWORD color masks.
            // If this is a V4 or V5 header, this info is included the header

            if (
                IsInfoHeader(pbmih) && 
                pbmih->biCompression == BI_BITFIELDS
            ) {
                
                pWin->m_dwOffBits += 3 * sizeof(DWORD);
            }

            // Add the color table

            pWin->m_dwOffBits += sizeof(RGBQUAD) * pbmih->biClrUsed;

            // Add the profile data

            if (
                IsV5Header(pbmih) && 
                CastV5Header(pbmih)->bV5ProfileData <= pWin->m_dwOffBits
            ) {

                pWin->m_dwOffBits += CastV5Header(pbmih)->bV5ProfileSize;
            }
        }

#ifdef ICM_ENABLED

        // Fill the rendering intent

        if (IsV5Header(pbmih)) {

            LCSGAMUTMATCH lcsIntent = CastV5Header(pbmih)->bV5Intent;

            if (
                lcsIntent != LCS_GM_BUSINESS &&
                lcsIntent != LCS_GM_GRAPHICS &&
                lcsIntent != LCS_GM_IMAGES &&
                lcsIntent != LCS_GM_ABS_COLORIMETRIC
            ) {

                ERROR_MESSAGE(ResourceString(IDS_INVALID_INTENT));
            }

            pWin->m_lcsRenderIntent = lcsIntent;
            pWin->m_lcsProofIntent  = lcsIntent;
        }

#endif //ICM_ENABLED

        // Extract the palette information

        CHECK(pWin->m_pLogPal = (PLOGPALETTE) GlobalAlloc(
            GMEM_FIXED, 
            sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * (pbmih->biClrUsed - 1)
        ));

        pWin->m_pLogPal->palVersion    = 0x300;
        pWin->m_pLogPal->palNumEntries = (WORD) pbmih->biClrUsed;
        
        for (i = 0; i < pbmih->biClrUsed; ++i) {
        
            pWin->m_pLogPal->palPalEntry[i].peRed   = pColorTable[i].rgbRed;
            pWin->m_pLogPal->palPalEntry[i].peGreen = pColorTable[i].rgbGreen;
            pWin->m_pLogPal->palPalEntry[i].peBlue  = pColorTable[i].rgbBlue;
            pWin->m_pLogPal->palPalEntry[i].peFlags = 0;
        }
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// BitmapWindow_CreateDDB
//
// Routine Description:
//   Converts the device independent bitmap (DIB) to a device dependent 
//   bitmap (DDB) (dependent to the display monitor)
//
// Arguments:
//   PBITMAPWINDOW pWin      pointer to the object  
//   int           nMonitor  index of the monitor 
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
BitmapWindow_CreateDDB(
    PBITMAPWINDOW pWin,
    int           nMonitor
)
{
    USES_BRESULT;
    HDC               hDC = 0;
    HDC               hMemDC = 0;
    HBITMAP           hOldBitmap = 0;
    RECT              rBitmap;

    ASSERT(BitmapWindow_AssertValid(pWin));

    CHECK(hDC = CreateDC(
        pWin->m_Monitor[nMonitor].szName,
        0, 
        0, 
        0
    ));

    CHECK(hMemDC = CreateCompatibleDC(hDC));

    // Create the DIBSection

    if (pWin->m_Monitor[nMonitor].hDIBSect) {

        CHECK(DeleteObject(pWin->m_Monitor[nMonitor].hDIBSect));
    }

#ifdef ICM_ENABLED 

    CHECK(pWin->m_Monitor[nMonitor].hDIBSect = CreateCompatibleDIBSection(
        hDC,
        pWin->m_nImageW,
        pWin->m_nImageH,
        pWin->m_Monitor[nMonitor].szProfile,
        pWin->m_pLogPal
    ));

#else //ICM_ENABLED 

    CHECK(pWin->m_Monitor[nMonitor].hDIBSect = CreateCompatibleDIBSection(
        hDC,
        pWin->m_nImageW,
        pWin->m_nImageH,
        pWin->m_pLogPal
    ));

#endif //ICM_ENABLED 

    // Select the DIBSection into the memory DC
    
    CHECK(hOldBitmap = (HBITMAP) SelectObject(
        hMemDC,
        pWin->m_Monitor[nMonitor].hDIBSect
    ));

    // Transform the DIB into this DIBSection

    if (pWin->m_Monitor[nMonitor].hPalette) {

        CHECK(DeleteObject(pWin->m_Monitor[nMonitor].hPalette));
    }
    
    rBitmap.left    = 0;
    rBitmap.top     = 0;
    rBitmap.right   = pWin->m_nImageW;
    rBitmap.bottom  = pWin->m_nImageH;

#ifdef ICM_ENABLED

    if (g_bICMFunctionalityPresent) {
    
        CHECK(CreatePaletteAndDrawDIB_ICM(
            hMemDC,
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &pWin->m_Monitor[nMonitor].hPalette,
            &rBitmap,
            pWin->m_bDisableICM ? 0 : pWin->m_Monitor[nMonitor].szProfile,
            pWin->m_lcsRenderIntent,
            pWin->m_bEnableProofing ? pWin->m_szTargetProfile : 0,
            pWin->m_lcsProofIntent
        ));

    } else 

#endif //ICM_ENABLED

    {
        CHECK(CreatePaletteAndDrawDIB(
            hMemDC,
            pWin->m_pDIB,
            pWin->m_dwOffBits,
            pWin->m_pLogPal,
            &pWin->m_Monitor[nMonitor].hPalette,
            &rBitmap
        ));
    }

    BEGIN_CLEANUP;

    if (hOldBitmap) {
        
        CHECK(SelectObject(
            hMemDC,
            hOldBitmap
        ));
    }

    if (hMemDC) {

        CHECK(DeleteDC(hMemDC));
    }

    if (hDC) {

        CHECK(DeleteDC(hDC));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// CreateCompatibleDIBSection
//
// Routine Description:
//   Creates a DIBSection compatible with the given DC
//
// Arguments:
//  HDC         hDC           destination DC
//  int         nWidth        width of bitmap, in pixels
//  int         nHeight       height of bitmap, in pixels
//  PCTSTR      pProfileName  name of the destination color profile
//  PLOGPALETTE plp           pointer to the logpalette
//
// Return Value:
//   Handle to the DIBSection / zero on error
//

HBITMAP
CreateCompatibleDIBSection(
    HDC         hDC,
    int         nWidth,
    int         nHeight,
#ifdef ICM_ENABLED 
    PCTSTR      pProfileName,
#endif //ICM_ENABLED 
    PLOGPALETTE plp
)
{
    USES_BRESULT;
    PBITMAPINFO  pbi = 0;
    HBITMAP      hDIBSect = 0;
    PVOID        pBits;
    DWORD        nNumPalEntries;
    HPALETTE     hHalftonePalette = 0;
    PALETTEENTRY peHalftone[256];
    RGBQUAD      *pDIBColors = 0;
    PALETTEENTRY *pPalColors = 0;
    DWORD        i;

    ASSERT(nWidth);
    ASSERT(nHeight);
    ASSERT(plp);
#ifdef ICM_ENABLED 
    ASSERT(pProfileName);
#endif //ICM_ENABLED 
    ASSERT(plp);

    // If there is a color table in the DIB, use it. 
    // If not, we will use the halftoning palette associated with the DC

    nNumPalEntries = plp->palNumEntries ? plp->palNumEntries : 256;

#ifdef ICM_ENABLED 
    
    if (g_bICMFunctionalityPresent) {

        USES_CONVERSION;
        PBITMAPV5HEADER   pV5h;
        DWORD             dwProfileSize = _tcslen(pProfileName) + 1;

        // Allocate zero initialized memory for the header

        CHECK(pbi = (PBITMAPINFO) GlobalAlloc(
            GMEM_FIXED | GMEM_ZEROINIT,
            sizeof(BITMAPV5HEADER) + 
            nNumPalEntries * sizeof(RGBQUAD) +
            dwProfileSize
        ));

        pV5h = CastV5Header(pbi);

        // Fill the header fields with information compatible with MemDC

        pV5h->bV5Size         = sizeof(BITMAPV5HEADER);
        pV5h->bV5Width        = nWidth;
        pV5h->bV5Height       = nHeight;
        pV5h->bV5Planes       = (WORD) GetDeviceCaps(hDC, PLANES);
        pV5h->bV5BitCount     = (WORD) GetDeviceCaps(hDC, BITSPIXEL);
        pV5h->bV5Compression  = BI_RGB;     
        pV5h->bV5ClrUsed      = nNumPalEntries; 
        pV5h->bV5CSType       = PROFILE_LINKED;
        pV5h->bV5Intent       = LCS_GM_IMAGES;
        pV5h->bV5ProfileSize  = dwProfileSize;
        pV5h->bV5ProfileData  = 
            pV5h->bV5Size + pV5h->bV5ClrUsed * sizeof(RGBQUAD);

        // Copy the name of the profile

        strcpy(
            (PSTR) ProfileData(pV5h),
            T2A(pProfileName)
        );
        
    } else

#endif //ICM_ENABLED 

    {
        PBITMAPINFOHEADER pbmih;

        // Allocate zero initialized memory for the header

        CHECK(pbi = (PBITMAPINFO) GlobalAlloc(
            GMEM_FIXED | GMEM_ZEROINIT,
            sizeof(BITMAPINFOHEADER) + 
            nNumPalEntries * sizeof(RGBQUAD)
        ));
        
        pbmih = CastInfoHeader(pbi);

        // Fill the header fields with information compatible with MemDC

        pbmih->biSize          = sizeof(BITMAPINFOHEADER);
        pbmih->biWidth         = nWidth;
        pbmih->biHeight        = nHeight;
        pbmih->biPlanes        = (WORD) GetDeviceCaps(hDC, PLANES); 
        pbmih->biBitCount      = (WORD) GetDeviceCaps(hDC, BITSPIXEL);    
        pbmih->biCompression   = BI_RGB;     
        pbmih->biClrUsed       = nNumPalEntries;
    }

    // Fill the color table

    if (plp->palNumEntries) {
    
        pPalColors = plp->palPalEntry;
    
    } else {

        CHECK(hHalftonePalette = CreateHalftonePalette(hDC));

        CHECK(GetPaletteEntries(
            hHalftonePalette, 
            0, 
            256, 
            peHalftone
        ));

        pPalColors = peHalftone;
    }

    pDIBColors = (RGBQUAD *) ColorTable(pbi);

    for (i = 0; i < nNumPalEntries; ++i) {

        pDIBColors[i].rgbRed      = pPalColors[i].peRed;
        pDIBColors[i].rgbGreen    = pPalColors[i].peGreen;
        pDIBColors[i].rgbBlue     = pPalColors[i].peBlue;
        pDIBColors[i].rgbReserved = 0;
    }

    // create the display device compatible DIB section

    CHECK(hDIBSect = CreateDIBSection(
        hDC,
        pbi,
        DIB_RGB_COLORS,
        &pBits,
        0,
        0
    ));

    BEGIN_CLEANUP;

    if (pbi) {

        CHECK(GlobalFree(pbi) == 0);
    }

    if (hHalftonePalette) {

        CHECK(DeleteObject(hHalftonePalette));
    }

    return hDIBSect;
}

//////////////////////////////////////////////////////////////////////////
//
// CenterBitmap
//
// Routine Description:
//   Centers the bitmap inside the given rectangle
//
// Arguments:
//  int    nImageW             the original width of the bitmap
//  int    nImageH             the original height of the bitmap
//  PRECT  pRect               pointer to the destination rectangle
//  BOOL   bStretch    
//  BOOL   bKeepAspectRatio
//
// Return Value:
//   none
//

VOID
CenterBitmap(
    int    nImageW,
    int    nImageH,
    PRECT  pRect,
    BOOL   bStretch,
    BOOL   bKeepAspectRatio
)
{
    int nOldW;
    int nOldH;
    int nNewW;
    int nNewH;
    int dW, dH;

    ASSERT(pRect);

    nOldW = Rect_W(pRect);
    nOldH = Rect_H(pRect);

    if (nImageW == 0 || nImageH == 0) {

        pRect->left   = nOldW / 2;
        pRect->right  = nOldW / 2;
        pRect->top    = nOldH / 2;
        pRect->bottom = nOldH / 2;

        return;
    }

    if (!bStretch) {

        // if we won't scretch the bitmap, the new size is 
        // the bitmap's original size

        nNewW = nImageW;
        nNewH = nImageH;

    } else {

        if (!bKeepAspectRatio) {
        
            // if we will scretch the bitmap, but won't keep the
            // aspect ratio, then the new size is the window size

            nNewW = nOldW;
            nNewH = nOldH;
        
        } else {

            // if we will scretch the bitmap and keep the aspect ratio, 
            // then we first try to match the bitmap's height

            nNewW = nOldW;
            nNewH = nNewW * nImageH / nImageW;

            if (nNewH > nOldH) {

                // if we cannot match the heigth, match the width

                nNewH = nOldH;
                nNewW = nNewH * nImageW / nImageH;
            }
        }
    }

    // If the image size is SMALLER than the destination rectangle size, 
    // then reduce the destination rectangle by dividing the extra
    // space evenly into along sides to create a "frame" around the image

    // If the image size is LARGER than the destination rectangle size, 
    // then enlarge the destination rectangle to the image size

    dW = nOldW - nNewW;

    if (dW > 0) {

        pRect->left   += dW / 2 + (dW & 1);
        pRect->right  -= dW / 2;

    } else {

        pRect->right  -= dW;
    }


    dH = nOldH - nNewH;

    if (dH > 0) {

        pRect->top    += dH / 2 + (dH & 1);
        pRect->bottom -= dH / 2;

    } else {

        pRect->bottom -= dH;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// DrawDDB
//
// Routine Description:
//   Draws a DDB using StretchBlt / BitBlt
//
// Arguments:
//   HDC         hDC         Destination DC
//   HBITMAP     hBitmap     handle of the DDB
//   HPALETTE    hPalette    Palette to realize on the DC
//   int         nImageW     source rectangle width
//   int         nImageH     source rectangle width
//   PRECT       pRect       destination rectangle
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
DrawDDB(
    HDC      hDC,
    HBITMAP  hBitmap,
    HPALETTE hPalette,
    int      nImageW,
    int      nImageH,
    PRECT    pRect
)
{
    USES_BRESULT;
    HDC      hMemDC = 0;
    HBITMAP  hOldBitmap = 0;
    HPALETTE hOldPalette = 0;

    // select the palette into the DC, flush the cache and realize it

    if (hPalette) {

        CHECK(hOldPalette = SelectPalette(
            hDC,
            hPalette,
            TRUE
        ));

        CHECK(UnrealizeObject(hPalette)); 

        CHECK(RealizePalette(hDC) != GDI_ERROR);
    }

    // Create a memory DC and select the bitmap into it

    CHECK(hMemDC = CreateCompatibleDC(hDC));

    CHECK(hOldBitmap = (HBITMAP) SelectObject(
        hMemDC, 
        hBitmap
    ));

    // Blt the DDB

    if (Rect_W(pRect) == nImageW && Rect_H(pRect) == nImageH) {

        CHECK(BitBlt(
            hDC,
            pRect->left, 
            pRect->top,
            nImageW, 
            nImageH,
            hMemDC,
            0,
            0,
            SRCCOPY
        ));

    } else {

        CHECK(SetStretchBltMode(
            hDC,
            HALFTONE
        ));

        CHECK(StretchBlt(
            hDC,
            pRect->left, 
            pRect->top,
            Rect_W(pRect), 
            Rect_H(pRect),
            hMemDC,
            0,
            0,
            nImageW,
            nImageH,
            SRCCOPY
        ));
    }

    BEGIN_CLEANUP;
    
    if (hOldBitmap) {

        CHECK(SelectObject(
            hMemDC, 
            hOldBitmap
        ));
    }

    if (hOldPalette) {

        CHECK(SelectPalette(
            hDC,
            hOldPalette,
            TRUE
        ));
    }

    if (hMemDC) {

        CHECK(DeleteDC(hMemDC));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// DrawDIB
//
// Routine Description:
//   Draws a DIB using StretchDIBits / SetDIBitsToDevice
//
// Arguments:
//   HDC         hDC         destination DC
//   PBYTE       pDIB        the DIB
//   DWORD       dwOffset    offset of the bitmap pixels
//   HPALETTE    hPalette    palette to realize on the DC
//   PRECT       pRect       destination rectangle
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
DrawDIB(
    HDC         hDC,
    PBYTE       pDIB,
    DWORD       dwOffset,
    HPALETTE    hPalette,
    PRECT       pRect
)
{
    USES_BRESULT;
    int      nImageW;
    int      nImageH;
    HPALETTE hOldPalette = 0;

    ASSERT(hDC);
    ASSERT(pDIB);
    ASSERT(pRect);

    // select the palette into the DC, flush the cache and realize it

    if (hPalette) {

        CHECK(hOldPalette = SelectPalette(
            hDC,
            hPalette,
            TRUE
        ));

        CHECK(UnrealizeObject(hPalette)); 

        CHECK(RealizePalette(hDC) != GDI_ERROR);
    }

    // Blt the DIB

    nImageW = abs(ImageW(pDIB));
    nImageH = abs(ImageH(pDIB));

    if (Rect_W(pRect) == nImageW && Rect_H(pRect) == nImageH) {

        CHECK(SetDIBitsToDevice(
            hDC,
            pRect->left, 
            pRect->top,
            nImageW, 
            nImageH,
            0, 
            0,
            0, 
            nImageH,
            pDIB + dwOffset,
            (PBITMAPINFO) pDIB,
            DIB_RGB_COLORS
        ) != GDI_ERROR);

    } else {

        CHECK(SetStretchBltMode(
            hDC,
            HALFTONE
        ));

        CHECK(StretchDIBits(
            hDC,
            pRect->left, 
            pRect->top,
            Rect_W(pRect), 
            Rect_H(pRect),
            0,
            0,
            nImageW,
            nImageH,
            pDIB + dwOffset,
            (PBITMAPINFO) pDIB,
            DIB_RGB_COLORS,
            SRCCOPY
        ) != GDI_ERROR);
    }

    BEGIN_CLEANUP;
    
    if (hOldPalette) {

        CHECK(SelectPalette(
            hDC,
            hOldPalette,
            TRUE
        ));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// CreatePaletteAndDrawDIB
//
// Routine Description:
//   Prepares the palette and calls DrawDIB
//
// Arguments:
//  PBITMAPWINDOW pWin
//  HDC           hDC             destination DC
//  HPALETTE      *phPalette      pointer to the palette to be created
//  PRECT         pRect           destination rectangle
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
CreatePaletteAndDrawDIB(
    HDC         hDC,
    PBYTE       pDIB,
    DWORD       dwOffBits,
    PLOGPALETTE pLogPal,
    HPALETTE    *phPalette,
    PRECT       pRect
)
{
    USES_BRESULT;
    HCURSOR hPrevCur = 0;

    ASSERT(hDC);
    ASSERT(pDIB);
    ASSERT(pLogPal);
    ASSERT(phPalette);
    ASSERT(pRect);

    // this may be a lengthy operation, display the hourglass

    hPrevCur = SetCursor(LoadCursor(0, IDC_WAIT));

    CHECK(*phPalette = pLogPal->palNumEntries ? 
        CreatePalette(pLogPal) : 
        CreateHalftonePalette(hDC)
    );

    CHECK(DrawDIB(
        hDC,
        pDIB,
        dwOffBits,
        *phPalette,
        pRect
    ));

    BEGIN_CLEANUP;
    
    if (hPrevCur) {
        
        SetCursor(hPrevCur);
    }

    return BRESULT;
}

