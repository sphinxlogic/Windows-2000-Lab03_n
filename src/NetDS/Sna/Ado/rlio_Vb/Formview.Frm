VERSION 5.00
Begin VB.Form frmFormView 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Microsoft ADO Consumer Sample"
   ClientHeight    =   6345
   ClientLeft      =   3375
   ClientTop       =   2235
   ClientWidth     =   8280
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6345
   ScaleWidth      =   8280
   StartUpPosition =   2  'CenterScreen
   WhatsThisHelp   =   -1  'True
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
      Left            =   6960
      TabIndex        =   1
      Top             =   720
      Width           =   1095
   End
   Begin VB.CommandButton cmdCommand 
      Caption         =   "Execute Cmd"
      Height          =   375
      Left            =   6960
      TabIndex        =   4
      Top             =   2760
      Width           =   1095
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
      Left            =   6960
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton cmdFilter 
      Caption         =   "Filte&r"
      Height          =   375
      Left            =   1800
      TabIndex        =   26
      Top             =   5760
      Width           =   1095
   End
   Begin VB.CommandButton cmdFind 
      Caption         =   "F&ind"
      Height          =   375
      Left            =   3000
      TabIndex        =   27
      Top             =   5760
      Width           =   1095
   End
   Begin VB.CommandButton cmdAddBookmark 
      Caption         =   "Add"
      Height          =   375
      Left            =   240
      TabIndex        =   21
      Top             =   5760
      Width           =   1095
   End
   Begin VB.ListBox lstBookmark 
      Enabled         =   0   'False
      Height          =   450
      ItemData        =   "FormView.frx":0000
      Left            =   240
      List            =   "FormView.frx":0002
      TabIndex        =   20
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "Dele&te"
      Height          =   375
      Left            =   6960
      TabIndex        =   7
      Top             =   4800
      Width           =   1095
   End
   Begin VB.CommandButton cmdUpdate 
      Caption         =   "&Update"
      Height          =   375
      Left            =   6960
      TabIndex        =   9
      Top             =   5760
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Canc&el"
      Height          =   375
      Left            =   6960
      TabIndex        =   8
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Add"
      Height          =   375
      Left            =   6960
      TabIndex        =   6
      Top             =   4320
      Width           =   1095
   End
   Begin VB.CommandButton cmdEdit 
      Caption         =   "&Edit"
      Height          =   375
      Left            =   6960
      TabIndex        =   5
      Top             =   3840
      Width           =   1095
   End
   Begin VB.Frame Frame2 
      Caption         =   "Editing"
      Height          =   2655
      Left            =   6840
      TabIndex        =   39
      Top             =   3600
      Width           =   1335
   End
   Begin VB.CommandButton cmdMoveLast 
      Caption         =   "&Last >|"
      Height          =   375
      Left            =   5400
      TabIndex        =   25
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdMoveNext 
      Caption         =   "&Next >"
      Height          =   375
      Left            =   4200
      TabIndex        =   24
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdMovePrevious 
      Caption         =   "< &Previous"
      Height          =   375
      Left            =   3000
      TabIndex        =   23
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton cmdMoveFirst 
      Caption         =   "|< &First"
      Height          =   375
      Left            =   1800
      TabIndex        =   22
      Top             =   5280
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Caption         =   "Navigation"
      Height          =   1215
      Left            =   1680
      TabIndex        =   40
      Top             =   5040
      Width           =   4935
      Begin VB.CommandButton cmdFindNext 
         Caption         =   "Find Next"
         Height          =   375
         Left            =   2520
         TabIndex        =   43
         Top             =   720
         Width           =   1095
      End
   End
   Begin VB.CommandButton cmdCloseRS 
      Caption         =   "Close RS"
      Height          =   375
      Left            =   6960
      TabIndex        =   3
      Top             =   1920
      Width           =   1095
   End
   Begin VB.CommandButton cmdOpenRS 
      Caption         =   "Open RS"
      Height          =   375
      Left            =   6960
      TabIndex        =   2
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Frame frmBookmark 
      Caption         =   "Bookmark"
      Height          =   1215
      Left            =   120
      TabIndex        =   38
      Top             =   5040
      Width           =   1335
   End
   Begin VB.Label lblSource 
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
      Height          =   255
      Left            =   2520
      TabIndex        =   42
      Top             =   240
      Width           =   735
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 1"
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   41
      Top             =   720
      Width           =   1215
   End
   Begin VB.Label lblColumnData 
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
      Height          =   255
      Left            =   1440
      TabIndex        =   37
      Top             =   240
      Width           =   615
   End
   Begin VB.Label lblColumnName 
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
      Height          =   255
      Index           =   9
      Left            =   120
      TabIndex        =   36
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 2"
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   35
      Top             =   1230
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 3"
      Height          =   255
      Index           =   2
      Left            =   120
      TabIndex        =   34
      Top             =   1710
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 4"
      Height          =   255
      Index           =   3
      Left            =   120
      TabIndex        =   33
      Top             =   2160
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 5"
      Height          =   255
      Index           =   4
      Left            =   120
      TabIndex        =   32
      Top             =   2640
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 6"
      Height          =   255
      Index           =   5
      Left            =   120
      TabIndex        =   31
      Top             =   3120
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 7"
      Height          =   255
      Index           =   6
      Left            =   120
      TabIndex        =   30
      Top             =   3600
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 8"
      Height          =   255
      Index           =   7
      Left            =   120
      TabIndex        =   29
      Top             =   4080
      Width           =   1215
   End
   Begin VB.Label lblColumnName 
      Caption         =   "Column 9"
      Height          =   255
      Index           =   8
      Left            =   120
      TabIndex        =   28
      Top             =   4560
      Width           =   1215
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFile_Connect 
         Caption         =   "Co&nnect"
      End
      Begin VB.Menu mnuFile_Disconnect 
         Caption         =   "&Disconnect"
      End
      Begin VB.Menu mnuFile_Separator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_OpenRS 
         Caption         =   "&Open"
      End
      Begin VB.Menu mnuFile_CloseRS 
         Caption         =   "&Close"
      End
      Begin VB.Menu mnuFile_Separator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Command 
         Caption         =   "&Execute"
      End
      Begin VB.Menu mnuFile_Separator3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFile_Exit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEdit_Edit 
         Caption         =   "&Edit Record"
      End
      Begin VB.Menu mnuEdit_Add 
         Caption         =   "&Add Record"
      End
      Begin VB.Menu mnuEdit_Separator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEdit_Delete 
         Caption         =   "&Delete Record"
      End
      Begin VB.Menu mnuEdit_Separator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEdit_Update 
         Caption         =   "&Update Records"
      End
      Begin VB.Menu mnuEdit_Cancel 
         Caption         =   "&Cancel Edit"
      End
   End
   Begin VB.Menu mnuNavigate 
      Caption         =   "&Navigate"
      Begin VB.Menu mnuNavigate_MoveFirst 
         Caption         =   "&First"
      End
      Begin VB.Menu mnuNavigate_MovePrevious 
         Caption         =   "&Previous"
      End
      Begin VB.Menu mnuNavigate_MoveNext 
         Caption         =   "&Next"
      End
      Begin VB.Menu mnuNavigate_MoveLast 
         Caption         =   "&Last"
      End
      Begin VB.Menu mnuNavigate_Divider1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuNavigate_Filter 
         Caption         =   "Filte&r"
      End
      Begin VB.Menu mnuNavigate_Find 
         Caption         =   "F&ind"
      End
      Begin VB.Menu mnuNavigate_FindNext 
         Caption         =   "Fi&nd Next"
      End
   End
   Begin VB.Menu mnuBookmark 
      Caption         =   "&Bookmark"
      Begin VB.Menu mnuBookmark_AddBookmark 
         Caption         =   "&Add Bookmark"
      End
      Begin VB.Menu mnuBookmark_GetBookmark 
         Caption         =   "&Get Bookmark"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelp_About 
         Caption         =   "&About..."
      End
   End
