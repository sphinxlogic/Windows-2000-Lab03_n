VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "tabctl32.ocx"
Begin VB.Form fSearch 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Find: Matching Entries"
   ClientHeight    =   4920
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6465
   Icon            =   "fSearch.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4920
   ScaleWidth      =   6465
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton bNewSearch 
      Caption         =   "Ne&w Search"
      Height          =   350
      Left            =   5160
      TabIndex        =   9
      Top             =   1320
      Width           =   1095
   End
   Begin VB.CommandButton bStop 
      Caption         =   "Sto&p"
      Enabled         =   0   'False
      Height          =   350
      Left            =   5160
      TabIndex        =   8
      Top             =   840
      Width           =   1095
   End
   Begin TabDlg.SSTab tsSearch 
      Height          =   2295
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   4935
      _ExtentX        =   8705
      _ExtentY        =   4048
      _Version        =   327681
      Style           =   1
      Tabs            =   2
      TabHeight       =   520
      TabCaption(0)   =   "Name && Location"
      TabPicture(0)   =   "fSearch.frx":08CA
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Label2"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "Label1"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "lSlowWarning"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "tADsPath"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "tNamed"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "ckRecursive"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).ControlCount=   6
      TabCaption(1)   =   "Advanced"
      TabPicture(1)   =   "fSearch.frx":08E6
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "tFilter"
      Tab(1).Control(1)=   "Label3"
      Tab(1).ControlCount=   2
      Begin VB.TextBox tFilter 
         Height          =   300
         Left            =   -74040
         TabIndex        =   11
         Text            =   "objectClass=*"
         Top             =   600
         Width           =   3735
      End
      Begin VB.CheckBox ckRecursive 
         Caption         =   "Include &subcontainers"
         Height          =   255
         Left            =   960
         TabIndex        =   7
         Top             =   1440
         Width           =   2175
      End
      Begin VB.TextBox tNamed 
         Height          =   300
         Left            =   960
         TabIndex        =   4
         Text            =   "*"
         Top             =   600
         Width           =   3735
      End
      Begin VB.TextBox tADsPath 
         Height          =   300
         Left            =   960
         TabIndex        =   3
         Top             =   1080
         Width           =   3735
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "&Filter:"
         Height          =   195
         Left            =   -74760
         TabIndex        =   12
         Top             =   645
         Width           =   375
      End
      Begin VB.Label lSlowWarning 
         AutoSize        =   -1  'True
         Caption         =   "Subcontainer searches can take a long time."
         Height          =   195
         Left            =   1560
         TabIndex        =   10
         Top             =   1730
         Visible         =   0   'False
         Width           =   3165
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "&Named:"
         Height          =   195
         Left            =   240
         TabIndex        =   6
         Top             =   650
         Width           =   555
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "&Look in:"
         Height          =   195
         Left            =   240
         TabIndex        =   5
         Top             =   1130
         Width           =   570
      End
   End
   Begin VB.CommandButton bFindNow 
      Caption         =   "F&ind Now"
      Default         =   -1  'True
      Height          =   350
      Left            =   5160
      TabIndex        =   1
      Top             =   360
      Width           =   1095
   End
   Begin ComctlLib.ListView lvContainer 
      Height          =   2295
      Left            =   120
      TabIndex        =   0
      Top             =   2520
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   4048
      View            =   3
      Arrange         =   2
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      OLEDropMode     =   1
      _Version        =   327682
      Icons           =   "ilLarge"
      SmallIcons      =   "ilSmall"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      OLEDropMode     =   1
      NumItems        =   2
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Name"
         Object.Width           =   5292
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Type"
         Object.Width           =   2540
      EndProperty
   End
   Begin ComctlLib.ImageList ilSmall 
      Left            =   7080
      Top             =   840
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   128
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   7
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0902
            Key             =   "Container"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0A14
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0B26
            Key             =   "Admin"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0C38
            Key             =   "Node"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0D4A
            Key             =   "Service"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0E5C
            Key             =   "User"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":0F6E
            Key             =   "Group"
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList ilLarge 
      Left            =   7080
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   7
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":1080
            Key             =   "Container"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":139A
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":16B4
            Key             =   "Service"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":19CE
            Key             =   "Admin"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":1CE8
            Key             =   "User"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":1F7A
            Key             =   "Node"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fSearch.frx":2294
            Key             =   "Group"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "fSearch"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Private Const SW_SHOW = 5
