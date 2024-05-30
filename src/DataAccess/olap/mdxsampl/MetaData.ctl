VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "comctl32.ocx"
Begin VB.UserControl QueryMetaDataPane 
   ClientHeight    =   3585
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10410
   ClipControls    =   0   'False
   ScaleHeight     =   3585
   ScaleWidth      =   10410
   Begin MDXSample.SplitRegion srgMain 
      Height          =   3075
      Left            =   0
      Top             =   90
      Width           =   10365
      _ExtentX        =   18283
      _ExtentY        =   5424
      FirstControl    =   "pctpane1"
      SecondControl   =   "pctpane2"
      FirstControlMinSize=   800.54
      SplitPercent    =   75
      SplitterBarVertical=   -1  'True
      KeepSplitPercentOnResize=   -1  'True
   End
   Begin VB.PictureBox pctPane2 
      BorderStyle     =   0  'None
      ClipControls    =   0   'False
      Height          =   3075
      Left            =   7824
      ScaleHeight     =   3075
      ScaleWidth      =   2535
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   90
      Width           =   2541
      Begin ComctlLib.TreeView tvwSyntax 
         Height          =   2715
         Left            =   0
         TabIndex        =   5
         Top             =   315
         Width           =   3525
         _ExtentX        =   6218
         _ExtentY        =   4789
         _Version        =   327682
         Indentation     =   529
         LabelEdit       =   1
         LineStyle       =   1
         Style           =   7
         ImageList       =   "imlMetadataIcons"
         Appearance      =   1
      End
      Begin VB.Label lblSyntax 
         Caption         =   "&Syntax Examples"
         Height          =   225
         Left            =   45
         TabIndex        =   4
         Top             =   45
         Width           =   2400
      End
   End
   Begin VB.PictureBox pctPane1 
      BorderStyle     =   0  'None
      ClipControls    =   0   'False
      Height          =   3075
      Left            =   0
      ScaleHeight     =   3075
      ScaleWidth      =   7725
      TabIndex        =   6
      TabStop         =   0   'False
      Top             =   90
      Width           =   7724
      Begin VB.ComboBox cboCube 
         Enabled         =   0   'False
         Height          =   315
         Left            =   615
         OLEDragMode     =   1  'Automatic
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   0
         Width           =   2310
      End
      Begin MDXSample.SplitRegion srgMetadata 
         Height          =   2715
         Left            =   0
         Top             =   315
         Width           =   7710
         _ExtentX        =   13600
         _ExtentY        =   4789
         FirstControl    =   "tvwmetadata"
         SecondControl   =   "lvwMetadata"
         SplitPercent    =   75
         SplitterBarVertical=   -1  'True
         SplitterBarThickness=   50
         KeepSplitPercentOnResize=   -1  'True
      End
      Begin ComctlLib.ListView lvwMetadata 
         Height          =   2715
         Left            =   5808
         TabIndex        =   3
         Top             =   315
         Width           =   1903
         _ExtentX        =   3360
         _ExtentY        =   4789
         View            =   2
         LabelEdit       =   1
         MultiSelect     =   -1  'True
         LabelWrap       =   0   'False
         HideSelection   =   -1  'True
         _Version        =   327682
         SmallIcons      =   "imlMetadataIcons"
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
      Begin ComctlLib.TreeView tvwMetadata 
         Height          =   2715
         Left            =   0
         TabIndex        =   2
         Top             =   315
         Width           =   5758
         _ExtentX        =   10160
         _ExtentY        =   4789
         _Version        =   327682
         Indentation     =   529
         LabelEdit       =   1
         PathSeparator   =   "."
         Style           =   7
         ImageList       =   "imlMetadataIcons"
         Appearance      =   1
         Enabled         =   0   'False
      End
      Begin ComctlLib.ImageList imlMetadataIcons 
         Left            =   4680
         Top             =   945
         _ExtentX        =   1005
         _ExtentY        =   1005
         BackColor       =   -2147483643
         ImageWidth      =   16
         ImageHeight     =   16
         MaskColor       =   12632256
         UseMaskColor    =   0   'False
         _Version        =   327682
         BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
            NumListImages   =   9
            BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":0000
               Key             =   ""
            EndProperty
            BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":031A
               Key             =   ""
            EndProperty
            BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":0634
               Key             =   ""
            EndProperty
            BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":094E
               Key             =   ""
            EndProperty
            BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":0C68
               Key             =   ""
            EndProperty
            BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":0F82
               Key             =   ""
            EndProperty
            BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":129C
               Key             =   ""
            EndProperty
            BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":15B6
               Key             =   ""
            EndProperty
            BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
               Picture         =   "MetaData.ctx":18D0
               Key             =   ""
            EndProperty
         EndProperty
      End
      Begin VB.Label lblCube 
         AutoSize        =   -1  'True
         Caption         =   "&Cube:"
         Height          =   195
         Left            =   50
         TabIndex        =   0
         Top             =   45
         Width           =   420
      End
   End
   Begin VB.Line lnBorder2 
      BorderColor     =   &H80000015&
      X1              =   0
      X2              =   10410
      Y1              =   10
      Y2              =   10
   End
   Begin VB.Line lnBorder1 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   10410
      Y1              =   2
      Y2              =   2
   End
