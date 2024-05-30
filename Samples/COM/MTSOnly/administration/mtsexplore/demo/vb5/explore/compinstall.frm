VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form CompInstall 
   Caption         =   "Install Component"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5835
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   5835
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4680
      Top             =   1440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
   End
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   495
      Left            =   3120
      TabIndex        =   4
      Top             =   2520
      Width           =   1455
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   840
      TabIndex        =   3
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CommandButton BrowseBtn 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   3960
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.TextBox DLLFile 
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   600
      Width           =   4935
   End
   Begin VB.Label Label1 
      Caption         =   "DLL:"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   240
      Width           =   1455
   End
End
Attribute VB_Name = "CompInstall"
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

Private Sub BrowseBtn_Click()
    ' Set CancelErrPor is True
    CommonDialog1.CancelError = True
    On Error GoTo ErrHandler
    ' Set flags
    CommonDialog1.Flags = cdlOFNHideReadOnly
    ' Set filters
    CommonDialog1.Filter = "All Files (*.*)|*.*|DLLs" & _
    "(*.dll)|*.dll"
    ' Specify default filter
    CommonDialog1.FilterIndex = 1
    ' Display the Open dialog box
    CommonDialog1.ShowOpen
    ' Display name of selected file
    DLLFile.Text = CommonDialog1.filename
    Exit Sub
    
ErrHandler:
    'User pressed the Cancel button
    Exit Sub

End Sub

Private Sub Cancel_Click()
    Hide
End Sub

Private Sub OK_Click()
    Hide
    Explorer.MousePointer = 11
    On Error GoTo err

    Dim util As Object
    Set util = Explorer.currentColl.GetUtilInterface
    util.InstallComponent DLLFile.Text, "", ""
    Explorer.MousePointer = 0
    Exit Sub
err:
    MsgBox "Component install failed with error code " + Explorer.mapError(err.Number)
    Explorer.MousePointer = 0

End Sub


