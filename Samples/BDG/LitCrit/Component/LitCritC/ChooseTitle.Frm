VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmChooseTitle 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Choose Title"
   ClientHeight    =   2490
   ClientLeft      =   45
   ClientTop       =   2625
   ClientWidth     =   7635
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2490
   ScaleWidth      =   7635
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   3240
      TabIndex        =   9
      Top             =   2040
      Width           =   1935
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   120
      Top             =   1920
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "ChooseTitle.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "ChooseTitle.frx":0454
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "ChooseTitle.frx":08A8
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton cmdFind 
      Caption         =   "&Find "
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   1200
      TabIndex        =   8
      Top             =   2040
      Width           =   1815
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5400
      TabIndex        =   10
      Top             =   2040
      Width           =   1695
   End
   Begin MSComctlLib.ListView lvwSearch 
      Height          =   3135
      Left            =   120
      TabIndex        =   14
      Top             =   2640
      Visible         =   0   'False
      Width           =   7455
      _ExtentX        =   13150
      _ExtentY        =   5530
      View            =   3
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   0   'False
      HideSelection   =   0   'False
      AllowReorder    =   -1  'True
      FullRowSelect   =   -1  'True
      GridLines       =   -1  'True
      HotTracking     =   -1  'True
      HoverSelection  =   -1  'True
      _Version        =   393217
      Icons           =   "ImageList1"
      SmallIcons      =   "ImageList1"
      ColHdrIcons     =   "ImageList1"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Title"
         Object.Width           =   5080
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Authors"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Media Type"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "Published"
         Object.Width           =   1552
      EndProperty
   End
   Begin VB.Frame Frame1 
      Caption         =   "Item Information"
      Height          =   1695
      Left            =   0
      TabIndex        =   0
      Top             =   120
      Width           =   7575
      Begin VB.OptionButton optMedia 
         Caption         =   "All"
         Height          =   255
         Index           =   0
         Left            =   1320
         TabIndex        =   1
         ToolTipText     =   "Search all media types"
         Top             =   240
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton optMedia 
         Caption         =   "Periodical"
         Height          =   255
         Index           =   3
         Left            =   4560
         TabIndex        =   4
         Tag             =   "Prd"
         ToolTipText     =   "Search periodicals only"
         Top             =   240
         Width           =   1095
      End
      Begin VB.TextBox txtAuthors 
         Height          =   375
         Left            =   1080
         TabIndex        =   7
         Top             =   1080
         Width           =   6375
      End
      Begin VB.OptionButton optMedia 
         Caption         =   "Software"
         Height          =   255
         Index           =   4
         Left            =   5760
         TabIndex        =   5
         Tag             =   "Soft"
         ToolTipText     =   "Search software and electronic media only"
         Top             =   240
         Width           =   1095
      End
      Begin VB.OptionButton optMedia 
         Caption         =   "Book"
         Height          =   255
         Index           =   1
         Left            =   2160
         TabIndex        =   2
         Tag             =   "Book"
         ToolTipText     =   "Search books only"
         Top             =   240
         Width           =   735
      End
      Begin VB.OptionButton optMedia 
         Caption         =   "Audio/Visual"
         Height          =   255
         Index           =   2
         Left            =   3120
         TabIndex        =   3
         Tag             =   "AV"
         ToolTipText     =   "Search video and audio cassettes only"
         Top             =   240
         Width           =   1215
      End
      Begin VB.TextBox txtTitle 
         Height          =   375
         Left            =   1080
         TabIndex        =   6
         Top             =   600
         Width           =   6375
      End
      Begin VB.Label lblAuthors 
         Caption         =   "Authors:"
         Height          =   375
         Index           =   0
         Left            =   240
         TabIndex        =   13
         Top             =   1080
         Width           =   855
      End
      Begin VB.Label lblTitle 
         Caption         =   "Title:"
         Height          =   255
         Left            =   240
         TabIndex        =   12
         Top             =   600
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Media type:"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   240
         Width           =   1095
      End
   End
   Begin VB.Line Line1 
      X1              =   0
      X2              =   7680
      Y1              =   2520
      Y2              =   2520
   End
End
Attribute VB_Name = "frmChooseTitle"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public MediaType As String
Public Title As String
Public Authors As String
Public ObjectID As String
Public BibNo As Long

Public Server As String
Public Logon As String

Private Const Margin = 250
Private SelectedMedia As Integer

Private Sub Form_Load()
    
   lvwSearch.SmallIcons = ImageList1
   lvwSearch.MultiSelect = False
End Sub

Private Sub Form_Activate()
   ' Select radio button by setting focus...
   Select Case MediaType
   Case "Book": optMedia(1).SetFocus
   Case "AV":   optMedia(2).SetFocus
   Case "Prd":  optMedia(3).SetFocus
   Case "Soft": optMedia(4).SetFocus
   End Select
   txtAuthors.Text = Authors
   txtTitle.Text = Title
   txtTitle.SelStart = 0
   txtTitle.SelLength = Len(txtTitle.Text)
   txtTitle.SetFocus
