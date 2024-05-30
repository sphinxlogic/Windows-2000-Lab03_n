VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form FolderPicker 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Select Folder"
   ClientHeight    =   5310
   ClientLeft      =   4605
   ClientTop       =   3360
   ClientWidth     =   6555
   Icon            =   "Folders.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   354
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   437
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdOK 
      Caption         =   "Ok"
      Default         =   -1  'True
      Height          =   375
      Left            =   5160
      TabIndex        =   4
      Top             =   120
      Width           =   1275
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   5400
      Top             =   4680
   End
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "&Refresh"
      Height          =   375
      Left            =   5160
      TabIndex        =   2
      Top             =   1080
      Width           =   1275
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5160
      TabIndex        =   1
      Top             =   600
      Width           =   1275
   End
   Begin ComctlLib.TreeView tvwFolders 
      Height          =   5115
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Visible         =   0   'False
      Width           =   4875
      _ExtentX        =   8599
      _ExtentY        =   9022
      _Version        =   327682
      Indentation     =   635
      LabelEdit       =   1
      LineStyle       =   1
      Style           =   7
      ImageList       =   "imlFolders"
      Appearance      =   1
   End
   Begin VB.Label Label1 
      Caption         =   "Loading Folders Please Wait..."
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   3
      Top             =   720
      Width           =   4455
   End
   Begin ComctlLib.ImageList imlFolders 
      Left            =   5400
      Top             =   3840
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   15
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":000C
            Key             =   "Root"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":0326
            Key             =   "FolderClosed"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":0640
            Key             =   "FolderOpened"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":095A
            Key             =   "Trash"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":0C74
            Key             =   "MsgUnread"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":0F8E
            Key             =   "MsgUnreadPri"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":12A8
            Key             =   "MsgUnreadAttach"
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":15C2
            Key             =   "MsgUnreadPriAttach"
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":18DC
            Key             =   "MsgRead"
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":1BF6
            Key             =   "MsgReadPri"
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":1F10
            Key             =   "MsgReadAttach"
         EndProperty
         BeginProperty ListImage12 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":222A
            Key             =   "MsgReadPriAttach"
         EndProperty
         BeginProperty ListImage13 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":2544
            Key             =   "RouteMap"
         EndProperty
         BeginProperty ListImage14 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":285E
            Key             =   "Binding Agent"
         EndProperty
         BeginProperty ListImage15 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Folders.frx":2B78
            Key             =   "Routing Agent"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "FolderPicker"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'
'  FOLDER PICKER
'
'  Overview: This Form is the "standard" folder picker UI in Visual Basic.
'  It is used to select the folder from the available stores and save
'  the folder ID for further processing by the program.
'***********************************************************************

'Booleans
Private mbNodeClick As Boolean
Private mbPublicFoldersFlag As Boolean

'Constants
Private Const ID_FOLDER_DUMMY = "Folder Dummy Key"   'This is a node place holder

'Image List images for treeview
Private Const ROOT_IMG As Integer = 1
Private Const FOLDER_CLOSED_IMG As Integer = 2
Private Const FOLDER_OPENED_IMG As Integer = 3
Private Const FOLDER_MAP As Integer = 13
Private Const FOLDER_AGENT As Integer = 14
Private Const FOLDER_ROUTING_AGENT As Integer = 15

'Access Levels (bit flags)
Private Const MAPI_ACCESS_MODIFY = &H1
Private Const OWNER_ACCESS = &H4
Private Const FOLDER_PERMISSIONS_ERROR_STRING = "Please select a folder from the list other than the root.  " & _
           "If there are no folders to select, contact " & _
           "your Administrator to obtain permissions to public folders."
Private Const PERSONAL_FOLDERS_STRING = "Personal Folders"
Private Const FAVORITES_STRING = "Favorites"

Private Const ERR_KEY_NOT_UNIQUE = 35602

'--------------------------------------
'  Private: Cancel Button
'
'  Action: Cancel the Form without making
'  a selection.
'--------------------------------------
Private Sub cmdCancel_Click()
   AEClass.Cancelled = True
   FolderPicker.Hide
End Sub

