VERSION 5.00
Begin VB.Form frmStartup 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Visual MIME"
   ClientHeight    =   1980
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4680
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1980
   ScaleWidth      =   4680
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer Timer1 
      Interval        =   2000
      Left            =   120
      Top             =   1560
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "A CDO-based application.  "
      Height          =   255
      Left            =   720
      TabIndex        =   1
      Top             =   1560
      Width           =   3495
   End
   Begin VB.Label Label1 
      Caption         =   "Visual MIME"
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   1080
      TabIndex        =   0
      Top             =   360
      Width           =   3495
   End
   Begin VB.Image Image1 
      Height          =   1230
      Left            =   120
      Picture         =   "frmStartup.frx":0000
      Top             =   120
      Width           =   840
   End
End
Attribute VB_Name = "frmStartup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Timer1_Timer()
    frmMimeViewer.Show
    Unload Me
End Sub
