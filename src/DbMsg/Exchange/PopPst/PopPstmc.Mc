;// --poppstmc.mc----------------------------------------------------------------
;//
;//  This file contains the messages displayed by the poppst sample.
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
;// If a message is used only by a single EDK sample application, then it 
;// should be placed in that application's .MC file and <COMPONENT> should be 
;// the name of the application (for example, "PERFTEST").
;//
;// If a message is used only by a single EDK library, then it should be placed 
;// in the EDK common message file ("EDKMSGS.MC") and <COMPONENT> should be the 
;// name of the library (for example, "MONITOR").
;//
;// If a message is used by more than one library and/or application, then 
;// it should be placed in the EDK common message file ("EDKMSGS.MC") and 
;// <COMPONENT> should be "EDKEVENT".
;//
;// The <MESSAGE_DESCRIPTION> portion of the name describes what the message 
;// is about.  For example, a message called EDKEVENT_INVALID_HEX_DIGIT could 
;// indicate that an illegal hexidecimal digit was found.
;//
;//
;// Message ID's
;// ------------
;//
;// Message ID's 0-1023 are for messages common to the entire EDK.
;// Message ID's 1024+ are for messages specific to each EDK executable.
;//
;// Only the first message in this file should have a Message ID number--
;// the message compiler will then assign consecutive numbers to the rest.
;//
;//

MessageIdTypedef=DWORD

MessageId=1024
Severity=Error
Facility=Application
SymbolicName=POPPST_ERROR
Language=English
%1
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=POPPST_POPULATE_SUCCEEDED
Language=English
PST populated successfully.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=POPPST_TEMPORARY_PROFILE_WARNING
Language=English
WARNING:  Using a temporary profile. No name resolution will be performed.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=POPPST_RESOLVE_WARNING
Language=English
WARNING: Could not resolve recipient names for Message at line %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_RESOLVE_ERROR
Language=English
ERROR: Could not resolve recipient names for Message at line %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_OPEN_FILE_ERROR
Language=English
ERROR: Can't open file %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_INTERNAL_ERROR
Language=English
ERROR: Internal program error: %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_MAPIINIT_ERROR
Language=English
ERROR:  MAPI initialization failed. [0x%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_SYNTAX_ERROR
Language=English
ERROR:	Syntax error at line %1 of input file.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_LENGTH_ERROR
Language=English
ERROR:  Line %1 of input file is too long.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_EMPTY_ERROR
Language=English
ERROR:  Input file %1 is empty.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_IO_ERROR
Language=English
ERROR: I/O error reading line %1 of INI file.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_FOLDER_ERROR
Language=English
ERROR: Could not open folder %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_ORDER_ERROR
Language=English
ERROR: Profile or NewPST section must preceed Message section; line %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_MISSING_ERROR
Language=English
ERROR: %1 section at line %2 is missing a required value.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_MUTUAL_EXCLUSIVENESS_ERROR
Language=English
ERROR: Exactly one Profile OR NewPST section required; line %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_NEWPST_ERROR
Language=English
ERROR: Could not create PST %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_LOGON_ERROR
Language=English
ERROR: Could not log on to profile %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_OPEN_STORE_ERROR
Language=English
ERROR: Could not open default message store for profile %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_AB_ERROR
Language=English
ERROR: Could not open address book for profile %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_FROM_ERROR
Language=English
ERROR: Exactly one FROM value allowed per message section; message starts at line %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_SENDER_ERROR
Language=English
ERROR: Could not resolve FROM name %1: message at %2. [0x%3]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_NEED_RECIPIENT_ERROR
Language=English
ERROR: At least one recipient required per message; line %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=POPPST_BODY_ERROR
Language=English
ERROR: Message body for messsage starting at line %1 is too large.
.
