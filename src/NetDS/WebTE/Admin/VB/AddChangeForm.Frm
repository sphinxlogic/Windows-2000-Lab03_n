VERSION 5.00
Begin VB.Form AddChangeForm 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Form1"
   ClientHeight    =   3450
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3900
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3450
   ScaleWidth      =   3900
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2040
      TabIndex        =   10
      Top             =   2760
      Width           =   1335
   End
   Begin VB.CommandButton OkButton 
      Caption         =   "OK"
      Enabled         =   0   'False
      Height          =   375
      Left            =   360
      TabIndex        =   9
      Top             =   2760
      Width           =   1335
   End
   Begin VB.TextBox DescriptionBox 
      Height          =   285
      Left            =   1320
      TabIndex        =   8
      Top             =   2040
      Width           =   2175
   End
   Begin VB.TextBox LineAddressBox 
      Height          =   285
      Left            =   1320
      TabIndex        =   7
      Top             =   1560
      Width           =   2175
   End
   Begin VB.TextBox PageBox 
      Height          =   285
      Left            =   1320
      TabIndex        =   6
      Top             =   1080
      Width           =   2175
   End
   Begin VB.TextBox NameBox 
      Height          =   285
      Left            =   1320
      TabIndex        =   5
      Top             =   600
      Width           =   2175
   End
   Begin VB.Label DescriptionLabel 
      Caption         =   "Description:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   2040
      Width           =   855
   End
   Begin VB.Label LineAddressLabel 
      Caption         =   "Line address:"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1560
      Width           =   975
   End
   Begin VB.Label AppLabel 
      Caption         =   "Initial Page:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   1080
      Width           =   975
   End
   Begin VB.Label NameLabel 
      Caption         =   "Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   600
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "Application properties:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1815
   End
End
Attribute VB_Name = "AddChangeForm"
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

Function SetOkButton() As Boolean
    If (NameBox.Text = "") Or (PageBox.Text = "") Then
        OkButton.Enabled = False
    Else
        OkButton.Enabled = True
    End If
End Function

Private Sub CancelButton_Click()
    Unload AddChangeForm
End Sub

Private Sub Form_Load()
    If AddOrChange = AddEntry Then
        AddChangeForm.Caption = "Add a New Entry"
        NameBox.Text = ""
        NameBox.Enabled = True
        PageBox.Text = ""
        NameBox.Enabled = True
        LineAddressBox.Text = ""
        LineAddressBox.Enabled = True
        DescriptionBox.Text = ""
        DescriptionBox.Enabled = True
    Else
        AddChangeForm.Caption = "Change an Existing Entry"
        NameBox.Text = AppName
        NameBox.Enabled = False
        PageBox.Text = AppPage
        PageBox.Enabled = True
        LineAddressBox.Text = AppLineAddr
        LineAddressBox.Enabled = True
        DescriptionBox.Text = AppDescription
        DescriptionBox.Enabled = True
    End If
End Sub

Private Sub NameBox_Change()
    SetOkButton
End Sub

Private Sub OkButton_Click()
    Dim myapp As MsIvrApplication
    Dim numbers As String
    Dim StartPos, EndPos, cnt As Integer
    
    On Error Resume Next
    If AddOrChange = ChangeEntry Then
        Set myapp = apps(NameBox.Text)
    Else
        Set myapp = apps.AddApplication(NameBox.Text, PageBox.Text)
    End If
    
    If Err.Number <> 0 Then
        MsgBox Err.Description
        Exit Sub
    End If
        
    myapp.Description = DescriptionBox.Text
    myapp.InitialPage = PageBox.Text
    If Err.Number <> 0 Then
        MsgBox Err.Description
        If AddOrChange = AddEntry Then apps.RemoveApplication (myapp.Name)
        Exit Sub
    End If
    
    numbers = LineAddressBox.Text
    
    StartPos = 0
    EndPos = 1
    cnt = 0
    
    ' count how many lines there are in the string
    Do While EndPos <> 0
        EndPos = InStr(StartPos + 1, numbers, ",")
        If EndPos = 0 Then Exit Do
        StartPos = EndPos
        cnt = cnt + 1
    Loop
    If numbers <> "" Then cnt = cnt + 1
    
    ' needs special attention
    If cnt = 0 Then
        myapp.LineAddresses = ""
        myapp.Save
        Unload AddChangeForm
        MainForm.RefreshAppList
        Exit Sub
    End If
    
    ReDim temp(0 To cnt - 1)

    EndPos = 1
    cnt = 0
    
    Do While EndPos <> 0
        Dim CurrNumber
        EndPos = InStr(1, numbers, ",")
        If EndPos = 0 Then Exit Do
        temp(cnt) = Mid(numbers, 1, EndPos - 1)
        cnt = cnt + 1
        numbers = Right(numbers, Len(numbers) - Len(temp(cnt - 1)) - 1)
        StartPos = EndPos
    Loop
    
    If numbers <> "" Then
        temp(cnt) = numbers
    End If
    
    myapp.LineAddresses = temp
    If Err.Number <> 0 Then
        MsgBox Err.Description
        If AddOrChange = AddEntry Then apps.RemoveApplication (myapp.Name)
        Exit Sub
    Else
        myapp.Save
    End If
      
    Unload AddChangeForm
    MainForm.RefreshAppList
End Sub

Private Sub Pagebox_change()
    SetOkButton
End Sub

