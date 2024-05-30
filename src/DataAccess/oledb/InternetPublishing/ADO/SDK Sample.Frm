VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "ADO SDK Sample"
   ClientHeight    =   4875
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4215
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4875
   ScaleWidth      =   4215
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdClear 
      Caption         =   "&Clear Output"
      Height          =   375
      Left            =   2760
      TabIndex        =   12
      Top             =   2160
      Width           =   1335
   End
   Begin VB.TextBox txtOutput 
      Height          =   2175
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   11
      TabStop         =   0   'False
      Top             =   2640
      Width           =   3975
   End
   Begin VB.CommandButton cmdExecute 
      Caption         =   "&Execute"
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   2160
      Width           =   1335
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   1320
      MaxLength       =   256
      PasswordChar    =   "*"
      TabIndex        =   9
      Top             =   1800
      Width           =   2775
   End
   Begin VB.TextBox txtUsername 
      Height          =   285
      Left            =   1320
      MaxLength       =   256
      TabIndex        =   7
      Top             =   1440
      Width           =   2775
   End
   Begin VB.TextBox txtFileLoc 
      Height          =   285
      Left            =   1320
      MaxLength       =   256
      TabIndex        =   5
      Text            =   "c:\"
      Top             =   960
      Width           =   2775
   End
   Begin VB.TextBox txtURL 
      Height          =   285
      Left            =   1320
      MaxLength       =   256
      TabIndex        =   3
      Text            =   "http://"
      Top             =   600
      Width           =   2775
   End
   Begin VB.ComboBox cmbMethod 
      Height          =   315
      Left            =   1320
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   120
      Width           =   2775
   End
   Begin VB.Label lblMethod 
      Caption         =   "&Method"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label lblFileLocation 
      Caption         =   "&File Location"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   1095
   End
   Begin VB.Label lblURL 
      Caption         =   "U&RL"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   1095
   End
   Begin VB.Label lblPassword 
      Caption         =   "&Password"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1800
      Width           =   1095
   End
   Begin VB.Label lblUsername 
      Caption         =   "&Username"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   1440
      Width           =   1095
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'global constants
Const METHOD_DOWNLOAD As Integer = 0
Const METHOD_ENUMERATE As Integer = 1
Const METHOD_UPLOAD As Integer = 2

' set up the combo list and init all globals
Private Sub Form_Load()
    ' add the method names to the list box
    cmbMethod.AddItem "Download", 0
    cmbMethod.AddItem "Enumerate", 1
    cmbMethod.AddItem "Upload", 2
    
    ' show the default method
    cmbMethod.Text = "Download"

End Sub

' do the magic
Private Sub cmdExecute_Click()
    Dim rc As Long              ' catch the return codes
    
    Select Case cmbMethod.ListIndex
        Case METHOD_DOWNLOAD
            txtOutput.Text = txtOutput.Text + "Downloading " + txtURL.Text + vbCrLf
            If (txtUsername.Text <> "") Then
                rc = Download(txtURL.Text, txtFileLoc.Text, _
                              txtUsername.Text, txtPassword.Text)
            Else
                rc = Download(txtURL.Text, txtFileLoc.Text)
            End If
        Case METHOD_ENUMERATE
            txtOutput.Text = txtOutput.Text + "Enumerating " + txtURL.Text + vbCrLf
            If (txtUsername.Text <> "") Then
                rc = Enumerate(txtURL.Text, txtUsername.Text, txtPassword.Text)
            Else
                rc = Enumerate(txtURL.Text, txtFileLoc.Text)
            End If
        Case METHOD_UPLOAD
            txtOutput.Text = txtOutput.Text + "Uploading " + txtFileLoc.Text + vbCrLf
            If (txtUsername.Text <> "") Then
                rc = Upload(txtURL.Text, txtFileLoc.Text, _
                              txtUsername.Text, txtPassword.Text)
            Else
                rc = Upload(txtURL.Text, txtFileLoc.Text)
            End If
    End Select

    If (0 <> rc) Then
        txtOutput.Text = txtOutput.Text + "Errors occured: 0x" + Hex(rc) + vbCrLf
    Else
        txtOutput.Text = txtOutput.Text + "Success" + vbCrLf
    End If

End Sub

Private Sub cmdClear_Click()
    txtOutput.Text = ""
End Sub


