VERSION 5.00
Begin VB.Form ClientFrm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Create new COM+ application"
   ClientHeight    =   5205
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4815
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5205
   ScaleWidth      =   4815
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command4 
      Caption         =   "Help"
      Height          =   495
      Left            =   3120
      TabIndex        =   11
      Top             =   4320
      Width           =   1095
   End
   Begin VB.Frame Frame2 
      Height          =   2775
      Left            =   480
      TabIndex        =   9
      Top             =   240
      Width           =   3855
      Begin VB.CommandButton Command3 
         Caption         =   "Add"
         Default         =   -1  'True
         Height          =   495
         Left            =   240
         TabIndex        =   2
         Top             =   1800
         Width           =   1095
      End
      Begin VB.TextBox Text1 
         Height          =   375
         Left            =   240
         TabIndex        =   1
         Top             =   840
         Width           =   3255
      End
      Begin VB.Label Label3 
         Caption         =   "Application Name:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   10
         Top             =   360
         Width           =   3135
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Transaction Options"
      Height          =   735
      Left            =   480
      TabIndex        =   6
      Top             =   3240
      Width           =   3855
      Begin VB.OptionButton Option1 
         Caption         =   "No"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   1
         Left            =   1560
         TabIndex        =   3
         Top             =   360
         Value           =   -1  'True
         Width           =   255
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Yes"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   3120
         TabIndex        =   0
         Top             =   360
         Width           =   255
      End
      Begin VB.Label Label2 
         Caption         =   "SetComplete"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   1335
      End
      Begin VB.Label Label1 
         Caption         =   "SetAbort"
         Height          =   255
         Left            =   2040
         TabIndex        =   7
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   1800
      TabIndex        =   5
      Top             =   4320
      Width           =   1095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   495
      Left            =   480
      TabIndex        =   4
      Top             =   4320
      Width           =   1095
   End
End
Attribute VB_Name = "ClientFrm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Copyright (C) 1995 - 1999, Microsoft Corporation.  All rights reserved.
'
' AdminClient.vbp
'
' This application provides a simple UI for creating a COM+ application
' using the MkCOMApp component.  Users may create one or more applications
' then commit all of the changes or cause all changes to be rolled back
' by calling SetComplete or SetAbort, respectively.
'
Dim bSucceedFail As Boolean
Dim objAdmin As New TransactAdmin.MkCOMApp

Private Sub Command1_Click()
    '
    ' Clicked OK button
    ' Commit all changes and reset UI
    '
    objAdmin.CommitChanges bSucceedFail
    
    Text1.Text = ""
    Option1(1).Value = True
    Command3.Enabled = False
    Command1.Enabled = False
    Text1.SetFocus
    
End Sub

    Private Sub Command3_Click()
    '
    ' Clicked Add button
    ' Add new application and reset UI
    '
    objAdmin.CreateApp Text1.Text
    
    Text1.Text = ""
    Option1(1).Value = True
    Command3.Enabled = False
    Command1.Enabled = True
    Text1.SetFocus

End Sub

Private Sub Command2_Click()
    '
    ' Clicked Cancel button
    ' Declare that we don't want to commit changes - i.e. no applications
    ' will be added.
    '

    objAdmin.CommitChanges False
    End
    
End Sub

Private Sub Command4_Click()
    
    '
    ' Display quick/dirty help text
    '
    MsgBox "The client application allows you to create several" & _
            "new COM+ applications in a single transaction.  Start " & _
            "by entering the application name for a new COM+ " & _
            "application and click on the 'Add' button.  You may " & _
            "add additional applications to be created by entering " & _
            "the application name and clicking on 'Add' for each one. " & _
            "To provide an example of the results when SetComplete " & _
            "or SetAbort are called in a transaction, the client " & _
            "application allows you to choose via its user interface. " & _
            "When you are ready to commit the changes, select either " & _
            "'SetComplete' or 'SetAbort' from the 'Transaction Options' " & _
            "frame then click 'OK'.  These options correspond to " & _
            "calling the SetComplete or SetAbort methods on the " & _
            "IObjectContext interface when the TransAdmin component " & _
            "is ready to commit changes.  Calling SetComplete " & _
            "indicates that the transaction completed successfully " & _
            "and commits the changes.  Calling SetAbort indicates " & _
            "that the transaction didn't complete successfully and " & _
            "any transactional changes are rolled back.   Also, if " & _
            "any errors occur while adding applications, SetAbort " & _
            "is automatically called through the error handler.", _
            vbOKOnly, "Help"
    
End Sub

Private Sub Form_Load()

    bSucceedFail = True
    Command3.Enabled = False
    Command1.Enabled = False
    
End Sub

Private Sub Option1_Click(Index As Integer)
    '
    ' Clicked SetComplete or SetAbort radio button
    '
    If Index = 0 Then
        bSucceedFail = False
    Else
        bSucceedFail = True
    End If
    
End Sub

Private Sub Text1_Change()
    '
    ' Typed characters in text box.  Make sure that leading spaces are
    ' trimmed.  If text is non null, then enable UI for adding
    ' a new application.
    '
    Text1.Text = LTrim(Text1.Text)
    If Text1.Text <> "" Then
        Command3.Enabled = True
    Else
        Command3.Enabled = False
    End If
    
End Sub