End
Attribute VB_Name = "QueryMetaDataPane"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*******************************************************************************
'* CONTROL: QueryMetaDataPane
'*    The QueryMetaDataPane is the portion of the QueryPane that provides
'*    metadata information to the user.
'*
'* PUBLIC PROPERTIES:
'*    ActiveConnection  Active ADO-MD connection (R/W)
'*    SelText           Currently selected text of the control (R/O)
'*
'* PUBLIC EVENTS:
'*    EditCapabilityChange    Occurs when the edit capabilities of the control
'*                            change
'*    DblClick                Occurs when a control is double clicked
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

Private Const m_iMaxMetadataTreeDepth = 68

Private Enum MetadataIcons
   icoCube = 1
   icoDimension = 2
   icoHierarchy = 3
   icoLevel = 4
   icoMember = 5
   icoMeasure = 6
   icoFolderClosed = 7
   icoFolderOpened = 8
   icoExample = 9
End Enum

Private m_cnActiveConnection As Connection
Private m_ctActiveCatalog As Catalog



'**************
'*** EVENTS ***
'**************

'*******************************************************************************
'* EVENT:  EditCapabilityChange
'*    Occurs when the edit capabilities of the control change
'*
'* PARAMETERS:
'*    fCanCut     Indicates if the Cut method is currently available
'*    fCanCopy    Indicates if the Copy method is currently available
'*******************************************************************************
Public Event EditCapabilityChange(fCanCut As Boolean, _
                                  fCanCopy As Boolean)

'*******************************************************************************
'* EVENT:  DblClick
'*    Occurs when a control is double clicked
'*******************************************************************************
Public Event DblClick()



'******************
'*** PROPERTIES ***
'******************

'*******************************************************************************
'* PROPERTY:  ActiveConnection
'*    Contains the active ADO-MD connection (R/W)
'*******************************************************************************
Public Property Get ActiveConnection() As Connection
   Set ActiveConnection = m_cnActiveConnection
End Property

Public Property Set ActiveConnection(NewActiveConnection As Connection)
   Dim fConnected As Boolean
   
   Set m_cnActiveConnection = NewActiveConnection
   
   ClearMetadata
   
   If m_cnActiveConnection Is Nothing Then
      fConnected = False
   ElseIf m_cnActiveConnection.State = adStateClosed Then
      fConnected = False
   Else
      fConnected = True
      Set m_ctActiveCatalog = New Catalog
      Set m_ctActiveCatalog.ActiveConnection = m_cnActiveConnection
   End If
   
   cboCube.Enabled = fConnected

