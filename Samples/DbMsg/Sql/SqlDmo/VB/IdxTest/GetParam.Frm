VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmIdxTestGetParams 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Enter parameter values for..."
   ClientHeight    =   2805
   ClientLeft      =   45
   ClientTop       =   345
   ClientWidth     =   6225
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2805
   ScaleWidth      =   6225
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   3
      Top             =   660
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.Frame frameParameters 
      Caption         =   "Parameters"
      Height          =   1995
      Left            =   180
      TabIndex        =   1
      Top             =   600
      Width           =   4275
      Begin MSFlexGridLib.MSFlexGrid gridParameters 
         Height          =   1575
         Left            =   180
         TabIndex        =   4
         Top             =   240
         Width           =   3915
         _ExtentX        =   6906
         _ExtentY        =   2778
         _Version        =   65541
         Rows            =   10
         Cols            =   3
         FixedCols       =   2
      End
   End
   Begin VB.Label lblSProcName 
      Height          =   255
      Left            =   180
      TabIndex        =   0
      Top             =   180
      Width           =   4275
   End
End
Attribute VB_Name = "frmIdxTestGetParams"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public bOK As Boolean
Private Sub cmdCancel_Click()
    bOK = False
    frmIdxTestGetParams.Hide
End Sub
Private Sub cmdOK_Click()
    bOK = True
    frmIdxTestGetParams.Hide
End Sub
Private Sub Form_Load()
    gridParameters.ColWidth(0) = 1200
    gridParameters.ColWidth(1) = 1200
    gridParameters.ColWidth(2) = 1300
    
    gridParameters.Row = 0
    gridParameters.Col = 0
    gridParameters.Text = "Parameter"
    gridParameters.Col = 1
    gridParameters.Text = "Data type"
    gridParameters.Col = 2
    gridParameters.Text = "Value"
End Sub
Private Sub gridParameters_KeyPress(KeyAscii As Integer)
    If Chr(KeyAscii) >= "-" And Chr(KeyAscii) <= "z" Then
        Dim strCurrent As String
        strCurrent = gridParameters.Text
        gridParameters.Text = strCurrent + Chr(KeyAscii)
    End If
End Sub
Private Sub gridParameters_KeyUp(KeyCode As Integer, Shift As Integer)
    If KeyCode = vbKeySpace Then
        Dim strCurrent As String
        strCurrent = gridParameters.Text
        gridParameters.Text = strCurrent + " "
    End If
End Sub
