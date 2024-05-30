/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996 - 1999.  Microsoft Corporation.  All rights reserved.


Module Name:

    security.h

Abstract:

    Functions to handle communication with the security package

Revision History:

--*/

# if !defined (INC_SECURITY_H)
#define INC_SECURITY_H

BOOL InitPackage (DWORD *pcbMaxMessage);
BOOL TermPackage ();
BOOL InitSession (DWORD_PTR dwKey);
BOOL TermSession (DWORD_PTR dwKey);
BOOL GenClientContext (
                      DWORD_PTR dwKey,
                      BYTE *pIn,
                      DWORD cbIn,
                      BYTE *pOut,
                      DWORD *pcbOut,
                      BOOL *pfDone
                      );
BOOL GenServerContext (
                      DWORD_PTR dwKey,
                      BYTE *pIn,
                      DWORD cbIn,
                      BYTE *pOut,
                      DWORD *pcbOut,
                      BOOL *pfDone
                      );
BOOL ImpersonateContext (DWORD_PTR dwKey);
BOOL RevertContext (DWORD_PTR dwKey);

#endif
