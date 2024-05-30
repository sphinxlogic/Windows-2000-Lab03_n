VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Cutlist Player"
   ClientHeight    =   8865
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9660
   LinkTopic       =   "Form1"
   ScaleHeight     =   8865
   ScaleWidth      =   9660
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox AudioStreams 
      Height          =   450
      Left            =   6720
      TabIndex        =   10
      Top             =   8040
      Width           =   2535
   End
   Begin VB.CommandButton NextMovie 
      Caption         =   "Next Movie"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   4800
      TabIndex        =   7
      Top             =   7800
      Width           =   1455
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   2760
      TabIndex        =   6
      Top             =   7800
      Width           =   1455
   End
   Begin VB.CommandButton PlayPause 
      Caption         =   "Play"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   720
      TabIndex        =   5
      Top             =   7800
      Width           =   1455
   End
   Begin VB.Frame movie 
      Height          =   6495
      Left            =   480
      TabIndex        =   4
      Top             =   1080
      Width           =   8775
   End
   Begin VB.TextBox Status 
      Height          =   375
      Left            =   4440
      TabIndex        =   3
      Text            =   "No Movie"
      Top             =   600
      Width           =   3375
   End
   Begin VB.TextBox MovieName 
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   600
      Width           =   3495
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   5280
      Top             =   8160
   End
   Begin VB.Label Label3 
      Caption         =   "Audio stream select"
      Height          =   495
      Left            =   6720
      TabIndex        =   11
      Top             =   7680
      Width           =   2535
   End
   Begin VB.Label Time 
      Caption         =   "0.0"
      Height          =   375
      Left            =   8040
      TabIndex        =   9
      Top             =   600
      Width           =   1335
   End
   Begin VB.Label MovieTime 
      Caption         =   "Movie Time"
      Height          =   375
      Left            =   8160
      TabIndex        =   8
      Top             =   240
      Width           =   1095
   End
   Begin VB.Label Label2 
      Caption         =   "Scheduled movie"
      Height          =   375
      Left            =   4440
      TabIndex        =   2
      Top             =   240
      Width           =   2175
   End
   Begin VB.Label Label1 
      Caption         =   "Movie"
      Height          =   375
      Left            =   480
      TabIndex        =   1
      Top             =   240
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim WithEvents MF As MultiF
Attribute MF.VB_VarHelpID = -1
Dim MC As IMediaControl
Dim VW As IVideoWindow
'  Our playlist
Private Type MovieItem
    movie As String
    Start As Long
    Length As Long
    StartTime As Long
    Offset As Long
    Title As String
    GotStart As Boolean
End Type
Dim NumberOfCuts As Integer
Dim CutNumber As Integer
Dim Cuts() As MovieItem

Private Sub AudioStreams_Click()
MF.SetAudioStream (CLng(AudioStreams.ListIndex))
End Sub

Private Sub Form_Load()

'  Use pixels
ScaleMode = 3

'  Read in the cut list
Open "cuts.lst" For Input As 1
ReDim Cuts(1 To 1)
NumberOfCuts = 0
While Not EOF(1)
    NumberOfCuts = NumberOfCuts + 1
    ReDim Preserve Cuts(1 To NumberOfCuts)
    Input #1, Cuts(NumberOfCuts).movie, Cuts(NumberOfCuts).Start, Cuts(NumberOfCuts).Length, _
          Cuts(NumberOfCuts).Title, Cuts(NumberOfCuts).Offset
    Cuts(NumberOfCuts).GotStart = False
Wend
Close 1

CutNumber = 0
Set MF = New MultiF
SetMovie False
'  Find audio stream info
Dim lStream As Long
For lStream = 0 To 100
    Dim name As String
    Dim selected As Long
    name = MF.GetAudioStream(lStream, selected)
    If IsNull(name) Then
        Exit For
    End If
    AudioStreams.AddItem (name)
    If Not selected = 0 Then
        AudioStreams.ListIndex = lStream
    End If
Next lStream

Set MC = MF.GetGraph
Set VW = MC
VW.WindowStyle = CLng(&H6000000)
VW.Owner = movie.hWnd
'  Position the window inside our frame
VW.SetWindowPosition 0, 0, CLng(movie.Width), CLng(movie.Height)
'MC.Run
End Sub
Private Sub SetMovie(Flush As Boolean)
    Dim lSecs As Long
    Dim lMs As Long
    If CutNumber < NumberOfCuts Then
        CutNumber = CutNumber + 1
        'MovieName.Text = Cuts(CutNumber).movie
        Dim flags As SetFileFlags
        If CutNumber = NumberOfCuts Then
            '  Set last movie
            flags = sffLast
        Else
            flags = 0
        End If
        If Flush Then
            flags = flags + sffFlush
        End If
        MF.SetFile Cuts(CutNumber).movie, Cuts(CutNumber).Start, 0, _
            Cuts(CutNumber).Length, 0, Cuts(CutNumber).Offset, CutNumber, flags
    Else
        MovieName.Text = "No Movie"
        Status.Text = "End Of Movies"
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
Timer1.Enabled = False
Set MF = Nothing
Set MC = Nothing
Set VW = Nothing
End Sub

Private Sub Label4_Click()

End Sub

Private Sub MF_OnComplete(ByVal FileId As Long)
If FileId < NumberOfCuts Then
    If Not (FileId = CutNumber) Then
        MsgBox ("Cut number wrong" & FileId & NumberOfCuts)
    End If
    SetMovie False
End If
End Sub
Private Sub MF_OnPlaybackComplete()
Status.Text = "Playback complete"
End Sub

Private Sub MF_OnFileStart(ByVal FileId As Long, ByVal Seconds As Long, ByVal Milliseconds As Long)
    Status.Text = "Cut " & FileId & " started at " & Seconds & " seconds"
    Cuts(FileId).StartTime = Seconds
    Cuts(FileId).GotStart = True
    MF.SetTimer Seconds, Milliseconds, FileId
End Sub
Private Sub MF_OnTimer(ByVal TimerId As Long)
'Title.Caption = Cuts(TimerId).Title
MovieName.Text = Cuts(TimerId).Title
End Sub
Private Sub NextMovie_Click()
'  Don't want for notification
SetMovie True
End Sub

Private Sub PlayPause_Click()
If PlayPause.Caption = "Play" Then
    PlayPause.Caption = "Pause"
    Form1.Stop.Enabled = True
    MC.Run
Else
    PlayPause.Caption = "Play"
    MC.Pause
End If
End Sub

Private Sub Stop_Click()
    MC.Stop
    Form1.Stop.Enabled = False
    Form1.PlayPause.Caption = "Play"
End Sub

Private Sub Timer1_Timer()
Dim MP As IMediaPosition
Set MP = MC
Time.Caption = Format(MP.CurrentPosition, "Fixed")
Set MP = Nothing
End Sub
