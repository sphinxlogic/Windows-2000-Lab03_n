Attribute VB_Name = "modConsts"
Public Const GUIDComCatOnPostEarly = "{C028FD86-F943-11d0-85BD-00C04FB960EA}" ' NNTP OnPostEarly GUID
Public Const GUIDComCatOnPost = "{C028FD83-F943-11d0-85BD-00C04FB960EA}" ' NNTP OnPost GUID
Public Const GUIDComCatOnPostFinal = "{C028FD85-F943-11d0-85BD-00C04FB960EA}" ' NNTP OnPostFinal GUID
Public Const GUIDNNTPSourceType = "{C028FD82-F943-11d0-85BD-00C04FB960EA}" ' NNTP SourceType
Public Const szNNTPService = "nntpsvc" ' NNTP Service display Name


Public Const GUIDComCatOnArrival = "{FF3CAA23-00B9-11D2-9DFB-00C04FA322BA}" ' SMTP on Arrival GUID
Public Const GUIDSMTPSourceType = "{4F803D90-FD85-11D0-869A-00C04FD65616}" ' SMTP Source Type
Public Const szSMTPService = "smtpsvc" ' SMTP service display name

Public Const SSOnArrival = "CDO.SS_SMTPOnArrivalSink"
Public Const SSOnPostEarly = "CDO.SS_NNTPOnPostEarlySink"
Public Const SSOnPost = "CDO.SS_NNTPOnPostSink"
Public Const SSOnPostFinal = "CDO.SS_NNTPOnPostFinalSink"

' The GUIDS for the interfaces to implement to handle each event
Public Const ISMTPOnArrivalGUID = "{CD000026-8B95-11D1-82DB-00C04FB1625D}"
Public Const INNTPOnPostEarlyGUID = "{CD000033-8B95-11D1-82DB-00C04FB1625D}"
Public Const INNTPOnPostGUID = "{CD000027-8B95-11D1-82DB-00C04FB1625D}"
Public Const INNTPOnPostFinalGUID = "{CD000028-8B95-11D1-82DB-00C04FB1625D}"

' Default priority for a registration
Public Const DefaultPrio = 24575

Public Enum EventTypes
    OnArrival = 0
    OnPostEarly = 1
    OnPost = 2
    OnPostFinal = 3
End Enum

Public Enum SinkTypes
    ScriptSink = 0
    DLLSink = 1
End Enum


