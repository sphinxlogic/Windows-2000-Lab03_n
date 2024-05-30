VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Logger"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'
' This file is provided as part of the Microsoft Transaction Server Samples
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
' WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
' INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
' OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
' PURPOSE.
'
' Copyright (C) 1997 Microsoft Corporation, All rights reserved

Option Explicit

Const APP_ERROR_LOW As Long = vbObjectError + 7000
Const APP_ERROR_HIGH As Long = vbObjectError + 7999

Const modName = "Logger"
Const INVALID_PASSWORD As Long = 2
Const INVOICE_NOT_FOUND As Long = 3
Const CUSTOMER_NOT_FOUND As Long = 4
Const NO_DATA As Long = 5
Const TRY_AGAIN As Long = 6
Const SQL_ERROR As Long = 7
Const CUSTOMER_WITH_ADS As Long = 8
Public Enum LogRetCodes
  elSuccess = -1
  elFail = 0
  elOther = 1
End Enum

Public Enum LogNTEvtLog
  elLogyes = -1
  elLogMayBe = 0
  elLogno = 1
End Enum

Public Enum LogDispToUser
  elShowUserYes = -1
  elShowUserNo = 0
End Enum






Public Function Log(plngErr As Long, Optional pstrDesc As String, _
  Optional pstrApp As String, Optional pstrSource As String, _
  Optional pstrProc As String, Optional pstrMod As String, _
  Optional eLogToEvt As LogNTEvtLog, _
  Optional eShowUser As LogDispToUser) _
  As LogRetCodes

  On Error GoTo Log_Err
  Const procName As String = "Log"
  
  
  ' Check for missing/unintialized parameters
  If Len(pstrApp) = 0 Then
    pstrApp = "App Unknown"
  End If
  If Len(pstrSource) = 0 Then
    pstrSource = "Source Unknown"
  End If
  If Len(pstrProc) = 0 Then
    pstrProc = "Procedure Unknown"
  End If
  If Len(pstrMod) = 0 Then
    pstrMod = "Module Unknown"
  End If
  
  ' Event Log Codes
  Dim strFriendlyMsg As String
  Dim strSource As String
  Dim strMessage As String
  Dim lngEvtTyp As Long
  Dim lngEvtCat As Long
  Dim lngEvtId As Long
  
  ' Ini (need to update)
  lngEvtTyp = 1
  lngEvtCat = 1
  lngEvtId = 1
  
  Select Case plngErr
    'Case Is > vbObjectError
    '  strFriendlyMsg = pstrDesc
    '  eLogToEvt = elLogNo
    Case 3021
      ' ADO Error
      ' Either BOF or EOF is True,
      '   or the current record has been deleted;
      '   the operation requested by the
      '   application requires a current record.
      If InStr(1, pstrSource, "Validate") > 0 Then
        strFriendlyMsg = LoadResString(INVALID_PASSWORD)
        eLogToEvt = elLogyes
      ElseIf InStr(1, pstrSource, "Invoice") > 0 Then
        strFriendlyMsg = LoadResString(INVOICE_NOT_FOUND)
      ElseIf InStr(1, pstrSource, "Customer") > 0 Then
        strFriendlyMsg = LoadResString(CUSTOMER_NOT_FOUND)
      Else
        strFriendlyMsg = LoadResString(NO_DATA)
      End If
      strFriendlyMsg = LoadResString(TRY_AGAIN)
      
    Case 13
      If InStr(1, pstrSource, "Validate") > 0 Then
        strFriendlyMsg = LoadResString(INVALID_PASSWORD)
        eLogToEvt = elLogyes
      ElseIf InStr(1, pstrSource, "Invoice") > 0 Then
        strFriendlyMsg = LoadResString(INVOICE_NOT_FOUND)
      ElseIf InStr(1, pstrSource, "Customer") > 0 Then
        strFriendlyMsg = LoadResString(CUSTOMER_NOT_FOUND)
      Else
        strFriendlyMsg = LoadResString(NO_DATA)
      End If
     Case -214721790
        strFriendlyMsg = LoadResString(CUSTOMER_WITH_ADS)
     Case Else
        If InStr(1, pstrSource, "Microsoft OLE DB Provider") > 0 Then
            strFriendlyMsg = LoadResString(SQL_ERROR)
        Else
            strFriendlyMsg = LoadResString(TRY_AGAIN)
        End If
  End Select
 
  strSource = pstrApp
      strMessage = "An unexpected error occured." & vbCrLf & _
        "Calling application: " & pstrApp & "." & vbCrLf & _
        "The call tree was as follows: " & pstrSource & "." & vbCrLf & _
        "The executing procedure was " & pstrProc & _
        " in " & pstrMod & "." & vbCrLf & _
        "The Reported Error Code was '" & plngErr & "'" & _
        "; defined as '" & pstrDesc & "'"
      If Right(strMessage, 3) = ".'." Then
        strMessage = Left$(strMessage, Len(strMessage) - 1)
      End If

  If eLogToEvt = elLogyes Then
    ' Now log to the client's event log
    ' Uses 'MTS Tools.dll' to log to NT Event Log
    ' Note: if we're running on 95 this will fail
    ' Check OS?
    Dim objevtlog As New UTIL_EVENTVIEWERLib.EventViewer
    If Len(strMessage) > 4090 Then
      strMessage = vbCrLf & Left$(strMessage, 4090)
    Else
      strMessage = vbCrLf & strMessage
    End If
    If Len(strSource) = 0 Then
      strSource = App.Title
    End If
    objevtlog.AddLog strSource, strMessage, lngEvtTyp, lngEvtCat, lngEvtId
  End If
  
  If eShowUser = elShowUserYes Then
      MsgBox strFriendlyMsg, vbExclamation, "Classifieds"
  End If
  
  Log = elSuccess
  
Log_Exit:
  On Error Resume Next
    Set objevtlog = Nothing
  Exit Function
  
Log_Err:
  Log = elFail
  Exit Function
  
End Function