End Property

'*******************************************************************************
'* PROPERTY:  SelText
'*    Contains the currently selected text of the control (R/O)
'*******************************************************************************
Public Property Get SelText() As String
   Dim ctlCur As Control
   
   Set ctlCur = UserControl.ActiveControl
   If ctlCur Is cboCube Then
      SelText = sGetLegalName(cboCube.Text)
   ElseIf TypeOf ctlCur Is TreeView Then
      SelText = ctlCur.SelectedItem.Tag
   ElseIf TypeOf ctlCur Is ComboBox Then
      SelText = ctlCur.Text
   ElseIf TypeOf ctlCur Is ListView Then
      SelText = ctlCur.SelectedItem.Tag
   Else
      Debug.Assert False
   End If
End Property



'***************
'*** METHODS ***
'***************

'* Clears all metadata
Private Sub ClearMetadata()
   cboCube.Clear
   tvwMetadata.Nodes.Clear
   tvwMetadata.Nodes.Add Text:="<No Cube Selected>", Image:=icoCube
   tvwMetadata.Enabled = False
   If lvwMetadata.ListItems.Count > 0 Then
      lvwMetadata.ListItems.Clear
   End If
   lvwMetadata.Enabled = False
End Sub

'* Adds a dummy child node to the indicated node so that the indicated
'* node can be expanded (at which time the real children are added)
Private Sub AddDummyChild(iNodeIndex As Integer)
   tvwMetadata.Nodes.Add iNodeIndex, tvwChild, vbNullString
End Sub

'* Returns true if the children of the specified node have been populated;
'* false otherwise
Private Function fChildrenPopulated(Nd As ComctlLib.Node) As Boolean
   If Nd.Children = 1 And Nd.Child.Text = vbNullString Then
      fChildrenPopulated = False
   Else
      fChildrenPopulated = True
   End If
End Function

'* Gets the object associated with a given node
Private Function oGetAssociatedObject(Nd As ComctlLib.Node) As Object
   Dim sNameStack(1 To m_iMaxMetadataTreeDepth) As String, iStackPos As Long
   Dim ndCur As ComctlLib.Node
   Dim cb As CubeDef, dm As Dimension, hr As Hierarchy
   Dim lv As Level, mb As Member
   
   Debug.Assert Not Nd Is Nothing
   
   '* Walk up tree creating name stack
   Set ndCur = Nd
   Do Until ndCur Is Nothing
      iStackPos = iStackPos + 1
      sNameStack(iStackPos) = ndCur.Text
      Set ndCur = ndCur.Parent
   Loop
      
   '*** ADOMD Example ***
   
   '* Get Cube using name on top of stack
   Set cb = m_ctActiveCatalog.CubeDefs(sNameStack(iStackPos))
   iStackPos = iStackPos - 1
   If iStackPos = 0 Then
      Set oGetAssociatedObject = cb
      Exit Function
   End If
   
   '* Get Dimension using next name on stack if any
   Set dm = cb.Dimensions(sNameStack(iStackPos))
   iStackPos = iStackPos - 1
   If iStackPos = 0 Then
      If dm.Hierarchies.Count = 1 Then
         Set oGetAssociatedObject = dm.Hierarchies(0)
      Else
         Set oGetAssociatedObject = dm
      End If
      Exit Function
   End If
   
   '* If current dimension contains only one hierarchy then get that;
   '* If multiple hierarchies then get hierarchy using next name on stack if any
   If dm.Hierarchies.Count = 1 Then
      Set hr = dm.Hierarchies(0)
   Else
      Set hr = dm.Hierarchies(sNameStack(iStackPos))
      iStackPos = iStackPos - 1
   End If
   If iStackPos = 0 Then
      Set oGetAssociatedObject = hr
      Exit Function
   End If
   
   '* Get Level using next name on stack if any
   Set lv = hr.Levels(sNameStack(iStackPos))
   iStackPos = iStackPos - 1
   If iStackPos = 0 Then
      Set oGetAssociatedObject = lv
      Exit Function
   End If
   
   '* Loop through any names remaining on stack and get use them to get
   '* members
   Set mb = lv.Members(sNameStack(iStackPos))
   iStackPos = iStackPos - 1
   Do Until iStackPos = 0
      Set mb = mb.Children(sNameStack(iStackPos))
      iStackPos = iStackPos - 1
   Loop
   Set oGetAssociatedObject = mb
   
   '*** End Example ***