End
Attribute VB_Name = "frmFormView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim BookmarkVals() As Variant
Dim Conn As New adodb.Connection
Dim CmdCL As New adodb.Command
Dim RS As New adodb.Recordset
Dim Param As New adodb.Parameter
Dim DefaultFile As String
Dim FilterText As String
Dim FindText As String
Dim CommandText As String

Private Sub cmdCommand_Click()
'This subroutine handles the input and execution of a command

    On Error GoTo Err
    
    ' Create command object
    Set CmdCL = Nothing
    Set CmdCL.ActiveConnection = Conn
    CmdCL.CommandType = adCmdText

    ' Obtain user input for the AS/400 command
    UserInput = InputBox("Which AS/400 command do you want to execute?", "Microsoft ADO Consumer Sample", CommandText)
    If UserInput = "" Then Exit Sub
        
    CommandText = UserInput
        
    ' Associate a parameter object with the command
    Set Param = CmdCL.CreateParameter("Param1", adBSTR, adParamOutput)
    CmdCL.Parameters.Append Param
    
    CmdCL.CommandText = "Exec Command " & UserInput
    
    ' Execute the command
    CmdCL.Execute adCmdText
        
    ' Display source command used
    txtSource.Text = CmdCL.CommandText
    txtSource.Enabled = True

    ' Display return message
    If CmdCL.Parameters.Count > 0 Then
        MsgBox CmdCL.Parameters(0).Value, , "Microsoft ADO Consumer Sample"
    End If
    
    ' Set behavior of user interface
    cmdCommand.Enabled = True
    mnuFile_Command.Enabled = True
      
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
    Set CmdCL = Nothing