Private Declare Function CloseWindow Lib "user32" (ByVal hwnd As Long) As Long



Private Sub m_FileOpen(ByVal sADsPath As String, ByVal bContainer As Boolean)
Dim oNewExplorer As fExplorer
Dim hwndParent As Long

    '
    ' Attempt to locating an existing window of this name:
    '
    hwndParent = FindWindow(vbNullString, sADsPath)
    If hwndParent <> 0 Then
        hwndParent = ShowWindow(hwndParent, SW_SHOW)
        Exit Sub
    End If
    
    '
    ' Put the cursor in "WAIT" mode:
    '
    Me.MousePointer = vbHourglass
        
    If bContainer = True Then
        '
        ' Create a new explorer:
        '
        Set oNewExplorer = New fExplorer
        Load oNewExplorer
        
        '
        ' Point it to our child:
        '
        On Error Resume Next
        oNewExplorer.SetADsPath sADsPath
        If Err.Number <> 0 Then
            '
            ' Unload it:
            '
            Unload oNewExplorer
        Else
            '
            ' Display it:
            '
            oNewExplorer.Show
        End If
    Else
        mnuFileProperties_Click
    End If
    
    '
    ' Return the cursor to "NORMAL" mode:
    '
    Me.MousePointer = vbArrow
End Sub



Private Sub mnuFileProperties_Click()
Dim oNewProperties As fProperties
Dim sADsPath As String

    sADsPath = Mid(lvContainer.SelectedItem.Tag, 2)
    
    '
    ' Put the cursor in "WAIT" mode:
    '
    Me.MousePointer = vbHourglass
        
    '
    ' Create a new properties:
    '
    Set oNewProperties = New fProperties
    Load oNewProperties
    
    '
    ' Point it to our child:
    '
    On Error Resume Next
    oNewProperties.SetADsPath sADsPath, ilLarge.ListImages(lvContainer.SelectedItem.Icon)
    If Err.Number <> 0 Then
        '
        ' Unload it:
        '
        Unload oNewProperties
    Else
        '
        ' Display it:
        '
        oNewProperties.Show
    End If
    
    '
    ' Return the cursor to "NORMAL" mode:
    '
    Me.MousePointer = vbArrow
End Sub




Private Sub bFindNow_Click()
Dim sFilter
Dim sADsPath
Dim sNamed

    '
    ' Put the cursor in "WAIT" mode:
    '
    Me.MousePointer = vbHourglass
    
    sADsPath = tADsPath.Text
    sNamed = tNamed.Text
    
    If tsSearch.Tab = 0 Then
        '
        ' Build a "naming" filter:
        '
        sFilter = "(|" & _
                  "(o=" & sNamed & ")" & _
                  "(ou=" & sNamed & ")" & _
                  "(cn=" & sNamed & ")" & _
                  ")"
    Else
        '
        ' Use "advanced" filter:
        '
        sFilter = tFilter.Text
    End If
    '
    ' Handle recursive:
    '
    'If ckRecursive.Value = vbChecked Then
    '    sFilter = "%" & sFilter
    'End If
    
    bFindNow.Enabled = False
    bNewSearch.Enabled = False
    DoEvents
    
    FillSearchContainer sADsPath, sFilter, Me
    
    DoEvents
    bFindNow.Enabled = True
    bNewSearch.Enabled = True

    '
    ' Put the cursor in "WAIT" mode:
    '
    Me.MousePointer = vbNormal
End Sub

Private Sub bNewSearch_Click()
    tNamed.Text = "*"
    tADsPath.Text = tADsPath.Tag
    tFilter.Text = "objectClass=*"
    lvContainer.ListItems.Clear
End Sub


Private Sub ckRecursive_Click()
    lSlowWarning.Visible = ckRecursive.Value
End Sub


Private Sub lvContainer_DblClick()
    '
    ' Open this browser:
    '
    m_FileOpen Mid(lvContainer.SelectedItem.Tag, 2), CInt(Left(lvContainer.SelectedItem.Tag, 1))
End Sub


