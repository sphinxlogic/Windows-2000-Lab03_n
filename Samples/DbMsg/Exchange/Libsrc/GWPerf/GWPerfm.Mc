;// --gwperfm.mc----------------------------------------------------------------
;//
;//  This file contains the messages displayed by the gwperf DLL.
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
SymbolicName=GWPERF_ERROR
Language=English
Performance monitoring DLL error:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_OPEN_ERROR
Language=English
Performance monitoring DLL open failed due to the following error:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_OPEN_ALREADY_OPEN
Language=English
Attempt to open performance monitoring DLL multiple times.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_OPEN_NO_LINKAGE
Language=English
Linkage\Export value does not exist or is empty.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_COLLECT_NOT_OPEN
Language=English
Attempt to call performance monitoring DLL collect routine without first calling open routine.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_COLLECT_ERROR
Language=English
Performance monitoring DLL data collection failed due to the following error:%n%1
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_COLLECT_TOO_MANY_FAILURES
Language=English
Too many failures in performance monitoring DLL data collection.  Data collection disabled.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_CLOSE_NOT_OPEN
Language=English
Attempt to call performance monitoring DLL close routine without first calling open routine.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_VERSION_MISMATCH
Language=English
Version mismatch between performance data from gateway instance %1 and the performance monitoring DLL.
.
MessageId=
Severity=Error
Facility=Application
SymbolicName=GWPERF_MUTEX_TIMEOUT
Language=English
Performance DLL timed out waiting for gateway instance %1 to release the communications mutex.  The gateway may not be running properly.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=GWPERF_NO_DEFAULT_COUNTERS
Language=English
Gateway instance %1 will not be visible in Performance Monitor until it has been run once.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=GWPERF_OPEN_DEFAULT_COUNTERS
Language=English
Cannot open registry key HKEY_LOCAL_MACHINE:%1 to read default counter data due to the following error:%n%2%nThe counters for this instance may not be visible.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=GWPERF_READ_DEFAULT_COUNTERS
Language=English
Cannot read default counter data from registry value HKEY_LOCAL_MACHINE:%1\ObjectDefaultPerformanceData due to the following error:%n%2%nThe counters for this instance may not be visible.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=GWPERF_DEFAULT_COUNTERS_WRONG_TYPE
Language=English
Cannot read default counter data from registry value HKEY_LOCAL_MACHINE:%1\ObjectDefaultPerformanceData because the registry value is not of type REG_BINARY.  The counters for this instance may not be visible.
.
MessageId=
Severity=Warning
Facility=Application
SymbolicName=GWPERF_CLOSE_DEFAULT_COUNTERS
Language=English
Cannot close the registry key HKEY_LOCAL_MACHINE:%1 due to the following error:%n%2
.