End Sub

Private Sub cmdConnect_Click()
'This subroutine handles connecting to a host machine
Dim DataLink As New DataLinks
    On Error GoTo Err
    
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    
    Set Conn = Nothing
    
    If (MsgBox("Would you like to connect using an existing data link file?", vbYesNo, "Microsoft ADO Consumer Sample") = vbYes) Then
        UserInput = InputBox("Enter the full path to the data link:", "Microsoft ADO Consumer Sample", "C:\Program Files\Common Files\System\OLE DB\Data Links\ddmdemo.udl")
        If UserInput = "" Then
            Set Conn = Nothing
            cmdConnect.Enabled = True
            mnuFile_Connect.Enabled = True
            Exit Sub
        Else
            Conn.ConnectionString = "File Name=" & UserInput
        End If
    Else
        'There are a number of different ways to open a connection.  You can pass the "Open" method
        ' all of the appropriate connection information, if you know that information in advance.
        ' You would use the syntax:
        ' Conn.Open "Provider=SNAOLEDB;NetLib=SNA;NetAddr=;NetPort=;RemoteLU=DDMDEMO;LocalLU=LOCAL;ModeName=QPCSUPP;Password=SNA;User ID=SNA;Location=DDMDEMO;DefaultLibrary=PUBS;CCSID=37;PCCodePage=1252;HCDFileName=;BinAsChar=NO;RepairKeys=NO;StrictVal=NO;Data Source=Sample;"

        'However, in this case we would like the user to input the connection information, so we will
        'not specify any connection information (except the provider, which is REQUIRED ALWAYS unless you
        'set it via the connection.provider property)
        
        Conn.ConnectionString = "Provider=SNAOLEDB"
        
        ' This automatically causes a data links dialog to pop up, asking the user for connection information
        If (DataLink.PromptEdit(Conn) = False) Then
            Set Conn = Nothing
            cmdConnect.Enabled = True
            mnuFile_Connect.Enabled = True
            Exit Sub
        End If
    End If
    
    Conn.Properties("Prompt") = adPromptNever
    Conn.Open
  
    ' Set behavior of user interface
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    cmdOpenRS.Enabled = True
    mnuFile_OpenRS.Enabled = True
    cmdCommand.Enabled = True
    mnuFile_Command.Enabled = True
    cmdDisconnect.Enabled = True
    mnuFile_Disconnect.Enabled = True
        
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
    For x = 0 To 8
        lblColumnName(x) = ""
    Next x
        
    Set Conn = Nothing
    
    cmdConnect.Enabled = True
    mnuFile_Connect.Enabled = True
    
End Sub

Private Sub cmdDisconnect_Click()
'This subroutine handles disconnecting from a host machine
    On Error Resume Next
    
    'Just in case the user did not properly close the recordset:
    Set RS = Nothing
    Set RScmd = Nothing
    
    'First we close the connection.  This disconnects us from the host machine
    Conn.Close
    'But closing an object does not completely eliminate its memory usage--we must set the object to nothing
    Set Conn = Nothing
    
    ' Set behavior of user interface
    DisableButtons
    DisableMenus
    cmdConnect.Enabled = True
    mnuFile_Connect.Enabled = True
    mnuBookmark_GetBookmark.Enabled = False

    For x = 0 To 8
        lblColumnName(x) = ""
    Next x
    
    ClearTextBoxes
    txtSource.Text = ""
    DisableText

