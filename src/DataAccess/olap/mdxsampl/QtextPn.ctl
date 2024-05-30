VERSION 5.00
Begin VB.UserControl QueryTextPane 
   ClientHeight    =   1485
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10365
   ClipControls    =   0   'False
   ScaleHeight     =   1485
   ScaleWidth      =   10365
   Begin VB.TextBox txtQuery 
      Height          =   1470
      HideSelection   =   0   'False
      Left            =   0
      MultiLine       =   -1  'True
      OLEDropMode     =   1  'Manual
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      ToolTipText     =   "MDX Query"
      Top             =   0
      Width           =   10350
   End
End
Attribute VB_Name = "QueryTextPane"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*******************************************************************************
'* CONTROL: QueryTextPane
'*    The QueryTextPane is the portion of the QueryPane that provides a user
'*    interface for viewing and editing an MDX query.
'*
'* PUBLIC PROPERTIES:
'*    Query       MDX Query to edit/display (R/W)
'*    SelText     Currently selected text of the control (R/W)
'*    SelStart    Starting point of text selected; indicates the position of the
'*                insertion point if no text is selected. (R/W)
'*    SelLength   Number of characters selected (R/W)
'*
'* PUBLIC EVENTS:
'*    EditCapabilityChange    Occurs when the edit capabilities of the control
'*                            change
'*    QueryChanged            Occurs when the query changes
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

'* API Declarations
Private Declare Function SendMessage Lib "user32" Alias "SendMessageA" ( _
         ByVal hwnd As Long, _
         ByVal wMsg As Long, _
         ByVal wParam As Long, _
         ByVal lParam As Long _
      ) As Long
Private Const EM_CHARFROMPOS = &HD7&


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
   Query = txtQuery.Text
End Property

Public Property Let Query(NewQuery As String)
   txtQuery = NewQuery
End Property

'*******************************************************************************
'* PROPERTY:  SelText
'*    Contains the currently selected text of the control (R/W)
'*******************************************************************************
Public Property Get SelText() As String
   SelText = txtQuery.SelText
End Property

Public Property Let SelText(NewSelText As String)
   txtQuery.SelText = NewSelText
End Property

'*******************************************************************************
'* PROPERTY:  SelStart
'*    Contains the starting point of text selected; indicates the position of
'*    the insertion point if no text is selected. (R/W)
'*******************************************************************************
Public Property Get SelStart() As String
   SelStart = txtQuery.SelStart
End Property

Public Property Let SelStart(NewSelStart As String)
   txtQuery.SelStart = NewSelStart
End Property

'*******************************************************************************
'* PROPERTY:  SelLength
'*    Contains the number of characters selected (R/W)
'*******************************************************************************
Public Property Get SelLength() As Long
   SelLength = txtQuery.SelLength
End Property

Public Property Let SelLength(NewSelLength As Long)
   txtQuery.SelLength = NewSelLength
End Property



'***************
'*** METHODS ***
'***************

'* Highlights the current tag if any
Private Sub HighlightTag(txtCtl As TextBox)
   Dim iCharsToStart As Long, iCharsToEnd As Long
   Dim iSelStart As Long, iSelEnd As Long, iSelEndNew As Long
   
   With txtCtl
      iSelStart = .SelStart
      iSelEnd = iSelStart + .SelLength
      
      iCharsToStart = iCharsToTagStart(.Text, iSelStart)
      If iCharsToStart > -1 Then
         iCharsToEnd = iCharsToTagEnd(.Text, iSelStart + 1)
         If iCharsToEnd > -1 Then
            .SelStart = iSelStart - iCharsToStart - 1
            iSelEndNew = iSelStart + 1 + iCharsToEnd
            If iSelEnd < iSelEndNew Then
               .SelLength = iSelEndNew - .SelStart
               Exit Sub
            End If
         End If
      End If
   
      iCharsToStart = iCharsToTagStart(.Text, iSelEnd)
      If iCharsToStart > -1 Then
         iCharsToEnd = iCharsToTagEnd(.Text, iSelEnd + 1)
         If iCharsToEnd > -1 Then
            iSelEnd = iSelEnd + 1 + iCharsToEnd
         End If
      End If
      If Not .SelLength = iSelEnd - .SelStart Then
         .SelLength = iSelEnd - .SelStart
      End If
   End With
   
End Sub

