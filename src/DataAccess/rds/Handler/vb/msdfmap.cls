'-----------------------------------------------------------------------------
'
' File:         msdfmap.cls
'
' Copyright:    Copyright (c) 1998-1999 Microsoft Corporation
'
' Contents:
'
' Comments:
'
'-----------------------------------------------------------------------------
VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Handler"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Implements MSDFHDL.IDataFactoryHandler

Private evh As New Events
Private dbg As Integer

Private Sub Execute(ByVal CommandText As String)
    Dim origCommand As String
    
    origCommand = CommandText
    Call ModifySqlViaIni(CommandText)
    If dbg Then MsgBox "before: " + origCommand + Chr$(10) + "after: " + CommandText, , "CommandText"

    evh.rs.CursorLocation = adUseClient
    Call evh.rs.Open(CommandText, evh.conn, adOpenUnspecified, adLockBatchOptimistic, adCmdUnspecified)
    If dbg Then MsgBox str$(evh.rs.State), , "State"
End Sub

Private Function Connect(ByVal ConnectString As String) As Long
    Dim origConnect As String
    Dim access As Long
    
    origConnect = ConnectString
    Call ModifyConnectViaIni(ConnectString)
    If dbg Then MsgBox "before: " + origConnect + Chr$(10) + "after: " + ConnectString, , "ConnectString"
    access = GetAccess(origConnect, GetUserName())
    If access = 2 Or access = 3 Then
        If access = 2 Then
            evh.conn.Mode = adModeRead
        End If
        Call evh.conn.Open(ConnectString)
    End If
    If dbg Then MsgBox str$(access), , "access"
    Connect = access
End Function

Private Sub Class_Initialize()
    dbg = 1
    If dbg Then MsgBox "Initialize", , "MSDFMAP_VB"
End Sub

Private Sub Class_Terminate()
    Set evh = Nothing
End Sub

Private Function IDataFactoryHandler_GetRecordset(ByVal conn As String, ByVal args As String, ByVal query As String) As ADODB.Recordset
    Dim access As Long

    'Initialize
    Call SetIniFile(args)
    
    'Connect to database and execute query to create recordset
    access = Connect(conn)
    If access >= 2 Then
        Call Execute(query)
    Else
        Call Err.Raise(&H80070005)  'E_ACCESSDENIED
    End If

    Set IDataFactoryHandler_GetRecordset = evh.rs
End Function

Private Function IDataFactoryHandler_OpenConnection(ByVal conn As String, ByVal args As String, ByVal lFlags As Long, ByRef pQuery As String) As ADODB.Connection
    'lFlags: 1=Synchronize, 2=Execute
    'NOTE: When this MDAC 2.1 method is called evh.rs is not opened or used.
    Dim access As Long
    Dim newCommand As String

    'Initialize
    Call SetIniFile(args)

    'Connect to database
    access = Connect(conn)
    If (lFlags = 2 And access >= 2) Or (lFlags = 1 And access >= 3) Then
        'Map the query string
        newCommand = pQuery
        Call ModifySqlViaIni(newCommand)
        If dbg Then MsgBox "before: " + pQuery + Chr$(10) + "after: " + newCommand, , "CommandText"
        pQuery = newCommand
    Else
        Call Err.Raise(&H80070005)  'E_ACCESSDENIED
    End If

    Set IDataFactoryHandler_OpenConnection = evh.conn
End Function

Private Sub IDataFactoryHandler_Reconnect(ByVal conn As String, ByVal args As String, ByVal pRS As ADODB.Recordset)
    Dim access As Long
    
    'Initialize
    Call SetIniFile(args)
    
    'Connect to database and attach recordset
    access = Connect(conn)
    If access >= 3 Then
        Set evh.rs = pRS
        Set evh.rs.ActiveConnection = evh.conn
    Else
        Call Err.Raise(&H80070005)  'E_ACCESSDENIED
    End If
End Sub

