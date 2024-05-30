VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form AEditorUI 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Agent Editor"
   ClientHeight    =   7560
   ClientLeft      =   2445
   ClientTop       =   2310
   ClientWidth     =   11010
   Icon            =   "AEditUI.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7560
   ScaleWidth      =   11010
   ShowInTaskbar   =   0   'False
   Begin ComctlLib.Toolbar MainToolbar 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   21
      Top             =   0
      Width           =   11010
      _ExtentX        =   19420
      _ExtentY        =   741
      ButtonWidth     =   635
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlMainToolbar"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   8
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.ToolTipText     =   "Agent"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Visible         =   0   'False
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.ToolTipText     =   "Save Changes"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Object.Tag             =   ""
            ImageIndex      =   4
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.ToolTipText     =   "Delete Column"
            Object.Tag             =   ""
            ImageIndex      =   4
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.ToolTipText     =   "Insert Column"
            Object.Tag             =   ""
            ImageIndex      =   5
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.ToolTipText     =   "Delete Row"
            Object.Tag             =   ""
            ImageIndex      =   6
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Enabled         =   0   'False
            Object.Visible         =   0   'False
            Object.ToolTipText     =   "Insert Row"
            Object.Tag             =   ""
            ImageIndex      =   7
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   10500
      Top             =   6360
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DialogTitle     =   "Event Script"
      Filter          =   "*.vbs;*.txt"
      InitDir         =   "C:\"
   End
   Begin TabDlg.SSTab MainTabs 
      Height          =   6195
      Left            =   120
      TabIndex        =   6
      Top             =   1320
      Width           =   10695
      _ExtentX        =   18865
      _ExtentY        =   10927
      _Version        =   393216
      Tab             =   1
      TabHeight       =   520
      WordWrap        =   0   'False
      TabCaption(0)   =   "Script"
      TabPicture(0)   =   "AEditUI.frx":030A
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "RETextBox"
      Tab(0).Control(1)=   "btnSelectScript"
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "Map"
      TabPicture(1)   =   "AEditUI.frx":0326
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "grdData"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "txtGridEdit"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "optMap(0)"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).Control(3)=   "optMap(1)"
      Tab(1).Control(3).Enabled=   0   'False
      Tab(1).Control(4)=   "btnMap(0)"
      Tab(1).Control(4).Enabled=   0   'False
      Tab(1).Control(5)=   "btnMap(1)"
      Tab(1).Control(5).Enabled=   0   'False
      Tab(1).Control(6)=   "btnMap(2)"
      Tab(1).Control(6).Enabled=   0   'False
      Tab(1).ControlCount=   7
      TabCaption(2)   =   "Agent"
      TabPicture(2)   =   "AEditUI.frx":0342
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "Frame1"
      Tab(2).Control(1)=   "Frame3"
      Tab(2).Control(2)=   "Frame2"
      Tab(2).ControlCount=   3
      Begin VB.CommandButton btnMap 
         Caption         =   "E&xport Map"
         Height          =   315
         Index           =   2
         Left            =   5100
         TabIndex        =   28
         Top             =   600
         Width           =   1575
      End
      Begin VB.CommandButton btnMap 
         Caption         =   "&Import Map"
         Height          =   315
         Index           =   1
         Left            =   6960
         TabIndex        =   27
         Top             =   600
         Width           =   1575
      End
      Begin VB.CommandButton btnMap 
         Caption         =   "&Clear Map"
         Height          =   315
         Index           =   0
         Left            =   8880
         TabIndex        =   26
         Top             =   600
         Width           =   1575
      End
      Begin VB.OptionButton optMap 
         Caption         =   "Map Stored on Route &Binding in Current Folder"
         Height          =   195
         Index           =   1
         Left            =   180
         TabIndex        =   25
         Top             =   780
         Width           =   5535
      End
      Begin VB.OptionButton optMap 
         Caption         =   "Map Stored on Current &Folder"
         Height          =   195
         Index           =   0
         Left            =   180
         TabIndex        =   24
         Top             =   480
         Value           =   -1  'True
         Width           =   3135
      End
      Begin VB.CommandButton btnSelectScript 
         Caption         =   "&Open Script..."
         Height          =   315
         Left            =   -74820
         TabIndex        =   23
         Top             =   540
         Visible         =   0   'False
         Width           =   1515
      End
      Begin VB.TextBox txtGridEdit 
         Height          =   315
         Left            =   240
         TabIndex        =   22
         Top             =   1920
         Width           =   855
      End
      Begin VB.Frame Frame1 
         Height          =   1155
         Left            =   -73440
         TabIndex        =   15
         Top             =   1080
         Width           =   2895
         Begin VB.CheckBox ChkActive 
            Caption         =   "&Agent Enabled"
            Height          =   210
            Left            =   480
            TabIndex        =   16
            Top             =   540
            Width           =   1815
         End
      End
      Begin VB.Frame Frame3 
         Caption         =   "When the following events occur"
         Height          =   2775
         Left            =   -73440
         TabIndex        =   10
         Top             =   2340
         Width           =   7215
         Begin VB.CheckBox ChkEvent 
            Caption         =   "A scheduled event &occurs"
            Height          =   210
            Index           =   1
            Left            =   1080
            TabIndex        =   14
            Top             =   1980
            Width           =   3075
         End
         Begin VB.CheckBox ChkEvent 
            Caption         =   "A new item is &posted"
            Height          =   210
            Index           =   2
            Left            =   1080
            TabIndex        =   13
            TabStop         =   0   'False
            Top             =   1620
            Width           =   3075
         End
         Begin VB.CheckBox ChkEvent 
            Caption         =   "An i&tem is changed"
            Height          =   195
            Index           =   3
            Left            =   1080
            TabIndex        =   12
            TabStop         =   0   'False
            Top             =   1200
            Width           =   3075
         End
         Begin VB.CheckBox ChkEvent 
            Caption         =   "An ite&m is deleted"
            Height          =   210
            Index           =   4
            Left            =   1080
            TabIndex        =   11
            TabStop         =   0   'False
            Top             =   780
            Width           =   3075
         End
      End
      Begin VB.Frame Frame2 
         Height          =   1155
         Left            =   -70440
         TabIndex        =   7
         Top             =   1080
         Width           =   4155
         Begin VB.TextBox txtAgentName 
            Height          =   285
            Left            =   180
            TabIndex        =   8
            Text            =   "Text1"
            Top             =   660
            Width           =   3735
         End
         Begin VB.Label Label1 
            BackStyle       =   0  'Transparent
            Caption         =   "Agent Name:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   315
            Left            =   180
            TabIndex        =   9
            Top             =   240
            Width           =   1815
         End
      End
      Begin MSFlexGridLib.MSFlexGrid grdData 
         Height          =   4875
         Left            =   120
         TabIndex        =   17
         Top             =   1140
         Width           =   10455
         _ExtentX        =   18441
         _ExtentY        =   8599
         _Version        =   65541
         Cols            =   4
         FixedCols       =   0
         FocusRect       =   2
         AllowUserResizing=   1
      End
      Begin RichTextLib.RichTextBox RETextBox 
         Height          =   4935
         Left            =   -74820
         TabIndex        =   18
         Top             =   900
         Visible         =   0   'False
         Width           =   10395
         _ExtentX        =   18336
         _ExtentY        =   8705
         _Version        =   393217
         Enabled         =   -1  'True
         ScrollBars      =   3
         TextRTF         =   $"AEditUI.frx":035E
      End
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Class Handler Name:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   5940
      TabIndex        =   20
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label lblHandlerName 
      BackStyle       =   0  'Transparent
      Caption         =   "lblHandlerName"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7920
      TabIndex        =   19
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label lblHostName 
      BackStyle       =   0  'Transparent
      Caption         =   "lblHostName"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3360
      TabIndex        =   5
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label lblFolderName 
      BackStyle       =   0  'Transparent
      Caption         =   "lblFolderName"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3360
      TabIndex        =   4
      Top             =   480
      Width           =   1815
   End
   Begin VB.Label lblAgentName 
      BackStyle       =   0  'Transparent
      Caption         =   "lblAgentName"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7920
      TabIndex        =   3
      Top             =   480
      Width           =   1815
   End
   Begin VB.Label Label8 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Agent Name:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   5940
      TabIndex        =   2
      Top             =   480
      Width           =   1815
   End
   Begin VB.Label Label6 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Host Server Name:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1380
      TabIndex        =   1
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label Label5 
      Alignment       =   1  'Right Justify
      BackStyle       =   0  'Transparent
      Caption         =   "Folder Name:"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   1380
      TabIndex        =   0
      Top             =   480
      Width           =   1815
   End
   Begin ComctlLib.ImageList imlMainToolbar 
      Left            =   120
      Top             =   600
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   7
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":045C
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":0776
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":0AC8
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":0E1A
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":116C
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":14BE
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "AEditUI.frx":1810
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuAgentTop 
      Caption         =   "A&gent"
      Begin VB.Menu mnuAgent 
         Caption         =   "Select &Folder"
         Index           =   0
      End
      Begin VB.Menu mnuAgent 
         Caption         =   "Select &Agent"
         Enabled         =   0   'False
         Index           =   1
      End
      Begin VB.Menu mnuAgent 
         Caption         =   "-"
         Index           =   2
      End
      Begin VB.Menu mnuAgent 
         Caption         =   "&Save Changes"
         Enabled         =   0   'False
         Index           =   3
      End
      Begin VB.Menu mnuAgent 
         Caption         =   "-"
         Index           =   4
      End
      Begin VB.Menu mnuAgent 
         Caption         =   "&Exit"
         Index           =   5
      End
      Begin VB.Menu mnuAgent 
         Caption         =   "Exit &Without Save"
         Index           =   6
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Index           =   6
      Begin VB.Menu mnuEditSub1 
         Caption         =   "Cu&t"
         Enabled         =   0   'False
         Index           =   0
      End
      Begin VB.Menu mnuEditSub1 
         Caption         =   "C&opy"
         Enabled         =   0   'False
         Index           =   1
      End
      Begin VB.Menu mnuEditSub1 
         Caption         =   "&Paste"
         Enabled         =   0   'False
         Index           =   2
      End
      Begin VB.Menu mnuEditSub1 
         Caption         =   "&Select All"
         Enabled         =   0   'False
         Index           =   3
      End
      Begin VB.Menu mnuSeparatorEditSub 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "&Add Column"
         Index           =   1
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "Insert &Row"
         Enabled         =   0   'False
         Index           =   2
         Visible         =   0   'False
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "&Delete Row"
         Enabled         =   0   'False
         Index           =   3
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "Delete Colu&mn"
         Enabled         =   0   'False
         Index           =   4
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "-"
         Index           =   5
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "&Cut Cell"
         Enabled         =   0   'False
         Index           =   6
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "C&opy Cell"
         Enabled         =   0   'False
         Index           =   7
      End
      Begin VB.Menu mnuEditSub2 
         Caption         =   "&Paste Cell"
         Enabled         =   0   'False
         Index           =   8
      End
   End
