// --propid.h------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _PROPID_H_
#define _PROPID_H_

#define PR_SCRIPT					PROP_TAG( PT_TSTRING, 0x7102 )
#define PR_SCRIPT_A					PROP_TAG( PT_STRING8, 0x7102 )
#define PR_SCRIPT_W					PROP_TAG( PT_UNICODE, 0x7102 )
#define PR_ICS_STREAM				PROP_TAG( PT_BINARY,  0x7103 )
#define PR_HANDLER_CLSID			PROP_TAG( PT_TSTRING, 0x7104 )
#define PR_HANDLER_PROGID			PROP_TAG( PT_TSTRING, 0x7105 )
#define PR_HANDLER_PROGID_A			PROP_TAG( PT_STRING8, 0x7105 )
#define PR_HANDLER_PROGID_W			PROP_TAG( PT_UNICODE, 0x7105 )
#define PR_HANDLER_LOG				PROP_TAG( PT_MV_TSTRING, 0x7106 )
#define PR_HANDLER_LOG_A			PROP_TAG( PT_MV_STRING8, 0x7106 )
#define PR_HANDLER_LOG_W			PROP_TAG( PT_MV_UNICODE, 0x7106 )
#define PR_HANDLER_LOG_MAX			PROP_TAG( PT_LONG, 0x7107 )
#define PR_SCRIPT_LAST_MOD_TIME		PROP_TAG( PT_SYSTIME, 0x7108 )
#define PR_SCRIPT_LAST_MOD_BY		PROP_TAG( PT_BINARY, 0x7109 )
// new / used message detection
#define PR_PROCESSED                PROP_TAG( PT_BOOLEAN, 0x710A )

#define EVENT_SCRIPT_CLASS		"Event.Script"
#define SCRIPT_HANDLER_PROGID	"ActiveEx.ScriptHandler"

enum EventType
{
	Invalid,
	Folder_OnTimer,
	Folder_OnMessageCreated,
	Folder_OnMessageDeleted,
	Message_OnChange,
	Message_OnMove,
};

#endif