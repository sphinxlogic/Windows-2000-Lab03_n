VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "SHDOCVW.DLL"
Begin VB.Form XSL_Pattern 
   Caption         =   "XSL Visual Pattern Builder"
   ClientHeight    =   8535
   ClientLeft      =   60
   ClientTop       =   540
   ClientWidth     =   9240
   Icon            =   "XSL.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8535
   ScaleWidth      =   9240
   Begin VB.CommandButton cmdView 
      Caption         =   "&View XML"
      Height          =   375
      Left            =   7320
      TabIndex        =   1
      Top             =   120
      Width           =   1695
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   8295
      Left            =   9360
      TabIndex        =   30
      Top             =   120
      Width           =   5775
      ExtentX         =   10186
      ExtentY         =   14631
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   1
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
   Begin VB.CommandButton cmdAdd6 
      Caption         =   "Add"
      Height          =   255
      Left            =   8520
      TabIndex        =   10
      Top             =   3240
      Width           =   495
   End
   Begin VB.TextBox txtAttributeValue 
      Height          =   285
      Left            =   5280
      TabIndex        =   9
      Top             =   3240
      Width           =   3135
   End
   Begin VB.ListBox lstAttributes 
      Height          =   1230
      Left            =   5280
      TabIndex        =   6
      Top             =   1680
      Width           =   3735
   End
   Begin VB.CommandButton cmdAdd5 
      Caption         =   "Add"
      Height          =   255
      Left            =   5880
      TabIndex        =   18
      Top             =   4080
      Width           =   495
   End
   Begin VB.ListBox lstMethods 
      Height          =   1035
      ItemData        =   "XSL.frx":0442
      Left            =   4440
      List            =   "XSL.frx":0473
      TabIndex        =   17
      Top             =   4080
      Width           =   1335
   End
   Begin VB.CommandButton cmdAdd4 
      Caption         =   "Add"
      Height          =   255
      Left            =   3360
      TabIndex        =   8
      Top             =   3240
      Width           =   495
   End
   Begin VB.CommandButton cmdAdd3 
      Caption         =   "Add"
      Height          =   255
      Left            =   3840
      TabIndex        =   16
      Top             =   4080
      Width           =   495
   End
   Begin VB.CommandButton cmdAdd2 
      Caption         =   "Add"
      Height          =   255
      Left            =   2160
      TabIndex        =   14
      Top             =   4080
      Width           =   495
   End
   Begin VB.CommandButton cmdAdd1 
      Caption         =   "Add"
      Height          =   255
      Left            =   840
      TabIndex        =   12
      Top             =   4080
      Width           =   495
   End
   Begin VB.TextBox txtValue 
      Height          =   285
      Left            =   120
      TabIndex        =   7
      Top             =   3240
      Width           =   3135
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "&Clear Pattern"
      Height          =   375
      Left            =   7560
      TabIndex        =   19
      Top             =   4080
      Width           =   1455
   End
   Begin VB.TextBox txtPatternResults 
      Height          =   2655
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   21
      Top             =   5760
      Width           =   9015
   End
   Begin VB.CommandButton cmdDrillup 
      Caption         =   "&Up One Level"
      Enabled         =   0   'False
      Height          =   495
      Left            =   4080
      TabIndex        =   4
      Top             =   1680
      Width           =   975
   End
   Begin VB.CommandButton cmdDrill 
      Caption         =   "&Down One Level"
      Enabled         =   0   'False
      Height          =   495
      Left            =   4080
      TabIndex        =   5
      Top             =   2400
      Width           =   975
   End
   Begin VB.ListBox lstNodes 
      Height          =   1230
      Left            =   120
      TabIndex        =   3
      Top             =   1680
      Width           =   3735
   End
   Begin VB.CommandButton cmdPattern 
      Caption         =   "&Run Pattern"
      Height          =   375
      Left            =   7560
      TabIndex        =   20
      Top             =   4800
      Width           =   1455
   End
   Begin VB.TextBox txtPattern 
      Height          =   285
      Left            =   120
      TabIndex        =   2
      Top             =   960
      Width           =   8895
   End
   Begin VB.ListBox lstContext 
      Height          =   1035
      ItemData        =   "XSL.frx":050A
      Left            =   240
      List            =   "XSL.frx":051D
      TabIndex        =   11
      Top             =   4080
      Width           =   495
   End
   Begin VB.ListBox lstExpressions 
      Height          =   1035
      ItemData        =   "XSL.frx":053E
      Left            =   2760
      List            =   "XSL.frx":0563
      TabIndex        =   15
      Top             =   4080
      Width           =   975
   End
   Begin VB.ListBox lstChars 
      Height          =   1035
      ItemData        =   "XSL.frx":05C8
      Left            =   1440
      List            =   "XSL.frx":05F3
      TabIndex        =   13
      Top             =   4080
      Width           =   615
   End
   Begin MSComDlg.CommonDialog FileOpen1 
      Left            =   5880
      Top             =   4680
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   ".xml"
      DialogTitle     =   "XML File Open"
      FileName        =   "*.xml"
      Filter          =   "*.xml"
      PrinterDefault  =   0   'False
   End
   Begin VB.CommandButton cmdLoad 
      Caption         =   "&Load XML File"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1575
   End
   Begin VB.Line Line2 
      X1              =   9240
      X2              =   9240
      Y1              =   0
      Y2              =   8400
   End
   Begin VB.Label lblXSLSyntax 
      AutoSize        =   -1  'True
      Caption         =   "Available XSL pattern operators and methods:"
      Height          =   195
      Left            =   240
      TabIndex        =   29
      Top             =   3720
      Width           =   3240
   End
   Begin VB.Label lblAttributes2 
      AutoSize        =   -1  'True
      Caption         =   "Selected Attribute Value:"
      Height          =   195
      Left            =   5280
      TabIndex        =   28
      Top             =   3000
      Width           =   1755
   End
   Begin VB.Label lblArributes1 
      AutoSize        =   -1  'True
      Caption         =   "Attributes from selected node:"
      Height          =   195
      Left            =   5280
      TabIndex        =   27
      Top             =   1440
      Width           =   2100
   End
   Begin VB.Label lblSelectedValue 
      AutoSize        =   -1  'True
      Caption         =   "Selected Node Value:"
      Height          =   195
      Left            =   120
      TabIndex        =   26
      Top             =   3000
      Width           =   1560
   End
   Begin VB.Line Line1 
      X1              =   0
      X2              =   9240
      Y1              =   5400
      Y2              =   5400
   End
   Begin VB.Label lblPatternResults 
      AutoSize        =   -1  'True
      Caption         =   "Pattern Results:"
      Height          =   195
      Left            =   120
      TabIndex        =   25
      Top             =   5520
      Width           =   1125
   End
   Begin VB.Label lblNodes 
      AutoSize        =   -1  'True
      Caption         =   "Available Nodes:"
      Height          =   195
      Left            =   120
      TabIndex        =   24
      Top             =   1440
      Width           =   1200
   End
   Begin VB.Label lblLoad 
      Caption         =   "No XML File Loaded"
      Height          =   615
      Left            =   1800
      TabIndex        =   23
      Top             =   240
      Width           =   5415
   End
   Begin VB.Label lblPatternString 
      AutoSize        =   -1  'True
      Caption         =   "Pattern String:"
      Height          =   195
      Left            =   120
      TabIndex        =   22
      Top             =   720
      Width           =   1005
   End