End Function

'* Populates the specified node from the metadata
Private Sub PopulateNode(iNodeIndex As Integer)
   Dim ndNew As ComctlLib.Node
   Dim oAssociatedObject As Object
   Dim dmCur As Dimension, hrCur As Hierarchy, lvCur As Level, mbCur As Member
   Dim eIcon As MetadataIcons
   
   With tvwMetadata.Nodes
   
      '* Remove dummy node
      .Remove tvwMetadata.Nodes(iNodeIndex).Child.Index
      
      '*** ADOMD Example ***
      
      '* Get object associated w/ the current node
      Set oAssociatedObject = _
               oGetAssociatedObject(tvwMetadata.Nodes(iNodeIndex))
      
      '* Based on the type of the ADOMD object associated with the node,
      '* loop through the objects contained in this associated object and
      '* add children nodes to represent each of these contained objects
      If TypeOf oAssociatedObject Is CubeDef Then
         SetStatus "Retrieving Dimensions..."
         For Each dmCur In oAssociatedObject.Dimensions
            Set ndNew = .Add(relative:=iNodeIndex, relationship:=tvwChild, _
                            Text:=dmCur.Name, Image:=icoDimension)
            ndNew.Tag = dmCur.UniqueName
            AddDummyChild ndNew.Index
         Next dmCur
      ElseIf TypeOf oAssociatedObject Is Dimension Then
         SetStatus "Retrieving Hierarchies..."
         For Each hrCur In oAssociatedObject.Hierarchies
            Set ndNew = .Add(relative:=iNodeIndex, relationship:=tvwChild, _
                            Text:=hrCur.Name, Image:=icoHierarchy)
            ndNew.Tag = hrCur.UniqueName
            AddDummyChild ndNew.Index
         Next hrCur
      ElseIf TypeOf oAssociatedObject Is Hierarchy Then
         SetStatus "Retrieving Levels..."
         For Each lvCur In oAssociatedObject.Levels
            Set ndNew = .Add(relative:=iNodeIndex, relationship:=tvwChild, _
                            Text:=lvCur.Name, Image:=icoLevel)
            ndNew.Tag = lvCur.UniqueName
            AddDummyChild ndNew.Index
         Next lvCur
      ElseIf TypeOf oAssociatedObject Is Level Then
         SetStatus "Retrieving Members..."
         Set lvCur = oAssociatedObject
         If lvCur.Name = "MeasuresLevel" Then
            eIcon = icoMeasure
         Else
            eIcon = icoMember
         End If
         For Each mbCur In oAssociatedObject.Members
            Set ndNew = .Add(relative:=iNodeIndex, relationship:=tvwChild, _
                            Text:=mbCur.Name, Image:=eIcon)
            ndNew.Tag = mbCur.UniqueName
            If mbCur.ChildCount > 0 Then
               AddDummyChild ndNew.Index
            End If
         Next mbCur
      ElseIf TypeOf oAssociatedObject Is Member Then
         SetStatus "Retrieving Children..."
         For Each mbCur In oAssociatedObject.Children
            Set ndNew = .Add(relative:=iNodeIndex, relationship:=tvwChild, _
                            Text:=mbCur.Name, Image:=icoMember)
            ndNew.Tag = mbCur.UniqueName
            If mbCur.ChildCount > 0 Then
               AddDummyChild ndNew.Index
            End If
         Next mbCur
      Else
         Debug.Assert False
      End If
      
      '*** End Example ***
      
   End With
   
   SetStatus
   
