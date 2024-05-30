Attribute VB_Name = "Routines"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Module Routines (HBNotify)
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
    
    LogErrorStr = "HBNotify Error"
    
    If Not Err Is Nothing Then
        If Err.Number <> 0 Then
            sLogErr = "**ERROR THROWN: HBNotify." & sIName & ":  ErrNum: " & Err.Number & "  Desc: " & Err.Description
            App.LogEvent sLogErr, vbLogEventTypeError
            
            ' If Exception, don't throw error back to caller (HBExchange - since it's a fire-and-forget)
            ' Ideally, notify HBInstitution of Error.
            ' Err.Raise Err.Number, sIName, Err.Description
            
            Exit Function
        End If
    End If
        
    sLogErr = "**ERROR: HBNotify." & sIName
    App.LogEvent sLogErr, vbLogEventTypeError
    LogErrorStr = sLogErr
    
End Function

Public Sub LogInfo(ByVal sMsg As String)

    Dim sLogInfo As String
    
    sLogInfo = "HBNotify." & sMsg
    
    App.LogEvent sLogInfo, vbLogEventTypeInformation
    
End Sub
