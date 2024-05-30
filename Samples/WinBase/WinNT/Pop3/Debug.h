
/*----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1992-1999.  Microsoft Corporation.  All rights reserved.

This source code is only intended as a supplement to
Microsoft Development Tools and/or WinHelp documentation.
See these sources for detailed information regarding the
Microsoft samples programs.

File:       debug.h

----------------------------------------------------------------------------*/


#ifndef __DEBUG_H__
#define __DEBUG_H__

#if DBG

extern  DWORD   PopInfoLevel;

#define DebugLog(x) LogEvent x


void    LogEvent(long, const char *, ...);
void    InitDebugSupport(void);

#define DEB_ERROR           0x00000001
#define DEB_WARN            0x00000002
#define DEB_TRACE           0x00000004
#define DEB_TRACE_PROT      0x00000008

#else

#define DebugLog(x)
#define InitDebugSupport()


#endif



#endif // __DEBUG_H__
