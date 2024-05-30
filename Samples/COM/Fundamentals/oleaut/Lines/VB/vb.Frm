VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2745
   ClientLeft      =   870
   ClientTop       =   1530
   ClientWidth     =   4785
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2745
   ScaleWidth      =   4785
   Begin VB.CommandButton RemoveTest 
      Caption         =   "RemoveTest"
      Height          =   372
      Left            =   1200
      TabIndex        =   2
      Top             =   1680
      Width           =   2292
   End
   Begin VB.CommandButton Clear 
      Caption         =   "Clear"
      Height          =   372
      Left            =   1200
      TabIndex        =   1
      Top             =   960
      Width           =   2292
   End
   Begin VB.CommandButton DrawLines 
      Caption         =   "Draw Lines"
      Height          =   372
      Left            =   1200
      TabIndex        =   0
      Top             =   240
      Width           =   2292
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'VB script to control the Lines automation server.

'Use the Tools/References menu to select the Lines type library before
'running this code.

Dim Application As IApplication
Dim Pane As IPane
Dim Lines As ILines
Dim L As ILine
Dim P1, P2 As IPoint

Private Sub Form_Load()
 Set Application = New Lines.Lines   'The first Lines in Lines.Lines is the library name;
                           'the second is the coclass. If the coclass and the
                           'library did'nt have the same name, just the coclass
                           'would be sufficient have been sufficient. i.e. Set Application = New Lines
                           'New Lines.Lines will create an object that supports the default
                           'interface (IApplication) of the Lines coclass
 Application.Visible = True
 Set Pane = Application.Pane
End Sub

'Draw 10 lines
Private Sub DrawLines_Click()
 Set Lines = Pane.Lines

 'Anchor one end point
 Set P1 = Application.CreatePoint()
 P1.x = 4500    'in twips
 P1.y = 4500    'in twips
 
  'Add 10 lines to the Lines collection. The Lines server can handle a maximum of 100 lines
 For I = 1 To 10
   'Create other end point of line
   Set P2 = Application.CreatePoint()
   P2.x = Int(9000 * Rnd + 1)   'in twips
   P2.y = Int(9000 * Rnd + 1)   'in twips
   
   'Create line
   Set L = Application.CreateLine()
   Set L.StartPoint = P1
   Set L.EndPoint = P2
   L.Thickness = 100             'in twips
   'Select a random color
   L.Color = RGB(Int(255 * Rnd + 1), Int(255 * Rnd + 1), Int(255 * Rnd + 1))
   
   'Add line to Lines collection
   Lines.Add L
 Next I
End Sub

'Clear the pane and remove all lines from collection
Private Sub Clear_Click()
 Pane.Clear
End Sub

'Remove the first line
Private Sub RemoveTest_Click()
  Set Lines = Pane.Lines
  Lines.Remove 1
  Debug.Print Lines.Count   'Print the number of lines in collection after line removal
End Sub