End Sub

'* Lists members of specified node
Private Sub ListNodeMembers(Nd As Node)
   Dim ndChildCur As Node, liCur As ListItem
   
   On Error GoTo ListNodeMembersErr
   
   SetHourglass True
   SetStatus "Retrieving members..."
   
   lvwMetadata.ListItems.Clear
   If Nd Is Nothing Then
      lvwMetadata.Enabled = False
   ElseIf Nd.Image = icoLevel Or Nd.Image = icoMember Then
      lvwMetadata.Enabled = True
      
      If Nd.Children > 0 Then
         If Not fChildrenPopulated(Nd) Then
            PopulateNode Nd.Index
         End If
      End If
      
      With lvwMetadata.ListItems
         Set ndChildCur = Nd.Child
         Do Until ndChildCur Is Nothing
            Set liCur = .Add(, , ndChildCur.Text, , ndChildCur.Image)
            liCur.Tag = ndChildCur.Tag
            Set ndChildCur = ndChildCur.Next
         Loop
      End With
   Else
      lvwMetadata.Enabled = False
   End If
   
   SetStatus
   SetHourglass False
   
   Exit Sub
ListNodeMembersErr:
   SetStatus
   SetHourglass False
   DisplayError "Unable to display members."
End Sub

'* Updates the edit capabilities for the tvwSyntax control
Private Sub UpdateEditCapabilityForTvwSyntax()
   Dim fCanCopy As Boolean
   If tvwSyntax.SelectedItem Is Nothing Then
      fCanCopy = False
   ElseIf tvwSyntax.SelectedItem.Image = icoExample Then
      fCanCopy = True
   Else
      fCanCopy = False
   End If
   RaiseEvent EditCapabilityChange(False, fCanCopy)
End Sub



'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub cboCube_DropDown()
   Dim i As Long, sSelectedCube As String

   On Error GoTo cboCube_DropDownErr
   
   SetHourglass True
   SetStatus "Retrieving list of cubes..."
   
   '* Save selected cube
   sSelectedCube = cboCube.Text
   
   '* Repopulate cube selecting the old selected cube if present
   cboCube.Clear
   With m_ctActiveCatalog.CubeDefs
      For i = 0 To .Count - 1
         cboCube.AddItem .Item(i).Name
         If .Item(i).Name = sSelectedCube Then
            cboCube.ListIndex = i
         End If
      Next i
   End With
   
   
   SetStatus
   SetHourglass False
   
   Exit Sub
cboCube_DropDownErr:
   SetStatus
   SetHourglass False
   DisplayError "Unable to display list of cubes.", m_cnActiveConnection
End Sub

Private Sub cboCube_Click()
   Dim ndCur As Node
   Dim cbCur As CubeDef
   Dim dmCur As Dimension
   Dim hrCur As Hierarchy
   Dim lvCur As Level
   Dim mbCur As Member
   
   On Error GoTo cboCube_ClickErr
   
   SetHourglass True
   
   tvwMetadata.Nodes.Clear
   
   If cboCube.Text = vbNullString Then
      ClearMetadata
   Else
      SetStatus "Retrieving Cube Dimensions..."
      
      Set cbCur = m_ctActiveCatalog.CubeDefs(cboCube.Text)
      tvwMetadata.Enabled = True
      With tvwMetadata.Nodes
         .Clear
         Set ndCur = .Add(Text:=cbCur.Name, Image:=icoCube)
         ndCur.Tag = sGetLegalName(cbCur.Name)
         AddDummyChild ndCur.Index
         ndCur.Expanded = True
      End With
   End If
   
   SetStatus
   SetHourglass False
   
   Exit Sub
