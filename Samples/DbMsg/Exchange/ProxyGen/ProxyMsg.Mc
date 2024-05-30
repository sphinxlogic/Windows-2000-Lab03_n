;/*++ BUILD Version: 0001    // Increment this if a change has global effects
;
;Copyright (c) 1986-1996.  Microsoft Corporation.  All Rights Reserved.
;
;Module Name:
;
;    proxymsg.mc
;
;Abstract:
;
;    This file contains the message definitions for the proxy DLL.
;
;--*/
;


SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
               Mask=0x3:STATUS_SEVERITY_MASK
              )

;// -------------------     messages for prxsmtp   ---------------------

MessageId = 0x0
Severity = Error
SymbolicName = iesNoSiteProxy
Language = English
Email Address Generation Failure: No site address.
.

MessageId =
Severity = Error
SymbolicName = iesBadSiteProxy
Language = English
Email Address Generation Failure: Bad site address '%1'.
.

MessageId =
Severity = Error
SymbolicName = iesInvalidFormatString
Language = English
Email Address Generation Failure: The format string '%1' portion of the site address is invalid.
.

MessageId =
Severity = Warning
SymbolicName = iesUnableToCreateUniqueProxy
Language = English
Email Address Generation Failure: Unable to create unique email address for '%1'.
.

MessageId =
Severity = Error
SymbolicName = iesProxyToBig
Language = English
Email Address Generation Failure: Email address for '%1' would be too large.
.

MessageId =
Severity = Error
SymbolicName = iesProxyInternalFailure
Language = English
Email Address Generation Failure: Internal Error
.

MessageId =
Severity = Error
SymbolicName = iesInvalidCharacter
Language = English
Email Address Generation Failure: The email address specified (%1) contains illegal characters
.
