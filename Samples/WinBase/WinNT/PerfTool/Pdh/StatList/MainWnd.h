/*
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

data type and constant definitions used by mainwnd.c
*/

#include <pdh.h>

typedef struct _CounterInfoBlock {
    struct _CounterInfoBlock *pNext;
    TCHAR   szCounterPath[MAX_PATH];
    HCOUNTER    hCounter;
    PPDH_RAW_COUNTER    pCounterArray;
    DWORD       dwFirstIndex;
    DWORD       dwNextIndex;
    DWORD       dwLastIndex;
    PDH_STATISTICS  pdhCurrentStats;
    double      dLastValue;
} CIB, *PCIB;

// global functions found in mainwnd.c
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
