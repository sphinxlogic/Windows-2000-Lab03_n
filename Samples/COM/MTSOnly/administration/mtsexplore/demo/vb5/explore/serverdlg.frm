VERSION 5.00
Begin VB.Form ServerDlg 
   Caption         =   "Connect"
   ClientHeight    =   3735
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3735
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2640
      TabIndex        =   6
      Top             =   3240
      Width           =   1455
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   480
      TabIndex        =   5
      Top             =   3240
      Width           =   1455
   End
   Begin VB.Frame Frame1 
      Caption         =   "Computer"
      Height          =   1935
      Left            =   360
      TabIndex        =   1
      Top             =   840
      Width           =   3855
      Begin VB.TextBox ServerName 
         Height          =   375
         Left            =   600
         TabIndex        =   4
         Top             =   1440
         Width           =   2775
      End
      Begin VB.OptionButton RemoteBtn 
         Caption         =   "A remote computer:"
         Height          =   375
         Left            =   360
         TabIndex        =   3
         Top             =   960
         Width           =   2655
      End
      Begin VB.OptionButton LocalBtn 
         Caption         =   "This computer"
         Height          =   255
         Left            =   360
         TabIndex        =   2
         Top             =   480
         Width           =   2655
      End
   End
   Begin VB.Label Label1 
      Caption         =   "What computer do you want to configure? "
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   360
      Width           =   3255
   End
End
Attribute VB_Name = "ServerDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'/******************************************************************************\
'********************************************************************************
' Explore Sample
'
'* This file is provided as part of the Microsoft Transaction Server
'* Software Development Kit
'*
'*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
'*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
'*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
'*PURPOSE.
'*
'* Copyright (C) 1997 Microsoft Corporation, All rights reserved
'********************************************************************************
'\******************************************************************************/

Private Sub Cancel_Click()
    Hide
End Sub

Private Sub LocalBtn_Click()
    EnableControls
End Sub

Private Sub OK_Click()
    If LocalBtn.Value = True Then
        Server = ""
        ServerDesc = "local"
    Else
        Server = ServerName.Text
        ServerDesc = Server
    End If
    Set Explorer.currentColl = Explorer.catalog.Connect(Server)
    Explorer.navigateTo Explorer.currentColl
    Explorer.ServerName.Caption = ServerDesc
    
    Hide
End Sub

Private Sub RemoteBtn_Click()
    EnableControls
End Sub
Private Sub EnableControls()
    If LocalBtn.Value = True Then
        ServerName.Enabled = False
    Else
        ServerName.Enabled = True
    End If
    
End Sub