End Sub

Private Sub cmdFilter_Click()
'This subroutine sets up a filter

    On Error GoTo Err   'Error handling
    
    'First we input from the user information about the filter
    UserInput = InputBox("Enter filter criteria.", "Microsoft ADO Consumer Sample", FilterText)
    FilterText = UserInput
    
    RS.Filter = UserInput   'Filter can be set to a string that contains multiple criteria strings
                            'separated by 'AND'.  Filter works in three ways:
                            '(1) If one criteria string is used then any operator can be used.
                            '(2) If two criteria strings are used then
                                '-if the column name is the same in both strings, then the criteria strings must define a contiguous range
                                '-if the column names are different, then the operators must be the same.
                            '(3) If three or more criteria strings are used then the operator must be the same for all.
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    EnableButtons
    EnableMenus
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    cmdOpenRS.Enabled = False
    mnuFile_OpenRS.Enabled = False
    cmdCancel.Enabled = False
    mnuEdit_Cancel.Enabled = False
    cmdUpdate.Enabled = False
    mnuEdit_Update.Enabled = False

    ' Display source command used
    txtSource.Text = RS.Source

    ' Display only first 9 fields of recordset (first 9 host columns)
    Columns = RS.Fields.Count
    If Columns > 9 Then Columns = 9
    For x = 0 To Columns - 1
        lblColumnName(x) = RS.Fields(x).Name
    Next x
    
    Exit Sub
        
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdFind_Click()
'This subroutine handles searching for a record
    On Error GoTo Err
    
    'First input the characteristics to search for
    UserInput = InputBox("Find record?", "Microsoft ADO Consumer Sample", FindText)
    If UserInput = "" Then Exit Sub
    FindText = UserInput
    
    RS.MoveFirst
    RS.Find UserInput
                        'The argument for the Find method takes a criteria string
                        'that has three parts: ColumnName, Operator, Value.
                        'In the example, the ColumnName is "AU_ID", the Operator is ">"
                        ' greater than, and the Value is "2".
                        'Find only works with files that are keyed by column name.
        
    ' Set behavior of user interface
    EnableButtons
    EnableMenus
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    cmdOpenRS.Enabled = False
    mnuFile_OpenRS.Enabled = False
    cmdCancel.Enabled = False
    mnuEdit_Cancel.Enabled = False
    cmdUpdate.Enabled = False
    mnuEdit_Update.Enabled = False

    ' Display a single recordset row (single host table record)
    DisplayRow
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
     
End Sub

Private Sub cmdFindNext_Click()
'This subroutine handles searching for a record from the current record
    On Error GoTo Err
    
    'First input the characteristics to search for
    UserInput = InputBox("Find next record?", "Microsoft ADO Consumer Sample", FindText)
    If UserInput = "" Then Exit Sub
    FindText = UserInput
    
    RS.Find UserInput, 1
                        'The argument for the Find method takes a criteria string
                        'that has three parts: ColumnName, Operator, Value.
                        'In the example, the ColumnName is "AU_ID", the Operator is ">"
                        ' greater than, and the Value is "2".
                        'Find only works with files that are keyed by column name.
    
    ' Set behavior of user interface
    EnableButtons
    EnableMenus
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    cmdOpenRS.Enabled = False
    mnuFile_OpenRS.Enabled = False
    cmdCancel.Enabled = False
    mnuEdit_Cancel.Enabled = False
    cmdUpdate.Enabled = False
    mnuEdit_Update.Enabled = False

    ' Display a single recordset row (single host table record)
    DisplayRow
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
     
End Sub


