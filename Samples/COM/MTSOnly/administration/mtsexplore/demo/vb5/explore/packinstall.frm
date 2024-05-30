VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form PackInstall 
   Caption         =   "Install Package"
   ClientHeight    =   3885
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5940
   LinkTopic       =   "Form2"
   MinButton       =   0   'False
   ScaleHeight     =   3885
   ScaleWidth      =   5940
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   5400
      Top             =   3360
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
   End
   Begin VB.CommandButton BrowseInstall 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   4680
      TabIndex        =   8
      Top             =   1440
      Width           =   1095
   End
   Begin VB.CommandButton BrowsePDF 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   4680
      TabIndex        =   7
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3480
      TabIndex        =   6
      Top             =   3480
      Width           =   1335
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   1200
      TabIndex        =   5
      Top             =   3480
      Width           =   1215
   End
   Begin VB.CheckBox AddUsersChk 
      Caption         =   "Add users to roles"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   2640
      Width           =   2895
   End
   Begin VB.TextBox InstallDir 
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   1920
      Width           =   5535
   End
   Begin VB.TextBox packageFile 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   5535
   End
   Begin VB.Label Label2 
      Caption         =   "Install Dir"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Package File:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   1815
   End
End
Attribute VB_Name = "PackInstall"
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

Private Sub BrowsePDF_Click()
    ' Set CancelError is True
    CommonDialog1.CancelError = True
    On Error GoTo ErrHandler
    ' Set flags
    CommonDialog1.Flags = cdlOFNHideReadOnly
    ' Set filters
    CommonDialog1.Filter = "All Files (*.*)|*.*|Package Files" & _
    "(*.pak)|*.pak"
    ' Specify default filter
    CommonDialog1.FilterIndex = 1
    ' Display the Open dialog box
    CommonDialog1.ShowOpen
    ' Display name of selected file
    packageFile.Text = CommonDialog1.filename
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
    Dim installOptions As Integer
    installOptions = 0
    If AddUsersChk.Value = 1 Then
        installOptions = installOptions + mtsInstallUsers
    End If
    
    Dim util As Object
    Set util = Explorer.currentColl.GetUtilInterface
    util.InstallPackage packageFile.Text, InstallDir.Text, installOptions
    
    Explorer.MousePointer = 0
    Exit Sub
err:
    MsgBox "Package install failed with error code " + Explorer.mapError(err.Number)
    
    Explorer.MousePointer = 0
    

End Sub
