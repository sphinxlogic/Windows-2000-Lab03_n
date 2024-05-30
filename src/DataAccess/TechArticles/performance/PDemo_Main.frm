VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6540
   ClientLeft      =   135
   ClientTop       =   360
   ClientWidth     =   10050
   LinkTopic       =   "Form1"
   ScaleHeight     =   6540
   ScaleWidth      =   10050
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtDiff 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   500
      Left            =   8400
      TabIndex        =   9
      Top             =   4560
      Width           =   1212
   End
   Begin VB.TextBox txtNewTime 
      Height          =   500
      Left            =   8400
      TabIndex        =   8
      Top             =   3600
      Width           =   1212
   End
   Begin VB.TextBox txtOldTime 
      Height          =   500
      Left            =   8400
      TabIndex        =   7
      Top             =   2880
      Width           =   1212
   End
   Begin VB.CommandButton btnExecute 
      Caption         =   "Execute"
      Height          =   500
      Left            =   8520
      TabIndex        =   6
      Top             =   960
      Width           =   1212
   End
   Begin VB.TextBox txtID 
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   7560
      TabIndex        =   5
      Text            =   "Text1"
      Top             =   240
      Width           =   600
   End
   Begin VB.TextBox txtTestName 
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   500
      Left            =   120
      TabIndex        =   4
      Text            =   "Text1"
      Top             =   240
      Width           =   7212
   End
   Begin VB.CommandButton btnNext 
      Caption         =   "->"
      Height          =   500
      Left            =   9360
      TabIndex        =   3
      Top             =   240
      Width           =   500
   End
   Begin VB.CommandButton btnPrev 
      Caption         =   "<-"
      Height          =   500
      Left            =   8520
      TabIndex        =   2
      Top             =   240
      Width           =   500
   End
   Begin VB.TextBox txtNew 
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2652
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Text            =   "PDemo_Main.frx":0000
      Top             =   3550
      Width           =   8172
   End
   Begin VB.TextBox txtOld 
      BeginProperty Font 
         Name            =   "Lucida Console"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2652
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Text            =   "PDemo_Main.frx":0006
      Top             =   800
      Width           =   8172
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim rsCodeFile As New ADODB.Recordset
Dim cn_Native As New ADODB.Connection
Dim cn_ODBC_Prov As New ADODB.Connection
Dim lStartTime As Long

' ****************************************
' Change DB Constants here.
' ****************************************
' Point to the XML file containing the code samples.
Const XML_CODE_FILE = "c:\mssdk\Samples\DataAccess\TechArticles\ADO\Performance\Code.xml"

' Change to point to your SQL Server.
Const SQL_SERVER = "MyServer"