End
Attribute VB_Name = "AEditorUI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'Local Constants
Private Const SCRIPT_CAPTION = "Script"
Private Const MAP_CAPTION = "Map"
Private Const AGENT_CAPTION = "Agent"

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'
'  AGENT EDITOR UI (AEditorUI)
'
'  Overview: This is main UI form that is called from mainmodule upon
'  program start up. It contains the toolbars, menu and a 3 tab - tab
'  control.
'***********************************************************************

'GRID CONTROL
Private bEditChange As Boolean

'----------------------------------------------------------
' Sub: BTN MAP CLICK
'
' Action: Clear, Import or Export Maps
'
'----------------------------------------------------------
Private Sub btnMap_Click(Index As Integer)

Select Case Index
   Case BTN_MAP_CLEAR
      Call ClearGrid
      Call FormatGridHeaders
      Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
      Call UpdateMenuToolbarItem("DEL ROW", False)
      
   Case BTN_MAP_IMPORT
      Call ImportMap(AEditorUI.grdData)
      
   Case BTN_MAP_EXPORT
      Call ExportMap(AEditorUI.grdData)
      
End Select

End Sub

'----------------------------------------------------------
' Sub: BTN SELECT SCRIPT CLICK
'
' Action: Select a script and place in rich edit control.
'----------------------------------------------------------
Private Sub btnSelectScript_Click()
   Call SelectScript
