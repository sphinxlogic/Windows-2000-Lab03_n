VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Begin VB.Form Form1 
   Caption         =   "VBCustomWB"
   ClientHeight    =   8010
   ClientLeft      =   2580
   ClientTop       =   1845
   ClientWidth     =   9570
   LinkTopic       =   "Form1"
   ScaleHeight     =   8010
   ScaleWidth      =   9570
   Begin VB.Frame Frame1 
      Caption         =   "Accelerators"
      Height          =   1455
      Left            =   2078
      TabIndex        =   0
      Top             =   6360
      Width           =   2655
      Begin VB.CheckBox chkAccelerators 
         Caption         =   "Turn off Accelerators"
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Value           =   1  'Checked
         Width           =   2055
      End
      Begin VB.CheckBox chkCtrlN 
         Caption         =   "Turn off Ctrl+N"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Value           =   1  'Checked
         Width           =   1455
      End
      Begin VB.CheckBox chkCtrlO 
         Caption         =   "Turn off Ctrl+O"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   1080
         Value           =   1  'Checked
         Width           =   1575
      End
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   6015
      Left            =   240
      TabIndex        =   6
      Top             =   120
      Width           =   9015
      ExtentX         =   15901
      ExtentY         =   10610
      ViewMode        =   1
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   -1  'True
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
   Begin VB.CheckBox chkContextMenu 
      Caption         =   "Turn off Context Menus"
      Height          =   255
      Left            =   5438
      TabIndex        =   4
      Top             =   6600
      Value           =   1  'Checked
      Width           =   2055
   End
   Begin VB.CommandButton btnStop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   5438
      TabIndex        =   5
      Top             =   7320
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim CustomWB As WBCustomizer

Private Sub btnStop_Click()
   WebBrowser1.Stop
End Sub

Private Sub chkAccelerators_Click()
   CustomWB.EnableAllAccelerators = Not CustomWB.EnableAllAccelerators
   
   If CustomWB.EnableAllAccelerators = True Then
      chkAccelerators.Caption = "Turn off Accelerators"
   Else
      chkAccelerators.Caption = "Turn on Accelerators"
   End If
End Sub

Private Sub chkContextMenu_Click()
   CustomWB.EnableContextMenus = Not CustomWB.EnableContextMenus
   
   If CustomWB.EnableContextMenus = True Then
      chkContextMenu.Caption = "Turn off Context Menus"
   Else
      chkContextMenu.Caption = "Turn on Context Menus"
   End If
End Sub

Private Sub chkCtrlN_Click()
   If chkCtrlN.Value = 1 Then
      CustomWB.EnableAccelerator vbKeyN, vbKeyControl, True
      chkCtrlN.Caption = "Turn off Ctrl+N"
   Else
      CustomWB.EnableAccelerator vbKeyN, vbKeyControl, False
      chkCtrlN.Caption = "Turn on Ctrl+N"
   End If
End Sub

Private Sub chkCtrlO_Click()
   If chkCtrlO.Value = 1 Then
      CustomWB.EnableAccelerator vbKeyO, vbKeyControl, True
      chkCtrlO.Caption = "Turn off Ctrl+O"
   Else
      CustomWB.EnableAccelerator vbKeyO, vbKeyControl, False
      chkCtrlO.Caption = "Turn on Ctrl+O"
   End If
End Sub

Private Sub Form_Load()
   Set CustomWB = New WBCustomizer
   With CustomWB
      .EnableAccelerator vbKeyN, vbKeyControl
      .EnableAccelerator vbKeyO, vbKeyControl
      
      .EnableContextMenus = True
      .EnableAllAccelerators = True
      
      Set .WebBrowser = WebBrowser1
   End With
   
   WebBrowser1.Navigate "http://www.microsoft.com"
End Sub
