VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "SMS Collection Tree"
   ClientHeight    =   6210
   ClientLeft      =   3240
   ClientTop       =   1395
   ClientWidth     =   6630
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6210
   ScaleWidth      =   6630
   Begin VB.Frame fraLogon 
      Caption         =   "Logon"
      Height          =   975
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   6495
      Begin VB.TextBox txtServer 
         Height          =   285
         Left            =   1080
         TabIndex        =   2
         Top             =   240
         Width           =   1395
      End
      Begin VB.TextBox txtSitecode 
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   1080
         MaxLength       =   3
         TabIndex        =   4
         Top             =   540
         Width           =   1395
      End
      Begin VB.TextBox txtUser 
         Height          =   285
         Left            =   3600
         TabIndex        =   6
         Top             =   240
         Width           =   1395
      End
      Begin VB.TextBox txtPassword 
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   3600
         PasswordChar    =   "*"
         TabIndex        =   8
         Top             =   540
         Width           =   1395
      End
      Begin VB.CommandButton cmdConnect 
         Caption         =   "Connect"
         Default         =   -1  'True
         Height          =   555
         Left            =   5220
         TabIndex        =   9
         Top             =   240
         Width           =   1095
      End
      Begin VB.Label lblSitecode 
         AutoSize        =   -1  'True
         Caption         =   "Sitecode:"
         Height          =   195
         Left            =   180
         TabIndex        =   3
         Top             =   600
         Width           =   675
      End
      Begin VB.Label lblServer 
         AutoSize        =   -1  'True
         Caption         =   "Server:"
         Height          =   195
         Left            =   180
         TabIndex        =   1
         Top             =   300
         Width           =   510
      End
      Begin VB.Label lblUser 
         AutoSize        =   -1  'True
         Caption         =   "User:"
         Height          =   195
         Left            =   2700
         TabIndex        =   5
         Top             =   300
         Width           =   375
      End
      Begin VB.Label lblPassword 
         AutoSize        =   -1  'True
         Caption         =   "Password:"
         Height          =   195
         Left            =   2700
         TabIndex        =   7
         Top             =   600
         Width           =   735
      End
   End
   Begin MSComctlLib.ImageList ImageList2 
      Left            =   5280
      Top             =   4440
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   2
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0442
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":075C
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.ComboBox cboMode 
      Height          =   315
      ItemData        =   "frmMain.frx":0A76
      Left            =   2100
      List            =   "frmMain.frx":0A78
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   1140
      Width           =   4470
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   4500
      Top             =   4440
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   4
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0A7A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0BD4
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0D2E
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0E88
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TreeView tvwMain 
      DragIcon        =   "frmMain.frx":0FE2
      Height          =   4635
      Left            =   60
      TabIndex        =   12
      Top             =   1500
      Width           =   6495
      _ExtentX        =   11456
      _ExtentY        =   8176
      _Version        =   393217
      Indentation     =   423
      LabelEdit       =   1
      Style           =   7
      ImageList       =   "ImageList1"
      Appearance      =   1
   End
   Begin VB.Label lblMode 
      AutoSize        =   -1  'True
      Caption         =   "Drag and Drop Operation:"
      Height          =   195
      Left            =   120
      TabIndex        =   10
      Top             =   1200
      Width           =   1830
   End
   Begin VB.Menu mnuContext 
      Caption         =   "menu root"
      Visible         =   0   'False
      Begin VB.Menu mnuInsertorphans 
         Caption         =   "Recover Orphaned Collections"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuInsertfragments 
         Caption         =   "Recover Lost Fragments"
      End
      Begin VB.Menu mnuSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDelete 
         Caption         =   "Delete Link"
         Enabled         =   0   'False
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'**************************************************************
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'**************************************************************

' frmMain.frm  (STARTUP FORM)


Private WbemServices As SWbemServices       'Global Wbem Services object
Private DragNode As Node                    'Node being dragged.
Private DragInProgress As Boolean           'Is a drag occurring now?
Private FragmentsMightExist As Boolean      'True if broken fragments were detected


