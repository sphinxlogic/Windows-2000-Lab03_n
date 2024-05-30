VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Object = "{65E121D4-0C60-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCHRT20.OCX"
Object = "{62CEE58A-5A21-11D2-8091-00C04F8EF90B}#1.0#0"; "TradeBanner.ocx"
Begin VB.Form frmMainProfile 
   BackColor       =   &H80000008&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "HBTradeStation:   Hanson Brothers Trade Station"
   ClientHeight    =   8235
   ClientLeft      =   150
   ClientTop       =   435
   ClientWidth     =   8940
   ClipControls    =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   14.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8235
   ScaleWidth      =   8940
   Begin VB.Timer BannerTimer 
      Interval        =   30000
      Left            =   4740
      Top             =   4080
   End
   Begin VB.TextBox Text2 
      CausesValidation=   0   'False
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
      TabIndex        =   110
      Top             =   1440
      Width           =   3375
   End
   Begin VB.TextBox Text1 
      CausesValidation=   0   'False
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
      TabIndex        =   109
      Top             =   960
      Width           =   3375
   End
   Begin VB.CommandButton ExitTBUT 
      Cancel          =   -1  'True
      Caption         =   "Exit"
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
      Left            =   7800
      TabIndex        =   83
      Top             =   4120
      Width           =   1095
   End
   Begin VB.TextBox TotalCashTED 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00E0E0E0&
      CausesValidation=   0   'False
      BeginProperty DataFormat 
         Type            =   1
         Format          =   """$""#,##0.00"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1033
         SubFormatType   =   2
      EndProperty
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   390
      Left            =   7080
      TabIndex        =   80
      Text            =   "0"
      Top             =   3480
      Width           =   1695
   End
   Begin VB.CommandButton RefreshTBut 
      Caption         =   "Refresh"
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
      Left            =   6480
      TabIndex        =   79
      Top             =   4120
      Width           =   1215
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000006&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   615
      Left            =   360
      Picture         =   "frmMain.frx":0000
      ScaleHeight     =   585
      ScaleWidth      =   3225
      TabIndex        =   67
      Top             =   3120
      Width           =   3255
   End
   Begin VB.TextBox TotalNetTED 
      Alignment       =   1  'Right Justify
      BackColor       =   &H00E0E0E0&
      CausesValidation=   0   'False
      BeginProperty DataFormat 
         Type            =   1
         Format          =   """$""#,##0.00"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1033
         SubFormatType   =   2
      EndProperty
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   405
      Left            =   7080
      TabIndex        =   15
      Text            =   "0"
      Top             =   3000
      Width           =   1695
   End
   Begin VB.ComboBox AccountsCombo 
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   1440
      TabIndex        =   14
      Text            =   "Select Account"
      Top             =   4080
      Width           =   2775
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   3615
      Left            =   45
      TabIndex        =   12
      Top             =   4560
      Width           =   8865
      _ExtentX        =   15637
      _ExtentY        =   6376
      _Version        =   393216
      Tabs            =   8
      TabsPerRow      =   8
      TabHeight       =   520
      BackColor       =   16384
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "Details"
      TabPicture(0)   =   "frmMain.frx":2631
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "AccountFlexGrid"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "ReportTBUT"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "HBut"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "AccountFlexGrid2"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).ControlCount=   4
      TabCaption(1)   =   "Holdings"
      TabPicture(1)   =   "frmMain.frx":264D
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "HoldingFGrid"
      Tab(1).ControlCount=   1
      TabCaption(2)   =   "History"
      TabPicture(2)   =   "frmMain.frx":2669
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "HistoryFGrid"
      Tab(2).ControlCount=   1
      TabCaption(3)   =   "Trade"
      TabPicture(3)   =   "frmMain.frx":2685
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "ConfirmFrame"
      Tab(3).Control(1)=   "TradeFrame"
      Tab(3).ControlCount=   2
      TabCaption(4)   =   "Pending"
      TabPicture(4)   =   "frmMain.frx":26A1
      Tab(4).ControlEnabled=   0   'False
      Tab(4).Control(0)=   "SettleTED"
      Tab(4).Control(1)=   "SettleTBUT"
      Tab(4).Control(2)=   "PendingFlxGrid"
      Tab(4).Control(3)=   "Label1"
      Tab(4).ControlCount=   4
      TabCaption(5)   =   "Quote"
      TabPicture(5)   =   "frmMain.frx":26BD
      Tab(5).ControlEnabled=   0   'False
      Tab(5).Control(0)=   "QuoteNameLabel"
      Tab(5).Control(1)=   "Frame4"
      Tab(5).Control(2)=   "QuoteCombo"
      Tab(5).Control(3)=   "ForceQuoteTBUT"
      Tab(5).Control(4)=   "SubscribeTBUT"
      Tab(5).ControlCount=   5
      TabCaption(6)   =   "Chart"
      TabPicture(6)   =   "frmMain.frx":26D9
      Tab(6).ControlEnabled=   0   'False
      Tab(6).Control(0)=   "ChartForm"
      Tab(6).ControlCount=   1
      TabCaption(7)   =   "Settings"
      TabPicture(7)   =   "frmMain.frx":26F5
      Tab(7).ControlEnabled=   0   'False
      Tab(7).Control(0)=   "Label26"
      Tab(7).Control(1)=   "ViewFrame"
      Tab(7).Control(2)=   "SetPanel"
      Tab(7).Control(3)=   "CCBut"
      Tab(7).ControlCount=   4
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid AccountFlexGrid2 
         Height          =   2580
         Left            =   120
         TabIndex        =   77
         Top             =   480
         Width           =   8655
         _ExtentX        =   15266
         _ExtentY        =   4551
         _Version        =   393216
         ForeColor       =   12582912
         BackColorFixed  =   -2147483638
         BackColorBkg    =   -2147483642
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   2
      End
      Begin VB.CheckBox CCBut 
         Height          =   330
         Left            =   -74760
         TabIndex        =   100
         Top             =   840
         Width           =   255
      End
      Begin VB.Frame SetPanel 
         Height          =   3135
         Left            =   -74400
         TabIndex        =   85
         Top             =   360
         Width           =   8175
         Begin VB.CheckBox TestModeCBut 
            Caption         =   "Test Mode"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   495
            Left            =   7080
            TabIndex        =   128
            Top             =   480
            Width           =   975
         End
         Begin VB.Frame Frame5 
            Caption         =   "Batch Jobs"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   855
            Left            =   4080
            TabIndex        =   99
            Top             =   240
            Width           =   2775
            Begin VB.CommandButton ReconcileBut 
               Caption         =   "Reconcile Orders"
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
               Left            =   120
               TabIndex        =   131
               Top             =   320
               Width           =   2415
            End
         End
         Begin VB.Frame Frame8 
            Caption         =   "LCE Subscription Mode"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   1695
            Left            =   4080
            TabIndex        =   93
            Top             =   1200
            Width           =   3975
            Begin VB.CheckBox PersistCBut 
               Caption         =   "Persistant Sub"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   1920
               TabIndex        =   98
               Top             =   240
               Width           =   1695
            End
            Begin VB.CheckBox TransientCBut 
               Caption         =   "Transient Sub"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   97
               Top             =   240
               Width           =   1575
            End
            Begin VB.TextBox NewsTEd 
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   360
               Left            =   1200
               TabIndex        =   96
               Text            =   "This is a news headline Test"
               Top             =   720
               Width           =   2655
            End
            Begin VB.CommandButton PublishTBut 
               Caption         =   "Publish"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   375
               Left            =   120
               TabIndex        =   95
               Top             =   720
               Width           =   975
            End
            Begin VB.CheckBox EventCBut 
               Caption         =   "Show Events in Message Box"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   240
               TabIndex        =   94
               Top             =   1200
               Width           =   3375
            End
         End
         Begin VB.Frame Frame9 
            Caption         =   "Data Initialize and Transfer"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   1095
            Left            =   120
            TabIndex        =   92
            Top             =   240
            Width           =   3855
            Begin VB.CommandButton CInitBut 
               BackColor       =   &H00808080&
               Caption         =   "Init Cust/Accts"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   127
               Top             =   320
               Width           =   1575
            End
            Begin VB.CommandButton DeleteOrdersTBut 
               Caption         =   "Delete Orders"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   1920
               TabIndex        =   121
               Top             =   320
               Width           =   1695
            End
            Begin VB.CheckBox TestCBut 
               Caption         =   "Test"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   120
               Top             =   675
               Width           =   735
            End
            Begin VB.TextBox TestTEd 
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   8.25
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   315
               Left            =   1920
               TabIndex        =   119
               Top             =   720
               Width           =   975
            End
            Begin VB.Label TestLabel 
               Caption         =   "Customers:"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   255
               Left            =   840
               TabIndex        =   122
               Top             =   720
               Width           =   1095
            End
         End
         Begin VB.Frame Frame10 
            Caption         =   "Timers"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   735
            Left            =   120
            TabIndex        =   89
            Top             =   1320
            Width           =   3855
            Begin VB.CheckBox StopCBut 
               Caption         =   "Stop"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   3000
               TabIndex        =   126
               Top             =   300
               Width           =   735
            End
            Begin VB.CheckBox ODBCCBut 
               Caption         =   "ODBC"
               Enabled         =   0   'False
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   2040
               TabIndex        =   125
               Top             =   300
               Width           =   855
            End
            Begin VB.TextBox TimerTEd 
               Alignment       =   1  'Right Justify
               BackColor       =   &H00C0C0C0&
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   700
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   360
               Left            =   1320
               TabIndex        =   90
               Text            =   "1000"
               Top             =   240
               Width           =   615
            End
            Begin VB.Label Label29 
               BackColor       =   &H80000004&
               Caption         =   "Quotes (ms):"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               ForeColor       =   &H00000000&
               Height          =   255
               Left            =   120
               TabIndex        =   91
               Top             =   300
               Width           =   2295
            End
         End
         Begin VB.Frame Frame11 
            Caption         =   "Object Creation Mode"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   735
            Left            =   120
            TabIndex        =   86
            Top             =   2160
            Width           =   3855
            Begin VB.CheckBox chkXML 
               Caption         =   "Use XML"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   2640
               TabIndex        =   130
               Top             =   240
               Width           =   1095
            End
            Begin VB.CheckBox QueueCBut 
               Caption         =   "Queued"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   88
               Top             =   260
               Width           =   1095
            End
            Begin VB.CheckBox ObjectCBut 
               Caption         =   "All Objects"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   1200
               TabIndex        =   87
               Top             =   240
               Width           =   1335
            End
         End
      End
      Begin VB.CheckBox HBut 
         Caption         =   "Portfolio Hierarchy"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   330
         Left            =   2040
         TabIndex        =   76
         Top             =   3120
         Width           =   2055
      End
      Begin VB.Frame ChartForm 
         BackColor       =   &H00000000&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000001&
         Height          =   3135
         Left            =   -74880
         TabIndex        =   68
         Top             =   360
         Width           =   8655
         Begin MSChart20Lib.MSChart chtReport 
            Height          =   3255
            Left            =   4320
            OleObjectBlob   =   "frmMain.frx":2711
            TabIndex        =   129
            Top             =   -120
            Width           =   4335
         End
         Begin VB.CommandButton ChartTBut 
            Caption         =   "Chart"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   2040
            TabIndex        =   78
            Top             =   2040
            Width           =   1335
         End
         Begin VB.ComboBox EndCombo 
            BackColor       =   &H00E0E0E0&
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   390
            Left            =   1440
            TabIndex        =   71
            Text            =   "Combo1"
            Top             =   1320
            Width           =   2775
         End
         Begin VB.ComboBox StartCombo 
            BackColor       =   &H00E0E0E0&
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   390
            Left            =   1440
            TabIndex        =   70
            Text            =   "Combo1"
            Top             =   840
            Width           =   2775
         End
         Begin VB.ComboBox ChartSymbolCombo 
            BackColor       =   &H00E0E0E0&
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   390
            Left            =   1440
            TabIndex        =   69
            Text            =   "Combo1"
            Top             =   360
            Width           =   2775
         End
         Begin VB.Label Label24 
            BackColor       =   &H00000000&
            Caption         =   "End Time"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808000&
            Height          =   375
            Left            =   240
            TabIndex        =   74
            Top             =   1320
            Width           =   1215
         End
         Begin VB.Label Label23 
            BackColor       =   &H00000000&
            Caption         =   "Start Time"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808000&
            Height          =   375
            Left            =   240
            TabIndex        =   73
            Top             =   840
            Width           =   1215
         End
         Begin VB.Label Label15 
            BackColor       =   &H00000000&
            Caption         =   "Symbol"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808000&
            Height          =   375
            Left            =   240
            TabIndex        =   72
            Top             =   360
            Width           =   1215
         End
      End
      Begin VB.CommandButton SubscribeTBUT 
         Caption         =   "Subscribe All News"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   -68280
         TabIndex        =   65
         Top             =   400
         Width           =   2055
      End
      Begin VB.TextBox SettleTED 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   405
         Left            =   -71760
         TabIndex        =   63
         Top             =   3000
         Width           =   2175
      End
      Begin VB.CommandButton SettleTBUT 
         Caption         =   "Force Settlement"
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
         Left            =   -69240
         TabIndex        =   62
         Top             =   3000
         Width           =   2175
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid PendingFlxGrid 
         Height          =   2415
         Left            =   -74880
         TabIndex        =   61
         Top             =   480
         Width           =   8655
         _ExtentX        =   15266
         _ExtentY        =   4260
         _Version        =   393216
         ForeColor       =   16711680
         BackColorBkg    =   -2147483640
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   2
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
      End
      Begin VB.CommandButton ReportTBUT 
         Caption         =   "View Report"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   355
         Left            =   240
         TabIndex        =   60
         Top             =   3120
         Width           =   1575
      End
      Begin VB.CommandButton ForceQuoteTBUT 
         Caption         =   "Refresh Quote"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   -69960
         TabIndex        =   58
         Top             =   400
         Width           =   1575
      End
      Begin VB.ComboBox QuoteCombo 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   405
         Left            =   -74880
         TabIndex        =   57
         Text            =   "Quote List"
         Top             =   400
         Width           =   1815
      End
      Begin VB.Frame Frame4 
         Appearance      =   0  'Flat
         BackColor       =   &H80000007&
         BorderStyle     =   0  'None
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H80000008&
         Height          =   2685
         Left            =   -74880
         TabIndex        =   35
         Top             =   840
         Width           =   8655
         Begin VB.TextBox NTEd 
            Alignment       =   1  'Right Justify
            BackColor       =   &H80000004&
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   360
            Left            =   120
            TabIndex        =   116
            Text            =   "0"
            Top             =   480
            Width           =   735
         End
         Begin VB.Timer QuoteTimer 
            Interval        =   1000
            Left            =   360
            Top             =   960
         End
         Begin BannerLabelControl.BannerLabel BannerLabel 
            Height          =   375
            Left            =   720
            TabIndex        =   75
            Top             =   1680
            Width           =   6735
            _ExtentX        =   11880
            _ExtentY        =   661
            BackColor       =   0
            ForeColor       =   8421376
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "Arial"
               Size            =   17.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            BorderStyle     =   0
            Interval        =   1000
            Caption         =   "Quote Ticker Banner!"
         End
         Begin VB.ComboBox NewsCombo 
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   360
            Left            =   120
            TabIndex        =   66
            Top             =   2205
            Width           =   8295
         End
         Begin VB.TextBox AskSizeTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   1
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   5040
            TabIndex        =   54
            Text            =   "Ask Size"
            Top             =   1200
            Width           =   1335
         End
         Begin VB.TextBox BidSizeTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   1
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   3720
            TabIndex        =   53
            Text            =   "Bid Size"
            Top             =   1200
            Width           =   1335
         End
         Begin VB.TextBox OpenPriceTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   3720
            TabIndex        =   43
            Text            =   "Open Price"
            Top             =   470
            Width           =   1335
         End
         Begin VB.TextBox AskPriceTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   2400
            TabIndex        =   42
            Text            =   "Ask Price"
            Top             =   1200
            Width           =   1335
         End
         Begin VB.TextBox BidPriceTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   960
            TabIndex        =   41
            Text            =   "Bid Price"
            Top             =   1200
            Width           =   1455
         End
         Begin VB.TextBox DailyHighTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   6360
            TabIndex        =   40
            Text            =   "Daily High"
            Top             =   1200
            Width           =   1455
         End
         Begin VB.TextBox DailyLowTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   6360
            TabIndex        =   39
            Text            =   "Daily Low"
            Top             =   470
            Width           =   1455
         End
         Begin VB.TextBox PrevCloseTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   5040
            TabIndex        =   38
            Text            =   "Previous Close"
            Top             =   470
            Width           =   1335
         End
         Begin VB.TextBox ChangeTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   "0.00%"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   5
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   2400
            TabIndex        =   37
            Text            =   "Change"
            Top             =   470
            Width           =   1335
         End
         Begin VB.TextBox LastPriceTED 
            Alignment       =   1  'Right Justify
            BeginProperty DataFormat 
               Type            =   1
               Format          =   """$""#,##0.00"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1033
               SubFormatType   =   2
            EndProperty
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   400
            Left            =   960
            TabIndex        =   36
            Text            =   "Last Price"
            Top             =   470
            Width           =   1455
         End
         Begin VB.Label NLabel 
            BackColor       =   &H00000000&
            Caption         =   "News Cnt"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808000&
            Height          =   255
            Left            =   45
            TabIndex        =   117
            Top             =   120
            Width           =   855
         End
         Begin VB.Label Label17 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "Ask Size"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   5040
            TabIndex        =   56
            Top             =   870
            Width           =   1335
         End
         Begin VB.Label Label16 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "Bid Size"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   3720
            TabIndex        =   55
            Top             =   870
            Width           =   1335
         End
         Begin VB.Label Label14 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "Ask Price"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2400
            TabIndex        =   52
            Top             =   870
            Width           =   1335
         End
         Begin VB.Label Label13 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   "Bid Price"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   960
            TabIndex        =   51
            Top             =   870
            Width           =   1455
         End
         Begin VB.Label Label12 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   " Daily High"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   6360
            TabIndex        =   50
            Top             =   870
            Width           =   1455
         End
         Begin VB.Label Label11 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   " Daily Low"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   6360
            TabIndex        =   49
            Top             =   120
            Width           =   1455
         End
         Begin VB.Label Label10 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   " Close"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   5040
            TabIndex        =   48
            Top             =   120
            Width           =   1335
         End
         Begin VB.Label Label9 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   " Open"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   3720
            TabIndex        =   47
            Top             =   120
            Width           =   1455
         End
         Begin VB.Label Label8 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   " Change"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Left            =   2400
            TabIndex        =   46
            Top             =   120
            Width           =   1335
         End
         Begin VB.Label Label7 
            BackColor       =   &H00C0C0C0&
            BorderStyle     =   1  'Fixed Single
            Caption         =   " Last Trade"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   345
            Index           =   0
            Left            =   960
            TabIndex        =   44
            Top             =   120
            Width           =   1575
         End
      End
      Begin VB.Frame ConfirmFrame 
         BackColor       =   &H80000007&
         BorderStyle     =   0  'None
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   3100
         Left            =   -71280
         TabIndex        =   32
         Top             =   400
         Width           =   5055
         Begin VB.TextBox LoopText 
            Alignment       =   1  'Right Justify
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   360
            Left            =   3840
            TabIndex        =   124
            Text            =   "1"
            Top             =   2640
            Width           =   975
         End
         Begin VB.CheckBox LoopCBut 
            BackColor       =   &H80000012&
            Caption         =   "Loop Test"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   330
            Left            =   2400
            TabIndex        =   123
            Top             =   2640
            Width           =   1215
         End
         Begin VB.CommandButton ConfirmTBUT 
            Caption         =   "Confirm"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   600
            TabIndex        =   34
            Top             =   2640
            Width           =   1335
         End
         Begin VB.TextBox TradeText 
            Appearance      =   0  'Flat
            BackColor       =   &H00E0E0E0&
            BorderStyle     =   0  'None
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   2415
            Left            =   120
            Locked          =   -1  'True
            MultiLine       =   -1  'True
            TabIndex        =   33
            Text            =   "frmMain.frx":40EC
            Top             =   120
            Width           =   4815
         End
      End
      Begin VB.Frame TradeFrame 
         BackColor       =   &H80000007&
         BorderStyle     =   0  'None
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   3100
         Left            =   -74880
         TabIndex        =   19
         Top             =   400
         Width           =   3495
         Begin VB.ComboBox TQuoteCombo 
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FF0000&
            Height          =   405
            Left            =   1080
            TabIndex        =   82
            Top             =   120
            Width           =   2055
         End
         Begin VB.CommandButton EnterTBUT 
            Caption         =   "Enter"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   1080
            TabIndex        =   31
            Top             =   2640
            Width           =   1335
         End
         Begin VB.TextBox PriceTED 
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00C00000&
            Height          =   375
            Left            =   1080
            TabIndex        =   29
            Top             =   1080
            Width           =   2055
         End
         Begin VB.Frame Frame7 
            BackColor       =   &H80000007&
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   550
            Left            =   1080
            TabIndex        =   24
            Top             =   2040
            Width           =   2055
            Begin VB.OptionButton LimitRB 
               BackColor       =   &H80000008&
               Caption         =   "Limit"
               BeginProperty Font 
                  Name            =   "MS Sans Serif"
                  Size            =   8.25
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               ForeColor       =   &H00E0E0E0&
               Height          =   375
               Left            =   1080
               TabIndex        =   26
               Top             =   120
               Width           =   855
            End
            Begin VB.OptionButton MarketRB 
               BackColor       =   &H80000008&
               Caption         =   "Market"
               BeginProperty Font 
                  Name            =   "MS Sans Serif"
                  Size            =   8.25
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               ForeColor       =   &H00E0E0E0&
               Height          =   375
               Left            =   120
               TabIndex        =   25
               Top             =   120
               Width           =   855
            End
         End
         Begin VB.Frame Frame6 
            BackColor       =   &H80000007&
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   550
            Left            =   1080
            TabIndex        =   21
            Top             =   1440
            Width           =   2055
            Begin VB.OptionButton SellRB 
               BackColor       =   &H80000007&
               Caption         =   "Sell"
               BeginProperty Font 
                  Name            =   "MS Sans Serif"
                  Size            =   8.25
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               ForeColor       =   &H00E0E0E0&
               Height          =   375
               Left            =   960
               TabIndex        =   23
               Top             =   120
               Width           =   615
            End
            Begin VB.OptionButton BuyRB 
               BackColor       =   &H80000007&
               Caption         =   "Buy"
               BeginProperty Font 
                  Name            =   "MS Sans Serif"
                  Size            =   8.25
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               ForeColor       =   &H00E0E0E0&
               Height          =   375
               Left            =   120
               TabIndex        =   22
               Top             =   120
               Width           =   615
            End
         End
         Begin VB.TextBox QuantityTED 
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00C00000&
            Height          =   405
            Left            =   1080
            TabIndex        =   20
            Top             =   600
            Width           =   2055
         End
         Begin VB.Label Label6 
            BackColor       =   &H80000007&
            Caption         =   "Price"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00E0E0E0&
            Height          =   375
            Left            =   120
            TabIndex        =   30
            Top             =   1080
            Width           =   855
         End
         Begin VB.Label Label5 
            BackColor       =   &H80000007&
            Caption         =   "Quantity"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00E0E0E0&
            Height          =   375
            Left            =   120
            TabIndex        =   28
            Top             =   600
            Width           =   855
         End
         Begin VB.Label Label3 
            BackColor       =   &H80000007&
            Caption         =   "Symbol"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00E0E0E0&
            Height          =   375
            Left            =   120
            TabIndex        =   27
            Top             =   120
            Width           =   735
         End
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid HoldingFGrid 
         Height          =   3135
         Left            =   -74940
         TabIndex        =   18
         Top             =   420
         Width           =   8715
         _ExtentX        =   15372
         _ExtentY        =   5530
         _Version        =   393216
         ForeColor       =   16711680
         Cols            =   6
         BackColorBkg    =   -2147483641
         AllowBigSelection=   0   'False
         FocusRect       =   0
         FillStyle       =   1
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   6
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid HistoryFGrid 
         Height          =   3105
         Left            =   -74880
         TabIndex        =   13
         Top             =   420
         Width           =   8655
         _ExtentX        =   15266
         _ExtentY        =   5477
         _Version        =   393216
         ForeColor       =   16711680
         Cols            =   15
         FixedCols       =   0
         BackColorBkg    =   -2147483641
         AllowBigSelection=   0   'False
         FocusRect       =   0
         FillStyle       =   1
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   15
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
      End
      Begin VB.Frame ViewFrame 
         Height          =   3135
         Left            =   -74400
         TabIndex        =   102
         Top             =   420
         Width           =   8175
         Begin VB.CheckBox DocsCBut 
            Caption         =   "View Docs"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   450
            Left            =   1620
            TabIndex        =   112
            Top             =   540
            Width           =   855
         End
         Begin VB.Frame VPanel 
            Caption         =   "Views"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   14.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   2775
            Left            =   120
            TabIndex        =   103
            Top             =   240
            Width           =   1455
            Begin VB.OptionButton V2RBut 
               Caption         =   "Order"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   115
               Top             =   720
               Width           =   855
            End
            Begin VB.OptionButton V6RBut 
               Caption         =   "QC"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   108
               Top             =   2400
               Width           =   975
            End
            Begin VB.OptionButton V5RBut 
               Caption         =   "IMDB (W)"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   450
               Left            =   120
               TabIndex        =   107
               Top             =   1920
               Width           =   1215
            End
            Begin VB.OptionButton V4RBut 
               Caption         =   "LCE"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   106
               Top             =   1560
               Width           =   975
            End
            Begin VB.OptionButton V3RBut 
               Caption         =   "IMDB (R)"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   450
               Left            =   120
               TabIndex        =   105
               Top             =   1080
               Width           =   1095
            End
            Begin VB.OptionButton V1RBut 
               Caption         =   "Top"
               BeginProperty Font 
                  Name            =   "Arial"
                  Size            =   9.75
                  Charset         =   0
                  Weight          =   400
                  Underline       =   0   'False
                  Italic          =   0   'False
                  Strikethrough   =   0   'False
               EndProperty
               Height          =   330
               Left            =   120
               TabIndex        =   104
               Top             =   360
               Width           =   1095
            End
         End
         Begin VB.TextBox ViewTEd 
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   2775
            Left            =   2520
            MultiLine       =   -1  'True
            TabIndex        =   113
            Text            =   "frmMain.frx":40F2
            Top             =   240
            Width           =   5535
         End
         Begin VB.Label Label28 
            Caption         =   "Dbl-click for large view (Picture only)"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   1215
            Left            =   1800
            TabIndex        =   114
            Top             =   1320
            Width           =   615
         End
         Begin VB.Image Image1 
            Height          =   2775
            Left            =   2640
            Stretch         =   -1  'True
            Top             =   240
            Width           =   5175
         End
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid AccountFlexGrid 
         Height          =   2565
         Left            =   120
         TabIndex        =   118
         Top             =   480
         Width           =   8655
         _ExtentX        =   15266
         _ExtentY        =   4524
         _Version        =   393216
         ForeColor       =   16711680
         Cols            =   15
         BackColorBkg    =   -2147483641
         AllowBigSelection=   0   'False
         FocusRect       =   0
         FillStyle       =   1
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         _NumberOfBands  =   1
         _Band(0).Cols   =   15
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
      End
      Begin VB.Label Label26 
         Caption         =   "Cntrl"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74880
         TabIndex        =   101
         Top             =   600
         Width           =   495
      End
      Begin VB.Label QuoteNameLabel 
         BackColor       =   &H00C0C0C0&
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -72960
         TabIndex        =   84
         Top             =   480
         Width           =   2775
      End
      Begin VB.Label Label1 
         Caption         =   "Confirmation Number:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   -74520
         TabIndex        =   64
         Top             =   3050
         Width           =   2655
      End
   End
   Begin VB.CommandButton ReAuthenticateTBUT 
      Caption         =   "Re-Authenticate"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   2160
      TabIndex        =   11
      Top             =   360
      Width           =   1695
   End
   Begin VB.Frame Frame3 
      BackColor       =   &H80000007&
      Caption         =   "Unacknowledged Trades"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00808000&
      Height          =   1355
      Left            =   4920
      TabIndex        =   9
      Top             =   1560
      Width           =   3975
      Begin VB.ListBox List4 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000B&
         CausesValidation=   0   'False
         BeginProperty Font 
            Name            =   "Fixedsys"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FF0000&
         Height          =   930
         Left            =   110
         TabIndex        =   10
         Top             =   280
         Width           =   3775
      End
   End
   Begin VB.Frame Frame2 
      BackColor       =   &H80000007&
      Caption         =   "Customer Information"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   1455
      Left            =   4920
      TabIndex        =   7
      Top             =   0
      Width           =   3975
      Begin VB.ListBox List3 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000B&
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00000080&
         Height          =   750
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Width           =   3735
      End
   End
   Begin VB.TextBox Text3 
      CausesValidation=   0   'False
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
      Top             =   1920
      Width           =   3375
   End
   Begin VB.TextBox Text4 
      CausesValidation=   0   'False
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
      Top             =   2400
      Width           =   3375
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H80000007&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2915
      Left            =   120
      TabIndex        =   2
      Top             =   0
      Width           =   4695
      Begin VB.CommandButton Command1 
         Caption         =   "About"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   3840
         TabIndex        =   111
         Top             =   360
         Width           =   735
      End
      Begin VB.ComboBox CustomerCombo 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   405
         Left            =   120
         TabIndex        =   59
         Text            =   "Customer SSN"
         Top             =   360
         Width           =   1815
      End
      Begin VB.Label Label22 
         BackColor       =   &H80000007&
         Caption         =   "Email:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00E0E0E0&
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   2400
         Width           =   855
      End
      Begin VB.Label Label21 
         BackColor       =   &H80000007&
         Caption         =   "Phone:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00E0E0E0&
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   1920
         Width           =   855
      End
      Begin VB.Label Label20 
         BackColor       =   &H80000007&
         Caption         =   "Address:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00E0E0E0&
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   1440
         Width           =   1095
      End
      Begin VB.Label Label19 
         BackColor       =   &H80000007&
         Caption         =   "Name:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00E0E0E0&
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   855
      End
   End
   Begin VB.Label Label25 
      BackColor       =   &H80000012&
      Caption         =   "Cash Available:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0E0E0&
      Height          =   375
      Left            =   5040
      TabIndex        =   81
      Top             =   3480
      Width           =   1815
   End
   Begin VB.Label Label7 
      Caption         =   "Cha"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   1
      Left            =   2160
      TabIndex        =   45
      Top             =   4920
      Width           =   1335
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000011&
      BorderWidth     =   5
      X1              =   9120
      X2              =   0
      Y1              =   3960
      Y2              =   3960
   End
   Begin VB.Label Label4 
      BackColor       =   &H80000007&
      Caption         =   "Account:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00808000&
      Height          =   375
      Left            =   240
      TabIndex        =   17
      Top             =   4080
      Width           =   1095
   End
   Begin VB.Label Label2 
      BackColor       =   &H80000007&
      Caption         =   "Portfolio Net Worth:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00E0E0E0&
      Height          =   255
      Index           =   0
      Left            =   4560
      TabIndex        =   16
      Top             =   3120
      Width           =   2295
   End
End
Attribute VB_Name = "frmMainProfile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'/***********************************************************************************\
'*************************************************************************************
'*  COM+ Hanson Brothers SDK Sample
'*  frmMain.FRM (HBTradeStation)
'*
'*  This file is provided as part of the COM+ Software Development Kit.
'*
'*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
'*  EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
'*  OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR PURPOSE.
'*
'* Copyright (C) 1999 Microsoft Corporation, All rights reserved
'**************************************************************************************
'\***********************************************************************************/

Option Explicit

Implements HBEVENTCLASSLib.INewsService
Implements HBEventClass

Private Sub BannerTimer_Timer()
    RunTicker
End Sub

Private Sub CCBut_Click()

    If CCBut.Value = 1 Then
        ViewFrame.Visible = False
        SetPanel.Visible = True
    Else
        SetPanel.Visible = False
        ViewFrame.Visible = True
    End If
    
End Sub



Private Sub ChartSymbolCombo_Click()
    SetChartInfo (Trim(frmMainProfile.ChartSymbolCombo.Text))
End Sub

Private Sub chkXML_Click()
    If chkXML.Value = 1 Then
        m_bUseXML = True
        
        If m_XMLDOM Is Nothing Then
            Set m_XMLDOM = New DOMDocument
        End If
        
        ' Disable the heirachical view if we're using XML, this needs to added later
        HBut.Enabled = False
        
        AccountFlexGrid.FixedCols = 0
        HoldingFGrid.FixedCols = 0
        PendingFlxGrid.FixedCols = 0
        
        ' Update Info
        Call UpdateInfoXML
    Else
        m_bUseXML = False
        
        If Not m_XMLDOM Is Nothing Then
            Set m_XMLDOM = Nothing
        End If
        
        HBut.Enabled = True
        
        AccountFlexGrid.FixedCols = 1
        HoldingFGrid.FixedCols = 1
        PendingFlxGrid.FixedCols = 1
        
        ' Update Info
        Call UpdateInfo
        
    End If
    
    
End Sub

Private Sub Command1_Click()
    frmAbout.Show 1
End Sub

Private Sub DeleteOrdersTBut_Click()

    If m_bStopQuote = True Then
        MsgBox ("You Must Enable Quotes from Settings before you can do this action.")
        Exit Sub
    End If
    If MsgBox("Are you Sure you want to Delete all Orders and Holdings?", vbOKCancel) = vbOK Then
    
        Dim rc As Long
        Dim sMsg As String
        Dim objAcct As HBInstitution.IAccount
        
        Set objAcct = New HBInstitution.IAccount
                
        rc = objAcct.InitTestData(INIT_ORDERS_ONLY, 0, sMsg, 0, 0)
        sMsg = "Pending Orders and holdings deleted."
        MsgBox sMsg
        
        Set objAcct = Nothing
        
    End If

End Sub

Private Sub DocsCBut_Click()
    If V1RBut.Value = True Then
            ShowInfo ("HB1")
    ElseIf V2RBut.Value = True Then
            ShowInfo ("HB2")
    ElseIf V3RBut.Value = True Then
            ShowInfo ("HB3")
    ElseIf V4RBut.Value = True Then
            ShowInfo ("HB4")
    ElseIf V5RBut.Value = True Then
            ShowInfo ("HB5")
    ElseIf V6RBut.Value = True Then
            ShowInfo ("HB6")
    End If
End Sub


Public Sub HBEventClass_NewEvent(ByVal sNewEvent As String)
    If EventCBut.Value = 1 Then
        MsgBox ("HBEventClass_NewEvent: " & sNewEvent)
    Else
        ' Not used Yet
    End If
End Sub

Private Sub ImagePanel_Click()

End Sub

Private Sub Image1_DblClick()
    frmView.Picture = Image1.Picture
    frmView.Show 1
End Sub

Public Sub INewsService_NewsHeadline(ByVal sNewsHeadline As String)
    If EventCBut.Value = 1 Then
        MsgBox ("INewsService_NewsHeadline: " & sNewsHeadline)
    Else
        ' These should be Transient Subscribed so Just the requesting Trader
        ' received headlines. Subscribe and publish code note added, but should
        ' be easily done.
        m_bNewsOk = False
        NewsCombo.AddItem (sNewsHeadline)
        NTEd.Text = "" & NewsCombo.ListCount
        NewsCombo.ListIndex = NewsCombo.ListCount - 1
        
    End If
End Sub

Public Sub INewsService_HotNews(ByVal sHotNews As String)
    If EventCBut.Value = 1 Then
        MsgBox ("INewsService_HotNews: " & sHotNews)
    Else
        ' Use HotNews for Alerts to Traders. These should be
        ' Persistently Subscribed so all Traders get them
        List3.AddItem (sHotNews)
    End If
End Sub

Public Sub SubscribeTransient()

    Dim TransColl As ICatalogCollection
    Dim Trans As ICatalogObject
    Dim Admin As Object
    
    On Error GoTo SubError

    Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")
    Set TransColl = Admin.GetCollection("TransientSubscriptions")
    
    TransColl.Populate
    
    ' Create subscription object
   
    Set Trans = TransColl.Add
    Trans.Value("Name") = "HBTransient"
    Trans.Value("EventCLSID") = "HBEventClass.HBEventClass.1"
    Trans.Value("SubscriberInterface") = Me
    TransColl.SaveChanges
    
    MsgBox ("HBEventClass Transient Subscription made")
 
Exit Sub

SubError:
    MsgBox "HB Transient Subscription Error: " & Hex$(Err.Number) & ": " & Err.Description
End Sub

Public Sub SubscribePersistent()
    
    Dim Admin As Object
    Dim Appcoll, Compcoll, Subcoll As ICatalogCollection
    Dim App, Comp, Subscription As ICatalogObject
    Dim bFound As Boolean
    Dim i As Integer
    
    On Error GoTo SubError
    
    Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")
     
    ' Create an Application to host EventClass
    Set Appcoll = Admin.GetCollection("Applications")
    
    Appcoll.Populate
    
    bFound = False
    For i = 0 To Appcoll.Count - 1
        If Appcoll.Item(i).Name = "HBSubscriber" Then
            bFound = True
        End If
    Next
    
    If bFound Then
        If MsgBox("HBSubscriber COM+ App already Created. Subscribe Again?", vbYesNo) = vbNo Then
            Exit Sub
        End If
    Else
        Set App = Appcoll.Add
        App.Value("Name") = "HBSubscriber"
        Appcoll.SaveChanges
    
        ' Install a component under the eventclass
        Admin.InstallComponent "HBSubscriber", "C:\Hanson\HBNewEvents\HBSubscriber\Debug\HBSubscriber.dll", "", ""
    
        '------------------------------------------------
        ' Create a subscription under this component
        '------------------------------------------------
        Appcoll.Populate
    End If
    
    ' Get the COMPONENTS collection
    For i = 0 To Appcoll.Count - 1
        If Appcoll.Item(i).Name = "HBSubscriber" Then
            Set Compcoll = Appcoll.GetCollection("Components", Appcoll.Item(i).Key)
        End If
    Next
    
    Compcoll.Populate
    
    ' Get the SUBSCRIPTIONS collection
    For i = 0 To Compcoll.Count - 1
        If Compcoll.Item(i).Name = "HBSubscriber.HBSubscriber.1" Then
        
            Set Subcoll = Compcoll.GetCollection("SubscriptionsForComponent", Compcoll.Item(i).Key)
        
            Subcoll.Populate
    
            ' Set the properties on the subscription
                
            Set Subscription = Subcoll.Add
            Subscription.Value("PublisherID") = "Hanson"
            Subscription.Value("Enabled") = True
            Subscription.Value("Name") = "HB Test Subscription"
    
            Subcoll.SaveChanges
                
            MsgBox ("HB Test Subscription Created")
        
        End If
    Next

Exit Sub

SubError:
MsgBox "Error: You probably have a 'HBSubscription COM+ Application already added. Delete it and try again. NOTE: Make sure you refresh (F5) the COM+ Applications First so you can see them." & Hex$(Err.Number) & ": " & Err.Description

End Sub

Private Sub MSHFlexGrid1_Click()

End Sub

Private Sub LoopCBut_Click()
    If LoopCBut.Value = 1 Then
        LoopText.Visible = True
        ConfirmTBUT.Caption = "Run Test"
    Else
        LoopText.Visible = False
        ConfirmTBUT.Caption = "Confirm"
    End If
End Sub

Private Sub NewsCombo_Click()
    If EventCBut.Value = 1 Or m_bNewsOk Then
        MsgBox (NewsCombo.Text)
    End If
    m_bNewsOk = True
End Sub



Private Sub ODBCCBut_Click()
    If ODBCCBut.Value = 1 Then
        MsgBox ("ODBC Quotes not tested ..")
    End If
End Sub

Private Sub PublishTBut_Click()

Dim HB As IHB
Dim NewsService As INewsService

On Error GoTo check
Set HB = CreateObject("HBEventClass.HBEventClass.1")
Set NewsService = HB

NewsService.NewsHeadline (NewsTEd.Text)
Exit Sub

check:
MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub

Private Sub InstallEC_Click()
Dim Admin As Object
Dim Appcoll, Compcoll As ICatalogCollection
Dim App, Comp, Itrobj, Eventobj As ICatalogObject
Dim bFound As Boolean
Dim i As Integer
Dim Var As String

On Error GoTo check

Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")

' Create an Application to host EventClass
Set Appcoll = Admin.GetCollection("Applications")
Appcoll.Populate

bFound = False
For i = 0 To Appcoll.Count - 1
    If Appcoll.Item(i).Name = "HBEventClass" Then
        bFound = True
    End If
Next

If bFound Then
    MsgBox ("HBEventClassApp COM+ App already Created")
    Exit Sub
Else
    Set App = Appcoll.Add
    App.Value("Name") = "HBEventClass"

    Appcoll.SaveChanges

    ' Install the eventclass under the created application
    Var = "C:\Hanson\HBNewEvents\HBEventClass\Debug\HBEventClass.dll"
    Admin.InstallEventClass "HBEventClass", Var, "", ""

    ' Set other EventClass properties
    Appcoll.Populate
End If

For i = 0 To Appcoll.Count - 1
    If Appcoll.Item(i).Name = "HBEventClass" Then
    Set Compcoll = Appcoll.GetCollection("Components", Appcoll.Item(i).Key)
    Compcoll.Populate
    End If
Next
    

For i = 0 To Compcoll.Count - 1
    If Compcoll.Item(i).Name = "HBEventClass.HBEventClass.1" Then
    Set Eventobj = Compcoll.Item(i)
    Eventobj.Value("FireInParallel") = True
    Eventobj.Value("AllowInprocSubscribers") = True
    Eventobj.Value("PublisherID") = "Hanson"
    'Eventobj.Value("MultiInterfacePublisherFilterCLSID") = "HBFilter.HBFilter.1"
    
    Compcoll.SaveChanges
    
    MsgBox ("HBEventClass COM+ App Created")
    
    End If
Next

Exit Sub
check:
MsgBox Hex$(Err.Number) & ": " & Err.Description

End Sub

Private Sub AccountsCombo_Click()
    If Not m_bUseXML Then
        Call UpdateInfo
    Else
        Call UpdateInfoXML
    End If
End Sub

Private Sub UpdateInfo()

    ' This Routine will be replaced shortly using the XML Stream. This will
    ' Replace the multiple  rpcs below with a single call which will return
    ' an XML stream. See HBXMLServer and HBXMLClient.exe for a view of the XML Stream.

    ' Create Copy of this routine for XML but put check for XML check box here to call XMLUpdateINfo
    
    Dim sAcctNum
    Dim sMsg As String
    Dim Holdings As Variant
    Dim cNetWorth As Variant
    Dim cCash As Variant
    Dim cCashDebit As Variant
    Dim rc As Long
    Dim cTotalNet As Double
    Dim cTotalCash As Double
    
    'EnableForm (False)
    
    sAcctNum = Trim(AccountsCombo.Text)
    
    If m_bStartAllObjects = False Then
        Dim objAcct As New HBInstitution.IAccount
        rc = objAcct.GetAccountNetWorth(sAcctNum, cNetWorth, cCash, cCashDebit, sMsg)
        Set objAcct = Nothing
    Else
        rc = m_objAcct.GetAccountNetWorth(sAcctNum, cNetWorth, cCash, cCashDebit, sMsg)
    End If
 
    If rc = SUCCESS Then
        'AccountNetTED.Text = cNetWorth
    
        TradeFrame.Visible = True
        ConfirmFrame.Visible = True
        Call FillFlxHolding(sAcctNum)
        
        If HBut.Value = 0 Then
            Call FillFlxAccount(customerSSN, AccountsCombo.ListIndex)
        Else
            Call FillFlxHistoryHierarchy(customerSSN, AccountsCombo.ListIndex)
        End If
        Call FillFlxHistory(sAcctNum, AccountsCombo.ListIndex)
        
        Call FillFlxPending(sAcctNum)
        
        EnableForm (True)
    ElseIf rc = NO_RECORDS_FOUND Then
        'MsgBox ("No Account Exist")
    Else
        MsgBox ("Account " & sAcctNum & " is in error: " & sMsg)
    End If
    
    If m_bStartAllObjects = False Then
        Dim objCust As New HBInstitution.ICustomer
        rc = objCust.GetTotalNetWorth(customerSSN, cTotalNet, cTotalCash, sMsg)
        Set objCust = Nothing
    Else
        rc = m_objCust.GetTotalNetWorth(customerSSN, cTotalNet, cTotalCash, sMsg)
    End If
    
    TotalNetTED.Text = FormatCurrency(cTotalNet)
    TotalCashTED.Text = FormatCurrency(cTotalCash)
       
End Sub

Private Sub UpdateInfoXML()

    ' This Routine will be replaced shortly using the XML Stream. This will
    ' Replace the multiple  rpcs below with a single call which will return
    ' an XML stream. See HBXMLServer and HBXMLClient.exe for a view of the XML Stream.

    ' Create Copy of this routine for XML but put check for XML check box here to call XMLUpdateINfo
    
    Dim sAcctNum
    Dim sMsg As String
    Dim Holdings As Variant
    Dim cNetWorth As Variant
    Dim cCash As Variant
    Dim cCashDebit As Variant
    Dim rc As Long
    Dim cTotalNet As Double
    Dim cTotalCash As Double
    Dim strXMLStream As String
    Dim vTotalNet As Variant
    Dim vTotalCash As Variant
    Dim xmlCurNode As MSXML.IXMLDOMNode

    sAcctNum = Trim(AccountsCombo.Text)
    
    If m_bStartAllObjects = False Then
        Dim objAcct As New HBInstitution.IAccount
        
        rc = objAcct.GetXMLAccounts(customerSSN, strXMLStream, sMsg)
        Set objAcct = Nothing
    Else
        rc = m_objAcct.GetXMLAccounts(customerSSN, strXMLStream, sMsg)
    End If
 
    If rc = SUCCESS Then
        
        m_XMLDOM.loadXML (strXMLStream)
        
        TradeFrame.Visible = True
        ConfirmFrame.Visible = True
        Call FillFlxHoldingXML(sAcctNum)
        
        If HBut.Value = 0 Then
            Call FillFlxAccountXML(customerSSN, AccountsCombo.ListIndex)
        Else
            ' Not Yet Implemented
            Call FillFlxHistoryHierarchyXML(customerSSN, AccountsCombo.ListIndex)
        End If
        
        Call FillFlxHistoryXML(sAcctNum, AccountsCombo.ListIndex)
        
        Call FillFlxPendingXML(sAcctNum)
        
        EnableForm (True)
    Else
        MsgBox ("Account " & sAcctNum & " is in error: " & sMsg)
    End If
    
    ' Parse XML to get Total Net Value and Total Cash Available ...
    Call XML_FindTopLevelNode(m_XMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "total_networth", "Accounts", sAcctNum, xmlCurNode)
    vTotalNet = XML_GetValue(xmlCurNode, "total_networth", "Accounts")
    vTotalCash = XML_GetValue(xmlCurNode, "total_cash", "Accounts")
    
    If vTotalNet <> "" Then
        TotalNetTED.Text = FormatCurrency(vTotalNet)
    Else
        TotalNetTED.Text = "$0.00"
    End If
    
    If Not vTotalCash = Empty Then
        TotalCashTED.Text = FormatCurrency(vTotalCash)
    Else
        TotalCashTED.Text = "$0.00"
    End If
       
End Sub

Sub FillFlxHolding(ByVal cAcctNum As String)
  
  Dim rst As ADODB.Recordset
  Dim rc As Long
  Dim sMsg As String
  Dim rs As Variant
  
  Dim objCust As HBInstitution.ICustomer

  If m_bStartAllObjects = False Then
    Set objCust = New HBInstitution.ICustomer
    rc = objCust.CalcHolding(cAcctNum, rs, sMsg)
  Else
    ' Update the Acct information with latest quotes
    rc = m_objCust.CalcHolding(cAcctNum, rs, sMsg)
  End If
  
  ' Ignore result set (acct has been updated)
  Set rs = Nothing
  
  If rc <> SUCCESS And rc <> NO_RECORDS_FOUND Then
      frmMainProfile.SSTab1.TabEnabled(1) = False
      frmMainProfile.HoldingFGrid.Visible = False
      If rc = NO_RECORDS_FOUND Then
        'MsgBox ("No Holdings Found")
      Else
        MsgBox (sMsg)
      End If
      Exit Sub
  End If
    
  If m_bStartAllObjects = False Then
    rc = objCust.GetHoldingHierarchy(cAcctNum, rst, sMsg)
    Set objCust = Nothing
  Else
    rc = m_objCust.GetHoldingHierarchy(cAcctNum, rst, sMsg)
  End If
    
  If rc <> SUCCESS Then
      Set rst = Nothing
      frmMainProfile.SSTab1.TabEnabled(1) = False
      frmMainProfile.HoldingFGrid.Visible = False
      If rc = NO_RECORDS_FOUND Then
        'MsgBox ("No Holdings Found")
      Else
        MsgBox (sMsg)
      End If
      Exit Sub
  End If
    
    frmMainProfile.SSTab1.TabEnabled(1) = True
    frmMainProfile.HoldingFGrid.Visible = True

    With frmMainProfile.HoldingFGrid
    Set .DataSource = rst
      On Error Resume Next
     .ColWidth(0) = 0
      
      If rst.RecordCount > 0 Then
          
          .TextMatrix(0, 1) = "Symbol"
          .ColWidth(1) = 1300
          .TextMatrix(0, 2) = "Quantity"
          .ColWidth(2) = 1100
          .TextMatrix(0, 3) = "Net Worth"
          .ColWidth(3) = 1500
          .TextMatrix(0, 4) = "Reconciled"
          .ColWidth(4) = 1400
          .TextMatrix(0, 5) = "Current Price"
          .ColWidth(5) = 1500
          .TextMatrix(0, 6) = "Current Value"
          .ColWidth(6) = 1880
          .CollapseAll 1
      End If
      'Collapse the rows
      .col = 2
      .row = 1
      Do While True
        .RowExpanded = False
        .row = .row + 1
        If Err Then Exit Do
      Loop
      .row = 1
      .col = 0
    End With
    
  Set rst = Nothing
  
End Sub


Sub FillFlxHistoryHierarchy(ByVal sSSN As String, ByVal index As Long)

    Dim rst As ADODB.Recordset
    Dim rsHoldings As Variant
    Dim sMsg As String
    Dim rc As Long
    Dim i As Integer
    Dim r As Integer
    
    If m_bStartAllObjects = False Then
        Dim objCust As New HBInstitution.ICustomer
        rc = objCust.GetHistoryHierarchy(sSSN, rst, sMsg)
        Set objCust = Nothing
    Else
        rc = m_objCust.GetHistoryHierarchy(sSSN, rst, sMsg)
    End If
    
    If rc <> SUCCESS Then
        Set rst = Nothing
        frmMainProfile.SSTab1.TabEnabled(2) = False
        frmMainProfile.AccountFlexGrid2.Visible = False
      If rc = NO_RECORDS_FOUND Then
        'MsgBox ("No History Orders Found")
      Else
        'MsgBox (sMsg)
      End If
      Exit Sub
    End If
    
    frmMainProfile.HBut.Visible = True
    frmMainProfile.SSTab1.TabEnabled(2) = True
    frmMainProfile.AccountFlexGrid2.Visible = True
    frmMainProfile.ReportTBUT.Visible = True
 
    With frmMainProfile.AccountFlexGrid2
    
    Set .DataSource = rst
      On Error Resume Next
      
      Do While True
        .RowExpanded = False
        .row = .row + 1
        If Err Then Exit Do
      Loop
      .row = 1
      .col = 0
   
    End With
   
  Set rst = Nothing
  
End Sub

Sub FillFlxPending(ByVal sAcctNum As String)
  
    Dim rst As ADODB.Recordset
    Dim sMsg As String
    Dim rc As Long
    Dim X As Long

   If m_bStartAllObjects = False Then
        Dim objAcct As New HBInstitution.IAccount
        rc = objAcct.GetPendingHierarchy(sAcctNum, rst, sMsg)
        Set objAcct = Nothing
   Else
       rc = m_objAcct.GetPendingHierarchy(sAcctNum, rst, sMsg)
   End If
   
   If rc <> SUCCESS Then
      Set rst = Nothing
      frmMainProfile.SSTab1.TabEnabled(4) = False
      frmMainProfile.PendingFlxGrid.Visible = False
      If rc = NO_RECORDS_FOUND Then
        'MsgBox ("No Pending Orders Found")
      Else
        'MsgBox (sMsg)
      End If
      Exit Sub
    End If
    
    frmMainProfile.SSTab1.TabEnabled(4) = True
    frmMainProfile.PendingFlxGrid.Visible = True
    frmMainProfile.SettleTBUT.Visible = True
    frmMainProfile.SettleTED.Visible = True
    frmMainProfile.Label1.Visible = True
        
    With frmMainProfile.PendingFlxGrid
    
    ' This is a ADODC and populates automatically
    
    Set .DataSource = rst
    
      On Error Resume Next
      .ColWidth(0) = 0
      If rst.RecordCount > 0 Then
          
          ' Populate Headings
          .TextMatrix(0, 1) = "Confirm #"
          .ColWidth(1) = 1550
          .TextMatrix(0, 2) = "Symbol"
          .ColWidth(2) = 1000
          .TextMatrix(0, 3) = "Quantity"
          .ColWidth(3) = 1200
          .TextMatrix(0, 4) = "Confirm Date"
          .ColWidth(4) = 1640
          .TextMatrix(0, 5) = "Limit Price"
          .ColWidth(5) = 1300
          .TextMatrix(0, 6) = "Acct Number"
          .ColWidth(6) = 1700
          .CollapseAll 1
      End If
      
      'Collapse the rows
      .col = 2
      .row = 1
      
      Do While True
        .RowExpanded = False
        .row = .row + 1
        If Err Then Exit Do
      Loop
      .row = 1
      .col = 0
    End With
   
  Set rst = Nothing
  
End Sub

Sub FillFlxAccount(ByVal sSSN As String, ByVal index As Long)
  
    Dim rst As ADODB.Recordset
    Dim sMsg As String
    Dim rc As Long

    If m_bStartAllObjects = False Then
        Dim objCust As New HBInstitution.ICustomer
        rc = objCust.GetAccountsDetails(sSSN, rst, sMsg)
        Set objCust = Nothing
    Else
        rc = m_objCust.GetAccountsDetails(sSSN, rst, sMsg)
    End If
    
    If rc <> SUCCESS Then
      Set rst = Nothing
      frmMainProfile.SSTab1.TabEnabled(0) = False
      frmMainProfile.AccountFlexGrid.Visible = False
      If rc = NO_RECORDS_FOUND Then
        'MsgBox ("No Account Orders Found")
      Else
        'MsgBox (sMsg)
      End If
      Exit Sub
    End If
    
    frmMainProfile.SSTab1.TabEnabled(0) = True
    frmMainProfile.AccountFlexGrid.Visible = True
    frmMainProfile.HBut.Visible = True
    frmMainProfile.ReportTBUT.Visible = True
    
    With frmMainProfile.AccountFlexGrid
    Set .DataSource = rst
      On Error Resume Next
      .ColWidth(0) = 0
      If rst.RecordCount > 0 Then
          
          .TextMatrix(0, 1) = "Account #"
          .ColWidth(1) = 1350
          .TextMatrix(0, 2) = "Type"
          .ColWidth(2) = 600
          .TextMatrix(0, 3) = "Cash"
          .ColWidth(3) = 1600
          .TextMatrix(0, 4) = "Cash Debit"
          .ColWidth(4) = 1600
          .TextMatrix(0, 5) = "Net Worth"
          .ColWidth(5) = 1600
          .TextMatrix(0, 6) = "Cash Avail"
          .ColWidth(6) = 1880
          .CollapseAll 1
      End If
      'Collapse the rows
      .col = 2
      .row = 1
      Do While True
        .RowExpanded = False
        .row = .row + 1
        If Err Then Exit Do
      Loop
      .row = 1
      .col = 0
    End With
   
  Set rst = Nothing
  
End Sub

Private Sub ChartTBut_Click()
    frmMainProfile.chtReport.Visible = True
    Call ChartRecords
End Sub

Private Sub ExitTBUT_Click()
    Call DeactivateAllObjects
    End
End Sub

Private Sub ConfirmTBUT_Click()

    On Error GoTo ErrorHandler:
    
    ConfirmTBUT.Enabled = False
    
    If LoopCBut.Value = 1 Then
        Dim cnt As Long
        Dim i As Long
        cnt = CLng(LoopText.Text)
        Dim tStart As Double
        Dim tEnd As Double
        tStart = Timer()
        
        For i = 0 To cnt - 1
            Verify_Enter (ENTER_ORDER)
            LoopText.Text = i
        Next
        
        tEnd = Timer()
        
        LoopText.Text = cnt
        MsgBox ("Done Adding " & cnt & " Orders. Time Lapse = " & Format(tEnd - tStart, "#######.##") & " seconds. Rate = " & Format((cnt / (tEnd - tStart)), "#######.##") & " orders/sec")
        If Not m_bUseXML Then
            Call UpdateInfo
        Else
            Call UpdateInfoXML
        End If
    Else
        Verify_Enter (ENTER_ORDER)
    End If
    
    FillAcks (customerSSN)
    
    Exit Sub

ErrorHandler:

    Call HandleError("Confirm Order")
    Resume Next
    
End Sub

Private Sub CustomerCombo_Click()

  Dim sSSN As String
  Dim rc As Long
  
    sSSN = CustomerCombo.Text
    
    If m_bStartAllObjects = False Then
        Dim objCust As New HBInstitution.ICustomer
        rc = objCust.IsCustomer(sSSN)
        Set objCust = Nothing
    Else
        rc = m_objCust.IsCustomer(sSSN)
    End If
    
    If rc <> SUCCESS Then
        MsgBox ("" & sSSN & " is NOT a Valid Customer SSN!")
    Else
        customerSSN = sSSN
        Call FillCustomer(sSSN)
    End If
  
End Sub


Private Sub EnterTBUT_Click()
    Verify_Enter (VERIFY_ORDER)
End Sub


Private Sub Verify_Enter(ByVal DoVerify As Long)
   
    Dim sMsg As String
    Dim sFullName As String
    Dim rc As Long
    Dim sAccount As String
    Dim sSymbol As String
    Dim iTradeAction As Integer
    Dim iTradeType As Integer
    Dim iShares As Integer
    Dim cBidPrice As Currency
    Dim cAskPrice As Currency
    Dim iConfirmNumber As Integer
    Dim Price As Currency
    
    Dim objOrder As HBInstitution.IOrder
    
    On Error GoTo ErrorHandler
    
    sAccount = AccountsCombo.Text
    
    sSymbol = Trim(TQuoteCombo.Text)
    If Trim(TQuoteCombo.Text) = "" Then
        MsgBox ("Please Enter a Symbol")
        Exit Sub
    End If
    
    If BuyRB.Value = True Then
        iTradeAction = BUY
    Else
        iTradeAction = SELL
    End If
    
    Price = 0
    If MarketRB.Value = True Then
        iTradeType = MARKET_ORDER
    Else
        iTradeType = LIMIT_ORDER
        If PriceTED.Text <> "" Then
            Price = CCur(PriceTED.Text)
        End If
    End If
    
    If QuantityTED.Text = "" Then
        iShares = 0
    Else
        iShares = CInt(QuantityTED.Text)
    End If
    
    ' quotes are turned off (for basic perf testing)
    
    If m_bStopQuote = True Then
        cBidPrice = 1
        cAskPrice = 1
    Else
        If m_bStartAllObjects = False Then
            Dim objQuote As New HBExchange.IQuote
            rc = objQuote.GetSymbolInfo(sSymbol, sFullName, sMsg)
            Set objQuote = Nothing
        Else
            rc = m_objQuote.GetSymbolInfo(sSymbol, sFullName, sMsg)
        End If
        
        If rc <> SUCCESS Then
            ConfirmTBUT.Enabled = False
             TradeText.Text = "Symbol " & sSymbol & " Does Not Exist!"
            Exit Sub
        End If
        
        ' Get the current quote and return the bid and ask price
        rc = UpdateQuoteFields(sSymbol, cBidPrice, cAskPrice)
        If rc <> SUCCESS Then
             ConfirmTBUT.Enabled = False
             TradeText.Text = "Symbol " & sSymbol & " Does Not Exist!"
            Exit Sub
        End If
    End If
    
    If DoVerify = VERIFY_ORDER Then

        If m_bStartAllObjects = False Then
            Set objOrder = New HBInstitution.IOrder
            rc = objOrder.Verify(sAccount, sSymbol, iShares, Price, cBidPrice, cAskPrice, iTradeAction, iTradeType, sMsg)
            Set objOrder = Nothing
        Else
            rc = m_objOrder.Verify(sAccount, sSymbol, iShares, Price, cBidPrice, cAskPrice, iTradeAction, iTradeType, sMsg)
        End If
       
        If rc <> SUCCESS Then
            ConfirmTBUT.Enabled = False
            TradeText.Text = sMsg
            Exit Sub
        End If
        
        ConfirmTBUT.Enabled = True
        
    ElseIf DoVerify = ENTER_ORDER Then
        
        ' This is a transacted call. If failure, it will abort and
        ' any changed data (in Holding table or ProcessPending table)
        ' will be Rolled back
        
        'Exit Sub
        
        If m_bStartAllObjects = False Then
            Set objOrder = New HBInstitution.IOrder
            rc = objOrder.Execute(customerSSN, sAccount, sSymbol, iShares, Price, cBidPrice, cAskPrice, iTradeAction, iTradeType, iConfirmNumber, m_bQueued, sMsg)
            Set objOrder = Nothing
        Else
            rc = m_objOrder.Execute(customerSSN, sAccount, sSymbol, iShares, Price, cBidPrice, cAskPrice, iTradeAction, iTradeType, iConfirmNumber, m_bQueued, sMsg)
        End If
        
       If rc <> SUCCESS Then
            ConfirmTBUT.Enabled = False
            TradeText.Text = "Enter Order Failed. " & sMsg
            Exit Sub
        Else
            ' Order Entered Successfully
            sMsg = "Order Entered Successfully. Your Confirmation Number is " & iConfirmNumber
            
            ' Update the Pending Information in the UI if not executing a test
            If LoopCBut.Value = 0 Then
                If Not m_bUseXML Then
                    Call UpdateInfo
                Else
                    Call UpdateInfoXML
                End If
            End If
        End If
    Else
        TradeText.Text = "Unknown Command"
        Exit Sub
    End If
    
    TradeText.Text = sMsg
    
    Exit Sub
    
ErrorHandler:

    ' We are not happy
    MsgBox "Error Handling Order: Make sure the HBExchange Component is marked as Queued. " & sMsg & ". " & Err.Description
    
End Sub

Sub FillAcks(ByVal sSSN As String)

    Dim rc As Integer
    Dim i As Integer
    Dim sAction As String
    Dim str As String
    Dim sMsg As String
    
    If m_bStartAllObjects = False Then
        Dim objCust As New HBInstitution.ICustomer
        rc = objCust.GetNonAcknowledgedTrades(sSSN, nakTrades, sMsg)
        Set objCust = Nothing
    Else
        rc = m_objCust.GetNonAcknowledgedTrades(sSSN, nakTrades, sMsg)
    End If
    
    frmMainProfile.List4.Clear
    
    If rc = SUCCESS Then
        For i = 0 To UBound(nakTrades, 2)
            If nakTrades(13, i) = BUY Then
                sAction = "B"
            ElseIf nakTrades(13, i) = SELL Then
                sAction = "S"
            Else
                sAction = "?"
            End If
            ' Confirm# + Action + Quantity + Symbol
            str = StringPad(Trim(nakTrades(17, i)), 6, " ")
            str = str & ":"
            str = str & StringPad(sAction, 2, " ")
            str = str & StringPad(Trim(nakTrades(3, i)), 6, " ")
            str = str & StringPad(Trim(nakTrades(2, i)), 5, " ")
            str = str & StringPad(Trim(nakTrades(11, i)), 10, " ")
            
            frmMainProfile.List4.AddItem (str)
        Next
    End If
    
End Sub

Sub frmMainProfile_()

End Sub
Sub FillCustomer(ByVal sSSN As String)
    'Customer
  
    Dim rc As Long
    Dim bFlag As Boolean
    Dim str As String
    Dim custType As String
    Dim custName As String
    Dim address As String
    Dim phone As String
    Dim email As String
    Dim sMsg As String
    Dim cTotalNet As Currency
    Dim cTotalCash As Currency
    Dim i As Integer
    Dim Accounts As Variant
    Dim cType As Integer
    
    Dim objCust As HBInstitution.ICustomer

    EnableForm (False)
    
    If m_bStartAllObjects = False Then
        Set objCust = New HBInstitution.ICustomer
        rc = objCust.GetCustomerInfo(sSSN, custType, custName, address, phone, email, sMsg)
    Else
        rc = m_objCust.GetCustomerInfo(sSSN, custType, custName, address, phone, email, sMsg)
    End If
    
    frmMainProfile.Text1 = custName
    frmMainProfile.Text2 = address
    frmMainProfile.Text3 = phone
    frmMainProfile.Text4 = email
    
    If custType = "" Then
        cType = CUSTOMER
    Else
        cType = CInt(custType)
    End If
    
    'Alerts
    If m_bStartAllObjects = False Then
       rc = objCust.GetAlerts(sSSN, alerts, sMsg)
    Else
        rc = m_objCust.GetAlerts(sSSN, alerts, sMsg)
    End If
    
    frmMainProfile.List3.Clear
    
    ' Add Customer Info - followed by any Alerts (not yet enabled in Events)
   
    If customerType = TRADER Then
            ReAuthenticateTBUT.Visible = True
            frmMainProfile.List3.AddItem ("Logged in as TRADER:")
    ElseIf customerType = REPRESENTATIVE Then
            ReAuthenticateTBUT.Visible = True
            frmMainProfile.List3.AddItem ("Logged in as REPRESENTATIVE:")
    ElseIf customerType = CUSTOMER Then
            ReAuthenticateTBUT.Visible = False
            frmMainProfile.List3.AddItem ("Logged in as Customer:")
    Else
        frmMainProfile.List3.AddItem ("Logged in as UNKNOWN")
    End If
    
    If cType = TRADER Then
        frmMainProfile.List3.AddItem (" TRADER Account Selected")
    ElseIf cType = REPRESENTATIVE Then
        frmMainProfile.List3.AddItem (" REPRESENTATIVE Account Selected")
    ElseIf cType = CUSTOMER Then
        frmMainProfile.List3.AddItem (" CUSTOMER Account Selected")
    Else
        frmMainProfile.List3.AddItem (" Select Customer ...")
    End If
    
'   GetAlerts doesn't set the rc yet
    If rc = SUCCESS Then
        For i = 0 To UBound(alerts, 2)
            frmMainProfile.List3.AddItem (alerts(2, i))
        Next i
    End If
    
    Set alerts = Nothing
    
    Call FillAcks(sSSN)
    
    If m_bStartAllObjects = False Then
        rc = objCust.GetAccounts(sSSN, Accounts, sMsg)
    Else
        rc = m_objCust.GetAccounts(sSSN, Accounts, sMsg)
    End If
 
    frmMainProfile.AccountsCombo.Clear
    If rc = SUCCESS Then
        While (Not Accounts.EOF)
            frmMainProfile.AccountsCombo.AddItem (Accounts("acctNumber"))
            Accounts.MoveNext
        Wend
    End If
    
    Set Accounts = Nothing
    
    If m_bStartAllObjects = False Then
        rc = objCust.GetTotalNetWorth(sSSN, cTotalNet, cTotalCash, sMsg)
        Set objCust = Nothing
    Else
        rc = m_objCust.GetTotalNetWorth(sSSN, cTotalNet, cTotalCash, sMsg)
    End If
    
    TotalNetTED.Text = FormatCurrency(cTotalNet)
    TotalCashTED.Text = FormatCurrency(cTotalCash)

End Sub

Private Function UpdateQuoteFields(ByVal sSymbol As String, ByRef cBidPrice As Variant, ByRef cAskPrice As Variant) As Long
    
    If m_bStopQuote = True Then
         UpdateQuoteFields = SUCCESS
         Exit Function
    End If
    
    Dim rc As Long
    
    Dim NetChange As Double
    Dim OpenPrice As Currency
    Dim ClosePrice As Currency
    Dim DailyHigh As Currency
    Dim DailyLow As Currency
    Dim askPrice As Currency
    Dim bidPrice As Currency
    Dim LastTradePrice As Currency
    Dim bidSize As Long
    Dim askSize As Long
    Dim QuoteTime As Date
    Dim LastTradeTime As Date
    Dim closeDate As Date
    Dim sMsg As String
    
    UpdateQuoteFields = FAILED
    
    If Trim(sSymbol) = "" Then
        Exit Function
    End If
    
    If m_bStartAllObjects = False Then
        Dim objQuote As New HBExchange.IQuote
        If ODBCCBut.Value = 1 Then
            rc = objQuote.RetrieveODBCEx(Trim(sSymbol), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        Else
            rc = objQuote.RetrieveEx(Trim(sSymbol), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        End If
        Set objQuote = Nothing
    Else
        If ODBCCBut.Value = 1 Then
            rc = objQuote.RetrieveODBCEx(Trim(sSymbol), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        Else
            rc = m_objQuote.RetrieveEx(Trim(sSymbol), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        End If
    End If
    
    If rc = SUCCESS Then
    
        LastPriceTED.Text = FormatCurrency(LastTradePrice)
        ChangeTED.Text = "" & NetChange & " %"
        OpenPriceTED.Text = FormatCurrency(CDec(OpenPrice))
        PrevCloseTED.Text = FormatCurrency(ClosePrice)
        DailyLowTED.Text = FormatCurrency(DailyLow)
        DailyHighTED.Text = FormatCurrency(DailyHigh)
        BidPriceTED.Text = FormatCurrency(bidPrice)
        AskPriceTED.Text = FormatCurrency(askPrice)
        BidSizeTED.Text = bidSize
        AskSizeTED.Text = askSize
        
        cBidPrice = bidPrice
        cAskPrice = askPrice
    
    End If
    
    UpdateQuoteFields = rc
    
End Function


Private Sub GetNewsTBUT_Click()
   MsgBox ("No News Avaliable at this Time")
End Sub

Private Sub ForceQuoteTBUT_Click()
    
    If m_bStopQuote = True Then
        MsgBox ("Quotes are turned Off. Go to Settings to Enable Quotes.")
        Exit Sub
    End If
    
    Dim sSymbol As String
    Dim rc As Long
    Dim cBidPrice As Currency
    Dim cAskPrice As Currency
     
    sSymbol = Trim(QuoteCombo.Text)
    
    If sSymbol = "" Then
        MsgBox ("Please Select a Quote First")
        Exit Sub
    End If
    
    rc = UpdateQuoteFields(sSymbol, cBidPrice, cAskPrice)
    If rc <> SUCCESS Then
        frmMainProfile.QuoteTimer.Enabled = False
        Exit Sub
    End If
    
    RunTicker
    
    frmMainProfile.QuoteTimer.Enabled = True
    
End Sub

Private Sub CInitBut_Click()

    If m_bStopQuote = True Then
        MsgBox ("You Must Enable Quotes from Settings before you can do this action.")
        Exit Sub
    End If
    
    If MsgBox("Are you Sure you want to re-initialize the Customer and Account Information?", vbOKCancel) = vbOK Then
        
        Dim rc As Long
        Dim sMsg As String
        
        Dim sym_len As Long
        
        If TestCBut.Value = 1 Then
            sym_len = CLng(Trim(TestTEd.Text))
        Else
            sym_len = 0
        End If
        
        If m_bStartAllObjects = False Then
            Dim objAcct As HBInstitution.IAccount
            Set objAcct = New HBInstitution.IAccount
            rc = objAcct.InitTestData(INIT_CUSTOMER, 1, sMsg, 1, sym_len)
            Set objAcct = Nothing
        Else
            rc = m_objAcct.InitTestData(INIT_CUSTOMER, 1, sMsg, 1, sym_len)
        End If
     
        If rc <> SUCCESS Then
            MsgBox sMsg
        Else
            Call FillForm
            MsgBox "Customer Account tables re-initialized"
        End If
    
        Call FillCustomer(CustomerCombo.Text)
        
            If Not m_bUseXML Then
                Call UpdateInfo
            Else
                Call UpdateInfoXML
            End If
    End If
    
End Sub

Private Sub HBut_Click()
 
    If HBut.Value = 0 Then
        frmMainProfile.AccountFlexGrid.Visible = True
        frmMainProfile.AccountFlexGrid2.Visible = False
        Call FillFlxAccount(customerSSN, AccountsCombo.ListIndex)
    Else
        frmMainProfile.AccountFlexGrid.Visible = False
        frmMainProfile.AccountFlexGrid2.Visible = True
        Call FillFlxHistoryHierarchy(customerSSN, AccountsCombo.ListIndex)
    End If

End Sub

Private Sub LimitRB_Click()
    If LimitRB.Enabled = True Then
        PriceTED.BackColor = &H80000005
        PriceTED.Enabled = True
    End If
End Sub

Private Sub MarketRB_Click()
    If MarketRB.Enabled = True Then
        PriceTED.BackColor = &HFF&
        PriceTED.Enabled = False
    End If
End Sub

Private Sub List4_Click()
    Dim str As String
    Dim rc As Long
    Dim ListIndx As Integer
    Dim ListCnt As Integer
    Dim sMsg As String
    Dim objOrder As HBInstitution.IOrder
    
    ListIndx = frmMainProfile.List4.ListIndex

    If ListIndx >= 0 Then
        ' Confirm# + Symbol + Quantity + Action
        
        str = Trim(nakTrades(17, ListIndx))
        
        If m_bStartAllObjects = False Then
            Set objOrder = New HBInstitution.IOrder
            rc = objOrder.Acknowledge(CInt(str), sMsg)
            Set objOrder = Nothing
        Else
            rc = m_objOrder.Acknowledge(CInt(str), sMsg)
        End If
        
        If rc = SUCCESS Then
            frmMainProfile.List4.RemoveItem (ListIndx)
            ListCnt = frmMainProfile.List4.ListCount
        End If
        
    End If
End Sub

Private Sub ObjectCBut_Click()
    ' Activate All Objects
    If ObjectCBut.Value = 1 Then
        m_bStartAllObjects = True
        Call ActivateAllObjects
    Else
        m_bStartAllObjects = False
        Call DeactivateAllObjects
    End If
    
End Sub



Private Sub QueueCBut_Click()

    If QueueCBut.Value = 1 Then
        m_bQueued = True
    Else
        MsgBox ("If Serialized (i.e., queued set to unchecked) you will receive a timeout (particularly from HBFeed). This is due to the HBInstitution.IOrder.Execute transaction resulting in a lock condition. I.E., where the same record used to create an order in HBInstitution is being later updated within the same transaction. Queuing isolates the transaction and this scenario is nicely resolved. This mode is left to illustrate a serialization issue and is used to enable debugging. To get around the time-out, change the transaction proprty of HBInstitution.IOrder to 'Does not use transactions'")
        m_bQueued = False
    End If
    
End Sub

Private Sub QuoteCombo_Click()
    QuoteNameLabel.Caption = m_qNames(QuoteCombo.ListIndex)
    Call ForceQuoteTBUT_Click
End Sub

Private Sub QuoteCombo_Change()

    If QuoteCombo.ListIndex >= 0 Then
        QuoteNameLabel.Caption = m_qNames(QuoteCombo.ListIndex)
    End If
    
    Call ForceQuoteTBUT_Click
    
End Sub

Private Sub QuoteTimer_Timer()
    Dim sSymbol As String
    Dim rc As Long
    Dim cBidPrice As Currency
    Dim cAskPrice As Currency
    
    sSymbol = Trim(QuoteCombo.Text)
    If sSymbol = "" Then
        Exit Sub
    End If
    rc = UpdateQuoteFields(sSymbol, cBidPrice, cAskPrice)
    If rc <> SUCCESS Then
        frmMainProfile.QuoteTimer.Enabled = False
        Exit Sub
    End If
End Sub

Private Sub ReAuthenticateTBUT_Click()

    ' Populate the Account ListBox
    frmMainProfile.Enabled = False
    
    frmLogin.txtUserName.Text = CustomerCombo.Text
    frmLogin.txtPassword = ""
    frmLogin.Show 1

    If CustLoginSucceeded = True Then
        frmMainProfile.Enabled = True
        Call FillCustomer(CustomerCombo.Text)
    End If
    
End Sub

Private Sub ReconcileBut_Click()
    Dim rc As Long
    Dim sMsg As String
    
    If m_bStartAllObjects = False Then
        Dim objAcct As New HBInstitution.IAccount
        rc = objAcct.Reconcile(sMsg)
        Set objAcct = Nothing
    Else
        rc = m_objAcct.Reconcile(sMsg)
    End If
    
    If rc <> SUCCESS Then
        MsgBox (sMsg)
    Else
        MsgBox (" Reconciliation Was Successful")
    End If
    If Not m_bUseXML Then
        Call UpdateInfo
    Else
        Call UpdateInfoXML
    End If
    Call FillAcks(customerSSN)
    
End Sub

Private Sub RefreshTBut_Click()
       
    If Not m_bUseXML Then
        Call UpdateInfo
    Else
        Call UpdateInfoXML
    End If
    
    FillAcks (customerSSN)

End Sub

Private Sub ReportTBUT_Click()
AccountDataReport.Show
End Sub


Private Sub SettleTBUT_Click()

Dim confirmNum As Integer
Dim sMsg As String
Dim retval As Long

 If SettleTED.Text = "" Then
    MsgBox ("Forced Settlement Failed: You Must Enter A Confirmation Number")
    Exit Sub
 End If
 confirmNum = CInt(SettleTED.Text)
 
 If m_bStartAllObjects = False Then
    Dim objAcct As New HBInstitution.IAccount
    retval = objAcct.ForceSettlement(confirmNum, sMsg)
    Set objAcct = Nothing
 Else
    retval = m_objAcct.ForceSettlement(confirmNum, sMsg)
 End If
 
 If retval <> SUCCESS Then
    MsgBox ("Forced Settlement Failed: " & sMsg)
 Else
    MsgBox ("Forced Settlement of " & confirmNum & " was Successful")
    If Not m_bUseXML Then
        Call UpdateInfo
    Else
        Call UpdateInfoXML
    End If
 End If
    
End Sub

Sub FillFlxHistory(ByVal sAcctNum As String, ByVal index As Long)

    Dim rst As Variant
    Dim sMsg As String
    Dim rc As Long
    
    If m_bStartAllObjects = False Then
        Dim objAcct As New HBInstitution.IAccount
        rc = objAcct.GetHistory(sAcctNum, rst, sMsg)
        Set objAcct = Nothing
    Else
        rc = m_objAcct.GetHistory(sAcctNum, rst, sMsg)
    End If
    
    If rc <> SUCCESS Then
        SSTab1.TabEnabled(2) = False
        HistoryFGrid.Visible = False
      
        If rc = NO_RECORDS_FOUND Then
            'MsgBox ("No History Orders Found")
        Else
            'MsgBox (sMsg)
        End If
        Exit Sub
    End If

    SSTab1.TabEnabled(2) = True
    HistoryFGrid.Visible = True
        
    Dim rownum As Integer
    Dim dDate As Date
     
    ' Fill grid with data from field(s) in the table.
    
    rownum = 0
        
    HistoryFGrid.Rows = rownum + 1
       
    rst.MoveFirst
    
    HistoryFGrid.TextMatrix(0, 0) = "Confirm #"
    HistoryFGrid.TextMatrix(0, 1) = "Action"
    HistoryFGrid.TextMatrix(0, 2) = "Shares"
    
    HistoryFGrid.TextMatrix(0, 3) = "Symbol"
    HistoryFGrid.TextMatrix(0, 4) = "Total Price"
    HistoryFGrid.TextMatrix(0, 5) = "Type"
    HistoryFGrid.TextMatrix(0, 6) = "Status"
    
    HistoryFGrid.TextMatrix(0, 7) = "Limit Price"
    HistoryFGrid.TextMatrix(0, 8) = "Price"
    
    
    HistoryFGrid.TextMatrix(0, 9) = "Confirmed"
    HistoryFGrid.TextMatrix(0, 10) = "Settled"
    HistoryFGrid.TextMatrix(0, 11) = "Reconciled"
    HistoryFGrid.TextMatrix(0, 12) = "Comm"
    HistoryFGrid.TextMatrix(0, 13) = "Check #"
    
    HistoryFGrid.TextMatrix(0, 14) = "Ack'ed"
    Do Until rst.EOF
        rownum = rownum + 1
        HistoryFGrid.Rows = rownum
        HistoryFGrid.AddItem ""
        
        ' Use the Institution OrderId as the tracking Confirmation Number
        HistoryFGrid.TextMatrix(rownum, 0) = rst("orderId")
       
        If rst("action") = BUY Then
           HistoryFGrid.TextMatrix(rownum, 1) = "BUY"
        ElseIf rst("action") = SELL Then
           HistoryFGrid.TextMatrix(rownum, 1) = "SELL"
        Else
            HistoryFGrid.TextMatrix(rownum, 1) = "UNKNOWN"
        End If
        
        HistoryFGrid.TextMatrix(rownum, 2) = rst("quantity")
        
        HistoryFGrid.TextMatrix(rownum, 3) = rst("symbol")
         
        HistoryFGrid.TextMatrix(rownum, 4) = rst("value")
            
        If rst("tradeType") = MARKET_ORDER Then
           HistoryFGrid.TextMatrix(rownum, 5) = "MARKET"
        ElseIf rst("tradeType") = LIMIT_ORDER Then
           HistoryFGrid.TextMatrix(rownum, 5) = "LIMIT"
        Else
            HistoryFGrid.TextMatrix(rownum, 5) = "UNKNOWN"
        End If
         
         
        If rst("orderStatus") = CONFIRMED Then
           HistoryFGrid.TextMatrix(rownum, 6) = "M-CONF"
        ElseIf rst("orderStatus") = SETTLED Then
           HistoryFGrid.TextMatrix(rownum, 6) = "FILLED"
        ElseIf rst("orderStatus") = RECONCILED Then
           HistoryFGrid.TextMatrix(rownum, 6) = "RECON"
        ElseIf rst("orderStatus") = CANCELED Then
           HistoryFGrid.TextMatrix(rownum, 6) = "CANC"
        ElseIf rst("orderStatus") = SETTLED_ERROR Then
           HistoryFGrid.TextMatrix(rownum, 6) = "S_ERR"
        ElseIf rst("orderStatus") = ICONFIRMED Then
           HistoryFGrid.TextMatrix(rownum, 6) = "I-CONF"
        Else
            HistoryFGrid.TextMatrix(rownum, 6) = "UNKNOWN"
        End If
           
        
        HistoryFGrid.TextMatrix(rownum, 7) = rst("limitPrice")
        HistoryFGrid.TextMatrix(rownum, 8) = rst("settledPrice")
        
        HistoryFGrid.TextMatrix(rownum, 9) = rst("confirmationDate") & ""
        HistoryFGrid.TextMatrix(rownum, 10) = rst("settlementDate") & ""
        HistoryFGrid.TextMatrix(rownum, 11) = rst("reconcileDate") & ""
        
        HistoryFGrid.TextMatrix(rownum, 12) = rst("commision")
        'HistoryFGrid.TextMatrix(rownum, 13) = rst("check_number")
        
        If rst("acknowledged") = NOT_ACKNOWLEDGED Then
           HistoryFGrid.TextMatrix(rownum, 14) = "NO"
        Else
            HistoryFGrid.TextMatrix(rownum, 14) = "YES"
        End If
            
        rst.MoveNext ' Move to next record in table.
    Loop

    Set rst = Nothing
    
End Sub

Public Sub HBEventClass_NewsHeadline(ByVal sHeadline As String)

    MsgBox ("HBEventClass_NewsHeadline")
    
End Sub

Public Sub NewsHeadline(ByVal sHeadline As String)

    MsgBox ("NewsHeadline")
    
End Sub




Private Sub StopCBut_Click()

    If StopCBut.Value = 0 Then
    
        MsgBox ("Disabling all Object Creation")
        If ObjectCBut.Value = 1 Then
            ObjectCBut.Value = 0
        End If
        
        m_bStopQuote = False
        frmMainProfile.QuoteTimer.Enabled = True
        frmMainProfile.BannerLabel.Visible = True
        frmMainProfile.BannerTimer.Enabled = True
    Else
        MsgBox ("NOTE: Quotes will also be turned off for Order Verification and Execution (Confirmation)")
        m_bStopQuote = True
        
        Call ActivateAllObjects
        
        frmMainProfile.QuoteTimer.Enabled = False
        frmMainProfile.BannerLabel.Visible = False
        frmMainProfile.BannerTimer.Enabled = False
    End If
        
End Sub

Private Sub SubscribeTBUT_Click()
    If PersistCBut.Value = 0 And TransientCBut.Value = 0 Then
        MsgBox ("No Subscribers are Checked. Select Subscriber Check Boxe(s)")
        Exit Sub
    End If
    
    If TransientCBut.Value = 1 Then
        Call SubscribeTransient
        frmMainProfile.NTEd.Visible = True
        frmMainProfile.NLabel.Visible = True
        Exit Sub
    End If
    
    If PersistCBut.Value = 1 Then
        Call SubscribePersistent
        Exit Sub
    End If
   
End Sub

Public Sub ChartRecords()

  Dim rst As ADODB.Recordset
  Dim dStartDate As Date
  Dim dEndDate As Date
  
  dStartDate = frmMainProfile.StartCombo.Text
  dEndDate = frmMainProfile.EndCombo.Text

  If m_bStartAllObjects = False Then
        Dim objQuote As New HBExchange.IQuote
        Set rst = objQuote.GetIntradayQuotes(Trim(frmMainProfile.ChartSymbolCombo.Text), frmMainProfile.StartCombo.Text, frmMainProfile.EndCombo.Text)
        Set objQuote = Nothing
  Else
        Set rst = m_objQuote.GetIntradayQuotes(Trim(frmMainProfile.ChartSymbolCombo.Text), frmMainProfile.StartCombo.Text, frmMainProfile.EndCombo.Text)
  End If
  
  If Not rst.EOF Then

    Dim i As Integer
     
    With chtReport
        .ColumnCount = 1
        .RowCount = 1
        For i = 1 To 1000
            If rst.EOF Then
                Exit For
            End If
            .RowCount = i
            .row = i
            .Data = rst("LastTradePrice")
            rst.MoveNext
        Next i
    End With
  Else
        MsgBox "No values for those dates!", vbInformation, "Broker"
  End If
  
End Sub

Public Sub UpdateTQuote()

    If m_bStopQuote = True Then
         Exit Sub
    End If
    
    Dim rc As Long
    Dim NetChange As Double
    Dim OpenPrice As Currency
    Dim ClosePrice As Currency
    Dim DailyHigh As Currency
    Dim DailyLow As Currency
    Dim askPrice As Currency
    Dim bidPrice As Currency
    Dim bidSize As Long
    Dim askSize As Long
    Dim QuoteTime As Date
    Dim LastTradeTime As Date
    Dim LastTradePrice As Currency
    Dim closeDate As Date
    Dim sMsg As String
    
    If m_bStartAllObjects = False Then
        Dim objQuote As New HBExchange.IQuote
        rc = objQuote.RetrieveEx(Trim(TQuoteCombo.Text), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
        Set objQuote = Nothing
    Else
        rc = m_objQuote.RetrieveEx(Trim(TQuoteCombo.Text), QuoteTime, bidPrice, askPrice, LastTradeTime, LastTradePrice, NetChange, DailyHigh, DailyLow, askSize, bidSize, OpenPrice, ClosePrice, closeDate, sMsg)
    End If
  
    If rc = SUCCESS Then
        PriceTED.Text = FormatCurrency(LastTradePrice)
    Else
         PriceTED.Text = "Unavailable"
    End If
    
    QuantityTED = "0"

End Sub

Private Sub QuantityTED_Validate(KeepFocus As Boolean)

    Dim s As String
    Dim i As Long
    
    On Error GoTo ErrorHandler
    
    s = QuantityTED.Text
    KeepFocus = False
    If s <> "" Then
        i = CLng(s)
        If i < 0 Then
            MsgBox ("Please Enter a Positive Share Amount")
            KeepFocus = True
        ElseIf i > 32000 Then
            MsgBox ("Please Enter a Share Amount less than 32,000")
            KeepFocus = True
        End If
    End If
    Exit Sub
    
ErrorHandler:
    KeepFocus = True
    MsgBox ("The Share Amount is too large or negative. Enter a share amount less than 100,000")
End Sub

Private Sub PriceTED_Validate(KeepFocus As Boolean)

    Dim s As String
    Dim d As Double
    
    On Error GoTo ErrorHandler
    
    s = PriceTED.Text
    KeepFocus = False
    If s <> "" Then
        d = CDbl(s)
        If d < 0 Then
            MsgBox ("Please Enter a Positive Share Price")
            KeepFocus = True
        ElseIf d > 1000 Then
            MsgBox ("Please Enter a Share Price less than $1,000")
            KeepFocus = True
        End If
    End If
    Exit Sub
    
ErrorHandler:
    KeepFocus = True
    MsgBox ("The Share Price is too large or negative. Enter a share Price less than $1,000")
End Sub


Private Sub TestCBut_Click()
    If TestCBut.Value = 1 Then
        TestTEd.Visible = True
        TestLabel.Visible = True
    Else
        TestTEd.Visible = False
        TestLabel.Visible = False
    End If
End Sub

Private Sub TestModeCBut_Click()

    If TestModeCBut.Value = 0 Then
        StopCBut.Visible = False
        TestCBut.Visible = False
        TestTEd.Visible = False
        TestLabel.Visible = False
        ODBCCBut.Visible = False
        PersistCBut.Visible = False
        LoopCBut.Visible = False
        LoopCBut.Value = 0
    Else
        StopCBut.Visible = True
        TestCBut.Visible = True
        If TestCBut.Value = 1 Then
            TestTEd.Visible = True
            TestLabel.Visible = True
        End If
        ODBCCBut.Visible = False  ' Keep false for now
        PersistCBut.Visible = True
        LoopCBut.Visible = True
        If LoopCBut.Value = 1 Then
            LoopText.Visible = True
            ConfirmTBUT.Caption = "Run Test"
        End If
    End If
    
End Sub

Private Sub TimerTEd_Change()

    Dim lVal As Long
    
    lVal = CLng(Trim(TimerTEd.Text))
    If lVal <= 0 Then
        MsgBox ("Cannot use a non-positive number")
        Exit Sub
    ElseIf lVal > 100000 Then
        MsgBox ("Cannot use a number > 100,000")
        Exit Sub
    End If
    
    QuoteTimer.Interval = lVal
    
    Call UpdateTQuote
End Sub

Private Sub TQuoteCombo_Click()
    Call UpdateTQuote
End Sub

Private Sub TQuoteCombo_Change()
    Call UpdateTQuote
End Sub


Private Sub ShowInfo(ByVal sFName As String)

    On Error GoTo ErrorHandler
    
    If DocsCBut.Value = 1 Then
        Dim fso As New FileSystemObject
        Dim fil1 As File, ts As TextStream
        Dim s As String
        
        Image1.Visible = False
         
        Set fil1 = fso.GetFile("..\Docs\" & sFName & ".txt")
        Set ts = fil1.OpenAsTextStream(ForReading)
        s = ts.ReadAll
        
        ViewTEd.Text = s
        
        ts.Close
        
        ViewTEd.Visible = True
    Else
        ViewTEd.Visible = False
        Image1.Visible = True
    
        If Not Image1.Picture Is Nothing Then
            Image1.Picture = LoadPicture("..\Docs\" & sFName & ".jpg")
        End If
    End If
    
    Exit Sub
ErrorHandler:
    MsgBox ("Image or Text not available")
End Sub

Private Sub V1RBut_Click()
     ShowInfo ("HB1")
End Sub



Private Sub V2RBut_Click()
    ShowInfo ("HB2")
End Sub

Private Sub V3RBut_Click()
     ShowInfo ("HB3")
End Sub

Private Sub V4RBut_Click()
     ShowInfo ("HB4")
End Sub

Private Sub V5RBut_Click()
    ShowInfo ("HB5")
End Sub

Private Sub V6RBut_Click()
    ShowInfo ("HB6")
End Sub

Sub FillFlxPendingXML(ByVal sAcctNum As String)
  
    Dim sMsg As String
    Dim nCount As Integer
    Dim nIndex As Integer
    Dim bFoundPending As Boolean
    
    PendingFlxGrid.Rows = 2
    PendingFlxGrid.Cols = 6
    PendingFlxGrid.Clear

    frmMainProfile.SSTab1.TabEnabled(4) = True
    frmMainProfile.PendingFlxGrid.Visible = True
    frmMainProfile.SettleTBUT.Visible = True
    frmMainProfile.SettleTED.Visible = True
    frmMainProfile.Label1.Visible = True
            
    Dim rownum As Integer
    
    ' Fill grid with data from field(s) in the table.
    rownum = 0
    
    PendingFlxGrid.TextMatrix(rownum, 0) = "Confirm #"
    PendingFlxGrid.ColWidth(0) = 1550
    PendingFlxGrid.TextMatrix(rownum, 1) = "Symbol"
    PendingFlxGrid.ColWidth(1) = 1000
    PendingFlxGrid.TextMatrix(rownum, 2) = "Quantity"
    PendingFlxGrid.ColWidth(2) = 1200
    PendingFlxGrid.TextMatrix(rownum, 3) = "Confirm Date"
    PendingFlxGrid.ColWidth(3) = 1640
    PendingFlxGrid.TextMatrix(rownum, 4) = "Limit Price"
    PendingFlxGrid.ColWidth(4) = 1300
    PendingFlxGrid.TextMatrix(rownum, 5) = "Acct Number"
    PendingFlxGrid.ColWidth(5) = 1700
    'PendingFlxGrid.CollapseAll 1
   
    Dim xmlCurNode As MSXML.IXMLDOMNode
    
    Call XML_FindTopLevelNode(m_XMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Pending_Orders", "Accounts", "", xmlCurNode)
    Call XML_PopulateGrid(xmlCurNode, 0, 0, "Pending", PendingFlxGrid, False, bFoundPending)
    
    If bFoundPending = False Then
        frmMainProfile.SSTab1.TabEnabled(4) = False
        frmMainProfile.PendingFlxGrid.Visible = False
        frmMainProfile.SettleTBUT.Visible = False
        frmMainProfile.SettleTED.Visible = False
        frmMainProfile.Label1.Visible = False
    End If
  
End Sub

Sub FillFlxHoldingXML(ByVal cAcctNum As String)
  
    Dim rc As Long
    Dim sMsg As String
    Dim rownum As Integer
    Dim nCount As Integer
    Dim nIndex As Integer
    Dim bHoldFound As Boolean
    
    HoldingFGrid.Rows = 2
    HoldingFGrid.Cols = 6
    HoldingFGrid.Clear
        
    frmMainProfile.SSTab1.TabEnabled(1) = True
    frmMainProfile.HoldingFGrid.Visible = True
        
    With frmMainProfile.HoldingFGrid
        ' Populate the Grid Headings
        .TextMatrix(0, 0) = "Symbol"
        .ColWidth(0) = 1300
        .TextMatrix(0, 1) = "Quantity"
        .ColWidth(1) = 1100
        .TextMatrix(0, 2) = "Net Worth"
        .ColWidth(2) = 1500
        
        .TextMatrix(0, 3) = "Reconciled"
        .ColWidth(3) = 1400
        .TextMatrix(0, 4) = "Current Price"
        .ColWidth(4) = 1500
        .TextMatrix(0, 5) = "Current Value"
        .ColWidth(5) = 1880
        .CollapseAll 1
    End With
    
    Dim xmlCurNode As MSXML.IXMLDOMNode
    
    Call XML_FindTopLevelNode(m_XMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "account", "Accounts", cAcctNum, xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Holdings", "account", "", xmlCurNode)
    
    Call XML_PopulateGrid(xmlCurNode, 0, 0, "Holding", HoldingFGrid, False, bHoldFound)

    If bHoldFound = False Then
        frmMainProfile.SSTab1.TabEnabled(1) = False
        frmMainProfile.HoldingFGrid.Visible = False
    End If
End Sub

Sub FillFlxHistoryHierarchyXML(ByVal sSSN As String, ByVal index As Long)

    Dim rst As ADODB.Recordset
    Dim rsHoldings As Variant
    Dim sMsg As String
    Dim rc As Long
    Dim i As Integer
    Dim r As Integer
    
    If m_bStartAllObjects = False Then
        Dim objCust As New HBInstitution.ICustomer
        rc = objCust.GetHistoryHierarchy(sSSN, rst, sMsg)
        Set objCust = Nothing
    Else
        rc = m_objCust.GetHistoryHierarchy(sSSN, rst, sMsg)
    End If
    
    If rc <> SUCCESS Then
        Set rst = Nothing
        frmMainProfile.SSTab1.TabEnabled(2) = False
        frmMainProfile.AccountFlexGrid2.Visible = False
      If rc = NO_RECORDS_FOUND Then
        'MsgBox ("No History Orders Found")
      Else
        'MsgBox (sMsg)
      End If
      Exit Sub
    End If
    
    frmMainProfile.HBut.Visible = True
    frmMainProfile.SSTab1.TabEnabled(2) = True
    frmMainProfile.AccountFlexGrid2.Visible = True
    frmMainProfile.ReportTBUT.Visible = True
 
    With frmMainProfile.AccountFlexGrid2
    
    Set .DataSource = rst
      On Error Resume Next
      
      Do While True
        .RowExpanded = False
        .row = .row + 1
        If Err Then Exit Do
      Loop
      .row = 1
      .col = 0
   
    End With
   
  Set rst = Nothing
  
End Sub

Sub FillFlxHistoryXML(ByVal sAcctNum As String, ByVal index As Long)

    'Dim rst As Variant
    Dim sMsg As String
    Dim rc As Long
    Dim nCount As Integer
    Dim nIndex As Integer
    Dim bFoundHist As Boolean
    
    HistoryFGrid.Rows = 2
    HistoryFGrid.Cols = 15
    HistoryFGrid.Clear
    
    SSTab1.TabEnabled(2) = True
    HistoryFGrid.Visible = True
        
    Dim rownum As Integer
    Dim dDate As Date
     
    ' Fill grid with data from field(s) in the table.
    rownum = 0
    
    HistoryFGrid.TextMatrix(rownum, 0) = "Confirm #"
    HistoryFGrid.TextMatrix(rownum, 1) = "Action"
    HistoryFGrid.TextMatrix(rownum, 2) = "Shares"

    HistoryFGrid.TextMatrix(rownum, 3) = "Symbol"
    HistoryFGrid.TextMatrix(rownum, 4) = "Total Price"
    HistoryFGrid.TextMatrix(rownum, 5) = "Type"
    HistoryFGrid.TextMatrix(rownum, 6) = "Status"

    HistoryFGrid.TextMatrix(rownum, 7) = "Limit Price"
    HistoryFGrid.TextMatrix(rownum, 8) = "Price"

    HistoryFGrid.TextMatrix(rownum, 9) = "Confirmed"
    HistoryFGrid.TextMatrix(rownum, 10) = "Settled"
    HistoryFGrid.TextMatrix(rownum, 11) = "Reconciled"
    HistoryFGrid.TextMatrix(rownum, 12) = "Comm"
    HistoryFGrid.TextMatrix(rownum, 13) = "Check #"

    HistoryFGrid.TextMatrix(rownum, 14) = "Ack'ed"
    
    HistoryFGrid.CollapseAll 1
    
    Dim xmlCurNode As MSXML.IXMLDOMNode
    
    Call XML_FindTopLevelNode(m_XMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "account", "Accounts", sAcctNum, xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Histories", "account", "", xmlCurNode)
    
    Call XML_PopulateGrid(xmlCurNode, 1, 0, "History", HistoryFGrid, True, bFoundHist)
    
    If bFoundHist = False Then
        SSTab1.TabEnabled(2) = False
        HistoryFGrid.Visible = False
    End If
End Sub

Public Function XML_FindTopLevelNode(DNo As MSXML.IXMLDOMNode, ByVal strXmlPath As String, ByVal strParent As String, ByVal strTwin As String, returnDN As MSXML.IXMLDOMNode) As Boolean
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i As Integer
    Dim bNotFound As Boolean
    
    ' Check to see if we have and node element
    If (DNo.nodeType = NODE_ELEMENT) Then ' NODE_ELEMENT = 1
        ' Check to see if we have the correct type of element
        If strXmlPath = DNo.baseName Then
            ' If no Twin, then we've found our element
            If strTwin = "" Then
                XML_FindTopLevelNode = True
                Set returnDN = DNo
                Exit Function
            ' If we have a twin, check to see if we have the correct node
            ElseIf DNo.firstChild.Text = strTwin Then
                XML_FindTopLevelNode = True
                Set returnDN = DNo
                Exit Function
            Else
                Exit Function
            End If
        ElseIf DNo.parentNode.baseName = strParent Then
            Exit Function
        End If
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1 And Not bNotFound
        bNotFound = XML_FindTopLevelNode(DNo.childNodes.Item(i), strXmlPath, strParent, strTwin, returnDN)
        i = i + 1
    Wend
End Function

Public Function XML_PopulateGrid(DNo As MSXML.IXMLDOMNode, ByVal row As Integer, ByVal col As Integer, ByRef strXmlPath As String, ByRef ctrlFlexGrid As MSHFlexGrid, ByVal bReverse As Boolean, ByRef bRowAdded As Boolean, Optional ByVal strRowText As String) As Boolean
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i As Integer
    Dim nInsideLoop As Integer
    Dim nIndex As Integer
    
    If (DNo.nodeType = NODE_ELEMENT) Then ' NODE_ELEMENT = 1
        If strXmlPath = DNo.baseName Then
            
            While nInsideLoop <= DNo.childNodes.length
                Call XML_PopulateGridRow(DNo.childNodes.Item(nInsideLoop), strRowText)
                nInsideLoop = nInsideLoop + 1
            Wend
            
            If bReverse Then
                Call ctrlFlexGrid.AddItem(strRowText, 1)
                bRowAdded = True
            Else
                nIndex = (ctrlFlexGrid.Rows) - 1
                Call ctrlFlexGrid.AddItem(strRowText, nIndex)
                bRowAdded = True
            End If
            strRowText = ""
        End If
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1
        Call XML_PopulateGrid(DNo.childNodes.Item(i), row, col, strXmlPath, ctrlFlexGrid, bReverse, bRowAdded)
        i = i + 1
    Wend
    
End Function

Public Function XML_PopulateGridRow(DNo As MSXML.IXMLDOMNode, ByRef strRowText As String) As Boolean
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i As Integer
    Dim nInsideLoop As Integer
    
    If (DNo.nodeType = NODE_ELEMENT) Then ' NODE_ELEMENT = 1
        strRowText = strRowText & DNo.Text & vbTab
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1
        Call XML_PopulateGridRow(DNo.childNodes.Item(i), strRowText)
        i = i + 1
    Wend
    
End Function

Public Function XML_GetValue(DNo As MSXML.IXMLDOMNode, ByVal strXmlPath As String, ByVal strParent As String) As Variant
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i As Integer
    Dim bNotFound As Boolean
    
    If (DNo.nodeType = NODE_ELEMENT) Then ' NODE_ELEMENT = 1
        If strXmlPath = DNo.baseName Then
            XML_GetValue = DNo.Text
            Exit Function
        End If
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1 And Not XML_GetValue <> ""
        XML_GetValue = XML_GetValue(DNo.childNodes.Item(i), strXmlPath, strParent)
        i = i + 1
    Wend
End Function

Sub FillFlxAccountXML(ByVal sSSN As String, ByVal index As Long)
  
    Dim sMsg As String
    Dim nCount As Integer
    Dim nIndex As Integer
    
    AccountFlexGrid.Rows = 2
    AccountFlexGrid.Cols = 6
    AccountFlexGrid.Clear
    
    SSTab1.TabEnabled(0) = True
    AccountFlexGrid.Visible = True
    HBut.Visible = True
    ReportTBUT.Visible = True
    
    Dim rownum As Integer
    
    ' Fill grid with data from field(s) in the table.
    rownum = 0
    
    AccountFlexGrid.Cols = 6
    AccountFlexGrid.TextMatrix(rownum, 0) = "Account #"
    AccountFlexGrid.ColWidth(0) = 1350
    AccountFlexGrid.TextMatrix(rownum, 1) = "Type"
    AccountFlexGrid.ColWidth(1) = 600
    AccountFlexGrid.TextMatrix(rownum, 2) = "Cash"
    AccountFlexGrid.ColWidth(2) = 1600
    AccountFlexGrid.TextMatrix(rownum, 3) = "Cash Debit"
    AccountFlexGrid.ColWidth(3) = 1600
    AccountFlexGrid.TextMatrix(rownum, 4) = "Net Worth"
    AccountFlexGrid.ColWidth(4) = 1600
    AccountFlexGrid.TextMatrix(rownum, 5) = "Cash Avail"
    AccountFlexGrid.ColWidth(5) = 1880
    AccountFlexGrid.CollapseAll 1
         
    Dim xmlCurNode As MSXML.IXMLDOMNode
    
    Call XML_FindTopLevelNode(m_XMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "account", "Accounts", "", xmlCurNode)
    
    Dim vXMLData As Variant
    Dim vXMLAccount As Variant
    Dim vXMLCash As Variant
    Dim vXMLCashDebit As Variant
    Dim strRow As String
    Dim bAccFound As Boolean
    
    vXMLAccount = XML_GetValue(xmlCurNode, "acctNumber", "Accounts")
    If vXMLAccount <> "" Then bAccFound = True
    strRow = vXMLAccount & vbTab
    vXMLData = XML_GetValue(xmlCurNode, "acctType", "Accounts")
    strRow = strRow & vXMLData & vbTab
    vXMLCash = XML_GetValue(xmlCurNode, "cash", "Accounts")
    strRow = strRow & FormatCurrency(vXMLCash) & vbTab
    vXMLCashDebit = XML_GetValue(xmlCurNode, "cashDebit", "Accounts")
    strRow = strRow & FormatCurrency(vXMLCashDebit) & vbTab
    vXMLData = XML_GetValue(xmlCurNode, "netWorth", "Accounts")
    strRow = strRow & FormatCurrency(vXMLData) & vbTab
    vXMLData = FormatCurrency(vXMLCash - vXMLCashDebit)
    strRow = strRow & vXMLData & vbTab
    
    ' Add row to grid
    nIndex = (AccountFlexGrid.Rows) - 1
    Call AccountFlexGrid.AddItem(strRow, 1)
    
    While XML_FindNextTopLevelNode(xmlCurNode, "account", "Accounts", xmlCurNode)
         vXMLAccount = ""
         strRow = ""
         
         vXMLAccount = XML_GetValue(xmlCurNode, "acctNumber", "Accounts")
         strRow = vXMLAccount & vbTab
         vXMLData = XML_GetValue(xmlCurNode, "acctType", "Accounts")
         strRow = strRow & vXMLData & vbTab
         vXMLCash = XML_GetValue(xmlCurNode, "cash", "Accounts")
         strRow = strRow & FormatCurrency(vXMLCash) & vbTab
         vXMLCashDebit = XML_GetValue(xmlCurNode, "cashDebit", "Accounts")
         strRow = strRow & FormatCurrency(vXMLCashDebit) & vbTab
         vXMLData = XML_GetValue(xmlCurNode, "netWorth", "Accounts")
         strRow = strRow & FormatCurrency(vXMLData) & vbTab
         vXMLData = FormatCurrency(vXMLCash - vXMLCashDebit)
         strRow = strRow & vXMLData & vbTab
         
         Call AccountFlexGrid.AddItem(strRow, 1)
    Wend
    
    If bAccFound = False Then
        SSTab1.TabEnabled(0) = False
        AccountFlexGrid.Visible = False
        HBut.Visible = False
        ReportTBUT.Visible = False
    End If
End Sub
 
Public Function XML_FindNextTopLevelNode(DNo As MSXML.IXMLDOMNode, ByVal strXmlPath As String, ByVal strParent As String, returnDN As MSXML.IXMLDOMNode) As Boolean
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    
    XML_FindNextTopLevelNode = False
    
    Dim DNoSibbling As MSXML.IXMLDOMNode
    Set DNoSibbling = DNo.nextSibling
    If DNoSibbling Is Nothing Then Exit Function
    
    ' Check to see if we have an element
    If (DNoSibbling.nodeType = NODE_ELEMENT) Then ' NODE_ELEMENT = 1
        'Check to see if it's the correct type, and has the same parent as it's sibbling
        If strXmlPath = DNoSibbling.baseName And strParent = DNoSibbling.parentNode.baseName Then
            XML_FindNextTopLevelNode = True
            Set returnDN = DNoSibbling
            Exit Function
        End If
    End If
    
End Function

