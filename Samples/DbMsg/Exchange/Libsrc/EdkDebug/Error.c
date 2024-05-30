// --error.c--------------------------------------------------------------------
// 
//  Function error code wrapping functions for DEBUG builds.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#define _PRIVATE_EDKDEBUG_H
#define _PRIVATE_MEMORY_H
#include "edk.h"

//$--EDKDBG_HrLog---------------------------------------------------------------
//  Log an HRESULT (and the last Win32 error) to the debug log.
// -----------------------------------------------------------------------------
HRESULT EDKDBG_HrLog(                   // RETURNS: HRESULT
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulLine,                    // line number
    IN HRESULT hr,                      // function return code
    IN DWORD dwLastError)               // last Win32 error
{
    _Assert(
        "ASSERT",
        lpszFile,
        ulLine,
        D_ERROR,
        SUCCEEDED(hr),
        "A function/method returned [%08lX] [%08lX]\n",
        hr,
        dwLastError);

    SetLastError(dwLastError);

    return(hr);
}

//$--EDKDBG_HrFailed------------------------------------------------------------
//  Log an HRESULT (and the last Win32 error) to the debug log.
// -----------------------------------------------------------------------------
BOOL EDKDBG_HrFailed(                   // RETURNS: HRESULT
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulLine,                    // line number
    IN HRESULT hr,                      // function return code
    IN DWORD dwLastError)               // last Win32 error
{
    _Assert(
        "ASSERT",
        lpszFile,
        ulLine,
        D_ERROR,
        SUCCEEDED(hr),
        "A function/method returned [%08lX] [%08lX]\n",
        hr,
        dwLastError);

    SetLastError(dwLastError);

    return(FAILED(hr));
}