End Sub

Private Sub cmdFind_Click()
   Dim objSearchCML As New TitleMatch
   Dim itemFound As FoundTitle
   Dim Item As MSComctlLib.ListItem
   Dim subItem As MSComctlLib.ListItem
   
   ' Display search results pane, if invisible
   If Not lvwSearch.Visible Then
      lvwSearch.Visible = True
      Me.Height = Me.ScaleHeight + lvwSearch.Height + Margin
   End If
   
   objSearchCML.LoadCollection txtTitle.Text, txtAuthors, optMedia(SelectedMedia).Tag, Logon, Server
   
   ' Clear the previous list items and refill
   lvwSearch.ListItems.Clear
   For Each itemFound In objSearchCML
      With itemFound
         Set Item = lvwSearch.ListItems.Add()
         Item.SmallIcon = .ReviewStatus
         Set Item.Tag = itemFound
         Item.Text = .Title
         Item.SubItems(1) = .Authors
         Item.SubItems(2) = .MediaType
         Item.SubItems(3) = .Published
      End With
   Next
   
   lvwSearch.Refresh
   
   ' Select the first approximate value
   If lvwSearch.ListItems.Count > 0 Then
      lvwSearch.SetFocus
      If txtTitle.Text <> "" Then
        Set Item = lvwSearch.FindItem(txtTitle.Text, lvwText, 1, lvwPartial)
      ElseIf txtAuthors.Text <> "" Then
         Set Item = lvwSearch.FindItem(txtAuthors.Text, lvwSubItem, 1, lvwPartial)
      Else
        Set Item = lvwSearch.GetFirstVisible
      End If
      
      If Not Item Is Nothing Then
        Item.EnsureVisible
        Item.Selected = True
      End If
   Else
      MsgBox "No items found.", vbInformation, "Find Title"
   End If
   
End Sub

Private Sub cmdOK_Click()
   Dim Item As MSComctlLib.ListItem
   Dim MediaType As String
   
   Set Item = lvwSearch.SelectedItem
   If Item Is Nothing Then
      Title = txtTitle.Text
      Authors = txtAuthors.Text
      MediaType = optMedia.Item(SelectedMedia).Tag
      Me.MediaType = IIf(MediaType = "", "Book", MediaType)
      BibNo = 0
      ObjectID = ""
   Else
      ObjectID = Item.Tag.ObjectID
      
      ' Items that are in process cannot be reviewed
      If ObjectID <> "" And Item.SmallIcon = statusInProcess Then
         MsgBox "You have recently reviewed '" & Item.Text & _
                "' but the review has not yet been approved. " & _
                "Please select another item to review.", _
                vbExclamation, "Review In Process..."
         Exit Sub
      End If
      
      BibNo = Item.Tag.BibNo
      Title = Item.Text
      Authors = Item.SubItems(1)
      Me.MediaType = Item.SubItems(2)
   End If
   
   Unload Me
End Sub

Private Sub cmdCancel_Click()
   Me.MediaType = "Book"
   Unload Me
End Sub

Private Sub Form_Resize()
   Frame1.Width = Me.ScaleWidth
   txtTitle.Width = Me.ScaleWidth - 1200
   txtAuthors.Width = Me.ScaleWidth - 1200
   If Me.ScaleHeight > 2640 Then
      lvwSearch.Visible = True
      lvwSearch.Move Me.ScaleLeft, Me.ScaleTop + 2640, Me.ScaleWidth, Me.ScaleHeight - 2640
   Else
      lvwSearch.Visible = False
   End If
End Sub

Private Sub lvwSearch_ColumnClick(ByVal ColumnHeader As MSComctlLib.ColumnHeader)
   lvwSearch.SortKey = ColumnHeader.Index - 1
   If lvwSearch.SortOrder = lvwAscending Then
      lvwSearch.SortOrder = lvwDescending
   Else
      lvwSearch.SortOrder = lvwAscending
   End If
   lvwSearch.Sorted = True
End Sub

Private Sub lvwSearch_DblClick()
   Call cmdOK_Click
End Sub

Private Sub optMedia_Click(Index As Integer)
   SelectedMedia = Index
End Sub

Private Sub txtAuthors_Change()
   If Trim(txtAuthors.Text) <> "" Then
      cmdFind.Enabled = True
   ElseIf Trim(txtTitle.Text) = "" Then
      cmdFind.Enabled = False
   End If
End Sub

Private Sub txtTitle_Change()
   If Trim(txtTitle.Text) <> "" Then
      cmdFind.Enabled = True
   ElseIf Trim(txtAuthors.Text) = "" Then
      cmdFind.Enabled = False
   End If
End Sub

