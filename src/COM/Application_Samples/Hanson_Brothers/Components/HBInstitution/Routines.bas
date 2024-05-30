Attribute VB_Name = "Routines"
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"37367D22033C"
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
        If Err.Number <> 0 Then
            sLogErr = "**ERROR THROWN: HBInstitution." & sIName & ":  ErrNum: " & Err.Number & "  Desc: " & Err.Description
            App.LogEvent sLogErr, vbLogEventTypeError
            Err.Raise Err.Number, sIName, Err.Description
            Exit Function
        End If
    End If
        
    sLogErr = "**ERROR: HBInstitution." & sIName
    App.LogEvent sLogErr, vbLogEventTypeError
    LogErrorStr = sLogErr
    
End Function

Public Sub LogInfo(ByVal sMsg As String)

    Dim sLogInfo As String
    
    sLogInfo = "HBInstitution." & sMsg
    
    App.LogEvent sLogInfo, vbLogEventTypeInformation
    
End Sub

Function GetDSN() As String
    
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
    
    On Error GoTo ErrorHandler
    
    s = Environ("HBPATH") & "\DSN.txt"
       
    Set fil1 = fso.GetFile(s)
    
    ' Read the contents of the file.
    Set ts = fil1.OpenAsTextStream(ForReading)
    
    GetDSN = ts.ReadLine & ""
    
    ts.Close
   
Done:
    Set fso = Nothing
    
    Exit Function

ErrorHandler:
  
    LogError ("GetDSN")
    
    GetDSN = ""
    
    GoTo Done
    
End Function

Public Function ValidateField(ByRef oRecordSet As Recordset, strFieldVal As String) As String
    If oRecordSet(strFieldVal) <> "" Then
        ValidateField = oRecordSet(strFieldVal)
    Else
        ValidateField = ""
    End If
End Function

Public Function ValidateFieldIndex(ByRef oRecordSet As Recordset, ByVal strFieldIndex As Long) As String
    If oRecordSet.Fields(strFieldIndex) <> "" Then
        ValidateFieldIndex = oRecordSet.Fields(strFieldIndex)
    Else
        ValidateFieldIndex = ""
    End If
End Function