Private Sub btnExecute_Click()
 
  DoEvents
  Form1.MousePointer = vbHourglass
  If rsCodeFile!dbkey = 1 Then
      CmdTypeTestSetup
      CmdTypeTableTestOld
      CmdTypeTestSetup
      CmdTypeTableTestNew
  
  ElseIf rsCodeFile!dbkey = 3 Then
      CmdTypeSprocTestOld
      CmdTypeSprocTestNew
  
  ElseIf rsCodeFile!dbkey = 4 Then
      CmdExecNoRecordsTestOld
      CmdExecNoRecordsTestNew
     
  ElseIf rsCodeFile!dbkey = 6 Then
      ParamRefreshVsDefineTestSetup
      ParamRefreshVsDefineTestOld
      ParamRefreshVsDefineTestSetup
      ParamRefreshVsDefineTestNew
  
  ElseIf rsCodeFile!dbkey = 8 Then
      RecordsetOpenSvrVsClientTestSetup
      RecordsetOpenSvrVsClientTestClient
      RecordsetOpenSvrVsClientTestSetup
      RecordsetOpenSvrVsClientTestServer
  
  ElseIf rsCodeFile!dbkey = 10 Then
      RecordsetUpdOptSvrVsClientTestSetup
      RecordsetUpdOptSvrVsClientTestServer
      RecordsetUpdOptSvrVsClientTestSetup
      RecordsetUpdOptSvrVsClientTestClient
  
  ElseIf rsCodeFile!dbkey = 11 Then
      RecordsetUpdBatchOptSvrVsClientTestSetup
      RecordsetUpdBatchOptSvrVsClientTestServer
      RecordsetUpdBatchOptSvrVsClientTestSetup
      RecordsetUpdBatchOptSvrVsClientTestClient
       
  ElseIf rsCodeFile!dbkey = 15 Then
      RecordsetColRefvsLookupTestSetup
      RecordsetColRefvsLookupTestLookup
      RecordsetColRefvsLookupTestSetup
      RecordsetColRefvsLookupTestReference
  
  ElseIf rsCodeFile!dbkey = 16 Then
      RecordsetNativeVsODBCProvTestSetup
      RecordsetNativeVsODBCProvTestODBCProv
      RecordsetNativeVsODBCProvTestSetup
      RecordsetNativeVsODBCProvTestNative
  
  End If
    
  If (txtNewTime.Text <> 0) Then
      txtDiff.Text = Round(((Val(txtOldTime.Text) / Val(txtNewTime.Text)) - 1) * 100, 2)
  Else
      txtDiff.Text = 0
  End If
  
  
  Form1.MousePointer = vbDefault
  DoEvents

End Sub

Private Sub btnNext_Click()
  txtOldTime.Text = ""
  txtNewTime.Text = ""
  txtDiff.Text = ""

  If Not rsCodeFile.EOF Then
    rsCodeFile.MoveNext
      If Not rsCodeFile.EOF Then
        UpdFormFields
      End If
  End If
    
End Sub

Private Sub btnPrev_Click()
  txtOldTime.Text = ""
  txtNewTime.Text = ""
  txtDiff.Text = ""
  
  If Not rsCodeFile.BOF Then
    rsCodeFile.MovePrevious
    
    If Not rsCodeFile.BOF Then
      UpdFormFields
    End If
  End If
    
End Sub

Private Sub Form_Load()
  ' Connection to Code file containing code to display.
  rsCodeFile.Open XML_CODE_FILE, , adOpenDynamic, adLockBatchOptimistic, adCmdFile
  
  ' Connection to Native SQLOLEDB data source.
  cn_Native.Open ("provider=SQLOLEDB;server=" + SQL_SERVER), "sa", ""
  cn_Native.DefaultDatabase = "NorthWind"

  ' Connection to the ODBC provider
  cn_ODBC_Prov.Open ("driver={sql server};server=" + SQL_SERVER), "sa", ""
  cn_ODBC_Prov.DefaultDatabase = "NorthWind"
  
  
  ' Sort the RS
  rsCodeFile.Sort = "dbkey ASC"
  
  UpdFormFields
  
    
End Sub


Private Sub Form_Resize()
  ' When the form is resized, resize the controlls accordingly.
  txtTestName.Width = (Form1.Width - 2160 - 700)
  txtID.Left = (txtTestName.Width + 220)
  
  ' Origional Code
  txtOld.Width = (Form1.Width - 2160)
  txtOld.Height = ((Form1.Height - 1350) / 2)
  
  ' New Code
  txtNew.Width = (Form1.Width - 2160)
  txtNew.Top = (txtOld.Top + txtOld.Height + 100)
  txtNew.Height = ((Form1.Height - 1350) / 2)
  
  ' Buttons
  btnPrev.Left = (txtNew.Width + 320)
  btnNext.Left = (btnPrev.Left + 700)
  btnExecute.Left = (txtNew.Width + 320)
  
  ' Result text boxes
  txtOldTime.Left = (txtOld.Left + txtOld.Width + 100)
  txtOldTime.Top = (txtOld.Top + txtOld.Height - 500)
  
  txtNewTime.Left = (txtNew.Left + txtNew.Width + 100)
  txtNewTime.Top = (txtNew.Top)
  ' % Diff
  txtDiff.Left = (txtNew.Left + txtNew.Width + 100)
  txtDiff.Top = (txtNew.Top + 700)

