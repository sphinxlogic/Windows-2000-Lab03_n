VERSION 5.00
Begin VB.Form MainCompInstall 
   Caption         =   "Install"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ImportComponentsBtn 
      Caption         =   "Import Components..."
      Height          =   495
      Left            =   600
      TabIndex        =   1
      Top             =   1800
      Width           =   2895
   End
   Begin VB.CommandButton InstallComponentsBtn 
      Caption         =   "Install Components..."
      Height          =   495
      Left            =   600
      TabIndex        =   0
      Top             =   480
      Width           =   2895
   End
End
Attribute VB_Name = "MainCompInstall"
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

Private Sub ImportComponentsBtn_Click()
    MousePointer = 11
    CompImport.Show 1, Me
    MousePointer = 0
    Hide
End Sub

Private Sub InstallComponentsBtn_Click()
    MousePointer = 11
    CompInstall.Show 1, Me
    MousePointer = 0
    Hide
End Sub
