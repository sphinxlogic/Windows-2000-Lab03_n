VERSION 5.00
Begin VB.Form LogonStatus 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   975
   ClientLeft      =   4035
   ClientTop       =   1875
   ClientWidth     =   6000
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   975
   ScaleWidth      =   6000
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.Timer tmrStatus 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   3660
      Top             =   120
   End
   Begin VB.Label lblStatus 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Message"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   900
      TabIndex        =   0
      Top             =   360
      Width           =   1050
   End
   Begin VB.Image imgTimer 
      Height          =   480
      Left            =   180
      Picture         =   "Status.frx":0000
      Top             =   240
      Width           =   480
   End
End
Attribute VB_Name = "LogonStatus"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'***********************************************************************
'  Copyright (c) by Microsoft 1998
'
'  STATUS
'
' Overview: The Status Form is simply a popup form that stays visible
' while the application is trying to logon.
'
' It uses a timer to make sure the form becomes visible before
' trying to logon.
'-----------------------------------------------------------

Option Explicit

Private Initializing As Boolean

Private Sub Form_Load()
  Initializing = True
  lblStatus.Caption = "Logging onto Exchange Server - Please wait..."
  lblStatus.Refresh
  Me.Width = lblStatus.Left + lblStatus.Width + 400
  tmrStatus.Enabled = True
End Sub



Private Sub tmrStatus_Timer()
  Dim iVar As Integer
  
  tmrStatus.Enabled = False
  If Not AgentMap.IsLoggedOn Then
     iVar = AgentMap.Logon(True, "", False)
     'Note: Since error messaging is turned on in the
     'class we don't trap it here. Also, if an error
     'occured during logon in the class the class.IsLoggedOn
     'will still be false.
  End If
  Unload Me
End Sub
