VERSION 5.00
Begin VB.Form RemoteComp 
   Caption         =   "Pulll Remote Component"
   ClientHeight    =   3810
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5910
   LinkTopic       =   "Form1"
   ScaleHeight     =   3810
   ScaleWidth      =   5910
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   495
      Left            =   3480
      TabIndex        =   7
      Top             =   3240
      Width           =   1335
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   480
      TabIndex        =   6
      Top             =   3240
      Width           =   1335
   End
   Begin VB.TextBox progID 
      Height          =   285
      Left            =   1800
      TabIndex        =   5
      Top             =   2520
      Width           =   3375
   End
   Begin VB.TextBox Package 
      Height          =   285
      Left            =   1800
      TabIndex        =   3
      Top             =   1320
      Width           =   3255
   End
   Begin VB.TextBox Server 
      Height          =   285
      Left            =   1800
      TabIndex        =   1
      Top             =   240
      Width           =   3255
   End
   Begin VB.Label Label3 
      Caption         =   "Component progID:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   2520
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Package name:"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   1320
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "From Server:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "RemoteComp"
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

Private Sub OK_Click()
    Hide
    Explorer.MousePointer = 11
    On Error GoTo err

    Dim util As Object
    Set util = Explorer.currentColl.GetUtilInterface
    util.InstallRemoteComponentByName Server.Text, Package.Text, progID.Text
    
    Explorer.MousePointer = 0
    Exit Sub
    
err:
    MsgBox "Remote component install failed with error code " + Explorer.mapError(err.Number)
    Explorer.MousePointer = 0


End Sub


