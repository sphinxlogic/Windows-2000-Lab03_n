VERSION 5.00
Begin VB.Form frmFormView 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Microsoft ADO Consumer Sample"
   ClientHeight    =   6720
   ClientLeft      =   3375
   ClientTop       =   2235
   ClientWidth     =   8280
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6720
   ScaleWidth      =   8280
   StartUpPosition =   2  'CenterScreen
   WhatsThisHelp   =   -1  'True
   Begin VB.Frame frmCursorLocation 
      Caption         =   "Cursor Location"
      Height          =   735
      Left            =   240
      TabIndex        =   39
      Top             =   5880
      Width           =   2055
      Begin VB.OptionButton optClientCursor 
         Caption         =   "Client"
         Height          =   255
         Index           =   1
         Left            =   1080
         TabIndex        =   41
         Top             =   360
         Width           =   855
      End
      Begin VB.OptionButton optServerCursor 
         Caption         =   "Server"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   40
         Top             =   360
         Value           =   -1  'True
         Width           =   855
      End
   End
   Begin VB.CommandButton cmdRollbackTrans 
      Caption         =   "Rollback Trans"
      Height          =   375
      Left            =   6840
      TabIndex        =   38
      Top             =   2280
      Width           =   1335
   End
   Begin VB.CommandButton cmdCommitTrans 
      Caption         =   "Commit Trans"
      Height          =   375
      Left            =   6840
      TabIndex        =   37
      Top             =   1800
      Width           =   1335
   End
   Begin VB.CommandButton cmdBeginTrans 
      Caption         =   "Begin Trans"
      Height          =   375
      Left            =   6840
      TabIndex        =   36
      Top             =   1320
      Width           =   1335
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   0
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   10
      TabStop         =   0   'False
      Top             =   720
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   8
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   19
      TabStop         =   0   'False
      Top             =   4560
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   7
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   17
      TabStop         =   0   'False
      Top             =   4080
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   6
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   16
      TabStop         =   0   'False
      Top             =   3600
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   5
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   15
      TabStop         =   0   'False
      Top             =   3120
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   4
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   14
      TabStop         =   0   'False
      Top             =   2640
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   3
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   13
      TabStop         =   0   'False
      Top             =   2160
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   2
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   12
      TabStop         =   0   'False
      Top             =   1680
      Width           =   5175
   End
   Begin VB.TextBox tbData 
      Enabled         =   0   'False
      Height          =   315
      Index           =   1
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   11
      TabStop         =   0   'False
      Top             =   1200
      Width           =   5175
   End
   Begin VB.CommandButton cmdDisconnect 
      Caption         =   "Disconnect"
      Height          =   375
      Left            =   6840
      TabIndex        =   1
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton cmdCommand 
      Caption         =   "Command with Parameters"
      Height          =   615
      Left            =   6840
      TabIndex        =   4
      Top             =   3960
      Width           =   1335
   End
   Begin VB.TextBox txtSource 
      Enabled         =   0   'False
      Height          =   285
      Left            =   3240
      Locked          =   -1  'True
      TabIndex        =   18
      TabStop         =   0   'False
      Top             =   225
      Width           =   3375
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   375
      Left            =   6840
      TabIndex        =   0
      Top             =   240
      Width           =   1335
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "Dele&te"
      Height          =   375
      Left            =   3593
      TabIndex        =   7
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "&Update"
      Height          =   375
      Left            =   4793
      TabIndex        =   9
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Canc&el"
      Height          =   375
      Left            =   5993
      TabIndex        =   8
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Add"
      Height          =   375
      Left            =   2393
      TabIndex        =   6
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdEdit 
      Caption         =   "&Edit"
      Height          =   375
      Left            =   1193
      TabIndex        =   5
      Top             =   5280
      Width           =   1095
   End
   Begin VB.Frame Frame2 
      Caption         =   "Editing"
      Height          =   735
      Left            =   1073
      TabIndex        =   32
      Top             =   5040
      Width           =   6135
   End
   Begin VB.CommandButton cmdMoveNext 
      Caption         =   "&Next >"
      Height          =   375
      Left            =   4193
      TabIndex        =   21
      Top             =   6120
      Width           =   1095
   End
   Begin VB.CommandButton cmdMoveFirst 
      Caption         =   "<< &First"
      Height          =   375
      Left            =   2993
      TabIndex        =   20
      Top             =   6120
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Caption         =   "Navigation"
      Height          =   735
      Left            =   2873
      TabIndex        =   33
      Top             =   5880
      Width           =   2535
   End
   Begin VB.CommandButton cmdCloseRS 
      Caption         =   "Close RS"
      Height          =   375
      Left            =   6840
      TabIndex        =   3
      Top             =   3360
      Width           =   1335
   End
   Begin VB.CommandButton cmdOpenRS 
      Caption         =   "Open RS"
      Height          =   375
      Left            =   6840
      TabIndex        =   2
      Top             =   2880
      Width           =   1335
   End
   Begin VB.Label lblSource 
      AutoSize        =   -1  'True
      Caption         =   "Source"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   2400
      TabIndex        =   35
      Top             =   240
      Width           =   615
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 1"
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   34
      Top             =   720
      Width           =   1215
   End
   Begin VB.Label lblColumnData 
      AutoSize        =   -1  'True
      Caption         =   "Data"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   1440
      TabIndex        =   31
      Top             =   240
      Width           =   420
   End
   Begin VB.Label lblColumnName 
      AutoSize        =   -1  'True
      Caption         =   "Column"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Index           =   9
      Left            =   120
      TabIndex        =   30
      Top             =   240
      Width           =   630
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 2"
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   29
      Top             =   1230
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 3"
      Height          =   255
      Index           =   2
      Left            =   120
      TabIndex        =   28
      Top             =   1710
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 4"
      Height          =   255
      Index           =   3
      Left            =   120
      TabIndex        =   27
      Top             =   2160
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 5"
      Height          =   255
      Index           =   4
      Left            =   120
      TabIndex        =   26
      Top             =   2640
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 6"
      Height          =   255
      Index           =   5
      Left            =   120
      TabIndex        =   25
      Top             =   3120
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 7"
      Height          =   255
      Index           =   6
      Left            =   120
      TabIndex        =   24
      Top             =   3600
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 8"
      Height          =   255
      Index           =   7
      Left            =   120
      TabIndex        =   23
      Top             =   4080
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 9"
      Height          =   255
      Index           =   8
      Left            =   120
      TabIndex        =   22
      Top             =   4560
      Width           =   1215
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelp_About 
         Caption         =   "&About this sample..."
      End
   End