End Sub

'----------------------------------------------------------
' Sub: CHK ACTIVE CLICK
'
' Action: Update the dirty status.
'----------------------------------------------------------
Private Sub ChkActive_Click()
   Call DirtyStatusUpdate(DIRTY_AGENT, DIRTY_ADD)
End Sub

'----------------------------------------------------------
' Sub: CHK EVENT CLICK
'
' Action: Update the dirty status.
'----------------------------------------------------------
Private Sub ChkEvent_Click(Index As Integer)
   Call DirtyStatusUpdate(DIRTY_AGENT, DIRTY_ADD)
End Sub

'----------------------------------------------------------
' Sub: FORM LOAD
'
' Action: Entry sub for the form. Set in UI defaults.
'----------------------------------------------------------
Private Sub Form_Load()

   Dim X As Integer    'loop variable
   
   'Initialize UI Name
   AEditorUI.Caption = "Agent Editor"
  
   'Initialize UI Variables
   lblFolderName = "No folder selected"
   lblHostName = "n/a"
   lblAgentName = "n/a"
   lblHandlerName = "n/a"
   
   'Make sure the first tab is always selected
   'no matter what the design environment was set at.
   MainTabs.Tab = TAB_SCRIPT
   For X = TAB_SCRIPT To TAB_AGENT
      MainTabs.TabEnabled(X) = False
   Next
   
   Call DirtyStatusUpdate(DIRTY_NONE, DIRTY_REMOVE)
   
   'This is enabled in the design environment so
   'you can just click on it and go the function to
   'edit it, so default it to false here.
    mnuEditSub2.item(MENU_INSERT_COL).Enabled = False
    
