Attribute VB_Name = "Routines"
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"373680E002CE"
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  Module Routines (HBExchange)
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

Public Sub LogError(ByVal sIName As String, Optional bRaiseError As Boolean = True)
    
    Dim sMsg As String
    
    sMsg = LogErrorStr(sIName, bRaiseError)
    
End Sub

Public Function LogErrorStr(ByVal sIName As String, Optional bRaiseError As Boolean = True) As String

    Dim sLogErr As String
    
    LogErrorStr = "HBExchange Error"
    
    If Not Err Is Nothing Then
        If Err.Number <> 0 Then
            sLogErr = "**ERROR THROWN: HBExchange." & sIName & ":  ErrNum: " & Err.Number & "  Desc: " & Err.Description
            App.LogEvent sLogErr, vbLogEventTypeError
            If bRaiseError Then
                Err.Raise Err.Number, sIName, Err.Description
            End If
            Exit Function
        End If
    End If
        
    sLogErr = "**ERROR: HBExchange." & sIName
    App.LogEvent sLogErr, vbLogEventTypeError
    LogErrorStr = sLogErr

End Function

Public Sub LogInfo(ByVal sMsg As String)

    Dim sLogInfo As String
    
    sLogInfo = "HBExchange." & sMsg
    
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

Public Function ReleaseSQLHandles(ByRef henv As Long, _
                    ByRef hdbc As Long, ByRef hstmt As Long) As Long
    
    Dim rc As Long
    
    ReleaseSQLHandles = FAILED

    If hstmt <> 0 Then
        rc = SQLFreeStmt(hstmt, SQL_CLOSE)
    End If
    If hdbc <> 0 Then
        rc = SQLDisconnect(hdbc)
        rc = SQLFreeConnect(hdbc)
    End If
    If henv <> 0 Then
        rc = SQLFreeEnv(henv)
    End If

    ReleaseSQLHandles = SUCCESS

End Function

Public Function GetSQLHandles(ByVal iDSN As Long, ByRef henv As Long, ByRef hdbc As Long, ByRef hstmt As Long) As Long

    Dim ret As Integer
    Dim rc As Long
    Dim sConnect As String
    
    ' Ignore iDSN for now
    
    GetSQLHandles = FAILED
    
    henv = 0
    hdbc = 0
    hstmt = 0
    
    rc = SQLAllocEnv(henv)
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If

    rc = SQLAllocConnect(henv, hdbc)
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If

    sConnect = CONNECT_DSN

    rc = SQLConnect(hdbc, sConnect, Len(sConnect), DSN_USER_ID, Len(DSN_USER_ID), DSN_PASSWORD, Len(DSN_PASSWORD))
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If

    rc = SQLAllocStmt(hdbc, hstmt)
    If Not (rc = SQL_SUCCESS Or rc = SQL_SUCCESS_WITH_INFO) Then
        GoTo onError
    End If

    ' all went well
    GetSQLHandles = SUCCESS
    Exit Function

onError:
    If hstmt <> 0 Then
        rc = SQLFreeStmt(hstmt, SQL_CLOSE)
    End If
    If hdbc <> 0 Then
        rc = SQLDisconnect(hdbc)
        rc = SQLFreeConnect(hdbc)
    End If
    If henv <> 0 Then
        rc = SQLFreeEnv(henv)
    End If

    GetSQLHandles = RETCODE_FAILURE

End Function

