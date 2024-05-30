VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form fExplorer 
   BackColor       =   &H80000005&
   ClientHeight    =   3555
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   5085
   Icon            =   "fExplorer.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3555
   ScaleWidth      =   5085
   StartUpPosition =   3  'Windows Default
   Begin ComctlLib.StatusBar sbStatus 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   3300
      Width           =   5085
      _ExtentX        =   8969
      _ExtentY        =   450
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            TextSave        =   ""
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ListView lvContainer 
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   600
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   2566
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
   Begin VB.PictureBox cbToolbar 
      Align           =   1  'Align Top
      Height          =   450
      Left            =   0
      ScaleHeight     =   390
      ScaleWidth      =   5025
      TabIndex        =   2
      Top             =   0
      Width           =   5085
      Begin ComctlLib.Toolbar tbToolbar 
         Height          =   390
         Left            =   3195
         TabIndex        =   3
         Top             =   30
         Width           =   1800
         _ExtentX        =   3175
         _ExtentY        =   688
         ButtonWidth     =   635
         ButtonHeight    =   582
         ImageList       =   "ilSmall"
         _Version        =   327682
         BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
            NumButtons      =   1
            BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
               Key             =   ""
               Object.ToolTipText     =   "Up one level"
               Object.Tag             =   ""
               ImageIndex      =   1
            EndProperty
         EndProperty
      End
      Begin VB.PictureBox pbAddress 
         BorderStyle     =   0  'None
         Height          =   375
         Left            =   165
         ScaleHeight     =   375
         ScaleWidth      =   2805
         TabIndex        =   4
         Top             =   30
         Width           =   2805
         Begin VB.ComboBox cbAddress 
            Height          =   315
            Left            =   0
            TabIndex        =   5
            Top             =   45
            Width           =   2055
         End
      End
   End
   Begin ComctlLib.ImageList ilSmall 
      Left            =   4440
      Top             =   1800
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
            Picture         =   "fExplorer.frx":0442
            Key             =   "Container"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":0554
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":0666
            Key             =   "Admin"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":0778
            Key             =   "Node"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":088A
            Key             =   "Service"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":099C
            Key             =   "User"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":0AAE
            Key             =   "Group"
         EndProperty
      EndProperty
   End
   Begin ComctlLib.ImageList ilLarge 
      Left            =   4440
      Top             =   1080
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
            Picture         =   "fExplorer.frx":0BC0
            Key             =   "Container"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":0EDA
            Key             =   "Computer"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":11F4
            Key             =   "Service"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":150E
            Key             =   "Admin"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":1828
            Key             =   "User"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":1ABA
            Key             =   "Node"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "fExplorer.frx":1DD4
            Key             =   "Group"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileNew 
         Caption         =   "&New"
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "0"
            Index           =   0
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "1"
            Index           =   1
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "2"
            Index           =   2
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "3"
            Index           =   3
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "4"
            Index           =   4
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "5"
            Index           =   5
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "6"
            Index           =   6
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "7"
            Index           =   7
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "8"
            Index           =   8
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "9"
            Index           =   9
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "10"
            Index           =   10
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "11"
            Index           =   11
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "12"
            Index           =   12
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "13"
            Index           =   13
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "14"
            Index           =   14
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "15"
            Index           =   15
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "16"
            Index           =   16
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "17"
            Index           =   17
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "18"
            Index           =   18
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "19"
            Index           =   19
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "20"
            Index           =   20
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "21"
            Index           =   21
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "22"
            Index           =   22
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "23"
            Index           =   23
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "24"
            Index           =   24
         End
         Begin VB.Menu mnuNewDynamic 
            Caption         =   "-"
            Index           =   99
         End
         Begin VB.Menu mnuNewOther 
            Caption         =   "&Object..."
         End
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuFileDiv1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileCreateShortcut 
         Caption         =   "Create &Shortcut"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuFileDelete 
         Caption         =   "&Delete"
         Enabled         =   0   'False
         Shortcut        =   {DEL}
      End
      Begin VB.Menu mnuFileRename 
         Caption         =   "Rena&me"
         Enabled         =   0   'False
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuFileProperties 
         Caption         =   "P&roperties"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuFileDiv9 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "&Close"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEditUndo 
         Caption         =   "&Undo"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuEditDiv0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "Cu&t"
         Enabled         =   0   'False
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "&Copy"
         Enabled         =   0   'False
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "&Paste"
         Enabled         =   0   'False
         Shortcut        =   ^V
      End
      Begin VB.Menu mnuEditPasteShortcut 
         Caption         =   "Paste &Shortcut"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuEditDiv2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSearch 
         Caption         =   "&Find"
         Enabled         =   0   'False
         Shortcut        =   {F3}
      End
      Begin VB.Menu mnuEditDiv3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditSelectAll 
         Caption         =   "Select &All"
         Enabled         =   0   'False
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuEditInvertSelection 
         Caption         =   "&Invert Selection"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuViewLargeIcons 
         Caption         =   "Lar&ge Icons"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewSmallIcons 
         Caption         =   "S&mall Icons"
      End
      Begin VB.Menu mnuViewList 
         Caption         =   "&List"
      End
      Begin VB.Menu mnuViewDetails 
         Caption         =   "&Details"
      End
      Begin VB.Menu mnuViewDiv0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuArrangeAutoArrange 
         Caption         =   "&Auto Arrange"
         Checked         =   -1  'True
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuViewDiv1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "&Toolbar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewSingleWindow 
         Caption         =   "Single Window Mode"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuAbout 
         Caption         =   "&About..."
      End
   End
   Begin VB.Menu mnuPopUp 
      Caption         =   "Popup"
      Visible         =   0   'False
      Begin VB.Menu mnuPopUpOpen 
         Caption         =   "&Open"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuPopUpDiv0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPopupCut 
         Caption         =   "Cu&t"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuPopupCopy 
         Caption         =   "&Copy"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuPopupDiv1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPopUpCreateShortcut 
         Caption         =   "Create &Shortcut"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuPopUpDelete 
         Caption         =   "&Delete"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuPopUpRename 
         Caption         =   "Rena&me"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuPopUpDiv2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPopUpNew 
         Caption         =   "&New"
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "0"
            Index           =   0
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "1"
            Index           =   1
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "2"
            Index           =   2
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "3"
            Index           =   3
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "4"
            Index           =   4
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "5"
            Index           =   5
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "6"
            Index           =   6
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "7"
            Index           =   7
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "8"
            Index           =   8
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "9"
            Index           =   9
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "10"
            Index           =   10
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "11"
            Index           =   11
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "12"
            Index           =   12
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "13"
            Index           =   13
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "14"
            Index           =   14
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "15"
            Index           =   15
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "16"
            Index           =   16
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "17"
            Index           =   17
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "18"
            Index           =   18
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "19"
            Index           =   19
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "20"
            Index           =   20
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "21"
            Index           =   21
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "22"
            Index           =   22
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "23"
            Index           =   23
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "24"
            Index           =   24
         End
         Begin VB.Menu mnuPopupNewDynamic 
            Caption         =   "-"
            Index           =   99
         End
         Begin VB.Menu mnuPopUpNewOther 
            Caption         =   "&Object..."
         End
      End
      Begin VB.Menu mnuPopUpDiv3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuPopupProperties 
         Caption         =   "P&roperties"
         Enabled         =   0   'False
      End
   End