End
Attribute VB_Name = "XSL_Pattern"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdAdd1_Click()

  txtPattern.Text = txtPattern.Text & Trim(lstContext.Text) ' add to Pattern string
  
  If lstContext.Text <> "" Then lstContext.Selected(lstContext.ListIndex) = False
  
End Sub

Private Sub cmdAdd2_Click()

  txtPattern.Text = txtPattern.Text & Trim(lstChars.Text) ' add to Pattern string
  
  If lstChars.Text <> "" Then lstChars.Selected(lstChars.ListIndex) = False
  
End Sub

Private Sub cmdAdd3_Click()

  txtPattern.Text = txtPattern.Text & lstExpressions.Text ' add to Pattern string

  If lstExpressions.Text <> "" Then lstExpressions.Selected(lstExpressions.ListIndex) = False
  
End Sub

Private Sub cmdAdd4_Click()

  If txtValue.Text <> "" Then txtPattern.Text = txtPattern.Text & "[text() = '" & txtValue.Text & "']"  ' add to Pattern string

End Sub

Private Sub cmdAdd5_Click()

  txtPattern.Text = txtPattern.Text & lstMethods.Text ' add to Pattern string

  If lstMethods.Text <> "" Then lstMethods.Selected(lstMethods.ListIndex) = False
  
