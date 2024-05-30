// --edklog.c-------------------------------------------------------------------
//
//  Functions to log debugging information in DEBUG builds.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------
 
#define _PRIVATE_EDKDEBUG_H
#define _PRIVATE_MEMORY_H
#include "edk.h"

#define REPORT_ERROR(x) \
    _WriteDebugString( \
        "***** error: %s, %lu, [%08lX] *****\n", __FILE__,__LINE__,(x))

#define DECL_FENCE(_name)   ULONG _dbg_##_name = 0xAAAAAAAA

#define TEST_FENCE(_name)   \
{ \
    if(_dbg_##_name != 0xAAAAAAAA) \
    { \
        _WriteDebugString( \
            "***** error: %s, %lu, memory overwrite at tag '%s'! *****\n", \
            __FILE__,__LINE__,#_name); \
    } \
}

DECL_FENCE(EDKDEBUG1);

static BOOL fDebugLevel[D_LAST] =
    {
        TRUE,
        TRUE,
        TRUE,
        TRUE,
        TRUE,
        TRUE,
        TRUE
    };

DECL_FENCE(EDKDEBUG2);

static BOOL             IsAssertOff = TRUE;

DECL_FENCE(EDKDEBUG3);

static BOOL             IsDebugOff  = FALSE;

DECL_FENCE(EDKDEBUG4);

static CHAR szFileName[MAX_PATH+1]  = {0};

DECL_FENCE(EDKDEBUG5);

static FILE*            fp          = NULL;

DECL_FENCE(EDKDEBUG6);

static CRITICAL_SECTION cs          = {0};

DECL_FENCE(EDKDEBUG7);

#define TEST_ALL_FENCES \
{ \
    TEST_FENCE(EDKDEBUG1); \
    TEST_FENCE(EDKDEBUG2); \
    TEST_FENCE(EDKDEBUG3); \
    TEST_FENCE(EDKDEBUG4); \
    TEST_FENCE(EDKDEBUG5); \
    TEST_FENCE(EDKDEBUG6); \
    TEST_FENCE(EDKDEBUG7); \
}

//$--_WriteDebugString----------------------------------------------------------
//
//  Write a string to the debugger output window.
//  
// -----------------------------------------------------------------------------
void _WriteDebugString(                 // RETURNS: nothing
    IN LPSTR lpszFormat,                // format string
    ...)                                // arguments
{
    char lpsz[BUFSIZ+1] = {0};
    va_list va_alist    = {0};

    SetLastError(ERROR_SUCCESS);

    __try
    {
        va_start( va_alist, lpszFormat );

        _vsnprintf( lpsz, BUFSIZ, lpszFormat, va_alist );

        va_end( va_alist );

        OutputDebugString(lpsz);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        SetLastError(_exception_code());
    }
}

//$--_StatusShowAssert----------------------------------------------------------
//
//  Status of the assert prompt.
//  
// -----------------------------------------------------------------------------
BOOL _StatusShowAssert(             // RETURNS: TRUE if assert prompt
    void)                           // no arguments
{
    TEST_ALL_FENCES // Check for memory overwrites in global variables

    return(!IsAssertOff);
}

//$--_StatusDebugFile-----------------------------------------------------------
//
//  Status of the debug log file.
//  
// -----------------------------------------------------------------------------
BOOL _StatusDebugFile(              // RETURNS: TRUE if debug log available
    void)                           // no arguments
{
    BOOL fStatus = TRUE;

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    if((fp == NULL) || (IsDebugOff == TRUE))
    {
        fStatus = FALSE;
    }

    return(fStatus);
}

//$--_StatusDebugLevel----------------------------------------------------------
//
//  Status of the debug level.
//  
// -----------------------------------------------------------------------------
BOOL _StatusDebugLevel(             // RETURNS: nothing
    IN DEBUGLEVEL level)            // debug level
{
    BOOL fStatus = TRUE;

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    if( (_StatusDebugFile() == FALSE) ||
        (level >= D_LAST) ||
        (fDebugLevel[(int)level] == FALSE))
    {

        fStatus = FALSE;
    }

    return(fStatus);
}

//$--_LockDebugFile-------------------------------------------------------------
//
//  Lock the debug log file.
//  
// -----------------------------------------------------------------------------
void _LockDebugFile(                // RETURNS: nothing
    void)                           // no arguments
{
    CHAR sz[BUFSIZ+1] = {0};

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    __try
    {
        EnterCriticalSection(&cs);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        REPORT_ERROR(_exception_code());
    }
}

//$--_UnlockDebugFile-----------------------------------------------------------
//
//  Unlock the debug log file.
//  
// -----------------------------------------------------------------------------
void _UnlockDebugFile(              // RETURNS: nothing
    void)                           // no arguments
{
    CHAR sz[BUFSIZ+1] = {0};

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    __try
    {
        LeaveCriticalSection(&cs);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        REPORT_ERROR(_exception_code());
    }
}

//$--_WriteDebugFile------------------------------------------------------------
//
//  Write to the debug log file.
//  
// -----------------------------------------------------------------------------
void _WriteDebugFile(               // RETURNS: nothing
    IN LPSTR lpszFormat,            // format string
    ...)                            // arguments
{
    va_list va_alist   = {0};

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    if(fp == NULL)
    {
        REPORT_ERROR(ERROR_INVALID_PARAMETER);
        goto cleanup;
    }

    __try
    {
        EnterCriticalSection(&cs);

        __try
        {
            va_start( va_alist, lpszFormat );

            vfprintf( fp, lpszFormat, va_alist );
    
            va_end( va_alist );

            fflush(fp);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            REPORT_ERROR(_exception_code());
        }

        LeaveCriticalSection(&cs);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        REPORT_ERROR(_exception_code());
    }

cleanup:

    return;
}

//$--SetDebugLevel--------------------------------------------------------------
//  Set debug levels to log.
// -----------------------------------------------------------------------------
static void SetDebugLevel(              // RETURNS: nothing
    IN LPSTR lpszLevel)                 // textized debug level
{
    int   level         = 0;
    char* lpszToken     = NULL;
    char  buf[BUFSIZ+1] = {0};

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    if(lpszLevel == NULL)
    {
        goto cleanup;
    }

    if(IsBadStringPtrA(lpszLevel, INFINITE))
    {
        REPORT_ERROR(ERROR_INVALID_PARAMETER);
        goto cleanup;
    }

    IsDebugOff = TRUE;

    for(level = 0; level < D_LAST; level++)
    {
        // Turn the debug level off
        fDebugLevel[level] = FALSE;
    }

    strncpy(buf, lpszLevel, BUFSIZ);
    buf[BUFSIZ] = 0;

    lpszToken = strtok(buf,", ");

    while(lpszToken != NULL)
    {
        if(!_stricmp("D_PUBLIC", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_PUBLIC] = TRUE; IsDebugOff = FALSE;
        }
        else if(!_stricmp("D_PRIVATE", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_PRIVATE] = TRUE; IsDebugOff = FALSE;
        }
        else if(!_stricmp("D_ERROR", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_ERROR] = TRUE; IsDebugOff = FALSE;
        }   
        else if(!_stricmp("D_WARNING", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_WARNING] = TRUE; IsDebugOff = FALSE;
        }   
        else if(!_stricmp("D_STATUS", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_STATUS] = TRUE; IsDebugOff = FALSE;
        }   
        else if(!_stricmp("D_ACTION", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_ACTION] = TRUE; IsDebugOff = FALSE;
        }   
        else if(!_stricmp("D_OTHER", lpszToken))
        {
            // Turn the debug level on
            fDebugLevel[(int)D_OTHER] = TRUE; IsDebugOff = FALSE;
        }

        lpszToken = strtok(NULL, ", ");
    }

cleanup:

    return;
}

//$--_InitDebugFile-------------------------------------------------------------
//
//  Initialize the debug log file.
//  
// -----------------------------------------------------------------------------
void _InitDebugFile(                // RETURNS: nothing
    void)                           // no arguments
{
    HANDLE hT                      = NULL;
    DWORD  dwT                     = 0;
    CHAR   szMutexName[MAX_PATH+1] = {0};
	CHAR   szTempPath[MAX_PATH+1]  = {0};	    // temporary file name path

    TEST_ALL_FENCES // Check for memory overwrites in global variables

    if((fp == NULL) && (IsDebugOff == FALSE))
    {
        _snprintf(szMutexName, MAX_PATH, "EDK%08lX", GetCurrentProcessId());

        hT = CreateMutex(NULL, FALSE, szMutexName);

        if(hT == NULL)
        {
            REPORT_ERROR(GetLastError());
            return;
        }

        if((hT != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
        {
            __try
            {
                dwT = WaitForSingleObject(hT, INFINITE);

                if((dwT == WAIT_OBJECT_0) || (dwT == WAIT_ABANDONED))
                {
                    ReleaseMutex(hT);
                }

                CloseHandle(hT);
            }
            __except(EXCEPTION_EXECUTE_HANDLER)
            {
                REPORT_ERROR(_exception_code());
            }

            return;
        }

        dwT = WaitForSingleObject(hT, INFINITE);

        if((dwT == WAIT_OBJECT_0) || (dwT == WAIT_ABANDONED))
        {
            LPSTR lpsz = NULL;

            InitializeCriticalSection(&cs);

            SetDebugLevel(getenv("EDK_DEBUG"));

            if(IsDebugOff == FALSE)
            {
                lpsz = getenv("EDK_DEBUG_FILE");

                if(lpsz == NULL)
                {
					// Create a file in the temporary file directory
					// with name equal to "EDKxxx.log".
					dwT = GetTempPath(
						MAX_PATH,		// length of buffer
						szTempPath);	// string buffer

					if ( dwT != 0 )
					{
                        // If TEMP has been removed, we'll create it
                        (VOID)CreateDirectory(
                            szTempPath,
                            NULL);

						dwT = GetTempFileName(
							szTempPath,				// temporary file path
							EDK_LOG_FILE_PREFIX,	// log file prefix
							0,						// creates unique file name
							szFileName);			// file name buffer

						if ( dwT != 0 )
						{
                            UINT    iFileSuffix = 0;

                            // Delete the edk*.tmp file created as a side
                            // effect of GetTempFileName().
                            (VOID)DeleteFile(szFileName);
    
                            // Replace .TMP suffix with .LOG suffix.
                            iFileSuffix = cbStrLenA(szFileName) - sizeof("TMP");
                            lstrcpyA( &szFileName[iFileSuffix], EDK_LOG_FILE_SUFFIX);
						}
                        else
                        {
							REPORT_ERROR(GetLastError());
                        }
					}
					else
					{
						REPORT_ERROR(GetLastError());
					}
                }
                else
                {
                    strncpy((char *)szFileName, lpsz, MAX_PATH);
                }

                szFileName[MAX_PATH] = 0;

                if((fp = fopen(szFileName, "w")) == NULL)
                {
                    REPORT_ERROR(ERROR_INVALID_PARAMETER);
                }
            }

            lpsz = getenv("EDK_ASSERT");

            if((lpsz != NULL) && (lstrcmpiA(lpsz, "TRUE") == 0))
            {
                IsAssertOff = FALSE;
            }

            ReleaseMutex(hT);
        }
        else
        {
            REPORT_ERROR(GetLastError());
        }

        CloseHandle(hT);
    }
}