End
Attribute VB_Name = "fExplorer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit




Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function ShowWindow Lib "user32" (ByVal hWnd As Long, ByVal nCmdShow As Long) As Long
Private Declare Function CreateThread_ByValParam Lib "kernel32" _
    Alias "CreateThread" (ByVal lpThreadAttributes As Long, ByVal dwStackSize As Long, lpStartAddress As Any, lpparameter As String, dwcreationflags As Long, ByRef lpthreadid As Long) As Long
Private Const SW_SHOW = 5
Private Declare Function CloseWindow Lib "user32" (ByVal hWnd As Long) As Long


Private Sub m_EnableMenus()
    '
    ' Enable the file menu:
    '
    mnuFileOpen.Enabled = True
    mnuFileProperties.Enabled = True
    mnuFileDelete.Enabled = True
    
    '
    ' Enable the pop-up menu:
    '
    mnuPopUpOpen.Enabled = True
    mnuPopupProperties.Enabled = True
    mnuPopUpDelete.Enabled = True
End Sub

Private Sub m_DisableMenus()
    '
    ' Enable the file menu:
    '
    mnuFileOpen.Enabled = False
    mnuFileProperties.Enabled = False
    mnuFileDelete.Enabled = False
    
    '
    ' Enable the pop-up menu:
    '
    mnuPopUpOpen.Enabled = False
    mnuPopupProperties.Enabled = False
    mnuPopUpDelete.Enabled = False
End Sub


