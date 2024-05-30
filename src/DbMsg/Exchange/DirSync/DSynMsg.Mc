;// --dsynmsg.mc----------------------------------------------------------------
;//
;//  This file contains the messages displayed by the dirsync sample.
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
SymbolicName=DIRSYNC_ERROR
Language=English
%1
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_EXPORT_SUCCEEDED
Language=English
Export operation completed successfully.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_EXPORT_SUCCEEDED_KEY
Language=English
Export operation completed successfully for key %1.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_EXPORT_SUCCEEDED_INSTANCE
Language=English
Export operation completed successfully for instance %1.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_INTERNAL_ERROR
Language=English
DirSync internal error.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_INVALID_REGISTRY_KEY_NAME
Language=English
DirSync instance registry key name %1 is invalid.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_CREATE_KEY
Language=English
Unable to create registry key %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_OPEN_KEY
Language=English
Unable to open registry key %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_READ_REGISTRY_VALUE
Language=English
Unable to read registry value %1 from key %2 due to the following error:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_WRITE_REGISTRY_VALUE
Language=English
Unable to write registry value %1 to key %2 due to the following error:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_CREATE_EXPORT_FILE
Language=English
Unable to create export file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_WRITE_EXPORT_FILE
Language=English
Unable to write to export file %1 due to the following error:%n%2%nFile will be deleted.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_CLOSE_EXPORT_FILE
Language=English
Unable to close export file %1 due to the following error:%n%2%nFile will be deleted.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_OPEN_IMPORT_FILE
Language=English
Unable to open import file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_READ_IMPORT_FILE
Language=English
Unable to read from import file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_CLOSE_IMPORT_FILE
Language=English
Unable to close import file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_INVALID_IMPORT_LINE
Language=English
Invalid line found while parsing object "%3" in import file "%1", line %2:%n%4
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_IMPORT_LINE_TOO_LONG
Language=English
Line too long in import file "%1", line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_CANNOT_IMPORT_COMMON_NAME
Language=English
The Common-Name attribute cannot be used since it is already implied by the first line of the import record.  Import file %1, line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_DUPLICATE_IMPORT_ATTRIBUTE
Language=English
Duplicate attribute "%1" in import file %2, line %3.:%n%4
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=DIRSYNC_CANNOT_REGISTER_DAPI_EVENT_SOURCE
Language=English
Unable to initialize DAPI event logging due to the following error:%n%1
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=DIRSYNC_CANNOT_INIT_MAPI
Language=English
Unable to initialize MAPI.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=DIRSYNC_INVALID_REGISTRY_VALUE_SIZE
Language=English
Size of data in registry value "%1" in key "%2" is not an even multiple of %3.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_BEGIN_IMPORT
Language=English
Import operation started to server %1.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_BEGIN_IMPORT_KEY
Language=English
Import operation started to server %1 for key %2.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_BEGIN_IMPORT_INSTANCE
Language=English
Import operation started to server %1 for instance %2.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_END_IMPORT
Language=English
Import operation completed with %1 object(s) imported to server %2.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_END_IMPORT_KEY
Language=English
Import operation completed with %1 object(s) imported to server %2 for key %3.
.
MessageId=
Severity=Informational
Facility=Application
SymbolicName=DIRSYNC_END_IMPORT_INSTANCE
Language=English
Import operation completed with %1 object(s) imported to server %2 for instance %3.
.
