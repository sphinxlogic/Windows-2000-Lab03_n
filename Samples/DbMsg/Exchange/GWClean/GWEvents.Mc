;// --gwevents.mc----------------------------------------------------------------
;//
;//  This file contains the messages displayed by the GWCLEAN sample.
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
SymbolicName=GWCLEAN_ERROR
Language=English
%1
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=GWCLEAN_SUCCESS
Language=English
%1 messages moved.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=GWCLEAN_NOMSGS
Language=English
WARNING: There are no message prior to %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_INTERNALERR
Language=English
ERROR: Internal program error: %1 returned 0x%2.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_PROFILEERR
Language=English
ERROR: Could not locate or access profile %1. [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_MAPIINIT
Language=English
ERROR Extended MAPI services could not be initialized. [0x%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_POSCHANGED
Language=English
ERROR: Position in message table changed during copy.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_NOCOPYMSGS
Language=English
ERROR: Service provider doesn't support copying of messages.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_PARTIALCOPY
Language=English
ERROR: Not all messages to be moved could be copied. [0x%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_PARTIALDEL
Language=English
ERROR: Not all copied messages could be deleted. [0x%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_NOTGWPROF
Language=English
ERROR: Profile %1 is not a gateway profile.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_OUTOFDISK
Language=English
ERROR: Not enough disk space to move messages.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_OUTOFMEMORY
Language=English
ERROR: Insufficient memory.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_BADFOLDER
Language=English
ERROR: Can't open folder %1 in profile %2. [0x%3]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWCLEAN_NEWPSTERR
Language=English
ERROR: Can't create/open PST %1. [0x%2]
.
