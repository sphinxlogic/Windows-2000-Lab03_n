VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form PackageExport 
   Caption         =   "Export Package"
   ClientHeight    =   3765
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5355
   LinkTopic       =   "Form1"
   ScaleHeight     =   3765
   ScaleWidth      =   5355
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2520
      Top             =   3240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
   End
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3480
      TabIndex        =   9
      Top             =   3360
      Width           =   1455
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   480
      TabIndex        =   8
      Top             =   3360
      Width           =   1455
   End
   Begin VB.Frame Frame2 
      Caption         =   "Options"
      Height          =   855
      Left            =   120
      TabIndex        =   6
      Top             =   2280
      Width           =   5055
      Begin VB.CheckBox ExportUsersChk 
         Caption         =   "Export users in roles"
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Value           =   1  'Checked
         Width           =   3375
      End
   End
   Begin VB.CommandButton BrowseBtn 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   3720
      TabIndex        =   4
      Top             =   960
      Width           =   1335
   End
   Begin VB.TextBox PackageFile 
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   1440
      Width           =   4815
   End
   Begin VB.Frame Frame1 
      Caption         =   "To File"
      Height          =   1335
      Left            =   120
      TabIndex        =   5
      Top             =   720
      Width           =   5055
   End
   Begin VB.Label Label3 
      Caption         =   "To file:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   1335
   End
   Begin VB.Label PackageName 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   1
      Top             =   240
      Width           =   3375
   End
   Begin VB.Label Label1 
      Caption         =   "Export package:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1335
   End
End
Attribute VB_Name = "PackageExport"
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

Private Sub Form_Load()
    PackageName.Caption = Explorer.currentColl.Item(Explorer.ObjList.ListIndex).Name

End Sub

Private Sub OK_Click()
    Hide
    Explorer.MousePointer = 11
    On Error GoTo err
    Dim exportOptions As Integer
    exportOptions = 0
    If ExportUsersChk.Value = 1 Then
        exportOptions = exportOptions + mtsExportUsers
    End If
    
    Dim packageID As String
    packageID = Explorer.currentColl.Item(Explorer.ObjList.ListIndex).key
    
    Dim util As Object
    Set util = Explorer.currentColl.GetUtilInterface
    util.ExportPackage packageID, packageFile.Text, exportOptions
    
    MsgBox ("Package successfully exported.")
    
    Explorer.MousePointer = 0

    Exit Sub
err:
    MsgBox "Package export failed with error code " + Explorer.mapError(err.Number)
    Explorer.MousePointer = 0
End Sub


