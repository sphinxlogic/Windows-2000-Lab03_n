VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "Comctl32.ocx"
Begin VB.Form frmMain 
   Caption         =   "Microsoft Multidimensional Expressions Demonstration"
   ClientHeight    =   7860
   ClientLeft      =   3570
   ClientTop       =   3420
   ClientWidth     =   10905
   ClipControls    =   0   'False
   FillColor       =   &H00FF0000&
   Icon            =   "Main.frx":0000
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   ScaleHeight     =   7860
   ScaleWidth      =   10905
   StartUpPosition =   2  'CenterScreen
   Begin ComctlLib.Toolbar tlbMain 
      Align           =   1  'Align Top
      Height          =   435
      Left            =   0
      TabIndex        =   7
      Top             =   0
      Width           =   10905
      _ExtentX        =   19235
      _ExtentY        =   767
      ButtonWidth     =   609
      ButtonHeight    =   609
      AllowCustomize  =   0   'False
      Wrappable       =   0   'False
      Appearance      =   1
      ImageList       =   "imlToolbar"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   26
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Connect"
            Description     =   "Connect"
            Object.ToolTipText     =   "Connect"
            Object.Tag             =   ""
            ImageKey        =   "Connect"
            Value           =   1
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "FileNew"
            Description     =   "New File"
            Object.ToolTipText     =   "New Query File"
            Object.Tag             =   ""
            ImageKey        =   "FileNew"
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "FileOpen"
            Description     =   "Open File"
            Object.ToolTipText     =   "Open Query File"
            Object.Tag             =   ""
            ImageKey        =   "FileOpen"
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "FileSave"
            Description     =   "Save File"
            Object.ToolTipText     =   "Save Query File"
            Object.Tag             =   ""
            ImageKey        =   "FileSave"
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.Visible         =   0   'False
            Key             =   "EditCut"
            Description     =   "Cut"
            Object.ToolTipText     =   "Cut"
            Object.Tag             =   ""
            ImageKey        =   "EditCut"
         EndProperty
         BeginProperty Button9 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.Visible         =   0   'False
            Key             =   "EditCopy"
            Description     =   "Copy"
            Object.ToolTipText     =   "Copy"
            Object.Tag             =   ""
            ImageKey        =   "EditCopy"
         EndProperty
         BeginProperty Button10 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.Visible         =   0   'False
            Key             =   "EditPaste"
            Description     =   "Paste"
            Object.ToolTipText     =   "Paste"
            Object.Tag             =   ""
            ImageKey        =   "EditPaste"
         EndProperty
         BeginProperty Button11 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Visible         =   0   'False
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button12 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "DatabaseListCaption"
            Description     =   "Database List Caption"
            Object.ToolTipText     =   "Current Database"
            Object.Tag             =   ""
            Style           =   4
            Object.Width           =   300
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button13 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "DatabaseList"
            Description     =   "Database List"
            Object.ToolTipText     =   "Current Database"
            Object.Tag             =   ""
            Style           =   4
            Object.Width           =   2200
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button14 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button15 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "QueryListCaption"
            Description     =   "Query List Caption"
            Object.ToolTipText     =   "Current Query"
            Object.Tag             =   ""
            Style           =   4
            Object.Width           =   640
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button16 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "QueryList"
            Description     =   "Query List"
            Object.ToolTipText     =   "Current Query"
            Object.Tag             =   ""
            Style           =   4
            Object.Width           =   3000
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button17 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "QueryNew"
            Description     =   "Query New"
            Object.ToolTipText     =   "New Query"
            Object.Tag             =   ""
            ImageKey        =   "QueryNew"
         EndProperty
         BeginProperty Button18 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "QueryDelete"
            Description     =   "Delete Query"
            Object.ToolTipText     =   "Delete Query"
            Object.Tag             =   ""
            ImageKey        =   "QueryDelete"
         EndProperty
         BeginProperty Button19 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button20 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "QueryRun"
            Description     =   "Run Query"
            Object.ToolTipText     =   "Run Query"
            Object.Tag             =   ""
            ImageKey        =   "QueryRun"
         EndProperty
         BeginProperty Button21 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button22 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewSplit"
            Description     =   "Split View"
            Object.ToolTipText     =   "Split View"
            Object.Tag             =   ""
            ImageKey        =   "ViewSplit"
            Style           =   2
            Value           =   1
         EndProperty
         BeginProperty Button23 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewQuery"
            Description     =   "Query View"
            Object.ToolTipText     =   "Query View"
            Object.Tag             =   ""
            ImageKey        =   "ViewQuery"
            Style           =   2
         EndProperty
         BeginProperty Button24 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ViewResults"
            Description     =   "Results View"
            Object.ToolTipText     =   "Results View"
            Object.Tag             =   ""
            ImageKey        =   "ViewResults"
            Style           =   2
         EndProperty
         BeginProperty Button25 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button26 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Key             =   "Pivot"
            Description     =   "Pivot Results"
            Object.ToolTipText     =   "Pivot Results"
            Object.Tag             =   ""
            ImageKey        =   "Pivot"
         EndProperty
      EndProperty
      BorderStyle     =   1
      Begin VB.PictureBox pctQueryListCaption 
         Appearance      =   0  'Flat
         BackColor       =   &H80000004&
         BorderStyle     =   0  'None
         ClipControls    =   0   'False
         ForeColor       =   &H80000008&
         Height          =   315
         Left            =   4161
         ScaleHeight     =   315
         ScaleWidth      =   645
         TabIndex        =   3
         TabStop         =   0   'False
         Top             =   45
         Width           =   640
         Begin VB.Label lblQueryListCaption 
            AutoSize        =   -1  'True
            Caption         =   "Q&ueries:"
            Height          =   195
            Left            =   0
            TabIndex        =   4
            Top             =   60
            Width           =   585
         End
      End
      Begin VB.PictureBox pctDatabaseListCaption 
         Appearance      =   0  'Flat
         BackColor       =   &H80000004&
         BorderStyle     =   0  'None
         ClipControls    =   0   'False
         ForeColor       =   &H80000008&
         Height          =   315
         Left            =   1741
         ScaleHeight     =   315
         ScaleWidth      =   300
         TabIndex        =   0
         TabStop         =   0   'False
         Top             =   45
         Width           =   300
         Begin VB.Label lblDatabaseListCaption 
            AutoSize        =   -1  'True
            Caption         =   "&DB:"
            Height          =   195
            Left            =   0
            TabIndex        =   1
            ToolTipText     =   "Current Database"
            Top             =   60
            Width           =   270
         End
      End
      Begin VB.ComboBox cboDatabaseList 
         Height          =   315
         Left            =   2040
         Style           =   2  'Dropdown List
         TabIndex        =   2
         ToolTipText     =   "Current Database"
         Top             =   45
         Width           =   2200
      End
      Begin VB.ComboBox cboQueryList 
         Height          =   315
         Left            =   4801
         Style           =   2  'Dropdown List
         TabIndex        =   5
         ToolTipText     =   "Current Query"
         Top             =   45
         Width           =   3000
      End
   End
   Begin ComctlLib.StatusBar stbMain 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   8
      Top             =   7485
      Width           =   10905
      _ExtentX        =   19235
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Bevel           =   0
            Object.Width           =   106
            MinWidth        =   106
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   2064
            MinWidth        =   177
            Text            =   "Not Connected"
            TextSave        =   "Not Connected"
            Key             =   "Connection"
            Object.Tag             =   ""
            Object.ToolTipText     =   "Connect"
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   16589
            Key             =   "CurrentActivity"
            Object.Tag             =   ""
            Object.ToolTipText     =   "Current Activity"
         EndProperty
      EndProperty
   End
   Begin MDXSample.ResultsPane cctlResultsPane 
      Height          =   3895
      Left            =   135
      TabIndex        =   9
      TabStop         =   0   'False
      Top             =   4445
      Width           =   10590
      _ExtentX        =   18680
      _ExtentY        =   6879
   End
   Begin MDXSample.QueryPane cctlQueryPane 
      Height          =   3895
      Left            =   135
      TabIndex        =   6
      Top             =   450
      Width           =   10590
      _ExtentX        =   18680
      _ExtentY        =   6879
   End
   Begin MDXSample.SplitRegion srgMain 
      Height          =   7890
      Left            =   135
      Top             =   450
      Width           =   10590
      _ExtentX        =   18680
      _ExtentY        =   13917
      FirstControl    =   "cctlquerypane"
      SecondControl   =   "cctlresultspane"
      FirstControlMinSize=   800
      SecondControlMinSize=   800
      SplitterBarThickness=   100
      AllowControlHiding=   -1  'True
      KeepSplitPercentOnResize=   -1  'True
   End
   Begin ComctlLib.ImageList imlToolbar 
      Left            =   9855
      Top             =   270
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   16
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0442
            Key             =   "Connect"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0994
            Key             =   "FileNew"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0AA6
            Key             =   "FileOpen"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0BB8
            Key             =   "FileSave"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0CCA
            Key             =   "EditCut"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0DDC
            Key             =   "EditCopy"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":0EEE
            Key             =   "EditPaste"
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":1000
            Key             =   "QueryNew"
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":1552
            Key             =   "QueryDelete"
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":1AA4
            Key             =   "QueryRun"
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":1FF6
            Key             =   "ViewSplit"
         EndProperty
         BeginProperty ListImage12 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":2108
            Key             =   "ViewQuery"
         EndProperty
         BeginProperty ListImage13 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":221A
            Key             =   "ViewResults"
         EndProperty
         BeginProperty ListImage14 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":232C
            Key             =   "Pivot"
         EndProperty
         BeginProperty ListImage15 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":243E
            Key             =   "NotConnected"
         EndProperty
         BeginProperty ListImage16 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Main.frx":2990
            Key             =   "Connected"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      NegotiatePosition=   1  'Left
      Begin VB.Menu mnuFileItem 
         Caption         =   "&Connect..."
         Index           =   0
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "&Disconnect"
         Enabled         =   0   'False
         Index           =   1
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "-"
         Index           =   2
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "&New"
         Index           =   3
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "&Open..."
         Index           =   4
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "-"
         Index           =   5
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "&Save"
         Index           =   6
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "Save &As..."
         Index           =   7
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "-"
         Index           =   8
      End
      Begin VB.Menu mnuFileItem 
         Caption         =   "E&xit"
         Index           =   9
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      NegotiatePosition=   2  'Middle
      Begin VB.Menu mnuEditItem 
         Caption         =   "Cu&t"
         Enabled         =   0   'False
         Index           =   0
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditItem 
         Caption         =   "&Copy"
         Enabled         =   0   'False
         Index           =   1
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditItem 
         Caption         =   "&Paste"
         Index           =   2
         Shortcut        =   ^V
      End
   End
   Begin VB.Menu mnuQuery 
      Caption         =   "&Query"
      NegotiatePosition=   2  'Middle
      Begin VB.Menu mnuQueryItem 
         Caption         =   "&New"
         Index           =   0
      End
      Begin VB.Menu mnuQueryItem 
         Caption         =   "&Delete"
         Index           =   1
      End
      Begin VB.Menu mnuQueryItem 
         Caption         =   "-"
         Index           =   2
      End
      Begin VB.Menu mnuQueryItem 
         Caption         =   "&Run"
         Index           =   3
         Shortcut        =   {F5}
      End
      Begin VB.Menu mnuQueryItem 
         Caption         =   "Run &All"
         Index           =   4
      End
      Begin VB.Menu mnuQueryItem 
         Caption         =   "-"
         Index           =   5
      End
      Begin VB.Menu mnuQueryList 
         Caption         =   "&1 Query1"
         Index           =   0
         Visible         =   0   'False
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuViewItem 
         Caption         =   "&Split"
         Checked         =   -1  'True
         Index           =   0
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "&Query"
         Index           =   1
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "&Results"
         Index           =   2
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "-"
         Index           =   3
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "&Toolbar"
         Checked         =   -1  'True
         Index           =   4
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "Status &Bar"
         Checked         =   -1  'True
         Index           =   5
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "-"
         Index           =   6
      End
      Begin VB.Menu mnuViewItem 
         Caption         =   "&Pivot Results"
         Enabled         =   0   'False
         Index           =   7
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      NegotiatePosition=   3  'Right
      Begin VB.Menu mnuHelpItem 
         Caption         =   "Context &Help"
         Enabled         =   0   'False
         Index           =   0
         Shortcut        =   {F1}
      End
      Begin VB.Menu mnuHelpItem 
         Caption         =   "-"
         Index           =   1
      End
      Begin VB.Menu mnuHelpItem 
         Caption         =   "&Contents and Index"
         Index           =   2
      End
      Begin VB.Menu mnuHelpItem 
         Caption         =   "&MDX Help"
         Enabled         =   0   'False
         Index           =   3
      End
      Begin VB.Menu mnuHelpItem 
         Caption         =   "-"
         Index           =   4
      End
      Begin VB.Menu mnuHelpItem 
         Caption         =   "&About"
         Index           =   5
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*******************************************************************************
'*******************************************************************************
'* PROJECT:  MDXSample
'*    This program is intended to serve as a sample application for exploring
'*    Microsoft OLAP Server and to provide examples of ADOMD programming.  To
'*    view examples of ADOMD in use, search for the comment "ADOMD Example"
'*    throughout this Visual Basic project.
'*
'* FORMS:
'*    FrmMain        Main application form (this form)
'*    frmAbout       About box form
'*    frmConnectDlg  Connection dialog
'*
'* MODULES:
'*    Globals        Global variable declarations
'*    Utils          General utilities
'*
'* CLASSES:
'*    QueryFile      Query File management
'*
'* USER CONTROLS:
'*    QueryPane            Portion of the main window used for viewing and
'*                         creating queries
'*    ResultsPane          Portion of the main window used for viewing query
'*                         results
'*    QueryMetaDataPane    Portion of the QueryPane containing the metadata and
'*                         syntax examples
'*    QueryTextPane        Portion of the QueryPane containing the query text
'*    SplitRegion          Control to provide a splitter bar between panes
'*******************************************************************************
'* ADOMD Name prefixes
'*    cs    Cellset
'*    cn    Connection
'*    ct    Catalog
'*    cb    CubeDef
'*    dm    Dimension
'*    lv    Level
'*    hr    Hierarchy
'*    mb    Member
'*    ax    Axis
'*    cl    Cell
'*    ps    Position
'*    er    Error
'*******************************************************************************
'* Conditional Compilation Flags
'*    DebugVersion      If true a debug build is created
'*******************************************************************************
'* Use of this Sample Code
'*    This source code is provided to you solely for purposes of testing and
'*    evaluating the Microsoft OLAP Server product.  Your use of this source
'*    code is governed exclusively by the Microsoft Corporation Non-Disclosure
'*    Agreement (Pre-Release Product) accompanying that product.  All other
'*    rights reserved by Microsoft Corporation.
'*******************************************************************************
'*******************************************************************************