'--------------------------------------
'  Private: OK BUTTON
'
'  Action: Get folder id and save it for
'  use in the project. Verify Permissions.
'
'--------------------------------------
Private Sub cmdOK_Click()
  
  On Error GoTo cmdOKClick_Err
  
  Dim sName As String            'Folder Name
  Dim oNode As Object            'Node Object
  Dim oFolder As Object          'Folder Object
  Dim lAccessMask As Long        'Access Right Long
  Dim sFolderID As String        'Folder ID string
  
  If tvwFolders.SelectedItem Is Nothing Then
    'Complain
    MsgBox FOLDER_PERMISSIONS_ERROR_STRING, vbOKOnly + vbInformation, App.Title
  Else
    If tvwFolders.SelectedItem.Parent Is Nothing Then
      MsgBox FOLDER_PERMISSIONS_ERROR_STRING, vbOKOnly + vbInformation, App.Title
    Else
      sFolderID = tvwFolders.SelectedItem.Key
      Set oNode = tvwFolders.SelectedItem.Parent
      Do
          sName = oNode.Text
          Set oNode = oNode.Parent
      Loop Until oNode Is Nothing
      If sName = AgentMap.PublicStoreName Then
          'gbPublicStore = True
          If tvwFolders.SelectedItem.Parent.Parent Is Nothing Then
            MsgBox "Please select a public folder other than " & tvwFolders.SelectedItem.Text & " from the list.  " & _
                   "If there are no folders to select, contact " & _
                   "your Administrator to obtain permissions to public folders.", vbOKOnly + vbInformation, App.Title
            GoTo Object_Cleanup
          End If
      End If
      
      'Check for proper permissions
      AgentMap.ActiveFolderId = sFolderID
      Set oFolder = AgentMap.Folder
      lAccessMask = oFolder.Fields.item(CdoPR_ACCESS)
      If lAccessMask And OWNER_ACCESS Then
        'Permission granted
        
      Else
        'Permission Denied
        MsgBox "You have to be the folder owner to open this folder. Choose another folder.", vbOKOnly + vbCritical, App.Title
        GoTo Object_Cleanup
      End If
      AgentMap.ActiveFolderId = tvwFolders.SelectedItem.Key
      AEClass.Cancelled = False
      AEditorUI.mnuAgent.item(MENU_AGENT_SELECT).Enabled = True
      Me.Hide
    End If
  End If
  
Object_Cleanup:

  Set oFolder = Nothing
  Set oNode = Nothing
  
  Exit Sub
  
'--------------
cmdOKClick_Err:
  
  Call AgentMap.CdoErrorHandler("cmdOk execution in Folder Picker while trying to access folder information.")
  
End Sub

'-----------------------------------------
'  Sub: CMD REFRESH CLICK
'
'  Action: Refresh the UI treeview control
'
'-----------------------------------------
Private Sub cmdRefresh_Click()
   Timer1.Enabled = True
End Sub


Private Sub Form_Load()
   'Default to true in case user selects top right exit button
   AEClass.Cancelled = True
   
   'Start Load procedure
   Timer1.Enabled = True
End Sub

'-------------------------------------------------
'  Sub: TIMER1 TIMER
'
'  Action: The timer is used to delay the loading
'  of stores until the form has had a chance to
'  fully load.
'-------------------------------------------------
Private Sub Timer1_Timer()

   Timer1.Enabled = False
   tvwFolders.Visible = False
   Me.MousePointer = vbHourglass
   
   'Start the loading of folders in the treeview control.
   Call LoadStores
End Sub

'--------------------------------------------------------------
'  Sub: TVWFOLDERS DBLCLICK
'
'  Action: If the user double clicks a folder then select that
'  folder by call cmdOK_Click
'
'--------------------------------------------------------------
Private Sub tvwFolders_DblClick()
   If mbNodeClick Then
      Call cmdOK_Click
   End If
End Sub

'--------------------------------------------------------------
' Sub:  TVWFOLDERS EXPAND
'
' Action:  Called when a folder is being expanded in the tree
'          view displayed in the Choose Folder page.  This
'          handler works in conjunction with the FolderView
'          class to populate a node in the TreeView.  Thus,
'          nodes are populated on demand.
'
'--------------------------------------------------------------
Private Sub tvwFolders_Expand(ByVal Node As Node)

    Dim sStoreId As String
    Dim sFolderID As String
    Dim iStoreNodeKey As Integer
    Dim iFolderNodeKey As Integer
    Dim nodParent As Object
    Dim nodGrandParent As Object
    
    'If the child has a dummy folder child then load the subfolders
    If Node.Child.Text = ID_FOLDER_DUMMY Then
    
        'Remove the child node. It is a valid node but is not displayed
        'in the tree. It is there so the + box will be displayed in the
        'level above it.
        tvwFolders.Nodes.Remove Node.Child.Index
    
        'Get the folder id and node number
        sFolderID = Node.Key
        iFolderNodeKey = Node.Index
        
        'Get the store id for the current folder by iterating back up through
        'the parent to the root.
        Set nodParent = Node.Parent
        Set nodGrandParent = nodParent
        While Not nodGrandParent Is Nothing  'when it's nothing we are at the top
            Set nodParent = nodGrandParent
            Set nodGrandParent = nodParent.Parent
        Wend
        sStoreId = nodParent.Key
        
        'Load Subfolders of the current folder
        Call LoadSubFolders(sStoreId, sFolderID, iFolderNodeKey)
        
        Me.MousePointer = vbNormal
    End If