End Sub

Private Sub Form_Unload(Cancel As Integer)
    
  If rsCodeFile.State = adStateOpen Then
    rsCodeFile.Close
    Set rsCodeFile = Nothing
  End If

End Sub

Sub UpdFormFields()
  ' Set the data fileds to the objects on the form.
  ' Trim must be used as values are saved in col width form in XML
  txtID.Text = Trim(rsCodeFile("dbKey"))
  txtTestName.Text = Trim(rsCodeFile("Description"))
  txtOld.Text = Trim(rsCodeFile("leftcode"))
  txtNew.Text = Trim(rsCodeFile("rightcode"))
End Sub
'CommandType Test
Sub CmdTypeTestSetup()

    On Error Resume Next
    cn_Native.Execute "drop table testtable"
    cn_Native.Execute "drop procedure inserttest"
    On Error GoTo 0
    cn_Native.Execute "create table testtable (dbkey integer identity primary key, field1 varchar(10))"
    cn_Native.Execute "create procedure inserttest As insert into testtable (field1) values ('string1')"

End Sub

Sub CmdTypeTableTestOld()

    Dim cmd As New ADODB.Command
    Dim rst As ADODB.Recordset
    Dim ii As Integer
    
    cmd.CommandText = "testtable"
        
    lStartTime = Timer
    
        For ii = 1 To 500
            Set cmd.ActiveConnection = Nothing
            Set cmd.ActiveConnection = cn_Native
            cmd.CommandText = "testtable"
            cmd.Execute
        Next

    txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

Sub CmdTypeTableTestNew()

    Dim cmd As New ADODB.Command
    Dim rst As ADODB.Recordset
    Dim ii As Integer
       
    lStartTime = Timer
    
        For ii = 1 To 500
            Set cmd.ActiveConnection = Nothing
            Set cmd.ActiveConnection = cn_Native
            cmd.CommandText = "testtable"
            cmd.CommandType = adCmdTable
            cmd.Execute
        Next

    txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

Sub CmdTypeSprocTestOld()

    Dim cmd As New ADODB.Command
    Dim rst As ADODB.Recordset
    Dim ii As Integer
    
    Set cmd.ActiveConnection = cn_Native
    cmd.CommandText = "inserttest"
        
    lStartTime = Timer
    
        For ii = 1 To 500
            cmd.Execute
        Next

    txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

Sub CmdTypeSprocTestNew()

    Dim cmd As New ADODB.Command
    Dim rst As ADODB.Recordset
    Dim ii As Integer
    
    Set cmd.ActiveConnection = cn_Native
    
    cmd.CommandText = "inserttest"
    cmd.CommandType = adCmdStoredProc
    
    lStartTime = Timer
    
        For ii = 1 To 500
            cmd.Execute
        Next

    txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

Sub CmdExecNoRecordsTestOld()

    Dim cmd As New ADODB.Command
    Dim rst As ADODB.Recordset
    Dim ii As Integer
    
    Set cmd.ActiveConnection = cn_Native
    cmd.CommandText = "update testtable set field1 = 'newstring' where dbkey = 1"
    cmd.CommandType = adCmdText
        
    lStartTime = Timer
    
        For ii = 1 To 500
            cmd.Execute
        Next

    txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

Sub CmdExecNoRecordsTestNew()

    Dim cmd As New ADODB.Command
    Dim rst As ADODB.Recordset
    Dim ii As Integer
    
    Set cmd.ActiveConnection = cn_Native
    
    cmd.CommandText = "update testtable set field1 = 'newstring' where dbkey = 1"
    cmd.CommandType = adCmdText
    
    lStartTime = Timer
    
        For ii = 1 To 500
            cmd.Execute , , adExecuteNoRecords
        Next

    txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

