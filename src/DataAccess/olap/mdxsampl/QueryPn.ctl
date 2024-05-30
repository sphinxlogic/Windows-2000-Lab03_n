VERSION 5.00
Begin VB.UserControl QueryPane 
   ClientHeight    =   3108
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   11076
   ClipControls    =   0   'False
   ScaleHeight     =   3108
   ScaleWidth      =   11076
   Begin MDXSample.QueryMetaDataPane cctlQueryMetaDataPane 
      Height          =   1666
      Left            =   0
      TabIndex        =   1
      Top             =   1407
      Width           =   11040
      _ExtentX        =   19473
      _ExtentY        =   2942
   End
   Begin MDXSample.QueryTextPane cctlQueryTextPane 
      Height          =   1307
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   11040
      _ExtentX        =   19473
      _ExtentY        =   2307
   End
   Begin MDXSample.SplitRegion srgMain 
      Height          =   3075
      Left            =   0
      Top             =   0
      Width           =   11040
      _ExtentX        =   19473
      _ExtentY        =   5419
      FirstControl    =   "cctlQueryTextPane"
      SecondControl   =   "cctlQueryMetaDataPane"
      SecondControlMinSize=   600
      SplitPercent    =   44.163
   End
End
Attribute VB_Name = "QueryPane"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*******************************************************************************
'* CONTROL: QueryPane
'*    The QueryPane provides the display and editing of an MDX Query.  To
'*    assist in the creation of valid MDX Queries, the QueryPane also provides
'*    a browser view of metadata
'*
'* PUBLIC PROPERTIES:
'*    Query             MDX Query to edit/display (R/W)
'*    ActiveConnection  Active ADO-MD connection (R/W)
'*    SelText           Currently selected text of the control (R/W)
'*    Query             MDX Query to edit/display (R/W)
'*    ActiveConnection  Active ADO-MD connection (R/W)
'*    SelText           Currently selected text of the control (R/W)
'*    SelStart          Starting point of text selected; indicates the position
'*                      of the insertion point if no text is selected; Available
'*                      only when fCanPaste is true (R/W)
'*    SelLength         Number of characters selected; Available only when
'*                      fCanPaste is true (R/W)
'*
'* PUBLIC EVENTS:
'*    EditCapabilityChange    Occurs when the edit capabilities of the control
'*                            change
'*    QueryRunablityChange    Occurs when the runability of the current query
'*                            changes
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
'*    fCanPaste   Indicates if the Paste method is currently available
'*******************************************************************************
Public Event EditCapabilityChange(fCanCut As Boolean, _
                                  fCanCopy As Boolean, _
                                  fCanPaste As Boolean)

'*******************************************************************************
'* EVENT:  QueryChanged
'*    Occurs when the query changes
'*******************************************************************************
Public Event QueryChanged()



'******************
'*** PROPERTIES ***
'******************

'*******************************************************************************
'* PROPERTY:  Query
'*    Contains the mDX Query to edit/display (R/W)
'*******************************************************************************
Public Property Get Query() As String
   Query = cctlQueryTextPane.Query
End Property

Public Property Let Query(NewQuery As String)
   cctlQueryTextPane.Query = NewQuery
End Property

'*******************************************************************************
'* PROPERTY:  ActiveConnection
'*    Contains the active ADO-MD connection (R/W)
'*******************************************************************************
Public Property Get ActiveConnection() As Connection
   Set ActiveConnection = cctlQueryMetaDataPane.ActiveConnection
End Property

Public Property Set ActiveConnection(NewActiveConnection As Connection)
   Set cctlQueryMetaDataPane.ActiveConnection = NewActiveConnection
End Property

'*******************************************************************************
'* PROPERTY:  SelText
'*    Contains the currently selected text of the control (R/W)
'*******************************************************************************
Public Property Get SelText() As String
   If UserControl.ActiveControl Is cctlQueryTextPane Then
      SelText = cctlQueryTextPane.SelText
   End If
End Property

Public Property Let SelText(NewSelText As String)
   UserControl.ActiveControl.SelText = NewSelText
End Property

'*******************************************************************************
'* PROPERTY:  SelStart
'*    Contains the starting point of text selected; indicates the position of
'*    the insertion point if no text is selected; Available only when fCanPaste
'*    is true (R/W)
'*******************************************************************************
Public Property Get SelStart() As String
   If UserControl.ActiveControl Is cctlQueryTextPane Then
      SelStart = cctlQueryTextPane.SelStart
   End If
End Property

Public Property Let SelStart(NewSelStart As String)
   If UserControl.ActiveControl Is cctlQueryTextPane Then
      cctlQueryTextPane.SelStart = NewSelStart
   End If
End Property

'*******************************************************************************
'* PROPERTY:  SelLength
'*    Contains the number of characters selected; Available only when fCanPaste
'*    is true (R/W)
'*******************************************************************************
Public Property Get SelLength() As Long
   If UserControl.ActiveControl Is cctlQueryTextPane Then
      SelLength = cctlQueryTextPane.SelLength
   End If
End Property

Public Property Let SelLength(NewSelLength As Long)
   If UserControl.ActiveControl Is cctlQueryTextPane Then
      cctlQueryTextPane.SelLength = NewSelLength
   End If
End Property

'***************
'*** METHODS ***
'***************



'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub UserControl_Resize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   srgMain.Width = UserControl.ScaleWidth
   srgMain.Height = UserControl.ScaleHeight
End Sub

Private Sub cctlQueryTextPane_QueryChanged()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   RaiseEvent QueryChanged
End Sub

Private Sub cctlQueryTextPane_EditCapabilityChange(fCanCut As Boolean, _
                                                   fCanCopy As Boolean, _
                                                   fCanPaste As Boolean)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   RaiseEvent EditCapabilityChange(fCanCut, fCanCopy, fCanPaste)
End Sub

Private Sub cctlQueryMetaDataPane_EditCapabilityChange(fCanCut As Boolean, _
                                                       fCanCopy As Boolean)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   RaiseEvent EditCapabilityChange(fCanCut, fCanCopy, False)
End Sub

Private Sub cctlQueryMetaDataPane_DblClick()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   With cctlQueryTextPane
      .SelText = cctlQueryMetaDataPane.SelText
      .SelStart = .SelStart + .SelLength
   End With
End Sub


