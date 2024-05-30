VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form MainForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VB Admin"
   ClientHeight    =   3390
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   7800
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3390
   ScaleWidth      =   7800
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton EditButton 
      Caption         =   "Edit..."
      Height          =   375
      Left            =   2760
      TabIndex        =   4
      Top             =   2640
      Width           =   975
   End
   Begin ComctlLib.ListView ListView 
      Height          =   1935
      Left            =   480
      TabIndex        =   3
      Top             =   480
      Width           =   6855
      _ExtentX        =   12091
      _ExtentY        =   3413
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327680
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   "A"
         Object.Tag             =   ""
         Text            =   "Name"
         Object.Width           =   2469
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   "B"
         Object.Tag             =   ""
         Text            =   "Initial Page"
         Object.Width           =   2469
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   "C"
         Object.Tag             =   ""
         Text            =   "LineAddress"
         Object.Width           =   2469
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   3
         Key             =   "D"
         Object.Tag             =   ""
         Text            =   "Description"
         Object.Width           =   2469
      EndProperty
   End
   Begin VB.CommandButton QuitButton 
      Caption         =   "Quit"
      Height          =   375
      Left            =   5400
      TabIndex        =   2
      Top             =   2640
      Width           =   975
   End
   Begin VB.CommandButton DeleteButton 
      Caption         =   "Delete"
      Height          =   375
      Left            =   4080
      TabIndex        =   1
      Top             =   2640
      Width           =   975
   End
   Begin VB.CommandButton NewButton 
      Caption         =   "New..."
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   2640
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Available applications:"
      Height          =   255
      Left            =   480
      TabIndex        =   5
      Top             =   120
      Width           =   1815
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' (C) 1998 Microsoft Corporation.  All rights reserved.                        '
' This is prerelease software and is provided as is and Microsoft makes no     '
' warranties,  either express or implied. The entire risk of the use or the    '
' results of the use of this prerelease software remains with the user.        '
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Private Sub DeleteButton_Click()
    On Error Resume Next
    
    If Not (ListView.SelectedItem Is Nothing) Then
        apps.RemoveApplication (ListView.SelectedItem)
        admin.Save
        If Err.Number <> 0 Then
            MsgBox Err.Description
        Else
            RefreshAppList
        End If
    End If
End Sub

Private Sub EditButton_Click()
    If Not (ListView.SelectedItem Is Nothing) Then
        AddOrChange = ChangeEntry
        AppName = ListView.SelectedItem
        AppPage = ListView.SelectedItem.SubItems(1)
        AppLineAddr = ListView.SelectedItem.SubItems(2)
        AppDescription = ListView.SelectedItem.SubItems(3)
        AddChangeForm.Show vbModal
    End If
End Sub

Private Sub Form_Load()
    Dim objitem As ListItem
    InitAdmin
    RefreshAppList
End Sub

Private Sub NewButton_Click()
    AddOrChange = AddEntry
    AddChangeForm.Show vbModal
End Sub

Private Sub QuitButton_Click()
    Hide
    Unload Me
End Sub

Sub RefreshAppList()
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' This subroutine will refresh the list of applications
'
    Dim objitem As ListItem
    Dim myapp As MsIvrApplication
    Dim lines As String
    ListView.ListItems.Clear ' clear the listbox
                  
    For Each myapp In apps
        Set objitem = ListView.ListItems.Add(Text:=myapp.Name)
        objitem.SubItems(1) = myapp.InitialPage
        lines = ""
        For Each lne In myapp.LineAddresses
            lines = lines & lne & ","
        Next
        If Len(lines) > 0 Then
            lines = Mid(lines, 1, Len(lines) - 1)
        End If
        objitem.SubItems(2) = lines
        objitem.SubItems(3) = myapp.Description
    Next
End Sub