'Parameter Test
Sub ParamRefreshVsDefineTestSetup()

    On Error Resume Next
    cn_Native.Execute "drop table testtable"
    On Error GoTo 0
    cn_Native.Execute "create table testtable (dbkey integer identity primary key, field1 varchar(10), field2 datetime, field3 varchar(100))"
    cn_Native.Execute "insert into testtable (field1, field2, field3) values ('string1', '19940701 12:30.00 AM', 'longer string')"

End Sub

Sub ParamRefreshVsDefineTestOld()
  Dim ii As Integer
  Dim cmd As ADODB.Command
  lStartTime = Timer
  
  For ii = 1 To 500
    Set cmd = New ADODB.Command
    cmd.CommandType = adCmdText
    cmd.CommandText = "update testtable set field1 = ?, field2 = ?, field3 = ? where dbkey = ?"
    Set cmd.ActiveConnection = cn_Native
    cmd.Parameters.Refresh
    cmd.Execute , Array("String Old" & ii, Time, "longer string", 1)
  Next

  txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
  
End Sub

Sub ParamRefreshVsDefineTestNew()
  Dim ii As Integer
  Dim cmd As ADODB.Command
  lStartTime = Timer
    
  For ii = 1 To 500
    Set cmd = New ADODB.Command
    cmd.CommandType = adCmdText
    cmd.CommandText = "update testtable set field1 = ?, field2 = ?, field3 = ? where dbkey = ?"
    Set cmd.ActiveConnection = cn_Native
    cmd.Parameters.Append cmd.CreateParameter("field1", adVarChar, adParamInput, 10)
    cmd.Parameters.Append cmd.CreateParameter("field2", adDBTimeStamp, adParamInput, 16)
    cmd.Parameters.Append cmd.CreateParameter("field3", adVarChar, adParamInput, 100)
    cmd.Parameters.Append cmd.CreateParameter("dbkey", adInteger, adParamInput, 4)
    cmd.Execute , Array("String New" & ii, Time, "longer string", 1)
  Next

  txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
    
End Sub
'Recordset Instantiation - server vs Client
Sub RecordsetOpenSvrVsClientTestSetup()

    Dim cn As ADODB.Connection
    Dim rst As ADODB.Recordset
    
    'Make sure the table is cached once so as not to incur a penalty for the first run test
    Set cn = cn_Native
    Set rst = cn_Native.Execute("select * from orders")
    Set rst = cn.Execute("select * from Orders")
    
End Sub

Sub RecordsetOpenSvrVsClientTestClient()

    Dim rst As New ADODB.Recordset
    
    Set rst.ActiveConnection = cn_Native
    rst.Source = "select * from Customers, Orders"
    rst.CursorLocation = adUseClient
    rst.CacheSize = 50
    
    lStartTime = Timer
    
    rst.Open , , adOpenStatic, adLockReadOnly
    rst.Close

    txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

Sub RecordsetOpenSvrVsClientTestServer()

    Dim rst As New ADODB.Recordset
    
    Set rst.ActiveConnection = cn_Native
    rst.Source = "select * from Customers, Orders"
    rst.CursorLocation = adUseServer
    rst.CacheSize = 50
        
    lStartTime = Timer
    
    rst.Open , , adOpenKeyset, adLockReadOnly
    rst.Close

    txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    DoEvents
    
End Sub

'Recordset Update optimistic - server vs Client
Sub RecordsetUpdOptSvrVsClientTestSetup()
  Dim cn As ADODB.Connection
  Dim rst As ADODB.Recordset
  Dim ii As Integer
  
  On Error Resume Next
  cn_Native.Execute "drop table testtable"
  On Error GoTo 0
  cn_Native.Execute "create table testtable (dbkey integer identity primary key, field1 varchar(10), field2 datetime, field3 varchar(100))"
  
  For ii = 1 To 500
    cn_Native.Execute "insert into testtable (field1, field2, field3) values ('string1', '19940701 12:30.00 AM', 'longer string')"
  Next
    
