VERSION 5.00
Begin VB.Form frmConnect 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "SMS Login"
   ClientHeight    =   2190
   ClientLeft      =   4980
   ClientTop       =   4185
   ClientWidth     =   4140
   Icon            =   "frmConnect.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2190
   ScaleWidth      =   4140
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox picLogo 
      BorderStyle     =   0  'None
      Height          =   2175
      Left            =   3060
      Picture         =   "frmConnect.frx":014A
      ScaleHeight     =   145
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   76
      TabIndex        =   12
      TabStop         =   0   'False
      Top             =   0
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   315
      Left            =   1620
      TabIndex        =   11
      Top             =   1800
      Width           =   855
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   315
      Left            =   600
      TabIndex        =   10
      Top             =   1800
      Width           =   855
   End
   Begin VB.Frame fraCredentials 
      Caption         =   "Credentials"
      Height          =   975
      Left            =   60
      TabIndex        =   5
      Top             =   720
      Width           =   2955
      Begin VB.TextBox txtPassword 
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   960
         PasswordChar    =   "*"
         TabIndex        =   9
         Top             =   540
         Width           =   1875
      End
      Begin VB.TextBox txtUser 
         Height          =   285
         Left            =   960
         TabIndex        =   7
         Top             =   240
         Width           =   1875
      End
      Begin VB.Label lblPassword 
         AutoSize        =   -1  'True
         Caption         =   "&Password:"
         Height          =   195
         Left            =   120
         TabIndex        =   8
         Top             =   600
         Width           =   735
      End
      Begin VB.Label lblUser 
         AutoSize        =   -1  'True
         Caption         =   "&User:"
         Height          =   195
         Left            =   120
         TabIndex        =   6
         Top             =   300
         Width           =   375
      End
   End
   Begin VB.Frame fraServer 
      Caption         =   "SMS Site"
      Height          =   675
      Left            =   60
      TabIndex        =   0
      Top             =   0
      Width           =   2955
      Begin VB.TextBox txtSitecode 
         Height          =   285
         Left            =   2400
         MaxLength       =   3
         TabIndex        =   4
         Top             =   240
         Width           =   435
      End
      Begin VB.TextBox txtServer 
         Height          =   285
         Left            =   720
         TabIndex        =   2
         Top             =   240
         Width           =   915
      End
      Begin VB.Label lblSitecode 
         AutoSize        =   -1  'True
         Caption         =   "Site&code:"
         Height          =   195
         Left            =   1680
         TabIndex        =   3
         Top             =   300
         Width           =   675
      End
      Begin VB.Label lblServer 
         AutoSize        =   -1  'True
         Caption         =   "&Server:"
         Height          =   195
         Left            =   120
         TabIndex        =   1
         Top             =   300
         Width           =   510
      End
   End
End
Attribute VB_Name = "frmConnect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
' frmConnect.frm
'
' Set a public variable based on whether the user presses
' OK or Cancel.
'
'************************************************************

Option Explicit

'Indicates if the connect operation was canceled by the user.
Public Canceled As Boolean


'Cancel button was pushed
Private Sub cmdCancel_Click()
    
    'Set the canceled flag to TRUE, hide the form.
    Canceled = True
    Me.Hide
    
End Sub


'OK button was pushed
Private Sub cmdOK_Click()
    
    'Set the canceled flag to FALSE, hide the form.
    Canceled = False
    Me.Hide
    
End Sub

Private Sub Form_Initialize()
    Canceled = True
End Sub

'An attempt was made to unload the form
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    
    'If the form is being unloaded because the controlbox close was pressed, process it like a cancel.
    If UnloadMode = 1 Then
        cmdCancel_Click
        Cancel = 1
    End If
    
End Sub