cboCube_ClickErr:
   SetStatus
   SetHourglass False
   DisplayError "Unable to retrieve metadata for the cube '" & _
                 cboCube.Text & "', m_cnActiveConnection"
End Sub

Private Sub cboCube_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   RaiseEvent EditCapabilityChange(False, True)
End Sub

Private Sub tvwMetadata_Collapse(ByVal Node As ComctlLib.Node)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   ListNodeMembers tvwMetadata.SelectedItem
End Sub

Private Sub tvwMetadata_Expand(ByVal Node As ComctlLib.Node)
   
   On Error GoTo tvwMetadata_ExpandErr
   SetHourglass True
   
   If Not fChildrenPopulated(Node) Then
      PopulateNode Node.Index
   End If
   
   SetStatus
   SetHourglass False
   
   Exit Sub
tvwMetadata_ExpandErr:
   SetStatus
   SetHourglass False
   DisplayError "Unable to expand node.", m_cnActiveConnection
End Sub

Private Sub tvwMetadata_MouseDown(Button As Integer, _
                                  Shift As Integer, _
                                  X As Single, _
                                  Y As Single)
   Dim ndNewSelection As Node
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   If Button And vbLeftButton Then
      Set ndNewSelection = tvwMetadata.HitTest(X, Y)
      If Not ndNewSelection Is Nothing Then
         ndNewSelection.Selected = True
      End If
   End If
End Sub

Private Sub tvwMetadata_MouseMove(Button As Integer, _
                                  Shift As Integer, _
                                  X As Single, _
                                  Y As Single)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   If Button And vbLeftButton Then
      If Not tvwMetadata.SelectedItem Is Nothing Then
         tvwMetadata.OLEDrag
      End If
   End If
End Sub

Private Sub tvwMetadata_OLECompleteDrag(Effect As Long)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   ListNodeMembers tvwMetadata.SelectedItem
End Sub

Private Sub tvwMetadata_OLEStartDrag(Data As ComctlLib.DataObject, _
                                     AllowedEffects As Long)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   Data.SetData tvwMetadata.SelectedItem.Tag, vbCFText
   AllowedEffects = vbDropEffectCopy
End Sub

Private Sub tvwMetadata_NodeClick(ByVal Node As ComctlLib.Node)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   ListNodeMembers Node
End Sub

Private Sub tvwMetadata_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   RaiseEvent EditCapabilityChange(False, True)
End Sub

Private Sub lvwMetadata_MouseMove(Button As Integer, _
                                  Shift As Integer, _
                                  X As Single, _
                                  Y As Single)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   If Button And vbLeftButton Then
      If Not lvwMetadata.SelectedItem Is Nothing Then
         lvwMetadata.OLEDrag
      End If
   End If
End Sub

Private Sub lvwMetadata_OLEStartDrag(Data As ComctlLib.DataObject, _
                                     AllowedEffects As Long)
   Dim sSelectedMembers As String, iSelectedMemberCnt As Long
   Dim liCur As ListItem
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   For Each liCur In lvwMetadata.ListItems
      If liCur.Selected Then
         If iSelectedMemberCnt = 0 Then
            sSelectedMembers = liCur.Tag
         Else
            sSelectedMembers = _
                  sSelectedMembers & g_sPaddedListDelimiter & liCur.Tag
         End If
         iSelectedMemberCnt = iSelectedMemberCnt + 1
      End If
   Next liCur
   If iSelectedMemberCnt > 1 Then
      sSelectedMembers = g_sSetPrefix & sSelectedMembers & g_sSetSuffix
   End If
   
   Data.SetData sSelectedMembers, vbCFText
   AllowedEffects = vbDropEffectCopy
End Sub

Private Sub lvwMetadata_DblClick()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   RaiseEvent DblClick
End Sub

Private Sub lvwMetadata_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   RaiseEvent EditCapabilityChange(False, True)
End Sub

