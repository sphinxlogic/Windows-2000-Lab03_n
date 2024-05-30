// --mapimem.c-------------------------------------------------------------------
// 
//  Memory wrapping functions for DEBUG builds.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#define _PRIVATE_EDKDEBUG_H
#define _PRIVATE_MEMORY_H

#include "edk.h"
#include "_exchdbg.h"

#include <stddef.h>
#include <malloc.h>

//$--EDKDBG_MAPIAllocateBuffer--------------------------------------------------
//  Wrapper for MAPIAllocateBuffer().
// -----------------------------------------------------------------------------
SCODE EDKDBG_MAPIAllocateBuffer(        // RETURNS: status code
    IN  ULONG ulLine,                   // line number
    IN  LPSTR lpszFile,                 // file name
    IN  ULONG ulSize,                   // size of memory block
    OUT LPVOID *lppv)                   // pointer to memory block address
                                        // variable
{
    SCODE sc            = 0;
    CHAR  buf[BUFSIZ+1] = {0};

    if(IsBadWritePtr(lppv, sizeof(LPVOID)))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid pointer [%08lx]\n", lppv);

        REPORT_ERROR(buf);

        sc = E_INVALIDARG;

        return(sc);
    }

    sc = MAPIAllocateBuffer(
        ulSize,
        lppv);

    if(FAILED(sc))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",ulSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,ulSize);
    }

    return(sc);
}

//$--EDKDBG_MAPIAllocateMore----------------------------------------------------
//  Wrapper for MAPIAllocateMore().
// -----------------------------------------------------------------------------
SCODE EDKDBG_MAPIAllocateMore(          // RETURNS: status code
    IN  ULONG ulLine,                   // line number
    IN  LPSTR lpszFile,                 // file name
    IN  ULONG ulSize,                   // size of memory block
    IN  LPVOID lpvOriginal,             // pointer to original memory block
    OUT LPVOID *lppvData)               // pointer to memory block address
                                        // variable
{
    SCODE sc            = 0;
    CHAR  buf[BUFSIZ+1] = {0};

    if(IsBadReadPtr(lpvOriginal, 1))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid original pointer [%08lx]\n", lpvOriginal);

        REPORT_ERROR(buf);

        sc = E_INVALIDARG;

        return(sc);
    }

    if(IsBadWritePtr(lppvData, sizeof(LPVOID)))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid pointer [%08lx]\n", lppvData);

        REPORT_ERROR(buf);

        sc = E_INVALIDARG;

        return(sc);
    }

    sc = MAPIAllocateMore(
        ulSize,
        lpvOriginal,
        lppvData);

    if(FAILED(sc))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",ulSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,ulSize);
    }

    return(sc);
}

//$--EDKDBG_MAPIFreeBuffer------------------------------------------------------
//  Wrapper for MAPIFreeBuffer().
// -----------------------------------------------------------------------------
SCODE EDKDBG_MAPIFreeBuffer(            // RETURNS: status code
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN LPVOID lpv)                      // pointer to memory block
{
    SCODE sc            = 0;
    CHAR  buf[BUFSIZ+1] = {0};

    if((lpv != NULL) && IsBadWritePtr(lpv, 1))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid pointer [%08lx]\n", lpv);

        REPORT_ERROR(buf);

        sc = E_INVALIDARG;

        return(sc);
    }

    sc = MAPIFreeBuffer(lpv);

    if(FAILED(sc))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: deallocation failed\n");

        REPORT_ERROR(buf);
    }

    return(sc);
}
