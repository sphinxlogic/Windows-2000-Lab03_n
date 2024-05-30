;// --iformmsg.mc---------------------------------------------------------------
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
SymbolicName=INSTFORM_INTERNAL_ERROR
Language=English
INTERNAL ERROR: %1 returned 0x%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=INSTFORM_NOTFOUND_ERROR
Language=English
ERROR: Cannot find specified message store and/or folder. [0x%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=INSTFORM_USER_CANCEL_ERROR
Language=English
ERROR: User canceled installation.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=INSTFORM_EXTENDED_ERROR
Language=English
EXTENDED ERROR:  %1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=INSTFORM_FORM_NOT_FOUND_ERROR
Language=English
ERROR: Form %1 not found.
.
