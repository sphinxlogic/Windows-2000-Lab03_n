/******************************************************************************\
 *       This is a part of the Microsoft Source Code Samples. 
 *       Copyright (C) 1997 Microsoft Corporation.
 *       All rights reserved. 
 *       This source code is only intended as a supplement to 
 *       Microsoft Development Tools and/or WinHelp documentation.
 *       See these sources for detailed information regarding the 
 *       Microsoft samples programs.
\******************************************************************************/

#ifndef MERGEPROXYDEBUG_H
#define MERGEPROXYDEBUG_H

#include <windows.h>

int DebugMsg(const TCHAR *pFmt, ...);

#ifdef _DEBUGTRACE
	#define DebugTrace DebugMsg
#else
	#define DebugTrace DebugMsg
#endif

#endif