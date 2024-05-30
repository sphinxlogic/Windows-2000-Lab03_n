VERSION 5.00
Begin VB.Form ViewForm 
   Caption         =   "Form1"
   ClientHeight    =   6450
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9075
   LinkTopic       =   "Form1"
   ScaleHeight     =   6450
   ScaleWidth      =   9075
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CloseTBut 
      Caption         =   "Close"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   6000
      Width           =   1095
   End
   Begin VB.Image BigImage 
      Height          =   5775
      Left            =   120
      Stretch         =   -1  'True
      Top             =   120
      Width           =   8895
   End
End
Attribute VB_Name = "ViewForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub CloseTBut_Click()

End Sub
