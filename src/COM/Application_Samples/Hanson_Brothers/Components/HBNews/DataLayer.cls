VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "DataLayer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Class DataLayer (HBNews)
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

Option Explicit

Public Function ExecSql(ByVal strSQL As String, ByVal strProvider As String, ByVal strConnect As String, Optional ByVal bResult As Boolean = True, Optional ByVal bDisconnect As Boolean = False) As Recordset

    On Error GoTo ErrorHandler

    Dim cn As ADODB.Connection
    Dim rs As ADODB.Recordset
    
    Set cn = New ADODB.Connection
    
    With cn
        cn.PROVIDER = strProvider
        cn.ConnectionString = strConnect
        cn.Open
    End With
    
    ' Check the Connection Status
    If (Not cn.State = adStateOpen) Then _
        Err.Raise vbObjectError, "DataLayer::ExecSQL", "Failed to Connect"
    
    Set rs = New ADODB.Recordset
    
    With rs
        
        If bDisconnect Then
            ' Good for Reads
            .CursorLocation = adUseClient
            .CursorType = adOpenStatic
            .LockType = adLockBatchOptimistic
        Else
            ' Good for updates, inserts, deletes
            .CursorLocation = adUseServer
            .CursorType = adOpenKeyset
            .LockType = adLockPessimistic
        End If
        
        Set .ActiveConnection = cn
        .Source = strSQL
        
        .Open , , , , adCmdText
        
    End With
    
    If bDisconnect Then _
        rs.ActiveConnection = Nothing
     
    If bResult Then _
        Set ExecSql = rs
    
       ' If the Connection is Open then Close It
    If bDisconnect And cn.State = adStateOpen Then _
        cn.Close
        
    ' If we have a Context the SetComplete
    GetObjectContext.SetComplete
        
    Exit Function
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If

    ' If we have a Context the Abort
    GetObjectContext.SetAbort
 
    LogError "DataLayer.ExecSql. SQL = " & strSQL
    
End Function

Public Sub Update(ByVal rs As Recordset, ByVal strProvider As String, ByVal strConnect As String)

    On Error GoTo ErrorHandler

    Dim cn As ADODB.Connection
    
    Set cn = New ADODB.Connection
    
    With cn
        cn.PROVIDER = strProvider
        cn.ConnectionString = strConnect
        cn.Open
    End With
    
    ' Check the Connection Status
    If (Not cn.State = adStateOpen) Then _
        Err.Raise vbObjectError, "DataLayer::Update", "Failed to Connect"
        
    With rs
        Set .ActiveConnection = cn
        .UpdateBatch
    End With
    
    rs.ActiveConnection = Nothing
    
     ' If the Connection is Open then Close It
    If cn.State = adStateOpen Then _
        cn.Close
        
    ' If we have a Context the SetComplete
    GetObjectContext.SetComplete

    Exit Sub
    
ErrorHandler:
    
    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    If Not cn Is Nothing Then
        Set cn = Nothing
    End If
    
    ' If we have a Context the Abort
    GetObjectContext.SetAbort
    
    LogError "DataLayer.Update"

End Sub




