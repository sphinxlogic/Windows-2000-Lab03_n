Attribute VB_Name = "Routines"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Module Routines (HBInstitution)
'*
'*  This file is provided as part of the COM+ Software Development Kit.
'*
'*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
'*  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'*  OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR PURPOSE.
'*
'* Copyright (C) 1999 Microsoft Corporation, All rights reserved
'**************************************************************************************
'\***********************************************************************************/

Public Sub LogError(ByVal sIName As String)
    
    Dim sMsg As String
    
    sMsg = LogErrorStr(sIName)
    
End Sub

Public Function LogErrorStr(ByVal sIName As String) As String

    Dim sLogErr As String
    
    LogErrorStr = "HBInstitution Error"
    
    If Not Err Is Nothing Then
        sLogErr = "**ERROR THROWN: HBInstitution." & sIName & ":  ErrNum: " & Err.Number & "  Desc: " & Err.Description
    Else
        sLogErr = "**ERROR: HBInstitution." & sIName
    End If
    
    App.LogEvent sLogErr, vbLogEventTypeError
    
    LogErrorStr = sLogErr
    
End Function

Public Sub LogInfo(ByVal sMsg As String)

    Dim sLogInfo As String
    
    sLogInfo = "HBInstitution." & sMsg
    
    App.LogEvent sLogInfo, vbLogEventTypeInformation
    
End Sub

Function GetDSN() As String
    
    On Error GoTo ErrorHandler
        
    If STATIC_DNS = True Then
        GetDSN = "" & CONNECT_CONSTANT & ""
        Exit Function
    End If
    
    Static CONNECT_STRING As String
    
    If CONNECT_STRING <> "" Then
        GetDSN = CONNECT_STRING
        Exit Function
    End If
       
    Dim fso As New FileSystemObject
    Dim fil1 As File
    Dim ts As TextStream
    Dim s As String
    
    s = Environ("HBPATH") & "\DSN.txt"
       
    Set fil1 = fso.GetFile(s)
    
    ' Read the contents of the file.
    Set ts = fil1.OpenAsTextStream(ForReading)
    
    GetDSN = ts.ReadLine & ""
    
    ts.Close
    
    ' If we have a Context the SetComplete
    If COMPLUS_MODE Then GetObjectContext.SetComplete
    
    Exit Function

ErrorHandler:

    If Not fso Is Nothing Then
        Set fso = Nothing
    End If
    
    GetDSN = ""
    
    If COMPLUS_MODE Then GetObjectContext.SetAbort
    
    LogError "GetDSN. HBPATH = " & s
    
End Function



