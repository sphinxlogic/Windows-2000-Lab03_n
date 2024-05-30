/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    ffilter.c

Abstract:
    
    Image file read filter functions

--*/

#include "pch.h"
#include "resource.h"

#include "conv.h"
#include "check.h"
#include "inline.h"

#include "FFilter.h"
#include "filtapi.h"


PVOID
RegQueryValue_Alloc(
    HKEY   hKey,
    PCTSTR pValueName
)
{
    USES_BRESULT;

    PVOID pBuffer = 0;
    DWORD dwSize = 0;
    DWORD dwType;

    CHECK0(RegQueryValueEx(
        hKey,
        pValueName,
        0,
        &dwType,
        0,
        &dwSize
    ));

    CHECK(pBuffer = GlobalAlloc(
        GMEM_FIXED, 
        dwSize
    ));

    CHECK0(RegQueryValueEx(  
        hKey,
        pValueName,
        0,
        &dwType,
        pBuffer,
        &dwSize
    ));

    BEGIN_CLEANUP;

    if (!BRESULT) {

        CHECK(GlobalFree(pBuffer) == 0);
        pBuffer = 0;
    }

    return pBuffer;
}



//////////////////////////////////////////////////////////////////////////
//
// FileFiltersList_Construct
//
// Routine Description:
//   Loads the file filter DLLs and forms the global list 
//
// Arguments:
//   PFILEFILTERSLIST pList  pointer to the object  
//
// Return Value:
//   none
//