'****************************************
'** Form_Load
'****************************************
Private Sub Form_Load()
    
    'Initialize
    DragInProgress = False
    FragmentsMightExist = False
    
    'Place a "not connected" root node in the tree.
    tvwMain.Nodes.Add(, , "COLLROOT", "Not Connected", 1).Tag = "COLLROOT"
    
    'Add
    cboMode.AddItem "Link Collections"
    cboMode.AddItem "Move Collection"
    
    'Set the default
    cboMode.ListIndex = 0
    
End Sub


'****************************************
'** cmdConnect_Click
'****************************************
Private Sub cmdConnect_Click()
    
    ' User and Password variables to be passed to ConnectServer
    Dim sUser As String
    Dim sPassword As String
    
    ' Adjust Logon values as necessary
    If txtServer.Text = "" Then txtServer.Text = "."
    If Len(txtSitecode.Text) <> 3 Then
        MsgBox "Sitecode must be 3 characters in length.", vbCritical, "SMS Collection Tree"
        Exit Sub
    End If
    
    ' Clear the tree if we're already connected.
    If tvwMain.Nodes("COLLROOT").Text <> "Not Connected" Then
        tvwMain.Nodes.Clear
        tvwMain.Nodes.Add(, , "COLLROOT", "Connecting...", 4).Tag = "COLLROOT"
    Else
        tvwMain.Nodes("COLLROOT").Image = 4
        tvwMain.Nodes("COLLROOT").Text = "Connecting..."
    End If
    
    ' Interpret blank user and password as Null Strings
    If txtUser.Text = "" Then sUser = vbNullString Else sUser = txtUser.Text
    If txtPassword.Text = "" Then sPassword = vbNullString Else sPassword = txtPassword.Text
    
    ' Display an hourglass cursor while we connect and resolve the collection tree
    frmMain.MousePointer = vbHourglass
    
    ' Ensure all actions are completed before beginning the connect operation
    DoEvents
    
    Dim WbemLocator As New SWbemLocator
    
    ' Enable error trapping
    On Error Resume Next
    
    ' Connect
    Set WbemServices = WbemLocator.ConnectServer(txtServer.Text, "root\sms\site_" & txtSitecode.Text, sUser, sPassword)
    
    If Err.Number <> wbemNoErr Then
        MsgBox "Connect failed.", vbCritical, "SMS Collection Tree"
        Exit Sub
    End If
    
    ' Disable error trapping
    On Error GoTo 0
    
    ' Change the root node text
    tvwMain.Nodes("COLLROOT").Text = "Collections (" & UCase(txtSitecode.Text) & ")"
    
    ' Resolve collection tree starting from the root
    GetSubCollects tvwMain.Nodes("COLLROOT")
    
    If CheckForLostFragments > 0 Then
        MsgBox "Lost collection tree fragments were detected." & vbCrLf & _
               "Choose ""Recover Lost Tree Fragments"" from the" & vbCrLf & _
               "right-click menu to fix the problem.", vbCritical, "SMS Collection Tree"
        FragmentsMightExist = True
    End If
    
    ' See if any orphaned collections exist and warn the user
    If FragmentsMightExist = False Then CheckForOrphans
    
    ' Set the root node image appropriately, depending on if it has been expanded.
    If tvwMain.Nodes("COLLROOT").Expanded Then tvwMain.Nodes("COLLROOT").Image = 3 Else tvwMain.Nodes("COLLROOT").Image = 2
    
    ' Scroll back to the top
    tvwMain.Nodes("COLLROOT").EnsureVisible
    
    ' Restore the mouse pointer
    frmMain.MousePointer = vbDefault
    
End Sub