Private Sub Form_Load()
'This subroutine loads the form and displays it correctly on the screen
    On Error Resume Next

    FilterText = "AU_ID > '2' AND AU_ID < '5'"
    FindText = "AU_ID > 3"
    CommandText = "AS/400 CL Command"
    
    ReDim BookmarkVals(1)
    ReDim BookmarkNames(1)
            
    ' Set behavior of user interface
    For x = 0 To 8
        lblColumnName(x) = ""
        tbData(x).TabStop = False
    Next x
    ClearTextBoxes
    
    DisableButtons
    DisableMenus
    
    DefaultFile = "Library/Table"
    
    cmdConnect.Enabled = True
    mnuFile_Connect.Enabled = True
    mnuBookmark_GetBookmark.Enabled = False
    
End Sub

Public Sub DisplayErrors()
'This subroutine cycles through any errors generated and displays them on the screen
On Error Resume Next    'continue even if an error occurs

    If Conn.Errors.Count > 0 Then
        For x = 0 To Conn.Errors.Count - 1
            ErrDesc = ErrDesc & Conn.Errors(x).Description & vbNewLine
        Next x
        MsgBox ErrDesc, vbExclamation, "Microsoft ADO Consumer Sample"
    End If
    Conn.Errors.Clear

End Sub

Private Sub cmdOpenRS_Click()
'This subroutine handles input of a file name and opening a recordset
    On Error GoTo Err
    
    Set RS = Nothing
    
    ' Open ADO Recordset - option 1 - allow the user to choose host table
    UserInput = InputBox("Which table do you want to open?", "Microsoft ADO Consumer Sample", DefaultFile)
    If UserInput = "" Then Exit Sub
    DefaultFile = UserInput
            
    ' Required OpenRS method parameters: CursorType = 2 "adOpenDynamic"; LockType = 4 "adLockOptimistic"; Options = 1 "adCmdText"
    RS.Open "Exec Open " & DefaultFile, Conn, adOpenDynamic, adLockOptimistic, adCmdText
                
    ' Open ADO Recordset - option 2 - specify target host table for user
    ' RS.Open "Exec Open LIBRARY/FILE", Conn, 2, 4, 1
                
    ' Display a single recordset row (single host table record)
    DisplayRow
    EnableText
    
    ' Set behavior of user interface
    EnableButtons
    EnableMenus
    cmdCloseRS.Enabled = True
    mnuFile_CloseRS.Enabled = True
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    cmdOpenRS.Enabled = False
    mnuFile_OpenRS.Enabled = False
    cmdCancel.Enabled = False
    mnuEdit_Cancel.Enabled = False
    cmdUpdate.Enabled = False
    mnuEdit_Update.Enabled = False
    
    ' Display only first 9 fields of recordset (first 9 host columns)
    Columns = RS.Fields.Count
    If Columns > 9 Then Columns = 9
    For x = 0 To Columns - 1
        lblColumnName(x) = RS.Fields(x).Name
    Next x
    
    ' Display source command used
    txtSource.Text = RS.Source
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
    Set RS = Nothing
    
    ' Set behavior of user interface
    For x = 0 To 8
        lblColumnName(x) = ""
    Next x
    ClearTextBoxes
    DisableButtons
    DisableMenus
    cmdDisconnect.Enabled = True
    mnuFile_Disconnect.Enabled = True
    cmdOpenRS.Enabled = True
    mnuFile_OpenRS.Enabled = True
    cmdCommand.Enabled = True
    mnuFile_Command.Enabled = True
    mnuBookmark_GetBookmark.Enabled = False
    
End Sub

Private Sub cmdCloseRS_Click()
'This subroutine closes the open recordset
    On Error Resume Next
   
    'First we close the recordset--this ends our lock on the file
    RS.Close
    'But at this point we are still using up memory with the recordset object, so we must free that
    ' memory by setting the object to nothing
    Set RS = Nothing

    ' Set behavior of user interface
    For x = 0 To 8
        lblColumnName(x) = ""
    Next x
    
    ClearTextBoxes
    txtSource.Text = ""
    DisableText
    
    DisableButtons
    DisableMenus
    
    cmdDisconnect.Enabled = True
    mnuFile_Disconnect.Enabled = True
    cmdOpenRS.Enabled = True
    mnuFile_OpenRS.Enabled = True
    cmdCommand.Enabled = True
    mnuFile_Command.Enabled = True
    cmdOpenRS.SetFocus
    lstBookmark.Clear
    mnuBookmark_GetBookmark.Enabled = False

End Sub

