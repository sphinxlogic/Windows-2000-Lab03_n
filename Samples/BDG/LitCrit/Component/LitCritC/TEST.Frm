VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "TEST"
   ClientHeight    =   3645
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3645
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtServer 
      Height          =   285
      Left            =   1080
      TabIndex        =   10
      Text            =   "boue"
      Top             =   2400
      Width           =   3375
   End
   Begin VB.TextBox txtLogon 
      Height          =   285
      Left            =   1080
      TabIndex        =   9
      Text            =   "jsudds"
      Top             =   2040
      Width           =   3375
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Test"
      Default         =   -1  'True
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   2880
      Width           =   4215
   End
   Begin VB.Label lblObjectID 
      Height          =   255
      Left            =   1560
      TabIndex        =   14
      Top             =   1680
      Width           =   2895
   End
   Begin VB.Label Label7 
      Caption         =   "ObjectID:"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Label Label6 
      Caption         =   "Server:"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   2400
      Width           =   855
   End
   Begin VB.Label Label5 
      Caption         =   "Logon:"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   2040
      Width           =   855
   End
   Begin VB.Label lblMediaType 
      Height          =   255
      Left            =   1560
      TabIndex        =   8
      Top             =   1320
      Width           =   2895
   End
   Begin VB.Label lblAuthors 
      Height          =   255
      Left            =   1560
      TabIndex        =   7
      Top             =   960
      Width           =   3015
   End
   Begin VB.Label lblTitle 
      Height          =   255
      Left            =   1560
      TabIndex        =   6
      Top             =   600
      Width           =   2895
   End
   Begin VB.Label lblBibNo 
      Height          =   255
      Left            =   1560
      TabIndex        =   5
      Top             =   240
      Width           =   3015
   End
   Begin VB.Label Label4 
      Caption         =   "Media Type:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1320
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "BibNo:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   240
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Authors:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Title:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   600
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
   Dim litcrit As New Critique
   Dim BibNo As Long
   Dim Title As String
   Dim Authors As String
   Dim MediaType As String
   Dim ObjectID As String
   
   Title = lblTitle.Caption
   Authors = lblAuthors.Caption
   MediaType = lblMediaType.Caption
   
   litcrit.ChooseTitle BibNo, Title, Authors, MediaType, ObjectID, txtLogon.Text, txtServer.Text
   
   lblBibNo.Caption = CStr(BibNo)
   lblTitle.Caption = Title
   lblAuthors.Caption = Authors
   lblMediaType.Caption = MediaType
   lblObjectID.Caption = ObjectID
End Sub

