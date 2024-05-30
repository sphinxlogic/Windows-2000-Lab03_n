// --memory.c-------------------------------------------------------------------
// 
//  Memory wrapping functions for DEBUG builds.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#define _PRIVATE_EDKDEBUG_H   
#define _PRIVATE_MEMORY_H

#include <malloc.h>

#define _INC_MALLOC

#include "edk.h"
#include "_exchdbg.h"

#ifdef _NTSDK
#undef _NTSDK
#endif

#include <stddef.h>

#undef _INC_MALLOC


//$--_DebugMemoryStatus---------------------------------------------------------
//  Writes an entry in the debug log for memory status.
// -----------------------------------------------------------------------------
void _DebugMemoryStatus(                // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN ULONG cBytes)                    // count of bytes
{
    CHAR         buf[BUFSIZ+1] = {0};
    MEMORYSTATUS ms            = {0};

    ZeroMemory(&ms, sizeof(MEMORYSTATUS));

    ms.dwLength = sizeof(MEMORYSTATUS);

    GlobalMemoryStatus(&ms);

	_snprintf(
	    buf,
        BUFSIZ,
	    "\n\tMEMORY:\tAllocBytes: %lu\n"
	    "\t\tMemoryLoad: %lu\n"
	    "\t\tTotalPhys: %lu ; AvailPhys: %lu\n"
	    "\t\tTotalPageFile: %lu ; AvailPageFile: %lu\n"
	    "\t\tTotalVirtual: %lu ; AvailVirtual: %lu\n",
        cBytes,
	    ms.dwMemoryLoad,
	    ms.dwTotalPhys,
	    ms.dwAvailPhys,
	    ms.dwTotalPageFile,
	    ms.dwAvailPageFile,
	    ms.dwTotalVirtual,
	    ms.dwAvailVirtual);

    REPORT_STATUS(buf);
}

//$--_DebugHeapStatus-----------------------------------------------------------
//  Writes an entry in the debug log.
// -----------------------------------------------------------------------------
static void _DebugHeapStatus(           // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN int heapstatus)                  // heap status
{
    CHAR buf[BUFSIZ+1] = {0};

    switch (heapstatus)
	{
    case _FREEENTRY:
	    _snprintf(buf,BUFSIZ,"HEAP: free entry in heap\n");
	    break;
    case _HEAPOK:
	    break;
    case _HEAPEMPTY:
	    _snprintf(buf,BUFSIZ,"HEAP: heap is empty\n");
        break;
    case _HEAPEND:
	    _snprintf(buf,BUFSIZ,"HEAP: end of heap\n");
	    break;
    case _HEAPBADPTR:
	    _snprintf(buf,BUFSIZ,"HEAP: bad pointer to heap\n");
	    break;
    case _HEAPBADBEGIN:
	    _snprintf(buf,BUFSIZ,"HEAP: bad start of heap\n");
	    break;
    case _HEAPBADNODE:
	    _snprintf(buf,BUFSIZ,"HEAP: bad node in heap\n");
	    break;
    default:
	    _snprintf(buf,BUFSIZ,"HEAP: _heapchk returned [%u]\n", heapstatus);
    }

    if(heapstatus != _HEAPOK)
    {
        REPORT_ERROR(buf);
    }
}

//$--_DebugHeapCheck------------------------------------------------------------
//  Writes an entry in the debug log. This function is only called in
//  DEBUG builds through the DebugHeapCheck() macro.
// -----------------------------------------------------------------------------
void _DebugHeapCheck(                   // RETURNS: return code
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile)                  // file name
{
    int heapstatus = _HEAPOK;

    heapstatus = _heapchk();
    
    _DebugHeapStatus(ulLine, lpszFile, heapstatus);
}

//$--_DebugDumpHeap-------------------------------------------------------------
//  Writes an entry in the debug log. This function is only called in
//  DEBUG builds through the DebugDumpHeap() macro.
// -----------------------------------------------------------------------------
void _DebugDumpHeap(                    // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile)                  // file name
{
    _HEAPINFO hi            = {0};
    int       heapstatus    = _HEAPOK;
    CHAR      buf[BUFSIZ+1] = {0};

    ZeroMemory(&hi, sizeof(_HEAPINFO));

    while((heapstatus = _heapwalk (&hi)) == _HEAPOK)
    {
        if (hi._useflag == _USEDENTRY)
        {
            _snprintf(buf, BUFSIZ, "HEAP: used block at %08lx of size %u\n",
                hi._pentry,
                hi._size );

            REPORT_STATUS(buf);
        }
    }

    if(heapstatus != _HEAPOK)
    {
        _DebugHeapStatus(ulLine, lpszFile, heapstatus);
    }
}

//$--EDKDBG_malloc--------------------------------------------------------------
//  Wrapper for malloc().
// -----------------------------------------------------------------------------
LPVOID EDKDBG_malloc(                   // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulSize)                    // size of memory block
{
    LPVOID lpv           = NULL;
    CHAR   buf[BUFSIZ+1] = {0};

    _DebugHeapCheck(ulLine, lpszFile);

    lpv = malloc(ulSize);

    if(lpv != NULL)
    {
        if(ulSize > 0)
        {
            FillMemory(lpv, ulSize, 0xCC);
        }
    }
    else
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",ulSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,ulSize);
    }

    return(lpv);
}

//$--EDKDBG_calloc--------------------------------------------------------------
//  Wrapper for calloc().
// -----------------------------------------------------------------------------
LPVOID EDKDBG_calloc(                   // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulNum,                     // number of elements
    IN ULONG ulSize)                    // size of element
{
    LPVOID lpv           = NULL;
    CHAR   buf[BUFSIZ+1] = {0};

    _DebugHeapCheck(ulLine, lpszFile);

    lpv = calloc(ulNum, ulSize);

    // Calloc cannot fill with 0xCC since that changes the known behaviour of calloc

    if(lpv == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",ulSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,ulSize);
    }

    return(lpv);
}

//$--EDKDBG_realloc-------------------------------------------------------------
//  Wrapper for realloc().
// -----------------------------------------------------------------------------
LPVOID EDKDBG_realloc(                  // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN LPVOID lpvBlock,                 // pointer to memory block
    IN ULONG ulSize)                    // new size of memory block
{
    LPVOID lpv           = NULL;
    CHAR   buf[BUFSIZ+1] = {0};

    _DebugHeapCheck(ulLine, lpszFile);

    lpv = realloc(lpvBlock, ulSize);

    if(lpv == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",ulSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,ulSize);
    }

    return(lpv);
}

//$--EDKDBG_strdup--------------------------------------------------------------
//  Wrapper for strdup().
// -----------------------------------------------------------------------------
char* EDKDBG_strdup(                    // RETURNS: pointer to allocated string
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN const char *lpsz)                // pointer to string
{
    LPVOID lpv           = NULL;
    CHAR   buf[BUFSIZ+1] = {0};

    if(IsBadStringPtrA(lpsz, INFINITE))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid pointer [%08lx]\n", lpsz);

        REPORT_ERROR(buf);

        return(lpv);
    }

    _DebugHeapCheck(ulLine, lpszFile);

    lpv = _strdup(lpsz);

    if(lpv == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",0,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,0);
    }

    return((char *)lpv);
}

//$--EDKDBG_wcsdup--------------------------------------------------------------
//  Wrapper for _wcsdup().
// -----------------------------------------------------------------------------
wchar_t* EDKDBG_wcsdup(                 // RETURNS: pointer to allocated string
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN const wchar_t *lpsz)             // pointer to string
{
    LPVOID lpv           = NULL;
    CHAR   buf[BUFSIZ+1] = {0};

    if(IsBadStringPtrW(lpsz, INFINITE))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid pointer [%08lx]\n", lpsz);

        REPORT_ERROR(buf);

        return(lpv);
    }

    _DebugHeapCheck(ulLine, lpszFile);

    lpv = _wcsdup(lpsz);

    if(lpv == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",0,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,0);
    }

    return((wchar_t *)lpv);
}

//$--EDKDBG_free----------------------------------------------------------------
//  Wrapper for free().
// -----------------------------------------------------------------------------
void EDKDBG_free(                       // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN LPVOID lpv)                      // pointer to memory block
{
    _DebugHeapCheck(ulLine, lpszFile);

    free(lpv);

    return;
}

//$--EDKDBG_GlobalAlloc---------------------------------------------------------
//  Wrapper for GlobalAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_GlobalAlloc(             // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN UINT  fuFlags,                   // allocation flags
    IN DWORD dwSize)                    // size of memory block
{
    LPVOID  lpv           = NULL;
    HGLOBAL hglb          = NULL;
    DWORD   cBytes        = 0;
    CHAR    buf[BUFSIZ+1] = {0};

    _DebugHeapCheck(ulLine, lpszFile);

    if((fuFlags != 0) && (! (fuFlags & GMEM_VALID_FLAGS)))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid allocation flags [%08lx]\n", fuFlags);

        REPORT_ERROR(buf);
    }

    hglb = GlobalAlloc(fuFlags, dwSize);

    if(hglb == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",dwSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,dwSize);
    }

    return(hglb);
}

