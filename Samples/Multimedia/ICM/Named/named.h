/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:
    
    named.h

Abstract:
    
    Header file for named.c

--*/

#ifndef NAMED_H
#define NAMED_H

//////////////////////////////////////////////////////////////////////////
//
// Function prototypes
//

BOOL
ReadNamedProfile(
    PCTSTR pFileName,
    PCTSTR pColorNameToFind
);

BOOL
FindColorIndex(
    HPROFILE hProfile,
    PCTSTR   pColorNameToFind
);

BOOL
PrintAllColorNames(
    HPROFILE hProfile
);


#endif //NAMED_H
