VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form fAbout 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About Fox"
   ClientHeight    =   5670
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5910
   Icon            =   "fAbout.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5670
   ScaleWidth      =   5910
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton bOk 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   350
      Left            =   3480
      TabIndex        =   5
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton bCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Enabled         =   0   'False
      Height          =   350
      Left            =   4680
      TabIndex        =   4
      Top             =   5280
      Width           =   1095
   End
   Begin TabDlg.SSTab tsTabs 
      Height          =   4455
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   5655
      _ExtentX        =   9975
      _ExtentY        =   7858
      _Version        =   327681
      Style           =   1
      Tabs            =   1
      TabHeight       =   520
      TabCaption(0)   =   "Properties"
      TabPicture(0)   =   "fAbout.frx":08CA
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "lvAbout"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).ControlCount=   1
      Begin ComctlLib.ListView lvAbout 
         Height          =   3855
         Left            =   120
         TabIndex        =   3
         Top             =   480
         Width           =   5415
         _ExtentX        =   9551
         _ExtentY        =   6800
         View            =   3
         LabelEdit       =   1
         LabelWrap       =   0   'False
         HideSelection   =   0   'False
         _Version        =   327682
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   2
         BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Text            =   "Property"
            Object.Width           =   2187
         EndProperty
         BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
            SubItemIndex    =   1
            Key             =   ""
            Object.Tag             =   ""
            Text            =   "Value"
            Object.Width           =   5645
         EndProperty
      End
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "(application)"
      Height          =   195
      Left            =   840
      TabIndex        =   1
      Top             =   360
      Width           =   855
   End
   Begin VB.Label lApplication 
      AutoSize        =   -1  'True
      Caption         =   "fox"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   840
      TabIndex        =   0
      Top             =   120
      Width           =   270
   End
   Begin VB.Image Image1 
      Height          =   480
      Left            =   120
      Picture         =   "fAbout.frx":08E6
      Top             =   120
      Width           =   480
   End
End
Attribute VB_Name = "fAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub bOk_Click()
    '
    ' Hide myself:
    '
    Unload Me
End Sub

Private Sub Form_Load()
Dim oItem As ListItem

    lApplication.Caption = App.Title
    
    Set oItem = lvAbout.ListItems.Add(, , "Author")
    oItem.SubItems(1) = "Microsoft Site Server ADSIExplorer"
    
    Set oItem = lvAbout.ListItems.Add(, , "Version")
    oItem.SubItems(1) = App.Major & "." & App.Minor & "." & App.Revision

    Set oItem = lvAbout.ListItems.Add(, , "")
    
    Set oItem = lvAbout.ListItems.Add(, , "Description")
    oItem.SubItems(1) = "Skeleton sample of a membership manager"
    
    Set oItem = lvAbout.ListItems.Add(, , "")
    oItem.SubItems(1) = "for Olympus 98."

    Set oItem = lvAbout.ListItems.Add(, , "")
    
    Set oItem = lvAbout.ListItems.Add(, , "Warning")
    oItem.SubItems(1) = "Unsupported software, use at your own risk."
    
    Set oItem = lvAbout.ListItems.Add(, , "")
    
    Set oItem = lvAbout.ListItems.Add(, , "")
    oItem.SubItems(1) = "Copyright (C) 1998 Microsoft Corp."

    Set oItem = lvAbout.ListItems.Add(, , "")
    oItem.SubItems(1) = "All Rights Reserved"
End Sub

Private Sub Label4_Click()

End Sub


