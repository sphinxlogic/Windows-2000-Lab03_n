VERSION 5.00
Begin VB.Form GetURL 
   Caption         =   "Open"
   ClientHeight    =   1845
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4335
   LinkTopic       =   "Form2"
   ScaleHeight     =   1845
   ScaleWidth      =   4335
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox theURL 
      Height          =   285
      Left            =   960
      TabIndex        =   3
      Text            =   "http://home.microsoft.com"
      Top             =   840
      Width           =   3015
   End
   Begin VB.CommandButton Browse 
      Caption         =   "&Browse..."
      Height          =   375
      Left            =   2880
      TabIndex        =   2
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton Cancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1560
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Image Image1 
      Appearance      =   0  'Flat
      Height          =   495
      Left            =   120
      Top             =   240
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "Type the Internet address of a document or folder and MyWebBrowser will open it for you."
      Height          =   495
      Left            =   960
      TabIndex        =   5
      Top             =   240
      Width           =   3375
   End
   Begin VB.Label Label1 
      Caption         =   "Open:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   840
      Width           =   735
   End
End
Attribute VB_Name = "GetURL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public exitStatus As Boolean
Private Sub Cancel_Click()
    Hide
    exitStatus = False
End Sub

Private Sub OK_Click()
    Hide
    exitStatus = True
End Sub
