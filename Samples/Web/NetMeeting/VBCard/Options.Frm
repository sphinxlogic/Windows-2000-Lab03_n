VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form Options 
   Caption         =   "Options"
   ClientHeight    =   5640
   ClientLeft      =   7470
   ClientTop       =   2940
   ClientWidth     =   5025
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5640
   ScaleWidth      =   5025
   Begin VB.PictureBox Conference 
      BorderStyle     =   0  'None
      Height          =   4455
      Left            =   240
      ScaleHeight     =   4455
      ScaleWidth      =   4575
      TabIndex        =   21
      Top             =   480
      Width           =   4575
      Begin VB.Frame Frame1 
         Caption         =   "Call with:"
         Height          =   1215
         Left            =   120
         TabIndex        =   22
         Top             =   120
         Width           =   4335
         Begin VB.OptionButton ConfData 
            Caption         =   "&Data only"
            Height          =   255
            Left            =   240
            TabIndex        =   24
            Top             =   720
            Value           =   -1  'True
            Width           =   1575
         End
         Begin VB.OptionButton ConfAll 
            Caption         =   "&Voice and data"
            Height          =   255
            Left            =   240
            TabIndex        =   23
            Top             =   360
            Width           =   2055
         End
      End
   End
   Begin VB.PictureBox BizCard 
      BorderStyle     =   0  'None
      Height          =   4455
      Left            =   240
      ScaleHeight     =   4455
      ScaleWidth      =   4575
      TabIndex        =   3
      Top             =   480
      Width           =   4575
      Begin VB.TextBox Photo 
         Height          =   300
         Left            =   960
         TabIndex        =   12
         Top             =   3480
         Width           =   3495
      End
      Begin VB.TextBox EMail 
         Height          =   300
         Left            =   960
         TabIndex        =   11
         Top             =   3000
         Width           =   3495
      End
      Begin VB.TextBox Fax 
         Height          =   300
         Left            =   960
         TabIndex        =   10
         Top             =   2520
         Width           =   3495
      End
      Begin VB.TextBox Phone 
         Height          =   300
         Left            =   960
         TabIndex        =   9
         Top             =   2040
         Width           =   3495
      End
      Begin VB.TextBox Address 
         Height          =   300
         Left            =   960
         TabIndex        =   8
         Top             =   1560
         Width           =   3495
      End
      Begin VB.TextBox Company 
         Height          =   300
         Left            =   960
         TabIndex        =   7
         Top             =   1080
         Width           =   3495
      End
      Begin VB.TextBox Title 
         Height          =   300
         Left            =   960
         TabIndex        =   6
         Top             =   600
         Width           =   3495
      End
      Begin VB.TextBox BizName 
         Height          =   300
         Left            =   960
         TabIndex        =   5
         Top             =   120
         Width           =   3495
      End
      Begin VB.CommandButton Browse 
         Caption         =   "Browse..."
         Height          =   375
         Left            =   3240
         TabIndex        =   4
         Top             =   3960
         Width           =   1215
      End
      Begin VB.Label Label8 
         Caption         =   "P&hoto"
         Height          =   255
         Left            =   120
         TabIndex        =   20
         Top             =   3480
         Width           =   855
      End
      Begin VB.Label Label7 
         Caption         =   "&E-Mail:"
         Height          =   255
         Left            =   120
         TabIndex        =   19
         Top             =   3000
         Width           =   855
      End
      Begin VB.Label Label6 
         Caption         =   "&Fax:"
         Height          =   255
         Left            =   120
         TabIndex        =   18
         Top             =   2520
         Width           =   855
      End
      Begin VB.Label Label5 
         Caption         =   "&Phone:"
         Height          =   255
         Left            =   120
         TabIndex        =   17
         Top             =   2040
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "&Address:"
         Height          =   255
         Left            =   120
         TabIndex        =   16
         Top             =   1560
         Width           =   855
      End
      Begin VB.Label Label3 
         Caption         =   "&Company:"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   1080
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "&Title:"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   600
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "&Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   13
         Top             =   120
         Width           =   855
      End
   End
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3840
      TabIndex        =   2
      Top             =   5160
      Width           =   1095
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2640
      TabIndex        =   1
      Top             =   5160
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   360
      Top             =   5160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
      DefaultExt      =   "*.bmp"
      DialogTitle     =   "Open"
      Filter          =   "Pictures (*.bmp)|*.bmp|All Files (*.*)|*.*"
      Flags           =   5
   End
   Begin ComctlLib.TabStrip TabStrip1 
      Height          =   4935
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4815
      _ExtentX        =   8493
      _ExtentY        =   8705
      _Version        =   327680
      BeginProperty Tabs {0713E432-850A-101B-AFC0-4210102A8DA7} 
         NumTabs         =   2
         BeginProperty Tab1 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Conference"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   ""
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {0713F341-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Business Card"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   ""
            ImageVarType    =   2
         EndProperty
      EndProperty
      MouseIcon       =   "Options.frx":0000
   End
End
Attribute VB_Name = "Options"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'****************************************************************************
'
'  Module:     VBCARD.EXE
'  File:       Options.frm
'  Content:    Implementation of the Options form
'
'  Copyright (c) Microsoft Corporation 1995-1997
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'****************************************************************************

Option Explicit

Private Sub Browse_Click()
    ' Display a FileOpen dialog so that user can select picture
    On Error Resume Next
    CommonDialog1.ShowOpen
    If Err <> cdlCancel Then
        Photo = CommonDialog1.FileName
    End If
End Sub

Private Sub Cancel_Click()
    ' Close form window
    Unload Options
End Sub

Private Sub Form_Load()
    ' Initialize the form
    BizName.text = MyCard.Name
    Title.text = MyCard.Title
    Company.text = MyCard.Company
    Address.text = MyCard.Address
    Phone.text = MyCard.Phone
    Fax.text = MyCard.Fax
    EMail.text = MyCard.EMail
    Photo.text = MyCard.PhotoFile
End Sub

Private Sub OK_Click()
    ' Read and store all values on sheets
    MyCard.Name = BizName.text
    MyCard.Title = Title.text
    MyCard.Company = Company.text
    MyCard.Address = Address.text
    MyCard.Phone = Phone.text
    MyCard.Fax = Fax.text
    MyCard.EMail = EMail.text
    MyCard.PhotoFile = Photo.text
    
    ' Close form window
    Unload Options
End Sub

Private Sub TabStrip1_Click()
    ' Display the selected property page
    If TabStrip1.SelectedItem.Index = 1 Then
        Conference.ZOrder 0
    Else
        BizCard.ZOrder 0
    End If
End Sub
