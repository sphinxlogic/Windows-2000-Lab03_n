VERSION 5.00
Begin VB.Form frmAbout 
   Caption         =   "About..."
   ClientHeight    =   3225
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5790
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3225
   ScaleWidth      =   5790
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   4560
      TabIndex        =   0
      Top             =   2640
      Width           =   1095
   End
   Begin VB.PictureBox Picture1 
      Height          =   975
      Left            =   120
      ScaleHeight     =   915
      ScaleWidth      =   1035
      TabIndex        =   7
      Top             =   240
      Width           =   1095
   End
   Begin VB.Label Label7 
      Caption         =   "All rights reserved."
      Height          =   255
      Left            =   1680
      TabIndex        =   9
      Top             =   1440
      Width           =   1455
   End
   Begin VB.Label lblCopyright 
      Caption         =   "Copyright (C) 1987-1998 Microsoft Corporation"
      Height          =   255
      Left            =   1680
      TabIndex        =   8
      Top             =   1200
      Width           =   3375
   End
   Begin VB.Label Label6 
      Caption         =   $"frmAbout.frx":0000
      Height          =   855
      Left            =   120
      TabIndex        =   6
      Top             =   2280
      Width           =   4215
   End
   Begin VB.Label Label5 
      Caption         =   "Warning: This computer program is protected by copyright law and international treaties."
      Height          =   375
      Left            =   120
      TabIndex        =   5
      Top             =   1920
      Width           =   4335
   End
   Begin VB.Line Line1 
      DrawMode        =   1  'Blackness
      X1              =   120
      X2              =   5640
      Y1              =   1800
      Y2              =   1800
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Version (Build 3.0.1)"
      Height          =   195
      Left            =   1680
      TabIndex        =   4
      Top             =   960
      Width           =   1410
   End
   Begin VB.Label Label3 
      Caption         =   "ADO Consumer Sample"
      Height          =   195
      Left            =   1680
      TabIndex        =   3
      Top             =   720
      Width           =   1665
   End
   Begin VB.Label Label2 
      Caption         =   "Microsoft Corporation"
      Height          =   255
      Left            =   1680
      TabIndex        =   2
      Top             =   240
      Width           =   1815
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Microsoft OLE DB Data Provider for DB2"
      Height          =   195
      Left            =   1680
      TabIndex        =   1
      Top             =   480
      Width           =   2880
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdOK_Click()
    On Error Resume Next
    
    frmAbout.Hide
    Unload frmAbout

End Sub