End Sub

Sub RecordsetUpdOptSvrVsClientTestClient()
  Dim rst As New ADODB.Recordset
  Dim ii As Integer
  
  Set rst.ActiveConnection = cn_Native
  rst.Source = "select * from testtable"
  rst.CursorLocation = adUseClient
  rst.CacheSize = 50
  
  rst.Open , , adOpenStatic, adLockOptimistic
  lStartTime = Timer
  
  While rst.EOF <> True
    rst.Update Array("field1"), Array("newstring")
    rst.MoveNext
  Wend
  rst.Close
  
  txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
  
End Sub

Sub RecordsetUpdOptSvrVsClientTestServer()

    Dim rst As New ADODB.Recordset
    
    Set rst.ActiveConnection = cn_Native
    rst.Source = "select * from testtable"
    rst.CursorLocation = adUseServer
    rst.CacheSize = 50
    
    rst.Open , , adOpenKeyset, adLockOptimistic
    lStartTime = Timer
    
    While rst.EOF <> True
        rst.Update Array("field1"), Array("newstring")
        rst.MoveNext
    Wend
    rst.Close

    txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
    DoEvents
    
End Sub

'Recordset Update batch optimistic - server vs Client
Sub RecordsetUpdBatchOptSvrVsClientTestSetup()
  Dim cn As ADODB.Connection
  Dim rst As ADODB.Recordset
  Dim ii As Integer
  
  On Error Resume Next
  cn_Native.Execute "drop table testtable"
  On Error GoTo 0
  cn_Native.Execute "create table testtable (dbkey integer identity primary key, field1 varchar(10), field2 datetime, field3 varchar(100))"
  
  For ii = 1 To 500
    cn_Native.Execute "insert into testtable (field1, field2, field3) values ('string1', '19940701 12:30.00 AM', 'longer string')"
  Next
    
End Sub

Sub RecordsetUpdBatchOptSvrVsClientTestClient()
   Dim rst As New ADODB.Recordset
   Dim ii As Integer
   
   Set rst.ActiveConnection = cn_Native
   rst.Source = "select * from testtable"
   rst.CursorLocation = adUseClient
   rst.CacheSize = 50
   
   rst.Open , , adOpenStatic, adLockBatchOptimistic
   lStartTime = Timer
  
   While rst.EOF <> True
       rst.Update Array("field1"), Array("newstring")
       rst.MoveNext
   Wend
   rst.UpdateBatch
   rst.Close

   txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
   DoEvents
   
End Sub

Sub RecordsetUpdBatchOptSvrVsClientTestServer()
    Dim rst As New ADODB.Recordset
    
  Set rst.ActiveConnection = cn_Native
  rst.Source = "select * from testtable"
  rst.CursorLocation = adUseServer
  rst.CacheSize = 50
  
  rst.Open , , adOpenKeyset, adLockBatchOptimistic
  lStartTime = Timer
    
  While rst.EOF <> True
    rst.Update Array("field1"), Array("newstring")
    rst.MoveNext
  Wend
  rst.UpdateBatch
  rst.Close
  
  txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
    
End Sub
'Recordset: Column referencing
Sub RecordsetColRefvsLookupTestSetup()
  Dim cn As ADODB.Connection
  Dim rst As ADODB.Recordset
  Dim ii As Integer
  
  On Error Resume Next
  cn_Native.Execute "drop table testtable"
  On Error GoTo 0
  cn_Native.Execute "create table testtable (dbkey integer identity primary key, field1 varchar(10), field2 datetime, field3 varchar(100))"
  
  For ii = 1 To 5000
    cn_Native.Execute "insert into testtable (field1, field2, field3) values ('string1', '19940701 12:30.00 AM', 'longer string')"
  Next
    
