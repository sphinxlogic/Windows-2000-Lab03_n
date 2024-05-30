VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3900
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5160
   LinkTopic       =   "Form1"
   ScaleHeight     =   3900
   ScaleWidth      =   5160
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSet 
      Caption         =   "Set"
      Height          =   375
      Left            =   1560
      TabIndex        =   9
      Top             =   3360
      Width           =   1455
   End
   Begin VB.CommandButton cmdGet 
      Caption         =   "Get"
      Height          =   375
      Left            =   3720
      TabIndex        =   2
      Top             =   600
      Width           =   1335
   End
   Begin VB.Frame Frame1 
      Caption         =   "CallBack"
      Height          =   1575
      Left            =   120
      TabIndex        =   4
      Top             =   1560
      Width           =   4935
      Begin VB.TextBox phoneNumber 
         Height          =   375
         Left            =   1680
         TabIndex        =   8
         Text            =   "Text2"
         Top             =   960
         Width           =   1935
      End
      Begin VB.OptionButton setByAdmin 
         Caption         =   "Preset To:"
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   960
         Width           =   1095
      End
      Begin VB.OptionButton setByTheCaller 
         Caption         =   "Set By The Caller"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   600
         Width           =   2655
      End
      Begin VB.OptionButton noCallBack 
         Caption         =   "NoCallBack"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   1935
      End
   End
   Begin VB.CheckBox chkDialin 
      Caption         =   "Dial-in Permission"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   2175
   End
   Begin VB.TextBox adsPath 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   600
      Width           =   3375
   End
   Begin VB.Label Label1 
      Caption         =   "User ADsPath"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public x



Private Sub cmdGet_Click()
Set x = GetObject(adsPath)
If (x.DialinPrivilege = True) Then
  chkDialin.Value = 1
Else
  chkDialin.Value = 0
End If

l = x.GetRasCallBack
If (l And ADS_RAS_NOCALLBACK) Then
  noCallBack = True
ElseIf (l And ADS_RAS_CALLER_SETCALLBACK) Then
  setByTheCaller = True
ElseIf (l And ADS_RAS_ADMIN_SETCALLBACK) Then
  setByAdmin = True
  phoneNumber = x.GetRasPhoneNumber
End If



End Sub

Private Sub cmdSet_Click()
If (chkDialin.Value = 0) Then
   x.DialinPrivilege = False
Else
   x.DialinPrivilege = True
End If
   

If (noCallBack) Then
  x.SetRasCallBack ADS_RAS_NOCALLBACK
ElseIf (setByTheCaller) Then
  x.SetRasCallBack ADS_RAS_CALLER_SETCALLBACK
ElseIf (setByAdmin) Then
  x.SetRasCallBack ADS_RAS_ADMIN_SETCALLBACK, phoneNumber
End If

End Sub

Private Sub Form_Load()

End Sub