End Sub

'----------------------------------------------------------
' Sub: MNU EDIT SUB 1
'
' Comment: SCRIPT EDITING
'
' Action: Events for Script cut, copy, paste and select all
' are located here.
'
' Parm: Index of selected menu item
'
'----------------------------------------------------------
Private Sub mnuEditSub1_Click(Index As Integer)
   
   Dim sTempStart As String
   Dim sTempEnd As String
   
   Select Case Index
      Case MENU_CUT_SCRIPT
          'Grab beginning and end and concatenate them after grabbing
          'selected text.
          If Len(RETextBox.SelText) > 0 Then
            sTempStart = Left(RETextBox.Text, RETextBox.SelStart)
            sTempEnd = Mid(RETextBox.Text, RETextBox.SelStart + RETextBox.SelLength + 1)
            Clipboard.Clear
            Clipboard.SetText RETextBox.SelText
            RETextBox.Text = sTempStart + sTempEnd
          End If
          
      Case MENU_COPY_SCRIPT
          Clipboard.Clear
          Clipboard.SetText RETextBox.SelText  'Put text on clipboard
          
      Case MENU_PASTE_SCRIPT
          RETextBox.SelText = Clipboard.GetText
          
      Case MENU_SELECTALL_SCRIPT
          RETextBox.SelStart = 0
          RETextBox.SelLength = Len(RETextBox.Text)
   End Select
End Sub

'----------------------------------------------------------
' Sub: MNU EDIT SUB 2
'
' Comment: MAP EDITING
'
' Action: 6 menu options that allows cut, copy, paste a cell
' and add,del a column and delete a row.
'
' Parm: Index of selected menu item
'
'----------------------------------------------------------
Private Sub mnuEditSub2_Click(Index As Integer)
   Select Case Index
      Case MENU_INSERT_COL
         'Add Column
         Call AddMapColumn
         Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
         
      Case MENU_DEL_COL
         Call DelMapColumn
         Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
          
      Case MENU_DEL_ROW
         Call DelMapRow
         Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
          
      Case MENU_CUT_CELL
         AEClass.CellData = grdData
         grdData = ""
         Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
          
      Case MENU_COPY_CELL
         AEClass.CellData = grdData
         
      Case MENU_PASTE_CELL
         grdData = AEClass.CellData
         Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
      
      Case Else
         MsgBox "Untrapped Menu Selection."
   End Select
End Sub

'----------------------------------------------------------
' Sub: MAIN TOOLBAR BUTTON CLICK
'
'
' Action: Passes the click events over to the repective
' menu click events and are processed there.
'
' Parm: Button Object intrinsic to the control
'
'----------------------------------------------------------
Private Sub MainToolbar_ButtonClick(ByVal Button As ComctlLib.Button)
   Select Case Button.Index
      Case TOOLBAR_AGENT
         Call mnuAgent_Click(MENU_AGENT_FOLDER_SELECT)
      
      Case TOOLBAR_SAVE
         Call mnuAgent_Click(MENU_AGENT_SAVE)
         
      Case TOOLBAR_DEL_COL
         Call mnuEditSub2_Click(MENU_DEL_COL)
         
      Case TOOLBAR_DEL_ROW
         Call mnuEditSub2_Click(MENU_DEL_ROW)
         
      Case TOOLBAR_INSERT_COL
         Call mnuEditSub2_Click(MENU_INSERT_COL)
   End Select
End Sub