Sub ClearTextBoxes()
'This subroutine clears the 9 field boxes on the screen
    On Error Resume Next
    
    For x = 0 To 8
        tbData(x) = ""
    Next x
   
End Sub

Sub LockTextBoxes(bLocked)
    On Error Resume Next
    
    For x = 0 To 8
        tbData(x).Locked = bLocked
    Next x
    
    For x = 0 To 8
        tbData(x).TabStop = True
    Next x
    
End Sub

Public Sub DisplayRow()
'This subroutine reads one set of 8 fields from the file and displays them on the screen
    On Error GoTo Err
    
    Columns = RS.Fields.Count
    If Columns > 9 Then Columns = 9     'we only have space for 9 fields in our form
    For x = 0 To Columns - 1
        tbData(x).Text = RTrim(RS(x))   'rtrim removes all the blank space on the right of a string
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
    cmdMoveLast.Enabled = True
    cmdMoveNext.Enabled = True
    cmdMovePrevious.Enabled = True
    cmdFilter.Enabled = True
    cmdFind.Enabled = True
    cmdFindNext.Enabled = True
    
    cmdAddBookmark.Enabled = True
    lstBookmark.Enabled = True

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
    cmdMovePrevious.Enabled = False
    cmdMoveNext.Enabled = False
    cmdMoveLast.Enabled = False
    cmdFilter.Enabled = False
    cmdFind.Enabled = False
    cmdFindNext.Enabled = False
    
    cmdAddBookmark.Enabled = False
    lstBookmark.Enabled = False

End Sub

Sub EnableMenus()
'This subroutine enables all the possible menu items
    On Error Resume Next
    
    mnuFile_Connect.Enabled = True
    mnuFile_OpenRS.Enabled = True
    mnuFile_CloseRS.Enabled = True
    mnuFile_Command.Enabled = True
    mnuFile_Disconnect.Enabled = False
    
    mnuEdit_Edit.Enabled = True
    mnuEdit_Add.Enabled = True
    mnuEdit_Delete.Enabled = True
    mnuEdit_Update.Enabled = True
    mnuEdit_Cancel.Enabled = True
    
    mnuNavigate_MoveFirst.Enabled = True
    mnuNavigate_MovePrevious.Enabled = True
    mnuNavigate_MoveNext.Enabled = True
    mnuNavigate_MoveLast.Enabled = True
    mnuNavigate_Filter.Enabled = True
    mnuNavigate_Find.Enabled = True
    mnuNavigate_FindNext.Enabled = True
    
    mnuBookmark_AddBookmark.Enabled = True

End Sub

Sub DisableMenus()
'This subroutine disables (greys out) all the possible menu items
    On Error Resume Next
    
    mnuFile_Connect.Enabled = False
    mnuFile_OpenRS.Enabled = False
    mnuFile_CloseRS.Enabled = False
    mnuFile_Command.Enabled = False
    mnuFile_Disconnect.Enabled = False
    
    mnuEdit_Edit.Enabled = False
    mnuEdit_Add.Enabled = False
    mnuEdit_Cancel.Enabled = False
    mnuEdit_Delete.Enabled = False
    mnuEdit_Update.Enabled = False
    
    mnuNavigate_MoveFirst.Enabled = False
    mnuNavigate_MovePrevious.Enabled = False
    mnuNavigate_MoveNext.Enabled = False
    mnuNavigate_MoveLast.Enabled = False
    mnuNavigate_Filter.Enabled = False
    mnuNavigate_Find.Enabled = False
    mnuNavigate_FindNext.Enabled = False

    mnuBookmark_AddBookmark.Enabled = False

End Sub

Sub EnableText()
    On Error Resume Next
    
    For x = 0 To 8
        tbData(x).Enabled = True
    Next x

    txtSource.Enabled = True
    
End Sub

Sub DisableText()
    On Error Resume Next
    
    For x = 0 To 8
        tbData(x).Enabled = False
    Next x
    
    txtSource.Enabled = False
    lstBookmark.TabStop = False

End Sub

