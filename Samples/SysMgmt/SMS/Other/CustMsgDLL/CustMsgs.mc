;//*****************************************************************************
;//
;// Copyright (c) 1999, Microsoft Corporation, All Rights Reserved
;//
;// FILE: custmsgs.mc
;//
;// This file contains instructions and samples for making custom status messages
;//   for use with the SMS Provider. These status messages can be raised by calling
;//   the SMS_StatusMessage::RaiseRawStatusMessage method in the SMS Provider
;//   see the CustMsg.exe sample for details on calling RaiseRawStatusMessage
;//
;// ESCAPE SEQUENCES: - (A list of escape codes you can use in your status messages)
;//
;//     %0  - This terminates a message text line without a trailing newline.
;//           This can be used to build up long lines or to terminate the
;//           message itself without a trailing newline.
;//
;//     %1  - Insertion string #1.
;//     %2  - Insertion string #2.
;//     %3  - Insertion string #3.
;//     %4  - Insertion string #4.
;//     %5  - Insertion string #5.
;//     %6  - Insertion string #6.
;//     %7  - Insertion string #7.
;//     %8  - Insertion string #8.
;//     %9  - Insertion string #9.
;//     %10 - Insertion string #10.
;//
;//     %11 - String prepended by the status system to the beginning of every
;//           message; MUST appear before the message string.
;//
;//     %12 - String appended by the status system to the end of every message;
;//           MUST appear at the very end of the message string.
;//
;//     .   - When on a line by itself, terminates the message.
;//
;//     %%  - Outputs a single percent sign in the formatted message text.
;//
;//     %n  - Outputs a hard line break when it occurs at the end of a line.
;//           Useful when FormatMessage is supplying normal line breaks so the
;//           message fits in a certain width.
;//
;//     %r  - Outputs a hard carriage return, without a trailing newline.
;//
;//     %b  - Outputs a space in the formatted message text.  This can be used
;//           to insure there are the appropriate number of trailing spaces in a
;//           message text line.
;//
;//     %t  - Outputs a tab in the formatted message text.
;//
;//     %.  - Outputs a single period in the formatted message text.  This can
;//           be used to get a single period at the beginning of a line without
;//           terminating the message text definition.
;//
;//     %!  - Outputs a single exclamation point in the formatted message text.
;//           This can be used to get an exclamation point immediately after an
;//           insert without it being mistaken for the beginning of a printf
;//           format string.
;//
;//    
;//*****************************************************************************

;// MessageIdTypeDef & SeverityNames are SMS Specific and should NOT be altered

MessageIdTypedef=DWORD

SeverityNames=(Success=0x0
               Informational=0x1
               Warning=0x2
               Error=0x3
              )

;// LanguageNames allows you to create Locale specific status messages
;//   for this sample, we'll use English.
;// Note: you should change the 'custmsgs' string to reflect the
;//   the altered name of this file. So if you rename this file to MyMsg.mc
;//   then the following line would read "LanguageNames=(English=0x409:MyMsg)"

LanguageNames=(English=0x409:custmsgs)

;//	- Change these defines to fit your own Status Messages Module Name

;#ifndef CUSTOM_MESSAGES
;#define CUSTOM_MESSAGES

;//*****************************************************************************
;//*
;//*    Display name for this module
;//*
;//*    The display string at the end of the first message block in the
;//*    following segment is the "ModuleName" for this Message DLL In order to
;//*    install and use this DLL, you must specify a unique ModuleName.  The 
;//*    SMS Provider itself uses "SMS Provider" as the ModuleName for all of 
;//*    it's status messages
;//*    
;//*    All calls to the SMS_StatusMessage::RaiseRawStatusMessage() Method require
;//*    a ModuleName as one of the Input-Parameters, this is where the ModuleName
;//*	is defined (for this sample, we use 'Custom Messages' as our ModuleName)
;//*
;//*    The 2nd and 3rd Message blocks in the below section are used to 
;//*    help SMS Install and access this Message DLL, Only modify the SymbolicName
;//*    property, the rest of the properties should be left alone
;//*
;//*****************************************************************************