'----------------------------------------------------------
' Sub: DEL MAP ROW
'
' Action: Delete a row from the map. Prompt for delete.
' Update UI as necessary (disable delete if needed).
'----------------------------------------------------------
Private Sub DelMapRow()
   
   If MsgBox("Delete current row?", vbYesNo + vbQuestion, App.Title) = vbYes Then
      
      'Make any edit grid invisible and clear
      txtGridEdit = ""
      txtGridEdit.Visible = False
      If grdData.Rows > 2 Then
         grdData.RemoveItem grdData.Row
         Call SetDeleteRow 'Update Delete Row feature visibility
         
      Else
         Call ClearGrid
         Call FormatGridHeaders
      End If
   End If

End Sub

'----------------------------------------------------------
' Sub: DEL MAP COLUMN
'
' Action: Delete a column from the map. Prompt for delete.
' Update UI as necessary. Don't allow delete of first four
' columns since they are required anyway as a minimum
'----------------------------------------------------------
Private Sub DelMapColumn()
   Dim lRow As Integer
   Dim lCol As Integer
   If grdData.Col > 3 Then
      If MsgBox("Delete current parameter column?", vbYesNo + vbQuestion, App.Title) = vbYes Then
         txtGridEdit = ""
         txtGridEdit.Visible = False
         For lCol = grdData.Col To grdData.Cols - 2
            For lRow = 1 To grdData.Rows - 1
               grdData.TextMatrix(lRow, lCol) = grdData.TextMatrix(lRow, lCol + 1)
            Next
         Next
      grdData.Cols = grdData.Cols - 1
      If grdData.Col < 4 Then
         Call UpdateMenuToolbarItem("DEL COL", False)
      Else
         Call UpdateMenuToolbarItem("DEL COL", True)
      End If
      End If
   Else
      MsgBox "Columns 1-4 are required and cannot be deleted.", vbInformation, App.Title
   End If
End Sub

'----------------------------------------------------------
' Sub: ADD MAP COLUMN
'
' Action: Add a parmeter column and the end of the map.
'----------------------------------------------------------
Private Sub AddMapColumn()
   
   Dim sFormatString As String     'String Format of Header with text
   Dim X As Integer                'loop variable
            
   'Add Column
   grdData.Cols = grdData.Cols + 1
   
   'Update Header Information.
   sFormatString = "^ActivityID" & Space(6) & "|^Activity" & Space(32) & "|^Flags" & Space(20)
   For X = 3 To grdData.Cols - 1
      sFormatString = sFormatString & "|^Parameters" & Space(32)
   Next
   grdData.FormatString = sFormatString
   
   Call UpdateMenuToolbarItem("DEL COL", True)
   
End Sub

'----------------------------------------------------------
' Sub: OPT MAP CLICK
'
' Action: Handles map option click event. Selects between
' storing map on the binding or on the FAI message.
'----------------------------------------------------------
Private Sub optMap_Click(Index As Integer)

Dim b_IGNORE As Boolean

Dim iVal As Integer  'Integer Return Value

   
'Prompt for save if dirty.
If (AEClass.Dirty And DIRTY_MAP) <> DIRTY_NONE Then
   iVal = MsgBox("The map has been modified. Save Changes to map ?", vbYesNo + vbQuestion, App.Title)
   If iVal = vbYes Then
      'Save changes to map
      AEditorUI.MousePointer = vbHourglass
      Call SaveRouteMap(grdData)
      AEditorUI.MousePointer = vbNormal
   End If
   Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_REMOVE)
End If

'Get MSG and MAP
Select Case Index
   Case 0  'FAI
   
      'READ IN FAI MAP
      'IF GET ROUTING MSG FAILS THEN THERE IS NO ROUTING MESSAGE
      'AND THE GET MAP AUTOMATICALLY CREATES ONE
      b_IGNORE = AgentMap.GetRoutingMsg
      b_IGNORE = AgentMap.GetMap("ROUTING")
      
   Case 1  'Binding
      If AEClass.EditMode = MODE_NEW_AGENT Then
         'no binding exist. just blank map
         Call PrepareGrid

         If (MsgBox("In order to edit this map you have to save the agent first. Save the agent ?", vbYesNo + vbQuestion, App.Title) = vbYes) Then
            If Not SaveAgent Then
               Exit Sub
            End If
            AEClass.EditMode = MODE_EDIT_AGENT
         Else
            MsgBox "Unable to allow editing of binding map.", vbCritical, App.Title
            b_IGNORE = AgentMap.GetRoutingMsg
            b_IGNORE = AgentMap.GetMap("ROUTING")
            optMap.item(0).Value = True
            optMap.item(0).SetFocus
            Exit Sub
         End If
         
      End If
      'READ IN BINDING MAP
      b_IGNORE = AgentMap.GetBindingMsg()
      b_IGNORE = AgentMap.GetMap("BINDING")
      