BOOL
FileFiltersList_Construct(
    PFILEFILTERSLIST pList
)
{
    USES_BRESULT;
    PFILEFILTER  pFilter;
    HKEY         hImportFiltersKey = 0;
    HKEY         hFilterKey = 0;
    PTSTR        pFilterName = 0;
    DWORD        dwFiltersStrLen;

    pList->m_pHead       = 0;
    pList->m_pFiltersStr = 0;

    // Insert the internal BMP reader as the first entry

    CHECK(pFilter = (PFILEFILTER) GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        sizeof(FILEFILTER)
    ));

    pFilter->pExtension   = _T("bmp");
    pFilter->pName        = ResourceString(IDS_BMP_FILES);
    pFilter->pfnReadFile  = ReadBMP;
    pFilter->bFreeStrings = FALSE;

    pList->m_pHead = pFilter;

    // Try to load the shared graphics filters

    if (RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
        _T("SOFTWARE\\Microsoft\\Shared Tools\\Graphics Filters\\Import"),
        0,
        KEY_READ,
        &hImportFiltersKey
    ) == ERROR_SUCCESS) {

        DWORD dwSubKeys;
        DWORD dwMaxSubKeyLen;
        DWORD i;

        // get the number of subkeys and the maximum length for key name

        CHECK0(RegQueryInfoKey(
            hImportFiltersKey,
            0,
            0,
            0,
            &dwSubKeys,
            &dwMaxSubKeyLen,
            0,
            0,
            0,
            0,
            0,
            0
        ));

        ++dwMaxSubKeyLen;

        CHECK(pFilterName = (PTSTR) GlobalAlloc(
            GMEM_FIXED,
            dwMaxSubKeyLen * sizeof(TCHAR)
        ));

        for (i = 0; i < dwSubKeys; ++i) {

            DWORD dwSize = dwMaxSubKeyLen;

            CHECK0(RegEnumKeyEx(
                hImportFiltersKey,
                i,
                pFilterName,
                &dwSize,
                0,
                0,
                0,
                0
            ));

            if (_tcsicmp(pFilterName, _T("bmp")) != 0) {

                CHECK0(RegOpenKeyEx(
                    hImportFiltersKey,
                    pFilterName,
                    0,
                    KEY_READ,
                    &hFilterKey
                ));

                CHECK(pFilter->pNext = (PFILEFILTER) GlobalAlloc(
                    GMEM_FIXED | GMEM_ZEROINIT, 
                    sizeof(FILEFILTER)
                ));

                pFilter = pFilter->pNext;

                CHECK(pFilter->pExtension = (PTSTR) RegQueryValue_Alloc(
                    hFilterKey,
                    _T("Extensions")
                ));

                CHECK(pFilter->pName = (PTSTR) RegQueryValue_Alloc(
                    hFilterKey,
                    _T("Name")
                ));

                CHECK(pFilter->pData = RegQueryValue_Alloc(
                    hFilterKey,
                    _T("Path")
                ));

                pFilter->pfnReadFile = ReadThroughFilter;

                pFilter->bFreeStrings = TRUE;

                CHECK0(RegCloseKey(hFilterKey));

                hFilterKey = 0;
            }
        }
    }

    // Create the "file types string" to be used in the "file open dialog"

    dwFiltersStrLen = 0;

    FileFiltersList_FormFiltersStr(
        pList->m_pHead, 
        0, 
        &dwFiltersStrLen
    );

    CHECK(pList->m_pFiltersStr = GlobalAlloc(
        GMEM_FIXED, 
        dwFiltersStrLen
    ));
    
    CHECK(FileFiltersList_FormFiltersStr(
        pList->m_pHead, 
        pList->m_pFiltersStr, 
        &dwFiltersStrLen
    ));

    BEGIN_CLEANUP;

    if (hFilterKey) {

        CHECK0(RegCloseKey(hFilterKey));
    }

    if (hImportFiltersKey) {

        CHECK0(RegCloseKey(hImportFiltersKey));
    }
    
    if (pFilterName) {

        CHECK(GlobalFree(pFilterName) == 0);
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// FileFiltersList_Destruct
//
// Routine Description:
//   Frees the memory associated with file filters list
//
// Arguments:
//   PFILEFILTERSLIST pList  pointer to the object  
//
// Return Value:
//   none
//

VOID
FileFiltersList_Destruct(
    PFILEFILTERSLIST pList
)
{
    PFILEFILTER pFilter = pList->m_pHead;

    while (pFilter) {

        PFILEFILTER pNext = pFilter->pNext;

        if (pFilter->bFreeStrings) {

            if (pFilter->pExtension) {
        
                GlobalFree(pFilter->pExtension);
            }

            if (pFilter->pName) {
        
                GlobalFree(pFilter->pName);
            }

            if (pFilter->pData) {
        
                GlobalFree(pFilter->pData);
            }
        }

        GlobalFree(pFilter);

        pFilter = pNext;
    }

    if (pList->m_pFiltersStr) {

        GlobalFree(pList->m_pFiltersStr);
    }
}

//////////////////////////////////////////////////////////////////////////
//
// AddToString
//
// Routine Description:
//   Copies source string to the destination if there is enough space, 
//   Moves the destination string pointer to the end of the string.
//   Copies a single terminating null for empty strings.
//
// Arguments:
//  PTSTR  *ppDest    double pointer to destination string
//  int    *pcbLeft   number of characters left in the destination string
//  PCTSTR  pSource
//   
//
// Return Value:
//   none
//

void
AddToString(
    PTSTR  *ppDest, 
    int    *pcbLeft,
    PCTSTR  pSource
)
{
    int dwLen = _tcslen(pSource);

    if (dwLen == 0) {

        dwLen = 1;
    } 
    
    if (*pcbLeft >= dwLen) {

        _tcscpy(*ppDest, pSource);
        *ppDest += dwLen;
    }

    *pcbLeft -= dwLen;
}

//////////////////////////////////////////////////////////////////////////
//
// FileFiltersList_FormFiltersStr
//
// Routine Description:
//   Forms the file types string that specifies the recognized image 
//   extensions. The string will be used in the file open dialog
//
// Arguments:
//   PFILEFILTERSLIST pList  pointer to the object  
//   int nFilterStrLen       Total length of the extension strings
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
FileFiltersList_FormFiltersStr(
    PFILEFILTER pListHead,
    PTSTR       pStr,
    PINT        pcbStr
)
{
    PFILEFILTER pFilter;
    int       cbLeft = *pcbStr;

    // First, copy the "Image Files" string

    AddToString(&pStr, &cbLeft, ResourceString(IDS_IMAGE_FILES));
    AddToString(&pStr, &cbLeft, _T(""));

    // Copy the extensions string that will be used by the common dialog
    // This will be in the form "\0*.ext1;*.ext2;*.ext3;...\0"

    for (pFilter = pListHead; pFilter; pFilter = pFilter->pNext) {

        AddToString(&pStr, &cbLeft, _T("*."));
        AddToString(&pStr, &cbLeft, pFilter->pExtension);
        AddToString(&pStr, &cbLeft, _T(";"));
    }

    AddToString(&pStr, &cbLeft, _T(""));

    // Now copy the type names one by one

    for (pFilter = pListHead; pFilter; pFilter = pFilter->pNext) {

        AddToString(&pStr, &cbLeft, pFilter->pName);

        AddToString(&pStr, &cbLeft, _T(" (*."));
        AddToString(&pStr, &cbLeft, pFilter->pExtension);
        AddToString(&pStr, &cbLeft, _T(")"));
        AddToString(&pStr, &cbLeft, _T(""));

        AddToString(&pStr, &cbLeft, _T("*."));
        AddToString(&pStr, &cbLeft, pFilter->pExtension);
        AddToString(&pStr, &cbLeft, _T(""));
    }

    // Last, include an "All Files" entry

    AddToString(&pStr, &cbLeft, ResourceString(IDS_ALL_FILES));

    AddToString(&pStr, &cbLeft, _T(" (*.*)"));
    AddToString(&pStr, &cbLeft, _T(""));

    AddToString(&pStr, &cbLeft, _T("*.*"));
    AddToString(&pStr, &cbLeft, _T(""));

    // Add the terminating null

    AddToString(&pStr, &cbLeft, _T(""));

    *pcbStr -= cbLeft;

    return cbLeft >= 0;
}

//////////////////////////////////////////////////////////////////////////
//
// ReadImageFile
//
// Routine Description:
//   Tries to read the image based on its extension
//
// Arguments:
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
FileFiltersList_ReadImageFile(
    PFILEFILTERSLIST pList,
    PCTSTR           pFileName,
    PBYTE           *ppDIB,
    DWORD           *pdwOffBits
)
{
    USES_BRESULT;

    PFILEFILTER pFilter;
    PCTSTR      pFileExt;
    BOOL        bFound;

    // Try to open the file based on its extension

    pFileExt = _tcsrchr(pFileName, '.');

    if (!pFileExt) {

        ERROR_MESSAGE(ResourceString(IDS_NO_EXTENSION));
    } 
    
    // Try each filter for an extension match

    ++pFileExt;

    for (
        pFilter = pList->m_pHead, bFound = FALSE;
        pFilter != 0 && !bFound;
        pFilter = pFilter->pNext
    ) {

        if (_tcsicmp(pFileExt, pFilter->pExtension) == 0) {

            CHECK((*pFilter->pfnReadFile)(
                pFileName,
                ppDIB,
                pdwOffBits,
                pFilter->pData
            ));

            bFound = TRUE;
        }
    }

    if (!bFound) {

        ERROR_MESSAGE(ResourceString(IDS_UNKNOWN_EXTENSION));
    }

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// ReadBMP
//
// Routine Description:
//   ReadWithFilter
//
// Arguments:
//   PCTSTR pFileName        name of the file to open
//   PVOID  *ppDIB           a double pointer that will receive the a 
//                           global memory pointer to the DIB 
//   PDWORD *pdwOffBits      a double pointer that will receive the offset
//                           of the bitmap bits from the start of the DIB
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
WINAPI
ReadThroughFilter(
    PCTSTR  pFileName,
    PBYTE   *ppDIB,
    PDWORD  pdwOffBits,
    PVOID   pData
)
{
    USES_BRESULT;
    USES_CONVERSION;
    HINSTANCE         hDll = 0;
    HANDLE            hPrefMem;
    PFNGetFilterInfo  pfnGetFilterInfo = 0;
    PFNImportGr       pfnImportGr = 0;
    FILESPEC          fs = { 0 };
    GRPIX             grpix = { 0 };
    PBITMAPINFOHEADER pbmih;
    HDC               hMemDC = 0;
    HBITMAP           hBitmap = 0;
    HBITMAP           hOldBitmap = 0;
    PVOID             pBits = 0;

    CHECK(hDll = LoadLibrary(pData));

    pfnGetFilterInfo = (PFNGetFilterInfo) GetProcAddress(
        hDll, 
        "GetFilterInfo"
    );

    (*pfnGetFilterInfo)(
        3,
        0,
        &hPrefMem,
        grfSupportEMF	
    ); 

    pfnImportGr = (PFNImportGr) GetProcAddress(
        hDll, 
        "ImportGr"
    );

    GetShortPathNameA(
        T2A(pFileName), 
        fs.szName, 
        sizeof(fs.szName)
    );

    grpix.cbGrpix = sizeof(grpix);
    grpix.hemf = 0;

    CHECK((*pfnImportGr)(
        0,
        &fs,
        (GRPI *) &grpix,
        hPrefMem
    ) == IE_NO_ERROR);

    CHECK(hMemDC = CreateCompatibleDC(0));

    CHECK(*ppDIB = GlobalAlloc(
        GMEM_FIXED | GMEM_ZEROINIT, 
        sizeof(BITMAPINFOHEADER) + grpix.bbox.right * grpix.bbox.bottom * 4
    ));

    *pdwOffBits = sizeof(BITMAPINFOHEADER);

    pbmih = (PBITMAPINFOHEADER) *ppDIB;

    pbmih->biSize        = sizeof(BITMAPINFOHEADER);
    pbmih->biWidth       = grpix.bbox.right;
    pbmih->biHeight      = grpix.bbox.bottom;
    pbmih->biPlanes      = 1;
    pbmih->biBitCount    = 32;
    pbmih->biCompression = BI_RGB;

    CHECK(hBitmap = CreateDIBSection(
        0,
        (PBITMAPINFO) pbmih,
        DIB_RGB_COLORS,
        &pBits,
        0,
        0
    ));

    CHECK(hOldBitmap = SelectObject(
        hMemDC, 
        hBitmap
    ));

    CHECK(PlayEnhMetaFile(
        hMemDC,
        grpix.hemf,
        &grpix.bbox
    ));

    CHECK(GdiFlush());

    CopyMemory(
        *ppDIB + *pdwOffBits,
        pBits,
        grpix.bbox.right * grpix.bbox.bottom * 4
    );

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

    if (hBitmap) {

        CHECK(DeleteObject(hBitmap));
    }

    if (hDll) {

        CHECK(FreeLibrary(hDll));
    }

    if (grpix.hemf) {

        CHECK(DeleteEnhMetaFile(grpix.hemf));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// ReadBMP
//
// Routine Description:
//   Reads a BMP file
//
// Arguments:
//   PCTSTR pFileName        name of the file to open
//   PVOID  *ppDIB           a double pointer that will receive the a 
//                           global memory pointer to the DIB 
//   PDWORD *pdwOffBits      a double pointer that will receive the offset
//                           of the bitmap bits from the start of the DIB
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
WINAPI
ReadBMP(
    PCTSTR  pFileName,
    PBYTE   *ppDIB,
    PDWORD  pdwOffBits,
    PVOID   pData
)
{
    USES_BRESULT;
    HANDLE           hFile = INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    DWORD            dwNumberOfBytesRead;

    ASSERT(pFileName);

    CHECK((hFile = CreateFile(
        pFileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        0,
        OPEN_EXISTING,
        FILE_FLAG_SEQUENTIAL_SCAN,
        0
    )) != INVALID_HANDLE_VALUE);

    // Read the file header

    CHECK(ReadFile(
        hFile,
        &bmfh,
        sizeof(bmfh),
        &dwNumberOfBytesRead,
        0
    ));

    if (LOBYTE(bmfh.bfType) != 'B' || HIBYTE(bmfh.bfType) != 'M') {

        ERROR_MESSAGE(ResourceString(IDS_INVALID_SIGNATURE));
    }

    if (bmfh.bfSize != GetFileSize(hFile, 0)) {

        ERROR_MESSAGE(ResourceString(IDS_WRONG_FILE_SIZE));
    }

    // If the file header is fine, read all of the rest

    CHECK(*ppDIB = (PBYTE) GlobalAlloc(
        GMEM_FIXED, 
        bmfh.bfSize - sizeof(BITMAPFILEHEADER)
    ));

    CHECK(ReadFile(
        hFile,
        *ppDIB,
        bmfh.bfSize - sizeof(BITMAPFILEHEADER),
        &dwNumberOfBytesRead,
        0
    ));

    // Store the offset of the actual bitmap bits from the start of the DIB

    *pdwOffBits = bmfh.bfOffBits - sizeof(BITMAPFILEHEADER);

    // Check the version of the header

    if (
        !IsCoreHeader(*ppDIB) &&
        !IsInfoHeader(*ppDIB) &&
        !IsV4Header(*ppDIB)   &&
        !IsV5Header(*ppDIB)
    ) {

        ERROR_MESSAGE(ResourceString(IDS_UNKNOWN_HEADER));
    }

    BEGIN_CLEANUP;

    if (!BRESULT && *ppDIB) {

        CHECK(GlobalFree(*ppDIB) == 0);
        *ppDIB = 0;
    }

    if (hFile != INVALID_HANDLE_VALUE) {

        CHECK(CloseHandle(hFile));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// SaveBMP
//
// Routine Description:
//   Writes a BMP file
//
// Arguments:
//   PCTSTR pFileName   name of the file to open
//   PVOID  pDIB        a global memory pointer to the DIB 
//   DWORD  dwOffBits   offset of the bitmap bits from the start of the DIB
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
WINAPI
SaveBMP(
    PCTSTR pFileName,
    PBYTE  pDIB,
    DWORD  dwOffBits
)
{
    USES_BRESULT;
    HANDLE           hFile = INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    DWORD            dwNumberOfBytesWritten;

    ASSERT(pFileName);

    CHECK((hFile = CreateFile(
        pFileName,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        0,
        CREATE_ALWAYS,
        FILE_FLAG_SEQUENTIAL_SCAN,
        0
    )) != INVALID_HANDLE_VALUE);

    // Write the file header

    bmfh.bfType      = MAKEWORD('B', 'M');
    bmfh.bfSize      = sizeof(bmfh) + GlobalSize(pDIB);
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfOffBits   = sizeof(bmfh) + dwOffBits;

    CHECK(WriteFile(
        hFile,
        &bmfh,
        sizeof(bmfh),
        &dwNumberOfBytesWritten,
        0
    ));

    // Write the DIB

    CHECK(WriteFile(
        hFile,
        pDIB,
        GlobalSize(pDIB),
        &dwNumberOfBytesWritten,
        0
    ));

    BEGIN_CLEANUP;

    if (hFile != INVALID_HANDLE_VALUE) {

        CHECK(CloseHandle(hFile));
    }

    return BRESULT;
}
