VERSION 5.00
Object = "{6F146B03-E7CF-11D0-B8E7-0000F81ECCE7}#1.0#0"; "JCalendar.tlb"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4460
   ClientLeft      =   4930
   ClientTop       =   3660
   ClientWidth     =   6560
   LinkTopic       =   "Form1"
   ScaleHeight     =   4460
   ScaleWidth      =   6560
   Begin VB.CommandButton nextMonth 
      Caption         =   "next month"
      Height          =   490
      Left            =   600
      TabIndex        =   6
      Top             =   3960
      Width           =   970
   End
   Begin VB.TextBox yearText 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.29
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   320
      Left            =   3720
      TabIndex        =   4
      Text            =   "Text1"
      Top             =   480
      Width           =   1210
   End
   Begin VB.ComboBox monthList 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.29
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   280
      ItemData        =   "JCalendar.frx":0000
      Left            =   1560
      List            =   "JCalendar.frx":002A
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   480
      Width           =   1330
   End
   Begin JCalendar.JCalendar JCalendar1 
      Height          =   2890
      Left            =   960
      OleObjectBlob   =   "JCalendar.frx":0090
      TabIndex        =   0
      Top             =   960
      Width           =   4570
   End
   Begin VB.Label Label3 
      Caption         =   "Year"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.29
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   250
      Left            =   3720
      TabIndex        =   5
      Top             =   240
      Width           =   850
   End
   Begin VB.Label Label2 
      Caption         =   "Month"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.29
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   250
      Left            =   1560
      TabIndex        =   3
      Top             =   240
      Width           =   490
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   370
      Left            =   2880
      TabIndex        =   2
      Top             =   2040
      Width           =   850
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub JCalendar1_yearChanged(ByVal Parameter0 As Long, ByVal Parameter1 As Long)
yearText.Text = JCalendar1.Year
End Sub

Private Sub monthList_Click()
JCalendar1.Month = monthList.ListIndex
End Sub

Private Sub Form_Load()
monthList.ListIndex = JCalendar1.Month
yearText.Text = JCalendar1.Year
End Sub

Private Sub JCalendar1_monthChanged(ByVal Parameter0 As String, ByVal Parameter1 As String)
monthList.ListIndex = JCalendar1.Month
End Sub

Private Sub yearText_Change()
JCalendar1.Year = yearText.Text
End Sub

Private Sub nextMonth_Click()
JCalendar1.nextMonth
End Sub
