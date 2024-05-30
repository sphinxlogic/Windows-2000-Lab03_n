VERSION 5.00
Begin VB.Form frmChooseSetting 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Add Critique to Library"
   ClientHeight    =   2565
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3510
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2565
   ScaleWidth      =   3510
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdResponse 
      Caption         =   "&No"
      Height          =   375
      Index           =   0
      Left            =   1920
      TabIndex        =   3
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CheckBox chkSetting 
      Caption         =   "&Set this response as the default"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   1560
      Width           =   2775
   End
   Begin VB.CommandButton cmdResponse 
      Caption         =   "&Yes"
      Default         =   -1  'True
      Height          =   375
      Index           =   1
      Left            =   360
      TabIndex        =   0
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Label lblQuestion 
      Height          =   1215
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   3255
   End
End
Attribute VB_Name = "frmChooseSetting"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public isChecked As Boolean
Public Response As Integer

Private Sub cmdResponse_Click(Index As Integer)
   Response = Index
   isChecked = chkSetting.Value
   Unload Me
End Sub

Private Sub Form_Load()
   Dim str As String
   
   str = str & "The Fitch & Mather library may contain the" & vbCrLf
   str = str & "item you are about to review. If it does, your" & vbCrLf
   str = str & "critique can be made available to library users." & vbCrLf & vbCrLf
   str = str & "Do you want to search for this title in the" & vbCrLf
   str = str & "library's database?"
   
   lblQuestion.Caption = str
End Sub

