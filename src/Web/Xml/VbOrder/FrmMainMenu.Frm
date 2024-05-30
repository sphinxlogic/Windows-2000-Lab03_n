VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmMainMenu 
   Caption         =   "Main Menu"
   ClientHeight    =   4905
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8280
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4905
   ScaleWidth      =   8280
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   495
      Left            =   0
      TabIndex        =   10
      Top             =   4410
      Width           =   8280
      _ExtentX        =   14605
      _ExtentY        =   873
      ShowTips        =   0   'False
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   2
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Object.Width           =   12877
            MinWidth        =   12877
            Text            =   "User:"
            TextSave        =   "User:"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            Object.Width           =   1235
            MinWidth        =   1235
            Text            =   "Date:"
            TextSave        =   "1/9/99"
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2760
      TabIndex        =   6
      Top             =   3840
      Width           =   2655
   End
   Begin VB.CommandButton cmdProducts 
      Caption         =   "View &Products"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4200
      TabIndex        =   5
      Top             =   3240
      Width           =   2415
   End
   Begin VB.CommandButton cmdEditOrders 
      Caption         =   "&Edit Orders"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1320
      TabIndex        =   2
      Top             =   3240
      Width           =   2655
   End
   Begin VB.CommandButton cmdViewShippedOrders 
      Caption         =   "Vie&w Shipped Orders"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4200
      TabIndex        =   4
      Top             =   2640
      Width           =   2415
   End
   Begin VB.CommandButton cmdViewOrders 
      Caption         =   "&View Orders"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Top             =   2640
      Width           =   2535
   End
   Begin VB.CommandButton cmdShipOrders 
      Caption         =   "&Ship Orders"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4200
      TabIndex        =   3
      Top             =   2040
      Width           =   2415
   End
   Begin VB.CommandButton cmdPlaceOrders 
      Caption         =   "Place &Orders"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1320
      TabIndex        =   0
      Top             =   2040
      Width           =   2535
   End
   Begin VB.Label lblMainMenu 
      Alignment       =   2  'Center
      Caption         =   "Main Menu:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   0
      TabIndex        =   9
      Top             =   1440
      Width           =   8055
   End
   Begin VB.Label lblTitle2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Computers R' Us"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   48
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   1125
      Left            =   360
      TabIndex        =   8
      Top             =   120
      Width           =   7755
   End
   Begin VB.Label lblTitle1 
      AutoSize        =   -1  'True
      Caption         =   "Computers R' Us"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   48
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1125
      Left            =   240
      TabIndex        =   7
      Top             =   120
      Width           =   7755
   End
End
Attribute VB_Name = "frmMainMenu"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdExit_Click()

 Unload frmMainMenu
 
End Sub

Private Sub cmdPlaceOrders_Click()

  frmMainMenu.MousePointer = 11
  Load frmOrder
  frmOrder.Height = 6870
  frmOrder.Width = 9510
  frmOrder.Show
  frmMainMenu.Hide
  
End Sub