'* Returns the number of characters from the start of the current tag or -1 if
'* not in a tag
Private Function iCharsToTagStart(sSource As String, iPos As Long) As Long
   Dim iPosCur As Long
   iPosCur = iPos
   Do Until iPosCur < 1
      Select Case Mid(sSource, iPosCur, 1)
         Case g_sTagStart
            Exit Do
         Case g_sTagEnd
            iPosCur = -1
         Case Else
         iPosCur = iPosCur - 1
      End Select
   Loop
   
   If iPosCur < 1 Then
      iCharsToTagStart = -1
   Else
      iCharsToTagStart = iPos - iPosCur
   End If
End Function

'* Returns the number of characters to the close of the current tag or -1 if
'* not in a tag
Private Function iCharsToTagEnd(sSource As String, iPos As Long) As Long
   Dim iPosCur As Long, iLen As Long
   
   iLen = Len(sSource)
   iPosCur = iPos
   Do Until iPosCur > iLen
      Select Case Mid(sSource, iPosCur, 1)
         Case g_sTagStart
            iPosCur = iLen + 1
         Case g_sTagEnd
            Exit Do
         Case Else
         iPosCur = iPosCur + 1
      End Select
   Loop
   
   If iPosCur > iLen Then
      iCharsToTagEnd = -1
   Else
      iCharsToTagEnd = iPosCur - iPos
   End If
End Function




'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub txtQuery_Change()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   RaiseEvent QueryChanged
End Sub

Private Sub txtQuery_GotFocus()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   RaiseEvent EditCapabilityChange(True, True, True)
End Sub

Private Sub txtQuery_KeyDown(KeyCode As Integer, Shift As Integer)
   Dim iNewPos As Long
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   If Shift = 0 Then
      With txtQuery
         Select Case KeyCode
            Case vbKeyLeft
               If .SelLength > 0 Then
                  iNewPos = .SelStart
                  .SelLength = 0
                  .SelStart = iNewPos
                  KeyCode = 0
               End If
            Case vbKeyRight
               If .SelLength > 0 Then
                  iNewPos = .SelStart + .SelLength
                  .SelLength = 0
                  .SelStart = iNewPos
                  KeyCode = 0
               End If
         End Select
      End With
   End If
End Sub

Private Sub txtQuery_KeyUp(KeyCode As Integer, Shift As Integer)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   HighlightTag txtQuery
End Sub

Private Sub txtQuery_MouseUp(Button As Integer, _
                             Shift As Integer, _
                             X As Single, _
                             Y As Single)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   HighlightTag txtQuery
End Sub

Private Sub txtQuery_OLEDragDrop(Data As DataObject, _
                                 Effect As Long, _
                                 Button As Integer, _
                                 Shift As Integer, _
                                 X As Single, _
                                 Y As Single)
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   '* Check to ensure text format available
   If Not Data.GetFormat(vbCFText) Then
      Effect = vbDropEffectNone
   Else
      '* Set effect as appropriate
      If Effect And vbDropEffectMove Then
         If Shift Then
            Effect = vbDropEffectCopy
         Else
            Effect = vbDropEffectMove
         End If
      Else
         Effect = vbDropEffectCopy
      End If
   
      '* Highlight and replace drop target
      HighlightTag txtQuery
      txtQuery.SelText = Data.GetData(vbCFText)
   End If
End Sub

Private Sub txtQuery_OLEDragOver(Data As DataObject, _
                                 Effect As Long, _
                                 Button As Integer, _
                                 Shift As Integer, _
                                 X As Single, _
                                 Y As Single, _
                                 State As Integer)
   Dim iX As Integer, iY As Integer
   Dim iResult As Long, iPos As Long, iChar As Integer
   
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
            
   '* Check to ensure text format available
   If Not Data.GetFormat(vbCFText) Then
      Effect = vbDropEffectNone
   Else
      '* Set effect as appropriate
      If Effect And vbDropEffectMove Then
         If Shift Then
            Effect = vbDropEffectCopy
         Else
            Effect = vbDropEffectMove
         End If
      Else
         Effect = vbDropEffectCopy
      End If
      
      '* Highlight drop target intelligently
      iX = CInt(UserControl.ScaleX(X, UserControl.ScaleMode, vbPixels))
      iY = CInt(UserControl.ScaleY(Y, UserControl.ScaleMode, vbPixels))
      iPos = iCombineWordHiLow(iY, iX)
      With txtQuery
         iResult = SendMessage(.hwnd, EM_CHARFROMPOS, 0&, iPos)
         iChar = iGetWordLow(iResult)
         If iChar >= 0 Then
            .SelStart = iChar
         Else
            .SelStart = Len(.Text) + 1
         End If
         HighlightTag txtQuery
      End With
   End If
End Sub

Private Sub UserControl_Resize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   txtQuery.Width = UserControl.ScaleWidth
   txtQuery.Height = UserControl.Height
End Sub