End
Attribute VB_Name = "frmFormView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public Conn As New ADODB.Connection
Public RS As New ADODB.Recordset
Dim DefaultFile As String

Private Sub cmdBeginTrans_Click()
    On Error GoTo Err
    
    Conn.BeginTrans
      
    cmdBeginTrans.Enabled = False
    cmdCommitTrans.Enabled = True
    cmdRollbackTrans.Enabled = True
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdCommand_Click()
    On Error GoTo Err
    
    frmParam.Show 1
    
    If RS.State = adStateOpen Then
        DisplayRow
        EnableText
        
        ' Set behavior of user interface
        EnableButtons
        cmdCloseRS.Enabled = True
        cmdConnect.Enabled = False
        cmdOpenRS.Enabled = False
        cmdCancel.Enabled = False
        cmdUpdate.Enabled = False
    
        ' Display only first 9 fields of recordset (first 9 host columns)
        Columns = RS.Fields.Count
        If Columns > 9 Then Columns = 9
        For X = 0 To Columns - 1
            lblColumnName(X) = RS.Fields(X).Name
        Next X
        
        ' Display source command used
        txtSource.Text = RS.Source
    End If
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdCommitTrans_Click()
    On Error GoTo Err
    
    Conn.CommitTrans
        
    cmdBeginTrans.Enabled = True
    cmdCommitTrans.Enabled = False
    cmdRollbackTrans.Enabled = False
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
   
End Sub

