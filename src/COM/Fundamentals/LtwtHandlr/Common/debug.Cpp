/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/
#include <stdio.h>
#include "debug.h"

/****************************************************************************

        FUNCTION: DebugMsg(const TCHAR, ...) 

        PURPOSE:  Prints formatted output to the debugger ala printf.
		PARAMETERS:
		   *pFmt   - string with the necessary formatting codes
		    ...     - arguments being embedded in the pFmt string.

		RETURN VALUE: Returns number of bytes written or -1 if buffer is too small

        COMMENTS: Calling this function should be just like calling printf.  The only
			      difference is this function outputs to the debugger instead of STDOUT.


****************************************************************************/
int DebugMsg(const TCHAR *pFmt, ...)
{
#ifdef _DEBUGTRACE
    int i;
    const int iMsgSize = 512;
    va_list pArgs;
    char szMsg[512];

    // outputs formatted string to debugger
    // returns count of bytes written or -1 if buffer size is too small

    va_start( pArgs, pFmt );
     i = wsprintf(szMsg, pFmt, pArgs);
/*
    #ifdef UNICODE
        i = _vsnwprintf(szMsg, iMsgSize+1, pFmt, pArgs);
    #else
        i = _vsnprintf(szMsg, iMsgSize+1, pFmt, pArgs);
    #endif
*/
    va_end( pArgs );

    OutputDebugString( szMsg );

    return( i );
#else
	return 0;
#endif
}
