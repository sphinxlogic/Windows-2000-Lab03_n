// --_exchdbg.h-----------------------------------------------------------------
// 
//  Header file for internal DEBUG functions.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EXCHDBG_H
#define _EXCHDBG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef DEBUG
#ifndef REPORT_ERROR
#define REPORT_ERROR(x) \
    { \
        OutputDebugString((x)); \
        _Assert("ASSERT", lpszFile, ulLine, D_ERROR, FALSE, "%s", (x)); \
    }
#endif

#define REPORT_STATUS(x) \
    { \
        OutputDebugString((x)); \
        _Assert("DEBUG", lpszFile, ulLine, D_STATUS, FALSE, "%s", (x)); \
    }

#else
#ifndef REPORT_ERROR
#define REPORT_ERROR(x) ((void)0)
#endif
#define REPORT_STATUS(x) ((void)0)
#endif

//$--_DebugMemoryStatus---------------------------------------------------------
//  Writes an entry in the debug log for memory status.
// -----------------------------------------------------------------------------
void _DebugMemoryStatus(                // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN ULONG cBytes);                   // count of bytes

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
