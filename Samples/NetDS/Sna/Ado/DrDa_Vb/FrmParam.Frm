VERSION 5.00
Begin VB.Form frmParam 
   Caption         =   "Command with Parameters"
   ClientHeight    =   6300
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8415
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6300
   ScaleWidth      =   8415
   StartUpPosition =   1  'CenterOwner
   Begin VB.CheckBox cbEnableParam 
      Caption         =   "Enable Parameter"
      Height          =   255
      Left            =   4320
      TabIndex        =   26
      Top             =   1560
      Width           =   1695
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   6960
      TabIndex        =   25
      Top             =   240
      Width           =   1335
   End
   Begin VB.CommandButton cmdExecute 
      Caption         =   "Execute"
      Height          =   375
      Left            =   5520
      TabIndex        =   24
      Top             =   240
      Width           =   1335
   End
   Begin VB.Frame fmParam1 
      Caption         =   "Parameter #1"
      Height          =   4215
      Left            =   120
      TabIndex        =   13
      Top             =   1920
      Width           =   3975
      Begin VB.ComboBox cboDirection1 
         Height          =   315
         ItemData        =   "frmParam.frx":0000
         Left            =   240
         List            =   "frmParam.frx":000D
         Style           =   2  'Dropdown List
         TabIndex        =   18
         Top             =   2160
         Width           =   3495
      End
      Begin VB.ComboBox cboType1 
         Height          =   315
         ItemData        =   "frmParam.frx":002E
         Left            =   240
         List            =   "frmParam.frx":0050
         Style           =   2  'Dropdown List
         TabIndex        =   17
         Top             =   1440
         Width           =   3495
      End
      Begin VB.TextBox tbValue1 
         Height          =   315
         Left            =   240
         TabIndex        =   16
         Top             =   3600
         Width           =   3495
      End
      Begin VB.TextBox tbSize1 
         Height          =   315
         Left            =   240
         TabIndex        =   15
         Top             =   2880
         Width           =   3495
      End
      Begin VB.TextBox tbName1 
         Height          =   315
         Left            =   240
         TabIndex        =   14
         Top             =   720
         Width           =   3495
      End
      Begin VB.Label lblValue1 
         AutoSize        =   -1  'True
         Caption         =   "Value:"
         Height          =   195
         Left            =   360
         TabIndex        =   23
         Top             =   3360
         Width           =   450
      End
      Begin VB.Label lblSize1 
         AutoSize        =   -1  'True
         Caption         =   "Size:"
         Height          =   195
         Left            =   360
         TabIndex        =   22
         Top             =   2640
         Width           =   345
      End
      Begin VB.Label lblDirection1 
         AutoSize        =   -1  'True
         Caption         =   "Direction:"
         Height          =   195
         Left            =   360
         TabIndex        =   21
         Top             =   1920
         Width           =   675
      End
      Begin VB.Label lblType1 
         AutoSize        =   -1  'True
         Caption         =   "Type:"
         Height          =   195
         Left            =   360
         TabIndex        =   20
         Top             =   1200
         Width           =   405
      End
      Begin VB.Label lblName1 
         AutoSize        =   -1  'True
         Caption         =   "Name:"
         Height          =   195
         Left            =   360
         TabIndex        =   19
         Top             =   480
         Width           =   465
      End
   End
   Begin VB.Frame fmParam2 
      Caption         =   "Parameter #2"
      Enabled         =   0   'False
      Height          =   4215
      Left            =   4320
      TabIndex        =   2
      Top             =   1920
      Width           =   3975
      Begin VB.ComboBox cboDirection2 
         Enabled         =   0   'False
         Height          =   315
         ItemData        =   "frmParam.frx":00C0
         Left            =   240
         List            =   "frmParam.frx":00CD
         Style           =   2  'Dropdown List
         TabIndex        =   7
         Top             =   2160
         Width           =   3495
      End
      Begin VB.ComboBox cboType2 
         Enabled         =   0   'False
         Height          =   315
         ItemData        =   "frmParam.frx":00EE
         Left            =   240
         List            =   "frmParam.frx":0110
         Style           =   2  'Dropdown List
         TabIndex        =   6
         Top             =   1440
         Width           =   3495
      End
      Begin VB.TextBox tbValue2 
         Enabled         =   0   'False
         Height          =   315
         Left            =   240
         TabIndex        =   5
         Top             =   3600
         Width           =   3495
      End
      Begin VB.TextBox tbSize2 
         Enabled         =   0   'False
         Height          =   315
         Left            =   240
         TabIndex        =   4
         Top             =   2880
         Width           =   3495
      End
      Begin VB.TextBox tbName2 
         Enabled         =   0   'False
         Height          =   315
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   3495
      End
      Begin VB.Label lblValue2 
         AutoSize        =   -1  'True
         Caption         =   "Value:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   360
         TabIndex        =   12
         Top             =   3360
         Width           =   450
      End
      Begin VB.Label lblSize2 
         AutoSize        =   -1  'True
         Caption         =   "Size:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   360
         TabIndex        =   11
         Top             =   2640
         Width           =   345
      End
      Begin VB.Label lblDirection2 
         AutoSize        =   -1  'True
         Caption         =   "Direction:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   360
         TabIndex        =   10
         Top             =   1920
         Width           =   675
      End
      Begin VB.Label lblType2 
         AutoSize        =   -1  'True
         Caption         =   "Type:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   360
         TabIndex        =   9
         Top             =   1200
         Width           =   405
      End
      Begin VB.Label lblName2 
         AutoSize        =   -1  'True
         Caption         =   "Name:"
         Enabled         =   0   'False
         Height          =   195
         Left            =   360
         TabIndex        =   8
         Top             =   480
         Width           =   465
      End
   End
   Begin VB.TextBox tbCommand 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Text            =   "SELECT * FROM PUBS.AUTHORS WHERE AU_LNAME = ?"
      Top             =   960
      Width           =   8175
   End
   Begin VB.Label lblCommand 
      Caption         =   "Command Text:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   720
      Width           =   1575
   End
