VERSION 5.00
Begin VB.Form fConnect 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Connect to Server"
   ClientHeight    =   2145
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5400
   Icon            =   "fConnect.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2145
   ScaleWidth      =   5400
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton bCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   350
      Left            =   4080
      TabIndex        =   2
      Top             =   1680
      Width           =   1095
   End
   Begin VB.CommandButton bOk 
      Caption         =   "OK"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   350
      Left            =   2880
      TabIndex        =   1
      Top             =   1680
      Width           =   1095
   End
   Begin VB.TextBox tServerName 
      Height          =   300
      Left            =   1080
      TabIndex        =   0
      Top             =   960
      Width           =   4095
   End
   Begin VB.Label Label1 
      Caption         =   "Enter the computer you would like to connect to:"
      Height          =   615
      Left            =   960
      TabIndex        =   4
      Top             =   240
      Width           =   4335
   End
   Begin VB.Image Image1 
      Height          =   480
      Left            =   240
      Picture         =   "fConnect.frx":0442
      Top             =   240
      Width           =   480
   End
   Begin VB.Label Label2 
      Caption         =   "Computer:"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1005
      Width           =   735
   End
End
Attribute VB_Name = "fConnect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub bCancel_Click()
    tServerName.Text = ""
    Me.Hide
End Sub


Private Sub bOk_Click()
    Me.Hide
End Sub

Private Sub Form_Unload(Cancel As Integer)
    tServerName.Text = ""
End Sub


Private Sub tServerName_Change()
    If Len(tServerName.Text) > 0 Then
        bOk.Enabled = True
    Else
        bOk.Enabled = False
    End If
End Sub