Private Sub cmdMoveFirst_Click()
    On Error GoTo Err
    
    RS.MoveFirst
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    cmdMoveFirst.Enabled = False
    mnuNavigate_MoveFirst.Enabled = False
    cmdMovePrevious.Enabled = False
    mnuNavigate_MovePrevious.Enabled = False
    cmdMoveLast.Enabled = True
    mnuNavigate_MoveLast.Enabled = True
    cmdMoveNext.Enabled = True
    mnuNavigate_MoveNext.Enabled = True
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
            cmdMoveLast.Enabled = True
            mnuNavigate_MoveLast.Enabled = True
            cmdMoveNext.Enabled = True
            mnuNavigate_MoveNext.Enabled = True
        Else
            cmdMoveFirst.Enabled = False
            mnuNavigate_MoveFirst.Enabled = False
            cmdMovePrevious.Enabled = False
            mnuNavigate_MovePrevious.Enabled = False
            cmdMoveLast.Enabled = True
            mnuNavigate_MoveLast.Enabled = True
            cmdMoveNext.Enabled = True
            mnuNavigate_MoveNext.Enabled = True
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
            mnuNavigate_MoveFirst.Enabled = True
            cmdMovePrevious.Enabled = True
            mnuNavigate_MovePrevious.Enabled = True
        Else
            cmdMoveFirst.Enabled = True
            mnuNavigate_MoveFirst.Enabled = True
            cmdMovePrevious.Enabled = True
            mnuNavigate_MovePrevious.Enabled = True
            cmdMoveLast.Enabled = False
            mnuNavigate_MoveLast.Enabled = False
            cmdMoveNext.Enabled = False
            mnuNavigate_MoveNext.Enabled = False
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
    mnuNavigate_MoveFirst.Enabled = True
    cmdMovePrevious.Enabled = True
    mnuNavigate_MovePrevious.Enabled = True
    cmdMoveLast.Enabled = False
    mnuNavigate_MoveLast.Enabled = False
    cmdMoveNext.Enabled = False
    mnuNavigate_MoveNext.Enabled = False
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub cmdAddBookmark_Click()
    On Error GoTo Err
        
    User_Input = InputBox("What do you want to label the bookmark?", "Add Bookmark", "")
    If User_Input <> "" Then
        ReDim Preserve BookmarkVals(UBound(BookmarkVals) + 1)
        lstBookmark.AddItem User_Input
        BookmarkVals(UBound(BookmarkVals)) = RS.Bookmark
    End If

    lstBookmark.TabStop = True
    lstBookmark.ListIndex = 0
    mnuBookmark_GetBookmark.Enabled = True
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub lstBookmark_DblClick()
    On Error GoTo Err
    
    RS.Bookmark = BookmarkVals(lstBookmark.ListIndex + 2)
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    cmdMoveFirst.Enabled = True
    mnuNavigate_MoveFirst.Enabled = True
    cmdMovePrevious.Enabled = True
    mnuNavigate_MovePrevious.Enabled = True
    cmdMoveNext.Enabled = True
    mnuNavigate_MoveNext.Enabled = True
    cmdMoveLast.Enabled = True
    mnuNavigate_MoveLast.Enabled = True
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub cmdEdit_Click()
    On Error Resume Next
    
    ' Set behavior of user interface
    DisableButtons
    DisableMenus
    cmdCancel.Enabled = True
    mnuEdit_Cancel.Enabled = True
    cmdUpdate.Enabled = True
    mnuEdit_Update.Enabled = True
    LockTextBoxes False

End Sub

Private Sub cmdAdd_Click()
    On Error GoTo Err
    
    RS.AddNew
    
    ' Set behavior of user interface
    ClearTextBoxes
    DisableButtons
    DisableMenus
    cmdCancel.Enabled = True
    mnuEdit_Cancel.Enabled = True
    cmdUpdate.Enabled = True
    mnuEdit_Update.Enabled = True
    LockTextBoxes False
    For x = 0 To 8
        tbData(x).TabStop = True
    Next x
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
    mnuEdit_Cancel.Enabled = False
    cmdUpdate.Enabled = False
    mnuEdit_Update.Enabled = False
    cmdOpenRS.Enabled = False
    mnuFile_OpenRS.Enabled = False
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    LockTextBoxes True
    For x = 0 To 8
        tbData(x).TabStop = False
    Next x
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
    
End Sub

