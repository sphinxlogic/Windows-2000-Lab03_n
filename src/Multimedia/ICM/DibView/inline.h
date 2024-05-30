/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    inline.h

Abstract:

    Inline functions

--*/

#ifndef INLINE_H
#define INLINE_H

//////////////////////////////////////////////////////////////////////////
//
// COUNTOF
//
// Routine Description:
//   Returns the number of elements in an array
//
// Arguments:
//
// Return Value:
//   
//

#define COUNTOF(Array) ( sizeof(Array) / sizeof(Array[0]) )


//////////////////////////////////////////////////////////////////////////
//
// Clip
//
// Routine Description:
//   
//
// Arguments:
//  int nValue  Current value
//  int nMin    Minimum allowed value
//  int nMax    Maximum allowed value
//
// Return Value:
//   
//

__inline
int
Clip(
    int nValue,
    int nMin,
    int nMax
)
{
    if (nValue < nMin) {

        return nMin;
    
    } else if (nValue > nMax) {

        return nMax;

    } else {

        return nValue;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// GlobalDuplicate
//
// Routine Description:
//   Creates a new global memory block and copies the contents of the
//   given block to the new block
//
// Arguments:
//  HGLOBAL hMem   Handle to the memory block to be duplicated
//
// Return Value:
//  Handle to the duplicate memory block on success / 0 on error
//

__inline
HGLOBAL
GlobalDuplicate(
    HGLOBAL hMem
)
{
    USES_BRESULT;

    PVOID   pMem = 0;
    HGLOBAL hNewMem = 0;
    DWORD   dwSize;

    if (hMem) {

        if (dwSize = GlobalSize(hMem)) {

            CHECK(pMem = GlobalLock(hMem));

            CHECK(hNewMem = GlobalAlloc(
                GMEM_FIXED, 
                dwSize
            ));

            CopyMemory(
                hNewMem,
                pMem,
                dwSize
            );
        }
    }

    BEGIN_CLEANUP;

    if (pMem) {
        
        GlobalUnlock(hMem);
    }

    return hNewMem;
}

//////////////////////////////////////////////////////////////////////////
//
// WidthBytes
//
// Routine Description:
//   Calculates the amount of memory a BITMAP raster line occupies
//
// Arguments:
//  DWORD dwWidth     Pixels per line
//  DWORD dwBitCount  Bits per pixel
//
// Return Value:
//   Width of the line in bytes
//

__inline 
DWORD
WidthBytes(
    DWORD dwWidth,
    DWORD dwBitCount
)
{
    return (((dwWidth * dwBitCount) + 31) & ~31) >> 3;
}

//////////////////////////////////////////////////////////////////////////
//
// HeaderLength
//
// Routine Description:
//   Gives the length of a BITMAP header
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV4HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   Length of th input struct
//

__inline 
DWORD
HeaderLength(
    PVOID pBitmapInfo
)
{
    return *(PDWORD)pBitmapInfo;
}

//////////////////////////////////////////////////////////////////////////
//
// IsCoreHeader
//
// Routine Description:
//   Determines if the given BITMAP header is a BITMAPCOREHEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV4HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   TRUE if the input structure is a BITMAPCOREHEADER / FALSE if not
//

__inline 
BOOL
IsCoreHeader(
    PVOID pBitmapInfo
)
{
    return HeaderLength(pBitmapInfo) == sizeof(BITMAPCOREHEADER);
}

//////////////////////////////////////////////////////////////////////////
//
// IsInfoHeader
//
// Routine Description:
//   Determines if the given BITMAP header is a BITMAPINFOHEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV4HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   TRUE if the input structure is a BITMAPINFOHEADER / FALSE if not
//

__inline 
BOOL
IsInfoHeader(
    PVOID pBitmapInfo
)
{
    return HeaderLength(pBitmapInfo) == sizeof(BITMAPINFOHEADER);
}

//////////////////////////////////////////////////////////////////////////
//
// IsV4Header
//
// Routine Description:
//   Determines if the given BITMAP header is a BITMAPV4HEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV4HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   TRUE if the input structure is a BITMAPV4HEADER / FALSE if not
//

__inline 
BOOL
IsV4Header(
    PVOID pBitmapInfo
)
{
    return HeaderLength(pBitmapInfo) == sizeof(BITMAPV4HEADER);
}

//////////////////////////////////////////////////////////////////////////
//
// IsV5Header
//
// Routine Description:
//   Determines if the given BITMAP header is a BITMAPV5HEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   TRUE if the input structure is a BITMAPV5HEADER / FALSE if not
//

__inline 
BOOL
IsV5Header(
    PVOID pBitmapInfo
)
{
    // Since at the time of writing this application the latest header 
    // struct we know of is the BITMAPV5HEADER, we still consider any longer 
    // header as a BITMAPV5HEADER

    return HeaderLength(pBitmapInfo) >= sizeof(BITMAPV5HEADER);
}

//////////////////////////////////////////////////////////////////////////
//
// CastXXXHeader
//
// Routine Description:
//   Casts the header pointer to PBITMAPxxxHEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPxxxHEADER
//
// Return Value:
//   PBITMAPxxxHEADER
//

__inline 
PBITMAPCOREHEADER
CastCoreHeader(
    PVOID pBitmapInfo
)
{
    return (PBITMAPCOREHEADER) pBitmapInfo;
}

__inline 
PBITMAPINFOHEADER
CastInfoHeader(
    PVOID pBitmapInfo
)
{
    return (PBITMAPINFOHEADER) pBitmapInfo;
}

__inline 
PBITMAPV4HEADER
CastV4Header(
    PVOID pBitmapInfo
)
{
    return (PBITMAPV4HEADER) pBitmapInfo;
}

__inline 
PBITMAPV5HEADER
CastV5Header(
    PVOID pBitmapInfo
)
{
    return (PBITMAPV5HEADER) pBitmapInfo;
}

//////////////////////////////////////////////////////////////////////////
//
// ProfileData
//
// Routine Description:
//   Finds the location of the ICM color profile data in a BITMAPHEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   Returns a pointer to the location of the color profile data
//

__inline 
PVOID
ProfileData(
    PVOID pBitmapInfo
)
{
    return 
        (PBYTE)pBitmapInfo + 
        ((PBITMAPV5HEADER)pBitmapInfo)->bV5ProfileData;
}

//////////////////////////////////////////////////////////////////////////
//
// ColorTable
//
// Routine Description:
//   Finds the location of the color table in a BITMAPHEADER
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   Returns a pointer to the first entry in the color table
//

__inline 
PVOID
ColorTable(
    PVOID pBitmapInfo
)
{
    PBYTE pColorTable = (PBYTE) pBitmapInfo + HeaderLength(pBitmapInfo);

    if (
        IsInfoHeader(pBitmapInfo) && 
        CastInfoHeader(pBitmapInfo)->biCompression == BI_BITFIELDS
    ) {

        pColorTable += 3 * sizeof(DWORD);
    }

    return (PVOID) pColorTable;
}

//////////////////////////////////////////////////////////////////////////
//
// BitCount
//
// Routine Description:
//   Finds the number of bits per pixel
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   Returns the bit count
//

__inline
int
BitCount(
     PVOID pBitmapInfo
)
{
    return IsCoreHeader(pBitmapInfo) ? 
        CastCoreHeader(pBitmapInfo)->bcBitCount :
        CastInfoHeader(pBitmapInfo)->biBitCount;
}

//////////////////////////////////////////////////////////////////////////
//
// 
//
// Routine Description:
//   
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   
//

__inline
int
MaxNumColors(
     int nBitCount
)
{
    return nBitCount <= 8 ? (1 << nBitCount) : 0;
}

//////////////////////////////////////////////////////////////////////////
//
// NumColors
//
// Routine Description:
//   Returns the number of colors in a DIB  
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   Number of colors
//

__inline
int
NumColors(
     PVOID pBitmapInfo
)
{
    if (IsCoreHeader(pBitmapInfo)) {

        PBITMAPCOREHEADER pbmch = CastCoreHeader(pBitmapInfo);

        return MaxNumColors(pbmch->bcBitCount);

    } else {

        PBITMAPINFOHEADER pbmih = CastInfoHeader(pBitmapInfo);

        if (pbmih->biClrUsed == 0) {

            return MaxNumColors(pbmih->biBitCount);

        } else {

            return pbmih->biClrUsed;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
// SizeImage
//
// Routine Description:
//   Calculates the image size
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   Image size in bytes
//

__inline
int
SizeImage(
     PVOID pBitmapInfo
)
{
    if (IsCoreHeader(pBitmapInfo)) {

        PBITMAPCOREHEADER pbmch = CastCoreHeader(pBitmapInfo);

        return 
            WidthBytes(pbmch->bcWidth, pbmch->bcBitCount) *
            pbmch->bcHeight;

    } else {

        PBITMAPINFOHEADER pbmih = CastInfoHeader(pBitmapInfo);

        if (pbmih->biSizeImage == 0) {

            ASSERT(pbmih->biCompression == BI_RGB);

            return 
                WidthBytes(pbmih->biWidth, pbmih->biBitCount) * 
                abs(pbmih->biHeight);

        } else {

            return pbmih->biSizeImage;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
// ImageW, ImageH
//
// Routine Description:
//   Returns the width / height of the DIB
//
// Arguments:
//   PVOID pBitmapInfo  pointer to a BITMAPCOREHEADER, a BITMAPINFOHEADER, 
//                      a BITMAPV5HEADER or a BITMAPV5HEADER struct.
//
// Return Value:
//   
//

__inline
int
ImageW(
     PVOID pBitmapInfo
)
{
    if (IsCoreHeader(pBitmapInfo)) {

        return CastCoreHeader(pBitmapInfo)->bcWidth;

    } else {

        return CastInfoHeader(pBitmapInfo)->biWidth;
    }
}

__inline
int
ImageH(
     PVOID pBitmapInfo
)
{
    if (IsCoreHeader(pBitmapInfo)) {

        return CastCoreHeader(pBitmapInfo)->bcHeight;

    } else {

        return CastInfoHeader(pBitmapInfo)->biHeight;
    }
}


//////////////////////////////////////////////////////////////////////////
//
// Rect_W
//
// Routine Description:
//   Gives the width of the given RECT
//
// Arguments:
//   PRECT pRect   Pointer to a RECT structure
//
// Return Value:
//   Width of the RECT
//

__inline
LONG
Rect_W(
    PRECT pRect
)
{
    return pRect->right - pRect->left;
}

//////////////////////////////////////////////////////////////////////////
//
// Rect_H
//
// Routine Description:
//   Gives the height of the given RECT
//
// Arguments:
//   PRECT pRect   Pointer to a RECT structure
//
// Return Value:
//   Height of the RECT
//

__inline
LONG
Rect_H(
    PRECT pRect
)
{
    return pRect->bottom - pRect->top;
}

//////////////////////////////////////////////////////////////////////////
//
// ResourceString
//
// Routine Description:
//   Returns the requested string in the resource string table
//
// Arguments:
//   int nIndex   index of the string within the string table
//
// Return Value:
//   Pointer to the requested string
//

extern PTSTR g_pResourceStrings[IDS_LAST - IDS_FIRST + 1];

__inline
PTSTR
ResourceString(
    int nIndex
)
{
    ASSERT(nIndex >= IDS_FIRST && nIndex <= IDS_LAST);
    return g_pResourceStrings[nIndex - IDS_FIRST];
}

#ifdef ICM_ENABLED

//////////////////////////////////////////////////////////////////////////
//
// ICC_TO_LCS
//
// Routine Description:
//   Returns the ICC equivalent of a LCS intent
//
// Arguments:
//   DWORD dwIntent   ICC intent
//
// Return Value:
//   LCS intent
//

__inline
LCSGAMUTMATCH
ICC_TO_LCS(
    DWORD dwIntent
)
{
    switch (dwIntent) {
    
    case INTENT_PERCEPTUAL:             return LCS_GM_IMAGES;
    case INTENT_RELATIVE_COLORIMETRIC:  return LCS_GM_GRAPHICS;
    case INTENT_SATURATION:             return LCS_GM_BUSINESS;
    case INTENT_ABSOLUTE_COLORIMETRIC:  return LCS_GM_ABS_COLORIMETRIC;
    default:                            ASSERT(0); return (LCSGAMUTMATCH) -1;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// LCS_TO_ICC
//
// Routine Description:
//   Returns the LCS equivalent of a ICC intent
//
// Arguments:
//   LCSGAMUTMATCH lcsIntent   LCS intent
//
// Return Value:
//   ICC intent
//

__inline
DWORD
LCS_TO_ICC(
    LCSGAMUTMATCH lcsIntent
)
{
    switch (lcsIntent) {
    
    case LCS_GM_BUSINESS:           return INTENT_SATURATION;
    case LCS_GM_GRAPHICS:           return INTENT_RELATIVE_COLORIMETRIC;
    case LCS_GM_IMAGES:             return INTENT_PERCEPTUAL;
    case LCS_GM_ABS_COLORIMETRIC:   return INTENT_ABSOLUTE_COLORIMETRIC;
    default:                        ASSERT(0); return (DWORD) -1;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// DMICM_TO_LCS
//
// Routine Description:
//   Returns the LCSGAMUTMATCH equivalent of a DevMode intent
//
// Arguments:
//   DWORD dwIntent   DevMode intent
//
// Return Value:
//   LCS intent
//

__inline
LCSGAMUTMATCH
DMICM_TO_LCS(
    DWORD dwIntent
)
{
    switch (dwIntent) {
    
    case DMICM_CONTRAST:            return LCS_GM_IMAGES;
    case DMICM_COLORIMETRIC:        return LCS_GM_GRAPHICS;
    case DMICM_SATURATE:            return LCS_GM_BUSINESS;
    case DMICM_ABS_COLORIMETRIC:    return LCS_GM_ABS_COLORIMETRIC;
    default:                        ASSERT(0); return (LCSGAMUTMATCH) -1;
    }
}


//////////////////////////////////////////////////////////////////////////
//
// LCS_TO_DMICM
//
// Routine Description:
//   Returns the DevMode equivalent of a LCS intent
//
// Arguments:
//   LCSGAMUTMATCH lcsIntent   LCS intent
//
// Return Value:
//   DevMode Intent
//

__inline
DWORD
LCS_TO_DMICM(
    LCSGAMUTMATCH lcsIntent
)
{
    switch (lcsIntent) {
    
    case LCS_GM_BUSINESS:           return DMICM_SATURATE;
    case LCS_GM_GRAPHICS:           return DMICM_COLORIMETRIC;
    case LCS_GM_IMAGES:             return DMICM_CONTRAST;
    case LCS_GM_ABS_COLORIMETRIC:   return DMICM_ABS_COLORIMETRIC;
    default:                        ASSERT(0); return (DWORD) -1;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// LCS_TO_TEXT
//
// Routine Description:
//   Returns the text equivalent of a LCS intent
//
// Arguments:
//   LCSGAMUTMATCH lcsIntent   LCS intent
//
// Return Value:
//   corresponding intent name in text
//

__inline
PCTSTR
LCS_TO_TEXT(
    LCSGAMUTMATCH lcsIntent
)
{
    switch (lcsIntent) {
    
    case LCS_GM_BUSINESS:           return ResourceString(IDS_INTENT_GRAPHICS);
    case LCS_GM_GRAPHICS:           return ResourceString(IDS_INTENT_PROOF);
    case LCS_GM_IMAGES:             return ResourceString(IDS_INTENT_PICTURES);
    case LCS_GM_ABS_COLORIMETRIC:   return ResourceString(IDS_INTENT_MATCH);
    default:                        ASSERT(0); return 0;
    }
}

//////////////////////////////////////////////////////////////////////////
//
// TEXT_TO_LCS
//
// Routine Description:
//   Returns the LCS equivalent of a intent string
//
// Arguments:
//   PCTSTR pText   intent name
//
// Return Value:
//   LCS intent constant
//

__inline
LCSGAMUTMATCH
TEXT_TO_LCS(
    PCTSTR pText
)
{
         if (_tcsicmp(pText, ResourceString(IDS_INTENT_PICTURES)) == 0) return LCS_GM_IMAGES;
    else if (_tcsicmp(pText, ResourceString(IDS_INTENT_PROOF)) == 0)    return LCS_GM_GRAPHICS;
    else if (_tcsicmp(pText, ResourceString(IDS_INTENT_GRAPHICS)) == 0) return LCS_GM_BUSINESS;
    else if (_tcsicmp(pText, ResourceString(IDS_INTENT_MATCH)) == 0)    return LCS_GM_ABS_COLORIMETRIC;
    else { ASSERT(0); return (DWORD) -1; }
}


//////////////////////////////////////////////////////////////////////////
//
// FXPT_TO_FLPT
//
// Routine Description:
//   Converts a fixed point real number to floating point real number
//
// Arguments:
//   long nFixed   fixed point real number
//   int  nPoint   location of the decimal point
//
// Return Value:
//   floating point real number
//

double  __cdecl ldexp(double, int);

__inline
double
FXPT_TO_FLPT(
    long nFixed,
    int  nPoint
)
{
    double nInteger  = nFixed >> nPoint;
    double nFraction = ldexp(nFixed & ((1 << nPoint) - 1), -nPoint);

    return nInteger + nFraction;
}

//////////////////////////////////////////////////////////////////////////
//
// FLPT_TO_FXPT
//
// Routine Description:
//   Converts a floating point real number to fixed point real number
//
// Arguments:
//   double nFloat   floating point real number
//   int  nPoint     location of the decimal point
//
// Return Value:
//   fixed point real number
//

__inline
long
FLPT_TO_FXPT(
    double nFloat,
    int    nPoint
)
{
    long   nInteger  = (long) nFloat;
    double nFraction = nFloat - nInteger;

    return (nInteger << nPoint) | (long) ldexp(nFraction, nPoint);
}

//////////////////////////////////////////////////////////////////////////
//
// FXPT2DOT30_TO_FLPT, FLPT_TO_FXPT2DOT30
//
// Routine Description:
//   Convert between floating point and 2.30 fixed point representations
//
// Arguments:
//
// Return Value:
//

__inline
double
FXPT2DOT30_TO_FLPT(
    FXPT2DOT30 nFixed
)
{
    return FXPT_TO_FLPT(nFixed, 30);
}

__inline
FXPT2DOT30
FLPT_TO_FXPT2DOT30(
    double nFloat
)
{
    return FLPT_TO_FXPT(nFloat, 30);
}

//////////////////////////////////////////////////////////////////////////
//
// FXPT16DOT16_TO_FLPT, FLPT_TO_FXPT16DOT16
//
// Routine Description:
//   Convert between floating point and 16.16 fixed point representations
//
// Arguments:
//
// Return Value:
//

__inline
double
FXPT16DOT16_TO_FLPT(
    FXPT16DOT16 nFixed
)
{
    return FXPT_TO_FLPT(nFixed, 16);
}

__inline
FXPT16DOT16
FLPT_TO_FXPT16DOT16(
    double nFloat
)
{
    return FLPT_TO_FXPT(nFloat, 16);
}

#endif //ICM_ENABLED

#endif //INLINE_H