//$--EDKDBG_GlobalReAlloc-------------------------------------------------------
//  Wrapper for GlobalReAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_GlobalReAlloc(           // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hglb,                    // pointer to memory block
    IN DWORD cbBytes,                   // new size of memory block
    IN UINT  fuFlags)                   // allocation flags
{
    LPVOID  lpv           = NULL;
    CHAR    buf[BUFSIZ+1] = {0};
    UINT    gflags        = 0;
    HGLOBAL hglbMem       = 0;

    _DebugHeapCheck(ulLine, lpszFile);

    if((fuFlags != 0) && (! (fuFlags & GMEM_VALID_FLAGS)))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid allocation flags [%08lx]\n", fuFlags);

        REPORT_ERROR(buf);
    }

    gflags = GlobalFlags(hglb);

    if(gflags == GMEM_INVALID_HANDLE)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid handle [%08lx]\n", hglb);

        REPORT_ERROR(buf);

        return(hglbMem);
    }

    hglbMem = GlobalReAlloc(hglb, cbBytes, fuFlags);

    if(hglbMem == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",cbBytes,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,cbBytes);
    }

    return(hglbMem);
}

//$--EDKDBG_GlobalFree----------------------------------------------------------
//  Wrapper for GlobalFree().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_GlobalFree(              // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hglb)                    // pointer to memory block
{
    LPVOID  lpv           = NULL;
    CHAR    buf[BUFSIZ+1] = {0};
    UINT    gflags        = 0;
    HGLOBAL hglbMem       = 0;

    _DebugHeapCheck(ulLine, lpszFile);

    gflags = GlobalFlags(hglb);

    if(gflags == GMEM_INVALID_HANDLE)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid handle [%08lx]\n", hglb);

        REPORT_ERROR(buf);

        SetLastError(ERROR_INVALID_HANDLE);

        return(hglb);
    }

    if(hglb == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid handle [%08lx]\n", hglb);

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,0);
    }

    hglbMem = GlobalFree(hglb);

    if(hglbMem != NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: deallocation failed [%08lx]\n", GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,0);
    }

    return(hglbMem);
}

