;// --fimportm.mc---------------------------------------------------------------
;//
;//  This file contains the messages displayed by the fimportsample.
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
SymbolicName=FIMPORT_ERROR
Language=English
%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_INTERNAL_ERROR
Language=English
FImport internal error:%n%1
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=FIMPORT_CANNOT_INIT_MAPI
Language=English
Unable to initialize MAPI.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_PROFILE_LOGON_ERROR
Language=English
ERROR: Could not log on to profile "%1". [0x%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_LOGON_ERROR
Language=English
ERROR: Could not log on to existing MAPI session. [0x%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_READ_IMPORT_FILE
Language=English
Unable to read from import file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_CLOSE_IMPORT_FILE
Language=English
Unable to close import file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_IMPORT_LINE_TOO_LONG
Language=English
Line too long in import file "%1", line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_INVALID_FOLDER_PATH
Language=English
Invalid folder path:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_FIND_STORE
Language=English
Can't find message store "%1".  [%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_FIND_DEFAULT_STORE
Language=English
Error locating default message store.  [%1]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_OPEN_STORE
Language=English
Unable to open message store "%1".  [%2]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_WRONG_STORE_TYPE
Language=English
Message store "%1" is wrong object type (%2).
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_FIND_FOLDER
Language=English
Can't find folder "%1" in message store "%2".  [%3]
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_OPEN_FOLDER
Language=English
Unable to open folder "%1" in message store "%2".  [%3]
.

MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_WRONG_FOLDER_TYPE
Language=English
Folder "%1" in message store "%2" is wrong object type (%3).
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_OPEN_IMPORT_FILE
Language=English
Unable to open import file "%1" due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_INVALID_KEYWORD
Language=English
Invalid keyword "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_AMBIGUOUS_KEYWORD
Language=English
Ambiguous keyword "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_ILLEGAL_BINARY_VALUE
Language=English
Illegal binary value "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_ILLEGAL_GUID_VALUE
Language=English
Illegal GUID value "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_ILLEGAL_BOOLEAN_VALUE
Language=English
Illegal boolean value "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_ILLEGAL_LONG_VALUE
Language=English
Illegal long integer value "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_ILLEGAL_SYSTIME_VALUE
Language=English
Illegal date/time value "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_UNSUPPORTED_PROPERTY_TYPE
Language=English
Property type "%4" is not supported by FImport.  Found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_UNEXPECTED_END_OF_FILE
Language=English
Unexpected end of file encountered in file "%1" line %2.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_INVALID_TYPE_PREFIX
Language=English
Invalid property type code '%4' found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_UNKNOWN_PROPERTY
Language=English
Unknown property "%4" found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_WRONG_NUMBER_OF_PROPERTY_VALUES
Language=English
Number of property values in line does not match the number of properties in the header line.  Found in file "%1" line %2:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_WRONG_MESSAGE_TYPE
Language=English
Message is wrong type (%1).
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=FIMPORT_PROBLEMS_SETTING_MESSAGE_PROPERTIES
Language=English
Problems setting message properties.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=FIMPORT_CANNOT_ADD_ATTACHMENT
Language=English
Unable to add message attachment "%4".  Found in file "%1" line %2:%n%3
.