MessageID=0
Severity=Success
Facility=Application
SymbolicName=CUSTOM_MESSAGES_MODULE_NAME
Language=English
Custom Messages%0
.

MessageID=300
Severity=Success
Facility=Application
SymbolicName=CUSTOM_MESSAGES_NEXT_TO_LAST_INSSTR
Language=English
On %s, component %s on computer %s reported:  %0
.

MessageID=301
Severity=Success
Facility=Application
SymbolicName=CUSTOM_MESSAGES_LAST_INSSTR
Language=English
 The operating system reported error %lu: %s%0
.

;//*****************************************************************************
;//*
;//*    COMPONENT NAMES (in ALPHABETICAL ORDER!)
;//*
;//*    - MessageID ranges from 1 to 299 (decimal).
;//*
;//*    - Severity must be Success.
;//*
;//*    - Facility must be Application.
;//*
;//*    - SymbolicName must begin with <your module name>_COMP_.  (For this sample, CUSTMSG_COMP_UNKNOWN will do)
;//*
;//*    - The message string itself must end with %0 and contain no other escape
;//*      sequences.
;//*
;//*    - <your module name>_COMP_UNKNOWN must be first!!! (for this sample CUSTMSG_COMP_UNKOWN)
;//*      Then your custom components follow.  when you use the AddMsgDLL Tool to add this DLL
;//*      to SMS, (described in the ReadMe), you'll need to re-specify these Component names
;//*
;//*    - leave the message text as 'Unknown Component' for the first component
;//*
;//*****************************************************************************

MessageID=1
Severity=Success
Facility=Application
SymbolicName=CUSTOM_MESSAGES_COMP_UNKNOWN
Language=English
Unknown Component%0
.

MessageID=2
Severity=Success
Facility=Application
SymbolicName=CUSTOM_MESSAGES_COMP_CUSTOM
Language=English
Custom Component%0
.


;//*****************************************************************************
;//*
;//*    COMPONENT-SPECIFIC MESSAGES (FOR A CUSTOM MESSAGE DLL)
;//*
;//*    These messages are specific to your custom message dll.
;//*
;//*    - MessageID - SMS uses from 0 - 39999, any ID over 40,000 should be open for
;//*                  any custom status messages.  Note: you can use any ID you wish since
;//*                  the 'module name' property will be specific to your custom DLL, but this may
;//*                  lead to conflicting Status Message IDs which could be confusing
;//*
;//*		Note: The MessageID you use when calling RaiseRawStatusMessage will be different than
;//*                  the message ID you specify here. See Section 4 in the ReadMe.txt file for more info.
;//*
;//*    - Severity may be Informational, Warning, or Error, but not Success.
;//*
;//*    - Facility must be Application.
;//*
;//*    - SymbolicName must begin with <your module name>_XXX_INFO_, <your module name>_XXX_WARNING_,
;//*      or <your module name>_XXX_ERROR_ where XXX is a code identifying the component.
;//*      XXX can be longer than three characters.
;//*
;//*    - The message string itself must be formatted as follows:
;//*
;//*          %11[message text]%12%0
;//*          .
;//*
;//*      where [message text] is the actual text of the message with insertion
;//*      strings.  Some examples:
;//*
;//*          %11Component started.%12%0
;//*          .
;//*
;//*          %11Could not copy %1 to %2.%12%0
;//*
;//*
;//*****************************************************************************

;// ------------------ Custom Messages ------------------

MessageID=40000
Severity=Informational
Facility=Application
SymbolicName=CUSTOM_MESSAGES_CUSTCOMP_INFO_MY_MESSAGE
Language=English
%11Insertion String 1 = "%1" and Insertion String 2 = %2.%12%0
.

MessageID=40001
Severity=Warning
Facility=Application
SymbolicName=CUSTOM_MESSAGES_CUSTCOMP_WARNING_GENERIC
Language=English
%11This message is a Warning.%12%0
.

;// DO NOT REMOVE THIS

;#endif