//$--EDKDBG_LocalAlloc----------------------------------------------------------
//  Wrapper for LocalAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_LocalAlloc(              // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN UINT  fuFlags,                   // allocation flags
    IN DWORD dwSize)                    // size of memory block
{
    LPVOID  lpv           = NULL;
    HGLOBAL hglb          = NULL;
    CHAR    buf[BUFSIZ+1] = {0};

    _DebugHeapCheck(ulLine, lpszFile);

    if((fuFlags != 0) && (! (fuFlags & LMEM_VALID_FLAGS)))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid allocation flags [%08lx]\n", fuFlags);

        REPORT_ERROR(buf);
    }

    hglb = LocalAlloc(fuFlags, dwSize);

    if(hglb == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",dwSize,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,dwSize);
    }

    return(hglb);
}

//$--EDKDBG_LocalReAlloc--------------------------------------------------------
//  Wrapper for LocalReAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_LocalReAlloc(            // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hglb,                    // pointer to memory block
    IN DWORD cbBytes,                   // new size of memory block
    IN UINT  fuFlags)                   // allocation flags
{
    LPVOID  lpv           = NULL;
    CHAR    buf[BUFSIZ+1] = {0};
    UINT    gflags        = 0;
    HGLOBAL hglbMem       = 0;

    _DebugHeapCheck(ulLine, lpszFile);

    if((fuFlags != 0) && (! (fuFlags & LMEM_VALID_FLAGS)))
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid allocation flags [%08lx]\n", fuFlags);

        REPORT_ERROR(buf);
    }

    gflags = LocalFlags(hglb);

    if(gflags == LMEM_INVALID_HANDLE)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid handle [%08lx]\n", hglb);

        REPORT_ERROR(buf);

        return(hglbMem);
    }

    hglbMem = LocalReAlloc(hglb, cbBytes, fuFlags);

    if(hglbMem == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: allocation of [%lu] bytes failed [%08lx]\n",cbBytes,GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,cbBytes);
    }

    return(hglbMem);
}

//$--EDKDBG_LocalFree-----------------------------------------------------------
//  Wrapper for LocalFree().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_LocalFree(               // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hglb)                    // pointer to memory block
{
    LPVOID  lpv           = NULL;
    CHAR    buf[BUFSIZ+1] = {0};
    UINT    gflags        = 0;
    HGLOBAL hglbMem       = 0;

    _DebugHeapCheck(ulLine, lpszFile);

    gflags = LocalFlags(hglb);

    if(gflags == LMEM_INVALID_HANDLE)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid handle [%08lx]\n", hglb);

        REPORT_ERROR(buf);

        SetLastError(ERROR_INVALID_HANDLE);

        return(hglb);
    }

    if(hglb == NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: invalid handle [%08lx]\n", hglb);

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,0);
    }

    hglbMem = LocalFree(hglb);

    if(hglbMem != NULL)
    {
	    _snprintf(buf,BUFSIZ,"MEMORY: deallocation failed [%08lx]\n", GetLastError());

        REPORT_ERROR(buf);

        _DebugMemoryStatus(ulLine,lpszFile,0);
    }

    return(hglbMem);
}
