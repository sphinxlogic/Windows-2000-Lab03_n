// --edkdebug.c-----------------------------------------------------------------
//
//  Functions to log debugging information in DEBUG builds.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------
 
#define _PRIVATE_EDKDEBUG_H
#define _PRIVATE_MEMORY_H
#include "edk.h"

#define REPORT_ERROR(x) \
    _WriteDebugString("error: %s, %lu, %s\n", __FILE__,__LINE__,(x))

static LPSTR szNullA = "";

//$--GetComponentFileName-------------------------------------------------------
//  Return a text representation of a component file name.
// -----------------------------------------------------------------------------
static LPSTR GetComponentFileName(      // RETURNS: component file name
    IN LPSTR lpszFile)                  // pointer to file name
{
    LPSTR pszT = NULL;
    LPSTR psz  = NULL;

    if(IsBadStringPtrA(lpszFile, INFINITE))
    {
        return(szNullA);
    }

    psz  = lpszFile;

    pszT = lpszFile + lstrlen(lpszFile);

    while(pszT >= lpszFile)
    {
        if(*pszT == '\\')
        {
            psz = pszT;
        }
        else if((*pszT == ':'))
        {
            psz = pszT;
            break;
        }

        pszT--;
    }
    
    if((*psz == '\\') || (*psz == ':'))
    {
        psz++;
    }

    return(psz);
}

//$--BoolName-------------------------------------------------------------------
//  Return a text representation of a boolean value.
// -----------------------------------------------------------------------------
static LPSTR BoolName(                  // RETURNS: textized boolean value
    IN BOOL fStatus)                    // boolean value
{
    switch(fStatus)
    {
        case TRUE:
            return("TRUE");
        case FALSE:
            return("FALSE");
        default:
            return("UNKNOWN");
    }
}

//$--DebugLevelName-------------------------------------------------------------
//  Return a text representation of a debug level.
// -----------------------------------------------------------------------------
static LPSTR DebugLevelName(            // RETURNS: textized debug level
    IN DEBUGLEVEL eLevel)               // debug level
{
    switch(eLevel)
    {
        case D_PUBLIC:
            return("D_PUBLIC");
        case D_PRIVATE:
            return("D_PRIVATE");
        case D_ERROR:
            return("D_ERROR");
        case D_WARNING:
            return("D_WARNING");
        case D_STATUS:
            return("D_STATUS");
        case D_ACTION:
            return("D_ACTION");
        case D_OTHER:
            return("D_OTHER");
        default:
            return("UNKNOWN");
    }
}

//$--_ShowAssert----------------------------------------------------------------
//  Prompts user for what action to take on an assertion failure.
// -----------------------------------------------------------------------------
static void _ShowAssert(                // RETURNS: nothing
    IN LPSTR lpszFile,                  // source file name
    IN ULONG ulLine)                    // source line number
{
    int  n              = 0;
    char lpsz[BUFSIZ+1] = {0};

    LPSTR  lpszPrompt
        =  "%s - line %lu\n"
                "\n"
                "Click on ABORT  to exit the application.\n"
                "Click on RETRY  to debug the application.\n"
                "Click on IGNORE to continue.";

    __try
    {
        n = _snprintf(
            lpsz,
            BUFSIZ,
            lpszPrompt,
            GetComponentFileName(lpszFile),
            ulLine);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        REPORT_ERROR(_exception_code());
        n = -1;
    }

    if(n < 0)
    {
        goto cleanup;
    }

    n = MessageBox(NULL,
        lpsz,
        "Assertion Failure",
        MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_TASKMODAL);

    switch(n)
    {
        case IDABORT:
            // User chose to terminate program
            ExitProcess(0);
            break;
        case IDRETRY:
            // User chose to trap into the debugger
            DebugBreak();
            break;
        case IDIGNORE:
            // User chose to continue execution
            break;
        default:
            break;
    }

cleanup:

    return;
}

//$--_Assert--------------------------------------------------------------------
//  
//  Write to the debug log file and/or evaluate assertion.
//  
// -----------------------------------------------------------------------------
void _Assert(                   // RETURNS: nothing
    IN LPSTR lpszTag,           // tag name
    IN LPSTR lpszFile,          // source file name
    IN ULONG ulLine,            // source line number
    IN DEBUGLEVEL Level,        // assertion level
    IN BOOL fValue,             // assertion value
    IN LPSTR lpszFormat,        // format string
    ...)                        // arguments
{
    char       lpsz[BUFSIZ+1] = {0};
    va_list    va_alist       = {0};
    SYSTEMTIME st             = {0};
    FILETIME   ft             = {0};
    BOOL       fRet           = FALSE;
        
    _InitDebugFile();

    if(_StatusDebugLevel(Level) == FALSE)
    {
        goto cleanup;
    }

    if((lpszTag == NULL) || IsBadStringPtrA(lpszTag, INFINITE))
    {
        REPORT_ERROR(ERROR_INVALID_PARAMETER);
        goto cleanup;
    }

    if((lpszFile == NULL) || IsBadStringPtrA(lpszFile, INFINITE))
    {
        REPORT_ERROR(ERROR_INVALID_PARAMETER);
        goto cleanup;
    }

    if((lpszFormat == NULL) || IsBadStringPtrA(lpszFormat, INFINITE))
    {
        REPORT_ERROR(ERROR_INVALID_PARAMETER);
        goto cleanup;
    }

    _LockDebugFile();

    if(((Level != D_ERROR) && (Level != D_WARNING)) ||
       (((Level == D_ERROR) || (Level == D_WARNING)) && (fValue == FALSE)))
    {
        __try
        {
            GetSystemTime(&st);

            fRet = SystemTimeToFileTime(&st, &ft);

            if(fRet != TRUE)
            {
                ft.dwLowDateTime  = 0;
                ft.dwHighDateTime = 0;
            }

            _WriteDebugFile(
                "%08lX%08lX %s - process %lu, thread %lu, level %s, file %s, line %lu: ",
                ft.dwHighDateTime,
                ft.dwLowDateTime,
                lpszTag,
                GetCurrentProcessId(),
                GetCurrentThreadId(),
                DebugLevelName(Level),
                lpszFile,
                ulLine);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            REPORT_ERROR(_exception_code());
        }

        __try
        {
            va_start( va_alist, lpszFormat );

            _vsnprintf( lpsz, BUFSIZ, lpszFormat, va_alist );

            va_end( va_alist );

            _WriteDebugFile("%s", lpsz);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            REPORT_ERROR(_exception_code());
        }
    }

    _UnlockDebugFile();

cleanup:

    if(_StatusShowAssert() && (fValue == FALSE) && (Level == D_ERROR))
    {
        _ShowAssert(lpszFile, ulLine);
    }

    return;
}
