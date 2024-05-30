/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    named.c

Abstract:

    Named Color Profiles Sample

--*/

#include "pch.h"
#include "named.h"
#include "conv.h"
#define IMPLEMENT_CHECK
#include "check.h"

#define COUNTOF(Array) ( sizeof(Array) / sizeof(Array[0]) )

//////////////////////////////////////////////////////////////////////////
//
// _tmain
//
// Routine Description:
//   The initial entry point - unicode aware version
//
// Arguments:
//  int   argc     Number of command line arguments
//  PTSTR argv[]   Array of command line argument strings
//
// Return Value:
//   The exit code (== 0 for this program)
//

int
__cdecl
_tmain(
    int   argc,
    PTSTR argv[]
)
{
    if (argc < 2) {

        _tprintf(
            _T("Usage: %s <Named profile filename> [Color name to find]\n"),
            argv[0]
        );

        return 1;
    }

    return ReadNamedProfile(
        argv[1],
        argc > 2 ? argv[2] : 0
    );
}

//////////////////////////////////////////////////////////////////////////
//
// ReadNamedProfile
//
// Routine Description:
//   Reads a named color profile, displays the color names or 
//   finds the index of a given color
//
// Arguments:
//  PCTSTR pFileName          Named color profile file name
//  PCTSTR pColorNameToFind   Name of the color to find
//                            or 0 to list all the color names
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
ReadNamedProfile(
    PCTSTR pFileName,
    PCTSTR pColorNameToFind
)
{
    USES_BRESULT;
    TCHAR       szProfileName[MAX_PATH];
    PTSTR       pFilePart;
    PROFILE     p;
    HPROFILE    hProfile = 0;
    BOOL        bValid;

    // get the full qualified path name for the profile

    CHECK(GetFullPathName(
        pFileName,
        COUNTOF(szProfileName),
        szProfileName,
        &pFilePart
    ));

    // open the profile

    p.dwType       = PROFILE_FILENAME;
    p.pProfileData = (PVOID) szProfileName;
    p.cbDataSize   = (_tcslen(szProfileName) + 1) * sizeof(TCHAR);

    CHECK(hProfile = OpenColorProfile(
        &p, 
        PROFILE_READ, 
        FILE_SHARE_READ, 
        OPEN_EXISTING
    ));

    // check whether the profile is valid

    CHECK(IsColorProfileValid(
        hProfile,
        &bValid
    ));

    CHECK(bValid);

    if (pColorNameToFind) {

        CHECK(FindColorIndex(
            hProfile,
            pColorNameToFind
        ));

    } else {

        CHECK(PrintAllColorNames(hProfile));
    }

    BEGIN_CLEANUP;

    if (hProfile) {

        CHECK(CloseColorProfile(hProfile));
    }

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// FindColorIndex
//
// Routine Description:
//   Finds the index of a given color name
//
// Arguments:
//  HPROFILE hProfile          Handle to the open color names profile
//  PCTSTR   pColorNameToFind  Name of the color to find
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
FindColorIndex(
    HPROFILE hProfile,
    PCTSTR   pColorNameToFind
)
{
    USES_BRESULT;
    USES_CONVERSION;
    COLOR_NAME AnsiColorNameToFind;
    DWORD      dwIndex = 0;

    strcpy(
        AnsiColorNameToFind,
        T2A(pColorNameToFind)
    );

    CHECK(ConvertColorNameToIndex(
        hProfile, 
        &AnsiColorNameToFind, 
        &dwIndex, 
        1
    ));

    printf("%d: %s\n", dwIndex, AnsiColorNameToFind);

    BEGIN_CLEANUP;

    return BRESULT;
}

//////////////////////////////////////////////////////////////////////////
//
// PrintAllColorNames
//
// Routine Description:
//   Displays all of the color names in a named color profile
//
// Arguments:
//  HPROFILE hProfile        Handle to the open color names profile
//
// Return Value:
//   Zero on error / nonzero on success
//

BOOL
PrintAllColorNames(
    HPROFILE hProfile
)
{
    USES_BRESULT;
    NAMED_PROFILE_INFO  npi;
    PDWORD              pIndex = 0;
    PCOLOR_NAME         pColorName = 0;
    DWORD               i;

    // print the profile info

    CHECK(GetNamedProfileInfo(
        hProfile, 
        &npi
    ));

    printf("Total number of named colors in the profile = %d\n", npi.dwCount);
    printf("Total number of device coordinates for each named color = %d\n", npi.dwCountDevCoordinates);
    printf("Prefix for each color name = %s\n", npi.szPrefix);
    printf("Suffix for each color name = %s\n", npi.szSuffix);

    // allocate memory for the color indices and 
    // initialize the array in order to list all color names
    // *** the color indices start with the offset 1 ***

    CHECK(pIndex = (PDWORD) GlobalAlloc(
        GMEM_FIXED, 
        npi.dwCount * sizeof(DWORD)
    ));

    for (i = 0; i < npi.dwCount; ++i) {

        pIndex[i] = i + 1;
    }

    // allocate memory for the color names

    CHECK(pColorName = (PCOLOR_NAME) GlobalAlloc(
        GMEM_FIXED, 
        npi.dwCount * sizeof(COLOR_NAME)
    ));

    // get the corresponding color names for all the index values

    CHECK(ConvertIndexToColorName(
        hProfile, 
        pIndex, 
        pColorName, 
        npi.dwCount
    ));

    for (i = 0; i < npi.dwCount; ++i) {

        printf("%d: %s\n", pIndex[i], pColorName[i]);
    }

    BEGIN_CLEANUP;

    if (pIndex) {

        CHECK(GlobalFree(pIndex) == 0);
    }

    if (pColorName) {

        CHECK(GlobalFree(pColorName) == 0);
    }

    return BRESULT;
}

