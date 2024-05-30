VERSION 5.00
Object = "{177CF4A3-E7E0-11D0-B8E7-0000F81ECCE7}#1.0#0"; "JChart.tlb"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6750
   ClientLeft      =   4480
   ClientTop       =   2750
   ClientWidth     =   7640
   LinkTopic       =   "Form1"
   ScaleHeight     =   6750
   ScaleWidth      =   7640
   Begin JChart.JChart JChart1 
      Height          =   3610
      Left            =   600
      OleObjectBlob   =   "JChart.frx":0000
      TabIndex        =   7
      Top             =   360
      Width           =   6610
   End
   Begin VB.ComboBox ComboFilter 
      Height          =   240
      ItemData        =   "JChart.frx":0665
      Left            =   3240
      List            =   "JChart.frx":066C
      TabIndex        =   5
      Text            =   "Combo1"
      Top             =   6000
      Width           =   2050
   End
   Begin VB.FileListBox File1 
      Height          =   1340
      Left            =   3240
      Pattern         =   "*.txt"
      TabIndex        =   4
      Top             =   4440
      Width           =   2050
   End
   Begin VB.DirListBox Dir1 
      Height          =   1320
      Left            =   5400
      TabIndex        =   3
      Top             =   4440
      Width           =   2170
   End
   Begin VB.DriveListBox Drive1 
      Height          =   240
      Left            =   5400
      TabIndex        =   2
      Top             =   6000
      Width           =   2170
   End
   Begin VB.ComboBox listChartType 
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
      ItemData        =   "JChart.frx":067D
      Left            =   600
      List            =   "JChart.frx":068D
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   4440
      Width           =   1450
   End
   Begin VB.Label Label2 
      Caption         =   "Select an Excel text data file"
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
      Left            =   3360
      TabIndex        =   6
      Top             =   4200
      Width           =   2170
   End
   Begin VB.Label Label1 
      Caption         =   "The chart type:"
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
      Left            =   600
      TabIndex        =   1
      Top             =   4200
      Width           =   1330
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False



Private Sub ComboFilter_Change()
File1.Pattern = ComboFilter.Text
End Sub

Private Sub ComboFilter_Click()
File1.Pattern = ComboFilter.Text
End Sub

Private Sub Dir1_Change()
File1.Path = Dir1.Path
End Sub

Private Sub Drive1_Change()
Dir1.Path = Drive1.Drive
End Sub

Private Sub File1_Click()
JChart1.dataFileName = File1.Path & "\" & File1.filename
End Sub

Private Sub Form_Load()
listChartType.ListIndex = 0
ComboFilter.ListIndex = 0
End Sub

Private Sub listChartType_Click()
JChart1.chartType = listChartType.ListIndex + 1
End Sub