'****************************************
'** GetSubCollects
'****************************************
Private Sub GetSubCollects(Parent As Node)
    Dim QueryResults As SWbemObjectSet
    Dim QueryResult As SWbemObject
    Dim SMSCollection As SWbemObject
    Dim NewNode As Node
    
    ' Find all children of the given node
    Set QueryResults = WbemServices.ExecQuery("SELECT * FROM SMS_CollectToSubCollect WHERE parentCollectionID = """ & Parent.Tag & """")
    
    ' Walk the results
    For Each QueryResult In QueryResults
        
        ' Retrieve the actual collection instances (only way to get the collection name)
        Set SMSCollection = WbemServices.Get("SMS_Collection.CollectionID=""" & QueryResult.subCollectionID & """")
        
        ' Add a new node to the tree, set it's tag and ensure it's visible
        Set NewNode = tvwMain.Nodes.Add(Parent.Key, tvwChild, Parent.Key & QueryResult.subCollectionID, SMSCollection.Name, 1)
        NewNode.Tag = QueryResult.subCollectionID
        NewNode.EnsureVisible
        
        ' WBEM calls block VB, it's good to put DoEvents in loops with wbem calls
        DoEvents
        
        ' Recurse down
        GetSubCollects NewNode
        
    Next QueryResult
    
End Sub


'****************************************
'** DragDropOccurred
'****************************************
Private Sub DragDropOccurred(FromNode As Node, ToNode As Node)
    
    If FromNode Is ToNode Or FromNode.Key = "COLLROOT" Then Exit Sub
    
    Dim MethodParameters As SWbemObject
    Dim MethodResult As SWbemObject
    
    frmMain.MousePointer = vbHourglass
    
    ' Retrieve the method in-parameter object for SMS_Collection::VerifyNoLoops
    Set MethodParameters = WbemServices.Get("SMS_Collection").Methods_("VerifyNoLoops").InParameters
    
    ' Fill the parameters
    MethodParameters.ParentCollection = "SMS_Collection.CollectionID=""" & ToNode.Tag & """"
    MethodParameters.subCollection = "SMS_Collection.CollectionID=""" & FromNode.Tag & """"
        
    ' Execute the method
    Set MethodResult = WbemServices.ExecMethod("SMS_Collection", "VerifyNoLoops", MethodParameters)
    
    ' Examine the method result object (out-parameter)
    If MethodResult.result = False Then
        frmMain.MousePointer = vbDefault
        MsgBox "ERROR: This operation would cause a loop condition to exist.", vbCritical, "SMS Collection Tree"
        Exit Sub
    End If
    
    ' Take appropriate action depending on the state of the "Drag-n-Drop Operation" combobox.
    Select Case cboMode.ListIndex
    
    Case 0
        CopyNode FromNode, ToNode
        
    Case 1
        MoveNode FromNode, ToNode
        
    End Select
    
    ' Reload the collection tree
    RefreshCollections
    
    
    
    '*****************************************
    
    ' REFRESH COLLECTIONS!!!!
    
    '*****************************************
    
    
    
    tvwMain.Nodes("COLLROOT").Text = "Collections (" & UCase(txtSitecode.Text) & ")"
    
    frmMain.MousePointer = vbDefault
    
End Sub


'****************************************
'** CopyNode
'****************************************
Private Sub CopyNode(FromNode As Node, ToNode As Node)
    
    Dim WbemObject As SWbemObject
    
    ' Spawn a new instance of SMS_CollectToSubCollect
    Set WbemObject = WbemServices.Get("SMS_CollectToSubCollect").SpawnInstance_
    
    ' Store properties
    WbemObject.subCollectionID = FromNode.Tag
    WbemObject.parentCollectionID = ToNode.Tag
    
    On Error Resume Next
    
    ' Commit the object
    WbemObject.Put_ wbemChangeFlagCreateOnly
    
    If Err.Number <> wbemNoErr Then
        MsgBox "ERROR: Could not establish collection relationship.", vbCritical, "SMS Collection Tree"
        Exit Sub
    End If
   
End Sub


'****************************************
'** MoveNode
'****************************************
Private Sub MoveNode(FromNode As Node, ToNode As Node)
    
    Dim WbemObject As SWbemObject
    
    ' Spawn new instance of SMS_CollectToSubCollect
    Set WbemObject = WbemServices.Get("SMS_CollectToSubCollect").SpawnInstance_
    
    ' Set properties
    WbemObject.subCollectionID = FromNode.Tag
    WbemObject.parentCollectionID = ToNode.Tag
        
    On Error Resume Next
    
    ' Commit Object
    WbemObject.Put_ wbemChangeFlagCreateOnly
    
    If Err.Number <> wbemNoErr Then
        MsgBox "ERROR: Could not establish collection relationship.", vbCritical, "SMS Collection Tree"
        Exit Sub
    End If
    
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ' Delete "old" instance
    WbemServices.Delete "SMS_CollectToSubCollect.parentCollectionID=""" & FromNode.Parent.Tag & """,subCollectionID=""" & FromNode.Tag & """"
    
    If Err.Number <> wbemNoErr Then
        MsgBox "ERROR: Could not establish collection relationship.", vbCritical, "SMS Collection Tree"
        Exit Sub
    End If
    
End Sub


'****************************************
'** RefreshCollections
'****************************************
Private Sub RefreshCollections(Optional bCheckForOrphans As Boolean = False)
    
    ' Clear the tree
    tvwMain.Nodes.Clear
    
    ' Add root node
    tvwMain.Nodes.Add(, , "COLLROOT", "Refreshing Collection Tree...", 4).Tag = "COLLROOT"
    
    ' Begin recursive tree discovery
    GetSubCollects tvwMain.Nodes("COLLROOT")
    
    ' Call CheckForOrphans diagnostic
    If bCheckForOrphans Then CheckForOrphans
    
    ' Set the root node image appropriately, depending on if it has been expanded.
    If tvwMain.Nodes("COLLROOT").Expanded Then tvwMain.Nodes("COLLROOT").Image = 3 Else tvwMain.Nodes("COLLROOT").Image = 2
    
End Sub


'****************************************
'** GetLinkCount
'****************************************
Private Function GetLinkCount(LinkNode As Node) As Integer
    'GetLinkCount counts all occurrences of a collection in the tree
    
    If LinkNode Is Nothing Or LinkNode.Key = "COLLROOT" Then Exit Function
    
    Dim subCollectionID As String
    Dim parentCollectionID As String
    Dim nodeiter As Node
    Dim count As Integer
    
    subCollectionID = LinkNode.Tag
    parentCollectionID = LinkNode.Parent.Tag
    
    count = 0
    
    For Each nodeiter In tvwMain.Nodes
        If nodeiter.Tag <> "COLLROOT" Then
            If nodeiter.Tag = subCollectionID And nodeiter.Parent <> parentCollectionID Then
                count = count + 1
            End If
        End If
    Next nodeiter
    
    GetLinkCount = count
    
End Function


'****************************************
'** CheckForOrphans
'****************************************
Private Function CheckForOrphans(Optional messagebox As Boolean = True) As Integer
    'CheckForOrphans searches for instances of SMS_Collection without any matching
    'instances of SMS_CollectToSubCollect.  Such instances would therefore
    'not be visible in the SMS Admin UI.
    
    Dim nodeiter As Node
    Dim Collections As SWbemObjectSet
    Dim Collection As SWbemObject
    Dim CollectionId As String
    
    Dim Orphan As Boolean
    Dim OrphanCount As Integer
    
    OrphanCount = 0
    
    Set Collections = WbemServices.InstancesOf("SMS_Collection")
    
    For Each Collection In Collections
        Orphan = True
        CollectionId = Collection.CollectionId
        If CollectionId <> "COLLROOT" Then
            For Each nodeiter In tvwMain.Nodes
                If nodeiter.Tag = CollectionId Then
                    Orphan = False
                    Exit For
                End If
            Next nodeiter
            If Orphan = True Then
                OrphanCount = OrphanCount + 1
            End If
        End If
    Next Collection
    
    If OrphanCount > 0 And messagebox Then
        
        MsgBox CStr(OrphanCount) & " orphaned collections were detected!" & vbCrLf & vbCrLf & _
                                 "Orphaned collections can be recovered by right-clicking" & vbCrLf & _
                                 "a collection and choosing ""Recover Orphaned Collections.""", vbExclamation
        
    End If
    
    CheckForOrphans = OrphanCount
    
End Function


'****************************************
'** CheckForLostFragments
'****************************************
Private Function CheckForLostFragments() As Integer
    'CheckForLostFragments searches for instances of SMS_CollectToSubCollect where
    'the ParentCollectionID is not the SubCollectionID of any others.

    Dim Collections As SWbemObjectSet
    Dim Collection As SWbemObject
    Dim QueryResult As SWbemObjectSet
    Dim fragment As Boolean
    Dim fragmentcount As Integer
    
    Set Collections = WbemServices.ExecQuery("SELECT * FROM SMS_CollectToSubCollect WHERE parentCollectionID != ""COLLROOT""")
    
    For Each Collection In Collections
        Set QueryResult = WbemServices.ExecQuery("SELECT * FROM SMS_CollectToSubCollect WHERE subCollectionID=""" & Collection.parentCollectionID & """")
        If QueryResult.count < 1 Then
            fragmentcount = fragmentcount + 1
        End If
    Next Collection
    
    CheckForLostFragments = fragmentcount
End Function




'****************************************
'****************************************
'** CONTEXT MENU FUNCTIONS AND EVENTS
'****************************************
'****************************************

'****************************************
'** ContextMenu
'****************************************
Private Sub ContextMenu(ForNode As Node, x As Single, y As Single)
    'Context menu is called when a context menu needs to be displayed.
    'This function determines which context menu items are to be enabled.
    
    mnuDelete.Enabled = False
    mnuInsertorphans.Enabled = False
    mnuInsertfragments.Enabled = False
    
    If ForNode.Key = "COLLROOT" And ForNode.Text <> "Collections (" & UCase(txtSitecode.Text) & ")" Then Exit Sub
    
    frmMain.MousePointer = vbHourglass
    
    If ForNode.Key <> "COLLROOT" Then If GetLinkCount(ForNode) > 1 Then mnuDelete.Enabled = True
    
    If CheckForOrphans(False) > 0 Then mnuInsertorphans.Enabled = True
    
    If FragmentsMightExist Then mnuInsertfragments.Enabled = True
    
    frmMain.MousePointer = vbDefault
    
    PopupMenu mnuContext, 0, x, y + tvwMain.Top
    
End Sub


'****************************************
'** mnuDelete_Click
'****************************************
Private Sub mnuDelete_Click()
    'This function deletes the instance of SMS_CollectToSubCollect matching
    ' the selected node in the tree
    
    frmMain.MousePointer = vbHourglass
    WbemServices.Delete "SMS_CollectToSubCollect.parentCollectionID=""" & tvwMain.SelectedItem.Parent.Tag & """,subCollectionID=""" & tvwMain.SelectedItem.Tag & """"
    RefreshCollections
    tvwMain.Nodes("COLLROOT").Text = "Collections (" & UCase(txtSitecode.Text) & ")"
    frmMain.MousePointer = vbDefault
End Sub


'****************************************
'** mnuInsertfragments_Click
'****************************************
Private Sub mnuInsertfragments_Click()
    'This function attempts to reconstruct any disconnected fragments of the collection
    'tree underneath the currently selected node.

    Dim Collections As SWbemObjectSet
    Dim Collection As SWbemObject
    Dim QueryResult As SWbemObjectSet
    Dim NewInstance As SWbemObject
    
    frmMain.MousePointer = vbHourglass
    
    Set Collections = WbemServices.ExecQuery("SELECT * FROM SMS_CollectToSubCollect WHERE parentCollectionID != ""COLLROOT""")
    
    For Each Collection In Collections
        Set QueryResult = WbemServices.ExecQuery("SELECT * FROM SMS_CollectToSubCollect WHERE subCollectionID=""" & Collection.parentCollectionID & """")
        If QueryResult.count < 1 Then
            Set NewInstance = WbemServices.Get("SMS_CollectToSubCollect").SpawnInstance_
            NewInstance.parentCollectionID = tvwMain.SelectedItem.Tag
            NewInstance.subCollectionID = Collection.parentCollectionID
            NewInstance.Put_
        End If
    Next Collection
    
    RefreshCollections
    tvwMain.Nodes("COLLROOT").Text = "Collections (" & UCase(txtSitecode.Text) & ")"
    frmMain.MousePointer = vbDefault
    
End Sub


'****************************************
'** mnuInsertorphans_Click
'****************************************
Private Sub mnuInsertorphans_Click()
    'This function creates instances of SMS_CollectToSubCollect for all
    'collections which do not have matching SMS_CollectToSubCollect instances.
    'The currently selected node becomes the parent.
    
    Dim Collections As SWbemObjectSet
    Dim Collection As SWbemObject
    Dim QueryResult As SWbemObjectSet
    Dim NewInstance As SWbemObject
    
    frmMain.MousePointer = vbHourglass
    
    Set Collections = WbemServices.ExecQuery("SELECT * FROM SMS_Collection WHERE CollectionID != ""COLLROOT""")
    
    For Each Collection In Collections
        Set QueryResult = WbemServices.ExecQuery("SELECT * FROM SMS_CollectToSubCollect WHERE subCollectionID=""" & Collection.CollectionId & """")
        If QueryResult.count < 1 Then
            Set NewInstance = WbemServices.Get("SMS_CollectToSubCollect").SpawnInstance_
            NewInstance.parentCollectionID = tvwMain.SelectedItem.Tag
            NewInstance.subCollectionID = Collection.CollectionId
            NewInstance.Put_
        End If
    Next Collection
    
    RefreshCollections
    tvwMain.Nodes("COLLROOT").Text = "Collections (" & UCase(txtSitecode.Text) & ")"
    frmMain.MousePointer = vbDefault
End Sub




'****************************************
'****************************************
'** TREEVIEW EVENTS
'****************************************
'****************************************

'****************************************
'** tvwMain_Expand
'****************************************
Private Sub tvwMain_Expand(ByVal Node As MSComctlLib.Node)
    If Node.Image = 2 Then Node.Image = 3
End Sub


'****************************************
'** tvwMain_Collapse
'****************************************
Private Sub tvwMain_Collapse(ByVal Node As MSComctlLib.Node)
    If Node.Image = 3 Then Node.Image = 2
End Sub


'****************************************
'** tvwMain_MouseDown
'****************************************
Private Sub tvwMain_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    Select Case Button
    Case vbLeftButton
        Set tvwMain.SelectedItem = tvwMain.HitTest(x, y)
        Set DragNode = tvwMain.SelectedItem
    Case vbRightButton
        Set tvwMain.SelectedItem = tvwMain.HitTest(x, y)
        If Not tvwMain.SelectedItem Is Nothing Then
            ContextMenu tvwMain.SelectedItem, x, y
        End If
    End Select
End Sub


'****************************************
'** tvwMain_MouseMove
'****************************************
Private Sub tvwMain_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = vbLeftButton And (Not tvwMain.SelectedItem Is Nothing) Then
        DragInProgress = True
        tvwMain.Drag vbBeginDrag
    End If
End Sub


'****************************************
'** tvwMain_DragOver
'****************************************
Private Sub tvwMain_DragOver(Source As Control, x As Single, y As Single, State As Integer)
    If DragInProgress Then Set tvwMain.DropHighlight = tvwMain.HitTest(x, y)
End Sub


'****************************************
'** tvwMain_DragDrop
'****************************************
Private Sub tvwMain_DragDrop(Source As Control, x As Single, y As Single)
    If Not tvwMain.DropHighlight Is Nothing Then
        DragDropOccurred DragNode, tvwMain.DropHighlight
        DragInProgress = False
    Else
        Set tvwMain.DropHighlight = Nothing
        DragInProgress = False
    End If
End Sub