Public Sub SetADsPath(ByVal sADsPath As String)
Dim sComputer
Dim fAskThem As fConnect

    Me.Caption = sADsPath
    
    '
    ' Are they choosing a provider?
    '
    If Right(sADsPath, 1) = ":" Then
        '
        ' Ask them for the name of the computer to talk to:
        '
        Set fAskThem = New fConnect
        fConnect.Show 1
        sComputer = fConnect.tServerName.Text
        Unload fConnect
        
        If sComputer = "" Then
            '
            ' They hit cancel, so ignore the request:
            '
            On Error Resume Next
            Err.Raise 76
            Exit Sub
        Else
            '
            ' Append the computer to the path:
            '
            sADsPath = sADsPath & "//" & sComputer
        End If
    End If
    
    '
    ' Fill the container with the items it should contain:
    '
    Me.MousePointer = vbHourglass
    FillContainer sADsPath, Me
    Me.MousePointer = vbArrow
End Sub





Private Sub bParent_Click()

End Sub

Private Sub cbToolbar_HeightChanged(ByVal NewHeight As Single)
    '
    ' Make the container fit inside the box:
    '
    On Error Resume Next
    If cbToolbar.Visible = True Then
        lvContainer.Top = NewHeight
        lvContainer.Height = ScaleHeight - sbStatus.Height - NewHeight
    Else
        lvContainer.Top = 0
        lvContainer.Height = ScaleHeight - sbStatus.Height
    End If
    On Error GoTo 0
End Sub

Private Sub Form_Resize()
    '
    ' Make the container fit inside the box:
    '
    On Error Resume Next
    lvContainer.Left = 0
    lvContainer.Width = ScaleWidth
    If cbToolbar.Visible = True Then
        cbToolbar.Width = ScaleWidth
        lvContainer.Top = cbToolbar.Height
        lvContainer.Height = ScaleHeight - sbStatus.Height - cbToolbar.Height
    Else
        lvContainer.Top = 0
        lvContainer.Height = ScaleHeight - sbStatus.Height
    End If
    On Error GoTo 0
        
   lvSetExtendedStyle lvContainer, lvGetExtendedStyle(lvContainer) Or lvs_ExTrackSelect Or Lvs_ExFullRowSelect Or lvs_ExGridLines Or lvs_ExHeaderDragDrop
End Sub


Private Sub lvContainer_Click()
On Error Resume Next
    If lvContainer.SelectedItem.Selected = False Then
        m_DisableMenus
    Else
        m_EnableMenus
    End If
End Sub

Private Sub lvContainer_ColumnClick(ByVal ColumnHeader As ComctlLib.ColumnHeader)
    If lvContainer.SortKey = ColumnHeader.Index - 1 Then
        If lvContainer.SortOrder = lvwDescending Then
            lvContainer.SortOrder = lvwAscending
        Else
            lvContainer.SortOrder = lvwDescending
        End If
    Else
        lvContainer.SortKey = ColumnHeader.Index - 1
    End If
End Sub


Private Sub lvContainer_DblClick()
    '
    ' This is the same as clicking File->Open
    '
    mnuFileOpen_Click
End Sub



Private Sub lvContainer_KeyPress(KeyAscii As Integer)
Dim oMyADsObject

    Select Case KeyAscii
    Case 8      ' Backspace:
        '
        ' Get this object:
        '
        Set oMyADsObject = ADSGetObject(Me.Caption)
        
        '
        ' Open my parent:
        '
        m_FileOpen oMyADsObject.Parent, True
    Case 13     ' Enter:
        '
        ' Enter = File open
        '
        mnuFileOpen_Click
    End Select
End Sub

Private Sub lvContainer_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
On Error Resume Next
    If Button = 2 Then
        '
        ' Display the popup-menu
        '
        If lvContainer.SelectedItem.Selected = False Then
            m_DisableMenus
        Else
            m_EnableMenus
        End If
        PopupMenu mnuPopUp, , , , mnuPopUpOpen
    End If
End Sub


Private Sub mnuAbout_Click()
    fAbout.Show
End Sub

Private Sub mnuEditSearch_Click()
Dim fSrch As New fSearch

    fSrch.tADsPath.Text = Me.Caption
    fSrch.tADsPath.Tag = Me.Caption
    fSrch.Show
End Sub

Private Sub mnuFileClose_Click()
    '
    ' Unload myself:
    '
    Unload Me
End Sub


Private Sub mnuFileDelete_Click()
Dim sDeleteQuery As String
Dim iDeleteObject As Integer
Dim sADsPath As String
Dim bContainer As Boolean

    sADsPath = Mid(lvContainer.SelectedItem.Tag, 2)
    bContainer = CInt(Left(lvContainer.SelectedItem.Tag, 1))
    
    '
    ' Form the query message (add the correct message for containers):
    '
    sDeleteQuery = "Are you sure you want to delete: " & vbCrLf & _
                   """" & sADsPath & """"
    If bContainer = True Then
        sDeleteQuery = sDeleteQuery & vbCrLf & vbCrLf & _
                       "Warning: All the object's children will also be deleted."
    End If
    
    iDeleteObject = MsgBox(sDeleteQuery, vbQuestion + vbYesNo, "Delete Object")
    If iDeleteObject = vbYes Then
        '
        ' Delete this child:
        '
        If ADSDeleteObject(Mid(lvContainer.SelectedItem.Tag, 2), CInt(Left(lvContainer.SelectedItem.Tag, 1))) = True Then
            lvContainer.ListItems.Remove (lvContainer.SelectedItem.Index)
        End If
    End If
