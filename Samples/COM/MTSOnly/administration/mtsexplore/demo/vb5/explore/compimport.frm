VERSION 5.00
Begin VB.Form CompImport 
   Caption         =   "Import Component"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   495
      Left            =   2760
      TabIndex        =   3
      Top             =   2280
      Width           =   1215
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   480
      TabIndex        =   2
      Top             =   2280
      Width           =   1335
   End
   Begin VB.TextBox ProgID 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   3975
   End
   Begin VB.Label Label1 
      Caption         =   "ProgID:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   1815
   End
End
Attribute VB_Name = "CompImport"
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
    util.ImportComponentByName progID.Text
    

    
    Explorer.MousePointer = 0
    Exit Sub
err:
    MsgBox "Component import failed with error code " + Explorer.mapError(err.Number)
    Explorer.MousePointer = 0

End Sub

