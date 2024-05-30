VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   8190
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   11325
   LinkTopic       =   "Form1"
   ScaleHeight     =   8190
   ScaleWidth      =   11325
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtDetails 
      Height          =   975
      Left            =   360
      MultiLine       =   -1  'True
      TabIndex        =   3
      Text            =   "Form1.frx":0000
      Top             =   6960
      Width           =   9015
   End
   Begin VB.ListBox lstDetails 
      Height          =   4935
      Left            =   5520
      TabIndex        =   2
      Top             =   840
      Width           =   5055
   End
   Begin VB.ListBox lstMain 
      Height          =   4935
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   5175
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   1080
      TabIndex        =   0
      Text            =   "http://adot20/davfs/"
      Top             =   0
      Width           =   7335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim grec As Record
Dim grs As Recordset

Private Sub Form_Load()
    Set grec = New Record
    Set grs = New Recordset
    'Replace URL value with your server information. MyServer is name of your server.
    'DAVfs is a DAV filestore on that server.
    grec.Open "", "URL=http://MyServer/DAVfs/", , adOpenIfExists Or adCreateCollection
    Set grs = grec.GetChildren
    While Not grs.EOF
        lstMain.AddItem grs(0)
        grs.MoveNext
    Wend
End Sub

Private Sub lstMain_Click()
    Dim rec As Record
    Dim rs As Recordset
    Set rec = New Record
    Set rs = New Recordset
    grs.MoveFirst
    grs.Move lstMain.ListIndex
    lstDetails.Clear
    rec.Open grs
    Select Case rec.RecordType
        Case adCollectionRecord:
            Set rs = rec.GetChildren
            While Not rs.EOF
                lstDetails.AddItem rs(0)
                rs.MoveNext
            Wend
        Case adSimpleRecord:
            recFields rec, lstDetails, txtDetails
            
        Case adStructDoc:
    End Select
    
End Sub