End Sub

'--------------------------------------------------------------
' Sub:  LOAD SUB FOLDERS
'
' Action:  Get the subfolders for the current folder and populates
'          the treeview control.
'
'--------------------------------------------------------------
Private Sub LoadSubFolders(ByVal sStoreId As String, ByVal sFolderID As String, ByVal iFolderKey As Integer)
  
   On Error GoTo LoadSubFolders_Err
      
   Dim oFoldersCol As Object
   Dim oParentFolder As Object
   Dim oFolder As Object
   Dim oChildFoldersCol As Object
   Dim oChildFolder As Object
   Dim nodX As Object
   
   Dim bExist As Boolean
   
   Dim lmask As Long
          
   Me.MousePointer = vbHourglass
   
   'Get folder Object
   Set oParentFolder = AgentMap.Session.GetFolder(sFolderID, sStoreId)
    
   'If there is none then we have an error in the sFolderID
   If (oParentFolder Is Nothing) Then
      Exit Sub
   End If
   
   'Here is where you can find out if you want to
   'populate a folder with messages or whatever.
   
   'Get the folder collection and the first folder.
   Set oFoldersCol = oParentFolder.Folders
   Set oFolder = oFoldersCol.GetFirst
      
   'Loop through all the Sub Folders
   If Not oFoldersCol Is Nothing Then
      While Not oFolder Is Nothing
   
         'Format of add is (NODE NUMBER,TYPE, USER KEY,TEXT,IMAGE CLOSED,IMAGE OPEN)
         Set nodX = tvwFolders.Nodes.Add(iFolderKey, tvwChild, oFolder.ID, oFolder.name, FOLDER_CLOSED_IMG, FOLDER_OPENED_IMG)
   
         Set oChildFoldersCol = oFolder.Folders
            If Not (oChildFoldersCol Is Nothing) Then             'may not have access
               Set oChildFolder = oChildFoldersCol.GetFirst
            If Not (oChildFolder Is Nothing) Then
         Set nodX = tvwFolders.Nodes.Add(nodX.Index, tvwChild, , ID_FOLDER_DUMMY, FOLDER_CLOSED_IMG, FOLDER_OPENED_IMG)
            End If
         End If
         
         Set oFolder = oFoldersCol.GetNext
      Wend
   End If
   
   'Cleanup
   Set oFoldersCol = Nothing
   Set oParentFolder = Nothing
   Set oFolder = Nothing
   Set oChildFoldersCol = Nothing
   Set oChildFolder = Nothing
   Set nodX = Nothing
   
   Exit Sub
   
   '---------------
LoadSubFolders_Err:
   
   AppActivate App.Title
   If Err = CdoE_NO_ACCESS Then
     Err.Clear
     Resume Next
   
   ElseIf Err = CdoE_NOT_FOUND Then
     'Some subfolders may not allow access
     Err.Clear
     Resume Next
     
   ElseIf Err = CdoE_INVALID_ENTRYID Then
     '(Caused by LoadStore keys not being unique)
     Err.Clear
     Resume Next
   
   Else
   
     Err.Raise Err.Number, "LoadSubFolders", Err.Description
   End If
   
   Me.MousePointer = vbNormal

End Sub