Private Sub cmdUpdate_Click()
    On Error GoTo Err
    
    Columns = RS.Fields.Count
    If Columns > 9 Then Columns = 9
    For x = 0 To Columns - 1
        RS(x) = LTrim(tbData(x))
    Next
    
    ' Note: If you open a file with locktype adLockBatchOptimistic (only valid for bookmarkable host files)
    '   then you must update with RS.UpdateBatch
    RS.Update
    
    ' Display a single recordset row (single host table record)
    DisplayRow
    
    ' Set behavior of user interface
    EnableButtons
    EnableMenus
    cmdCancel.Enabled = False
    mnuEdit_Cancel.Enabled = False
    cmdUpdate.Enabled = False
    mnuEdit_Update.Enabled = False
    cmdConnect.Enabled = False
    mnuFile_Connect.Enabled = False
    cmdOpenRS.Enabled = False
    mnuFile_OpenRS.Enabled = False
    
    LockTextBoxes True
    For x = 0 To 8
        tbData(x).TabStop = True
    Next x
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
        ' Note: If you open a file with locktype adLockBatchOptimistic (only valid for bookmarkable host files)
        '   then you must update with RS.UpdateBatch
        RS.Update
        RS.MoveFirst
        
        ' Display a single recordset row (single host table record)
        DisplayRow
    
        ' Set behavior of user interface
        cmdMoveNext.Enabled = True
        mnuNavigate_MoveNext.Enabled = True
        cmdMoveLast.Enabled = True
        mnuNavigate_MoveLast.Enabled = True
    End If
    Exit Sub

Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"
        
End Sub

Private Sub mnuBookmark_AddBookmark_Click()
    On Error Resume Next
    
    cmdAddBookmark_Click

End Sub

Private Sub mnuBookmark_GetBookmark_Click()
    On Error Resume Next
    
    lstBookmark_DblClick

End Sub

Private Sub mnuEdit_Add_Click()
    On Error Resume Next
    
    cmdAdd_Click
    
End Sub

Private Sub mnuEdit_Cancel_Click()
    On Error Resume Next
    
    cmdCancel_Click
    
End Sub

Private Sub mnuEdit_Delete_Click()
    On Error Resume Next
    
    cmdDelete_Click
    
End Sub

Private Sub mnuEdit_Edit_Click()
    On Error Resume Next
    
    cmdEdit_Click
    
End Sub

Private Sub mnuEdit_Update_Click()
    On Error Resume Next
    
    cmdUpdate_Click
    
End Sub

Private Sub mnuFile_CloseRS_Click()
    On Error Resume Next
    
    cmdCloseRS_Click
    
End Sub

Private Sub mnuFile_Command_Click()
    On Error Resume Next
    
    cmdCommand_Click
    
End Sub

Private Sub mnuFile_Disconnect_Click()
    On Error Resume Next
        
    cmdDisconnect_Click
    
End Sub

Private Sub mnuFile_Exit_Click()
    On Error Resume Next
    
    Unload frmFormView
    
End Sub

Private Sub mnuFile_Connect_Click()
    On Error Resume Next
    
    cmdConnect_Click
    
End Sub

Private Sub mnuFile_OpenRS_Click()
    On Error Resume Next
    
    cmdOpenRS_Click

End Sub

Private Sub mnuHelp_About_Click()
    On Error Resume Next
    
    Load frmAbout
    frmAbout.Show
    
End Sub

Private Sub mnuNavigate_Filter_Click()
    On Error Resume Next
    
    cmdFilter_Click

End Sub

Private Sub mnuNavigate_Find_Click()
    On Error Resume Next
    
    cmdFind_Click

End Sub

Private Sub mnuNavigate_FindNext_Click()
    On Error Resume Next

    cmdFindNext_Click
    
End Sub

Private Sub mnuNavigate_MoveFirst_Click()
    On Error Resume Next
    
    cmdMoveFirst_Click
    
End Sub

Private Sub mnuNavigate_MoveLast_Click()
    On Error Resume Next
    
    cmdMoveLast_Click
    
End Sub

Private Sub mnuNavigate_MoveNext_Click()
    On Error Resume Next
    
    cmdMoveNext_Click

End Sub

Private Sub mnuNavigate_MovePrevious_Click()
    On Error Resume Next
    
    cmdMovePrevious_Click

End Sub