End Select

'Clear grid, setup and populate.
Call PrepareGrid
b_IGNORE = DisplayMap

'Set DeleteRow Options
Call SetDeleteRow

End Sub

'----------------------------------------------------------
' Sub: RETEXTBOX CHANGE
'
' Action: Handle the change event and update the dirty status.
'----------------------------------------------------------
Private Sub RETextBox_Change()
   Call DirtyStatusUpdate(DIRTY_SCRIPT, DIRTY_ADD)
End Sub

'----------------------------------------------------------
' Sub: TXT AGENT NAME CHANGE
'
' Action: Handle the change event and update the dirty status
' as well as the over UI agent name display not on the tab
' control.
'----------------------------------------------------------
Private Sub txtAgentName_Change()
   
   lblAgentName = txtAgentName
   Call DirtyStatusUpdate(DIRTY_AGENT, DIRTY_ADD)
   
End Sub

'----------------------------------------------------------
' Sub: MAINTABS CLICK
'
' Action: Handle the click event switch between tabs. Update
' the UI, Toolbar and Menu to make sure proper items are
' enabled/disabled.
'
' Parm: Previous Tab (not used).
'----------------------------------------------------------
Private Sub MainTabs_Click(PreviousTab As Integer)

'When selecting tabs, set editing features visibility
Select Case MainTabs.Caption
   Case SCRIPT_CAPTION
      Call ScriptEditingToggle(True)
      Call MapEditingToggle(False)
      
   Case MAP_CAPTION
      Call ScriptEditingToggle(False)
      Call MapEditingToggle(True)
      Call SetDeleteRow
      
   Case AGENT_CAPTION
      Call ScriptEditingToggle(False)
      Call MapEditingToggle(False)
End Select

End Sub

'----------------------------------------------------------
' Sub: MNU AGENT CLICK
'
' Action: Handle the click event for the agents menu array.
'
' Parm: Index is associated with the menu entry.
'----------------------------------------------------------
Private Sub mnuAgent_Click(Index As Integer)

Dim b_OK As Boolean           'Boolean Success
Dim iVal As Integer           'Integer Error
Dim X As Integer


Select Case Index
   
   Case MENU_AGENT_FOLDER_SELECT
   
      Call SaveChangesPrompt
       
      'Pick Folder
      Call PickFolder
      
      If AEClass.Cancelled Then
         'Cancelled, exit quietly
         Exit Sub
      
      Else
         Call InitializeAgentSelect
      End If
   
   Case MENU_AGENT_SELECT
   
      Call SaveChangesPrompt
      Call InitializeAgentSelect
      
   Case MENU_AGENT_SAVE
      
      If (AEClass.EditMode <> MODE_NEW_AGENT) And (AgentMap.Permissions = True) Then
         If Not AgentMap.VerifyEID(AEClass.BindingEID) Then
            MsgBox "Agent was deleted by another application. Select a new agent to edit.", vbExclamation, App.Title
            Exit Sub
         End If
      End If
      
      'Save Changes to agent and script
      If (AEClass.Dirty And (DIRTY_AGENT Or DIRTY_SCRIPT)) Then
         If Not SaveAgent Then
            Exit Sub
         End If
      End If
      
      'Save Changes to map
      If (AEClass.Dirty And DIRTY_MAP) Then
         If txtGridEdit.Visible Then
            AEditorUI.grdData.TextMatrix(AEClass.CurrentRow, AEClass.CurrentCol) = AEditorUI.txtGridEdit.Text
            AEditorUI.txtGridEdit.Visible = False
         End If
         AEditorUI.MousePointer = vbHourglass
         Call SaveRouteMap(grdData)
         AEditorUI.MousePointer = vbNormal
      End If
      
      'Update Dirty Status
      Call DirtyStatusUpdate(DIRTY_NONE, DIRTY_REMOVE)
      
      'The tab is set to script for event permission people, otherwise
      'it is set to be focused on the map tab.
      If AgentMap.Permissions Then
         MainTabs.Tab = TAB_SCRIPT
      Else
         MainTabs.Tab = TAB_MAP
      End If

   Case MENU_AGENT_EXIT
      'Verify exit if changes have been made.
      If AEClass.Dirty Then
         If (MsgBox("Do you want to save changes ? ", vbYesNo + vbQuestion, App.Title) = vbYes) Then
            Call mnuAgent_Click(MENU_AGENT_SAVE)
            AEClass.Dirty = DIRTY_NONE
         End If
      End If
      Call TerminateApp
      
   Case MENU_EXIT_NO_SAVE
      AEClass.Dirty = False
      Call TerminateApp