Private Sub cmdConnect_Click()
'This subroutine handles connecting to a host machine
Dim DataLink As New DataLinks

    On Error GoTo Err
    
    cmdConnect.Enabled = False
    
    Set Conn = Nothing
    
    If (MsgBox("Would you like to connect using an existing data link file?", vbYesNo, "Microsoft ADO Consumer Sample") = vbYes) Then
        UserInput = InputBox("Enter the full path to the data link:", "Microsoft ADO Consumer Sample", "C:\Program Files\Common Files\System\OLE DB\Data Links\drdademo.udl")
        If UserInput = "" Then
            Set Conn = Nothing
            cmdConnect.Enabled = True
            Exit Sub
        Else
            Conn.ConnectionString = "File Name=" & UserInput
        End If
    Else
        'There are a number of different ways to open a connection.  You can pass the "Open" method
        ' all of the appropriate connection information, if you know that information in advance.
        ' You would use the syntax:
        ' Conn.Open "Provider=DB2OLEDB;NetLib=SNA;NetAddr=;NetPort=;RemoteLU=DRDADEMO;LocalLU=LOCAL;ModeName=QPCSUPP;User ID=SNA;Password=SNA;InitCat=OLYMPIA;Default Schema=PUBS;PkgCol=PUBS;TPName=0X07F9F9F9;Commit=YES;IsoLvl=NC;AccMode=;CCSID=37;PCCodePage=1252;BinAsChar=NO;Data Source=Sample;"
        'However, in this case we would like the user to input the connection information, so we will
        'not specify any connection information (except the provider, which is REQUIRED ALWAYS unless you
        'set it via the connection.provider property)
        
        Conn.ConnectionString = "Provider=DB2OLEDB"
        
        ' This automatically causes a data links dialog to pop up, asking the user for connection information
        If (DataLink.PromptEdit(Conn) = False) Then
            Set Conn = Nothing
            cmdConnect.Enabled = True
            Exit Sub
        End If
    End If
    
    Conn.Properties("Prompt") = adPromptNever
    
    Conn.Open
        
    ' This automatically causes a dialog to pop up asking the user for data source, user name, and password
        
    ' Set behavior of user interface
    cmdConnect.Enabled = False
    cmdOpenRS.Enabled = True
    cmdCommand.Enabled = True
    cmdDisconnect.Enabled = True
    cmdBeginTrans.Enabled = True
    cmdCommitTrans.Enabled = False
    cmdRollbackTrans.Enabled = False
        
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
    For X = 0 To 8
        lblColumnName(X) = ""
    Next X
        
    Set Conn = Nothing
    
    cmdConnect.Enabled = True
    
End Sub

Private Sub cmdDisconnect_Click()
'This subroutine handles disconnecting from a host machine
    On Error GoTo Err
    
    'Just in case the user did not properly close the recordset:
    Set RS = Nothing

    'First we close the connection.  This disconnects us from the host machine
    Conn.Close
    
    'But closing an object does not completely eliminate its memory usage--we must set the object to nothing
    Set Conn = Nothing
    
    ' Set behavior of user interface
    DisableButtons
    cmdBeginTrans.Enabled = False
    cmdCommitTrans.Enabled = False
    cmdRollbackTrans.Enabled = False
    cmdConnect.Enabled = True

    For X = 0 To 8
        lblColumnName(X) = ""
    Next X
    
    ClearTextBoxes
    txtSource.Text = ""
    DisableText
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"

End Sub

Private Sub cmdRollbackTrans_Click()
    On Error GoTo Err
    
    Conn.RollbackTrans
        
    cmdBeginTrans.Enabled = True
    cmdCommitTrans.Enabled = False
    cmdRollbackTrans.Enabled = False
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    Resume Next
   
End Sub

Private Sub Form_Load()
'This subroutine loads the form and displays it correctly on the screen
    On Error Resume Next
            
    ' Set behavior of user interface
    For X = 0 To 8
        lblColumnName(X) = ""
        tbData(X).TabStop = False
    Next X
    ClearTextBoxes
    
    DisableButtons
    cmdBeginTrans.Enabled = False
    cmdCommitTrans.Enabled = False
    cmdRollbackTrans.Enabled = False
    
    DefaultFile = "SELECT * FROM PUBS.AUTHORS"
    
    cmdConnect.Enabled = True
    
End Sub

Public Sub DisplayErrors()
'This subroutine cycles through any errors generated and displays them on the screen
    Dim Msg As String
    Dim I As Integer
    Dim MyErr As Object
    
    On Error Resume Next    'continue even if an error occurs
    
    For I = 1 To Conn.Errors.Count
        Set MyErr = Conn.Errors(I - 1)
        Msg = "[Description: " & MyErr.Description & "][" & MyErr.Number & "]"
        MsgBox Msg, vbExclamation, "Microsoft ADO Consumer Sample"
        Set MyErr = Nothing
    Next I
    Conn.Errors.Clear
    Exit Sub

End Sub