'*******************************************************************************
'* FORM:  frmMain
'*    Main form of the application.  This form is the startup form of the
'*    project and provides main window of the application.  All other components
'*    of the project are called and controlled by code in this form.
'*
'* VERSIONS:
'*    1.00  9/9/97   Matthew Carroll
'*
'* Copyright © 1997 Microsoft Corp.  All rights reserved.
'*******************************************************************************
Option Explicit
Option Compare Text



'********************
'*** DECLARATIONS ***
'********************

'* File menu constants
Private Const m_iMnuFileConnect = 0
Private Const m_iMnuFileDisconnect = 1
Private Const m_iMnuFileNew = 3
Private Const m_iMnuFileOpen = 4
Private Const m_iMnuFileSave = 6
Private Const m_iMnuFileSaveAs = 7
Private Const m_iMnuFileExit = 9

'* Edit menu constants
Private Const m_iMnuEditCut = 0
Private Const m_iMnuEditCopy = 1
Private Const m_iMnuEditPaste = 2

'* Query menu constants
Private Const m_iMnuQueryNew = 0
Private Const m_iMnuQueryDelete = 1
Private Const m_iMnuQueryRun = 3
Private Const m_iMnuQueryRunAll = 4

'* View menu constants
Private Const m_iMnuViewSplit = 0
Private Const m_iMnuViewQuery = 1
Private Const m_iMnuViewResults = 2
Private Const m_iMnuViewToolbar = 4
Private Const m_iMnuViewStatusBar = 5
Private Const m_iMnuViewPivotResults = 7

