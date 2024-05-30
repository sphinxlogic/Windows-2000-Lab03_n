;// --cfgcode.mc----------------------------------------------------------------
;//
;//  This file contains the messages displayed by the sample cfgcode.
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
SymbolicName=CFGCODE_CANNOT_GET_CURRENT_DIR
Language=English
Unable to get current directory due to the following error:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_CANNOT_PACK_CONFIG_INFO
Language=English
Unable to pack configuration information into binary structure.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_CANNOT_READ_PROFILE_SECTION
Language=English
Unable to read MAPI properties from section [%1] in file %2 due to the following error:%n%3
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_CANNOT_READ_PROFILE_SECTION_FNF
Language=English
Unable to read MAPI properties from section [%1] in file %2.  Either the system can't find the file specified or the file is not formatted correctly.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_NO_PROP_TAG
Language=English
No property tag found in the string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_PROP_TAG_WITHOUT_EQUALS
Language=English
Property tag not followed by "=" in the string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_ILLEGAL_BINARY_VALUE
Language=English
Illegal binary value in string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_ILLEGAL_BOOLEAN_VALUE
Language=English
Illegal boolean value in string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_ILLEGAL_LONG_VALUE
Language=English
Illegal long integer value in string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_ILLEGAL_SYSTIME_VALUE
Language=English
Illegal date/time value in string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_CANNOT_CONVERT_TIME
Language=English
Unable to convert from system time to file time for string:%n%1%ndue to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_UNSUPPORTED_PROPERTY_TYPE
Language=English
Unsupported property type in string:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_COULD_NOT_CREATE_FILE
Language=English
Could not create file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_COULD_NOT_WRITE_FILE
Language=English
Could not write file %1 due to the following error:%n%2
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=CFGCODE_COULD_NOT_CLOSE_FILE
Language=English
Could not close file %1 due to the following error:%n%2
.