End Sub

Private Sub cmdAdd6_Click()

  If txtAttributeValue.Text <> "" Then txtPattern.Text = txtPattern.Text & "[text() = '" & txtAttributeValue.Text & "']"  ' add to Pattern string

End Sub

Private Sub cmdClear_Click()
  
  txtPattern.Text = "" ' Clear the Pattern string
  
End Sub

Private Sub cmdDrill_Click()

  If lstNodes.Text = "" Then
    MsgBox "Please select a node before drilling down."
    Exit Sub
  Else
    'MsgBox lstNodes.ListIndex
    
    Call Find_Nodes(1) ' Find the next set of nodes
    
    cmdDrill.Enabled = False ' Turn off because we don't know if nodes exist below current position
    
    lstAttributes.Clear ' Empty Attributes select box
    txtAttributeValue.Text = "" ' empty attribute value box
    txtValue.Text = "" ' empty node value box
    
  End If
    
End Sub

Private Sub cmdDrillup_Click()

  Call Find_Nodes(2) ' Reload the nodes above current position in tree
  
  cmdDrill.Enabled = False ' Turn off because we don't know if nodes exist below current position
    
  lstAttributes.Clear ' Empty Attributes select box
  txtAttributeValue.Text = "" ' empty attribute value box
  txtValue.Text = "" ' empty node value box
    
End Sub


Private Sub cmdLoad_Click()

On Error Resume Next

FileOpen1.FileName = "*.xml" ' reset the filename to XML file type

FileOpen1.Action = 1 ' Open XML File

DoEvents

If InStr(FileOpen1.FileName, "*") Then Exit Sub

XSL_Pattern.MousePointer = 11 ' hourglass

DoEvents

Load_XML_File (FileOpen1.FileName) ' Load File

If doc.parseError.reason <> "" Then

  lblLoad.Caption = "Loaded XML File has errors: " & FileOpen1.FileName

Else

  lblLoad.Caption = "Loaded XML File: " & FileOpen1.FileName

End If

XSL_Pattern.MousePointer = 0 ' default pointer

On Error GoTo 0

End Sub

Private Sub cmdPattern_Click()

  If txtPattern.Text = "" Then Exit Sub ' no Pattern then don't run
  
  On Error GoTo Pattern_Error
  
  Dim Pattern_Results As Object
  Dim Output As String
  Dim Node As Object
  
  txtPatternResults.Text = "" ' Clear results box before Pattern
  
  Set Pattern_Results = doc.documentElement.selectNodes(txtPattern.Text)
        
  For Each Node In Pattern_Results
     
    Output = Output + Node.xml ' build output string

  Next
  
  txtPatternResults.Text = Output ' display the XSL pattern result set
    
  Set Pattern_Results = Nothing
  Set Node = Nothing
  
  On Error GoTo 0
  
  Exit Sub
  
Pattern_Error:

  MsgBox "There was a problem with your Pattern:" & Chr$(13) & Chr$(13) & Error
    
  Set Pattern_Results = Nothing
  Set Node = Nothing
  
  On Error GoTo 0
  
End Sub

Private Sub cmdView_Click()

    If cmdView.Caption = "&View XML" Then
    
        XSL_Pattern.Width = 15360 ' Expand window
  
        cmdView.Caption = "&Hide XML"
        
    Else
    
        XSL_Pattern.Width = 9360 ' Shrink window
  
        cmdView.Caption = "&View XML"
        
    End If
    
End Sub

Private Sub Form_Unload(Cancel As Integer)

    Set doc = Nothing ' Close open XML document object
    
End Sub