End Select

End Sub

'-------------------------------------------------------------
' Sub: Initialize Agent Select
'
' Action: Select Agent Handling
'-------------------------------------------------------------
Private Sub InitializeAgentSelect()

Dim X As Integer
Dim b_IGNORE As Boolean
Dim bRoutingOnly As Boolean


'Always default to script tab
MainTabs.Tab = TAB_SCRIPT

If AgentMap.Permissions Then
   b_IGNORE = AgentMap.InitializeFolder()
   If AgentMap.Permissions Then
      AgentPicker.Show vbModal
      If AEClass.Cancelled Then
         Exit Sub
      End If
   Else
      bRoutingOnly = True
   End If
Else
   
   bRoutingOnly = True
End If
      
If bRoutingOnly Then
   'No event permissions
   'This means that we can only edit the Folder Routing Map so load it
   'directly and disable other tabs.
   MainTabs.Tab = TAB_MAP
   AEClass.EditMode = MODE_EDIT_MAP_ONLY
   b_IGNORE = AgentMap.GetRoutingMsg
   b_IGNORE = AgentMap.GetMap("ROUTING")
   Call PrepareGrid
   b_IGNORE = DisplayMap
   With AEditorUI
      .MainTabs.TabEnabled(TAB_SCRIPT) = False
      .MainTabs.TabEnabled(TAB_MAP) = True
      .MainTabs.TabEnabled(TAB_AGENT) = False
      .optMap.item(0).Value = True
      .optMap.item(1).Enabled = False
   End With
   AEditorUI.mnuAgent.item(MENU_AGENT_SELECT).Enabled = False
Else
   AEditorUI.optMap.item(1).Enabled = True
   AEditorUI.optMap.item(0).Enabled = True
   AEditorUI.mnuAgent.item(MENU_AGENT_SELECT).Enabled = True
End If


End Sub

'-------------------------------------------------------------
' Sub: Save Changes Prompt
'
' Action: Prompt for saving of changes and undirty
'-------------------------------------------------------------
Private Sub SaveChangesPrompt()
   If AEClass.Dirty Then
      If (MsgBox("Do you want to save changes ? ", vbYesNo + vbQuestion, App.Title) = vbYes) Then
         Call mnuAgent_Click(MENU_AGENT_SAVE)
         Call DirtyStatusUpdate(DIRTY_NONE, DIRTY_IGNORE)
      Else
         Call DirtyStatusUpdate(DIRTY_NONE, DIRTY_IGNORE)
      End If
   End If
End Sub

'-------------------------------------------------------------
' Sub: grdData_DblClick()
'
' Action: Allow editing of grid via Text Box
'-------------------------------------------------------------
Private Sub grdData_DblClick()
   Call MSFlexGridEdit(grdData, txtGridEdit, -1)
End Sub

'-------------------------------------------------------------
' Sub: grdData_GotFocus()
'
' Action: Copy data from temporary entry box to grid.
'-------------------------------------------------------------
Private Sub grdData_GotFocus()
   If txtGridEdit.Visible = False Or txtGridEdit.Text = "" Then Exit Sub
   grdData = txtGridEdit
   txtGridEdit.Visible = False
End Sub

'-------------------------------------------------------------
' Sub: grdData_KeyPress()
'
' Action: Allow Editing of grid via Text Box
'-------------------------------------------------------------
Private Sub grdData_KeyPress(KeyAscii As Integer)
   
   'Set visibility of row delete feature
   Call SetDeleteRow
   
   AEClass.CurrentCol = grdData.Col
   AEClass.CurrentRow = grdData.Row
   Call MSFlexGridEdit(grdData, txtGridEdit, KeyAscii)
End Sub

'-------------------------------------------------------------
' Sub: GRDDATA LEAVE CELL
'
' Action: If the user leaves the cell then copy any new data
' to the cell.
'-------------------------------------------------------------
Private Sub grdData_LeaveCell()
   If txtGridEdit.Visible = False Then Exit Sub
   grdData.Text = txtGridEdit.Text
   txtGridEdit = ""
   txtGridEdit.Visible = False
End Sub