'* Help menu constants
Private Const m_iMnuHelpContextHelp = 0
Private Const m_iMnuHelpContentsAndIndex = 2
Private Const m_iMnuHelpSyntaxHelp = 3
Private Const m_iMnuHelpAbout = 5

'* Constants for parsing command line arguments
Private Const m_sCommandLineArgStart = "/"
Private Const m_sCommandLineArgStartAlt = "-"
Private Const m_sCommandLineQuote = """"
Private Const m_sCommandLineFlagRunAll = "R"
Private Const m_sCommandLineFlagConnect = "C"
Private Const m_sCommandLineFlagFile = "F"

'* Other constants
Private Const m_sDefaultQueryFileName = "MDXQueries"
Private Const m_sQueryTitlePrefix = "#%s1 "
Private Const m_sQueryTitleEllipses = "..."
Private Const m_iQueryTitleLen = 40
Private Const m_iInvalidQuery = 0
Private Const m_nHorizontalBorder = 100
Private Const m_sFieldCatalogName = "CATALOG_NAME"

Private Enum ViewType
   vtSplit
   vtQuery
   vtResults
End Enum

Private m_cn As Connection       '* ADOMD connection used by the app
Private m_csResults As Cellset   '* ADOMD cellset for retrieving results
Private m_sDataSource As String
Private m_fDisplayPivoted As Boolean
Private m_oQueryFile As New QueryFile
Private m_iSelectedQuery As Long
Private m_fIngoreQueryListClicks As Boolean
Private m_nLastSplitPercent As Single



'******************
'*** PROPERTIES ***
'******************



'***************
'*** METHODS ***
'***************


'*******************************************************************************
'* FUNCTION: Connect
'*    Connects to a multidimensional data source storing the connection in m_cn
'*
'* PARAMETERS:
'*    sConnectStr    Connection String to use to establish a connection.  If not
'*                   specified or the connection could not be opened using
'*                   sConnectStr then the user will be prompted for connection
'*                   information.
'*
'* RETURNS
'*    True if successful, false if canceled by the user
'*******************************************************************************
Private Function Connect(Optional sConnectStr As String = vbNullString) _
                                                                      As Boolean
   On Error GoTo ConnectErr
   
   SetHourglass True
   
   '*** ADOMD Example ***
   
   '* If no connection string, prompt user to connect
   If sConnectStr = vbNullString Then
      Connect = frmConnectDlg.GetConnection(m_cn, m_sDataSource)
   '* Otherwise try opening a connection with the connection string
   Else
      '* Make sure connection object exists and is closed
      If m_cn Is Nothing Then
         Set m_cn = New Connection
      ElseIf Not m_cn.State = adStateClosed Then
         m_cn.Close
      End If
      
      '* Open connection with connection string supplied
      m_cn.Open sConnectStr
      
      '* If connection not open then prompt user to connect
      If Not m_cn.State = adStateOpen Then
         Connect = frmConnectDlg.GetConnection(m_cn, m_sDataSource)
      '* Otherwise save the data source name and return true
      Else
         Connect = True
         m_sDataSource = sGetConnectStrValue(sConnectStr, g_sCnStrDataSource)
      End If
   End If
   
   '*** End Example ***
   
   Set cctlQueryPane.ActiveConnection = m_cn
   
   UpdateDatabaseList m_cn
   
   UpdateConnectionStateUI
   
   SetHourglass False
   
   Exit Function
ConnectErr:
   DisplayError "Unable to establish connection.", m_cn
   Resume Next
End Function

'*******************************************************************************
'* SUB: Disconnect
'*    Disconnects from the multidimensional data source referenced by m_cn
'*******************************************************************************
Private Sub Disconnect()
   On Error GoTo DisconnectErr
   SetHourglass True
   
   Debug.Assert m_cn.State = adStateOpen
   
   '*** ADOMD Example ***
   
   '* If connection object exist and it's not closed then close it
   If Not m_cn Is Nothing Then
      If Not m_cn.State = adStateClosed Then
         m_cn.Close
      End If
   End If
   
   '*** End Example ***
   
   Set cctlQueryPane.ActiveConnection = Nothing
   
   UpdateDatabaseList m_cn
   
   UpdateConnectionStateUI
   
   SetHourglass False
   
   Exit Sub
DisconnectErr:
   SetHourglass False
   DisplayError "A problem occurred while disconnecting."
   On Error Resume Next
   Set m_cn = Nothing
   UpdateConnectionStateUI
End Sub

'* Updates the user interface to reflect the current connection state
Private Sub UpdateConnectionStateUI()
   Dim fConnectionOpen As Boolean
   
   fConnectionOpen = fConnected()
   
   '* Update Menus
   mnuFileItem(m_iMnuFileConnect).Enabled = Not fConnectionOpen
   mnuFileItem(m_iMnuFileDisconnect).Enabled = fConnectionOpen
   mnuQueryItem(m_iMnuQueryRun).Enabled = fConnectionOpen
   mnuQueryItem(m_iMnuQueryRunAll).Enabled = fConnectionOpen

   '* Update toolbar buttons
   With tlbMain.Buttons
      If fConnectionOpen Then
         .Item("Connect").Value = tbrPressed
      Else
         .Item("Connect").Value = tbrUnpressed
      End If
   End With
      
   '* Update status bar
   With stbMain.Panels("Connection")
      If fConnectionOpen Then
         .Text = m_sDataSource
         .ToolTipText = "Disconnect"
         Set .Picture = imlToolbar.ListImages("Connected").ExtractIcon
      Else
         .Text = "Not Connected"
         .ToolTipText = "Connect..."
         Set .Picture = imlToolbar.ListImages("NotConnected").ExtractIcon
      End If
   End With
   
   '* Update Run menu and toolbar button
   UpdateQueryRunUI fConnectionOpen
   
   '* Disable pivot results
   UpdatePivotUI False

End Sub

'* Updates the list of databases
Private Sub UpdateDatabaseList(cnActive As ADODB.Connection)
   Dim rs As ADODB.Recordset, sCatalogActive As String, sCatalogCur As String
   
   cboDatabaseList.Clear
   If cnActive Is Nothing Then
      cboDatabaseList.Enabled = False
   ElseIf cnActive.State <> adStateOpen Then
      cboDatabaseList.Enabled = False
   Else
      cboDatabaseList.Enabled = True
      sCatalogActive = cnActive.DefaultDatabase
      Set rs = cnActive.OpenSchema(adSchemaCatalogs)
      Do Until rs.EOF
         sCatalogCur = rs.Fields(m_sFieldCatalogName)
         cboDatabaseList.AddItem sCatalogCur
         If sCatalogCur = sCatalogActive Then
            cboDatabaseList.ListIndex = cboDatabaseList.NewIndex
         End If
         rs.MoveNext
      Loop
   End If
   
End Sub

'* Returns true if connected to a data source, false otherwise
Private Function fConnected() As Boolean
   If m_cn Is Nothing Then
      fConnected = False
   Else
      fConnected = (m_cn.State = adStateOpen)
   End If
End Function

'* Opens a new query file containing a single blank query
Private Sub FileNew()
   Static iNewCnt As Long
   
   On Error GoTo FileNewErr
   SetHourglass True
      
   If fPromptToSaveChanges() Then
      
      Set m_oQueryFile = New QueryFile
         
      iNewCnt = iNewCnt + 1
      With m_oQueryFile
         .File = m_sDefaultQueryFileName & iNewCnt
         .AddNew
         .Dirty = False
      End With
         
      ChangeSelectedQuery 1
      
   End If
   
   UpdateFileNameUI
   SetHourglass False
   
   Exit Sub
FileNewErr:
   DisplayError "Unable to open a new query file."
   SetHourglass False
End Sub

'* Opens the query file or prompts the user for a query file to open
Private Sub FileOpen(Optional sFile As String = vbNullString)
   
   On Error GoTo FileOpenErr
   SetHourglass True
   
   If fPromptToSaveChanges() Then
      If m_oQueryFile.OpenFile(sFile) Then
         ChangeSelectedQuery 1
      End If
   End If
      
   UpdateFileNameUI
   SetHourglass False
   
   Exit Sub
FileOpenErr:
   DisplayError "Unable to open the file '" & sGetCurrentFile() & "'."
   SetHourglass False
End Sub

'* Saves the open query file
Private Sub FileSave()
   
   On Error GoTo FileSaveErr
   SetHourglass True
   
   UpdateSelectedQuery
   
   m_oQueryFile.Save
   
   UpdateFileNameUI
   SetHourglass False
   
   Exit Sub
FileSaveErr:
   DisplayError "Unable to save file '" & sGetCurrentFile() & "'."
   SetHourglass False
End Sub

'* Saves the open query file to a new file
Private Sub FileSaveAs()

   On Error GoTo FileSaveAsErr
   SetHourglass True
   
   UpdateSelectedQuery
   
   m_oQueryFile.SaveAs
   
   UpdateFileNameUI
   SetHourglass False
   
   Exit Sub
FileSaveAsErr:
   DisplayError "Unable to save file '" & sGetCurrentFile() & "'."
   SetHourglass False
End Sub

'* Prompts the user to save changes if the file is dirty
'* Returns true if successful, false if canceled by the user
Private Function fPromptToSaveChanges() As Boolean
   Dim iResponse As Long
   
   On Error GoTo fPromptToSaveChangesErr
   
   If m_oQueryFile Is Nothing Then
      fPromptToSaveChanges = True
   Else
      UpdateSelectedQuery
      If Not m_oQueryFile.Dirty Then
         fPromptToSaveChanges = True
      Else
         iResponse = MsgBox("Save changes to " & m_oQueryFile.Name & "?", _
                            vbYesNoCancel + vbQuestion, App.Title)
         If iResponse = vbCancel Then
            fPromptToSaveChanges = False
         ElseIf iResponse = vbYes Then
            fPromptToSaveChanges = m_oQueryFile.Save()
         Else
            fPromptToSaveChanges = True
         End If
      End If
   End If
   
   Exit Function
fPromptToSaveChangesErr:
   DisplayError "Unable to save changes to the file '" & sGetCurrentFile & "'"
   fPromptToSaveChanges = False
End Function

'* Deletes the selected query from the query file.  If the last query in the
'* file is deleted, a new blank query is automatically added.
'* Returns True if successful, false otherwise
Private Function fDeleteSelectedQuery() As Boolean
   Dim iResponse As Long
   
   On Error GoTo DeleteSelectedQueryErr
   
   If Not fValidQueryIndex(m_iSelectedQuery) Then
      fDeleteSelectedQuery = False
   Else
      iResponse = MsgBox("Delete the current query?", _
                         vbYesNo + vbDefaultButton2 + vbQuestion, _
                         App.Title)
      If iResponse = vbYes Then
         m_oQueryFile.Remove (m_iSelectedQuery)
         If m_oQueryFile.QueryCount = 0 Then
            ChangeSelectedQuery m_iInvalidQuery
            NewQuery
         ElseIf fValidQueryIndex(m_iSelectedQuery) Then
            ChangeSelectedQuery m_iSelectedQuery
         Else
            ChangeSelectedQuery m_iSelectedQuery - 1
         End If
         fDeleteSelectedQuery = True
      Else
         fDeleteSelectedQuery = False
      End If
   End If
   
   Exit Function
DeleteSelectedQueryErr:
   DisplayError "Unable to delete the current query."
   fDeleteSelectedQuery = False
End Function

'* Adds a new query to the end of the query file
Private Sub NewQuery()
   
   On Error GoTo NewQueryErr
   
   m_oQueryFile.AddNew
   SelectQuery m_oQueryFile.QueryCount
   
   Exit Sub
NewQueryErr:
   DisplayError "Unable to add new query."
End Sub

'* Selects a query in the open query file
Private Sub SelectQuery(iQuery As Long)
   
   On Error GoTo SelectQueryErr
   
   UpdateSelectedQuery
   
   If Not iQuery = m_iSelectedQuery Then
      cctlResultsPane.Current = False
   End If
   
   ChangeSelectedQuery iQuery
   
   Exit Sub
SelectQueryErr:
   DisplayError "Unable to select query " & iQuery & "."
End Sub

'* Changes the selected query
Private Sub ChangeSelectedQuery(iQuery As Long)

   If fValidQueryIndex(iQuery) Then
      m_iSelectedQuery = iQuery
   Else
      m_iSelectedQuery = m_iInvalidQuery
   End If
   
   UpdateQueriesUI
         
   '* Select new query if valid iQuery
   If Not fValidQueryIndex(iQuery) Then
      cctlQueryPane.Query = vbNullString
      m_iSelectedQuery = m_iInvalidQuery
   Else
      cctlQueryPane.Query = m_oQueryFile.Queries(iQuery)
      m_iSelectedQuery = iQuery
   End If
End Sub

'* Updates the currently selected query
Private Sub UpdateSelectedQuery()
   Debug.Assert Not m_oQueryFile Is Nothing
   If fValidQueryIndex(m_iSelectedQuery) Then
      m_oQueryFile.Queries(m_iSelectedQuery) = cctlQueryPane.Query
   End If
End Sub

'* Returns true if the specified index is a valid query index in the current
'* query file, false if it is not
Private Function fValidQueryIndex(iQueryIndex As Long) As Boolean
   If m_oQueryFile Is Nothing Then
      fValidQueryIndex = False
   ElseIf iQueryIndex < 1 Then
      fValidQueryIndex = False
   ElseIf iQueryIndex > m_oQueryFile.QueryCount Then
      fValidQueryIndex = False
   Else
      fValidQueryIndex = True
   End If
End Function

'* Updates the UI's display of the open query file name
Private Sub UpdateFileNameUI()
   Me.Caption = App.Title & " - " & m_oQueryFile.Name
End Sub

'* Updates the UI's display of queries in the open query file
Private Sub UpdateQueriesUI()
   Dim i As Long, iPositionCnt As Long, iQueryCnt As Long
   Dim sQueryTitleCur As String, iEllipsesLen As Long
   
   iQueryCnt = m_oQueryFile.QueryCount
   iPositionCnt = mnuQueryList.UBound
   
   '* Add any required new menu list positions
   For i = iPositionCnt + 1 To iQueryCnt
      Load mnuQueryList(i)
   Next i
   
   '* Remove any extra menu list positions
   For i = iPositionCnt To iQueryCnt + 1 Step -1
      Unload mnuQueryList(i)
   Next i
   
   '* Clear toolbar combo box
   cboQueryList.Clear
   
   '* Update list of queries
   iEllipsesLen = Len(m_sQueryTitleEllipses)
   For i = 1 To iQueryCnt
      '* Get query title
      sQueryTitleCur = sprintf(m_sQueryTitlePrefix, CStr(i))
      If Len(m_oQueryFile.Queries(i)) = 0 Then
         sQueryTitleCur = sQueryTitleCur & "New Query"
      Else
         sQueryTitleCur = sQueryTitleCur & m_oQueryFile.Queries(i)
      End If
      If Len(sQueryTitleCur) > m_iQueryTitleLen Then
         sQueryTitleCur = _
                     Left(sQueryTitleCur, m_iQueryTitleLen - iEllipsesLen) & _
                     m_sQueryTitleEllipses
      End If
      
      '* Display query title in query menu
      With mnuQueryList(i)
         .Caption = sQueryTitleCur
         .Checked = False
         .Visible = True
      End With
      
      '* Display query title in toolbar combobox
      cboQueryList.AddItem sQueryTitleCur
   Next i
   
   m_fIngoreQueryListClicks = True
   If Not fValidQueryIndex(m_iSelectedQuery) Then
      '* Unselect all queries in toolbar drop-down
      cboQueryList.ListIndex = -1
   Else
      '* Check query in query menu
      mnuQueryList(m_iSelectedQuery).Checked = True
      
      '* Select query in toolbar drop-down
      cboQueryList.ListIndex = m_iSelectedQuery - 1
   End If
   m_fIngoreQueryListClicks = False
   
End Sub

'* Runs the currently selected query
'* Returns true if successful, otherwise false
Private Function RunQuery() As Boolean
   Dim sErrMsg As String
   
   Debug.Assert fConnected
   
   On Error GoTo RunQueryErr
   SetHourglass True
   SetStatus "Opening cellset..."
   
   sErrMsg = "Unable to open cellset"
   
   '* Update the query
   UpdateSelectedQuery
   UpdateQueriesUI
   
   '*** ADOMD Example ***
   
   '* Close the cellset if it is open
   If m_csResults.State = adStateOpen Then
      m_csResults.Close
   End If
      
   '* Execute the query
   Set m_csResults = New Cellset
   m_csResults.Open cctlQueryPane.Query, m_cn
   
   '*** End Example ***
   
   sErrMsg = "Unable to display opened cellset"
   
   '* Display results
   Set cctlResultsPane.ActiveCellset = m_csResults
   
   '* Enable pivot results
   UpdatePivotUI True
   
   SetStatus
   SetHourglass False
   RunQuery = True
   
   Exit Function
RunQueryErr:
   SetHourglass False
   DisplayError sErrMsg, m_cn
   SetStatus sErrMsg
   UpdatePivotUI False
   cctlResultsPane.Current = False
   RunQuery = False
End Function

'* Attempts to run every query in the query file
'* Returns true if all queries where run successfully, otherwise false
Private Function RunAllQueries() As Boolean
   Dim i As Long
   
   RunAllQueries = True
   For i = 1 To m_oQueryFile.QueryCount
      ChangeSelectedQuery i
      Me.Refresh
      If Not RunQuery() Then
         RunAllQueries = False
         Exit For
      End If
   Next i
   tlbMain.Refresh
End Function

'* Updates the UI enabling of query run
Private Sub UpdateQueryRunUI(Optional vConnected As Variant)
   Static fConnected As Boolean
   Dim fCanRun As Boolean
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   If Not IsMissing(vConnected) Then
      fConnected = CBool(vConnected)
   End If
   
   fCanRun = fConnected And (Len(Trim(cctlQueryPane.Query)) > 0)
   
   mnuQueryItem(m_iMnuQueryRun).Enabled = fCanRun
   tlbMain.Buttons("QueryRun").Enabled = fCanRun
   
End Sub

'* Updates the UI enabling of pivot results
Private Sub UpdatePivotUI(fCanPivot As Boolean)
   mnuViewItem(m_iMnuViewPivotResults).Enabled = fCanPivot
   tlbMain.Buttons("Pivot").Enabled = fCanPivot
End Sub

'* Process command line arguments, returns false if an unexpected argument
'* is encountered.
'*
'* Expected arguments
'*    /C <connect String>  specifies the connection string to use to open a
'*                         connection
'*    /F <filename>        specifies a query file to be opened
'*    /R                   attempts to runs all queries in the specified file
'*                         (requires /F and /C)
Private Function fParseCommandLine(sCommandLine As String, _
                                   O_sConnectStr As String, _
                                   O_sQueryFile As String, _
                                   O_fRunAll As Boolean) As Boolean
   Dim fDisplayHelp As Boolean
   Dim sArgFlagCur As String, sArgValueCur As String
   Dim sMsg As String
   
   On Error GoTo fParseCommandLineErr
   
   Do Until Len(sCommandLine) = 0
      RemoveNextArgument sCommandLine, sArgFlagCur, sArgValueCur
      Select Case sArgFlagCur
         Case m_sCommandLineFlagConnect
            O_sConnectStr = sArgValueCur
         Case m_sCommandLineFlagFile
            O_sQueryFile = sArgValueCur
         Case m_sCommandLineFlagRunAll
            O_fRunAll = True
         Case Else
            fDisplayHelp = True
      End Select
   Loop
   
   If O_fRunAll Then
      If Len(O_sConnectStr) = 0 Or Len(O_sQueryFile) = 0 Then
         fDisplayHelp = True
      End If
   End If
      
   If fDisplayHelp Then
      sMsg = "MDXSample Usage:" & vbCrLf
      sMsg = sMsg & "   " & m_sCommandLineArgStart & _
            m_sCommandLineFlagConnect & vbTab & "<ConnectionString>" & vbTab & _
            vbTab & "Connect to the given data source" & vbCrLf
      sMsg = sMsg & "   " & m_sCommandLineArgStart & m_sCommandLineFlagFile & _
             vbTab & "<FileName>" & vbTab & vbTab & _
             "Open the given query file" & vbCrLf
      sMsg = sMsg & "   " & m_sCommandLineArgStart & _
            m_sCommandLineFlagRunAll & vbTab & vbTab & vbTab & vbTab & _
            "Run all queries in the specified file (requires /F and /C)"
             
      MsgBox sMsg, vbOKOnly, App.Title
      
      fParseCommandLine = False
   Else
      fParseCommandLine = True
   End If
   
   Exit Function
fParseCommandLineErr:
   fParseCommandLine = False
   DisplayError "Unable to parse command line arguments."
End Function

'* Removes the next command line from the input string
Private Sub RemoveNextArgument(sArguments As String, _
                                O_sArgFlag As String, _
                                O_sArgValue As String)
   Dim iPos As Long, fInQuote As Boolean
   
   sArguments = Trim(sArguments)
   
   '* Get and remove argument flag
   Select Case Mid(sArguments, 1, 1)
      Case m_sCommandLineArgStart, m_sCommandLineArgStartAlt
         O_sArgFlag = Mid(sArguments, 2, 1)
         sArguments = Mid(sArguments, 3)
      Case Else
         O_sArgFlag = vbNullString
   End Select
   
   '* Get and remove argument value
   sArguments = Trim(sArguments)
   iPos = 1
   Do
      Select Case Mid(sArguments, iPos, 1)
         Case m_sCommandLineQuote
            If fInQuote Then
               If Mid(sArguments, iPos + 1, 1) = m_sCommandLineQuote Then
                  sArguments = _
                        Left(sArguments, iPos) & Mid(sArguments, iPos + 2)
                  iPos = iPos + 1
               Else
                  O_sArgValue = Left(sArguments, iPos - 1)
                  sArguments = Mid(sArguments, iPos + 1)
                  Exit Do
               End If
            Else
               sArguments = Mid(sArguments, 2)
               fInQuote = True
            End If
         Case vbTab, " ", vbNullString, m_sCommandLineArgStart, _
                  m_sCommandLineArgStartAlt
            If fInQuote Then
               iPos = iPos + 1
            Else
               O_sArgValue = Left(sArguments, iPos - 1)
               sArguments = Mid(sArguments, iPos)
               Exit Do
            End If
         Case Else
            iPos = iPos + 1
      End Select
   Loop
   
   sArguments = Trim(sArguments)
End Sub

'* Toggle the toolbar on and off
Private Sub ToggleToolbar()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   tlbMain.Visible = Not tlbMain.Visible
   mnuViewItem(m_iMnuViewToolbar).Checked = tlbMain.Visible
   Form_Resize
End Sub

'* Toggle the status bar on and off
Private Sub ToggleStatusBar()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   stbMain.Visible = Not stbMain.Visible
   mnuViewItem(m_iMnuViewStatusBar).Checked = stbMain.Visible
   Form_Resize
End Sub

'* Cut the current se
Private Sub EditCut()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   With Me.ActiveControl
      Clipboard.Clear
      Clipboard.SetText .SelText
      .SelText = vbNullString
   End With
End Sub

Private Sub EditCopy()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   With Me.ActiveControl
      Clipboard.Clear
      Clipboard.SetText .SelText
   End With
End Sub

Private Sub EditPaste()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   With Me.ActiveControl
      .SelText = Clipboard.GetText
      .SelStart = .SelStart + .SelLength
      .SelLength = 0
   End With
End Sub

'* Updates the UI enabling of cut & paste features
Private Sub UpdateCutAndPasteUI(fCanCut As Boolean, _
                                fCanCopy As Boolean, _
                                fCanPaste As Boolean)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   mnuEditItem(m_iMnuEditCut).Enabled = fCanCut
   tlbMain.Buttons("EditCut").Enabled = fCanCut
   
   mnuEditItem(m_iMnuEditCopy).Enabled = fCanCopy
   tlbMain.Buttons("EditCopy").Enabled = fCanCopy
      
   mnuEditItem(m_iMnuEditPaste).Enabled = fCanPaste
   tlbMain.Buttons("EditPaste").Enabled = fCanPaste
End Sub

'* Updates the view
Private Sub SetView(eNewView As ViewType)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case eNewView
      Case vtSplit
         srgMain.SplitPercent = m_nLastSplitPercent
      Case vtQuery
         srgMain.SplitPercent = 100
      Case vtResults
         srgMain.SplitPercent = 0
   End Select
End Sub

'* Pivots
Private Sub PivotResults()
   Dim fPivot As Boolean
   
   On Error GoTo PivotResultsErr
   SetHourglass True
   
   fPivot = Not cctlResultsPane.Pivoted
   mnuViewItem(m_iMnuViewPivotResults).Checked = fPivot
   tlbMain.Buttons("Pivot").Value = Abs(fPivot)
   cctlResultsPane.Pivoted = fPivot
   
   SetHourglass False
   
   Exit Sub
PivotResultsErr:
   SetHourglass False
   DisplayError "Unable to pivot results.", m_cn
End Sub

'* Safely returns the current query file path
Private Function sGetCurrentFile() As String
   If m_oQueryFile Is Nothing Then
      sGetCurrentFile = vbNullString
   Else
      sGetCurrentFile = m_oQueryFile.File
   End If
End Function



'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Cancel = Not fPromptToSaveChanges
End Sub

Private Sub mnuFileItem_Click(Index As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case Index
      Case m_iMnuFileConnect
         Connect
      Case m_iMnuFileDisconnect
         Disconnect
      Case m_iMnuFileNew
         FileNew
      Case m_iMnuFileOpen
         FileOpen
      Case m_iMnuFileSave
         FileSave
      Case m_iMnuFileSaveAs
         FileSaveAs
      Case m_iMnuFileExit
         Unload Me
   End Select
End Sub

Private Sub mnuEditItem_Click(Index As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case Index
      Case m_iMnuEditCut
         EditCut
      Case m_iMnuEditCopy
         EditCopy
      Case m_iMnuEditPaste
         EditPaste
   End Select
End Sub

Private Sub mnuQueryItem_Click(Index As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case Index
      Case m_iMnuQueryNew
         NewQuery
      Case m_iMnuQueryDelete
         fDeleteSelectedQuery
      Case m_iMnuQueryRun
         RunQuery
      Case m_iMnuQueryRunAll
         RunAllQueries
   End Select
End Sub

Private Sub mnuViewItem_Click(Index As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case Index
      Case m_iMnuViewSplit
         SetView vtSplit
      Case m_iMnuViewQuery
         SetView vtQuery
      Case m_iMnuViewResults
         SetView vtResults
      Case m_iMnuViewToolbar
         ToggleToolbar
      Case m_iMnuViewStatusBar
         ToggleStatusBar
      Case m_iMnuViewPivotResults
         PivotResults
   End Select
End Sub

Private Sub mnuHelpItem_Click(Index As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case Index
      Case m_iMnuHelpContextHelp
      Case m_iMnuHelpContentsAndIndex
         WinHelp Me.hwnd, App.HelpFile, HELP_FINDER, 0&
      Case m_iMnuHelpSyntaxHelp
      Case m_iMnuHelpAbout
         frmAbout.Show 1
   End Select
End Sub

Private Sub mnuQueryList_Click(Index As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   SelectQuery CLng(Index)
End Sub

Private Sub cctlQueryPane_EditCapabilityChange(fCanCut As Boolean, _
                                               fCanCopy As Boolean, _
                                               fCanPaste As Boolean)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   UpdateCutAndPasteUI fCanCut, fCanCopy, fCanPaste
End Sub

Private Sub cctlQueryPane_QueryChanged()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   UpdateQueryRunUI
End Sub

Private Sub cctlResultsPane_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   UpdateCutAndPasteUI False, False, False
End Sub

Private Sub srgMain_RepositionSplit()
   Dim fSplitView As Boolean, fQueryView As Boolean, fResultsVeiw As Boolean
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case srgMain.SplitPercent
      Case 0
         fResultsVeiw = True
      Case 100
         fQueryView = True
      Case Else
         fSplitView = True
         m_nLastSplitPercent = srgMain.SplitPercent
   End Select
   
   mnuViewItem(m_iMnuViewSplit).Checked = fSplitView
   tlbMain.Buttons("ViewSplit").Value = Abs(fSplitView)
   
   mnuViewItem(m_iMnuViewQuery).Checked = fQueryView
   tlbMain.Buttons("ViewQuery").Value = Abs(fQueryView)
   
   mnuViewItem(m_iMnuViewResults).Checked = fResultsVeiw
   tlbMain.Buttons("ViewResults").Value = Abs(fResultsVeiw)

End Sub

Private Sub stbMain_PanelDblClick(ByVal Panel As ComctlLib.Panel)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   If Panel.Key = "Connection" Then
      If fConnected Then
         Disconnect
      Else
         Connect
      End If
   End If
End Sub

Private Sub tlbMain_ButtonClick(ByVal Button As ComctlLib.Button)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   Select Case Button.Key
      Case "Connect"
         Button.Value = tbrPressed
         If fConnected Then
            Disconnect
         Else
            Connect
         End If
      Case "FileNew"
         FileNew
      Case "FileOpen"
         FileOpen
      Case "FileSave"
         FileSave
      Case "EditCut"
         EditCut
      Case "EditCopy"
         EditCopy
      Case "EditPaste"
         EditPaste
      Case "QueryNew"
         NewQuery
      Case "QueryDelete"
         fDeleteSelectedQuery
      Case "QueryRun"
         RunQuery
      Case "ViewSplit"
         SetView vtSplit
      Case "ViewQuery"
         SetView vtQuery
      Case "ViewResults"
         SetView vtResults
      Case "Pivot"
         PivotResults
   End Select
End Sub

Private Sub cboDatabaseList_Click()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   m_cn.DefaultDatabase = cboDatabaseList.Text
   Set cctlQueryPane.ActiveConnection = m_cn
End Sub

Private Sub cboQueryList_Click()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   If Not m_fIngoreQueryListClicks Then
      SelectQuery cboQueryList.ListIndex + 1
   End If
End Sub

Private Sub cboQueryList_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   UpdateCutAndPasteUI False, False, False
End Sub

Private Sub cboQueryList_DropDown()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   UpdateSelectedQuery
   UpdateQueriesUI
End Sub

Private Sub Form_Load()
   Dim sConnectStr As String, sQueryFile As String, fRunAll As Boolean
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
   
   '* Set properties based on app title
   mnuHelpItem(m_iMnuHelpContextHelp).Caption = App.Title & " &Help"
   mnuHelpItem(m_iMnuHelpAbout).Caption = "&About " & App.Title
   frmMain.Caption = App.Title
   
   Set m_csResults = New Cellset
   
   '* Parse command line arguments
   If Not fParseCommandLine(Command$, sConnectStr, sQueryFile, fRunAll) Then
      Unload Me
   Else
   
      Set stbMain.Panels("Connection").Picture = imlToolbar.ListImages("NotConnected").ExtractIcon
      Me.Show
      
      '* Open a connection using connect string specified on the command line
      Connect sConnectStr
      
      '* Opens the file specified on the command line or a new query file
      '* containing a single blank query
      If Len(sQueryFile) > 0 Then
         FileOpen sQueryFile
      Else
         FileNew
      End If
      
      '* Run queries if requested in command line
      If fRunAll Then
         If fConnected Then
            RunAllQueries
         End If
      End If
      
      '* Save initial split position
      m_nLastSplitPercent = srgMain.SplitPercent
   
   End If
   
End Sub

Private Sub Form_Resize()
   Dim nToolbarHeight As Single, nStatusBarHeight As Single
   Dim nNewHeight As Single, nNewWidth As Single
     
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   '* Position query list caption on toolbar
   With tlbMain.Buttons("QueryListCaption")
      pctQueryListCaption.Move .Left, .Top, .Width, .Height
   End With
   
   '* Position query list combo on toolbar
   With tlbMain.Buttons("QueryList")
      cboQueryList.Move .Left, .Top, .Width
   End With
   
   '* Position Database list caption on toolbar
   With tlbMain.Buttons("DatabaseListCaption")
      pctDatabaseListCaption.Move .Left, .Top, .Width, .Height
   End With
   
   '* Position Database list combo on toolbar
   With tlbMain.Buttons("databaseList")
      cboDatabaseList.Move .Left, .Top, .Width
   End With
     
   '* Resize SplitRegion
   If tlbMain.Visible Then
      nToolbarHeight = tlbMain.Height
   Else
      nToolbarHeight = 0
   End If
   If stbMain.Visible Then
      nStatusBarHeight = stbMain.Height
   Else
      nStatusBarHeight = 0
   End If
  
   nNewWidth = Me.ScaleWidth - 2 * m_nHorizontalBorder
   nNewHeight = Me.ScaleHeight - nToolbarHeight - nStatusBarHeight
   If nNewHeight > srgMain.SplitterBarThickness + _
                   srgMain.FirstControlMinSize + _
                   srgMain.SecondControlMinSize Then
      srgMain.Move m_nHorizontalBorder, _
                   nToolbarHeight, _
                   nNewWidth, _
                   nNewHeight
   End If
End Sub

