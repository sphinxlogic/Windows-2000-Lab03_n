/*-----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

ENUMDRV.H
-----------------------------------------------------------------------------*/


#ifndef ENUMDRV_INCLUDED
#define ENUMDRV_INCLUDED

// procedure definitions

BOOL   CheckRM      (LPTSTR);
BOOL   FillRDStruct (LPDINFO);
VOID   EnumDrives   (LPDINFO*);

#endif