'-------------------------------------------------------------
' Sub: GRDDATA SCROLL
'
' Action: If the user scrolls enter data if editing is in progress
'-------------------------------------------------------------
Private Sub grdData_Scroll()
   If txtGridEdit.Visible Then
      grdData.TextMatrix(AEClass.CurrentRow, AEClass.CurrentCol) = txtGridEdit.Text
      txtGridEdit.Visible = False
   End If
End Sub

'-------------------------------------------------------------
' Sub: TXT GRID EDIT KEY UP
'
' Action: If the user key is in the txtgridedit then dirty
' the map.
'-------------------------------------------------------------
Private Sub txtGridEdit_KeyUp(KeyCode As Integer, Shift As Integer)
   Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
End Sub

'----------------------------------------------------------
' Sub: TXTGRIDEDIT LOST FOCUS
'
' Action: Write editing data if focus leaves grid
'----------------------------------------------------------
Private Sub txtGridEdit_LostFocus()
   'Trap change if the grid loses focus, but if the user is
   'moving to a different cell it ignore this update since
   'it's already been done.
   If bEditChange Then
      bEditChange = False
   Else
      If txtGridEdit.Visible Then
         grdData.TextMatrix(AEClass.CurrentRow, AEClass.CurrentCol) = txtGridEdit.Text
         txtGridEdit.Visible = False
      End If
   End If
End Sub

'----------------------------------------------------------
' Sub: TXTGRIDEDIT KEY PRESS
'
' Action: Perform special handling for grid editing keystrokes
'
' Note: Currently designed to process the escape, tab and return
' as special handling.
'----------------------------------------------------------
Private Sub txtGridEdit_KeyPress(KeyAscii As Integer)
  
   Dim lRow As Long
   Dim lCol As Long
   
   Select Case KeyAscii
      Case vbKeyEscape
         txtGridEdit.Visible = False
         grdData.SetFocus
        
      Case vbKeyTab, vbKeyReturn
         KeyAscii = 0
         bEditChange = True  'Set to true so the set focus also update
         lCol = grdData.Col + 1  'move to next column
         lRow = grdData.Row      'initialize row info
         
         'If last col move to next row first col
         If lCol > grdData.Cols - 1 Then
            lCol = 0
            lRow = lRow + 1
            If lRow > grdData.Rows - 1 Then
               grdData.Rows = lRow + 1
            End If
         End If
                  
         'Update grid
         grdData.Col = lCol
         grdData.Row = lRow
         
         Call MSFlexGridEdit(grdData, txtGridEdit, -1)
   End Select
End Sub

'----------------------------------------------------------
' Sub: MSFLEXGRIDEDIT
'
' Action: Initialize Textbox Control, Locate Edit box
'         pass focus to edit box
'----------------------------------------------------------
Private Sub MSFlexGridEdit(grdEdit As MSFlexGrid, Edt As TextBox, KeyAscii As Integer)
   
   With Edt
      'Use the character that was typed
      Select Case KeyAscii
         Case -1
            .Text = grdEdit.Text
            .SelStart = Len(.Text) + 1
            AEClass.CurrentRow = grdEdit.Row
            AEClass.CurrentCol = grdEdit.Col
         Case 0 To 31
            KeyAscii = 0
            'Bypass these keys
         Case Else
            .Text = Chr(KeyAscii)
            .SelStart = 1
      End Select
      
      'Move the editing box to the proper location. Make sure it's
      'on top and has the focus.
      .Move grdEdit.CellLeft + grdData.Left, grdEdit.CellTop + grdData.Top, grdEdit.CellWidth, grdEdit.CellHeight
      .Visible = True
      .SetFocus
      .ZOrder
   End With
   
   If grdData.Row = grdData.Rows - 1 Then
      grdData.Rows = grdData.Rows + 1
   End If
End Sub

'----------------------------------------------------------
' Sub: FORM_QUERYUNLOAD
'
' Action: Trap termination so forms and objects release can
'         be controlled.
'----------------------------------------------------------
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    
    Dim b_OK As Boolean
    
    If AEClass Is Nothing Then
       Call TerminateApp
    Else
      If AEClass.Dirty = DIRTY_NONE Then
         Call TerminateApp
      Else
         If (MsgBox("Do you want to save changes ? ", vbYesNo + vbQuestion, App.Title) = vbYes) Then
              Call mnuAgent_Click(MENU_AGENT_SAVE)
              AEClass.Dirty = DIRTY_NONE
              Call TerminateApp
         Else
              AEClass.Dirty = DIRTY_NONE
              Call TerminateApp
         End If
      End If
    End If
    
End Sub

