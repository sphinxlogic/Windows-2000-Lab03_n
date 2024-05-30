VERSION 5.00
Begin VB.Form BizCard 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Business Card"
   ClientHeight    =   4080
   ClientLeft      =   7425
   ClientTop       =   5805
   ClientWidth     =   4620
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   4080
   ScaleWidth      =   4620
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton Close 
      Caption         =   "Close"
      Default         =   -1  'True
      Height          =   375
      Left            =   3240
      TabIndex        =   14
      Top             =   3480
      Width           =   1215
   End
   Begin VB.TextBox BizName 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   6
      Top             =   120
      Width           =   3495
   End
   Begin VB.TextBox Title 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   5
      Top             =   600
      Width           =   3495
   End
   Begin VB.TextBox Company 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   4
      Top             =   1080
      Width           =   3495
   End
   Begin VB.TextBox Address 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   3
      Top             =   1560
      Width           =   3495
   End
   Begin VB.TextBox Phone 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   2
      Top             =   2040
      Width           =   3495
   End
   Begin VB.TextBox Fax 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   1
      Top             =   2520
      Width           =   3495
   End
   Begin VB.TextBox EMail 
      Enabled         =   0   'False
      Height          =   300
      Left            =   960
      TabIndex        =   0
      Top             =   3000
      Width           =   3495
   End
   Begin VB.Label Label1 
      Caption         =   "&Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   120
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "&Title:"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   600
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "&Company:"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   1080
      Width           =   855
   End
   Begin VB.Label Label4 
      Caption         =   "&Address:"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   1560
      Width           =   855
   End
   Begin VB.Label Label5 
      Caption         =   "&Phone:"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   2040
      Width           =   855
   End
   Begin VB.Label Label6 
      Caption         =   "&Fax:"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   2520
      Width           =   855
   End
   Begin VB.Label Label7 
      Caption         =   "&E-Mail:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   3000
      Width           =   855
   End
End
Attribute VB_Name = "BizCard"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'****************************************************************************
'
'  Module:     VBCARD.EXE
'  File:       BizCard.frm
'  Content:    Implementation of the BizCard form
'
'  Copyright (c) Microsoft Corporation 1995-1997
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'****************************************************************************

Option Explicit

Private Sub Close_Click()
    Unload BizCard
End Sub

Private Sub Form_Load()
    Dim Card As BizCardInfo

    Card = GetActiveCard
    BizName.text = Card.Name
    Title.text = Card.Title
    Company.text = Card.Company
    Address.text = Card.Address
    Phone.text = Card.Phone
    Fax.text = Card.Fax
    EMail.text = Card.EMail
End Sub

