VERSION 5.00
Begin VB.UserControl UserControl1 
   ClientHeight    =   3600
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   PropertyPages   =   "Picture.ctx":0000
   ScaleHeight     =   3600
   ScaleWidth      =   4800
   Begin VB.PictureBox Picture1 
      BorderStyle     =   0  'None
      Height          =   2775
      Left            =   0
      Picture         =   "Picture.ctx":0004
      ScaleHeight     =   2775
      ScaleWidth      =   2895
      TabIndex        =   0
      Top             =   0
      Width           =   2895
   End
End
Attribute VB_Name = "UserControl1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private Sub UserControl_Resize()
    Picture1.Top = 0
    Picture1.Left = 0
    Picture1.Height = UserControl.Height
    Picture1.Width = UserControl.Width
    
End Sub