Private Sub tvwSyntax_Collapse(ByVal Node As ComctlLib.Node)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   Node.Image = icoFolderClosed
   UpdateEditCapabilityForTvwSyntax
End Sub

Private Sub tvwSyntax_Expand(ByVal Node As ComctlLib.Node)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   Node.Image = icoFolderOpened
End Sub

Private Sub tvwSyntax_NodeClick(ByVal Node As ComctlLib.Node)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   UpdateEditCapabilityForTvwSyntax
End Sub

Private Sub tvwMetadata_DblClick()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   RaiseEvent DblClick
End Sub

Private Sub tvwSyntax_OLEStartDrag(Data As ComctlLib.DataObject, _
                                   AllowedEffects As Long)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   Data.SetData tvwSyntax.SelectedItem.Tag, vbCFText
   AllowedEffects = vbDropEffectCopy
End Sub

Private Sub tvwSyntax_MouseDown(Button As Integer, _
                                Shift As Integer, _
                                X As Single, _
                                Y As Single)
   Dim ndNewSelection As Node
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   If Button And vbLeftButton Then
      Set ndNewSelection = tvwSyntax.HitTest(X, Y)
      If Not ndNewSelection Is Nothing Then
         ndNewSelection.Selected = True
      End If
   End If
End Sub

Private Sub tvwSyntax_MouseMove(Button As Integer, _
                                Shift As Integer, _
                                X As Single, _
                                Y As Single)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   If Button And vbLeftButton Then
      If Not tvwSyntax.SelectedItem Is Nothing Then
         If tvwSyntax.SelectedItem.Image = icoExample Then
            tvwSyntax.OLEDrag
         End If
      End If
   End If
End Sub

Private Sub tvwSyntax_DblClick()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   RaiseEvent DblClick
End Sub

Private Sub tvwSyntax_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   UpdateEditCapabilityForTvwSyntax
End Sub

Private Sub pctPane1_Resize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   With srgMetadata
      .Move .Left, .Top, _
            pctPane1.ScaleWidth - .Left, pctPane1.ScaleHeight - .Top
   End With
End Sub

Private Sub pctPane2_Resize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   With tvwSyntax
      .Move .Left, .Top, _
            pctPane2.ScaleWidth - .Left, pctPane2.ScaleHeight - .Top
   End With
End Sub