Private Sub lstAttributes_Click()

  On Error Resume Next
  
  Dim Temp_Pattern As String
  Dim Tree_Position As Object
  
  If XSL_Pattern.lblNodes.Caption = "Available Nodes:" Then
  
    Temp_Pattern = "*[" & XSL_Pattern.lstNodes.ListIndex & "]"
  
  Else
  
    Temp_Pattern = Mid(XSL_Pattern.lblNodes.Caption, 17, Len(XSL_Pattern.lblNodes.Caption)) & "/" & lstNodes.Text
          
  End If
  
  Set Tree_Position = doc.documentElement.selectNodes(Temp_Pattern)
    
  Set Tree_Position = Tree_Position.nextNode()
 
  txtAttributeValue.Text = Tree_Position.Attributes.Item(lstAttributes.ListIndex).nodeValue
  
  Set Tree_Position = Nothing
  
End Sub

Private Sub lstAttributes_DblClick()

  If (Right(txtPattern.Text, 1) <> "/" And Right(txtPattern.Text, 1) <> "") Then txtPattern.Text = txtPattern.Text & "/"
  
  txtPattern.Text = txtPattern.Text & "@" & lstAttributes.Text ' add to Pattern string

End Sub

Private Sub lstChars_DblClick()

  txtPattern.Text = txtPattern.Text & Trim(lstChars.Text) ' add to Pattern string
  
  If lstChars.Text <> "" Then lstChars.Selected(lstChars.ListIndex) = False
  
End Sub

Private Sub lstContext_DblClick()
  
  txtPattern.Text = txtPattern.Text & Trim(lstContext.Text) ' add to Pattern string
  
  If lstContext.Text <> "" Then lstContext.Selected(lstContext.ListIndex) = False
  
End Sub

Private Sub lstExpressions_DblClick()

  txtPattern.Text = txtPattern.Text & lstExpressions.Text ' add to Pattern string

  If lstExpressions.Text <> "" Then lstExpressions.Selected(lstExpressions.ListIndex) = False
  
End Sub

Private Sub lstMethods_DblClick()
 
  txtPattern.Text = txtPattern.Text & lstMethods.Text ' add to Pattern string

  If lstMethods.Text <> "" Then lstMethods.Selected(lstMethods.ListIndex) = False
  
End Sub

Private Sub lstNodes_Click()

  On Error Resume Next
  
  Dim Temp_Pattern As String
  Dim intY As Double
  Dim Tree_Position As Object
  
  intY = 0
  
  cmdDrill.Enabled = False ' Disable drilling down until a node is found
  lstAttributes.Clear ' Empty attribute select box
  
  If XSL_Pattern.lblNodes.Caption = "Available Nodes:" Then
  
    Temp_Pattern = "*[" & XSL_Pattern.lstNodes.ListIndex & "]"
  
  Else
  
    Temp_Pattern = Mid(XSL_Pattern.lblNodes.Caption, 17, Len(XSL_Pattern.lblNodes.Caption)) & "/" & lstNodes.Text
          
  End If
  
  Set Tree_Position = doc.documentElement.selectNodes(Temp_Pattern)
    
  Set Tree_Position = Tree_Position.nextNode()
 
  For intY = 0 To (Tree_Position.Attributes.length - 1) ' Find all attributes for selected node
      
        lstAttributes.AddItem (Tree_Position.Attributes.Item(intY).nodeName)
        
  Next
      
  If Tree_Position.childNodes.Item(0).nodeType = 3 Then ' If text node then display text
  
        txtValue.Text = Tree_Position.childNodes.Item(0).Text
          
  Else
  
    txtValue.Text = ""
    
  End If

  If txtValue.Text = "" Or Tree_Position.childNodes.length > 1 Then ' If no text node then enable drilling down
  
    cmdDrill.Enabled = True
       
  End If
  
  Set Tree_Position = Nothing
  
End Sub

Private Sub lstNodes_DblClick()

   If (Right(txtPattern.Text, 1) <> "/" And Right(txtPattern.Text, 1) <> "") Then txtPattern.Text = txtPattern.Text & "/"
   
   txtPattern.Text = txtPattern.Text & lstNodes.Text ' add to Pattern string

End Sub