End
Attribute VB_Name = "frmParam"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cbEnableParam_Click()
    If cbEnableParam.Value = Checked Then
        lblName2.Enabled = True
        tbName2.Enabled = True
        lblType2.Enabled = True
        cboType2.Enabled = True
        lblDirection2.Enabled = True
        cboDirection2.Enabled = True
        lblSize2.Enabled = True
        tbSize2.Enabled = True
        lblValue2.Enabled = True
        tbValue2.Enabled = True
        fmParam2.Enabled = True
    Else
        lblName2.Enabled = False
        tbName2.Enabled = False
        lblType2.Enabled = False
        cboType2.Enabled = False
        lblDirection2.Enabled = False
        cboDirection2.Enabled = False
        lblSize2.Enabled = False
        tbSize2.Enabled = False
        lblValue2.Enabled = False
        tbValue2.Enabled = False
        fmParam2.Enabled = False
    End If
End Sub

Private Sub cmdCancel_Click()
    Me.Hide
End Sub

Private Sub cmdExecute_Click()
Dim Cmd As New ADODB.Command
Dim Param1 As New ADODB.Parameter
Dim Param2 As New ADODB.Parameter

    On Error GoTo Err

    Cmd.Prepared = True
    Cmd.CommandText = Trim(tbCommand)
    Cmd.CommandType = adCmdText
    Set Cmd.ActiveConnection = frmFormView.Conn
    
    Param1.Direction = cboDirection1.ItemData(cboDirection1.ListIndex)
    Param1.Type = cboType1.ItemData(cboType1.ListIndex)
    Param1.Size = CInt(tbSize1.Text)
    
    Select Case Param1.Type
    Case adChar
        Param1.Value = tbValue1.Text
    Case adSmallInt
        Param1.Value = CInt(tbValue1.Text)
    Case adInteger
        Param1.Value = CInt(tbValue1.Text)
    Case adSingle
        Param1.Value = CSng(tbValue1.Text)
    Case adDouble
        Param1.Value = CDbl(tbValue1.Text)
    Case adNumeric
        Param1.Value = CDec(tbValue1.Text)
    Case adDecimal
        Param1.Value = CDec(tbValue1.Text)
    Case adDBDate
        Param1.Value = CDate(tbValue1.Text)
    Case adDBTime
        Param1.Value = CDate(tbValue1.Text)
    Case adDBTimeStamp
        Param1.Value = CDate(tbValue1.Text)
    Case Else
        Param1.Value = tbValue1.Text
    End Select

    Cmd.Parameters.Append Param1
    
    If cbEnableParam.Value = Checked Then
        Param2.Direction = cboDirection2.ItemData(cboDirection2.ListIndex)
        Param2.Type = cboType2.ItemData(cboType2.ListIndex)
        Param2.Size = CInt(tbSize2.Text)
        
        Select Case Param2.Type
        Case adChar
            Param2.Value = tbValue2.Text
        Case adSmallInt
            Param2.Value = CInt(tbValue2.Text)
        Case adInteger
            Param2.Value = CInt(tbValue2.Text)
        Case adSingle
            Param2.Value = CSng(tbValue2.Text)
        Case adDouble
            Param2.Value = CDbl(tbValue2.Text)
        Case adNumeric
            Param2.Value = CDec(tbValue2.Text)
        Case adDecimal
            Param2.Value = CDec(tbValue2.Text)
        Case adDBDate
            Param2.Value = CDate(tbValue2.Text)
        Case adDBTime
            Param2.Value = CDate(tbValue2.Text)
        Case adDBTimeStamp
            Param2.Value = CDate(tbValue2.Text)
        Case Else
            Param2.Value = tbValue2.Text
        End Select
    
        Cmd.Parameters.Append Param2
    
    End If
    
    Set frmFormView.RS = Cmd.Execute
    
    Me.Hide
    
    Exit Sub
    