Private Sub cmdOpenRS_Click()
'This subroutine handles input of a file name and opening a recordset
    On Error GoTo Err
    
    Set RS = Nothing
    
    ' Open ADO Recordset - option 1 - allow the user to choose host table
    UserInput = InputBox("Enter a SQL statement:", "Microsoft ADO Consumer Sample", DefaultFile)
    If UserInput = "" Then Exit Sub
    DefaultFile = UserInput
    
    ' RS.CursorLocation = adUseServer
    If optServerCursor(0) Then
        RS.CursorLocation = adUseServer
    Else
        RS.CursorLocation = adUseClient
    End If
 
    
            
    ' Required OpenRS method parameters: CursorType = 2 "adOpenDynamic"; LockType = 4 "adLockOptimistic"; Options = 1 "adCmdText"
    'RS.Open "Exec Open " & DefaultFile, Conn, adOpenDynamic, adLockOptimistic, adCmdText
    RS.Open DefaultFile, Conn, adOpenForwardOnly, adLockOptimistic, adCmdText
                
    ' Open ADO Recordset - option 2 - specify target host table for user
        ' RS.Open "Exec Open LIBRARY/FILE", Conn, 2, 4, 1
                
    ' Display a single recordset row (single host table record)
    If RS.State = adStateOpen Then
        DisplayRow
        EnableText
        
        ' Set behavior of user interface
        EnableButtons
        cmdCloseRS.Enabled = True
        cmdConnect.Enabled = False
        cmdOpenRS.Enabled = False
        cmdCancel.Enabled = False
        cmdUpdate.Enabled = False
    
        ' Display only first 9 fields of recordset (first 9 host columns)
        Columns = RS.Fields.Count
        If Columns > 9 Then Columns = 9
        For X = 0 To Columns - 1
            lblColumnName(X) = RS.Fields(X).Name
        Next X
        
        ' Display source command used
        txtSource.Text = RS.Source
    Else
        MsgBox "Command succeeded."
    End If
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
    Set RS = Nothing
    
    ' Set behavior of user interface
    For X = 0 To 8
        lblColumnName(X) = ""
    Next X
    ClearTextBoxes
    DisableButtons
    cmdDisconnect.Enabled = True
    cmdOpenRS.Enabled = True
    cmdCommand.Enabled = True
    
End Sub

Private Sub cmdCloseRS_Click()
'This subroutine closes the open recordset
    On Error Resume Next
   
    'First we close the recordset
    RS.Close
    
    'But at this point we are still using up memory with the recordset object, so we must free that
    ' memory by setting the object to nothing
    Set RS = Nothing

    ' Set behavior of user interface
    For X = 0 To 8
        lblColumnName(X) = ""
    Next X
    
    ClearTextBoxes
    txtSource.Text = ""
    DisableText
    
    DisableButtons
    
    cmdDisconnect.Enabled = True
    cmdOpenRS.Enabled = True
    cmdCommand.Enabled = True
    cmdOpenRS.SetFocus
    
End Sub

Sub ClearTextBoxes()
'This subroutine clears the 9 field boxes on the screen
    On Error Resume Next
    
    For X = 0 To 8
        tbData(X) = ""
    Next X
   
End Sub

Sub LockTextBoxes(bLocked)
    On Error Resume Next
    
    For X = 0 To 8
        tbData(X).Locked = bLocked
    Next X
    
    For X = 0 To 8
        tbData(X).TabStop = True
    Next X
    
End Sub

Public Sub DisplayRow()
'This subroutine reads one set of 9 fields from the file and displays them on the screen
    On Error GoTo Err
    
    Columns = RS.Fields.Count
    If Columns > 9 Then Columns = 9     'we only have space for 9 fields in our form
    For X = 0 To Columns - 1
        If Not IsNull(RS(X)) Then
            tbData(X).Text = RTrim(RS(X))   'rtrim removes all the blank space on the right of a string
        Else
            tbData(X).Text = "<null>"
        End If
    Next
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Sub EnableButtons()
'This subroutine enables all the buttons on the screen
    On Error Resume Next
    
    cmdConnect.Enabled = True
    cmdDisconnect.Enabled = True
    cmdOpenRS.Enabled = True
    cmdCloseRS.Enabled = True
    cmdCommand.Enabled = True
    
    cmdEdit.Enabled = True
    cmdAdd.Enabled = True
    cmdDelete.Enabled = True
    cmdUpdate.Enabled = True
    
    cmdMoveFirst.Enabled = True
    cmdMoveNext.Enabled = True
    
End Sub

Sub DisableButtons()
'This subroutine disables (greys out) all the buttons on the screen
    On Error Resume Next
    
    cmdConnect.Enabled = False
    cmdDisconnect.Enabled = False
    cmdOpenRS.Enabled = False
    cmdCloseRS.Enabled = False
    cmdCommand.Enabled = False
    
    cmdEdit.Enabled = False
    cmdAdd.Enabled = False
    cmdCancel.Enabled = False
    cmdDelete.Enabled = False
    cmdUpdate.Enabled = False
    
    cmdMoveFirst.Enabled = False
    cmdMoveNext.Enabled = False

