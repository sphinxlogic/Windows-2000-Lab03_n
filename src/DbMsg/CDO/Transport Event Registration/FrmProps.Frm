VERSION 5.00
Begin VB.Form frmProps 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   3075
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6915
   Icon            =   "frmProps.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   3075
   ScaleWidth      =   6915
   Begin VB.CommandButton cmdViewPropBag 
      Caption         =   "&View Property Bag"
      Height          =   375
      Left            =   2160
      TabIndex        =   5
      Top             =   1920
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.ListBox lstProps 
      Height          =   2790
      ItemData        =   "frmProps.frx":0442
      Left            =   240
      List            =   "frmProps.frx":0444
      TabIndex        =   0
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label lblValue 
      Height          =   495
      Left            =   2280
      TabIndex        =   4
      Top             =   1920
      Width           =   4575
   End
   Begin VB.Label lblName 
      Height          =   495
      Left            =   2280
      TabIndex        =   3
      Top             =   840
      Width           =   4575
   End
   Begin VB.Label Label2 
      Caption         =   "Property Value:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2040
      TabIndex        =   2
      Top             =   1560
      Width           =   1935
   End
   Begin VB.Label Label1 
      Caption         =   "Property Name"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2040
      TabIndex        =   1
      Top             =   480
      Width           =   1575
   End
End
Attribute VB_Name = "frmProps"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim mvarMetaDict As CSEOMetaDictionary

Property Set Props(MetaDict As CSEOMetaDictionary)
    Dim I As Integer

    Set mvarMetaDict = MetaDict
    
    For I = 1 To mvarMetaDict.Count
        lstProps.AddItem mvarMetaDict.Name(I)
    Next
    If mvarMetaDict.Count > 0 Then
        lstProps.Selected(0) = True
    End If
End Property

Private Sub cmdViewPropBag_Click()
    Dim frm As New frmProps
    
    frm.Caption = Me.Caption & " : " & lstProps.List(lstProps.ListIndex)
    Set frm.Props = mvarMetaDict.Item(lstProps.ListIndex + 1)
    frm.Left = Me.Left + 300
    frm.Top = Me.Top + 300
    If ((frm.Left + frm.Width) > (frmEventRegister.Left + frmEventRegister.Width)) Or _
        ((frm.Top + frm.Height) > (frmEventRegister.Top + frmEventRegister.Height)) Then
        frm.Left = frmEventRegister.Left + 300
        frm.Top = frmEventRegister.Top + 300
    End If
    frm.Show vbModal, Me
End Sub

Private Sub lstProps_Click()
    On Error GoTo Novalue
    
    cmdViewPropBag.Visible = False
    lblName.Caption = lstProps.List(lstProps.ListIndex)
    lblValue.Caption = mvarMetaDict.Item(lstProps.ListIndex + 1)
    lblValue.Font.Italic = False
    
    Exit Sub
Novalue:
    If Err.Number = 450 Then
        cmdViewPropBag.Visible = True
        lblValue.Caption = ""
    Else
        lblValue.Caption = "<No value available>"
        lblValue.Font.Italic = True
    End If
End Sub