Err:
    MsgBox Error, vbExclamation, "Microsoft ADO Consumer Sample"

End Sub

Private Sub Form_Load()
    cboType1.ItemData(0) = adChar
    cboType1.ItemData(1) = adSmallInt
    cboType1.ItemData(2) = adInteger
    cboType1.ItemData(3) = adSingle
    cboType1.ItemData(4) = adDouble
    cboType1.ItemData(5) = adNumeric
    cboType1.ItemData(6) = adDecimal
    cboType1.ItemData(7) = adDBDate
    cboType1.ItemData(8) = adDBTime
    cboType1.ItemData(9) = adDBTimeStamp
    cboType1.ListIndex = 0
    
    cboType2.ItemData(0) = adChar
    cboType2.ItemData(1) = adSmallInt
    cboType2.ItemData(2) = adInteger
    cboType2.ItemData(3) = adSingle
    cboType2.ItemData(4) = adDouble
    cboType2.ItemData(5) = adNumeric
    cboType2.ItemData(6) = adDecimal
    cboType2.ItemData(7) = adDBDate
    cboType2.ItemData(8) = adDBTime
    cboType2.ItemData(9) = adDBTimeStamp
    cboType2.ListIndex = 0
    
    cboDirection1.ItemData(0) = adParamInput
    cboDirection1.ItemData(1) = adParamOutput
    cboDirection1.ItemData(2) = adParamInputOutput
    cboDirection1.ListIndex = 0
    
    cboDirection2.ItemData(0) = adParamInput
    cboDirection2.ItemData(1) = adParamOutput
    cboDirection2.ItemData(2) = adParamInputOutput
    cboDirection2.ListIndex = 0
    
End Sub
