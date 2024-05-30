VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.2#0"; "COMCTL32.OCX"
Begin VB.Form frmMonitor 
   Caption         =   "Trigger Monitor"
   ClientHeight    =   3420
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5775
   LinkTopic       =   "Form1"
   ScaleHeight     =   3420
   ScaleWidth      =   5775
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdBeginMonitor 
      Caption         =   "Begin Monitor"
      Height          =   495
      Left            =   3120
      TabIndex        =   13
      Top             =   2880
      Width           =   1215
   End
   Begin VB.TextBox txtMsgCount 
      Height          =   375
      Left            =   4560
      TabIndex        =   12
      Top             =   1920
      Width           =   975
   End
   Begin VB.TextBox txtPollingFrequency 
      Height          =   375
      Left            =   2160
      TabIndex        =   11
      Top             =   1920
      Width           =   1215
   End
   Begin VB.CommandButton cmdPollingConfig 
      Caption         =   "Polling Frequency"
      Height          =   495
      Left            =   120
      TabIndex        =   9
      Top             =   2880
      Width           =   1575
   End
   Begin VB.Timer Timer1 
      Left            =   240
      Top             =   720
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   495
      Left            =   4440
      TabIndex        =   0
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton cmdConfigure 
      Caption         =   "Settings"
      Height          =   495
      Left            =   1800
      TabIndex        =   1
      Top             =   2880
      Width           =   1215
   End
   Begin ComctlLib.ProgressBar ProgressBar1 
      Height          =   375
      Left            =   960
      TabIndex        =   4
      Top             =   1200
      Width           =   4575
      _ExtentX        =   8070
      _ExtentY        =   661
      _Version        =   327682
      Appearance      =   1
   End
   Begin VB.TextBox txtQueueName 
      Enabled         =   0   'False
      Height          =   375
      Left            =   960
      TabIndex        =   2
      Top             =   240
      Width           =   4575
   End
   Begin VB.Label Label4 
      Caption         =   "Message Count:"
      Height          =   375
      Left            =   3720
      TabIndex        =   14
      Top             =   1920
      Width           =   735
   End
   Begin VB.Label Label3 
      Caption         =   "Polling Frequency (sec) :"
      Height          =   255
      Left            =   240
      TabIndex        =   10
      Top             =   2040
      Width           =   1815
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Count:"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1320
      Width           =   615
   End
   Begin VB.Label lblProgressMax 
      Caption         =   "Max"
      Height          =   255
      Left            =   5040
      TabIndex        =   7
      Top             =   840
      Width           =   495
   End
   Begin VB.Label lblThreshold 
      Caption         =   "Threshold"
      Height          =   255
      Left            =   3600
      TabIndex        =   6
      Top             =   840
      Width           =   735
   End
   Begin VB.Label lblProgress0 
      Caption         =   "0"
      Height          =   255
      Left            =   960
      TabIndex        =   5
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Queue:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   360
      Width           =   615
   End
End
Attribute VB_Name = "frmMonitor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
    Public qTargetQueue As New MSMQQueue
    Public qinfoTargetQueue As New MSMQQueueInfo

Private Sub cmdBeginMonitor_Click()
    If Timer1.Enabled Then
        Timer1.Enabled = False
        cmdBeginMonitor.Caption = "Begin Monitor"
    Else
        Timer1.Enabled = True
        cmdBeginMonitor.Caption = "Stop Monitor"
    End If
End Sub

Private Sub cmdClose_Click()
    'Clean up and exit
    Unload frmConfig
    Unload frmMonitor
End Sub

Private Sub cmdConfigure_Click()
    frmConfig.Show vbModal
    InitGlobals
    InitControls
End Sub

Sub InitControls()
    'initialize controls
    txtQueueName = sQueueName
    txtPollingFrequency = iPollingFrequency
    lblProgress0 = "0"
    lblThreshold = iThreshold
    lblProgressMax = (1 + iThreshold) * 3 \ 2
    lblProgressMax.Refresh
    ProgressBar1.Min = 0
    ProgressBar1.Max = (1 + iThreshold) * 3 \ 2
    Timer1.Enabled = False
    Timer1.Interval = iPollingFrequency * 1000
End Sub

Private Sub cmdPollingConfig_Click()
    frmPollingConfig.Show vbModal
    iPollingFrequency = GetSetting("MQTrigger", "Settings", "PollingFrequency")
    txtPollingFrequency = iPollingFrequency
    Timer1.Interval = iPollingFrequency * 1000
End Sub

Private Sub OpenQueue()
    On Error GoTo ErrHandler
    
    'verify queue exists
    qinfoTargetQueue.PathName = txtQueueName
    Set qTargetQueue = qinfoTargetQueue.Open(Access:=MQ_PEEK_ACCESS, ShareMode:=MQ_DENY_NONE)
    qTargetQueue.Close
    Exit Sub
ErrHandler:
    MsgBox txtQueueName & " is an invalid Queue pathname", vbOKOnly, "Queue Open Failure"
    cmdConfigure_Click
    Resume

End Sub

Private Sub Form_Load()
    InitControls
    OpenQueue
End Sub

Private Sub Timer1_Timer()
    Dim dwNumMessages As Long
    Dim TriggerMsg As String
    
    dwNumMessages = GetPerfmonInfo(qinfoTargetQueue.PathName)
    If ProgressBar1.Max < dwNumMessages Then
        ' max the bar do nothing else (to avoid overflowing the progress bar)
        ProgressBar1 = ProgressBar1.Max
    Else
        ProgressBar1 = dwNumMessages
    End If
    txtMsgCount = dwNumMessages
    If dwNumMessages > iThreshold Then
        TriggerMsg = "Trigger: " & txtMsgCount & " messages in queue."
        MsgBox TriggerMsg, vbSystemModal, "Trigger Event"
    End If
End Sub
