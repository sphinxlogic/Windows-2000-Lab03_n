/************************************************************************
*                                                                       *
*   $$Root$$Util.h													*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/

#ifndef $$ROOT$$_UTIL_H
#define $$ROOT$$_UTIL_H

#include "StdAfx.h"
$$IF(!PROJTYPE_NTSERVICE)
#include "$$Root$$TraceBox.h"
$$ENDIF

//
// Collector types
//

const short CONTENT_COLLECTOR	= 0;
const short HIERARCHY_COLLECTOR = 1;

//
// GUIDs for interfaces used by the ICS same
// 
const GUID __IID_IExchangeExportChanges = {0xa3ea9cc0,0xd1b2,0x11cd,0x80,0xfc,0x00,0xaa,0x00,0x4b,0xba,0x0b};
const GUID __IID_IExchangeImportContentsChanges = {0xf75abfa0,0xd0e0,0x11cd,0x80,0xfc,0x00,0xaa,0x00,0x4b,0xba,0x0b};
const GUID __IID_IExchangeImportHierarchyChanges = {0xf75abfa1, 0xd0e0,0x11cd,0x80,0xfc,0x00,0xaa,0x00,0x4b,0xba,0x0b};

//
// Utility procedures used by the ICS sample code
//

void DebugMessage(const string & strMessage);
void ErrorMessage(const string & strMessage);
void FatalErrorMessage(const string & strMessage);
ULONG GetNumProcessors();
$$IF(PROJTYPE_NTSERVICE)
BOOL ReportICSEvent(LPCTSTR szMsg, int iMsgType);
$$ENDIF
void StatusMessage(const string & strMessage);
void WarningMessage(const string & strMessage);

$$IF(!PROJTYPE_NTSERVICE)
extern C$$Root$$TraceBox theTraceBox;
$$ENDIF

#endif // #ifndef $$ROOT$$_UTIL_H

