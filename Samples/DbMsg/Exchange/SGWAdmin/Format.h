// -----------------------------------------------------------------------------
// Format.h : header file
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#include <stdarg.h>

//----------------------------------------------------------------------------

// Pass a printf() style format string and variable argument list 
// and we will return a CString with the results.
CString _Format( TCHAR *pFmt, va_list pVArg);
    
// Pass a printf() style format string and variable arguments
// and we will return a CString with the results.
CString Format( TCHAR *pFmt ...);

// Pass a string resource handle as the format string and list of 
// variable arguments and we will return a CString with the results.
CString _FormatResource( int hResStr, va_list pVArg);

// Pass a string resource handle as the format string and variable 
// arguments and we will return a CString with the results.
CString FormatResource( int hResStr ...);

//----------------------------------------------------------------------------