'--------------------------------------------------------------
' Sub:  LOAD STORES
'
' Action:  Loads the stores into the FolderView.
'
' Return: Boolean Success
'--------------------------------------------------------------
Private Function LoadStores() As Boolean
  
   On Error GoTo LoadStores_Err
  
   Dim bReturnStatus As Boolean           'Fail or Success
   
   'Messaging Objects
   Dim oFoldersCol As Object            'Folder Collection
   Dim oFolder As Object                'Folder Object
   Dim ostore As Object                 'Store Object
   Dim oStoreRoot As Object             'Store Root Object
   Dim oInfoStores As Object            'InfoStores Object
   Dim oChildFoldersCol As Object       'Folder Collection, Children
   Dim oChildFolder As Object           'Folder Object Child
   Dim oTemp As Object                  'Temporary Object
   
   Dim nodTopofStore As Object            'Node Top Object
   
   Dim lmask As Long                      'Long Mask
   Dim iStoreKey As Integer               'Store Key Integer
   Dim iLoop As Integer                   'Loop Variable
   
   Dim sFolderID As String             'Folder ID String
   
   Dim bPublicFlag As Boolean             'Public Store Flag
   Dim bContinue As Boolean               'Continue Flag
   
   
   'Assume Successful
   bReturnStatus = True
   
   ' Clear Treeview control
   tvwFolders.Nodes.Clear
   
   Set oInfoStores = AgentMap.Session.InfoStores
     
   'Pre open all stores
   For Each ostore In oInfoStores
      Set oTemp = ostore.RootFolder
   Next
   
   'Iterate through all of the stores and populate the
   'treeview control
   For Each ostore In oInfoStores
      If ostore.ProviderName <> PERSONAL_FOLDERS_STRING Then
         Set oStoreRoot = ostore.RootFolder
       
         If (ostore Is Nothing) Or (oStoreRoot Is Nothing) Then
            'Problem here.
            bReturnStatus = False
            GoTo ObjectCleanup
         End If
         
         'Set the top node.
         'loop through main folders
         Set nodTopofStore = tvwFolders.Nodes.Add(, , ostore.ID, ostore.name, ROOT_IMG, ROOT_IMG)
         iStoreKey = nodTopofStore.Index
         
         Set oFoldersCol = oStoreRoot.Folders
         If oFoldersCol Is Nothing Then
            'No folder collection available
            
         Else
            For Each oFolder In oFoldersCol
            If oFolder.name <> FAVORITES_STRING Then
               
                Set nodTopofStore = tvwFolders.Nodes.Add(ostore.ID, tvwChild, oFolder.ID, oFolder.name, FOLDER_CLOSED_IMG, FOLDER_OPENED_IMG)
                nodTopofStore.EnsureVisible
               
                'Check for sub-folders
                Set oChildFoldersCol = oFolder.Folders
                If Not (oChildFoldersCol Is Nothing) Then 'may not have access
                  'Add the sub folders for this node.
                  Call LoadSubFolders(ostore.ID, nodTopofStore.Key, nodTopofStore.Index)
                End If
            End If
            Set oChildFoldersCol = Nothing
            Next
         End If
      End If
   Next 'store
   
ObjectCleanup:
   
   'Release Objects
   Set oFoldersCol = Nothing
   Set oFolder = Nothing
   Set ostore = Nothing
   Set oStoreRoot = Nothing
   Set oInfoStores = Nothing
   Set oChildFoldersCol = Nothing
   Set oChildFolder = Nothing
   Set oTemp = Nothing
   Set nodTopofStore = Nothing
   
   Me.MousePointer = vbNormal
   tvwFolders.Visible = True
   
   LoadStores = bReturnStatus
   
   Exit Function
   
'Error Handling
'***************
LoadStores_Err:
      
   Select Case Err.Number
         
      Case CdoE_FAILONEPROVIDER
         MsgBox "Store is unavailable."
         bReturnStatus = False
         Unload FolderPicker
         
      Case CdoE_NO_ACCESS, CdoE_NOT_FOUND, ERR_KEY_NOT_UNIQUE
         Err.Clear
         Resume ObjectCleanup
      
      Case Else
         Call AgentMap.CdoErrorHandler("LoadStores in FrmFolders")
         Err.Clear
         'Resume Next
         Me.MousePointer = vbNormal
         bReturnStatus = False
         Resume ObjectCleanup
   End Select
   
   
End Function

'--------------------------------------------------------------
' Sub:  tvwFolders Mouse Down
'
' Action:  This events is trapped if you are on a folder.
'
'--------------------------------------------------------------
Private Sub tvwFolders_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
   mbNodeClick = False
End Sub

'--------------------------------------------------------------
' Sub:  tvwFolders node click
'
' Action:  This event is trapped on a node.
'
'--------------------------------------------------------------
Private Sub tvwFolders_NodeClick(ByVal Node As ComctlLib.Node)
   mbNodeClick = True
End Sub