Private Sub UserControl_Initialize()
   Dim ndCur As Node
   Dim iParent As Long
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
      
   ClearMetadata
   With tvwSyntax.Nodes
      '* MDX Query Examples
      Set ndCur = .Add(, , , "MDX Query", icoExample)
      ndCur.Tag = g_sMDXTplQuery
      Set ndCur = .Add(, , , "MDX Query w/ Member Definition", icoExample)
      ndCur.Tag = g_sMDXTplQueryWMemberDef
      Set ndCur = .Add(, , , "MDX Query w/ Set Definition", icoExample)
      ndCur.Tag = g_sMDXTplQueryWSetDef
      
      '* Set Function Examples
      Set ndCur = .Add(, , , "Set Functions", icoFolderClosed)
      iParent = ndCur.Index
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnBottomCount, icoExample)
      ndCur.Tag = g_sSetFnTplBottomCount
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnBottomPercent, icoExample)
      ndCur.Tag = g_sSetFnTplBottomPercent
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnBottomSum, icoExample)
      ndCur.Tag = g_sSetFnTplBottomSum
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnChildren, icoExample)
      ndCur.Tag = g_sSetFnTplChildren
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnDescendants, icoExample)
      ndCur.Tag = g_sSetFnTplDescendants
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnExcept, icoExample)
      ndCur.Tag = g_sSetFnTplExcept
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnExtract, icoExample)
      ndCur.Tag = g_sSetFnTplExtract
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnFilter, icoExample)
      ndCur.Tag = g_sSetFnTplFilter
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnGenerate, icoExample)
      ndCur.Tag = g_sSetFnTplGenerate
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnHierarchize, icoExample)
      ndCur.Tag = g_sSetFnTplHierarchize
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnIntersect, icoExample)
      ndCur.Tag = g_sSetFnTplIntersect
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnMembers, icoExample)
      ndCur.Tag = g_sSetFnTplMembers
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnNest, icoExample)
      ndCur.Tag = g_sSetFnTplNest
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnOrder, icoExample)
      ndCur.Tag = g_sSetFnTplOrder
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnTopCount, icoExample)
      ndCur.Tag = g_sSetFnTplTopCount
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnTopPercent, icoExample)
      ndCur.Tag = g_sSetFnTplTopPercent
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnTopSum, icoExample)
      ndCur.Tag = g_sSetFnTplTopSum
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnUnion, icoExample)
      ndCur.Tag = g_sSetFnTplUnion
      Set ndCur = .Add(iParent, tvwChild, , g_sSetFnUnique, icoExample)
      ndCur.Tag = g_sSetFnTplUnique
      
      '* Tuple Function Examples
      Set ndCur = .Add(, , , "Tuple Functions", icoFolderClosed)
      iParent = ndCur.Index
      Set ndCur = .Add(iParent, tvwChild, , g_sTpFnCurrent, icoExample)
      ndCur.Tag = g_sTpFnTplCurrent
      
      '* Member Functions Examples
      Set ndCur = .Add(, , , "Member Functions", icoFolderClosed)
      iParent = ndCur.Index
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnAncestor, icoExample)
      ndCur.Tag = g_sMbFnTplAncestor
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnCurrentMember, icoExample)
      ndCur.Tag = g_sMbFnTplCurrentMember
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnFirstChild, icoExample)
      ndCur.Tag = g_sMbFnTplFirstChild
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnFirstSibling, icoExample)
      ndCur.Tag = g_sMbFnTplFirstSibling
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnLag, icoExample)
      ndCur.Tag = g_sMbFnTplLag
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnLastChild, icoExample)
      ndCur.Tag = g_sMbFnTplLastChild
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnLastSibling, icoExample)
      ndCur.Tag = g_sMbFnTplLastSibling
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnLead, icoExample)
      ndCur.Tag = g_sMbFnTplLead
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnNextMember, icoExample)
      ndCur.Tag = g_sMbFnTplNextMember
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnParent, icoExample)
      ndCur.Tag = g_sMbFnTplParent
      Set ndCur = .Add(iParent, tvwChild, , g_sMbFnPrevMember, icoExample)
      ndCur.Tag = g_sMbFnTplPrevMember
           
      '* Numeric Function Examples
      Set ndCur = .Add(, , , "Numeric Functions", icoFolderClosed)
      iParent = ndCur.Index
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnAvg, icoExample)
      ndCur.Tag = g_sNmFnTplAvg
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnCount, icoExample)
      ndCur.Tag = g_sNmFnTplCount
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnMax, icoExample)
      ndCur.Tag = g_sNmFnTplMax
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnMin, icoExample)
      ndCur.Tag = g_sNmFnTplMin
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnRank, icoExample)
      ndCur.Tag = g_sNmFnTplRank
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnStdDev, icoExample)
      ndCur.Tag = g_sNmFnTplStdDev
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnSum, icoExample)
      ndCur.Tag = g_sNmFnTplSum
      Set ndCur = .Add(iParent, tvwChild, , g_sNmFnVariance, icoExample)
      ndCur.Tag = g_sNmFnTplVariance
            
   End With
End Sub

Private Sub UserControl_Resize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   lnBorder1.X2 = UserControl.ScaleWidth
   lnBorder2.X2 = UserControl.ScaleWidth
   With srgMain
      .Move .Left, .Top, _
            UserControl.ScaleWidth - .Left, UserControl.ScaleHeight - .Top
   End With
End Sub