End Sub

Sub EnableText()
    On Error Resume Next
    
    tbData(0).Enabled = True
    tbData(1).Enabled = True
    tbData(2).Enabled = True
    tbData(3).Enabled = True
    tbData(4).Enabled = True
    tbData(5).Enabled = True
    tbData(6).Enabled = True
    tbData(7).Enabled = True
    tbData(8).Enabled = True
    txtSource.Enabled = True
    
End Sub

Sub DisableText()
    On Error Resume Next
    
    tbData(0).Enabled = False
    tbData(1).Enabled = False
    tbData(2).Enabled = False
    tbData(3).Enabled = False
    tbData(4).Enabled = False
    tbData(5).Enabled = False
    tbData(6).Enabled = False
    tbData(7).Enabled = False
    tbData(8).Enabled = False
    txtSource.Enabled = False

End Sub

Private Sub cmdMoveFirst_Click()
    On Error GoTo Err
    
    RS.MoveFirst
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    cmdMoveFirst.Enabled = False
    cmdMoveNext.Enabled = True
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdMovePrevious_Click()
    On Error GoTo Err
    
    If RS.BOF = False Then
        RS.MovePrevious
        If RS.BOF = False Then
            DisplayRow
            cmdMoveNext.Enabled = True
        Else
            cmdMoveFirst.Enabled = False
            cmdMoveNext.Enabled = True
        End If
    End If
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub cmdMoveNext_Click()
    On Error GoTo Err
    
    If RS.EOF = False Then
        RS.MoveNext
        If RS.EOF = False Then
            DisplayRow
            cmdMoveFirst.Enabled = True
        Else
            cmdMoveFirst.Enabled = True
            cmdMoveNext.Enabled = False
        End If
    End If
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub cmdMoveLast_Click()
    On Error GoTo Err
    
    RS.MoveLast
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    cmdMoveFirst.Enabled = True
    cmdMoveNext.Enabled = False
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub Form_Unload(Cancel As Integer)
'This subroutine ensures that all memory has been freed up prior to exit
    On Error Resume Next
    
    Set RS = Nothing
    Set CmdCL = Nothing
    Set Conn = Nothing
    
End Sub

Private Sub cmdEdit_Click()
    On Error Resume Next
    
    ' Set behavior of user interface
    DisableButtons
    cmdCancel.Enabled = True
    cmdUpdate.Enabled = True
    LockTextBoxes False

End Sub

Private Sub cmdAdd_Click()
    On Error GoTo Err
    
    RS.AddNew
    
    ' Set behavior of user interface
    ClearTextBoxes
    DisableButtons
    cmdCancel.Enabled = True
    cmdUpdate.Enabled = True
    LockTextBoxes False
    For X = 0 To 8
        tbData(X).TabStop = True
    Next X
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdCancel_Click()
    On Error GoTo Err
    
    RS.CancelUpdate
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    EnableButtons
    cmdCancel.Enabled = False
    cmdUpdate.Enabled = False
    cmdOpenRS.Enabled = False
    cmdConnect.Enabled = False
    LockTextBoxes True
    For X = 0 To 8
        tbData(X).TabStop = False
    Next X
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdUpdate_Click()
    On Error GoTo Err
    
    Columns = RS.Fields.Count
    If Columns > 9 Then Columns = 9
    For X = 0 To Columns - 1
        RS(X) = LTrim(tbData(X))
    Next

    RS.Update
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    EnableButtons
    cmdCancel.Enabled = False
    cmdUpdate.Enabled = False
    cmdConnect.Enabled = False
    cmdOpenRS.Enabled = False
    
    LockTextBoxes True
    For X = 0 To 8
        tbData(X).TabStop = True
    Next X
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
       
End Sub

Private Sub cmdDelete_Click()
    On Error GoTo Err
    
    If MsgBox("Are you sure you want to delete this row?", vbYesNo, "Microsoft ADO Consumer Sample") = vbNo Then
        Exit Sub
    Else
        RS.Delete

        RS.Update
        RS.MoveFirst
        
        ' Display a single recordset row (single host table record)
        DisplayRow
    
        ' Set behavior of user interface
        cmdMoveNext.Enabled = True
    End If
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub mnuFile_Exit_Click()
    Unload Me
End Sub

Private Sub mnuHelp_About_Click()
    On Error Resume Next
    
    Load frmAbout
    frmAbout.Show 1
    
End Sub


