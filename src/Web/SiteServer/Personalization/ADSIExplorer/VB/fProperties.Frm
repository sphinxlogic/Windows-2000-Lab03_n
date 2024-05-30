VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "tabctl32.ocx"
Begin VB.Form fProperties 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Properties"
   ClientHeight    =   5670
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5910
   Icon            =   "fProperties.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5670
   ScaleWidth      =   5910
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton bOk 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   350
      Left            =   3480
      TabIndex        =   6
      Top             =   5280
      Width           =   1095
   End
   Begin VB.CommandButton bCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   350
      Left            =   4680
      TabIndex        =   5
      Top             =   5280
      Width           =   1095
   End
   Begin TabDlg.SSTab tsTabs 
      Height          =   4455
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   5655
      _ExtentX        =   9975
      _ExtentY        =   7858
      _Version        =   327681
      Style           =   1
      Tabs            =   2
      TabHeight       =   520
      TabCaption(0)   =   "Properties"
      TabPicture(0)   =   "fProperties.frx":08CA
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "lvProperties"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Children"
      TabPicture(1)   =   "fProperties.frx":08E6
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "lvContainer"
      Tab(1).ControlCount=   1
      Begin ComctlLib.ListView lvProperties 
         Height          =   3855
         Left            =   120
         TabIndex        =   3
         Top             =   480
         Width           =   5415
         _ExtentX        =   9551
         _ExtentY        =   6800
         View            =   3
         LabelEdit       =   1
         Sorted          =   -1  'True
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         _Version        =   327682
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   2
         BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Text            =   "Property"
            Object.Width           =   2540
         EndProperty
         BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
            SubItemIndex    =   1
            Key             =   ""
            Object.Tag             =   ""
            Text            =   "Value"
            Object.Width           =   5080
         EndProperty
      End
      Begin ComctlLib.ListView lvContainer 
         Height          =   3855
         Left            =   -74880
         TabIndex        =   4
         Top             =   480
         Width           =   5415
         _ExtentX        =   9551
         _ExtentY        =   6800
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
   End
   Begin ComctlLib.ImageList ilLarge 
      Left            =   6600
      Top             =   1200
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
            Picture         =   "fProperties.frx":0902
            Key             =   "Container"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":0C1C
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":0F36
            Key             =   "Service"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":1250
            Key             =   "Admin"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":156A
            Key             =   "User"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":17FC
            Key             =   "Node"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":1B16
            Key             =   "Group"
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList ilSmall 
      Left            =   6600
      Top             =   1920
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
            Picture         =   "fProperties.frx":1DA8
            Key             =   "Container"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":1EBA
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":1FCC
            Key             =   "Admin"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":20DE
            Key             =   "Node"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":21F0
            Key             =   "Service"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":2302
            Key             =   "User"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fProperties.frx":2414
            Key             =   "Group"
         EndProperty
      EndProperty
   End
   Begin VB.Label lClass 
      AutoSize        =   -1  'True
      Caption         =   "class"
      Height          =   195
      Left            =   840
      TabIndex        =   1
      Top             =   360
      Width           =   360
   End
   Begin VB.Label lName 
      AutoSize        =   -1  'True
      Caption         =   "object name"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   840
      TabIndex        =   0
      Top             =   120
      Width           =   1050
   End
   Begin VB.Image Image1 
      Height          =   480
      Left            =   120
      Picture         =   "fProperties.frx":2526
      Top             =   120
      Width           =   480
   End
End
Attribute VB_Name = "fProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function ShowWindow Lib "user32" (ByVal hWnd As Long, ByVal nCmdShow As Long) As Long
Private Const SW_SHOW = 5
Private Declare Function CloseWindow Lib "user32" (ByVal hWnd As Long) As Long
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



Public Sub SetADsPath(ByVal sADsPath As String, ByVal pIconImage)
    '
    ' Set our title:
    '
    Me.Caption = sADsPath
    
    '
    ' Fill the container with the items it should contain:
    '
    Me.MousePointer = vbHourglass
    FillProperties sADsPath, Me
    Me.MousePointer = vbArrow
End Sub


Private Sub bCancel_Click()
    '
    ' Unload ourselves:
    '
    Unload Me
End Sub










Private Sub bOk_Click()
    '
    ' Unload the form:
    '
    Unload Me
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





Private Sub Form_Load()
    '
    ' Configure our list view to show gridlines:
    '
    lvSetExtendedStyle lvProperties, lvGetExtendedStyle(lvProperties) Or lvs_ExGridLines
End Sub

Private Sub lvContainer_Click()
    '
    ' Open this browser:
    '
    m_FileOpen Mid(lvContainer.SelectedItem.Tag, 2), CInt(Left(lvContainer.SelectedItem.Tag, 1))
End Sub


Private Sub lvProperties_ColumnClick(ByVal ColumnHeader As ComctlLib.ColumnHeader)
    If lvProperties.SortKey = ColumnHeader.Index - 1 Then
        If lvProperties.SortOrder = lvwDescending Then
            lvProperties.SortOrder = lvwAscending
        Else
            lvProperties.SortOrder = lvwDescending
        End If
    Else
        lvProperties.SortKey = ColumnHeader.Index - 1
    End If
End Sub