End Sub

Sub RecordsetColRefvsLookupTestReference()
  Dim rst As New ADODB.Recordset
  Dim aColumns(10)
  Dim ii As Integer
  Dim x As Variant
  
  Set rst.ActiveConnection = cn_Native
  rst.Source = "select * from testtable"
  rst.CursorLocation = adUseClient
  rst.Open , , adOpenStatic, adLockReadOnly
  
  lStartTime = Timer
    
  For ii = 0 To rst.Fields.Count - 1
    Set aColumns(ii) = rst.Fields(ii)
  Next
  
  While rst.EOF <> True
    For ii = 0 To rst.Fields.Count - 1
      x = aColumns(ii).Value
    Next
    rst.MoveNext
  Wend
  
  txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
    
End Sub

Sub RecordsetColRefvsLookupTestLookup()
  Dim rst As New ADODB.Recordset
  Dim ii As Integer
  Dim x As Variant
  
  Set rst.ActiveConnection = cn_Native
  rst.Source = "select * from testtable"
  rst.CursorLocation = adUseClient
  rst.Open , , adOpenStatic, adLockReadOnly
  
  lStartTime = Timer
  
  While rst.EOF <> True
    For ii = 0 To rst.Fields.Count - 1
      x = rst.Fields(ii).Value
    Next
    rst.MoveNext
  Wend
  
  txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents

End Sub


'Native Provider vs ODBC Provider
Sub RecordsetNativeVsODBCProvTestSetup()
  
  Dim cn As ADODB.Connection
  Dim rst As ADODB.Recordset
  Dim ii As Integer
  
  On Error Resume Next
  cn_Native.Execute "drop table testtable"
  On Error GoTo 0
  cn_Native.Execute "create table testtable (dbkey integer identity primary key, field1 varchar(10), field2 datetime, field3 varchar(100))"
  
  For ii = 1 To 5000
    cn_Native.Execute "insert into testtable (field1, field2, field3) values ('string1', '19940701 12:30.00 AM', 'longer string')"
  Next
    
End Sub

Sub RecordsetNativeVsODBCProvTestNative()
  
  Dim rst As New ADODB.Recordset
  Dim aColumns(10)
  Dim ii As Integer
  Dim x As Variant
  
  Set rst.ActiveConnection = cn_Native
  rst.Source = "select * from testtable"
  rst.CursorLocation = adUseServer
  
  lStartTime = Timer
  
  rst.Open , , adOpenForwardOnly, adLockReadOnly
    
  For ii = 0 To rst.Fields.Count - 1
     Set aColumns(ii) = rst.Fields(ii)
  Next
  
  While rst.EOF <> True
     For ii = 0 To rst.Fields.Count - 1
       x = aColumns(ii).Value
     Next
     rst.MoveNext
  Wend
  
  txtNewTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
    
End Sub

Sub RecordsetNativeVsODBCProvTestODBCProv()
  Dim rst As New ADODB.Recordset
  Dim aColumns(10)
  Dim ii As Integer
  Dim x As Variant
  
  Set rst.ActiveConnection = cn_ODBC_Prov
  rst.Source = "select * from testtable"
  rst.CursorLocation = adUseServer
  
  lStartTime = Timer
  rst.Open , , adOpenForwardOnly, adLockReadOnly
    
  For ii = 0 To rst.Fields.Count - 1
     Set aColumns(ii) = rst.Fields(ii)
  Next
  
  While rst.EOF <> True
     For ii = 0 To rst.Fields.Count - 1
       x = aColumns(ii).Value
     Next
     rst.MoveNext
  Wend
  
  txtOldTime.Text = Str(Round(Timer - lStartTime, 2))
  DoEvents
  
End Sub



