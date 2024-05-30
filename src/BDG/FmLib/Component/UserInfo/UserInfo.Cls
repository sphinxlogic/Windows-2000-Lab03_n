VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "UserInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Property Get Logon()
Attribute Logon.VB_Description = "Get user logon name."
Attribute Logon.VB_UserMemId = 0
    Dim sbuf As String, cnt As Long, ret As Long
    
    cnt = UNLEN
    sbuf = String$(cnt + 1, 0)
    ret = GetUserName(sbuf, cnt)
    
    If ret > 0 Then
        Logon = Left$(sbuf, cnt - 1)
    Else
        Err.Raise GetLastError, "UserInfo.Logon", "Failed to get user logon name."
    End If
End Property

Public Property Get ComputerName()
    Dim sbuf As String, cnt As Long, ret As Long
    
    cnt = MAX_COMPUTERNAME_LENGTH
    sbuf = String$(cnt + 1, 0)
    ret = GetComputerName(sbuf, cnt)
    
    If ret > 0 Then
        ComputerName = Left$(sbuf, cnt)
    Else
        Err.Raise GetLastError, "UserInfo.ComputerName", "Failed to get computer name."
    End If
End Property