End Sub

Private Sub mnuFileOpen_Click()
    '
    ' Open this browser:
    '
    m_FileOpen Mid(lvContainer.SelectedItem.Tag, 2), CInt(Left(lvContainer.SelectedItem.Tag, 1))
End Sub

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
    DoEvents
    
    If bContainer = True Then
        If mnuViewSingleWindow.Checked = True Then
            '
            ' Use the existing explorer:
            '
            Set oNewExplorer = Me
            lvContainer.ListItems.Clear
        Else
            '
            ' Create a new explorer:
            '
            Set oNewExplorer = New fExplorer
            Load oNewExplorer
            
            '
            ' Inherit the toolbar settings in the new window:
            '
            oNewExplorer.mnuViewToolbar.Checked = mnuViewToolbar.Checked
            oNewExplorer.cbToolbar.Visible = mnuViewToolbar.Checked
            
            If ((oNewExplorer.Width + Me.Left + 360) < Screen.Width) And _
               ((oNewExplorer.Height + Me.Top + 360) < Screen.Height) Then
                oNewExplorer.Top = Me.Top + 360
                oNewExplorer.Left = Me.Left + 360
            End If
        End If
        
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
    DoEvents
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


Private Sub mnuNewDynamic_Click(Index As Integer)
    MsgBox mnuNewDynamic(Index).Caption
End Sub

Private Sub mnuPopUpDelete_Click()
    mnuFileDelete_Click
End Sub

Private Sub mnuPopupNewDynamic_Click(Index As Integer)
    mnuNewDynamic_Click Index
End Sub

Private Sub mnuPopUpOpen_Click()
    mnuFileOpen_Click
End Sub

Private Sub mnuPopupProperties_Click()
    mnuFileProperties_Click
End Sub


Private Sub mnuViewDetails_Click()
    '
    ' Toggle the check marks in the menu:
    '
    mnuViewLargeIcons.Checked = False
    mnuViewSmallIcons.Checked = False
    mnuViewList.Checked = False
    mnuViewDetails.Checked = True
    
    '
    ' Toggle the list mode:
    '
    lvContainer.View = lvwReport
End Sub

Private Sub mnuViewLargeIcons_Click()
    '
    ' Toggle the check marks in the menu:
    '
    mnuViewLargeIcons.Checked = True
    mnuViewSmallIcons.Checked = False
    mnuViewList.Checked = False
    mnuViewDetails.Checked = False
    
    '
    ' Toggle the list mode:
    '
    lvContainer.View = lvwIcon
End Sub


Private Sub mnuViewList_Click()
    '
    ' Toggle the check marks in the menu:
    '
    mnuViewLargeIcons.Checked = False
    mnuViewSmallIcons.Checked = False
    mnuViewList.Checked = True
    mnuViewDetails.Checked = False
    
    '
    ' Toggle the list mode:
    '
    lvContainer.View = lvwList
End Sub


Private Sub mnuViewSingleWindow_Click()
    '
    ' Toggle the check mark:
    '
    mnuViewSingleWindow.Checked = Not mnuViewSingleWindow.Checked
End Sub

Private Sub mnuViewSmallIcons_Click()
    '
    ' Toggle the check marks in the menu:
    '
    mnuViewLargeIcons.Checked = False
    mnuViewSmallIcons.Checked = True
    mnuViewList.Checked = False
    mnuViewDetails.Checked = False
    
    '
    ' Toggle the list mode:
    '
    lvContainer.View = lvwSmallIcon
End Sub


Private Sub mnuViewToolbar_Click()
    mnuViewToolbar.Checked = Not mnuViewToolbar.Checked
    cbToolbar.Visible = mnuViewToolbar.Checked
    Form_Resize
End Sub


Private Sub pbAddress_Resize()
On Error Resume Next
    cbAddress.Width = pbAddress.ScaleWidth
End Sub


Private Sub tbToolbar_ButtonClick(ByVal Button As ComctlLib.Button)
    Select Case Button.Index
        Case 1
            '
            ' Signal a backspace click:
            '
            lvContainer_KeyPress (8)
    End Select
End Sub


