;// --edkmsg.mc-----------------------------------------------------------------
;//
;//  This file contains the messages common to the entire EDK.
;//
;// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
;// ----------------------------------------------------------------------------
;//
;//
;// Message Naming Convention
;// -------------------------
;//
;// Each message has a symbolic name that becomes a #define'ed constant for 
;// use in a .C file.  A message's symbolic name should follow this naming 
;// convention:
;// 
;// <COMPONENT>_<MESSAGE_DESCRIPTION>
;//
;// If a message is used by more than one library and/or application, then 
;// <COMPONENT> should be "EDKEVENT".
;//
;// The <MESSAGE_DESCRIPTION> portion of the name describes what the message 
;// is about.  For example, a message called EDKEVENT_INVALID_HEX_DIGIT could 
;// indicate that an illegal hexidecimal digit was found.
;//
;// Only the first message in this file should have a Message ID number--
;// the message compiler will then assign consecutive numbers to the rest.
;//
;//

MessageIdTypedef=DWORD

;// Generic Information message allowing user to fill in text or error code.
MessageId=0
Severity=Informational
Facility=Application
SymbolicName=EDKEVENT_INFORMATION
Language=English
%1
.
;// Generic Warning message allowing user to fill in text or error code.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=EDKEVENT_WARNING
Language=English
%1
.
;// Generic Error message allowing user to fill in text or error code.
MessageId=
Severity=Error
Facility=Application
SymbolicName=EDKEVENT_ERROR
Language=English
%1
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=WINWRAP_SERVICE_STARTING
Language=English
Service starting.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=WINWRAP_SERVICE_STARTED
Language=English
Service started.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=WINWRAP_SERVICE_STOPPING
Language=English
Service stopping.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=WINWRAP_SERVICE_STOPPED
Language=English
Service stopped.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=EDKEVENT_CANNOT_INIT_MAPI
Language=English
Unable to initialize MAPI.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=MESGXLAT_CNV_CONVERT_FAIL
Language=English
%1 conversion DLL convert function failed:  point = %2, class = %3, error code = %4.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=MESGXLAT_CNV_NO_CANDIDATE
Language=English
No conversion DLL candidate found for point = %1 and class = %2.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=MESGXLAT_CNV_NO_ACCEPT
Language=English
Candidate conversion DLL %1 rejected conversion for point = %2, class = %3.  Error code = %4.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=MESGXLAT_CNV_QUERY_FAIL
Language=English
Conversion DLL %1 query function failed:  point = %2, class = %3.  Error code = %4.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=MESGXLAT_CNV_BAD_SYNTAX
Language=English
Invalid registry key values for MAPI Conversion DLL %1:  entry point = %2 class = %3, options = %4, point = %5.
.
